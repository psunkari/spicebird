#include "csTpConnectionImp.h"
#include "csTpGenericTypes.h"
#include "csTelepathyUtils.h"
#include "nsComponentManagerUtils.h"

#include "telepathy-glib/contact.h"
#include "telepathy-glib/interfaces.h"
#include "telepathy-glib/proxy-subclass.h"

// Intentionally put above csTelepathyMacros.h
NS_IMPL_ISUPPORTS1(csTpContact, csITpContact)

#include "csTelepathyMacros.h"
#define NS_INTERFACE_TABLE_TAIL                                               \
    CS_TELEPATHY_INTERFACE_LIST_BEGIN                                         \
    CS_TELEPATHY_INTERFACE_ITEM(csITpConnectionInterfaceAvatars,              \
      "org.freedesktop.Telepathy.Connection.Interface.Avatars")               \
    CS_TELEPATHY_INTERFACE_ITEM(csITpConnectionInterfaceAliasing,             \
      "org.freedesktop.Telepathy.Connection.Interface.Aliasing")              \
    CS_TELEPATHY_INTERFACE_ITEM(csITpConnectionInterfaceCapabilities,         \
      "org.freedesktop.Telepathy.Connection.Interface.Capabilities")          \
    CS_TELEPATHY_INTERFACE_ITEM(csITpConnectionInterfaceContactCapabilities,  \
      "org.freedesktop.Telepathy.Connection.Interface.ContactCapabilities")   \
    CS_TELEPATHY_INTERFACE_ITEM(csITpConnectionInterfaceLocation,             \
      "org.freedesktop.Telepathy.Connection.Interface.Location")              \
    CS_TELEPATHY_INTERFACE_ITEM(csITpConnectionInterfaceContacts,             \
      "org.freedesktop.Telepathy.Connection.Interface.Contacts")              \
    CS_TELEPATHY_INTERFACE_ITEM(csITpConnectionInterfacePresence,             \
      "org.freedesktop.Telepathy.Connection.Interface.Presence")              \
    CS_TELEPATHY_INTERFACE_ITEM(csITpConnectionInterfaceRequests,             \
      "org.freedesktop.Telepathy.Connection.Interface.Requests")              \
    CS_TELEPATHY_INTERFACE_ITEM(csITpConnectionInterfaceSimplePresence,       \
      "org.freedesktop.Telepathy.Connection.Interface.SimplePresence")        \
    CS_TELEPATHY_INTERFACE_LIST_END

NS_IMPL_ISUPPORTS12(                                                          \
  csTpConnectionImp,csITpProxy,csITpConnectionUtils,csITpConnection,            \
  csITpConnectionInterfaceAvatars,csITpConnectionInterfaceAliasing,           \
  csITpConnectionInterfaceCapabilities,                                       \
  csITpConnectionInterfaceContactCapabilities,                                \
  csITpConnectionInterfaceLocation,csITpConnectionInterfaceContacts,          \
  csITpConnectionInterfacePresence,csITpConnectionInterfaceRequests,          \
  csITpConnectionInterfaceSimplePresence);

csTpConnectionImp::csTpConnectionImp()
{
  m_BusDaemon = tp_dbus_daemon_new(tp_get_bus());
  m_Proxy = NULL;
  m_InterfacesReadyObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);

  CS_TELEPATHY_INIT_PROXY
}

csTpConnectionImp::~csTpConnectionImp()
{
  if (m_Proxy)
    g_object_unref(m_Proxy);

  m_Proxy = NULL;
}

static void
EarlyGotInterfaces(TpConnection *connection, const gchar **interfaces,
                   const GError *error, gpointer user_data, GObject *weak_object)
{
  csTpConnectionImp *obj = (csTpConnectionImp *)user_data;
  if (!obj)
    return;

  obj->HandleEarlyGotInterfaces(interfaces, error);
}

