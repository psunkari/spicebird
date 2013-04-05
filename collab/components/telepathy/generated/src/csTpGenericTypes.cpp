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


#include "csTpGenericTypes.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpQualifiedPropertyValueMap
 */

NS_IMPL_ISUPPORTS1(csTpQualifiedPropertyValueMap, csITpQualifiedPropertyValueMap)

NS_METHOD
csTpQualifiedPropertyValueMap::Create(const nsCString &aKey, nsIVariant *aValue, void **aResult)
{
  csITpQualifiedPropertyValueMap *it = 
          new csTpQualifiedPropertyValueMap(aKey, aValue);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpQualifiedPropertyValueMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpQualifiedPropertyValueMap::Create(gpointer aGLibItem, nsIArray **aResult)
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

    csITpQualifiedPropertyValueMap *temp = new csTpQualifiedPropertyValueMap(cKey, cValue);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpQualifiedPropertyValueMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpQualifiedPropertyValueMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpQualifiedPropertyValueMap::csTpQualifiedPropertyValueMap(const nsCString &aKey, nsIVariant *aValue)
{
  m_Key.Assign(aKey);
  m_Value = aValue;
}

csTpQualifiedPropertyValueMap::~csTpQualifiedPropertyValueMap()
{}

NS_IMETHODIMP
csTpQualifiedPropertyValueMap::GetKey(nsACString &aKey)
{
  aKey.Assign(m_Key);
  return NS_OK;
}

NS_IMETHODIMP
csTpQualifiedPropertyValueMap::GetValue(nsIVariant **aValue)
{
  NS_IF_ADDREF(*aValue = m_Value);
  return NS_OK;
}

/*
 *  Implementation of csTpStringVariantMap
 */

NS_IMPL_ISUPPORTS1(csTpStringVariantMap, csITpStringVariantMap)

NS_METHOD
csTpStringVariantMap::Create(const nsCString &aKey, nsIVariant *aValue, void **aResult)
{
  csITpStringVariantMap *it = 
          new csTpStringVariantMap(aKey, aValue);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpStringVariantMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpStringVariantMap::Create(gpointer aGLibItem, nsIArray **aResult)
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

    csITpStringVariantMap *temp = new csTpStringVariantMap(cKey, cValue);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpStringVariantMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpStringVariantMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpStringVariantMap::csTpStringVariantMap(const nsCString &aKey, nsIVariant *aValue)
{
  m_Key.Assign(aKey);
  m_Value = aValue;
}

csTpStringVariantMap::~csTpStringVariantMap()
{}

NS_IMETHODIMP
csTpStringVariantMap::GetKey(nsACString &aKey)
{
  aKey.Assign(m_Key);
  return NS_OK;
}

NS_IMETHODIMP
csTpStringVariantMap::GetValue(nsIVariant **aValue)
{
  NS_IF_ADDREF(*aValue = m_Value);
  return NS_OK;
}

/*
 *  Implementation of csTpStringStringMap
 */

NS_IMPL_ISUPPORTS1(csTpStringStringMap, csITpStringStringMap)

NS_METHOD
csTpStringStringMap::Create(const nsCString &aKey, const nsCString &aValue, void **aResult)
{
  csITpStringStringMap *it = 
          new csTpStringStringMap(aKey, aValue);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpStringStringMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpStringStringMap::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    const gchar *key = (gchar *)keyPtr;
    const gchar *value = (gchar *)valuePtr;

    nsCString cKey = nsDependentCString(key);
    nsCString cValue = nsDependentCString(value);

    csITpStringStringMap *temp = new csTpStringStringMap(cKey, cValue);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpStringStringMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpStringStringMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpStringStringMap::csTpStringStringMap(const nsCString &aKey, const nsCString &aValue)
{
  m_Key.Assign(aKey);
  m_Value.Assign(aValue);
}

csTpStringStringMap::~csTpStringStringMap()
{}

NS_IMETHODIMP
csTpStringStringMap::GetKey(nsACString &aKey)
{
  aKey.Assign(m_Key);
  return NS_OK;
}

NS_IMETHODIMP
csTpStringStringMap::GetValue(nsACString &aValue)
{
  aValue.Assign(m_Value);
  return NS_OK;
}

/*
 *  Implementation of csTpSocketAddressIP
 */

NS_IMPL_ISUPPORTS1(csTpSocketAddressIP, csITpSocketAddressIP)

NS_METHOD
csTpSocketAddressIP::Create(const nsCString &aAddress, PRUint16 aPort, void **aResult)
{
  csITpSocketAddressIP *it = 
          new csTpSocketAddressIP(aAddress, aPort);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSocketAddressIP), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpSocketAddressIP::Create(gpointer aGLibItem, void **aResult)
{
  const gchar *address;
  guint port;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_SOCKET_ADDRESS_IP);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &address, 1, &port,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cAddress = nsDependentCString(address);
  csITpSocketAddressIP *it = new csTpSocketAddressIP(cAddress, port);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSocketAddressIP), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpSocketAddressIP::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpSocketAddressIP::csTpSocketAddressIP(const nsCString &aAddress, PRUint16 aPort)
{
  m_Address.Assign(aAddress);
  m_Port = aPort;
}

csTpSocketAddressIP::~csTpSocketAddressIP()
{}

NS_IMETHODIMP
csTpSocketAddressIP::GetAddress(nsACString &aAddress)
{
  aAddress.Assign(m_Address);
  return NS_OK;
}

NS_IMETHODIMP
csTpSocketAddressIP::GetPort(PRUint16 *aPort)
{
  *aPort = m_Port;
  return NS_OK;
}

/*
 *  Implementation of csTpSocketAddressIPv4
 */

NS_IMPL_ISUPPORTS1(csTpSocketAddressIPv4, csITpSocketAddressIPv4)

NS_METHOD
csTpSocketAddressIPv4::Create(const nsCString &aAddress, PRUint16 aPort, void **aResult)
{
  csITpSocketAddressIPv4 *it = 
          new csTpSocketAddressIPv4(aAddress, aPort);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSocketAddressIPv4), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpSocketAddressIPv4::Create(gpointer aGLibItem, void **aResult)
{
  const gchar *address;
  guint port;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_SOCKET_ADDRESS_IPV4);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &address, 1, &port,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cAddress = nsDependentCString(address);
  csITpSocketAddressIPv4 *it = new csTpSocketAddressIPv4(cAddress, port);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSocketAddressIPv4), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpSocketAddressIPv4::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpSocketAddressIPv4::csTpSocketAddressIPv4(const nsCString &aAddress, PRUint16 aPort)
{
  m_Address.Assign(aAddress);
  m_Port = aPort;
}

csTpSocketAddressIPv4::~csTpSocketAddressIPv4()
{}

NS_IMETHODIMP
csTpSocketAddressIPv4::GetAddress(nsACString &aAddress)
{
  aAddress.Assign(m_Address);
  return NS_OK;
}

NS_IMETHODIMP
csTpSocketAddressIPv4::GetPort(PRUint16 *aPort)
{
  *aPort = m_Port;
  return NS_OK;
}

/*
 *  Implementation of csTpSocketAddressIPv6
 */

NS_IMPL_ISUPPORTS1(csTpSocketAddressIPv6, csITpSocketAddressIPv6)

NS_METHOD
csTpSocketAddressIPv6::Create(const nsCString &aAddress, PRUint16 aPort, void **aResult)
{
  csITpSocketAddressIPv6 *it = 
          new csTpSocketAddressIPv6(aAddress, aPort);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSocketAddressIPv6), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpSocketAddressIPv6::Create(gpointer aGLibItem, void **aResult)
{
  const gchar *address;
  guint port;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_SOCKET_ADDRESS_IPV6);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &address, 1, &port,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cAddress = nsDependentCString(address);
  csITpSocketAddressIPv6 *it = new csTpSocketAddressIPv6(cAddress, port);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSocketAddressIPv6), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpSocketAddressIPv6::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpSocketAddressIPv6::csTpSocketAddressIPv6(const nsCString &aAddress, PRUint16 aPort)
{
  m_Address.Assign(aAddress);
  m_Port = aPort;
}

