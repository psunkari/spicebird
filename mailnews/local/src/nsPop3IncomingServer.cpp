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
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
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

#include "prmem.h"
#include "plstr.h"
#include "prprf.h"

#include "nsCOMPtr.h"
#include "nsIStringBundle.h"
#include "nsIPop3IncomingServer.h"
#include "nsPop3IncomingServer.h"
#include "nsIPop3Service.h"
#include "nsMsgBaseCID.h"
#include "nsMsgLocalCID.h"
#include "nsMsgFolderFlags.h"
#include "nsPop3Protocol.h"
#include "nsIMsgLocalMailFolder.h"
#include "nsIMsgAccountManager.h"
#include "nsIMsgMailNewsUrl.h"
#include "nsServiceManagerUtils.h"
#include "nsIMutableArray.h"
#include "nsMsgUtils.h"

static NS_DEFINE_CID(kCPop3ServiceCID, NS_POP3SERVICE_CID);

class nsPop3GetMailChainer : public nsIUrlListener
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIURLLISTENER

  nsPop3GetMailChainer();
  ~nsPop3GetMailChainer();
  nsresult GetNewMailForServers(nsISupportsArray *servers, nsIMsgWindow *msgWindow,
                                nsIMsgFolder *folderToDownloadTo, nsIUrlListener *listener);
  nsresult RunNextGetNewMail();
protected:
  nsCOMPtr <nsIMsgFolder> m_folderToDownloadTo;
  nsCOMPtr <nsIMsgWindow> m_downloadingMsgWindow;
  nsCOMPtr <nsISupportsArray> m_serversToGetNewMailFor;
  nsCOMPtr <nsIUrlListener> m_listener;
};



NS_IMPL_ISUPPORTS_INHERITED2(nsPop3IncomingServer,
                             nsMsgIncomingServer,
                             nsIPop3IncomingServer,
                             nsILocalMailIncomingServer)

nsPop3IncomingServer::nsPop3IncomingServer()
{
  m_capabilityFlags =
  POP3_AUTH_MECH_UNDEFINED |
  POP3_HAS_AUTH_USER |               // should be always there
  POP3_GURL_UNDEFINED |
  POP3_UIDL_UNDEFINED |
  POP3_TOP_UNDEFINED |
  POP3_XTND_XLST_UNDEFINED;

  m_canHaveFilters = PR_TRUE;
  m_authenticated = PR_FALSE;
}

nsPop3IncomingServer::~nsPop3IncomingServer()
{
}

NS_IMPL_SERVERPREF_BOOL(nsPop3IncomingServer,
                        LeaveMessagesOnServer,
                        "leave_on_server")

NS_IMPL_SERVERPREF_BOOL(nsPop3IncomingServer,
                        HeadersOnly,
                        "headers_only")

NS_IMPL_SERVERPREF_BOOL(nsPop3IncomingServer,
                        DeleteMailLeftOnServer,
                        "delete_mail_left_on_server")

NS_IMPL_SERVERPREF_BOOL(nsPop3IncomingServer,
                        AuthLogin,
                        "auth_login")

NS_IMPL_SERVERPREF_BOOL(nsPop3IncomingServer,
                        DotFix,
                        "dot_fix")

NS_IMPL_SERVERPREF_BOOL(nsPop3IncomingServer,
                        DeleteByAgeFromServer,
                        "delete_by_age_from_server")

NS_IMPL_SERVERPREF_INT(nsPop3IncomingServer,
                        NumDaysToLeaveOnServer,
                        "num_days_to_leave_on_server")


NS_IMPL_SERVERPREF_BOOL(nsPop3IncomingServer,
                            DeferGetNewMail,
                            "defer_get_new_mail")

