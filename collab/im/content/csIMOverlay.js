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

const gIMAppName = "im";
const mozIJSSubScriptLoader = Components.interfaces.mozIJSSubScriptLoader;
const gIMVersion = "2008.11.04";

var gConversationManager = {};
var gTelepathy = {};
var gIMStatusService = {};

var gIMPromptService;
var gIMStringBundle;
var gIMCollabHasFocus = false;

var gIMChatLogService = {};

// Enable app status in appInfo component
var imAppInfoClass = Components.classes["@synovel.com/collab/im-appinfo;1"];
if (imAppInfoClass) {
    var imAppInfo = imAppInfoClass.getService(Components.interfaces.csIAppInfo);
    if (imAppInfo)
        imAppInfo.enabled = true;
}

var csTPLoadObserver = {
  observe: function (aSubject, aTopic, aCurrentApp) {
    if (aTopic == "csTPLoadComplete") {
      loadIMPreferences();
      doAutoLogin();
    }
  }
};

var chatsTabType = {
  name: "chats",
  panelId: "tabpanel-im",

  modes: {
    im: {
      type: "im",
      maxTabs: 1,

      openTab: function(aTab, aArgs) {
        getLinkedTabPanel(aTab).controllers.appendController(imController);
      },
      showTab: function(aTab) {
        var focusedElement = aTab.focusedElement;
        if (!focusedElement)
          focusedElement = document.getElementById("sidebar-im-box");
        focusedElement.focus();

        clearIMFlash();
      },
      persistTab: function(aTab) {},
      restoreTab: function(aTab) {},
      saveTabState: function(aTab) {},
      closeTab: function(aTab) {},
      onTitleChanged: function(aTab, aTabNode) {}
    }
  }
};

function OnLoadCollabIM ()
{
  var tabcollab = document.getElementById("tabcollab");
  if (tabcollab)
    tabcollab.registerTabType(chatsTabType);

  gObserverService.addObserver(csTPLoadObserver, "csTPLoadComplete" ,false);

  gIMStatusService = Components.classes["@synovel.com/collab/im/imstatusservice;1"]
                               .getService(Components.interfaces.csIIMStatusService);
  gIMPromptService = Components.classes["@mozilla.org/embedcomp/prompt-service;1"]
                               .getService(Components.interfaces.nsIPromptService);
  gIMStringBundle = document.getElementById("bundle_im");

  loadScripts();

  var contactList = document.getElementById("sidebar-im-box");
  contactList.hideToolbar();

  gIMChatLogService = Components.classes["@synovel.com/collab/im/chatlogservice;1"]
                                .getService(Components.interfaces.csIChatLogService);

  window.addEventListener("unload", OnUnload, true);
}

function addIMTab(foreground)
{
  let tabcollab = document.getElementById("tabcollab");
  if (typeof foreground == "undefined")
    foreground = false;

  tabcollab.openTab("im", { background: !foreground,
                            title: getLocaleString([["IMTabTitle"]]) });
}

function removeIMTab()
{
  let tabcollab = document.getElementById("tabcollab");
  let tabinfo = tabcollab.getTabInfoForCurrentOrFirstModeInstance(chatsTabType.modes.im);
  if (!tabinfo)
    return;

  tabcollab.closeTab(tabinfo);
}

function doAutoLogin()
{
  try {
    var prefBranch = Components.classes["@mozilla.org/preferences-service;1"]
                               .getService(Components.interfaces.nsIPrefService)
                               .getBranch('collab.im.');

    var autologin = false;
    autologin = prefBranch.getBoolPref('autologin');
  } catch (ex) { }

  if (autologin) {
    var autologinStatus = 'available';
    var messages = {};
    try {
      autologinStatus = prefBranch.getCharPref("autologin.status");
      for (var key = 0; key < 10; key++) {
        var st = prefBranch.getCharPref('statuses.' + key + '.status');
        var sm = prefBranch.getCharPref('statuses.' + key + '.message');
        messages[st] = sm;
      }
    } catch (ex) {}

    var statusMessage = messages[autologinStatus]?
                        messages[autologinStatus]: 'Spicebird!';
    gTelepathy.setGlobalStatus(autologinStatus, statusMessage);
  }
}

