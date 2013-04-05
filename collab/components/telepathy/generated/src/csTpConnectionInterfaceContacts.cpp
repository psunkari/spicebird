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


#include "csTpConnectionInterfaceContacts.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpSingleContactAttributesMap
 */

NS_IMPL_ISUPPORTS1(csTpSingleContactAttributesMap, csITpSingleContactAttributesMap)

NS_METHOD
csTpSingleContactAttributesMap::Create(const nsCString &aName, nsIVariant *aValue, void **aResult)
{
  csITpSingleContactAttributesMap *it = 
          new csTpSingleContactAttributesMap(aName, aValue);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSingleContactAttributesMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpSingleContactAttributesMap::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    const gchar *name = (gchar *)keyPtr;
    const GValue *value = (GValue *)valuePtr;

    nsCString cName = nsDependentCString(name);
    nsCOMPtr<nsIVariant> cValue;
    GValueToVariant(value, getter_AddRefs(cValue));

    csITpSingleContactAttributesMap *temp = new csTpSingleContactAttributesMap(cName, cValue);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpSingleContactAttributesMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpSingleContactAttributesMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpSingleContactAttributesMap::csTpSingleContactAttributesMap(const nsCString &aName, nsIVariant *aValue)
{
  m_Name.Assign(aName);
  m_Value = aValue;
}

csTpSingleContactAttributesMap::~csTpSingleContactAttributesMap()
{}

NS_IMETHODIMP
csTpSingleContactAttributesMap::GetName(nsACString &aName)
{
  aName.Assign(m_Name);
  return NS_OK;
}

NS_IMETHODIMP
csTpSingleContactAttributesMap::GetValue(nsIVariant **aValue)
{
  NS_IF_ADDREF(*aValue = m_Value);
  return NS_OK;
}

/*
 *  Implementation of csTpContactAttributesMap
 */

NS_IMPL_ISUPPORTS1(csTpContactAttributesMap, csITpContactAttributesMap)

NS_METHOD
csTpContactAttributesMap::Create(PRUint32 aContact, nsIArray *aAttributes, void **aResult)
{
  csITpContactAttributesMap *it = 
          new csTpContactAttributesMap(aContact, aAttributes);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpContactAttributesMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpContactAttributesMap::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    guint contact = GPOINTER_TO_UINT(keyPtr);
    GHashTable *attributes = (GHashTable *)valuePtr;

    nsCOMPtr<nsIArray> cAttributes;
    csTpSingleContactAttributesMap::Create((gpointer)attributes, getter_AddRefs(cAttributes));

    csITpContactAttributesMap *temp = new csTpContactAttributesMap(contact, cAttributes);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpContactAttributesMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpContactAttributesMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpContactAttributesMap::csTpContactAttributesMap(PRUint32 aContact, nsIArray *aAttributes)
{
  m_Contact = aContact;
  m_Attributes = aAttributes;
}

csTpContactAttributesMap::~csTpContactAttributesMap()
{}

NS_IMETHODIMP
csTpContactAttributesMap::GetContact(PRUint32 *aContact)
{
  *aContact = m_Contact;
  return NS_OK;
}

NS_IMETHODIMP
csTpContactAttributesMap::GetAttributes(nsIArray **aAttributes)
{
  NS_IF_ADDREF(*aAttributes = m_Attributes);
  return NS_OK;
}

static void
ContactAttributeInterfacesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceContactsContactAttributeInterfacesCB *callback = (csITpConnectionInterfaceContactsContactAttributeInterfacesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyContactAttributeInterfacesError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar ** contactattributeinterfaces;
  contactattributeinterfaces = (gchar **)g_value_get_boxed(out);
  PRUint32 cContactAttributeInterfacesCount = 0;
  for (char **pos = (char**)contactattributeinterfaces; *pos; pos++, cContactAttributeInterfacesCount++);
  char **cContactAttributeInterfaces = (char **)nsMemory::Alloc(cContactAttributeInterfacesCount * sizeof(char*));
  for (PRUint32 i=0; i<cContactAttributeInterfacesCount; i++)
    cContactAttributeInterfaces[i] = (char *)nsMemory::Clone(contactattributeinterfaces[i], strlen(contactattributeinterfaces[i]) + 1);

  callback->GetPropertyContactAttributeInterfacesDone(cContactAttributeInterfacesCount, (const char **)cContactAttributeInterfaces);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceContacts::GetPropertyContactAttributeInterfaces(csITpConnectionInterfaceContactsContactAttributeInterfacesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection.Interface.Contacts",
      "ContactAttributeInterfaces",
      cb? ContactAttributeInterfacesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetContactAttributesResponse(TpConnection *proxy,
    GHashTable *attributes,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceContactsGetContactAttributesCB *callback = (csITpConnectionInterfaceContactsGetContactAttributesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetContactAttributesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIArray> cAttributes;
  csTpContactAttributesMap::Create((gpointer)attributes, getter_AddRefs(cAttributes));

  callback->OnGetContactAttributesDone(cAttributes);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceContacts::CallGetContactAttributes(PRUint32 aHandlesCount, PRUint32 *aHandles, PRUint32 aInterfacesCount, const char **aInterfaces, PRBool aHold,
    csITpConnectionInterfaceContactsGetContactAttributesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cHandles = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aHandlesCount; i++)
    g_array_append_val(cHandles, aHandles[i]);
  char **cInterfaces = (char **)nsMemory::Alloc((aInterfacesCount + 1) * sizeof(char*));
  for (PRUint32 i=0; i<aInterfacesCount; i++)
    cInterfaces[i] = (char *)nsMemory::Clone(aInterfaces[i], strlen(aInterfaces[i]) + 1);
  cInterfaces[aInterfacesCount] = NULL;

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_contacts_call_get_contact_attributes(m_Proxy, -1,
      cHandles, (const char**) cInterfaces, aHold,
      cb? GetContactAttributesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpConnectionInterfaceContacts::csTpConnectionInterfaceContacts()
{}

csTpConnectionInterfaceContacts::~csTpConnectionInterfaceContacts()
{}
