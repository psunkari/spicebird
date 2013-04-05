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


const csMailnewsAppInfo_ContractID = "@synovel.com/collab/mailnews-appinfo;1";
const csMailnewsAppInfo_CID = Components.ID("{870ac6f9-ad95-43ae-9474-8d6163cc37b9}");
const csMailnewsAppInfo_Desc = "Component for providing application information for Main & News application";

/********************
  csMailnewsAppInfo 
 ********************/
function csMailnewsAppInfo() {
  this._enabled = false;
}

csMailnewsAppInfo.prototype = {

  QueryInterface: function(aIID) {
    if (aIID.equals(csIAppInfo) ||
        aIID.equals(nsISupports))
      return this;

    throw Components.results.NS_ERROR_NO_INTERFACE;
  },

  get name() {
    return "mailnews";
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
    var appBundle = stringBundleService.createBundle("chrome://messenger/locale/synovel-messenger.properties");
    return appBundle.GetStringFromName("mailnews.appName");
  },

  getOverlays: function(aCount) {
    var overlays = [];
    overlays.push(new csMailnewsOverlayInfo(
                    "chrome://messenger/content/csMailnewsOverlay.xul",
                    "chrome://collab/content/collab.xul", 100));
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
  csMailnewsOverlayInfo 
 ***********************/
function csMailnewsOverlayInfo(aOverlay, aTarget, aPrio) {
  this._overlay = aOverlay;
  this._target = aTarget;
  this._priority = aPrio;
}

csMailnewsOverlayInfo.prototype = {

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
var csMailnewsAppInfoFactory = {
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
    return (new csMailnewsAppInfo()).QueryInterface(aIID);
  },

  lockFactory: function(lock) {}
};

/**********
   Module 
 **********/
var csMailnewsAppInfoModule = {
  
  /* nsISupports */
  QueryInterface: function QI(aIID) {
    if (aIID.equals(nsIModule) || 
        aIID.equals(nsISupports))
      return this;

    throw Components.results.NS_ERROR_NO_INTERFACE;
  },

  /* nsIModule */
  getClassObject: function (compMgr, cid, aIID) {
    if (cid.equals(csMailnewsAppInfo_CID))
      return csMailnewsAppInfoFactory;

    throw Components.results.NS_ERROR_FAILURE;
  },
    
  registerSelf: function (aCompMgr, aFileSpec, aLocation, aType) {
    /* Register the factory */
    var compReg = aCompMgr.QueryInterface(Components.interfaces.nsIComponentRegistrar);
    compReg.registerFactoryLocation(csMailnewsAppInfo_CID, 
                                    csMailnewsAppInfo_Desc,
                                    csMailnewsAppInfo_ContractID, 
                                    aFileSpec, aLocation, aType);

    /* Register to Category Manager */
    var catMan = Components.classes["@mozilla.org/categorymanager;1"]
                           .getService(Components.interfaces.nsICategoryManager);

    catMan.addCategoryEntry("installed-applications", "mailnews",
                            csMailnewsAppInfo_ContractID, true, true);
  },
    
  unregisterSelf: function (compMgr, location, type) {
    var compReg = compMgr.QueryInterface(Components.interfaces.nsIComponentRegistrar);
    compReg.unregisterFactoryLocation(csMailnewsAppInfo_CID, location);

    var catMan = Components.classes["@mozilla.org/categorymanager;1"]
                           .getService(Components.interfaces.nsICategoryManager);

    catMan.deleteCategoryEntry("installed-applications", "mailnews", true);
  },

  canUnload: function(compMgr) {
    return true;
  }
};

/* NSGetModule */
function NSGetModule(compMgr, fileSpec) {
  return csMailnewsAppInfoModule;
}
