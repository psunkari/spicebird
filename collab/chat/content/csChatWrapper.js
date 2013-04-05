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
# Portions created by the Initial Developer are Copyright (C) 2009
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Prasad Sunkari <prasad@synovel.com> (Original Author)
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

var Ci = Components.interfaces;

var csChatWrapper = {
  service: null,
  prefBranch: null,
  statusService: null,
  init: function() {
    this.service = Components.classes["@synovel.com/collab/telepathy/service;1"]
                             .getService(Ci.csITelepathyService);
    this.prefBranch = Components.classes["@mozilla.org/preferences-service;1"]
                                .getService(Ci.nsIPrefService).getBranch('collab.chat.');

    this._loading = 2;
    this._handlers = [];
    this._stringBundle = document.getElementById("bundle_chatwrapper");

    this.service.getManagerList(this._serviceCB);
    this.service.getConnectionList(this._serviceCB);
  },

  destroy: function() {
    for each (var connection in this.connections) {
      connection.destroy();
      connection = null;
    }
  },

  networkOnline: function() {
    if (this.presence.requestedStatus &&
        this.presence.requestedStatus != 'offline') {
      this.setGlobalStatus(this.presence.requestedStatus,
                           this.presence.requestedMessage);
    }
  },

  networkOffline: function() {
    for each (var connection in this.connections)
      connection.disconnect();
  },

  // Telepathy statuses to Spicebird status
  statusMap: {
    'available': 'available',
    'chat':      'available',
    'away':      'away',
    'brb':       'away',
    'busy':      'busy',
    'dnd':       'busy',
    'xa':        'xa',
    'ext_away':  'xa',
    'hidden':    'invisible',
    'invisible': 'invisible',
    'offline':   'offline'
  },

  managers: null,
  connections: {},
  _serviceCB: {
    onGetManagerListDone: function(managers) {
      var enumerator = managers.enumerate();
      csChatWrapper.managers = {}

      while (enumerator.hasMoreElements()) {
        var mgr = enumerator.getNext().QueryInterface(Ci.csITpConnectionManagerUtils);
        csChatWrapper.managers[mgr.connectionManager] = 
                                      mgr.QueryInterface(Ci.csITpConnectionManager);
      }

      csChatWrapper._finishLoading("managers");
    },

    onGetManagerListError: function(domain, code, desc) {
      csChatWrapper.reportError(csChatWrapper.NOTIFICATION_WARNING,
                                "GetManagersList", domain, code);
    },

    onGetConnectionListDone: function(connections) {
      var enumerator = connections.enumerate();
      csChatWrapper.connections = {};

      while (enumerator.hasMoreElements()) {
        var connection = enumerator.getNext()
                                   .QueryInterface(Ci.csITpConnection)
                                   .QueryInterface(Ci.csITpProxy)

        var wConnection = new csChatConnectionWrapper(connection, false);
        csChatWrapper.connections[wConnection.key] = wConnection;
      }

      csChatWrapper._finishLoading("connections");
    },

    onGetConnectionListError: function(domain, code, desc) {
      csChatWrapper.reportError(csChatWrapper.NOTIFICATION_INFO,
                                "CreateNewGroup", domain, code);
    }
  },

  _finishLoading: function(subsys) {
    this._loading -= 1;

    if (this._loading == 0) {
      this.checkFirstRun();
      this.login();
    }
  },

  /*
   * Check if this is first time chat application is being run.
   * If this is the first time, we prompt user to create a new account
   * and try to migrate users from other chat applications
   */
  checkFirstRun: function() {
    // TODO
  },

  /*
   * Check if the user enabled autologin. If he did, login and set the
   * status message to the most recently used.
   */
  login: function() {
    var autologin = false;
    try {
      autologin = this.prefBranch.getBoolPref('autologin');
    } catch (ex) { }
 
    if (!autologin)
      return;

    var autostatus = 'available';
    var messages = {};
    try {
      autostatus = this.prefBranch.getCharPref("autologin.status");
      for (var key = 0; key < 10; key++) {
        var sts = this.prefBranch.getCharPref('statuses.' + key + '.status');
        var msg = this.prefBranch.getCharPref('statuses.' + key + '.message');
        messages[sts] = msg;
      }
    } catch (ex) {}
 
    var statusMessage = messages[autostatus]?
                        messages[autostatus]: null;
    this.setGlobalStatus(autostatus, statusMessage, true);
  },

  presence: {},
  setGlobalStatus: function(onlineStatus, statusMessage, isAutoLogin) {
    // If status is set to offline, disconnect all connections
    if (onlineStatus == 'offline') {
      for each (var connection in this.connections)
        connection.disconnect();

      return;
    }

    // If network is offline then ask if the user wishes
    // to get connected to the network before proceeding.
    if (!navigator.onLine) {
      if (isAutoLogin)
        return;

      let prompts = Components.classes["@mozilla.org/embedcomp/prompt-service;1"]
                              .getService(Components.interfaces.nsIPromptService)
     
      let brandShortName = gBrandBundle.getString("brandShortName");
      let result = prompts.confirm(window,
                                   this._("networkGoOnlineTitle"),
                                   this._(["networkGoOnlineLabel", brandShortName]))
      if (!result)
        return;

      let ioService = Components.classes["@mozilla.org/network/io-service;1"]
                                .getService(Components.interfaces.nsIIOService2);
      ioService.offline = false;
    }

    this.presence.requestedStatus = onlineStatus;
    this.presence.requestedMessage = statusMessage;

    this.presence.status = onlineStatus;
    this.presence.message = statusMessage;

    // Set the status on all existing connections
    for each (connection in this.connections)
      connection.setPresenceStatus(onlineStatus, statusMessage);

    // Create connection and et the status on all enabled accounts
    // for which connections don't already exist.
    for each (account in csChatAccountManager.accounts)
      if (account.enabled)
        csChatAccountManager.createConnectionForAccount(account);

    // Notify observers about the global status change.
    // It is not right to update the visible status based on this broadcast
    // because it would mislead the user to think that the status on server
    // has changed.  Instead observe for "ChatStatusSync".
    Components.classes["@mozilla.org/observer-service;1"]
              .getService(Ci.nsIObserverService)
              .notifyObservers(null, "ChatStatusChange", this.presence.status);
  },

  /*
   * TpContact corresponding to self handle got updated.
   * ConnectionKey is available at TpContact->connectionKey
   */
  myDetailsUpdated: function(contact, detail) {
    // We set the visible status to a more available status
    if (detail == 'presence-status' || detail == 'presence-message') {
      var status = 'offline';
      for each (var connection in this.connections) {
        if(connection.myself &&
           this.isMoreAvailable(connection.myself.presenceStatus, status))
          status = connection.myself.presenceStatus;
      }
      this.syncGlobalStatus(this.statusMap[status], connection.myself.presenceMessage);
    } else {
      // We ignore all other external updates
    }
  },
  
  isMoreAvailable: function(one, two) {
    var statuses = ["offline", "invisible", "xa", "away", "busy", "available"];
    return statuses.indexOf(this.statusMap[one]) > statuses.indexOf(this.statusMap[two]);
  },

  syncGlobalStatus: function(onlineStatus, statusMessage)
  {
    this.presence.status = onlineStatus;
    if (statusMessage !== undefined)
      this.presence.message = statusMessage;
  
    // Notify observers that the global status needs
    // to be synced.  This sync is due to change in status
    // of one or more connections and is not set directly by the user.
    //
    // This could even be in response to user action.
    //
    // All UI elements that display status to the users should
    // subscribe to this status to get updates
    Components.classes["@mozilla.org/observer-service;1"]
              .getService(Components.interfaces.nsIObserverService)
              .notifyObservers(null, "ChatStatusSync", onlineStatus);
  },

  _connectingKeys: [],
  _pushConnectingKey: function(key) {
    if (this._connectingKeys.indexOf(key) >= 0)
      return;

    if (this._connectingKeys.length == 0) {
      Components.classes["@mozilla.org/observer-service;1"]
                .getService(Components.interfaces.nsIObserverService)
                .notifyObservers(null, "ChatConnecting", true);
    }
    
    this._connectingKeys.push(key);
  },

  _popConnectingKey: function(key, state, reason) {
    var index = this._connectingKeys.indexOf(key)
    if (index == -1)
      return;

    this._connectingKeys.splice(index, 1);
    if (this._connectingKeys.length == 0) {
      Components.classes["@mozilla.org/observer-service;1"]
                .getService(Components.interfaces.nsIObserverService)
                .notifyObservers(null, "ChatConnecting", false);
    }
  },

  connectionStateChanged: function(key, state, reason) {

    // Inform the listeners.
    for each (var handler in this._connectionStateListeners) {
      try {
        handler.apply(this, [key, state, reason]);
      } catch(ex) {};
    }

    switch(state) {
      // Connection got established.
      case Ci.csITpConnection.Connection_Status_Connected:
        this._popConnectingKey(key, state, reason);
        break;

      // Connecting...
      case Ci.csITpConnection.Connection_Status_Connecting:
        this._pushConnectingKey(key);
        break;

      // Cleanup is taken care of by the csChatConnectionWrapper.
      case Ci.csITpConnection.Connection_Status_Disconnected:
        this._popConnectingKey(key, state, reason);

        // Update the global status
        var status = "offline";
        for each (var connection in this.connections) {
          if(connection.myself && connection.key != key &&
             this.isMoreAvailable(connection.myself.presenceStatus, status))
            status = connection.myself.presenceStatus;
        }
        this.syncGlobalStatus(csChatWrapper.statusMap[status]);

        // A few more tasks to be done if we own the connection!
        connection = this.connections[key];
        if (connection.accountKey && csChatAccountManager.accounts[connection.accountKey] &&
            csChatAccountManager.accounts[connection.accountKey].connectionKey == connection.key) {
          this.diagnoseDisconnection(connection, reason);
          csChatAccountManager.accounts[connection.accountKey].connectionKey = null;
        }

        delete this.connections[key];
    }
  },

  notifyAuthFailureForAccount: function(accountKey) {
    var prompts = Components.classes["@mozilla.org/embedcomp/prompt-service;1"]
                            .getService(Components.interfaces.nsIPromptService)

    var account = csChatAccountManager.accounts[accountKey];
    if (!account)
      return;

    var result = prompts.confirmEx(null,
                                   this._("chatServerLoginFailedTitle"),
                                   this._(["chatServerLoginFailed", account.account]),
                                   (prompts.BUTTON_TITLE_IS_STRING * prompts.BUTTON_POS_0) +
                                   (prompts.BUTTON_TITLE_IS_STRING * prompts.BUTTON_POS_1),
                                   this._("chatServerLoginFailedEnterNewPassword"), 
                                   this._("chatServerLoginFailedDisableAccount"),
                                   null, null, {});
    if (result == 0)
      csChatAccountManager.createConnectionForAccount(account, true);
    else
      account.enabled = false;
  },

  diagnoseDisconnection: function(connection, reason) {
    // Don't display any error if user requested the disconnection
    if (reason == Ci.csITpConnection.Connection_Status_Reason_Requested)
      return;

    // Check if it is an authentication failure
    if (connection.connectionError &&
        connection.connectionError.error == "AuthenticationFailed" || reason == 3) {
      var accountKey = connection.accountKey;
      setTimeout(function() {
                   csChatWrapper.notifyAuthFailureForAccount(accountKey);
                 }, 0);
      return;
    }

    // Check if it is a problem with invalid certificate.
    // Must prompt the user to add that certificate to trusted certificates
    // TODO

    // Is it due to a network connection?
    // Schedule a reconnection for this account between 60 & 90 seconds.
    
    var retryOnNetworkError = false;
    try {
      retryOnNetworkError = this.prefBranch.getBoolPref('retryonerror');
    } catch (ex) { }

    if (retryOnNetworkError && (connection.connectionError &&
        connection.connectionError.error == "NetworkError" || reason == 2)) {
      var interval = Math.floor(Math.random() * 30) + 60;
      var accountKey = connection.accountKey;
      setTimeout(function() {
                   csChatAccountManager.createConnectionForAccountKey(accountKey);
                 }, interval * 1000);
    }

    // Inform of the user of any other reasons.
    var detail;
    if (connection.connectionError)
      detail = csChatWrapper._("error." + connection.connectionError.error);

    if (!detail)
      detail = csChatWrapper._("connection.statusReason." + reason);

    csChatWrapper.reportLocalizedError(csChatWrapper.NOTIFICATION_CRITICAL,
                                       connection.id, detail);
  },

  connectionHandleChanged: function(key, handle) {
  },


  /*
   * Request a channel. Raises a signal when new channel is created
   */
  requestChannel: function(key, channelType, targetHandleType, targetHandle) {
    channelType = "org.freedesktop.Telepathy.Channel.Type." + channelType;
    if (this.connections[key]) {
      this.connections[key].requestChannel(channelType,
                                           targetHandleType,
                                           targetHandle);
    } else {
      csChatWrapper.reportLocalizedError(csChatWrapper.NOTIFICATION_INFO,
                                         csChatWrapper._("error.RequestChannel"),
                                         csChatWrapper._("error.InvalidConnectionKey"));
    }
  },


  /*
   * Channel Handlers
   */
  _channelHandlers: {},
  registerChannelHandler: function(type, handler) {
    if (typeof handler == 'function') {
      if (this._channelHandlers[type])
        this._channelHandlers[type].push(handler);
      else
        this._channelHandlers[type] = [handler];
    }
    return handler;
  },

  unregisterChannelHandler: function(type, handler) {
    if (!this._channelHandlers[type])
      return;

    var index = this._channelHandlers[type].indexOf(handler);
    if (index != -1)
      this._channelHandlers[type].splice(index, 1);
  },

  getChannelHandlers: function(type) {
    if (this._channelHandlers[type])
      return this._channelHandlers[type];
    else
      return [];
  },


  /*
   * Contact Update Listeners
   */
  _contactUpdateListeners: [],
  registerContactUpdateListener: function(handler) {
    if (typeof handler == 'function')
      this._contactUpdateListeners.push(handler);

    return handler;
  },

  unregisterContactUpdateListener: function(handler) {
    var index = this._contactUpdateListeners.indexOf(handler);
    if (index != -1)
      this._contactUpdateListeners.splice(index, 1);
  },

  getContactUpdateListeners: function() {
    return this._contactUpdateListeners;
  },


  /*
   * New Contacts Listeners
   */
  _newContactsListeners: [],
  registerNewContactsListener: function(handler) {
    if (typeof handler == 'function')
      this._newContactsListeners.push(handler);

    return handler;
  },

  unregisterNewContactsListener: function(handler) {
    var index = this._newContactsListeners.indexOf(handler);
    if (index != -1)
      this._newContactsListeners.splice(index, 1);
  },

  getNewContactsListeners: function() {
    return this._newContactsListeners;
  },


  /*
   * Contact Lists and Groups Listeners
   */
  _newContactGroupListeners: [],
  registerNewContactGroupListener: function(handler) {
    if (typeof handler == 'function')
      this._newContactGroupListeners.push(handler);

    return handler;
  },

  unregisterNewContactGroupListener: function(handler) {
    var index = this._newContactGroupListeners.indexOf(handler);
    if (index != -1)
      this._newContactGroupListeners.splice(index, 1);
  },

  getNewContactGroupListeners: function() {
    return this._newContactGroupListeners;
  },


  /*
   * Contact Lists and Groups Update Listeners
   */
  _contactGroupUpdateListeners: [],
  registerContactGroupUpdateListener: function(handler) {
    if (typeof handler == 'function')
      this._contactGroupUpdateListeners.push(handler);

    return handler;
  },

  unregisterContactGroupUpdateListener: function(handler) {
    var index = this._contactGroupUpdateListeners.indexOf(handler);
    if (index != -1)
      this._contactGroupUpdateListeners.splice(index, 1);
  },

  getContactGroupUpdateListeners: function() {
    return this._contactGroupUpdateListeners;
  },


  /*
   * Contact List Delete Listeners
   */
  _contactGroupDeleteListeners: [],
  registerContactGroupDeleteListener: function(handler) {
    if (typeof handler == 'function')
      this._contactGroupDeleteListeners.push(handler);

    return handler;
  },

  unregisterContactGroupDeleteListener: function(handler) {
    var index = this._contactGroupDeleteListeners.indexOf(handler);
    if (index != -1)
      this._contactGroupDeleteListeners.splice(index, 1);
  },

  getContactGroupDeleteListeners: function() {
    return this._contactGroupDeleteListeners;
  },


  /*
   * Connection status change listeners
   */
  _connectionStateListeners: [],
  registerConnectionStateListener: function(handler) {
    if (typeof handler == 'function')
      this._connectionStateListeners.push(handler);

    return handler;
  },

  unregisterConnectionStateListener: function(handler) {
    var index = this._connectionStateListeners.indexOf(handler);
    if (index != -1)
      this._connectionStateListeners.splice(index, 1);
  },

  getConnectionStateListeners: function() {
    return this._connectionStateListeners;
  },

  showChatHistory: function() {
    window.openDialog("chrome://chat/content/csChatHistory.xul", "", "chrome");
  },

  // Give access to accounts through csChatWrapper
  get accountManager() {
    return csChatAccountManager;
  },

  // Get localized string from csChatWrapper.properties
  _: function(code) {
    var localeString = '';

    try {
      if (typeof code == 'object')
        localeString = this._stringBundle.getFormattedString(code[0], code.slice(1));
      else
        localeString = this._stringBundle.getString(code);
    } catch(ex) { }

    return localeString;
  },

  // Severity of the errors/notifications
  // Should be kept in sync with notification.xml
  NOTIFICATION_INFO: 2,
  NOTIFICATION_WARNING: 5,
  NOTIFICATION_CRITICAL: 8,

  // Report error.  Takes care of getting the strings from string bundle.
  reportError: function(severity, taskCode, domain, errorCode) {
    var task = (typeof taskCode == 'object')?
               csChatWrapper._(["error." + taskCode[0], taskCode.slice(1)]):
               task = csChatWrapper._("error." + taskCode);

    var error = csChatWrapper._("error." + domain + "." + errorCode);

    this.reportLocalizedError(severity, task, error);
  },

  // Report error.  Expects both task and errors as localized strings.
  reportLocalizedError: function(severity, task, error) {
    alert(task + "\n" + error);
  },

  // In future we may use csChatQuickStatus for all prompts
  showSubscriptionRequest: function(connection, contact, afterUserPrompt) {
    var prompts = Components.classes["@mozilla.org/embedcomp/prompt-service;1"]
                            .getService(Components.interfaces.nsIPromptService)
    var identifier = contact.identifier;

    var result = prompts.confirmEx(null,
                                   this._("ConfirmAuthorizeContactTitle"),
                                   this._(["ConfirmAuthorizeContactInfo",
                                           identifier, connection.id]),
                                   (prompts.BUTTON_TITLE_IS_STRING * prompts.BUTTON_POS_0) +
                                   (prompts.BUTTON_TITLE_IS_STRING * prompts.BUTTON_POS_1) +
                                   (prompts.BUTTON_TITLE_IS_STRING * prompts.BUTTON_POS_2),
                                   this._("AuthorizeContactAllow"), 
                                   this._("AuthorizeContactLater"), 
                                   this._("AuthorizeContactDeny"), 
                                   null, {});
  
    afterUserPrompt(contact, result);
  }
}
