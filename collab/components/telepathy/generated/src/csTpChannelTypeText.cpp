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


#include "csTpChannelTypeText.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpPendingTextMessage
 */

NS_IMPL_ISUPPORTS1(csTpPendingTextMessage, csITpPendingTextMessage)

NS_METHOD
csTpPendingTextMessage::Create(PRUint32 aIdentifier, PRUint32 aUnixTimestamp, PRUint32 aSender, PRUint32 aMessageType, PRUint32 aFlags, const nsCString &aText, void **aResult)
{
  csITpPendingTextMessage *it = 
          new csTpPendingTextMessage(aIdentifier, aUnixTimestamp, aSender, aMessageType, aFlags, aText);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpPendingTextMessage), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpPendingTextMessage::Create(gpointer aGLibItem, void **aResult)
{
  guint identifier;
  guint unix_timestamp;
  guint sender;
  guint message_type;
  guint flags;
  const gchar *text;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_PENDING_TEXT_MESSAGE);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &identifier, 1, &unix_timestamp, 2, &sender, 3, &message_type, 4, &flags, 5, &text,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cText = nsDependentCString(text);
  csITpPendingTextMessage *it = new csTpPendingTextMessage(identifier, unix_timestamp, sender, message_type, flags, cText);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpPendingTextMessage), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpPendingTextMessage::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpPendingTextMessage::csTpPendingTextMessage(PRUint32 aIdentifier, PRUint32 aUnixTimestamp, PRUint32 aSender, PRUint32 aMessageType, PRUint32 aFlags, const nsCString &aText)
{
  m_Identifier = aIdentifier;
  m_UnixTimestamp = aUnixTimestamp;
  m_Sender = aSender;
  m_MessageType = aMessageType;
  m_Flags = aFlags;
  m_Text.Assign(aText);
}

csTpPendingTextMessage::~csTpPendingTextMessage()
{}

NS_IMETHODIMP
csTpPendingTextMessage::GetIdentifier(PRUint32 *aIdentifier)
{
  *aIdentifier = m_Identifier;
  return NS_OK;
}

NS_IMETHODIMP
csTpPendingTextMessage::GetUnixTimestamp(PRUint32 *aUnixTimestamp)
{
  *aUnixTimestamp = m_UnixTimestamp;
  return NS_OK;
}

NS_IMETHODIMP
csTpPendingTextMessage::GetSender(PRUint32 *aSender)
{
  *aSender = m_Sender;
  return NS_OK;
}

NS_IMETHODIMP
csTpPendingTextMessage::GetMessageType(PRUint32 *aMessageType)
{
  *aMessageType = m_MessageType;
  return NS_OK;
}

NS_IMETHODIMP
csTpPendingTextMessage::GetFlags(PRUint32 *aFlags)
{
  *aFlags = m_Flags;
  return NS_OK;
}

NS_IMETHODIMP
csTpPendingTextMessage::GetText(nsACString &aText)
{
  aText.Assign(m_Text);
  return NS_OK;
}

