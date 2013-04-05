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


#include "csTpChannelTypeTubes.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpTubeInfo
 */

NS_IMPL_ISUPPORTS1(csTpTubeInfo, csITpTubeInfo)

NS_METHOD
csTpTubeInfo::Create(PRUint32 aIdentifier, PRUint32 aInitiator, PRUint32 aType, const nsCString &aService, nsIArray *aParameters, PRUint32 aState, void **aResult)
{
  csITpTubeInfo *it = 
          new csTpTubeInfo(aIdentifier, aInitiator, aType, aService, aParameters, aState);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpTubeInfo), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpTubeInfo::Create(gpointer aGLibItem, void **aResult)
{
  guint identifier;
  guint initiator;
  guint type;
  const gchar *service;
  GHashTable *parameters;
  guint state;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_TUBE_INFO);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &identifier, 1, &initiator, 2, &type, 3, &service, 4, &parameters, 5, &state,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cService = nsDependentCString(service);
  nsCOMPtr<nsIArray> cParameters;
  csTpStringVariantMap::Create((gpointer)parameters, getter_AddRefs(cParameters));
  csITpTubeInfo *it = new csTpTubeInfo(identifier, initiator, type, cService, cParameters, state);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpTubeInfo), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpTubeInfo::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpTubeInfo::csTpTubeInfo(PRUint32 aIdentifier, PRUint32 aInitiator, PRUint32 aType, const nsCString &aService, nsIArray *aParameters, PRUint32 aState)
{
  m_Identifier = aIdentifier;
  m_Initiator = aInitiator;
  m_Type = aType;
  m_Service.Assign(aService);
  m_Parameters = aParameters;
  m_State = aState;
}

csTpTubeInfo::~csTpTubeInfo()
{}

NS_IMETHODIMP
csTpTubeInfo::GetIdentifier(PRUint32 *aIdentifier)
{
  *aIdentifier = m_Identifier;
  return NS_OK;
}

NS_IMETHODIMP
csTpTubeInfo::GetInitiator(PRUint32 *aInitiator)
{
  *aInitiator = m_Initiator;
  return NS_OK;
}

NS_IMETHODIMP
csTpTubeInfo::GetType(PRUint32 *aType)
{
  *aType = m_Type;
  return NS_OK;
}

NS_IMETHODIMP
csTpTubeInfo::GetService(nsACString &aService)
{
  aService.Assign(m_Service);
  return NS_OK;
}

NS_IMETHODIMP
csTpTubeInfo::GetParameters(nsIArray **aParameters)
{
  NS_IF_ADDREF(*aParameters = m_Parameters);
  return NS_OK;
}

NS_IMETHODIMP
csTpTubeInfo::GetState(PRUint32 *aState)
{
  *aState = m_State;
  return NS_OK;
}

/*
 *  Implementation of csTpDBusTubeMember
 */

NS_IMPL_ISUPPORTS1(csTpDBusTubeMember, csITpDBusTubeMember)

NS_METHOD
csTpDBusTubeMember::Create(PRUint32 aHandle, const nsCString &aUniqueName, void **aResult)
{
  csITpDBusTubeMember *it = 
          new csTpDBusTubeMember(aHandle, aUniqueName);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpDBusTubeMember), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpDBusTubeMember::Create(gpointer aGLibItem, void **aResult)
{
  guint handle;
  const gchar *unique_name;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_DBUS_TUBE_MEMBER);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &handle, 1, &unique_name,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cUniqueName = nsDependentCString(unique_name);
  csITpDBusTubeMember *it = new csTpDBusTubeMember(handle, cUniqueName);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpDBusTubeMember), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpDBusTubeMember::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpDBusTubeMember::csTpDBusTubeMember(PRUint32 aHandle, const nsCString &aUniqueName)
{
  m_Handle = aHandle;
  m_UniqueName.Assign(aUniqueName);
}

csTpDBusTubeMember::~csTpDBusTubeMember()
{}

NS_IMETHODIMP
csTpDBusTubeMember::GetHandle(PRUint32 *aHandle)
{
  *aHandle = m_Handle;
  return NS_OK;
}

NS_IMETHODIMP
csTpDBusTubeMember::GetUniqueName(nsACString &aUniqueName)
{
  aUniqueName.Assign(m_UniqueName);
  return NS_OK;
}

/*
 *  Implementation of csTpSupportedSocketMap
 */

