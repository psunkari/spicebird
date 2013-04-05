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
# Portions created by the Initial Developer are Copyright (C) 2010
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

function csChatAccount(aPrefKey) {
  this._key = aPrefKey;
  this._prefBranch = csChatAccountManager._prefBranch;

  this.load();
}

csChatAccount.prototype = {
  _reloadTimer: null,
  reload: function() {
    if (this._reloadTimer)
      clearTimeout(this._reloadTimer);

    var self = this;
    this._reloadTimer = setTimeout(function() {
                                     self.load();
                                     clearTimeout(self._reloadTimer);
                                   }, 10);
  },

  load: function() {
    this.settings = {};

    var prefs = this._prefBranch.getChildList(this.key + '.', {});
    for each (var pref in prefs) {
      var type = this._prefBranch.getPrefType(pref);
      var value = null;

      switch(type) {
        case Ci.nsIPrefBranch.PREF_STRING:
          value = this._prefBranch.getCharPref(pref);
          break;
        case Ci.nsIPrefBranch.PREF_INT:
          value = this._prefBranch.getIntPref(pref);
          break;
        case Ci.nsIPrefBranch.PREF_BOOL:
          value = this._prefBranch.getBoolPref(pref);
          break;
      }

      this.settings[pref.split('.')[1]] = value;
    }
  },

  get uri() {
    var server = this.settings["server"]? this.settings["server"] + "/": "default-server";
    return this.settings["protocol"] + "://" + server;
  },

  get account() {
    return this.settings["account"];
  },

  get enabled() {
    return this.settings["enabled"] !== "undefined" && this.settings["enabled"];
  },

  set enabled(aIsEnabled) {
    if (aIsEnabled)
      this.connect();
    else
      this.disconnect();

    this._prefBranch.setBoolPref(this.key + ".enabled", Boolean(aIsEnabled));
    csChatAccountManager._savePrefs();
  },

  get key() {
    return this._key;
  },

  get connectionKey() {
    return this._connectionKey;
  },

  set connectionKey(key) {
    this._connectionKey = key;
  },

  connect: function() {
    if (!this._connectionKey)
      csChatAccountManager.createConnectionForAccount(this);
  },

  disconnect: function() {
    if (!this._connectionKey)
      return;

    if (csChatWrapper.connections[this.connectionKey])
      csChatWrapper.connections[this.connectionKey].disconnect();

    delete this._connectionKey;
  },

  edit: function() {
    csChatAccountManager.editAccount(this.key);
  },

  remove: function() {
    csChatAccountManager.removeAccount(this.key);
  }
};


/*
 * Wrapper for chat account handling functionality
 */
