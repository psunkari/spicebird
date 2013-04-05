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


#include "csTpChannelInterfaceMessages.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
static void
SupportedContentTypesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceMessagesSupportedContentTypesCB *callback = (csITpChannelInterfaceMessagesSupportedContentTypesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertySupportedContentTypesError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  gchar ** supportedcontenttypes;
  supportedcontenttypes = (gchar **)g_value_get_boxed(out);
  PRUint32 cSupportedContentTypesCount = 0;
  for (char **pos = (char**)supportedcontenttypes; *pos; pos++, cSupportedContentTypesCount++);
  char **cSupportedContentTypes = (char **)nsMemory::Alloc(cSupportedContentTypesCount * sizeof(char*));
  for (PRUint32 i=0; i<cSupportedContentTypesCount; i++)
    cSupportedContentTypes[i] = (char *)nsMemory::Clone(supportedcontenttypes[i], strlen(supportedcontenttypes[i]) + 1);

  callback->GetPropertySupportedContentTypesDone(cSupportedContentTypesCount, (const char **)cSupportedContentTypes);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceMessages::GetPropertySupportedContentTypes(csITpChannelInterfaceMessagesSupportedContentTypesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Interface.Messages",
      "SupportedContentTypes",
      cb? SupportedContentTypesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
MessagePartSupportFlagsResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceMessagesMessagePartSupportFlagsCB *callback = (csITpChannelInterfaceMessagesMessagePartSupportFlagsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyMessagePartSupportFlagsError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  messagepartsupportflags;

  callback->GetPropertyMessagePartSupportFlagsDone(messagepartsupportflags);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceMessages::GetPropertyMessagePartSupportFlags(csITpChannelInterfaceMessagesMessagePartSupportFlagsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Interface.Messages",
      "MessagePartSupportFlags",
      cb? MessagePartSupportFlagsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


/*
 *  Implementation of csTpMessagePart
 */

NS_IMPL_ISUPPORTS1(csTpMessagePart, csITpMessagePart)

NS_METHOD
csTpMessagePart::Create(const nsCString &aKey, nsIVariant *aValue, void **aResult)
{
  csITpMessagePart *it = 
          new csTpMessagePart(aKey, aValue);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpMessagePart), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpMessagePart::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    const gchar *key = (gchar *)keyPtr;
    const GValue *value = (GValue *)valuePtr;

    nsCString cKey = nsDependentCString(key);
    nsCOMPtr<nsIVariant> cValue;
    GValueToVariant(value, getter_AddRefs(cValue));

    csITpMessagePart *temp = new csTpMessagePart(cKey, cValue);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpMessagePart> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpMessagePart::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpMessagePart::csTpMessagePart(const nsCString &aKey, nsIVariant *aValue)
{
  m_Key.Assign(aKey);
  m_Value = aValue;
}

csTpMessagePart::~csTpMessagePart()
{}

NS_IMETHODIMP
csTpMessagePart::GetKey(nsACString &aKey)
{
  aKey.Assign(m_Key);
  return NS_OK;
}

NS_IMETHODIMP
csTpMessagePart::GetValue(nsIVariant **aValue)
{
  NS_IF_ADDREF(*aValue = m_Value);
  return NS_OK;
}

/*
 *  Implementation of csTpMessagePartContentMap
 */

NS_IMPL_ISUPPORTS1(csTpMessagePartContentMap, csITpMessagePartContentMap)

NS_METHOD
csTpMessagePartContentMap::Create(PRUint32 aPart, nsIVariant *aContent, void **aResult)
{
  csITpMessagePartContentMap *it = 
          new csTpMessagePartContentMap(aPart, aContent);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpMessagePartContentMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpMessagePartContentMap::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    guint part = GPOINTER_TO_UINT(keyPtr);
    const GValue *content = (GValue *)valuePtr;

    nsCOMPtr<nsIVariant> cContent;
    GValueToVariant(content, getter_AddRefs(cContent));

    csITpMessagePartContentMap *temp = new csTpMessagePartContentMap(part, cContent);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpMessagePartContentMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpMessagePartContentMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpMessagePartContentMap::csTpMessagePartContentMap(PRUint32 aPart, nsIVariant *aContent)
{
  m_Part = aPart;
  m_Content = aContent;
}

csTpMessagePartContentMap::~csTpMessagePartContentMap()
{}

NS_IMETHODIMP
csTpMessagePartContentMap::GetPart(PRUint32 *aPart)
{
  *aPart = m_Part;
  return NS_OK;
}

NS_IMETHODIMP
csTpMessagePartContentMap::GetContent(nsIVariant **aContent)
{
  NS_IF_ADDREF(*aContent = m_Content);
  return NS_OK;
}

static void
SendMessageResponse(TpChannel *proxy,
    const gchar *token,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceMessagesSendMessageCB *callback = (csITpChannelInterfaceMessagesSendMessageCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnSendMessageError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCString cToken = nsDependentCString(token);

  callback->OnSendMessageDone(cToken);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceMessages::CallSendMessage(nsIArray *aMessage, PRUint32 aFlags,
    csITpChannelInterfaceMessagesSendMessageCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  /* TODO */

  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_messages_call_send_message(m_Proxy, -1,
      NULL, aFlags,
      cb? SendMessageResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
MessageSentSignalCallback(TpChannel *proxy,
    const GPtrArray *content, guint flags, const gchar *message_token,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelInterfaceMessages *obj = (csTpChannelInterfaceMessages *)user_data;
  if (!obj)
    return;

  obj->HandleMessageSent(content, flags, message_token);
}


void
csTpChannelInterfaceMessages::HandleMessageSent(const GPtrArray *content, guint flags, const gchar *message_token)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_MessageSentObservers->GetLength(&length);
  nsCOMPtr<csITpChannelInterfaceMessagesMessageSentObserver> observer;

  nsCOMPtr<nsIMutableArray> cContent = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)content)->len; i++) {
    gpointer content_item = g_ptr_array_index((GPtrArray*)content, i);
    nsCOMPtr<nsIArray> cContentItem;
    csTpMessagePart::Create((gpointer)content_item, getter_AddRefs(cContentItem));
    cContent->AppendElement(cContentItem, PR_FALSE);
  }
  nsCString cMessageToken = nsDependentCString(message_token);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_MessageSentObservers, i);
    observer->OnMessageSent(cContent, flags, cMessageToken);
  }
}


NS_IMETHODIMP
csTpChannelInterfaceMessages::ConnectToMessageSent(csITpChannelInterfaceMessagesMessageSentObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_MessageSentObservers) {
    m_MessageSentObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_interface_messages_connect_to_message_sent(m_Proxy,
        MessageSentSignalCallback, this, NULL, NULL, NULL);
  }

  m_MessageSentObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelInterfaceMessages::DisconnectFromMessageSent(csITpChannelInterfaceMessagesMessageSentObserver *observer)
{
  if (!m_MessageSentObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_MessageSentObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_MessageSentObservers->RemoveElementAt(idx);
}


static void
PendingMessagesResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceMessagesPendingMessagesCB *callback = (csITpChannelInterfaceMessagesPendingMessagesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyPendingMessagesError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GPtrArray * pendingmessages;
  pendingmessages = (GPtrArray *)g_value_get_boxed(out);
  nsCOMPtr<nsIMutableArray> cPendingMessages = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)pendingmessages)->len; i++) {
    gpointer pendingmessages_item = g_ptr_array_index((GPtrArray*)pendingmessages, i);
    nsCOMPtr<nsIMutableArray> cPendingMessagesItem = do_CreateInstance(NS_ARRAY_CONTRACTID);
    for (PRUint32 i=0; i<((GPtrArray*)pendingmessages_item)->len; i++) {
      gpointer pendingmessages_item_item = g_ptr_array_index((GPtrArray*)pendingmessages_item, i);
      nsCOMPtr<nsIArray> cPendingMessagesItemItem;
      csTpMessagePart::Create((gpointer)pendingmessages_item_item, getter_AddRefs(cPendingMessagesItemItem));
      cPendingMessagesItem->AppendElement(cPendingMessagesItemItem, PR_FALSE);
    }
    cPendingMessages->AppendElement(cPendingMessagesItem, PR_FALSE);
  }

  callback->GetPropertyPendingMessagesDone(cPendingMessages);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceMessages::GetPropertyPendingMessages(csITpChannelInterfaceMessagesPendingMessagesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Interface.Messages",
      "PendingMessages",
      cb? PendingMessagesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
PendingMessagesRemovedSignalCallback(TpChannel *proxy,
    const GArray *message_ids,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelInterfaceMessages *obj = (csTpChannelInterfaceMessages *)user_data;
  if (!obj)
    return;

  obj->HandlePendingMessagesRemoved(message_ids);
}


void
csTpChannelInterfaceMessages::HandlePendingMessagesRemoved(const GArray *message_ids)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_PendingMessagesRemovedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelInterfaceMessagesPendingMessagesRemovedObserver> observer;

  PRUint32 cMessageIDsCount = message_ids->len;
  PRUint32 *cMessageIDs = (PRUint32 *)nsMemory::Alloc(sizeof(PRUint32)*cMessageIDsCount);
  for (unsigned int i=0; i<cMessageIDsCount; i++)
    cMessageIDs[i] = g_array_index(message_ids, guint, i);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_PendingMessagesRemovedObservers, i);
    observer->OnPendingMessagesRemoved(cMessageIDsCount, cMessageIDs);
  }
}


