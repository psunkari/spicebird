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


#include "csTpConnection.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpChannelInfo
 */

NS_IMPL_ISUPPORTS1(csTpChannelInfo, csITpChannelInfo)

NS_METHOD
csTpChannelInfo::Create(const nsCString &aChannel, const nsCString &aChannelType, PRUint32 aHandleType, PRUint32 aHandle, void **aResult)
{
  csITpChannelInfo *it = 
          new csTpChannelInfo(aChannel, aChannelType, aHandleType, aHandle);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpChannelInfo), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpChannelInfo::Create(gpointer aGLibItem, void **aResult)
{
  const gchar *channel;
  const gchar *channel_type;
  guint handle_type;
  guint handle;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_CHANNEL_INFO);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &channel, 1, &channel_type, 2, &handle_type, 3, &handle,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cChannel = nsDependentCString(channel);
  nsCString cChannelType = nsDependentCString(channel_type);
  csITpChannelInfo *it = new csTpChannelInfo(cChannel, cChannelType, handle_type, handle);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpChannelInfo), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpChannelInfo::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpChannelInfo::csTpChannelInfo(const nsCString &aChannel, const nsCString &aChannelType, PRUint32 aHandleType, PRUint32 aHandle)
{
  m_Channel.Assign(aChannel);
  m_ChannelType.Assign(aChannelType);
  m_HandleType = aHandleType;
  m_Handle = aHandle;
}

csTpChannelInfo::~csTpChannelInfo()
{}

NS_IMETHODIMP
csTpChannelInfo::GetChannel(nsACString &aChannel)
{
  aChannel.Assign(m_Channel);
  return NS_OK;
}

NS_IMETHODIMP
csTpChannelInfo::GetChannelType(nsACString &aChannelType)
{
  aChannelType.Assign(m_ChannelType);
  return NS_OK;
}

NS_IMETHODIMP
csTpChannelInfo::GetHandleType(PRUint32 *aHandleType)
{
  *aHandleType = m_HandleType;
  return NS_OK;
}

NS_IMETHODIMP
csTpChannelInfo::GetHandle(PRUint32 *aHandle)
{
  *aHandle = m_Handle;
  return NS_OK;
}

