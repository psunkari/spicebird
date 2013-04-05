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
 * The Original Code is mail folder code.
 *
 * The Initial Developer of the Original Code is
 *   Synovel Software Technologies
 * Portions created by the Initial Developer are Copyright (C) 2010
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

/**
 * This file contains helper methods for dealing with friendly date formats.
 * Similar code also resides in the nsMsgDBView.cpp for use with mail listing.
 *
 * When using friendly formats, the responsibility is on the user of this code
 * to update the UI when date changes.
 */

var EXPORTED_SYMBOLS = ["getFriendlyDateTime"];
var stringBundle = null;

/**
 * Returns a formatted string for a given javascript date
 * @param aDate the javascript date that should be formatted
 * @param aIncludeTime indicates that time should always be included
 */
function getFriendlyDateTime(aDate, aIncludeTime) {
  if (!stringBundle) {
    stringBundle = Components.classes["@mozilla.org/intl/stringbundle;1"]
                             .getService(Components.interfaces.nsIStringBundleService)
                             .createBundle("chrome://collab/locale/csDateFormatter.properties");
    if (!stringBundle)
      return 
  }

  let withTime = aIncludeTime? "WithTime": "";

  let today = new Date();
  today = new Date(today.getFullYear(), today.getMonth(), today.getDate());

  // Today
  if (aDate.getDate() == today.getDate() &&
      aDate.getMonth() == today.getMonth() &&
      aDate.getFullYear() == today.getFullYear())
    return aDate.toLocaleFormat(stringBundle.GetStringFromName("collab.dateFormat.today"));

  // Not today, is it from the future!
  if (aDate.getTime() > Date.now()) {

    // Tomorrow
    if ((aDate.getTime() - today.getTime()) / 1000 < 172800)
      return aDate.toLocaleFormat(stringBundle.GetStringFromName("collab.dateFormat.tomorrow"));

    return aDate.toLocaleFormat(stringBundle.GetStringFromName("collab.dateFormat.other" + withTime));
  }

  // Yesterday
  if ((today.getTime() - aDate.getTime()) / 1000 < 86400)
    return aDate.toLocaleFormat(stringBundle.GetStringFromName("collab.dateFormat.yesterday"));

  // This Week
  if ((today.getTime() - aDate.getTime()) / 1000 < today.getDay() * 86400)
    return aDate.toLocaleFormat(stringBundle.GetStringFromName("collab.dateFormat.thisWeek" + withTime));

  // This Year
  if (aDate.getFullYear() == today.getFullYear())
    return aDate.toLocaleFormat(stringBundle.GetStringFromName("collab.dateFormat.thisYear" + withTime));

  return aDate.toLocaleFormat(stringBundle.GetStringFromName("collab.dateFormat.other" + withTime));
}