var csChatAccountManager = {
  init: function() {
    this._prefBranch = Components.classes["@mozilla.org/preferences-service;1"]
                                 .getService(Ci.nsIPrefService)
                                 .getBranch('collab.chat.accounts.');

    var observerService = Components.classes["@mozilla.org/observer-service;1"]
                                    .getService(Ci.nsIObserverService);

    // Monitor changes to accounts
    Components.classes["@mozilla.org/preferences-service;1"]
              .getService(Ci.nsIPrefBranch2)
              .addObserver("collab.chat.accounts", this, false);

    this.accounts = {};
    this._loadAccounts();
  },

  uninit: function() {
    if (this._connectionStateListener)
      csChatWrapper.unregisterConnectionStateListener(this._connectionStateListener);
  },

  _loadAccounts: function() {
    var prefs = this._prefBranch.getChildList('', {});
    var re = /\d+\.account/;
    for each (var pref in prefs) {
      if (pref.match(re)) {
        var key = pref.split('.')[0];
        this.accounts[key] = new csChatAccount(key);
      }
    }
  },

  observe: function(subject, topic, data) {
    if (topic != "nsPref:changed")
      return;

    var key = data.split('.')[3];
    if (this.accounts[key] === undefined)
      this.accounts[key] = new csChatAccount(key);
    else
      this.accounts[key].reload();
  },

  // Util to persist any changes to the chat accounts
  _savePrefs: function() {
    Components.classes["@mozilla.org/preferences-service;1"]
              .getService(Ci.nsIPrefService).savePrefFile(null);
  },

  // Create a new chat account
  newAccount: function() {
    window.openDialog('chrome://chat/content/csChatAccountDialog.xul',
                      'chatAccount', 'chrome,resizable=no,modal,titlebar,centerscreen',
                      csChatWrapper.managers);

    this._savePrefs();
  },

  // Edit an existing chat account
  editAccount: function(key) {
    window.openDialog('chrome://chat/content/csChatAccountDialog.xul',
                      'chatAccount', 'chrome,resizable=no,modal,titlebar,centerscreen',
                      csChatWrapper.managers, key);

    this._savePrefs();
  },

  // Try to remove an account
  removeAccount: function(key) {
    try {
      this.accounts[key].disconnect();
      delete this.accounts[key];

      this._prefBranch.deleteBranch(key);
    } catch(ex) {};   // Ignore invalid key.

    this._savePrefs();
  },

  createConnectionForAccount: function(account, ignoreStoredPassword) {
    if (!csChatWrapper.presence || !csChatWrapper.presence.requestedStatus ||
        csChatWrapper.presence.requestedStatus == "offline")
      return;

    var manager = account.settings.manager;
    var protocol = account.settings.protocol;

    if (account.connectionKey)
      return true;

    if (!csChatWrapper.managers[manager]) {
      csChatWrapper.reportLocalizedError(csChatWrapper.NOTIFICATION_CRITICAL,
                                         csChatWrapper._("error.RequestConnection"),
                                         csChatWrapper._(["error.ManagerNotInstalled", manager]));
      return;
    }

    var paramsCB = new csChatGetParametersForConnection(account, ignoreStoredPassword);
    csChatWrapper.managers[manager].callGetParameters(protocol, paramsCB);
  },

  createConnectionForAccountKey: function(key, ignoreStoredPassword) {
    if (key && this.accounts[key])
      return this.createConnectionForAccount(this.accounts[key], ignoreStoredPassword);
  }
}

/*
 * Get list of parameters supported, get their values from the prefs
 * or from the user (password) and establish a connection!
 */
function csChatGetParametersForConnection(account, ignoreStoredPassword) {
  this.account = account;
  this.ignoreStoredPassword = ignoreStoredPassword? ignoreStoredPassword: false;
  this.lm = Components.classes["@mozilla.org/login-manager;1"]
                      .getService(Ci.nsILoginManager);
}