NS_IMETHODIMP
csTpChannelInterfaceMessages::ConnectToPendingMessagesRemoved(csITpChannelInterfaceMessagesPendingMessagesRemovedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_PendingMessagesRemovedObservers) {
    m_PendingMessagesRemovedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_interface_messages_connect_to_pending_messages_removed(m_Proxy,
        PendingMessagesRemovedSignalCallback, this, NULL, NULL, NULL);
  }

  m_PendingMessagesRemovedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelInterfaceMessages::DisconnectFromPendingMessagesRemoved(csITpChannelInterfaceMessagesPendingMessagesRemovedObserver *observer)
{
  if (!m_PendingMessagesRemovedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_PendingMessagesRemovedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_PendingMessagesRemovedObservers->RemoveElementAt(idx);
}


static void
GetPendingMessageContentResponse(TpChannel *proxy,
    GHashTable *content,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceMessagesGetPendingMessageContentCB *callback = (csITpChannelInterfaceMessagesGetPendingMessageContentCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetPendingMessageContentError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIArray> cContent;
  csTpMessagePartContentMap::Create((gpointer)content, getter_AddRefs(cContent));

  callback->OnGetPendingMessageContentDone(cContent);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceMessages::CallGetPendingMessageContent(PRUint32 aMessageID, PRUint32 aPartsCount, PRUint32 *aParts,
    csITpChannelInterfaceMessagesGetPendingMessageContentCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  GArray *cParts = g_array_new(false, false, sizeof(guint ));
  for (PRUint32 i=0; i<aPartsCount; i++)
    g_array_append_val(cParts, aParts[i]);

  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_messages_call_get_pending_message_content(m_Proxy, -1,
      aMessageID, cParts,
      cb? GetPendingMessageContentResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
MessageReceivedSignalCallback(TpChannel *proxy,
    const GPtrArray *message,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelInterfaceMessages *obj = (csTpChannelInterfaceMessages *)user_data;
  if (!obj)
    return;

  obj->HandleMessageReceived(message);
}


void
csTpChannelInterfaceMessages::HandleMessageReceived(const GPtrArray *message)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_MessageReceivedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelInterfaceMessagesMessageReceivedObserver> observer;

  nsCOMPtr<nsIMutableArray> cMessage = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)message)->len; i++) {
    gpointer message_item = g_ptr_array_index((GPtrArray*)message, i);
    nsCOMPtr<nsIArray> cMessageItem;
    csTpMessagePart::Create((gpointer)message_item, getter_AddRefs(cMessageItem));
    cMessage->AppendElement(cMessageItem, PR_FALSE);
  }

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_MessageReceivedObservers, i);
    observer->OnMessageReceived(cMessage);
  }
}


