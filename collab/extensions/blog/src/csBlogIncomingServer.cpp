/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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
 * The Original Code is mozilla mailnews.
 *
 * The Initial Developer of the Original Code is
 * Seth Spitzer <sspitzer@mozilla.org>.
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   David Bienvenu <bienvenu@nventure.com>
 *   Sunil Mohan Adapa <sunil@synovel.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
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

#include "nsMsgBaseCID.h"
#include "nsIMsgMailSession.h"
#include "nsIMsgHdr.h"
#include "nsMsgFolderFlags.h"
#include "nsIMsgLocalMailFolder.h"
#include "nsMsgUtils.h"

#include "csIBlogManager.h"
#include "csBlogIncomingServer.h"

nsrefcnt csBlogIncomingServer::gInstanceCount    = 0;

NS_IMPL_ISUPPORTS_INHERITED2(csBlogIncomingServer,
			     nsMsgIncomingServer,
                             nsILocalMailIncomingServer,
                             nsIFolderListener)

csBlogIncomingServer::csBlogIncomingServer()
{
  nsresult rv;
 
  m_canHaveFilters = PR_TRUE;

  //if (gInstanceCount == 0)
  {
    nsCOMPtr<nsIMsgMailSession> mailSession = do_GetService(NS_MSGMAILSESSION_CONTRACTID, &rv);

    if (NS_SUCCEEDED(rv))
      mailSession->AddFolderListener(this, nsIFolderListener::added | 
                                     nsIFolderListener::removed | 
                                     nsIFolderListener::propertyFlagChanged);
  }

  mBlogManager = do_CreateInstance(CS_BLOGMANAGER_CONTRACTID, &rv);
  if (NS_FAILED(rv) || !mBlogManager)
  {
    fprintf(stderr, "Failed to create blog manager component\n");
  }
  else
  {
    nsCOMPtr<nsIMsgIncomingServer> server;
    rv = QueryInterface(NS_GET_IID(nsIMsgIncomingServer), getter_AddRefs(server));

    if (NS_SUCCEEDED(rv))
      mBlogManager->SetServer(server);
  }

  gInstanceCount++;
}

csBlogIncomingServer::~csBlogIncomingServer()
{
  gInstanceCount--;
}

NS_IMETHODIMP
csBlogIncomingServer::GetSupportsDiskSpace(PRBool *aSupportsDiskSpace)
{
  NS_ENSURE_ARG_POINTER(aSupportsDiskSpace);
  *aSupportsDiskSpace = PR_FALSE;
  return NS_OK;
}

NS_IMETHODIMP
csBlogIncomingServer::GetCanHaveFilters(PRBool *aCanHaveFilters)
{
  NS_ENSURE_ARG_POINTER(aCanHaveFilters);
  *aCanHaveFilters = PR_FALSE;
  return NS_OK;
}

NS_IMETHODIMP
csBlogIncomingServer::GetLocalStoreType(nsACString& type)
{
  type.AssignLiteral ("mailbox");
  return NS_OK;
}

NS_IMETHODIMP
csBlogIncomingServer::GetAccountManagerChrome(nsAString& aResult)
{
  aResult.AssignLiteral ("am-blog.xul");
  return NS_OK;
}

NS_IMETHODIMP
csBlogIncomingServer::GetCanSearchMessages(PRBool *canSearchMessages)
{
  NS_ENSURE_ARG_POINTER(canSearchMessages);

  *canSearchMessages = PR_TRUE;
  return NS_OK;
}

NS_IMETHODIMP
csBlogIncomingServer::GetCanFileMessages(PRBool *canFileMessages)
{
  NS_ENSURE_ARG_POINTER(canFileMessages);

  *canFileMessages = PR_TRUE;
  return NS_OK;
}

NS_IMETHODIMP
csBlogIncomingServer::CreateDefaultMailboxes(nsIFile *aPath)
{
  NS_ENSURE_ARG_POINTER(aPath);
  nsCOMPtr <nsIFile> path;
  nsresult rv = aPath->Clone(getter_AddRefs(path));
  NS_ENSURE_SUCCESS(rv, rv);

  rv = path->AppendNative(NS_LITERAL_CSTRING("Published"));
  NS_ENSURE_SUCCESS(rv, rv);
  rv = CreateLocalFolder(path, NS_LITERAL_CSTRING("Published"));
  NS_ENSURE_SUCCESS(rv, rv);
  rv = CreateLocalFolder(path, NS_LITERAL_CSTRING("Drafts"));
  NS_ENSURE_SUCCESS(rv, rv);

  return CreateLocalFolder(path, NS_LITERAL_CSTRING("Trash"));
}

NS_IMETHODIMP
csBlogIncomingServer::SetFlagsOnDefaultMailboxes()
{
  SetFlagsOnDefaultMailbox(NS_LITERAL_STRING("Published"), nsMsgFolderFlags::Inbox);
  SetFlagsOnDefaultMailbox(NS_LITERAL_STRING("Drafts"), nsMsgFolderFlags::Drafts);
  SetFlagsOnDefaultMailbox(NS_LITERAL_STRING("Trash"), nsMsgFolderFlags::Trash);
  return NS_OK;
}