void
csTpConnectionImp::HandleEarlyGotInterfaces(const gchar **interfaces, const GError *error)
{
  if (!m_Proxy)
    return;

  if (!error) {
    const gchar **iter;
    for (iter = interfaces; *iter != NULL; iter++) {
      GQuark quark = g_quark_try_string(*iter);
 
      if (quark == TP_IFACE_QUARK_CONNECTION_INTERFACE_SIMPLE_PRESENCE)
        tp_proxy_add_interface_by_id((TpProxy*)m_Proxy, quark);
 
      else if (quark == TP_IFACE_QUARK_CONNECTION_INTERFACE_CONTACT_CAPABILITIES)
        tp_proxy_add_interface_by_id((TpProxy*)m_Proxy, quark);
    }
  }

  // Now that we added the interfaces to the proxy. QueryInterface on those 
  // interfaces will succeed - can safely say that we got the interfaces!

  PRUint32 length;
  m_InterfacesReadyObservers->GetLength(&length);
  
  nsCOMPtr<csITpConnectionInterfacesReadyCB> observer;
  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_InterfacesReadyObservers, i);
    if (!error)
      observer->OnConnectionInterfacesReady();
    else
      observer->OnConnectionInterfacesReadyError(nsDependentCString(g_quark_to_string(error->domain)),
                                                error->code, nsDependentCString(error->message));
  }
  m_InterfacesReadyObservers->Clear();
}

NS_IMETHODIMP
csTpConnectionImp::CallWhenInterfacesReady(csITpConnectionInterfacesReadyCB *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  m_InterfacesReadyObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}

NS_IMETHODIMP
csTpConnectionImp::Init(const nsACString& aBusName, const nsACString& aObjectPath)
{
  if (m_Proxy)
    return NS_ERROR_ALREADY_INITIALIZED;

  char *busName = NULL;
  char *objPath = NULL;

  if (!aBusName.IsEmpty())
    busName = g_strdup(nsCString(aBusName).get());

  if (!aObjectPath.IsEmpty())
    objPath = g_strdup(nsCString(aObjectPath).get());

  m_Proxy = tp_connection_new(m_BusDaemon, busName, objPath, NULL);
  if (!m_Proxy)
    return NS_ERROR_OUT_OF_MEMORY;

  // Lookup for interfaces.
  // In a connection we need an early lookup of interfaces
  // in order to set presence status on connect.
  tp_cli_connection_call_get_interfaces(m_Proxy, -1, EarlyGotInterfaces,
                                        this, NULL, NULL);

  if (busName)
    g_free(busName);

  if (objPath)
    g_free(objPath);

  return NS_OK;
}

/* Copied from generated csTpConnectionInterfaceRequests.cpp */
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

// XXX: This will be gone once we implement ToGLib functions
//      Currently there are very few functions that use ToGLib
NS_IMETHODIMP
csTpConnectionImp::CallCreateChannel(nsIArray *aRequest,
    csITpConnectionInterfaceRequestsCreateChannelCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 length;
  aRequest->GetLength(&length);

  nsCOMPtr<csITpQualifiedPropertyValueMap> param;
  nsCString key;
  GValue *cValue;
  nsCOMPtr<nsIVariant> value;
  GHashTable *table = g_hash_table_new(g_str_hash, g_str_equal);

  for(PRUint32 i=0; i<length; i++) {
    param = do_QueryElementAt(aRequest, i);
    param->GetKey(key);
    param->GetValue(getter_AddRefs(value));

    cValue = VariantToGValue(value);
    if (cValue)
      g_hash_table_insert(table, g_strdup(key.get()), cValue);
  }

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_requests_call_create_channel(m_Proxy, -1,
      table,
      cb? CreateChannelResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}

/* Copied from generated csTpConnectinInterfaceAliasing.cpp */
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


// XXX: This will be gone once we implement ToGLib functions
//      Currently there are very few functions that use ToGLib
NS_IMETHODIMP
csTpConnectionImp::CallSetAliases(nsIArray *aAliasesMap,
    csITpConnectionInterfaceAliasingSetAliasesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 length;
  aAliasesMap->GetLength(&length);

  nsCOMPtr<csITpAliasMap> aliasMap;
  PRUint32 handle;
  nsCString alias;
  GHashTable *table = g_hash_table_new_full(g_direct_hash, g_int_equal, NULL, g_free);

  for(PRUint32 i=0; i<length; i++) {
    aliasMap = do_QueryElementAt(aAliasesMap, i);
    aliasMap->GetHandle(&handle);
    aliasMap->GetAlias(alias);

    g_hash_table_insert(table, GUINT_TO_POINTER(handle), g_strdup(alias.get()));
  }


  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_aliasing_call_set_aliases(m_Proxy, -1,
      table,
      cb? SetAliasesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}

NS_IMETHODIMP
csTpConnectionImp::GetProtocolName(nsACString &aProtocolName)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  char *protocol;
  if (!tp_connection_parse_object_path(m_Proxy, &protocol, NULL))
    return NS_ERROR_FAILURE;

  aProtocolName.Assign(protocol);
  return NS_OK;
}

NS_IMETHODIMP
csTpConnectionImp::GetManagerName(nsACString &aManagerName)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  char *manager;
  if (!tp_connection_parse_object_path(m_Proxy, NULL, &manager))
    return NS_ERROR_FAILURE;

  aManagerName.Assign(manager);
  return NS_OK;
}

