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


#include "csTpChannelTypeFileTransfer.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
#include "csTpChannelTypeTubes.h"
static void
StateResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeFileTransferStateCB *callback = (csITpChannelTypeFileTransferStateCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyStateError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  state;

  callback->GetPropertyStateDone(state);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::GetPropertyState(csITpChannelTypeFileTransferStateCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.FileTransfer",
      "State",
      cb? StateResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ContentTypeResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeFileTransferContentTypeCB *callback = (csITpChannelTypeFileTransferContentTypeCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyContentTypeError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar * contenttype;
  nsCString cContentType = nsDependentCString(contenttype);

  callback->GetPropertyContentTypeDone(cContentType);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::GetPropertyContentType(csITpChannelTypeFileTransferContentTypeCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.FileTransfer",
      "ContentType",
      cb? ContentTypeResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
FilenameResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeFileTransferFilenameCB *callback = (csITpChannelTypeFileTransferFilenameCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyFilenameError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar * filename;
  nsCString cFilename = nsDependentCString(filename);

  callback->GetPropertyFilenameDone(cFilename);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::GetPropertyFilename(csITpChannelTypeFileTransferFilenameCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.FileTransfer",
      "Filename",
      cb? FilenameResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
SizeResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeFileTransferSizeCB *callback = (csITpChannelTypeFileTransferSizeCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertySizeError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint64  size;

  callback->GetPropertySizeDone(size);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::GetPropertySize(csITpChannelTypeFileTransferSizeCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.FileTransfer",
      "Size",
      cb? SizeResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ContentHashTypeResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeFileTransferContentHashTypeCB *callback = (csITpChannelTypeFileTransferContentHashTypeCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyContentHashTypeError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  contenthashtype;

  callback->GetPropertyContentHashTypeDone(contenthashtype);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::GetPropertyContentHashType(csITpChannelTypeFileTransferContentHashTypeCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.FileTransfer",
      "ContentHashType",
      cb? ContentHashTypeResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ContentHashResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeFileTransferContentHashCB *callback = (csITpChannelTypeFileTransferContentHashCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyContentHashError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar * contenthash;
  nsCString cContentHash = nsDependentCString(contenthash);

  callback->GetPropertyContentHashDone(cContentHash);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::GetPropertyContentHash(csITpChannelTypeFileTransferContentHashCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.FileTransfer",
      "ContentHash",
      cb? ContentHashResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
DescriptionResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeFileTransferDescriptionCB *callback = (csITpChannelTypeFileTransferDescriptionCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyDescriptionError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar * description;
  nsCString cDescription = nsDependentCString(description);

  callback->GetPropertyDescriptionDone(cDescription);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::GetPropertyDescription(csITpChannelTypeFileTransferDescriptionCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.FileTransfer",
      "Description",
      cb? DescriptionResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
DateResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeFileTransferDateCB *callback = (csITpChannelTypeFileTransferDateCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyDateError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gint64  date;

  callback->GetPropertyDateDone(date);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::GetPropertyDate(csITpChannelTypeFileTransferDateCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.FileTransfer",
      "Date",
      cb? DateResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
AvailableSocketTypesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeFileTransferAvailableSocketTypesCB *callback = (csITpChannelTypeFileTransferAvailableSocketTypesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyAvailableSocketTypesError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GHashTable * availablesockettypes;
  availablesockettypes = (GHashTable *)g_value_get_boxed(out);
  nsCOMPtr<nsIArray> cAvailableSocketTypes;
  csTpSupportedSocketMap::Create((gpointer)availablesockettypes, getter_AddRefs(cAvailableSocketTypes));

  callback->GetPropertyAvailableSocketTypesDone(cAvailableSocketTypes);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::GetPropertyAvailableSocketTypes(csITpChannelTypeFileTransferAvailableSocketTypesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.FileTransfer",
      "AvailableSocketTypes",
      cb? AvailableSocketTypesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
TransferredBytesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeFileTransferTransferredBytesCB *callback = (csITpChannelTypeFileTransferTransferredBytesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyTransferredBytesError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint64  transferredbytes;

  callback->GetPropertyTransferredBytesDone(transferredbytes);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::GetPropertyTransferredBytes(csITpChannelTypeFileTransferTransferredBytesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.FileTransfer",
      "TransferredBytes",
      cb? TransferredBytesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
InitialOffsetResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeFileTransferInitialOffsetCB *callback = (csITpChannelTypeFileTransferInitialOffsetCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyInitialOffsetError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint64  initialoffset;

  callback->GetPropertyInitialOffsetDone(initialoffset);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::GetPropertyInitialOffset(csITpChannelTypeFileTransferInitialOffsetCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Type.FileTransfer",
      "InitialOffset",
      cb? InitialOffsetResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
AcceptFileResponse(TpChannel *proxy,
    const GValue *address,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeFileTransferAcceptFileCB *callback = (csITpChannelTypeFileTransferAcceptFileCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnAcceptFileError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIVariant> cAddress;
  GValueToVariant(address, getter_AddRefs(cAddress));

  callback->OnAcceptFileDone(cAddress);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::CallAcceptFile(PRUint32 aAddressType, PRUint32 aAccessControl, nsIVariant *aAccessControlParam, PRUint64 aOffset,
    csITpChannelTypeFileTransferAcceptFileCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GValue *cAccessControlParam = VariantToGValue(aAccessControlParam);

  NS_IF_ADDREF(cb);
  tp_cli_channel_type_file_transfer_call_accept_file(m_Proxy, -1,
      aAddressType, aAccessControl, cAccessControlParam, aOffset,
      cb? AcceptFileResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ProvideFileResponse(TpChannel *proxy,
    const GValue *address,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeFileTransferProvideFileCB *callback = (csITpChannelTypeFileTransferProvideFileCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnProvideFileError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIVariant> cAddress;
  GValueToVariant(address, getter_AddRefs(cAddress));

  callback->OnProvideFileDone(cAddress);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::CallProvideFile(PRUint32 aAddressType, PRUint32 aAccessControl, nsIVariant *aAccessControlParam,
    csITpChannelTypeFileTransferProvideFileCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GValue *cAccessControlParam = VariantToGValue(aAccessControlParam);

  NS_IF_ADDREF(cb);
  tp_cli_channel_type_file_transfer_call_provide_file(m_Proxy, -1,
      aAddressType, aAccessControl, cAccessControlParam,
      cb? ProvideFileResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
FileTransferStateChangedSignalCallback(TpChannel *proxy,
    guint state, guint reason,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeFileTransfer *obj = (csTpChannelTypeFileTransfer *)user_data;
  if (!obj)
    return;

  obj->HandleFileTransferStateChanged(state, reason);
}


void
csTpChannelTypeFileTransfer::HandleFileTransferStateChanged(guint state, guint reason)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_FileTransferStateChangedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeFileTransferFileTransferStateChangedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_FileTransferStateChangedObservers, i);
    observer->OnFileTransferStateChanged(state, reason);
  }
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::ConnectToFileTransferStateChanged(csITpChannelTypeFileTransferFileTransferStateChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_FileTransferStateChangedObservers) {
    m_FileTransferStateChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_file_transfer_connect_to_file_transfer_state_changed(m_Proxy,
        FileTransferStateChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_FileTransferStateChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::DisconnectFromFileTransferStateChanged(csITpChannelTypeFileTransferFileTransferStateChangedObserver *observer)
{
  if (!m_FileTransferStateChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_FileTransferStateChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_FileTransferStateChangedObservers->RemoveElementAt(idx);
}


static void
TransferredBytesChangedSignalCallback(TpChannel *proxy,
    guint64 count,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeFileTransfer *obj = (csTpChannelTypeFileTransfer *)user_data;
  if (!obj)
    return;

  obj->HandleTransferredBytesChanged(count);
}


void
csTpChannelTypeFileTransfer::HandleTransferredBytesChanged(guint64 count)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_TransferredBytesChangedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeFileTransferTransferredBytesChangedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_TransferredBytesChangedObservers, i);
    observer->OnTransferredBytesChanged(count);
  }
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::ConnectToTransferredBytesChanged(csITpChannelTypeFileTransferTransferredBytesChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_TransferredBytesChangedObservers) {
    m_TransferredBytesChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_file_transfer_connect_to_transferred_bytes_changed(m_Proxy,
        TransferredBytesChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_TransferredBytesChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::DisconnectFromTransferredBytesChanged(csITpChannelTypeFileTransferTransferredBytesChangedObserver *observer)
{
  if (!m_TransferredBytesChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_TransferredBytesChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_TransferredBytesChangedObservers->RemoveElementAt(idx);
}


static void
InitialOffsetDefinedSignalCallback(TpChannel *proxy,
    guint64 initialoffset,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeFileTransfer *obj = (csTpChannelTypeFileTransfer *)user_data;
  if (!obj)
    return;

  obj->HandleInitialOffsetDefined(initialoffset);
}


void
csTpChannelTypeFileTransfer::HandleInitialOffsetDefined(guint64 initialoffset)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_InitialOffsetDefinedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeFileTransferInitialOffsetDefinedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_InitialOffsetDefinedObservers, i);
    observer->OnInitialOffsetDefined(initialoffset);
  }
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::ConnectToInitialOffsetDefined(csITpChannelTypeFileTransferInitialOffsetDefinedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_InitialOffsetDefinedObservers) {
    m_InitialOffsetDefinedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_file_transfer_connect_to_initial_offset_defined(m_Proxy,
        InitialOffsetDefinedSignalCallback, this, NULL, NULL, NULL);
  }

  m_InitialOffsetDefinedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeFileTransfer::DisconnectFromInitialOffsetDefined(csITpChannelTypeFileTransferInitialOffsetDefinedObserver *observer)
{
  if (!m_InitialOffsetDefinedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_InitialOffsetDefinedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_InitialOffsetDefinedObservers->RemoveElementAt(idx);
}



csTpChannelTypeFileTransfer::csTpChannelTypeFileTransfer()
{}

csTpChannelTypeFileTransfer::~csTpChannelTypeFileTransfer()
{}
