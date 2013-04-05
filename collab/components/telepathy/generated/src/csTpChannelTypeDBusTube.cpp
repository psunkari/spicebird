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


#include "csTpChannelTypeDBusTube.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
static void
OfferResponse(TpChannel *proxy,
    const gchar *address,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeDBusTubeOfferCB *callback = (csITpChannelTypeDBusTubeOfferCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnOfferError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCString caddress = nsDependentCString(address);

  callback->OnOfferDone(caddress);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeDBusTube::CallOffer(nsIArray *aparameters, PRUint32 aaccesscontrol,
    csITpChannelTypeDBusTubeOfferCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  /* TODO */

  NS_IF_ADDREF(cb);
  tp_cli_channel_type_dbus_tube_call_offer(m_Proxy, -1,
      NULL, aaccesscontrol,
      cb? OfferResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
AcceptResponse(TpChannel *proxy,
    const gchar *address,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeDBusTubeAcceptCB *callback = (csITpChannelTypeDBusTubeAcceptCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnAcceptError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCString caddress = nsDependentCString(address);

  callback->OnAcceptDone(caddress);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeDBusTube::CallAccept(PRUint32 aaccesscontrol,
    csITpChannelTypeDBusTubeAcceptCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_dbus_tube_call_accept(m_Proxy, -1,
      aaccesscontrol,
      cb? AcceptResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
DBusNamesChangedSignalCallback(TpChannel *proxy,
    GHashTable *added, const GArray *removed,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeDBusTube *obj = (csTpChannelTypeDBusTube *)user_data;
  if (!obj)
    return;

  obj->HandleDBusNamesChanged(added, removed);
}


void
csTpChannelTypeDBusTube::HandleDBusNamesChanged(GHashTable *added, const GArray *removed)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_DBusNamesChangedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeDBusTubeDBusNamesChangedObserver> observer;

  nsCOMPtr<nsIArray> cAdded;
  csTpDBusTubeParticipants::Create((gpointer)added, getter_AddRefs(cAdded));
  PRUint32 cRemovedCount = removed->len;
  PRUint32 *cRemoved = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cRemovedCount);
  for (unsigned int i=0; i<cRemovedCount; i++)
    cRemoved[i] = g_array_index(removed, guint, i);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_DBusNamesChangedObservers, i);
    observer->OnDBusNamesChanged(cAdded, cRemovedCount, cRemoved);
  }
}


NS_IMETHODIMP
csTpChannelTypeDBusTube::ConnectToDBusNamesChanged(csITpChannelTypeDBusTubeDBusNamesChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_DBusNamesChangedObservers) {
    m_DBusNamesChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_dbus_tube_connect_to_dbus_names_changed(m_Proxy,
        DBusNamesChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_DBusNamesChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeDBusTube::DisconnectFromDBusNamesChanged(csITpChannelTypeDBusTubeDBusNamesChangedObserver *observer)
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
ServiceNameResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeDBusTubeServiceNameCB *callback = (csITpChannelTypeDBusTubeServiceNameCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyServiceNameError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar * servicename;
  nsCString cServiceName = nsDependentCString(servicename);

  callback->GetPropertyServiceNameDone(cServiceName);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeDBusTube::GetPropertyServiceName(csITpChannelTypeDBusTubeServiceNameCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.DBusTube",
      "ServiceName",
      cb? ServiceNameResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
DBusNamesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeDBusTubeDBusNamesCB *callback = (csITpChannelTypeDBusTubeDBusNamesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyDBusNamesError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GHashTable * dbusnames;
  dbusnames = (GHashTable *)g_value_get_boxed(out);
  nsCOMPtr<nsIArray> cDBusNames;
  csTpDBusTubeParticipants::Create((gpointer)dbusnames, getter_AddRefs(cDBusNames));

  callback->GetPropertyDBusNamesDone(cDBusNames);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeDBusTube::GetPropertyDBusNames(csITpChannelTypeDBusTubeDBusNamesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.DBusTube",
      "DBusNames",
      cb? DBusNamesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


/*
 *  Implementation of csTpDBusTubeParticipants
 */

NS_IMPL_ISUPPORTS1(csTpDBusTubeParticipants, csITpDBusTubeParticipants)

NS_METHOD
csTpDBusTubeParticipants::Create(PRUint32 aHandle, const nsCString &aUniqueName, void **aResult)
{
  csITpDBusTubeParticipants *it = 
          new csTpDBusTubeParticipants(aHandle, aUniqueName);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpDBusTubeParticipants), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpDBusTubeParticipants::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    guint handle = GPOINTER_TO_UINT(keyPtr);
    const gchar *unique_name = (gchar *)valuePtr;

    nsCString cUniqueName = nsDependentCString(unique_name);

    csITpDBusTubeParticipants *temp = new csTpDBusTubeParticipants(handle, cUniqueName);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpDBusTubeParticipants> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpDBusTubeParticipants::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpDBusTubeParticipants::csTpDBusTubeParticipants(PRUint32 aHandle, const nsCString &aUniqueName)
{
  m_Handle = aHandle;
  m_UniqueName.Assign(aUniqueName);
}

csTpDBusTubeParticipants::~csTpDBusTubeParticipants()
{}

NS_IMETHODIMP
csTpDBusTubeParticipants::GetHandle(PRUint32 *aHandle)
{
  *aHandle = m_Handle;
  return NS_OK;
}

NS_IMETHODIMP
csTpDBusTubeParticipants::GetUniqueName(nsACString &aUniqueName)
{
  aUniqueName.Assign(m_UniqueName);
  return NS_OK;
}

static void
SupportedAccessControlsResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeDBusTubeSupportedAccessControlsCB *callback = (csITpChannelTypeDBusTubeSupportedAccessControlsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertySupportedAccessControlsError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GArray * supportedaccesscontrols;
  supportedaccesscontrols = (GArray *)g_value_get_boxed(out);
  PRUint32 cSupportedAccessControlsCount = supportedaccesscontrols->len;
  PRUint32 *cSupportedAccessControls = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cSupportedAccessControlsCount);
  for (unsigned int i=0; i<cSupportedAccessControlsCount; i++)
    cSupportedAccessControls[i] = g_array_index(supportedaccesscontrols, guint, i);

  callback->GetPropertySupportedAccessControlsDone(cSupportedAccessControlsCount, cSupportedAccessControls);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeDBusTube::GetPropertySupportedAccessControls(csITpChannelTypeDBusTubeSupportedAccessControlsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.DBusTube",
      "SupportedAccessControls",
      cb? SupportedAccessControlsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpChannelTypeDBusTube::csTpChannelTypeDBusTube()
{}

csTpChannelTypeDBusTube::~csTpChannelTypeDBusTube()
{}
