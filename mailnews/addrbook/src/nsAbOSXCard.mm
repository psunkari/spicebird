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
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Peter Van der Beken.
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Peter Van der Beken <peterv@propagandism.org>
 *
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

#include "nsAbOSXCard.h"
#include "nsAbOSXDirectory.h"
#include "nsAbOSXUtils.h"
#include "nsAutoPtr.h"
#include "nsIAbManager.h"
#include "nsServiceManagerUtils.h"

#include <AddressBook/AddressBook.h>
#if (MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_3)    
#define kABPersonFlags nil
#define kABShowAsCompany (0)
#define kABNameOrderingMask (0)
#define kABDefaultNameOrdering (-1)
#define kABFirstNameFirst (-1)
#define kABOtherDatesProperty nil
#define kABAnniversaryLabel nil
#endif

NS_IMPL_ISUPPORTS_INHERITED2(nsAbOSXCard,
                             nsRDFResource,
                             nsIAbCard,
                             nsIAbOSXCard)

#ifdef DEBUG
static ABPropertyType
GetPropertType(ABRecord *aCard, NSString *aProperty)
{
  ABPropertyType propertyType = kABErrorInProperty;
  if ([aCard isKindOfClass:[ABPerson class]])
    propertyType = [ABPerson typeOfProperty:aProperty];
  else if ([aCard isKindOfClass:[ABGroup class]])
    propertyType = [ABGroup typeOfProperty:aProperty];
  return propertyType;
}
#endif

static void
SetStringProperty(nsAbOSXCard *aCard, const nsString &aValue,
                  const char *aMemberName, PRBool aNotify,
                  nsIAbManager *aAbManager)
{
  nsString oldValue;
  nsresult rv = aCard->GetPropertyAsAString(aMemberName, oldValue);
  if (NS_FAILED(rv))
    oldValue.Truncate();

  if (!aNotify) {
    aCard->SetPropertyAsAString(aMemberName, aValue);
  }
  else if (!oldValue.Equals(aValue)) {
    aCard->SetPropertyAsAString(aMemberName, aValue);
    
    nsISupports *supports = NS_ISUPPORTS_CAST(nsRDFResource*, aCard);
    aAbManager->NotifyItemPropertyChanged(supports, aMemberName,
                                          oldValue.get(), aValue.get());
  }
}

static void
SetStringProperty(nsAbOSXCard *aCard, NSString *aValue, const char *aMemberName,
                  PRBool aNotify, nsIAbManager *aAbManager)
{
  nsAutoString value;
  if (aValue)
    AppendToString(aValue, value);

  SetStringProperty(aCard, value, aMemberName, aNotify, aAbManager);
}

static void
MapStringProperty(nsAbOSXCard *aCard, ABRecord *aOSXCard, NSString *aProperty,
                  const char *aMemberName, PRBool aNotify,
                  nsIAbManager *aAbManager)
{
  NS_ASSERTION(aProperty, "This is bad! You asked for an unresolved symbol.");
  NS_ASSERTION(GetPropertType(aOSXCard, aProperty) == kABStringProperty,
               "Wrong type!");
  
  SetStringProperty(aCard, [aOSXCard valueForProperty:aProperty], aMemberName,
                    aNotify, aAbManager);
}

static ABMutableMultiValue*
GetMultiValue(ABRecord *aCard, NSString *aProperty)
{
  NS_ASSERTION(aProperty, "This is bad! You asked for an unresolved symbol.");
  NS_ASSERTION(GetPropertType(aCard, aProperty) & kABMultiValueMask,
               "Wrong type!");
  
  return [aCard valueForProperty:aProperty];
}

static void
MapDate(nsAbOSXCard *aCard, NSDate *aDate, const char *aYearPropName,
        const char *aMonthPropName, const char *aDayPropName, PRBool aNotify,
        nsIAbManager *aAbManager)
{
  // XXX Should we pass a format and timezone?
  NSCalendarDate *date = [aDate dateWithCalendarFormat:nil timeZone:nil];
  
  nsAutoString value;
  value.AppendInt([date yearOfCommonEra]);
  SetStringProperty(aCard, value, aYearPropName, aNotify, aAbManager);
  value.Truncate();
  value.AppendInt([date monthOfYear]);
  SetStringProperty(aCard, value, aMonthPropName, aNotify, aAbManager);
  value.Truncate();
  value.AppendInt([date dayOfMonth]);
  SetStringProperty(aCard, value, aDayPropName, aNotify, aAbManager);
}

