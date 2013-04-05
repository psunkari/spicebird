/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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
 * Synovel Software Technologies
 * Portions created by the Initial Developer are Copyright (C) 2008, 2009
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

#include "csTelepathyService.h"
#include "nsComponentManagerUtils.h"
#include "nsIMutableArray.h"
#include "nsStringGlue.h"
#include "csTpConnectionManagerImp.h"
#include "csTpConnectionImp.h"
#include "csTelepathyCID.h"

#include <telepathy-glib/connection-manager.h>
#include <telepathy-glib/connection.h>
#include <telepathy-glib/debug.h>

NS_IMPL_ISUPPORTS1(csTelepathyService, csITelepathyService)

// Deliberately included after NS_IMPL_ISUPPORTS
#include "csTelepathyMacros.h"

csTelepathyService::csTelepathyService()
{
#ifndef CS_SYSTEM_TELEPATHY_STACK
  g_setenv("DBUS_SESSION_BUS_ADDRESS", "autolaunch:", TRUE);
#endif

  m_BusDaemon = tp_dbus_daemon_new(tp_get_bus());

  /* 
   * Uncomment the line below if you are ready
   * to have hundreds of debug messages on the console
   */
  // tp_debug_set_all_flags();
}

csTelepathyService::~csTelepathyService()
{
}

static void
GetManagerListResponse(TpConnectionManager * const *cms, gsize n_cms, 
                        const GError *error, gpointer user_data, GObject *unused)
{
  csITpGetManagerListCB *callback = (csITpGetManagerListCB *)user_data;

  if (error) {
    callback->OnGetManagerListError(nsDependentCString(g_quark_to_string(error->domain)),
                                    error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (gsize i = 0; i < n_cms; i++)
  {
    nsresult rv;
    TpConnectionManager *cm = cms[i];

    nsCOMPtr<csITpConnectionManagerUtils> mgr = do_CreateInstance(CS_TPCONNECTIONMANAGER_CONTRACTID, &rv);
    if (NS_FAILED(rv)) {
      callback->OnGetManagerListError(NS_LITERAL_CSTRING("xpcom"), rv, nsCString());
      return;
    }

    mgr->Init(nsDependentCString(cm->name));
    array->AppendElement(mgr, PR_FALSE);
  }

  callback->OnGetManagerListDone(array);
  NS_IF_RELEASE(callback);
}

NS_IMETHODIMP csTelepathyService::GetManagerList(csITpGetManagerListCB *cb)
{
  if (!m_BusDaemon)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_list_connection_managers(m_BusDaemon, GetManagerListResponse, cb, NULL, NULL);
  return NS_OK;
}

static void
GetConnectionListResponse(const gchar * const *bus_names, gsize n,
                          const gchar * const *cms, const gchar * const *protocols,
                          const GError *error, gpointer user_data, GObject *unused)
{
  csITpGetConnectionListCB *callback = (csITpGetConnectionListCB *)user_data;

  if (error) {
    callback->OnGetConnectionListError(nsDependentCString(g_quark_to_string(error->domain)),
                                       error->code, nsDependentCString(error->message));
    return;
  }

  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);
  for (gsize i = 0; i < n; i++)
  {
    nsresult rv;
    const char *bus_name = bus_names[i];

    nsCOMPtr<csITpConnectionUtils> conn = do_CreateInstance(CS_TPCONNECTION_CONTRACTID, &rv);
    if (NS_FAILED(rv)) {
      callback->OnGetConnectionListError(NS_LITERAL_CSTRING("xpcom"), rv, nsCString());
      return;
    }

    conn->Init(nsDependentCString(bus_name), nsCString());
    array->AppendElement(conn, PR_FALSE);
  }

  callback->OnGetConnectionListDone(array);
  NS_IF_RELEASE(callback);
}

NS_IMETHODIMP csTelepathyService::GetConnectionList(csITpGetConnectionListCB *cb)
{
  if (!m_BusDaemon)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_list_connection_names(m_BusDaemon, GetConnectionListResponse, cb, NULL, NULL);
  return NS_OK;
}