csTpSocketAddressIPv6::~csTpSocketAddressIPv6()
{}

NS_IMETHODIMP
csTpSocketAddressIPv6::GetAddress(nsACString &aAddress)
{
  aAddress.Assign(m_Address);
  return NS_OK;
}

NS_IMETHODIMP
csTpSocketAddressIPv6::GetPort(PRUint16 *aPort)
{
  *aPort = m_Port;
  return NS_OK;
}

/*
 *  Implementation of csTpSocketNetmaskIPv4
 */

NS_IMPL_ISUPPORTS1(csTpSocketNetmaskIPv4, csITpSocketNetmaskIPv4)

NS_METHOD
csTpSocketNetmaskIPv4::Create(const nsCString &aAddress, PRUint8 aPrefixLength, void **aResult)
{
  csITpSocketNetmaskIPv4 *it = 
          new csTpSocketNetmaskIPv4(aAddress, aPrefixLength);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSocketNetmaskIPv4), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpSocketNetmaskIPv4::Create(gpointer aGLibItem, void **aResult)
{
  const gchar *address;
  guchar prefix_length;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_SOCKET_NETMASK_IPV4);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &address, 1, &prefix_length,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cAddress = nsDependentCString(address);
  csITpSocketNetmaskIPv4 *it = new csTpSocketNetmaskIPv4(cAddress, prefix_length);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSocketNetmaskIPv4), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpSocketNetmaskIPv4::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpSocketNetmaskIPv4::csTpSocketNetmaskIPv4(const nsCString &aAddress, PRUint8 aPrefixLength)
{
  m_Address.Assign(aAddress);
  m_PrefixLength = aPrefixLength;
}

