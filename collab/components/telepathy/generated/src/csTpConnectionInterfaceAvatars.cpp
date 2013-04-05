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


#include "csTpConnectionInterfaceAvatars.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpAvatarTokenMap
 */

NS_IMPL_ISUPPORTS1(csTpAvatarTokenMap, csITpAvatarTokenMap)

NS_METHOD
csTpAvatarTokenMap::Create(PRUint32 aHandle, const nsCString &aToken, void **aResult)
{
  csITpAvatarTokenMap *it = 
          new csTpAvatarTokenMap(aHandle, aToken);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpAvatarTokenMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpAvatarTokenMap::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    guint handle = GPOINTER_TO_UINT(keyPtr);
    const gchar *token = (gchar *)valuePtr;

    nsCString cToken = nsDependentCString(token);

    csITpAvatarTokenMap *temp = new csTpAvatarTokenMap(handle, cToken);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpAvatarTokenMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpAvatarTokenMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpAvatarTokenMap::csTpAvatarTokenMap(PRUint32 aHandle, const nsCString &aToken)
{
  m_Handle = aHandle;
  m_Token.Assign(aToken);
}

csTpAvatarTokenMap::~csTpAvatarTokenMap()
{}

NS_IMETHODIMP
csTpAvatarTokenMap::GetHandle(PRUint32 *aHandle)
{
  *aHandle = m_Handle;
  return NS_OK;
}

NS_IMETHODIMP
csTpAvatarTokenMap::GetToken(nsACString &aToken)
{
  aToken.Assign(m_Token);
  return NS_OK;
}

static void
AvatarUpdatedSignalCallback(TpConnection *proxy,
    guint contact, const gchar *new_avatar_token,
    gpointer user_data, GObject *weak_object)
{
  csTpConnectionInterfaceAvatars *obj = (csTpConnectionInterfaceAvatars *)user_data;
  if (!obj)
    return;

  obj->HandleAvatarUpdated(contact, new_avatar_token);
}


void
csTpConnectionInterfaceAvatars::HandleAvatarUpdated(guint contact, const gchar *new_avatar_token)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_AvatarUpdatedObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionInterfaceAvatarsAvatarUpdatedObserver> observer;

  nsCString cNewAvatarToken = nsDependentCString(new_avatar_token);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_AvatarUpdatedObservers, i);
    observer->OnAvatarUpdated(contact, cNewAvatarToken);
  }
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::ConnectToAvatarUpdated(csITpConnectionInterfaceAvatarsAvatarUpdatedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_AvatarUpdatedObservers) {
    m_AvatarUpdatedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_interface_avatars_connect_to_avatar_updated(m_Proxy,
        AvatarUpdatedSignalCallback, this, NULL, NULL, NULL);
  }

  m_AvatarUpdatedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::DisconnectFromAvatarUpdated(csITpConnectionInterfaceAvatarsAvatarUpdatedObserver *observer)
{
  if (!m_AvatarUpdatedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_AvatarUpdatedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_AvatarUpdatedObservers->RemoveElementAt(idx);
}


static void
AvatarRetrievedSignalCallback(TpConnection *proxy,
    guint contact, const gchar *token, const GArray *avatar, const gchar *type,
    gpointer user_data, GObject *weak_object)
{
  csTpConnectionInterfaceAvatars *obj = (csTpConnectionInterfaceAvatars *)user_data;
  if (!obj)
    return;

  obj->HandleAvatarRetrieved(contact, token, avatar, type);
}


void
csTpConnectionInterfaceAvatars::HandleAvatarRetrieved(guint contact, const gchar *token, const GArray *avatar, const gchar *type)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_AvatarRetrievedObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionInterfaceAvatarsAvatarRetrievedObserver> observer;

  nsCString cToken = nsDependentCString(token);
  PRUint32 cAvatarCount = avatar->len;
  PRUint8 *cAvatar = (PRUint8 *)nsMemory::Alloc(sizeof(PRUint8)*cAvatarCount);
  for (unsigned int i=0; i<cAvatarCount; i++)
    cAvatar[i] = g_array_index(avatar, guchar, i);
  nsCString cType = nsDependentCString(type);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_AvatarRetrievedObservers, i);
    observer->OnAvatarRetrieved(contact, cToken, cAvatarCount, cAvatar, cType);
  }
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::ConnectToAvatarRetrieved(csITpConnectionInterfaceAvatarsAvatarRetrievedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_AvatarRetrievedObservers) {
    m_AvatarRetrievedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_interface_avatars_connect_to_avatar_retrieved(m_Proxy,
        AvatarRetrievedSignalCallback, this, NULL, NULL, NULL);
  }

  m_AvatarRetrievedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::DisconnectFromAvatarRetrieved(csITpConnectionInterfaceAvatarsAvatarRetrievedObserver *observer)
{
  if (!m_AvatarRetrievedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_AvatarRetrievedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_AvatarRetrievedObservers->RemoveElementAt(idx);
}


static void
SupportedAvatarMIMETypesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsSupportedAvatarMIMETypesCB *callback = (csITpConnectionInterfaceAvatarsSupportedAvatarMIMETypesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertySupportedAvatarMIMETypesError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar ** supportedavatarmimetypes;
  supportedavatarmimetypes = (gchar **)g_value_get_boxed(out);
  PRUint32 cSupportedAvatarMIMETypesCount = 0;
  for (char **pos = (char**)supportedavatarmimetypes; *pos; pos++, cSupportedAvatarMIMETypesCount++);
  char **cSupportedAvatarMIMETypes = (char **)nsMemory::Alloc(cSupportedAvatarMIMETypesCount * sizeof(char*));
  for (PRUint32 i=0; i<cSupportedAvatarMIMETypesCount; i++)
    cSupportedAvatarMIMETypes[i] = (char *)nsMemory::Clone(supportedavatarmimetypes[i], strlen(supportedavatarmimetypes[i]) + 1);

  callback->GetPropertySupportedAvatarMIMETypesDone(cSupportedAvatarMIMETypesCount, (const char **)cSupportedAvatarMIMETypes);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::GetPropertySupportedAvatarMIMETypes(csITpConnectionInterfaceAvatarsSupportedAvatarMIMETypesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection.Interface.Avatars",
      "SupportedAvatarMIMETypes",
      cb? SupportedAvatarMIMETypesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
MinimumAvatarHeightResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsMinimumAvatarHeightCB *callback = (csITpConnectionInterfaceAvatarsMinimumAvatarHeightCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyMinimumAvatarHeightError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  minimumavatarheight;

  callback->GetPropertyMinimumAvatarHeightDone(minimumavatarheight);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::GetPropertyMinimumAvatarHeight(csITpConnectionInterfaceAvatarsMinimumAvatarHeightCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection.Interface.Avatars",
      "MinimumAvatarHeight",
      cb? MinimumAvatarHeightResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
MinimumAvatarWidthResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsMinimumAvatarWidthCB *callback = (csITpConnectionInterfaceAvatarsMinimumAvatarWidthCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyMinimumAvatarWidthError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  minimumavatarwidth;

  callback->GetPropertyMinimumAvatarWidthDone(minimumavatarwidth);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::GetPropertyMinimumAvatarWidth(csITpConnectionInterfaceAvatarsMinimumAvatarWidthCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection.Interface.Avatars",
      "MinimumAvatarWidth",
      cb? MinimumAvatarWidthResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RecommendedAvatarHeightResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsRecommendedAvatarHeightCB *callback = (csITpConnectionInterfaceAvatarsRecommendedAvatarHeightCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyRecommendedAvatarHeightError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  recommendedavatarheight;

  callback->GetPropertyRecommendedAvatarHeightDone(recommendedavatarheight);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::GetPropertyRecommendedAvatarHeight(csITpConnectionInterfaceAvatarsRecommendedAvatarHeightCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection.Interface.Avatars",
      "RecommendedAvatarHeight",
      cb? RecommendedAvatarHeightResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RecommendedAvatarWidthResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsRecommendedAvatarWidthCB *callback = (csITpConnectionInterfaceAvatarsRecommendedAvatarWidthCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyRecommendedAvatarWidthError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  recommendedavatarwidth;

  callback->GetPropertyRecommendedAvatarWidthDone(recommendedavatarwidth);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::GetPropertyRecommendedAvatarWidth(csITpConnectionInterfaceAvatarsRecommendedAvatarWidthCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection.Interface.Avatars",
      "RecommendedAvatarWidth",
      cb? RecommendedAvatarWidthResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
MaximumAvatarHeightResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsMaximumAvatarHeightCB *callback = (csITpConnectionInterfaceAvatarsMaximumAvatarHeightCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyMaximumAvatarHeightError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  maximumavatarheight;

  callback->GetPropertyMaximumAvatarHeightDone(maximumavatarheight);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::GetPropertyMaximumAvatarHeight(csITpConnectionInterfaceAvatarsMaximumAvatarHeightCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection.Interface.Avatars",
      "MaximumAvatarHeight",
      cb? MaximumAvatarHeightResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
MaximumAvatarWidthResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsMaximumAvatarWidthCB *callback = (csITpConnectionInterfaceAvatarsMaximumAvatarWidthCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyMaximumAvatarWidthError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  maximumavatarwidth;

  callback->GetPropertyMaximumAvatarWidthDone(maximumavatarwidth);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::GetPropertyMaximumAvatarWidth(csITpConnectionInterfaceAvatarsMaximumAvatarWidthCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection.Interface.Avatars",
      "MaximumAvatarWidth",
      cb? MaximumAvatarWidthResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
MaximumAvatarBytesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsMaximumAvatarBytesCB *callback = (csITpConnectionInterfaceAvatarsMaximumAvatarBytesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyMaximumAvatarBytesError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  maximumavatarbytes;

  callback->GetPropertyMaximumAvatarBytesDone(maximumavatarbytes);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::GetPropertyMaximumAvatarBytes(csITpConnectionInterfaceAvatarsMaximumAvatarBytesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection.Interface.Avatars",
      "MaximumAvatarBytes",
      cb? MaximumAvatarBytesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetAvatarRequirementsResponse(TpConnection *proxy,
    const gchar **mime_types, guint min_width, guint min_height, guint max_width, guint max_height, guint max_bytes,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsGetAvatarRequirementsCB *callback = (csITpConnectionInterfaceAvatarsGetAvatarRequirementsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetAvatarRequirementsError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cMIMETypesCount = 0;
  for (char **pos = (char**)mime_types; *pos; pos++, cMIMETypesCount++);
  char **cMIMETypes = (char **)nsMemory::Alloc(cMIMETypesCount * sizeof(char*));
  for (PRUint32 i=0; i<cMIMETypesCount; i++)
    cMIMETypes[i] = (char *)nsMemory::Clone(mime_types[i], strlen(mime_types[i]) + 1);

  callback->OnGetAvatarRequirementsDone(cMIMETypesCount, (const char **)cMIMETypes, min_width, min_height, max_width, max_height, max_bytes);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::CallGetAvatarRequirements(csITpConnectionInterfaceAvatarsGetAvatarRequirementsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_avatars_call_get_avatar_requirements(m_Proxy, -1,
      cb? GetAvatarRequirementsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetAvatarTokensResponse(TpConnection *proxy,
    const gchar **tokens,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsGetAvatarTokensCB *callback = (csITpConnectionInterfaceAvatarsGetAvatarTokensCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetAvatarTokensError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cTokensCount = 0;
  for (char **pos = (char**)tokens; *pos; pos++, cTokensCount++);
  char **cTokens = (char **)nsMemory::Alloc(cTokensCount * sizeof(char*));
  for (PRUint32 i=0; i<cTokensCount; i++)
    cTokens[i] = (char *)nsMemory::Clone(tokens[i], strlen(tokens[i]) + 1);

  callback->OnGetAvatarTokensDone(cTokensCount, (const char **)cTokens);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::CallGetAvatarTokens(PRUint32 aContactsCount, PRUint32 *aContacts,
    csITpConnectionInterfaceAvatarsGetAvatarTokensCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cContacts = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aContactsCount; i++)
    g_array_append_val(cContacts, aContacts[i]);

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_avatars_call_get_avatar_tokens(m_Proxy, -1,
      cContacts,
      cb? GetAvatarTokensResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetKnownAvatarTokensResponse(TpConnection *proxy,
    GHashTable *tokens,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsGetKnownAvatarTokensCB *callback = (csITpConnectionInterfaceAvatarsGetKnownAvatarTokensCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetKnownAvatarTokensError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIArray> cTokens;
  csTpAvatarTokenMap::Create((gpointer)tokens, getter_AddRefs(cTokens));

  callback->OnGetKnownAvatarTokensDone(cTokens);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::CallGetKnownAvatarTokens(PRUint32 aContactsCount, PRUint32 *aContacts,
    csITpConnectionInterfaceAvatarsGetKnownAvatarTokensCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cContacts = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aContactsCount; i++)
    g_array_append_val(cContacts, aContacts[i]);

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_avatars_call_get_known_avatar_tokens(m_Proxy, -1,
      cContacts,
      cb? GetKnownAvatarTokensResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RequestAvatarResponse(TpConnection *proxy,
    const GArray *data, const gchar *mime_type,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsRequestAvatarCB *callback = (csITpConnectionInterfaceAvatarsRequestAvatarCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnRequestAvatarError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cDataCount = data->len;
  PRUint8 *cData = (PRUint8 *)nsMemory::Alloc(sizeof(PRUint8)*cDataCount);
  for (unsigned int i=0; i<cDataCount; i++)
    cData[i] = g_array_index(data, guchar, i);
  nsCString cMIMEType = nsDependentCString(mime_type);

  callback->OnRequestAvatarDone(cDataCount, cData, cMIMEType);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::CallRequestAvatar(PRUint32 aContact,
    csITpConnectionInterfaceAvatarsRequestAvatarCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_avatars_call_request_avatar(m_Proxy, -1,
      aContact,
      cb? RequestAvatarResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RequestAvatarsResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsRequestAvatarsCB *callback = (csITpConnectionInterfaceAvatarsRequestAvatarsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnRequestAvatarsError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnRequestAvatarsDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::CallRequestAvatars(PRUint32 aContactsCount, PRUint32 *aContacts,
    csITpConnectionInterfaceAvatarsRequestAvatarsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cContacts = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aContactsCount; i++)
    g_array_append_val(cContacts, aContacts[i]);

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_avatars_call_request_avatars(m_Proxy, -1,
      cContacts,
      cb? RequestAvatarsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
SetAvatarResponse(TpConnection *proxy,
    const gchar *token,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsSetAvatarCB *callback = (csITpConnectionInterfaceAvatarsSetAvatarCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnSetAvatarError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCString cToken = nsDependentCString(token);

  callback->OnSetAvatarDone(cToken);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::CallSetAvatar(PRUint32 aAvatarCount, PRUint8 *aAvatar, const nsACString &aMIMEType,
    csITpConnectionInterfaceAvatarsSetAvatarCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cAvatar = g_array_new(false, false, sizeof(guchar ));
  for (PRUint32 i=0; i<aAvatarCount; i++)
    g_array_append_val(cAvatar, aAvatar[i]);
  char *cMIMEType = ToNewCString(aMIMEType);

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_avatars_call_set_avatar(m_Proxy, -1,
      cAvatar, cMIMEType,
      cb? SetAvatarResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ClearAvatarResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAvatarsClearAvatarCB *callback = (csITpConnectionInterfaceAvatarsClearAvatarCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnClearAvatarError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnClearAvatarDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAvatars::CallClearAvatar(csITpConnectionInterfaceAvatarsClearAvatarCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_avatars_call_clear_avatar(m_Proxy, -1,
      cb? ClearAvatarResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpConnectionInterfaceAvatars::csTpConnectionInterfaceAvatars()
{}

csTpConnectionInterfaceAvatars::~csTpConnectionInterfaceAvatars()
{}
