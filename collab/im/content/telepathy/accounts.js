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
# Portions created by the Initial Developer are Copyright (C) 2008
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

// IM Accounts integration with addresbook 

const gIMDirectoryKey  = 4; // IMDirectory defined in nsDirPrefs.h
const gAbDirectoryPrefix = "moz-abimdirectory://";

var gIMAddressbookURI = null;
var gIMDirectoryBranch;

function initAccounts() {
  // TODO: Hack to prevent creation of IM directory before the
  // creation of "Personal Address Book". Problem arises
  // only when a new profile is created. 
  // Timeout for 500ms is sufficient.
  setTimeout(function() {
          checkRootDirectory();
          attachAddressBookListener();
          loadComplete('accounts');
         }, 1000);

  var observerService = Components.classes["@mozilla.org/observer-service;1"]
                                  .getService(Components.interfaces.nsIObserverService);
  observerService.addObserver(imAccountObserver, "csIMAccountCreated", false);
  observerService.addObserver(imAccountObserver, "csIMAccountDeleted", false);
  observerService.addObserver(imAccountObserver, "im-status", false);
  observerService.addObserver(imAccountObserver, "im-connection-status", false);

  //dump('init accounts done\n');
}

var imAccountObserver = {
  observe: function (aSubject, aTopic, aData) {
    if (aTopic == 'csIMAccountCreated') {
      var account = getAccountByKey(aData);
      createIMAddrBook(aData, account.account);

      // Enable account by default
      account.enabled = true;
      if (gMyPresence.status != 'offline')
        checkAndCreateConnection(account.key, gMyPresence.status);
    }
    else if (aTopic == 'csIMAccountDeleted') {
      var account = getAccountByKey(aData).account;
      deleteIMAddrBook(account);
    }
    else if (aTopic == 'im-status') {
      gAccounts.forEach(function(account) {
        if (account.enabled) {
          var oConnection = gConnectionsByKey[account.key];
          if (oConnection)
            oConnection.setOnlineStatus(gMyPresence.status,
                                        gMyPresence.message);
          else if (gMyPresence.status != 'offline')
            checkAndCreateConnection(account.key, gMyPresence.status);
        }
      });
    }
    else if (aTopic == 'im-connection-status') {
      // Start with offline status
      var status = 'offline';

      gAccounts.forEach(function(account) {
        if (account.enabled) {
          var oConnection = gConnectionsByKey[account.key];
          if (oConnection && 
              compareStatusStrings(oConnection.mMyPresence.status, status))
            status = oConnection.mMyPresence.status;
        }
      });
      updateGlobalStatus(status, gMyPresence.message);
    }
  }
};

var gInstmsgAbListener = {
  onItemAdded: function(aParentDir, aItem) {
    // Called when a new address book, mailing list or card is added.

    // Filter calls when address book & mailing list added.
    // When a card is added, aItem will be of type nsIAbCard.
    var card;
    try {
      card = aItem.QueryInterface(Components.interfaces.nsIAbCard);
    } catch(ex) {
      //dump("skipping item add. no card\n");
      return;
    }

    //dump("New card added: " + card.primaryEmail + "\n");

    try {
      var parentDir = aParentDir.QueryInterface(Components.interfaces.nsIAbDirectory);
      // Dont bother about additions to any addressbook directly.
      // We care only about mailing lists.
      //dump("IM Dir: " + gIMAddressbookURI + ", Parent dirName: " + parentDir.dirName + ", nick: " + parentDir.listNickName + "\n");
      if (!parentDir.isMailList)
        return;

      if (isIMAccount(parentDir)) {
        // Add contact since the mail list is present in the rootIMDirectory.
        // TODO:
        addContactToAccount(parentDir.dirName, card.primaryEmail);
      }
    } catch(ex) {
      //dump("parent not a directory. ex: " + ex + "\n");
    }
  },

  onItemRemoved: function(aParentDir, aItem) {
    // Called when a mailing list or card is removed.

    // Filter calls when address book & mailing list added.
    // When a card is removed, aItem will be of type nsIAbCard.
    var card;
    try {
      card = aItem.QueryInterface(Components.interfaces.nsIAbCard);
    } catch(ex) {
      //dump("skipping item remove. no card\n");
      return;
    }

    //dump("card removed: " + card.primaryEmail + "\n");

    try {
      var parentDir = aParentDir.QueryInterface(Components.interfaces.nsIAbDirectory);
      // Dont bother about deletes from any addressbook directly.
      // We care only about mailing lists.
      //dump("Parent dirName: " + parentDir.dirName + ", nick: " + parentDir.listNickName + "\n");
      if (!parentDir.isMailList)
        return;

      if (isIMAccount(parentDir)) {
        // Remove contact since the mail list is present in the rootIMDirectory.
        // TODO:
        removeContactFromAccount(parentDir.dirName, card.primaryEmail);
      }
    } catch(ex) {
      //dump("parent not a directory. ex: " + ex + "\n");
    }
  },

  onItemPropertyChanged: function(aItem, property, oldValue, newValue) {
    // Called when an addressbook, mailing list or card is changed.

    try {
      var selectedURI = GetSelectedDirectory();

      if (selectedURI.indexOf(gIMAddressbookURI) == -1)
        return;

      var card = aItem.QueryInterface(Components.interfaces.nsIAbCard);
      var address = card.primaryEmail; 

      var parentDir = GetDirectoryFromURI(selectedURI);
      var account = parentDir.dirName;

      if (!parentDir.isMailList) {
        // TODO: Handle display name change in following case.
        //       -> Select IM Root directory 
        //       -> Open properties of a mailing list 
        //       -> Update display name of a contact in the mailing list
        // There is no direct way to identify the parent mailing list from
        //  the property change notification
        return;
      }

      // Get existing alias for contact
      var alias = nickFor(account, address);
      if (!alias) {
        // No cache present => not signed into the account.
        // TODO: Handle case when display name changed for card, but the account is not up.
        return;
      }

      if (card.displayName != alias)
        updateContactAlias(account, address, card.displayName);

    } catch(ex) {
      // Ignore if property change done to a mailing list
    }
  }
};

