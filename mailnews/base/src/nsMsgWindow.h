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

#ifndef _nsMsgWindow_h
#define _nsMsgWindow_h

#include "nsIMsgWindow.h"
#include "nsIMsgStatusFeedback.h"
#include "nsITransactionManager.h"
#include "nsIMsgFolder.h"
#include "nsIDocShell.h"
#include "nsIURIContentListener.h"
#include "nsIMimeMiscStatus.h"
#include "nsWeakReference.h"
#include "nsIInterfaceRequestor.h"
#include "nsCOMPtr.h"

class nsMsgWindow : public nsIMsgWindow,
                    public nsIURIContentListener,
                    public nsSupportsWeakReference
{

public:

  NS_DECL_ISUPPORTS

  nsMsgWindow();
  virtual ~nsMsgWindow();
  nsresult Init();
  NS_DECL_NSIMSGWINDOW
  NS_DECL_NSIURICONTENTLISTENER

protected:
  nsCOMPtr<nsIMsgHeaderSink> mMsgHeaderSink;
  nsCOMPtr<nsIMsgStatusFeedback> mStatusFeedback;
  nsCOMPtr<nsITransactionManager> mTransactionManager;
  nsCOMPtr<nsIMsgFolder> mOpenFolder;
  nsCOMPtr<nsIMsgWindowCommands> mMsgWindowCommands;
  // These are used by the backend protocol code to attach
  // notification callbacks to channels, e.g., nsIBadCertListner2.
  nsCOMPtr<nsIInterfaceRequestor> mNotificationCallbacks;

  // let's not make this a strong ref - we don't own it.
  nsWeakPtr mRootDocShellWeak;
  nsWeakPtr mMessageWindowDocShellWeak;
  nsWeakPtr mDomWindow; 

  nsCString mMailCharacterSet;
  PRBool    mCharsetOverride;
  PRBool    m_stopped;
  // small helper function used to optimize our use of a weak reference
  // on the message window docshell. Under no circumstances should you be holding on to
  // the docshell returned here outside the scope of your routine.
  void GetMessageWindowDocShell(nsIDocShell ** aDocShell);
};

#endif
