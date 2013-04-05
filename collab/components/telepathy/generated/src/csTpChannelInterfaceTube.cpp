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


#include "csTpChannelInterfaceTube.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
static void
ParametersResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceTubeParametersCB *callback = (csITpChannelInterfaceTubeParametersCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->GetPropertyParametersError(nsDependentCString(g_quark_to_string(error->domain)),
                                 error->code, nsDependentCString(error->message));
    return;
  }

  GHashTable * parameters;
  parameters = (GHashTable *)g_value_get_boxed(out);
  nsCOMPtr<nsIArray> cParameters;
  csTpStringVariantMap::Create((gpointer)parameters, getter_AddRefs(cParameters));

  callback->GetPropertyParametersDone(cParameters);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceTube::GetPropertyParameters(csITpChannelInterfaceTubeParametersCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Interface.Tube",
      "Parameters",
      cb? ParametersResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
StateResponse(TpProxy *proxy, const GValue *out,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceTubeStateCB *callback = (csITpChannelInterfaceTubeStateCB *)user_data;
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
csTpChannelInterfaceTube::GetPropertyState(csITpChannelInterfaceTubeStateCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_cli_dbus_properties_call_get(m_Proxy, -1,
      "org.freedesktop.Telepathy.Channel.Interface.Tube",
      "State",
      cb? StateResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
TubeChannelStateChangedSignalCallback(TpChannel *proxy,
    guint state,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelInterfaceTube *obj = (csTpChannelInterfaceTube *)user_data;
  if (!obj)
    return;

  obj->HandleTubeChannelStateChanged(state);
}


void
csTpChannelInterfaceTube::HandleTubeChannelStateChanged(guint state)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_TubeChannelStateChangedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelInterfaceTubeTubeChannelStateChangedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_TubeChannelStateChangedObservers, i);
    observer->OnTubeChannelStateChanged(state);
  }
}


NS_IMETHODIMP
csTpChannelInterfaceTube::ConnectToTubeChannelStateChanged(csITpChannelInterfaceTubeTubeChannelStateChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_TubeChannelStateChangedObservers) {
    m_TubeChannelStateChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_interface_tube_connect_to_tube_channel_state_changed(m_Proxy,
        TubeChannelStateChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_TubeChannelStateChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelInterfaceTube::DisconnectFromTubeChannelStateChanged(csITpChannelInterfaceTubeTubeChannelStateChangedObserver *observer)
{
  if (!m_TubeChannelStateChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_TubeChannelStateChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_TubeChannelStateChangedObservers->RemoveElementAt(idx);
}



csTpChannelInterfaceTube::csTpChannelInterfaceTube()
{}

csTpChannelInterfaceTube::~csTpChannelInterfaceTube()
{}
