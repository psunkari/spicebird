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
#   Prasad Sunkari <prasad@synovel.com>
# Portions created by the Initial Developer are Copyright (C) 2007-2008
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Fred Jendrzejewski <fred.jen@web.de> 
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

const HOME_APPLETS_BRANCH = "collab.home.applets.";

var gHomeApplets = {

  mInitialized: false,
  mHomeBox: null,
  mPrefBranch: null,

  init: function()
  {
    this.mHomeBox = document.getElementById("applications-home-panel");
    this.mPrefBranch = Components.classes["@mozilla.org/preferences-service;1"]
                               .getService(Components.interfaces.nsIPrefService)
                               .getBranch(HOME_APPLETS_BRANCH)

    this.mInitialized = true;
  },

  create: function()
  {
    if (!this.mInitialized)
      this.init();

    var list = this.mPrefBranch.getChildList("", {});
    for (var i=0; i<list.length; i++) {
      var applet = list[i];
      if(/[^\.]*\.type/.test(applet)) {
        this.add(applet.split("\.")[0]);
      }
    }
  },

  add: function(aKey) 
  {
    try {
      var node = null;
      var type = this.mPrefBranch.getCharPref(aKey + ".type");
      var column = this.mPrefBranch.getIntPref(aKey + ".column");
      var weight = this.mPrefBranch.getIntPref(aKey + ".weight");
      var appnode = document.createElement(type);
      var appletNode = document.getElementById(type);
      
      node = document.createElement("homeapplet");
      node.setAttribute("class", "homeapplet");
      node.setAttribute("title", appletNode.getAttribute("label"));
      node.appendChild(appnode);

      node.setAttribute("column", column.toString());
      node.setAttribute("weight", weight.toString());
      node.setAttribute("homekey", aKey);
      node.setAttribute("id", type + "-" + aKey);
      this.mHomeBox.insertNode(node);
    } catch (ex) {
      dump("Could not create applet for " + aKey + "\n");
    }
  },

  // XXX: Supports only 1000 Applets? Who will need more anyway!
  // XXX: Code also assumes that its called from a menuitem
  addNew: function (aEvent)
  {
    var type = aEvent.originalTarget.value;
    if (!type)
      return;

    var key;
    try {
      for (key=0; key<1000; key++) 
        this.mPrefBranch.getCharPref(key.toString() + ".type");
    } catch (ex) { };

    this.mPrefBranch.setCharPref(key + ".type", type);
    this.setWeight (key, 0);
    this.setColumn (key, this.mHomeBox.getShortestColumn());
    this.add(key);
  },

  setWeight: function(aKey, aWeight)
  {
    this.mPrefBranch.setIntPref(aKey + ".weight", aWeight);
  },

  setColumn: function(aKey, aColumn)
  {
    this.mPrefBranch.setIntPref(aKey + ".column", aColumn);
  }
}

function initAddAppletMenu(aPopup)
{
    if (!aPopup)
        return false;

    var node = document.getElementById("framework-applets");
    var applets = node.childNodes;
    for each (var applet in applets) {
        var item = document.createElement("menuitem");
        try {
            item.setAttribute("label", applet.getAttribute("label"));
            item.setAttribute("value", applet.getAttribute("id"));
            item.setAttribute("id", applet.getAttribute("id") + "-menuitem");
            item.setAttribute("class","menuitem-iconic");
            aPopup.appendChild(item);
        } catch (ex) { }
    }

    aPopup.onpopupshowing = null;
    return true;
}
