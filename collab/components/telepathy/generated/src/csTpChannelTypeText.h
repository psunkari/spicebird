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


#ifndef __CS_TELEPATHY_HEADER_CHANNELTYPETEXT__
#define __CS_TELEPATHY_HEADER_CHANNELTYPETEXT__

#include "nsISupports.h"
#include "csITpChannelTypeText.h"
#include "glib.h"
#include "nsStringGlue.h"
#include "nsIArray.h"
#include "nsCOMPtr.h"
#include "nsIMutableArray.h"
#include "nsArrayUtils.h"
#include "csTpBaseProxies.h"
#include "telepathy-glib/channel.h"


class csTpPendingTextMessage: public csITpPendingTextMessage
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPPENDINGTEXTMESSAGE

  csTpPendingTextMessage(PRUint32 aIdentifier, PRUint32 aUnixTimestamp, PRUint32 aSender, PRUint32 aMessageType, PRUint32 aFlags, const nsCString &aText);
  static NS_METHOD Create(PRUint32 aIdentifier, PRUint32 aUnixTimestamp, PRUint32 aSender, PRUint32 aMessageType, PRUint32 aFlags, const nsCString &aText, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpPendingTextMessage();

protected:
  PRUint32 m_Identifier;
  PRUint32 m_UnixTimestamp;
  PRUint32 m_Sender;
  PRUint32 m_MessageType;
  PRUint32 m_Flags;
  nsCString m_Text;
};



class csTpChannelTypeText: public csITpChannelTypeText, public virtual _csTpChannelProxyBase
{
public:
  NS_DECL_CSITPCHANNELTYPETEXT

  csTpChannelTypeText();

  void HandleLostMessage();
  void HandleReceived(guint id, guint timestamp, guint sender, guint type, guint flags, const gchar *text);
  void HandleSendError(guint error, guint timestamp, guint type, const gchar *text);
  void HandleSent(guint timestamp, guint type, const gchar *text);

protected:
  nsCOMPtr<nsIMutableArray> m_LostMessageObservers;
  nsCOMPtr<nsIMutableArray> m_ReceivedObservers;
  nsCOMPtr<nsIMutableArray> m_SendErrorObservers;
  nsCOMPtr<nsIMutableArray> m_SentObservers;

  ~csTpChannelTypeText();

private:

};
#endif