NS_IMPL_ISUPPORTS1(csTpSupportedSocketMap, csITpSupportedSocketMap)

NS_METHOD
csTpSupportedSocketMap::Create(PRUint32 aAddressType, PRUint32 aAccessControlCount, PRUint32 *aAccessControl, void **aResult)
{
  csITpSupportedSocketMap *it = 
          new csTpSupportedSocketMap(aAddressType, aAccessControlCount, aAccessControl);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSupportedSocketMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpSupportedSocketMap::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    guint address_type = GPOINTER_TO_UINT(keyPtr);
    const GArray *access_control = (GArray *)valuePtr;

    PRUint32 cAccessControlCount = access_control->len;
    PRUint32 *cAccessControl = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cAccessControlCount);
    for (unsigned int i=0; i<cAccessControlCount; i++)
      cAccessControl[i] = g_array_index(access_control, guint, i);

    csITpSupportedSocketMap *temp = new csTpSupportedSocketMap(address_type, cAccessControlCount, cAccessControl);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpSupportedSocketMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpSupportedSocketMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpSupportedSocketMap::csTpSupportedSocketMap(PRUint32 aAddressType, PRUint32 aAccessControlCount, PRUint32 *aAccessControl)
{
  m_AddressType = aAddressType;
  m_AccessControlCount = aAccessControlCount; m_AccessControl = (PRUint32 *)aAccessControl;
}

csTpSupportedSocketMap::~csTpSupportedSocketMap()
{}

NS_IMETHODIMP
csTpSupportedSocketMap::GetAddressType(PRUint32 *aAddressType)
{
  *aAddressType = m_AddressType;
  return NS_OK;
}

NS_IMETHODIMP
csTpSupportedSocketMap::GetAccessControl(PRUint32 *aAccessControlCount, PRUint32 **aAccessControl)
{
  *aAccessControlCount = m_AccessControlCount; *aAccessControl = m_AccessControl;
  return NS_OK;
}

