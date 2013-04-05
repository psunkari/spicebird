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

// Instance of the csITelepathyService
var gTPService;

// Cache of all the existing telepathy connections
// mapped by uniqueID derived from the objectPath
var gConnectionsCache = {};

// Cache of all connections mapped by the
// AccountKey.  Only connections whose prefs are available
// with us are present in this mapping
// TODO: Eliminate this :)
var gConnectionsByKey = {};

// List of managers available on the system
var gTPManagers;

var gPrefService;
// IM Preferences Branch
var gPrefBranch;

// IM status service to be intimated on status changes
var gIMStatusService;

// Offset to find the unique part of the object path
const gObjectPathOffset = 37;

// Items to load before telepathy load is complete
var gTPLoadingList = [];

// Spicebird status strings to telepathy status strings
// ext_away and invisible are not part of the spec, but Haze uses them!
var gStatusStringMap = {
  'available':  ['available'],
  'away':       ['away', 'brb', 'xa', 'ext_away'],
  'busy':       ['busy', 'dnd'],
  'invisible':  ['hidden', 'invisible'],
  'offline':    ['offline']
};

// Telepathy status strings -> Spicebird status strings map
var gStatusStringReverseMap = {
  'available': 'available',
  'away':      'away',
  'brb':       'away',
  'busy':      'busy',
  'dnd':       'busy',
  'xa':        'away',
  'ext_away':  'away',
  'hidden':    'invisible',
  'invisible': 'invisible',
  'offline':   'offline'
};

// IM Global Status: All connections that
// are subscribed to the global status are in sync!
var gMyPresence = { status:'offline', message:'' };

/*
 * Status handler for telepathy
 */
var gTelepathyStatus = {
  mDoneLoading: false,
  mConnectingList: [],

  mProgressMeterContainer: null,
  mStatusBar: null,
  mStatusTextField : null,

  load: function() {
    if (this.mDoneLoading)
      return;

    this.mProgressMeterContainer = document.getElementById("statusbar-progresspanel");
    this.mStatusBar = document.getElementById("statusbar-icon");
    this.mStatusTextField = document.getElementById("statusText");

    this.mDoneLoading = true;
  },

  updateStatus: function(aIndex) {
    if (aIndex)
      // Show status of requested index
      var index = aIndex;
    else
      // Fallback to show status of last item in the list
      var index = this.mConnectingList.length - 1;

    if (index > -1) {
      this.mProgressMeterContainer.removeAttribute('collapsed');
      this.mStatusBar.setAttribute("mode","undetermined");

      this.mStatusTextField.label = this.mConnectingList[index].status;
    } else {
      this.mProgressMeterContainer.setAttribute('collapsed', true);
      this.mStatusBar.setAttribute("mode","normal");

      this.mStatusTextField.label = '';
    }
  },

  addStatus: function(aKey, aStatus) {
    var item = this.mConnectingList.filter( function(item) {return item.accountKey == aKey;} )[0];
    if (!item) {
      this.mConnectingList.push({accountKey: aKey, status: aStatus});
      var index = this.mConnectingList.length - 1;
    } else {
      var index = this.mConnectingList.indexOf(item);
      this.mConnectingList[index].status = aStatus;
    }

    this.updateStatus(index);
  },

  removeStatus: function(aKey) {
    var item = this.mConnectingList.filter( function(item) {return item.accountKey == aKey;} )[0];
    if (item)
      this.mConnectingList.splice(this.mConnectingList.indexOf(item), 1);

    this.updateStatus();
  }
};

/*
 * Initialize Telepathy
 */
function init() {
  gTPService = Components.classes["@synovel.com/collab/telepathy/service;1"]
                         .getService()
                         .QueryInterface(Components.interfaces.csITelepathyService);

  gPrefService = Components.classes['@mozilla.org/preferences-service;1']
                   .getService(Components.interfaces.nsIPrefService);

  gPrefBranch = gPrefService.getBranch('collab.im.');

  gIMStatusService = Components.classes["@synovel.com/collab/im/imstatusservice;1"]
                               .getService(Components.interfaces.csIIMStatusService);

  // Load status bar 
  gTelepathyStatus.load();

  // Initialize accounts
  // Currently the accounts are handled as part of the
  // addressbook integration
  initAccounts();
  gTPLoadingList.push('accounts');
}

/*
 * Load existing telepathy connections
 * and connection managers from the system
 */
function load() 
{
  // Retrieve the list of existing connection managers
  gTPManagers = {};
  var managerListCB = new GetInterfaceListCB();
  managerListCB.postItemsComplete = function() {
    for each (var item in this.mItems) {
      var manager = item.QueryInterface(Components.interfaces.csITPConnectionManager);
      gTPManagers[manager.name] = manager;
    }

    loadComplete('managers');

    // TODO: Add new connection observers to Connection Managers
  };
  gTPService.getManagersList(managerListCB);
  gTPLoadingList.push('managers');

  // Retrieve the list of existing connections
  gConnectionsCache = {};
  var connectionListCB = new GetInterfaceListCB();
  connectionListCB.postItemsComplete = function() {
    for each (var item in this.mItems) {
      var connection = item.QueryInterface(Components.interfaces.csITPConnection);
      var uniqueID = connection.objectPath.substr(gObjectPathOffset);
      gConnectionsCache[uniqueID] = new Connection(connection, uniqueID, false);
      gConnectionsCache[uniqueID].load();
    }

    loadComplete('connections');
  }
  gTPService.getConnectionList(connectionListCB);
  gTPLoadingList.push('connections');
}

function loadComplete(aItem)
{
  gTPLoadingList.splice(gTPLoadingList.indexOf(aItem), 1);

  if (gTPLoadingList.length == 0) {
    // Notify observers
    var observerService = Components.classes["@mozilla.org/observer-service;1"]
                                    .getService(Components.interfaces.nsIObserverService);
    observerService.notifyObservers(null, "csTPLoadComplete", null);
  }
}

function finish() {
  for each (var connection in gConnectionsCache)
    if (connection.ownConnection)
      connection.close();
}

/*
 * Connection class
 * Convenience Wrapper to the telepathy connection bindings
 */
function Connection(aConnection, aUniqueID, aOwnConnection)
{
  this.mConnection = aConnection;
  this.mUniqueID = aUniqueID;
  this.mOwnConnection = aOwnConnection == undefined? true : aOwnConnection;

  this.mAccountKey = null;
  this.mProtocol = null;
  this.mAccount = null;

  // Map of handles to contact details
  // Contact details include accountID, Alias, Presence
  // and other channels with handle type as contact.
  this.mContacts = {};

  // Shortname
  // Will be the alias, if aliasing is present
  this.mMyAlias = "";

  // Contact Lists
  this.mContactLists = [];

  // Contact Groups
  this.mContactGroups = [];

  // Interfaces and their callbacks
  this.mPresenceInterface = null;
  this.mPresenceCB = null;

  this.mAliasingInterface = null;
  this.mAliasingCB = null;
}

