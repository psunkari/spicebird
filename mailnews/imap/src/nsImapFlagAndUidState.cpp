/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1999
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Pierre Phaneuf <pp@ludusdesign.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "msgCore.h"  // for pre-compiled headers

#include "nsImapCore.h"
#include "nsImapFlagAndUidState.h"
#include "prcmon.h"
#include "nspr.h"
#include "nsAutoLock.h"

NS_IMPL_THREADSAFE_ISUPPORTS1(nsImapFlagAndUidState, nsIImapFlagAndUidState)

NS_IMETHODIMP nsImapFlagAndUidState::GetNumberOfMessages(PRInt32 *result)
{
  if (!result)
    return NS_ERROR_NULL_POINTER;
  *result = fNumberOfMessagesAdded;
  return NS_OK;
}

NS_IMETHODIMP nsImapFlagAndUidState::GetUidOfMessage(PRInt32 zeroBasedIndex, PRUint32 *result)
{
  if (!result)
    return NS_ERROR_NULL_POINTER;
  
  PR_CEnterMonitor(this);
  if (zeroBasedIndex < fNumberOfMessagesAdded)
    *result = fUids[zeroBasedIndex];
  else
    *result = 0xFFFFFFFF;	// so that value is non-zero and we don't ask for bad msgs
  PR_CExitMonitor(this);
  return NS_OK;
}



NS_IMETHODIMP	nsImapFlagAndUidState::GetMessageFlags(PRInt32 zeroBasedIndex, PRUint16 *result)
{
  if (!result)
    return NS_ERROR_NULL_POINTER;
  imapMessageFlagsType returnFlags = kNoImapMsgFlag;
  if (zeroBasedIndex < fNumberOfMessagesAdded)
    returnFlags = fFlags[zeroBasedIndex];
  
  *result = returnFlags;
  return NS_OK;
}

NS_IMETHODIMP nsImapFlagAndUidState::SetMessageFlags(PRInt32 zeroBasedIndex, unsigned short flags)
{
  if (zeroBasedIndex < fNumberOfMessagesAdded)
    fFlags[zeroBasedIndex] = flags;
  return NS_OK;
}

NS_IMETHODIMP nsImapFlagAndUidState::GetNumberOfRecentMessages(PRInt32 *result)
{
  if (!result)
    return NS_ERROR_NULL_POINTER;
  
  PR_CEnterMonitor(this);
  PRUint32 counter = 0;
  PRInt32 numUnseenMessages = 0;
  
  for (counter = 0; counter < (PRUint32) fNumberOfMessagesAdded; counter++)
  {
    if (fFlags[counter] & kImapMsgRecentFlag)
      numUnseenMessages++;
  }
  PR_CExitMonitor(this);
  
  *result = numUnseenMessages;
  
  return NS_OK;
}

NS_IMETHODIMP nsImapFlagAndUidState::GetPartialUIDFetch(PRBool *aPartialUIDFetch)
{
  NS_ENSURE_ARG_POINTER(aPartialUIDFetch);
  *aPartialUIDFetch = fPartialUIDFetch;
  return NS_OK;
}

/* amount to expand for imap entry flags when we need more */

nsImapFlagAndUidState::nsImapFlagAndUidState(PRInt32 numberOfMessages)
{
  fNumberOfMessagesAdded = 0;
  fNumberOfMessageSlotsAllocated = numberOfMessages;
  if (!fNumberOfMessageSlotsAllocated)
	  fNumberOfMessageSlotsAllocated = kImapFlagAndUidStateSize;
  fFlags = (imapMessageFlagsType*) PR_Malloc(sizeof(imapMessageFlagsType) * fNumberOfMessageSlotsAllocated); // new imapMessageFlagsType[fNumberOfMessageSlotsAllocated];
  
  fUids.InsertElementsAt(0, fNumberOfMessageSlotsAllocated, 0);
  memset(fFlags, 0, sizeof(imapMessageFlagsType) * fNumberOfMessageSlotsAllocated);
  fSupportedUserFlags = 0;
  fNumberDeleted = 0;
  fPartialUIDFetch = PR_TRUE;
  m_customFlagsHash.Init(10);
}

/* static */PLDHashOperator nsImapFlagAndUidState::FreeCustomFlags(const PRUint32 &aKey, char *aData,
                                        void *closure)
{
  PR_Free(aData);
  return PL_DHASH_NEXT;
}

nsImapFlagAndUidState::~nsImapFlagAndUidState()
{
  PR_Free(fFlags);
  if (m_customFlagsHash.IsInitialized())
    m_customFlagsHash.EnumerateRead(FreeCustomFlags, nsnull);
}

NS_IMETHODIMP
nsImapFlagAndUidState::OrSupportedUserFlags(uint16 flags)
{
  fSupportedUserFlags |= flags;
  return NS_OK;
}