static void
GetAvailableStreamTubeTypesResponse(TpChannel *proxy,
    GHashTable *available_stream_tube_types,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTubesGetAvailableStreamTubeTypesCB *callback = (csITpChannelTypeTubesGetAvailableStreamTubeTypesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetAvailableStreamTubeTypesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIArray> cAvailableStreamTubeTypes;
  csTpSupportedSocketMap::Create((gpointer)available_stream_tube_types, getter_AddRefs(cAvailableStreamTubeTypes));

  callback->OnGetAvailableStreamTubeTypesDone(cAvailableStreamTubeTypes);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeTubes::CallGetAvailableStreamTubeTypes(csITpChannelTypeTubesGetAvailableStreamTubeTypesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_tubes_call_get_available_stream_tube_types(m_Proxy, -1,
      cb? GetAvailableStreamTubeTypesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetAvailableTubeTypesResponse(TpChannel *proxy,
    const GArray *available_tube_types,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTubesGetAvailableTubeTypesCB *callback = (csITpChannelTypeTubesGetAvailableTubeTypesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetAvailableTubeTypesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cAvailableTubeTypesCount = available_tube_types->len;
  PRUint32 *cAvailableTubeTypes = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cAvailableTubeTypesCount);
  for (unsigned int i=0; i<cAvailableTubeTypesCount; i++)
    cAvailableTubeTypes[i] = g_array_index(available_tube_types, guint, i);

  callback->OnGetAvailableTubeTypesDone(cAvailableTubeTypesCount, cAvailableTubeTypes);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeTubes::CallGetAvailableTubeTypes(csITpChannelTypeTubesGetAvailableTubeTypesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_tubes_call_get_available_tube_types(m_Proxy, -1,
      cb? GetAvailableTubeTypesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ListTubesResponse(TpChannel *proxy,
    const GPtrArray *tubes,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTubesListTubesCB *callback = (csITpChannelTypeTubesListTubesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnListTubesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIMutableArray> cTubes = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)tubes)->len; i++) {
    gpointer tubes_item = g_ptr_array_index((GPtrArray*)tubes, i);
    nsCOMPtr<csITpTubeInfo> cTubesItem;
    csTpTubeInfo::Create((gpointer)tubes_item, getter_AddRefs(cTubesItem));
    cTubes->AppendElement(cTubesItem, PR_FALSE);
  }

  callback->OnListTubesDone(cTubes);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeTubes::CallListTubes(csITpChannelTypeTubesListTubesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_tubes_call_list_tubes(m_Proxy, -1,
      cb? ListTubesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
OfferDBusTubeResponse(TpChannel *proxy,
    guint tube_id,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTubesOfferDBusTubeCB *callback = (csITpChannelTypeTubesOfferDBusTubeCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnOfferDBusTubeError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnOfferDBusTubeDone(tube_id);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeTubes::CallOfferDBusTube(const nsACString &aService, nsIArray *aParameters,
    csITpChannelTypeTubesOfferDBusTubeCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  char *cService = ToNewCString(aService);
  /* TODO */

  NS_IF_ADDREF(cb);
  tp_cli_channel_type_tubes_call_offer_d_bus_tube(m_Proxy, -1,
      cService, NULL,
      cb? OfferDBusTubeResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
OfferStreamTubeResponse(TpChannel *proxy,
    guint tube_id,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTubesOfferStreamTubeCB *callback = (csITpChannelTypeTubesOfferStreamTubeCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnOfferStreamTubeError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnOfferStreamTubeDone(tube_id);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeTubes::CallOfferStreamTube(const nsACString &aService, nsIArray *aParameters, PRUint32 aAddressType, nsIVariant *aAddress, PRUint32 aAccessControl, nsIVariant *aAccessControlParam,
    csITpChannelTypeTubesOfferStreamTubeCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  char *cService = ToNewCString(aService);
  /* TODO */
  GValue *cAddress = VariantToGValue(aAddress);
  GValue *cAccessControlParam = VariantToGValue(aAccessControlParam);

  NS_IF_ADDREF(cb);
  tp_cli_channel_type_tubes_call_offer_stream_tube(m_Proxy, -1,
      cService, NULL, aAddressType, cAddress, aAccessControl, cAccessControlParam,
      cb? OfferStreamTubeResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
NewTubeSignalCallback(TpChannel *proxy,
    guint id, guint initiator, guint type, const gchar *service, GHashTable *parameters, guint state,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeTubes *obj = (csTpChannelTypeTubes *)user_data;
  if (!obj)
    return;

  obj->HandleNewTube(id, initiator, type, service, parameters, state);
}


void
csTpChannelTypeTubes::HandleNewTube(guint id, guint initiator, guint type, const gchar *service, GHashTable *parameters, guint state)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_NewTubeObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeTubesNewTubeObserver> observer;

  nsCString cService = nsDependentCString(service);
  nsCOMPtr<nsIArray> cParameters;
  csTpStringVariantMap::Create((gpointer)parameters, getter_AddRefs(cParameters));

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_NewTubeObservers, i);
    observer->OnNewTube(id, initiator, type, cService, cParameters, state);
  }
}


NS_IMETHODIMP
csTpChannelTypeTubes::ConnectToNewTube(csITpChannelTypeTubesNewTubeObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_NewTubeObservers) {
    m_NewTubeObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_tubes_connect_to_new_tube(m_Proxy,
        NewTubeSignalCallback, this, NULL, NULL, NULL);
  }

  m_NewTubeObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeTubes::DisconnectFromNewTube(csITpChannelTypeTubesNewTubeObserver *observer)
{
  if (!m_NewTubeObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_NewTubeObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_NewTubeObservers->RemoveElementAt(idx);
}


static void
AcceptDBusTubeResponse(TpChannel *proxy,
    const gchar *address,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTubesAcceptDBusTubeCB *callback = (csITpChannelTypeTubesAcceptDBusTubeCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnAcceptDBusTubeError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCString cAddress = nsDependentCString(address);

  callback->OnAcceptDBusTubeDone(cAddress);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeTubes::CallAcceptDBusTube(PRUint32 aID,
    csITpChannelTypeTubesAcceptDBusTubeCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_tubes_call_accept_d_bus_tube(m_Proxy, -1,
      aID,
      cb? AcceptDBusTubeResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
AcceptStreamTubeResponse(TpChannel *proxy,
    const GValue *address,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTubesAcceptStreamTubeCB *callback = (csITpChannelTypeTubesAcceptStreamTubeCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnAcceptStreamTubeError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIVariant> cAddress;
  GValueToVariant(address, getter_AddRefs(cAddress));

  callback->OnAcceptStreamTubeDone(cAddress);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeTubes::CallAcceptStreamTube(PRUint32 aID, PRUint32 aAddressType, PRUint32 aAccessControl, nsIVariant *aAccessControlParam,
    csITpChannelTypeTubesAcceptStreamTubeCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GValue *cAccessControlParam = VariantToGValue(aAccessControlParam);

  NS_IF_ADDREF(cb);
  tp_cli_channel_type_tubes_call_accept_stream_tube(m_Proxy, -1,
      aID, aAddressType, aAccessControl, cAccessControlParam,
      cb? AcceptStreamTubeResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
TubeStateChangedSignalCallback(TpChannel *proxy,
    guint id, guint state,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeTubes *obj = (csTpChannelTypeTubes *)user_data;
  if (!obj)
    return;

  obj->HandleTubeStateChanged(id, state);
}


void
csTpChannelTypeTubes::HandleTubeStateChanged(guint id, guint state)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_TubeStateChangedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeTubesTubeStateChangedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_TubeStateChangedObservers, i);
    observer->OnTubeStateChanged(id, state);
  }
}


NS_IMETHODIMP
csTpChannelTypeTubes::ConnectToTubeStateChanged(csITpChannelTypeTubesTubeStateChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_TubeStateChangedObservers) {
    m_TubeStateChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_tubes_connect_to_tube_state_changed(m_Proxy,
        TubeStateChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_TubeStateChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeTubes::DisconnectFromTubeStateChanged(csITpChannelTypeTubesTubeStateChangedObserver *observer)
{
  if (!m_TubeStateChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_TubeStateChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_TubeStateChangedObservers->RemoveElementAt(idx);
}


static void
CloseTubeResponse(TpChannel *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTubesCloseTubeCB *callback = (csITpChannelTypeTubesCloseTubeCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnCloseTubeError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnCloseTubeDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeTubes::CallCloseTube(PRUint32 aID,
    csITpChannelTypeTubesCloseTubeCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_tubes_call_close_tube(m_Proxy, -1,
      aID,
      cb? CloseTubeResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
TubeClosedSignalCallback(TpChannel *proxy,
    guint id,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeTubes *obj = (csTpChannelTypeTubes *)user_data;
  if (!obj)
    return;

  obj->HandleTubeClosed(id);
}


void
csTpChannelTypeTubes::HandleTubeClosed(guint id)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_TubeClosedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeTubesTubeClosedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_TubeClosedObservers, i);
    observer->OnTubeClosed(id);
  }
}


NS_IMETHODIMP
csTpChannelTypeTubes::ConnectToTubeClosed(csITpChannelTypeTubesTubeClosedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_TubeClosedObservers) {
    m_TubeClosedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_tubes_connect_to_tube_closed(m_Proxy,
        TubeClosedSignalCallback, this, NULL, NULL, NULL);
  }

  m_TubeClosedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeTubes::DisconnectFromTubeClosed(csITpChannelTypeTubesTubeClosedObserver *observer)
{
  if (!m_TubeClosedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_TubeClosedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_TubeClosedObservers->RemoveElementAt(idx);
}


static void
GetDBusTubeAddressResponse(TpChannel *proxy,
    const gchar *address,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTubesGetDBusTubeAddressCB *callback = (csITpChannelTypeTubesGetDBusTubeAddressCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetDBusTubeAddressError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCString cAddress = nsDependentCString(address);

  callback->OnGetDBusTubeAddressDone(cAddress);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeTubes::CallGetDBusTubeAddress(PRUint32 aID,
    csITpChannelTypeTubesGetDBusTubeAddressCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_tubes_call_get_d_bus_tube_address(m_Proxy, -1,
      aID,
      cb? GetDBusTubeAddressResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetDBusNamesResponse(TpChannel *proxy,
    const GPtrArray *dbus_names,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTubesGetDBusNamesCB *callback = (csITpChannelTypeTubesGetDBusNamesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetDBusNamesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIMutableArray> cDBusNames = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)dbus_names)->len; i++) {
    gpointer dbus_names_item = g_ptr_array_index((GPtrArray*)dbus_names, i);
    nsCOMPtr<csITpDBusTubeMember> cDBusNamesItem;
    csTpDBusTubeMember::Create((gpointer)dbus_names_item, getter_AddRefs(cDBusNamesItem));
    cDBusNames->AppendElement(cDBusNamesItem, PR_FALSE);
  }

  callback->OnGetDBusNamesDone(cDBusNames);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeTubes::CallGetDBusNames(PRUint32 aID,
    csITpChannelTypeTubesGetDBusNamesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_tubes_call_get_d_bus_names(m_Proxy, -1,
      aID,
      cb? GetDBusNamesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
DBusNamesChangedSignalCallback(TpChannel *proxy,
    guint id, const GPtrArray *added, const GArray *removed,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeTubes *obj = (csTpChannelTypeTubes *)user_data;
  if (!obj)
    return;

  obj->HandleDBusNamesChanged(id, added, removed);
}


void
csTpChannelTypeTubes::HandleDBusNamesChanged(guint id, const GPtrArray *added, const GArray *removed)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_DBusNamesChangedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeTubesDBusNamesChangedObserver> observer;

  nsCOMPtr<nsIMutableArray> cAdded = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)added)->len; i++) {
    gpointer added_item = g_ptr_array_index((GPtrArray*)added, i);
    nsCOMPtr<csITpDBusTubeMember> cAddedItem;
    csTpDBusTubeMember::Create((gpointer)added_item, getter_AddRefs(cAddedItem));
    cAdded->AppendElement(cAddedItem, PR_FALSE);
  }
  PRUint32 cRemovedCount = removed->len;
  PRUint32 *cRemoved = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cRemovedCount);
  for (unsigned int i=0; i<cRemovedCount; i++)
    cRemoved[i] = g_array_index(removed, guint, i);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_DBusNamesChangedObservers, i);
    observer->OnDBusNamesChanged(id, cAdded, cRemovedCount, cRemoved);
  }
}


NS_IMETHODIMP
csTpChannelTypeTubes::ConnectToDBusNamesChanged(csITpChannelTypeTubesDBusNamesChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_DBusNamesChangedObservers) {
    m_DBusNamesChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_tubes_connect_to_d_bus_names_changed(m_Proxy,
        DBusNamesChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_DBusNamesChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeTubes::DisconnectFromDBusNamesChanged(csITpChannelTypeTubesDBusNamesChangedObserver *observer)
{
  if (!m_DBusNamesChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_DBusNamesChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_DBusNamesChangedObservers->RemoveElementAt(idx);
}


static void
GetStreamTubeSocketAddressResponse(TpChannel *proxy,
    guint address_type, const GValue *address,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTubesGetStreamTubeSocketAddressCB *callback = (csITpChannelTypeTubesGetStreamTubeSocketAddressCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetStreamTubeSocketAddressError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIVariant> cAddress;
  GValueToVariant(address, getter_AddRefs(cAddress));

  callback->OnGetStreamTubeSocketAddressDone(address_type, cAddress);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeTubes::CallGetStreamTubeSocketAddress(PRUint32 aID,
    csITpChannelTypeTubesGetStreamTubeSocketAddressCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_tubes_call_get_stream_tube_socket_address(m_Proxy, -1,
      aID,
      cb? GetStreamTubeSocketAddressResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
StreamTubeNewConnectionSignalCallback(TpChannel *proxy,
    guint id, guint handle,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeTubes *obj = (csTpChannelTypeTubes *)user_data;
  if (!obj)
    return;

  obj->HandleStreamTubeNewConnection(id, handle);
}


void
csTpChannelTypeTubes::HandleStreamTubeNewConnection(guint id, guint handle)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_StreamTubeNewConnectionObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeTubesStreamTubeNewConnectionObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_StreamTubeNewConnectionObservers, i);
    observer->OnStreamTubeNewConnection(id, handle);
  }
}


NS_IMETHODIMP
csTpChannelTypeTubes::ConnectToStreamTubeNewConnection(csITpChannelTypeTubesStreamTubeNewConnectionObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_StreamTubeNewConnectionObservers) {
    m_StreamTubeNewConnectionObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_tubes_connect_to_stream_tube_new_connection(m_Proxy,
        StreamTubeNewConnectionSignalCallback, this, NULL, NULL, NULL);
  }

  m_StreamTubeNewConnectionObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeTubes::DisconnectFromStreamTubeNewConnection(csITpChannelTypeTubesStreamTubeNewConnectionObserver *observer)
{
  if (!m_StreamTubeNewConnectionObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_StreamTubeNewConnectionObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_StreamTubeNewConnectionObservers->RemoveElementAt(idx);
}



csTpChannelTypeTubes::csTpChannelTypeTubes()
{}

csTpChannelTypeTubes::~csTpChannelTypeTubes()
{}