Connection.prototype = {

  /*
   * Get the backend connection object
   */
  get connection()
  {
    return this.mConnection;
  },

  /* 
   * Do I own the connection
   */
  get ownConnection()
  {
    return this.mOwnConnection;
  },

  /*
   * Do I support Interface.Presence
   */
  get hasPresence()
  {
    return Boolean(this.mPresenceInterface);
  },

  /*
   * Do I supporte Interface.Aliasing
   */
  get hasAliasing()
  {
    return Boolean(this.mAliasingInterface);
  },

  /* 
   * Close the connection
   * Only connections that were created inside Spicebird
   * should be closed - use ownConnection() to know it Spicebird
   * owns the connection.
   *
   * TODO: Close the channels, remove the observers and
   *       then close the connection
   */
  close: function()
  {
    var closeCB = new GetEmptyCB(this.mUniqueID,
                                 getLocaleString([['CloseConnectionError']]));
    this.mConnection.disconnect(closeCB);
  },

  /*
   * Get the status spec that best suites the
   * matching status string used in Spicebird
   *
   * We could use the types, but currently both Haze and Gabble
   * have wrong types set in the status specs.  String seem more
   * reliable!
   */
  getStatusSpec: function(aOnlineStatus)
  {
    var statuses = gStatusStringMap[aOnlineStatus];
    if (statuses) {
      for each (var status in statuses) {
        var spec = this.mPresenceStatuses[status];
        if (spec)
          return spec;
      }
    }
      
    dump("ERROR: Invalid status! We should never be here!\n");
    return null;
  },

  get systemStatus() {
    return Boolean(this.mSystemStatusObserver);
  },

  /*
   * Set the online status of the user
   */
  setOnlineStatus: function(aOnlineStatus, aStatusMessage)
  {
    if (!this.mPresenceInterface)
      return;

    if (this.mMyPresence.status == aOnlineStatus &&
        this.mMyPresence.statusMessage == aStatusMessage)
      return;

    var status = this.getStatusSpec(aOnlineStatus)

    // Close the connection if the status is being set to offline.
    // Some managers don't handle 'offline' right, so just disconnect
    if (aOnlineStatus == 'offline') {
      this.close();

    // If the status is not offline, set the
    // status and update to telepathy backend
    } else if (status) {
      this.mMyPresence.status = status.statusString;
      this.mMyPresence.statusMessage = aStatusMessage;
      this._updateStatusToBackend();
    }
  },

  /*
   * Update the status and status message to the backend
   */
  _updateStatusToBackend: function()
  {
    // {sv}: Map of string to variant for parameters
    var paramsBag = Components.classes["@mozilla.org/hash-property-bag;1"]
                              .createInstance(Components.interfaces
                                              .nsIWritablePropertyBag2);
    if (this.mMyPresence.statusMessage)
      paramsBag.setPropertyAsAString('message', this.mMyPresence.statusMessage);

    // {s{sv}}: Map of status string to the params map
    var statusBag = Components.classes["@mozilla.org/hash-property-bag;1"]
                              .createInstance(Components.interfaces
                                              .nsIWritablePropertyBag2);

    statusBag.setPropertyAsInterface(this.mMyPresence.status, paramsBag);

    this.mPresenceInterface.setStatus(statusBag, this.mPresenceCB);
  },

  /*
   * Update the contacts list to addressbook.
   */
  updateRoster: function(handleList)
  {
    var abookOperations = [];

    for each (var handle in handleList) {
      var contact = {};
      contact.address = this.mContacts[handle].account;
      contact.alias = this.mContacts[handle].alias;

      var operation = {};
      switch (this.mContacts[handle].subscribe) {
        case 'both':
          operation.action = 'add';
          operation.contact = contact;
          // Include in address book entry changes list
          abookOperations.push(operation);
          break;

        case 'remove':
          operation.action = 'remove';
          operation.contact = contact;
          // Include in address book entry changes list
          abookOperations.push(operation);

          // Remove contact from connection instance
          this.cleanupContact(handle);
          break;
      };
    }

    // Update address book entries
    if (this.mAccountKey != undefined)
      modifyIMAddrBook(this.mAccountKey, this.mAccount, abookOperations);

  },

  /*
   * Remove member from contacts list
   */
  removeContactListMember: function(aHandle)
  {
    var emptyCB = new GetEmptyCB(this.mUniqueID, '');
    emptyCB.onError = function() {};

    var group = this.mContactLists['publish'];
    if (group)
      group.removeMembers(1, [aHandle], '', emptyCB);

    group = this.mContactLists['subscribe'];
    if (group)
      group.removeMembers(1, [aHandle], '', emptyCB);
  },

  /*
   * Add member to contact list
   */
  addContactListMember: function(aHandle, aAddToPublish)
  {
    var group = this.mContactLists['subscribe'];
    group.addMembers(1, [aHandle], '',
                     new GetEmptyCB(this.mUniqueID,
                                    getLocaleString([['AddContactError']])));

    if (aAddToPublish) {
      group = this.mContactLists['publish'];
      group.addMembers(1, [aHandle], '',
                       new GetEmptyCB(this.mUniqueID,
                                      getLocaleString([['AddContactError']])));
    }
  },

  /*
   * Get aliases for contacts
   */
  getAliases: function(aHandleList)
  {
    var handleList;
    if (aHandleList) {
      handleList = aHandleList;
    } else {
      handleList = [];
      for (var handle in this.mContacts)
        handleList.push(handle);
    }

    // TODO - fix telepathy-glib
    // Ideally we should be calling GetAliases
    // to get the cached aliases, but the function
    // is currently not implemented!

    var requestAliasesCB = {
      mAliasingCB: this.mAliasingCB,

      onRequestAliasesError: function(aErrorCode)
      {
        this.mAliasingCB.onRequestAliasesError(aErrorCode);
      },

      onRequestAliasesResult: function(aAliasesArray)
      {
        if (handleList.length > 0 &&
            handleList.length == aAliasesArray.length)
          this.mAliasingCB.parseAliasesArray(handleList, aAliasesArray);
      }
    };
    this.mAliasingInterface.requestAliases(handleList.length,
                                           handleList, requestAliasesCB);
  },

  /*
   * Set alias for a contact
   */
  setContactAlias: function(aContactAccount, aNewAlias)
  {
    if (!this.mSetContactAlias) {
      // TODO
      dump('INFO: Cannot set aliases on this connection\n');
      displayAlert(getLocaleString([['SetAliasDisabledError']]), null, this.mUniqueID);
      return;
    }

    var contactHandle = this.findContact(aContactAccount);
    if (contactHandle == -1) {
      // TODO
      dump('INFO: ' + aContactAccount + ' does not exist in account ' + this.mAccount + '. Cannot set alias\n');
      return;
    }

    var handleAlias = new GetHandleAliasPair(contactHandle, aNewAlias);
    var handleAliasArray = Components.classes["@mozilla.org/array;1"].createInstance(Components.interfaces.nsIMutableArray);
    handleAliasArray.appendElement(handleAlias, false);

    var setAliasesCB = {
      mConnectionID: this.mUniqueID,

      onSetAliasesError: function(aErrorCode) {
        // TODO
        dump('ERROR: setAliases - ' + aErrorCode + '\n');
        displayAlert(getLocaleString([['SetAliasError'], ['telepathy.error.' + aErrorCode]]),
                     getLocaleString([['ConnectionErrorTitle']]), this.mConnectionID);
      },

      onSetAliasesComplete: function() {}
    };
    
    try {
      var connectionAliasing = this.mConnection.QueryInterface(Components.interfaces.csITPConnectionAliasing);
      connectionAliasing.setAliases(handleAliasArray, setAliasesCB);
    } catch(ex) {
      // TODO
      dump('Could not set an alias: ' + ex + '\n');
    }
  },

  /*
   * Initiates loading the connection.
   * Gets the self handle, inspects it and checks
   * if we have an account configured for it
   */
  load: function()
  {
    var selfHandleCB = new GetIntegerCB(this.mUniqueID, getLocaleString([['LoadConnectionError']]));

    selfHandleCB.postGotValue = function() {
      var selfHandle = this.mInteger;
      var handleType = Components.interfaces.csITPConnection.Handle_Type_Contact;
      var handleList = [ this.mInteger ];
      var handleListCB = new GetHandlesCB(this.mConnectionID, handleType);

      handleListCB.postItemsComplete = function() {
        var oConnection = gConnectionsCache[this.mConnectionID];
        var account = this.mHandleStringMap[selfHandle];
        var oAccount = getAccount(account);
        if (oAccount) {
          oConnection.mAccountKey = oAccount.key;
          oConnection.mProtocol = oAccount.protocol;
          gConnectionsByKey[oAccount.key] = oConnection;
        } else {
          var protocolCB = {
            connection: oConnection,
            onError: function() {},
            onGotValue: function(aProtocolString) {
              this.connection.mProtocol = aProtocolString;
            }
          }
          oConnection.mConnection.getProtocol(protocolCB);
        }

        oConnection.mAccount = account;
        oConnection.mMyAlias = account.split("@")[0];
        oConnection.mSelfHandle = selfHandle;
        oConnection._loadImpl();
      }
      var connection = gConnectionsCache[this.mConnectionID].mConnection;
      connection.inspectHandles(handleType, handleList.length, handleList, handleListCB);
    }
    this.mConnection.getSelfHandle(selfHandleCB);
  },

  /*
   * Actually load the connection
   * Called by the 'load' function on getting the self handle
   */
  _loadImpl: function() 
  {
    // TODO: We should also consider the connecting state.
    if (this.mConnection.status != Components.interfaces
                                             .csITPConnection
                                             .Status_Connected) {
      // TODO
      displayAlert(getLocaleString([['LoadConnectionError']]),
                   getLocaleString([['ConnectionErrorTitle']]), this.mUniqueID);
      return;
    }
  
    // TODO
    gTelepathyStatus.addStatus(this.mAccountKey, getLocaleString([['FetchingAccountDetailsMessage', this.mAccount]]));

    // Add status change observer
    this.mStatusChangeObserver = new GetStatusChangeObserver(this.mUniqueID);
    this.mConnection.addStatusChangeObserver(this.mStatusChangeObserver);

    var ci = Components.interfaces;

    // Initialize the presence handling.
    // A connection may not always support presence
    // so quitely ignore if it does not support!

    try {
      this.mPresenceInterface = this.mConnection
                                    .QueryInterface(ci.csITPConnectionPresence);
    
      // all-in-one callback for presence interface
      this.mPresenceCB = new GetConnectionPresenceCB(this);

      // The connections current presence information.
      // Start with being offline and null message
      this.mMyPresence = {status: 'offline', statusMessage: ''};

      // Add presence update observer
      this.mPresenceInterface.addPresenceUpdateObserver(this.mPresenceCB);
    
      // Get valid presence statuses
      this.mPresenceStatuses = [];
      this.mPresenceInterface.getStatuses(this.mPresenceCB);

      // Get self presence
      var requestPresenceCB = {
        mConnectionID: this.mUniqueID,
        
        onRequestPresenceError: function(aErrorCode) {
          // TODO
          dump('ERROR: when requested presence of self - ' + aErrorCode + '\n');
          displayAlert(getLocaleString([['LoadConnectionError'], ['telepathy.error.' + aErrorCode]]),
                       getLocaleString([['ConnectionErrorTitle']]), this.mConnectionID);
        },
    
        // Request also causes a presence update to be called
        // and that update is handled by the PresenceUpdateObserver
        onRequestPresenceComplete: function() {
          var oConnection = gConnectionsCache[this.mConnectionID];
          var loadWithPresence = oConnection.mLoadWithPresence;
          if (loadWithPresence) {
            oConnection.setOnlineStatus(loadWithPresence.status,
                                        loadWithPresence.statusMessage);
          }

          // Now that we have our presence,
          // let the world know that a connection got created!
          Components.classes["@mozilla.org/observer-service;1"]
                    .getService(Components.interfaces.nsIObserverService)
                    .notifyObservers(null, "im-connection-status", oConnection.mAccount);
        }
      };
      this.mConnection.requestPresence(1, [this.mSelfHandle],
                                       requestPresenceCB);

    } catch (ex) {}


    // Initialize the aliases handling.
    // A connection may not always support aliasing
    // so quitely ignore if it does not support!

    try {
      this.mAliasingInterface = this.mConnection
                                    .QueryInterface(ci.csITPConnectionAliasing);

      // all-in-one callback for aliasing interface
      this.mAliasingCB = new GetConnectionAliasingCB(this);

      // Add aliasing update observer
      this.mAliasingInterface.addAliasesChangedObserver(this.mAliasingCB);

      // Aliasing flags, can the user set aliases for
      // other users in my contact lists? Default to False.
      this.mSetContactAlias = false;
      this.mAliasingInterface.getAliasFlags(this.mAliasingCB);

    } catch (ex) {}


    // Initialize the avatars handling.
    // A connection may not always support avatars
    // so quitely ignore if it does not support!

    try {
      // TODO
    } catch (ex) {}


    // Handle channels
    // Usually ContactList channels like subscribe, publish exist as
    // soon as the connection is created.

    // Get existing Channels - contacts, text
    var channelListCB = new GetInterfaceListCB(this.mUniqueID);
    channelListCB.mConnectionID = this.mUniqueID;
    channelListCB.postItemsComplete = function() {
      for each (var item in this.mItems) {
        var channel = item.QueryInterface(Components.interfaces.csITPChannel);
        var channelReadyObserver = new GetChannelReadyObserver(this.mConnectionID, channel, false /*isUserTriggered*/);
        channel.addChannelReadyObserver(channelReadyObserver);
      }
    }
    this.mConnection.getChannelsList(channelListCB);

    // Add new channel observer
    var newChannelObserver = new GetNewChannelObserver(this.mUniqueID);
    newChannelObserver.postGotValue = function() {
      this.handleNewChannel(false);
    };
    this.mConnection.addNewChannelObserver(newChannelObserver);
  },

  /*
   * addContactListChannel
   * This function is called from within the channel ready observer
   * to initiate loading of contacts into Spicebird
   */
  addContactListChannel: function(aChannel)
  {
    var channel = aChannel.QueryInterface(Components.interfaces.csITPChannelGroup);
    var type = channel.targetHandleType;
    var handle = channel.targetHandle;

    switch(type) {
      // Handle_Type_List indicates a server created list.
      // The list should first be introspected to determine
      // the string name/type of the list
      //
      //  1. subscribe: Users for whom we recieve presence
      //  2. publish: Users to whom we publish our presence
      //  3. hide: Users from "publish" list who are temporarily blocked
      //  4. allow: Contacts who may send us messages
      //  5. deny: Contacts who many not send us messages
      case Components.interfaces.csITPConnection.Handle_Type_List:
        var handleListCB = new GetHandlesCB(this.mUniqueID, type);
        handleListCB.postItemsComplete = function() {
          var name = this.mHandleStringMap[handle];
          if (name) {
            var oConnection = gConnectionsCache[this.mConnectionID];
            oConnection.mContactLists[name] = channel;

            // Load contacts. Two lists of primary interest are
            // the "publish" channel for its 'localPending' contacts and
            // the "subscribe" channel for the main contact list and the
            // 'remotePending' list.  So we add observers to both these
            // channels and handle them accordingly

            if (name == 'subscribe' || name == 'publish') {
              var contactList = channel;
              if (!contactList)
                return;
             
              var membersListCB = new GetMembersListCB(this.mConnectionID, name);
              membersListCB.postItemsComplete = function()
              {
                // Ugly hack for a few jabber servers on Haze
                // The ChannelReady signal is emitted too early!
                if (this.mAddMembers.length == 0) {
                  if (!this.mSecondTry) {
                    this.mSecondTry = true;
                    var self = this;
                    setTimeout(function() {contactList.getAllMembers(self)}, 10000);
                    return;
                  } else
                    gTelepathyStatus.removeStatus(gConnectionsCache[this.mConnectionID].mAccountKey);
                }

                var membersChangeObserverCB = new GetMembersListCB(this.mConnectionID,
                                                                   this.mChannelID);
                contactList.addMembersChangeObserver(membersChangeObserverCB);
              }
             
              // Let the loading happen slightly later (better load time?)
              setTimeout(function() {contactList.getAllMembers(membersListCB)}, 0);
            }
          }
        }
        this.mConnection.inspectHandles(type, 1, [handle], handleListCB);
        break;

      // Handle_Type_Group indicates
      // that this is a user created contact group
      case Components.interfaces.csITPConnection.Handle_Type_Group:
      default:
        break;
    }
  },

  /*
   * Add contact to contactList
   */
  addContact: function(aContactAccount) {
    var contactHandle = this.findContact(aContactAccount);
    if (contactHandle != -1)
      return;

    var handleType = Components.interfaces.csITPConnection.Handle_Type_Contact;
    var handleListCB = new GetHandlesCB(this.mUniqueID, handleType);
    handleListCB.mContactAccount = aContactAccount;
    handleListCB.postItemsComplete = function() {
      var contactHandle;
      // Find the handle for the aContactAccount
      for (var handle in this.mHandleStringMap) {
        if (this.mHandleStringMap[handle] == this.mContactAccount) {
          contactHandle = handle;
          break;
        }
      }

      if (!contactHandle) {
        // TODO
        dump('ERROR: Cannot add contact ' + this.mContactAccount + '. Did not get handle.\n');
        displayAlert(getLocaleString([['AddContactError']]),
                     getLocaleString([['ConnectionErrorTitle']]), this.mConnectionID);
        return;
      }

      // Add handle as member of contact list
      gConnectionsCache[this.mConnectionID].addContactListMember(contactHandle);
    }
    this.mConnection.requestHandles(handleType, 1, [aContactAccount], handleListCB);
  },

  // Remove contact from contactList
  removeContact: function(aContactAccount) {
    var contactHandle = this.findContact(aContactAccount);
    if (contactHandle == -1) {
      dump('INFO: ' + aContactAccount + ' does not exist in account ' + this.mAccount + '\n');
      displayAlert(getLocaleString([['RemoveContactError'], ['ContactDoesNotExistError', aContactAccount]]),
                   getLocaleString([['ConnectionErrorTitle']]), this.mUniqueID);
      return;
    }

    // Remove handle as member of contact list
    this.removeContactListMember(contactHandle);
  },

  findContact: function(aContactAccount) {
    for (var handle in this.mContacts)
      if (this.mContacts[handle].account &&
          this.mContacts[handle].account == aContactAccount)
        return handle;

    return -1;
  },

  // Add a new contact object for this handle
  newContact: function(aHandle) {
    // Add contact as offline
    this.mContacts[aHandle] = {handle: aHandle, status: 'offline', statusMessage: ''};
  },

  // Cleanup existing contact for this handle
  cleanupContact: function(aHandle) {
    if (!this.mContacts[aHandle])
      return; // Nothing to do

    // Ensure contact is removed from IM tab sidebar
    this.updateContact(aHandle, {status: 'remove', statusMessage: ''});

    delete this.mContacts[aHandle];
  },

  updateContactStatus: function(aHandle) {
    var contactObj = Components.classes["@synovel.com/collab/im/imcontact;1"]
                               .createInstance(Components.interfaces.csIIMContact);
    contactObj.connectionID = this.mUniqueID;
    contactObj.account = this.mAccount;
    contactObj.id = this.mContacts[aHandle].account;
    contactObj.alias = this.mContacts[aHandle].alias;
    contactObj.status = this.mContacts[aHandle].status;
    contactObj.statusMessage = this.mContacts[aHandle].statusMessage;

    gIMStatusService.setContactStatus(contactObj);
  },

  updateSelfStatus: function(aPropertyMap) {
      
    for (var property in aPropertyMap)
      this.mMyPresence[property] = aPropertyMap[property];

    var contactObj = Components.classes["@synovel.com/collab/im/imcontact;1"]
                               .createInstance(Components.interfaces.csIIMContact);
    contactObj.connectionID = this.mUniqueID;
    contactObj.account = this.mAccount;
    contactObj.id = this.mAccount;
    contactObj.alias = this.mMyAlias;
    contactObj.status = this.mMyPresence.status;
    contactObj.statusMessage = this.mMyPresence.statusMessage;

    // Let the world know that the status of a connection changed
    Components.classes["@mozilla.org/observer-service;1"]
              .getService(Components.interfaces.nsIObserverService)
              .notifyObservers(null, "im-connection-status", this.mAccount);

    // Let im service know about it too :)
    gIMStatusService.setContactStatus(contactObj);
  },

  updateContact: function(aHandle, aPropertyMap) {
    if (!this.mContacts[aHandle])
      this.newContact(aHandle);

    // Shield ourselves from requests that don't
    // change any field on the contact.
    var changed = false;
    for (var property in aPropertyMap) {
      if (typeof(this.mContacts[aHandle][property]) == 'undefined' ||
          this.mContacts[aHandle][property] != aPropertyMap[property]) {
        this.mContacts[aHandle][property] = aPropertyMap[property];
        changed = true;
      }
    }

    if (changed && this.mContacts[aHandle].account)
      this.updateContactStatus(aHandle);
  },

  getPresence: function(aHandleList) {
    if (!this.mPresenceInterface)
      return;

    var handleList;
    if (aHandleList) {
      handleList = aHandleList;
    } else {
      handleList = [];
      for (var handle in this.mContacts)
        handleList.push(handle);
    }

    // Get Presence does not trigger presence update
    this.mPresenceInterface.getPresence(handleList.length,
                                        handleList, this.mPresenceCB);
  },

  // TODO: This function needs a revisit
  cleanup: function() {
    if (gConnectionsCache[this.mUniqueID])
      delete gConnectionsCache[this.mUniqueID];

    if (this.mAccountKey && gConnectionsByKey[this.mAccountKey])
      delete gConnectionsByKey[this.mAccountKey];
  },

  handleSubscriptionRequest: function(aHandle) {
    var aContactAccount = this.mContacts[aHandle].account;
    var result = gIMPromptService.confirmEx(null, 
                   getLocaleString([["ConfirmAuthorizeContactTitle"]]),
                   getLocaleString([["ConfirmAuthorizeContactInfo", 
                                     aContactAccount, oConnection.mAccount]]),
                   (gPromptService.BUTTON_TITLE_IS_STRING * gPromptService.BUTTON_POS_0) +
                   (gPromptService.BUTTON_TITLE_IS_STRING * gPromptService.BUTTON_POS_1) +
                   (gPromptService.BUTTON_TITLE_IS_STRING * gPromptService.BUTTON_POS_2),
                   getLocaleString([["AuthorizeContactAllow"]]), 
                   getLocaleString([["AuthorizeContactLater"]]), 
                   getLocaleString([["AuthorizeContactDeny"]]), 
                   null, {value: 0});

    if (result == 0)
      this.addContactListMember(aHandle, true);
    else if (result == 2)
      this.removeContactListMember(aHandle);
    // else leave contact aHandle in 'local-pending' list
  }
}

