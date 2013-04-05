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
#   Ashok Gudibandla <ashok@synovel.com> (Original Author)
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

const nsISupports              = Components.interfaces.nsISupports;
const nsIModule                = Components.interfaces.nsIModule;
const nsIFactory               = Components.interfaces.nsIFactory;
const csIAppInfo               = Components.interfaces.csIAppInfo;
const csIOverlayInfo           = Components.interfaces.csIOverlayInfo;


const csContactsAppInfo_ContractID = "@synovel.com/collab/contacts-appinfo;1";
const csContactsAppInfo_CID = Components.ID("{198616e9-bb14-4b5b-8811-b1b25b7cf306}");
const csContactsAppInfo_Desc = "Component for providing application information for Contacts application";

/********************
  csContactsAppInfo 
 ********************/
function csContactsAppInfo() {
  this._enabled = false;
}

csContactsAppInfo.prototype = {

  QueryInterface: function(aIID) {
    if (aIID.equals(csIAppInfo) ||
        aIID.equals(nsISupports))
      return this;

    throw Components.results.NS_ERROR_NO_INTERFACE;
  },

  get name() {
    return "contacts";
  },

  get enabled() {
    return this._enabled;
  },

  set enabled(aVal) {
    return this._enabled = aVal;
  },

  getDisplayName: function() {
    var stringBundleService = Components.classes["@mozilla.org/intl/stringbundle;1"].getService();
    stringBundleService = stringBundleService.QueryInterface(Components.interfaces.nsIStringBundleService);
    var appBundle = stringBundleService.createBundle("chrome://messenger/locale/addressbook/contacts.properties");
    return appBundle.GetStringFromName("contacts.appName");
  },

  getOverlays: function(aCount) {
    var overlays = [];
    overlays.push(new csContactsOverlayInfo(
                    "chrome://messenger/content/addressbook/csContactsOverlay.xul",
                    "chrome://collab/content/collab.xul", 200));
    aCount.value = overlays.length;
    return overlays;
  },

  getRequiredApps: function(aCount) {
    var apps = [];
    aCount.value = apps.length;
    return apps;
  }
};

/***********************
  csContactsOverlayInfo 
 ***********************/
function csContactsOverlayInfo(aOverlay, aTarget, aPrio) {
  this._overlay = aOverlay;
  this._target = aTarget;
  this._priority = aPrio;
}

csContactsOverlayInfo.prototype = {

  QueryInterface: function(aIID) {
    if (aIID.equals(csIOverlayInfo) ||
        aIID.equals(nsISupports))
      return this;

    throw Components.results.NS_ERROR_NO_INTERFACE;
  },

  get overlay() {
    return this._overlay;
  },

  get target() {
    return this._target;
  },

  get priority() {
    return this._priority;
  }
};

/***********
   Factory
 ***********/
var csContactsAppInfoFactory = {
  QueryInterface: function(aIID) {
    if (aIID.equals(nsIFactory) ||
        aIID.equals(nsISupports))
      return this;
    throw Components.results.NS_ERROR_NO_INTERFACE;
  },

  createInstance: function(aOuter, aIID) {
    if (aOuter != null) {
      throw Components.results.NS_ERROR_NO_AGGREGATION;
    }
    return (new csContactsAppInfo()).QueryInterface(aIID);
  },

  lockFactory: function(lock) {}
};

/**********
   Module 
 **********/
var csContactsAppInfoModule = {
  
  /* nsISupports */
  QueryInterface: function QI(aIID) {
    if (aIID.equals(nsIModule) || 
        aIID.equals(nsISupports))
      return this;

    throw Components.results.NS_ERROR_NO_INTERFACE;
  },

  /* nsIModule */
  getClassObject: function (compMgr, cid, aIID) {
    if (cid.equals(csContactsAppInfo_CID))
      return csContactsAppInfoFactory;

    throw Components.results.NS_ERROR_FAILURE;
  },
    
  registerSelf: function (aCompMgr, aFileSpec, aLocation, aType) {
    /* Register the factory */
    var compReg = aCompMgr.QueryInterface(Components.interfaces.nsIComponentRegistrar);
    compReg.registerFactoryLocation(csContactsAppInfo_CID, 
                                    csContactsAppInfo_Desc,
                                    csContactsAppInfo_ContractID, 
                                    aFileSpec, aLocation, aType);

    /* Register to Category Manager */
    var catMan = Components.classes["@mozilla.org/categorymanager;1"]
                           .getService(Components.interfaces.nsICategoryManager);

    catMan.addCategoryEntry("installed-applications", "contacts",
                            csContactsAppInfo_ContractID, true, true);
  },
    
  unregisterSelf: function (compMgr, location, type) {
    var compReg = compMgr.QueryInterface(Components.interfaces.nsIComponentRegistrar);
    compReg.unregisterFactoryLocation(csContactsAppInfo_CID, location);

    var catMan = Components.classes["@mozilla.org/categorymanager;1"]
                           .getService(Components.interfaces.nsICategoryManager);

    catMan.deleteCategoryEntry("installed-applications", "contacts", true);
  },

  canUnload: function(compMgr) {
    return true;
  }
};

/* NSGetModule */
function NSGetModule(compMgr, fileSpec) {
  return csContactsAppInfoModule;
}
