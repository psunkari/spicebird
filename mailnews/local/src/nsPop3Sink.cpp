/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Pierre Phaneuf <pp@ludusdesign.com>
 *   bienvenu@nventure.com
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

#include "msgCore.h"    // precompiled header...
#include "nsPop3Sink.h"
#include "prprf.h"
#include "prlog.h"
#include "nscore.h"
#include <stdio.h>
#include <time.h>
#include "nsParseMailbox.h"
#include "nsIMsgLocalMailFolder.h"
#include "nsIMsgIncomingServer.h"
#include "nsLocalUtils.h"
#include "nsMsgLocalFolderHdrs.h"
#include "nsIMsgFolder.h" // TO include biffState enum. Change to bool later...
#include "nsMailHeaders.h"
#include "nsIMsgAccountManager.h"
#include "nsILineInputStream.h"
#include "nsIPop3Protocol.h"
#include "nsLocalMailFolder.h"
#include "nsIPrefBranch.h"
#include "nsIPrefService.h"
#include "nsDirectoryServiceDefs.h"
#include "nsIPrompt.h"
#include "nsIPromptService.h"
#include "nsIInterfaceRequestor.h"
#include "nsIInterfaceRequestorUtils.h"
#include "nsIDocShell.h"
#include "nsIDOMWindowInternal.h"
#include "nsEmbedCID.h"
#include "nsMsgUtils.h"
#include "nsMsgBaseCID.h"
#include "nsLocalStrings.h"
#include "nsServiceManagerUtils.h"

NS_IMPL_THREADSAFE_ISUPPORTS1(nsPop3Sink, nsIPop3Sink)

nsPop3Sink::nsPop3Sink()
{
    m_authed = PR_FALSE;
    m_downloadingToTempFile = PR_FALSE;
    m_accountUrl = nsnull;
    m_biffState = 0;
    m_numNewMessages = 0;
    m_numNewMessagesInFolder = 0;
    m_senderAuthed = PR_FALSE;
    m_outputBuffer = nsnull;
    m_outputBufferSize = 0;
    m_newMailParser = nsnull;
#ifdef DEBUG
    m_fileCounter = 0;
#endif
    m_popServer = nsnull;
    m_outFileStream = nsnull;
    m_folder = nsnull;
    m_buildMessageUri = PR_FALSE;
}

nsPop3Sink::~nsPop3Sink()
{
    PR_Free(m_accountUrl);
    PR_Free(m_outputBuffer);
    NS_IF_RELEASE(m_popServer);
    ReleaseFolderLock();
    NS_IF_RELEASE(m_folder);
    NS_IF_RELEASE(m_newMailParser);
}

nsresult
nsPop3Sink::SetUserAuthenticated(PRBool authed)
{
  m_authed = authed;
  m_popServer->SetAuthenticated(authed);
  return NS_OK;
}

nsresult
nsPop3Sink::GetUserAuthenticated(PRBool* authed)
{
  return m_popServer->GetAuthenticated(authed);
}

nsresult
nsPop3Sink::SetSenderAuthedFlag(void* closure, PRBool authed)
{
  m_authed = authed;
  return NS_OK;
}

nsresult
nsPop3Sink::SetMailAccountURL(const char* urlString)
{
  if (urlString)
  {
    PR_Free(m_accountUrl);
    m_accountUrl = PL_strdup(urlString);
  }

  return NS_OK;
}

nsresult
nsPop3Sink::GetMailAccountURL(char* *urlString)
{
  NS_ASSERTION(urlString, "null getter in getMailAccountURL");
  if (!urlString) return NS_ERROR_NULL_POINTER;

  *urlString = strdup(m_accountUrl);
  return NS_OK;
}

struct partialRecord
{
  partialRecord();
  ~partialRecord();

  nsCOMPtr<nsIMsgDBHdr> m_msgDBHdr;
  nsCString m_uidl;
};

partialRecord::partialRecord() :
  m_msgDBHdr(nsnull)
{
}

partialRecord::~partialRecord()
{
}

