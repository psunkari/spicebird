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

/***********************************************************
* constants
***********************************************************/

const Ci = Components.interfaces;
const Cc = Components.classes;

const CHATLOG_STORAGE_CATEGORY = "chatlog-storage-provider";
const CONTRACT_ID_CHATMESSAGE = "@synovel.com/collab/im/chatmessage;1";
const CONTRACT_ID_CHATLOGSEARCHPARAMS = "@synovel.com/collab/im/chatlogsearchparams;1";

Components.utils.import("resource://gre/modules/XPCOMUtils.jsm");

/***********************************************************
* class definition
***********************************************************/

// Class constructor
function csChatLogService() { 
  if (!this.mInitialized)
    this.initialize();
};

// class definition
csChatLogService.prototype = {
  classDescription: "Component that implements chatlog service.",
  classID: Components.ID("{c83bdb0b-8ce3-476c-90f8-6abaf0fae1c3}"),
  contractID: "@synovel.com/collab/im/chatlogservice;1",
  QueryInterface: XPCOMUtils.generateQI([Ci.csIChatLogService]),

  mInitialized: false,
  mStorageProviders: [],
  mUpdateStorageProviders: [],
  mSessions: [],
  mIsSearchTextSplit: true,
  mDebug: false,

  get isSearchTextSplit() { return this.mIsSearchTextSplit; },

  debug: function(msg) {
    if (this.mDebug) { dump(msg + '\n'); }
  },

  getUUID: function() {
    var uuidGen = Cc["@mozilla.org/uuid-generator;1"]
                  .getService(Ci.nsIUUIDGenerator);
    return uuidGen.generateUUID().toString().replace(/[{}]/g, '');
  },

  getKey: function(aAccount, aAddress) {
    return aAccount + '|' + aAddress;
  },

  observe: function(aSubject, aTopic, aData) {
    switch(aTopic) {
      case 'csIMStartSession':
        this.debug('csIMStartSession, data: ' + aData);
        // aData => account|address
        var data = aData.split('|');

        var session_id = this.getUUID();
        var key = this.getKey(data[0], data[1]);

        this.mSessions[key] = session_id;

        for each (var storageProvider in this.mUpdateStorageProviders)
          storageProvider.startSession(session_id, data[0], data[1]);

        break;

      case 'csIMEndSession':
        this.debug('csIMEndSession, data: ' + aData);
        // aData => account|address
        var data = aData.split('|');

        var key = this.getKey(data[0], data[1]);
        if (this.mSessions[key] == undefined) {
          this.debug('ERROR: end session key not found');
          this.mSessions[key] = this.getUUID();
        }

        var session_id = this.mSessions[key];
        var timestamp = (new Date()).getTime().toString();

        for each (var storageProvider in this.mUpdateStorageProviders)
          storageProvider.endSession(session_id, timestamp);

        break;

      case 'csIMNewMessage':
        this.debug('csIMNewMessage, data: ' + aData);
        // aData => account|address|time|direction|text
        var data = aData.split('|');
        this.debug('data[3]: ' + data[3] + ' data[2]: ' + data[2]);

        var chatMessage = Cc[CONTRACT_ID_CHATMESSAGE]
                          .createInstance(Ci.csIChatMessage);

        chatMessage.timestamp = data[2];
        if (data[3] == 'incoming') 
          chatMessage.direction = Ci.csIChatMessage.MESSAGE_INCOMING;
        else
          chatMessage.direction = Ci.csIChatMessage.MESSAGE_OUTGOING;
        chatMessage.text = data[4];

        var key = this.getKey(data[0], data[1]);
        if (this.mSessions[key] == undefined) {
          this.debug('ERROR: new message session key not found');

          for each (var storageProvider in this.mUpdateStorageProviders)
            storageProvider.startSession(session_id, data[0], data[1]);

          this.mSessions[key] = this.getUUID();
        }

        var session_id = this.mSessions[key];

        for each (var storageProvider in this.mUpdateStorageProviders)
          storageProvider.newChatMessage(session_id, chatMessage);

        break;
    }
  },

  initialize: function() {
    this.debug("Initializing chat log service");

    // Register to observer notifications
    var observerService = Cc["@mozilla.org/observer-service;1"]
                          .getService(Ci.nsIObserverService);
    observerService.addObserver(this, "csIMStartSession", false);
    observerService.addObserver(this, "csIMEndSession", false);
    observerService.addObserver(this, "csIMNewMessage", false);
    
    // Read category manager for CHATLOG_STORAGE_CATEGORY
    var categorymanager = Cc["@mozilla.org/categorymanager;1"]
                          .getService(Ci.nsICategoryManager);
    var enumerator = categorymanager.enumerateCategory(CHATLOG_STORAGE_CATEGORY);

    while (enumerator.hasMoreElements()) {
      var entry = enumerator.getNext()
                            .QueryInterface(Ci.nsISupportsCString);
      var contractId = categorymanager.getCategoryEntry(CHATLOG_STORAGE_CATEGORY, entry);
      this.debug("Adding to storage providers list, contractId: " + contractId);

      // Add all providers to list & initialize them
      try {
        var storageProvider = Cc[contractId]
                              .getService(Ci.csIChatLogStorageProvider);

        this.mStorageProviders.push(storageProvider);
        if (!storageProvider.isServerStorage) {
          this.mUpdateStorageProviders.push(storageProvider);
        }
      } catch(ex) {
        // Handle exceptions to ensure other providers are initialized 
        this.debug("Error in handling a storage provider entry. ex: " + ex + "\n");
      }
      
    }

    this.mInitialized = true;
  },

  deleteChatLog: function(aId) {
    for each (var storageProvider in this.mStorageProviders) {
      if (storageProvider.isReadOnly)
        continue;

      storageProvider.deleteChatLog(aId);
    }
  },

  getChatLogs: function(aSearchParams, aCount) {
    this.debug('aSearchParams, user:' + aSearchParams.user + ', text:' + 
               aSearchParams.text + ', oper:' + aSearchParams.oper);

    var searchParamsList = [];

    if (this.mIsSearchTextSplit) {
      this.debug('Splitting into keywords');
      keywords = aSearchParams.text.split(' ');
      for each (var keyword in keywords) {
        var searchParams = Cc[CONTRACT_ID_CHATLOGSEARCHPARAMS]
                           .createInstance(Ci.csIChatLogSearchParams);
        searchParams.user = aSearchParams.user;
        searchParams.oper = aSearchParams.oper;
        searchParams.text = keyword;
        searchParamsList.push(searchParams);

        this.debug('Searching for user: ' + searchParams.user + 
                   ', text: ' + searchParams.text + ', oper: ' + 
                   searchParams.oper + '\n');
      }
    } else {
      searchParamsList.push(aSearchParams);
    }

    var allChatLogs = [];
    var chatLogsMap = [];

    for each (var storageProvider in this.mStorageProviders) {
      if (!storageProvider.isSearchable)
        continue;

      try {
        var chatLogs = storageProvider.searchChatLogs(searchParamsList.length, 
                                                      searchParamsList, {});

        for each (var chatLog in chatLogs) {
          if (!chatLogsMap[chatLog.id]) {
            this.debug('adding new chat: ' + chatLog.id + ', txt: ' + chatLog.text);
            chatLogsMap[chatLog.id] = storageProvider;
            allChatLogs.push(chatLog);
          } else
            this.debug('ignoring existing chat: ' + chatLog.id + ', txt: ' + chatLog.text);
        }


      } catch(ex) {
        this.debug('Ex during search: ' + ex);
      }
    }

    this.debug('no of chats: ' + allChatLogs.length);
    aCount.value = allChatLogs.length;
    return allChatLogs;
  }
};

var components = [csChatLogService];

function NSGetModule(aCompMgr, aFileSpec) {
  return XPCOMUtils.generateModule(components);
}

