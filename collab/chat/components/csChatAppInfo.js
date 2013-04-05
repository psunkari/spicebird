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
#   Prasad Sunkari <prasad@synovel.com> (Original Author)
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

Components.utils.import("resource://gre/modules/XPCOMUtils.jsm");

var Ci = Components.interfaces;

function csChatAppInfo() {
  this._enabled = false;
}

csChatAppInfo.prototype = {

  // Component Variables
  classDescription: "Component for providing information about chat application",
  contractID: "@synovel.com/collab/chat/appinfo;1",
  classID: Components.ID("{8b73ca75-1d11-47ed-bf4d-1a9ca83c9726}"),

  // Categories
  _xpcom_categories: [{category: "installed-applications", entry: "chat"}],

  // Query Interface
  QueryInterface: XPCOMUtils.generateQI([Ci.csIAppInfo]),

  get name() {
    return "chat";
  },

  get enabled() {
    return this._enabled;
  },

  set enabled(aVal) {
    return this._enabled = aVal;
  },

  getDisplayName: function() {
    var strBundle = Components.classes["@mozilla.org/intl/stringbundle;1"]
                              .getService()
                              .QueryInterface(Ci.nsIStringBundleService)
                              .createBundle("chrome://chat/locale/csChatOverlay.properties");
    return strBundle.GetStringFromName("chat.appName");
  },

  getOverlays: function(aCount) {
    var overlays = [
      new csChatOverlayInfo(
        "chrome://chat/content/csChatOverlay.xul",
        "chrome://collab/content/collab.xul", 500),
      new csChatOverlayInfo(
        "chrome://chat/content/csChatPreferences.xul",
        "chrome://messenger/content/preferences/preferences.xul", 510),
      new csChatOverlayInfo(
        "chrome://chat/content/csAddressbookOverlay.xul",
        "chrome://messenger/content/addressbook/csContactsOverlay.xul", 520)
    ];
    aCount.value = overlays.length;
    return overlays;
  },

  getRequiredApps: function(aCount) {
    var apps = [];
    apps.push("contacts");
    aCount.value = apps.length;
    return apps;
  }
};

/*
 * csChatOverlayInfo 
 */

function csChatOverlayInfo(aOverlay, aTarget, aPrio)
{
  this._overlay = aOverlay;
  this._target = aTarget;
  this._priority = aPrio;
}

csChatOverlayInfo.prototype = {

  QueryInterface: XPCOMUtils.generateQI([Ci.csIOverlayInfo]),

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

var components = [csChatAppInfo];
function NSGetModule(compMgr, fileSpec)
{
  return XPCOMUtils.generateModule(components);
}
