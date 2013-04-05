#include "csTpConnectionManagerImp.h"
#include "csITpGenericTypes.h"
#include "csTelepathyUtils.h"

#include "nsStringGlue.h"
#include "nsInterfaceHashtable.h"
#include "nsMemory.h"

#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"

NS_IMPL_ISUPPORTS2(csTpConnectionManagerImp,csITpConnectionManagerUtils,csITpConnectionManager)

// Deliberately included after the NS_IMPL_ISUPPORTS
#include "csTelepathyMacros.h"

csTpConnectionManagerImp::csTpConnectionManagerImp()
{
  m_BusDaemon = tp_dbus_daemon_new(tp_get_bus());
  m_Proxy = NULL;

  CS_TELEPATHY_INIT_PROXY
}

csTpConnectionManagerImp::~csTpConnectionManagerImp()
{
  if (m_Proxy)
    g_object_unref(m_Proxy);
}

NS_IMETHODIMP
csTpConnectionManagerImp::Init(const nsACString& aName)
{
  if (m_Proxy)
    return NS_ERROR_ALREADY_INITIALIZED;

  m_Proxy = tp_connection_manager_new(m_BusDaemon, nsCString(aName).get(), NULL, NULL);
  if (!m_Proxy)
    return NS_ERROR_FAILURE;

  return NS_OK;
}

NS_IMETHODIMP
csTpConnectionManagerImp::GetConnectionManager(nsACString &aManagerName)
{
  const gchar *manager;
  g_object_get(m_Proxy, "connection-manager", &manager, NULL);
  aManagerName.Assign(manager);
  return NS_OK;
}

NS_IMETHODIMP
csTpConnectionManagerImp::GetManagerFile(nsACString &aFileName)
{
  const gchar *file;
  g_object_get(m_Proxy, "manager-file", &file, NULL);
  aFileName.Assign(file);
  return NS_OK;
}

NS_IMETHODIMP
csTpConnectionManagerImp::GetInfoSource(PRUint32 *aInfoSource)
{
  g_object_get(m_Proxy, "info-source", aInfoSource, NULL);
  return NS_OK;
}

NS_IMETHODIMP
csTpConnectionManagerImp::GetAlwaysIntrospect(PRBool *aAlwaysIntrospect)
{
  g_object_get(m_Proxy, "always-introspect", aAlwaysIntrospect, NULL);
  return NS_OK;
}

NS_IMETHODIMP
csTpConnectionManagerImp::SetAlwaysIntrospect(PRBool aAlwaysIntrospect)
{
  g_object_set(m_Proxy, "always-introspect", aAlwaysIntrospect, NULL);
  return NS_OK;
}

NS_IMETHODIMP
csTpConnectionManagerImp::CallListProtocols(csITpConnectionManagerListProtocolsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  // Cut down on unnecessary round trips on the DBus

  if (m_Proxy->info_source > TP_CM_INFO_SOURCE_NONE) {
    PRUint32 cProtocolsCount = 0;

    const TpConnectionManagerProtocol *const *it;
    for(it = m_Proxy->protocols; it != NULL && *it != NULL; it++, cProtocolsCount++);

    char **cProtocols = (char**)nsMemory::Alloc(cProtocolsCount * sizeof(char*));
    for (PRUint32 i=0; i<cProtocolsCount; i++)
      cProtocols[i] = (char *)nsMemory::Clone(m_Proxy->protocols[i]->name, strlen(m_Proxy->protocols[i]->name) + 1);

    cb->OnListProtocolsDone(cProtocolsCount, (const char **)cProtocols);
  }
  else {
    return csTpConnectionManager::CallListProtocols(cb);
  }

  return NS_OK;
}

// Copied from csTpConnectionManager.cpp (Generated)
static void
RequestConnectionResponse(TpConnectionManager *proxy,
    const gchar *bus_name, const gchar *object_path,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionManagerRequestConnectionCB *callback = (csITpConnectionManagerRequestConnectionCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnRequestConnectionError(nsDependentCString(g_quark_to_string(error->domain)),
                                       error->code, nsDependentCString(error->message));
    return;
  }

  nsCString cBusName = nsDependentCString(bus_name);
  nsCString cObjectPath = nsDependentCString(object_path);

  callback->OnRequestConnectionDone(cBusName, cObjectPath);
  NS_IF_RELEASE(callback);
}

typedef struct {
  csITpConnectionManagerRequestConnectionCB *connectionCB;
  nsCString protocolName;
  nsIArray *parameters;
} Get_Params_For_Connection;

