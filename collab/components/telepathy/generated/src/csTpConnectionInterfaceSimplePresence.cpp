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


#include "csTpConnectionInterfaceSimplePresence.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpSimplePresence
 */

NS_IMPL_ISUPPORTS1(csTpSimplePresence, csITpSimplePresence)

NS_METHOD
csTpSimplePresence::Create(PRUint32 aType, const nsCString &aStatus, const nsCString &aStatusMessage, void **aResult)
{
  csITpSimplePresence *it = 
          new csTpSimplePresence(aType, aStatus, aStatusMessage);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSimplePresence), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpSimplePresence::Create(gpointer aGLibItem, void **aResult)
{
  guint type;
  const gchar *status;
  const gchar *status_message;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_SIMPLE_PRESENCE);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &type, 1, &status, 2, &status_message,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cStatus = nsDependentCString(status);
  nsCString cStatusMessage = nsDependentCString(status_message);
  csITpSimplePresence *it = new csTpSimplePresence(type, cStatus, cStatusMessage);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSimplePresence), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpSimplePresence::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpSimplePresence::csTpSimplePresence(PRUint32 aType, const nsCString &aStatus, const nsCString &aStatusMessage)
{
  m_Type = aType;
  m_Status.Assign(aStatus);
  m_StatusMessage.Assign(aStatusMessage);
}

csTpSimplePresence::~csTpSimplePresence()
{}

NS_IMETHODIMP
csTpSimplePresence::GetType(PRUint32 *aType)
{
  *aType = m_Type;
  return NS_OK;
}

NS_IMETHODIMP
csTpSimplePresence::GetStatus(nsACString &aStatus)
{
  aStatus.Assign(m_Status);
  return NS_OK;
}

NS_IMETHODIMP
csTpSimplePresence::GetStatusMessage(nsACString &aStatusMessage)
{
  aStatusMessage.Assign(m_StatusMessage);
  return NS_OK;
}

/*
 *  Implementation of csTpSimpleContactPresences
 */

NS_IMPL_ISUPPORTS1(csTpSimpleContactPresences, csITpSimpleContactPresences)

NS_METHOD
csTpSimpleContactPresences::Create(PRUint32 aContact, nsISupports *aPresence, void **aResult)
{
  csITpSimpleContactPresences *it = 
          new csTpSimpleContactPresences(aContact, aPresence);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSimpleContactPresences), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpSimpleContactPresences::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    guint contact = GPOINTER_TO_UINT(keyPtr);
    const GValueArray *presence = (GValueArray *)valuePtr;

    nsCOMPtr<csITpSimplePresence> cPresence;
    csTpSimplePresence::Create((gpointer)presence, getter_AddRefs(cPresence));

    csITpSimpleContactPresences *temp = new csTpSimpleContactPresences(contact, cPresence);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpSimpleContactPresences> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpSimpleContactPresences::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpSimpleContactPresences::csTpSimpleContactPresences(PRUint32 aContact, nsISupports *aPresence)
{
  m_Contact = aContact;
  m_Presence = aPresence;
}

csTpSimpleContactPresences::~csTpSimpleContactPresences()
{}

NS_IMETHODIMP
csTpSimpleContactPresences::GetContact(PRUint32 *aContact)
{
  *aContact = m_Contact;
  return NS_OK;
}

NS_IMETHODIMP
csTpSimpleContactPresences::GetPresence(nsISupports **aPresence)
{
  NS_IF_ADDREF(*aPresence = m_Presence);
  return NS_OK;
}

/*
 *  Implementation of csTpSimpleStatusSpec
 */

NS_IMPL_ISUPPORTS1(csTpSimpleStatusSpec, csITpSimpleStatusSpec)

