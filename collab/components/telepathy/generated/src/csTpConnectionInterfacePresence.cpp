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


#include "csTpConnectionInterfacePresence.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpMultipleStatusMap
 */

NS_IMPL_ISUPPORTS1(csTpMultipleStatusMap, csITpMultipleStatusMap)

NS_METHOD
csTpMultipleStatusMap::Create(const nsCString &aStatus, nsIArray *aParameters, void **aResult)
{
  csITpMultipleStatusMap *it = 
          new csTpMultipleStatusMap(aStatus, aParameters);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpMultipleStatusMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpMultipleStatusMap::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    const gchar *status = (gchar *)keyPtr;
    GHashTable *parameters = (GHashTable *)valuePtr;

    nsCString cStatus = nsDependentCString(status);
    nsCOMPtr<nsIArray> cParameters;
    csTpStringVariantMap::Create((gpointer)parameters, getter_AddRefs(cParameters));

    csITpMultipleStatusMap *temp = new csTpMultipleStatusMap(cStatus, cParameters);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpMultipleStatusMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpMultipleStatusMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpMultipleStatusMap::csTpMultipleStatusMap(const nsCString &aStatus, nsIArray *aParameters)
{
  m_Status.Assign(aStatus);
  m_Parameters = aParameters;
}

csTpMultipleStatusMap::~csTpMultipleStatusMap()
{}

NS_IMETHODIMP
csTpMultipleStatusMap::GetStatus(nsACString &aStatus)
{
  aStatus.Assign(m_Status);
  return NS_OK;
}

NS_IMETHODIMP
csTpMultipleStatusMap::GetParameters(nsIArray **aParameters)
{
  NS_IF_ADDREF(*aParameters = m_Parameters);
  return NS_OK;
}

/*
 *  Implementation of csTpLastActivityAndStatuses
 */

NS_IMPL_ISUPPORTS1(csTpLastActivityAndStatuses, csITpLastActivityAndStatuses)

NS_METHOD
csTpLastActivityAndStatuses::Create(PRUint32 aLastActivity, nsIArray *aStatuses, void **aResult)
{
  csITpLastActivityAndStatuses *it = 
          new csTpLastActivityAndStatuses(aLastActivity, aStatuses);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpLastActivityAndStatuses), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpLastActivityAndStatuses::Create(gpointer aGLibItem, void **aResult)
{
  guint last_activity;
  GHashTable *statuses;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_LAST_ACTIVITY_AND_STATUSES);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &last_activity, 1, &statuses,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCOMPtr<nsIArray> cStatuses;
  csTpMultipleStatusMap::Create((gpointer)statuses, getter_AddRefs(cStatuses));
  csITpLastActivityAndStatuses *it = new csTpLastActivityAndStatuses(last_activity, cStatuses);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpLastActivityAndStatuses), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpLastActivityAndStatuses::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpLastActivityAndStatuses::csTpLastActivityAndStatuses(PRUint32 aLastActivity, nsIArray *aStatuses)
{
  m_LastActivity = aLastActivity;
  m_Statuses = aStatuses;
}

csTpLastActivityAndStatuses::~csTpLastActivityAndStatuses()
{}

NS_IMETHODIMP
csTpLastActivityAndStatuses::GetLastActivity(PRUint32 *aLastActivity)
{
  *aLastActivity = m_LastActivity;
  return NS_OK;
}

NS_IMETHODIMP
csTpLastActivityAndStatuses::GetStatuses(nsIArray **aStatuses)
{
  NS_IF_ADDREF(*aStatuses = m_Statuses);
  return NS_OK;
}

/*
 *  Implementation of csTpContactPresences
 */

NS_IMPL_ISUPPORTS1(csTpContactPresences, csITpContactPresences)

NS_METHOD
csTpContactPresences::Create(PRUint32 aContact, nsISupports *aPresence, void **aResult)
{
  csITpContactPresences *it = 
          new csTpContactPresences(aContact, aPresence);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpContactPresences), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpContactPresences::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    guint contact = GPOINTER_TO_UINT(keyPtr);
    const GValueArray *presence = (GValueArray *)valuePtr;

    nsCOMPtr<csITpLastActivityAndStatuses> cPresence;
    csTpLastActivityAndStatuses::Create((gpointer)presence, getter_AddRefs(cPresence));

    csITpContactPresences *temp = new csTpContactPresences(contact, cPresence);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpContactPresences> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpContactPresences::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpContactPresences::csTpContactPresences(PRUint32 aContact, nsISupports *aPresence)
{
  m_Contact = aContact;
  m_Presence = aPresence;
}

csTpContactPresences::~csTpContactPresences()
{}

NS_IMETHODIMP
csTpContactPresences::GetContact(PRUint32 *aContact)
{
  *aContact = m_Contact;
  return NS_OK;
}

NS_IMETHODIMP
csTpContactPresences::GetPresence(nsISupports **aPresence)
{
  NS_IF_ADDREF(*aPresence = m_Presence);
  return NS_OK;
}

