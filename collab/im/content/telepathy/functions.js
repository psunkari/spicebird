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

/*
 * TODO:
 */
function nickFor(account, aContactAccount) {
  var oAccount = getAccount(account);
  if (!oAccount) {
    // TODO
    dump('ERROR: unknown account: ' + account + '. Cannot get alias\n');
    return aContactAccount;
  }

  var contactHandle = gConnectionsByKey[oAccount.key].findContact(aContactAccount);
  if (contactHandle == -1) {
    // TODO
    dump('ERROR: unknown contact ' + aContactAccount + ' in account ' + account + '\n');
    return aContactAccount.split("@")[0];
  }
  return gConnectionsByKey[oAccount.key].mContacts[contactHandle].alias;
}

function addContactToAccount(account, aContactAccount) {
  var oAccount = getAccount(account);
  if (!oAccount) {
    // TODO
    dump('ERROR: unknown account: ' + account + '. Cannot add contact\n');
    displayAlert(getLocaleString([ ['AddContactError'], ['AccountUnknownMessage', account] ]));
    return;
  }

  var oConnection = gConnectionsByKey[oAccount.key];

  if (!oConnection 
      || oConnection.connection.status != Components.interfaces.csITPConnection.Status_Connected) {
    displayAlert(getLocaleString([ ["IMAccNotLoggedInAddContactInfo", account, aContactAccount] ]),
                 getLocaleString([ ["IMAccNotLoggedInTitle"] ]));
    //TODO: Remove contact from IM account Address book
    return;
  }

  oConnection.addContact(aContactAccount);
}

function removeContactFromAccount(account, aContactAccount) {
  var oAccount = getAccount(account);
  if (!oAccount) {
    dump('ERROR: unknown account: ' + account + '. Cannot remove contact\n');
    displayAlert(getLocaleString([ ['RemoveContactError'], ['AccountUnknownMessage', account] ]));
    return;
  }

  var oConnection = gConnectionsByKey[oAccount.key];

  if (!oConnection 
      || oConnection.connection.status != Components.interfaces.csITPConnection.Status_Connected) {
    displayAlert(getLocaleString([ ["IMAccNotLoggedInRemoveContactInfo", account, aContactAccount] ]),
                 getLocaleString([ ["IMAccNotLoggedInTitle"] ]));

    //TODO: Add contact back to IM account Address book
    return;
  }

  oConnection.removeContact(aContactAccount);
}

function updateContactAlias(account, aContactAccount, newAlias) {
  var oAccount = getAccount(account);
  if (!oAccount) {
    dump('ERROR: unknown account: ' + account + '. Cannot update alias\n');
    displayAlert(getLocaleString([ ['SetAliasError', aContactAccount], ['AccountUnknownMessage', account] ]));
    return;
  }

  var oConnection = gConnectionsByKey[oAccount.key];

  if (!oConnection 
      || oConnection.connection.status != Components.interfaces.csITPConnection.Status_Connected) {
    displayAlert(getLocaleString([ ["IMAccNotLoggedInUpdateAliasInfo", account, aContactAccount] ]),
                 getLocaleString([ ["IMAccNotLoggedInTitle"] ]));
    return;
  }

  oConnection.setContactAlias(aContactAccount, newAlias);
}

function sendMessage(account, aContactAccount) {
  var oConnection;
  var remoteUserHandle = -1;
  var accountKey;

  var oAccount = getAccount(account);
  if (!oAccount) {
    // Try to find if the email address is present in any other accounts
    for each (oConnection in gConnectionsCache) {
      remoteUserHandle = oConnection.findContact(aContactAccount);
      if (remoteUserHandle != -1) {
        accountKey = oConnection.mAccountKey;
        oAccount = getAccountByKey(accountKey);
        break;
      }
    }

    if (remoteUserHandle == -1) {
      displayAlert(getLocaleString([ ['LaunchChatSessionError'],  ['ContactUnknownMessage', aContactAccount] ]));
      return;
    }

  }
  else {
    oConnection = gConnectionsByKey[oAccount.key];
    accountKey = oAccount.key;

    remoteUserHandle = oConnection.findContact(aContactAccount);
    if (remoteUserHandle == -1) {
      dump('ERROR: Cannot find ' + aContactAccount + ' in ' + account + ' contacts. Unable to send message\n');
      displayAlert(getLocaleString([ ['LaunchChatSessionError'], ['ContactUnknownMessage', aContactAccount] ]),
                   null, oConnection.mUniqueID);
      return;
    }
  }

  if (!oConnection 
      || oConnection.connection.status != Components.interfaces.csITPConnection.Status_Connected) {
    displayAlert(getLocaleString([ ["IMAccNotLoggedInSendMessageInfo", oAccount.account, aContactAccount] ]),
                 getLocaleString([ ["IMAccNotLoggedInTitle"] ]));
    return;
  }

  if (!oConnection.mContacts[remoteUserHandle].TextChannel) {
    var connection = gConnectionsByKey[accountKey].connection;

    var newChannelCB = new GetNewChannelObserver(gConnectionsByKey[accountKey].mUniqueID);
    newChannelCB.postGotValue = function() {
      this.handleNewChannel(true);
    };

    // NOTE: New channel observer also receives this channel. Passing 
    //  'aSuppressHandlers' as 'true' ensures the channel is handled only by
    //  the observer we pass and is ignored by connection's new channel observer.
    connection.requestNewChannel(Components.interfaces.csITPConnection.Channel_Type_Text,
                                 Components.interfaces.csITPConnection.Handle_Type_Contact, 
                                 remoteUserHandle, true /*aSuppressHandlers*/, newChannelCB);

  }
  else {
    //dump("Send message from: " + accountKey + ", to: " + remoteUserHandle + ".\n");
    var channel = oConnection.mContacts[remoteUserHandle].TextChannel;

    // Check if it is a valid channel
    if (channel.targetHandleType != Components.interfaces.csITPConnection.Handle_Type_Contact 
        || channel.targetHandle != remoteUserHandle) {
      oConnection.mContacts[remoteUserHandle].TextChannel = null;

      displayAlert(getLocaleString([ ['LaunchChatSessionError'], ['RetryMessage'] ]),
                   getLocaleString([ ['ChannelErrorTitle'] ]), oConnection.mUniqueID);

      return;
    }
    
    var userAccount = getAccountByKey(oConnection.mAccountKey).account;
    var remoteUserAccount = oConnection.mContacts[channel.targetHandle].account;
    gConversationManager.startConversation(userAccount, remoteUserAccount, 
                                           channel, true /*isUserTriggered*/);
  }
}