// Walk through all the messages in this folder and look for any
// PARTIAL messages. For each of those, dig thru the mailbox and
// find the Account that the message belongs to. If that Account
// matches the current Account, then look for the Uidl and save
// this message for later processing.
nsresult
nsPop3Sink::FindPartialMessages(nsILocalFile *folderFile)
{
  nsresult rv;

  nsCOMPtr<nsISimpleEnumerator> messages;
  PRBool hasMore = PR_FALSE;
  PRBool isOpen = PR_FALSE;
  nsLocalFolderScanState folderScanState;
  nsCOMPtr<nsIMsgLocalMailFolder> localFolder = do_QueryInterface(m_folder);

  if (!localFolder)
    return NS_ERROR_FAILURE;  // we need it to grub thru the folder

  rv = m_newMailParser->m_mailDB->EnumerateMessages(getter_AddRefs(messages));
  if (messages)
    messages->HasMoreElements(&hasMore);
  while(hasMore && NS_SUCCEEDED(rv))
  {
    nsCOMPtr<nsISupports> aSupport;
    PRUint32 flags = 0;
    rv = messages->GetNext(getter_AddRefs(aSupport));
    nsCOMPtr<nsIMsgDBHdr> msgDBHdr(do_QueryInterface(aSupport, &rv));
    msgDBHdr->GetFlags(&flags);
    if (flags & nsMsgMessageFlags::Partial)
    {
      // Open the various streams we need to seek and read from the mailbox
      if (!isOpen)
      {
        folderScanState.m_localFile = folderFile;
        rv = localFolder->GetFolderScanState(&folderScanState);
        if (NS_SUCCEEDED(rv))
          isOpen = PR_TRUE;
        else
          break;
      }
      rv = localFolder->GetUidlFromFolder(&folderScanState, msgDBHdr);
      if (!NS_SUCCEEDED(rv))
        break;

      // If we got the uidl, see if this partial message belongs to this
      // account. Add it to the array if so...
#ifdef MOZILLA_INTERNAL_API
      if (folderScanState.m_uidl && 
          m_accountKey.Equals(folderScanState.m_accountKey, nsCaseInsensitiveCStringComparator()))
#else
      if (folderScanState.m_uidl &&
          m_accountKey.Equals(folderScanState.m_accountKey, CaseInsensitiveCompare))
#endif
      {
        partialRecord *partialMsg = new partialRecord();
        if (partialMsg)
        {
          partialMsg->m_uidl = folderScanState.m_uidl;
          partialMsg->m_msgDBHdr = msgDBHdr;
          m_partialMsgsArray.AppendElement(partialMsg);
        }
      }
    }
    messages->HasMoreElements(&hasMore);
  }
  if (isOpen)
    folderScanState.m_fileStream->Close();
  return rv;
}

// For all the partial messages saved by FindPartialMessages,
// ask the protocol handler if they still exist on the server.
// Any messages that don't exist any more are deleted from the
// msgDB.
void
nsPop3Sink::CheckPartialMessages(nsIPop3Protocol *protocol)
{
  PRUint32 count = m_partialMsgsArray.Count();
  PRBool deleted = PR_FALSE;

  for (PRUint32 i = 0; i < count; i++)
  {
    partialRecord *partialMsg;
    PRBool found = PR_TRUE;
    partialMsg = static_cast<partialRecord *>(m_partialMsgsArray.ElementAt(i));
    protocol->CheckMessage(partialMsg->m_uidl.get(), &found);
    if (!found)
    {
      m_newMailParser->m_mailDB->DeleteHeader(partialMsg->m_msgDBHdr, nsnull, PR_FALSE, PR_TRUE);
      deleted = PR_TRUE;
    }
    delete partialMsg;
  }
  m_partialMsgsArray.Clear();
  if (deleted)
  {
    nsCOMPtr<nsIMsgLocalMailFolder> localFolder = do_QueryInterface(m_folder);
    if (localFolder)
      localFolder->NotifyDelete();
  }
}