/*
 *  Implementation of csTpStatusSpec
 */

NS_IMPL_ISUPPORTS1(csTpStatusSpec, csITpStatusSpec)

NS_METHOD
csTpStatusSpec::Create(PRUint32 aType, PRBool aMaySetOnSelf, PRBool aExclusive, nsIArray *aParameterTypes, void **aResult)
{
  csITpStatusSpec *it = 
          new csTpStatusSpec(aType, aMaySetOnSelf, aExclusive, aParameterTypes);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpStatusSpec), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpStatusSpec::Create(gpointer aGLibItem, void **aResult)
{
  guint type;
  gboolean may_set_on_self;
  gboolean exclusive;
  GHashTable *parameter_types;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_STATUS_SPEC);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &type, 1, &may_set_on_self, 2, &exclusive, 3, &parameter_types,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCOMPtr<nsIArray> cParameterTypes;
  csTpStringStringMap::Create((gpointer)parameter_types, getter_AddRefs(cParameterTypes));
  csITpStatusSpec *it = new csTpStatusSpec(type, may_set_on_self, exclusive, cParameterTypes);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpStatusSpec), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpStatusSpec::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpStatusSpec::csTpStatusSpec(PRUint32 aType, PRBool aMaySetOnSelf, PRBool aExclusive, nsIArray *aParameterTypes)
{
  m_Type = aType;
  m_MaySetOnSelf = aMaySetOnSelf;
  m_Exclusive = aExclusive;
  m_ParameterTypes = aParameterTypes;
}

csTpStatusSpec::~csTpStatusSpec()
{}

NS_IMETHODIMP
csTpStatusSpec::GetType(PRUint32 *aType)
{
  *aType = m_Type;
  return NS_OK;
}

NS_IMETHODIMP
csTpStatusSpec::GetMaySetOnSelf(PRBool *aMaySetOnSelf)
{
  *aMaySetOnSelf = m_MaySetOnSelf;
  return NS_OK;
}

NS_IMETHODIMP
csTpStatusSpec::GetExclusive(PRBool *aExclusive)
{
  *aExclusive = m_Exclusive;
  return NS_OK;
}

NS_IMETHODIMP
csTpStatusSpec::GetParameterTypes(nsIArray **aParameterTypes)
{
  NS_IF_ADDREF(*aParameterTypes = m_ParameterTypes);
  return NS_OK;
}

/*
 *  Implementation of csTpStatusSpecMap
 */

NS_IMPL_ISUPPORTS1(csTpStatusSpecMap, csITpStatusSpecMap)