csTpSocketNetmaskIPv4::~csTpSocketNetmaskIPv4()
{}

NS_IMETHODIMP
csTpSocketNetmaskIPv4::GetAddress(nsACString &aAddress)
{
  aAddress.Assign(m_Address);
  return NS_OK;
}

NS_IMETHODIMP
csTpSocketNetmaskIPv4::GetPrefixLength(PRUint8 *aPrefixLength)
{
  *aPrefixLength = m_PrefixLength;
  return NS_OK;
}

/*
 *  Implementation of csTpSocketNetmaskIPv6
 */

NS_IMPL_ISUPPORTS1(csTpSocketNetmaskIPv6, csITpSocketNetmaskIPv6)

NS_METHOD
csTpSocketNetmaskIPv6::Create(const nsCString &aAddress, PRUint8 aPrefixLength, void **aResult)
{
  csITpSocketNetmaskIPv6 *it = 
          new csTpSocketNetmaskIPv6(aAddress, aPrefixLength);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSocketNetmaskIPv6), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpSocketNetmaskIPv6::Create(gpointer aGLibItem, void **aResult)
{
  const gchar *address;
  guchar prefix_length;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_SOCKET_NETMASK_IPV6);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &address, 1, &prefix_length,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cAddress = nsDependentCString(address);
  csITpSocketNetmaskIPv6 *it = new csTpSocketNetmaskIPv6(cAddress, prefix_length);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSocketNetmaskIPv6), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpSocketNetmaskIPv6::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpSocketNetmaskIPv6::csTpSocketNetmaskIPv6(const nsCString &aAddress, PRUint8 aPrefixLength)
{
  m_Address.Assign(aAddress);
  m_PrefixLength = aPrefixLength;
}

csTpSocketNetmaskIPv6::~csTpSocketNetmaskIPv6()
{}

NS_IMETHODIMP
csTpSocketNetmaskIPv6::GetAddress(nsACString &aAddress)
{
  aAddress.Assign(m_Address);
  return NS_OK;
}

NS_IMETHODIMP
csTpSocketNetmaskIPv6::GetPrefixLength(PRUint8 *aPrefixLength)
{
  *aPrefixLength = m_PrefixLength;
  return NS_OK;
}
