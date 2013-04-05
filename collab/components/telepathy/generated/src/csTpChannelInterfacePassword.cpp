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


#include "csTpChannelInterfacePassword.h"
#include "nsComponentManagerUtils.h"
#include "nsMemory.h"
#include "telepathy-glib/util.h"
#include "telepathy-glib/enums.h"
#include "telepathy-glib/gtypes.h"
#include "csTelepathyUtils.h"
#include "csTpGenericTypes.h"
static void
GetPasswordFlagsResponse(TpChannel *proxy,
    guint password_flags,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfacePasswordGetPasswordFlagsCB *callback = (csITpChannelInterfacePasswordGetPasswordFlagsCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnGetPasswordFlagsError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnGetPasswordFlagsDone(password_flags);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfacePassword::CallGetPasswordFlags(csITpChannelInterfacePasswordGetPasswordFlagsCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;


  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_password_call_get_password_flags(m_Proxy, -1,
      cb? GetPasswordFlagsResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}


static void
PasswordFlagsChangedSignalCallback(TpChannel *proxy,
    guint added, guint removed,
    gpointer user_data, GObject *weak_object)
{
  csTpChannelInterfacePassword *obj = (csTpChannelInterfacePassword *)user_data;
  if (!obj)
    return;

  obj->HandlePasswordFlagsChanged(added, removed);
}


void
csTpChannelInterfacePassword::HandlePasswordFlagsChanged(guint added, guint removed)
{
  if (!m_Proxy)
    return;

  PRUint32 length;
  m_PasswordFlagsChangedObservers->GetLength(&length);
  nsCOMPtr<csITpChannelInterfacePasswordPasswordFlagsChangedObserver> observer;


  for (PRUint32 i=0; i<length; i++) {
    observer = do_QueryElementAt(m_PasswordFlagsChangedObservers, i);
    observer->OnPasswordFlagsChanged(added, removed);
  }
}


NS_IMETHODIMP
csTpChannelInterfacePassword::ConnectToPasswordFlagsChanged(csITpChannelInterfacePasswordPasswordFlagsChangedObserver *observer)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_ENSURE_ARG_POINTER(observer);

  if (!m_PasswordFlagsChangedObservers) {
    m_PasswordFlagsChangedObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);
    tp_cli_channel_interface_password_connect_to_password_flags_changed(m_Proxy,
        PasswordFlagsChangedSignalCallback, this, NULL, NULL, NULL);
  }

  m_PasswordFlagsChangedObservers->AppendElement(observer, PR_FALSE);
  return NS_OK;
}


NS_IMETHODIMP
csTpChannelInterfacePassword::DisconnectFromPasswordFlagsChanged(csITpChannelInterfacePasswordPasswordFlagsChangedObserver *observer)
{
  if (!m_PasswordFlagsChangedObservers)
    return NS_ERROR_NOT_INITIALIZED;

  PRUint32 idx;
  nsresult rv = m_PasswordFlagsChangedObservers->IndexOf(0, observer, &idx);
  if(NS_FAILED(rv))
    return rv;

  return m_PasswordFlagsChangedObservers->RemoveElementAt(idx);
}


static void
ProvidePasswordResponse(TpChannel *proxy,
    gboolean correct,
    const GError *error, gpointer user_data, GObject *weak_object)
{
  csITpChannelInterfacePasswordProvidePasswordCB *callback = (csITpChannelInterfacePasswordProvidePasswordCB *)user_data;
  if (!callback)
    return;

  if (error != NULL) {
    callback->OnProvidePasswordError(nsDependentCString(g_quark_to_string(error->domain)),
                        error->code, nsDependentCString(error->message));
    return;
  }


  callback->OnProvidePasswordDone(correct);
  NS_IF_RELEASE(callback);
}


NS_IMETHODIMP
csTpChannelInterfacePassword::CallProvidePassword(const nsACString &aPassword,
    csITpChannelInterfacePasswordProvidePasswordCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  char *cPassword = ToNewCString(aPassword);

  NS_IF_ADDREF(cb);
  tp_cli_channel_interface_password_call_provide_password(m_Proxy, -1,
      cPassword,
      cb? ProvidePasswordResponse: NULL, cb? cb: NULL, NULL, NULL);

  return NS_OK;
}



csTpChannelInterfacePassword::csTpChannelInterfacePassword()
{}

csTpChannelInterfacePassword::~csTpChannelInterfacePassword()
{}
