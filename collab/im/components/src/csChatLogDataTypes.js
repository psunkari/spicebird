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

Components.utils.import("resource://gre/modules/XPCOMUtils.jsm");

/***********************************************************
* class implementing csIChatMessage
***********************************************************/

// class constructor 
function csChatMessage() {
};

// class definition
csChatMessage.prototype = {

  classDescription: "Component that contains a chat message",
  classID: Components.ID("{c5ce889f-275d-477c-bac1-f49368db084e}"),
  contractID: "@synovel.com/collab/im/chatmessage;1",
  QueryInterface: XPCOMUtils.generateQI([Ci.csIChatMessage]),

  mTimestamp: 0,
  mDirection: 0,
  mText: "",

  get timestamp() { return this.mTimestamp; },
  set timestamp(aValue) { this.mTimestamp = aValue; },

  get direction() { return this.mDirection; },
  set direction(aValue) { this.mDirection = aValue; },

  get text() { return this.mText; },
  set text(aValue) { this.mText = aValue; }
};



/***********************************************************
* class implementing csIChatLog
***********************************************************/

// class constructor 
function csChatLog() {
};

// class definition
csChatLog.prototype = {
  classDescription: "Component that contains an entire chat log",
  classID: Components.ID("{f4bd7ab2-98ed-4244-83d8-03149ae78f7b}"),
  contractID: "@synovel.com/collab/im/chatlog;1",
  QueryInterface: XPCOMUtils.generateQI([Ci.csIChatLog]),

  mId: null,
  mAccount: "",
  mAddress: "",
  mAddress: "",
  mStartTime: 0,
  mEndTime: 0,
  mText: "",

  get id() { return this.mId; },
  set id(aValue) { this.mId = aValue; },

  get account() { return this.mAccount; },
  set account(aValue) { this.mAccount = aValue; },

  get address() { return this.mAddress; },
  set address(aValue) { this.mAddress = aValue; },

  get startTime() { return this.mStartTime; },
  set startTime(aValue) { this.mStartTime = aValue; },

  get endTime() { return this.mEndTime; },
  set endTime(aValue) { this.mEndTime = aValue; },

  get text() { return this.mText; },
  set text(aValue) { this.mText = aValue; }
};


/***********************************************************
* class implementing csIChatLogSearchParams
***********************************************************/

// class constructor 
function csChatLogSearchParams() {
};

// class definition
csChatLogSearchParams.prototype = {

  classDescription: "Component that contains search parameters to search a chat log",
  classID: Components.ID("{bb0f7612-6d6b-4722-8436-dd5fe3fb9fdc}"),
  contractID: "@synovel.com/collab/im/chatlogsearchparams;1",
  QueryInterface: XPCOMUtils.generateQI([Ci.csIChatLogSearchParams]),

  mUser: "",
  mText: "",
  mOper: "AND", // default

  get user() { return this.mUser; },
  set user(aValue) { this.mUser = aValue; },

  get text() { return this.mText; },
  set text(aValue) { this.mText = aValue; },

  get oper() { return this.mOper; },
  set oper(aValue) { this.mOper = aValue; }
};

var components = [csChatMessage, csChatLog, csChatLogSearchParams];

function NSGetModule(aCompMgr, aFileSpec) {
  return XPCOMUtils.generateModule(components);
}

