/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Synovel Software code.
 *
 * The Initial Developer of the Original Code is
 *   Sivakrishna Edpuganti <sivakrishna@synovel.com>
 * Portions created by the Initial Developer are Copyright (C) 2007
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
/* -*- Mode: javascript; tab-width: 20; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/***********************************************************
* constants
***********************************************************/

const csITimezones = Components.interfaces.csITimezones;
const nsISupports = Components.interfaces.nsISupports;

// UUID uniquely identifying our component
const CLASS_ID = Components.ID("{82683f3d-9bbd-4741-a867-d3f4dc9e48ad}");

// description
const CLASS_NAME = "Component that provides timezone utility functions";

// textual unique identifier
const CONTRACT_ID = "@synovel.com/collab/collab/timezones;1";

/***********************************************************
* class definition
***********************************************************/

// Class constructor
function csTimezones() {
  this.mPrefBranch = Components.classes['@mozilla.org/preferences-service;1']
                               .getService(Components.interfaces.nsIPrefService)
                               .getBranch('collab.timezones.default.');

  this.mTzSvc =  Components.classes["@mozilla.org/calendar/timezone-service;1"]
                           .getService(Components.interfaces.calITimezoneService);

  this.mDatetimeFormatter =  Components.classes["@mozilla.org/calendar/datetime-formatter;1"]
                                       .getService(Components.interfaces.calIDateTimeFormatter);
  this.init();
};

// class definition
csTimezones.prototype = {

  mCurrentTimezoneId: "",
  mAllTimezoneIds: new Array(),
  mDefaultTimezoneIds: new Array(),

  refreshDefaultTimezones: function () {
    this.mDefaultTimezoneIds.length = 0;
    var list = this.mPrefBranch.getChildList("", {});

    for( var i=0; i<list.length; i++ ) {
      var zone = this.mPrefBranch.getCharPref(list[i]);
      this.mDefaultTimezoneIds.push(zone);
    }

    this.mDefaultTimezoneIds.sort();
  },

  refreshAllTimezones: function() {
    this.mAllTimezoneIds.length = 0;
    var enumerator = this.mTzSvc.timezoneIds;

    while (enumerator.hasMore())
      this.mAllTimezoneIds.push(enumerator.getNext());
  },

  init: function() {
    this.refreshDefaultTimezones();
    this.refreshAllTimezones();
  },

  getAllTimezoneIds: function (length) {
    length.value = this.mAllTimezoneIds.length;
    return this.mAllTimezoneIds;
  },

  getDefaultTimezoneIds: function (length) {
    length.value = this.mDefaultTimezoneIds.length;
    return this.mDefaultTimezoneIds;
  },

  isTimezoneId: function (timezoneId) {
    if (this.mAllTimezoneIds.indexOf(timezoneId) == -1)
      return false;

    return true;
  },

  get currentTimezoneId () {
    this.mCurrentTimezoneId = calendarDefaultTimezone();
    return this.mCurrentTimezoneId;
  },

  setDefaultTimezoneIds: function (length, timezoneIds) {

    this.mPrefBranch.deleteBranch("");

    timezoneIds.sort();
    timezoneIds.reverse();
    var key = 1;
    var tzId = "";
    while (timezoneIds.length)
    {
      tzId = timezoneIds.pop();
      // Check if present in alltimezones list.
      if (this.isTimezoneId(tzId))
      {
        this.mPrefBranch.setCharPref(key.toString(), tzId);
        key++;
      }
      else
        dump('setDefaultTimezoneIds: Ignoring unrecognized timezone id: ' + tzId + '\n');
    }

    this.refreshDefaultTimezones();
  },

  getInTimezone: function (iDatetime, timezoneId) {
    var d  = new Date(iDatetime);
    var dt = jsDateToDateTime(d);
    var datetimeString = "";

    var timezone = this.mTzSvc.getTimezone(timezoneId);

    if (timezone) 
    {
      var newdt = dt.getInTimezone(timezone);
      datetimeString = this.mDatetimeFormatter.formatDateTime(newdt);
    }
    else
      dump('getInTimezone: Ignoring unrecognized timezone id: ' + timezoneId + '\n');

    return datetimeString;
  },

  getTimezoneOffset: function(timezoneId) {
    var d  = new Date();
    var dt = jsDateToDateTime(d);

    try {
      var timezone = this.mTzSvc.getTimezone(timezoneId);
      return dt.getInTimezone(timezone).timezoneOffset;
    } catch(ex) {
      dump('getTimezoneOffset: Error in fetching offset : ' + ex + '\n');
    }
  },

  QueryInterface: function(aIID) {
    if (!aIID.equals(csITimezones) &&    
      !aIID.equals(nsISupports))
      throw Components.results.NS_ERROR_NO_INTERFACE;
    return this;
  }
};

/***********************************************************
* class factory
***********************************************************/

var csTimezonesFactory = {
  createInstance: function (aOuter, aIID) {
    if (aOuter != null)
      throw Components.results.NS_ERROR_NO_AGGREGATION;
    return (new csTimezones()).QueryInterface(aIID);
  }
};

/***********************************************************
* module definition (xpcom registration)
***********************************************************/
var csTimezonesModule = {
  loadScripts: function() {
    var scripts = [ "calUtils.js" ];
    var scriptLoader =  Components.classes["@mozilla.org/moz/jssubscript-loader;1"]
                                  .getService(Components.interfaces.mozIJSSubScriptLoader);
     
    var iosvc = Components.classes["@mozilla.org/network/io-service;1"]
                          .getService(Components.interfaces.nsIIOService);
     
    var appdir = __LOCATION__.parent.parent;
    appdir.append("calendar-js");
     
    if ( !scriptLoader ) return;
     
    for each (var script in scripts) {
      var scriptName = appdir.clone();
      scriptName.append(script);
     
      try {
        var scriptUri = iosvc.newFileURI(scriptName);
        scriptLoader.loadSubScript(scriptUri.spec, null);
      } catch (e) {
        dump("Error while loading " + scriptUri.spec + "\n");
        throw e;
      }
    }
  },

  registerSelf: function(aCompMgr, aFileSpec, aLocation, aType) {
    aCompMgr = aCompMgr.QueryInterface(Components.interfaces.nsIComponentRegistrar);

    aCompMgr.registerFactoryLocation(CLASS_ID, CLASS_NAME, 
                                     CONTRACT_ID, aFileSpec,
                                     aLocation, aType);
  },

  unregisterSelf: function(aCompMgr, aLocation, aType) {
    aCompMgr = aCompMgr.QueryInterface(Components.interfaces.nsIComponentRegistrar);
    aCompMgr.unregisterFactoryLocation(CLASS_ID, aLocation);        
  },
  
  getClassObject: function(aCompMgr, aCID, aIID) {
    if (!aIID.equals(Components.interfaces.nsIFactory))
      throw Components.results.NS_ERROR_NOT_IMPLEMENTED;

    if (aCID.equals(CLASS_ID))
    {
      this.loadScripts();
      return csTimezonesFactory;
    }
    
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
function NSGetModule(aCompMgr, aFileSpec) { return csTimezonesModule; }