static PRBool
MapMultiValue(nsAbOSXCard *aCard, ABRecord *aOSXCard,
              const nsAbOSXPropertyMap &aMap, PRBool aNotify,
              nsIAbManager *aAbManager)
{
  ABMultiValue *value = GetMultiValue(aOSXCard, aMap.mOSXProperty);
  if (value) {
    unsigned int j;
    unsigned int count = [value count];
    for (j = 0; j < count; ++j) {
      if ([[value labelAtIndex:j] isEqualToString:aMap.mOSXLabel]) {
        NSString *stringValue = (aMap.mOSXKey)
          ? [[value valueAtIndex:j] objectForKey:aMap.mOSXKey]
          : [value valueAtIndex:j];
        
        SetStringProperty(aCard, stringValue, aMap.mPropertyName, aNotify,
                          aAbManager);
        
        return PR_TRUE;
      }
    }
  }
  // String wasn't found, set value of card to empty if it was set previously
  SetStringProperty(aCard, EmptyString(), aMap.mPropertyName, aNotify,
                    aAbManager);
  
  return PR_FALSE;
}

NS_IMETHODIMP
nsAbOSXCard::Init(const char *aUri)
{
  if (strncmp(aUri, NS_ABOSXCARD_URI_PREFIX,
              sizeof(NS_ABOSXCARD_URI_PREFIX) - 1) != 0)
    return NS_ERROR_FAILURE;
  
  nsresult rv = nsRDFResource::Init(aUri);
  NS_ENSURE_SUCCESS(rv, rv);
  
  return Update(PR_FALSE);
}

