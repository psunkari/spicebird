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


#include "csTpConnectionInterfaceAliasing.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpAliasMap
 */

NS_IMPL_ISUPPORTS1(csTpAliasMap, csITpAliasMap)

NS_METHOD
csTpAliasMap::Create(PRUint32 aHandle, const nsCString &aAlias, void **aResult)
{
  csITpAliasMap *it = 
          new csTpAliasMap(aHandle, aAlias);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpAliasMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpAliasMap::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    guint handle = GPOINTER_TO_UINT(keyPtr);
    const gchar *alias = (gchar *)valuePtr;

    nsCString cAlias = nsDependentCString(alias);

    csITpAliasMap *temp = new csTpAliasMap(handle, cAlias);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpAliasMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpAliasMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpAliasMap::csTpAliasMap(PRUint32 aHandle, const nsCString &aAlias)
{
  m_Handle = aHandle;
  m_Alias.Assign(aAlias);
}

csTpAliasMap::~csTpAliasMap()
{}

NS_IMETHODIMP
csTpAliasMap::GetHandle(PRUint32 *aHandle)
{
  *aHandle = m_Handle;
  return NS_OK;
}

NS_IMETHODIMP
csTpAliasMap::GetAlias(nsACString &aAlias)
{
  aAlias.Assign(m_Alias);
  return NS_OK;
}

/*
 *  Implementation of csTpAliasPair
 */

NS_IMPL_ISUPPORTS1(csTpAliasPair, csITpAliasPair)

NS_METHOD
csTpAliasPair::Create(PRUint32 aHandle, const nsCString &aAlias, void **aResult)
{
  csITpAliasPair *it = 
          new csTpAliasPair(aHandle, aAlias);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpAliasPair), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpAliasPair::Create(gpointer aGLibItem, void **aResult)
{
  guint handle;
  const gchar *alias;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_ALIAS_PAIR);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &handle, 1, &alias,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cAlias = nsDependentCString(alias);
  csITpAliasPair *it = new csTpAliasPair(handle, cAlias);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpAliasPair), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpAliasPair::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpAliasPair::csTpAliasPair(PRUint32 aHandle, const nsCString &aAlias)
{
  m_Handle = aHandle;
  m_Alias.Assign(aAlias);
}

csTpAliasPair::~csTpAliasPair()
{}

NS_IMETHODIMP
csTpAliasPair::GetHandle(PRUint32 *aHandle)
{
  *aHandle = m_Handle;
  return NS_OK;
}

NS_IMETHODIMP
csTpAliasPair::GetAlias(nsACString &aAlias)
{
  aAlias.Assign(m_Alias);
  return NS_OK;
}

static void
AliasesChangedSignalCallback(TpConnection *proxy,
    const GPtrArray *aliases,
    gpointer user_data, GObject *weak_object)
{
  csTpConnectionInterfaceAliasing *obj = (csTpConnectionInterfaceAliasing *)user_data;
  if (!obj)
    return;

  obj->HandleAliasesChanged(aliases);
}


void
csTpConnectionInterfaceAliasing::HandleAliasesChanged(const GPtrArray *aliases)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_AliasesChangedObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionInterfaceAliasingAliasesChangedObserver> observer;

  nsCOMPtr<nsIMutableArray> cAliases = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)aliases)->len; i++) {
    gpointer aliases_item = g_ptr_array_index((GPtrArray*)aliases, i);
    nsCOMPtr<csITpAliasPair> cAliasesItem;
    csTpAliasPair::Create((gpointer)aliases_item, getter_AddRefs(cAliasesItem));
    cAliases->AppendElement(cAliasesItem, PR_FALSE);
  }

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_AliasesChangedObservers, i);
    observer->OnAliasesChanged(cAliases);
  }
}


NS_IMETHODIMP
csTpConnectionInterfaceAliasing::ConnectToAliasesChanged(csITpConnectionInterfaceAliasingAliasesChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_AliasesChangedObservers) {
    m_AliasesChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_interface_aliasing_connect_to_aliases_changed(m_Proxy,
        AliasesChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_AliasesChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnectionInterfaceAliasing::DisconnectFromAliasesChanged(csITpConnectionInterfaceAliasingAliasesChangedObserver *observer)
{
  if (!m_AliasesChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_AliasesChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_AliasesChangedObservers->RemoveElementAt(idx);
}


static void
GetAliasFlagsResponse(TpConnection *proxy,
    guint alias_flags,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAliasingGetAliasFlagsCB *callback = (csITpConnectionInterfaceAliasingGetAliasFlagsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetAliasFlagsError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnGetAliasFlagsDone(alias_flags);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAliasing::CallGetAliasFlags(csITpConnectionInterfaceAliasingGetAliasFlagsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_aliasing_call_get_alias_flags(m_Proxy, -1,
      cb? GetAliasFlagsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RequestAliasesResponse(TpConnection *proxy,
    const gchar **aliases,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAliasingRequestAliasesCB *callback = (csITpConnectionInterfaceAliasingRequestAliasesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnRequestAliasesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cAliasesCount = 0;
  for (char **pos = (char**)aliases; *pos; pos++, cAliasesCount++);
  char **cAliases = (char **)nsMemory::Alloc(cAliasesCount * sizeof(char*));
  for (PRUint32 i=0; i<cAliasesCount; i++)
    cAliases[i] = (char *)nsMemory::Clone(aliases[i], strlen(aliases[i]) + 1);

  callback->OnRequestAliasesDone(cAliasesCount, (const char **)cAliases);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAliasing::CallRequestAliases(PRUint32 aContactsCount, PRUint32 *aContacts,
    csITpConnectionInterfaceAliasingRequestAliasesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cContacts = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aContactsCount; i++)
    g_array_append_val(cContacts, aContacts[i]);

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_aliasing_call_request_aliases(m_Proxy, -1,
      cContacts,
      cb? RequestAliasesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetAliasesResponse(TpConnection *proxy,
    GHashTable *aliases,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAliasingGetAliasesCB *callback = (csITpConnectionInterfaceAliasingGetAliasesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetAliasesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIArray> cAliases;
  csTpAliasMap::Create((gpointer)aliases, getter_AddRefs(cAliases));

  callback->OnGetAliasesDone(cAliases);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAliasing::CallGetAliases(PRUint32 aContactsCount, PRUint32 *aContacts,
    csITpConnectionInterfaceAliasingGetAliasesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cContacts = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aContactsCount; i++)
    g_array_append_val(cContacts, aContacts[i]);

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_aliasing_call_get_aliases(m_Proxy, -1,
      cContacts,
      cb? GetAliasesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
SetAliasesResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceAliasingSetAliasesCB *callback = (csITpConnectionInterfaceAliasingSetAliasesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnSetAliasesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnSetAliasesDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceAliasing::CallSetAliases(nsIArray *aAliases,
    csITpConnectionInterfaceAliasingSetAliasesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  /* TODO */

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_aliasing_call_set_aliases(m_Proxy, -1,
      NULL,
      cb? SetAliasesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpConnectionInterfaceAliasing::csTpConnectionInterfaceAliasing()
{}

csTpConnectionInterfaceAliasing::~csTpConnectionInterfaceAliasing()
{}