function isIMAccount(directory) {
  var rootDirectory = GetDirectoryFromURI(gIMAddressbookURI);

  var count = rootDirectory.addressLists.length;
  for (var i=0; i<count; i++) {
    var dirproperty = rootDirectory.addressLists.queryElementAt(i, Components.interfaces.nsIAbDirectory);
    //dirproperty = dirproperty.QueryInterface(Components.interfaces.nsIAbDirectory);

    // It is not possible to create multiple maillists with same name in the entire addressbook.
    // So if "rootDir" has a directory with same name, it must be a child of rootDir.
    if (dirproperty.dirName == directory.dirName)
      return true;
  }

  return false;
}

function attachAddressBookListener() {
  // Do this after the gIMAddressbookURI is set, i.e. after checkRootDirectory()
  var nsIAbListener = Components.interfaces.nsIAbListener;
  var abManager = Components.classes["@mozilla.org/abmanager;1"]
                            .getService(Components.interfaces.nsIAbManager);
  abManager.addAddressBookListener(gInstmsgAbListener,
                                   nsIAbListener.itemAdded |
                                   nsIAbListener.itemChanged |
                                   nsIAbListener.directoryItemRemoved
                                  );

}

function checkRootDirectory() {
  var tmpPrefBranch = Components.classes["@mozilla.org/preferences-service;1"]
                                .getService(Components.interfaces.nsIPrefService)
                                .getBranch(null);

  // Get preference "collab.im.IMDirectoryBranch".
  //     If not set, create directory.
  var rootDirectoryBranch;
  try {
    rootDirectoryBranch = tmpPrefBranch.getCharPref("collab.im.IMDirectoryBranch");
  } catch(ex) {
    rootDirectoryBranch = createRootDirectory();
  }

  // Get filename of the addressbook branch to create the URL
  var filename = null;
  try {
    filename = tmpPrefBranch.getCharPref(rootDirectoryBranch + ".filename");
  } catch(ex) {
    // Should not come here. filename should exist under directory preference branch
    // - If not -> Unstable situation: directory prefbranch exists but not file???
    dump("ERROR: " + ex + "\n");

    // Never mind, lets create the root directory in any case.
    rootDirectoryBranch = createRootDirectory();
    if (!rootDirectoryBranch)
      dump("ERROR: Should not happen. Unable to create root IM directory.\n");

    filename = tmpPrefBranch.getCharPref(rootDirectoryBranch + ".filename");
  }

  gIMDirectoryBranch = rootDirectoryBranch;

  // Get IM Root Directory URL based on filename. -> "moz-abimdirectory://<filename>"
  gIMAddressbookURI = gAbDirectoryPrefix + filename;
}

function createRootDirectory() {
  // Create addressbook with a "localized" name.
  var rootDirectoryBranch = null;
  try {
    var abManager = Components.classes["@mozilla.org/abmanager;1"]
                              .getService(Components.interfaces.nsIAbManager);

    var IMRootDirName = getLocaleString([['IMRootDirectoryName']]);

    rootDirectoryBranch = abManager.newAddressBook(IMRootDirName, "", gIMDirectoryKey);

    // Store branch name as "collab.im.IMDirectoryBranch"
    gPrefBranch.setCharPref("IMDirectoryBranch", rootDirectoryBranch);
    savePrefFile();
  } catch (ex) {
    dump("ERROR: during IM Root Directory creation: " + ex + "\n");
  }

  return rootDirectoryBranch;
}

function savePrefFile() {
  Components.classes["@mozilla.org/preferences-service;1"]
            .getService(Components.interfaces.nsIPrefService)
            .savePrefFile(null);
}

function getMailListURI(address) {
  if (!address) {  
    dump("WARN: Cant getMailListURI for null\n");
    return null;
  }

  var parentDirectory = GetDirectoryFromURI(gIMAddressbookURI);

  var count = parentDirectory.addressLists.length;
  for (var i=0; i<count; i++) {
    var dirproperty = parentDirectory.addressLists.queryElementAt(i, Components.interfaces.nsIAbDirectory);
    //dirproperty = dirproperty.QueryInterface(Components.interfaces.nsIAbDirectory);

    if (dirproperty.isMailList && dirproperty.dirName == address) {
      return dirproperty;
    }
  }

  return null;
}

