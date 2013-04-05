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


#include "csTpChannel.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
static void
ChannelTypeResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelChannelTypeCB *callback = (csITpChannelChannelTypeCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyChannelTypeError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar * channeltype;
  nsCString cChannelType = nsDependentCString(channeltype);

  callback->GetPropertyChannelTypeDone(cChannelType);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannel::GetPropertyChannelType(csITpChannelChannelTypeCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel",
      "ChannelType",
      cb? ChannelTypeResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
InterfacesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfacesCB *callback = (csITpChannelInterfacesCB *)user_data;
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
csTpChannel::GetPropertyInterfaces(csITpChannelInterfacesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel",
      "Interfaces",
      cb? InterfacesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
TargetHandleResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTargetHandleCB *callback = (csITpChannelTargetHandleCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyTargetHandleError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  targethandle;

  callback->GetPropertyTargetHandleDone(targethandle);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannel::GetPropertyTargetHandle(csITpChannelTargetHandleCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel",
      "TargetHandle",
      cb? TargetHandleResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
TargetIDResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTargetIDCB *callback = (csITpChannelTargetIDCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyTargetIDError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar * targetid;
  nsCString cTargetID = nsDependentCString(targetid);

  callback->GetPropertyTargetIDDone(cTargetID);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannel::GetPropertyTargetID(csITpChannelTargetIDCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel",
      "TargetID",
      cb? TargetIDResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
TargetHandleTypeResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTargetHandleTypeCB *callback = (csITpChannelTargetHandleTypeCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyTargetHandleTypeError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  targethandletype;

  callback->GetPropertyTargetHandleTypeDone(targethandletype);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannel::GetPropertyTargetHandleType(csITpChannelTargetHandleTypeCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel",
      "TargetHandleType",
      cb? TargetHandleTypeResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
CloseResponse(TpChannel *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelCloseCB *callback = (csITpChannelCloseCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnCloseError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnCloseDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannel::CallClose(csITpChannelCloseCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_call_close(m_Proxy, -1,
      cb? CloseResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ClosedSignalCallback(TpChannel *proxy,
    gpointer user_data, GObject *weak_object)
{
  csTpChannel *obj = (csTpChannel *)user_data;
  if (!obj)
    return;

  obj->HandleClosed();
}


void
csTpChannel::HandleClosed()
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_ClosedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelClosedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_ClosedObservers, i);
    observer->OnClosed();
  }
}


NS_IMETHODIMP
csTpChannel::ConnectToClosed(csITpChannelClosedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_ClosedObservers) {
    m_ClosedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_connect_to_closed(m_Proxy,
        ClosedSignalCallback, this, NULL, NULL, NULL);
  }

  m_ClosedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannel::DisconnectFromClosed(csITpChannelClosedObserver *observer)
{
  if (!m_ClosedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_ClosedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_ClosedObservers->RemoveElementAt(idx);
}


static void
GetChannelTypeResponse(TpChannel *proxy,
    const gchar *channel_type,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelGetChannelTypeCB *callback = (csITpChannelGetChannelTypeCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetChannelTypeError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCString cChannelType = nsDependentCString(channel_type);

  callback->OnGetChannelTypeDone(cChannelType);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannel::CallGetChannelType(csITpChannelGetChannelTypeCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_call_get_channel_type(m_Proxy, -1,
      cb? GetChannelTypeResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetHandleResponse(TpChannel *proxy,
    guint target_handle_type, guint target_handle,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelGetHandleCB *callback = (csITpChannelGetHandleCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetHandleError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnGetHandleDone(target_handle_type, target_handle);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannel::CallGetHandle(csITpChannelGetHandleCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_call_get_handle(m_Proxy, -1,
      cb? GetHandleResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetInterfacesResponse(TpChannel *proxy,
    const gchar **interfaces,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelGetInterfacesCB *callback = (csITpChannelGetInterfacesCB *)user_data;
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
csTpChannel::CallGetInterfaces(csITpChannelGetInterfacesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_call_get_interfaces(m_Proxy, -1,
      cb? GetInterfacesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RequestedResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelRequestedCB *callback = (csITpChannelRequestedCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyRequestedError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gboolean  requested;

  callback->GetPropertyRequestedDone(requested);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannel::GetPropertyRequested(csITpChannelRequestedCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel",
      "Requested",
      cb? RequestedResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
InitiatorHandleResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInitiatorHandleCB *callback = (csITpChannelInitiatorHandleCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyInitiatorHandleError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  initiatorhandle;

  callback->GetPropertyInitiatorHandleDone(initiatorhandle);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannel::GetPropertyInitiatorHandle(csITpChannelInitiatorHandleCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel",
      "InitiatorHandle",
      cb? InitiatorHandleResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
InitiatorIDResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInitiatorIDCB *callback = (csITpChannelInitiatorIDCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyInitiatorIDError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar * initiatorid;
  nsCString cInitiatorID = nsDependentCString(initiatorid);

  callback->GetPropertyInitiatorIDDone(cInitiatorID);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannel::GetPropertyInitiatorID(csITpChannelInitiatorIDCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel",
      "InitiatorID",
      cb? InitiatorIDResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpChannel::csTpChannel()
{}

csTpChannel::~csTpChannel()
{}
