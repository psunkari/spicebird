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

/*
 * Todo:
 * - Show/Edit local user status
 * - Provide preferences for: IM_WINDOWS_*_MAX, getAttentionOnUnread
 */

const Cc = Components.classes;
const Ci = Components.interfaces;

var prefBranch;

const IM_WINDOWS_ROWS_MAX = 2;
const IM_WINDOWS_COLS_MAX = 3;

const IM_WINDOWS_MAX = IM_WINDOWS_ROWS_MAX * IM_WINDOWS_COLS_MAX;

const IM_OUT = 'outgoing';
const IM_IN = 'incoming';

const IM_WINDOW_DETACHED = 0;
const IM_WINDOW_DOCKED = 1;
var defaultWindowStyle = IM_WINDOW_DETACHED;

const soundAlertSystemType = "_moz_mailbeep";
var getAttentionOnUnread = true;
var soundAlertEnabled = true;
var soundAlertOnNewMessage = false;
var soundAlertType = 0;
var soundAlertURI = null;

// currentColsPerRow=3 => 3 windows per row
var currentColsPerRow;
// currentRow=0 => Row 1
var currentRow;

var lastUsedKey = [];
var conversationHash = {};
var dockedConversationsCount = 0;
var currentConversationKey = null;

var contactInfoList = [];

var imObserverService;

function init() {
  // All rows are collapsed
  currentRow = -1;
  currentColsPerRow = IM_WINDOWS_COLS_MAX;

  prefBranch = Cc["@mozilla.org/preferences-service;1"]
                 .getService(Ci.nsIPrefService)
                 .getBranch('collab.im.')
                 .QueryInterface(Ci.nsIPrefBranch2);

  loadIMPanel();
  loadIMPrefs();

  // Add pref observers
  var self = this;
  prefBranch.addObserver("alerts.", {observe: self.loadIMPrefs}, false);
  prefBranch.addObserver("startdocked", {observe: self.loadIMPrefs}, false);

  imObserverService = Cc["@mozilla.org/observer-service;1"]
                        .getService(Ci.nsIObserverService);
                                                             
}

function checkIMTab(switchToIM) {
  var imtab = document.getElementById('tab-im');
  var switchToIMCmd = document.getElementById('switch-to-im');

  if (dockedConversationsCount == 0) {
    removeIMTab();
    switchToIMCmd.setAttribute('hidden', true);
    switchToIMCmd.setAttribute('disabled', true);
    setCurrentApp(gContactsAppName);
  } else {
    addIMTab(switchToIM);
    switchToIMCmd.removeAttribute('hidden');
    switchToIMCmd.removeAttribute('disabled');
  }
}

function loadIMPrefs() {
  try {
    soundAlertEnabled = prefBranch.getBoolPref("alerts.sound");
  } catch (ex) {
    prefBranch.setBoolPref("alerts.sound", true);
  }

  if (soundAlertEnabled) {
    try {
      soundAlertType = prefBranch.getIntPref("alerts.sound.type");
    } catch (ex) {}

    if (soundAlertType == 1) {
      try {
        var url = prefBranch.getCharPref("alerts.sound.url");
        var ioService = Components.classes["@mozilla.org/network/io-service;1"]
                                  .getService(Components.interfaces.nsIIOService);
        soundAlertURI = ioService.newURI(url, null, null);
      } catch(ex) {
        soundAlertType == 0;
      }
    }

    try {
      var c = prefBranch.getBoolPref("alerts.sound.conversationsonly");
      soundAlertOnNewMessage = !c;
    } catch (ex) {}
  }

  try {
    var docked = prefBranch.getBoolPref("startdocked");
    if (docked)
      defaultWindowStyle = IM_WINDOW_DOCKED;
    else
      defaultWindowStyle = IM_WINDOW_DETACHED;
  } catch(ex) {}
}