function deleteIMAddrBook(address) {
  var mailList = getMailListURI(address);

  if (!mailList) {
    dump("ERROR: Cannot delete non-existent maillist: " + address + "\n");
    return;
  }

  //dump("Starting to delete: add - " + address + "\n");
  mailList = mailList.QueryInterface(Components.interfaces.nsIAbDirectory);

  var parentDirectory = GetDirectoryFromURI(gIMAddressbookURI);
  parentDirectory.deleteDirectory(mailList);

  //dump("Done deleting IM Addrbook for: " + address + "\n");
}

function createIMAddrBook(accountKey, address) {

  if (getMailListURI(address)) { // Already exists
    dump("ERROR: Cant create existing maillist: " + address + "\n");
    return;
  }

  // Create an address book card with account address. 
  // Ensures autocomplete does not replace account address with the mailing list

  var parentDirectory = GetDirectoryFromURI(gIMAddressbookURI);
  var cardproperty = Components.classes["@mozilla.org/addressbook/cardproperty;1"]
                               .createInstance();
  cardproperty = cardproperty.QueryInterface(Components.interfaces.nsIAbCard);
  cardproperty.primaryEmail = address;
  parentDirectory.addCard(cardproperty);


  // Add mailing list to IM Address book
  var mailList = Components.classes["@mozilla.org/addressbook/directoryproperty;1"].createInstance();
  mailList = mailList.QueryInterface(Components.interfaces.nsIAbDirectory);

  mailList.isMailList = true;
  mailList.dirName = address;
  mailList.listNickName = address.split('@')[0] || address;
  mailList.description = "Contacts for Account - " + address;

  parentDirectory.addMailList(mailList);

  var abookPref = 'accounts.' + accountKey + '.abookcreated';
  gPrefBranch.setCharPref(abookPref, address);
  savePrefFile();

  //dump("Done creating IM Addrbook for: " + address + "\n");
}

function checkForContact(mailList, contact) {
  var count = mailList.addressLists.length;
  for (var i=0; i<count; i++) {
    var cardproperty = mailList.addressLists.queryElementAt(i, Components.interfaces.nsIAbCard);
    //cardproperty = cardproperty.QueryInterface(Components.interfaces.nsIAbCard);

    if (cardproperty.primaryEmail == contact.address) {
      //dump("Checking - Address: " + contact.address 
      //     + " exists in " + mailList.dirName + "\n");
      return i;
    }
  }
  return -1;
}

function modifyIMAddrBook(accountKey, abookAddress, operations) {

  if (operations.length == 0)
    return;

  var mailList = getMailListURI(abookAddress);
  if (!mailList) {
    dump("ERROR: Creating non-existent maillist: " + abookAddress + "\n");
    createIMAddrBook(accountKey, abookAddress);
    mailList = getMailListURI(abookAddress);
  }

  for (var count=0; count<operations.length; count++) {
    var cardproperty;
    var contact = operations[count].contact;
    var action = operations[count].action;

    if (action == "add") {
      //dump("Adding Address: " + contact.address 
      //             + " to " + abookAddress + "\n");

      // XXX: hasCard throws an exception 
      //if (mailList.hasCard(cardproperty))
      var index = checkForContact(mailList, contact);
      if (index != -1) {
        //dump("Address: " + contact.address 
        //     + " already exists in " + abookAddress + "\n");

        // Set display name
        var cardproperty2 = mailList.addressLists.queryElementAt(index, Components.interfaces.nsIAbCard);
        //cardproperty2 = cardproperty2.QueryInterface(Components.interfaces.nsIAbCard);

        cardproperty2.displayName = contact.alias;
        continue;
      }

      cardproperty = Components.classes["@mozilla.org/addressbook/cardproperty;1"]
                               .createInstance();
      cardproperty = cardproperty.QueryInterface(Components.interfaces.nsIAbCard);

      cardproperty.primaryEmail = contact.address;
      cardproperty.displayName = contact.alias;
    
      //dump("Creating Address: " + contact.address 
      //     + " in " + abookAddress + "\n");
      mailList.addressLists.appendElement(cardproperty, false);

    } 
    else if (action == "remove") {
      //dump("Removing Address: " + contact.address 
      //             + " from " + abookAddress + "\n");
      var addressCount = mailList.addressLists.length;
      for (var i=0; i<addressCount; i++) {
        cardproperty = mailList.addressLists.queryElementAt(i, Components.interfaces.nsIAbCard);
        //cardproperty = cardproperty.QueryInterface(Components.interfaces.nsIAbCard);

        if (cardproperty.primaryEmail == contact.address) {
          //dump("Address: " + contact.address 
          //     + " exists in " + abookAddress + "\n");
          mailList.addressLists.removeElementAt(i);
          break;
        }
      }
    }
  }

  mailList.editMailListToDatabase(null);
}

