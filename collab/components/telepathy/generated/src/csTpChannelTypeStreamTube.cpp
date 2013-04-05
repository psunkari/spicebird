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


#include "csTpChannelTypeStreamTube.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
#include "csTpChannelTypeTubes.h"
static void
OfferResponse(TpChannel *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeStreamTubeOfferCB *callback = (csITpChannelTypeStreamTubeOfferCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnOfferError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnOfferDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeStreamTube::CallOffer(PRUint32 aaddresstype, nsIVariant *aaddress, PRUint32 aaccesscontrol, nsIArray *aparameters,
    csITpChannelTypeStreamTubeOfferCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GValue *caddress = VariantToGValue(aaddress);
  /* TODO */

  NS_IF_ADDREF(cb);
  tp_cli_channel_type_stream_tube_call_offer(m_Proxy, -1,
      aaddresstype, caddress, aaccesscontrol, NULL,
      cb? OfferResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
AcceptResponse(TpChannel *proxy,
    const GValue *address,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeStreamTubeAcceptCB *callback = (csITpChannelTypeStreamTubeAcceptCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnAcceptError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIVariant> caddress;
  GValueToVariant(address, getter_AddRefs(caddress));

  callback->OnAcceptDone(caddress);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeStreamTube::CallAccept(PRUint32 aaddresstype, PRUint32 aaccesscontrol, nsIVariant *aaccesscontrolparam,
    csITpChannelTypeStreamTubeAcceptCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GValue *caccesscontrolparam = VariantToGValue(aaccesscontrolparam);

  NS_IF_ADDREF(cb);
  tp_cli_channel_type_stream_tube_call_accept(m_Proxy, -1,
      aaddresstype, aaccesscontrol, caccesscontrolparam,
      cb? AcceptResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
NewRemoteConnectionSignalCallback(TpChannel *proxy,
    guint handle, const GValue *connection_param, guint connection_id,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeStreamTube *obj = (csTpChannelTypeStreamTube *)user_data;
  if (!obj)
    return;

  obj->HandleNewRemoteConnection(handle, connection_param, connection_id);
}


void
csTpChannelTypeStreamTube::HandleNewRemoteConnection(guint handle, const GValue *connection_param, guint connection_id)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_NewRemoteConnectionObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeStreamTubeNewRemoteConnectionObserver> observer;

  nsCOMPtr<nsIVariant> cConnectionParam;
  GValueToVariant(connection_param, getter_AddRefs(cConnectionParam));

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_NewRemoteConnectionObservers, i);
    observer->OnNewRemoteConnection(handle, cConnectionParam, connection_id);
  }
}


NS_IMETHODIMP
csTpChannelTypeStreamTube::ConnectToNewRemoteConnection(csITpChannelTypeStreamTubeNewRemoteConnectionObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_NewRemoteConnectionObservers) {
    m_NewRemoteConnectionObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_stream_tube_connect_to_new_remote_connection(m_Proxy,
        NewRemoteConnectionSignalCallback, this, NULL, NULL, NULL);
  }

  m_NewRemoteConnectionObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeStreamTube::DisconnectFromNewRemoteConnection(csITpChannelTypeStreamTubeNewRemoteConnectionObserver *observer)
{
  if (!m_NewRemoteConnectionObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_NewRemoteConnectionObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_NewRemoteConnectionObservers->RemoveElementAt(idx);
}


static void
NewLocalConnectionSignalCallback(TpChannel *proxy,
    guint connection_id,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeStreamTube *obj = (csTpChannelTypeStreamTube *)user_data;
  if (!obj)
    return;

  obj->HandleNewLocalConnection(connection_id);
}


void
csTpChannelTypeStreamTube::HandleNewLocalConnection(guint connection_id)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_NewLocalConnectionObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeStreamTubeNewLocalConnectionObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_NewLocalConnectionObservers, i);
    observer->OnNewLocalConnection(connection_id);
  }
}


NS_IMETHODIMP
csTpChannelTypeStreamTube::ConnectToNewLocalConnection(csITpChannelTypeStreamTubeNewLocalConnectionObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_NewLocalConnectionObservers) {
    m_NewLocalConnectionObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_stream_tube_connect_to_new_local_connection(m_Proxy,
        NewLocalConnectionSignalCallback, this, NULL, NULL, NULL);
  }

  m_NewLocalConnectionObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeStreamTube::DisconnectFromNewLocalConnection(csITpChannelTypeStreamTubeNewLocalConnectionObserver *observer)
{
  if (!m_NewLocalConnectionObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_NewLocalConnectionObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_NewLocalConnectionObservers->RemoveElementAt(idx);
}


static void
ConnectionClosedSignalCallback(TpChannel *proxy,
    guint connection_id, const gchar *error, const gchar *message,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeStreamTube *obj = (csTpChannelTypeStreamTube *)user_data;
  if (!obj)
    return;

  obj->HandleConnectionClosed(connection_id, error, message);
}


void
csTpChannelTypeStreamTube::HandleConnectionClosed(guint connection_id, const gchar *error, const gchar *message)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_ConnectionClosedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeStreamTubeConnectionClosedObserver> observer;

  nsCString cError = nsDependentCString(error);
  nsCString cMessage = nsDependentCString(message);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_ConnectionClosedObservers, i);
    observer->OnConnectionClosed(connection_id, cError, cMessage);
  }
}


NS_IMETHODIMP
csTpChannelTypeStreamTube::ConnectToConnectionClosed(csITpChannelTypeStreamTubeConnectionClosedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_ConnectionClosedObservers) {
    m_ConnectionClosedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_stream_tube_connect_to_connection_closed(m_Proxy,
        ConnectionClosedSignalCallback, this, NULL, NULL, NULL);
  }

  m_ConnectionClosedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeStreamTube::DisconnectFromConnectionClosed(csITpChannelTypeStreamTubeConnectionClosedObserver *observer)
{
  if (!m_ConnectionClosedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_ConnectionClosedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_ConnectionClosedObservers->RemoveElementAt(idx);
}


static void
ServiceResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeStreamTubeServiceCB *callback = (csITpChannelTypeStreamTubeServiceCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyServiceError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar * service;
  nsCString cService = nsDependentCString(service);

  callback->GetPropertyServiceDone(cService);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeStreamTube::GetPropertyService(csITpChannelTypeStreamTubeServiceCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.StreamTube",
      "Service",
      cb? ServiceResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
SupportedSocketTypesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeStreamTubeSupportedSocketTypesCB *callback = (csITpChannelTypeStreamTubeSupportedSocketTypesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertySupportedSocketTypesError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GHashTable * supportedsockettypes;
  supportedsockettypes = (GHashTable *)g_value_get_boxed(out);
  nsCOMPtr<nsIArray> cSupportedSocketTypes;
  csTpSupportedSocketMap::Create((gpointer)supportedsockettypes, getter_AddRefs(cSupportedSocketTypes));

  callback->GetPropertySupportedSocketTypesDone(cSupportedSocketTypes);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeStreamTube::GetPropertySupportedSocketTypes(csITpChannelTypeStreamTubeSupportedSocketTypesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.StreamTube",
      "SupportedSocketTypes",
      cb? SupportedSocketTypesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpChannelTypeStreamTube::csTpChannelTypeStreamTube()
{}

csTpChannelTypeStreamTube::~csTpChannelTypeStreamTube()
{}
