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

var InfoDialog = {
  onLoad: function() {
    csChatWrapper = window.arguments[0];

    this.connectionKey = window.arguments[1];
    this.handle = window.arguments[2];
  
    if (!csChatWrapper || !this.connectionKey || !this.handle)
      window.close();
  
    var connection = csChatWrapper.connections[this.connectionKey];
    if (!connection)
      return;

    var contact = connection.contacts[this.handle];
    if (!contact)
      return;

    var self = this;
    this._updateListener =  csChatWrapper.registerContactUpdateListener(
                              function(contact, detail) {
                                self.onContactUpdated(contact, detail);
                              });

    document.title = contact.alias;
    document.getElementById("accounts-label")
            .setAttribute("value", connection.myself.identifier);

    this.onContactUpdated(contact, null);
  },

  onContactUpdated: function(contact, detail) {
    if (contact.connectionKey != this.connectionKey || contact.handle != this.handle)
      return;

    document.getElementById("username-label")
            .setAttribute("value", contact.identifier);
    document.getElementById("alias-label")
            .setAttribute("value", contact.alias);
    document.getElementById("status-image")
            .setAttribute("chat-status", csChatWrapper.statusMap[contact.presenceStatus]);

    var statusMessage = contact.presenceMessage;
    if (statusMessage === undefined || contact.presenceMessage == "") {
      var bundle = document.getElementById("chat-status-bundle");
      try {
        statusMessage = bundle.getString(contact.presenceStatus);
      } catch(ex) {
        statusMessage = bundle.getString("status" + contact.presenceType);
      }
    }
    document.getElementById("status-message").setAttribute("value", statusMessage);
  },

  onDestroy: function() {
    csChatWrapper.unregisterContactUpdateListener(this._updateListener);
  }
}
