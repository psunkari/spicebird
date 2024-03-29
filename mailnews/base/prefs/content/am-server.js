/* -*- Mode: Java; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * ***** BEGIN LICENSE BLOCK *****
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
 * The Original Code is Mozilla Communicator client code, released
 * March 31, 1998.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998-2003
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   alecf@netscape.com
 *   sspitzer@netscape.com
 *   racham@netscape.com
 *   hwaara@chello.se
 *   bienvenu@nventure.com
 *   Matthew Willis <mattwillis@gmail.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
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

var gServer;
var gObserver;

function onInit(aPageId, aServerId) 
{
  initServerType();

  onCheckItem("server.biffMinutes", "server.doBiff");
  onCheckItem("nntp.maxArticles", "nntp.notifyOn");
  setupMailOnServerUI();
  setupFixedUI();
  if (document.getElementById("server.type").getAttribute("value") == "imap")
    setupImapDeleteUI(aServerId);

  // "STARTTLS, if available" is vulnerable to MITM attacks so we shouldn't
  // allow users to choose it anymore. Hide the option unless the user already
  // has it set.
  var hidden = (document.getElementById("server.socketType").value !=
                Components.interfaces.nsIMsgIncomingServer.tryTLS);
  document.getElementById("connectionSecurityType-1").hidden = hidden;
}

function onPreInit(account, accountValues)
{
  var type = parent.getAccountValue(account, accountValues, "server", "type", null, false);
  hideShowControls(type);

  gObserver= Components.classes["@mozilla.org/observer-service;1"].
             getService(Components.interfaces.nsIObserverService);
  gObserver.notifyObservers(null, "charsetmenu-selected", "other");

  gServer = account.incomingServer;

  if(!account.incomingServer.canEmptyTrashOnExit)
  {
    document.getElementById("server.emptyTrashOnExit").setAttribute("hidden", "true");
    document.getElementById("imap.deleteModel.box").setAttribute("hidden", "true");
  }
}

function initServerType()
{
  var serverType = document.getElementById("server.type").getAttribute("value");
  var propertyName = "serverType-" + serverType;

  var messengerBundle = document.getElementById("bundle_messenger");
  var verboseName = messengerBundle.getString(propertyName);
  setDivText("servertype.verbose", verboseName);

  var isSecureSelected = (document.getElementById("server.socketType").value ==
                          Components.interfaces.nsIMsgIncomingServer.useSSL);

  var protocolInfo = Components.classes["@mozilla.org/messenger/protocol/info;1?type=" + serverType]
                               .getService(Components.interfaces.nsIMsgProtocolInfo);
  document.getElementById("defaultPort").value = protocolInfo.getDefaultServerPort(isSecureSelected);
}

function setDivText(divname, value) 
{
  var div = document.getElementById(divname);
  if (!div) 
    return;
  div.setAttribute("value", value);
}


function onAdvanced()
{
  // Store the server type and, if an IMAP or POP3 server,
  // the settings needed for the IMAP/POP3 tab into the array
  var serverSettings = {};
  var serverType = document.getElementById("server.type").getAttribute("value");
  serverSettings.serverType = serverType;


  if (serverType == "imap")
  {
    serverSettings.dualUseFolders = document.getElementById("imap.dualUseFolders").checked;
    serverSettings.usingSubscription = document.getElementById("imap.usingSubscription").checked;
    serverSettings.useIdle = document.getElementById("imap.useIdle").checked;
    serverSettings.maximumConnectionsNumber = document.getElementById("imap.maximumConnectionsNumber").getAttribute("value");
    // string prefs
    serverSettings.personalNamespace = document.getElementById("imap.personalNamespace").getAttribute("value");
    serverSettings.publicNamespace = document.getElementById("imap.publicNamespace").getAttribute("value");
    serverSettings.serverDirectory = document.getElementById("imap.serverDirectory").getAttribute("value");
    serverSettings.otherUsersNamespace = document.getElementById("imap.otherUsersNamespace").getAttribute("value");
    serverSettings.overrideNamespaces = document.getElementById("imap.overrideNamespaces").checked;
  }
  else if (serverType == "pop3")
  {
    serverSettings.deferGetNewMail = document.getElementById("pop3.deferGetNewMail").checked;
    serverSettings.deferredToAccount = document.getElementById("pop3.deferredToAccount").getAttribute("value");
  }

  window.openDialog("chrome://messenger/content/am-server-advanced.xul",
                    "_blank", "chrome,modal,titlebar", serverSettings);

  if (serverType == "imap")
  {
    document.getElementById("imap.dualUseFolders").checked = serverSettings.dualUseFolders;
    document.getElementById("imap.usingSubscription").checked = serverSettings.usingSubscription;
    document.getElementById("imap.useIdle").checked = serverSettings.useIdle;
    document.getElementById("imap.maximumConnectionsNumber").setAttribute("value", serverSettings.maximumConnectionsNumber);
    // string prefs
    document.getElementById("imap.personalNamespace").setAttribute("value", serverSettings.personalNamespace);
    document.getElementById("imap.publicNamespace").setAttribute("value", serverSettings.publicNamespace);
    document.getElementById("imap.serverDirectory").setAttribute("value", serverSettings.serverDirectory);
    document.getElementById("imap.otherUsersNamespace").setAttribute("value", serverSettings.otherUsersNamespace);
    document.getElementById("imap.overrideNamespaces").checked = serverSettings.overrideNamespaces;
  }
  else if (serverType == "pop3")
  {
    document.getElementById("pop3.deferGetNewMail").checked = serverSettings.deferGetNewMail;
    document.getElementById("pop3.deferredToAccount").setAttribute("value", serverSettings.deferredToAccount);
    var pop3Server = gServer.QueryInterface(Components.interfaces.nsIPop3IncomingServer);
    // we're explicitly setting this so we'll go through the SetDeferredToAccount method
    pop3Server.deferredToAccount = serverSettings.deferredToAccount;
  }
}

function secureSelect()
{
    var serverType   = document.getElementById("server.type").getAttribute("value");
    var protocolInfo = Components.classes["@mozilla.org/messenger/protocol/info;1?type=" + serverType]
                                 .getService(Components.interfaces.nsIMsgProtocolInfo);

    var isSecureSelected = (document.getElementById("server.socketType").value ==
                            Components.interfaces.nsIMsgIncomingServer.useSSL);

    var defaultPort = protocolInfo.getDefaultServerPort(false);
    var defaultPortSecure = protocolInfo.getDefaultServerPort(true);
    var port = document.getElementById("server.port");
    var portDefault = document.getElementById("defaultPort");
    var prevDefaultPort = portDefault.value;

    if (isSecureSelected) {
      portDefault.value = defaultPortSecure;
      if (port.value == "" || (port.value == defaultPort && prevDefaultPort != portDefault.value))
        port.value = defaultPortSecure;
    } else {
        portDefault.value = defaultPort;
        if (port.value == "" || (port.value == defaultPortSecure && prevDefaultPort != portDefault.value))
          port.value = defaultPort;
    }
}

function onCheckItem(changeElementId, checkElementId)
{
    var element = document.getElementById(changeElementId);
    var notify = document.getElementById(checkElementId);
    var checked = notify.checked;

    if(checked && !getAccountValueIsLocked(notify))
      element.removeAttribute("disabled");
    else
      element.setAttribute("disabled", "true");
}

function setupMailOnServerUI()
{ 
   var checked = document.getElementById("pop3.leaveMessagesOnServer").checked;
   var locked = getAccountValueIsLocked(document.getElementById("pop3.leaveMessagesOnServer"));
   document.getElementById("pop3.deleteMailLeftOnServer").disabled = locked || !checked ;
   setupAgeMsgOnServerUI();
}

function setupAgeMsgOnServerUI()
{ 
   var leaveMsgsChecked = document.getElementById("pop3.leaveMessagesOnServer").checked;
   var checked = document.getElementById("pop3.deleteByAgeFromServer").checked;
   var locked = getAccountValueIsLocked(document.getElementById("pop3.deleteByAgeFromServer"));
   document.getElementById("pop3.deleteByAgeFromServer").disabled = locked || !leaveMsgsChecked;
   document.getElementById("daysEnd").disabled = locked || !leaveMsgsChecked;
   document.getElementById("pop3.numDaysToLeaveOnServer").disabled = locked || !checked || !leaveMsgsChecked;
}

function setupFixedUI()
{
  var controls = [document.getElementById("fixedServerName"), 
                  document.getElementById("fixedUserName"),
                  document.getElementById("fixedServerPort")];

  var len = controls.length;  
  for (var i=0; i<len; i++) {
    var fixedElement = controls[i];
    var otherElement = document.getElementById(fixedElement.getAttribute("use"));

    fixedElement.setAttribute("collapsed", "true");
    otherElement.removeAttribute("collapsed");
  }
}

function BrowseForNewsrc()
{
  var newsrcTextBox = document.getElementById("nntp.newsrcFilePath");
  var fp = Components.classes["@mozilla.org/filepicker;1"].createInstance(nsIFilePicker);
  fp.init(window, 
          document.getElementById("browseForNewsrc").getAttribute("filepickertitle"),
          nsIFilePicker.modeSave);

  var currentNewsrcFile;
  try {
    currentNewsrcFile = Components.classes[LOCALFILE_CTRID].createInstance(nsILocalFile);
    currentNewsrcFile.initWithPath(newsrcTextBox.value);
  } catch (e) {
    dump("Failed to create nsILocalFile instance for the current newsrc file.\n");
  }

  if (currentNewsrcFile) {
    fp.displayDirectory = currentNewsrcFile.parent;
    fp.defaultString = currentNewsrcFile.leafName;
  }

  fp.appendFilters(nsIFilePicker.filterAll);

  if (fp.show() != nsIFilePicker.returnCancel)
    newsrcTextBox.value = fp.file.path;
}

function setupImapDeleteUI(aServerId)
{
  // read delete_model preference
  var deleteModel = document.getElementById("imap.deleteModel").getAttribute("value");
  selectImapDeleteModel(deleteModel);

  // read trash_folder_name preference
  var trashFolderName = getTrashFolderName();

  // set folderPicker menulist
  var trashPopup = document.getElementById("msgTrashFolderPopup");
  trashPopup._teardown();
  trashPopup._parentFolder = GetMsgFolderFromUri(aServerId);
  trashPopup._ensureInitialized();

  var trashFolder = GetMsgFolderFromUri(aServerId+"/"+trashFolderName);
  try {
    trashPopup.selectFolder(trashFolder);
  } catch(ex) {
    trashPopup.parentNode.setAttribute("label", trashFolder.prettyName);
  }
  trashPopup.parentNode.folder = trashFolder;
}

function selectImapDeleteModel(choice)
{
  // set deleteModel to selected mode
  document.getElementById("imap.deleteModel").setAttribute("value", choice);

  switch (choice)
  {
    case "0" : // markDeleted
      // disable folderPicker
      document.getElementById("msgTrashFolderPicker").setAttribute("disabled", "true");
      break;  
    case "1" : // moveToTrashFolder
      // enable folderPicker
      document.getElementById("msgTrashFolderPicker").removeAttribute("disabled");
      break;
    case "2" : // deleteImmediately
      // disable folderPicker
      document.getElementById("msgTrashFolderPicker").setAttribute("disabled", "true");
      break;
    default :
      dump("Error in enabling/disabling server.TrashFolderPicker\n");
      break;
  }
}

// Capture any menulist changes from folderPicker
function folderPickerChange(aEvent)
{
  var folder = aEvent.target._folder;
  var folderPath = getFolderPathFromRoot(folder);

  // Set the value to be persisted.
  document.getElementById("imap.trashFolderName")
          .setAttribute("value", folderPath);

  // Update the widget to show/do correct things even for subfolders.
  var trashFolderPicker = document.getElementById("msgTrashFolderPicker");
  trashFolderPicker.setAttribute("label", folder.prettyName);
}

/** Generate the relative folder path from the root. */
function getFolderPathFromRoot(folder)
{
  var path = folder.name;
  var parentFolder = folder.parent;
  while (parentFolder && parentFolder != folder.rootFolder) {
    path = parentFolder.name + "/" + path;
    parentFolder = parentFolder.parent;
  }
  // IMAP Inbox URI's start with INBOX, not Inbox.
  return path.replace(/^Inbox/, "INBOX");
}

// Get trash_folder_name from prefs
function getTrashFolderName()
{
  var trashFolderName = document.getElementById("imap.trashFolderName").getAttribute("value");
  // if the preference hasn't been set, set it to a sane default
  if (!trashFolderName) {
    trashFolderName = "Trash";
    document.getElementById("imap.trashFolderName").setAttribute("value",trashFolderName);
  }
  return trashFolderName;
}

/**
 * Called when someone changes the biff-minutes value.  We'll check whether it's
 * zero, and if so, disable the biff checkbox as well, otherwise enable the box
 *
 * @param aValue  the new value for the textbox
 */
function onBiffMinChange(aValue)
{
  document.getElementById("server.doBiff").checked = (aValue != 0);
}
