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
const CONTRACT_ID_CHATLOG = "@synovel.com/collab/im/chatlog;1";

const DEBUG_CHATLOG_STORAGE_PROVIDER = false;

Components.utils.import("resource://gre/modules/XPCOMUtils.jsm");

/***********************************************************
* class definition
***********************************************************/

// Class constructor
function csChatLogSQLiteStorageProvider() {
  if (!this.mInitialized)
    this.initialize();
};

// class definition
csChatLogSQLiteStorageProvider.prototype = {

  classDescription: "Component that implements chatlog storage using SQLite db.",
  classID: Components.ID("{a5f52266-43c3-4045-b508-7863034ace19}"),
  contractID: "@synovel.com/collab/im/chatlogstorage;1?type=sqlite",
  QueryInterface: XPCOMUtils.generateQI([Ci.csIChatLogStorageProvider]),
  _xpcom_categories: [{category: "chatlog-storage-provider"}],

  mChatStorageFile: "chatlog.sqlite",
  mChatStorageVersion: 0.1,
  mChatStorageConn: null,

  mName: "sqlite",
  mProtocols: "ALL",
  mIsSearchable: true,
  mIsReadOnly: false,
  mUpdateOnChatMessage: true,

  mInitialized: false,

  debug: function(msg) {
    if (DEBUG_CHATLOG_STORAGE_PROVIDER)
      dump(msg + '\n');
  },

  get name() { return this.mName; },

  get protocols() { return this.mProtocols; },

  get isSearchable() { return this.mIsSearchable; },

  get isReadOnly() { return this.mIsReadOnly; },

  get updateOnChatMessage() { return this.mUpdateOnChatMessage; },

  startSession: function(aId, aAccount, aAddress) {
    this.debug("Adding session into db. id: " + aId);
    var stmtWrapper = this.createStatementWrapper("INSERT INTO session " +
                        "(session_id, account, address, start_time) values " +
                        "(:session_id, :account, :address, strftime('%s','now'))");
    stmtWrapper.params.session_id = aId;
    stmtWrapper.params.account = aAccount;
    stmtWrapper.params.address = aAddress;
    stmtWrapper.execute();
  },

  endSession: function(aId) {
    this.debug('marking session close. id: ' + aId);
    var  stmtWrapper = this.createStatementWrapper("UPDATE session " +
                         "SET end_time = strftime('%s','now') " +
                         "WHERE session_id = :session_id");

    stmtWrapper.params.session_id = aId;
    stmtWrapper.execute();
  },

  deleteChatLog: function(aId) {
    this.debug('delete session aId: ' + aId);
    var stmtWrapper = this.createStatementWrapper("DELETE FROM session " +
                        "WHERE session_id = :session_id");
    stmtWrapper.params.session_id = aId;
    stmtWrapper.execute();
  },

  newChatMessage: function(aId, aChatMessage) {
    this.debug("Update session in db: " + aId);
    var stmtWrapper = this.createStatementWrapper("SELECT chat_text " +
                        "FROM session WHERE session_id = :session_id");
    stmtWrapper.params.session_id = aId;

    var chat_text = "";

    // Get existing chat_text in db, if any
    try {
      if (stmtWrapper.step() && stmtWrapper.row.chat_text)
        chat_text = stmtWrapper.row.chat_text +
                    String.fromCharCode(Ci.csIChatLog.CHATLOG_MESSAGE_DELIMITER_CODE);
    } finally {
      stmtWrapper.reset();
    }

    chat_text += aChatMessage.timestamp +
                 String.fromCharCode(Ci.csIChatLog.CHATLOG_MESSAGE_FIELD_DELIMITER_CODE) +
                 aChatMessage.direction +
                 String.fromCharCode(Ci.csIChatLog.CHATLOG_MESSAGE_FIELD_DELIMITER_CODE) +
                 aChatMessage.text;

    try {
      this.debug('session_id: ' + aId + ', chat_text : ' + chat_text);
      stmtWrapper = this.createStatementWrapper("UPDATE session " +
                          "SET chat_text = :chat_text " +
                          "WHERE session_id = :session_id");

      stmtWrapper.params.session_id = aId;
      stmtWrapper.params.chat_text = chat_text;
      stmtWrapper.execute();
    } catch(ex) {
      this.debug('ex: ' + ex + '. lastError: ' + this.mChatStorageConn.lastError);
    }
  },

  searchChatLogs: function(aSearchParamsCount, aSearchParamsList, aCount) {
    var chatLogs = [];
    var sql = "SELECT * FROM session WHERE chat_text IS NOT NULL";

    bindParamsCount = 0;
    bindParams = [];
    // Generate bind parameter to be used in constructing search sql
    // Stores parameter value in 'bindParams', to be bound after creating statement
    function getBindParam(aValue) {
      var key = "param" + bindParamsCount;
      bindParams[key] = aValue;
      bindParamsCount++;
      return key;
    }

    // conditional clause for all params in aSearchParamsList,
    // separated by ' OR '
    var searchSql = "";

    for each (var searchParams in aSearchParamsList) {
      this.debug("search in db: " + searchParams.user + ", " + searchParams.text);

      var partSql = ""; // conditional clause for 'searchParams'

      if (searchParams.user) {
        partSql += "(account LIKE :" + getBindParam(searchParams.user) +  " ESCAPE '/'" +
                   " OR address LIKE :" + getBindParam(searchParams.user) + " ESCAPE '/')";
        /*
        partSql += "(account LIKE '%" + searchParams.user + "%'" +
                   " OR address LIKE '%" + searchParams.user + "%')";
                   */
      }

      if (searchParams.text) {
        if (partSql)
          partSql += " " + searchParams.oper + " ";

        partSql += "chat_text LIKE :" + getBindParam(searchParams.text) + " ESCAPE '/'";
      }

      if (partSql) {
        if (searchSql)
          searchSql += " AND "; // Default is to look for logs with all the keywords

        searchSql += " ( " + partSql + " ) ";
      }
    }

    if (searchSql)
      sql += " AND (" + searchSql + ")";

    this.debug('final sql: ' + sql);
    try {
      var stmtWrapper = this.createStatementWrapper(sql);
    } catch(ex) {
      this.debug('ex: ' + ex + '. lastError: ' + this.mChatStorageConn.lastError);
    }

    // bind search parameter values
    for (var param in bindParams) {
      this.debug('binding ' + param + ' to ' + bindParams[param]);
      stmtWrapper.params[param] = '%' + stmtWrapper.statement.escapeStringForLIKE(bindParams[param], '/') + '%';
    }

    try {
      while (stmtWrapper.step()) {
        var chatLog = Cc[CONTRACT_ID_CHATLOG].createInstance(Ci.csIChatLog);
        chatLog.id = stmtWrapper.row.session_id;
        chatLog.account = stmtWrapper.row.account;
        chatLog.address = stmtWrapper.row.address;
        chatLog.startTime = stmtWrapper.row.start_time;
        chatLog.endTime = stmtWrapper.row.end_time;
        chatLog.text = stmtWrapper.row.chat_text;
        this.debug('added text : ' + chatLog.text);

        chatLogs.push(chatLog);
      }
    } finally {
      stmtWrapper.reset();
    }

    this.debug('result logs count: ' + chatLogs.length);

    aCount.value = chatLogs.length;
    return chatLogs;
  },

  initialize: function() {
    this.debug('initialize csChatLogSQLiteStorageProvider');

    try {
      var file = Cc["@mozilla.org/file/directory_service;1"]
                 .getService(Ci.nsIProperties).get("ProfD", Ci.nsIFile);
      file.append(this.mChatStorageFile);

      var storageService = Cc["@mozilla.org/storage/service;1"]
                           .getService(Ci.mozIStorageService);
      this.mChatStorageConn = storageService.openUnsharedDatabase(file);
    } catch(ex) {
      switch(ex.result) {
        case Components.results.NS_ERROR_OUT_OF_MEMORY:
        case Components.results.NS_ERROR_FILE_CORRUPTED:
        case Components.results.NS_ERROR_FAILURE:
          break;
      }
      this.debug('Ex: ' + ex);
    }

    this.checkChatStorage();

    this.mInitialized = true;
  },

  createStatementWrapper: function(sql) {
    try {
      var statement = this.mChatStorageConn.createStatement(sql);
      var wrapper = Cc["@mozilla.org/storage/statement-wrapper;1"]
                    .createInstance(Ci.mozIStorageStatementWrapper);
      wrapper.initialize(statement);
      return wrapper;
    } catch (ex) {
      throw ex;
    }
  },

  checkChatStorage: function() {
    this.debug('checkChatStorage');
    var version;

    try {
      if (this.mChatStorageConn.tableExists('version')) {
        var stmtWrapper = this.createStatementWrapper("SELECT id FROM version LIMIT 1");
        if (stmtWrapper.step())
          version = stmtWrapper.row.id;
      }
    } finally {
      if (stmtWrapper)
        stmtWrapper.reset();
    }

    if (version == undefined) {
      this.createChatStorage();
    } else if (version != this.mChatStorageVersion) {
      this.upgradeChatStorage(version);
    }
  },

  upgradeChatStorage: function(version) {
    // Nothing to do yet
  },

  createChatStorage: function() {
    try {
      var stmtWrapper = this.createStatementWrapper("CREATE TABLE version (id)");
      stmtWrapper.execute();

      stmtWrapper = this.createStatementWrapper("INSERT INTO version VALUES (:id)");
      stmtWrapper.params.id = this.mChatStorageVersion;
      stmtWrapper.execute();

      stmtWrapper = this.createStatementWrapper("CREATE TABLE session " +
                           "(session_id, account, address, start_time, " +
                           "end_time, chat_text)");
      stmtWrapper.execute();

      stmtWrapper = this.createStatementWrapper("CREATE INDEX chat_text_index " +
                                                "ON session (chat_text)");
      stmtWrapper.execute();
    } catch(ex) {
      this.debug('ex: ' + ex + '. lastError: ' + this.mChatStorageConn.lastError);
    }
  }
};

var components = [csChatLogSQLiteStorageProvider];

function NSGetModule(aCompMgr, aFileSpec) {
  return XPCOMUtils.generateModule(components);
}
