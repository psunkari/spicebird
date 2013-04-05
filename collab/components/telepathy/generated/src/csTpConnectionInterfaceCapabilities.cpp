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


#include "csTpConnectionInterfaceCapabilities.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpCapabilityPair
 */

NS_IMPL_ISUPPORTS1(csTpCapabilityPair, csITpCapabilityPair)

NS_METHOD
csTpCapabilityPair::Create(const nsCString &aChannelType, PRUint32 aTypeSpecificFlags, void **aResult)
{
  csITpCapabilityPair *it = 
          new csTpCapabilityPair(aChannelType, aTypeSpecificFlags);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpCapabilityPair), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpCapabilityPair::Create(gpointer aGLibItem, void **aResult)
{
  const gchar *channel_type;
  guint type_specific_flags;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_CAPABILITY_PAIR);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &channel_type, 1, &type_specific_flags,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cChannelType = nsDependentCString(channel_type);
  csITpCapabilityPair *it = new csTpCapabilityPair(cChannelType, type_specific_flags);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpCapabilityPair), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpCapabilityPair::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpCapabilityPair::csTpCapabilityPair(const nsCString &aChannelType, PRUint32 aTypeSpecificFlags)
{
  m_ChannelType.Assign(aChannelType);
  m_TypeSpecificFlags = aTypeSpecificFlags;
}

csTpCapabilityPair::~csTpCapabilityPair()
{}

NS_IMETHODIMP
csTpCapabilityPair::GetChannelType(nsACString &aChannelType)
{
  aChannelType.Assign(m_ChannelType);
  return NS_OK;
}

NS_IMETHODIMP
csTpCapabilityPair::GetTypeSpecificFlags(PRUint32 *aTypeSpecificFlags)
{
  *aTypeSpecificFlags = m_TypeSpecificFlags;
  return NS_OK;
}

/*
 *  Implementation of csTpContactCapability
 */

NS_IMPL_ISUPPORTS1(csTpContactCapability, csITpContactCapability)

NS_METHOD
csTpContactCapability::Create(PRUint32 aHandle, const nsCString &aChannelType, PRUint32 aGenericFlags, PRUint32 aTypeSpecificFlags, void **aResult)
{
  csITpContactCapability *it = 
          new csTpContactCapability(aHandle, aChannelType, aGenericFlags, aTypeSpecificFlags);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpContactCapability), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpContactCapability::Create(gpointer aGLibItem, void **aResult)
{
  guint handle;
  const gchar *channel_type;
  guint generic_flags;
  guint type_specific_flags;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_CONTACT_CAPABILITY);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &handle, 1, &channel_type, 2, &generic_flags, 3, &type_specific_flags,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cChannelType = nsDependentCString(channel_type);
  csITpContactCapability *it = new csTpContactCapability(handle, cChannelType, generic_flags, type_specific_flags);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpContactCapability), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpContactCapability::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpContactCapability::csTpContactCapability(PRUint32 aHandle, const nsCString &aChannelType, PRUint32 aGenericFlags, PRUint32 aTypeSpecificFlags)
{
  m_Handle = aHandle;
  m_ChannelType.Assign(aChannelType);
  m_GenericFlags = aGenericFlags;
  m_TypeSpecificFlags = aTypeSpecificFlags;
}

csTpContactCapability::~csTpContactCapability()
{}

NS_IMETHODIMP
csTpContactCapability::GetHandle(PRUint32 *aHandle)
{
  *aHandle = m_Handle;
  return NS_OK;
}

NS_IMETHODIMP
csTpContactCapability::GetChannelType(nsACString &aChannelType)
{
  aChannelType.Assign(m_ChannelType);
  return NS_OK;
}

NS_IMETHODIMP
csTpContactCapability::GetGenericFlags(PRUint32 *aGenericFlags)
{
  *aGenericFlags = m_GenericFlags;
  return NS_OK;
}

NS_IMETHODIMP
csTpContactCapability::GetTypeSpecificFlags(PRUint32 *aTypeSpecificFlags)
{
  *aTypeSpecificFlags = m_TypeSpecificFlags;
  return NS_OK;
}

/*
 *  Implementation of csTpCapabilityChange
 */

NS_IMPL_ISUPPORTS1(csTpCapabilityChange, csITpCapabilityChange)