nsresult
nsPop3Sink::BeginMailDelivery(PRBool uidlDownload, nsIMsgWindow *aMsgWindow, PRBool* aBool)
{
#ifdef DEBUG
    m_fileCounter++;
#endif

    nsresult rv;

    nsCOMPtr<nsIMsgIncomingServer> server = do_QueryInterface(m_popServer);
    if (!server)
      return NS_ERROR_UNEXPECTED;

    nsCOMPtr <nsIMsgAccountManager> acctMgr = do_GetService(NS_MSGACCOUNTMANAGER_CONTRACTID, &rv);
    nsCOMPtr <nsIMsgAccount> account;
    NS_ENSURE_SUCCESS(rv, rv);
    acctMgr->FindAccountForServer(server, getter_AddRefs(account));
    if (account)
      account->GetKey(m_accountKey);

    PRBool isLocked;
    nsCOMPtr <nsISupports> supports = do_QueryInterface(static_cast<nsIPop3Sink*>(this));
    m_folder->GetLocked(&isLocked);
    if(!isLocked)
      m_folder->AcquireSemaphore(supports);
    else
      return NS_MSG_FOLDER_BUSY;

    nsCOMPtr<nsILocalFile> path;

    m_folder->GetFilePath(getter_AddRefs(path));

    nsCOMPtr<nsIPrefBranch> pPrefBranch(do_GetService(NS_PREFSERVICE_CONTRACTID, &rv));
    if (pPrefBranch)
       pPrefBranch->GetBoolPref("mailnews.downloadToTempFile", &m_downloadingToTempFile);

    if (m_downloadingToTempFile)
    {
      // need to create an nsIOFileStream from a temp file...
      nsCOMPtr<nsIFile> tmpDownloadFile;
      rv = GetSpecialDirectoryWithFileName(NS_OS_TEMP_DIR,
                                           "newmsg",
                                           getter_AddRefs(tmpDownloadFile));

      NS_ASSERTION(NS_SUCCEEDED(rv),"writing tmp pop3 download file: failed to append filename");
      if (NS_FAILED(rv))
        return rv;

      rv = tmpDownloadFile->CreateUnique(nsIFile::NORMAL_FILE_TYPE, 00600);  //need a unique tmp file to prevent dataloss in multiuser environment
      NS_ENSURE_SUCCESS(rv, rv);

      m_tmpDownloadFile = do_QueryInterface(tmpDownloadFile, &rv);
      if (NS_SUCCEEDED(rv))
      {
        rv = MsgGetFileStream(m_tmpDownloadFile, getter_AddRefs(m_outFileStream));
        NS_ENSURE_SUCCESS(rv, rv);
      }
    }
    else
    {
      rv = MsgGetFileStream(path, getter_AddRefs(m_outFileStream));
      NS_ENSURE_SUCCESS(rv, rv);
    }
    // The following (!m_outFileStream etc) was added to make sure that we don't write somewhere
    // where for some reason or another we can't write to and lose the messages
    // See bug 62480
    if (!m_outFileStream)
        return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr <nsISeekableStream> seekableOutStream = do_QueryInterface(m_outFileStream);
    seekableOutStream->Seek(nsISeekableStream::NS_SEEK_END, 0);

    // create a new mail parser
    m_newMailParser = new nsParseNewMailState;
    NS_IF_ADDREF(m_newMailParser);
    if (m_newMailParser == nsnull)
      return NS_ERROR_OUT_OF_MEMORY;

    m_folder->GetNumNewMessages(PR_FALSE, &m_numNewMessagesInFolder);
    nsCOMPtr <nsIMsgFolder> serverFolder;
    rv = GetServerFolder(getter_AddRefs(serverFolder));
    if (NS_FAILED(rv)) return rv;

    nsCOMPtr <nsIInputStream> inboxInputStream = do_QueryInterface(m_outFileStream);
    rv = m_newMailParser->Init(serverFolder, m_folder, (m_downloadingToTempFile) ? m_tmpDownloadFile : path,
                              inboxInputStream, aMsgWindow, m_downloadingToTempFile);
  // if we failed to initialize the parser, then just don't use it!!!
  // we can still continue without one...

    if (NS_FAILED(rv))
    {
      NS_IF_RELEASE(m_newMailParser);
      rv = NS_OK;
    }
    else
    {
      // Share the inbox fileStream so that moz-status-line flags can be set in the Inbox
      m_newMailParser->SetDBFolderStream(m_outFileStream);
      if (m_downloadingToTempFile)
      {
        // Tell the parser to use the offset that will be in the dest folder,
        // not the temp folder, so that the msg hdr will start off with
        // the correct mdb oid
        PRInt64 fileSize;
        path->GetFileSize(&fileSize);
        m_newMailParser->SetEnvelopePos((PRUint32) fileSize);
      }
    }
    if (m_newMailParser)
    {
      if (uidlDownload)
        m_newMailParser->DisableFilters();
      else
        FindPartialMessages(path);
    }


#ifdef DEBUG
    printf("Begin mail message delivery.\n");
#endif
    if (aBool)
        *aBool = PR_TRUE;
    return NS_OK;
}

