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
var textchat = null;

function init() {
  if (!"arguments" in window || window.arguments.length < 2) {
    dump("TextChatWindow launched without sufficient arguments!\n");
    window.close();
    return;
  }

  var wrapper = window.arguments[0];
  var channel = window.arguments[1];
  var browser = window.arguments[2];

  textchat = document.getElementById("textchat");
  textchat.init(wrapper, channel, browser);
}

function destroy() {
  textchat.destroy();
}

function reinit(channel) {
  textchat.initWithChannel(channel);
}

function onChatAreaClicked(aEvent) {
  if (!aEvent.isTrusted || aEvent.getPreventDefault() || aEvent.button)
    return true;

  let href = hRefForClickEvent(aEvent, true);
  if (href) {
    let uri = makeURI(href);
    let protocolSvc = Components.classes["@mozilla.org/uriloader/external-protocol-service;1"]
                                .getService(Components.interfaces.nsIExternalProtocolService);
    if (!protocolSvc.isExposedProtocol(uri.scheme) ||
        uri.schemeIs("http") || uri.schemeIs("https")) {
      aEvent.preventDefault();
      openLinkExternally(href);
    }
  }
}

// TODO: Some of the old functionality is yet to be implemented.
