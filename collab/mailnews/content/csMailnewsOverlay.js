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
# The Original Code is Mozilla Communicator client code, released
# March 31, 1998.
#
# The Initial Developer of the Original Code is
# Netscape Communications Corporation.
# Portions created by the Initial Developer are Copyright (C) 1998-1999
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#  Prasad Sunkari <prasad@synovel.com>
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
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

const gMailAppName = "mailnews";

// Enable app status in appInfo component
var mailnewsAppInfoClass = Components.classes["@synovel.com/collab/mailnews-appinfo;1"];
if (mailnewsAppInfoClass) {
    var mailnewsAppInfo = mailnewsAppInfoClass.getService(Components.interfaces.csIAppInfo);
    if (mailnewsAppInfo)
        mailnewsAppInfo.enabled = true;
}

function switchToMailnews() {
  let mode = "folder";
  let folder = null;
  try {
    let accountManager = Components.classes["@mozilla.org/messenger/account-manager;1"]
                          .getService(Components.interfaces.nsIMsgAccountManager);
    folder = GetInboxFolder(accountManager.defaultAccount.incomingServer);
  } catch (ex) {}
  
  let tabcollab = document.getElementById("tabcollab");
  tabcollab.openTab("folder", {switchToExisting: true, folder: folder});
}

function OnLoadCollabMessenger() {
  OnLoadMessenger();

  addCommonController(MailnewsGlobalController);
  MailnewsGlobalController.updateCommands();

  // Add a clear notification signal upon unloading of messagepane contents
  document.getElementById("messagepane")
          .addProgressListener(messagePaneProgressListener);
}

var messagePaneProgressListener = {
  QueryInterface: function(aIID)
  { return this; },
  
  onLocationChange: function(webProgress, request, location)
  {
    let observer = Components.classes["@mozilla.org/observer-service;1"]
                             .getService(Components.interfaces.nsIObserverService);
    observer.notifyObservers(window.document, "MsgClearNotifications", 0);
  },

  onProgressChange: function(webProgress, request, curSelfProgress,
                             maxSelfProgress, curTotalProgress, maxTotalProgress)
  { },

  onSecurityChange: function(webProgress, request, state)
  { },

  onStateChange: function (webProgress, request, stateFlags, status)
  { },

  onStatusChange: function (webProgress, request, status, message)
  { }
}

addEventListener("load", OnLoadCollabMessenger, true);
addEventListener("unload", OnUnloadMessenger, false);

