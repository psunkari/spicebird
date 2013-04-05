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


#include "csTpConnectionInterfaceLocation.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
#include "csTpConnectionInterfaceSimplePresence.h"
/*
 *  Implementation of csTpLocation
 */

NS_IMPL_ISUPPORTS1(csTpLocation, csITpLocation)

NS_METHOD
csTpLocation::Create(const nsCString &aKey, nsIVariant *aValue, void **aResult)
{
  csITpLocation *it = 
          new csTpLocation(aKey, aValue);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpLocation), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpLocation::Create(gpointer aGLibItem, nsIArray **aResult)
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

    csITpLocation *temp = new csTpLocation(cKey, cValue);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpLocation> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpLocation::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpLocation::csTpLocation(const nsCString &aKey, nsIVariant *aValue)
{
  m_Key.Assign(aKey);
  m_Value = aValue;
}

csTpLocation::~csTpLocation()
{}

NS_IMETHODIMP
csTpLocation::GetKey(nsACString &aKey)
{
  aKey.Assign(m_Key);
  return NS_OK;
}

NS_IMETHODIMP
csTpLocation::GetValue(nsIVariant **aValue)
{
  NS_IF_ADDREF(*aValue = m_Value);
  return NS_OK;
}

/*
 *  Implementation of csTpContactLocations
 */

NS_IMPL_ISUPPORTS1(csTpContactLocations, csITpContactLocations)

NS_METHOD
csTpContactLocations::Create(PRUint32 aContact, nsIArray *aLocation, void **aResult)
{
  csITpContactLocations *it = 
          new csTpContactLocations(aContact, aLocation);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpContactLocations), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpContactLocations::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    guint contact = GPOINTER_TO_UINT(keyPtr);
    GHashTable *location = (GHashTable *)valuePtr;

    nsCOMPtr<nsIArray> cLocation;
    csTpLocation::Create((gpointer)location, getter_AddRefs(cLocation));

    csITpContactLocations *temp = new csTpContactLocations(contact, cLocation);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpContactLocations> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpContactLocations::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpContactLocations::csTpContactLocations(PRUint32 aContact, nsIArray *aLocation)
{
  m_Contact = aContact;
  m_Location = aLocation;
}

csTpContactLocations::~csTpContactLocations()
{}

NS_IMETHODIMP
csTpContactLocations::GetContact(PRUint32 *aContact)
{
  *aContact = m_Contact;
  return NS_OK;
}

NS_IMETHODIMP
csTpContactLocations::GetLocation(nsIArray **aLocation)
{
  NS_IF_ADDREF(*aLocation = m_Location);
  return NS_OK;
}

