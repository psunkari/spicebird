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
 *   Nick Kreeger <nick.kreeger@park.edu>
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

#ifndef nsMsgMailSession_h___
#define nsMsgMailSession_h___

#include "nsIMsgMailSession.h"
#include "nsISupports.h"
#include "nsCOMPtr.h"
#include "nsIMsgStatusFeedback.h"
#include "nsIMsgWindow.h"
#include "nsCOMArray.h"
#include "nsIMsgShutdown.h"
#include "nsIObserver.h"
#include "nsIMutableArray.h"
#include "nsIMsgProgress.h"
#include "nsTArray.h"
#include "nsTObserverArray.h"
#include "nsIMsgUserFeedbackListener.h"
#include "nsIUrlListener.h"

///////////////////////////////////////////////////////////////////////////////////
// The mail session is a replacement for the old 4.x MSG_Master object. It contains
// mail session generic information such as the user's current mail identity, ....
// I'm starting this off as an empty interface and as people feel they need to
// add more information to it, they can. I think this is a better approach than 
// trying to port over the old MSG_Master in its entirety as that had a lot of 
// cruft in it....
//////////////////////////////////////////////////////////////////////////////////

class nsMsgMailSession : public nsIMsgMailSession,
                         public nsIFolderListener
{
public:
  nsMsgMailSession();
  virtual ~nsMsgMailSession();

  NS_DECL_ISUPPORTS
  NS_DECL_NSIMSGMAILSESSION
  NS_DECL_NSIFOLDERLISTENER

  nsresult Init();
  nsresult GetSelectedLocaleDataDir(nsIFile *defaultsDir);

protected:
  struct folderListener {
    nsCOMPtr<nsIFolderListener> mListener;
    PRUint32 mNotifyFlags;

    folderListener(nsIFolderListener *aListener, PRUint32 aNotifyFlags)
      : mListener(aListener), mNotifyFlags(aNotifyFlags) {}
    folderListener(const folderListener &aListener)
      : mListener(aListener.mListener), mNotifyFlags(aListener.mNotifyFlags) {}
    ~folderListener() {}

    int operator==(nsIFolderListener* aListener) const {
      return mListener == aListener;
    }
    int operator==(const folderListener &aListener) const {
      return mListener == aListener.mListener &&
             mNotifyFlags == aListener.mNotifyFlags;
    }
  };

  nsTObserverArray<folderListener> mListeners;
  nsTObserverArray<nsCOMPtr<nsIMsgUserFeedbackListener> > mFeedbackListeners;

  nsCOMArray<nsIMsgWindow> mWindows;
  // stick this here temporarily
  nsCOMPtr <nsIMsgWindow> m_temporaryMsgWindow;
};

/********************************************************************************/

class nsMsgShutdownService : public nsIMsgShutdownService,
                             public nsIUrlListener,
                             public nsIObserver
{
public:
  nsMsgShutdownService();
  virtual ~nsMsgShutdownService();
  
  NS_DECL_ISUPPORTS
  NS_DECL_NSIMSGSHUTDOWNSERVICE
  NS_DECL_NSIURLLISTENER
  NS_DECL_NSIOBSERVER
    
protected:
  nsresult ProcessNextTask();
  void AttemptShutdown();
  
private:
  nsCOMArray<nsIMsgShutdownTask> mShutdownTasks;
  nsCOMPtr<nsIMsgProgress>       mMsgProgress;
  PRUint32                       mTaskIndex;
  PRUint32                       mQuitMode;
  PRPackedBool mProcessedShutdown;
  PRPackedBool mQuitForced;
  PRPackedBool mReadyToQuit;
};

#endif /* nsMsgMailSession_h__ */
