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


#include "csTpChannelTypeStreamedMedia.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpMediaStreamInfo
 */

NS_IMPL_ISUPPORTS1(csTpMediaStreamInfo, csITpMediaStreamInfo)

NS_METHOD
csTpMediaStreamInfo::Create(PRUint32 aIdentifier, PRUint32 aContact, PRUint32 aType, PRUint32 aState, PRUint32 aDirection, PRUint32 aPendingSendFlags, void **aResult)
{
  csITpMediaStreamInfo *it = 
          new csTpMediaStreamInfo(aIdentifier, aContact, aType, aState, aDirection, aPendingSendFlags);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpMediaStreamInfo), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpMediaStreamInfo::Create(gpointer aGLibItem, void **aResult)
{
  guint identifier;
  guint contact;
  guint type;
  guint state;
  guint direction;
  guint pending_send_flags;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_MEDIA_STREAM_INFO);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &identifier, 1, &contact, 2, &type, 3, &state, 4, &direction, 5, &pending_send_flags,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  csITpMediaStreamInfo *it = new csTpMediaStreamInfo(identifier, contact, type, state, direction, pending_send_flags);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpMediaStreamInfo), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpMediaStreamInfo::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpMediaStreamInfo::csTpMediaStreamInfo(PRUint32 aIdentifier, PRUint32 aContact, PRUint32 aType, PRUint32 aState, PRUint32 aDirection, PRUint32 aPendingSendFlags)
{
  m_Identifier = aIdentifier;
  m_Contact = aContact;
  m_Type = aType;
  m_State = aState;
  m_Direction = aDirection;
  m_PendingSendFlags = aPendingSendFlags;
}

csTpMediaStreamInfo::~csTpMediaStreamInfo()
{}

NS_IMETHODIMP
csTpMediaStreamInfo::GetIdentifier(PRUint32 *aIdentifier)
{
  *aIdentifier = m_Identifier;
  return NS_OK;
}

NS_IMETHODIMP
csTpMediaStreamInfo::GetContact(PRUint32 *aContact)
{
  *aContact = m_Contact;
  return NS_OK;
}

NS_IMETHODIMP
csTpMediaStreamInfo::GetType(PRUint32 *aType)
{
  *aType = m_Type;
  return NS_OK;
}

NS_IMETHODIMP
csTpMediaStreamInfo::GetState(PRUint32 *aState)
{
  *aState = m_State;
  return NS_OK;
}

NS_IMETHODIMP
csTpMediaStreamInfo::GetDirection(PRUint32 *aDirection)
{
  *aDirection = m_Direction;
  return NS_OK;
}

NS_IMETHODIMP
csTpMediaStreamInfo::GetPendingSendFlags(PRUint32 *aPendingSendFlags)
{
  *aPendingSendFlags = m_PendingSendFlags;
  return NS_OK;
}