function loadIMPreferences()
{
  var prefBranch = Components.classes["@mozilla.org/preferences-service;1"]
                             .getService(Components.interfaces.nsIPrefService)
                             .getBranch('collab.im.');

  var checked = false;
  try {
    checked = prefBranch.getBoolPref("showOfflineContacts");
  }
  catch (ex) {}

  document.getElementById("im-show-offline").setAttribute("checked", checked);
  doShowOffline();

  // Check first install
  var firstInstall;
  try {
    firstInstall = prefBranch.getBoolPref('firstInstall');
  } catch(ex) {
    firstInstall = true;
  }

  if (firstInstall) {
    prefBranch.setBoolPref('firstInstall', false);
    // TODO: Show account setup dialog after telepathy managers are loaded.
    // showAccountSetup();
  }

  // See if we can upgrade from
  // previous version of Spicebird IM
  //
  // Note that we were not setting the collab.im.version
  // preference in the old days... so in the absence of appVersion
  // Lets just try to upgrade from 0.4

  var comparator = Components.classes["@mozilla.org/xpcom/version-comparator;1"]
                             .getService(Components.interfaces.nsIVersionComparator);
  var version = "2008.01.13";
  try {
    version = prefBranch.getCharPref('version');
  } catch(ex) {}

  if(!version || comparator.compare(version, gIMVersion) < 0)
    performUpgrade(version);
}

function loadScripts()
{
  var telepathyScripts = ['telepathy/telepathy.js', 'telepathy/ui.js',
                          'telepathy/accounts.js', 'telepathy/functions.js',
                          'telepathy/utils.js'];

  for each (var script in telepathyScripts) {
    Components.classes['@mozilla.org/moz/jssubscript-loader;1']
              .getService(mozIJSSubScriptLoader)
              .loadSubScript('chrome://im/content/' + script, gTelepathy);
  }
  gTelepathy.init();

  Components.classes['@mozilla.org/moz/jssubscript-loader;1']
            .getService(mozIJSSubScriptLoader)
            .loadSubScript('chrome://im/content/conversationManager.js', gConversationManager);
  gConversationManager.init();

  gTelepathy.load();
}

window.addEventListener("blur", function() {
                                  window.gIMCollabHasFocus = false;
                                }, true);
window.addEventListener("focus", function() {
                                  window.gIMCollabHasFocus = true;
                                }, true);
window.addEventListener("load", OnLoadCollabIM, true);

function OnUnload(event)
{
  if (event.originalTarget != window.document)
    return;

  gTelepathy.finish();
}

function toggleShowTimestamp()
{
  gConversationManager.toggleShowTimestamp();
}

var dragDropObserver = {
  getSupportedFlavours: function () {
    var flavours = new FlavourSet();
    flavours.appendFlavour('text/html');
    flavours.appendFlavour('text/unicode');
    return flavours;
  },

  onDrop: function(event, dropdata, session) {
    if (!dropdata.data)
      return;

    var contentType = dropdata.flavour.contentType;

    switch(contentType) {
      case 'text/html':
      case 'text/unicode':
        var editor = event.currentTarget;
        var htmlEditor = editor.getHTMLEditor(editor.contentWindow);

        htmlEditor.insertHTML(dropdata.data);
        break;

      default:
        break;
        //TODO: intimate user?
    }
  }
};

function handleDragDrop(event)
{
  nsDragAndDrop.drop(event, dragDropObserver);
  event.stopPropagation();
}

function showAccountSetup(aPrefKey)
{
  //TODO: Wait until telepathy managers load
  gTelepathy.accountSetup(aPrefKey);
}

function addIMContact()
{
  window.openDialog("chrome://im/content/imContactEditDialog.xul",
                    "", "chrome", gTelepathy);

}

function getLocaleString(aStringIds)
{
  var localeString = '';

  for each (var stringId in aStringIds) {
    try {
      if (stringId.length > 1)
        localeString += gIMStringBundle.getFormattedString(stringId[0], stringId.slice(1));
      else
        localeString += gIMStringBundle.getString(stringId[0]);
    } catch(ex) {
        localeString += stringId[0];
    }

    localeString += '\n\n';
  }

  // chop trailing '\n\n'
  localeString = localeString.substring(0, localeString.length-2);

  return localeString;
}

