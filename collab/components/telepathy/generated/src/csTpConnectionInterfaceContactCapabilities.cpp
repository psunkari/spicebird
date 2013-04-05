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


#include "csTpConnectionInterfaceContactCapabilities.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
#include "csTpConnectionInterfaceRequests.h"
/*
 *  Implementation of csTpHandlerCapabilities
 */

NS_IMPL_ISUPPORTS1(csTpHandlerCapabilities, csITpHandlerCapabilities)

NS_METHOD
csTpHandlerCapabilities::Create(const nsCString &aWellKnownName, nsIArray *aChannelClasses, PRUint32 aCapabilitiesCount, const char **aCapabilities, void **aResult)
{
  csITpHandlerCapabilities *it = 
          new csTpHandlerCapabilities(aWellKnownName, aChannelClasses, aCapabilitiesCount, aCapabilities);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpHandlerCapabilities), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpHandlerCapabilities::Create(gpointer aGLibItem, void **aResult)
{
  const gchar *well_known_name;
  const GPtrArray *channel_classes;
  const gchar **capabilities;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_HANDLER_CAPABILITIES);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &well_known_name, 1, &channel_classes, 2, &capabilities,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cWellKnownName = nsDependentCString(well_known_name);
  nsCOMPtr<nsIMutableArray> cChannelClasses = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)channel_classes)->len; i++) {
    gpointer channel_classes_item = g_ptr_array_index((GPtrArray*)channel_classes, i);
    nsCOMPtr<nsIArray> cChannelClassesItem;
    csTpStringVariantMap::Create((gpointer)channel_classes_item, getter_AddRefs(cChannelClassesItem));
    cChannelClasses->AppendElement(cChannelClassesItem, PR_FALSE);
  }
  PRUint32 cCapabilitiesCount = 0;
  for (char **pos = (char**)capabilities; *pos; pos++, cCapabilitiesCount++);
  char **cCapabilities = (char **)nsMemory::Alloc(cCapabilitiesCount * sizeof(char*));
  for (PRUint32 i=0; i<cCapabilitiesCount; i++)
    cCapabilities[i] = (char *)nsMemory::Clone(capabilities[i], strlen(capabilities[i]) + 1);
  csITpHandlerCapabilities *it = new csTpHandlerCapabilities(cWellKnownName, cChannelClasses, cCapabilitiesCount, (const char **)cCapabilities);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpHandlerCapabilities), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpHandlerCapabilities::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpHandlerCapabilities::csTpHandlerCapabilities(const nsCString &aWellKnownName, nsIArray *aChannelClasses, PRUint32 aCapabilitiesCount, const char **aCapabilities)
{
  m_WellKnownName.Assign(aWellKnownName);
  m_ChannelClasses = aChannelClasses;
  m_CapabilitiesCount = aCapabilitiesCount; m_Capabilities = (char **)aCapabilities;
}

csTpHandlerCapabilities::~csTpHandlerCapabilities()
{}

NS_IMETHODIMP
csTpHandlerCapabilities::GetWellKnownName(nsACString &aWellKnownName)
{
  aWellKnownName.Assign(m_WellKnownName);
  return NS_OK;
}

NS_IMETHODIMP
csTpHandlerCapabilities::GetChannelClasses(nsIArray **aChannelClasses)
{
  NS_IF_ADDREF(*aChannelClasses = m_ChannelClasses);
  return NS_OK;
}

NS_IMETHODIMP
csTpHandlerCapabilities::GetCapabilities(PRUint32 *aCapabilitiesCount, char ***aCapabilities)
{
  *aCapabilitiesCount = m_CapabilitiesCount; *aCapabilities = m_Capabilities;
  return NS_OK;
}