NS_IMETHODIMP nsPop3IncomingServer::GetDeferredToAccount(nsACString& aRetVal)
{
  nsresult rv = GetCharValue("deferred_to_account", aRetVal);
  if (aRetVal.IsEmpty())
    return rv;
  // We need to repair broken profiles that defer to hidden or invalid servers,
  // so find out if the deferred to account has a valid non-hidden server, and
  // if not, defer to the local folders inbox.
  nsCOMPtr<nsIMsgAccountManager> acctMgr =
                      do_GetService(NS_MSGACCOUNTMANAGER_CONTRACTID);
  PRBool invalidAccount = PR_TRUE;
  if (acctMgr)
  {
    nsCOMPtr<nsIMsgAccount> account;
    nsCOMPtr<nsIMsgIncomingServer> server;
    rv = acctMgr->GetAccount(aRetVal, getter_AddRefs(account));
    if (account)
    {
      account->GetIncomingServer(getter_AddRefs(server));
      if (server)
        server->GetHidden(&invalidAccount);
    }
    if (invalidAccount)
    {
      nsCOMPtr<nsIMsgIncomingServer> localServer;
      nsCOMPtr<nsIMsgAccount> localAccount;

      rv = acctMgr->GetLocalFoldersServer(getter_AddRefs(localServer));
      NS_ENSURE_SUCCESS(rv, rv);
      // Try to copy any folders that have been stranded in the hidden account
      // into the local folders account.
      if (server)
      {
        nsCOMPtr<nsIMsgFolder> hiddenRootFolder;
        nsCOMPtr<nsIMsgFolder> localFoldersRoot;
        server->GetRootFolder(getter_AddRefs(hiddenRootFolder));
        localServer->GetRootFolder(getter_AddRefs(localFoldersRoot));
        if (hiddenRootFolder && localFoldersRoot)
        {
          // We're going to iterate over the folders in Local Folders-1,
          // though I suspect only the Inbox will have messages. I don't
          // think Sent Mail could end up here, but if any folders have
          // messages, might as well copy them to the real Local Folders
          // account.
          nsCOMPtr<nsISimpleEnumerator> enumerator;
          rv = hiddenRootFolder->GetSubFolders(getter_AddRefs(enumerator));
          if (NS_SUCCEEDED(rv))
          {
            PRBool hasMore;
            while (NS_SUCCEEDED(enumerator->HasMoreElements(&hasMore)) &&
                   hasMore)
            {
              nsCOMPtr<nsISupports> item;
              enumerator->GetNext(getter_AddRefs(item));
              nsCOMPtr<nsIMsgFolder> subFolder(do_QueryInterface(item));
              if (subFolder)
              {
                nsCOMPtr<nsIMsgDatabase> subFolderDB;
                subFolder->GetMsgDatabase(getter_AddRefs(subFolderDB));
                if (subFolderDB)
                {
                  // Copy any messages in this sub-folder of the hidden
                  // account to the corresponding folder in Local Folders.
                  nsTArray<nsMsgKey> keys;
                  rv = subFolderDB->ListAllKeys(keys);
                  nsCOMPtr<nsIMutableArray> hdrsToCopy(do_CreateInstance(NS_ARRAY_CONTRACTID));
                  MsgGetHeadersFromKeys(subFolderDB, keys, hdrsToCopy);
                  PRUint32 numHdrs = 0;
                  if (hdrsToCopy)
                    hdrsToCopy->GetLength(&numHdrs);
                  if (numHdrs)
                  {
                    // Look for a folder with the same name in Local Folders.
                    nsCOMPtr<nsIMsgFolder> dest;
                    nsString folderName;
                    subFolder->GetName(folderName);
                    localFoldersRoot->GetChildNamed(folderName,
                                                    getter_AddRefs(dest));
                    if (dest)
                      dest->CopyMessages(subFolder, hdrsToCopy, PR_FALSE,
                                         nsnull, nsnull, PR_FALSE,PR_FALSE);
                    // Should we copy the folder if the dest doesn't exist?
                  }
                }
              }
            }
          }
        }
      }
      rv = acctMgr->FindAccountForServer(localServer, getter_AddRefs(localAccount));
      NS_ENSURE_SUCCESS(rv, rv);
      if (!localAccount)
        return NS_ERROR_NOT_AVAILABLE;

      localAccount->GetKey(aRetVal);
      // Can't call SetDeferredToAccount because it calls GetDeferredToAccount.
      return SetCharValue("deferred_to_account", aRetVal);
    }
  }
  return rv;
}

