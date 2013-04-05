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
#   Ashok Gudibandla <ashok@synovel.com>
# Portions created by the Initial Developer are Copyright (C) 2007-2008
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#
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

const EVENT_DETECTOR_CID = "@synovel.com/collab/calendar/event-filter;1";

var gEventFilter = Components.classes[EVENT_DETECTOR_CID].createInstance(); 
gEventFilter = gEventFilter.QueryInterface(Components.interfaces.csIEventFilter);

function quickAdd() {
   var text = document.getElementById("cal-quickadd-text").value;
   if (text == "" ) return false;

   var events = gEventFilter.extractEvents(text, null, {});
   var event = events[0];
   event.title = event.getProperty("X-TITLE-MATCH");
   if (!event || !event.title || event.title == "") {
      alert('No event created. Insufficient information.');
      return false;
   }

   if (!event.endDate) {
     event.endDate = event.startDate.clone();
     event.endDate.hour += 1;
   }

   var calendar = window.opener.getSelectedCalendar();
   event.calendar = calendar;
   
   var calOpListener = {
      onOperationComplete : function (aCalendar, aStatus, aOperationType, aId, aDetail ) {
         if (aStatus != 0 )
            alert("Error adding event to '" + calendar.name + "' calendar :" + aDetail );
      },
      onGetResult: function ( aCalendar, aStatus, aItemType, aDetail, aCount, aItems ) {
      }
   };

   calendar.addItem(event, calOpListener );
   
   return true;
}
