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


#include "csTpChannelInterfaceGroup.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpLocalPendingInfo
 */

NS_IMPL_ISUPPORTS1(csTpLocalPendingInfo, csITpLocalPendingInfo)

NS_METHOD
csTpLocalPendingInfo::Create(PRUint32 aToBeAdded, PRUint32 aActor, PRUint32 aReason, const nsCString &aMessage, void **aResult)
{
  csITpLocalPendingInfo *it = 
          new csTpLocalPendingInfo(aToBeAdded, aActor, aReason, aMessage);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpLocalPendingInfo), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpLocalPendingInfo::Create(gpointer aGLibItem, void **aResult)
{
  guint to_be_added;
  guint actor;
  guint reason;
  const gchar *message;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_LOCAL_PENDING_INFO);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &to_be_added, 1, &actor, 2, &reason, 3, &message,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cMessage = nsDependentCString(message);
  csITpLocalPendingInfo *it = new csTpLocalPendingInfo(to_be_added, actor, reason, cMessage);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpLocalPendingInfo), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpLocalPendingInfo::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpLocalPendingInfo::csTpLocalPendingInfo(PRUint32 aToBeAdded, PRUint32 aActor, PRUint32 aReason, const nsCString &aMessage)
{
  m_ToBeAdded = aToBeAdded;
  m_Actor = aActor;
  m_Reason = aReason;
  m_Message.Assign(aMessage);
}

csTpLocalPendingInfo::~csTpLocalPendingInfo()
{}

NS_IMETHODIMP
csTpLocalPendingInfo::GetToBeAdded(PRUint32 *aToBeAdded)
{
  *aToBeAdded = m_ToBeAdded;
  return NS_OK;
}

NS_IMETHODIMP
csTpLocalPendingInfo::GetActor(PRUint32 *aActor)
{
  *aActor = m_Actor;
  return NS_OK;
}

NS_IMETHODIMP
csTpLocalPendingInfo::GetReason(PRUint32 *aReason)
{
  *aReason = m_Reason;
  return NS_OK;
}

NS_IMETHODIMP
csTpLocalPendingInfo::GetMessage(nsACString &aMessage)
{
  aMessage.Assign(m_Message);
  return NS_OK;
}