function loadIMPanel() {
  // Create all chatwindows and collapse
  var imPanel = document.getElementById('applications-im-panel');

  while (imPanel.firstChild)
    imPanel.removeChild(imPanel.firstChild);

  for (var row = 0; row < IM_WINDOWS_ROWS_MAX; row++) {
    if (row != 0) {
      var splitter = document.createElement('splitter');
      splitter.setAttribute('collapsed', 'true');

      imPanel.appendChild(splitter);
    }

    var imBox = document.createElement('hbox');
    imBox.setAttribute('id', 'im-box-' + row);
    imBox.setAttribute('flex', '1');
    imBox.setAttribute('collapsed', 'true');
    imPanel.appendChild(imBox);

    for (var col = 0; col < IM_WINDOWS_COLS_MAX; col++) {
      if (col != 0) {
        var splitter = document.createElement('splitter');
        splitter.setAttribute('collapsed', 'true');

        imBox.appendChild(splitter);
      }

      var chatwindow = document.createElement('chatwindow');
      chatwindow.setAttribute("id", "cw_" + row + '_' + col);
      chatwindow.setAttribute("flex", "1");
      chatwindow.setAttribute('collapsed', 'true');
      // Hide Toolbar
      chatwindow.setAttribute('dockedwindow', 'true');

      imBox.appendChild(chatwindow);
    }
  }
}

function uninit(event) {
  finish();
}

function finish() {
  for (var key in conversationHash)
    if (conversationHash[key] != undefined)
      conversationHash[key].close();
}

function getKey(account, address) {
  return account + '_' + address;
}

function prevConversation() {
  var found = false;

  var conversation = conversationHash[currentConversationKey];
  if (!conversation.dockedWindow)
    return;

  // Id of the conversation window => cw_row_col
  var match = conversation.dockedWindow.id.match(/cw_([\d]*)_([\d]*)/);
  if (!match) {
    dump('ERROR: Id syntax incorrect\n');
    return;
  }

  var row = match[1];
  var col = match[2];

  var chatwindow;

  var startRow = row;
  var startCol = col;
  while (!found) {
    if (col > 0) {
      col--;
    } else if (row > 0) {
      col = currentColsPerRow - 1;
      row--;
    }
    else {
      col = currentColsPerRow - 1;
      row = currentRow;
    }

    // Avoid infinite loop
    if (row == startRow && col == startCol)
      break;

    var newId = 'cw_' + row + '_' + col;
    chatwindow = document.getElementById(newId);

    if (!chatwindow.collapsed)
      found = true;
  }

  // Cannot happen
  if (!chatwindow)
    return;

  var key = getKey(chatwindow.session.account, chatwindow.session.address);
  conversationHash[key].focus();
}

function nextConversation() {
  var found = false;

  var conversation = conversationHash[currentConversationKey];
  if (!conversation.dockedWindow)
    return;

  // Id of the conversation window => cw_row_col
  var match = conversation.dockedWindow.id.match(/cw_([\d]*)_([\d]*)/);
  if (!match) {
    dump('ERROR: Id syntax incorrect\n');
    return;
  }

  var row = match[1];
  var col = match[2];

  var chatwindow;

  var startRow = row;
  var startCol = col;
  while (!found) {
    if (col < currentColsPerRow - 1) {
      col++;
    } else if (row < currentRow) {
      col = 0;
      row++;
    }
    else {
      col = 0;
      row = 0;
    }

    // Avoid infinite loop
    if (row == startRow && col == startCol)
      break;

    var newId = 'cw_' + row + '_' + col;
    chatwindow = document.getElementById(newId);

    if (!chatwindow.collapsed)
      found = true;
  }

  // Cannot happen
  if (!chatwindow)
    return;

  var key = getKey(chatwindow.session.account, chatwindow.session.address);
  conversationHash[key].focus();
}

function nextUnreadConversation() {
  var found = false;

  for (key in conversationHash) {
    if (conversationHash[key] == undefined)
      continue;

    if (conversationHash[key].unread) {
      conversationHash[key].focus();
      return;
    }
  }

  dump('INFO: NO unread conversations to focus.\n');
}

function setContactUnreadStatus(account, address, state) {
  var data = account + '|' + address + '|' + state;
  imObserverService.notifyObservers(null, "csIMContactUnread", data);
}

// Called by child window when focused
function focusedConversation(account, address) {
  currentConversationKey = getKey(account,address);
  setContactUnreadStatus(account, address, "false");

  conversationHash[currentConversationKey].unread = false;
}

// Called by child window when closed by user
function closeConversation(account, address) {
  var key = getKey(account, address);

  conversationHash[key].close(true /*shouldCloseChannel*/);
}

function dockWindow(account, address) {
  var key = getKey(account, address);
  conversationHash[key].dock();
}

function detachWindow(account, address) {
  var key = getKey(account, address);
  conversationHash[key].detach();
}