nsresult
nsAbOSXCard::Update(PRBool aNotify)
{
  ABAddressBook *addressBook = [ABAddressBook sharedAddressBook];

  const char *uid = &((mURI.get())[16]);
  ABRecord *card = [addressBook recordForUniqueId:[NSString stringWithUTF8String:uid]];
  NS_ENSURE_TRUE(card, NS_ERROR_FAILURE);

  nsCOMPtr<nsIAbManager> abManager;
  nsresult rv;
  if (aNotify) {
    abManager = do_GetService(NS_ABMANAGER_CONTRACTID, &rv);
    NS_ENSURE_SUCCESS(rv, rv);
  }

  if ([card isKindOfClass:[ABGroup class]]) {
    m_IsMailList = PR_TRUE;
    m_MailListURI.AssignLiteral(NS_ABOSXDIRECTORY_URI_PREFIX);
    m_MailListURI.Append(uid);
    MapStringProperty(this, card, kABGroupNameProperty, "DisplayName", aNotify,
                      abManager);
    MapStringProperty(this, card, kABGroupNameProperty, "LastName", aNotify,
                      abManager);

    return NS_OK;
  }
  
  PRBool foundHome = PR_FALSE, foundWork = PR_FALSE;
  
  PRUint32 i;
  for (i = 0; i < nsAbOSXUtils::kPropertyMapSize; ++i) {
    const nsAbOSXPropertyMap &propertyMap = nsAbOSXUtils::kPropertyMap[i];
    if (!propertyMap.mOSXProperty)
      continue;
    
    if (propertyMap.mOSXLabel) {
      if (MapMultiValue(this, card, propertyMap, aNotify,
                        abManager) && propertyMap.mOSXProperty == kABAddressProperty) {
        if (propertyMap.mOSXLabel == kABAddressHomeLabel) 
          foundHome = PR_TRUE;
        else
          foundWork = PR_TRUE;
      }
    }
    else {
      MapStringProperty(this, card, propertyMap.mOSXProperty,
                        propertyMap.mPropertyName, aNotify, abManager);
    }
  }
  
  int flags = 0;
  if (kABPersonFlags)
    flags = [[card valueForProperty:kABPersonFlags] intValue];
  
#define SET_STRING(_value, _name, _notify, _session) \
  SetStringProperty(this, _value, #_name, _notify, _session)
    
    // If kABShowAsCompany is set we use the company name as display name.
    if (kABPersonFlags && (flags & kABShowAsCompany)) {
      nsString company;
      nsresult rv = GetPropertyAsAString(kCompanyProperty, company);
      if (NS_FAILED(rv))
        company.Truncate();
      SET_STRING(company, DisplayName, aNotify, abManager);
    }
  else {
    // Use the order used in the OS X address book to set DisplayName.
    int order = kABPersonFlags && (flags & kABNameOrderingMask);
    if (kABPersonFlags && (order == kABDefaultNameOrdering)) {
      order = [addressBook defaultNameOrdering];
    }
    
    nsAutoString displayName, tempName;
    if (kABPersonFlags && (order == kABFirstNameFirst)) {
      GetFirstName(tempName);
      displayName.Append(tempName);

      GetLastName(tempName);

      // Only append a space if the last name and the first name are not empty
      if (!tempName.IsEmpty() && !displayName.IsEmpty())
        displayName.Append(' ');

      displayName.Append(tempName);
    }
    else {
      GetLastName(tempName);
      displayName.Append(tempName);

      GetFirstName(tempName);

      // Only append a space if the last name and the first name are not empty
      if (!tempName.IsEmpty() && !displayName.IsEmpty())
        displayName.Append(' ');

      displayName.Append(tempName);
    }
    SET_STRING(displayName, DisplayName, aNotify, abManager);
  }
  
  ABMultiValue *value = GetMultiValue(card, kABEmailProperty);
  if (value) {
    unsigned int count = [value count];
    if (count > 0) {
      unsigned int j = [value indexForIdentifier:[value primaryIdentifier]];
      
      if (j < count)
        SET_STRING([value valueAtIndex:j], PrimaryEmail, aNotify,
                   abManager);
      
      // If j is 0 (first in the list) we want the second in the list
      // (index 1), if j is anything else we want the first in the list
      // (index 0).
      j = (j == 0);
      if (j < count)
        SET_STRING([value valueAtIndex:j], SecondEmail, aNotify,
                   abManager);
    }
  }
  
  // We map the first home address we can find and the first work address
  // we can find. If we find none, we map the primary address to the home
  // address.
  if (!foundHome && !foundWork) {
    value = GetMultiValue(card, kABAddressProperty);
    if (value) {
      unsigned int count = [value count];
      unsigned int j = [value indexForIdentifier:[value primaryIdentifier]];
      
      if (j < count) {
        NSDictionary *address = [value valueAtIndex:j];
        if (address) {
          SET_STRING([address objectForKey:kABAddressStreetKey],
                     HomeAddress, aNotify, abManager);
          SET_STRING([address objectForKey:kABAddressCityKey],
                     HomeCity, aNotify, abManager);
          SET_STRING([address objectForKey:kABAddressStateKey],
                     HomeState, aNotify, abManager);
          SET_STRING([address objectForKey:kABAddressZIPKey],
                     HomeZipCode, aNotify, abManager);
          SET_STRING([address objectForKey:kABAddressCountryKey],
                     HomeCountry, aNotify, abManager);
        }
      }
    }
  }
  
  value = GetMultiValue(card, kABAIMInstantProperty);
  if (value) {
    unsigned int count = [value count];
    if (count > 0) {
      unsigned int j = [value indexForIdentifier:[value primaryIdentifier]];
      
      if (j < count)
        SET_STRING([value valueAtIndex:j], AimScreenName, aNotify,
                   abManager);
    }
  }
  
#define MAP_DATE(_date, _name, _notify, _session) \
  MapDate(this, _date, #_name"Year", #_name"Month", #_name"Day", _notify, \
  _session)
    
    NSDate *date = [card valueForProperty:kABBirthdayProperty];
  if (date)
    MAP_DATE(date, Birth, aNotify, abManager);
  
  if (kABOtherDatesProperty) {
    value = GetMultiValue(card, kABOtherDatesProperty);
    if (value) {
      unsigned int j, count = [value count];
      for (j = 0; j < count; ++j) {
        if ([[value labelAtIndex:j] isEqualToString:kABAnniversaryLabel]) {
          date = [value valueAtIndex:j];
          if (date) {
            MAP_DATE(date, Anniversary, aNotify, abManager);
            
            break;
          }
        }
      }
    }
  }
#undef MAP_DATE
#undef SET_STRING
  
  date = [card valueForProperty:kABModificationDateProperty];
  if (date) 
    SetPropertyAsUint32("LastModifiedDate",
                        PRUint32([date timeIntervalSince1970]));
    // XXX No way to notify about this?
  
  return NS_OK;
}