var imController = {
  commands: {
    "cmd_new": true,
    "cmd_im_add_contact": true,
    "cmd_im_edit_contact": true,
    "button_delete": true,
    "cmd_im_contact_info": true,
    "cmd_im_chat": true,
    "cmd_im_account": true,
    "cmd_im_status": true,
    "cmd_im_history": true
  },

  updateCommands: function() {
    if (gCurrentApplication != gIMAppName)
      return;
    for (var command in this.commands)
      goUpdateCommand(command);
  },

  supportsCommand: function(aCommand) {
    if (aCommand in this.commands)
      return true;
    return false;
  },

  isCommandEnabled: function(aCommand) {
    var tree = document.getElementById("sidebar-im-box").mTree;
    switch(aCommand) {
      case "cmd_new":
      case "cmd_im_add_contact":
      case "cmd_im_account":
      case "cmd_im_status":
      case "cmd_im_history":
        return true;
      case "cmd_im_edit_contact":
      case "button_delete":
      case "cmd_im_contact_info":
      case "cmd_im_chat":
        return tree && tree.view.selection.count > 0 && isFocusInContactsList();
      return false;
    }
  },

  doCommand: function(aCommand) {
    var contactList = document.getElementById("sidebar-im-box");
    switch(aCommand) {
      case "cmd_im_add_contact":
        contactList.addContact();
        break;
      case "cmd_im_edit_contact":
        contactList.editContact();
        break;
      case "button_delete":
        contactList.deleteContact();
        break;
      case "cmd_im_contact_info":
        contactList.showContactInfo();
        break;
      case "cmd_im_account":
        gTelepathy.accountSetup();
        break;
      case "cmd_im_chat":
      case "cmd_new":
        contactList.chatWithContact();
        break;
      case "cmd_im_history":
	showHistoryWindow();
	break;
    }
  }
};

function doShowOffline()
{
  var checked = document.getElementById("im-show-offline")
                        .getAttribute("checked");

  var prefBranch = Components.classes["@mozilla.org/preferences-service;1"]
                             .getService(Components.interfaces.nsIPrefService)
                             .getBranch('collab.im.');
  prefBranch.setBoolPref("showOfflineContacts", 
                         (checked == "true") ? true : false);

  var im_list = document.getElementById("sidebar-im-box");
  var ab_list = document.getElementById("sidebar-contacts-im-box");

  if (im_list)
    im_list.setAttribute("showoffline", checked);

  if (ab_list)
    ab_list.setAttribute("showoffline", checked);
}

function isFocusInContactsList()
{
  var item = document.commandDispatcher.focusedElement;
  var contactList = document.getElementById("sidebar-im-box");
  while (item && item != top) {
    if (item.isEqualNode(contactList))
      return true;
    item = item.parentNode;
  }
  return false;
}

function flashIMTab()
{
  let tabcollab = document.getElementById("tabcollab");
  let tabinfo = tabcollab.getTabInfoForCurrentOrFirstModeInstance(chatsTabType.modes.im);
  if (!tabinfo)
    return;

  tabcollab.setTabNeedsAttention(tabinfo, true);
}

function clearIMFlash()
{
  let tabcollab = document.getElementById("tabcollab");
  let tabinfo = tabcollab.getTabInfoForCurrentOrFirstModeInstance(chatsTabType.modes.im);
  if (!tabinfo)
    return;

  tabcollab.setTabNeedsAttention(tabinfo, false);
}

