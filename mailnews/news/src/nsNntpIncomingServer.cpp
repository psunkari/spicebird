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
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Seth Spitzer <sspitzer@netscape.com>
 *   David Bienvenu <bienvenu@nventure.com>
 *   Henrik Gemal <mozilla@gemal.dk>
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

#include "nsNntpIncomingServer.h"
#include "nsIPrefBranch.h"
#include "nsIPrefService.h"
#include "nsNewsFolder.h"
#include "nsIMsgFolder.h"
#include "nsILocalFile.h"
#include "nsCOMPtr.h"
#include "nsINntpService.h"
#include "nsINNTPProtocol.h"
#include "nsMsgNewsCID.h"
#include "nsNNTPProtocol.h"
#include "nsIDirectoryService.h"
#include "nsMailDirServiceDefs.h"
#include "nsInt64.h"
#include "nsMsgUtils.h"
#include "nsIPrompt.h"
#include "nsIStringBundle.h"
#include "nntpCore.h"
#include "nsIWindowWatcher.h"
#include "nsITreeColumns.h"
#include "nsIDOMElement.h"
#include "nsMsgFolderFlags.h"
#include "nsMsgI18N.h"
#include "nsUnicharUtils.h"
#include "nsEscape.h"
#include "nsISupportsObsolete.h"
#include "nsILineInputStream.h"
#include "nsNetUtil.h"
#include "nsISimpleEnumerator.h"

#define INVALID_VERSION         0
#define VALID_VERSION           1
#define NEW_NEWS_DIR_NAME       "News"
#define PREF_MAIL_NEWSRC_ROOT   "mail.newsrc_root"
#define PREF_MAIL_NEWSRC_ROOT_REL "mail.newsrc_root-rel"
#define PREF_MAILNEWS_VIEW_DEFAULT_CHARSET "mailnews.view_default_charset"
#define HOSTINFO_FILE_NAME      "hostinfo.dat"

#define NEWS_DELIMITER          '.'

// this platform specific junk is so the newsrc filenames we create
// will resemble the migrated newsrc filenames.
#if defined(XP_UNIX) || defined(XP_BEOS)
#define NEWSRC_FILE_PREFIX "newsrc-"
#define NEWSRC_FILE_SUFFIX ""
#else
#define NEWSRC_FILE_PREFIX ""
#define NEWSRC_FILE_SUFFIX ".rc"
#endif /* XP_UNIX || XP_BEOS */

// ###tw  This really ought to be the most
// efficient file reading size for the current
// operating system.
#define HOSTINFO_FILE_BUFFER_SIZE 1024

static NS_DEFINE_CID(kSubscribableServerCID, NS_SUBSCRIBABLESERVER_CID);

NS_IMPL_ADDREF_INHERITED(nsNntpIncomingServer, nsMsgIncomingServer)
NS_IMPL_RELEASE_INHERITED(nsNntpIncomingServer, nsMsgIncomingServer)

NS_INTERFACE_MAP_BEGIN(nsNntpIncomingServer)
    NS_INTERFACE_MAP_ENTRY(nsINntpIncomingServer)
    NS_INTERFACE_MAP_ENTRY(nsIUrlListener)
    NS_INTERFACE_MAP_ENTRY(nsISubscribableServer)
    NS_INTERFACE_MAP_ENTRY(nsITreeView)
NS_INTERFACE_MAP_END_INHERITING(nsMsgIncomingServer)

nsNntpIncomingServer::nsNntpIncomingServer()
{
  mNewsrcHasChanged = PR_FALSE;

  mHostInfoLoaded = PR_FALSE;
  mHostInfoHasChanged = PR_FALSE;
  mVersion = INVALID_VERSION;

  mLastGroupDate = 0;
  mUniqueId = 0;
  mHasSeenBeginGroups = PR_FALSE;
  mPostingAllowed = PR_FALSE;
  m_userAuthenticated = PR_FALSE;
  mLastUpdatedTime = 0;

  // these atoms are used for subscribe search
  mSubscribedAtom = do_GetAtom("subscribed");
  mNntpAtom = do_GetAtom("nntp");

  // we have server wide and per group filters
  m_canHaveFilters = PR_TRUE;

  SetupNewsrcSaveTimer();
}

nsNntpIncomingServer::~nsNntpIncomingServer()
{
    nsresult rv;

    if (mNewsrcSaveTimer) {
        mNewsrcSaveTimer->Cancel();
        mNewsrcSaveTimer = nsnull;
    }
    rv = ClearInner();
    NS_ASSERTION(NS_SUCCEEDED(rv), "ClearInner failed");

    rv = CloseCachedConnections();
    NS_ASSERTION(NS_SUCCEEDED(rv), "CloseCachedConnections failed");
}

NS_IMPL_SERVERPREF_BOOL(nsNntpIncomingServer, NotifyOn, "notify.on")
NS_IMPL_SERVERPREF_BOOL(nsNntpIncomingServer, MarkOldRead, "mark_old_read")
NS_IMPL_SERVERPREF_BOOL(nsNntpIncomingServer, Abbreviate, "abbreviate")
NS_IMPL_SERVERPREF_BOOL(nsNntpIncomingServer, PushAuth, "always_authenticate")
NS_IMPL_SERVERPREF_BOOL(nsNntpIncomingServer, SingleSignon, "singleSignon")
NS_IMPL_SERVERPREF_INT(nsNntpIncomingServer, MaxArticles, "max_articles")