NS_METHOD
csTpCapabilityChange::Create(PRUint32 aHandle, const nsCString &aChannelType, PRUint32 aOldGenericFlags, PRUint32 aNewGenericFlags, PRUint32 aOldTypeSpecificFlags, PRUint32 aNewTypeSpecificFlags, void **aResult)
{
  csITpCapabilityChange *it = 
          new csTpCapabilityChange(aHandle, aChannelType, aOldGenericFlags, aNewGenericFlags, aOldTypeSpecificFlags, aNewTypeSpecificFlags);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpCapabilityChange), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpCapabilityChange::Create(gpointer aGLibItem, void **aResult)
{
  guint handle;
  const gchar *channel_type;
  guint old_generic_flags;
  guint new_generic_flags;
  guint old_type_specific_flags;
  guint new_type_specific_flags;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_CAPABILITY_CHANGE);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &handle, 1, &channel_type, 2, &old_generic_flags, 3, &new_generic_flags, 4, &old_type_specific_flags, 5, &new_type_specific_flags,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cChannelType = nsDependentCString(channel_type);
  csITpCapabilityChange *it = new csTpCapabilityChange(handle, cChannelType, old_generic_flags, new_generic_flags, old_type_specific_flags, new_type_specific_flags);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpCapabilityChange), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpCapabilityChange::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpCapabilityChange::csTpCapabilityChange(PRUint32 aHandle, const nsCString &aChannelType, PRUint32 aOldGenericFlags, PRUint32 aNewGenericFlags, PRUint32 aOldTypeSpecificFlags, PRUint32 aNewTypeSpecificFlags)
{
  m_Handle = aHandle;
  m_ChannelType.Assign(aChannelType);
  m_OldGenericFlags = aOldGenericFlags;
  m_NewGenericFlags = aNewGenericFlags;
  m_OldTypeSpecificFlags = aOldTypeSpecificFlags;
  m_NewTypeSpecificFlags = aNewTypeSpecificFlags;
}

csTpCapabilityChange::~csTpCapabilityChange()
{}

NS_IMETHODIMP
csTpCapabilityChange::GetHandle(PRUint32 *aHandle)
{
  *aHandle = m_Handle;
  return NS_OK;
}

NS_IMETHODIMP
csTpCapabilityChange::GetChannelType(nsACString &aChannelType)
{
  aChannelType.Assign(m_ChannelType);
  return NS_OK;
}

NS_IMETHODIMP
csTpCapabilityChange::GetOldGenericFlags(PRUint32 *aOldGenericFlags)
{
  *aOldGenericFlags = m_OldGenericFlags;
  return NS_OK;
}

NS_IMETHODIMP
csTpCapabilityChange::GetNewGenericFlags(PRUint32 *aNewGenericFlags)
{
  *aNewGenericFlags = m_NewGenericFlags;
  return NS_OK;
}

NS_IMETHODIMP
csTpCapabilityChange::GetOldTypeSpecificFlags(PRUint32 *aOldTypeSpecificFlags)
{
  *aOldTypeSpecificFlags = m_OldTypeSpecificFlags;
  return NS_OK;
}

NS_IMETHODIMP
csTpCapabilityChange::GetNewTypeSpecificFlags(PRUint32 *aNewTypeSpecificFlags)
{
  *aNewTypeSpecificFlags = m_NewTypeSpecificFlags;
  return NS_OK;
}