function GetConnectionPresenceCB(aOConnection) {
  this.mOConnection = aOConnection;

  /*
   * Converts org.freedesktop.Telepathy.Connection.Interface.Presence
   * to org.freedesktop.Telepathy.Connection.Interface.SimplePresence
   */
  this.getSimplePresence = function(aPresence)
  {
    // aPresence => csITPPresenceInfo
    // - handle, lastActivityTime, currentStatuses => nsIArray[csITPPresenceStatus]
    //                             - statusString, optParams => nsIPropertyBag
    //                                             - key, value pairs

    var statusCount = aPresence.currentStatuses.length;
    // SimplePresence has only one status
    if (statusCount > 1) {
      dump('WARNING: Will not handle multiple statuses. Will ignore all statuses after first one.\n');
    }

    var presenceStatus = aPresence.currentStatuses.queryElementAt(0, Components.interfaces.csITPPresenceStatus);
    var statusMessage;
    try {
      statusMessage = presenceStatus.optParams.getProperty('message');
    } catch(ex) {
      // To reset existing status message
      statusMessage = '';
    }

    return { 
      status: gStatusStringReverseMap[presenceStatus.statusString],
      statusMessage: statusMessage
    };
  },

  this.parsePresenceArray = function(aPresenceArray)
  {
    // aPresenceArray => nsIArray[csITPPresenceInfo]

    var presenceCount = aPresenceArray.length;
    var presence;
    for (var index = 0; index < presenceCount; ++index) {
      presence = aPresenceArray.queryElementAt(index, Components.interfaces.csITPPresenceInfo);

      var simplePresence = this.getSimplePresence(presence);
      // Check if it is self presence update
      if (presence.handle == this.mOConnection.mSelfHandle)
        this.mOConnection.updateSelfStatus(simplePresence);
      else
        this.mOConnection.updateContact(presence.handle, simplePresence);
    }
  };

  this.onPresenceUpdate = function(aPresenceArray)
  {
    this.parsePresenceArray(aPresenceArray);
  };

  this.onGetPresenceError = function(aErrorCode)
  {
    dump("ERROR: onGetPresenceError - " + aErrorCode + '\n');
    displayAlert(getLocaleString([['LoadConnectionError'], ['telepathy.error.' + aErrorCode]]),
                 getLocaleString([['ConnectionErrorTitle']]), this.mOConnection.mUniqueID);

    gTelepathyStatus.removeStatus(this.mOConnection.mAccountKey);
  };

  this.onGetPresenceResult = function(aPresenceArray)
  {
    this.parsePresenceArray(aPresenceArray);

    gTelepathyStatus.removeStatus(this.mOConnection.mAccountKey);
  };

  // csITPPresenceGetStatusesCB
  this.onGetStatusesError = function(aErrorCode)
  {
    dump("ERROR: onGetStatusesError - " + aErrorCode + '\n');
    displayAlert(getLocaleString([['LoadConnectionError'], ['telepathy.error.' + aErrorCode]]),
                 getLocaleString([['ConnectionErrorTitle']]), this.mOConnection.mUniqueID);
  };

  this.onGetStatusesResult = function(aStatusSpecsArray)
  {
    this.parseStatusSpecsArray(aStatusSpecsArray);
  };

  this.parseStatusSpecsArray = function(aArray)
  {
    // aStatusSpecsArray => nsIArray[csITPPresenceStatusSpec]
    // csITPPresenceStatusSpec
    // - statusString, type, maySetOnSelf, isExclusive, parameters
    // parameters
    // - param name, param type

    var count = aArray.length;
    for (var i = 0; i < count; ++i) {
      var spec = aArray.queryElementAt(i, Components.interfaces
                                                    .csITPPresenceStatusSpec);
      this.mOConnection.mPresenceStatuses[spec.statusString] = spec;
    }
  };

  this.onAddStatusError = function(aErrorCode)
  {
    dump("ERROR: onAddStatusError - " + aErrorCode + '\n');
    displayAlert(getLocaleString([['SetStatusError'], ['telepathy.error.' + aErrorCode]]),
                 getLocaleString([['ConnectionErrorTitle']]), this.mOConnection.mUniqueID);
  };

  this.onAddStatusComplete = function() {};

  this.onSetStatusError = function(aErrorCode)
  {
    dump("ERROR: onSetStatusError - " + aErrorCode + '\n');
    displayAlert(getLocaleString([['SetStatusError'], ['telepathy.error.' + aErrorCode]]),
                 getLocaleString([['ConnectionErrorTitle']]), this.mOConnection.mUniqueID);
  };

  this.onSetStatusComplete = function() {};
}


