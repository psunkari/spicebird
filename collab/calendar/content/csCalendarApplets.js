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
#   Prasad Sunkari <prasad@synovel.com>
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
*/

var gAgendaCompositeCalendar = null;
function getAgendaCompositeCalendar() 
{
  if (!gAgendaCompositeCalendar) {
    gAgendaCompositeCalendar =
      Components.classes["@mozilla.org/calendar/calendar;1?type=composite"]
      .createInstance(Components.interfaces.calICompositeCalendar);

    gAgendaCompositeCalendar.prefPrefix = 'calendar-agenda';

    var cals = getCalendarManager().getCalendars({});
    for each (var cal in cals) 
      gAgendaCompositeCalendar.addCalendar(cal);

    getCalendarManager().addObserver(gAgendaCompositeObserver);
  }
  return gAgendaCompositeCalendar;
}

var gAgendaCompositeObserver = {
  QueryInterface: function (aIID) 
  {
    if (!aIID.equals(Components.interfaces.calICalendarManagerObserver) &&
        !aIID.equals(Components.interfaces.nsISupports)) {
      throw Components.results.NS_ERROR_NO_INTERFACE;
    }
 
    return this;
  },

  onCalendarRegistered: function (aCalendar) 
  {
    getAgendaCompositeCalendar().addCalendar(aCalendar);
  },

  onCalendarUnregistering: function (aCalendar) 
  {
    getAgendaCompositeCalendar().removeCalendar(aCalendar.uri);
  },

  onCalendarDeleting: function (aCalendar) 
  {
    getAgendaCompositeCalendar().removeCalendar(aCalendar.uri);
  },

  onCalendarPrefSet: function (aCalendar, aName, aValue)
  { },

  onCalendarPrefDeleting: function (aCalendar, aName)
  { }
}
