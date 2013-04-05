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


#ifndef __CS_TELEPATHY_HEADER_GENERICTYPES__
#define __CS_TELEPATHY_HEADER_GENERICTYPES__

#include "nsISupports.h"
#include "csITpGenericTypes.h"
#include "glib.h"
#include "nsStringGlue.h"
#include "nsIVariant.h"
#include "nsCOMPtr.h"
#include "nsIMutableArray.h"
#include "nsArrayUtils.h"


class csTpQualifiedPropertyValueMap: public csITpQualifiedPropertyValueMap
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPQUALIFIEDPROPERTYVALUEMAP

  csTpQualifiedPropertyValueMap(const nsCString &aKey, nsIVariant *aValue);
  static NS_METHOD Create(const nsCString &aKey, nsIVariant *aValue, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, nsIArray **array);
  static NS_METHOD ToGLib(nsIArray *aObj, gpointer *_retval);

private:
  ~csTpQualifiedPropertyValueMap();

protected:
  nsCString m_Key;
  nsCOMPtr<nsIVariant> m_Value;
};

class csTpStringVariantMap: public csITpStringVariantMap
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPSTRINGVARIANTMAP

  csTpStringVariantMap(const nsCString &aKey, nsIVariant *aValue);
  static NS_METHOD Create(const nsCString &aKey, nsIVariant *aValue, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, nsIArray **array);
  static NS_METHOD ToGLib(nsIArray *aObj, gpointer *_retval);

private:
  ~csTpStringVariantMap();

protected:
  nsCString m_Key;
  nsCOMPtr<nsIVariant> m_Value;
};

class csTpStringStringMap: public csITpStringStringMap
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPSTRINGSTRINGMAP

  csTpStringStringMap(const nsCString &aKey, const nsCString &aValue);
  static NS_METHOD Create(const nsCString &aKey, const nsCString &aValue, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, nsIArray **array);
  static NS_METHOD ToGLib(nsIArray *aObj, gpointer *_retval);

private:
  ~csTpStringStringMap();

protected:
  nsCString m_Key;
  nsCString m_Value;
};

class csTpSocketAddressIP: public csITpSocketAddressIP
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPSOCKETADDRESSIP

  csTpSocketAddressIP(const nsCString &aAddress, PRUint16 aPort);
  static NS_METHOD Create(const nsCString &aAddress, PRUint16 aPort, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpSocketAddressIP();

protected:
  nsCString m_Address;
  PRUint16 m_Port;
};

class csTpSocketAddressIPv4: public csITpSocketAddressIPv4
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPSOCKETADDRESSIPV4

  csTpSocketAddressIPv4(const nsCString &aAddress, PRUint16 aPort);
  static NS_METHOD Create(const nsCString &aAddress, PRUint16 aPort, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpSocketAddressIPv4();

protected:
  nsCString m_Address;
  PRUint16 m_Port;
};

class csTpSocketAddressIPv6: public csITpSocketAddressIPv6
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPSOCKETADDRESSIPV6

  csTpSocketAddressIPv6(const nsCString &aAddress, PRUint16 aPort);
  static NS_METHOD Create(const nsCString &aAddress, PRUint16 aPort, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpSocketAddressIPv6();

protected:
  nsCString m_Address;
  PRUint16 m_Port;
};

class csTpSocketNetmaskIPv4: public csITpSocketNetmaskIPv4
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPSOCKETNETMASKIPV4

  csTpSocketNetmaskIPv4(const nsCString &aAddress, PRUint8 aPrefixLength);
  static NS_METHOD Create(const nsCString &aAddress, PRUint8 aPrefixLength, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpSocketNetmaskIPv4();

protected:
  nsCString m_Address;
  PRUint8 m_PrefixLength;
};

class csTpSocketNetmaskIPv6: public csITpSocketNetmaskIPv6
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPSOCKETNETMASKIPV6

  csTpSocketNetmaskIPv6(const nsCString &aAddress, PRUint8 aPrefixLength);
  static NS_METHOD Create(const nsCString &aAddress, PRUint8 aPrefixLength, void **aResult);
  static NS_METHOD Create(gpointer aGLibItem, void **aResult);

private:
  ~csTpSocketNetmaskIPv6();

protected:
  nsCString m_Address;
  PRUint8 m_PrefixLength;
};



#endif