NS_IMETHODIMP
nsImapFlagAndUidState::GetSupportedUserFlags(uint16 *aFlags)
{
  NS_ENSURE_ARG_POINTER(aFlags);
  *aFlags = fSupportedUserFlags;
  return NS_OK;
}

// we need to reset our flags, (re-read all) but chances are the memory allocation needed will be
// very close to what we were already using

NS_IMETHODIMP nsImapFlagAndUidState::Reset(PRUint32 howManyLeft)
{
  PR_CEnterMonitor(this);
  if (!howManyLeft)
    fNumberOfMessagesAdded = fNumberDeleted = 0; // used space is still here
  if (m_customFlagsHash.IsInitialized())
    m_customFlagsHash.EnumerateRead(FreeCustomFlags, nsnull);
  memset(fFlags, 0, sizeof(imapMessageFlagsType) * fNumberOfMessageSlotsAllocated);
  m_customFlagsHash.Clear();
  memset(fUids.Elements(), 0, fNumberOfMessageSlotsAllocated * sizeof(nsMsgKey));
  fPartialUIDFetch = PR_TRUE;
  PR_CExitMonitor(this);
  return NS_OK;
}


// Remove (expunge) a message from our array, since now it is gone for good

NS_IMETHODIMP nsImapFlagAndUidState::ExpungeByIndex(PRUint32 msgIndex)
{
  // protect ourselves in case the server gave us an index key of -1.....
  if ((PRInt32) msgIndex < 0)
    return NS_ERROR_INVALID_ARG;

  PRUint32 counter = 0;
  
  if ((PRUint32) fNumberOfMessagesAdded < msgIndex)
    return NS_ERROR_INVALID_ARG;
  
  PR_CEnterMonitor(this);
  msgIndex--;  // msgIndex is 1-relative
  fNumberOfMessagesAdded--;
  if (fFlags[msgIndex] & kImapMsgDeletedFlag)	// see if we already had counted this one as deleted
    fNumberDeleted--;
  for (counter = msgIndex; counter < (PRUint32) fNumberOfMessagesAdded; counter++)
  {
    fUids[counter] = fUids[counter + 1];
    fFlags[counter] = fFlags[counter + 1];                                  
  }

  PR_CExitMonitor(this);
  return NS_OK;
}


// adds to sorted list.  protects against duplicates and going past fNumberOfMessageSlotsAllocated  
NS_IMETHODIMP nsImapFlagAndUidState::AddUidFlagPair(PRUint32 uid, imapMessageFlagsType flags, PRUint32 zeroBasedIndex)
{
  if (uid == nsMsgKey_None) // ignore uid of -1
    return NS_OK;
  // check for potential overflow in buffer size for uid array
  if (zeroBasedIndex > 0x3FFFFFFF)
    return NS_ERROR_INVALID_ARG;
  PR_CEnterMonitor(this);
  if (zeroBasedIndex + 1 > fNumberOfMessagesAdded)
    fNumberOfMessagesAdded = zeroBasedIndex + 1;
  // make sure there is room for this pair
  if (fNumberOfMessagesAdded >= fNumberOfMessageSlotsAllocated)
  {
    PRInt32 sizeToGrowBy = PR_MAX(kImapFlagAndUidStateSize, 
                      fNumberOfMessagesAdded - fNumberOfMessageSlotsAllocated);
    fNumberOfMessageSlotsAllocated += sizeToGrowBy;
    fUids.InsertElementsAt(fUids.Length(), sizeToGrowBy, 0);
    fFlags = (imapMessageFlagsType*) PR_REALLOC(fFlags, sizeof(imapMessageFlagsType) * fNumberOfMessageSlotsAllocated); // new imapMessageFlagsType[fNumberOfMessageSlotsAllocated];
    if (!fFlags)
      return NS_ERROR_OUT_OF_MEMORY;
  }

  fUids[zeroBasedIndex] = uid;
  fFlags[zeroBasedIndex] = flags;
  if (flags & kImapMsgDeletedFlag)
    fNumberDeleted++;
  PR_CExitMonitor(this);
  return NS_OK;
}


NS_IMETHODIMP nsImapFlagAndUidState::GetNumberOfDeletedMessages(PRInt32 *numDeletedMessages)
{
  NS_ENSURE_ARG_POINTER(numDeletedMessages);
  *numDeletedMessages = NumberOfDeletedMessages();
  return NS_OK;
}

PRInt32 nsImapFlagAndUidState::NumberOfDeletedMessages()
{
  return fNumberDeleted;
}
	
// since the uids are sorted, start from the back (rb)

PRUint32  nsImapFlagAndUidState::GetHighestNonDeletedUID()
{
  PRUint32 msgIndex = fNumberOfMessagesAdded;
  do 
  {
    if (msgIndex <= 0)
      return(0);
    msgIndex--;
    if (fUids[msgIndex] && !(fFlags[msgIndex] & kImapMsgDeletedFlag))
      return fUids[msgIndex];
  }
  while (msgIndex > 0);
  return 0;
}