NS_IMETHODIMP nsPop3IncomingServer::SetDeferredToAccount(const nsACString& aAccountKey)
{
  nsCString deferredToAccount;
  GetDeferredToAccount(deferredToAccount);
  m_rootMsgFolder = nsnull; // clear this so we'll recalculate it on demand.
  //Notify listeners who listen to every folder

  nsresult rv =  SetCharValue("deferred_to_account", aAccountKey);
  NS_ENSURE_SUCCESS(rv, rv);
  nsCOMPtr<nsIFolderListener> folderListenerManager =
           do_GetService(NS_MSGMAILSESSION_CONTRACTID, &rv);
  if (NS_SUCCEEDED(rv))
  {

    nsCOMPtr<nsIMsgFolder> rootFolder;
    // use GetRootFolder, because that returns the real
    // root, not the deferred to root.
    rv = GetRootFolder(getter_AddRefs(rootFolder));
    if (rootFolder)
    {
      // if isDeferred state has changed, send notification
      if (aAccountKey.IsEmpty() != deferredToAccount.IsEmpty())
      {
        nsCOMPtr <nsIAtom> deferAtom = getter_AddRefs(NS_NewAtom("isDeferred"));
        nsCOMPtr <nsIAtom> canFileAtom = getter_AddRefs(NS_NewAtom("CanFileMessages"));
        folderListenerManager->OnItemBoolPropertyChanged(rootFolder, deferAtom,
                  !deferredToAccount.IsEmpty(), deferredToAccount.IsEmpty());
        folderListenerManager->OnItemBoolPropertyChanged(rootFolder, canFileAtom,
                  deferredToAccount.IsEmpty(), !deferredToAccount.IsEmpty());

        // this hack causes the account manager ds to send notifications to the
        // xul content builder that make the changed acct appear or disappear
        // from the folder pane and related menus.
        nsCOMPtr<nsIMsgAccountManager> acctMgr =
                            do_GetService(NS_MSGACCOUNTMANAGER_CONTRACTID);
        if (acctMgr)
        {
          acctMgr->NotifyServerUnloaded(this);
          acctMgr->NotifyServerLoaded(this);
          // check if this newly deferred to account is the local folders account
          // and needs to have a newly created INBOX.
          if (!aAccountKey.IsEmpty())
          {
            nsCOMPtr <nsIMsgAccount> account;
            acctMgr->GetAccount(aAccountKey, getter_AddRefs(account));
            if (account)
            {
              nsCOMPtr <nsIMsgIncomingServer> server;
              account->GetIncomingServer(getter_AddRefs(server));
              if (server)
              {
                nsCOMPtr <nsILocalMailIncomingServer> incomingLocalServer = do_QueryInterface(server);
                if (incomingLocalServer)
                {
                  nsCOMPtr <nsIMsgFolder> rootFolder;
                  rv = server->GetRootFolder(getter_AddRefs(rootFolder));
                  NS_ENSURE_SUCCESS(rv, rv);
                  // this will fail if it already exists, which is fine.
                  rootFolder->CreateSubfolder(NS_LITERAL_STRING("Inbox"), nsnull);
                }
              }
            }
          }
        }
      }
    }
  }
  return rv;
}

//NS_IMPL_GETSET(nsPop3IncomingServer, Authenticated, PRBool, m_authenticated);

NS_IMETHODIMP nsPop3IncomingServer::GetAuthenticated(PRBool *aAuthenticated)
{
  NS_ENSURE_ARG_POINTER(aAuthenticated);
  *aAuthenticated = m_authenticated;
  return NS_OK;
}

NS_IMETHODIMP nsPop3IncomingServer::SetAuthenticated(PRBool aAuthenticated)
{
  m_authenticated = aAuthenticated;
  return NS_OK;
}