function GetConnectionAliasingCB(aOConnection)
{
  this.mOConnection = aOConnection;
  this.mHandleList = [];

  this.onRequestAliasesError = function(aErrorCode)
  {
    displayAlert(getLocaleString([['LoadConnectionError'], ['telepathy.error.' + aErrorCode]]),
                 getLocaleString([['ConnectionErrorTitle']]), this.mConnectionID);
    gTelepathyStatus.removeStatus(this.mOConnection.mAccountKey);
  };

  this.onRequestAliasesResult = function(aAliasesArray)
  {
    if (this.mHandleList.length > 0 &&
        this.mHandleList.length == aAliasesArray.length) {
      this.parseAliasesArray(this.mHandleList, aAliasesArray);
    } else {
      /* TODO */
      dump('ERROR: inconsistency with input handles & returned aliases list\n');
      displayAlert(getLocaleString([['LoadConnectionError']]),
                   getLocaleString([['ConnectionErrorTitle']]), this.mConnectionID);
    }
  };

  this.parseAliasesArray = function(aHandleList, aArray)
  {
    var count = aArray.length;

    for (var i = 0; i < count; i++ ) {
      var alias = aArray.queryElementAt(i, Components.interfaces.nsIVariant);
      this.mOConnection.updateContact(aHandleList[i], { alias: alias });
    }

    // Update Roster Information
    this.mOConnection.updateRoster(aHandleList);
  };

  this.onAliasesChanged = function(aArray)
  {
    this.parseHandleAliasesPairArray(aArray);
  };

  this.parseHandleAliasesPairArray = function(aArray)
  {
    var count = aArray.length;
    for (var i = 0; i < count; ++i) {
      var alias = aArray.queryElementAt(i, Components.interfaces
                                                .csITPAliasingHandleAliasPair);

      if (this.mOConnection.mSelfHandle == alias.handle)
        this.mOConnection.mMyAlias = alias.alias;

      this.mOConnection.updateContact(alias.handle, { alias: alias.alias });
    }
  };

  this.onGetAliasFlagsError = function(aErrorCode)
  {
    // TODO
    dump('ERROR: getAliasFlags - ' + aErrorCode + '\n');

    displayAlert(getLocaleString([['LoadConnectionError'], ['telepathy.error.' + aErrorCode]]),
                 getLocaleString([['ConnectionErrorTitle']]), this.mOConnection.mUniqueID);
  };
  
  this.onGetAliasFlagsResult = function(aAliasFlags)
  {
    this.mOConnection.mSetContactAlias = Boolean(
                aAliasFlags &
                Components.interfaces
                          .csITPConnectionAliasing.Alias_Flag_User_Set
    );
  };
}