nsresult
csBlogIncomingServer::SetFlagsOnDefaultMailbox(const nsAString& aFolderName, PRUint32 flags)
{
  nsCOMPtr<nsIMsgFolder> rootFolder;
  nsresult rv = GetRootFolder(getter_AddRefs(rootFolder));
  NS_ENSURE_SUCCESS(rv, rv);

  // FindSubFolder() expects the folder name to be escaped
  // see bug #192043
  nsCAutoString escapedFolderName;
  rv = NS_MsgEscapeEncodeURLPath(aFolderName, escapedFolderName);
  NS_ENSURE_SUCCESS(rv,rv);

  nsCOMPtr<nsIMsgFolder> msgFolder;
  rv = rootFolder->FindSubFolder(escapedFolderName, getter_AddRefs(msgFolder));
  if (NS_FAILED(rv) || !msgFolder)
    return NS_ERROR_FAILURE;

  // we only want to do this if the folder *really* exists,
  // so check if it has a parent. Otherwise, we'll create the
  // .msf file when we don't want to.
  nsCOMPtr <nsIMsgFolder> parent;
  msgFolder->GetParent(getter_AddRefs(parent));
  if (!parent)
    return NS_ERROR_FAILURE;

  rv = msgFolder->SetFlag(flags);
  NS_ENSURE_SUCCESS(rv, rv);
  return msgFolder->SetPrettyName(aFolderName);
}

NS_IMETHODIMP
csBlogIncomingServer::GetNewMail(nsIMsgWindow *aMsgWindow,
                                 nsIUrlListener *aUrlListener,
                                 nsIMsgFolder *aFolder,
                                 nsIURI **_retval)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
csBlogIncomingServer::GetNewMessages(nsIMsgFolder *aFolder,
                                     nsIMsgWindow *aMsgWindow,
                                     nsIUrlListener *aUrlListener)
{
  return mBlogManager->UpdateItems(aMsgWindow);
}

NS_IMETHODIMP
csBlogIncomingServer::ConfigureTemporaryFilters(nsIMsgFilterList *aFilterList)
{
  return NS_OK;
}

NS_IMETHODIMP
csBlogIncomingServer::OnItemAdded(nsIRDFResource *parentItem, nsISupports *item)
{
  nsCOMPtr<nsIMsgDBHdr> header = do_QueryInterface(item);
  if (!header)
    return NS_OK;

  nsCOMPtr<nsIMsgFolder> folder;
  nsresult rv = header->GetFolder(getter_AddRefs(folder)); 
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIMsgIncomingServer> server;
  rv = folder->GetServer(getter_AddRefs(server));
  NS_ENSURE_SUCCESS(rv, rv);

  nsCString type;
  rv = server->GetType(type);
  NS_ENSURE_SUCCESS(rv, rv);

  if (type.EqualsLiteral("blog"))
  {
    /* 
     * This item could have been added on a different account and we still
     * could get this event. So, first ensure that the event occured on our
     * folder.
     */
    nsCOMPtr<nsIMsgFolder> rootFolder;
    rv = GetRootFolder(getter_AddRefs(rootFolder));
    NS_ENSURE_SUCCESS(rv, rv);

    PRBool isOurItem = PR_FALSE;
    rv = rootFolder->IsAncestorOf(folder, &isOurItem);
    if (NS_FAILED(rv) || !isOurItem)
      return NS_OK;

    PRUint32 flags;
    folder->GetFlags(&flags);

    if (flags & nsMsgFolderFlags::Inbox || flags & nsMsgFolderFlags::Drafts)
    {
      fprintf (stderr, "Will set the tags on the message here\n");
      rv = mBlogManager->AddItem(header);
    } 
  }

  return rv;
}

NS_IMETHODIMP
csBlogIncomingServer::OnItemRemoved(nsIRDFResource *parentItem, nsISupports *item)
{
  nsCOMPtr<nsIMsgDBHdr> header = do_QueryInterface(item);
  if (!header)
    return NS_OK;

  nsCOMPtr<nsIMsgFolder> folder;
  nsresult rv = header->GetFolder(getter_AddRefs(folder)); 
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIMsgIncomingServer> server;
  rv = folder->GetServer(getter_AddRefs(server));
  NS_ENSURE_SUCCESS(rv, rv);

  nsCString type;
  rv = server->GetType(type);
  NS_ENSURE_SUCCESS(rv, rv);

  if (type.EqualsLiteral("blog"))
  {
    /* 
     * This item could have been removed on a different account and we still
     * could get this event. So, first ensure that the event occured on our
     * folder.
     */
    nsCOMPtr<nsIMsgFolder> rootFolder;
    rv = GetRootFolder(getter_AddRefs(rootFolder));
    NS_ENSURE_SUCCESS(rv, rv);

    PRBool isOurItem = PR_FALSE;
    rv = rootFolder->IsAncestorOf(folder, &isOurItem);
    if (NS_FAILED(rv) || !isOurItem)
      return NS_OK;

    PRUint32 flags;
    folder->GetFlags(&flags);

    if (flags & nsMsgFolderFlags::Inbox || flags & nsMsgFolderFlags::Drafts)
    {
      fprintf (stderr, "Will unpublish the blog here\n");
      rv = mBlogManager->RemoveItem(header);
    }
  }

  return rv;
}

NS_IMETHODIMP
csBlogIncomingServer::OnItemPropertyChanged(nsIRDFResource *item, nsIAtom *property, const char *oldValue, const char *newValue)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
csBlogIncomingServer::OnItemIntPropertyChanged(nsIRDFResource *item, nsIAtom *property, PRInt32 oldValue, PRInt32 newValue)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
csBlogIncomingServer::OnItemBoolPropertyChanged(nsIRDFResource *item, nsIAtom *property, PRBool oldValue, PRBool newValue)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
csBlogIncomingServer::OnItemUnicharPropertyChanged(nsIRDFResource *item, nsIAtom *property, const PRUnichar *oldValue, const PRUnichar *newValue)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
csBlogIncomingServer::OnItemPropertyFlagChanged(nsIMsgDBHdr *item, nsIAtom *property, PRUint32 oldFlag, PRUint32 newFlag)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
csBlogIncomingServer::OnItemEvent(nsIMsgFolder *aFolder, nsIAtom *aEvent)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

