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


#include "csTpChannelDispatcherInterfaceOperationList.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpDispatchOperationDetails
 */

NS_IMPL_ISUPPORTS1(csTpDispatchOperationDetails, csITpDispatchOperationDetails)

NS_METHOD
csTpDispatchOperationDetails::Create(const nsCString &aChannelDispatchOperation, nsIArray *aProperties, void **aResult)
{
  csITpDispatchOperationDetails *it = 
          new csTpDispatchOperationDetails(aChannelDispatchOperation, aProperties);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpDispatchOperationDetails), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpDispatchOperationDetails::Create(gpointer aGLibItem, void **aResult)
{
  const gchar *channel_dispatch_operation;
  GHashTable *properties;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_DISPATCH_OPERATION_DETAILS);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &channel_dispatch_operation, 1, &properties,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cChannelDispatchOperation = nsDependentCString(channel_dispatch_operation);
  nsCOMPtr<nsIArray> cProperties;
  csTpQualifiedPropertyValueMap::Create((gpointer)properties, getter_AddRefs(cProperties));
  csITpDispatchOperationDetails *it = new csTpDispatchOperationDetails(cChannelDispatchOperation, cProperties);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpDispatchOperationDetails), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpDispatchOperationDetails::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpDispatchOperationDetails::csTpDispatchOperationDetails(const nsCString &aChannelDispatchOperation, nsIArray *aProperties)
{
  m_ChannelDispatchOperation.Assign(aChannelDispatchOperation);
  m_Properties = aProperties;
}

csTpDispatchOperationDetails::~csTpDispatchOperationDetails()
{}

NS_IMETHODIMP
csTpDispatchOperationDetails::GetChannelDispatchOperation(nsACString &aChannelDispatchOperation)
{
  aChannelDispatchOperation.Assign(m_ChannelDispatchOperation);
  return NS_OK;
}

NS_IMETHODIMP
csTpDispatchOperationDetails::GetProperties(nsIArray **aProperties)
{
  NS_IF_ADDREF(*aProperties = m_Properties);
  return NS_OK;
}

static void
DispatchOperationsResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelDispatcherInterfaceOperationListDispatchOperationsCB *callback = (csITpChannelDispatcherInterfaceOperationListDispatchOperationsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyDispatchOperationsError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GPtrArray * dispatchoperations;
  dispatchoperations = (GPtrArray *)g_value_get_boxed(out);
  nsCOMPtr<nsIMutableArray> cDispatchOperations = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)dispatchoperations)->len; i++) {
    gpointer dispatchoperations_item = g_ptr_array_index((GPtrArray*)dispatchoperations, i);
    nsCOMPtr<csITpDispatchOperationDetails> cDispatchOperationsItem;
    csTpDispatchOperationDetails::Create((gpointer)dispatchoperations_item, getter_AddRefs(cDispatchOperationsItem));
    cDispatchOperations->AppendElement(cDispatchOperationsItem, PR_FALSE);
  }

  callback->GetPropertyDispatchOperationsDone(cDispatchOperations);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelDispatcherInterfaceOperationList::GetPropertyDispatchOperations(csITpChannelDispatcherInterfaceOperationListDispatchOperationsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.ChannelDispatcher.Interface.OperationList",
      "DispatchOperations",
      cb? DispatchOperationsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
NewDispatchOperationSignalCallback(TpChannelDispatcher *proxy,
    const gchar *dispatch_operation, GHashTable *properties,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelDispatcherInterfaceOperationList *obj = (csTpChannelDispatcherInterfaceOperationList *)user_data;
  if (!obj)
    return;

  obj->HandleNewDispatchOperation(dispatch_operation, properties);
}


void
csTpChannelDispatcherInterfaceOperationList::HandleNewDispatchOperation(const gchar *dispatch_operation, GHashTable *properties)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_NewDispatchOperationObservers->GetLength(&length);
  nsCOMPtr<csITpChannelDispatcherInterfaceOperationListNewDispatchOperationObserver> observer;

  nsCString cDispatchOperation = nsDependentCString(dispatch_operation);
  nsCOMPtr<nsIArray> cProperties;
  csTpQualifiedPropertyValueMap::Create((gpointer)properties, getter_AddRefs(cProperties));

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_NewDispatchOperationObservers, i);
    observer->OnNewDispatchOperation(cDispatchOperation, cProperties);
  }
}


NS_IMETHODIMP
csTpChannelDispatcherInterfaceOperationList::ConnectToNewDispatchOperation(csITpChannelDispatcherInterfaceOperationListNewDispatchOperationObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_NewDispatchOperationObservers) {
    m_NewDispatchOperationObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_dispatcher_interface_operation_list_connect_to_new_dispatch_operation(m_Proxy,
        NewDispatchOperationSignalCallback, this, NULL, NULL, NULL);
  }

  m_NewDispatchOperationObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelDispatcherInterfaceOperationList::DisconnectFromNewDispatchOperation(csITpChannelDispatcherInterfaceOperationListNewDispatchOperationObserver *observer)
{
  if (!m_NewDispatchOperationObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_NewDispatchOperationObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_NewDispatchOperationObservers->RemoveElementAt(idx);
}


static void
DispatchOperationFinishedSignalCallback(TpChannelDispatcher *proxy,
    const gchar *dispatch_operation,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelDispatcherInterfaceOperationList *obj = (csTpChannelDispatcherInterfaceOperationList *)user_data;
  if (!obj)
    return;

  obj->HandleDispatchOperationFinished(dispatch_operation);
}


void
csTpChannelDispatcherInterfaceOperationList::HandleDispatchOperationFinished(const gchar *dispatch_operation)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_DispatchOperationFinishedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelDispatcherInterfaceOperationListDispatchOperationFinishedObserver> observer;

  nsCString cDispatchOperation = nsDependentCString(dispatch_operation);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_DispatchOperationFinishedObservers, i);
    observer->OnDispatchOperationFinished(cDispatchOperation);
  }
}


NS_IMETHODIMP
csTpChannelDispatcherInterfaceOperationList::ConnectToDispatchOperationFinished(csITpChannelDispatcherInterfaceOperationListDispatchOperationFinishedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_DispatchOperationFinishedObservers) {
    m_DispatchOperationFinishedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_dispatcher_interface_operation_list_connect_to_dispatch_operation_finished(m_Proxy,
        DispatchOperationFinishedSignalCallback, this, NULL, NULL, NULL);
  }

  m_DispatchOperationFinishedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelDispatcherInterfaceOperationList::DisconnectFromDispatchOperationFinished(csITpChannelDispatcherInterfaceOperationListDispatchOperationFinishedObserver *observer)
{
  if (!m_DispatchOperationFinishedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_DispatchOperationFinishedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_DispatchOperationFinishedObservers->RemoveElementAt(idx);
}



csTpChannelDispatcherInterfaceOperationList::csTpChannelDispatcherInterfaceOperationList()
{}

csTpChannelDispatcherInterfaceOperationList::~csTpChannelDispatcherInterfaceOperationList()
{}