/*
 * Helper classes
 */
function GetHandleAliasPair(aHandle, aAlias) {
  this._handle = aHandle;
  this._alias  = aAlias;
};

GetHandleAliasPair.prototype = {
  get handle() {return this._handle;},

  get alias() {return this._alias;},

  QueryInterface: function(aIID) {
    if (!aIID.equals(Components.interfaces.csITPAliasingHandleAliasPair) &&
        !aIID.equals(Components.interfaces.nsISupports))
      throw Components.results.NS_ERROR_NO_INTERFACE;
    return this;
  }
};

/*
 * GetChannelReadyObserver
 *
 * Handles the channel ready events and takes action based on the
 * channel type
 *
 * @aConnectionID is the connection's unique ID
 * @aChannel is the channel object on which the ready signal is emitted
 * @isUserTriggered indicates if the event was triggered by the user
 */
function GetChannelReadyObserver(aConnectionID, aChannel, isUserTriggered)
{
  this.mConnectionID = aConnectionID;
  this.mChannel = aChannel;
  this.mIsUserTriggered = isUserTriggered;

  // An error occurred when waiting for the channel to be ready
  this.onError = function(aErrorCode)
  {
    dump('ERROR: channelReadyObserver - ' + aErrorCode + '\n');
    displayAlert(getLocaleString([['telepathy.error.' + aErrorCode]]),
                 getLocaleString([['ChannelErrorTitle']]), this.mConnectionID);
  };

  // The channel is ready, take necessary action
  this.doAction = function()
  {
    var channel = this.mChannel;
    var channelType = channel.channelType.split(".")[5];
    var oConnection = gConnectionsCache[this.mConnectionID];

    switch (channelType) {
      // ContactList channels implement the group interface
      // and hold the server contact lists as well as the user
      // defined contact groups
      case "ContactList":
        oConnection.addContactListChannel(channel);
        break;

      // Text channels implement the plain text messaging
      // in Telepathy. Based on the targetHHandleType the chat
      // is either single user or multi-user
      case "Text":
        channel = channel.QueryInterface(Components.interfaces.csITPTextChannel);
       
        if (channel.targetHandleType == Components.interfaces
                                                  .csITPConnection
                                                  .Handle_Type_Contact) {
          // Link created channel to the user
          oConnection.updateContact(channel.targetHandle, {TextChannel: channel});
          var userAccount = oConnection.mAccount;
       
          // TODO
          // Currently conversation manager requires
          // the contact accountID.  This should change to handle
          // in place of accountID.

          if (oConnection.mContacts[channel.targetHandle] &&
              oConnection.mContacts[channel.targetHandle].account) {
            var contactAccount = oConnection.mContacts[channel.targetHandle].account;
            gConversationManager.startConversation(userAccount,
                                                   contactAccount, channel,
                                                   this.mIsUserTriggered);
          } else {
            var handleListCB = new GetHandlesCB(this.mConnectionID,
                                                channel.targetHandleType);
            handleListCB.mIsUserTriggered = this.mIsUserTriggered;
            handleListCB.postItemsComplete = function() {
              var contactAccount = this.mHandleStringMap[channel.targetHandle];
              gConversationManager.startConversation(userAccount,
                                                     contactAccount, channel,
                                                     this.mIsUserTriggered);
            }
            oConnection.mConnection.inspectHandles(channel.targetHandleType, 1,
                                                   [channel.targetHandle],
                                                   handleListCB);
          }
        }
        break;

      // Telepathy also supports multimedia and tubes channels
      // TODO: Spicebird does not currently implement them
      default:
        break;
    }
  };
}