NS_METHOD
csTpSimpleStatusSpec::Create(PRUint32 aType, PRBool aMaySetOnSelf, PRBool aCanHaveMessage, void **aResult)
{
  csITpSimpleStatusSpec *it = 
          new csTpSimpleStatusSpec(aType, aMaySetOnSelf, aCanHaveMessage);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSimpleStatusSpec), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpSimpleStatusSpec::Create(gpointer aGLibItem, void **aResult)
{
  guint type;
  gboolean may_set_on_self;
  gboolean can_have_message;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_SIMPLE_STATUS_SPEC);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &type, 1, &may_set_on_self, 2, &can_have_message,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  csITpSimpleStatusSpec *it = new csTpSimpleStatusSpec(type, may_set_on_self, can_have_message);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSimpleStatusSpec), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpSimpleStatusSpec::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpSimpleStatusSpec::csTpSimpleStatusSpec(PRUint32 aType, PRBool aMaySetOnSelf, PRBool aCanHaveMessage)
{
  m_Type = aType;
  m_MaySetOnSelf = aMaySetOnSelf;
  m_CanHaveMessage = aCanHaveMessage;
}

csTpSimpleStatusSpec::~csTpSimpleStatusSpec()
{}

NS_IMETHODIMP
csTpSimpleStatusSpec::GetType(PRUint32 *aType)
{
  *aType = m_Type;
  return NS_OK;
}

NS_IMETHODIMP
csTpSimpleStatusSpec::GetMaySetOnSelf(PRBool *aMaySetOnSelf)
{
  *aMaySetOnSelf = m_MaySetOnSelf;
  return NS_OK;
}

NS_IMETHODIMP
csTpSimpleStatusSpec::GetCanHaveMessage(PRBool *aCanHaveMessage)
{
  *aCanHaveMessage = m_CanHaveMessage;
  return NS_OK;
}

/*
 *  Implementation of csTpSimpleStatusSpecMap
 */

NS_IMPL_ISUPPORTS1(csTpSimpleStatusSpecMap, csITpSimpleStatusSpecMap)