static void
GotParamsForNewConnection(TpConnectionManager *cm, const GPtrArray *arr,
                          const GError *error, gpointer user_data, GObject *unused)
{
  Get_Params_For_Connection* cb_struct = (Get_Params_For_Connection*)user_data;
  csITpConnectionManagerRequestConnectionCB *cb = cb_struct->connectionCB;
  nsCString aProtocol = cb_struct->protocolName;
  nsIArray *aParameters = cb_struct->parameters;

  if (error != NULL) {
    if (cb) {
      cb->OnRequestConnectionError(nsDependentCString(g_quark_to_string(error->domain)),
                                   error->code, nsDependentCString(error->message));
    }
    return;
  }

  PRUint32 parametersCount;
  nsresult rv = aParameters->GetLength(&parametersCount);
  if (NS_FAILED(rv))
    return;

  // Put all the passed parameters in a hash.
  // XXX: Copy of this code exists in CallRequestConnection.
  nsInterfaceHashtable<nsCStringHashKey, nsIVariant> parameters;
  parameters.Init();
  for (PRUint32 i=0; i<parametersCount; i++) {
    nsCOMPtr<csITpStringVariantMap> param = do_QueryElementAt(aParameters, i);
    nsCOMPtr<nsIVariant> value;
    nsCString key;

    rv = param->GetKey(key);
    if (NS_FAILED(rv))
      continue;

    rv = param->GetValue(getter_AddRefs(value));
    if (NS_FAILED(rv))
      continue;

    if (value)
      parameters.Put(key, value);
  }

  PRUint32 length = arr->len;
  GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);

  for (PRUint32 i=0; i<length; i++) {
    GValue structure = {0};
    TpConnectionManagerParam *tpparam = g_new0(TpConnectionManagerParam, 1);

    g_value_init(&structure, TP_STRUCT_TYPE_PARAM_SPEC);
    g_value_set_static_boxed(&structure, g_ptr_array_index(arr, i));

    if (dbus_g_type_struct_get(&structure,
                               0, &tpparam->name, 1, &tpparam->flags,
                               2, &tpparam->dbus_signature, G_MAXUINT)) {
      nsCOMPtr<nsIVariant> variant;

      if (parameters.Get(nsDependentCString(tpparam->name), getter_AddRefs(variant))) {
        GValue *value = VariantToGValueWithSignature(variant, tpparam->dbus_signature);
        g_hash_table_insert(hash, g_strdup(tpparam->name), value);
      }
    }
  }

  NS_IF_ADDREF(cb);
  tp_cli_connection_manager_call_request_connection(cm, -1,
                                              nsCString(aProtocol).get(), hash,
                                              cb? RequestConnectionResponse: NULL,
                                              cb? cb: NULL, NULL, NULL);
  NS_IF_RELEASE(cb);
  NS_IF_RELEASE(aParameters);
}

// XXX: This will be gone once we implement ToGLib functions
//      Currently this is the only function that needs them
//
// Verify the parameters - otherwise it is tough to distinguish between
// a few parameter types that nsIVariant gives us (Eg: Uint vs Int)
NS_IMETHODIMP
csTpConnectionManagerImp::CallRequestConnection(const nsACString & aProtocol,
                                                nsIArray *aParameters,
                                                csITpConnectionManagerRequestConnectionCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  if (m_Proxy->info_source > TP_CM_INFO_SOURCE_NONE) {
    GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);
    const TpConnectionManagerProtocol *const *it;
    PRBool foundProtocol = PR_FALSE;
    nsresult rv;

    for (it = m_Proxy->protocols; it != NULL && *it != NULL; it++) {
      if (g_str_equal((*it)->name, nsCString(aProtocol).get())) {
        const TpConnectionManagerParam *tpparam = (*it)->params;

        PRUint32 parametersCount;
        rv = aParameters->GetLength(&parametersCount);
        NS_ENSURE_SUCCESS(rv, rv);

        // Put all the passed parameters in a hash.
        // XXX: Copy of this code exists in GotParamsForNewConnection.
        nsInterfaceHashtable<nsCStringHashKey, nsIVariant> parameters;
        parameters.Init();
        for (PRUint32 i=0; i<parametersCount; i++) {
          nsCOMPtr<csITpStringVariantMap> param = do_QueryElementAt(aParameters, i);
          nsCOMPtr<nsIVariant> value;
          nsCString key;

          rv = param->GetKey(key);
          NS_ENSURE_SUCCESS(rv, rv);

          rv = param->GetValue(getter_AddRefs(value));
          NS_ENSURE_SUCCESS(rv, rv);

          if (value)
            parameters.Put(key, value);
        }

        // Build a GHashTable out of all the parameters we got
        for (tpparam = (*it)->params; tpparam->name != NULL; tpparam++) {
          nsCOMPtr<nsIVariant> variant;
          if (parameters.Get(nsDependentCString(tpparam->name), getter_AddRefs(variant))) {
            GValue *value = VariantToGValueWithSignature(variant, tpparam->dbus_signature);
            g_hash_table_insert(hash, g_strdup(tpparam->name), value);
          }
        }

        NS_IF_ADDREF(cb);
        tp_cli_connection_manager_call_request_connection(m_Proxy, -1,
                                                    nsCString(aProtocol).get(), hash,
                                                    cb? RequestConnectionResponse: NULL,
                                                    cb? cb: NULL, NULL, NULL);
        foundProtocol = PR_TRUE;
      }
    }

    if (foundProtocol == PR_FALSE)
      return NS_ERROR_INVALID_ARG;
  }
  else {
    // Handle the case where the connection manager is not yet introspected!
    // This is extremely rare!!!
    NS_IF_ADDREF(cb);
    NS_IF_ADDREF(aParameters);

    Get_Params_For_Connection *cb_struct = new Get_Params_For_Connection;
    cb_struct->connectionCB = cb;
    cb_struct->protocolName = aProtocol;
    cb_struct->parameters = aParameters;

    tp_cli_connection_manager_call_get_parameters(m_Proxy, -1,
                                                  nsCString(aProtocol).get(),
                                                  GotParamsForNewConnection,
                                                  cb_struct, NULL, NULL);
  }

  return NS_OK;
}

CS_TELEPATHY_IMPL_PROXY(csTpConnectionManagerImp, m_Proxy);
