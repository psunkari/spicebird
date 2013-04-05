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


#include "csTpChannelRequest.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
static void
AccountResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelRequestAccountCB *callback = (csITpChannelRequestAccountCB *)user_data;
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
csTpChannelRequest::GetPropertyAccount(csITpChannelRequestAccountCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.ChannelRequest",
      "Account",
      cb? AccountResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
UserActionTimeResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelRequestUserActionTimeCB *callback = (csITpChannelRequestUserActionTimeCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyUserActionTimeError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gint64  useractiontime;

  callback->GetPropertyUserActionTimeDone(useractiontime);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelRequest::GetPropertyUserActionTime(csITpChannelRequestUserActionTimeCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.ChannelRequest",
      "UserActionTime",
      cb? UserActionTimeResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
PreferredHandlerResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelRequestPreferredHandlerCB *callback = (csITpChannelRequestPreferredHandlerCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyPreferredHandlerError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar * preferredhandler;
  nsCString cPreferredHandler = nsDependentCString(preferredhandler);

  callback->GetPropertyPreferredHandlerDone(cPreferredHandler);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelRequest::GetPropertyPreferredHandler(csITpChannelRequestPreferredHandlerCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.ChannelRequest",
      "PreferredHandler",
      cb? PreferredHandlerResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RequestsResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelRequestRequestsCB *callback = (csITpChannelRequestRequestsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyRequestsError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GPtrArray * requests;
  requests = (GPtrArray *)g_value_get_boxed(out);
  nsCOMPtr<nsIMutableArray> cRequests = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)requests)->len; i++) {
    gpointer requests_item = g_ptr_array_index((GPtrArray*)requests, i);
    nsCOMPtr<nsIArray> cRequestsItem;
    csTpQualifiedPropertyValueMap::Create((gpointer)requests_item, getter_AddRefs(cRequestsItem));
    cRequests->AppendElement(cRequestsItem, PR_FALSE);
  }

  callback->GetPropertyRequestsDone(cRequests);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelRequest::GetPropertyRequests(csITpChannelRequestRequestsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.ChannelRequest",
      "Requests",
      cb? RequestsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
InterfacesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelRequestInterfacesCB *callback = (csITpChannelRequestInterfacesCB *)user_data;
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
csTpChannelRequest::GetPropertyInterfaces(csITpChannelRequestInterfacesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.ChannelRequest",
      "Interfaces",
      cb? InterfacesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ProceedResponse(TpChannelRequest *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelRequestProceedCB *callback = (csITpChannelRequestProceedCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnProceedError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnProceedDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelRequest::CallProceed(csITpChannelRequestProceedCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_request_call_proceed(m_Proxy, -1,
      cb? ProceedResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
CancelResponse(TpChannelRequest *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelRequestCancelCB *callback = (csITpChannelRequestCancelCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnCancelError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnCancelDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelRequest::CallCancel(csITpChannelRequestCancelCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_request_call_cancel(m_Proxy, -1,
      cb? CancelResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
FailedSignalCallback(TpChannelRequest *proxy,
    const gchar *error, const gchar *message,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelRequest *obj = (csTpChannelRequest *)user_data;
  if (!obj)
    return;

  obj->HandleFailed(error, message);
}


void
csTpChannelRequest::HandleFailed(const gchar *error, const gchar *message)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_FailedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelRequestFailedObserver> observer;

  nsCString cError = nsDependentCString(error);
  nsCString cMessage = nsDependentCString(message);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_FailedObservers, i);
    observer->OnFailed(cError, cMessage);
  }
}


NS_IMETHODIMP
csTpChannelRequest::ConnectToFailed(csITpChannelRequestFailedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_FailedObservers) {
    m_FailedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_request_connect_to_failed(m_Proxy,
        FailedSignalCallback, this, NULL, NULL, NULL);
  }

  m_FailedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelRequest::DisconnectFromFailed(csITpChannelRequestFailedObserver *observer)
{
  if (!m_FailedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_FailedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_FailedObservers->RemoveElementAt(idx);
}


static void
SucceededSignalCallback(TpChannelRequest *proxy,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelRequest *obj = (csTpChannelRequest *)user_data;
  if (!obj)
    return;

  obj->HandleSucceeded();
}


void
csTpChannelRequest::HandleSucceeded()
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_SucceededObservers->GetLength(&length);
  nsCOMPtr<csITpChannelRequestSucceededObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_SucceededObservers, i);
    observer->OnSucceeded();
  }
}


NS_IMETHODIMP
csTpChannelRequest::ConnectToSucceeded(csITpChannelRequestSucceededObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_SucceededObservers) {
    m_SucceededObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_request_connect_to_succeeded(m_Proxy,
        SucceededSignalCallback, this, NULL, NULL, NULL);
  }

  m_SucceededObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelRequest::DisconnectFromSucceeded(csITpChannelRequestSucceededObserver *observer)
{
  if (!m_SucceededObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_SucceededObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_SucceededObservers->RemoveElementAt(idx);
}



csTpChannelRequest::csTpChannelRequest()
{}

csTpChannelRequest::~csTpChannelRequest()
{}