static void
ListStreamsResponse(TpChannel *proxy,
    const GPtrArray *streams,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeStreamedMediaListStreamsCB *callback = (csITpChannelTypeStreamedMediaListStreamsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnListStreamsError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIMutableArray> cStreams = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)streams)->len; i++) {
    gpointer streams_item = g_ptr_array_index((GPtrArray*)streams, i);
    nsCOMPtr<csITpMediaStreamInfo> cStreamsItem;
    csTpMediaStreamInfo::Create((gpointer)streams_item, getter_AddRefs(cStreamsItem));
    cStreams->AppendElement(cStreamsItem, PR_FALSE);
  }

  callback->OnListStreamsDone(cStreams);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::CallListStreams(csITpChannelTypeStreamedMediaListStreamsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_streamed_media_call_list_streams(m_Proxy, -1,
      cb? ListStreamsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RemoveStreamsResponse(TpChannel *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeStreamedMediaRemoveStreamsCB *callback = (csITpChannelTypeStreamedMediaRemoveStreamsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnRemoveStreamsError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnRemoveStreamsDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::CallRemoveStreams(PRUint32 aStreamsCount, PRUint32 *aStreams,
    csITpChannelTypeStreamedMediaRemoveStreamsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cStreams = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aStreamsCount; i++)
    g_array_append_val(cStreams, aStreams[i]);

  NS_IF_ADDREF(cb);
  tp_cli_channel_type_streamed_media_call_remove_streams(m_Proxy, -1,
      cStreams,
      cb? RemoveStreamsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RequestStreamDirectionResponse(TpChannel *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeStreamedMediaRequestStreamDirectionCB *callback = (csITpChannelTypeStreamedMediaRequestStreamDirectionCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnRequestStreamDirectionError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnRequestStreamDirectionDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::CallRequestStreamDirection(PRUint32 aStreamID, PRUint32 aStreamDirection,
    csITpChannelTypeStreamedMediaRequestStreamDirectionCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_streamed_media_call_request_stream_direction(m_Proxy, -1,
      aStreamID, aStreamDirection,
      cb? RequestStreamDirectionResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
RequestStreamsResponse(TpChannel *proxy,
    const GPtrArray *streams,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeStreamedMediaRequestStreamsCB *callback = (csITpChannelTypeStreamedMediaRequestStreamsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnRequestStreamsError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIMutableArray> cStreams = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)streams)->len; i++) {
    gpointer streams_item = g_ptr_array_index((GPtrArray*)streams, i);
    nsCOMPtr<csITpMediaStreamInfo> cStreamsItem;
    csTpMediaStreamInfo::Create((gpointer)streams_item, getter_AddRefs(cStreamsItem));
    cStreams->AppendElement(cStreamsItem, PR_FALSE);
  }

  callback->OnRequestStreamsDone(cStreams);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::CallRequestStreams(PRUint32 aContactHandle, PRUint32 aTypesCount, PRUint32 *aTypes,
    csITpChannelTypeStreamedMediaRequestStreamsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cTypes = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aTypesCount; i++)
    g_array_append_val(cTypes, aTypes[i]);

  NS_IF_ADDREF(cb);
  tp_cli_channel_type_streamed_media_call_request_streams(m_Proxy, -1,
      aContactHandle, cTypes,
      cb? RequestStreamsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
StreamAddedSignalCallback(TpChannel *proxy,
    guint stream_id, guint contact_handle, guint stream_type,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeStreamedMedia *obj = (csTpChannelTypeStreamedMedia *)user_data;
  if (!obj)
    return;

  obj->HandleStreamAdded(stream_id, contact_handle, stream_type);
}


void
csTpChannelTypeStreamedMedia::HandleStreamAdded(guint stream_id, guint contact_handle, guint stream_type)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_StreamAddedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeStreamedMediaStreamAddedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_StreamAddedObservers, i);
    observer->OnStreamAdded(stream_id, contact_handle, stream_type);
  }
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::ConnectToStreamAdded(csITpChannelTypeStreamedMediaStreamAddedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_StreamAddedObservers) {
    m_StreamAddedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_streamed_media_connect_to_stream_added(m_Proxy,
        StreamAddedSignalCallback, this, NULL, NULL, NULL);
  }

  m_StreamAddedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::DisconnectFromStreamAdded(csITpChannelTypeStreamedMediaStreamAddedObserver *observer)
{
  if (!m_StreamAddedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_StreamAddedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_StreamAddedObservers->RemoveElementAt(idx);
}


static void
StreamDirectionChangedSignalCallback(TpChannel *proxy,
    guint stream_id, guint stream_direction, guint pending_flags,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeStreamedMedia *obj = (csTpChannelTypeStreamedMedia *)user_data;
  if (!obj)
    return;

  obj->HandleStreamDirectionChanged(stream_id, stream_direction, pending_flags);
}


void
csTpChannelTypeStreamedMedia::HandleStreamDirectionChanged(guint stream_id, guint stream_direction, guint pending_flags)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_StreamDirectionChangedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeStreamedMediaStreamDirectionChangedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_StreamDirectionChangedObservers, i);
    observer->OnStreamDirectionChanged(stream_id, stream_direction, pending_flags);
  }
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::ConnectToStreamDirectionChanged(csITpChannelTypeStreamedMediaStreamDirectionChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_StreamDirectionChangedObservers) {
    m_StreamDirectionChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_streamed_media_connect_to_stream_direction_changed(m_Proxy,
        StreamDirectionChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_StreamDirectionChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::DisconnectFromStreamDirectionChanged(csITpChannelTypeStreamedMediaStreamDirectionChangedObserver *observer)
{
  if (!m_StreamDirectionChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_StreamDirectionChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_StreamDirectionChangedObservers->RemoveElementAt(idx);
}


static void
StreamErrorSignalCallback(TpChannel *proxy,
    guint stream_id, guint error_code, const gchar *message,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeStreamedMedia *obj = (csTpChannelTypeStreamedMedia *)user_data;
  if (!obj)
    return;

  obj->HandleStreamError(stream_id, error_code, message);
}


void
csTpChannelTypeStreamedMedia::HandleStreamError(guint stream_id, guint error_code, const gchar *message)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_StreamErrorObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeStreamedMediaStreamErrorObserver> observer;

  nsCString cMessage = nsDependentCString(message);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_StreamErrorObservers, i);
    observer->OnStreamError(stream_id, error_code, cMessage);
  }
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::ConnectToStreamError(csITpChannelTypeStreamedMediaStreamErrorObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_StreamErrorObservers) {
    m_StreamErrorObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_streamed_media_connect_to_stream_error(m_Proxy,
        StreamErrorSignalCallback, this, NULL, NULL, NULL);
  }

  m_StreamErrorObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::DisconnectFromStreamError(csITpChannelTypeStreamedMediaStreamErrorObserver *observer)
{
  if (!m_StreamErrorObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_StreamErrorObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_StreamErrorObservers->RemoveElementAt(idx);
}


static void
StreamRemovedSignalCallback(TpChannel *proxy,
    guint stream_id,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeStreamedMedia *obj = (csTpChannelTypeStreamedMedia *)user_data;
  if (!obj)
    return;

  obj->HandleStreamRemoved(stream_id);
}


void
csTpChannelTypeStreamedMedia::HandleStreamRemoved(guint stream_id)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_StreamRemovedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeStreamedMediaStreamRemovedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_StreamRemovedObservers, i);
    observer->OnStreamRemoved(stream_id);
  }
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::ConnectToStreamRemoved(csITpChannelTypeStreamedMediaStreamRemovedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_StreamRemovedObservers) {
    m_StreamRemovedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_streamed_media_connect_to_stream_removed(m_Proxy,
        StreamRemovedSignalCallback, this, NULL, NULL, NULL);
  }

  m_StreamRemovedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::DisconnectFromStreamRemoved(csITpChannelTypeStreamedMediaStreamRemovedObserver *observer)
{
  if (!m_StreamRemovedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_StreamRemovedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_StreamRemovedObservers->RemoveElementAt(idx);
}


static void
StreamStateChangedSignalCallback(TpChannel *proxy,
    guint stream_id, guint stream_state,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeStreamedMedia *obj = (csTpChannelTypeStreamedMedia *)user_data;
  if (!obj)
    return;

  obj->HandleStreamStateChanged(stream_id, stream_state);
}


void
csTpChannelTypeStreamedMedia::HandleStreamStateChanged(guint stream_id, guint stream_state)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_StreamStateChangedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeStreamedMediaStreamStateChangedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_StreamStateChangedObservers, i);
    observer->OnStreamStateChanged(stream_id, stream_state);
  }
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::ConnectToStreamStateChanged(csITpChannelTypeStreamedMediaStreamStateChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_StreamStateChangedObservers) {
    m_StreamStateChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_streamed_media_connect_to_stream_state_changed(m_Proxy,
        StreamStateChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_StreamStateChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::DisconnectFromStreamStateChanged(csITpChannelTypeStreamedMediaStreamStateChangedObserver *observer)
{
  if (!m_StreamStateChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_StreamStateChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_StreamStateChangedObservers->RemoveElementAt(idx);
}


static void
InitialAudioResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeStreamedMediaInitialAudioCB *callback = (csITpChannelTypeStreamedMediaInitialAudioCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyInitialAudioError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gboolean  initialaudio;

  callback->GetPropertyInitialAudioDone(initialaudio);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::GetPropertyInitialAudio(csITpChannelTypeStreamedMediaInitialAudioCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.StreamedMedia",
      "InitialAudio",
      cb? InitialAudioResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
InitialVideoResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeStreamedMediaInitialVideoCB *callback = (csITpChannelTypeStreamedMediaInitialVideoCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyInitialVideoError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gboolean  initialvideo;

  callback->GetPropertyInitialVideoDone(initialvideo);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::GetPropertyInitialVideo(csITpChannelTypeStreamedMediaInitialVideoCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.StreamedMedia",
      "InitialVideo",
      cb? InitialVideoResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ImmutableStreamsResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeStreamedMediaImmutableStreamsCB *callback = (csITpChannelTypeStreamedMediaImmutableStreamsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyImmutableStreamsError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gboolean  immutablestreams;

  callback->GetPropertyImmutableStreamsDone(immutablestreams);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeStreamedMedia::GetPropertyImmutableStreams(csITpChannelTypeStreamedMediaImmutableStreamsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.StreamedMedia",
      "ImmutableStreams",
      cb? ImmutableStreamsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpChannelTypeStreamedMedia::csTpChannelTypeStreamedMedia()
{}

csTpChannelTypeStreamedMedia::~csTpChannelTypeStreamedMedia()
{}
