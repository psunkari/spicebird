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


#include "csTpConnectionInterfaceRequests.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpChannelDetails
 */

NS_IMPL_ISUPPORTS1(csTpChannelDetails, csITpChannelDetails)

NS_METHOD
csTpChannelDetails::Create(const nsCString &aChannel, nsIArray *aProperties, void **aResult)
{
  csITpChannelDetails *it = 
          new csTpChannelDetails(aChannel, aProperties);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpChannelDetails), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpChannelDetails::Create(gpointer aGLibItem, void **aResult)
{
  const gchar *channel;
  GHashTable *properties;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_CHANNEL_DETAILS);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &channel, 1, &properties,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cChannel = nsDependentCString(channel);
  nsCOMPtr<nsIArray> cProperties;
  csTpQualifiedPropertyValueMap::Create((gpointer)properties, getter_AddRefs(cProperties));
  csITpChannelDetails *it = new csTpChannelDetails(cChannel, cProperties);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpChannelDetails), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpChannelDetails::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpChannelDetails::csTpChannelDetails(const nsCString &aChannel, nsIArray *aProperties)
{
  m_Channel.Assign(aChannel);
  m_Properties = aProperties;
}

csTpChannelDetails::~csTpChannelDetails()
{}

NS_IMETHODIMP
csTpChannelDetails::GetChannel(nsACString &aChannel)
{
  aChannel.Assign(m_Channel);
  return NS_OK;
}

NS_IMETHODIMP
csTpChannelDetails::GetProperties(nsIArray **aProperties)
{
  NS_IF_ADDREF(*aProperties = m_Properties);
  return NS_OK;
}

