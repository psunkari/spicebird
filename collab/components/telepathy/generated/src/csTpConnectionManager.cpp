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


#include "csTpConnectionManager.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpParamSpec
 */

NS_IMPL_ISUPPORTS1(csTpParamSpec, csITpParamSpec)

NS_METHOD
csTpParamSpec::Create(const nsCString &aName, PRUint32 aFlags, const nsCString &aSignature, nsIVariant *aDefaultValue, void **aResult)
{
  csITpParamSpec *it = 
          new csTpParamSpec(aName, aFlags, aSignature, aDefaultValue);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpParamSpec), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpParamSpec::Create(gpointer aGLibItem, void **aResult)
{
  const gchar *name;
  guint flags;
  const gchar *signature;
  const GValue *default_value;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_PARAM_SPEC);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &name, 1, &flags, 2, &signature, 3, &default_value,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cName = nsDependentCString(name);
  nsCString cSignature = nsDependentCString(signature);
  nsCOMPtr<nsIVariant> cDefaultValue;
  GValueToVariant(default_value, getter_AddRefs(cDefaultValue));
  csITpParamSpec *it = new csTpParamSpec(cName, flags, cSignature, cDefaultValue);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpParamSpec), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpParamSpec::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpParamSpec::csTpParamSpec(const nsCString &aName, PRUint32 aFlags, const nsCString &aSignature, nsIVariant *aDefaultValue)
{
  m_Name.Assign(aName);
  m_Flags = aFlags;
  m_Signature.Assign(aSignature);
  m_DefaultValue = aDefaultValue;
}

csTpParamSpec::~csTpParamSpec()
{}

NS_IMETHODIMP
csTpParamSpec::GetName(nsACString &aName)
{
  aName.Assign(m_Name);
  return NS_OK;
}

NS_IMETHODIMP
csTpParamSpec::GetFlags(PRUint32 *aFlags)
{
  *aFlags = m_Flags;
  return NS_OK;
}

NS_IMETHODIMP
csTpParamSpec::GetSignature(nsACString &aSignature)
{
  aSignature.Assign(m_Signature);
  return NS_OK;
}

NS_IMETHODIMP
csTpParamSpec::GetDefaultValue(nsIVariant **aDefaultValue)
{
  NS_IF_ADDREF(*aDefaultValue = m_DefaultValue);
  return NS_OK;
}

static void
GetParametersResponse(TpConnectionManager *proxy,
    const GPtrArray *parameters,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionManagerGetParametersCB *callback = (csITpConnectionManagerGetParametersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetParametersError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIMutableArray> cParameters = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)parameters)->len; i++) {
    gpointer parameters_item = g_ptr_array_index((GPtrArray*)parameters, i);
    nsCOMPtr<csITpParamSpec> cParametersItem;
    csTpParamSpec::Create((gpointer)parameters_item, getter_AddRefs(cParametersItem));
    cParameters->AppendElement(cParametersItem, PR_FALSE);
  }

  callback->OnGetParametersDone(cParameters);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionManager::CallGetParameters(const nsACString &aProtocol,
    csITpConnectionManagerGetParametersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  char *cProtocol = ToNewCString(aProtocol);

  NS_IF_ADDREF(cb);
  tp_cli_connection_manager_call_get_parameters(m_Proxy, -1,
      cProtocol,
      cb? GetParametersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ListProtocolsResponse(TpConnectionManager *proxy,
    const gchar **protocols,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionManagerListProtocolsCB *callback = (csITpConnectionManagerListProtocolsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnListProtocolsError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cProtocolsCount = 0;
  for (char **pos = (char**)protocols; *pos; pos++, cProtocolsCount++);
  char **cProtocols = (char **)nsMemory::Alloc(cProtocolsCount * sizeof(char*));
  for (PRUint32 i=0; i<cProtocolsCount; i++)
    cProtocols[i] = (char *)nsMemory::Clone(protocols[i], strlen(protocols[i]) + 1);

  callback->OnListProtocolsDone(cProtocolsCount, (const char **)cProtocols);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionManager::CallListProtocols(csITpConnectionManagerListProtocolsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_connection_manager_call_list_protocols(m_Proxy, -1,
      cb? ListProtocolsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
NewConnectionSignalCallback(TpConnectionManager *proxy,
    const gchar *bus_name, const gchar *object_path, const gchar *protocol,
    gpointer user_data, GObject *weak_object)
{
  csTpConnectionManager *obj = (csTpConnectionManager *)user_data;
  if (!obj)
    return;

  obj->HandleNewConnection(bus_name, object_path, protocol);
}


void
csTpConnectionManager::HandleNewConnection(const gchar *bus_name, const gchar *object_path, const gchar *protocol)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_NewConnectionObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionManagerNewConnectionObserver> observer;

  nsCString cBusName = nsDependentCString(bus_name);
  nsCString cObjectPath = nsDependentCString(object_path);
  nsCString cProtocol = nsDependentCString(protocol);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_NewConnectionObservers, i);
    observer->OnNewConnection(cBusName, cObjectPath, cProtocol);
  }
}


NS_IMETHODIMP
csTpConnectionManager::ConnectToNewConnection(csITpConnectionManagerNewConnectionObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_NewConnectionObservers) {
    m_NewConnectionObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_manager_connect_to_new_connection(m_Proxy,
        NewConnectionSignalCallback, this, NULL, NULL, NULL);
  }

  m_NewConnectionObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnectionManager::DisconnectFromNewConnection(csITpConnectionManagerNewConnectionObserver *observer)
{
  if (!m_NewConnectionObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_NewConnectionObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_NewConnectionObservers->RemoveElementAt(idx);
}


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


NS_IMETHODIMP
csTpConnectionManager::CallRequestConnection(const nsACString &aProtocol, nsIArray *aParameters,
    csITpConnectionManagerRequestConnectionCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  char *cProtocol = ToNewCString(aProtocol);
  /* TODO */

  NS_IF_ADDREF(cb);
  tp_cli_connection_manager_call_request_connection(m_Proxy, -1,
      cProtocol, NULL,
      cb? RequestConnectionResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
InterfacesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionManagerInterfacesCB *callback = (csITpConnectionManagerInterfacesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyInterfacesError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar ** interfaces;
  interfaces = (gchar **)g_value_get_boxed(out);
  PRUint32 cInterfacesCount = 0;
  for (char **pos = (char**)interfaces; *pos; pos++, cInterfacesCount++);
  char **cInterfaces = (char **)nsMemory::Alloc(cInterfacesCount * sizeof(char*));
  for (PRUint32 i=0; i<cInterfacesCount; i++)
    cInterfaces[i] = (char *)nsMemory::Clone(interfaces[i], strlen(interfaces[i]) + 1);

  callback->GetPropertyInterfacesDone(cInterfacesCount, (const char **)cInterfaces);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionManager::GetPropertyInterfaces(csITpConnectionManagerInterfacesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.ConnectionManager",
      "Interfaces",
      cb? InterfacesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpConnectionManager::csTpConnectionManager()
{}

csTpConnectionManager::~csTpConnectionManager()
{}