nsresult
nsPop3Sink::EndMailDelivery(nsIPop3Protocol *protocol)
{
  CheckPartialMessages(protocol);

  if (m_newMailParser)
  {
    if (m_outFileStream)
      m_outFileStream->Flush();  // try this.
    m_newMailParser->OnStopRequest(nsnull, nsnull, NS_OK);
    m_newMailParser->SetDBFolderStream(nsnull); // stream is going away
    m_newMailParser->EndMsgDownload();
  }
  if (m_outFileStream)
  {
    m_outFileStream->Close();
    m_outFileStream = 0;
  }

  if (m_downloadingToTempFile)
    m_tmpDownloadFile->Remove(PR_FALSE);

  // tell the parser to mark the db valid *after* closing the mailbox.
  if (m_newMailParser)
    m_newMailParser->UpdateDBFolderInfo();

  nsresult rv = ReleaseFolderLock();
  NS_ASSERTION(NS_SUCCEEDED(rv),"folder lock not released successfully");

  PRBool filtersRun;
  m_folder->CallFilterPlugins(nsnull, &filtersRun); // ??? do we need msgWindow?
  PRInt32 numNewMessagesInFolder;
  // if filters have marked msgs read or deleted, the num new messages count
  // will go negative by the number of messages marked read or deleted,
  // so if we add that number to the number of msgs downloaded, that will give
  // us the number of actual new messages.
  m_folder->GetNumNewMessages(PR_FALSE, &numNewMessagesInFolder);
  m_numNewMessages -= (m_numNewMessagesInFolder  - numNewMessagesInFolder);
  m_folder->SetNumNewMessages(m_numNewMessages); // we'll adjust this for spam later
  if (!filtersRun && m_numNewMessages > 0)
  {
    nsCOMPtr <nsIMsgIncomingServer> server;
    m_folder->GetServer(getter_AddRefs(server));
    if (server)
    {
      server->SetPerformingBiff(PR_TRUE);
      m_folder->SetBiffState(m_biffState);
      server->SetPerformingBiff(PR_FALSE);
    }
  }
  // note that size on disk has possibly changed.
  nsCOMPtr<nsIMsgLocalMailFolder> localFolder = do_QueryInterface(m_folder);
  if (localFolder)
    (void) localFolder->RefreshSizeOnDisk();
  nsCOMPtr<nsIMsgIncomingServer> server = do_QueryInterface(m_popServer);
  if (server)
  {
    nsCOMPtr <nsIMsgFilterList> filterList;
    rv = server->GetFilterList(nsnull, getter_AddRefs(filterList));
    NS_ENSURE_SUCCESS(rv,rv);

    if (filterList)
      (void) filterList->FlushLogIfNecessary();
  }

  // fix for bug #161999
  // we should update the summary totals for the folder (inbox)
  // in case it's not the open folder
  m_folder->UpdateSummaryTotals(PR_TRUE);

  // check if the folder open in this window is not the current folder, and if it has new
  // message, in which case we need to try to run the filter plugin.
  if (m_newMailParser)
  {
    nsCOMPtr <nsIMsgWindow> msgWindow;
    m_newMailParser->GetMsgWindow(getter_AddRefs(msgWindow));
    // this breaks down if it's biff downloading new mail because
    // there's no msgWindow...
    if (msgWindow)
    {
      nsCOMPtr <nsIMsgFolder> openFolder;
      (void) msgWindow->GetOpenFolder(getter_AddRefs(openFolder));
      if (openFolder && openFolder != m_folder)
      {
        // only call filter plugins if folder is a local folder, because only
        // local folders get messages filtered into them synchronously by pop3.
        nsCOMPtr<nsIMsgLocalMailFolder> localFolder = do_QueryInterface(openFolder);
        if (localFolder)
        {
          PRBool hasNew, isLocked;
          (void) openFolder->GetHasNewMessages(&hasNew);
          if (hasNew)
          {
            // if the open folder is locked, we shouldn't run the spam filters
            // on it because someone is using the folder. see 218433.
            // Ideally, the filter plugin code would try to grab the folder lock
            // and hold onto it until done, but that's more difficult and I think
            // this will actually fix the problem.
            openFolder->GetLocked(&isLocked);
            if(!isLocked)
              openFolder->CallFilterPlugins(nsnull, &filtersRun);
          }
        }
      }
    }
  }
#ifdef DEBUG
  printf("End mail message delivery.\n");
#endif
  return NS_OK;
}

nsresult
nsPop3Sink::ReleaseFolderLock()
{
  nsresult result = NS_OK;
  if (!m_folder)
    return result;
  PRBool haveSemaphore;
  nsCOMPtr <nsISupports> supports = do_QueryInterface(static_cast<nsIPop3Sink*>(this));
  result = m_folder->TestSemaphore(supports, &haveSemaphore);
  if(NS_SUCCEEDED(result) && haveSemaphore)
    result = m_folder->ReleaseSemaphore(supports);
  return result;
}

nsresult
nsPop3Sink::AbortMailDelivery(nsIPop3Protocol *protocol)
{
  CheckPartialMessages(protocol);

  if (m_newMailParser)
    m_newMailParser->SetDBFolderStream(nsnull); //stream is going away

  if (m_outFileStream)
  {
    m_outFileStream->Close();
    m_outFileStream = 0;
  }

  if (m_downloadingToTempFile && m_tmpDownloadFile)
    m_tmpDownloadFile->Remove(PR_FALSE);

  /* tell the parser to mark the db valid *after* closing the mailbox.
  we have truncated the inbox, so berkeley mailbox and msf file are in sync*/
  if (m_newMailParser)
    m_newMailParser->UpdateDBFolderInfo();
#ifdef DEBUG
  nsresult rv =
#endif
    ReleaseFolderLock();
  NS_ASSERTION(NS_SUCCEEDED(rv),"folder lock not released successfully");

#ifdef DEBUG
    printf("Abort mail message delivery.\n");
#endif
  return NS_OK;
}

