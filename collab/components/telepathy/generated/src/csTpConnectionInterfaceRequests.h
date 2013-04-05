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


#ifndef __CS_TELEPATHY_HEADER_CONNECTIONINTERFACEREQUESTS__
#define __CS_TELEPATHY_HEADER_CONNECTIONINTERFACEREQUESTS__

#include "nsISupports.h"
#include "csITpConnectionInterfaceRequests.h"
#include "glib.h"
#include "nsStringGlue.h"
#include "nsIArray.h"
#include "nsIVariant.h"
#include "nsCOMPtr.h"
#include "nsIMutableArray.h"
#include "nsArrayUtils.h"
#include "csTpBaseProxies.h"
#include "telepathy-glib/connection.h"


class csTpChannelDetails: public csITpChannelDetails
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPCHANNELDETAILS

  csTpChannelDetails(const nsCString &aChannel, nsIArray *aProperties);
  static NS_METHOD Create(const nsCString &aChannel, nsIArray *aProperties, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpChannelDetails();

protected:
  nsCString m_Channel;
  nsCOMPtr<nsIArray> m_Properties;
};

class csTpChannelClass: public csITpChannelClass
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPCHANNELCLASS

  csTpChannelClass(const nsCString &aKey, nsIVariant *aValue);
  static NS_METHOD Create(const nsCString &aKey, nsIVariant *aValue, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, nsIArray **array);
  static NS_METHOD ToGLib(nsIArray *aObj, gpointer *_retval);

private:
  ~csTpChannelClass();

protected:
  nsCString m_Key;
  nsCOMPtr<nsIVariant> m_Value;
};

class csTpRequestableChannelClass: public csITpRequestableChannelClass
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPREQUESTABLECHANNELCLASS

  csTpRequestableChannelClass(nsIArray *aFixedProperties, PRUint32 aAllowedPropertiesCount, const char **aAllowedProperties);
  static NS_METHOD Create(nsIArray *aFixedProperties, PRUint32 aAllowedPropertiesCount, const char **aAllowedProperties, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpRequestableChannelClass();

protected:
  nsCOMPtr<nsIArray> m_FixedProperties;
  PRUint32 m_AllowedPropertiesCount; char **m_AllowedProperties;
};



class csTpConnectionInterfaceRequests: public csITpConnectionInterfaceRequests, public virtual _csTpConnectionProxyBase
{
public:
  NS_DECL_CSITPCONNECTIONINTERFACEREQUESTS

  csTpConnectionInterfaceRequests();

  void HandleNewChannels(const GPtrArray *channels);
  void HandleChannelClosed(const gchar *removed);

protected:
  nsCOMPtr<nsIMutableArray> m_NewChannelsObservers;
  nsCOMPtr<nsIMutableArray> m_ChannelClosedObservers;

  ~csTpConnectionInterfaceRequests();

private:

};
#endif