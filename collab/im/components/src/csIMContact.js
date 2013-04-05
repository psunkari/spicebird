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

const csIIMContact = Components.interfaces.csIIMContact;
const nsISupports = Components.interfaces.nsISupports;

// UUID uniquely identifying our component
const CLASS_ID = Components.ID("{2b3e92ae-77b6-4151-9dba-acb5add31b79}");

// description
const CLASS_NAME = "Component that contains details of a contact";

// textual unique identifier
const CONTRACT_ID = "@synovel.com/collab/im/imcontact;1";

/***********************************************************
* class definition
***********************************************************/

// Class constructor
function csIMContact() {
};

// class definition
csIMContact.prototype = {

    mAccount: "",
    mConnectionID: "",
    mId: "",
    mAlias: "",
    mStatus: "",
    mStatusMessage: "",

    get account() { return this.mAccount; },
    set account(aValue) { this.mAccount = aValue; },

    get id() { return this.mId; },
    set id(aValue) { this.mId = aValue; },

    get alias() { return this.mAlias; },
    set alias(aValue) { this.mAlias = aValue; },

    get status() { return this.mStatus; },
    set status(aValue) { this.mStatus = aValue; },

    get statusMessage() { return this.mStatusMessage; },
    set statusMessage(aValue) { this.mStatusMessage = aValue; },

    get connectionID() { return this.mConnectionID; },
    set connectionID(aValue) { this.mConnectionID = aValue; },

    QueryInterface: function(aIID) {
        if (!aIID.equals(csIIMContact) &&    
            !aIID.equals(nsISupports))
            throw Components.results.NS_ERROR_NO_INTERFACE;
        return this;
    }
};

/***********************************************************
* class factory
***********************************************************/

var csIMContactFactory = {
    createInstance: function (aOuter, aIID) {
        if (aOuter != null)
            throw Components.results.NS_ERROR_NO_AGGREGATION;
        return (new csIMContact()).QueryInterface(aIID);
    }
};

/***********************************************************
* module definition (xpcom registration)
***********************************************************/
var csIMContactModule = {
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
            return csIMContactFactory;
        
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
function NSGetModule(aCompMgr, aFileSpec) { return csIMContactModule; }

