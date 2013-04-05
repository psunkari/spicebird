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
#   Siva Edupuganti <sivakrishna@synovel.com>
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
var csITpConnectionManager = Ci.csITpConnectionManager;

var csChatAccountDialogWrapper = {
  _managers: null,
  _prefKey: null,
  _protocols: null,

  /*
   * Fetch the list of protocols that the system currently supports.
   * We do not look for any new installed connection-managers, but instead
   * use the list cached at the starting of the application.
   *
   * Uses two arguments that need to be passed to this window.
   * - A hashmap of connection-manager name to csITpConnectionManager
   * - Account key if we are editing an existing account
   */
  init: function() {
    this._managers = window.arguments[0];
    this._prefKey = window.arguments[1];

    this._basicRows = document.getElementById("basic-param-rows");
    this._advancedRows = document.getElementById("advanced-param-rows");
    this._protocolMenuList = document.getElementById("protocol-list");
    this._stringBundle = document.getElementById("chat-accounts-bundle");

    this._prefBranch = Components.classes["@mozilla.org/preferences-service;1"]
                                 .getService(Ci.nsIPrefService)
                                 .getBranch("collab.chat.accounts.");

    this._prompts = Components.classes["@mozilla.org/embedcomp/prompt-service;1"]
                              .getService(Ci.nsIPromptService);

    /* An account key was passed for editing */
    if (this._prefKey) {
      this._loadFromPrefs = true;
    
      var popup = this._protocolMenuList.firstChild;
      while (popup.lastChild)
        popup.removeChild(popup.lastChild);
    
      // Get manager & protocol from pref
      try {
        var manager  = this._prefBranch.getCharPref(this._prefKey + '.manager');
        var protocol = this._prefBranch.getCharPref(this._prefKey + '.protocol');
      } catch(ex) {
        // A few mandatory settings are missing.  Remove this account!
        try {
          this._prefBranch.deleteBranch(this._prefKey);
        } catch(ex) { };

        return window.close();
      }

      var menuitem = document.createElementNS(popup.namespaceURI, "menuitem");

      try {
        menuitem.setAttribute("label", this._stringBundle.getString(protocol));
      } catch(ex) {
        menuitem.setAttribute("label", protocol);
      }
      menuitem.setAttribute("value", protocol);
      menuitem.setAttribute("class", "chat-protocol " + protocol + " menuitem-iconic");
      menuitem.setAttribute("manager", manager);
      popup.appendChild(menuitem);

      this._protocolMenuList.selectedIndex = 0;
      this._protocolMenuList.setAttribute("disabled", true);
    }

    /* Create a new chat account */
    else {
      this._protocols = []

      function ListProtocolCB(scope, manager) {
        this._scope = scope;
        this._manager = manager;
      }

      ListProtocolCB.prototype = {
        onListProtocolsDone: function(count, protocols) {
          for each (var protocol in protocols) {
            var existing = this._scope._protocols.filter(function(item) {
                             return item.protocol == protocol;
                           });
            if (existing.length)
              continue;

            this._scope._protocols.push({protocol: protocol, manager: this._manager});
          }
          this.finish();
        },

        onListProtocolsError: function(code, desc) {
          this.finish();
        },

        finish: function() {
          var index = this._scope._pendingManagersList.indexOf(this._manager);
          if (index == -1)
            return;

          this._scope._pendingManagersList.splice(index, 1);

          if (this._scope._pendingManagersList.length == 0)
            this._scope.refreshProtocolMenu();
        }
      }

      /* Get the list of supported protocols for each connection manager */
      /* TODO: Priorities among connection managers that support the same protocol */
      this._pendingManagersList = [];
      for each (var mgr in this._managers) {
        var mgrName = mgr.QueryInterface(Ci.csITpConnectionManagerUtils)
                         .connectionManager;
        this._pendingManagersList.push(mgrName);

        var callback = new ListProtocolCB(this, mgrName);
        mgr.callListProtocols(callback);
      }
    }
  },

  /*
   * Create menuitems for each available protocol handler
   */
  refreshProtocolMenu: function() {
    if (this._protocols.length == 0) {
      alert("No backends installed or backends not functional.\n");
      return window.close();
    }
    
    var popup = this._protocolMenuList.firstChild;
    while (popup.lastChild)
      popup.removeChild(popup.lastChild);

    for each (var item in this._protocols) {
      var menuitem = document.createElementNS(popup.namespaceURI, "menuitem");

      try {
        menuitem.setAttribute("label", this._stringBundle.getString(item.protocol));
      } catch(ex) {
        menuitem.setAttribute("label", item.protocol);
      }
      menuitem.setAttribute("value", item.protocol);
      menuitem.setAttribute("class", "chat-protocol " + item.protocol + " menuitem-iconic");
      menuitem.setAttribute("manager", item.manager);
      popup.appendChild(menuitem);
    }

    this._protocolMenuList.selectedIndex = 0;
  },

  /*
   * Implementation of csITpGetParametersCB.
   * When the call is successful we get an array of csITpParamSpec.
   */
  onGetParametersDone: function(parameters) {

    // In case of jabber (with haze) support kerberos
    if (this._selectedManager == "haze" && this._selectedProtocol == "jabber") {
      this.addParameter({
          flags: Ci.csITpConnectionManager.Conn_Mgr_Param_Flags_Has_Default,
          name: "useSecAuth",
          signature: "b",
          defaultValue: false
        });
    }

    var enumerator = parameters.enumerate();
    while (enumerator.hasMoreElements()) {
      var param = enumerator.getNext().QueryInterface(Ci.csITpParamSpec)

      // Skip adding password to the dialog.
      // Just as with mail, user is asked for password when required.
      if (param.flags & Ci.csITpConnectionManager.Conn_Mgr_Param_Flags_Secret ||
          /^password$/i.test(param.name))
        continue;

      this.addParameter(param);
    }

    // User nickname (for this connection)
    // Prefill to the account name
    this.addParameter({
        flags: Ci.csITpConnectionManager.Conn_Mgr_Param_Flags_Required ||
               Ci.csITpConnectionManager.Conn_Mgr_Param_Flags_Has_Default,
        name: "localNick",
        signature: "s",
        get defaultValue() {
          return "Name";
        }
      });

    this._dialogUpdating = false;
  },

  /*
   * Implementation of csITpGetParametersCB.
   * Called when an error occured during the GetParameters DBus call
   */
  onGetParametersError: function(domain, code, desc) {
    this._showError(desc);  // Extremely rare!!!
    this._dialogUpdating = false;
  },

  _showError: function(error) {
    var namespaceURI = this._basicRows.namespaceURI;
    var row = document.createElementNS(namespaceURI, "row");
    var message = document.createElementNS(namespaceURI, "label");

    row.setAttribute("class", "error");
    message.setAttribute("value", error);

    row.appendChild(message);
    this._basicRows.appendChild(row);
  },

  /*
   * Add parameter to the UI.
   * Either the default values or the currently set values are shown here
   */
  addParameter: function(param) {
    var namespaceURI = this._basicRows.namespaceURI;
    var row = document.createElementNS(namespaceURI, "row");
    row.setAttribute("align", "center");

    // Create the label
    var titleCell = document.createElementNS(namespaceURI, "hbox");

    var titleCellSpacer = document.createElementNS(namespaceURI, "spacer");
    titleCell.appendChild(titleCellSpacer);
    titleCellSpacer.setAttribute("flex", "1");

    var titleCellLabel = document.createElementNS(namespaceURI, "label");
    titleCell.appendChild(titleCellLabel);

    titleCellLabel.setAttribute("value", this.getLocalizedParamName(param));

    // Parse the flags
    var flags = param.flags;
    var hasDefault = flags & csITpConnectionManager.Conn_Mgr_Param_Flags_Has_Default;
    var isRequired = flags & csITpConnectionManager.Conn_Mgr_Param_Flags_Required;

    var defaultValue = null;
    if (this._loadFromPrefs) {
      var signature = param.signature;
      var name = param.name;

      try {
        switch (signature) {
          case "q":
          case "n":
          case "i":
            defaultValue = this._prefBranch.getIntPref(this._prefKey + "." + name);
            break;
          case "b":
            defaultValue = this._prefBranch.getBoolPref(this._prefKey + "." + name);
            break;
          case "s":
            defaultValue = this._prefBranch.getCharPref(this._prefKey + "." + name);
            break;
          default:
            defaultValue = this._prefBranch.getCharPref(this._prefKey + "." + name);
        }
        hasDefault = true;
      } catch(ex) {
        hasDefault = false;
        defaultValue = '';
      }
    }
    else if (hasDefault) {
      defaultValue = param.defaultValue;
    }

    // Create the input field.
    var valueCell;
    switch(param.signature) {

      case 's':
        valueCell = document.createElementNS(namespaceURI, "textbox");
        if (hasDefault)
          valueCell.setAttribute("value", defaultValue);
        break;

      case 'q':
      case 'n':
      case 'i':
        valueCell = document.createElementNS(namespaceURI, "textbox");
        valueCell.setAttribute("type", "number");
        if (hasDefault)
          valueCell.setAttribute("value", defaultValue);
        break;

      case 'b':
        valueCell = document.createElementNS(namespaceURI, "checkbox");
        if (defaultValue)
          valueCell.setAttribute("checked", defaultValue);

        valueCell.setAttribute("label", this.getLocalizedParamName(param));
        titleCell.setAttribute("collapsed", "true");
        break;

      default:
        valueCell = document.createElementNS(namespaceURI, "label");
        valueCell.setAttribute("value", this.getLocalizedParamName(param));
        if (hasDefault)
          valueCell.value = valueCell.value + "(default)";
    }

    // Store param name & signature to use when saving parameters.
    valueCell.setAttribute("param", param.name);
    valueCell.setAttribute("signature", param.signature);

    row.appendChild(titleCell);
    row.appendChild(valueCell);

    // Disable account parameter if loading from preferences
    var self = this;
    if (/^account$/i.test(param.name)) {
      if (this.mLoadFromPrefs)
        valueCell.setAttribute("disabled", true);
      else
        valueCell.addEventListener("blur", function() { self.setDefaultNick(); }, true);
    }

    // Add to corresponding tab based on 'required' param flag
    if (isRequired)
      this._basicRows.appendChild(row);
    else
      this._advancedRows.appendChild(row);
  },

  setDefaultNick: function() {
    let accountValue = this._basicRows.getElementsByAttribute("param", "account")[0];
    let localNickValue = this._basicRows.getElementsByAttribute("param", "localNick")[0];

    if (accountValue && localNickValue && !localNickValue.value)
      localNickValue.value = accountValue.value;
  },

  getLocaleString: function(message) {
    var localeString = '';
    try {
      if (typeof(message) == 'object')
        localeString = this._stringBundle.getFormattedString(message[0], message.slice(1));
      else
        localeString = this._stringBundle.getString(message);
    } catch(ex) {}

    return localeString;
  },

  getLocalizedParamName: function(param) {
    var name = param.name;
    var localized = this.getLocaleString(this._selectedManager + '.params.' + name);
    
    // If localized string does not exist:
    // - Capitalize first letter
    // - Replace '-' with space
    // - Append ':' if the parameter type is not boolean

    if (!localized) {
      localized = name.charAt(0).toUpperCase() + name.substring(1);
      localized = localized.replace(/-/g, ' ');
      if (param.signature != 'b')
        localized += ':';
    }

    return localized;
  },

  protocolSelected: function() {
    this._selectedProtocol = this._protocolMenuList.selectedItem.value;
    this._selectedManager = this._protocolMenuList.selectedItem.getAttribute("manager");

    if (this._dialogUpdating)
      return;

    this.clearParamFields();
    this._managers[this._selectedManager].callGetParameters(this._selectedProtocol, this);
    this._dialogUpdating = true;
  },

  clearParamFields: function() {
    while (this._basicRows.lastChild)
      this._basicRows.removeChild(this._basicRows.lastChild);

    while (this._advancedRows.lastChild)
      this._advancedRows.removeChild(this._advancedRows.lastChild);
  },

  // Checks if basic parameters are filled. 
  // Sets focus to the first empty value cell, if 'focus' is true.
  checkForBasicParams: function(focus) {
    var completed = true;
            
    for (var i = 0; i < this._basicRows.childNodes.length && completed; i++) {
      var valueCell = this._basicRows.childNodes[i].lastChild;

      // If the local nickname was not given, just set the default value.
      if (valueCell.getAttribute("param") == "localNick") {
        if (!valueCell.value)
          this.setDefaultNick();
      }

      // Raise an error in case of other required/basic params
      else if (!valueCell.value &&
               (valueCell.checked == undefined ||
                valueCell.checked.toString() == '')) {
        if (focus)
          valueCell.focus();

        completed = false;
        break;
      }
    }

    return completed;
  },

  saveParameters: function() {
    if (!this.checkForBasicParams(/*focus = */true)) {
      this._prompts.alert(null, 
                          this.getLocaleString('ChatAccountSetupErrorTitle'), 
                          this.getLocaleString('BasicParametersMandatoryError'));
      return false; 
    }

    // Get a new unique key for new accounts
    if (!this._loadFromPrefs) {
      var key;
      try {
        for (key=0; key<1000; key++)
          this._prefBranch.getCharPref(key.toString() + ".account");
      } catch (ex) { };

      this._prefKey = key.toString();
    }

    // Cleanup existing preferences, if any
    try {
      this._prefBranch.deleteBranch(this._prefKey);
    } catch(ex) { };
 
    this._prefBranch.setCharPref(this._prefKey + ".manager", this._selectedManager);
    this._prefBranch.setCharPref(this._prefKey + ".protocol", this._selectedProtocol);

    var paramRows = new Array();
    for (var i = 0; i < this._basicRows.childNodes.length; i++)
      paramRows.push(this._basicRows.childNodes[i]);

    for (var i = 0; i < this._advancedRows.childNodes.length; i++)
      paramRows.push(this._advancedRows.childNodes[i]);

    for (var i = 0; i < paramRows.length; i++) {

      var valueCell = paramRows[i].lastChild;
      var signature = valueCell.getAttribute("signature");
      var param = valueCell.getAttribute("param");

      switch (signature) {
        case "q":
        case "n":
        case "i":
          if (valueCell.value)
            this._prefBranch.setIntPref(this._prefKey + "." + param, valueCell.value);
          break;
        case "b":
          this._prefBranch.setBoolPref(this._prefKey + "." + param, valueCell.checked);
          break;
        case "s":
          if (valueCell.value)
            this._prefBranch.setCharPref(this._prefKey + "." + param, valueCell.value);
          break;
        default:
          if (valueCell.value)
            this._prefBranch.setCharPref(this._prefKey + "." + param, valueCell.value.toString);
      }
    }
    
    // TODO: account creation notification

    return true;
  }
}