nsresult
nsPop3IncomingServer::GetPop3CapabilityFlags(PRUint32 *flags)
{
  *flags = m_capabilityFlags;
  return NS_OK;
}

nsresult
nsPop3IncomingServer::SetPop3CapabilityFlags(PRUint32 flags)
{
  m_capabilityFlags = flags;
  return NS_OK;
}

NS_IMETHODIMP
nsPop3IncomingServer::GetRootMsgFolder(nsIMsgFolder **aRootMsgFolder)
{
  NS_ENSURE_ARG_POINTER(aRootMsgFolder);
  nsresult rv = NS_OK;
  if (!m_rootMsgFolder)
  {
    nsCString deferredToAccount;
    GetDeferredToAccount(deferredToAccount);
    if (deferredToAccount.IsEmpty())
    {
      rv = CreateRootFolder();
      m_rootMsgFolder = m_rootFolder;
    }
    else
    {
      nsCOMPtr <nsIMsgAccountManager> accountManager = do_GetService(NS_MSGACCOUNTMANAGER_CONTRACTID, &rv);
      NS_ENSURE_SUCCESS(rv,rv);
      nsCOMPtr <nsIMsgAccount> account;
      rv = accountManager->GetAccount(deferredToAccount, getter_AddRefs(account));
      NS_ENSURE_SUCCESS(rv,rv);
      if (account)
      {
        nsCOMPtr <nsIMsgIncomingServer> incomingServer;
        rv = account->GetIncomingServer(getter_AddRefs(incomingServer));
        NS_ENSURE_SUCCESS(rv,rv);
        // make sure we're not deferred to ourself...
        if (incomingServer && incomingServer != this)
          rv = incomingServer->GetRootMsgFolder(getter_AddRefs(m_rootMsgFolder));
        else
          rv = NS_ERROR_FAILURE;
      }
    }
  }

  NS_IF_ADDREF(*aRootMsgFolder = m_rootMsgFolder);
  return m_rootMsgFolder ? rv : NS_ERROR_FAILURE;
}

nsresult nsPop3IncomingServer::GetInbox(nsIMsgWindow *msgWindow, nsIMsgFolder **inbox)
{
  NS_ENSURE_ARG_POINTER(inbox);
  nsCOMPtr<nsIMsgFolder> rootFolder;
  nsresult rv = GetRootMsgFolder(getter_AddRefs(rootFolder));
  if(NS_SUCCEEDED(rv) && rootFolder)
  {
    rootFolder->GetFolderWithFlags(nsMsgFolderFlags::Inbox, inbox);
  }

  nsCOMPtr<nsIMsgLocalMailFolder> localInbox = do_QueryInterface(*inbox, &rv);
  if (NS_SUCCEEDED(rv) && localInbox)
  {
    nsCOMPtr <nsIMsgDatabase> db;
    rv = (*inbox)->GetMsgDatabase(getter_AddRefs(db));
    if (NS_FAILED(rv))
    {
      (*inbox)->SetMsgDatabase(nsnull);
      (void) localInbox->SetCheckForNewMessagesAfterParsing(PR_TRUE);
      // this will cause a reparse of the mail folder.
      localInbox->GetDatabaseWithReparse(nsnull, msgWindow, getter_AddRefs(db));
      rv = NS_MSG_ERROR_FOLDER_SUMMARY_OUT_OF_DATE;
    }
  }
  return rv;
}