static void
CreateChannelResponse(TpConnection *proxy,
    const gchar *channel, GHashTable *properties,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceRequestsCreateChannelCB *callback = (csITpConnectionInterfaceRequestsCreateChannelCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnCreateChannelError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCString cChannel = nsDependentCString(channel);
  nsCOMPtr<nsIArray> cProperties;
  csTpQualifiedPropertyValueMap::Create((gpointer)properties, getter_AddRefs(cProperties));

  callback->OnCreateChannelDone(cChannel, cProperties);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceRequests::CallCreateChannel(nsIArray *aRequest,
    csITpConnectionInterfaceRequestsCreateChannelCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  /* TODO */

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_requests_call_create_channel(m_Proxy, -1,
      NULL,
      cb? CreateChannelResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
EnsureChannelResponse(TpConnection *proxy,
    gboolean yours, const gchar *channel, GHashTable *properties,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceRequestsEnsureChannelCB *callback = (csITpConnectionInterfaceRequestsEnsureChannelCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnEnsureChannelError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCString cChannel = nsDependentCString(channel);
  nsCOMPtr<nsIArray> cProperties;
  csTpQualifiedPropertyValueMap::Create((gpointer)properties, getter_AddRefs(cProperties));

  callback->OnEnsureChannelDone(yours, cChannel, cProperties);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceRequests::CallEnsureChannel(nsIArray *aRequest,
    csITpConnectionInterfaceRequestsEnsureChannelCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  /* TODO */

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_requests_call_ensure_channel(m_Proxy, -1,
      NULL,
      cb? EnsureChannelResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
NewChannelsSignalCallback(TpConnection *proxy,
    const GPtrArray *channels,
    gpointer user_data, GObject *weak_object)
{
  csTpConnectionInterfaceRequests *obj = (csTpConnectionInterfaceRequests *)user_data;
  if (!obj)
    return;

  obj->HandleNewChannels(channels);
}


void
csTpConnectionInterfaceRequests::HandleNewChannels(const GPtrArray *channels)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_NewChannelsObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionInterfaceRequestsNewChannelsObserver> observer;

  nsCOMPtr<nsIMutableArray> cChannels = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)channels)->len; i++) {
    gpointer channels_item = g_ptr_array_index((GPtrArray*)channels, i);
    nsCOMPtr<csITpChannelDetails> cChannelsItem;
    csTpChannelDetails::Create((gpointer)channels_item, getter_AddRefs(cChannelsItem));
    cChannels->AppendElement(cChannelsItem, PR_FALSE);
  }

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_NewChannelsObservers, i);
    observer->OnNewChannels(cChannels);
  }
}


NS_IMETHODIMP
csTpConnectionInterfaceRequests::ConnectToNewChannels(csITpConnectionInterfaceRequestsNewChannelsObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_NewChannelsObservers) {
    m_NewChannelsObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_interface_requests_connect_to_new_channels(m_Proxy,
        NewChannelsSignalCallback, this, NULL, NULL, NULL);
  }

  m_NewChannelsObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnectionInterfaceRequests::DisconnectFromNewChannels(csITpConnectionInterfaceRequestsNewChannelsObserver *observer)
{
  if (!m_NewChannelsObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_NewChannelsObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_NewChannelsObservers->RemoveElementAt(idx);
}


static void
ChannelsResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceRequestsChannelsCB *callback = (csITpConnectionInterfaceRequestsChannelsCB *)user_data;
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
csTpConnectionInterfaceRequests::GetPropertyChannels(csITpConnectionInterfaceRequestsChannelsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection.Interface.Requests",
      "Channels",
      cb? ChannelsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ChannelClosedSignalCallback(TpConnection *proxy,
    const gchar *removed,
    gpointer user_data, GObject *weak_object)
{
  csTpConnectionInterfaceRequests *obj = (csTpConnectionInterfaceRequests *)user_data;
  if (!obj)
    return;

  obj->HandleChannelClosed(removed);
}


void
csTpConnectionInterfaceRequests::HandleChannelClosed(const gchar *removed)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_ChannelClosedObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionInterfaceRequestsChannelClosedObserver> observer;

  nsCString cRemoved = nsDependentCString(removed);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_ChannelClosedObservers, i);
    observer->OnChannelClosed(cRemoved);
  }
}


NS_IMETHODIMP
csTpConnectionInterfaceRequests::ConnectToChannelClosed(csITpConnectionInterfaceRequestsChannelClosedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_ChannelClosedObservers) {
    m_ChannelClosedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_interface_requests_connect_to_channel_closed(m_Proxy,
        ChannelClosedSignalCallback, this, NULL, NULL, NULL);
  }

  m_ChannelClosedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnectionInterfaceRequests::DisconnectFromChannelClosed(csITpConnectionInterfaceRequestsChannelClosedObserver *observer)
{
  if (!m_ChannelClosedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_ChannelClosedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_ChannelClosedObservers->RemoveElementAt(idx);
}


/*
 *  Implementation of csTpChannelClass
 */

NS_IMPL_ISUPPORTS1(csTpChannelClass, csITpChannelClass)

NS_METHOD
csTpChannelClass::Create(const nsCString &aKey, nsIVariant *aValue, void **aResult)
{
  csITpChannelClass *it = 
          new csTpChannelClass(aKey, aValue);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpChannelClass), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpChannelClass::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    const gchar *key = (gchar *)keyPtr;
    const GValue *value = (GValue *)valuePtr;

    nsCString cKey = nsDependentCString(key);
    nsCOMPtr<nsIVariant> cValue;
    GValueToVariant(value, getter_AddRefs(cValue));

    csITpChannelClass *temp = new csTpChannelClass(cKey, cValue);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpChannelClass> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpChannelClass::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpChannelClass::csTpChannelClass(const nsCString &aKey, nsIVariant *aValue)
{
  m_Key.Assign(aKey);
  m_Value = aValue;
}

csTpChannelClass::~csTpChannelClass()
{}

NS_IMETHODIMP
csTpChannelClass::GetKey(nsACString &aKey)
{
  aKey.Assign(m_Key);
  return NS_OK;
}

NS_IMETHODIMP
csTpChannelClass::GetValue(nsIVariant **aValue)
{
  NS_IF_ADDREF(*aValue = m_Value);
  return NS_OK;
}

/*
 *  Implementation of csTpRequestableChannelClass
 */

NS_IMPL_ISUPPORTS1(csTpRequestableChannelClass, csITpRequestableChannelClass)

NS_METHOD
csTpRequestableChannelClass::Create(nsIArray *aFixedProperties, PRUint32 aAllowedPropertiesCount, const char **aAllowedProperties, void **aResult)
{
  csITpRequestableChannelClass *it = 
          new csTpRequestableChannelClass(aFixedProperties, aAllowedPropertiesCount, aAllowedProperties);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpRequestableChannelClass), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpRequestableChannelClass::Create(gpointer aGLibItem, void **aResult)
{
  GHashTable *fixed_properties;
  const gchar **allowed_properties;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_REQUESTABLE_CHANNEL_CLASS);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &fixed_properties, 1, &allowed_properties,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCOMPtr<nsIArray> cFixedProperties;
  csTpChannelClass::Create((gpointer)fixed_properties, getter_AddRefs(cFixedProperties));
  PRUint32 cAllowedPropertiesCount = 0;
  for (char **pos = (char**)allowed_properties; *pos; pos++, cAllowedPropertiesCount++);
  char **cAllowedProperties = (char **)nsMemory::Alloc(cAllowedPropertiesCount * sizeof(char*));
  for (PRUint32 i=0; i<cAllowedPropertiesCount; i++)
    cAllowedProperties[i] = (char *)nsMemory::Clone(allowed_properties[i], strlen(allowed_properties[i]) + 1);
  csITpRequestableChannelClass *it = new csTpRequestableChannelClass(cFixedProperties, cAllowedPropertiesCount, (const char **)cAllowedProperties);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpRequestableChannelClass), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpRequestableChannelClass::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpRequestableChannelClass::csTpRequestableChannelClass(nsIArray *aFixedProperties, PRUint32 aAllowedPropertiesCount, const char **aAllowedProperties)
{
  m_FixedProperties = aFixedProperties;
  m_AllowedPropertiesCount = aAllowedPropertiesCount; m_AllowedProperties = (char **)aAllowedProperties;
}

csTpRequestableChannelClass::~csTpRequestableChannelClass()
{}

NS_IMETHODIMP
csTpRequestableChannelClass::GetFixedProperties(nsIArray **aFixedProperties)
{
  NS_IF_ADDREF(*aFixedProperties = m_FixedProperties);
  return NS_OK;
}

NS_IMETHODIMP
csTpRequestableChannelClass::GetAllowedProperties(PRUint32 *aAllowedPropertiesCount, char ***aAllowedProperties)
{
  *aAllowedPropertiesCount = m_AllowedPropertiesCount; *aAllowedProperties = m_AllowedProperties;
  return NS_OK;
}

static void
RequestableChannelClassesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceRequestsRequestableChannelClassesCB *callback = (csITpConnectionInterfaceRequestsRequestableChannelClassesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyRequestableChannelClassesError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GPtrArray * requestablechannelclasses;
  requestablechannelclasses = (GPtrArray *)g_value_get_boxed(out);
  nsCOMPtr<nsIMutableArray> cRequestableChannelClasses = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)requestablechannelclasses)->len; i++) {
    gpointer requestablechannelclasses_item = g_ptr_array_index((GPtrArray*)requestablechannelclasses, i);
    nsCOMPtr<csITpRequestableChannelClass> cRequestableChannelClassesItem;
    csTpRequestableChannelClass::Create((gpointer)requestablechannelclasses_item, getter_AddRefs(cRequestableChannelClassesItem));
    cRequestableChannelClasses->AppendElement(cRequestableChannelClassesItem, PR_FALSE);
  }

  callback->GetPropertyRequestableChannelClassesDone(cRequestableChannelClasses);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceRequests::GetPropertyRequestableChannelClasses(csITpConnectionInterfaceRequestsRequestableChannelClassesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection.Interface.Requests",
      "RequestableChannelClasses",
      cb? RequestableChannelClassesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpConnectionInterfaceRequests::csTpConnectionInterfaceRequests()
{}

csTpConnectionInterfaceRequests::~csTpConnectionInterfaceRequests()
{}
