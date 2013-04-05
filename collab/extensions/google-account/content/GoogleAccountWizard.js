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
#   Ashok Gudibandla <ashok@synovel.com>
# Portions created by the Initial Developer are Copyright (C) 2007-2008
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
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

window.addEventListener("load", GoogleWizardInit, false);

function GoogleWizardCollapseNode(aID) {
   var node = document.getElementById(aID);
   if (node)
     node.setAttribute("collapsed", true);
}

function GoogleWizardInit() {
   GoogleWizardCollapseNode("domain:gmail.com?type=pop3");
   GoogleWizardCollapseNode("domain:gmail.com?type=imap");
   GoogleWizardCollapseNode("domain:gmail.com");
   GoogleWizardCollapseNode("domain:googlemail.com");

   var accountPage = document.getElementById("accounttype");
   // Order matters here. GoogleAccountSelection() over rides the page order
   // set by acctTypePageUnload()
   accountPage.addEventListener ("pageadvanced", acctTypePageUnload, false);
   accountPage.addEventListener("pageadvanced", GoogleAccountSetPages, false );

   var identityPage = document.getElementById("identitypage");

   var wizard = document.getElementById("AccountWizard");
   wizard.addEventListener("wizardfinish", GoogleWizardFinish, false );
}

function GoogleWizardFinish() {
   var type = document.getElementById("acctyperadio").selectedItem.value;
   if (type != "google-account")
      return;
   var setupCalendar = document.getElementById("google-calendar").checked;
   var setupTalk = document.getElementById("google-im").checked;
   var email = document.getElementById("identity.email.text").value;
   if (setupCalendar)
      createGoogleCalendar(email)
   if (setupTalk)
      createGoogleIM(email);
}

var gIMPendingList;
var gIMAccount;
var gJabberProtocol = 'jabber';
var gJabberProtocolManagers;

function GetProtocolListCB(aThisObject, aManager) {
  this._self = aThisObject;
  this.manager = aManager;
}

GetProtocolListCB.prototype = {
  onAddItem: function(aStringItem) {
    if (aStringItem == gJabberProtocol) {
      dump('## Jabber provided by: ' + this.manager + '\n');
      this._self.gJabberProtocolManagers.push(this.manager);
    }
  },
  
  onError: function(aErrorStr) {
    dump("ERROR: protocol list CB - " + aErrorStr);
  },
  
  onItemsComplete: function() {
    this._self.GotProtocolList(this.manager);
  }
};

function GotProtocolList(aManager) {
  var index = gIMPendingList.indexOf(aManager);
  if (index == -1)
    return;

  gIMPendingList.splice(index, 1);

  // Check if protocol list is got from all managers
  if (gIMPendingList.length == 0)
    createIMAccount();
}

function createGoogleIM(email) {
  var gTelepathy = window.opener.gTelepathy;

  // Check if account already exists
  if (gTelepathy.getAccount(email))
    return;

  var connectionManagers = gTelepathy.gTPManagers;

  gIMAccount = email;
  gIMPendingList = [];
  gJabberProtocolManagers = [];

  for each (var connectionManager in connectionManagers) {
    try {
      connectionManager = connectionManager.QueryInterface(Components.interfaces.csITPConnectionManager);
      var protocolListCB = new GetProtocolListCB(this, connectionManager.name);

      gIMPendingList.push(connectionManager.name);
      connectionManager.getProtocolList(protocolListCB);

    } catch(ex) {
      dump('ERROR: Got a non-connection-manager object\n');
    }
  }
}

var gIMAccountParams = {
  'haze': [ { param: 'auth-plain-in-clear', type: 'bool',   value: false },
            { param: 'old-ssl',             type: 'bool',   value: false },
            { param: 'port',                type: 'int',    value: 5222 },
            { param: 'protocol',            type: 'char',   value: "google-talk" },
            { param: 'require-encryption',  type: 'bool',   value: false },
            { param: 'server',              type: 'char',   value: "talk.google.com" } ],

  'gabble': [ { param: 'old-ssl',             type: 'bool',   value: false },
              { param: 'port',                type: 'int',    value: 5222 },
              { param: 'protocol',            type: 'char',   value: "google-talk" },
              { param: 'require-encryption',  type: 'bool',   value: false },
              { param: 'server',              type: 'char',   value: "talk.google.com" },
              { param: 'ignore-ssl-errors',   type: 'bool',   value: true },
              { param: 'resource',            type: 'char',   value: 'Spicebird' } ]
};