NS_IMETHODIMP nsPop3IncomingServer::PerformBiff(nsIMsgWindow *aMsgWindow)
{
  nsresult rv;
  nsCOMPtr<nsIPop3Service> pop3Service(do_GetService(kCPop3ServiceCID, &rv));
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIMsgFolder> inbox;
  nsCOMPtr<nsIMsgFolder> rootMsgFolder;
  nsCOMPtr<nsIUrlListener> urlListener;
  rv = GetRootMsgFolder(getter_AddRefs(rootMsgFolder));
  NS_ENSURE_TRUE(rootMsgFolder, NS_ERROR_FAILURE);

  rootMsgFolder->GetFolderWithFlags(nsMsgFolderFlags::Inbox,
                                    getter_AddRefs(inbox));
  if (!inbox)
    return NS_ERROR_FAILURE;

  nsCOMPtr <nsIMsgIncomingServer> server;
  inbox->GetServer(getter_AddRefs(server));

  server->SetPerformingBiff(PR_TRUE);

  urlListener = do_QueryInterface(inbox);

  PRBool downloadOnBiff = PR_FALSE;
  rv = GetDownloadOnBiff(&downloadOnBiff);
  if (downloadOnBiff)
  {
    nsCOMPtr <nsIMsgLocalMailFolder> localInbox = do_QueryInterface(inbox, &rv);
    if (localInbox && NS_SUCCEEDED(rv))
    {
      PRBool valid = PR_FALSE;
      nsCOMPtr <nsIMsgDatabase> db;
      rv = inbox->GetMsgDatabase(getter_AddRefs(db));
      if (NS_SUCCEEDED(rv) && db)
        rv = db->GetSummaryValid(&valid);
      if (NS_SUCCEEDED(rv) && valid)
        rv = pop3Service->GetNewMail(aMsgWindow, urlListener, inbox, this, nsnull);
      else
      {
        PRBool isLocked;
        inbox->GetLocked(&isLocked);
        if (!isLocked)
          rv = localInbox->GetDatabaseWithReparse(urlListener, aMsgWindow, getter_AddRefs(db));
        if (NS_SUCCEEDED(rv))
          rv = localInbox->SetCheckForNewMessagesAfterParsing(PR_TRUE);
      }
    }
  }
  else
    rv = pop3Service->CheckForNewMail(nsnull, urlListener, inbox, this, nsnull);
    // it's important to pass in null for the msg window if we are performing biff
        // this makes sure that we don't show any kind of UI during biff.
  return NS_OK;
}

NS_IMETHODIMP
nsPop3IncomingServer::SetFlagsOnDefaultMailboxes()
{
  nsCOMPtr<nsIMsgFolder> rootFolder;
  nsresult rv = GetRootFolder(getter_AddRefs(rootFolder));
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIMsgLocalMailFolder> localFolder = do_QueryInterface(rootFolder, &rv);
  NS_ENSURE_SUCCESS(rv, rv);

  // pop3 gets an inbox, but no queue (unsent messages)
  localFolder->SetFlagsOnDefaultMailboxes(nsMsgFolderFlags::Inbox |
                                          nsMsgFolderFlags::Archive |
                                          nsMsgFolderFlags::SentMail |
                                          nsMsgFolderFlags::Drafts |
                                          nsMsgFolderFlags::Templates |
                                          nsMsgFolderFlags::Trash |
                                          nsMsgFolderFlags::Junk);
  return NS_OK;
}


NS_IMETHODIMP nsPop3IncomingServer::CreateDefaultMailboxes(nsIFile *aPath)
{
  NS_ENSURE_ARG_POINTER(aPath);
  nsCOMPtr <nsIFile> path;
  nsresult rv = aPath->Clone(getter_AddRefs(path));
  NS_ENSURE_SUCCESS(rv, rv);

  (void) path->AppendNative(NS_LITERAL_CSTRING("Inbox"));
  rv = CreateLocalFolder(path, NS_LITERAL_CSTRING("Inbox"));
  NS_ENSURE_SUCCESS(rv, rv);
  return CreateLocalFolder(path, NS_LITERAL_CSTRING("Trash"));
}

// override this so we can say that deferred accounts can't have messages
// filed to them, which will remove them as targets of all the move/copy
// menu items.
NS_IMETHODIMP
nsPop3IncomingServer::GetCanFileMessagesOnServer(PRBool *aCanFileMessagesOnServer)
{
  NS_ENSURE_ARG_POINTER(aCanFileMessagesOnServer);

  nsCString deferredToAccount;
  GetDeferredToAccount(deferredToAccount);
  *aCanFileMessagesOnServer = deferredToAccount.IsEmpty();
  return NS_OK;
}