function GetNewConnectionCB(aKey) {
  this.mItem = null;
  this.mAccountKey = aKey;

  this.onGotValue = function(aSupportsItem) {
    this.mItem = aSupportsItem;
    this.postGotValue();
  }

  this.postGotValue = function() {
    // To be overwritten when instantiated
  }

  this.onError = function(aErrorCode) {
    gTelepathyStatus.removeStatus(this.mAccountKey);

    var errorString = getLocaleString([['CreateConnectionError'], ['telepathy.error.' + aErrorCode]]);

    var oAccount = getAccountByKey(this.mAccountKey);
    if (oAccount)
      errorString += '\n\n' + getLocaleString([['AccountMessage', oAccount.account + '/' + oAccount.protocol]]);

    // TODO: If password is not supplied during login, 
    // Components.interfaces.csITelepathyService.Error_InvalidArgument error occurs.
    // In this case, instead of an error prompt, show the error in console.
    if (aErrorCode != Components.interfaces.csITelepathyService.Error_InvalidArgument)
      displayAlert(errorString, getLocaleString([['ConnectionErrorTitle']]));
    else
      Components.utils.reportError(errorString);

    dump("ERROR: GetNewConnectionCB callback - " + errorString + '\n');
  }
}

function removePasswordFromManager(aAccountKey) {
  var oAccount = getAccountByKey(aAccountKey);
  var passwordManager = Components.classes["@mozilla.org/login-manager;1"]
                             .getService(Components.interfaces.nsILoginManager);

  var nsLoginInfo = new Components.Constructor(
                                "@mozilla.org/login-manager/loginInfo;1",
                                Components.interfaces.nsILoginInfo, "init");
          
  var loginInfo = new nsLoginInfo(oAccount.url, null, oAccount.url,
                                  oAccount.account, null, "", "");

  try {
    passwordManager.removeLogin(oAccount.url, oAccount.account);
  } catch (ex) { /* The entry may not be present in the password manager */ }
}

function promptPassword(aAccountKey) {
  var oAccount = getAccountByKey(aAccountKey);

  var password = {value: ""};
  var check = {value: false};
  var result = gIMPromptService.promptPassword(null, 
                 getLocaleString([['PasswordRequiredTitle']]), 
                 getLocaleString([['PasswordRequiredMessage', 
                                   oAccount.account + '/' + oAccount.protocol]]), 
                 password, getLocaleString([['RememberPasswordMessage']]), check);

  // Check if ok pressed
  if (result) {
    // Check if remember password requested
    if (check.value) {
      // Store to password manager
      storePasswordToManager(oAccount.url, oAccount.account, password.value);
    }
  } else
    // Ensures the password will not be prompted again
    throw Components.results.NS_ERROR_FAILURE;

  return password.value;
}

function storePasswordToManager(aUrl, aAccount, aPassword) {
  var passwordManager = Components.classes["@mozilla.org/login-manager;1"]
                             .getService(Components.interfaces.nsILoginManager);

  var nsLoginInfo = new Components.Constructor(
                                "@mozilla.org/login-manager/loginInfo;1",
                                Components.interfaces.nsILoginInfo, "init");

  var loginInfo = new nsLoginInfo(aUrl, null, aUrl, aAccount, aPassword, "", "");

  try {
    passwordManager.addLogin(loginInfo);
  } catch (ex) {
    dump('ERROR: when storing password. ' + ex + '\n');
  }
}

function GetInterfaceListCB(aConnectionID) {
  this.mConnectionID = aConnectionID;
  this.mItems = [];

  this.onAddItem = function(aSupportsItem) {
    this.mItems.push(aSupportsItem);
  }

  this.onItemsComplete = function() {
    this.postItemsComplete();
  }

  this.postItemsComplete = function() {
    // To be overwritten when instantiated
  }

  this.onError = function(aErrorCode) {
    dump("ERROR: interface list callback - " + aErrorCode + '\n');
    displayAlert(getLocaleString([['LoadConnectionError'], ['telepathy.error.' + aErrorCode]]),
                 getLocaleString([['ConnectionErrorTitle']]), this.mConnectionID);
  }
}

function GetIntegerCB(aConnectionID, aDebugStr) {
  this.mConnectionID = aConnectionID;
  this.mInteger = null;
  this.mDebugStr = aDebugStr;

  this.onError = function(aErrorCode) {
    dump("ERROR: Integer callback - " + aErrorCode + '\n');
    displayAlert(this.mDebugStr + '\n' + getLocaleString([['telepathy.error.' + aErrorCode]]));
  }

  this.onGotValue = function(aItem) {
    this.mInteger = aItem;
    this.postGotValue();
  }

  this.postGotValue = function() {
  }
}

