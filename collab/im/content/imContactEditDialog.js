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

var gTelepathy = null;
var gConnectionID = null;
var gRemoteUser = null;
var gUserAlias = null;

function onLoad() {
  gTelepathy = window.arguments[0];
  gConnectionID = window.arguments[1];
  gRemoteUser = window.arguments[2];
  gUserAlias = window.arguments[3];

  if (!gTelepathy) {
    dump("gTelepathy is not defined in the edit contact window!");
    window.close();
  }

  // Populate the accounts popup
  var menupopup = document.getElementById("accounts-popup");
  menupopup.populate();
  
  // If we have a connection id passed, then
  // select it by default, else select the first available connection
  var accounts = document.getElementById("accounts-menulist");
  var item = null;
  if (gConnectionID)
    item = document.getAnonymousElementByAttribute(menupopup, "value", gConnectionID);
  else
    item = document.getAnonymousElementByAttribute(menupopup, "type", "im-connection");

  if (item)
    selectConnection(item);

  // If we have remote user information, fill it.
  var username = document.getElementById("username");
  if (gRemoteUser && gRemoteUser != "")
    username.value = gRemoteUser;

  // If we have alias of the remote user, fill it.
  var alias = document.getElementById("alias");
  if (gUserAlias && gUserAlias != "")
    alias.value = gUserAlias;

  // If account and user were passed
  // let the user edit the alias
  if (gConnectionID && gRemoteUser) {
    accounts.setAttribute("disabled", "true");
    username.setAttribute("readonly", "true");
    document.getElementById("alias-row").removeAttribute("collapsed");
  }
}

function selectConnection(target) {
  var menulist = document.getElementById("accounts-menulist");
  
  menulist.setAttribute("label", target.getAttribute("label"));
  menulist.setAttribute("value", target.getAttribute("value"));
}

function onDialogAccept() {
  var connection = document.getElementById("accounts-menulist").value;
  var username = document.getElementById("username").value;
  var alias = document.getElementById("alias").value;

  if (gRemoteUser && gRemoteUser == username)
    onEditContact(alias);
  else
    gTelepathy.imAddNewContact(connection, username, alias);
}

function onEditContact(aAlias) {
  gTelepathy.imUpdateContactAlias(gConnectionID, gRemoteUser, aAlias);
}