/*
 * UI Triggered actions
 */
function checkAndCreateConnection(aKey, aStatus) {
  var oAccount = new AccountWrapper(aKey);
  if (!gTPManagers[oAccount.manager]) {

    displayAlert(getLocaleString([ ['telepathy.error.manager_unavailable', oAccount.manager],  
                                   ['AccountMessage', oAccount.account + '/' + oAccount.protocol] ]),
                 getLocaleString([ ['ConnectionErrorTitle'] ]));
    return;
  }

  var oConnection = gConnectionsByKey[oAccount.key];

  // Check if the account already has a connection
  if (oConnection && oConnection.connection) {
    var connection = oConnection.connection;

    if (connection.status == Components.interfaces.csITPConnection.Status_Connected) {
      // Set status if required
      //if (oConnection.mStatusString != aStatus) {
      //  oConnection.setStatus(aStatus);
      //}
    } else if ( connection.status == Components.interfaces.csITPConnection.Status_Connecting) {
      displayAlert(getLocaleString([ ['ConnectionInProgressMessage'] ]), null, oConnection.mUniqueID);
    } else {
      dump('ERROR: Existing connection not in connected state. Should not happen.\n');
      displayAlert(getLocaleString([ ['InconsistentConnectionError'] ]), null, oConnection.mUniqueID);
      oConnection.cleanup();
    }
  } else {
    var paramsCB = new GetParamsCB(oAccount.key);
    var connectionCB = new GetNewConnectionCB(oAccount.key);

    connectionCB.postGotValue = function() {
      var connection = this.mItem.QueryInterface(Components.interfaces.csITPConnection);
      var uniqueID = connection.objectPath.substr(gObjectPathOffset);
      gConnectionsCache[uniqueID] = new Connection(connection, uniqueID, true);

      // Will be reset during load. Required for error meanwhile
      gConnectionsCache[uniqueID].mAccount = oAccount.account;
      gConnectionsCache[uniqueID].mProtocol = oAccount.protocol;
      gConnectionsCache[uniqueID].mAccountKey = oAccount.key;

      var connectionReadyObserver = new GetConnectionReadyObserver(uniqueID);
      connection.addConnectionReadyObserver(connectionReadyObserver);

      connection.connect(new GetEmptyCB(uniqueID, getLocaleString([ ['CreateConnectionError'] ])));
    }

    gTelepathyStatus.addStatus(oAccount.key, getLocaleString([ ['ConnectingToAccountMessage', oAccount.account] ])); 
    gTPManagers[oAccount.manager].requestConnection(connectionCB, paramsCB, oAccount.protocol);
  }
}

function closeConnection(aKey) {
  var oAccount = new AccountWrapper(aKey);
  var oConnection = gConnectionsByKey[oAccount.key];

  if (oConnection
      && oConnection.connection.status == Components.interfaces.csITPConnection.Status_Connected) {
    oConnection.connection.disconnect(new GetEmptyCB(oConnection.mUniqueID, getLocaleString([ ['CloseConnectionError'] ])));
  }
}

/*
 * Helper functions
 */
function displayAlert(aMessage, aTitle, aUniqueID) {
  var title = aTitle;
  if (!title)
    title = getLocaleString([ ['AlertTitle'] ]);

  if (aUniqueID) {
    var oConnection = gConnectionsCache[aUniqueID];
    if (oConnection.mAccount && oConnection.mProtocol)
      aMessage += '\n\n' + getLocaleString([ ['AccountMessage', oConnection.mAccount + '/' + oConnection.mProtocol] ]);
  }

  gIMPromptService.alert(null, title, aMessage);
}
      
function compareStatusStrings(one, two) {
  var statuses = ["offline", "invisible", "away", "busy", "available"];
  return statuses.indexOf(one) > statuses.indexOf(two);
}

