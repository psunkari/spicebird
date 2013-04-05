/*
# ***** BEGIN LICENSE BLOCK *****
# Version: MPL 1.1/GPL 2.0/LGPL 2.1
#
# The contents of this file are subject to the Mozilla Public License Version
# 1.1 (the "License"); you may not use this file except in compliance with
# the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
# for the specific language governing rights and limitations under the
# License.
#
# The Original Code is Spicebird code.
#
# The Initial Developer of the Original Code is
# Synovel Software Technologies
# Portions created by the Initial Developer are Copyright (C) 2007-2008
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Ashok Gudibandla <ashok@synovel.com> (Original Author)
#   Sunil Mohan Adapa <sunil@synovel.com>
#
# Alternatively, the contents of this file may be used under the terms of
# either of the GNU General Public License Version 2 or later (the "GPL"),
# or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
# in which case the provisions of the GPL or the LGPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of either the GPL or the LGPL, and not to allow others to
# use your version of this file under the terms of the MPL, indicate your
# decision by deleting the provisions above and replace them with the notice
# and other provisions required by the GPL or the LGPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the MPL, the GPL or the LGPL.
#
# ***** END LICENSE BLOCK ***** 
*/

var tzComp = Components.classes["@synovel.com/collab/collab/timezones;1"]
	               .getService(Components.interfaces.csITimezones);
var tzStringBundle = null;

function tzDialogCreateListItem(aVal, aChecked) {
   var listItem = document.createElement("richlistitem");
   var selectedCell = document.createElement("richlistcell");
   var nameCell = document.createElement("richlistcell");
   nameCell.setAttribute("flex", "1");

   var label = document.createElement("label");
   label.setAttribute("id", aVal);
   
   var tzName;
   try {
     tzName = tzStringBundle.GetStringFromName("pref.timezone." + 
					       aVal.replace(/\//g, "."));
   } catch (ex) {
     tzName = aVal.replace(/_/g, " ");
   }

   label.setAttribute("value", tzName);
   nameCell.appendChild(label);

   var checkbox = document.createElement("checkbox");
   if (aChecked)
     checkbox.setAttribute("checked", "true");
   selectedCell.appendChild(checkbox);

   listItem.appendChild(selectedCell);
   listItem.appendChild(nameCell);

   return listItem;
}

function tzDialogInit() {
  try {
    tzStringBundle = Components.classes["@mozilla.org/intl/stringbundle;1"]
      .getService(Components.interfaces.nsIStringBundleService)
      .createBundle("chrome://calendar-timezones/locale/timezones.properties");
  } catch (ex) {
  }

  var allIds = tzComp.getAllTimezoneIds({});
  var curIds = tzComp.getDefaultTimezoneIds({});
  var listBox = document.getElementById("tz-listitem");

  for each (id in allIds) {
    var index = curIds.indexOf(id);
    listBox.appendChild(tzDialogCreateListItem(id, index != -1));
  }
}

function tzDialogAccept() {
   var newIds = new Array();
   var listItems = document.getElementsByTagName("richlistitem");
   for  (var i = 0; i < listItems.length; i++) {
      var listItem = listItems[i];
      if (listItem.firstChild.firstChild.checked) {
          newIds.push(listItem.lastChild.firstChild.id);
      }
   }
   tzComp.setDefaultTimezoneIds(newIds.length, newIds);
   return true;
}