function createIMAccount() {
  var prefService = Components.classes["@mozilla.org/preferences-service;1"]
                              .getService(Components.interfaces.nsIPrefService);
  var prefBranch = prefService.getBranch("collab.im.accounts.");
  
  // Get the next available key
  var prefKey;
  try {
    for (prefKey = 0; prefKey < 10000; prefKey++) {
      prefBranch.getCharPref(key.toString() + ".account");
    }
  } catch (ex) { };

  var defaultManager = gJabberProtocolManagers[0];

  prefBranch.setCharPref(prefKey + '.account', gIMAccount);
  prefBranch.setCharPref(prefKey + '.manager', defaultManager);
  prefBranch.setCharPref(prefKey + '.protocol', 'jabber');

  for (var i = 0; i < gIMAccountParams[defaultManager].length; i++) {
    switch (gIMAccountParams[defaultManager][i].type) {
      case 'char':
        prefBranch.setCharPref(prefKey + '.' + gIMAccountParams[defaultManager][i].param,
                               gIMAccountParams[defaultManager][i].value);
        break;
      case 'int':
        prefBranch.setIntPref(prefKey + '.' + gIMAccountParams[defaultManager][i].param,
                              gIMAccountParams[defaultManager][i].value);
        break;
      case 'bool':
        prefBranch.setBoolPref(prefKey + '.' + gIMAccountParams[defaultManager][i].param,
                               gIMAccountParams[defaultManager][i].value);
        break;
    }
  }

  prefService.savePrefFile(null);

  var observerService = Components.classes["@mozilla.org/observer-service;1"]
                                  .getService(Components.interfaces.nsIObserverService);
  observerService.notifyObservers(null, "csIMAccountCreated", prefKey);
}

function createGoogleCalendar(email) {
   var newCalendar;
   var calManager = window.opener.getCalendarManager();
   var gcalUri = "http://www.google.com/calendar/ical/" 
                  + email + "/public/basic.ics";
    var ioSvc = Components.classes["@mozilla.org/network/io-service;1"].
                getService(Components.interfaces.nsIIOService);
    var url =  ioSvc.newURI(gcalUri, null, null);

    var cals = calManager.getCalendars({});
    var already = cals.filter(function (c) { return c.uri.spec == gcalUri; })
    if (already.length) {
      alert("Already have calendar with URI " + gcalUri);
      return true;
    }

    try {
        newCalendar = calManager.createCalendar("gdata",url);
    } catch (ex) {
        dump(ex);
        return false;
    }

    calManager.registerCalendar(newCalendar);

    newCalendar.name = "Google Calendar";
    newCalendar.setProperty('color', '#115511');
}

function showHideProtocolBox(event) {
   var collapse = !event.target.checked;
   document.getElementById("protocol-box").setAttribute("hidden", collapse.toString());
}

function GoogleIdentityPageLoad() {
   var type = document.getElementById("acctyperadio").selectedItem.value;
   if (type != "google-account")
      return identityPageInit();

   if (gCurrentAccountData)
      gCurrentAccountData.domain = null;
   var ret = identityPageInit();

   var domainLable = document.getElementById("postEmailText");
   domainLable.setAttribute("collapsed", "true");

   var emailDesc  = document.getElementById("emailDescText");
   if (emailDesc.firstChild )
     emailDesc.removeChild(emailDesc.firstChild);

   var bundle = document.getElementById("googleAccount-bundle");
   var text = bundle.getString("emailDescText");
   emailDesc.appendChild( document.createTextNode(text));

   return ret;
}

function GoogleIdentityPageAdvance() {
  var isOk = identityPageUnload();
  if (!isOk)
      return false;

  var pageData = GetPageData();
  var email = document.getElementById("email").value;
  setPageData(pageData, "identity", "email", email);
  setPageData(pageData, "login", "username", email);
  setPageData(pageData, "login", "smtpusername", email);

  return true;
}

function GoogleAccountSetPages() {
   var type = document.getElementById("acctyperadio").selectedItem.value;
   if (type != "google-account")
      return;
   setNextPage("accounttype", "ispPage7");
   setNextPage("ispPage7", "identitypage");
   setNextPage("identitypage", "done");
}

function GoogleServerPageAdvance() {
   var type = document.getElementById("acctyperadio").selectedItem.value;
   if (type != "google-account")
      return;
   var type = document.getElementById("google-servertype").value;
   var ispName = "domain:gmail.com?type=" + type;
   var emailEnabled = document.getElementById("google-email").checked;
   if (emailEnabled)
      parent.PrefillAccountForIsp(ispName);
}

