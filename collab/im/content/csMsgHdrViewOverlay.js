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
#   Siva Edpuganti <sivakrishna@synovel.com> (Original Author)
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

var gIMStatusService = gIMStatusService || {}; 

function SendInstantMessage(emailAddressNode) {
  if (emailAddressNode) {
    gTelepathy.sendMessage(emailAddressNode.getAttribute("account"), 
                                 emailAddressNode.getAttribute("emailAddress"));
  }
}

function updateMsgHdrStatus(contact) {
  // Check all email header boxes
  var boxes = document.getElementsByTagName("mail-multi-emailHeaderField");

  for (var index=0; index<boxes.length; index++) {
    // 'emailAddresses' property defined in mailWidgets.xml
    var emailAddresses = boxes[index].emailAddresses;

    // Attribute defined in mailWidgets.xml -> aEmailNode.setAttribute("emailAddress", aAddress.emailAddress)
    var emailAddressNodes = emailAddresses.getElementsByAttribute("emailAddress", contact.id);

    for (var i=0; i< emailAddressNodes.length; i++) {
      emailAddressNodes[i].setAttribute("im-status", contact.status); 
      emailAddressNodes[i].setAttribute("account", contact.account); 
    }
  }
}

function setMsgHdrStatus() {
  // Update all email header boxes
  var boxes = document.getElementsByTagName("mail-multi-emailHeaderField");

  for (var index=0; index<boxes.length; index++) {
    // 'emailAddresses' property defined in mailWidgets.xml
    var emailAddresses = boxes[index].emailAddresses;

    var emailAddressNodes = emailAddresses.getElementsByTagName("mail-emailaddress");

    for (var i=0; i< emailAddressNodes.length; i++) {
      var contact = gIMStatusService.getContactStatus(null, emailAddressNodes[i].getAttribute("emailAddress"));

      if (contact) {
        contact = contact.QueryInterface(Components.interfaces.csIIMContact);
        emailAddressNodes[i].setAttribute("im-status", contact.status); 
        emailAddressNodes[i].setAttribute("account", contact.account); 
      } else {
        emailAddressNodes[i].removeAttribute("im-status");
      }
    }
  }
}

var msgHdrStatusUpdateObserver = {
  observe: function (aSubject, aTopic, aData)
  {
    if (aTopic == "MsgMsgDisplayed") {
      setMsgHdrStatus();
    }
  }
}

var csMsgHdrStatusUpdateListener = {
  self: this,

  statusUpdated: function(contact) {
    this.self.updateMsgHdrStatus(contact);
  }
};

function removeMsgHdrStatusUpdater(event) {
  if (event.originalTarget != window.document)
    return;

  window.removeEventListener("unload", removeMsgHdrStatusUpdater, true);

  gIMStatusService.removeListener(csMsgHdrStatusUpdateListener);

  var observerService = Components.classes["@mozilla.org/observer-service;1"]
                                          .getService(Components.interfaces.nsIObserverService);
  observerService.removeObserver(msgHdrStatusUpdateObserver, "MsgMsgDisplayed");
}

function initMsgHdrStatusUpdater(event) {
  if (event.originalTarget != window.document)
    return;

  window.removeEventListener("load", initMsgHdrStatusUpdater, true);
  window.addEventListener("unload", removeMsgHdrStatusUpdater, true);

  if (typeof gIMStatusService.getContactStatus != 'function')
    gIMStatusService = Components.classes["@synovel.com/collab/im/imstatusservice;1"]
                                 .getService(Components.interfaces.csIIMStatusService);

  gIMStatusService.addListener(csMsgHdrStatusUpdateListener);

  var observerService = Components.classes["@mozilla.org/observer-service;1"]
                                          .getService(Components.interfaces.nsIObserverService);
  // set the msg hdr status when new email displayed.
  observerService.addObserver(msgHdrStatusUpdateObserver, "MsgMsgDisplayed", false);

  // set the msg hdr status when header view toggled.
  document.getElementById("toggleHeaderView").addEventListener("click", setMsgHdrStatus, true);
}

window.addEventListener("load", initMsgHdrStatusUpdater, true);