static void
GetLocationsResponse(TpConnection *proxy,
    GHashTable *locations,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceLocationGetLocationsCB *callback = (csITpConnectionInterfaceLocationGetLocationsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetLocationsError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIArray> cLocations;
  csTpContactLocations::Create((gpointer)locations, getter_AddRefs(cLocations));

  callback->OnGetLocationsDone(cLocations);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceLocation::CallGetLocations(PRUint32 aContactsCount, PRUint32 *aContacts,
    csITpConnectionInterfaceLocationGetLocationsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cContacts = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aContactsCount; i++)
    g_array_append_val(cContacts, aContacts[i]);

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_location_call_get_locations(m_Proxy, -1,
      cContacts,
      cb? GetLocationsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RequestLocationResponse(TpConnection *proxy,
    GHashTable *location,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceLocationRequestLocationCB *callback = (csITpConnectionInterfaceLocationRequestLocationCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnRequestLocationError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIArray> cLocation;
  csTpLocation::Create((gpointer)location, getter_AddRefs(cLocation));

  callback->OnRequestLocationDone(cLocation);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceLocation::CallRequestLocation(PRUint32 aContact,
    csITpConnectionInterfaceLocationRequestLocationCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_location_call_request_location(m_Proxy, -1,
      aContact,
      cb? RequestLocationResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
LocationUpdatedSignalCallback(TpConnection *proxy,
    guint contact, GHashTable *location,
    gpointer user_data, GObject *weak_object)
{
  csTpConnectionInterfaceLocation *obj = (csTpConnectionInterfaceLocation *)user_data;
  if (!obj)
    return;

  obj->HandleLocationUpdated(contact, location);
}


void
csTpConnectionInterfaceLocation::HandleLocationUpdated(guint contact, GHashTable *location)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_LocationUpdatedObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionInterfaceLocationLocationUpdatedObserver> observer;

  nsCOMPtr<nsIArray> cLocation;
  csTpLocation::Create((gpointer)location, getter_AddRefs(cLocation));

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_LocationUpdatedObservers, i);
    observer->OnLocationUpdated(contact, cLocation);
  }
}


NS_IMETHODIMP
csTpConnectionInterfaceLocation::ConnectToLocationUpdated(csITpConnectionInterfaceLocationLocationUpdatedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_LocationUpdatedObservers) {
    m_LocationUpdatedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_interface_location_connect_to_location_updated(m_Proxy,
        LocationUpdatedSignalCallback, this, NULL, NULL, NULL);
  }

  m_LocationUpdatedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnectionInterfaceLocation::DisconnectFromLocationUpdated(csITpConnectionInterfaceLocationLocationUpdatedObserver *observer)
{
  if (!m_LocationUpdatedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_LocationUpdatedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_LocationUpdatedObservers->RemoveElementAt(idx);
}


static void
SetLocationResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceLocationSetLocationCB *callback = (csITpConnectionInterfaceLocationSetLocationCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnSetLocationError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnSetLocationDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceLocation::CallSetLocation(nsIArray *aLocation,
    csITpConnectionInterfaceLocationSetLocationCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  /* TODO */

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_location_call_set_location(m_Proxy, -1,
      NULL,
      cb? SetLocationResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
LocationAccessControlTypesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceLocationLocationAccessControlTypesCB *callback = (csITpConnectionInterfaceLocationLocationAccessControlTypesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyLocationAccessControlTypesError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GArray * locationaccesscontroltypes;
  locationaccesscontroltypes = (GArray *)g_value_get_boxed(out);
  PRUint32 cLocationAccessControlTypesCount = locationaccesscontroltypes->len;
  PRUint32 *cLocationAccessControlTypes = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cLocationAccessControlTypesCount);
  for (unsigned int i=0; i<cLocationAccessControlTypesCount; i++)
    cLocationAccessControlTypes[i] = g_array_index(locationaccesscontroltypes, guint, i);

  callback->GetPropertyLocationAccessControlTypesDone(cLocationAccessControlTypesCount, cLocationAccessControlTypes);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceLocation::GetPropertyLocationAccessControlTypes(csITpConnectionInterfaceLocationLocationAccessControlTypesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection.Interface.Location",
      "LocationAccessControlTypes",
      cb? LocationAccessControlTypesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
LocationAccessControlResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceLocationLocationAccessControlCB *callback = (csITpConnectionInterfaceLocationLocationAccessControlCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyLocationAccessControlError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GValueArray * locationaccesscontrol;
  locationaccesscontrol = (GValueArray *)g_value_get_boxed(out);
  nsCOMPtr<csITpRichPresenceAccessControl> cLocationAccessControl;
  csTpRichPresenceAccessControl::Create((gpointer)locationaccesscontrol, getter_AddRefs(cLocationAccessControl));

  callback->GetPropertyLocationAccessControlDone(cLocationAccessControl);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceLocation::GetPropertyLocationAccessControl(csITpConnectionInterfaceLocationLocationAccessControlCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection.Interface.Location",
      "LocationAccessControl",
      cb? LocationAccessControlResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpConnectionInterfaceLocation::csTpConnectionInterfaceLocation()
{}

csTpConnectionInterfaceLocation::~csTpConnectionInterfaceLocation()
{}