NS_IMETHODIMP
nsPop3Sink::IncorporateBegin(const char* uidlString,
                             nsIURI* aURL,
                             PRUint32 flags,
                             void** closure)
{
#ifdef DEBUG
    printf("Incorporate message begin:\n");
    if (uidlString)
        printf("uidl string: %s\n", uidlString);
#endif
    if (closure)
        *closure = (void*) this;
    nsCOMPtr <nsISeekableStream> seekableStream = do_QueryInterface(m_outFileStream);
    PRInt64 filePos;
    seekableStream->Tell(&filePos);
    m_msgOffset = (PRUint32) filePos;

    char *dummyEnvelope = GetDummyEnvelope();

    nsresult rv = WriteLineToMailbox(dummyEnvelope);
    if (NS_FAILED(rv)) return rv;
    // write out account-key before UIDL so the code that looks for
    // UIDL will find the account first and know it can stop looking
    // once it finds the UIDL line.
    if (!m_accountKey.IsEmpty())
    {
      nsCAutoString outputString;
      outputString.AssignLiteral(HEADER_X_MOZILLA_ACCOUNT_KEY ": ");
      outputString.Append(m_accountKey);
      outputString.AppendLiteral(MSG_LINEBREAK);
      WriteLineToMailbox(outputString.get());
    }
    if (uidlString)
    {
      nsCAutoString uidlCString("X-UIDL: ");
      uidlCString += uidlString;
      uidlCString += MSG_LINEBREAK;
      rv = WriteLineToMailbox(const_cast<char*>(uidlCString.get()));
      NS_ENSURE_SUCCESS(rv, rv);
    }
    // WriteLineToMailbox("X-Mozilla-Status: 8000" MSG_LINEBREAK);
    char *statusLine = PR_smprintf(X_MOZILLA_STATUS_FORMAT MSG_LINEBREAK, flags);
    rv = WriteLineToMailbox(statusLine);
    if (NS_FAILED(rv)) return rv;
    rv = WriteLineToMailbox("X-Mozilla-Status2: 00000000" MSG_LINEBREAK);
    if (NS_FAILED(rv)) return rv;
    // leave space for 60 bytes worth of keys/tags
    rv = WriteLineToMailbox(X_MOZILLA_KEYWORDS);
    PR_smprintf_free(statusLine);
    return NS_OK;
}

nsresult
nsPop3Sink::SetPopServer(nsIPop3IncomingServer *server)
{
  NS_IF_RELEASE(m_popServer);
  m_popServer=server;
  NS_ADDREF(m_popServer);

  return NS_OK;
}

nsresult
nsPop3Sink::GetPopServer(nsIPop3IncomingServer* *server)
{
    if (!server) return NS_ERROR_NULL_POINTER;
    *server = m_popServer;
    if (*server) NS_ADDREF(*server);
    return NS_OK;
}

nsresult nsPop3Sink::GetFolder(nsIMsgFolder * *folder)
{
  NS_ENSURE_ARG_POINTER(folder);
  NS_IF_ADDREF(*folder = m_folder);
  return NS_OK;
}

nsresult nsPop3Sink::SetFolder(nsIMsgFolder * folder)
{
  NS_IF_RELEASE(m_folder);
  m_folder=folder;
  NS_IF_ADDREF(m_folder);

  return NS_OK;
}

nsresult
nsPop3Sink::GetServerFolder(nsIMsgFolder **aFolder)
{
  if (!aFolder)
    return NS_ERROR_NULL_POINTER;
  if (m_popServer)
  {
    // not sure what this is used for - might be wrong if we have a deferred account.
    nsCOMPtr <nsIMsgIncomingServer> incomingServer = do_QueryInterface(m_popServer);
    if (incomingServer)
      return incomingServer->GetRootFolder(aFolder);
  }
  *aFolder = nsnull;
  return NS_ERROR_NULL_POINTER;
}

char*
nsPop3Sink::GetDummyEnvelope(void)
{
  static char result[75];
  char *ct;
  time_t now = time ((time_t *) 0);
#if defined (XP_WIN)
  if (now < 0 || now > 0x7FFFFFFF)
    now = 0x7FFFFFFF;
#endif
  ct = ctime(&now);
  PR_ASSERT(ct[24] == '\r' || ct[24] == '\n');
  ct[24] = 0;
  /* This value must be in ctime() format, with English abbreviations.
   strftime("... %c ...") is no good, because it is localized. */
  PL_strcpy(result, "From - ");
  PL_strcpy(result + 7, ct);
  PL_strcpy(result + 7 + 24, MSG_LINEBREAK);
  return result;
}

nsresult
nsPop3Sink::IncorporateWrite(const char* block,
                             PRInt32 length)
{
  PRInt32 blockOffset = 0;
  if (!strncmp(block, "From ", 5))
  {
    length++;
    blockOffset = 1;
  }
  if (!m_outputBuffer || length > m_outputBufferSize)
  {
    if (!m_outputBuffer)
      m_outputBuffer = (char*) PR_MALLOC(length+1);
    else
      m_outputBuffer = (char*) PR_REALLOC(m_outputBuffer, length+1);

    m_outputBufferSize = length;
  }
  if (m_outputBuffer)
  {
    if (blockOffset == 1)
      *m_outputBuffer = '>';
    memcpy(m_outputBuffer + blockOffset, block, length - blockOffset);
    *(m_outputBuffer + length) = 0;
    nsresult rv = WriteLineToMailbox (m_outputBuffer);
    if (NS_FAILED(rv)) return rv;
  }
  return NS_OK;
}