function closeDockedConversation(account, address) {
  var key = getKey(account, address);

  var chatwindow = conversationHash[key].dockedWindow;
  chatwindow.closeSession();

  dockedConversationsCount--;
  checkIMTab();
  removeConversationFromTab(account, address);

  // Remove the key from the lastUsedKey list.
  lastUsedKey.splice( lastUsedKey.indexOf( key ), 1 );
}

// Returns a clone of the input object
function clone(src) {
  if (!src || typeof(src) != 'object')
    return src;

  // Special handling for date.
  // Unless the date object is passed to constructor, 
  //  new time is assigned to dest.
  if (src.constructor.name == 'Date')
    var dest = new src.constructor(src);
  else
    var dest = new src.constructor();

  for (var key in src)
    dest[key] = clone(src[key]);

  return dest;
}

function getSessionsList() {

  var sessionsList = [];

  for (var row = 0; row < IM_WINDOWS_ROWS_MAX; row++) {
    var imBox = document.getElementById('im-box-' + row);
    if (imBox.collapsed)
      continue;
    
    for (var col = 0; col < IM_WINDOWS_COLS_MAX; col++) {
      // Id of the conversation window => cw_row_col
      var chatwindow = document.getElementById('cw_' + row + '_' + col);

      if (!chatwindow.collapsed) {
        // Sanity check
        if (!chatwindow.session)
          dump('ERROR: Uncollapsed, but NO Session for ' + chatwindow.id + '\n');

        sessionsList.push(chatwindow.session);
      }
    }
  }

  // Send the clone of the existing sessions. References cause problems.
  return sessionsList.map(clone);
}

function setRowsAndCols(action) {
  var row;

  if (dockedConversationsCount == 0) {
    currentRow = 0;
    currentColsPerRow = 0;
    return;
  }

  if (action == 'add') {
    // row starts from 0, not 1
    row = Math.ceil(dockedConversationsCount/currentColsPerRow) - 1;

    // Check if next conversation should be placed in a new row
    if (row > currentRow) {

      // If all columns are not used, dont add new row
      if (currentColsPerRow < IM_WINDOWS_COLS_MAX) {
        currentColsPerRow++;
        row = Math.ceil(dockedConversationsCount/currentColsPerRow) - 1;
      }
    }
  } else if (action == 'remove') {
    if (currentColsPerRow < IM_WINDOWS_COLS_MAX) {
      // Check if we can increase currentColsPerRow
      row = Math.ceil( dockedConversationsCount / (currentColsPerRow + 1) ) - 1;
      if (row < currentRow)
        currentColsPerRow++;
    }
    else
      row = Math.ceil( dockedConversationsCount / currentColsPerRow ) - 1;
  }
  else {
    dump('ERROR: "action" argument required. \n');
    return;
  }

  currentRow = row;

  // currentRow=0 => Row 1
  var new_cols_per_row = Math.ceil(dockedConversationsCount/(currentRow + 1));
  // Sanity check
  if (new_cols_per_row == 0) {
    dump('ERROR: new_cols_per_row cannot be zero\n');
    return;
  }

  currentColsPerRow = new_cols_per_row;
}

/* 
 * Adjusts the existings conversations
 * (un)collapses im-box-'currentRow' as required
 * Adds splitter if required 
 */
function addConversationToTab(account, address) {
  setRowsAndCols('add');

  var key = getKey(account, address);

  var sessionsList = getSessionsList();
  sessionsList.push(conversationHash[key].session);

  refreshConversationTab(sessionsList);
}

function removeConversationFromTab(account, address) {
  setRowsAndCols('remove');

  var key = getKey(account, address);
  var conversation = conversationHash[key].dockedWindow;

  // No splitter for the first chat window in a row
  if (conversation.previousSibling)
    conversation.previousSibling.collapsed = true;

  conversation.collapsed = true;

  var sessionsList = getSessionsList();
  refreshConversationTab(sessionsList);
}