static void
UpdateCapabilitiesResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceContactCapabilitiesUpdateCapabilitiesCB *callback = (csITpConnectionInterfaceContactCapabilitiesUpdateCapabilitiesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnUpdateCapabilitiesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnUpdateCapabilitiesDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceContactCapabilities::CallUpdateCapabilities(nsIArray *aHandlerCapabilities,
    csITpConnectionInterfaceContactCapabilitiesUpdateCapabilitiesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  /* TODO */

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_contact_capabilities_call_update_capabilities(m_Proxy, -1,
      NULL,
      cb? UpdateCapabilitiesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetContactCapabilitiesResponse(TpConnection *proxy,
    GHashTable *contact_capabilities,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceContactCapabilitiesGetContactCapabilitiesCB *callback = (csITpConnectionInterfaceContactCapabilitiesGetContactCapabilitiesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetContactCapabilitiesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIArray> cContactCapabilities;
  csTpContactCapabilitiesMap::Create((gpointer)contact_capabilities, getter_AddRefs(cContactCapabilities));

  callback->OnGetContactCapabilitiesDone(cContactCapabilities);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceContactCapabilities::CallGetContactCapabilities(PRUint32 ahandlesCount, PRUint32 *ahandles,
    csITpConnectionInterfaceContactCapabilitiesGetContactCapabilitiesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *chandles = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<ahandlesCount; i++)
    g_array_append_val(chandles, ahandles[i]);

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_contact_capabilities_call_get_contact_capabilities(m_Proxy, -1,
      chandles,
      cb? GetContactCapabilitiesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ContactCapabilitiesChangedSignalCallback(TpConnection *proxy,
    GHashTable *caps,
    gpointer user_data, GObject *weak_object)
{
  csTpConnectionInterfaceContactCapabilities *obj = (csTpConnectionInterfaceContactCapabilities *)user_data;
  if (!obj)
    return;

  obj->HandleContactCapabilitiesChanged(caps);
}


void
csTpConnectionInterfaceContactCapabilities::HandleContactCapabilitiesChanged(GHashTable *caps)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_ContactCapabilitiesChangedObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionInterfaceContactCapabilitiesContactCapabilitiesChangedObserver> observer;

  nsCOMPtr<nsIArray> ccaps;
  csTpContactCapabilitiesMap::Create((gpointer)caps, getter_AddRefs(ccaps));

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_ContactCapabilitiesChangedObservers, i);
    observer->OnContactCapabilitiesChanged(ccaps);
  }
}


NS_IMETHODIMP
csTpConnectionInterfaceContactCapabilities::ConnectToContactCapabilitiesChanged(csITpConnectionInterfaceContactCapabilitiesContactCapabilitiesChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_ContactCapabilitiesChangedObservers) {
    m_ContactCapabilitiesChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_interface_contact_capabilities_connect_to_contact_capabilities_changed(m_Proxy,
        ContactCapabilitiesChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_ContactCapabilitiesChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnectionInterfaceContactCapabilities::DisconnectFromContactCapabilitiesChanged(csITpConnectionInterfaceContactCapabilitiesContactCapabilitiesChangedObserver *observer)
{
  if (!m_ContactCapabilitiesChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_ContactCapabilitiesChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_ContactCapabilitiesChangedObservers->RemoveElementAt(idx);
}


/*
 *  Implementation of csTpContactCapabilitiesMap
 */

NS_IMPL_ISUPPORTS1(csTpContactCapabilitiesMap, csITpContactCapabilitiesMap)

NS_METHOD
csTpContactCapabilitiesMap::Create(PRUint32 aKey, nsIArray *aValue, void **aResult)
{
  csITpContactCapabilitiesMap *it = 
          new csTpContactCapabilitiesMap(aKey, aValue);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpContactCapabilitiesMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpContactCapabilitiesMap::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    guint key = GPOINTER_TO_UINT(keyPtr);
    const GPtrArray *value = (GPtrArray *)valuePtr;

    nsCOMPtr<nsIMutableArray> cValue = do_CreateInstance(NS_ARRAY_CONTRACTID);
    for (PRUint32 i=0; i<((GPtrArray*)value)->len; i++) {
      gpointer value_item = g_ptr_array_index((GPtrArray*)value, i);
      nsCOMPtr<csITpRequestableChannelClass> cValueItem;
      csTpRequestableChannelClass::Create((gpointer)value_item, getter_AddRefs(cValueItem));
      cValue->AppendElement(cValueItem, PR_FALSE);
    }

    csITpContactCapabilitiesMap *temp = new csTpContactCapabilitiesMap(key, cValue);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpContactCapabilitiesMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpContactCapabilitiesMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpContactCapabilitiesMap::csTpContactCapabilitiesMap(PRUint32 aKey, nsIArray *aValue)
{
  m_Key = aKey;
  m_Value = aValue;
}

csTpContactCapabilitiesMap::~csTpContactCapabilitiesMap()
{}

NS_IMETHODIMP
csTpContactCapabilitiesMap::GetKey(PRUint32 *aKey)
{
  *aKey = m_Key;
  return NS_OK;
}

NS_IMETHODIMP
csTpContactCapabilitiesMap::GetValue(nsIArray **aValue)
{
  NS_IF_ADDREF(*aValue = m_Value);
  return NS_OK;
}


csTpConnectionInterfaceContactCapabilities::csTpConnectionInterfaceContactCapabilities()
{}

csTpConnectionInterfaceContactCapabilities::~csTpConnectionInterfaceContactCapabilities()
{}