function performUpgrade(aVersion)
{
  var tmpPrefBranch = Components.classes["@mozilla.org/preferences-service;1"]
                        .getService(Components.interfaces.nsIPrefService)
                        .getBranch(null);

  // Upgrade from Spicebird 0.4
  // XMPP4Moz accounts and  addressbook integration

  if (aVersion == '2008.01.13') {

    var rootDirectoryBranch;
    try {
      rootDirectoryBranch = tmpPrefBranch.getCharPref("xmpp.IMDirectoryBranch");
    } catch(ex) {
      dump('INFO: Cannot find old addressbook directory. No upgrade done.\n');
      tmpPrefBranch.setCharPref('collab.im.version', gIMVersion);
      return;
    }

    var filename;
    try {
      filename = tmpPrefBranch.getCharPref(rootDirectoryBranch + ".filename");
    } catch(ex) {
      dump('ERROR: Cannot find old addressbook file. No upgrade done.\n');
      tmpPrefBranch.setCharPref('collab.im.version', gIMVersion);
      return;
    }

    var oldIMAbURI = 'moz-abmdbdirectory://' + filename;
    var oldIMDirectory = GetDirectoryFromURI(oldIMAbURI);
    var curIMDirectory = GetDirectoryFromURI(gTelepathy.gIMAddressbookURI);

    for (var i = 0; i < oldIMDirectory.addressLists.length; i++) {
      var mailList = oldIMDirectory.addressLists
                       .queryElementAt(i, Components.interfaces.nsIAbDirectory);
      curIMDirectory.addMailList(mailList);
    }

    var abManager = Components.classes["@mozilla.org/abmanager;1"]
                              .getService(Components.interfaces.nsIAbManager);
    abManager.deleteAddressBook(oldIMAbURI);

    /*
     * Migrate xmpp accounts as telepathy accounts
     * if a manager which provides jabber is available
     */
    function migrateXMPPAccounts(aJabberManagers)
    {
      var defaultJabberManager = aJabberManagers[0];

      var prefBranch = Components.classes["@mozilla.org/preferences-service;1"]
                         .getService(Components.interfaces.nsIPrefService)
                         .getBranch(null);

      var keys = prefBranch.getChildList('xmpp.account.', {})
                           .map(function(item) {try {return item.split('.')[2];}
                                                catch(ex) {return undefined;}})
                           .filter(function(item) {return item});

      var seen = [];
      for each (var key in keys) {
        if (seen[key])
          return;

        seen[key] = true;

        // Currently we only support Gabble and Haze for XMPP
        // The code below does a direct mapping of account setting between
        // the XMPP4Moz based 0.4 and the Spicebird 0.7

        try {
          var accountKey = 'xmpp.account.' + key;
          var params = {};

          // Connection manager (Gabble or Haze)
          params.manager  = {
            type: 'char',
            value: defaultJabberManager
          };

          // Protocol is jabber
          params.protocol = {
            type: 'char',
            value: 'jabber'
          };

          // Account
          params.account  = {
            type: 'char',
            value: prefBranch.getCharPref(accountKey + '.address')
          };

          // Server
          params.server   =  {
            type: 'char',
            value: prefBranch.getCharPref(accountKey + '.connectionHost')
          };

          // Port
          var port;
          try {
            port = prefBranch.getIntPref(accountKey + '.connectionPort');
          } catch(ex) {}

          // XMPP4Moz for what ever reasons stored 443 as port for gtalk,
          // it should actually be 5223 with old-ssl enabled.
          if (port == 443 && params.server.value == 'talk.google.com') {
            port = 5223;
          }

          params.port = {
            type: 'int',
            value: port
          };

          // SSL
          var ssl = 0;
          try {
            ssl = prefBranch.getIntPref(accountKey + '.connectionSecurity');
          } catch(ex) {}

          params['require-encryption'] = {
            type: 'bool',
            value: (ssl ?  true : false)
          };

          if (port == 5223 && ssl) {
            params['old-ssl'] = {
              type: 'bool',
              value: true
            };
          }

          gTelepathy.createIMAccount(params);
          prefBranch.deleteBranch(accountKey);
        } catch(ex) {
          dump('INFO: Ignoring account with key: ' + key + '. Ex: ' + ex + '\n');
        }
      }
      prefBranch.deleteBranch('xmpp');
    }

    gTelepathy.getProtocolManagers('jabber', migrateXMPPAccounts);
    tmpPrefBranch.setCharPref('collab.im.version', gIMVersion);
  }
}

function setGlobalStatus(event)
{
  // Do we have any accounts configured?
  if (gTelepathy.gAccounts.length == 0) {
    gTelepathy.displayAlert(getLocaleString([["IMNoAccountsConfigured"]]));
    gTelepathy.accountSetup();
    return;
  }

  // Do we have any enabled accounts?
  if (gTelepathy.enabledAccountsCount() == 0) {
    gTelepathy.displayAlert(getLocaleString([["IMNoAccountsEnabled"]]));
    return;
  }

  var target = event.originalTarget;
  if (target.nodeName == 'command')
    target = event.sourceEvent.originalTarget;

  var status = target.getAttribute("im-status");
  var message = target.getAttribute("im-message");

  if (!message)
    message = gTelepathy.gMyPresence.message;

  if (status)
    gTelepathy.setGlobalStatus(status, message);
}

function showHistoryWindow()
{
  window.openDialog("chrome://im/content/csChatHistory.xul",
                    "", "chrome");
}