NS_METHOD
csTpStatusSpecMap::Create(const nsCString &aIdentifier, nsISupports *aSpec, void **aResult)
{
  csITpStatusSpecMap *it = 
          new csTpStatusSpecMap(aIdentifier, aSpec);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpStatusSpecMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpStatusSpecMap::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    const gchar *identifier = (gchar *)keyPtr;
    const GValueArray *spec = (GValueArray *)valuePtr;

    nsCString cIdentifier = nsDependentCString(identifier);
    nsCOMPtr<csITpStatusSpec> cSpec;
    csTpStatusSpec::Create((gpointer)spec, getter_AddRefs(cSpec));

    csITpStatusSpecMap *temp = new csTpStatusSpecMap(cIdentifier, cSpec);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpStatusSpecMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpStatusSpecMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpStatusSpecMap::csTpStatusSpecMap(const nsCString &aIdentifier, nsISupports *aSpec)
{
  m_Identifier.Assign(aIdentifier);
  m_Spec = aSpec;
}

csTpStatusSpecMap::~csTpStatusSpecMap()
{}

NS_IMETHODIMP
csTpStatusSpecMap::GetIdentifier(nsACString &aIdentifier)
{
  aIdentifier.Assign(m_Identifier);
  return NS_OK;
}

NS_IMETHODIMP
csTpStatusSpecMap::GetSpec(nsISupports **aSpec)
{
  NS_IF_ADDREF(*aSpec = m_Spec);
  return NS_OK;
}

static void
AddStatusResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfacePresenceAddStatusCB *callback = (csITpConnectionInterfacePresenceAddStatusCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnAddStatusError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnAddStatusDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfacePresence::CallAddStatus(const nsACString &aStatus, nsIArray *aParameters,
    csITpConnectionInterfacePresenceAddStatusCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  char *cStatus = ToNewCString(aStatus);
  /* TODO */

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_presence_call_add_status(m_Proxy, -1,
      cStatus, NULL,
      cb? AddStatusResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ClearStatusResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfacePresenceClearStatusCB *callback = (csITpConnectionInterfacePresenceClearStatusCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnClearStatusError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnClearStatusDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfacePresence::CallClearStatus(csITpConnectionInterfacePresenceClearStatusCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_presence_call_clear_status(m_Proxy, -1,
      cb? ClearStatusResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetPresenceResponse(TpConnection *proxy,
    GHashTable *presence,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfacePresenceGetPresenceCB *callback = (csITpConnectionInterfacePresenceGetPresenceCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetPresenceError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIArray> cPresence;
  csTpContactPresences::Create((gpointer)presence, getter_AddRefs(cPresence));

  callback->OnGetPresenceDone(cPresence);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfacePresence::CallGetPresence(PRUint32 aContactsCount, PRUint32 *aContacts,
    csITpConnectionInterfacePresenceGetPresenceCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cContacts = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aContactsCount; i++)
    g_array_append_val(cContacts, aContacts[i]);

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_presence_call_get_presence(m_Proxy, -1,
      cContacts,
      cb? GetPresenceResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetStatusesResponse(TpConnection *proxy,
    GHashTable *available_statuses,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfacePresenceGetStatusesCB *callback = (csITpConnectionInterfacePresenceGetStatusesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetStatusesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIArray> cAvailableStatuses;
  csTpStatusSpecMap::Create((gpointer)available_statuses, getter_AddRefs(cAvailableStatuses));

  callback->OnGetStatusesDone(cAvailableStatuses);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfacePresence::CallGetStatuses(csITpConnectionInterfacePresenceGetStatusesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_presence_call_get_statuses(m_Proxy, -1,
      cb? GetStatusesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
PresenceUpdateSignalCallback(TpConnection *proxy,
    GHashTable *presence,
    gpointer user_data, GObject *weak_object)
{
  csTpConnectionInterfacePresence *obj = (csTpConnectionInterfacePresence *)user_data;
  if (!obj)
    return;

  obj->HandlePresenceUpdate(presence);
}


void
csTpConnectionInterfacePresence::HandlePresenceUpdate(GHashTable *presence)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_PresenceUpdateObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionInterfacePresencePresenceUpdateObserver> observer;

  nsCOMPtr<nsIArray> cPresence;
  csTpContactPresences::Create((gpointer)presence, getter_AddRefs(cPresence));

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_PresenceUpdateObservers, i);
    observer->OnPresenceUpdate(cPresence);
  }
}


NS_IMETHODIMP
csTpConnectionInterfacePresence::ConnectToPresenceUpdate(csITpConnectionInterfacePresencePresenceUpdateObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_PresenceUpdateObservers) {
    m_PresenceUpdateObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_interface_presence_connect_to_presence_update(m_Proxy,
        PresenceUpdateSignalCallback, this, NULL, NULL, NULL);
  }

  m_PresenceUpdateObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnectionInterfacePresence::DisconnectFromPresenceUpdate(csITpConnectionInterfacePresencePresenceUpdateObserver *observer)
{
  if (!m_PresenceUpdateObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_PresenceUpdateObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_PresenceUpdateObservers->RemoveElementAt(idx);
}


static void
RemoveStatusResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfacePresenceRemoveStatusCB *callback = (csITpConnectionInterfacePresenceRemoveStatusCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnRemoveStatusError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnRemoveStatusDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfacePresence::CallRemoveStatus(const nsACString &aStatus,
    csITpConnectionInterfacePresenceRemoveStatusCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  char *cStatus = ToNewCString(aStatus);

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_presence_call_remove_status(m_Proxy, -1,
      cStatus,
      cb? RemoveStatusResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RequestPresenceResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfacePresenceRequestPresenceCB *callback = (csITpConnectionInterfacePresenceRequestPresenceCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnRequestPresenceError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnRequestPresenceDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfacePresence::CallRequestPresence(PRUint32 aContactsCount, PRUint32 *aContacts,
    csITpConnectionInterfacePresenceRequestPresenceCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cContacts = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aContactsCount; i++)
    g_array_append_val(cContacts, aContacts[i]);

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_presence_call_request_presence(m_Proxy, -1,
      cContacts,
      cb? RequestPresenceResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
SetLastActivityTimeResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfacePresenceSetLastActivityTimeCB *callback = (csITpConnectionInterfacePresenceSetLastActivityTimeCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnSetLastActivityTimeError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnSetLastActivityTimeDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfacePresence::CallSetLastActivityTime(PRUint32 aTime,
    csITpConnectionInterfacePresenceSetLastActivityTimeCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_presence_call_set_last_activity_time(m_Proxy, -1,
      aTime,
      cb? SetLastActivityTimeResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
SetStatusResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfacePresenceSetStatusCB *callback = (csITpConnectionInterfacePresenceSetStatusCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnSetStatusError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnSetStatusDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfacePresence::CallSetStatus(nsIArray *aStatuses,
    csITpConnectionInterfacePresenceSetStatusCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  /* TODO */

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_presence_call_set_status(m_Proxy, -1,
      NULL,
      cb? SetStatusResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpConnectionInterfacePresence::csTpConnectionInterfacePresence()
{}

csTpConnectionInterfacePresence::~csTpConnectionInterfacePresence()
{}
