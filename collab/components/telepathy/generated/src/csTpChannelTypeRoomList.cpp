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


#include "csTpChannelTypeRoomList.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpRoomInfo
 */

NS_IMPL_ISUPPORTS1(csTpRoomInfo, csITpRoomInfo)

NS_METHOD
csTpRoomInfo::Create(PRUint32 aHandle, const nsCString &aChannelType, nsIArray *aInfo, void **aResult)
{
  csITpRoomInfo *it = 
          new csTpRoomInfo(aHandle, aChannelType, aInfo);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpRoomInfo), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpRoomInfo::Create(gpointer aGLibItem, void **aResult)
{
  guint handle;
  const gchar *channel_type;
  GHashTable *info;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_ROOM_INFO);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &handle, 1, &channel_type, 2, &info,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cChannelType = nsDependentCString(channel_type);
  nsCOMPtr<nsIArray> cInfo;
  csTpStringVariantMap::Create((gpointer)info, getter_AddRefs(cInfo));
  csITpRoomInfo *it = new csTpRoomInfo(handle, cChannelType, cInfo);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpRoomInfo), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpRoomInfo::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpRoomInfo::csTpRoomInfo(PRUint32 aHandle, const nsCString &aChannelType, nsIArray *aInfo)
{
  m_Handle = aHandle;
  m_ChannelType.Assign(aChannelType);
  m_Info = aInfo;
}

csTpRoomInfo::~csTpRoomInfo()
{}

NS_IMETHODIMP
csTpRoomInfo::GetHandle(PRUint32 *aHandle)
{
  *aHandle = m_Handle;
  return NS_OK;
}

NS_IMETHODIMP
csTpRoomInfo::GetChannelType(nsACString &aChannelType)
{
  aChannelType.Assign(m_ChannelType);
  return NS_OK;
}

NS_IMETHODIMP
csTpRoomInfo::GetInfo(nsIArray **aInfo)
{
  NS_IF_ADDREF(*aInfo = m_Info);
  return NS_OK;
}

static void
ServerResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeRoomListServerCB *callback = (csITpChannelTypeRoomListServerCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyServerError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar * server;
  nsCString cServer = nsDependentCString(server);

  callback->GetPropertyServerDone(cServer);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeRoomList::GetPropertyServer(csITpChannelTypeRoomListServerCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.RoomList",
      "Server",
      cb? ServerResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetListingRoomsResponse(TpChannel *proxy,
    gboolean in_progress,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeRoomListGetListingRoomsCB *callback = (csITpChannelTypeRoomListGetListingRoomsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetListingRoomsError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnGetListingRoomsDone(in_progress);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeRoomList::CallGetListingRooms(csITpChannelTypeRoomListGetListingRoomsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_room_list_call_get_listing_rooms(m_Proxy, -1,
      cb? GetListingRoomsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GotRoomsSignalCallback(TpChannel *proxy,
    const GPtrArray *rooms,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeRoomList *obj = (csTpChannelTypeRoomList *)user_data;
  if (!obj)
    return;

  obj->HandleGotRooms(rooms);
}


void
csTpChannelTypeRoomList::HandleGotRooms(const GPtrArray *rooms)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_GotRoomsObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeRoomListGotRoomsObserver> observer;

  nsCOMPtr<nsIMutableArray> cRooms = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)rooms)->len; i++) {
    gpointer rooms_item = g_ptr_array_index((GPtrArray*)rooms, i);
    nsCOMPtr<csITpRoomInfo> cRoomsItem;
    csTpRoomInfo::Create((gpointer)rooms_item, getter_AddRefs(cRoomsItem));
    cRooms->AppendElement(cRoomsItem, PR_FALSE);
  }

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_GotRoomsObservers, i);
    observer->OnGotRooms(cRooms);
  }
}


NS_IMETHODIMP
csTpChannelTypeRoomList::ConnectToGotRooms(csITpChannelTypeRoomListGotRoomsObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_GotRoomsObservers) {
    m_GotRoomsObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_room_list_connect_to_got_rooms(m_Proxy,
        GotRoomsSignalCallback, this, NULL, NULL, NULL);
  }

  m_GotRoomsObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeRoomList::DisconnectFromGotRooms(csITpChannelTypeRoomListGotRoomsObserver *observer)
{
  if (!m_GotRoomsObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_GotRoomsObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_GotRoomsObservers->RemoveElementAt(idx);
}


static void
ListRoomsResponse(TpChannel *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeRoomListListRoomsCB *callback = (csITpChannelTypeRoomListListRoomsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnListRoomsError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnListRoomsDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeRoomList::CallListRooms(csITpChannelTypeRoomListListRoomsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_room_list_call_list_rooms(m_Proxy, -1,
      cb? ListRoomsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
StopListingResponse(TpChannel *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeRoomListStopListingCB *callback = (csITpChannelTypeRoomListStopListingCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnStopListingError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnStopListingDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeRoomList::CallStopListing(csITpChannelTypeRoomListStopListingCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_room_list_call_stop_listing(m_Proxy, -1,
      cb? StopListingResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ListingRoomsSignalCallback(TpChannel *proxy,
    gboolean listing,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeRoomList *obj = (csTpChannelTypeRoomList *)user_data;
  if (!obj)
    return;

  obj->HandleListingRooms(listing);
}


void
csTpChannelTypeRoomList::HandleListingRooms(gboolean listing)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_ListingRoomsObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeRoomListListingRoomsObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_ListingRoomsObservers, i);
    observer->OnListingRooms(listing);
  }
}


NS_IMETHODIMP
csTpChannelTypeRoomList::ConnectToListingRooms(csITpChannelTypeRoomListListingRoomsObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_ListingRoomsObservers) {
    m_ListingRoomsObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_room_list_connect_to_listing_rooms(m_Proxy,
        ListingRoomsSignalCallback, this, NULL, NULL, NULL);
  }

  m_ListingRoomsObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeRoomList::DisconnectFromListingRooms(csITpChannelTypeRoomListListingRoomsObserver *observer)
{
  if (!m_ListingRoomsObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_ListingRoomsObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_ListingRoomsObservers->RemoveElementAt(idx);
}



csTpChannelTypeRoomList::csTpChannelTypeRoomList()
{}

csTpChannelTypeRoomList::~csTpChannelTypeRoomList()
{}