function refreshConversationTab(sessionsList) {

  // Browse through all chatwindows
  for (var row = 0; row < IM_WINDOWS_ROWS_MAX; row++) {
    var imBox = document.getElementById('im-box-' + row);

    // Chatwindows upto 'currentRow' need to be open. 
    if (row <= currentRow) {
      imBox.collapsed = false;

      if (row != 0)
        imBox.previousSibling.collapsed = false;

      for (var col = 0; col < IM_WINDOWS_COLS_MAX; col++) {
        var chatwindow = document.getElementById('cw_' + row + '_' + col);

        if ( col < currentColsPerRow && 
             col + currentColsPerRow * row < dockedConversationsCount ) {

          var sessionIndex = row * currentColsPerRow + col;
          
          var session = sessionsList[sessionIndex];
          chatwindow.session = session;

          var key = getKey(session.account, session.address);

          if (chatwindow.previousSibling)
            chatwindow.previousSibling.collapsed = false;

          chatwindow.collapsed = false;

          // Update hash
          conversationHash[key].dockedWindow = chatwindow;

        } else {
          chatwindow.collapsed = true;

          // Cleanup existing session, if any
          chatwindow.closeSession();

          // Close the splitter
          if (chatwindow.previousSibling)
            chatwindow.previousSibling.collapsed = true;
        }
      }
    }
    else {
      imBox.collapsed = true;
      if (row != 0)
        imBox.previousSibling.collapsed = false;
    }
  }
}

/*
 * Alert using sound
 * Called from inside the chat windows
 */
function soundAlert(aNewConversation)
{
  // Are the sound alerts are enabled?
  if (!soundAlertEnabled)
    return;

  // We play sounds either for a new conversation or
  // when the sounds are enabled for new messages too.
  if (!(soundAlertOnNewMessage || aNewConversation))
    return;

  var sound = Components.classes["@mozilla.org/sound;1"]
                        .createInstance(Components.interfaces.nsISound);
  
  if (soundAlertType == 0)
    sound.playSystemSound(soundAlertSystemType);
  else
    sound.play(soundAlertURI);
}

/*
 * Start conversation with account, address
 *  setFocus => true, if user initiated chat
 *           => false, if user received message
 */
function startConversation(account, address, channel, setFocus) {
  if (!account || !address) {
    dump('ERROR: Cannot start conversation without ' +
         (account? 'address' : 'account') + ' information.');
    return;
  }

  var key = getKey(account, address);

  if ( conversationHash[key] == undefined )
    conversationHash[key] = new ConversationWrapper(account, address);

  var conversation = conversationHash[key];
  // Set channel object
  conversation.channel = channel;
  conversation.open(setFocus);

  var data = account + '|' + address;
  imObserverService.notifyObservers(null, "csIMStartSession", data);
}

function channelClosed(account, address) {
  var key = getKey(account, address);

  // Ignore if no conversation exists
  if ( conversationHash[key] == undefined )
    return;

  conversationHash[key].channelClosed();
}

/* 
 * Open Docked Window conversation
 */
function openDockedConversation(account, address, setFocus) {
  if (dockedConversationsCount < IM_WINDOWS_MAX) {
    // Open conversation if there is space in IM tab
    var key = getKey(account, address);

    dockedConversationsCount++;
    checkIMTab(true);
    addConversationToTab(account, address);

    // Add the key to the lastUsedKey list.
    updateUsedKeyList(key);
  }
  else if (setFocus)
    // If initiated by user, replace last used conversation with new one, 
    replaceDockedConversation(account, address);
  else
    // Set unread if conversation cannot be opened
    setUnread(account, address);
}

function replaceDockedConversation(account, address) {
  var oldKey = lastUsedKey[0];
  var newKey = getKey( account, address );

  // Update conversationHash
  if ( conversationHash[newKey] == undefined )
    dump('ERROR: cannot replace a conversation without its object\n');

  conversationHash[newKey].dockedWindow = conversationHash[oldKey].dockedWindow;
  conversationHash[oldKey].dockedWindow = null;

  // load new session
  conversationHash[newKey].dockedWindow.session = conversationHash[newKey].session;

  // update lastUsedKey
  lastUsedKey.splice( lastUsedKey.indexOf( oldKey ), 1 );
  updateUsedKeyList( newKey );
}

function isConversationOpen(account, address) {
  var conversation = getConversation(account, address);
  if (conversation
      && (conversation.dockedWindow || conversation.detachedWindow))
    return true;
  else
    return false;
}

function getCurrentConversation() {
  return conversationHash[currentConversationKey];
}

function getConversation(account, address) {
  var key = getKey(account,address);
  return conversationHash[key];
}

function focusCurrentConversation() {
  getCurrentConversation().focus();
}

