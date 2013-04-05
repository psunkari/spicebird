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


#ifndef __CS_TELEPATHY_HEADER_CONNECTIONINTERFACESIMPLEPRESENCE__
#define __CS_TELEPATHY_HEADER_CONNECTIONINTERFACESIMPLEPRESENCE__

#include "nsISupports.h"
#include "csITpConnectionInterfaceSimplePresence.h"
#include "glib.h"
#include "nsStringGlue.h"
#include "nsIArray.h"
#include "nsIVariant.h"
#include "nsCOMPtr.h"
#include "nsIMutableArray.h"
#include "nsArrayUtils.h"
#include "csTpBaseProxies.h"
#include "telepathy-glib/connection.h"


class csTpSimplePresence: public csITpSimplePresence
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPSIMPLEPRESENCE

  csTpSimplePresence(PRUint32 aType, const nsCString &aStatus, const nsCString &aStatusMessage);
  static NS_METHOD Create(PRUint32 aType, const nsCString &aStatus, const nsCString &aStatusMessage, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpSimplePresence();

protected:
  PRUint32 m_Type;
  nsCString m_Status;
  nsCString m_StatusMessage;
};

class csTpSimpleContactPresences: public csITpSimpleContactPresences
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPSIMPLECONTACTPRESENCES

  csTpSimpleContactPresences(PRUint32 aContact, nsISupports *aPresence);
  static NS_METHOD Create(PRUint32 aContact, nsISupports *aPresence, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, nsIArray **array);
  static NS_METHOD ToGLib(nsIArray *aObj, gpointer *_retval);

private:
  ~csTpSimpleContactPresences();

protected:
  PRUint32 m_Contact;
  nsCOMPtr<nsISupports> m_Presence;
};

class csTpSimpleStatusSpec: public csITpSimpleStatusSpec
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPSIMPLESTATUSSPEC

  csTpSimpleStatusSpec(PRUint32 aType, PRBool aMaySetOnSelf, PRBool aCanHaveMessage);
  static NS_METHOD Create(PRUint32 aType, PRBool aMaySetOnSelf, PRBool aCanHaveMessage, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpSimpleStatusSpec();

protected:
  PRUint32 m_Type;
  PRBool m_MaySetOnSelf;
  PRBool m_CanHaveMessage;
};

class csTpSimpleStatusSpecMap: public csITpSimpleStatusSpecMap
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPSIMPLESTATUSSPECMAP

  csTpSimpleStatusSpecMap(const nsCString &aIdentifier, nsISupports *aSpec);
  static NS_METHOD Create(const nsCString &aIdentifier, nsISupports *aSpec, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, nsIArray **array);
  static NS_METHOD ToGLib(nsIArray *aObj, gpointer *_retval);

private:
  ~csTpSimpleStatusSpecMap();

protected:
  nsCString m_Identifier;
  nsCOMPtr<nsISupports> m_Spec;
};

class csTpRichPresenceAccessControl: public csITpRichPresenceAccessControl
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPRICHPRESENCEACCESSCONTROL

  csTpRichPresenceAccessControl(PRUint32 aType, nsIVariant *aDetail);
  static NS_METHOD Create(PRUint32 aType, nsIVariant *aDetail, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpRichPresenceAccessControl();

protected:
  PRUint32 m_Type;
  nsCOMPtr<nsIVariant> m_Detail;
};



class csTpConnectionInterfaceSimplePresence: public csITpConnectionInterfaceSimplePresence, public virtual _csTpConnectionProxyBase
{
public:
  NS_DECL_CSITPCONNECTIONINTERFACESIMPLEPRESENCE

  csTpConnectionInterfaceSimplePresence();

  void HandlePresencesChanged(GHashTable *presence);

protected:
  nsCOMPtr<nsIMutableArray> m_PresencesChangedObservers;

  ~csTpConnectionInterfaceSimplePresence();

private:

};
#endif