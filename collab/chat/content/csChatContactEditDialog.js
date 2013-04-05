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

var csChatWrapper = null;

var EditContact = {
  init: function() {
    csChatWrapper = window.arguments[0];

    var connectionKey = window.arguments[1];
    var handle = window.arguments[2];

    if (!csChatWrapper)
      window.close()

    // Disable the accept button
    this.acceptButton = document.getElementById("dialog").getButton("accept");
    this.acceptButton.setAttribute("disabled", "true");

    // Save the localized default title
    this._defaultTitle = document.title;

    // Populate the accounts popup
    var menupopup = document.getElementById("accounts-popup");
    menupopup.populate();

    // If we have a connection key, set it as the default...
    // else, choose the first available, established connection
    var accounts = document.getElementById("accounts-menulist");
    var item = null;
    if (connectionKey)
      item = document.getAnonymousElementByAttribute(menupopup, "value", connectionKey);
    else
      item = document.getAnonymousElementByAttribute(menupopup, "type", "chat-connection");

    if (item)
      this.selectConnection(item);

    // Populate the list of groups
    this._populateGroups();

    // To proceed, we need a connection and a valid handle
    if (!this.connection || !handle)
      return;

    this.contact = this.connection.contacts[handle];
    if (!this.contact)
      return;

    // Meta info may be undefined if there is no relevant information
    var contactMetaInfo = this.connection.contactsMetaInfo[handle];
    if (contactMetaInfo && contactMetaInfo.groups) {
      for each (var group in contactMetaInfo.groups) {
        var item = document.getElementById("group-" + btoa(group));
        if (item)
          item.setAttribute("checked", true);
      }
    }

    // We are editing a contact.
    // So, first make the account, the target username read-only

    var username = document.getElementById("username");
    var alias = document.getElementById("alias");

    accounts.setAttribute("disabled", "true");
    username.setAttribute("readonly", "true");

    username.value = this.contact.identifier;
    alias.value = this.contact.alias;

    document.title = this.contact.identifier;
    this.acceptButton.removeAttribute("disabled");
  },

  newGroupKeypress: function(event) {
    if (event.keyCode == KeyEvent.DOM_VK_RETURN) {
      var item = this.addGroup();
      if (item) {
        document.getElementById("groups").ensureElementIsVisible(item);
        document.getElementById("group-new").value = "";
      }

      event.preventDefault();
    }
  },

  // XXX: It would be interesting to create the new group here,
  // but since I anyway have to a check in csChatConnection, let
  // me do it there itself.
  addGroup: function() {
    var groupId = document.getElementById("group-new").value;
    if (!groupId)
      return;

    var itemId = "group-" + btoa(groupId);
    if (document.getElementById(itemId))
      return;

    var item = document.createElement("listitem");
    item.setAttribute("type", "checkbox");
    item.setAttribute("label", groupId);
    item.setAttribute("checked", true);
    item.setAttribute("id", itemId);

    return document.getElementById("groups").appendChild(item);
  },

  // TODO: Check if the connection supports groups at all!
  _populateGroups: function() {
    var groupsListBox = document.getElementById("groups");

    for each (var connection in csChatWrapper.connections) {
      for (var groupId in connection.contactGroups) {

        var itemId = "group-" + btoa(groupId);
        if (document.getElementById(itemId))
          return;

        var item = document.createElement("listitem");
        item.setAttribute("type", "checkbox");
        item.setAttribute("label", groupId);
        item.setAttribute("id", itemId);
        
        groupsListBox.appendChild(item);
      }
    }

    // Set empty text on new groups textbox
    var newGroupTextBox = document.getElementById("group-new");
    newGroupTextBox.emptyText = newGroupTextBox.getAttribute("emptyText");
  },

  selectConnection: function(target) {
    var menulist = document.getElementById("accounts-menulist");
    var connectionKey = target.getAttribute("value");

    this.connection = csChatWrapper.connections[connectionKey];

    menulist.setAttribute("label", target.getAttribute("label"));
    menulist.setAttribute("value", target.getAttribute("value"));
  },

  accept: function() {
    if (!this.connection)
      return;

    if (this.contact)
      this.contactUpdated();
    else
      this.contactAdded();
  },

  _getSelectedGroups: function() {
    var listbox = document.getElementById("groups");
    var listitems = listbox.childNodes;
    var selected = [];

    for each (var item in listitems)
      if (item.checked)
        selected.push(item.getAttribute("label"));

    return selected;
  },

  contactUpdated: function() {
    var alias = document.getElementById("alias").value;
    var groups = this._getSelectedGroups();
    var details = {};

    details.alias = alias;
    details.groups = groups;

    this.connection.updateContact(this.contact.handle, details);
  },

  contactAdded: function() {
    var alias = document.getElementById("alias").value;
    var username = document.getElementById("username").value;
    var groups = this._getSelectedGroups();
    var details = {};

    details.identifier = username;
    details.groups = groups;
    details.alias = alias;

    this.connection.addContact(details);
  },

  usernameInput: function() {
    var username = document.getElementById("username").value;
    if (username == "") {
      document.title = this._defaultTitle;
      this.acceptButton.setAttribute("disabled", "true");
    } else {
      document.title = username;
      this.acceptButton.removeAttribute("disabled");
    }
  }
}