static void
AddMembersResponse(TpChannel *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupAddMembersCB *callback = (csITpChannelInterfaceGroupAddMembersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnAddMembersError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnAddMembersDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::CallAddMembers(PRUint32 aContactsCount, PRUint32 *aContacts, const nsACString &aMessage,
    csITpChannelInterfaceGroupAddMembersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cContacts = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aContactsCount; i++)
    g_array_append_val(cContacts, aContacts[i]);
  char *cMessage = ToNewCString(aMessage);

  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_group_call_add_members(m_Proxy, -1,
      cContacts, cMessage,
      cb? AddMembersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetAllMembersResponse(TpChannel *proxy,
    const GArray *members, const GArray *local_pending, const GArray *remote_pending,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupGetAllMembersCB *callback = (csITpChannelInterfaceGroupGetAllMembersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetAllMembersError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cMembersCount = members->len;
  PRUint32 *cMembers = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cMembersCount);
  for (unsigned int i=0; i<cMembersCount; i++)
    cMembers[i] = g_array_index(members, guint, i);
  PRUint32 cLocalPendingCount = local_pending->len;
  PRUint32 *cLocalPending = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cLocalPendingCount);
  for (unsigned int i=0; i<cLocalPendingCount; i++)
    cLocalPending[i] = g_array_index(local_pending, guint, i);
  PRUint32 cRemotePendingCount = remote_pending->len;
  PRUint32 *cRemotePending = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cRemotePendingCount);
  for (unsigned int i=0; i<cRemotePendingCount; i++)
    cRemotePending[i] = g_array_index(remote_pending, guint, i);

  callback->OnGetAllMembersDone(cMembersCount, cMembers, cLocalPendingCount, cLocalPending, cRemotePendingCount, cRemotePending);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::CallGetAllMembers(csITpChannelInterfaceGroupGetAllMembersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_group_call_get_all_members(m_Proxy, -1,
      cb? GetAllMembersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GroupFlagsResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupGroupFlagsCB *callback = (csITpChannelInterfaceGroupGroupFlagsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyGroupFlagsError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  groupflags;

  callback->GetPropertyGroupFlagsDone(groupflags);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::GetPropertyGroupFlags(csITpChannelInterfaceGroupGroupFlagsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Interface.Group",
      "GroupFlags",
      cb? GroupFlagsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetGroupFlagsResponse(TpChannel *proxy,
    guint group_flags,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupGetGroupFlagsCB *callback = (csITpChannelInterfaceGroupGetGroupFlagsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetGroupFlagsError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnGetGroupFlagsDone(group_flags);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::CallGetGroupFlags(csITpChannelInterfaceGroupGetGroupFlagsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_group_call_get_group_flags(m_Proxy, -1,
      cb? GetGroupFlagsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


/*
 *  Implementation of csTpHandleOwnerMap
 */

NS_IMPL_ISUPPORTS1(csTpHandleOwnerMap, csITpHandleOwnerMap)

NS_METHOD
csTpHandleOwnerMap::Create(PRUint32 aChannelSpecificHandle, PRUint32 aGlobalHandle, void **aResult)
{
  csITpHandleOwnerMap *it = 
          new csTpHandleOwnerMap(aChannelSpecificHandle, aGlobalHandle);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpHandleOwnerMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpHandleOwnerMap::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    guint channel_specific_handle = GPOINTER_TO_UINT(keyPtr);
    guint global_handle = GPOINTER_TO_UINT(valuePtr);


    csITpHandleOwnerMap *temp = new csTpHandleOwnerMap(channel_specific_handle, global_handle);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpHandleOwnerMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpHandleOwnerMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpHandleOwnerMap::csTpHandleOwnerMap(PRUint32 aChannelSpecificHandle, PRUint32 aGlobalHandle)
{
  m_ChannelSpecificHandle = aChannelSpecificHandle;
  m_GlobalHandle = aGlobalHandle;
}

csTpHandleOwnerMap::~csTpHandleOwnerMap()
{}

NS_IMETHODIMP
csTpHandleOwnerMap::GetChannelSpecificHandle(PRUint32 *aChannelSpecificHandle)
{
  *aChannelSpecificHandle = m_ChannelSpecificHandle;
  return NS_OK;
}

NS_IMETHODIMP
csTpHandleOwnerMap::GetGlobalHandle(PRUint32 *aGlobalHandle)
{
  *aGlobalHandle = m_GlobalHandle;
  return NS_OK;
}

static void
HandleOwnersResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupHandleOwnersCB *callback = (csITpChannelInterfaceGroupHandleOwnersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyHandleOwnersError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GHashTable * handleowners;
  handleowners = (GHashTable *)g_value_get_boxed(out);
  nsCOMPtr<nsIArray> cHandleOwners;
  csTpHandleOwnerMap::Create((gpointer)handleowners, getter_AddRefs(cHandleOwners));

  callback->GetPropertyHandleOwnersDone(cHandleOwners);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::GetPropertyHandleOwners(csITpChannelInterfaceGroupHandleOwnersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Interface.Group",
      "HandleOwners",
      cb? HandleOwnersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
HandleOwnersChangedSignalCallback(TpChannel *proxy,
    GHashTable *added, const GArray *removed,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelInterfaceGroup *obj = (csTpChannelInterfaceGroup *)user_data;
  if (!obj)
    return;

  obj->HandleHandleOwnersChanged(added, removed);
}


void
csTpChannelInterfaceGroup::HandleHandleOwnersChanged(GHashTable *added, const GArray *removed)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_HandleOwnersChangedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelInterfaceGroupHandleOwnersChangedObserver> observer;

  nsCOMPtr<nsIArray> cAdded;
  csTpHandleOwnerMap::Create((gpointer)added, getter_AddRefs(cAdded));
  PRUint32 cRemovedCount = removed->len;
  PRUint32 *cRemoved = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cRemovedCount);
  for (unsigned int i=0; i<cRemovedCount; i++)
    cRemoved[i] = g_array_index(removed, guint, i);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_HandleOwnersChangedObservers, i);
    observer->OnHandleOwnersChanged(cAdded, cRemovedCount, cRemoved);
  }
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::ConnectToHandleOwnersChanged(csITpChannelInterfaceGroupHandleOwnersChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_HandleOwnersChangedObservers) {
    m_HandleOwnersChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_interface_group_connect_to_handle_owners_changed(m_Proxy,
        HandleOwnersChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_HandleOwnersChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::DisconnectFromHandleOwnersChanged(csITpChannelInterfaceGroupHandleOwnersChangedObserver *observer)
{
  if (!m_HandleOwnersChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_HandleOwnersChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_HandleOwnersChangedObservers->RemoveElementAt(idx);
}


static void
GetHandleOwnersResponse(TpChannel *proxy,
    const GArray *owners,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupGetHandleOwnersCB *callback = (csITpChannelInterfaceGroupGetHandleOwnersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetHandleOwnersError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cOwnersCount = owners->len;
  PRUint32 *cOwners = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cOwnersCount);
  for (unsigned int i=0; i<cOwnersCount; i++)
    cOwners[i] = g_array_index(owners, guint, i);

  callback->OnGetHandleOwnersDone(cOwnersCount, cOwners);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::CallGetHandleOwners(PRUint32 aHandlesCount, PRUint32 *aHandles,
    csITpChannelInterfaceGroupGetHandleOwnersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cHandles = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aHandlesCount; i++)
    g_array_append_val(cHandles, aHandles[i]);

  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_group_call_get_handle_owners(m_Proxy, -1,
      cHandles,
      cb? GetHandleOwnersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetLocalPendingMembersResponse(TpChannel *proxy,
    const GArray *handles,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupGetLocalPendingMembersCB *callback = (csITpChannelInterfaceGroupGetLocalPendingMembersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetLocalPendingMembersError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cHandlesCount = handles->len;
  PRUint32 *cHandles = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cHandlesCount);
  for (unsigned int i=0; i<cHandlesCount; i++)
    cHandles[i] = g_array_index(handles, guint, i);

  callback->OnGetLocalPendingMembersDone(cHandlesCount, cHandles);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::CallGetLocalPendingMembers(csITpChannelInterfaceGroupGetLocalPendingMembersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_group_call_get_local_pending_members(m_Proxy, -1,
      cb? GetLocalPendingMembersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetLocalPendingMembersWithInfoResponse(TpChannel *proxy,
    const GPtrArray *info,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupGetLocalPendingMembersWithInfoCB *callback = (csITpChannelInterfaceGroupGetLocalPendingMembersWithInfoCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetLocalPendingMembersWithInfoError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIMutableArray> cInfo = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)info)->len; i++) {
    gpointer info_item = g_ptr_array_index((GPtrArray*)info, i);
    nsCOMPtr<csITpLocalPendingInfo> cInfoItem;
    csTpLocalPendingInfo::Create((gpointer)info_item, getter_AddRefs(cInfoItem));
    cInfo->AppendElement(cInfoItem, PR_FALSE);
  }

  callback->OnGetLocalPendingMembersWithInfoDone(cInfo);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::CallGetLocalPendingMembersWithInfo(csITpChannelInterfaceGroupGetLocalPendingMembersWithInfoCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_group_call_get_local_pending_members_with_info(m_Proxy, -1,
      cb? GetLocalPendingMembersWithInfoResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
LocalPendingMembersResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupLocalPendingMembersCB *callback = (csITpChannelInterfaceGroupLocalPendingMembersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyLocalPendingMembersError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GPtrArray * localpendingmembers;
  localpendingmembers = (GPtrArray *)g_value_get_boxed(out);
  nsCOMPtr<nsIMutableArray> cLocalPendingMembers = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)localpendingmembers)->len; i++) {
    gpointer localpendingmembers_item = g_ptr_array_index((GPtrArray*)localpendingmembers, i);
    nsCOMPtr<csITpLocalPendingInfo> cLocalPendingMembersItem;
    csTpLocalPendingInfo::Create((gpointer)localpendingmembers_item, getter_AddRefs(cLocalPendingMembersItem));
    cLocalPendingMembers->AppendElement(cLocalPendingMembersItem, PR_FALSE);
  }

  callback->GetPropertyLocalPendingMembersDone(cLocalPendingMembers);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::GetPropertyLocalPendingMembers(csITpChannelInterfaceGroupLocalPendingMembersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Interface.Group",
      "LocalPendingMembers",
      cb? LocalPendingMembersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
MembersResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupMembersCB *callback = (csITpChannelInterfaceGroupMembersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyMembersError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GArray * members;
  members = (GArray *)g_value_get_boxed(out);
  PRUint32 cMembersCount = members->len;
  PRUint32 *cMembers = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cMembersCount);
  for (unsigned int i=0; i<cMembersCount; i++)
    cMembers[i] = g_array_index(members, guint, i);

  callback->GetPropertyMembersDone(cMembersCount, cMembers);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::GetPropertyMembers(csITpChannelInterfaceGroupMembersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Interface.Group",
      "Members",
      cb? MembersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetMembersResponse(TpChannel *proxy,
    const GArray *handles,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupGetMembersCB *callback = (csITpChannelInterfaceGroupGetMembersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetMembersError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cHandlesCount = handles->len;
  PRUint32 *cHandles = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cHandlesCount);
  for (unsigned int i=0; i<cHandlesCount; i++)
    cHandles[i] = g_array_index(handles, guint, i);

  callback->OnGetMembersDone(cHandlesCount, cHandles);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::CallGetMembers(csITpChannelInterfaceGroupGetMembersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_group_call_get_members(m_Proxy, -1,
      cb? GetMembersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RemotePendingMembersResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupRemotePendingMembersCB *callback = (csITpChannelInterfaceGroupRemotePendingMembersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyRemotePendingMembersError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GArray * remotependingmembers;
  remotependingmembers = (GArray *)g_value_get_boxed(out);
  PRUint32 cRemotePendingMembersCount = remotependingmembers->len;
  PRUint32 *cRemotePendingMembers = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cRemotePendingMembersCount);
  for (unsigned int i=0; i<cRemotePendingMembersCount; i++)
    cRemotePendingMembers[i] = g_array_index(remotependingmembers, guint, i);

  callback->GetPropertyRemotePendingMembersDone(cRemotePendingMembersCount, cRemotePendingMembers);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::GetPropertyRemotePendingMembers(csITpChannelInterfaceGroupRemotePendingMembersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Interface.Group",
      "RemotePendingMembers",
      cb? RemotePendingMembersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetRemotePendingMembersResponse(TpChannel *proxy,
    const GArray *handles,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupGetRemotePendingMembersCB *callback = (csITpChannelInterfaceGroupGetRemotePendingMembersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetRemotePendingMembersError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cHandlesCount = handles->len;
  PRUint32 *cHandles = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cHandlesCount);
  for (unsigned int i=0; i<cHandlesCount; i++)
    cHandles[i] = g_array_index(handles, guint, i);

  callback->OnGetRemotePendingMembersDone(cHandlesCount, cHandles);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::CallGetRemotePendingMembers(csITpChannelInterfaceGroupGetRemotePendingMembersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_group_call_get_remote_pending_members(m_Proxy, -1,
      cb? GetRemotePendingMembersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
SelfHandleChangedSignalCallback(TpChannel *proxy,
    guint self_handle,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelInterfaceGroup *obj = (csTpChannelInterfaceGroup *)user_data;
  if (!obj)
    return;

  obj->HandleSelfHandleChanged(self_handle);
}


void
csTpChannelInterfaceGroup::HandleSelfHandleChanged(guint self_handle)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_SelfHandleChangedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelInterfaceGroupSelfHandleChangedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_SelfHandleChangedObservers, i);
    observer->OnSelfHandleChanged(self_handle);
  }
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::ConnectToSelfHandleChanged(csITpChannelInterfaceGroupSelfHandleChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_SelfHandleChangedObservers) {
    m_SelfHandleChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_interface_group_connect_to_self_handle_changed(m_Proxy,
        SelfHandleChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_SelfHandleChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::DisconnectFromSelfHandleChanged(csITpChannelInterfaceGroupSelfHandleChangedObserver *observer)
{
  if (!m_SelfHandleChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_SelfHandleChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_SelfHandleChangedObservers->RemoveElementAt(idx);
}


static void
SelfHandleResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupSelfHandleCB *callback = (csITpChannelInterfaceGroupSelfHandleCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertySelfHandleError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  selfhandle;

  callback->GetPropertySelfHandleDone(selfhandle);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::GetPropertySelfHandle(csITpChannelInterfaceGroupSelfHandleCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Interface.Group",
      "SelfHandle",
      cb? SelfHandleResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetSelfHandleResponse(TpChannel *proxy,
    guint self_handle,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupGetSelfHandleCB *callback = (csITpChannelInterfaceGroupGetSelfHandleCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetSelfHandleError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnGetSelfHandleDone(self_handle);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::CallGetSelfHandle(csITpChannelInterfaceGroupGetSelfHandleCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_group_call_get_self_handle(m_Proxy, -1,
      cb? GetSelfHandleResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GroupFlagsChangedSignalCallback(TpChannel *proxy,
    guint added, guint removed,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelInterfaceGroup *obj = (csTpChannelInterfaceGroup *)user_data;
  if (!obj)
    return;

  obj->HandleGroupFlagsChanged(added, removed);
}


void
csTpChannelInterfaceGroup::HandleGroupFlagsChanged(guint added, guint removed)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_GroupFlagsChangedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelInterfaceGroupGroupFlagsChangedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_GroupFlagsChangedObservers, i);
    observer->OnGroupFlagsChanged(added, removed);
  }
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::ConnectToGroupFlagsChanged(csITpChannelInterfaceGroupGroupFlagsChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_GroupFlagsChangedObservers) {
    m_GroupFlagsChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_interface_group_connect_to_group_flags_changed(m_Proxy,
        GroupFlagsChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_GroupFlagsChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::DisconnectFromGroupFlagsChanged(csITpChannelInterfaceGroupGroupFlagsChangedObserver *observer)
{
  if (!m_GroupFlagsChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_GroupFlagsChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_GroupFlagsChangedObservers->RemoveElementAt(idx);
}


static void
MembersChangedSignalCallback(TpChannel *proxy,
    const gchar *message, const GArray *added, const GArray *removed, const GArray *local_pending, const GArray *remote_pending, guint actor, guint reason,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelInterfaceGroup *obj = (csTpChannelInterfaceGroup *)user_data;
  if (!obj)
    return;

  obj->HandleMembersChanged(message, added, removed, local_pending, remote_pending, actor, reason);
}


void
csTpChannelInterfaceGroup::HandleMembersChanged(const gchar *message, const GArray *added, const GArray *removed, const GArray *local_pending, const GArray *remote_pending, guint actor, guint reason)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_MembersChangedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelInterfaceGroupMembersChangedObserver> observer;

  nsCString cMessage = nsDependentCString(message);
  PRUint32 cAddedCount = added->len;
  PRUint32 *cAdded = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cAddedCount);
  for (unsigned int i=0; i<cAddedCount; i++)
    cAdded[i] = g_array_index(added, guint, i);
  PRUint32 cRemovedCount = removed->len;
  PRUint32 *cRemoved = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cRemovedCount);
  for (unsigned int i=0; i<cRemovedCount; i++)
    cRemoved[i] = g_array_index(removed, guint, i);
  PRUint32 cLocalPendingCount = local_pending->len;
  PRUint32 *cLocalPending = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cLocalPendingCount);
  for (unsigned int i=0; i<cLocalPendingCount; i++)
    cLocalPending[i] = g_array_index(local_pending, guint, i);
  PRUint32 cRemotePendingCount = remote_pending->len;
  PRUint32 *cRemotePending = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cRemotePendingCount);
  for (unsigned int i=0; i<cRemotePendingCount; i++)
    cRemotePending[i] = g_array_index(remote_pending, guint, i);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_MembersChangedObservers, i);
    observer->OnMembersChanged(cMessage, cAddedCount, cAdded, cRemovedCount, cRemoved, cLocalPendingCount, cLocalPending, cRemotePendingCount, cRemotePending, actor, reason);
  }
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::ConnectToMembersChanged(csITpChannelInterfaceGroupMembersChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_MembersChangedObservers) {
    m_MembersChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_interface_group_connect_to_members_changed(m_Proxy,
        MembersChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_MembersChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::DisconnectFromMembersChanged(csITpChannelInterfaceGroupMembersChangedObserver *observer)
{
  if (!m_MembersChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_MembersChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_MembersChangedObservers->RemoveElementAt(idx);
}


/*
 *  Implementation of csTpHandleIdentifierMap
 */

NS_IMPL_ISUPPORTS1(csTpHandleIdentifierMap, csITpHandleIdentifierMap)

NS_METHOD
csTpHandleIdentifierMap::Create(PRUint32 aHandle, const nsCString &aIdentifier, void **aResult)
{
  csITpHandleIdentifierMap *it = 
          new csTpHandleIdentifierMap(aHandle, aIdentifier);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpHandleIdentifierMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpHandleIdentifierMap::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    guint handle = GPOINTER_TO_UINT(keyPtr);
    const gchar *identifier = (gchar *)valuePtr;

    nsCString cIdentifier = nsDependentCString(identifier);

    csITpHandleIdentifierMap *temp = new csTpHandleIdentifierMap(handle, cIdentifier);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpHandleIdentifierMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpHandleIdentifierMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpHandleIdentifierMap::csTpHandleIdentifierMap(PRUint32 aHandle, const nsCString &aIdentifier)
{
  m_Handle = aHandle;
  m_Identifier.Assign(aIdentifier);
}

csTpHandleIdentifierMap::~csTpHandleIdentifierMap()
{}

NS_IMETHODIMP
csTpHandleIdentifierMap::GetHandle(PRUint32 *aHandle)
{
  *aHandle = m_Handle;
  return NS_OK;
}

NS_IMETHODIMP
csTpHandleIdentifierMap::GetIdentifier(nsACString &aIdentifier)
{
  aIdentifier.Assign(m_Identifier);
  return NS_OK;
}

static void
MembersChangedDetailedSignalCallback(TpChannel *proxy,
    const GArray *added, const GArray *removed, const GArray *local_pending, const GArray *remote_pending, GHashTable *details,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelInterfaceGroup *obj = (csTpChannelInterfaceGroup *)user_data;
  if (!obj)
    return;

  obj->HandleMembersChangedDetailed(added, removed, local_pending, remote_pending, details);
}


void
csTpChannelInterfaceGroup::HandleMembersChangedDetailed(const GArray *added, const GArray *removed, const GArray *local_pending, const GArray *remote_pending, GHashTable *details)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_MembersChangedDetailedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelInterfaceGroupMembersChangedDetailedObserver> observer;

  PRUint32 cAddedCount = added->len;
  PRUint32 *cAdded = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cAddedCount);
  for (unsigned int i=0; i<cAddedCount; i++)
    cAdded[i] = g_array_index(added, guint, i);
  PRUint32 cRemovedCount = removed->len;
  PRUint32 *cRemoved = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cRemovedCount);
  for (unsigned int i=0; i<cRemovedCount; i++)
    cRemoved[i] = g_array_index(removed, guint, i);
  PRUint32 cLocalPendingCount = local_pending->len;
  PRUint32 *cLocalPending = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cLocalPendingCount);
  for (unsigned int i=0; i<cLocalPendingCount; i++)
    cLocalPending[i] = g_array_index(local_pending, guint, i);
  PRUint32 cRemotePendingCount = remote_pending->len;
  PRUint32 *cRemotePending = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cRemotePendingCount);
  for (unsigned int i=0; i<cRemotePendingCount; i++)
    cRemotePending[i] = g_array_index(remote_pending, guint, i);
  nsCOMPtr<nsIArray> cDetails;
  csTpStringVariantMap::Create((gpointer)details, getter_AddRefs(cDetails));

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_MembersChangedDetailedObservers, i);
    observer->OnMembersChangedDetailed(cAddedCount, cAdded, cRemovedCount, cRemoved, cLocalPendingCount, cLocalPending, cRemotePendingCount, cRemotePending, cDetails);
  }
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::ConnectToMembersChangedDetailed(csITpChannelInterfaceGroupMembersChangedDetailedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_MembersChangedDetailedObservers) {
    m_MembersChangedDetailedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_interface_group_connect_to_members_changed_detailed(m_Proxy,
        MembersChangedDetailedSignalCallback, this, NULL, NULL, NULL);
  }

  m_MembersChangedDetailedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::DisconnectFromMembersChangedDetailed(csITpChannelInterfaceGroupMembersChangedDetailedObserver *observer)
{
  if (!m_MembersChangedDetailedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_MembersChangedDetailedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_MembersChangedDetailedObservers->RemoveElementAt(idx);
}


static void
RemoveMembersResponse(TpChannel *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupRemoveMembersCB *callback = (csITpChannelInterfaceGroupRemoveMembersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnRemoveMembersError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnRemoveMembersDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::CallRemoveMembers(PRUint32 aContactsCount, PRUint32 *aContacts, const nsACString &aMessage,
    csITpChannelInterfaceGroupRemoveMembersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cContacts = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aContactsCount; i++)
    g_array_append_val(cContacts, aContacts[i]);
  char *cMessage = ToNewCString(aMessage);

  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_group_call_remove_members(m_Proxy, -1,
      cContacts, cMessage,
      cb? RemoveMembersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RemoveMembersWithReasonResponse(TpChannel *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceGroupRemoveMembersWithReasonCB *callback = (csITpChannelInterfaceGroupRemoveMembersWithReasonCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnRemoveMembersWithReasonError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnRemoveMembersWithReasonDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceGroup::CallRemoveMembersWithReason(PRUint32 aContactsCount, PRUint32 *aContacts, const nsACString &aMessage, PRUint32 aReason,
    csITpChannelInterfaceGroupRemoveMembersWithReasonCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cContacts = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aContactsCount; i++)
    g_array_append_val(cContacts, aContacts[i]);
  char *cMessage = ToNewCString(aMessage);

  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_group_call_remove_members_with_reason(m_Proxy, -1,
      cContacts, cMessage, aReason,
      cb? RemoveMembersWithReasonResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpChannelInterfaceGroup::csTpChannelInterfaceGroup()
{}

csTpChannelInterfaceGroup::~csTpChannelInterfaceGroup()
{}
