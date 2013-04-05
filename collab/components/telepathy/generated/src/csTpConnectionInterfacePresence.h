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
 *   Synovel Software Technologies
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Prasad Sunkari <prasad@synovel.com> (Original Author)
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

/*
 * Code in this file is generated using a computer program.
 * Please refer to the corresponding telepathy spec for any help in using the
 * code here.  You may also feel free to contact the original developer for
 * any related help.
 */


#ifndef __CS_TELEPATHY_HEADER_CONNECTIONINTERFACEPRESENCE__
#define __CS_TELEPATHY_HEADER_CONNECTIONINTERFACEPRESENCE__

#include "nsISupports.h"
#include "csITpConnectionInterfacePresence.h"
#include "glib.h"
#include "nsStringGlue.h"
#include "nsIArray.h"
#include "nsCOMPtr.h"
#include "nsIMutableArray.h"
#include "nsArrayUtils.h"
#include "csTpBaseProxies.h"
#include "telepathy-glib/connection.h"


class csTpMultipleStatusMap: public csITpMultipleStatusMap
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPMULTIPLESTATUSMAP

  csTpMultipleStatusMap(const nsCString &aStatus, nsIArray *aParameters);
  static NS_METHOD Create(const nsCString &aStatus, nsIArray *aParameters, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, nsIArray **array);
  static NS_METHOD ToGLib(nsIArray *aObj, gpointer *_retval);

private:
  ~csTpMultipleStatusMap();

protected:
  nsCString m_Status;
  nsCOMPtr<nsIArray> m_Parameters;
};

class csTpLastActivityAndStatuses: public csITpLastActivityAndStatuses
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPLASTACTIVITYANDSTATUSES

  csTpLastActivityAndStatuses(PRUint32 aLastActivity, nsIArray *aStatuses);
  static NS_METHOD Create(PRUint32 aLastActivity, nsIArray *aStatuses, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpLastActivityAndStatuses();

protected:
  PRUint32 m_LastActivity;
  nsCOMPtr<nsIArray> m_Statuses;
};

class csTpContactPresences: public csITpContactPresences
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPCONTACTPRESENCES

  csTpContactPresences(PRUint32 aContact, nsISupports *aPresence);
  static NS_METHOD Create(PRUint32 aContact, nsISupports *aPresence, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, nsIArray **array);
  static NS_METHOD ToGLib(nsIArray *aObj, gpointer *_retval);

private:
  ~csTpContactPresences();

protected:
  PRUint32 m_Contact;
  nsCOMPtr<nsISupports> m_Presence;
};

class csTpStatusSpec: public csITpStatusSpec
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPSTATUSSPEC

  csTpStatusSpec(PRUint32 aType, PRBool aMaySetOnSelf, PRBool aExclusive, nsIArray *aParameterTypes);
  static NS_METHOD Create(PRUint32 aType, PRBool aMaySetOnSelf, PRBool aExclusive, nsIArray *aParameterTypes, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpStatusSpec();

protected:
  PRUint32 m_Type;
  PRBool m_MaySetOnSelf;
  PRBool m_Exclusive;
  nsCOMPtr<nsIArray> m_ParameterTypes;
};

class csTpStatusSpecMap: public csITpStatusSpecMap
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPSTATUSSPECMAP

  csTpStatusSpecMap(const nsCString &aIdentifier, nsISupports *aSpec);
  static NS_METHOD Create(const nsCString &aIdentifier, nsISupports *aSpec, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, nsIArray **array);
  static NS_METHOD ToGLib(nsIArray *aObj, gpointer *_retval);

private:
  ~csTpStatusSpecMap();

protected:
  nsCString m_Identifier;
  nsCOMPtr<nsISupports> m_Spec;
};



class csTpConnectionInterfacePresence: public csITpConnectionInterfacePresence, public virtual _csTpConnectionProxyBase
{
public:
  NS_DECL_CSITPCONNECTIONINTERFACEPRESENCE

  csTpConnectionInterfacePresence();

  void HandlePresenceUpdate(GHashTable *presence);

protected:
  nsCOMPtr<nsIMutableArray> m_PresenceUpdateObservers;

  ~csTpConnectionInterfacePresence();

private:

};
#endif