nsresult
nsNntpIncomingServer::CreateRootFolderFromUri(const nsCString &serverUri,
                                              nsIMsgFolder **rootFolder)
{
  nsMsgNewsFolder *newRootFolder = new nsMsgNewsFolder;
  if (!newRootFolder)
    return NS_ERROR_OUT_OF_MEMORY;
  NS_ADDREF(*rootFolder = newRootFolder);
  newRootFolder->Init(serverUri.get());
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetNewsrcFilePath(nsILocalFile **aNewsrcFilePath)
{
  nsresult rv;
  if (mNewsrcFilePath)
  {
    *aNewsrcFilePath = mNewsrcFilePath;
    NS_IF_ADDREF(*aNewsrcFilePath);
    return NS_OK;
  }

  rv = GetFileValue("newsrc.file-rel", "newsrc.file", aNewsrcFilePath);
  if (NS_SUCCEEDED(rv) && *aNewsrcFilePath)
  {
    mNewsrcFilePath = *aNewsrcFilePath;
    return rv;
  }

  rv = GetNewsrcRootPath(getter_AddRefs(mNewsrcFilePath));
  if (NS_FAILED(rv)) return rv;

  nsCString hostname;
  rv = GetHostName(hostname);
  NS_ENSURE_SUCCESS(rv, rv);

  nsCAutoString newsrcFileName(NEWSRC_FILE_PREFIX);
  newsrcFileName.Append(hostname);
  newsrcFileName.Append(NEWSRC_FILE_SUFFIX);
  rv = mNewsrcFilePath->AppendNative(newsrcFileName);
  rv = mNewsrcFilePath->CreateUnique(nsIFile::NORMAL_FILE_TYPE, 0644);
  NS_ENSURE_SUCCESS(rv, rv);

  rv = SetNewsrcFilePath(mNewsrcFilePath);
  NS_ENSURE_SUCCESS(rv, rv);

  NS_ADDREF(*aNewsrcFilePath = mNewsrcFilePath);
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetNewsrcFilePath(nsILocalFile *aFile)
{
    NS_ENSURE_ARG_POINTER(aFile);

    PRBool exists;
    nsresult rv = aFile->Exists(&exists);
    if (!exists)
    {
      rv = aFile->CreateUnique(nsIFile::NORMAL_FILE_TYPE, 0664);
      if (NS_FAILED(rv)) return rv;
    }
    return SetFileValue("newsrc.file-rel", "newsrc.file", aFile);
}

NS_IMETHODIMP
nsNntpIncomingServer::GetLocalStoreType(nsACString& type)
{
  type.AssignLiteral("news");
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetNewsrcRootPath(nsILocalFile *aNewsrcRootPath)
{
    NS_ENSURE_ARG(aNewsrcRootPath);
    return NS_SetPersistentFile(PREF_MAIL_NEWSRC_ROOT_REL, PREF_MAIL_NEWSRC_ROOT, aNewsrcRootPath);
}

NS_IMETHODIMP
nsNntpIncomingServer::GetNewsrcRootPath(nsILocalFile **aNewsrcRootPath)
{
    NS_ENSURE_ARG_POINTER(aNewsrcRootPath);
    *aNewsrcRootPath = nsnull;

    PRBool havePref;
    nsresult rv = NS_GetPersistentFile(PREF_MAIL_NEWSRC_ROOT_REL,
                              PREF_MAIL_NEWSRC_ROOT,
                              NS_APP_NEWS_50_DIR,
                              havePref,
                              aNewsrcRootPath);

    NS_ENSURE_SUCCESS(rv, rv);

    PRBool exists;
    rv = (*aNewsrcRootPath)->Exists(&exists);
    if (NS_SUCCEEDED(rv) && !exists)
        rv = (*aNewsrcRootPath)->Create(nsIFile::DIRECTORY_TYPE, 0775);
    NS_ENSURE_SUCCESS(rv, rv);

    if (!havePref || !exists)
    {
        rv = NS_SetPersistentFile(PREF_MAIL_NEWSRC_ROOT_REL, PREF_MAIL_NEWSRC_ROOT, *aNewsrcRootPath);
        NS_ASSERTION(NS_SUCCEEDED(rv), "Failed to set root dir pref.");
    }
    return rv;
}

/* static */ void nsNntpIncomingServer::OnNewsrcSaveTimer(nsITimer *timer, void *voidIncomingServer)
{
  nsNntpIncomingServer *incomingServer = (nsNntpIncomingServer*)voidIncomingServer;
  incomingServer->WriteNewsrcFile();
}

nsresult nsNntpIncomingServer::SetupNewsrcSaveTimer()
{
  nsInt64 ms(300000);   // hard code, 5 minutes.
  //Convert biffDelay into milliseconds
  PRUint32 timeInMSUint32 = (PRUint32)ms;
  //Can't currently reset a timer when it's in the process of
  //calling Notify. So, just release the timer here and create a new one.
  if(mNewsrcSaveTimer)
    mNewsrcSaveTimer->Cancel();
  mNewsrcSaveTimer = do_CreateInstance("@mozilla.org/timer;1");
  mNewsrcSaveTimer->InitWithFuncCallback(OnNewsrcSaveTimer, (void*)this, timeInMSUint32,
                                           nsITimer::TYPE_REPEATING_SLACK);
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetCharset(const nsACString & aCharset)
{
  return SetCharValue("charset", aCharset);
}

NS_IMETHODIMP
nsNntpIncomingServer::GetCharset(nsACString & aCharset)
{
  nsresult rv;
  //first we get the per-server settings mail.server.<serverkey>.charset
  rv = GetCharValue("charset", aCharset);

  //if the per-server setting is empty,we get the default charset from
  //mailnews.view_default_charset setting and set it as per-server preference.
  if(aCharset.IsEmpty()){
    nsString defaultCharset;
    rv = NS_GetLocalizedUnicharPreferenceWithDefault(nsnull,
         PREF_MAILNEWS_VIEW_DEFAULT_CHARSET,
         NS_LITERAL_STRING("ISO-8859-1"), defaultCharset);
    LossyCopyUTF16toASCII(defaultCharset, aCharset);
    SetCharset(aCharset);
  }
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::WriteNewsrcFile()
{
    nsresult rv;

    PRBool newsrcHasChanged;
    rv = GetNewsrcHasChanged(&newsrcHasChanged);
    if (NS_FAILED(rv)) return rv;

#ifdef DEBUG_NEWS
  nsCString hostname;
  rv = GetHostName(hostname);
  if (NS_FAILED(rv)) return rv;
#endif /* DEBUG_NEWS */

    if (newsrcHasChanged) {
#ifdef DEBUG_NEWS
        printf("write newsrc file for %s\n", hostname.get());
#endif
        nsCOMPtr <nsILocalFile> newsrcFile;
        rv = GetNewsrcFilePath(getter_AddRefs(newsrcFile));
        if (NS_FAILED(rv)) return rv;

        nsCOMPtr<nsIOutputStream> newsrcStream;
        nsresult rv = NS_NewLocalFileOutputStream(getter_AddRefs(newsrcStream), newsrcFile, -1, 00600);
        if (NS_FAILED(rv))
          return rv;

        nsCOMPtr<nsISimpleEnumerator> subFolders;
        nsCOMPtr<nsIMsgFolder> rootFolder;
        rv = GetRootFolder(getter_AddRefs(rootFolder));
        if (NS_FAILED(rv)) return rv;

        nsCOMPtr <nsIMsgNewsFolder> newsFolder = do_QueryInterface(rootFolder, &rv);
        if (NS_FAILED(rv)) return rv;

        PRUint32 bytesWritten;
        nsCString optionLines;
        rv = newsFolder->GetOptionLines(optionLines);
        if (NS_SUCCEEDED(rv) && !optionLines.IsEmpty()) {
          newsrcStream->Write(optionLines.get(), optionLines.Length(), &bytesWritten);
#ifdef DEBUG_NEWS
               printf("option lines:\n%s", optionLines.get());
#endif /* DEBUG_NEWS */
        }
#ifdef DEBUG_NEWS
        else {
            printf("no option lines to write out\n");
        }
#endif /* DEBUG_NEWS */

        nsCString unsubscribedLines;
        rv = newsFolder->GetUnsubscribedNewsgroupLines(unsubscribedLines);
        if (NS_SUCCEEDED(rv) && !unsubscribedLines.IsEmpty()) {
          newsrcStream->Write(unsubscribedLines.get(), unsubscribedLines.Length(), &bytesWritten);
#ifdef DEBUG_NEWS
               printf("unsubscribedLines:\n%s", unsubscribedLines.get());
#endif /* DEBUG_NEWS */
        }
#ifdef DEBUG_NEWS
        else {
            printf("no unsubscribed lines to write out\n");
        }
#endif /* DEBUG_NEWS */

        rv = rootFolder->GetSubFolders(getter_AddRefs(subFolders));
        if (NS_FAILED(rv)) return rv;

        PRBool moreFolders;

        while (NS_SUCCEEDED(subFolders->HasMoreElements(&moreFolders)) &&
               moreFolders) {
            nsCOMPtr<nsISupports> child;
            rv = subFolders->GetNext(getter_AddRefs(child));
            if (NS_SUCCEEDED(rv) && child) {
                newsFolder = do_QueryInterface(child, &rv);
                if (NS_SUCCEEDED(rv) && newsFolder) {
                    nsCString newsrcLine;
                    rv = newsFolder->GetNewsrcLine(newsrcLine);
                    if (NS_SUCCEEDED(rv) && !newsrcLine.IsEmpty()) {
                        // write the line to the newsrc file
                        newsrcStream->Write(newsrcLine.get(), newsrcLine.Length(), &bytesWritten);
                    }
                }
            }
        }

        newsrcStream->Close();

        rv = SetNewsrcHasChanged(PR_FALSE);
        if (NS_FAILED(rv)) return rv;
    }
#ifdef DEBUG_NEWS
    else {
        printf("no need to write newsrc file for %s, it was not dirty\n", (hostname.get()));
    }
#endif /* DEBUG_NEWS */

    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetNewsrcHasChanged(PRBool aNewsrcHasChanged)
{
    mNewsrcHasChanged = aNewsrcHasChanged;
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetNewsrcHasChanged(PRBool *aNewsrcHasChanged)
{
    if (!aNewsrcHasChanged) return NS_ERROR_NULL_POINTER;

    *aNewsrcHasChanged = mNewsrcHasChanged;
    return NS_OK;
}

NS_IMPL_GETSET(nsNntpIncomingServer, UserAuthenticated, PRBool, m_userAuthenticated)

NS_IMETHODIMP
nsNntpIncomingServer::CloseCachedConnections()
{
  nsresult rv;
  nsCOMPtr<nsINNTPProtocol> connection;

  // iterate through the connection cache and close the connections.
  PRInt32 cnt = mConnectionCache.Count();

  for (PRInt32 i = 0; i < cnt; ++i)
  {
    connection = mConnectionCache[0];
    if (connection)
    {
      rv = connection->CloseConnection();
      // We need to do this instead of RemoveObjectAt(0) because the
      // above call will likely cause the object to be removed from the
      // array anyway
      mConnectionCache.RemoveObject(connection);
    }
  }

  rv = WriteNewsrcFile();
  if (NS_FAILED(rv)) return rv;

  if (!mGetOnlyNew && !mHostInfoLoaded)
  {
    rv = WriteHostInfoFile();
    NS_ENSURE_SUCCESS(rv,rv);
  }

  return NS_OK;
}

NS_IMPL_SERVERPREF_INT(nsNntpIncomingServer, MaximumConnectionsNumber,
                       "max_cached_connections")

PRBool
nsNntpIncomingServer::ConnectionTimeOut(nsINNTPProtocol* aConnection)
{
    PRBool retVal = PR_FALSE;
    if (!aConnection) return retVal;
    nsresult rv;

    PRTime cacheTimeoutLimits;

    LL_I2L(cacheTimeoutLimits, 170 * 1000000); // 170 seconds in microseconds
    PRTime lastActiveTimeStamp;
    rv = aConnection->GetLastActiveTimeStamp(&lastActiveTimeStamp);

    PRTime elapsedTime;
    LL_SUB(elapsedTime, PR_Now(), lastActiveTimeStamp);
    PRTime t;
    LL_SUB(t, elapsedTime, cacheTimeoutLimits);
    if (LL_GE_ZERO(t))
    {
#ifdef DEBUG_seth
      printf("XXX connection timed out, close it, and remove it from the connection cache\n");
#endif
      aConnection->CloseConnection();
      mConnectionCache.RemoveObject(aConnection);
      retVal = PR_TRUE;
    }
    return retVal;
}


nsresult
nsNntpIncomingServer::CreateProtocolInstance(nsINNTPProtocol ** aNntpConnection, nsIURI *url,
                                             nsIMsgWindow *aMsgWindow)
{
  // create a new connection and add it to the connection cache
  // we may need to flag the protocol connection as busy so we don't get
  // a race
  // condition where someone else goes through this code
  nsNNTPProtocol * protocolInstance = new nsNNTPProtocol(url, aMsgWindow);
  if (!protocolInstance)
    return NS_ERROR_OUT_OF_MEMORY;

  nsresult rv = protocolInstance->QueryInterface(NS_GET_IID(nsINNTPProtocol), (void **) aNntpConnection);
  // take the protocol instance and add it to the connectionCache
  if (NS_SUCCEEDED(rv) && *aNntpConnection)
    mConnectionCache.AppendObject(*aNntpConnection);
  return rv;
}

/* By default, allow the user to open at most this many connections to one news host */
#define kMaxConnectionsPerHost 2

nsresult
nsNntpIncomingServer::GetNntpConnection(nsIURI * aUri, nsIMsgWindow *aMsgWindow,
                                        nsINNTPProtocol ** aNntpConnection)
{
  // Get our maximum connection count. We need at least 1. If the value is 0,
  // we use the default. If it's negative, we treat that as 1.
  PRInt32 maxConnections = kMaxConnectionsPerHost;
  nsresult rv = GetMaximumConnectionsNumber(&maxConnections);
  if (NS_FAILED(rv) || maxConnections == 0)
  {
    maxConnections = kMaxConnectionsPerHost;
    SetMaximumConnectionsNumber(maxConnections);
  }
  else if (maxConnections < 1)
  {
    maxConnections = 1;
    SetMaximumConnectionsNumber(maxConnections);
  }

  // Find a non-busy connection
  nsCOMPtr<nsINNTPProtocol> connection;
  PRInt32 cnt = mConnectionCache.Count();
  for (PRInt32 i = 0; i < cnt; i++)
  {
    connection = mConnectionCache[i];
    if (connection)
    {
      PRBool isBusy;
      connection->GetIsBusy(&isBusy);
      if (!isBusy)
        break;
      connection = nsnull;
    }
  }

  if (ConnectionTimeOut(connection))
  {
    connection = nsnull;
    // We have one less connection, since we closed this one.
    --cnt;
  }

  if (connection)
  {
    NS_IF_ADDREF(*aNntpConnection = connection);
    connection->SetIsCachedConnection(PR_TRUE);
  }
  else if (cnt < maxConnections)
  {
    // We have room for another connection. Create this connection and return
    // it to the caller.
    rv = CreateProtocolInstance(aNntpConnection, aUri, aMsgWindow);
    NS_ENSURE_SUCCESS(rv, rv);
  }
  else
  {
    // We maxed out our connection count. The caller must therefore enqueue the
    // call.
    *aNntpConnection = nsnull;
    return NS_OK;
  }

  // Initialize the URI here and now.
  return (*aNntpConnection)->Initialize(aUri, aMsgWindow);
}

NS_IMETHODIMP
nsNntpIncomingServer::GetNntpChannel(nsIURI *aURI, nsIMsgWindow *aMsgWindow,
                                     nsIChannel **aChannel)
{
  NS_ENSURE_ARG_POINTER(aChannel);

  nsCOMPtr<nsINNTPProtocol> protocol;
  nsresult rv = GetNntpConnection(aURI, aMsgWindow, getter_AddRefs(protocol));
  NS_ENSURE_SUCCESS(rv, rv);

  if (protocol)
    return CallQueryInterface(protocol, aChannel);

  // No protocol? We need our mock channel.
  nsNntpMockChannel *channel = new nsNntpMockChannel(aURI, aMsgWindow);
  if (!channel)
    return NS_ERROR_OUT_OF_MEMORY;
  NS_ADDREF(*aChannel = channel);

  m_queuedChannels.AppendElement(channel);
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::LoadNewsUrl(nsIURI *aURI, nsIMsgWindow *aMsgWindow,
                                  nsISupports *aConsumer)
{
  nsCOMPtr<nsINNTPProtocol> protocol;
  nsresult rv = GetNntpConnection(aURI, aMsgWindow, getter_AddRefs(protocol));
  NS_ENSURE_SUCCESS(rv, rv);

  if (protocol)
    return protocol->LoadNewsUrl(aURI, aConsumer);

  // No protocol? We need our mock channel.
  nsNntpMockChannel *channel = new nsNntpMockChannel(aURI, aMsgWindow,
                                                     aConsumer);
  if (!channel)
    return NS_ERROR_OUT_OF_MEMORY;

  m_queuedChannels.AppendElement(channel);
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::PrepareForNextUrl(nsNNTPProtocol *aConnection)
{
  NS_ENSURE_ARG(aConnection);

  // Start the connection on the next URL in the queue. If it can't get a URL to
  // work, drop that URL (the channel will handle failure notification) and move
  // on.
  while (m_queuedChannels.Length() > 0)
  {
    nsRefPtr<nsNntpMockChannel> channel = m_queuedChannels[0];
    m_queuedChannels.RemoveElementAt(0);
    nsresult rv = channel->AttachNNTPConnection(*aConnection);
    // If this succeeded, the connection is now running the URL.
    if (NS_SUCCEEDED(rv))
      return NS_OK;
  }
  
  // No queued uris.
  return NS_OK;
}

/* void RemoveConnection (in nsINNTPProtocol aNntpConnection); */
NS_IMETHODIMP nsNntpIncomingServer::RemoveConnection(nsINNTPProtocol *aNntpConnection)
{
  if (aNntpConnection)
    mConnectionCache.RemoveObject(aNntpConnection);

  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::PerformExpand(nsIMsgWindow *aMsgWindow)
{
  // Get news.update_unread_on_expand pref
  nsresult rv;
  PRBool updateUnreadOnExpand = PR_TRUE;
  nsCOMPtr<nsIPrefBranch> prefBranch = do_GetService(NS_PREFSERVICE_CONTRACTID, &rv);
  if (NS_SUCCEEDED(rv))
    prefBranch->GetBoolPref("news.update_unread_on_expand", &updateUnreadOnExpand);

  // Only if news.update_unread_on_expand is true do we update the unread counts
  if (updateUnreadOnExpand)
    return DownloadMail(aMsgWindow);
  return NS_OK;
}

nsresult
nsNntpIncomingServer::DownloadMail(nsIMsgWindow *aMsgWindow)
{
  nsCOMPtr<nsIMsgFolder> rootFolder;
  nsresult rv = GetRootFolder(getter_AddRefs(rootFolder));
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsISimpleEnumerator> groups;
  rv = rootFolder->GetSubFolders(getter_AddRefs(groups));
  NS_ENSURE_SUCCESS(rv, rv);

  PRBool hasNext;
  while (NS_SUCCEEDED(rv = groups->HasMoreElements(&hasNext)) && hasNext)
  {
    nsCOMPtr<nsISupports> nextGroup;
    rv = groups->GetNext(getter_AddRefs(nextGroup));
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsIMsgFolder> group(do_QueryInterface(nextGroup));
    rv = group->GetNewMessages(aMsgWindow, nsnull);
    NS_ENSURE_SUCCESS(rv, rv);
  }
  return rv;
}

NS_IMETHODIMP
nsNntpIncomingServer::DisplaySubscribedGroup(nsIMsgNewsFolder *aMsgFolder, PRInt32 aFirstMessage, PRInt32 aLastMessage, PRInt32 aTotalMessages)
{
  nsresult rv;

  if (!aMsgFolder) return NS_ERROR_NULL_POINTER;
#ifdef DEBUG_NEWS
  printf("DisplaySubscribedGroup(...,%ld,%ld,%ld)\n",aFirstMessage,aLastMessage,aTotalMessages);
#endif
  rv = aMsgFolder->UpdateSummaryFromNNTPInfo(aFirstMessage,aLastMessage,aTotalMessages);
  return rv;
}

NS_IMETHODIMP
nsNntpIncomingServer::PerformBiff(nsIMsgWindow *aMsgWindow)
{
  // Biff will force a download of the messages. If the user doesn't want this
  // (e.g., there is a lot of high-traffic newsgroups), the better option is to
  // just ignore biff.
  return PerformExpand(aMsgWindow);
}

NS_IMETHODIMP nsNntpIncomingServer::GetServerRequiresPasswordForBiff(PRBool *aServerRequiresPasswordForBiff)
{
  NS_ENSURE_ARG_POINTER(aServerRequiresPasswordForBiff);
  *aServerRequiresPasswordForBiff = PR_FALSE;  // for news, biff is getting the unread counts
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::OnStartRunningUrl(nsIURI *url)
{
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::OnStopRunningUrl(nsIURI *url, nsresult exitCode)
{
  nsresult rv;
  rv = UpdateSubscribed();
  if (NS_FAILED(rv)) return rv;

  rv = StopPopulating(mMsgWindow);
  if (NS_FAILED(rv)) return rv;

  return NS_OK;
}


PRBool
checkIfSubscribedFunction(nsCString &aElement, void *aData)
{
    if (aElement.Equals(*static_cast<nsACString *>(aData))) {
        return PR_FALSE;
    }
    else {
        return PR_TRUE;
    }
}


NS_IMETHODIMP
nsNntpIncomingServer::ContainsNewsgroup(const nsACString &name,
                                        PRBool *containsGroup)
{
    if (name.IsEmpty()) return NS_ERROR_FAILURE;
    nsCAutoString unescapedName;
    NS_UnescapeURL(nsCString(name),
                   esc_FileBaseName|esc_Forced|esc_AlwaysCopy, unescapedName);

    *containsGroup = !(mSubscribedNewsgroups.EnumerateForwards(
                       nsCStringArrayEnumFunc(checkIfSubscribedFunction),
                       (void *) &unescapedName));
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SubscribeToNewsgroup(const nsACString &aName)
{
    NS_ASSERTION(!aName.IsEmpty(), "no name");
    if (aName.IsEmpty()) return NS_ERROR_FAILURE;

    nsCOMPtr<nsIMsgFolder> msgfolder;
    nsresult rv = GetRootMsgFolder(getter_AddRefs(msgfolder));
    if (NS_FAILED(rv)) return rv;
    if (!msgfolder) return NS_ERROR_FAILURE;

    rv = msgfolder->CreateSubfolder(NS_ConvertUTF8toUTF16(aName), nsnull);
    if (NS_FAILED(rv)) return rv;

    return NS_OK;
}

PRBool
writeGroupToHostInfoFile(nsCString &aElement, void *aData)
{
    nsIOutputStream *stream;
    stream = (nsIOutputStream *)aData;
    NS_ASSERTION(stream, "no stream");
    if (!stream) {
        // stop, something is bad.
        return PR_FALSE;
    }
    PRUint32 bytesWritten;
    // XXX todo ",,1,0,0" is a temporary hack, fix it
    stream->Write(aElement.get(), aElement.Length(), &bytesWritten);
    stream->Write(",,1,0,0"MSG_LINEBREAK, 7 + MSG_LINEBREAK_LEN, &bytesWritten);
    return PR_TRUE;
}

void nsNntpIncomingServer::WriteLine(nsIOutputStream *stream, nsCString &str)
{
  PRUint32 bytesWritten;
  str.Append(MSG_LINEBREAK);
  stream->Write(str.get(), str.Length(), &bytesWritten);
}
nsresult
nsNntpIncomingServer::WriteHostInfoFile()
{
  if (!mHostInfoHasChanged)
    return NS_OK;
  PRInt32 firstnewdate;

  LL_L2I(firstnewdate, mFirstNewDate);

  mLastUpdatedTime = PRUint32(PR_Now() / PR_USEC_PER_SEC);

  nsCString hostname;
  nsresult rv = GetHostName(hostname);
  NS_ENSURE_SUCCESS(rv,rv);

  if (!mHostInfoFile)
    return NS_ERROR_UNEXPECTED;
  nsCOMPtr<nsIOutputStream> hostInfoStream;
  rv = NS_NewLocalFileOutputStream(getter_AddRefs(hostInfoStream), mHostInfoFile, -1, 00600);
  NS_ENSURE_SUCCESS(rv, rv);

  // todo, missing some formatting, see the 4.x code
  nsCAutoString header("# News host information file.");
  WriteLine(hostInfoStream, header);
  header.Assign("# This is a generated file!  Do not edit.");
  WriteLine(hostInfoStream, header);
  header.Truncate();
  WriteLine(hostInfoStream, header);
  nsCAutoString version("version=");
  version.AppendInt(VALID_VERSION);
  WriteLine(hostInfoStream, version);
  nsCAutoString newsrcname("newsrcname=");
  newsrcname.Append(hostname);
  WriteLine(hostInfoStream, hostname);
  nsCAutoString dateStr("lastgroupdate=");
  dateStr.AppendInt(mLastUpdatedTime);
  WriteLine(hostInfoStream, dateStr);
  dateStr ="firstnewdate=";
  dateStr.AppendInt(firstnewdate);
  WriteLine(hostInfoStream, dateStr);
  dateStr = "uniqueid=";
  dateStr.AppendInt(mUniqueId);
  WriteLine(hostInfoStream, dateStr);
  header.Assign(MSG_LINEBREAK"begingroups");
  WriteLine(hostInfoStream, header);

  // XXX todo, sort groups first?

  mGroupsOnServer.EnumerateForwards((nsCStringArrayEnumFunc)writeGroupToHostInfoFile, (void *)hostInfoStream);

  hostInfoStream->Close();
  mHostInfoHasChanged = PR_FALSE;
  return NS_OK;
}

nsresult
nsNntpIncomingServer::LoadHostInfoFile()
{
  nsresult rv;
  // we haven't loaded it yet
  mHostInfoLoaded = PR_FALSE;

  rv = GetLocalPath(getter_AddRefs(mHostInfoFile));
  if (NS_FAILED(rv)) return rv;
  if (!mHostInfoFile) return NS_ERROR_FAILURE;

  rv = mHostInfoFile->AppendNative(NS_LITERAL_CSTRING(HOSTINFO_FILE_NAME));
  if (NS_FAILED(rv)) return rv;

  PRBool exists;
  rv = mHostInfoFile->Exists(&exists);
  if (NS_FAILED(rv)) return rv;

  // it is ok if the hostinfo.dat file does not exist.
  if (!exists) return NS_OK;

  nsCOMPtr<nsIInputStream> fileStream;
  rv = NS_NewLocalFileInputStream(getter_AddRefs(fileStream), mHostInfoFile);
  NS_ENSURE_SUCCESS(rv, nsnull);

  nsCOMPtr<nsILineInputStream> lineInputStream(do_QueryInterface(fileStream, &rv));
  NS_ENSURE_SUCCESS(rv, nsnull);

  PRBool more = PR_TRUE;
  nsCString line;

  while (more && NS_SUCCEEDED(rv))
  {
    lineInputStream->ReadLine(line, &more);
    if (line.IsEmpty())
      continue;
    HandleLine(line.get(), line.Length());
  }
  mHasSeenBeginGroups = PR_FALSE;
  fileStream->Close();

  return UpdateSubscribed();
}

NS_IMETHODIMP
nsNntpIncomingServer::StartPopulatingWithUri(nsIMsgWindow *aMsgWindow, PRBool aForceToServer, const char *uri)
{
  nsresult rv = NS_OK;

#ifdef DEBUG_seth
  printf("StartPopulatingWithUri(%s)\n",uri);
#endif

    rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
    rv = mInner->StartPopulatingWithUri(aMsgWindow, aForceToServer, uri);
    NS_ENSURE_SUCCESS(rv,rv);

  rv = StopPopulating(mMsgWindow);
  if (NS_FAILED(rv)) return rv;

  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SubscribeCleanup()
{
  nsresult rv = NS_OK;
    rv = ClearInner();
    NS_ENSURE_SUCCESS(rv,rv);
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::StartPopulating(nsIMsgWindow *aMsgWindow, PRBool aForceToServer, PRBool aGetOnlyNew)
{
  nsresult rv;

  mMsgWindow = aMsgWindow;

  rv = EnsureInner();
  NS_ENSURE_SUCCESS(rv,rv);

  rv = mInner->StartPopulating(aMsgWindow, aForceToServer, aGetOnlyNew);
  NS_ENSURE_SUCCESS(rv,rv);

  rv = SetDelimiter(NEWS_DELIMITER);
  if (NS_FAILED(rv)) return rv;

  rv = SetShowFullName(PR_TRUE);
  if (NS_FAILED(rv)) return rv;

  nsCOMPtr<nsINntpService> nntpService = do_GetService(NS_NNTPSERVICE_CONTRACTID, &rv);
  NS_ENSURE_SUCCESS(rv,rv);

  mHostInfoLoaded = PR_FALSE;
  mVersion = INVALID_VERSION;
  mGroupsOnServer.Clear();
  mGetOnlyNew = aGetOnlyNew;

  if (!aForceToServer) {
  rv = LoadHostInfoFile();
    if (NS_FAILED(rv)) return rv;
  }

  // mHostInfoLoaded can be false if we failed to load anything
  if (aForceToServer || !mHostInfoLoaded || (mVersion != VALID_VERSION)) {
    // set these to true, so when we are done and we call WriteHostInfoFile()
    // we'll write out to hostinfo.dat
  mHostInfoHasChanged = PR_TRUE;
  mVersion = VALID_VERSION;

  mGroupsOnServer.Clear();
  rv = nntpService->GetListOfGroupsOnServer(this, aMsgWindow, aGetOnlyNew);
  if (NS_FAILED(rv)) return rv;
  }
  else {
  rv = StopPopulating(aMsgWindow);
  if (NS_FAILED(rv)) return rv;
  }

  return NS_OK;
}

/**
 * This method is the entry point for |nsNNTPProtocol| class. |aName| is now
 * encoded in the serverside character encoding, but we need to handle
 * newsgroup names in UTF-8 internally, So we convert |aName| to
 * UTF-8 here for later use.
 **/
NS_IMETHODIMP
nsNntpIncomingServer::AddNewsgroupToList(const char *aName)
{
    nsresult rv;

    nsAutoString newsgroupName;
    nsCAutoString dataCharset;
    rv = GetCharset(dataCharset);
    NS_ENSURE_SUCCESS(rv,rv);

    rv = nsMsgI18NConvertToUnicode(dataCharset.get(),
                                   nsDependentCString(aName),
                                   newsgroupName);
#ifdef DEBUG_jungshik
    NS_ASSERTION(NS_SUCCEEDED(rv), "newsgroup name conversion failed");
#endif
    if (NS_FAILED(rv)) {
        CopyASCIItoUTF16(aName, newsgroupName);
    }

    rv = AddTo(NS_ConvertUTF16toUTF8(newsgroupName),
               PR_FALSE, PR_TRUE, PR_TRUE);
    if (NS_FAILED(rv)) return rv;
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetIncomingServer(nsIMsgIncomingServer *aServer)
{
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
  return mInner->SetIncomingServer(aServer);
}

NS_IMETHODIMP
nsNntpIncomingServer::SetShowFullName(PRBool showFullName)
{
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
  return mInner->SetShowFullName(showFullName);
}

nsresult
nsNntpIncomingServer::ClearInner()
{
    nsresult rv = NS_OK;

    if (mInner) {
        rv = mInner->SetSubscribeListener(nsnull);
        NS_ENSURE_SUCCESS(rv,rv);

        rv = mInner->SetIncomingServer(nsnull);
        NS_ENSURE_SUCCESS(rv,rv);

        mInner = nsnull;
    }
    return NS_OK;
}

nsresult
nsNntpIncomingServer::EnsureInner()
{
    nsresult rv = NS_OK;

    if (mInner) return NS_OK;

    mInner = do_CreateInstance(kSubscribableServerCID,&rv);
    NS_ENSURE_SUCCESS(rv,rv);
    if (!mInner) return NS_ERROR_FAILURE;

    rv = SetIncomingServer(this);
    NS_ENSURE_SUCCESS(rv,rv);

    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetDelimiter(char *aDelimiter)
{
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
    return mInner->GetDelimiter(aDelimiter);
}

NS_IMETHODIMP
nsNntpIncomingServer::SetDelimiter(char aDelimiter)
{
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
    return mInner->SetDelimiter(aDelimiter);
}

NS_IMETHODIMP
nsNntpIncomingServer::SetAsSubscribed(const nsACString &path)
{
    mTempSubscribed.AppendCString(path);
    if (mGetOnlyNew && (mGroupsOnServer.IndexOf(path) == -1))
      return NS_OK;

    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
    return mInner->SetAsSubscribed(path);
}

PRBool
setAsSubscribedFunction(nsCString &aElement, void *aData)
{
    nsresult rv = NS_OK;
    nsNntpIncomingServer *server;
    server = (nsNntpIncomingServer *)aData;
    NS_ASSERTION(server, "no server");
    if (!server) {
        return PR_FALSE;
    }

    rv = server->SetAsSubscribed(aElement);
    NS_ASSERTION(NS_SUCCEEDED(rv),"SetAsSubscribed failed");
    return PR_TRUE;
}

NS_IMETHODIMP
nsNntpIncomingServer::UpdateSubscribed()
{
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
  mTempSubscribed.Clear();
  mSubscribedNewsgroups.EnumerateForwards((nsCStringArrayEnumFunc)setAsSubscribedFunction, (void *)this);
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::AddTo(const nsACString &aName, PRBool addAsSubscribed,
                            PRBool aSubscribable, PRBool changeIfExists)
{
    NS_ASSERTION(IsUTF8(aName), "Non-UTF-8 newsgroup name");
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);

    rv = AddGroupOnServer(aName);
    NS_ENSURE_SUCCESS(rv,rv);

    rv = mInner->AddTo(aName, addAsSubscribed, aSubscribable, changeIfExists);
    NS_ENSURE_SUCCESS(rv,rv);

    return rv;
}

NS_IMETHODIMP
nsNntpIncomingServer::StopPopulating(nsIMsgWindow *aMsgWindow)
{
  nsresult rv = NS_OK;

  nsCOMPtr<nsISubscribeListener> listener;
  rv = GetSubscribeListener(getter_AddRefs(listener));
  NS_ENSURE_SUCCESS(rv,rv);

  if (!listener)
    return NS_ERROR_FAILURE;

  rv = listener->OnDonePopulating();
  NS_ENSURE_SUCCESS(rv,rv);

  rv = EnsureInner();
  NS_ENSURE_SUCCESS(rv,rv);
  rv = mInner->StopPopulating(aMsgWindow);
  NS_ENSURE_SUCCESS(rv,rv);

  if (!mGetOnlyNew && !mHostInfoLoaded)
  {
    rv = WriteHostInfoFile();
    NS_ENSURE_SUCCESS(rv,rv);
  }

  //xxx todo when do I set this to null?
  //rv = ClearInner();
  //NS_ENSURE_SUCCESS(rv,rv);
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetSubscribeListener(nsISubscribeListener *aListener)
{
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
  return mInner->SetSubscribeListener(aListener);
}

NS_IMETHODIMP
nsNntpIncomingServer::GetSubscribeListener(nsISubscribeListener **aListener)
{
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
    return mInner->GetSubscribeListener(aListener);
}

NS_IMETHODIMP
nsNntpIncomingServer::Subscribe(const PRUnichar *aUnicharName)
{
  return SubscribeToNewsgroup(NS_ConvertUTF16toUTF8(aUnicharName));
}

NS_IMETHODIMP
nsNntpIncomingServer::Unsubscribe(const PRUnichar *aUnicharName)
{
  NS_ENSURE_ARG_POINTER(aUnicharName);

  nsresult rv;

  nsCOMPtr <nsIMsgFolder> serverFolder;
  rv = GetRootMsgFolder(getter_AddRefs(serverFolder));
  if (NS_FAILED(rv))
    return rv;

  if (!serverFolder)
    return NS_ERROR_FAILURE;

  // to handle non-ASCII newsgroup names, we store them internally as escaped.
  // so we need to escape and encode the name, in order to find it.
  nsCAutoString escapedName;
  rv = NS_MsgEscapeEncodeURLPath(nsDependentString(aUnicharName), escapedName);

  nsCOMPtr <nsIMsgFolder> newsgroupFolder;
  rv = serverFolder->FindSubFolder(escapedName,
                                   getter_AddRefs(newsgroupFolder));

  if (NS_FAILED(rv))
    return rv;

  if (!newsgroupFolder)
    return NS_ERROR_FAILURE;

  rv = serverFolder->PropagateDelete(newsgroupFolder, PR_TRUE /* delete storage */, nsnull);
  if (NS_FAILED(rv))
    return rv;

  // since we've unsubscribed to a newsgroup, the newsrc needs to be written out
  rv = SetNewsrcHasChanged(PR_TRUE);
  if (NS_FAILED(rv))
    return rv;

  return NS_OK;
}

PRInt32
nsNntpIncomingServer::HandleLine(const char* line, PRUint32 line_size)
{
  NS_ASSERTION(line, "line is null");
  if (!line) return 0;

  // skip blank lines and comments
  if (line[0] == '#' || line[0] == '\0') return 0;
  // ###TODO - make this truly const, maybe pass in an nsCString &

  if (mHasSeenBeginGroups) {
    char *commaPos = (char *) PL_strchr(line,',');
    if (commaPos) *commaPos = 0;

        // newsrc entries are all in UTF-8
#ifdef DEBUG_jungshik
    NS_ASSERTION(IsUTF8(nsDependentCString(line)), "newsrc line is not utf-8");
#endif
    nsresult rv = AddTo(nsDependentCString(line), PR_FALSE, PR_TRUE, PR_TRUE);
    NS_ASSERTION(NS_SUCCEEDED(rv),"failed to add line");
    if (NS_SUCCEEDED(rv)) {
      // since we've seen one group, we can claim we've loaded the
      // hostinfo file
      mHostInfoLoaded = PR_TRUE;
    }
  }
  else {
    if (PL_strncmp(line,"begingroups", 11) == 0) {
      mHasSeenBeginGroups = PR_TRUE;
    }
    char*equalPos = (char *) PL_strchr(line, '=');
    if (equalPos) {
      *equalPos++ = '\0';
      if (PL_strcmp(line, "lastgroupdate") == 0) {
        mLastUpdatedTime = strtoul(equalPos, nsnull, 10);
      } else if (PL_strcmp(line, "firstnewdate") == 0) {
        PRInt32 firstnewdate = strtol(equalPos, nsnull, 16);
        LL_I2L(mFirstNewDate, firstnewdate);
      } else if (PL_strcmp(line, "uniqueid") == 0) {
        mUniqueId = strtol(equalPos, nsnull, 16);
      } else if (PL_strcmp(line, "version") == 0) {
        mVersion = strtol(equalPos, nsnull, 16);
      }
    }
  }

  return 0;
}

nsresult
nsNntpIncomingServer::AddGroupOnServer(const nsACString &aName)
{
  mGroupsOnServer.AppendCString(aName);
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::AddNewsgroup(const nsAString &aName)
{
    // handle duplicates?
    mSubscribedNewsgroups.AppendCString(NS_ConvertUTF16toUTF8(aName));
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::RemoveNewsgroup(const nsAString &aName)
{
    // handle duplicates?
    mSubscribedNewsgroups.RemoveCString(NS_ConvertUTF16toUTF8(aName));
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetState(const nsACString &path, PRBool state,
                               PRBool *stateChanged)
{
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);

    rv = mInner->SetState(path, state, stateChanged);
    if (*stateChanged) {
      if (state)
        mTempSubscribed.AppendCString(path);
      else
        mTempSubscribed.RemoveCString(path);
    }
    return rv;
}

NS_IMETHODIMP
nsNntpIncomingServer::HasChildren(const nsACString &path, PRBool *aHasChildren)
{
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
    return mInner->HasChildren(path, aHasChildren);
}

NS_IMETHODIMP
nsNntpIncomingServer::IsSubscribed(const nsACString &path,
                                   PRBool *aIsSubscribed)
{
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
    return mInner->IsSubscribed(path, aIsSubscribed);
}

NS_IMETHODIMP
nsNntpIncomingServer::IsSubscribable(const nsACString &path,
                                     PRBool *aIsSubscribable)
{
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
    return mInner->IsSubscribable(path, aIsSubscribable);
}

NS_IMETHODIMP
nsNntpIncomingServer::GetLeafName(const nsACString &path, nsAString &aLeafName)
{
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
    return mInner->GetLeafName(path, aLeafName);
}

NS_IMETHODIMP
nsNntpIncomingServer::GetFirstChildURI(const nsACString &path, nsACString &aResult)
{
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
    return mInner->GetFirstChildURI(path, aResult);
}

NS_IMETHODIMP
nsNntpIncomingServer::GetChildren(const nsACString &aPath,
                                  nsISimpleEnumerator **aResult)
{
    nsresult rv = EnsureInner();
    NS_ENSURE_SUCCESS(rv,rv);
    return mInner->GetChildren(aPath, aResult);
}

NS_IMETHODIMP
nsNntpIncomingServer::CommitSubscribeChanges()
{
    nsresult rv;

    // we force the newrc to be dirty, so it will get written out when
    // we call WriteNewsrcFile()
    rv = SetNewsrcHasChanged(PR_TRUE);
    NS_ENSURE_SUCCESS(rv,rv);
    return WriteNewsrcFile();
}

NS_IMETHODIMP
nsNntpIncomingServer::ForgetPassword()
{
    nsresult rv;

    // clear password of root folder (for the news account)
    nsCOMPtr<nsIMsgFolder> rootFolder;
    rv = GetRootFolder(getter_AddRefs(rootFolder));
    NS_ENSURE_SUCCESS(rv,rv);
    if (!rootFolder) return NS_ERROR_FAILURE;

    nsCOMPtr <nsIMsgNewsFolder> newsFolder = do_QueryInterface(rootFolder, &rv);
    NS_ENSURE_SUCCESS(rv,rv);
    if (!newsFolder) return NS_ERROR_FAILURE;

    rv = newsFolder->ForgetGroupUsername();
    NS_ENSURE_SUCCESS(rv,rv);
    rv = newsFolder->ForgetGroupPassword();
    NS_ENSURE_SUCCESS(rv,rv);

    // clear password of all child folders
    nsCOMPtr<nsISimpleEnumerator> subFolders;

    rv = rootFolder->GetSubFolders(getter_AddRefs(subFolders));
    NS_ENSURE_SUCCESS(rv,rv);

    PRBool moreFolders = PR_FALSE;

    nsresult return_rv = NS_OK;

    while (NS_SUCCEEDED(subFolders->HasMoreElements(&moreFolders)) &&
           moreFolders) {
        nsCOMPtr<nsISupports> child;
        rv = subFolders->GetNext(getter_AddRefs(child));
        if (NS_SUCCEEDED(rv) && child) {
            newsFolder = do_QueryInterface(child, &rv);
            if (NS_SUCCEEDED(rv) && newsFolder) {
                rv = newsFolder->ForgetGroupUsername();
                if (NS_FAILED(rv)) return_rv = rv;
                rv = newsFolder->ForgetGroupPassword();
                if (NS_FAILED(rv)) return_rv = rv;
            }
            else {
                return_rv = NS_ERROR_FAILURE;
            }
        }
    }

    return return_rv;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetSupportsExtensions(PRBool *aSupportsExtensions)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetSupportsExtensions(PRBool aSupportsExtensions)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::AddExtension(const char *extension)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::QueryExtension(const char *extension, PRBool *result)
{
#ifdef DEBUG_seth
  printf("no extension support yet\n");
#endif
  *result = PR_FALSE;
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetPostingAllowed(PRBool *aPostingAllowed)
{
  *aPostingAllowed = mPostingAllowed;
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetPostingAllowed(PRBool aPostingAllowed)
{
  mPostingAllowed = aPostingAllowed;
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetLastUpdatedTime(PRUint32 *aLastUpdatedTime)
{
  *aLastUpdatedTime = mLastUpdatedTime;
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetLastUpdatedTime(PRUint32 aLastUpdatedTime)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::AddPropertyForGet(const char *name, const char *value)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::QueryPropertyForGet(const char *name, char **value)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::AddSearchableGroup(const nsAString &name)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::QuerySearchableGroup(const nsAString &name, PRBool *result)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::AddSearchableHeader(const char *name)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::QuerySearchableHeader(const char *name, PRBool *result)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::FindGroup(const nsACString &name, nsIMsgNewsFolder **result)
{
  NS_ENSURE_ARG_POINTER(result);

  nsresult rv;
  nsCOMPtr <nsIMsgFolder> serverFolder;
  rv = GetRootMsgFolder(getter_AddRefs(serverFolder));
  NS_ENSURE_SUCCESS(rv,rv);

  if (!serverFolder) return NS_ERROR_FAILURE;

  nsCOMPtr <nsIMsgFolder> subFolder;
  rv = serverFolder->FindSubFolder(name, getter_AddRefs(subFolder));
  NS_ENSURE_SUCCESS(rv,rv);
  if (!subFolder) return NS_ERROR_FAILURE;

  rv = subFolder->QueryInterface(NS_GET_IID(nsIMsgNewsFolder), (void**)result);
  NS_ENSURE_SUCCESS(rv,rv);
  if (!*result) return NS_ERROR_FAILURE;
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetFirstGroupNeedingExtraInfo(nsACString &result)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetGroupNeedsExtraInfo(const nsACString &name,
                                             PRBool needsExtraInfo)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}


NS_IMETHODIMP
nsNntpIncomingServer::GroupNotFound(nsIMsgWindow *aMsgWindow,
                                    const nsAString &aName, PRBool aOpening)
{
  nsresult rv;
  nsCOMPtr <nsIPrompt> prompt;

  if (aMsgWindow) {
    rv = aMsgWindow->GetPromptDialog(getter_AddRefs(prompt));
    NS_ASSERTION(NS_SUCCEEDED(rv), "no prompt from the msg window");
  }

  if (!prompt) {
    nsCOMPtr<nsIWindowWatcher> wwatch(do_GetService(NS_WINDOWWATCHER_CONTRACTID));
    rv = wwatch->GetNewPrompter(nsnull, getter_AddRefs(prompt));
    NS_ENSURE_SUCCESS(rv,rv);
  }

  nsCOMPtr <nsIStringBundleService> bundleService = do_GetService(NS_STRINGBUNDLE_CONTRACTID,&rv);
  NS_ENSURE_SUCCESS(rv,rv);

  nsCOMPtr <nsIStringBundle> bundle;
  rv = bundleService->CreateBundle(NEWS_MSGS_URL, getter_AddRefs(bundle));
  NS_ENSURE_SUCCESS(rv,rv);

  nsCString hostname;
  rv = GetHostName(hostname);
  NS_ENSURE_SUCCESS(rv,rv);

  NS_ConvertUTF8toUTF16 hostStr(hostname);

  nsString groupName(aName);
  const PRUnichar *formatStrings[2] = { groupName.get(), hostStr.get() };
  nsString confirmText;
  rv = bundle->FormatStringFromName(
                    NS_LITERAL_STRING("autoUnsubscribeText").get(),
                    formatStrings, 2,
                    getter_Copies(confirmText));
  NS_ENSURE_SUCCESS(rv,rv);

  PRBool confirmResult = PR_FALSE;
  rv = prompt->Confirm(nsnull, confirmText.get(), &confirmResult);
  NS_ENSURE_SUCCESS(rv,rv);

  if (confirmResult) {
    rv = Unsubscribe(groupName.get());
    NS_ENSURE_SUCCESS(rv,rv);
  }

  return rv;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetPrettyNameForGroup(const nsAString &name,
                                            const nsAString &prettyName)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetCanSearchMessages(PRBool *canSearchMessages)
{
    NS_ENSURE_ARG_POINTER(canSearchMessages);
    *canSearchMessages = PR_TRUE;
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetOfflineSupportLevel(PRInt32 *aSupportLevel)
{
    NS_ENSURE_ARG_POINTER(aSupportLevel);
    nsresult rv;

    rv = GetIntValue("offline_support_level", aSupportLevel);
    if (*aSupportLevel != OFFLINE_SUPPORT_LEVEL_UNDEFINED) return rv;

    // set default value
    *aSupportLevel = OFFLINE_SUPPORT_LEVEL_EXTENDED;
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetDefaultCopiesAndFoldersPrefsToServer(PRBool *aCopiesAndFoldersOnServer)
{
    NS_ENSURE_ARG_POINTER(aCopiesAndFoldersOnServer);

    /**
     * When a news account is created, the copies and folder prefs for the
     * associated identity don't point to folders on the server.
     * This makes sense, since there is no "Drafts" folder on a news server.
     * They'll point to the ones on "Local Folders"
     */

    *aCopiesAndFoldersOnServer = PR_FALSE;
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetCanCreateFoldersOnServer(PRBool *aCanCreateFoldersOnServer)
{
    NS_ENSURE_ARG_POINTER(aCanCreateFoldersOnServer);

    // No folder creation on news servers. Return false.
    *aCanCreateFoldersOnServer = PR_FALSE;
    return NS_OK;
}

PRBool
buildSubscribeSearchResult(nsCString &aElement, void *aData)
{
    nsresult rv = NS_OK;
    nsNntpIncomingServer *server;
    server = (nsNntpIncomingServer *)aData;
    NS_ASSERTION(server, "no server");
    if (!server) {
        return PR_FALSE;
    }

    rv = server->AppendIfSearchMatch(aElement);
    NS_ASSERTION(NS_SUCCEEDED(rv),"AddSubscribeSearchResult failed");
    return PR_TRUE;
}

nsresult
nsNntpIncomingServer::AppendIfSearchMatch(nsCString& newsgroupName)
{
  NS_ConvertUTF8toUTF16 groupName(newsgroupName);
  // When we move to frozen linkage this should be:
  //   if (groupName.Find(mSearchValue, CaseInsensitiveCompare) >= 0)
  nsAString::const_iterator start, end;
  groupName.BeginReading(start);
  groupName.EndReading(end);
  if (FindInReadable(mSearchValue, start, end,
                     nsCaseInsensitiveStringComparator()))
      mSubscribeSearchResult.AppendCString(newsgroupName);
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetSearchValue(const nsAString &searchValue)
{
    mSearchValue = searchValue;

    if (mTree) {
        mTree->BeginUpdateBatch();
        mTree->RowCountChanged(0, -mSubscribeSearchResult.Count());
    }

    mSubscribeSearchResult.Clear();
    mGroupsOnServer.
        EnumerateForwards(nsCStringArrayEnumFunc(buildSubscribeSearchResult),
                          (void *)this);
    mSubscribeSearchResult.SortIgnoreCase();

    if (mTree) {
        mTree->RowCountChanged(0, mSubscribeSearchResult.Count());
        mTree->EndUpdateBatch();
    }
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetSupportsSubscribeSearch(PRBool *retVal)
{
    *retVal = PR_TRUE;
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetRowCount(PRInt32 *aRowCount)
{
    *aRowCount = mSubscribeSearchResult.Count();
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetSelection(nsITreeSelection * *aSelection)
{
  *aSelection = mTreeSelection;
  NS_IF_ADDREF(*aSelection);
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetSelection(nsITreeSelection * aSelection)
{
  mTreeSelection = aSelection;
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetRowProperties(PRInt32 index, nsISupportsArray *properties)
{
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetCellProperties(PRInt32 row, nsITreeColumn* col, nsISupportsArray *properties)
{
    if (!IsValidRow(row))
      return NS_ERROR_UNEXPECTED;

    NS_ENSURE_ARG_POINTER(col);
    NS_ENSURE_ARG_POINTER(properties);

    const PRUnichar* colID;
    col->GetIdConst(&colID);
    if (colID[0] == 's') {
        // if <name> is in our temporary list of subscribed groups
        // add the "subscribed" property so the check mark shows up
        // in the "subscribedCol"
        nsCString name;
        if (mSearchResultSortDescending)
          row = mSubscribeSearchResult.Count() + ~row;
        mSubscribeSearchResult.CStringAt(row, name);
        if (mTempSubscribed.IndexOf(name) != -1) {
          properties->AppendElement(mSubscribedAtom);
        }
    }
    else if (colID[0] == 'n') {
      // add the "nntp" property to the "nameCol"
      // so we get the news folder icon in the search view
      properties->AppendElement(mNntpAtom);
    }
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetColumnProperties(nsITreeColumn* col, nsISupportsArray *properties)
{
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::IsContainer(PRInt32 index, PRBool *_retval)
{
    *_retval = PR_FALSE;
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::IsContainerOpen(PRInt32 index, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::IsContainerEmpty(PRInt32 index, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::IsSeparator(PRInt32 index, PRBool *_retval)
{
    *_retval = PR_FALSE;
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::IsSorted(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
#ifdef MOZILLA_1_9_1_BRANCH
nsNntpIncomingServer::CanDrop(PRInt32 index, PRInt32 orientation, PRBool *_retval)
#else
nsNntpIncomingServer::CanDrop(PRInt32 index,
                              PRInt32 orientation,
                              nsIDOMDataTransfer *dataTransfer,
                              PRBool *_retval)
#endif
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
#ifdef MOZILLA_1_9_1_BRANCH
nsNntpIncomingServer::Drop(PRInt32 row, PRInt32 orientation)
#else
nsNntpIncomingServer::Drop(PRInt32 row,
                           PRInt32 orientation,
                           nsIDOMDataTransfer *dataTransfer)
#endif
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetParentIndex(PRInt32 rowIndex, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::HasNextSibling(PRInt32 rowIndex, PRInt32 afterIndex, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetLevel(PRInt32 index, PRInt32 *_retval)
{
    *_retval = 0;
    return NS_OK;
}

nsresult
nsNntpIncomingServer::IsValidRow(PRInt32 row)
{
    return ((row >= 0) && (row < mSubscribeSearchResult.Count()));
}

NS_IMETHODIMP
nsNntpIncomingServer::GetImageSrc(PRInt32 row, nsITreeColumn* col, nsAString& _retval)
{
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetProgressMode(PRInt32 row, nsITreeColumn* col, PRInt32* _retval)
{
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetCellValue(PRInt32 row, nsITreeColumn* col, nsAString& _retval)
{
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetCellText(PRInt32 row, nsITreeColumn* col, nsAString& _retval)
{
    if (!IsValidRow(row))
      return NS_ERROR_UNEXPECTED;

    NS_ENSURE_ARG_POINTER(col);

    const PRUnichar* colID;
    col->GetIdConst(&colID);

    nsresult rv = NS_OK;
    if (colID[0] == 'n') {
      nsCAutoString str;
      if (mSearchResultSortDescending)
        row = mSubscribeSearchResult.Count() + ~row;
      mSubscribeSearchResult.CStringAt(row, str);
      // some servers have newsgroup names that are non ASCII.  we store
      // those as escaped. unescape here so the UI is consistent
      rv = NS_MsgDecodeUnescapeURLPath(str, _retval);
    }
    return rv;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetTree(nsITreeBoxObject *tree)
{
  mTree = tree;
  if (!tree)
      return NS_OK;

  nsCOMPtr<nsITreeColumns> cols;
  tree->GetColumns(getter_AddRefs(cols));
  if (!cols)
      return NS_OK;

  nsCOMPtr<nsITreeColumn> col;
  cols->GetKeyColumn(getter_AddRefs(col));
  if (!col)
      return NS_OK;

  nsCOMPtr<nsIDOMElement> element;
  col->GetElement(getter_AddRefs(element));
  if (!element)
      return NS_OK;

  nsAutoString dir;
  element->GetAttribute(NS_LITERAL_STRING("sortDirection"), dir);
  mSearchResultSortDescending = dir.EqualsLiteral("descending");
  return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::ToggleOpenState(PRInt32 index)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::CycleHeader(nsITreeColumn* col)
{
    NS_ENSURE_ARG_POINTER(col);

    PRBool cycler;
    col->GetCycler(&cycler);
    if (!cycler) {
        NS_NAMED_LITERAL_STRING(dir, "sortDirection");
        nsCOMPtr<nsIDOMElement> element;
        col->GetElement(getter_AddRefs(element));
        mSearchResultSortDescending = !mSearchResultSortDescending;
        element->SetAttribute(dir, mSearchResultSortDescending ?
            NS_LITERAL_STRING("descending") : NS_LITERAL_STRING("ascending"));
        mTree->Invalidate();
    }
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SelectionChanged()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::CycleCell(PRInt32 row, nsITreeColumn* col)
{
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::IsEditable(PRInt32 row, nsITreeColumn* col, PRBool *_retval)
{
    *_retval = PR_FALSE;
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::IsSelectable(PRInt32 row, nsITreeColumn* col, PRBool *_retval)
{
    *_retval = PR_FALSE;
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetCellValue(PRInt32 row, nsITreeColumn* col, const nsAString& value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetCellText(PRInt32 row, nsITreeColumn* col, const nsAString& value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::PerformAction(const PRUnichar *action)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::PerformActionOnRow(const PRUnichar *action, PRInt32 row)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::PerformActionOnCell(const PRUnichar *action, PRInt32 row, nsITreeColumn* col)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetCanFileMessagesOnServer(PRBool *aCanFileMessagesOnServer)
{
    NS_ENSURE_ARG_POINTER(aCanFileMessagesOnServer);

    // No folder creation on news servers. Return false.
    *aCanFileMessagesOnServer = PR_FALSE;
    return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetFilterScope(nsMsgSearchScopeValue *filterScope)
{
   NS_ENSURE_ARG_POINTER(filterScope);

   *filterScope = nsMsgSearchScope::newsFilter;
   return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetSearchScope(nsMsgSearchScopeValue *searchScope)
{
   NS_ENSURE_ARG_POINTER(searchScope);

   if (WeAreOffline()) {
     // This value is set to the localNewsBody scope to be compatible with
     // the legacy default value.
     *searchScope = nsMsgSearchScope::localNewsBody;
   }
   else {
     *searchScope = nsMsgSearchScope::news;
   }
   return NS_OK;
}

NS_IMETHODIMP
nsNntpIncomingServer::GetSocketType(PRInt32 *aSocketType)
{
  NS_ENSURE_ARG_POINTER(aSocketType);
  if (!mPrefBranch)
    return NS_ERROR_NOT_INITIALIZED;

  nsresult rv = mPrefBranch->GetIntPref("socketType", aSocketType);
  if (NS_FAILED(rv))
  {
    if (!mDefPrefBranch)
      return NS_ERROR_NOT_INITIALIZED;
    rv = mDefPrefBranch->GetIntPref("socketType", aSocketType);
    if (NS_FAILED(rv))
      *aSocketType = nsIMsgIncomingServer::defaultSocket;
  }

  // nsMsgIncomingServer::GetSocketType migrates old isSecure to socketType
  // style for mail. Unfortunately, a bug caused news socketType 0 to be stored
  // in the prefs even for isSecure true, so the migration wouldn't happen :(

  // Now that we know the socket, make sure isSecure true + socketType 0
  // doesn't mix. Migrate if that's the case here.
  if (*aSocketType == nsIMsgIncomingServer::defaultSocket)
  {
    PRBool isSecure = PR_FALSE;
    nsresult rv2 = mPrefBranch->GetBoolPref("isSecure", &isSecure);
    if (NS_SUCCEEDED(rv2) && isSecure)
    {
      *aSocketType = nsIMsgIncomingServer::useSSL;
      // Don't call virtual method in case overrides call GetSocketType.
      nsMsgIncomingServer::SetSocketType(*aSocketType);
    }
  }
  return rv;
}

NS_IMETHODIMP
nsNntpIncomingServer::SetSocketType(PRInt32 aSocketType)
{
  if (!mPrefBranch)
    return NS_ERROR_NOT_INITIALIZED;
  nsresult rv = nsMsgIncomingServer::SetSocketType(aSocketType);
  if (NS_SUCCEEDED(rv))
  {
    PRBool isSecure = PR_FALSE;
    if (NS_SUCCEEDED(mPrefBranch->GetBoolPref("isSecure", &isSecure)))
    {
      // Must keep isSecure in sync since we migrate based on it... if it's set.
      rv = mPrefBranch->SetBoolPref("isSecure",
                                    aSocketType == nsIMsgIncomingServer::useSSL);
      NS_ENSURE_SUCCESS(rv, rv);
    }
  }
  return rv;
}

NS_IMETHODIMP
nsNntpIncomingServer::OnUserOrHostNameChanged(const nsACString& oldName, const nsACString& newName)
{
  nsresult rv;
  // 1. Do common things in the base class.
  rv = nsMsgIncomingServer::OnUserOrHostNameChanged(oldName, newName);
  NS_ENSURE_SUCCESS(rv,rv);

  // 2. Remove file hostinfo.dat so that the new subscribe
  //    list will be reloaded from the new server.
  nsCOMPtr <nsILocalFile> hostInfoFile;
  rv = GetLocalPath(getter_AddRefs(hostInfoFile));
  NS_ENSURE_SUCCESS(rv, rv);
  rv = hostInfoFile->AppendNative(NS_LITERAL_CSTRING(HOSTINFO_FILE_NAME));
  NS_ENSURE_SUCCESS(rv, rv);
  hostInfoFile->Remove(PR_FALSE);

  // 3.Unsubscribe and then subscribe the existing groups to clean up the article numbers
  //   in the rc file (this is because the old and new servers may maintain different
  //   numbers for the same articles if both servers handle the same groups).
  nsCOMPtr <nsIMsgFolder> serverFolder;
  rv = GetRootMsgFolder(getter_AddRefs(serverFolder));
  NS_ENSURE_SUCCESS(rv,rv);

  nsCOMPtr<nsISimpleEnumerator> subFolders;
  rv = serverFolder->GetSubFolders(getter_AddRefs(subFolders));
  NS_ENSURE_SUCCESS(rv,rv);

  nsStringArray groupList;
  nsString folderName;

  // Prepare the group list
  PRBool hasMore;
  while (NS_SUCCEEDED(subFolders->HasMoreElements(&hasMore)) && hasMore)
  {
    nsCOMPtr<nsISupports> item;
    subFolders->GetNext(getter_AddRefs(item));
    nsCOMPtr<nsIMsgFolder> newsgroupFolder(do_QueryInterface(item));
    if (!newsgroupFolder)
      continue;

    rv = newsgroupFolder->GetName(folderName);
    NS_ENSURE_SUCCESS(rv,rv);
    groupList.AppendString(folderName);
  }

  // If nothing subscribed then we're done.
  if (groupList.Count() == 0)
    return NS_OK;

  // Now unsubscribe & subscribe.
  int i, cnt=groupList.Count();
  nsAutoString groupStr;
  nsCAutoString cname;
  for (i=0; i<cnt; i++)
  {
    // unsubscribe.
    groupList.StringAt(i, groupStr);
    rv = Unsubscribe(groupStr.get());
    NS_ENSURE_SUCCESS(rv,rv);
  }

  for (i=0; i<cnt; i++)
  {
    // subscribe.
    groupList.StringAt(i, groupStr);
    rv = SubscribeToNewsgroup(NS_ConvertUTF16toUTF8(groupStr));
    NS_ENSURE_SUCCESS(rv,rv);
  }

  groupList.Clear();

  // Force updating the rc file.
  return CommitSubscribeChanges();
}