static void
AcknowledgePendingMessagesResponse(TpChannel *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTextAcknowledgePendingMessagesCB *callback = (csITpChannelTypeTextAcknowledgePendingMessagesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnAcknowledgePendingMessagesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnAcknowledgePendingMessagesDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeText::CallAcknowledgePendingMessages(PRUint32 aIDsCount, PRUint32 *aIDs,
    csITpChannelTypeTextAcknowledgePendingMessagesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cIDs = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aIDsCount; i++)
    g_array_append_val(cIDs, aIDs[i]);

  NS_IF_ADDREF(cb);
  tp_cli_channel_type_text_call_acknowledge_pending_messages(m_Proxy, -1,
      cIDs,
      cb? AcknowledgePendingMessagesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
GetMessageTypesResponse(TpChannel *proxy,
    const GArray *available_types,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTextGetMessageTypesCB *callback = (csITpChannelTypeTextGetMessageTypesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetMessageTypesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  PRUint32 cAvailableTypesCount = available_types->len;
  PRUint32 *cAvailableTypes = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cAvailableTypesCount);
  for (unsigned int i=0; i<cAvailableTypesCount; i++)
    cAvailableTypes[i] = g_array_index(available_types, guint, i);

  callback->OnGetMessageTypesDone(cAvailableTypesCount, cAvailableTypes);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeText::CallGetMessageTypes(csITpChannelTypeTextGetMessageTypesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_text_call_get_message_types(m_Proxy, -1,
      cb? GetMessageTypesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
ListPendingMessagesResponse(TpChannel *proxy,
    const GPtrArray *pending_messages,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTextListPendingMessagesCB *callback = (csITpChannelTypeTextListPendingMessagesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnListPendingMessagesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIMutableArray> cPendingMessages = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)pending_messages)->len; i++) {
    gpointer pending_messages_item = g_ptr_array_index((GPtrArray*)pending_messages, i);
    nsCOMPtr<csITpPendingTextMessage> cPendingMessagesItem;
    csTpPendingTextMessage::Create((gpointer)pending_messages_item, getter_AddRefs(cPendingMessagesItem));
    cPendingMessages->AppendElement(cPendingMessagesItem, PR_FALSE);
  }

  callback->OnListPendingMessagesDone(cPendingMessages);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeText::CallListPendingMessages(PRBool aClear,
    csITpChannelTypeTextListPendingMessagesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_type_text_call_list_pending_messages(m_Proxy, -1,
      aClear,
      cb? ListPendingMessagesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
LostMessageSignalCallback(TpChannel *proxy,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeText *obj = (csTpChannelTypeText *)user_data;
  if (!obj)
    return;

  obj->HandleLostMessage();
}


void
csTpChannelTypeText::HandleLostMessage()
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_LostMessageObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeTextLostMessageObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_LostMessageObservers, i);
    observer->OnLostMessage();
  }
}


NS_IMETHODIMP
csTpChannelTypeText::ConnectToLostMessage(csITpChannelTypeTextLostMessageObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_LostMessageObservers) {
    m_LostMessageObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_text_connect_to_lost_message(m_Proxy,
        LostMessageSignalCallback, this, NULL, NULL, NULL);
  }

  m_LostMessageObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeText::DisconnectFromLostMessage(csITpChannelTypeTextLostMessageObserver *observer)
{
  if (!m_LostMessageObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_LostMessageObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_LostMessageObservers->RemoveElementAt(idx);
}


static void
ReceivedSignalCallback(TpChannel *proxy,
    guint id, guint timestamp, guint sender, guint type, guint flags, const gchar *text,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeText *obj = (csTpChannelTypeText *)user_data;
  if (!obj)
    return;

  obj->HandleReceived(id, timestamp, sender, type, flags, text);
}


void
csTpChannelTypeText::HandleReceived(guint id, guint timestamp, guint sender, guint type, guint flags, const gchar *text)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_ReceivedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeTextReceivedObserver> observer;

  nsCString cText = nsDependentCString(text);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_ReceivedObservers, i);
    observer->OnReceived(id, timestamp, sender, type, flags, cText);
  }
}


NS_IMETHODIMP
csTpChannelTypeText::ConnectToReceived(csITpChannelTypeTextReceivedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_ReceivedObservers) {
    m_ReceivedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_text_connect_to_received(m_Proxy,
        ReceivedSignalCallback, this, NULL, NULL, NULL);
  }

  m_ReceivedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeText::DisconnectFromReceived(csITpChannelTypeTextReceivedObserver *observer)
{
  if (!m_ReceivedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_ReceivedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_ReceivedObservers->RemoveElementAt(idx);
}


static void
SendResponse(TpChannel *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelTypeTextSendCB *callback = (csITpChannelTypeTextSendCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnSendError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnSendDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelTypeText::CallSend(PRUint32 aType, const nsACString &aText,
    csITpChannelTypeTextSendCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  char *cText = ToNewCString(aText);

  NS_IF_ADDREF(cb);
  tp_cli_channel_type_text_call_send(m_Proxy, -1,
      aType, cText,
      cb? SendResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
SendErrorSignalCallback(TpChannel *proxy,
    guint error, guint timestamp, guint type, const gchar *text,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeText *obj = (csTpChannelTypeText *)user_data;
  if (!obj)
    return;

  obj->HandleSendError(error, timestamp, type, text);
}


void
csTpChannelTypeText::HandleSendError(guint error, guint timestamp, guint type, const gchar *text)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_SendErrorObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeTextSendErrorObserver> observer;

  nsCString cText = nsDependentCString(text);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_SendErrorObservers, i);
    observer->OnSendError(error, timestamp, type, cText);
  }
}


NS_IMETHODIMP
csTpChannelTypeText::ConnectToSendError(csITpChannelTypeTextSendErrorObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_SendErrorObservers) {
    m_SendErrorObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_text_connect_to_send_error(m_Proxy,
        SendErrorSignalCallback, this, NULL, NULL, NULL);
  }

  m_SendErrorObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeText::DisconnectFromSendError(csITpChannelTypeTextSendErrorObserver *observer)
{
  if (!m_SendErrorObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_SendErrorObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_SendErrorObservers->RemoveElementAt(idx);
}


static void
SentSignalCallback(TpChannel *proxy,
    guint timestamp, guint type, const gchar *text,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelTypeText *obj = (csTpChannelTypeText *)user_data;
  if (!obj)
    return;

  obj->HandleSent(timestamp, type, text);
}


void
csTpChannelTypeText::HandleSent(guint timestamp, guint type, const gchar *text)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_SentObservers->GetLength(&length);
  nsCOMPtr<csITpChannelTypeTextSentObserver> observer;

  nsCString cText = nsDependentCString(text);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_SentObservers, i);
    observer->OnSent(timestamp, type, cText);
  }
}


NS_IMETHODIMP
csTpChannelTypeText::ConnectToSent(csITpChannelTypeTextSentObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_SentObservers) {
    m_SentObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_type_text_connect_to_sent(m_Proxy,
        SentSignalCallback, this, NULL, NULL, NULL);
  }

  m_SentObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelTypeText::DisconnectFromSent(csITpChannelTypeTextSentObserver *observer)
{
  if (!m_SentObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_SentObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_SentObservers->RemoveElementAt(idx);
}



csTpChannelTypeText::csTpChannelTypeText()
{}

csTpChannelTypeText::~csTpChannelTypeText()
{}