function toggleShowTimestamp() {
  // Get focused chat window

  var focused = document.commandDispatcher.focusedElement;
  while(focused) {
    if (focused.tagName == 'chatwindow')
      break;

    focused = focused.parentNode;
  }

  if (focused && focused.session)
    focused.setTimestampState(!focused.session.showTimestamps);
}

function setUnread(account, address) {
  var key = getKey(account, address);
  var conversation = conversationHash[key];
  if (conversation == undefined)
    return;

  conversation.unread = true;

  setContactUnreadStatus(account, address, "true");
}

function updateUsedKeyList(key) {
  // Remove the existing key, if any
  var index = lastUsedKey.indexOf(key);
  if ( index != -1 )
    lastUsedKey.splice(index, 1);

  // Add the key to the end
  lastUsedKey.push(key);
}

/* 
 * ConversationWrapper class
 */
function ConversationWrapper(account, address) {
  this.account = account;
  this.address = address;
  this.showTimestamps = false;

  this._channel = null;
  this.messages = [];

  this._dockedWindow = null;
  this._detachedWindow = null;
  this._unread = false;

  this.priority = 0;

  // Default
  this.windowType = defaultWindowStyle;
  this.mPendingMessages = new Array();
  
  var self = this;
  prefBranch.addObserver("showtimestamps", {
                           observe: function() {
                             self.updateShowTimestamps();
                           }
                         }, false);

  this.updateShowTimestamps();
}