NS_IMETHODIMP
nsPop3IncomingServer::GetCanCreateFoldersOnServer(PRBool *aCanCreateFoldersOnServer)
{
  NS_ENSURE_ARG_POINTER(aCanCreateFoldersOnServer);

  nsCString deferredToAccount;
  GetDeferredToAccount(deferredToAccount);
  *aCanCreateFoldersOnServer = deferredToAccount.IsEmpty();
  return NS_OK;
}

NS_IMETHODIMP
nsPop3IncomingServer::VerifyLogon(nsIUrlListener *aUrlListener,
                                  nsIMsgWindow *aMsgWindow, nsIURI **aURL)
{
  nsresult rv;
  nsCOMPtr<nsIPop3Service> pop3Service = do_GetService(kCPop3ServiceCID, &rv);
  NS_ENSURE_SUCCESS(rv,rv);
  return pop3Service->VerifyLogon(this, aUrlListener, aMsgWindow, aURL);
}

NS_IMETHODIMP nsPop3IncomingServer::DownloadMailFromServers(nsISupportsArray *aServers,
                              nsIMsgWindow *aMsgWindow,
                              nsIMsgFolder *aFolder,
                              nsIUrlListener *aUrlListener)
{
  nsPop3GetMailChainer *getMailChainer = new nsPop3GetMailChainer;
  NS_ENSURE_TRUE(getMailChainer, NS_ERROR_OUT_OF_MEMORY);
  getMailChainer->AddRef(); // this object owns itself and releases when done.
  return getMailChainer->GetNewMailForServers(aServers, aMsgWindow, aFolder, aUrlListener);
}

NS_IMETHODIMP nsPop3IncomingServer::GetNewMail(nsIMsgWindow *aMsgWindow, nsIUrlListener *aUrlListener, nsIMsgFolder *aInbox, nsIURI **aResult)
{
  nsresult rv;
  nsCOMPtr<nsIPop3Service> pop3Service = do_GetService(kCPop3ServiceCID, &rv);
  NS_ENSURE_SUCCESS(rv,rv);
  return pop3Service->GetNewMail(aMsgWindow, aUrlListener, aInbox, this, aResult);
}

// user has clicked get new messages on this server. If other servers defer to this server,
// we need to get new mail for them. But if this server defers to an other server,
// I think we only get new mail for this server.
NS_IMETHODIMP
nsPop3IncomingServer::GetNewMessages(nsIMsgFolder *aFolder, nsIMsgWindow *aMsgWindow,
                      nsIUrlListener *aUrlListener)
{
  nsresult rv;

  nsCOMPtr<nsIPop3Service> pop3Service = do_GetService(kCPop3ServiceCID, &rv);
  NS_ENSURE_SUCCESS(rv,rv);

  nsCOMPtr <nsIMsgFolder> inbox;
  rv = GetInbox(aMsgWindow, getter_AddRefs(inbox));
  NS_ENSURE_SUCCESS(rv, rv);
  nsCOMPtr <nsIURI> url;
  nsCOMPtr <nsIMsgIncomingServer> server;
  nsCOMPtr <nsISupportsArray> deferredServers;
  nsCString deferredToAccount;
  GetDeferredToAccount(deferredToAccount);

  if (deferredToAccount.IsEmpty())
  {
    aFolder->GetServer(getter_AddRefs(server));
    GetDeferredServers(server, getter_AddRefs(deferredServers));
  }
  PRUint32 numDeferredServers;
  if (deferredToAccount.IsEmpty() && deferredServers && NS_SUCCEEDED(deferredServers->Count(&numDeferredServers))
    && numDeferredServers > 0)
  {
    nsPop3GetMailChainer *getMailChainer = new nsPop3GetMailChainer;
    NS_ENSURE_TRUE(getMailChainer, NS_ERROR_OUT_OF_MEMORY);
    getMailChainer->AddRef(); // this object owns itself and releases when done.
    nsCOMPtr <nsISupports> supports;
    this->QueryInterface(NS_GET_IID(nsISupports), getter_AddRefs(supports));
    deferredServers->InsertElementAt(supports, 0);
    rv = getMailChainer->GetNewMailForServers(deferredServers, aMsgWindow, inbox, aUrlListener);
  }
  else
    rv = pop3Service->GetNewMail(aMsgWindow, aUrlListener, inbox, this, getter_AddRefs(url));
  return rv;
}