function GetParamsCB(aPrefKey) {
  this.mPrefKey = aPrefKey;

  this.mPrefBranch = Components.classes["@mozilla.org/preferences-service;1"]
                               .getService(Components.interfaces.nsIPrefService)
                               .getBranch("collab.im.accounts." + aPrefKey + ".");

  this.getValueFor = function(aParamName, aParamSignature) {
    var value = null;
    try {
      switch (aParamSignature) {
        case 's':
          value = this.mPrefBranch.getCharPref(aParamName);
          break;
        case 'b':
          value = this.mPrefBranch.getBoolPref(aParamName);
          break;
        case 'q':
        case 'n':
        case 'i':
          value = this.mPrefBranch.getIntPref(aParamName);
          break;
        case 'u':
        case 't':
        case 'x':
        case 'd':
          value = new Number(this.mPrefBranch.getCharPref(aParamName));
          break;
        default:
          value = this.mPrefBranch.getCharPref(aParamName);
      }
    } catch (ex) {
      throw Components.results.NS_ERROR_FAILURE;
    }
    return value;
  };

  this.getSecretValueFor = function(aParamName, aParamSignature) {
    try {
      var password = '';

      var oAccount = getAccountByKey(this.mPrefKey);
      var url = oAccount.url;
      var account = oAccount.account;

      try {
        // Get Login Manager 
        var loginManager = Components.classes["@mozilla.org/login-manager;1"]
                             .getService(Components.interfaces.nsILoginManager);
          
        // Find users for the given parameters
        var logins = loginManager.findLogins({}, url, null, url);
      
        // Find user from returned array of nsILoginInfo objects
        for (var i = 0; i < logins.length; i++) {
           if (logins[i].username == account) {
              password = logins[i].password;
              break;
          }
        }
      }
      catch(ex) {
         // This will only happen if there is no nsILoginManager component class
      }

      while (!password)
        password = promptPassword(this.mPrefKey);

      return password;
    } catch (ex) {
      throw Components.results.NS_ERROR_FAILURE;
    }
  };
}

function GetConnectionReadyObserver(aConnectionID) {
  this.mConnectionID = aConnectionID;

  this.onError = function(aErrorCode) {
    dump("ERROR: connection ready CB - " + aErrorCode + "\n");
    displayAlert(getLocaleString([['CreateConnectionError'], ['telepathy.error.' + aErrorCode]]),
                 getLocaleString([['ConnectionErrorTitle']]), this.mConnectionID);

    gTelepathyStatus.removeStatus(gConnectionsCache[this.mConnectionID].mAccountKey);
  };

  this.doAction = function() {
    var oConnection = gConnectionsCache[this.mConnectionID];

    if (oConnection.connection.status !=
        Components.interfaces.csITPConnection.Status_Connected) {

      var status = oConnection.connection.status;
      dump('ERROR: connection not in connected status. status: ' + status + '\n');

      var statusReason = oConnection.connection.statusReason;
      var errorString = getLocaleString([['connection.status.reason.' + statusReason]]);
      if (!errorString)
        errorString = getLocaleString([['connection.status.reason.generic']]);

      displayAlert(errorString,
                   getLocaleString([['ConnectionErrorTitle']]), this.mConnectionID);

      var accountKey = oConnection.mAccountKey;

      // Cleanup the connection.
      gTelepathyStatus.removeStatus(accountKey);
      oConnection.cleanup();

      if (oConnection.connection.statusReason == Components.interfaces.csITPConnection.Reason_Authentication_Failed) {
        removePasswordFromManager(accountKey);
        checkAndCreateConnection(accountKey);
      }

      return;
    }

    // Check if requested to login with a status other than online
    if (gMyPresence.status != 'available') {
      var presenceInterface = 
        oConnection.connection.QueryInterface(
          Components.interfaces.csITPConnectionPresence);

      var presenceCB = {
        onSetStatusError: function(aErrorCode) {
          dump('INFO: Cannot set status before connecting. Error - ' +
               aErrorCode + '\n');
        },

        onSetStatusComplete: function() {}
      };

      // {sv}: Map of string to variant for parameters
      var paramsBag = Components.classes["@mozilla.org/hash-property-bag;1"]
                                .createInstance(Components.interfaces
                                                .nsIWritablePropertyBag2);
      paramsBag.setPropertyAsAString('message', gMyPresence.message);

      // {s{sv}}: Map of status string to the params map
      var statusBag = Components.classes["@mozilla.org/hash-property-bag;1"]
                                .createInstance(Components.interfaces
                                                .nsIWritablePropertyBag2);
      statusBag.setPropertyAsInterface(gMyPresence.status, paramsBag);

      presenceInterface.setStatus(statusBag, presenceCB);
    }

    // Set user requested status when the connection is ready
    // Irrespective of the status update before connecting works or not,
    // this can be done
    if (gMyPresence.status != 'offline')
      oConnection.mLoadWithPresence = 
        {status: gMyPresence.status,
         statusMessage: gMyPresence.message};

    var selfHandleCB = new GetIntegerCB(this.mConnectionID,
                                        getLocaleString([['LoadConnectionError']]));
    selfHandleCB.postGotValue = function() {
      gConnectionsCache[this.mConnectionID].mSelfHandle = this.mInteger;
      gConnectionsCache[this.mConnectionID].load();
    }
    oConnection.connection.getSelfHandle(selfHandleCB);
  };
}

function GetStatusChangeObserver(aConnectionID) {
  this.mConnectionID = aConnectionID;

  this.onStatusChange = function(aStatus, aStatusReason) {
    if (aStatus == Components.interfaces.csITPConnection.Status_Disconnected) {
      var connection = gConnectionsCache[this.mConnectionID];
      connection.updateSelfStatus({status: 'offline', statusMessage: ''});

      gConnectionsCache[this.mConnectionID].cleanup();
    }
  }
}

function GetHandlesCB(aConnectionID, aHandleType) {
  this.mConnectionID = aConnectionID;
  this.mHandleType = aHandleType;
  this.mAccount = gConnectionsCache[this.mConnectionID].mAccount;
  this.mHandleStringMap = {};

  this.onError = function(aErrorCode) {
    dump("ERROR: inspect handles CB - " + aErrorCode + "\n");
    displayAlert(getLocaleString([['LoadConnectionError'], ['telepathy.error.' + aErrorCode]]),
                 getLocaleString([['ConnectionErrorTitle']]), this.mConnectionID);
    gTelepathyStatus.removeStatus(gConnectionsCache[this.mConnectionID].mAccountKey);
  }

  this.onGotHandle = function(aHandle, aHandleString) {
    this.mHandleStringMap[aHandle] = aHandleString;
  }

  this.onItemsComplete = function() { 
    this.postItemsComplete();
  }

  this.postItemsComplete = function() {
  }
}

/*
 * GetMembersListCB
 * Updates the status of the contacts in the connection
 * Understands the different types of channels and takes action accordingly
 *
 * @aConnectionID is the unique-id of the connection
 * @aChannelID is the channel type (subscribe, publish, deny ...)
 */