static void
ConnectResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionConnectCB *callback = (csITpConnectionConnectCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnConnectError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnConnectDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnection::CallConnect(csITpConnectionConnectCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_call_connect(m_Proxy, -1,
      cb? ConnectResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
DisconnectResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionDisconnectCB *callback = (csITpConnectionDisconnectCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnDisconnectError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnDisconnectDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnection::CallDisconnect(csITpConnectionDisconnectCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_call_disconnect(m_Proxy, -1,
      cb? DisconnectResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetInterfacesResponse(TpConnection *proxy,
    const gchar **interfaces,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionGetInterfacesCB *callback = (csITpConnectionGetInterfacesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetInterfacesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cInterfacesCount = 0;
  for (char **pos = (char**)interfaces; *pos; pos++, cInterfacesCount++);
  char **cInterfaces = (char **)nsMemory::Alloc(cInterfacesCount * sizeof(char*));
  for (PRUint32 i=0; i<cInterfacesCount; i++)
    cInterfaces[i] = (char *)nsMemory::Clone(interfaces[i], strlen(interfaces[i]) + 1);

  callback->OnGetInterfacesDone(cInterfacesCount, (const char **)cInterfaces);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnection::CallGetInterfaces(csITpConnectionGetInterfacesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_call_get_interfaces(m_Proxy, -1,
      cb? GetInterfacesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetProtocolResponse(TpConnection *proxy,
    const gchar *protocol,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionGetProtocolCB *callback = (csITpConnectionGetProtocolCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetProtocolError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCString cProtocol = nsDependentCString(protocol);

  callback->OnGetProtocolDone(cProtocol);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnection::CallGetProtocol(csITpConnectionGetProtocolCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_call_get_protocol(m_Proxy, -1,
      cb? GetProtocolResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
SelfHandleChangedSignalCallback(TpConnection *proxy,
    guint self_handle,
    gpointer user_data, GObject *weak_object)
{
  csTpConnection *obj = (csTpConnection *)user_data;
  if (!obj)
    return;

  obj->HandleSelfHandleChanged(self_handle);
}


void
csTpConnection::HandleSelfHandleChanged(guint self_handle)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_SelfHandleChangedObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionSelfHandleChangedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_SelfHandleChangedObservers, i);
    observer->OnSelfHandleChanged(self_handle);
  }
}


NS_IMETHODIMP
csTpConnection::ConnectToSelfHandleChanged(csITpConnectionSelfHandleChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_SelfHandleChangedObservers) {
    m_SelfHandleChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_connect_to_self_handle_changed(m_Proxy,
        SelfHandleChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_SelfHandleChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnection::DisconnectFromSelfHandleChanged(csITpConnectionSelfHandleChangedObserver *observer)
{
  if (!m_SelfHandleChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_SelfHandleChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_SelfHandleChangedObservers->RemoveElementAt(idx);
}


static void
SelfHandleResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionSelfHandleCB *callback = (csITpConnectionSelfHandleCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertySelfHandleError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  selfhandle;

  callback->GetPropertySelfHandleDone(selfhandle);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnection::GetPropertySelfHandle(csITpConnectionSelfHandleCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection",
      "SelfHandle",
      cb? SelfHandleResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetSelfHandleResponse(TpConnection *proxy,
    guint self_handle,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionGetSelfHandleCB *callback = (csITpConnectionGetSelfHandleCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetSelfHandleError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnGetSelfHandleDone(self_handle);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnection::CallGetSelfHandle(csITpConnectionGetSelfHandleCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_call_get_self_handle(m_Proxy, -1,
      cb? GetSelfHandleResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetStatusResponse(TpConnection *proxy,
    guint status,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionGetStatusCB *callback = (csITpConnectionGetStatusCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetStatusError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnGetStatusDone(status);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnection::CallGetStatus(csITpConnectionGetStatusCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_call_get_status(m_Proxy, -1,
      cb? GetStatusResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
HoldHandlesResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionHoldHandlesCB *callback = (csITpConnectionHoldHandlesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnHoldHandlesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnHoldHandlesDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnection::CallHoldHandles(PRUint32 aHandleType, PRUint32 aHandlesCount, PRUint32 *aHandles,
    csITpConnectionHoldHandlesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cHandles = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aHandlesCount; i++)
    g_array_append_val(cHandles, aHandles[i]);

  NS_IF_ADDREF(cb);
  tp_cli_connection_call_hold_handles(m_Proxy, -1,
      aHandleType, cHandles,
      cb? HoldHandlesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
InspectHandlesResponse(TpConnection *proxy,
    const gchar **identifiers,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInspectHandlesCB *callback = (csITpConnectionInspectHandlesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnInspectHandlesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cIdentifiersCount = 0;
  for (char **pos = (char**)identifiers; *pos; pos++, cIdentifiersCount++);
  char **cIdentifiers = (char **)nsMemory::Alloc(cIdentifiersCount * sizeof(char*));
  for (PRUint32 i=0; i<cIdentifiersCount; i++)
    cIdentifiers[i] = (char *)nsMemory::Clone(identifiers[i], strlen(identifiers[i]) + 1);

  callback->OnInspectHandlesDone(cIdentifiersCount, (const char **)cIdentifiers);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnection::CallInspectHandles(PRUint32 aHandleType, PRUint32 aHandlesCount, PRUint32 *aHandles,
    csITpConnectionInspectHandlesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cHandles = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aHandlesCount; i++)
    g_array_append_val(cHandles, aHandles[i]);

  NS_IF_ADDREF(cb);
  tp_cli_connection_call_inspect_handles(m_Proxy, -1,
      aHandleType, cHandles,
      cb? InspectHandlesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ListChannelsResponse(TpConnection *proxy,
    const GPtrArray *channel_info,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionListChannelsCB *callback = (csITpConnectionListChannelsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnListChannelsError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIMutableArray> cChannelInfo = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)channel_info)->len; i++) {
    gpointer channel_info_item = g_ptr_array_index((GPtrArray*)channel_info, i);
    nsCOMPtr<csITpChannelInfo> cChannelInfoItem;
    csTpChannelInfo::Create((gpointer)channel_info_item, getter_AddRefs(cChannelInfoItem));
    cChannelInfo->AppendElement(cChannelInfoItem, PR_FALSE);
  }

  callback->OnListChannelsDone(cChannelInfo);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnection::CallListChannels(csITpConnectionListChannelsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_call_list_channels(m_Proxy, -1,
      cb? ListChannelsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
NewChannelSignalCallback(TpConnection *proxy,
    const gchar *object_path, const gchar *channel_type, guint handle_type, guint handle, gboolean suppress_handler,
    gpointer user_data, GObject *weak_object)
{
  csTpConnection *obj = (csTpConnection *)user_data;
  if (!obj)
    return;

  obj->HandleNewChannel(object_path, channel_type, handle_type, handle, suppress_handler);
}


void
csTpConnection::HandleNewChannel(const gchar *object_path, const gchar *channel_type, guint handle_type, guint handle, gboolean suppress_handler)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_NewChannelObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionNewChannelObserver> observer;

  nsCString cObjectPath = nsDependentCString(object_path);
  nsCString cChannelType = nsDependentCString(channel_type);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_NewChannelObservers, i);
    observer->OnNewChannel(cObjectPath, cChannelType, handle_type, handle, suppress_handler);
  }
}


NS_IMETHODIMP
csTpConnection::ConnectToNewChannel(csITpConnectionNewChannelObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_NewChannelObservers) {
    m_NewChannelObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_connect_to_new_channel(m_Proxy,
        NewChannelSignalCallback, this, NULL, NULL, NULL);
  }

  m_NewChannelObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnection::DisconnectFromNewChannel(csITpConnectionNewChannelObserver *observer)
{
  if (!m_NewChannelObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_NewChannelObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_NewChannelObservers->RemoveElementAt(idx);
}


static void
ReleaseHandlesResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionReleaseHandlesCB *callback = (csITpConnectionReleaseHandlesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnReleaseHandlesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnReleaseHandlesDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnection::CallReleaseHandles(PRUint32 aHandleType, PRUint32 aHandlesCount, PRUint32 *aHandles,
    csITpConnectionReleaseHandlesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cHandles = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aHandlesCount; i++)
    g_array_append_val(cHandles, aHandles[i]);

  NS_IF_ADDREF(cb);
  tp_cli_connection_call_release_handles(m_Proxy, -1,
      aHandleType, cHandles,
      cb? ReleaseHandlesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RequestChannelResponse(TpConnection *proxy,
    const gchar *object_path,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionRequestChannelCB *callback = (csITpConnectionRequestChannelCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnRequestChannelError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCString cObjectPath = nsDependentCString(object_path);

  callback->OnRequestChannelDone(cObjectPath);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnection::CallRequestChannel(const nsACString &aType, PRUint32 aHandleType, PRUint32 aHandle, PRBool aSuppressHandler,
    csITpConnectionRequestChannelCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  char *cType = ToNewCString(aType);

  NS_IF_ADDREF(cb);
  tp_cli_connection_call_request_channel(m_Proxy, -1,
      cType, aHandleType, aHandle, aSuppressHandler,
      cb? RequestChannelResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RequestHandlesResponse(TpConnection *proxy,
    const GArray *handles,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionRequestHandlesCB *callback = (csITpConnectionRequestHandlesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnRequestHandlesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cHandlesCount = handles->len;
  PRUint32 *cHandles = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cHandlesCount);
  for (unsigned int i=0; i<cHandlesCount; i++)
    cHandles[i] = g_array_index(handles, guint, i);

  callback->OnRequestHandlesDone(cHandlesCount, cHandles);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnection::CallRequestHandles(PRUint32 aHandleType, PRUint32 aIdentifiersCount, const char **aIdentifiers,
    csITpConnectionRequestHandlesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  char **cIdentifiers = (char **)nsMemory::Alloc((aIdentifiersCount + 1) * sizeof(char*));
  for (PRUint32 i=0; i<aIdentifiersCount; i++)
    cIdentifiers[i] = (char *)nsMemory::Clone(aIdentifiers[i], strlen(aIdentifiers[i]) + 1);
  cIdentifiers[aIdentifiersCount] = NULL;

  NS_IF_ADDREF(cb);
  tp_cli_connection_call_request_handles(m_Proxy, -1,
      aHandleType, (const char**) cIdentifiers,
      cb? RequestHandlesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ConnectionErrorSignalCallback(TpConnection *proxy,
    const gchar *error, GHashTable *details,
    gpointer user_data, GObject *weak_object)
{
  csTpConnection *obj = (csTpConnection *)user_data;
  if (!obj)
    return;

  obj->HandleConnectionError(error, details);
}


void
csTpConnection::HandleConnectionError(const gchar *error, GHashTable *details)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_ConnectionErrorObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionConnectionErrorObserver> observer;

  nsCString cError = nsDependentCString(error);
  nsCOMPtr<nsIArray> cDetails;
  csTpStringVariantMap::Create((gpointer)details, getter_AddRefs(cDetails));

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_ConnectionErrorObservers, i);
    observer->OnConnectionError(cError, cDetails);
  }
}


NS_IMETHODIMP
csTpConnection::ConnectToConnectionError(csITpConnectionConnectionErrorObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_ConnectionErrorObservers) {
    m_ConnectionErrorObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_connect_to_connection_error(m_Proxy,
        ConnectionErrorSignalCallback, this, NULL, NULL, NULL);
  }

  m_ConnectionErrorObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnection::DisconnectFromConnectionError(csITpConnectionConnectionErrorObserver *observer)
{
  if (!m_ConnectionErrorObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_ConnectionErrorObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_ConnectionErrorObservers->RemoveElementAt(idx);
}


static void
StatusChangedSignalCallback(TpConnection *proxy,
    guint status, guint reason,
    gpointer user_data, GObject *weak_object)
{
  csTpConnection *obj = (csTpConnection *)user_data;
  if (!obj)
    return;

  obj->HandleStatusChanged(status, reason);
}


void
csTpConnection::HandleStatusChanged(guint status, guint reason)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_StatusChangedObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionStatusChangedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_StatusChangedObservers, i);
    observer->OnStatusChanged(status, reason);
  }
}


NS_IMETHODIMP
csTpConnection::ConnectToStatusChanged(csITpConnectionStatusChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_StatusChangedObservers) {
    m_StatusChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_connect_to_status_changed(m_Proxy,
        StatusChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_StatusChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnection::DisconnectFromStatusChanged(csITpConnectionStatusChangedObserver *observer)
{
  if (!m_StatusChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_StatusChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_StatusChangedObservers->RemoveElementAt(idx);
}



csTpConnection::csTpConnection()
{}

csTpConnection::~csTpConnection()
{}