NS_IMETHODIMP
nsPop3IncomingServer::GetDownloadMessagesAtStartup(PRBool *getMessagesAtStartup)
{
  NS_ENSURE_ARG_POINTER(getMessagesAtStartup);
  // GetMessages is not automatically done for pop servers at startup.
  // We need to trigger that action. Return true.
  *getMessagesAtStartup = PR_TRUE;
  return NS_OK;
}

NS_IMETHODIMP
nsPop3IncomingServer::GetCanBeDefaultServer(PRBool *canBeDefaultServer)
{
  NS_ENSURE_ARG_POINTER(canBeDefaultServer);
  *canBeDefaultServer = PR_TRUE;
  return NS_OK;
}

NS_IMETHODIMP
nsPop3IncomingServer::GetCanSearchMessages(PRBool *canSearchMessages)
{
  // this will return false if this server is deferred, which is what we want.
  return GetCanFileMessagesOnServer(canSearchMessages);
}

NS_IMETHODIMP
nsPop3IncomingServer::GetOfflineSupportLevel(PRInt32 *aSupportLevel)
{
  NS_ENSURE_ARG_POINTER(aSupportLevel);

  nsresult rv;
  rv = GetIntValue("offline_support_level", aSupportLevel);
  if (*aSupportLevel != OFFLINE_SUPPORT_LEVEL_UNDEFINED) return rv;

  // set default value
  *aSupportLevel = OFFLINE_SUPPORT_LEVEL_NONE;
  return NS_OK;
}

NS_IMETHODIMP
nsPop3IncomingServer::SetRunningProtocol(nsIPop3Protocol *aProtocol)
{
  NS_ASSERTION(!aProtocol || !m_runningProtocol, "overriding running protocol");
  m_runningProtocol = aProtocol;
  return NS_OK;
}

NS_IMETHODIMP nsPop3IncomingServer::GetRunningProtocol(nsIPop3Protocol **aProtocol)
{
  NS_ENSURE_ARG_POINTER(aProtocol);
  NS_IF_ADDREF(*aProtocol = m_runningProtocol);
  return NS_OK;
}

NS_IMETHODIMP nsPop3IncomingServer::AddUidlToMark(const char *aUidl, PRInt32 aMark)
{
  Pop3UidlEntry *uidlEntry;
  nsresult rv = NS_ERROR_OUT_OF_MEMORY;

  uidlEntry = PR_NEWZAP(Pop3UidlEntry);
  if (uidlEntry)
  {
    uidlEntry->uidl = strdup(aUidl);
    if (uidlEntry->uidl)
    {
      uidlEntry->status = (aMark == POP3_DELETE) ? DELETE_CHAR :
      (aMark == POP3_FETCH_BODY) ? FETCH_BODY : KEEP;
      m_uidlsToMark.AppendElement(uidlEntry);
      rv = NS_OK;
    } else
      PR_Free(uidlEntry);
  }
  return rv;
}

