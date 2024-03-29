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

/**
   Interface for representing News folders.
*/

#ifndef nsMsgNewsFolder_h__
#define nsMsgNewsFolder_h__

#include "nsMsgDBFolder.h"
#include "nsILocalFile.h"
#include "nsINntpIncomingServer.h" // need this for the IID
#include "nsNewsUtils.h"
#include "nsMsgKeySet.h"
#include "nsIMsgNewsFolder.h"
#include "nsCOMPtr.h"
#include "nsIMsgFilterService.h"
#include "nsIArray.h"

class nsMsgNewsFolder : public nsMsgDBFolder, public nsIMsgNewsFolder
{
public:
  nsMsgNewsFolder(void);
  virtual ~nsMsgNewsFolder(void);

  NS_DECL_ISUPPORTS_INHERITED
  NS_DECL_NSIMSGNEWSFOLDER

  // nsIUrlListener method
  NS_IMETHOD OnStopRunningUrl(nsIURI * aUrl, nsresult aExitCode);
  // nsIMsgFolder methods:
  NS_IMETHOD GetSubFolders(nsISimpleEnumerator **aResult);

  NS_IMETHOD GetMessages(nsISimpleEnumerator **result);
  NS_IMETHOD UpdateFolder(nsIMsgWindow *aWindow);

  NS_IMETHOD CreateSubfolder(const nsAString& folderName,nsIMsgWindow *msgWindow);

  NS_IMETHOD Delete ();
  NS_IMETHOD Rename (const nsAString& newName, nsIMsgWindow *msgWindow);

  NS_IMETHOD GetAbbreviatedName(nsAString& aAbbreviatedName);

  NS_IMETHOD GetFolderURL(nsACString& url);

  NS_IMETHOD GetExpungedBytesCount(PRUint32 *count);
  NS_IMETHOD GetDeletable (PRBool *deletable);
  NS_IMETHOD GetRequiresCleanup(PRBool *requiresCleanup);

  NS_IMETHOD GetSizeOnDisk(PRUint32 *size);

  NS_IMETHOD GetDBFolderInfoAndDB(nsIDBFolderInfo **folderInfo, nsIMsgDatabase **db);

  NS_IMETHOD DeleteMessages(nsIArray *messages,
                      nsIMsgWindow *msgWindow, PRBool deleteStorage, PRBool isMove,
                      nsIMsgCopyServiceListener* listener, PRBool allowUndo);
  NS_IMETHOD GetNewMessages(nsIMsgWindow *aWindow, nsIUrlListener *aListener);

  NS_IMETHOD GetCanSubscribe(PRBool *aResult);
  NS_IMETHOD GetCanFileMessages(PRBool *aResult);
  NS_IMETHOD GetCanDeleteMessages(PRBool *aCanDeleteMessages);
  NS_IMETHOD GetCanCreateSubfolders(PRBool *aResult);
  NS_IMETHOD GetCanRename(PRBool *aResult);
  NS_IMETHOD GetCanCompact(PRBool *aResult);
  NS_IMETHOD OnReadChanged(nsIDBChangeListener * aInstigator);

  NS_IMETHOD DownloadMessagesForOffline(nsIArray *messages, nsIMsgWindow *window);
  NS_IMETHOD Compact(nsIUrlListener *aListener, nsIMsgWindow *aMsgWindow);
  NS_IMETHOD DownloadAllForOffline(nsIUrlListener *listener, nsIMsgWindow *msgWindow);
  NS_IMETHOD GetSortOrder(PRInt32 *order);
  NS_IMETHOD SetSortOrder(PRInt32 order);

  NS_IMETHOD Shutdown(PRBool shutdownChildren);

  NS_IMETHOD GetFilterList(nsIMsgWindow *aMsgWindow, nsIMsgFilterList **aFilterList);
  NS_IMETHOD GetEditableFilterList(nsIMsgWindow *aMsgWindow, nsIMsgFilterList **aFilterList);
  NS_IMETHOD SetFilterList(nsIMsgFilterList *aFilterList);
  NS_IMETHOD SetEditableFilterList(nsIMsgFilterList *aFilterList);
  NS_IMETHOD ApplyRetentionSettings();

protected:
  // helper routine to parse the URI and update member variables
  nsresult AbbreviatePrettyName(nsAString& prettyName, PRInt32 fullwords);
  nsresult ParseFolder(nsILocalFile *path);
  nsresult CreateSubFolders(nsILocalFile *path);
  nsresult AddDirectorySeparator(nsILocalFile *path);
  nsresult GetDatabase();
  virtual nsresult CreateChildFromURI(const nsCString &uri, nsIMsgFolder **folder);

  nsresult LoadNewsrcFileAndCreateNewsgroups();
  PRInt32 RememberLine(const nsACString& line);
  nsresult RememberUnsubscribedGroup(const nsACString& newsgroup, const nsACString& setStr);
  nsresult ForgetLine(void);
  nsresult GetNewsMessages(nsIMsgWindow *aMsgWindow, PRBool getOld, nsIUrlListener *aListener);

  PRInt32 HandleNewsrcLine(const char * line, PRUint32 line_size);
  virtual void GetIncomingServerType(nsCString& serverType) { serverType.AssignLiteral("nntp");}
  virtual nsresult CreateBaseMessageURI(const nsACString& aURI);

protected:
  PRUint32  mExpungedBytes;
  PRPackedBool mGettingNews;
  PRPackedBool mInitialized;
  PRPackedBool m_downloadMessageForOfflineUse;
  PRPackedBool m_downloadingMultipleMessages;

  nsCString mOptionLines;
  nsCString mUnsubscribedNewsgroupLines;
  nsMsgKeySet *mReadSet;

  nsCOMPtr<nsILocalFile> mNewsrcFilePath;

  // used for auth news
  nsCString mGroupUsername;
  nsCString mGroupPassword;

  nsCString mPrevUsername;
  nsCString mPrevPassword;

  // the name of the newsgroup.
  nsCString mRawName;
  PRInt32 mSortOrder;

private:
  nsresult CreateNewsgroupUsernameUrlForSignon(const nsACString& inUriStr, nsACString& result);
  nsresult CreateNewsgroupPasswordUrlForSignon(const nsACString& inUriStr, nsACString& result);
  nsresult CreateNewsgroupUrlForSignon(const nsACString& inUriStr, const char * ref, nsACString& result);
  nsCOMPtr <nsIMsgFilterList> mFilterList;
};

#endif // nsMsgNewsFolder_h__
