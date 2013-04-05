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


#ifndef __CS_TELEPATHY_HEADER_CHANNELTYPETUBES__
#define __CS_TELEPATHY_HEADER_CHANNELTYPETUBES__

#include "nsISupports.h"
#include "csITpChannelTypeTubes.h"
#include "glib.h"
#include "nsStringGlue.h"
#include "nsIArray.h"
#include "nsIVariant.h"
#include "nsCOMPtr.h"
#include "nsIMutableArray.h"
#include "nsArrayUtils.h"
#include "csTpBaseProxies.h"
#include "telepathy-glib/channel.h"


class csTpTubeInfo: public csITpTubeInfo
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPTUBEINFO

  csTpTubeInfo(PRUint32 aIdentifier, PRUint32 aInitiator, PRUint32 aType, const nsCString &aService, nsIArray *aParameters, PRUint32 aState);
  static NS_METHOD Create(PRUint32 aIdentifier, PRUint32 aInitiator, PRUint32 aType, const nsCString &aService, nsIArray *aParameters, PRUint32 aState, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpTubeInfo();

protected:
  PRUint32 m_Identifier;
  PRUint32 m_Initiator;
  PRUint32 m_Type;
  nsCString m_Service;
  nsCOMPtr<nsIArray> m_Parameters;
  PRUint32 m_State;
};

class csTpDBusTubeMember: public csITpDBusTubeMember
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPDBUSTUBEMEMBER

  csTpDBusTubeMember(PRUint32 aHandle, const nsCString &aUniqueName);
  static NS_METHOD Create(PRUint32 aHandle, const nsCString &aUniqueName, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpDBusTubeMember();

protected:
  PRUint32 m_Handle;
  nsCString m_UniqueName;
};

class csTpSupportedSocketMap: public csITpSupportedSocketMap
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPSUPPORTEDSOCKETMAP

  csTpSupportedSocketMap(PRUint32 aAddressType, PRUint32 aAccessControlCount, PRUint32 *aAccessControl);
  static NS_METHOD Create(PRUint32 aAddressType, PRUint32 aAccessControlCount, PRUint32 *aAccessControl, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, nsIArray **array);
  static NS_METHOD ToGLib(nsIArray *aObj, gpointer *_retval);

private:
  ~csTpSupportedSocketMap();

protected:
  PRUint32 m_AddressType;
  PRUint32 m_AccessControlCount; PRUint32 *m_AccessControl;
};



class csTpChannelTypeTubes: public csITpChannelTypeTubes, public virtual _csTpChannelProxyBase
{
public:
  NS_DECL_CSITPCHANNELTYPETUBES

  csTpChannelTypeTubes();

  void HandleNewTube(guint id, guint initiator, guint type, const gchar *service, GHashTable *parameters, guint state);
  void HandleTubeStateChanged(guint id, guint state);
  void HandleTubeClosed(guint id);
  void HandleDBusNamesChanged(guint id, const GPtrArray *added, const GArray *removed);
  void HandleStreamTubeNewConnection(guint id, guint handle);

protected:
  nsCOMPtr<nsIMutableArray> m_NewTubeObservers;
  nsCOMPtr<nsIMutableArray> m_TubeStateChangedObservers;
  nsCOMPtr<nsIMutableArray> m_TubeClosedObservers;
  nsCOMPtr<nsIMutableArray> m_DBusNamesChangedObservers;
  nsCOMPtr<nsIMutableArray> m_StreamTubeNewConnectionObservers;

  ~csTpChannelTypeTubes();

private:

};
#endif