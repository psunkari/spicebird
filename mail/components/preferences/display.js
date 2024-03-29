# -*- Mode: Java; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
# The Original Code is the Thunderbird Preferences System.
#
# The Initial Developer of the Original Code is
# Scott MacGregor.
# Portions created by the Initial Developer are Copyright (C) 2005
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Scott MacGregor <mscott@mozilla.org>
#   Prasad Sunkari <prasad@synovel.com>
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
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

var gDisplayPane = {
  mInitialized: false,
  mTagListBox:  null,

  init: function ()
  {
    var preference = document.getElementById("mail.preferences.display.selectedTabIndex");
    if (preference.value)
      document.getElementById("displayPrefs").selectedIndex = preference.value;

    this._rebuildFonts();
    var menulist = document.getElementById("defaultFont");
    if (menulist.selectedIndex == -1) {
      menulist.insertItemAt(0, "", "", "");
      menulist.selectedIndex = 0;
    }

    this.mInitialized = true;

    this.mTagListBox = document.getElementById("tagList");
    this.buildTagList();
  },

  // FONTS

  /**
   * Populates the default font list in UI.
   */
  _rebuildFonts: function ()
  {
    var langGroupPref = document.getElementById("font.language.group");
    this._selectDefaultLanguageGroup(langGroupPref.value,
          this._readDefaultFontTypeForLanguage(langGroupPref.value) == "serif");
  },

  /**
   * Select the default language group.
   */
  _selectDefaultLanguageGroup: function (aLanguageGroup, aIsSerif)
  {
    const kFontNameFmtSerif         = "font.name.serif.%LANG%";
    const kFontNameFmtSansSerif     = "font.name.sans-serif.%LANG%";
    const kFontNameListFmtSerif     = "font.name-list.serif.%LANG%";
    const kFontNameListFmtSansSerif = "font.name-list.sans-serif.%LANG%";
    const kFontSizeFmtVariable      = "font.size.variable.%LANG%";

    var prefs = [{format: aIsSerif ? kFontNameFmtSerif : kFontNameFmtSansSerif,
                  type: "fontname",
                  element: "defaultFont",
                  fonttype: aIsSerif ? "serif" : "sans-serif" },
                 {format: aIsSerif ? kFontNameListFmtSerif : kFontNameListFmtSansSerif,
                  type: "unichar",
                  element: null,
                  fonttype: aIsSerif ? "serif" : "sans-serif" },
                 {format: kFontSizeFmtVariable,
                  type: "int",
                  element: "defaultFontSize",
                  fonttype: null }];

    var preferences = document.getElementById("displayPreferences");
    for (var i = 0; i < prefs.length; ++i) {
      var preference = document.getElementById(prefs[i].format.replace(/%LANG%/,
                                                               aLanguageGroup));
      if (!preference) {
        preference = document.createElement("preference");
        var name = prefs[i].format.replace(/%LANG%/, aLanguageGroup);
        preference.id = name;
        preference.setAttribute("name", name);
        preference.setAttribute("type", prefs[i].type);
        preferences.appendChild(preference);
      }

      if (!prefs[i].element)
        continue;

      var element = document.getElementById(prefs[i].element);
      if (element) {
        element.setAttribute("preference", preference.id);

        if (prefs[i].fonttype)
          FontBuilder.buildFontList(aLanguageGroup, prefs[i].fonttype, element);

        preference.setElementValue(element);
      }
    }
  },

  /**
   * Returns the type of the current default font for the language denoted by
   * aLanguageGroup.
   */
  _readDefaultFontTypeForLanguage: function (aLanguageGroup)
  {
    const kDefaultFontType = "font.default.%LANG%";
    var defaultFontTypePref = kDefaultFontType.replace(/%LANG%/, aLanguageGroup);
    var preference = document.getElementById(defaultFontTypePref);
    if (!preference) {
      preference = document.createElement("preference");
      preference.id = defaultFontTypePref;
      preference.setAttribute("name", defaultFontTypePref);
      preference.setAttribute("type", "string");
      preference.setAttribute("onchange", "gDisplayPane._rebuildFonts();");
      document.getElementById("displayPreferences").appendChild(preference);
    }
    return preference.value;
  },

  tabSelectionChanged: function ()
  {
    if (this.mInitialized)
      document.getElementById("mail.preferences.display.selectedTabIndex")
              .valueFromPreferences = document.getElementById("displayPrefs").selectedIndex;
  },

  /**
   * Displays the fonts dialog, where web page font names and sizes can be
   * configured.
   */
  configureFonts: function ()
  {
    document.documentElement.openSubDialog("chrome://messenger/content/preferences/fonts.xul",
                                           "", null);
  },

  toggleTodo: function()
  {
    var index = this.mTagListBox.selectedIndex;
    if (index >= 0)
    {
      var item = this.mTagListBox.getItemAtIndex(index);
      var checkBox = item.getElementsByTagName("checkbox")[0];
      if (!checkBox)
        return;

      var pref = Components.classes["@mozilla.org/preferences-service;1"]
                           .getService(Components.interfaces.nsIPrefBranch2);
      pref.setBoolPref("mailnews.tags." + item.getAttribute("value") + ".todo", checkBox.checked);
    }
  },
  
  // appends the tag to the tag list box
  appendTagItem: function(aTagName, aKey, aColor)
  {
    var item = document.createElement("richlistitem");
    var labelCell = document.createElement("richlistcell");
    var checkCell = document.createElement("richlistcell");
    var checkbox = document.createElement("checkbox");
    var label = document.createElement("label");
    var pref = Components.classes["@mozilla.org/preferences-service;1"]
                         .getService(Components.interfaces.nsIPrefBranch2);

    item.appendChild(labelCell);
    item.appendChild(checkCell);
    checkCell.appendChild(checkbox);
    labelCell.appendChild(label);

    item.setAttribute("value", aKey);
    labelCell.setAttribute("flex", "1");
    label.setAttribute("value", aTagName);
    checkbox.setAttribute("oncommand", "gDisplayPane.toggleTodo()");

    var todo = false;
    try {
      todo = pref.getBoolPref("mailnews.tags." + aKey + ".todo");
    } catch (ex) {
      todo = false;
    }

    if (todo)
      checkbox.setAttribute("checked", "true");
    else
      checkbox.removeAttribute("checked");

    // var item = this.mTagListBox.appendItem(aTagName, aKey);
    this.mTagListBox.appendChild(item);
    item.style.color = aColor;
    return item;
  },

  buildTagList: function()
  {
    var tagService = Components.classes["@mozilla.org/messenger/tagservice;1"]
                               .getService(Components.interfaces.nsIMsgTagService);
    var tagArray = tagService.getAllTags({});
    for (var i = 0; i < tagArray.length; ++i)
    {
      var taginfo = tagArray[i];
      this.appendTagItem(taginfo.tag, taginfo.key, taginfo.color);
    }
  },

  removeTag: function()
  {
    var index = this.mTagListBox.selectedIndex;
    if (index >= 0)
    {
      var itemToRemove = this.mTagListBox.getItemAtIndex(index);
      var tagService = Components.classes["@mozilla.org/messenger/tagservice;1"].getService(Components.interfaces.nsIMsgTagService);
      tagService.deleteKey(itemToRemove.getAttribute("value"));
      this.mTagListBox.removeItemAt(index);
      var numItemsInListBox = this.mTagListBox.getRowCount();
      this.mTagListBox.selectedIndex = index < numItemsInListBox ? index : numItemsInListBox - 1;
    }
  },

  /**
   * Open the edit tag dialog
   */
  editTag: function()
  {
    var index = this.mTagListBox.selectedIndex;
    if (index >= 0)
    {
      var tagElToEdit = this.mTagListBox.getItemAtIndex(index);
      var args = {result: "", keyToEdit: tagElToEdit.getAttribute("value"), okCallback: editTagCallback};
      var dialog = window.openDialog(
                  "chrome://messenger/content/newTagDialog.xul",
                  "",
                  "chrome,titlebar,modal",
                  args);
    }
  },

  addTag: function()
  {
    var args = {result: "", okCallback: addTagCallback};
    var dialog = window.openDialog(
                 "chrome://messenger/content/newTagDialog.xul",
                 "",
                 "chrome,titlebar,modal",
                 args);
  },

  reorderTagUp: function()
  {
    var selected = this.mTagListBox.selectedItem;
    var index = this.mTagListBox.selectedIndex;
    var previous = this.mTagListBox.getPreviousItem(selected, 1);
    if (!previous)
      return;

    var selectedKey = selected.getAttribute("value");
    var previousKey = previous.getAttribute("value");

    var tagService = Components.classes["@mozilla.org/messenger/tagservice;1"]
                               .getService(Components.interfaces.nsIMsgTagService);

    this.initOrdinals(selectedKey);
    var selectedOrdinal = tagService.getOrdinalForKey(selectedKey);
    var previousOrdinal = tagService.getOrdinalForKey(previousKey);

    tagService.setOrdinalForKey(selectedKey, previousOrdinal);
    tagService.setOrdinalForKey(previousKey, selectedOrdinal);

    this.refreshTagList();
    this.mTagListBox.selectedIndex = index - 1;
  },

  reorderTagDown: function()
  {
    var selected = this.mTagListBox.selectedItem;
    var index = this.mTagListBox.selectedIndex;
    var next = this.mTagListBox.getNextItem(selected, 1);
    if (!next)
      return;

    var selectedKey = selected.getAttribute("value");
    var nextKey = next.getAttribute("value");

    var tagService = Components.classes["@mozilla.org/messenger/tagservice;1"]
                               .getService(Components.interfaces.nsIMsgTagService);

    this.initOrdinals(selectedKey);
    var selectedOrdinal = tagService.getOrdinalForKey(selectedKey);
    var nextOrdinal = tagService.getOrdinalForKey(nextKey);

    tagService.setOrdinalForKey(selectedKey, nextOrdinal);
    tagService.setOrdinalForKey(nextKey, selectedOrdinal);

    this.refreshTagList();
    this.mTagListBox.selectedIndex = index + 1;
  },

  refreshTagList: function()
  {
    while (this.mTagListBox.getRowCount())
      this.mTagListBox.removeItemAt(0);

    this.buildTagList();
  },

  createNextOrdinal: function(ordinal)
  {
    var num = parseInt(ordinal, 10) + 1;
    var newOrdinal = num.toString();
    var len = newOrdinal.length;

    for(var i = len; i < 4; i++)
      newOrdinal = "0" + newOrdinal;

    return newOrdinal;
  },

  initOrdinals: function(key)
  {
    var tagService = Components.classes["@mozilla.org/messenger/tagservice;1"]
                               .getService(Components.interfaces.nsIMsgTagService);
    try {
      tagService.getOrdinalForKey(selectedKey);
    } catch (ex) {
      var tagArray = tagService.getAllTags({});
      var ordinal = "0000";
      for (var i = 0; i < tagArray.length; ++i) {
        tagService.setOrdinalForKey(tagArray[i].key, ordinal);
        ordinal = this.createNextOrdinal(ordinal);
      }
    }
  },

  tagSelected: function()
  {
    var selected = this.mTagListBox.selectedItem;
    var reorderdown = document.getElementById("reorderTagDownButton");
    var reorderup = document.getElementById("reorderTagUpButton");

    reorderdown.disabled = true;
    reorderup.disabled = true;

    if(selected) {
      if(this.mTagListBox.selectedIndex != this.mTagListBox.getRowCount() - 1) 
        reorderdown.disabled = false;
      if(this.mTagListBox.selectedIndex != 0)
        reorderup.disabled = false;

      document.getElementById("editTagButton").removeAttribute("disabled");
      document.getElementById("removeTagButton").removeAttribute("disabled");
    } 
  }
};

function addTagCallback(aName, aColor)
{
  var tagService = Components.classes["@mozilla.org/messenger/tagservice;1"]
                    .getService(Components.interfaces.nsIMsgTagService);
  tagService.addTag(aName, aColor, "");

  var item = gDisplayPane.appendTagItem(aName, tagService.getKeyForTag(aName), aColor);
  var tagListBox = document.getElementById("tagList");
  tagListBox.ensureElementIsVisible(item);
  tagListBox.selectItem(item);
  tagListBox.focus();
}

function editTagCallback()
{
  // update the values of the selected item
  var tagListEl = document.getElementById("tagList");
  var index = tagListEl.selectedIndex;
  if (index >= 0)
  {
    var tagElToEdit = tagListEl.getItemAtIndex(index);
    var key = tagElToEdit.getAttribute("value");
    var tagService = Components.classes["@mozilla.org/messenger/tagservice;1"]
                     .getService(Components.interfaces.nsIMsgTagService);
    // update the color and label elements
    tagElToEdit.setAttribute("label", tagService.getTagForKey(key));
    tagElToEdit.style.color = tagService.getColorForKey(key);
  }
}
