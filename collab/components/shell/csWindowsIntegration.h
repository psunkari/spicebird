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
 * The Original Code is Thunderbird Windows Integration.
 *
 * The Initial Developer of the Original Code is
 *   Scott MacGregor <mscott@mozilla.org>.
 * Portions created by the Initial Developer are Copyright (C) 2006
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

#ifndef nsMailWinIntegration_h_
#define nsMailWinIntegration_h_

#include "nsIShellService.h"
#include "nsIObserver.h"
#include "nsIGenericFactory.h"
#include "nsString.h"

#include <ole2.h>
#include <windows.h>

#define CS_WINDOWS_INTEGRATION_CID \
{0x7253fdab, 0x854b, 0x496c, {0xb0, 0xf1, 0x72, 0x32, 0x2e, 0x02, 0xb4, 0x65}}

typedef struct {
  char* keyName;
  char* valueName;
  char* valueData;

  PRInt32 flags;
} SETTING;

class nsWindowsShellService : public nsIShellService
{
public:
  nsWindowsShellService();
  virtual ~nsWindowsShellService() {};
  NS_HIDDEN_(nsresult) Init();

  NS_DECL_ISUPPORTS
  NS_DECL_NSISHELLSERVICE

protected:
  PRBool TestForDefault(SETTING aSettings[], PRInt32 aSize);
  PRBool IsDefaultClientVista(PRUint16 aApps, PRBool* aIsDefaultClient);

private:
  PRBool mCheckedThisSession;
  nsAutoString mAppLongPath;
 };

#endif
