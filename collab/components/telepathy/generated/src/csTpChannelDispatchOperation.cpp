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


#include "csTpChannelDispatchOperation.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
#include "csTpConnectionInterfaceRequests.h"
static void
InterfacesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelDispatchOperationInterfacesCB *callback = (csITpChannelDispatchOperationInterfacesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyInterfacesError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar ** interfaces;
  interfaces = (gchar **)g_value_get_boxed(out);
  PRUint32 cInterfacesCount = 0;
  for (char **pos = (char**)interfaces; *pos; pos++, cInterfacesCount++);
  char **cInterfaces = (char **)nsMemory::Alloc(cInterfacesCount * sizeof(char*));
  for (PRUint32 i=0; i<cInterfacesCount; i++)
    cInterfaces[i] = (char *)nsMemory::Clone(interfaces[i], strlen(interfaces[i]) + 1);

  callback->GetPropertyInterfacesDone(cInterfacesCount, (const char **)cInterfaces);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelDispatchOperation::GetPropertyInterfaces(csITpChannelDispatchOperationInterfacesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.ChannelDispatchOperation",
      "Interfaces",
      cb? InterfacesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ConnectionResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelDispatchOperationConnectionCB *callback = (csITpChannelDispatchOperationConnectionCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyConnectionError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar * connection;
  connection = (gchar *)g_value_get_boxed(out);
  nsCString cConnection = nsDependentCString(connection);

  callback->GetPropertyConnectionDone(cConnection);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelDispatchOperation::GetPropertyConnection(csITpChannelDispatchOperationConnectionCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.ChannelDispatchOperation",
      "Connection",
      cb? ConnectionResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
AccountResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelDispatchOperationAccountCB *callback = (csITpChannelDispatchOperationAccountCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyAccountError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar * account;
  account = (gchar *)g_value_get_boxed(out);
  nsCString cAccount = nsDependentCString(account);

  callback->GetPropertyAccountDone(cAccount);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelDispatchOperation::GetPropertyAccount(csITpChannelDispatchOperationAccountCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.ChannelDispatchOperation",
      "Account",
      cb? AccountResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ChannelsResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelDispatchOperationChannelsCB *callback = (csITpChannelDispatchOperationChannelsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyChannelsError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GPtrArray * channels;
  channels = (GPtrArray *)g_value_get_boxed(out);
  nsCOMPtr<nsIMutableArray> cChannels = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)channels)->len; i++) {
    gpointer channels_item = g_ptr_array_index((GPtrArray*)channels, i);
    nsCOMPtr<csITpChannelDetails> cChannelsItem;
    csTpChannelDetails::Create((gpointer)channels_item, getter_AddRefs(cChannelsItem));
    cChannels->AppendElement(cChannelsItem, PR_FALSE);
  }

  callback->GetPropertyChannelsDone(cChannels);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelDispatchOperation::GetPropertyChannels(csITpChannelDispatchOperationChannelsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.ChannelDispatchOperation",
      "Channels",
      cb? ChannelsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ChannelLostSignalCallback(TpChannelDispatchOperation *proxy,
    const gchar *channel, const gchar *error, const gchar *message,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelDispatchOperation *obj = (csTpChannelDispatchOperation *)user_data;
  if (!obj)
    return;

  obj->HandleChannelLost(channel, error, message);
}


void
csTpChannelDispatchOperation::HandleChannelLost(const gchar *channel, const gchar *error, const gchar *message)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_ChannelLostObservers->GetLength(&length);
  nsCOMPtr<csITpChannelDispatchOperationChannelLostObserver> observer;

  nsCString cChannel = nsDependentCString(channel);
  nsCString cError = nsDependentCString(error);
  nsCString cMessage = nsDependentCString(message);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_ChannelLostObservers, i);
    observer->OnChannelLost(cChannel, cError, cMessage);
  }
}


NS_IMETHODIMP
csTpChannelDispatchOperation::ConnectToChannelLost(csITpChannelDispatchOperationChannelLostObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_ChannelLostObservers) {
    m_ChannelLostObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_dispatch_operation_connect_to_channel_lost(m_Proxy,
        ChannelLostSignalCallback, this, NULL, NULL, NULL);
  }

  m_ChannelLostObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelDispatchOperation::DisconnectFromChannelLost(csITpChannelDispatchOperationChannelLostObserver *observer)
{
  if (!m_ChannelLostObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_ChannelLostObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_ChannelLostObservers->RemoveElementAt(idx);
}


static void
PossibleHandlersResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelDispatchOperationPossibleHandlersCB *callback = (csITpChannelDispatchOperationPossibleHandlersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyPossibleHandlersError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar ** possiblehandlers;
  possiblehandlers = (gchar **)g_value_get_boxed(out);
  PRUint32 cPossibleHandlersCount = 0;
  for (char **pos = (char**)possiblehandlers; *pos; pos++, cPossibleHandlersCount++);
  char **cPossibleHandlers = (char **)nsMemory::Alloc(cPossibleHandlersCount * sizeof(char*));
  for (PRUint32 i=0; i<cPossibleHandlersCount; i++)
    cPossibleHandlers[i] = (char *)nsMemory::Clone(possiblehandlers[i], strlen(possiblehandlers[i]) + 1);

  callback->GetPropertyPossibleHandlersDone(cPossibleHandlersCount, (const char **)cPossibleHandlers);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelDispatchOperation::GetPropertyPossibleHandlers(csITpChannelDispatchOperationPossibleHandlersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.ChannelDispatchOperation",
      "PossibleHandlers",
      cb? PossibleHandlersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
HandleWithResponse(TpChannelDispatchOperation *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelDispatchOperationHandleWithCB *callback = (csITpChannelDispatchOperationHandleWithCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnHandleWithError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnHandleWithDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelDispatchOperation::CallHandleWith(const nsACString &aHandler,
    csITpChannelDispatchOperationHandleWithCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  char *cHandler = ToNewCString(aHandler);

  NS_IF_ADDREF(cb);
  tp_cli_channel_dispatch_operation_call_handle_with(m_Proxy, -1,
      cHandler,
      cb? HandleWithResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ClaimResponse(TpChannelDispatchOperation *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelDispatchOperationClaimCB *callback = (csITpChannelDispatchOperationClaimCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnClaimError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnClaimDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelDispatchOperation::CallClaim(csITpChannelDispatchOperationClaimCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_dispatch_operation_call_claim(m_Proxy, -1,
      cb? ClaimResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
FinishedSignalCallback(TpChannelDispatchOperation *proxy,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelDispatchOperation *obj = (csTpChannelDispatchOperation *)user_data;
  if (!obj)
    return;

  obj->HandleFinished();
}


void
csTpChannelDispatchOperation::HandleFinished()
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_FinishedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelDispatchOperationFinishedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_FinishedObservers, i);
    observer->OnFinished();
  }
}


NS_IMETHODIMP
csTpChannelDispatchOperation::ConnectToFinished(csITpChannelDispatchOperationFinishedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_FinishedObservers) {
    m_FinishedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_dispatch_operation_connect_to_finished(m_Proxy,
        FinishedSignalCallback, this, NULL, NULL, NULL);
  }

  m_FinishedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelDispatchOperation::DisconnectFromFinished(csITpChannelDispatchOperationFinishedObserver *observer)
{
  if (!m_FinishedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_FinishedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_FinishedObservers->RemoveElementAt(idx);
}



csTpChannelDispatchOperation::csTpChannelDispatchOperation()
{}

csTpChannelDispatchOperation::~csTpChannelDispatchOperation()
{}
