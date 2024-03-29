/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Thunderbird Feature Configurator.
 *
 * The Initial Developer of the Original Code is
 * Mozilla Messaging, Inc.
 * Portions created by the Initial Developer are Copyright (C) 2009
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   David Ascher <dascher@mozillamessaging.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

const Cc = Components.classes;
const Ci = Components.interfaces;
const Cu = Components.utils;
Cu.import("resource://app/modules/errUtils.js");
Cu.import("resource://gre/modules/iteratorUtils.jsm");

var FeatureConfigurator = {
  updateStatus: function() {
    try {
      let dom = this.parentWin.document;
      let toolbar = dom.getElementById("mail-bar3");
      let useSmartFolders = this.parentWin.gFolderTreeView.mode == "smart";
      if (useSmartFolders) {
        $("#useSmartFolders").attr("invisible", true);
        $("#useAllFolders").removeAttr("invisible");
        $("#using-smart-folders").removeAttr("invisible");
        $("#using-all-folders").attr("invisible", true);
      } else {
        $("#useAllFolders").attr("invisible", true);
        $("#useSmartFolders").removeAttr("invisible");
        $("#using-smart-folders").attr("invisible", true);
        $("#using-all-folders").removeAttr("invisible");
      }

      let allSync = true;
      let noneSync = true;

      let servers = Cc["@mozilla.org/messenger/account-manager;1"].
                      getService(Ci.nsIMsgAccountManager).allServers;

      for each (let server in fixIterator(servers, Ci.nsIMsgIncomingServer)) {
        if (server.type != "imap")
          continue;
        server = server.QueryInterface(Ci.nsIImapIncomingServer);
        let allFolders = Cc["@mozilla.org/supports-array;1"].
                           createInstance(Ci.nsISupportsArray);

        server.rootFolder.ListDescendents(allFolders);
        for each (let folder in fixIterator(allFolders, Ci.nsIMsgFolder)) {
          if (folder.getFlag(Ci.nsMsgFolderFlags.Offline))
            noneSync = false;
          else
            allSync = false;
        }
      }
      // Display the current status
      let allSynced = $("#all-synced");
      let noneSynced = $("#none-synced");
      let someSynced = $("#some-synced");

      let syncAll = $("#sync-all");
      let syncNone = $("#sync-none");

      if (allSync) {
        allSynced.removeAttr("invisible");
        noneSynced.attr("invisible", true);
        someSynced.attr("invisible", true);
        syncAll.attr("invisible", true);
        syncNone.removeAttr("invisible");
      } else if (noneSync) {
        noneSynced.removeAttr("invisible");
        allSynced.attr("invisible", true);
        someSynced.attr("invisible", true);
        syncAll.removeAttr("invisible");
        syncNone.attr("invisible", true);
      } else {
        someSynced.removeAttr("invisible");
        allSynced.attr("invisible", true);
        noneSynced.attr("invisible", true);
        syncAll.removeAttr("invisible");
        syncNone.removeAttr("invisible");
      }

      $("#sync-none").attr("invisible", noneSync);
    } catch (e) {
      logException(e);
    }
  },

  setSyncStatus: function(sync) {
    try {
      let servers = Cc["@mozilla.org/messenger/account-manager;1"].
                      getService(Ci.nsIMsgAccountManager).allServers;

      for each (let server in fixIterator(servers, Ci.nsIMsgIncomingServer)) {
        if (server.type != "imap")
          continue;
        server = server.QueryInterface(Ci.nsIImapIncomingServer);
        let allFolders = Cc["@mozilla.org/supports-array;1"].
                           createInstance(Ci.nsISupportsArray);

        server.offlineDownload = sync;
        server.rootFolder.ListDescendents(allFolders);
        for each (let folder in fixIterator(allFolders, Ci.nsIMsgFolder)) {
          if (sync)
            folder.setFlag(Ci.nsMsgFolderFlags.Offline);
          else
            folder.clearFlag(Ci.nsMsgFolderFlags.Offline);
        }
      }
      this.updateStatus();
      $("#imap_status").effect("highlight");;
    } catch (e) {
      logException(e);
    }
  },

  setup: function(parentWin) {
    this.parentWin = parentWin;
    try {
      let dis = this;
      $("#useSmartFolders").click(function() {
        dis.parentWin.gFolderTreeView.mode = "smart";
        dis.updateStatus();
        $("#foldermode_status").effect("highlight", {}, 1000);
      });
      $("#useAllFolders").click(function() {
        dis.parentWin.gFolderTreeView.mode = "all";
        dis.updateStatus();
        $("#foldermode_status").effect("highlight", {}, 1000);
      });

      $("#sync-none").click(function() dis.setSyncStatus(false));
      $("#sync-all").click(function() dis.setSyncStatus(true));

      let servers = Cc["@mozilla.org/messenger/account-manager;1"].
                      getService(Ci.nsIMsgAccountManager).allServers;

      let ul = document.getElementById("account_list");
      for each (let server in fixIterator(servers, Ci.nsIMsgIncomingServer)) {
        if (server.type != "imap")
          continue;
        let li = document.createElement("li");
        li.setAttribute("class", "button");
        li.textContent = server.prettyName;
        let aServer = server;
        $(li).click(function() {
          try {
            dis.parentWin
               .openDialog("chrome://messenger/content/AccountManager.xul",
                           "AccountManager",
                           "chrome,centerscreen,modal,titlebar",
                           { server: aServer, selectPage: "am-offline.xul"});
          } catch (e) {
            logException(e);
          }
        });
        ul.appendChild(li);
      }
      this.updateStatus();
    } catch (e) {
      logException(e);
    }
  }
}


/**
 * addEventListener betrayals compel us to establish our link with the
 * outside world from inside.  NeilAway suggests the problem might have
 * been the registration of the listener prior to initiating the load.  Which
 * is odd considering it works for the XUL case, but I could see how that might
 * differ.  Anywho, this works for now and is a delightful reference to boot.
 */
function reachOutAndTouchFrame() {
  try {
    let us = window.QueryInterface(Ci.nsIInterfaceRequestor)
                   .getInterface(Ci.nsIWebNavigation)
                   .QueryInterface(Ci.nsIDocShellTreeItem);
    let parentWin = us.parent
                      .QueryInterface(Ci.nsIInterfaceRequestor)
                      .getInterface(Ci.nsIDOMWindow);
    FeatureConfigurator.setup(parentWin);
  } catch (e) {
    logException(e);
  }
}