NS_IMETHODIMP nsPop3IncomingServer::MarkMessages()
{
  nsresult rv;
  if (m_runningProtocol)
    rv = m_runningProtocol->MarkMessages(&m_uidlsToMark);
  else
  {
    nsCString hostName;
    nsCString userName;
    nsCOMPtr<nsILocalFile> localPath;

    GetLocalPath(getter_AddRefs(localPath));

    GetHostName(hostName);
    GetUsername(userName);
    // do it all in one fell swoop
    rv = nsPop3Protocol::MarkMsgForHost(hostName.get(), userName.get(), localPath, m_uidlsToMark);
  }
  PRUint32 count = m_uidlsToMark.Count();
  for (PRUint32 i = 0; i < count; i++)
  {
    Pop3UidlEntry *ue = static_cast<Pop3UidlEntry*>(m_uidlsToMark[i]);
    PR_Free(ue->uidl);
    PR_Free(ue);
  }
  m_uidlsToMark.Clear();
  return rv;
}

NS_IMPL_ISUPPORTS1(nsPop3GetMailChainer, nsIUrlListener)

nsPop3GetMailChainer::nsPop3GetMailChainer()
{
}
nsPop3GetMailChainer::~nsPop3GetMailChainer()
{
}

nsresult nsPop3GetMailChainer::GetNewMailForServers(nsISupportsArray *servers, nsIMsgWindow *msgWindow,
                                nsIMsgFolder *folderToDownloadTo, nsIUrlListener *listener)
{
  NS_ENSURE_ARG_POINTER(folderToDownloadTo);

  m_serversToGetNewMailFor = servers;
  m_folderToDownloadTo = folderToDownloadTo;
  m_downloadingMsgWindow = msgWindow;
  m_listener = listener;
  nsCOMPtr <nsIMsgDatabase> destFolderDB;

  nsresult rv = folderToDownloadTo->GetMsgDatabase(getter_AddRefs(destFolderDB));
  if (NS_FAILED(rv) || !destFolderDB)
  {
    nsCOMPtr <nsIMsgLocalMailFolder> localFolder = do_QueryInterface(folderToDownloadTo);
    if (localFolder)
    {
      localFolder->GetDatabaseWithReparse(this, msgWindow, getter_AddRefs(destFolderDB));
      return NS_OK;
    }
  }
  return RunNextGetNewMail();
}

NS_IMETHODIMP
nsPop3GetMailChainer::OnStartRunningUrl(nsIURI *url)
{
  return NS_OK;
}

NS_IMETHODIMP
nsPop3GetMailChainer::OnStopRunningUrl(nsIURI *aUrl, nsresult aExitCode)
{
  return RunNextGetNewMail();
}

nsresult nsPop3GetMailChainer::RunNextGetNewMail()
{
  nsresult rv;
  PRUint32 numServersLeft;
  m_serversToGetNewMailFor->Count(&numServersLeft);

  for (; numServersLeft > 0;)
  {
    nsCOMPtr <nsIPop3IncomingServer> popServer (do_QueryElementAt(m_serversToGetNewMailFor, 0));
    m_serversToGetNewMailFor->RemoveElementAt(0);
    numServersLeft--;
    if (popServer)
    {
      PRBool deferGetNewMail = PR_FALSE;
      nsCOMPtr <nsIMsgIncomingServer> downloadingToServer;
      m_folderToDownloadTo->GetServer(getter_AddRefs(downloadingToServer));
      popServer->GetDeferGetNewMail(&deferGetNewMail);
      nsCOMPtr <nsIMsgIncomingServer> server = do_QueryInterface(popServer);
      if (deferGetNewMail || downloadingToServer == server)
      {
        // have to call routine that just gets mail for one server,
        // and ignores deferred servers...
        if (server)
        {
          nsCOMPtr <nsIURI> url;
          nsCOMPtr<nsIPop3Service> pop3Service = do_GetService(kCPop3ServiceCID, &rv);
          NS_ENSURE_SUCCESS(rv,rv);
          return pop3Service->GetNewMail(m_downloadingMsgWindow, this, m_folderToDownloadTo, popServer, getter_AddRefs(url));
        }
      }
    }
  }
  rv = m_listener ? m_listener->OnStopRunningUrl(nsnull, NS_OK) : NS_OK;
  Release(); // release ref to ourself.
  return rv;
}
