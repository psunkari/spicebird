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
#   Prasad Sunkari <prasad@synovel.com>
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

/****************************************************
 * IM Account details
 *  read from preferences
 ****************************************************/
function uniq(array) {
    var encountered = [];

    return array.filter(
        function(item) {
            if(encountered.indexOf(item) == -1) {
                encountered.push(item);
                return true;
            } else
                return false;
        });
}

this.__defineGetter__(
    'gAccounts', function() {
        var keys = uniq(
            gPrefBranch
            .getChildList('accounts.', {})
            .map(
                function(item) {
                    return item.split('.')[1];
                })
            .filter(
                function(aPrefKey) {
                    return aPrefKey != undefined;
                }));

        return keys.map(
            function(aPrefKey) {
                return new AccountWrapper(aPrefKey);
            });
    });

function AccountWrapper(aPrefKey) {
    this.key = aPrefKey;
}

AccountWrapper.prototype = {
    _read: function(preference) {
        var prefReaders = ['getCharPref', 'getIntPref', 'getBoolPref'];
        for each(var reader in prefReaders) {
            try {
                return gPrefBranch[reader]('accounts.' + this.key + '.' + preference);
            } catch(e) {}
        }
        return undefined;
    },

    get id() {
        return this.account;
    },

    get enabled() {
        try {
            return gPrefBranch.getBoolPref('accounts.' +
                                           this.key +
                                           '.enabled');
        } catch(ex) {};

        return true;
    },

    set enabled(aEnabled) {
        try {
            gPrefBranch.setBoolPref('accounts.' + this.key + '.enabled',
                                    Boolean(aEnabled));
        } catch(ex) {
          dump(ex);
        };
    }
};

['account', 'server', 'protocol', 'manager', 'url']
.forEach(function(property) {
                  AccountWrapper.prototype.__defineGetter__(
                      property, function() {
                          var propertyValue = this._read(property);

                          // Handling for 'google-talk'
                          if (property == 'protocol') {
                            if (propertyValue == 'google-talk')
                              propertyValue = 'jabber';
                          }
                          else if (property == 'url') {
                            propertyValue = 'im-' + this. protocol + '://' + this.account +  
                              ((this.server != undefined) ?  ('@' + this.server) : '');
                          }

                          return propertyValue;
                      });
              });

function accountSetup(prefKey) {
  window.openDialog('chrome://im/content/imAccountSetup.xul',
                    'im-account-setup', 'chrome', gTPManagers, prefKey);
}

function enableAccount(event) {
  var target = event.originalTarget;
  if (event.originalTarget.nodeName == 'command')
    target = event.sourceEvent.originalTarget;
    
  var accountKey = event.originalTarget.getAttribute('account');
  var account = getAccountByKey(accountKey);
  account.enabled = target.getAttribute("checked");

  // Update the accounts status
  var connection = gConnectionsByKey[account.key];
  if (account.enabled && gMyPresence.status != 'offline') {
    if (connection)
      connection.setOnlineStatus(gMyPresence.status, gMyPresence.message);
    else
      checkAndCreateConnection(account.key, gMyPresence.status);
  } else if(connection)
    connection.close();
}

function editAccount(event) {
  var accountKey;
  if (event.originalTarget.nodeName == 'command')
    accountKey = event.sourceEvent.originalTarget.getAttribute('account');
  else
    accountKey = event.originalTarget.getAttribute('account');

  accountSetup(accountKey);
}

function deleteAccount(event) {
  var accountKey;
  if (event.originalTarget.nodeName == 'command') 
    accountKey = event.sourceEvent.originalTarget.getAttribute('account');
  else
    accountKey = event.originalTarget.getAttribute('account');

  var account = getAccountByKey(accountKey).account;
  var result = gIMPromptService.confirm(null, getLocaleString([ ['ConfirmIMAccDeleteTitle'] ]), 
                                getLocaleString([ ['ConfirmIMAccDeleteInfo', account] ]));
  if (result) {
    // Delete entry in password manager, if any
    removePasswordFromManager(accountKey);

    // Close if connected to this account 
    closeConnection(accountKey);

    // Notify observers (to delete addressbook entry)
    var observerService = Components.classes["@mozilla.org/observer-service;1"]
                                    .getService(Components.interfaces.nsIObserverService);
    observerService.notifyObservers(null, "csIMAccountDeleted", accountKey);

    // Delete account preferences
    var accountPrefBranch = Components.classes["@mozilla.org/preferences-service;1"]
                                 .getService(Components.interfaces.nsIPrefService)
                                 .getBranch("collab.im.accounts." + accountKey);

    accountPrefBranch.deleteBranch("");
  }
}

