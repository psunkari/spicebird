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


#include "csTpChannelInterfaceCallState.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
static void
GetCallStatesResponse(TpChannel *proxy,
    GHashTable *states,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceCallStateGetCallStatesCB *callback = (csITpChannelInterfaceCallStateGetCallStatesCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetCallStatesError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIArray> cStates;
  csTpChannelCallStateMap::Create((gpointer)states, getter_AddRefs(cStates));

  callback->OnGetCallStatesDone(cStates);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceCallState::CallGetCallStates(csITpChannelInterfaceCallStateGetCallStatesCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_call_state_call_get_call_states(m_Proxy, -1,
      cb? GetCallStatesResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
CallStateChangedSignalCallback(TpChannel *proxy,
    guint contact, guint state,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelInterfaceCallState *obj = (csTpChannelInterfaceCallState *)user_data;
  if (!obj)
    return;

  obj->HandleCallStateChanged(contact, state);
}


void
csTpChannelInterfaceCallState::HandleCallStateChanged(guint contact, guint state)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_CallStateChangedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelInterfaceCallStateCallStateChangedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_CallStateChangedObservers, i);
    observer->OnCallStateChanged(contact, state);
  }
}


NS_IMETHODIMP
csTpChannelInterfaceCallState::ConnectToCallStateChanged(csITpChannelInterfaceCallStateCallStateChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_CallStateChangedObservers) {
    m_CallStateChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_interface_call_state_connect_to_call_state_changed(m_Proxy,
        CallStateChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_CallStateChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelInterfaceCallState::DisconnectFromCallStateChanged(csITpChannelInterfaceCallStateCallStateChangedObserver *observer)
{
  if (!m_CallStateChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_CallStateChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_CallStateChangedObservers->RemoveElementAt(idx);
}


/*
 *  Implementation of csTpChannelCallStateMap
 */

NS_IMPL_ISUPPORTS1(csTpChannelCallStateMap, csITpChannelCallStateMap)

NS_METHOD
csTpChannelCallStateMap::Create(PRUint32 aContact, PRUint32 aState, void **aResult)
{
  csITpChannelCallStateMap *it = 
          new csTpChannelCallStateMap(aContact, aState);
  if (!it)
    return NS_ERROR_OUT_OF_MEMORY;

  NS_ADDREF(it);
  nsresult rv = it->QueryInterface(NS_GET_IID(csITpChannelCallStateMap), aResult);
  NS_RELEASE(it);

  return rv;
}

NS_METHOD
csTpChannelCallStateMap::Create(gpointer aGLibItem, nsIArray **aResult)
{
  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  GHashTable *hashTable = (GHashTable*)aGLibItem;
  GHashTableIter iter;
  gpointer keyPtr, valuePtr;

  g_hash_table_iter_init(&iter, hashTable);
  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {
    guint contact = GPOINTER_TO_UINT(keyPtr);
    guint state = GPOINTER_TO_UINT(valuePtr);


    csITpChannelCallStateMap *temp = new csTpChannelCallStateMap(contact, state);
    if (!temp)
      return NS_ERROR_OUT_OF_MEMORY;

    nsCOMPtr<csITpChannelCallStateMap> it = do_QueryInterface(temp);
    array->AppendElement(it, false);
  }

  NS_ADDREF(*aResult = array);
  return NS_OK;
}

NS_METHOD
csTpChannelCallStateMap::ToGLib(nsIArray *aObj, gpointer *_retval)
{
  *_retval = NULL; /* TODO */
  return NS_OK;
}

csTpChannelCallStateMap::csTpChannelCallStateMap(PRUint32 aContact, PRUint32 aState)
{
  m_Contact = aContact;
  m_State = aState;
}

csTpChannelCallStateMap::~csTpChannelCallStateMap()
{}

NS_IMETHODIMP
csTpChannelCallStateMap::GetContact(PRUint32 *aContact)
{
  *aContact = m_Contact;
  return NS_OK;
}

NS_IMETHODIMP
csTpChannelCallStateMap::GetState(PRUint32 *aState)
{
  *aState = m_State;
  return NS_OK;
}


csTpChannelInterfaceCallState::csTpChannelInterfaceCallState()
{}

csTpChannelInterfaceCallState::~csTpChannelInterfaceCallState()
{}