// Has the user read the last message here ? Used when we first open the inbox to see if there
// really is new mail there.

PRBool nsImapFlagAndUidState::IsLastMessageUnseen()
{
  PRUint32 msgIndex = fNumberOfMessagesAdded;
  
  if (msgIndex <= 0)
    return PR_FALSE;
  msgIndex--;
  // if last message is deleted, it was probably filtered the last time around
  if (fUids[msgIndex] && (fFlags[msgIndex] & (kImapMsgSeenFlag | kImapMsgDeletedFlag)))
    return PR_FALSE;
  return PR_TRUE; 
}



// find a message flag given a key with non-recursive binary search, since some folders
// may have thousand of messages, once we find the key set its index, or the index of
// where the key should be inserted

imapMessageFlagsType nsImapFlagAndUidState::GetMessageFlagsFromUID(PRUint32 uid, PRBool *foundIt, PRInt32 *ndx)
{
  PR_CEnterMonitor(this);
  
  PRInt32 msgIndex = 0;
  PRInt32 hi = fNumberOfMessagesAdded - 1;
  PRInt32 lo = 0;
  
  *foundIt = PR_FALSE;
  *ndx = -1;
  while (lo <= hi)
  {
    msgIndex = (lo + hi) / 2;
    if (fUids[msgIndex] == (PRUint32) uid)
    {
      PRInt32 returnFlags = fFlags[msgIndex];
      
      *foundIt = PR_TRUE;
      *ndx = msgIndex;
      PR_CExitMonitor(this);
      return returnFlags;
    }
    if (fUids[msgIndex] > (PRUint32) uid)
      hi = msgIndex -1;
    else if (fUids[msgIndex] < (PRUint32) uid)
      lo = msgIndex + 1;
  }
  msgIndex = lo;
  // leave msgIndex pointing to the first slot with a value > uid
  // first, move it before any ids that are > (shouldn't happen).
  while ((msgIndex > 0) && (fUids[msgIndex - 1] > (PRUint32) uid))
    msgIndex--;
  
  // next, move msgIndex up to the first slot > than uid.
  while ((PRUint32) uid < fUids[msgIndex])
    msgIndex++;
  
  if (msgIndex < 0)
    msgIndex = 0;
  *ndx = msgIndex;
  PR_CExitMonitor(this);
  return 0;
}

NS_IMETHODIMP nsImapFlagAndUidState::AddUidCustomFlagPair(PRUint32 uid, const char *customFlag)
{
  nsAutoCMonitor mon(this);
  if (!m_customFlagsHash.IsInitialized())
    return NS_ERROR_OUT_OF_MEMORY;
  char *ourCustomFlags;
  char *oldValue = nsnull;
  m_customFlagsHash.Get(uid, &oldValue);
  if (oldValue)
  {
  // we'll store multiple keys as space-delimited since space is not
  // a valid character in a keyword. First, we need to look for the
    // customFlag in the existing flags;
    char *existingCustomFlagPtr = PL_strstr(oldValue, customFlag);
    PRUint32 customFlagLen = strlen(customFlag);
    while (existingCustomFlagPtr)
    {
      // if existing flags ends with this exact flag, or flag + ' ', we have this flag already;
      if (strlen(existingCustomFlagPtr) == customFlagLen || existingCustomFlagPtr[customFlagLen] == ' ')
        return NS_OK;
      // else, advance to next flag
      existingCustomFlagPtr = PL_strstr(existingCustomFlagPtr + 1, customFlag);
    }
    ourCustomFlags = (char *) PR_Malloc(strlen(oldValue) + customFlagLen + 2);
    strcpy(ourCustomFlags, oldValue);
    strcat(ourCustomFlags, " ");
    strcat(ourCustomFlags, customFlag);
    PR_Free(oldValue);
    m_customFlagsHash.Remove(uid);
  }
  else
  {
    ourCustomFlags = NS_strdup(customFlag);
    if (!ourCustomFlags)
      return NS_ERROR_OUT_OF_MEMORY;
  }
  return (m_customFlagsHash.Put(uid, ourCustomFlags) == 0) ? NS_OK : NS_ERROR_OUT_OF_MEMORY;
}

NS_IMETHODIMP nsImapFlagAndUidState::GetCustomFlags(PRUint32 uid, char **customFlags)
{
  nsAutoCMonitor mon(this);
  if (m_customFlagsHash.IsInitialized())
  {
    char *value = nsnull;
    m_customFlagsHash.Get(uid, &value);
    if (value)
    {
      *customFlags = NS_strdup(value);
      return (*customFlags) ? NS_OK : NS_ERROR_FAILURE;
    }
  }
  *customFlags = nsnull;
  return NS_OK;
}

NS_IMETHODIMP nsImapFlagAndUidState::ClearCustomFlags(PRUint32 uid)
{
  nsAutoCMonitor mon(this);
  m_customFlagsHash.Remove(uid);
  return NS_OK;
}