function changeStatusMessage(event) {
  var check = {value: false}; // Will not be used, but required by prompt()
  var input = {value: gMyPresence.message};
  var result = gIMPromptService.prompt(null, getLocaleString([ ['IMStatusMessageTitle'] ]), 
                               getLocaleString([ ['IMStatusMessageInfo'] ]), input, null, check);

  if (result) {
    if (input.value == gMyPresence.message) {
      //dump('changeStatusMessage Nothing to do\n');
      return;
    }

    gMyPresence.message = input.value;

    // Intimate all connections
    for each (var connection in gConnectionsCache) {
      connection.setOnlineStatus(connection.mMyPresence.status,
                                 gMyPresence.message);
    }
  }
}

function enabledAccountsCount()
{
  var accounts = gAccounts.filter(function(oAccount) { 
                   return oAccount.enabled;
                 });
  return accounts.length;
}

/*
 * setGlobalStatus: Change the global status
 * All observers (including connections) subscribed to "im-status"
 * get the update and change status accordingly
 *
 * @aOnlineStatus is the new online status
 * @aStatusMessage is the new status message
 */
function setGlobalStatus(aOnlineStatus, aStatusMessage)
{
  if (enabledAccountsCount() == 0)
    return;

  gMyPresence.status = aOnlineStatus;
  gMyPresence.message = aStatusMessage;

  // Notify observers about the global
  // status change.  The observers include
  // connections that are subscribed to the
  // global status
  Components.classes["@mozilla.org/observer-service;1"]
            .getService(Components.interfaces.nsIObserverService)
            .notifyObservers(null, "im-status", gMyPresence.status);
}

function updateGlobalStatus(aOnlineStatus, aStatusMessage)
{
  gMyPresence.status = aOnlineStatus;
  gMyPresence.message = aStatusMessage;

  // Notify observers that the global status needs
  // to be synced.  This sync is due to change in status
  // of one or more connections and is not set by the user.
  //
  // All UI elements that display status to the users should
  // subscribe to this status to get updates
  Components.classes["@mozilla.org/observer-service;1"]
            .getService(Components.interfaces.nsIObserverService)
            .notifyObservers(null, "im-status-sync", aOnlineStatus);
}

/*
 * setAccountStatus: Set status for an unexisting connection
 *
 * @aAccountKey is the account identifier
 * @aOnlineStatus is the new online status
 * @aStatusMessage is the new status message
 */
function setAccountStatus(aAccountKey,
                          aOnlineStatus, aStatusMessage)
{
  if (aAccountKey)
    checkAndCreateConnection(aAccountKey, aOnlineStatus);
}

/*
 * setConnectionStatus: Set status for an existing connection
 *
 * @aConnectionID is the unique identifier of the connection
 * @aOnlineStatus is the new online status for the connection
 * @aStatusMessage is the new status message fro the connection
 */
function setConnectionStatus(aConnectionID,
                             aOnlineStatus, aStatusMessage)
{
  var connection = gConnectionsCache[aConnectionID];
  if (!connection)
    return;

  connection.setOnlineStatus(aOnlineStatus, aStatusMessage);
}
  
/*
 * Returns account wrapper for given account
 */
function getAccount(account)
{
  var accounts = gAccounts.filter( function(oAccount) { return oAccount.account == account; } );
  if (accounts.length > 0)
    return accounts[0];

  return null;
}

function getAccountByKey(key)
{
  var accounts = gAccounts.filter( function(oAccount) {return oAccount.key == key} );
  if (accounts.length > 0)
    return accounts[0];

  return null;
}

function requestConversation(account, address)
{
  if (account == address) {
    dump('ERROR: cannot start conversation for same account & address\n');
    return;
  }
  //dump('send Message to: ' + account + ' from : ' + address + '\n');
  var oAccount = getAccount(account);

  sendMessage(account, address);
}

