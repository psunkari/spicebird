/* -*- Mode: js2; tab-width: 4; indent-tabs-mode: nil; -*-
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
#   Sunil Mohan Adapa <sunil@synovel.com>, original author
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

const Cc = Components.classes;
const Ci = Components.interfaces;

function onClearSearch()
{
  csChatHistoryView.mChatLogSearchBox.value = "";
  csChatHistoryView.onSearch();
}

var csChatHistoryController = {

  supportsCommand: function(aCommand)
  {
    switch(aCommand)
    {
      case "cmd_delete":
      case "cmd_saveas":
        return true;
    }

    return false;
  },

  isCommandEnabled: function(aCommand)
  {
    switch(aCommand)
    {
      case "cmd_delete":
      case "cmd_saveas":
        return true;
    }

    return false;
  },

  doCommand: function(aCommand)
  {
    switch(aCommand)
    {
      case "cmd_delete":
        csChatHistoryView.onDelete();
        break;
      case "cmd_saveas":
        csChatHistoryView.onSaveAs();
        break;
    }
  },

  onEvent: function(aEvent)
  {
  }
};

var csChatHistoryView = {

  mDebugView: false,

  mChatLogService: null,
  mChatLogs: null,

  mChatLogListBox: null,
  mChatLogFrame: null,

  initialize: function()
  {
    // Service
    this.mChatLogService = Cc["@synovel.com/collab/im/chatlogservice;1"]
                             .getService(Ci.csIChatLogService);

    // UI Element cache
    this.mChatLogListBox = document.getElementById("chat-history-listbox");
    this.mChatLogSearchBox = document.getElementById("chat-history-searchbox");
    this.mChatLogFrame = document.getElementById("chat-history-frame");
    this.mChatLogFrame.readonly = true;

    // Behaviour addition
    var this_ = this;
    this.mChatLogListBox.addEventListener("select", function () {
                                            this_.onSelect();
                                          }, false);
    this.mChatLogSearchBox.addEventListener("command", function () {
                                              this_.onSearch();
                                            }, false);
    window.controllers.appendController(csChatHistoryController);

    // Initial filling of data
    this.onSearch();
  },

  // Listbox selection change
  onSelect: function()
  {
    if (this.mChatLogService.isSearchTextSplit)
      this.mChatLogFrame.keywords = this.mChatLogSearchBox.value.split(' ');
    else
      this.mChatLogFrame.keywords = [this.mChatLogSearchBox.value];

    this.mChatLogFrame.session = this.buildSession(this.mChatLogListBox.selectedItem.chatLog);
  },

  // Given a chat log item create a session object required by the chatWindow
  // binding
  buildSession: function(aLog)
  {
    var chatSession = {};
    chatSession.account = aLog.account;
    chatSession.address = aLog.address;
    chatSession.channel = null;

    chatSession.messages = [];

    var chatText = aLog.text;
    var chatMessages = chatText.split(String.fromCharCode(
                         Ci.csIChatLog.CHATLOG_MESSAGE_DELIMITER_CODE));

    var messageCount = 0;
    for each (var chatMessage in chatMessages)
    {
      messageCount++;
      var chatMessageFields = chatMessage.split(String.fromCharCode(
                                Ci.csIChatLog.CHATLOG_MESSAGE_FIELD_DELIMITER_CODE));

      if (chatMessageFields.length < 3)
      {
        this.debug('Ignoring corrupted message (' + messageCount +
                   ') in chat log: ' + aLog.id + '\n');
        continue;
      }

      var message = {};
      message.time = chatMessageFields[0];
      message.direction = (chatMessageFields[1] ==
        Ci.csIChatMessage.MESSAGE_INCOMING) ? 'incoming' : 'outgoing';
      message.body = chatMessageFields[2];

      chatSession.messages.push(message);
    }

    return chatSession;
  },

  onDelete: function()
  {
    // Do nothing if there is no selection
    if(!this.mChatLogListBox.selectedCount)
      return;

    this.mChatLogService.deleteChatLog(this.mChatLogListBox.selectedItem.chatLog.id);

    this.onSearch();
  },

  onSaveAs: function()
  {
    var chatWindow = document.getElementById("chat-history-frame");
    var serializer = new XMLSerializer();
    alert(serializer.serializeToString(chatWindow.mChatBrowser.contentDocument));
  },

  // Search box changed
  onSearch: function()
  {
    var searchParams = Cc["@synovel.com/collab/im/chatlogsearchparams;1"]
                         .createInstance(Ci.csIChatLogSearchParams);
    searchParams.text = this.mChatLogSearchBox.value;

    while(this.mChatLogListBox.getRowCount())
      this.mChatLogListBox.removeItemAt(0);

    this.mChatLogs = this.mChatLogService.getChatLogs(searchParams, {});
    for (var i = 0; i < this.mChatLogs.length; i++)
    {
      var time = new Date(parseInt(this.mChatLogs[i].startTime) * 1000)
                   .toLocaleString();

      var item = document.createElementNS
        ("http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul",
         "richlistitem");
      item.setAttribute ("class", "chat-history-listitem");

      this.mChatLogListBox.appendChild(item);
      item.chatLog = this.mChatLogs[i];
    }
  },

  // Debugging utility function
  debug: function(aMessage)
  {
    if (this.mDebugView)
      dump(aMessage);
  }
};

window.addEventListener("load", function () {
                          csChatHistoryView.initialize();
                        }, false);
