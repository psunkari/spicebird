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
 * The Original Code is Spicebird code.
 *
 * The Initial Developer of the Original Code is
 * Synovel Software Technologies
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Sunil Mohan Adapa <sunil@synovel.com>, original author
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
#ifndef __CS_BLOGINCOMINGSERVER_H__
#define __CS_BLOGINCOMINGSERVER_H__

#include "nsMsgIncomingServer.h"
#include "nsILocalMailIncomingServer.h"
#include "csIBlogManager.h"

#define CS_BLOGINCOMINGSERVER_CONTRACTID        \
  "@mozilla.org/messenger/server;1?type=blog"

#define CS_BLOGINCOMINGSERVER_CID               \
 { /* {23a9ccd3-0eeb-4fdf-a217-58fac2ea8de2} */ \
   0x23a9ccd3, 0x0eeb, 0x4fdf,                  \
   { 0xa2, 0x17, 0x58, 0xfa, 0xc2, 0xea, 0x8d, 0xe2}}

#define CS_BLOGINCOMINGSERVER_DESC              \
  "Provider for Blog Incoming Server"

class csBlogIncomingServer: public nsMsgIncomingServer,
                            public nsILocalMailIncomingServer,
                            public nsIFolderListener
{
public:

    csBlogIncomingServer();
    virtual ~csBlogIncomingServer();

    NS_DECL_ISUPPORTS_INHERITED
    NS_DECL_NSILOCALMAILINCOMINGSERVER
    NS_DECL_NSIFOLDERLISTENER

    NS_IMETHOD GetSupportsDiskSpace(PRBool *aSupportsDiskSpace);
    NS_IMETHOD GetCanHaveFilters(PRBool *aCanHaveFilters);
    NS_IMETHOD GetCanSearchMessages(PRBool *canSearchMessages);
    NS_IMETHOD GetCanFileMessages(PRBool *canFileMessages);
    NS_IMETHOD GetLocalStoreType(nsACString& type);
    NS_IMETHOD GetAccountManagerChrome(nsAString& aResult);
    NS_IMETHOD GetNewMessages(nsIMsgFolder *aFolder, nsIMsgWindow *aMsgWindow,
                              nsIUrlListener *aUrlListener);
    NS_IMETHOD ConfigureTemporaryFilters(nsIMsgFilterList *aFilterList);

protected:
    nsresult SetFlagsOnDefaultMailbox(const nsAString& aFolderName,
                                      PRUint32 flags);

    static nsrefcnt gInstanceCount;
    
    nsCOMPtr<csIBlogManager> mBlogManager;
};

#endif /* __CS_BLOGINCOMINGSERVER_H__ */