nsresult nsPop3Sink::WriteLineToMailbox(const char *buffer)
{

  if (buffer)
  {
    PRInt32 bufferLen = PL_strlen(buffer);
    if (m_newMailParser) // HandleLine should really take a const char *...
      m_newMailParser->HandleLine((char *) buffer, bufferLen);
    // The following (!m_outFileStream etc) was added to make sure that we don't write somewhere
    // where for some reason or another we can't write to and lose the messages
    // See bug 62480
    if (!m_outFileStream)
      return NS_ERROR_OUT_OF_MEMORY;

    // seek to the end in case someone else has seeked elsewhere in our stream.
    nsCOMPtr <nsISeekableStream> seekableOutStream = do_QueryInterface(m_outFileStream);
    seekableOutStream->Seek(nsISeekableStream::NS_SEEK_END, 0);
    PRUint32 bytesWritten;
    m_outFileStream->Write(buffer, bufferLen, &bytesWritten);
    if ((PRInt32) bytesWritten != bufferLen) return NS_ERROR_FAILURE;
  }
  return NS_OK;
}

nsresult nsPop3Sink::HandleTempDownloadFailed(nsIMsgWindow *msgWindow)
{
  nsresult rv;
  nsCOMPtr<nsIStringBundleService> bundleService(do_GetService("@mozilla.org/intl/stringbundle;1", &rv));
  NS_ENSURE_SUCCESS(rv, rv);
  nsCOMPtr<nsIStringBundle> bundle;
  rv = bundleService->CreateBundle("chrome://messenger/locale/localMsgs.properties", getter_AddRefs(bundle));
  NS_ENSURE_SUCCESS(rv, rv);
  nsString fromStr, subjectStr, confirmString;

  m_newMailParser->m_newMsgHdr->GetMime2DecodedSubject(subjectStr);
  m_newMailParser->m_newMsgHdr->GetMime2DecodedAuthor(fromStr);
  const PRUnichar *params[] = { fromStr.get(), subjectStr.get() };
  bundle->FormatStringFromID(POP3_TMP_DOWNLOAD_FAILED, params, 2, getter_Copies(confirmString));
  nsCOMPtr<nsIDOMWindowInternal> parentWindow;
  nsCOMPtr<nsIPromptService> promptService = do_GetService(NS_PROMPTSERVICE_CONTRACTID);
  nsCOMPtr<nsIDocShell> docShell;
  if (msgWindow)
  {
    (void) msgWindow->GetRootDocShell(getter_AddRefs(docShell));
    parentWindow = do_QueryInterface(docShell);
  }
  if (promptService && !confirmString.IsEmpty())
  {
    PRInt32 dlgResult  = -1;
    rv = promptService->ConfirmEx(parentWindow, nsnull, confirmString.get(),
                      nsIPromptService::STD_YES_NO_BUTTONS,
                      nsnull,
                      nsnull,
                      nsnull,
                      nsnull,
                      nsnull,
                      &dlgResult);
    m_newMailParser->m_newMsgHdr = nsnull;

    return (dlgResult == 0) ? NS_OK : NS_MSG_ERROR_COPYING_FROM_TMP_DOWNLOAD;
  }
  return rv;
}


