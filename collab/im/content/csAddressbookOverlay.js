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

/* 
 * Todo:
 * - Update list view also. Currently updates only card view cards.
 * - Set the contact account, address on AbIMSelected() popup menu.
 */

var gIMAddressbookURI = null;

function CheckIfIMAccountSelected(aURI) {
  // Check if this is "Instant Messaging" folder or a mailing list under it.

  //    Get IM Directory Branch
  var rootDirectoryBranch = null;
  var rootDirectoryFile = null;
  var tmpPrefBranch = Components.classes["@mozilla.org/preferences-service;1"]
                                .getService(Components.interfaces.nsIPrefBranch);

  try {
    rootDirectoryBranch = tmpPrefBranch.getCharPref("collab.im.IMDirectoryBranch");
    rootDirectoryFile = tmpPrefBranch.getCharPref(rootDirectoryBranch + ".filename");
  } catch(ex) {
    if (rootDirectoryBranch)
      dump("ERROR: Cant get fileName for: " + rootDirectoryBranch + "\n");
  }

  //    Check if the "aURI" has IM folder fileName in it.
  //      Delimiter ensures appropriate match.
  if (rootDirectoryFile && aURI.indexOf('://' + rootDirectoryFile) != -1)
    return true;

  return false;
}

// Extend existing function
var AbCardDefaultActionBase = AbCardDefaultAction;
var AbCardDefaultAction = function() {
  if (CheckIfIMAccountSelected(GetSelectedDirectory()))
    AbIMSelected();
  else
    AbCardDefaultActionBase();
}

// Override existing function
function AbIMSelected() {
  var cards = GetSelectedAbCards();
  var count = cards.length;

  var screennames;
  var screennameCount = 0;

  for (var i=0; i<count; i++) {

    var email = cards[i].primaryEmail;

    if (email != undefined && email != "")
      gTelepathy.sendMessage(null, email);
  }
}

function updateVcardStatus(contact) {
  // Update specific cards in card view.

  var cardsBox = document.getElementById("abCardViewBox");

  if (!cardsBox)
    return;

  var vcards = cardsBox.getElementsByAttribute("emailAddress", contact.id);

  for (var i = 0; i < vcards.length; i++) {
    vcards[i].setAttribute("im-status", contact.status);
    vcards[i].setAttribute("account", contact.account);
  }
}

function setVcardStatus() {
  // Ignore if current view is not card view
  if (gAbViewType != kAbView_CardView)
    return;

  // Update all vcards in card view.
  var cardsBox = document.getElementById("abCardViewBox");

  if (!cardsBox)
    return;

  var vcards = cardsBox.getElementsByTagName("vcard");

  for (var i=0; i<vcards.length; i++) {

    // Dont bother about collapsed cards.
    if (vcards[i].getAttribute("collapsed") == "true")
      continue;

    var emailAddress = vcards[i].getAttribute("emailAddress");
    if (emailAddress) {
      var contact = gIMStatusService.getContactStatus(null, emailAddress);

      if (contact) {
        vcards[i].setAttribute("im-status", contact.status);
        vcards[i].setAttribute("account", contact.account);
        // Proceed to the next card
        continue;
      } 
    }

    // Reset status attributes of vcard when email address is missing 
    //  or contact status is not known
    vcards[i].removeAttribute("im-status");
    vcards[i].removeAttribute("account");
  }
}

var cardStatusUpdateObserver = {
  observe: function (aSubject, aTopic, aData) {
    if (aTopic == "AbViewInitDone")
      setVcardStatus();
  }
}

function csInstallColumnHandler()
{
  var csContactsColumnHandler = {

    atomService: Components.classes["@mozilla.org/atom-service;1"]
                           .getService(Components.interfaces.nsIAtomService),

    getCellText: function(row, col) {
      /*
       * Currently no text.  Only the icon will be displayed.
       * Will support status text and user photos in future versions
       *
      var card = gAbView.getCardFromRow(row);
      var email = card.getProperty('PrimaryEmail', '') || card.getProperty('SecondEmail', '');

      var onlineStatus = gIMStatusService.getContactStatus(null, email);
      if (onlineStatus) {
        var contact = onlineStatus.QueryInterface(Components.interfaces.csIIMContact);
        if (contact)
            return contact.status;
      }

      return '';
      */
    },

    getRowProperties: function(index, props){
      // Set the online status in property
    },

    getCellProperties: function(row, col, props){
      var card = gAbView.getCardFromRow(row);
      var email = card.getProperty('PrimaryEmail', '') || card.getProperty('SecondEmail', '');

      var onlineStatus = gIMStatusService.getContactStatus(null, email);
      if (onlineStatus) {
        var contact = onlineStatus.QueryInterface(Components.interfaces.csIIMContact);
        if (contact) {
            if (!this.atomService) {
                this.atomService = Components.classes["@mozilla.org/atom-service;1"]
                                             .getService(Components.interfaces.nsIAtomService)
            }
            props.AppendElement(this.atomService.getAtom("im-" + contact.status));
        }
      }
    },

    getImageSrc: function(row, col) {},

    getSortLongForRow: function(hdr) {
      var card = gAbView.getCardFromRow(row);
      var email = card.getProperty('PrimaryEmail', '') || card.getProperty('SecondEmail', '');

      var onlineStatus = gIMStatusService.getContactStatus(null, email);
      if (onlineStatus) {
        var contact = onlineStatus.QueryInterface(Components.interfaces.csIIMContact);
        if (contact) {
            switch(contact.status) {
                case "online":
                  return 0;
                case "offline":
                  return 10;
                case "busy":
                  return 1;
                case "away":
                  return 2;
                default:
                  return 9;
            }
        }
      }
      return 0;
    }
  };
  gAbView.addColumnHandler("IMStatus", csContactsColumnHandler);
}

var cardStatusUpdateListener = {
  self: this,

  statusUpdated: function(contact) {
    this.self.updateVcardStatus(contact);
  }
};

function initIMAddressbookOverlay() {
  window.removeEventListener("load", initIMAddressbookOverlay, true);

  var ObserverService = Components.classes["@mozilla.org/observer-service;1"]
                                  .getService(Components.interfaces.nsIObserverService);

  ObserverService.addObserver(cardStatusUpdateObserver, "AbViewInitDone", false);
  ObserverService.addObserver(
      {
        observe: function(aMsgFolder, aTopic, aData) {
          csInstallColumnHandler();
        }
      }, "abview:create", false );

  var imStatusService = Components.classes["@synovel.com/collab/im/imstatusservice;1"]
                                  .getService(Components.interfaces.csIIMStatusService);

  imStatusService.addListener(cardStatusUpdateListener);

}

window.addEventListener("load", initIMAddressbookOverlay, true);