NS_IMETHODIMP
csTpChannelInterfaceMessages::ConnectToMessageReceived(csITpChannelInterfaceMessagesMessageReceivedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_MessageReceivedObservers) {
    m_MessageReceivedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_interface_messages_connect_to_message_received(m_Proxy,
        MessageReceivedSignalCallback, this, NULL, NULL, NULL);
  }

  m_MessageReceivedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelInterfaceMessages::DisconnectFromMessageReceived(csITpChannelInterfaceMessagesMessageReceivedObserver *observer)
{
  if (!m_MessageReceivedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_MessageReceivedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_MessageReceivedObservers->RemoveElementAt(idx);
}


static void
DeliveryReportingSupportResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceMessagesDeliveryReportingSupportCB *callback = (csITpChannelInterfaceMessagesDeliveryReportingSupportCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyDeliveryReportingSupportError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  guint  deliveryreportingsupport;

  callback->GetPropertyDeliveryReportingSupportDone(deliveryreportingsupport);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceMessages::GetPropertyDeliveryReportingSupport(csITpChannelInterfaceMessagesDeliveryReportingSupportCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Interface.Messages",
      "DeliveryReportingSupport",
      cb? DeliveryReportingSupportResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpChannelInterfaceMessages::csTpChannelInterfaceMessages()
{}

csTpChannelInterfaceMessages::~csTpChannelInterfaceMessages()
{}
