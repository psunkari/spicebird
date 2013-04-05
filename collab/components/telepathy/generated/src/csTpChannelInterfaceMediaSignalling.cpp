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


#include "csTpChannelInterfaceMediaSignalling.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
/*
 *  Implementation of csTpMediaSessionHandlerInfo
 */

NS_IMPL_ISUPPORTS1(csTpMediaSessionHandlerInfo, csITpMediaSessionHandlerInfo)

NS_METHOD
csTpMediaSessionHandlerInfo::Create(const nsCString &aSessionHandler, const nsCString &aMediaSessionType, void **aResult)
{
  csITpMediaSessionHandlerInfo *it = 
          new csTpMediaSessionHandlerInfo(aSessionHandler, aMediaSessionType);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpMediaSessionHandlerInfo), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpMediaSessionHandlerInfo::Create(gpointer aGLibItem, void **aResult)
{
  const gchar *session_handler;
  const gchar *media_session_type;

  GValue structure = { 0 };
  g_value_init(&structure, TP_STRUCT_TYPE_MEDIA_SESSION_HANDLER_INFO);
  g_value_set_static_boxed(&structure, aGLibItem);

  if (!dbus_g_type_struct_get(&structure,
           0, &session_handler, 1, &media_session_type,
           G_MAXUINT))
    return NS_ERROR_FAILURE;

  nsCString cSessionHandler = nsDependentCString(session_handler);
  nsCString cMediaSessionType = nsDependentCString(media_session_type);
  csITpMediaSessionHandlerInfo *it = new csTpMediaSessionHandlerInfo(cSessionHandler, cMediaSessionType);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpMediaSessionHandlerInfo), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_IMETHODIMP
csTpMediaSessionHandlerInfo::ToGLib(gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpMediaSessionHandlerInfo::csTpMediaSessionHandlerInfo(const nsCString &aSessionHandler, const nsCString &aMediaSessionType)
{
  m_SessionHandler.Assign(aSessionHandler);
  m_MediaSessionType.Assign(aMediaSessionType);
}

csTpMediaSessionHandlerInfo::~csTpMediaSessionHandlerInfo()
{}

NS_IMETHODIMP
csTpMediaSessionHandlerInfo::GetSessionHandler(nsACString &aSessionHandler)
{
  aSessionHandler.Assign(m_SessionHandler);
  return NS_OK;
}

NS_IMETHODIMP
csTpMediaSessionHandlerInfo::GetMediaSessionType(nsACString &aMediaSessionType)
{
  aMediaSessionType.Assign(m_MediaSessionType);
  return NS_OK;
}

static void
GetSessionHandlersResponse(TpChannel *proxy,
    const GPtrArray *session_handlers,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceMediaSignallingGetSessionHandlersCB *callback = (csITpChannelInterfaceMediaSignallingGetSessionHandlersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetSessionHandlersError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIMutableArray> cSessionHandlers = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (PRUint32 i=0; i<((GPtrArray*)session_handlers)->len; i++) {
    gpointer session_handlers_item = g_ptr_array_index((GPtrArray*)session_handlers, i);
    nsCOMPtr<csITpMediaSessionHandlerInfo> cSessionHandlersItem;
    csTpMediaSessionHandlerInfo::Create((gpointer)session_handlers_item, getter_AddRefs(cSessionHandlersItem));
    cSessionHandlers->AppendElement(cSessionHandlersItem, PR_FALSE);
  }

  callback->OnGetSessionHandlersDone(cSessionHandlers);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceMediaSignalling::CallGetSessionHandlers(csITpChannelInterfaceMediaSignallingGetSessionHandlersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_media_signalling_call_get_session_handlers(m_Proxy, -1,
      cb? GetSessionHandlersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
NewSessionHandlerSignalCallback(TpChannel *proxy,
    const gchar *session_handler, const gchar *session_type,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelInterfaceMediaSignalling *obj = (csTpChannelInterfaceMediaSignalling *)user_data;
  if (!obj)
    return;

  obj->HandleNewSessionHandler(session_handler, session_type);
}


void
csTpChannelInterfaceMediaSignalling::HandleNewSessionHandler(const gchar *session_handler, const gchar *session_type)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_NewSessionHandlerObservers->GetLength(&length);
  nsCOMPtr<csITpChannelInterfaceMediaSignallingNewSessionHandlerObserver> observer;

  nsCString cSessionHandler = nsDependentCString(session_handler);
  nsCString cSessionType = nsDependentCString(session_type);

  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_NewSessionHandlerObservers, i);
    observer->OnNewSessionHandler(cSessionHandler, cSessionType);
  }
}


NS_IMETHODIMP
csTpChannelInterfaceMediaSignalling::ConnectToNewSessionHandler(csITpChannelInterfaceMediaSignallingNewSessionHandlerObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_NewSessionHandlerObservers) {
    m_NewSessionHandlerObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_interface_media_signalling_connect_to_new_session_handler(m_Proxy,
        NewSessionHandlerSignalCallback, this, NULL, NULL, NULL);
  }

  m_NewSessionHandlerObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelInterfaceMediaSignalling::DisconnectFromNewSessionHandler(csITpChannelInterfaceMediaSignallingNewSessionHandlerObserver *observer)
{
  if (!m_NewSessionHandlerObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_NewSessionHandlerObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_NewSessionHandlerObservers->RemoveElementAt(idx);
}



csTpChannelInterfaceMediaSignalling::csTpChannelInterfaceMediaSignalling()
{}

csTpChannelInterfaceMediaSignalling::~csTpChannelInterfaceMediaSignalling()
{}
