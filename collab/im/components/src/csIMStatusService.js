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

/***********************************************************
* constants
***********************************************************/

const nsISupports = Components.interfaces.nsISupports;
const nsIAbViewColumnHandler = Components.interfaces.nsIAbViewColumnHandler;

const csIIMStatusService = Components.interfaces.csIIMStatusService;
const csIIMContact = Components.interfaces.csIIMContact;
const csIIMStatusListener = Components.interfaces.csIIMStatusListener;

// UUID uniquely identifying our component
const CLASS_ID = Components.ID("{d88be1e1-7ebd-435c-a72a-b8a51d86f551}");

// description
const CLASS_NAME = "Component that detects calendar events in a given text";

// textual unique identifier
const CONTRACT_ID = "@synovel.com/collab/im/imstatusservice;1";

/***********************************************************
* class definition
***********************************************************/

// Class constructor
function csIMStatusService() {
};

// class definition
csIMStatusService.prototype = {

    mContactsCache: [],

    keyField: "PrimaryEmail",

    field: "IMStatus",

    mListeners: [],

    getCellText: function(id){
      return id;
    },

    getImageSrc: function(){
    },

    getCellProperties: function(){
    },

    searchContactsCache: function(contact) {
        for (var i=0; i<this.mContactsCache.length; i++) {
            // if contact.account is set to '--all--', return any entry with same account.
            if ((contact.account == "--all--" || contact.account == this.mContactsCache[i].account)
                && contact.id == this.mContactsCache[i].id)
                return i;
        }

        return -1;
    },

    setContactStatus: function(contact) {
        contact = contact.QueryInterface(csIIMContact);

        var index = this.searchContactsCache(contact);
        if (index == -1) {
            // Set default online status if undefined.
            if (contact.status == undefined)
                contact.status = "offline";
            this.mContactsCache.push(contact);
        }
        else {
            this.mContactsCache[index].alias = contact.alias;
            this.mContactsCache[index].status = contact.status;
            this.mContactsCache[index].statusMessage = contact.statusMessage;
        }

        // Special case to handle account logout
        if (contact.id == contact.account && contact.status == 'offline') {
          var members = [];

          // Set all members status to offline & update listeners
          for each (var member in this.mContactsCache) {
            if (member.account == contact.account &&
                member.id != contact.account) {
              member.status = 'offline';
              member.statusMessage = '';

              for each (var listener in this.mListeners) {
                listener = listener.QueryInterface(csIIMStatusListener);
                listener.statusUpdated(member);
              }
            }
          }

          // Remove all the members of the account from cache, 
          // except the account itself
          this.mContactsCache = this.mContactsCache.filter(function(item) {
                                  return !(item.account == contact.account &&
                                          item.id != contact.account);});
        }

        // Intimate about status change to listeners
        for each (var listener in this.mListeners) {
          listener = listener.QueryInterface(csIIMStatusListener);
          listener.statusUpdated(contact);
        }
    },

    getContactStatus: function(account, id) {
        if (id == null)
            return null;

        if (account == null)
          account = '--all--';

        var contact = Components.classes["@synovel.com/collab/im/imcontact;1"]
                                .createInstance(csIIMContact);

        contact.account = account;
        contact.id = id;

        var index = this.searchContactsCache(contact);
        if (index == -1)
            contact = null;
        else {
            contact.alias = this.mContactsCache[index].alias;
            contact.status = this.mContactsCache[index].status;
            contact.statusMessage = this.mContactsCache[index].statusMessage;
        }

        return contact;
    },

    addListener: function(aListener) {
      this.mListeners.push(aListener);
    },

    removeListener: function(aListener) {
      var index = this.mListeners.indexOf(aListener);
      if (index >= 0)
        this.mListeners.splice(index, 1);
    },

    QueryInterface: function(aIID) {
        if (!aIID.equals(nsIAbViewColumnHandler) &&    
            !aIID.equals(nsISupports) &&
            !aIID.equals(csIIMStatusService))
            throw Components.results.NS_ERROR_NO_INTERFACE;
        return this;
    }
};

/***********************************************************
* class factory
***********************************************************/

var csIMStatusServiceFactory = {
    createInstance: function (aOuter, aIID) {
        if (aOuter != null)
            throw Components.results.NS_ERROR_NO_AGGREGATION;
        return (new csIMStatusService()).QueryInterface(aIID);
    }
};

/***********************************************************
* module definition (xpcom registration)
***********************************************************/
var csIMStatusServiceModule = {
    registerSelf: function(aCompMgr, aFileSpec, aLocation, aType) {
        aCompMgr = aCompMgr.
        QueryInterface(Components.interfaces.nsIComponentRegistrar);
        aCompMgr.registerFactoryLocation(CLASS_ID, CLASS_NAME, 
                                         CONTRACT_ID, aFileSpec,
                                         aLocation, aType);
    },

    unregisterSelf: function(aCompMgr, aLocation, aType) {
        aCompMgr = aCompMgr.
                   QueryInterface(Components.interfaces.nsIComponentRegistrar);
        aCompMgr.unregisterFactoryLocation(CLASS_ID, aLocation);        
    },
  
    getClassObject: function(aCompMgr, aCID, aIID) {
        if (!aIID.equals(Components.interfaces.nsIFactory))
            throw Components.results.NS_ERROR_NOT_IMPLEMENTED;

        if (aCID.equals(CLASS_ID))
            return csIMStatusServiceFactory;
        
        throw Components.results.NS_ERROR_NO_INTERFACE;
    },

    canUnload: function(aCompMgr) { return true; }
};

/***********************************************************
* module initialization
*
* When the application registers the component, this function
* is called.
***********************************************************/
function NSGetModule(aCompMgr, aFileSpec) { return csIMStatusServiceModule; }

