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


#ifndef __CS_TELEPATHY_HEADER_CONNECTION__
#define __CS_TELEPATHY_HEADER_CONNECTION__

#include "nsISupports.h"
#include "csITpConnection.h"
#include "glib.h"
#include "nsStringGlue.h"
#include "nsIArray.h"
#include "nsCOMPtr.h"
#include "nsIMutableArray.h"
#include "nsArrayUtils.h"
#include "csTpBaseProxies.h"
#include "telepathy-glib/connection.h"


class csTpChannelInfo: public csITpChannelInfo
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPCHANNELINFO

  csTpChannelInfo(const nsCString &aChannel, const nsCString &aChannelType, PRUint32 aHandleType, PRUint32 aHandle);
  static NS_METHOD Create(const nsCString &aChannel, const nsCString &aChannelType, PRUint32 aHandleType, PRUint32 aHandle, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpChannelInfo();

protected:
  nsCString m_Channel;
  nsCString m_ChannelType;
  PRUint32 m_HandleType;
  PRUint32 m_Handle;
};



class csTpConnection: public csITpConnection, public virtual _csTpConnectionProxyBase
{
public:
  NS_DECL_CSITPCONNECTION

  csTpConnection();

  void HandleSelfHandleChanged(guint self_handle);
  void HandleNewChannel(const gchar *object_path, const gchar *channel_type, guint handle_type, guint handle, gboolean suppress_handler);
  void HandleConnectionError(const gchar *error, GHashTable *details);
  void HandleStatusChanged(guint status, guint reason);

protected:
  nsCOMPtr<nsIMutableArray> m_SelfHandleChangedObservers;
  nsCOMPtr<nsIMutableArray> m_NewChannelObservers;
  nsCOMPtr<nsIMutableArray> m_ConnectionErrorObservers;
  nsCOMPtr<nsIMutableArray> m_StatusChangedObservers;

  ~csTpConnection();

private:

};
#endif