ConversationWrapper.prototype = {

  updateShowTimestamps: function() {
    try {
      var timestamps = prefBranch.getBoolPref("showtimestamps");
    } catch (ex) {
      timestamps = false;
    }

    this.showTimestamps = timestamps;

    if (this.dockedWindow)
      this.dockedWindow.setTimestampState(timestamps);
    else if (this.detachedWindow)
      this.detachedWindow.chatwindow.setTimestampState(timestamps);
  },

  /*********** Start channel observer members ***********/
  onError: function(aErrorCode) {
    dump("ERROR: conversation manager channel observer - " + aErrorCode);
    gIMPromptService.alert(null, getLocaleString([ ['ChannelErrorTitle'] ]),
                           getLocaleString([ ['telepathy.error.' + aErrorCode] ]));
  },

  onAddItem: function(aItem) {
    var message = aItem.QueryInterface(Components.interfaces.csITPTextChannelPendingMessage);
    this.mPendingMessages.push(message);
  },

  onItemsComplete: function() {
    for each (var pendingMessage in this.mPendingMessages) {
      var message = { body      : pendingMessage.text, 
                      time      : pendingMessage.timestamp,
                      direction : 'incoming' };

      this.addMessage(message);
    }
    this.mPendingMessages = new Array();
  },

  // Channel text received observer 
  onTextReceived: function(aId, aTimeStamp, aSender, aType, aFlags, aTextMessage) {
    //TODO: check for type & flags
    var message = { body      : aTextMessage, 
                    time      : aTimeStamp,
                    direction : 'incoming' };

    this.addMessage(message);

    setUnread(this.account, this.address);
  },

  // Channel text send observer 
  onTextSent: function(aTimeStamp, aType, aTextMessage) {
    //TODO: check for type
    var message = { body      : aTextMessage, 
                    time      : aTimeStamp,
                    direction : 'outgoing' };

    this.addMessage(message);
  },

  // Channel send error observer
  onTextSendError: function(aErrorCode, aTimeStamp, aType, aTextMessage) {
    var text = getLocaleString([['telepathy.text.senderror.' + aErrorCode, aTextMessage]]);
    var message = { body     : text,
                    time     : aTimeStamp,
                    direction: 'error' };
    this.addMessage(message);
  },

  /*********** End channel observer members ***********/

  addMessage: function(message) {
    this.messages.push(message);

    var data = this.account + '|' + this.address + '|' + message.time + '|' + 
               message.direction + '|' + message.body;
    imObserverService.notifyObservers(null, "csIMNewMessage", data);
  },

  get channel() {
    return this._channel;
  },

  set channel(val) {
    if (this.channel) {
      // Remove channel observers for existing channel.
      this.channel.removeReceivedObserver(this);
      this.channel.removeSentObserver(this);
      this.channel.removeSendErrorObserver(this);
    }

    // Set the channel value
    this._channel = val;

    if (val == null)
      return;

    // Register for received/sent messages
    this.channel.addReceivedObserver(this);
    this.channel.addSentObserver(this);
    this.channel.addSendErrorObserver(this);
  },

  channelClosed: function() {
    this.channel = null;

    if (this.windowType == IM_WINDOW_DETACHED)
      var conversationWindow = this.detachedWindow;
    else
      var conversationWindow = this.dockedWindow;

    if (conversationWindow) {
      dump('WARNING: A chat window is open, but channel is closed. Deactivating the chat session\n');
      conversationWindow.updateChannel(null);
    }
  },

  get session() {
    return {
      account: this.account,
      address: this.address,
      channel: this.channel,
      messages: this.messages.slice(0),
      showTimestamps: this.showTimestamps
    };
  },

  set session(val) {
    if (!val) {
      dump('ERROR: Null val in set session\n');
    }

    this.account = val.account;
    this.address = val.address;
    this.channel = val.channel;
    this.messages = val.messages;
    this.showTimestamps = val.showTimestamps;
  },

  get dockedWindow() {
    return this._dockedWindow;
  },

  set dockedWindow(val) {
    this._dockedWindow = val;
  },

  get detachedWindow() {
    return this._detachedWindow;
  },

  set detachedWindow(val) {
    this._detachedWindow = val;
  },

  get unread() {
    return this._unread;
  },

  set unread(val) {
    this._unread = val;

    if (!getAttentionOnUnread)
      return;

    if (val) {
      if (this.windowType == IM_WINDOW_DETACHED)
        this.detachedWindow.getAttention();
      else {
        window.getAttention();
        if (gCurrentApplication != gIMAppName) 
         flashIMTab();
      }
    }
  },

  focus: function() {
    if (this.windowType == IM_WINDOW_DETACHED) {
      this.detachedWindow.focus();
    }
    else {
      if (!this.dockedWindow)
        openDockedConversation(this.account, this.address, true);
      else
        this.dockedWindow.focus();
    }
  },

  open: function(setFocus) {
    var existingWindow = null;

    if (this.windowType == IM_WINDOW_DETACHED) {
      if (this.detachedWindow) {
        if (setFocus)
          this.detachedWindow.focus();
        else
          setUnread(this.account, this.address);

        existingWindow = this.detachedWindow;
      } else {
        this.detachedWindow = 
              window.openDialog("chrome://im/content/chatWindow.xul", 
                                "", "dialog=no", this.session, setFocus);
      }
    }
    else {
      if (this.dockedWindow) {
        if (setFocus) {
          if (gCurrentApplication != gIMAppName)
            setCurrentApp(gIMAppName);
          this.dockedWindow.focus();
        }
        else
          setUnread(this.account, this.address);

        existingWindow = this.dockedWindow;
      } else {
        openDockedConversation(this.account, this.address, setFocus);
      }
    }

    if (existingWindow) 
      existingWindow.updateChannel(this.channel);

    // Request pending messages after opening chat window
    // We need to have a copy of those messages also.
    //  acknowledge will be done by chat window
    if (this.channel)
      this.channel.listPendingMessages(false, this);
  },

  // shouldCloseChannel - true, if close requested by user
  //  ensures channel is not closed when docking/detaching chat window
  close: function(shouldCloseChannel) {
    if (this.windowType == IM_WINDOW_DETACHED && this.detachedWindow) {
      this.detachedWindow.closeConversation();
      this.detachedWindow = null;
    }
    else if (this.dockedWindow) {
      closeDockedConversation(this.account, this.address);
      this.dockedWindow = null;
    }

    if (shouldCloseChannel && this.channel) {
      // TODO: Close telepathy channel
      var emptyCB = {
        doAction: function() {
        },
        onError: function(aErrorCode) {
          dump('WARNING: Ignoring error while closing channel. ' + aErrorCode + '\n');
        }
      };
      this.channel.close(emptyCB);
    }

    var data = this.account + '|' + this.address;
    imObserverService.notifyObservers(null, "csIMEndSession", data);
  },

  setChatState: function(chatstate) {
    if (this.windowType == IM_WINDOW_DETACHED)
      var conversationWindow = this.detachedWindow;
    else
      var conversationWindow = this.dockedWindow;

    if (conversationWindow)
      conversationWindow.setChatState(chatstate);
  },

  dock: function() {
    this.close();
    this.windowType = IM_WINDOW_DOCKED;
    // Focus new window
    this.open(true);
  },

  detach: function() {
    this.close();
    this.windowType = IM_WINDOW_DETACHED;
    // Focus new window
    this.open(true);
  }
};

