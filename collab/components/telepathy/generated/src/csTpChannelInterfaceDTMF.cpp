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


#include "csTpChannelInterfaceDTMF.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
static void
StartToneResponse(TpChannel *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceDTMFStartToneCB *callback = (csITpChannelInterfaceDTMFStartToneCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnStartToneError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnStartToneDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceDTMF::CallStartTone(PRUint32 aStreamID, PRUint8 aEvent,
    csITpChannelInterfaceDTMFStartToneCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_dtmf_call_start_tone(m_Proxy, -1,
      aStreamID, aEvent,
      cb? StartToneResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
StopToneResponse(TpChannel *proxy,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfaceDTMFStopToneCB *callback = (csITpChannelInterfaceDTMFStopToneCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnStopToneError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnStopToneDone();
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfaceDTMF::CallStopTone(PRUint32 aStreamID,
    csITpChannelInterfaceDTMFStopToneCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_dtmf_call_stop_tone(m_Proxy, -1,
      aStreamID,
      cb? StopToneResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpChannelInterfaceDTMF::csTpChannelInterfaceDTMF()
{}

csTpChannelInterfaceDTMF::~csTpChannelInterfaceDTMF()
{}