NS_IMETHODIMP
nsPop3Sink::IncorporateComplete(nsIMsgWindow *aMsgWindow, PRInt32 aSize)
{
  if (m_buildMessageUri && !m_baseMessageUri.IsEmpty())
  {
    PRUint32 msgKey;
    m_newMailParser->GetEnvelopePos(&msgKey);
    m_messageUri.SetLength(0);
    nsBuildLocalMessageURI(m_baseMessageUri.get(), msgKey, m_messageUri);
  }

  nsresult rv = WriteLineToMailbox(MSG_LINEBREAK);
  if (NS_FAILED(rv)) return rv;
  PRBool leaveOnServer = PR_FALSE;
  m_popServer->GetLeaveMessagesOnServer(&leaveOnServer);
  // aSize is only set for partial messages. Skip the flush for partials.
  // Only flush if this is a full message and we didn't leave a copy on the server.
  if (!aSize && !leaveOnServer)
    rv = m_outFileStream->Flush();   //to make sure the message is written to the disk
  if (NS_FAILED(rv)) return rv;
  NS_ASSERTION(m_newMailParser, "could not get m_newMailParser");
  if (m_newMailParser)
  {
    // PublishMsgHdr clears m_newMsgHdr, so we need a comptr to
    // hold onto it.
    nsCOMPtr<nsIMsgDBHdr> hdr = m_newMailParser->m_newMsgHdr;
    NS_ASSERTION(hdr, "m_newMailParser->m_newMsgHdr wasn't set");
    if (!hdr)
      return NS_ERROR_FAILURE;

    nsCOMPtr<nsIMsgLocalMailFolder> localFolder = do_QueryInterface(m_folder);
    PRBool doSelect = PR_FALSE;

    // aSize is only set for partial messages. For full messages,
    // check to see if we're replacing an old partial message.
    if (!aSize && localFolder)
      (void) localFolder->DeleteDownloadMsg(hdr, &doSelect);

    // If a header already exists for this message (for example, when
    // getting a complete message when a partial exists), then update the new
    // header from the old.
    if (!m_origMessageUri.IsEmpty() && localFolder)
    {
      nsCOMPtr <nsIMsgDBHdr> oldMsgHdr;
      rv = GetMsgDBHdrFromURI(m_origMessageUri.get(), getter_AddRefs(oldMsgHdr));
      if (NS_SUCCEEDED(rv) && oldMsgHdr)
        localFolder->UpdateNewMsgHdr(oldMsgHdr, hdr);
    }

    if (m_downloadingToTempFile)
    {
      PRBool moved = PR_FALSE;
      // close file to give virus checkers a chance to do their thing...
      m_outFileStream->Flush();
      m_outFileStream->Close();
      m_newMailParser->FinishHeader();
      // need to re-open the inbox file stream.
      PRBool exists;
      m_tmpDownloadFile->Exists(&exists);
      if (!exists)
        return HandleTempDownloadFailed(aMsgWindow);

      nsCOMPtr <nsIInputStream> inboxInputStream = do_QueryInterface(m_outFileStream);
      rv = MsgReopenFileStream(m_tmpDownloadFile, inboxInputStream);
      NS_ENSURE_SUCCESS(rv, HandleTempDownloadFailed(aMsgWindow));
      nsMsgKey saveMsgKey;
      hdr->GetMessageKey(&saveMsgKey);
      // this is the offset in the temp file, which we need to be correct
      // when applying filters;
      hdr->SetMessageKey(0);
      m_newMailParser->ApplyFilters(&moved, aMsgWindow, 0);
      // restore the msg key so that we don't confuse the msg hdr
      // use cache, which requires the hdr to have the same msg key when put
      // in the use cache as when it is deleted and hence removed
      // from the use cache.
      hdr->SetMessageKey(saveMsgKey);
      if (!moved)
      {
        if (m_outFileStream)
        {
          nsCOMPtr<nsILocalFile> path;

          PRInt64 folderSize, tmpDownloadFileSize;
          m_folder->GetFilePath(getter_AddRefs(path));
          path->GetFileSize(&folderSize);
          PRUint32 newMsgPos = (PRUint32) folderSize;
          PRUint32 msgSize;
          hdr->GetMessageSize(&msgSize);
          hdr->SetMessageKey(newMsgPos);
          // we need to clone because nsLocalFileUnix caches its stat result,
          // so it doesn't realize the file has changed size.
          nsCOMPtr <nsIFile> tmpClone;
          rv = m_tmpDownloadFile->Clone(getter_AddRefs(tmpClone));
          NS_ENSURE_SUCCESS(rv, rv);
          tmpClone->GetFileSize(&tmpDownloadFileSize);

          if (msgSize > tmpDownloadFileSize)
            rv = NS_MSG_ERROR_WRITING_MAIL_FOLDER;
          else
            rv = m_newMailParser->AppendMsgFromFile(inboxInputStream, 0, msgSize, path);
          if (NS_FAILED(rv))
            return HandleTempDownloadFailed(aMsgWindow);

          // if we have made it this far then the message has successfully been written to the new folder
          // now add the header to the destMailDB.
          if (NS_SUCCEEDED(rv) && m_newMailParser->m_mailDB)
          {
            PRUint32 newFlags;
            hdr->GetFlags(&newFlags);
            if (! (newFlags & nsMsgMessageFlags::Read))
            {
              nsCString junkScoreStr;
              (void) hdr->GetStringProperty("junkscore", getter_Copies(junkScoreStr));
              if (atoi(junkScoreStr.get()) < 50)
              {
                hdr->OrFlags(nsMsgMessageFlags::New, &newFlags);
                m_newMailParser->m_mailDB->AddToNewList(newMsgPos);
              }
            }
            m_newMailParser->m_mailDB->AddNewHdrToDB(hdr, PR_TRUE);
            nsCOMPtr<nsIMsgFolderNotificationService> notifier(do_GetService(NS_MSGNOTIFICATIONSERVICE_CONTRACTID));
            if (notifier)
              notifier->NotifyMsgAdded(hdr);
            m_folder->OrProcessingFlags(
              newMsgPos, nsMsgProcessingFlags::NotReportedClassified);
          }
        }
        else
        {
            return HandleTempDownloadFailed(aMsgWindow);
          // need to give an error here.
        }
      }
      else
      {
        nsCOMPtr<nsILocalFile> path;
        // cleanup after mailHdr in source DB because we moved the message.
        m_newMailParser->m_mailDB->RemoveHeaderMdbRow(hdr);

        // if the filter moved the message, it called nsParseMailMessageState::Init
        // to truncate the source folder, which resets m_envelopePos and m_position.
        // So set the envelopePos explicitly here.
        m_folder->GetFilePath(getter_AddRefs(path));
        PRInt64 fileSize;
        path->GetFileSize(&fileSize);
        m_newMailParser->SetEnvelopePos((PRUint32) fileSize);
      }
      m_newMailParser->m_newMsgHdr = nsnull;
      m_outFileStream->Close(); // close so we can truncate.
      m_tmpDownloadFile->SetFileSize(0);
      rv = MsgReopenFileStream(m_tmpDownloadFile, inboxInputStream);
      NS_ENSURE_SUCCESS(rv, rv);
    } else
      m_newMailParser->PublishMsgHeader(aMsgWindow);
    // run any reply/forward filter after we've finished with the
    // temp quarantine file, and/or moved the message to another folder.
    m_newMailParser->ApplyForwardAndReplyFilter(aMsgWindow);
    if (aSize)
      hdr->SetUint32Property("onlineSize", aSize);

    // if DeleteDownloadMsg requested it, select the new message
    else if (doSelect)
      (void) localFolder->SelectDownloadMsg();
  }

#ifdef DEBUG
  printf("Incorporate message complete.\n");
#endif
  return NS_OK;
}