NS_METHOD
csTpSimpleStatusSpecMap::Create(const nsCString &aIdentifier, nsISupports *aSpec, void **aResult)
{
  csITpSimpleStatusSpecMap *it = 
          new csTpSimpleStatusSpecMap(aIdentifier, aSpec);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpSimpleStatusSpecMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpSimpleStatusSpecMap::Create(gpointer aGLibItem, nsIArray **aResult)
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
    nsCOMPtr<csITpSimpleStatusSpec> cSpec;
    csTpSimpleStatusSpec::Create((gpointer)spec, getter_AddRefs(cSpec));

    csITpSimpleStatusSpecMap *temp = new csTpSimpleStatusSpecMap(cIdentifier, cSpec);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpSimpleStatusSpecMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpSimpleStatusSpecMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpSimpleStatusSpecMap::csTpSimpleStatusSpecMap(const nsCString &aIdentifier, nsISupports *aSpec)
{
  m_Identifier.Assign(aIdentifier);
  m_Spec = aSpec;
}

csTpSimpleStatusSpecMap::~csTpSimpleStatusSpecMap()
{}

NS_IMETHODIMP
csTpSimpleStatusSpecMap::GetIdentifier(nsACString &aIdentifier)
{
  aIdentifier.Assign(m_Identifier);
  return NS_OK;
}

NS_IMETHODIMP
csTpSimpleStatusSpecMap::GetSpec(nsISupports **aSpec)
{
  NS_IF_ADDREF(*aSpec = m_Spec);
  return NS_OK;
}

static void
SetPresenceResponse(TpConnection *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceSimplePresenceSetPresenceCB *callback = (csITpConnectionInterfaceSimplePresenceSetPresenceCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnSetPresenceError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnSetPresenceDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceSimplePresence::CallSetPresence(const nsACString &aStatus, const nsACString &aStatusMessage,
    csITpConnectionInterfaceSimplePresenceSetPresenceCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  char *cStatus = ToNewCString(aStatus);
  char *cStatusMessage = ToNewCString(aStatusMessage);

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_simple_presence_call_set_presence(m_Proxy, -1,
      cStatus, cStatusMessage,
      cb? SetPresenceResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetPresencesResponse(TpConnection *proxy,
    GHashTable *presence,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceSimplePresenceGetPresencesCB *callback = (csITpConnectionInterfaceSimplePresenceGetPresencesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetPresencesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIArray> cPresence;
  csTpSimpleContactPresences::Create((gpointer)presence, getter_AddRefs(cPresence));

  callback->OnGetPresencesDone(cPresence);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceSimplePresence::CallGetPresences(PRUint32 aContactsCount, PRUint32 *aContacts,
    csITpConnectionInterfaceSimplePresenceGetPresencesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cContacts = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aContactsCount; i++)
    g_array_append_val(cContacts, aContacts[i]);

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_simple_presence_call_get_presences(m_Proxy, -1,
      cContacts,
      cb? GetPresencesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
StatusesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceSimplePresenceStatusesCB *callback = (csITpConnectionInterfaceSimplePresenceStatusesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyStatusesError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GHashTable * statuses;
  statuses = (GHashTable *)g_value_get_boxed(out);
  nsCOMPtr<nsIArray> cStatuses;
  csTpSimpleStatusSpecMap::Create((gpointer)statuses, getter_AddRefs(cStatuses));

  callback->GetPropertyStatusesDone(cStatuses);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceSimplePresence::GetPropertyStatuses(csITpConnectionInterfaceSimplePresenceStatusesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Connection.Interface.SimplePresence",
      "Statuses",
      cb? StatusesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
PresencesChangedSignalCallback(TpConnection *proxy,
    GHashTable *presence,
    gpointer user_data, GObject *weak_object)
{
  csTpConnectionInterfaceSimplePresence *obj = (csTpConnectionInterfaceSimplePresence *)user_data;
  if (!obj)
    return;

  obj->HandlePresencesChanged(presence);
}


void
csTpConnectionInterfaceSimplePresence::HandlePresencesChanged(GHashTable *presence)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_PresencesChangedObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionInterfaceSimplePresencePresencesChangedObserver> observer;

  nsCOMPtr<nsIArray> cPresence;
  csTpSimpleContactPresences::Create((gpointer)presence, getter_AddRefs(cPresence));

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_PresencesChangedObservers, i);
    observer->OnPresencesChanged(cPresence);
  }
}


NS_IMETHODIMP
csTpConnectionInterfaceSimplePresence::ConnectToPresencesChanged(csITpConnectionInterfaceSimplePresencePresencesChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_PresencesChangedObservers) {
    m_PresencesChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_interface_simple_presence_connect_to_presences_changed(m_Proxy,
        PresencesChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_PresencesChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnectionInterfaceSimplePresence::DisconnectFromPresencesChanged(csITpConnectionInterfaceSimplePresencePresencesChangedObserver *observer)
{
  if (!m_PresencesChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_PresencesChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_PresencesChangedObservers->RemoveElementAt(idx);
}


/*
 *  Implementation of csTpRichPresenceAccessControl
 */

NS_IMPL_ISUPPORTS1(csTpRichPresenceAccessControl, csITpRichPresenceAccessControl)

NS_METHOD
csTpRichPresenceAccessControl::Create(PRUint32 aType, nsIVariant *aDetail, void **aResult)
{
  csITpRichPresenceAccessControl *it = 
          new csTpRichPresenceAccessControl(aType, aDetail);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpRichPresenceAccessControl), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpRichPresenceAccessControl::Create(gpointer aGLibItem, void **aResult)
{
  guint type;
  const GValue *detail;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_RICH_PRESENCE_ACCESS_CONTROL);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &type, 1, &detail,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCOMPtr<nsIVariant> cDetail;
  GValueToVariant(detail, getter_AddRefs(cDetail));
  csITpRichPresenceAccessControl *it = new csTpRichPresenceAccessControl(type, cDetail);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpRichPresenceAccessControl), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpRichPresenceAccessControl::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpRichPresenceAccessControl::csTpRichPresenceAccessControl(PRUint32 aType, nsIVariant *aDetail)
{
  m_Type = aType;
  m_Detail = aDetail;
}

csTpRichPresenceAccessControl::~csTpRichPresenceAccessControl()
{}

NS_IMETHODIMP
csTpRichPresenceAccessControl::GetType(PRUint32 *aType)
{
  *aType = m_Type;
  return NS_OK;
}

NS_IMETHODIMP
csTpRichPresenceAccessControl::GetDetail(nsIVariant **aDetail)
{
  NS_IF_ADDREF(*aDetail = m_Detail);
  return NS_OK;
}


csTpConnectionInterfaceSimplePresence::csTpConnectionInterfaceSimplePresence()
{}

csTpConnectionInterfaceSimplePresence::~csTpConnectionInterfaceSimplePresence()
{}