static void
AdvertiseCapabilitiesResponse(TpConnection *proxy,
    const GPtrArray *self_capabilities,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceCapabilitiesAdvertiseCapabilitiesCB *callback = (csITpConnectionInterfaceCapabilitiesAdvertiseCapabilitiesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnAdvertiseCapabilitiesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIMutableArray> cSelfCapabilities = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)self_capabilities)->len; i++) {
    gpointer self_capabilities_item = g_ptr_array_index((GPtrArray*)self_capabilities, i);
    nsCOMPtr<csITpCapabilityPair> cSelfCapabilitiesItem;
    csTpCapabilityPair::Create((gpointer)self_capabilities_item, getter_AddRefs(cSelfCapabilitiesItem));
    cSelfCapabilities->AppendElement(cSelfCapabilitiesItem, PR_FALSE);
  }

  callback->OnAdvertiseCapabilitiesDone(cSelfCapabilities);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceCapabilities::CallAdvertiseCapabilities(nsIArray *aAdd, PRUint32 aRemoveCount, const char **aRemove,
    csITpConnectionInterfaceCapabilitiesAdvertiseCapabilitiesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  /* TODO */
  char **cRemove = (char **)nsMemory::Alloc((aRemoveCount + 1) * sizeof(char*));
  for (PRUint32 i=0; i<aRemoveCount; i++)
    cRemove[i] = (char *)nsMemory::Clone(aRemove[i], strlen(aRemove[i]) + 1);
  cRemove[aRemoveCount] = NULL;

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_capabilities_call_advertise_capabilities(m_Proxy, -1,
      NULL, (const char**) cRemove,
      cb? AdvertiseCapabilitiesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
CapabilitiesChangedSignalCallback(TpConnection *proxy,
    const GPtrArray *caps,
    gpointer user_data, GObject *weak_object)
{
  csTpConnectionInterfaceCapabilities *obj = (csTpConnectionInterfaceCapabilities *)user_data;
  if (!obj)
    return;

  obj->HandleCapabilitiesChanged(caps);
}


void
csTpConnectionInterfaceCapabilities::HandleCapabilitiesChanged(const GPtrArray *caps)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_CapabilitiesChangedObservers->GetLength(&length);
  nsCOMPtr<csITpConnectionInterfaceCapabilitiesCapabilitiesChangedObserver> observer;

  nsCOMPtr<nsIMutableArray> cCaps = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)caps)->len; i++) {
    gpointer caps_item = g_ptr_array_index((GPtrArray*)caps, i);
    nsCOMPtr<csITpCapabilityChange> cCapsItem;
    csTpCapabilityChange::Create((gpointer)caps_item, getter_AddRefs(cCapsItem));
    cCaps->AppendElement(cCapsItem, PR_FALSE);
  }

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_CapabilitiesChangedObservers, i);
    observer->OnCapabilitiesChanged(cCaps);
  }
}


NS_IMETHODIMP
csTpConnectionInterfaceCapabilities::ConnectToCapabilitiesChanged(csITpConnectionInterfaceCapabilitiesCapabilitiesChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_CapabilitiesChangedObservers) {
    m_CapabilitiesChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_connection_interface_capabilities_connect_to_capabilities_changed(m_Proxy,
        CapabilitiesChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_CapabilitiesChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpConnectionInterfaceCapabilities::DisconnectFromCapabilitiesChanged(csITpConnectionInterfaceCapabilitiesCapabilitiesChangedObserver *observer)
{
  if (!m_CapabilitiesChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_CapabilitiesChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_CapabilitiesChangedObservers->RemoveElementAt(idx);
}


static void
GetCapabilitiesResponse(TpConnection *proxy,
    const GPtrArray *contact_capabilities,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpConnectionInterfaceCapabilitiesGetCapabilitiesCB *callback = (csITpConnectionInterfaceCapabilitiesGetCapabilitiesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetCapabilitiesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIMutableArray> cContactCapabilities = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)contact_capabilities)->len; i++) {
    gpointer contact_capabilities_item = g_ptr_array_index((GPtrArray*)contact_capabilities, i);
    nsCOMPtr<csITpContactCapability> cContactCapabilitiesItem;
    csTpContactCapability::Create((gpointer)contact_capabilities_item, getter_AddRefs(cContactCapabilitiesItem));
    cContactCapabilities->AppendElement(cContactCapabilitiesItem, PR_FALSE);
  }

  callback->OnGetCapabilitiesDone(cContactCapabilities);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpConnectionInterfaceCapabilities::CallGetCapabilities(PRUint32 aHandlesCount, PRUint32 *aHandles,
    csITpConnectionInterfaceCapabilitiesGetCapabilitiesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cHandles = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aHandlesCount; i++)
    g_array_append_val(cHandles, aHandles[i]);

  NS_IF_ADDREF(cb);
  tp_cli_connection_interface_capabilities_call_get_capabilities(m_Proxy, -1,
      cHandles,
      cb? GetCapabilitiesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpConnectionInterfaceCapabilities::csTpConnectionInterfaceCapabilities()
{}

csTpConnectionInterfaceCapabilities::~csTpConnectionInterfaceCapabilities()
{}