NS_IMETHODIMP
nsPop3Sink::IncorporateAbort(PRBool uidlDownload)
{
  nsresult rv;
  rv = m_outFileStream->Close();   //need to close so that the file can be truncated.
  NS_ENSURE_SUCCESS(rv,rv);
  if (m_msgOffset >= 0 && !m_downloadingToTempFile)
  {
     nsCOMPtr<nsIMsgIncomingServer> server = do_QueryInterface(m_popServer);
     NS_ASSERTION(server, "Could not get the pop server !!");
     nsCOMPtr<nsILocalFile> mailDirectory;
     if (uidlDownload)
        m_folder->GetFilePath(getter_AddRefs(mailDirectory));
     else
     {
       rv = server->GetLocalPath(getter_AddRefs(mailDirectory));
       NS_ENSURE_SUCCESS(rv,rv);
       rv = mailDirectory->AppendRelativePath(NS_LITERAL_STRING("Inbox"));
       NS_ENSURE_SUCCESS(rv,rv);
     }
     rv = mailDirectory->SetFileSize(m_msgOffset);
     NS_ENSURE_SUCCESS(rv,rv);
  }
#ifdef DEBUG
    printf("Incorporate message abort.\n");
#endif
    return rv;
}

nsresult
nsPop3Sink::BiffGetNewMail()
{
#ifdef DEBUG
    printf("Biff get new mail.\n");
#endif
    return NS_OK;
}

nsresult
nsPop3Sink::SetBiffStateAndUpdateFE(PRUint32 aBiffState, PRInt32 numNewMessages, PRBool notify)
{
  m_biffState = aBiffState;
  if (m_newMailParser)
    numNewMessages -= m_newMailParser->m_numNotNewMessages;

  if (notify && m_folder && numNewMessages > 0 && numNewMessages != m_numNewMessages
      && aBiffState == nsIMsgFolder::nsMsgBiffState_NewMail)
  {
    m_folder->SetNumNewMessages(numNewMessages);
    m_folder->SetBiffState(aBiffState);
  }
  m_numNewMessages = numNewMessages;

  return NS_OK;
}

NS_IMETHODIMP
nsPop3Sink::GetBuildMessageUri(PRBool *bVal)
{
  NS_ENSURE_ARG_POINTER(bVal);
  *bVal = m_buildMessageUri;
  return NS_OK;
}

NS_IMETHODIMP
nsPop3Sink::SetBuildMessageUri(PRBool bVal)
{
  m_buildMessageUri = bVal;
  return NS_OK;
}

NS_IMETHODIMP
nsPop3Sink::GetMessageUri(char **messageUri)
{
  NS_ENSURE_ARG_POINTER(messageUri);
  NS_ENSURE_TRUE(!m_messageUri.IsEmpty(), NS_ERROR_FAILURE);
  *messageUri = ToNewCString(m_messageUri);
  return NS_OK;
}

NS_IMETHODIMP
nsPop3Sink::SetMessageUri(const char *messageUri)
{
  NS_ENSURE_ARG_POINTER(messageUri);
  m_messageUri = messageUri;
  return NS_OK;
}

NS_IMETHODIMP
nsPop3Sink::GetBaseMessageUri(char ** baseMessageUri)
{
  NS_ENSURE_ARG_POINTER(baseMessageUri);
  NS_ENSURE_TRUE(!m_baseMessageUri.IsEmpty(), NS_ERROR_FAILURE);
  *baseMessageUri = ToNewCString(m_baseMessageUri);
  return NS_OK;
}

NS_IMETHODIMP
nsPop3Sink::SetBaseMessageUri(const char *baseMessageUri)
{
  NS_ENSURE_ARG_POINTER(baseMessageUri);
  m_baseMessageUri = baseMessageUri;
  return NS_OK;
}

NS_IMETHODIMP
nsPop3Sink::GetOrigMessageUri(nsACString& aOrigMessageUri)
{
  aOrigMessageUri.Assign(m_origMessageUri);
  return NS_OK;
}

NS_IMETHODIMP
nsPop3Sink::SetOrigMessageUri(const nsACString& aOrigMessageUri)
{
  m_origMessageUri.Assign(aOrigMessageUri);
  return NS_OK;
}