/*
 * Add a new IM contact.
 *
 * @aConnectionID is the unique identifier of the connection
 * @aAccountID is the identifier of the user to add
 * @aAccountAlias is the alias for the newly added user
 */
function imAddNewContact(aConnectionID, aAccountID, aAccountAlias)
{
  if (aConnectionID == undefined || aConnectionID == "" ||
      aAccountID == undefined || aAccountID == "")
    return;

  var connection = gConnectionsCache[aConnectionID];
  if (connection)
    connection.addContact(aAccountID);

  return;

  // We currently don't support setting aliases at
  // the time of adding contact.

  if (aAccountAlias && aAccountAlias != "")
    connection.setContactAlias(aAccountID, aAccountAlias);
}

/*
 * Remove and existing IM contact.
 *
 * @aConnectionID is the unique identifier of the connection
 * @aAccountID is the identifier of the user to be removed
 */
function imRemoveContact(aConnectionID, aAccountID)
{
  var oConnection = gConnectionsCache[aConnectionID];
  if (!oConnection) {
    dump("Could not find a connection with the given ID\n");
    return;
  }

  oConnection.removeContact(aAccountID);
}

/*
 * Update alias of an IM contact.
 *
 * @aConnectionID is the unique identifier of the connection
 * @aAccountID is the identifier of the remote user
 * @aAccountAlias is the alias for the newly added user
 */
function imUpdateContactAlias(aConnectionID, aAccountID, aAccountAlias)
{
  if (aConnectionID == undefined || aConnectionID == "" ||
      aAccountID == undefined || aAccountID == "" ||
      aAccountAlias == undefined || aAccountAlias == "")
    return;

  var oConnection = gConnectionsCache[aConnectionID];
  if (!oConnection) {
    dump("Could not find a connections with the given ID\n");
    return;
  }
  
  oConnection.setContactAlias(aAccountID, aAccountAlias);
}

/*
 * Open a text chat channel to an IM contact
 *
 * @aConnectionID is the unique identifier of the connection
 * @aAccountID is the identifier of the remote user
 */
function imOpenTextChannel(aConnectionID, aAccountID)
{
  var oConnection = gConnectionsCache[aConnectionID];
  if (!oConnection) {
    dump("Could not find a connection with the given ID\n");
    return;
  }

  var remoteUserHandle = oConnection.findContact(aAccountID);
  if (remoteUserHandle == -1) {
    dump("Cannot send message to " + aAccountID + ".  Contact not found!\n");
    return;
  }

  if (oConnection.connection.status != Components.interfaces.csITPConnection.Status_Connected) {
    dump("Cannot send message to " + aAccountID + ".  Not Connected!\n");
    return;
  }

  /* Create a channel if it does not already exist */
  if (!oConnection.mContacts[remoteUserHandle].TextChannel) {
    var connection = oConnection.connection;
    var newChannelCB = new GetNewChannelObserver(oConnection.mUniqueID);
    newChannelCB.postGotValue = function() {
      this.handleNewChannel(true);
    };

    connection.requestNewChannel(Components.interfaces.csITPConnection.Channel_Type_Text,
                                 Components.interfaces.csITPConnection.Handle_Type_Contact, 
                                 remoteUserHandle, true, newChannelCB);

  } else {
    var channel = oConnection.mContacts[remoteUserHandle].TextChannel;
    var userAccount = oConnection.mAccount;
    var remoteUserAccount = oConnection.mContacts[channel.targetHandle].account;
    gConversationManager.startConversation(userAccount, remoteUserAccount, 
                                           channel, oConnection.mSelfHandle, true);
  }
}

/*
 * Prompt user for approval of a contact
 *
 * @aConnectionID is the unique identifier of the connection
 * @aAccountID is the identifier of the user to be removed
 */
function promptUserApproval(aConnectionID, aAccountID)
{
  var oConnection = gConnectionsCache[aConnectionID];
  if (!oConnection) {
    dump("ERROR: Could not find a connection with the given ID\n");
    return;
  }

  var remoteUserHandle = oConnection.findContact(aAccountID);
  if (remoteUserHandle == -1) {
    dump("ERROR: Cannot send approve " + aAccountID + ".  Contact not found!\n");
    return;
  }

  oConnection.handleSubscriptionRequest(remoteUserHandle);
}

