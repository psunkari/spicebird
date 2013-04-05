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

const IM_ENTER_KEYCODE = 13; 
const IM_BACKSPACE_KEYCODE = 8; 

var session;
var account;
var address;
var channel;
var showTimestamps;
var setFocus;

var chatwindow;
var closeInitiated;

var gIMPromptService;
var gIMStringBundle;

function init() {
  setFocus = false;

  if ("arguments" in window && window.arguments.length == 2) {
    session = window.arguments[0];
    setFocus = window.arguments[1];
  }
  else {
    dump('ERROR: Insufficient arguments to chatWindow.xul\n');
    return;
  }

  chatwindow = document.getElementById("chatwindow");
  chatwindow.session = session;

  closeInitiated = false;
  account = session.account;
  address = session.address;
  channel = session.channel;
  showTimestamps = session.showTimestamps;

  window.addEventListener('focus', function() {chatwindow.focus();}, false);

  if (setFocus)
    setTimeout(window.focus, 0);
  else
    window.opener.gConversationManager.setUnread(account, address);

  gIMPromptService = Components.classes["@mozilla.org/embedcomp/prompt-service;1"]
                               .getService(Components.interfaces.nsIPromptService);

  gIMStringBundle = document.getElementById("bundle_im");

}

function destroy() {
  if (closeInitiated)
    return;

  if (typeof(window.opener.gConversationManager.closeConversation) == 'function')
    window.opener.gConversationManager.closeConversation(account, address);
}

function updateChannel(aChannel) {
  channel = aChannel;
  chatwindow.updateChannel(aChannel);
}

function closeConversation() {
  chatwindow.closeSession();

  closeInitiated = true;
  window.close();
}

function toggleShowTimestamp() {
  showTimestamps = !showTimestamps;
  chatwindow.setTimestampState(showTimestamps);
}

function handleDragDrop(event) {
  nsDragAndDrop.drop(event, dragDropObserver);
  event.stopPropagation();
}

function setChatState(chatstate) {
  chatwindow.setChatState(chatstate);
}

