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
#   Sivakrishna Edpuganti <sivakrishna@synovel.com> 
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

const EVENT_DETECTOR_CID = "@synovel.com/collab/calendar/event-filter;1";
const uSEC_PER_SEC = 1000 * 1000;

var gEventFilter = {

  // This function runs in the window scope, so use variables accordingly
  init: function(event)
  {
    if (event.originalTarget != window.document)
      return;

    // Find a window where we can safely lookup for calendar stuff!
    // We cannot do that in stand alone message window.
    gEventFilter.window = Components.classes["@mozilla.org/appshell/window-mediator;1"]
                                    .getService(Components.interfaces.nsIWindowMediator)
                                    .getMostRecentWindow("collab:main");
    if (!gEventFilter.window)
      return;
  
    this.window.removeEventListener("load", gEventFilter.init, true);
    this.window.addEventListener("unload", gEventFilter.uninit, true);
  
    gEventFilter.filter = Components.classes[EVENT_DETECTOR_CID].createInstance()
                                    .QueryInterface(Components.interfaces.csIEventFilter);

    var observerService = Components.classes["@mozilla.org/observer-service;1"]
                                    .getService(Components.interfaces.nsIObserverService);

    observerService.addObserver(gEventFilter, "MsgMsgDisplayed", false);
    observerService.addObserver(gEventFilter, "MsgClearNotifications", false);
  },
  
  observe: function (aSubject, aTopic, aData) {
    if (aTopic == "MsgMsgDisplayed")
      this.messageDisplayed(aSubject, aTopic, aData);
    else if (aTopic == "MsgClearNotifications")
      this.clearNotifications(aSubject, aTopic, aData);
  },

  clearNotifications: function(aSubject, aTopic, aData) {
    if (aSubject != window.document)
      return;
    
    var bar = document.getElementById("eventsFilterBar");
    bar.setAttribute("collapsed", "true");
  },

  messageDisplayed: function(aHeaderSink, aTopic, aUri) {
    var message = gMessageDisplay.displayedMessage;
    if (!message)
      return;

    // This observer is invoked across windows and when message window is
    // open, loading a new message in message window or the main window 
    // invokes this observer in the other window as well.
    if (message.folder.getUriForMsg(message) != aUri)
      return;

    var bar = document.getElementById("eventsFilterBar");
    bar.setAttribute("collapsed", "true");

    if (this.ignoreEventsSet())
      return;

    if (this.filter) {
      this.filter.contextDate = message.dateInSeconds * uSEC_PER_SEC;
  
      // remove all quoted text from the html 
      var bodyText = this.getFilterText(document.getElementById("messagepane").contentDocument.body);
      var msgText = message.subject + ". " + bodyText
  
      this.events = this.filter.extractEvents(msgText, aUri, {});
      if(!this.events || this.events.length <= 0) 
        return;

      var nTitledEvents = 0;
      for (var i=0; i < this.events.length; i++)
        if (this.events[i].getProperty("X-TITLE-MATCH"))
          nTitledEvents++;
  
      if (!nTitledEvents)
        return;
  
      var text = document.getElementById("eventsFilterDescText");
      var hbox = document.getElementById("eventsFilterListHBox");
      var bundle = document.getElementById("bundle_eventfilter");
      while (hbox.childNodes.length > 0) 
        hbox.removeChild(hbox.childNodes[0]);
  
      if (nTitledEvents == 1)
        text.setAttribute("value", bundle.getString("singleEventLabel"));
      else
        text.setAttribute("value", bundle.getString("multipleEventsLabel"));
  
      for (var i=0; i < this.events.length; i++) {
        // Don't consider the events that dont have an event name for the
        // purpose of adding them in the events header
        if (!this.events[i].getProperty("X-TITLE-MATCH"))
          continue;
        // Set the calendar as the selected calendar.
        this.events[i].calendar = this.window.getSelectedCalendar();
  
        var label = document.createElementNS("http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul","label");
        label.setAttribute("value", this.getEventString(this.events[i]));
        label.setAttribute("class", "text-link");
        label.setAttribute("onclick", "gEventFilter.addDetectedEvent(gEventFilter.events[" + i + "])");
        hbox.appendChild(label);
      }
        
      bar.removeAttribute("collapsed");
    }
  },

  getFilterText: function(aNode) {
    var text = '';
    if (!aNode)
      return text;

    // Get rid of style data and blockquote tags with type='cite' attribute
    tagName = aNode.tagName;
    if (tagName)
      if (tagName.toUpperCase() == "STYLE" ||
         (tagName.toUpperCase() == "BLOCKQUOTE" &&
         ("" + aNode.getAttribute("TYPE")).toUpperCase() == "CITE"))
        return "";

    for each (var node in aNode.childNodes) 
       text += this.getFilterText(node);

    if (aNode.nodeName == "#text") 
       text += aNode.textContent;
  
    return text;
  },

  getEventString: function(aEvent) {
    // XXX: localize the way strings are concatenated
    var eventString = "";
    var titleMatch = aEvent.getProperty("X-TITLE-MATCH");
    if (titleMatch)
      eventString = titleMatch + ": ";
  
    var dateMatchedText = aEvent.getProperty("X-DATE-MATCH");
    var timeMatchedText = aEvent.getProperty("X-TIME-MATCH");
  
    /* The only situation when this will needed is when date is not given
       if this assumption is wrong, uncomment this.
    if (!dateMatchedText && (timeMatchedText || aEvent.startDate.isDate)) {
      var dateTime = new Date (aEvent.startDate.year, aEvent.startDate.month,
                               aEvent.startDate.day);
      dateMatchedText = dateTime.toLocaleDateString ();
    }
    */
  
    /* The only situation when this will needed is when time is not given
       if this assumption is wrong, uncomment this.
    if (!aEvent.startDate.isDate && !timeMatchedText && dateMatchedText) {
      var dateTime = new Date (aEvent.startDate.year, aEvent.startDate.month,
                               aEvent.startDate.day, aEvent.startDate.hour,
                               aEvent.startDate.minute, aEvent.startDate.second);
      timeMatchedText = dateTime.toLocaleTimeString ();
    }
    */
  
    if (dateMatchedText) {
      eventString += dateMatchedText;
  
      if (timeMatchedText)
        eventString += ", ";
    }
  
    if (timeMatchedText)
      eventString += timeMatchedText;
    
    return eventString;
  },
 
  // This function runs in the window scope, so use variables accordingly
  uninit: function(event) {
    if (event.originalTarget != window.document)
      return;
  
    var observerService = Components.classes["@mozilla.org/observer-service;1"]
                                    .getService(Components.interfaces.nsIObserverService);
    observerService.removeObserver(gEventFilter, "MsgMsgDisplayed");
    observerService.removeObserver(gEventFilter, "MsgClearNotifications");
  },

  addDetectedEvent: function(aEvent) {
    var bar = document.getElementById("eventsFilterBar");
    bar.setAttribute("collapsed", "true");
  
    var self = this;
    var onNewItem = function(item, calendar, originalItem) {
      self.window.doTransaction('add', item, calendar, null, null);
    }
  
    this.window.openEventDialog(aEvent.QueryInterface(Components.interfaces.calIEvent), 
                                this.window.getSelectedCalendar(), "new", onNewItem);
  },

  ignoreEventFilter: function() {
    var message = gMessageDisplay.displayedMessage;
    if (!message)
      return;

    var folder = message.folder;
    var imapFolder = true;
  
    try {
      folder.QueryInterface(Components.interfaces.nsIMsgImapMailFolder);
    } catch (ex) { 
      imapFolder = false;
    }
  
    // Ignore future events on this mesage
    message.setUint32Property("X-Synovel-IgnoreEvents", 1);
      
    // Hide the bar now.
    var bar = document.getElementById("eventsFilterBar");
    bar.setAttribute("collapsed", "true");
  },
  
  ignoreEventsSet: function() {
    var message = gMessageDisplay.displayedMessage;
    return (message && message.getUint32Property("X-Synovel-IgnoreEvents") == 1)
  }
}

window.addEventListener("load", gEventFilter.init, true);