static void
ConnectionReady(TpConnection *proxy, const GError *error, gpointer user_data)
{
  csITpConnectionReadyCB *callback = (csITpConnectionReadyCB *)user_data;

  if (error != NULL) {
    callback->OnConnectionReadyError(nsDependentCString(g_quark_to_string(error->domain)),
                                     error->code, nsDependentCString(error->message));
    return;
  }

  callback->OnConnectionReady();
  NS_IF_RELEASE(callback);
}

NS_IMETHODIMP
csTpConnectionImp::CallWhenReady(csITpConnectionReadyCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_connection_call_when_ready(m_Proxy, ConnectionReady, cb);

  return NS_OK;
}

static void
GetContactsByHandleResponse(TpConnection *conn, guint n_contacts,
                            TpContact * const *contacts, guint n_failed,
                            const TpHandle *failed, const GError *error,
                            gpointer user_data, GObject *weak_obj)
{
  csITpGetContactsByHandleCB *callback = (csITpGetContactsByHandleCB *)user_data;
  if (error != NULL) {
    callback->OnGetContactsByHandleError(nsDependentCString(g_quark_to_string(error->domain)),
                                         error->code, nsDependentCString(error->message));
    return;
  }

  char *objectPath;
  g_object_get(conn, "object-path", &objectPath, NULL);
  nsCString objectPathStr(objectPath);

  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  nsCOMPtr<csITpContact> contact;
  for (guint i=0; i<n_contacts; i++) {
    csTpContact::Create(contacts[i], objectPathStr, getter_AddRefs(contact));
    array->AppendElement(contact, PR_FALSE);
  }

  callback->OnGetContactsByHandleDone(array, n_failed, (PRUint32*)failed);
  NS_IF_RELEASE(callback);
}

NS_IMETHODIMP
csTpConnectionImp::GetContactsByHandle(PRUint32 aHandlesCount, PRUint32 *aHandles,
                                       PRUint32 aFeaturesCount, PRUint32 *aFeatures,
                                       csITpGetContactsByHandleCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_connection_get_contacts_by_handle(m_Proxy, aHandlesCount, (const TpHandle*)aHandles,
                                       aFeaturesCount, (const TpContactFeature*)aFeatures,
                                       GetContactsByHandleResponse, cb, NULL, NULL);

  return NS_OK;
}

NS_IMETHODIMP
csTpConnectionImp::GetContactsById(PRUint32 aIdsCount, char const** aIds,
                                       PRUint32 aFeaturesCount, PRUint32 *aFeatures,
                                       csITpGetContactsByIdCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
csTpConnectionImp::UpgradeContacts(nsIArray *aContacts, PRUint32 aFeaturesCount,
                                   PRUint32 *aFeatures, csITpUpgradeContactsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
csTpConnectionImp::GetConnectionReady(PRBool *aConnectionReady)
{
  g_object_get(m_Proxy, "connection-ready", aConnectionReady, NULL);
  return NS_OK;
}

NS_IMETHODIMP
csTpConnectionImp::GetSelfHandle(PRUint32 *aSelfHandle)
{
  g_object_get(m_Proxy, "self-handle", aSelfHandle, NULL);
  return NS_OK;
}

NS_IMETHODIMP
csTpConnectionImp::GetStatus(PRUint32 *aStatus)
{
  g_object_get(m_Proxy, "status", aStatus, NULL);
  return NS_OK;
}

NS_IMETHODIMP
csTpConnectionImp::GetStatusReason(PRUint32 *aStatusReason)
{
  g_object_get(m_Proxy, "status-reason", aStatusReason, NULL);
  return NS_OK;
}

CS_TELEPATHY_IMPL_PROXY(csTpConnectionImp, m_Proxy);


/*
 * Implementation of csITpContact
 */

NS_METHOD
csTpContact::Create(TpContact *contact, const nsACString &aObjectPath, csITpContact** aContact)
{
  csITpContact *it = new csTpContact(contact, aObjectPath);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpContact), (void **)aContact);
  NS_RELEASE(it);

  return rv;
}