csChatGetParametersForConnection.prototype = {
  onGetParametersDone: function(parameters) {
    var values = Cc["@mozilla.org/array;1"].createInstance(Ci.nsIMutableArray);
    var enumerator = parameters.enumerate();
    var value;

    while(enumerator.hasMoreElements()) {
      var param = enumerator.getNext().QueryInterface(Ci.csITpParamSpec);
      var flags = param.flags;

      // See if we have a saved values for this param.
      if (param.name in this.account.settings) {
        value = new csChatTpProtocolParam(param.name,
                                          this.account.settings[param.name]);
        values.appendElement(value, false);

      // We don't have a param.  Is it a password?
      } else if (flags & Ci.csITpConnectionManager.Conn_Mgr_Param_Flags_Secret ||
                 /^password$/i.test(param.name)) {
        var password = null;

        // See if the user prefers secure auth (and that there was no auth failure).
        if (this.account.settings["useSecAuth"] && !this.ignoreStoredPassword) {
          if (flags & Ci.csITpConnectionManager.Conn_Mgr_Param_Flags_Required)
            password = "none_using_sec_auth";

        // We authenticate using a password.
        } else {
          var uri = this.account.uri;
          var logins = this.lm.findLogins({}, uri, uri, null)
          for each (var login in logins) {
            if (login.username == this.account.account) {
              password = login.password;

              // Remove login if we failed previous time.
              if (this.ignoreStoredPassword)
                this.lm.removeLogin(login);
              break;
            }
          }
         
          // We get the new password and possibly save it to login manager.
          if (password == null || this.ignoreStoredPassword)
            password = this.promptPassword(password);
         
          // We don't have a password.  Don't connect now! 
          if (password == null)
            return;
        }

        // Password will be null when it is not required
        // and we are using secure authentication.
        if (password) {
          value = new csChatTpProtocolParam(param.name, password);
          values.appendElement(value, false);
        }

      // A required parameter is missing.  Raise an error!
      } else if (flags & Ci.csITpConnectionManager.Conn_Mgr_Param_Flags_Required) {
        csChatWrapper.reportLocalizedError(csChatWrapper.NOTIFICATION_CRITICAL,
                                           csChatWrapper._("error.RequestConnection"),
                                           csChatWrapper._(["error.RequiredParameterMissing", param.name]));
      }
    }

    this.params = values;
    this.requestConnection();
  },

  requestConnection: function() {
    var manager = csChatWrapper.managers[this.account.settings.manager];
    var self = this;
    var requestConnectionCB = {
      onRequestConnectionDone: function(aBusName, aObjectPath) {
        var connection = Components.classes["@synovel.com/collab/telepathy/connection;1"]
                                   .createInstance(Ci.csITpConnectionUtils);
        connection.init(aBusName, aObjectPath);

        // This may be too early to create a wrapper, but it also has
        // some advantages.  We don't have to handle callbacks ourselves.
        var wrapper = new csChatConnectionWrapper(connection, true, self.account.key);

        csChatWrapper.connections[wrapper.key] = wrapper;
        self.account.connectionKey = wrapper.key;
      },

      onRequestConnectionError: function(domain, code, desc) {
        csChatWrapper.reportError(csChatWrapper.NOTIFICATION_CRITICAL,
                                  "RequestConnection", domain, code);
      }
    }
    manager.callRequestConnection(this.account.settings.protocol, this.params, requestConnectionCB);
  },
  
  onGetParametersError: function(domain, code, desc) {
    csChatWrapper.reportError(csChatWrapper.NOTIFICATION_CRITICAL,
                              "RequestConnectionGetParameters", domain, code);
  },

  promptPassword: function(defaultPassword) {
    var prompts = Components.classes["@mozilla.org/embedcomp/prompt-service;1"]
                            .getService(Components.interfaces.nsIPromptService)

    var password = {value: defaultPassword};
    var check = {value: defaultPassword? true: false};
    var promptLabel = this.account.settings.server?
                      csChatWrapper._(["PasswordLabelWithServer",
                                       this.account.account,
                                       this.account.settings.server]):
                      csChatWrapper._(["PasswordLabel", this.account.account]);
    var result = prompts.promptPassword(window, csChatWrapper._("PasswordDialogTitle"),
                                        promptLabel, password,
                                        csChatWrapper._("PasswordRemember"), check);
    if (!result)
      return null;

    if (check.value) {
      var nsLoginInfo = Components.Constructor("@mozilla.org/login-manager/loginInfo;1",
                                               Ci.nsILoginInfo, "init");
      var uri = this.account.uri;
      var login = new nsLoginInfo(uri, uri, null, this.account.account,
                                  password.value, "", "");
      this.lm.addLogin(login);
    }

    return password.value;
  }
}

/*
 * Helper for passing parameter when creating a connection
 */
function csChatTpProtocolParam(key, value) {
  this._key = key;
  this._value = value;
}
csChatTpProtocolParam.prototype = {
  get key() { return this._key; },
  get value() { return this._value; },
  QueryInterface: function(aIID) {
    if (!aIID.equals(Ci.csITpStringVariantMap) &&
        !aIID.equals(Ci.nsISupports))
      throw Components.results.NS_ERROR_NO_INTERFACE;
    return this;
  }
}

