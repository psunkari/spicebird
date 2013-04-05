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
# The Initial Developer of the Original Code is Synovel Software
# Portions created by the Initial Developer are Copyright (C) 2010
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Prasad Sunkari <prasad@synovel.com>
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

var GlodaToolbarHackTabMonitor = {
  onTabTitleChanged: function() {
  },

  onTabSwitched: function (aTab, aOldTab) {
    var toolbar = document.getElementById("mailnews-primary-toolbar");
    if (!toolbar)
      return;

    var item = toolbar.firstChild;
    var re = new RegExp("\\bglodaFacet\\b");

    // We are entering a glodaFacet tab... remove items that are not relevant
    if (aTab.mode.tabType == glodaFacetTabType) {
      while (item) {
        if (!item.hasAttribute("app") || item.getAttribute("app").match(re))
          item.removeAttribute("collapsed");
        else
          item.setAttribute("collapsed", "true");

        item = item.nextSibling;
      }

      // Remove unwanted separators & springs
      var visibleNodeAppeared = false;
      var lastSeparator;

      item = toolbar.firstChild;
      while(item) {
        if (item.tagName == "toolbarseparator")
          item.removeAttribute("collapsed");
       
        if (item.tagName == "toolbarseparator") {
          if (!visibleNodeAppeared)
            item.setAttribute("collapsed", "true");
            
          if (lastSeparator)
            lastSeparator.setAttribute("collapsed", "true");
       
          lastSeparator = item;
        } else if (!item.hasAttribute("collapsed")){
          lastSeparator = null;
          visibleNodeAppeared = true;
        }
        item = item.nextSibling;
      }

      if (lastSeparator)
        lastSeparator.setAttribute("collapsed", "true");
    }
    
    // Previous tab was glodaFacets, restore stuff.
    else if (aOldTab.mode.tabType == glodaFacetTabType) {
      while (item) {
        if (!item.hasAttribute("app") || item.getAttribute("app") != "glodaFacet")
          item.removeAttribute("collapsed");
        else
          item.setAttribute("collapsed", "true");

        item = item.nextSibling;
      }
    }
  }
};