csTpContact::csTpContact(TpContact *contact, const nsACString &aObjectPath)
{
  m_Contact = contact;
  m_ConnectionKey.Assign(aObjectPath);

  g_object_ref(m_Contact);
}

csTpContact::~csTpContact()
{
  g_object_unref(m_Contact);
}

NS_IMETHODIMP 
csTpContact::GetConnectionKey(nsACString & aConnectionKey)
{
  if (!m_Contact)
    return NS_ERROR_NOT_INITIALIZED;

  aConnectionKey.Assign(m_ConnectionKey);
  return NS_OK;
}

NS_IMETHODIMP 
csTpContact::GetAlias(nsACString & aAlias)
{
  if (!m_Contact)
    return NS_ERROR_NOT_INITIALIZED;

  aAlias.Assign(tp_contact_get_alias(m_Contact));
  return NS_OK;
}

NS_IMETHODIMP
csTpContact::GetAvatarToken(nsACString & aAvatarToken)
{
  if (!m_Contact)
    return NS_ERROR_NOT_INITIALIZED;

  aAvatarToken.Assign(tp_contact_get_avatar_token(m_Contact));
  return NS_OK;
}

NS_IMETHODIMP
csTpContact::GetHandle(PRUint32 *aHandle)
{
  if (!m_Contact)
    return NS_ERROR_NOT_INITIALIZED;

  *aHandle = tp_contact_get_handle(m_Contact);
  return NS_OK;
}

NS_IMETHODIMP
csTpContact::GetIdentifier(nsACString & aIdentifier)
{
  if (!m_Contact)
    return NS_ERROR_NOT_INITIALIZED;

  aIdentifier.Assign(tp_contact_get_identifier(m_Contact));
  return NS_OK;
}

NS_IMETHODIMP
csTpContact::GetPresenceMessage(nsACString & aPresenceMessage)
{
  if (!m_Contact)
    return NS_ERROR_NOT_INITIALIZED;

  aPresenceMessage.Assign(tp_contact_get_presence_message(m_Contact));
  return NS_OK;
}

NS_IMETHODIMP
csTpContact::GetPresenceStatus(nsACString & aPresenceStatus)
{
  if (!m_Contact)
    return NS_ERROR_NOT_INITIALIZED;

  aPresenceStatus.Assign(tp_contact_get_presence_status(m_Contact));
  return NS_OK;
}

NS_IMETHODIMP
csTpContact::GetPresenceType(PRUint32 *aPresenceType)
{
  if (!m_Contact)
    return NS_ERROR_NOT_INITIALIZED;

  *aPresenceType = (PRUint32)tp_contact_get_presence_type(m_Contact);
  return NS_OK;
}

NS_IMETHODIMP
csTpContact::ContactHasFeature(PRUint32 feature, PRBool *_retval NS_OUTPARAM)
{
  if (!m_Contact)
    return NS_ERROR_NOT_INITIALIZED;

  *_retval = tp_contact_has_feature(m_Contact, (TpContactFeature)feature);
  return NS_OK;
}

static void
ContactUpdated(TpContact *contact, GParamSpec *spec, gpointer user_data)
{
  csTpContact *obj = (csTpContact *)user_data;
  if (!obj)
    return;

  obj->HandleUpdate(contact, spec);
}

void
csTpContact::HandleUpdate(TpContact *contact, GParamSpec *spec)
{
  if (!m_Contact)
    return;

  PRUint32 length;
  m_UpdateObservers->GetLength(&length);
  
  nsCOMPtr<csITpContactUpdateObserver> observer;
  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_UpdateObservers, i);
    observer->OnContactUpdate(this, nsCString(g_param_spec_get_name(spec)));
  }
}

NS_IMETHODIMP
csTpContact::AddUpdateObserver(csITpContactUpdateObserver *observer)
{
  if (!m_Contact)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);
  if (!m_UpdateObservers) {
    m_UpdateObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    g_signal_connect(m_Contact, "notify", G_CALLBACK(ContactUpdated), this);
  }

  m_UpdateObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}

NS_IMETHODIMP
csTpContact::RemoveUpdateObserver(csITpContactUpdateObserver *observer)
{
  if (!m_Contact)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_UpdateObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_UpdateObservers->RemoveElementAt(idx);
}

