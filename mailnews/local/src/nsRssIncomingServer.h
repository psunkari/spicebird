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

#ifndef __nsRssIncomingServer_h
#define __nsRssIncomingServer_h

#include "nsIRssIncomingServer.h"
#include "nsILocalMailIncomingServer.h"
#include "nsMsgIncomingServer.h"
#include "nsIMsgFolderListener.h"
#include "nsMailboxServer.h"

class nsRssIncomingServer : public nsMailboxServer,
                            public nsIRssIncomingServer,
                            public nsILocalMailIncomingServer,
                            public nsIMsgFolderListener

{
public:
    NS_DECL_ISUPPORTS_INHERITED
    NS_DECL_NSIRSSINCOMINGSERVER
    NS_DECL_NSILOCALMAILINCOMINGSERVER
    NS_DECL_NSIMSGFOLDERLISTENER

    NS_IMETHOD GetOfflineSupportLevel(PRInt32 *aSupportLevel);
    NS_IMETHOD GetSupportsDiskSpace(PRBool *aSupportsDiskSpace);
    NS_IMETHOD GetAccountManagerChrome(nsAString& aResult);
    NS_IMETHOD PerformBiff(nsIMsgWindow *aMsgWindow);
    NS_IMETHOD GetServerRequiresPasswordForBiff(PRBool *aServerRequiresPasswordForBiff);
    NS_IMETHOD GetCanSearchMessages(PRBool *canSearchMessages);

    nsRssIncomingServer();
    virtual ~nsRssIncomingServer();
protected:
    nsresult FolderChanged(nsIMsgFolder *aFolder, PRBool aUnsubscribe);
    nsresult FillInDataSourcePath(const nsAString& aDataSourceName, nsILocalFile ** aLocation);
    static nsrefcnt gInstanceCount;
};

#endif /* __nsRssIncomingServer_h */