function GetMembersListCB(aConnectionID, aChannelID)
{
  this.mConnectionID = aConnectionID;
  this.mChannelID = aChannelID;

  this.mAddMembers = [];
  this.mLocalPendingMembers = [];
  this.mRemotePendingMembers = [];
  this.mRemoveMembers = [];

  this.doAddMember = function(aHandle)
  {
    this.mAddMembers.push(aHandle);
  }

  this.doRemoveMember = function(aHandle)
  {
    this.mRemoveMembers.push(aHandle);
  }

  this.doAddLocalPendingMember = function(aHandle)
  {
    this.mLocalPendingMembers.push(aHandle);
  }

  this.doAddRemotePendingMember = function(aHandle)
  {
    this.mRemotePendingMembers.push(aHandle);
  }

  this.onError = function(aErrorCode)
  {
    dump("ERROR: members list CB - " + aErrorCode + "\n");
    displayAlert(getLocaleString([['LoadConnectionError'], ['telepathy.error.' + aErrorCode]]),
                 getLocaleString([['ConnectionErrorTitle']]), this.mConnectionID);
    gTelepathyStatus.removeStatus(gConnectionsCache[this.mConnectionID].mAccountKey);
  }

  /*
   * onItemsComplete assumes the following behaviour in the interest of 
   * usability for a naive user
   *
   * 1. Only contacts present and shown in my contacts list are the people who
   *    get to know my presence
   * 2. A contact shows up with unknown status as soon as we add a contact.
   *    Upon authorization by the remote user, the actual status is shown
   */

  this.onItemsComplete = function()
  {
    // Add member handles to connection class
    var handleList = [];
    oConnection = gConnectionsCache[this.mConnectionID];

    // On the subscribe channel, we are currently
    // only interested in the removed, added and the
    // remote pending members
    if (this.mChannelID == 'subscribe') {

      // Remove members
      if (this.mRemoveMembers.length > 0) {
        for each (var member in this.mRemoveMembers)
          oConnection.updateContact(member, {subscribe: 'remove'});

        oConnection.updateRoster(this.mRemoveMembers);
      }

      // Add members
      for each (var member in this.mAddMembers) {
        oConnection.updateContact(member, {subscribe: 'both'});
        handleList.push(member);
      }

      if (this.mRemotePendingMembers.length > 0) {
        for each (var member in this.mRemotePendingMembers) {
          oConnection.updateContact(
                        member, 
                        {subscribe: 'remote-pending',
                         status: 'remote-pending',
                         statusMessage:
                           getLocaleString([['NotAuthorizedMessage']])});
        }

        var handleType = Components.interfaces.csITPConnection.Handle_Type_Contact;
        var handleListCB = new GetHandlesCB(this.mConnectionID, handleType);

        handleListCB.postItemsComplete = function()
        {
          var oConnection = gConnectionsCache[this.mConnectionID];

          for (var handle in this.mHandleStringMap) {
            oConnection.updateContact(handle, {
                          account: this.mHandleStringMap[handle],
                          alias: this.mHandleStringMap[handle].split("@")[0]
                        });
          }
        };
       
        var oConnection = gConnectionsCache[this.mConnectionID];
        oConnection.getAliases(this.mRemotePendingMembers);

        var connection = oConnection.connection;
        connection.inspectHandles(handleType, this.mRemotePendingMembers.length, 
                                  this.mRemotePendingMembers, handleListCB);
      }
    }

    // On the publish channel, we are only
    // interested in the local pending members & remove members
    if (this.mChannelID == 'publish') {
      // Local pending members
      for each (var member in this.mLocalPendingMembers) {
        oConnection.updateContact(
                      member, 
                      {subscribe: 'local-pending', 
                       status: 'local-pending'});
        handleList.push(member);
      }

      // Remove members
      if (this.mRemoveMembers.length > 0) {
        for each (var member in this.mRemoveMembers)
          oConnection.updateContact(member, {subscribe: 'remove'});

        oConnection.updateRoster(this.mRemoveMembers);
      }
    }

    // Get corresponding account names for member handles, if any
    if (handleList && handleList.length > 0) {

      var handleType = Components.interfaces.csITPConnection.Handle_Type_Contact;
      var handleListCB = new GetHandlesCB(this.mConnectionID, handleType);
      handleListCB.mChannelID = this.mChannelID;

      handleListCB.postItemsComplete = function()
      {
        var oConnection = gConnectionsCache[this.mConnectionID];
        var handleList = [];

        for (var handle in this.mHandleStringMap) {
          handleList.push(handle);
          oConnection.updateContact(handle, {
                        account: this.mHandleStringMap[handle],
                        alias: this.mHandleStringMap[handle].split("@")[0]
                      });
        }

        // On the subscribe channel proceed with getAliases
        if (this.mChannelID == 'subscribe') {
          oConnection.getAliases(handleList);
          oConnection.getPresence(handleList);

        // On the publish channel prompt user to add users
        } else if (this.mChannelID == 'publish') {
          for each (var handle in handleList)
            oConnection.handleSubscriptionRequest(handle);
        }
      };
     
      var oConnection = gConnectionsCache[this.mConnectionID];
      var connection = oConnection.connection;
      connection.inspectHandles(handleType, handleList.length, handleList, handleListCB);
    }
    
    this.postItemsComplete();

    // Initialize arrays for future calls
    this.mAddMembers = [];
    this.mLocalPendingMembers = [];
    this.mRemotePendingMembers = [];
    this.mRemoveMembers = [];
  }

  this.postItemsComplete = function() {
  }
}


function GetEmptyCB(aConnectionID, aDebugStr) {
  this.mConnectionID = aConnectionID;
  this.mDebugStr = aDebugStr;

  this.onError = function(aErrorCode) {
    dump("ERROR: " + this.mDebugStr + " - " + aErrorCode + "\n");
    displayAlert(this.mDebugStr + '\n' + getLocaleString([['telepathy.error.' + aErrorCode]]),
                 null, this.mConnectionID);
  }

  this.doAction = function() {
    // empty
  }
}

function GetNewChannelObserver(aConnectionID)
{
  this.mConnectionID = aConnectionID;
  this.mChannel = null;

  this.onNewChannel = function(aChannel, aSuppressHandlers)
  {
    // Don't handle this channel if
    // that was what the creater of the channel wanted us to do!
    if (aSuppressHandlers)
      return;

    this.gotChannel(aChannel);
  },

  this.onGotValue = function(aChannel)
  {
    this.gotChannel(aChannel);
  },

  this.gotChannel = function(aChannel)
  {
    this.mChannel = aChannel.QueryInterface(Components.interfaces.csITPChannel);
    this.postGotValue();
  },

  this.postGotValue = function()
  {
    // Empty for system created channels.
    // Scripts triggering channel creation can overwrite this function.
  },

  /*
   * isUserTriggered - true, if triggered by user
   * Enables use of 'GetNewChannelObserver' for both
   * remote & user triggered channels
   */
  this.handleNewChannel = function(isUserTriggered)
  {
    var channelReadyObserver = new GetChannelReadyObserver(this.mConnectionID,
                                                           this.mChannel,
                                                           isUserTriggered);
    this.mChannel.addChannelReadyObserver(channelReadyObserver);

    var channelCloseObserver = new GetChannelCloseObserver(this.mConnectionID,
                                                           this.mChannel);
    this.mChannel.addCloseObserver(channelCloseObserver);
  },

  this.onError = function(aErrorCode)
  {
    dump("ERROR: new channel CB - " + aErrorCode + "\n");
    displayAlert(getLocaleString([['CreateChannelError'], ['telepathy.error.' + aErrorCode]]),
                 getLocaleString([['ChannelErrorTitle']]), this.mConnectionID);
  }
}

function GetChannelCloseObserver(aConnectionID, aChannel) {
  this.mConnectionID = aConnectionID;
  this.mChannel = aChannel;

  this.onError = function(aErrorCode) {
    dump('ERROR: channelCloseObserver - ' + aErrorCode + '\n');
    displayAlert(getLocaleString([['CloseChannelError'], ['telepathy.error.' + aErrorCode]]),
                 getLocaleString([['ChannelErrorTitle']]), this.mConnectionID);
  }

  this.doAction = function() {
    //TODO: Do required stuff to close channel

    //dump("## 18 ## channel close\n");
    var channel = this.mChannel;
    var channelType = channel.channelType.split(".")[5];
    var oConnection = gConnectionsCache[this.mConnectionID];

   //dump('%% %% Closing Channel: ' + channel.channelType + ', htype: ' 
   //      + channel.targetHandleType + ', hnum:' + channel.targetHandle + '\n');

    if (channelType == "ContactList"
        && channel.targetHandleType == Components.interfaces.csITPConnection.Handle_Type_List) {
      // We don't do anything on closing of a ContactList or Group
      // dump('INFO: Ignore ContactList channel close\n');
    } else if (channelType == "Text") {
      channel = channel.QueryInterface(Components.interfaces.csITPTextChannel);

      if (channel.targetHandleType == Components.interfaces.csITPConnection.Handle_Type_Contact) {
        oConnection.updateContact(channel.targetHandle, {TextChannel: null});
      }

      // Intimate conversation manager
      var contactAccount = oConnection.mContacts[channel.targetHandle].account;
      gConversationManager.channelClosed(oConnection.mAccount, contactAccount);
    }
  }
}

