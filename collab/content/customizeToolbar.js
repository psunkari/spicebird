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
# The Original Code is Mozilla Communicator client code, released
# March 31, 1998.
#
# The Initial Developer of the Original Code is
# David Hyatt.
# Portions created by the Initial Developer are Copyright (C) 2002
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   David Hyatt (hyatt@apple.com)
#   Blake Ross (blaker@netscape.com)
#   Joe Hewitt (hewitt@netscape.com)
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
*/

const kWindowWidth = 350;
const kWindowHeight = 400;
const kVSizeSlop = 5;

var gToolboxDocument = null;
var gToolbox = null;
var gTabCollab = null;
var gCurrentDragOverItem = null;
var gToolboxChanged = false;
var gToolboxIconSize = false;
var gToolboxSheet = false;

function onLoad()
{
  if ("arguments" in window && window.arguments[0]) {
    InitWithToolbox(window.arguments[0]);
    InitApplications(window.arguments[1]);
    repositionDialog();
  }
  else if (window.frameElement &&
           "toolbox" in window.frameElement) {
    gToolboxSheet = true;
    InitWithToolbox(window.frameElement.toolbox);
  }
}

function InitApplications(aTabCollab)
{
  if (!aTabCollab) 
    return;

  gTabCollab = aTabCollab;
  document.getElementById("customize-select-app").removeAttribute("collapsed");

  var appMenuPopup = document.getElementById("select-app-menupopup");
  var appMenuList = document.getElementById("select-app-menulist");

  // First child is the menubar :)
  var toolbar = gToolbox.firstChild.nextSibling;
  while(toolbar) {
    if(isCustomizableToolbar(toolbar)) {
      var menuItem = document.createElementNS(
                     "http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul", 
                     "menuitem");
      menuItem.setAttribute("id", toolbar.getAttribute("app").split(" ")[0] + "-toolbar");
      menuItem.setAttribute("class", "menuitem-iconic");
      menuItem.setAttribute("label", toolbar.getAttribute("toolbarname"));
      menuItem.setAttribute("value", toolbar.getAttribute("app"));
      menuItem.setAttribute("appname", toolbar.getAttribute("app"));
      appMenuPopup.appendChild(menuItem);
    }
    if (!toolbar.hasAttribute("collapsed") ||
         toolbar.getAttribute("collapsed") != "true")
      appMenuList.value = menuItem.value;

    toolbar = toolbar.nextSibling;
  }

  aTabCollab.registerTabMonitor(customizeToolbarTabMonitor);
  setTimeout(buildPalette, 0);
}

var customizeToolbarTabMonitor = {
  onTabTitleChanged: function() {},
  onTabSwitched: function(aTab, aOldTab) {
    let list = document.getElementById("select-app-menulist");
    let items = list.getElementsByAttribute("appname", "*");
    let app = aTab.mode.type;

    for (var i=0; i<items.length; i++) {
      let item = items[i];
      if (item.getAttribute("appname").split(" ").indexOf(app) >= 0) {
        list.selectedItem = item;
        break;
      }
    }

    // The user switched to tab that does not have a toolbar
    if (list.selectedItem.getAttribute("appname").split(" ").indexOf(app) < 0)
      list.selectedItem = null;

    // Rebuild the palette.
    setTimeout(buildPalette, 0);
  }
};

function SwitchApplication() 
{
  var list = document.getElementById("select-app-menulist");
  var apps = list.selectedItem.getAttribute("appname").split(" ");

  for each (app in apps) {
    if (gTabCollab.tabModes[app].tabs.length > 0)
      return window.opener.setCurrentApp(app);
  }

  // XXX: If we don't have open tabs, lets open one.
  window.opener.setCurrentApp(apps[0]);
}

function InitWithToolbox(aToolbox)
{
  gToolbox = aToolbox;
  gToolboxDocument = gToolbox.ownerDocument;
  gToolbox.customizing = true;

  gToolbox.addEventListener("dragstart", onToolbarDragStart, false);
  gToolbox.addEventListener("dragover", onToolbarDragOver, false);
  gToolbox.addEventListener("dragleave", onToolbarDragLeave, false);
  gToolbox.addEventListener("drop", onToolbarDrop, false);

  initDialog();
}

function onClose()
{
  if (!gToolboxSheet)
    window.close();
  else
    finishToolbarCustomization();
}

function onUnload()
{
  if (!gToolboxSheet)
    finishToolbarCustomization();
}

function finishToolbarCustomization()
{
  if (gTabCollab)
    gTabCollab.unregisterTabMonitor(customizeToolbarTabMonitor);

  gToolbox.customizing = false;
  removeToolboxListeners();
  unwrapToolbarItems();
  persistCurrentSets();
  
  notifyParentComplete();
}

function initDialog()
{
  buildPalette();

  // Wrap all the items on the toolbar in toolbarpaletteitems.
  wrapToolbarItems();
}

function repositionDialog()
{
  // Position the dialog touching the bottom of the toolbox and centered with 
  // it. We must resize the window smaller first so that it is positioned 
  // properly. 
  var screenX = gToolbox.boxObject.screenX + ((gToolbox.boxObject.width - kWindowWidth) / 2);
  var screenY = gToolbox.boxObject.screenY + gToolbox.boxObject.height;

  var newHeight = kWindowHeight;
  if (newHeight >= screen.availHeight - screenY - kVSizeSlop) {
    newHeight = screen.availHeight - screenY - kVSizeSlop;
  }

  window.resizeTo(kWindowWidth, newHeight);
  window.moveTo(screenX, screenY);
}

function removeToolboxListeners()
{
  gToolbox.removeEventListener("dragstart", onToolbarDragStart, false);
  gToolbox.removeEventListener("dragover", onToolbarDragOver, false);
  gToolbox.removeEventListener("dragleave", onToolbarDragLeave, false);
  gToolbox.removeEventListener("drop", onToolbarDrop, false);
}

/**
 * Invoke a callback on the toolbox to notify it that the dialog is done
 * and going away.
 */
function notifyParentComplete()
{
  if ("customizeDone" in gToolbox)
    gToolbox.customizeDone(gToolboxChanged);
}

function toolboxChanged(aEvent)
{
  gToolboxChanged = true;
  if ("customizeChange" in gToolbox)
    gToolbox.customizeChange(aEvent);
}

function getToolbarAt(i)
{
  return gToolbox.childNodes[i];
}

/**
 * Persist the current set of buttons in all customizable toolbars to
 * localstore.
 */
function persistCurrentSets()
{
  if (!gToolboxChanged || gToolboxDocument.defaultView.closed)
    return;

  var customCount = 0;
  for (var i = 0; i < gToolbox.childNodes.length; ++i) {
    // Look for customizable toolbars that need to be persisted.
    var toolbar = getToolbarAt(i);
    if (isCustomizableToolbar(toolbar)) {
      // Calculate currentset and store it in the attribute.
      var currentSet = toolbar.currentSet;
      toolbar.setAttribute("currentset", currentSet);
      
      var customIndex = toolbar.hasAttribute("customindex");
      if (customIndex) {
        if (!toolbar.firstChild) {
          // Remove custom toolbars whose contents have been removed.
          gToolbox.removeChild(toolbar);
          --i;
        } else {
          // Persist custom toolbar info on the <toolbarset/>
          gToolbox.toolbarset.setAttribute("toolbar"+(++customCount),
                                           toolbar.toolbarName + ":" + currentSet);
          gToolboxDocument.persist(gToolbox.toolbarset.id, "toolbar"+customCount);
        }
      }

      if (!customIndex) {
        // Persist the currentset attribute directly on hardcoded toolbars.
        gToolboxDocument.persist(toolbar.id, "currentset");
      }
    }
  }
  
  // Remove toolbarX attributes for removed toolbars.
  while (gToolbox.toolbarset.hasAttribute("toolbar"+(++customCount))) {
    gToolbox.toolbarset.removeAttribute("toolbar"+customCount);
    gToolboxDocument.persist(gToolbox.toolbarset.id, "toolbar"+customCount);
  }
}

/**
 * Wraps all items in all customizable toolbars in a toolbox.
 */
function wrapToolbarItems()
{
  for (var i = 0; i < gToolbox.childNodes.length; ++i) {
    var toolbar = getToolbarAt(i);
    if (isCustomizableToolbar(toolbar)) {
      for (var k = 0; k < toolbar.childNodes.length; ++k) {
        var item = toolbar.childNodes[k];

#ifdef XP_MACOSX
        if (item.firstChild && item.firstChild.localName == "menubar")
          continue;
#endif

        if (isToolbarItem(item)) {
          var wrapper = wrapToolbarItem(item);
          cleanupItemForToolbar(item, wrapper);
        }
      }
    }
  }
}

/**
 * Unwraps all items in all customizable toolbars in a toolbox.
 */
function unwrapToolbarItems()
{
  var paletteItems = gToolbox.getElementsByTagName("toolbarpaletteitem");
  var paletteItem;
  while ((paletteItem = paletteItems.item(0)) != null) {
    var toolbarItem = paletteItem.firstChild;

    if (paletteItem.hasAttribute("itemdisabled"))
      toolbarItem.disabled = true;

    if (paletteItem.hasAttribute("itemcommand"))
      toolbarItem.setAttribute("command", paletteItem.getAttribute("itemcommand"));

    paletteItem.parentNode.replaceChild(toolbarItem, paletteItem);
  }
}

/**
 * Creates a wrapper that can be used to contain a toolbaritem and prevent
 * it from receiving UI events.
 */
function createWrapper(aId, aDocument)
{
  var wrapper = aDocument.createElementNS("http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul",
                                         "toolbarpaletteitem");

  wrapper.id = "wrapper-"+aId;  
  return wrapper;
}

/**
 * Wraps an item that has been cloned from a template and adds
 * it to the end of a row in the palette.
 */
function wrapPaletteItem(aPaletteItem, aCurrentRow, aSpacer)
{
  var wrapper = createWrapper(aPaletteItem.id, document);

  wrapper.setAttribute("flex", 1);
  wrapper.setAttribute("align", "center");
  wrapper.setAttribute("pack", "center");
  wrapper.setAttribute("minheight", "0");
  wrapper.setAttribute("minwidth", "0");

  wrapper.appendChild(aPaletteItem);
  
  var listItem = document.createElementNS("http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul",
                                          "palettelistitem");
  listItem.appendChild(wrapper);
  
  // XXX We need to call this AFTER the palette item has been appended
  // to the wrapper or else we crash dropping certain buttons on the 
  // palette due to removal of the command and disabled attributes - JRH
  cleanUpItemForPalette(aPaletteItem, wrapper, listItem);

  if (aPaletteItem.hasAttribute("app"))
    aCurrentRow.insertBefore(listItem, document.getElementById("common-elements-separator"));
  else
    aCurrentRow.appendChild(listItem);

}

/**
 * Wraps an item that is currently on a toolbar and replaces the item
 * with the wrapper. This is not used when dropping items from the palette,
 * only when first starting the dialog and wrapping everything on the toolbars.
 */
function wrapToolbarItem(aToolbarItem)
{
  var wrapper = createWrapper(aToolbarItem.id, gToolboxDocument);

  wrapper.flex = aToolbarItem.flex;

  aToolbarItem.parentNode.replaceChild(wrapper, aToolbarItem);
  
  wrapper.appendChild(aToolbarItem);
  
  return wrapper;
}

/**
 * Builds the palette of draggable items that are not yet in a toolbar.
 */
function buildPalette()
{
  // Empty the palette first.
  var paletteBox = document.getElementById("palette-box");
  while (paletteBox.lastChild)
    paletteBox.removeChild(paletteBox.lastChild);

  // Separator for common & app specific items (dummy palette item)
  var commonSep = document.createElementNS("http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul",
                                           "palettelistitem");
  commonSep.id = "common-elements-separator";
  paletteBox.appendChild(commonSep);

  // Add the toolbar separator item.
  var templateNode = document.createElementNS("http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul",
                                              "toolbarseparator");
  templateNode.id = "separator";
  wrapPaletteItem(templateNode, paletteBox, null);

  // Add the toolbar spring item.
  templateNode = document.createElementNS("http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul",
                                          "toolbarspring");
  templateNode.id = "spring";
  templateNode.flex = 1;
  wrapPaletteItem(templateNode, paletteBox, null);

  // Add the toolbar spacer item.
  templateNode = document.createElementNS("http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul",
                                           "toolbarspacer");
  templateNode.id = "spacer";
  templateNode.flex = 1;
  wrapPaletteItem(templateNode, paletteBox, null);

  templateNode = gToolbox.palette.firstChild;
  while (templateNode) {
    if (canAddItemToPalette(templateNode)) {
      var paletteItem = templateNode.cloneNode(true);
      wrapPaletteItem(paletteItem, paletteBox, null);
    }
    
    templateNode = templateNode.nextSibling;
  }
}

function canAddItemToPalette(aItem) {
  var currentApp = window.opener.gCurrentApplication;
  if ( !currentApp ) { // customizing a dialog..
    var presentItem =  window.opener.document.getElementById(aItem.id);
    if (presentItem)
      return false;
    return true;
  }

  // Is the item already present on the current toolbar?
  var toolbar = gToolbox.firstChild;
  while (toolbar) {
    if (isToolbarShown(toolbar)) {
      var idPresent = toolbar.getElementsByAttribute("id", aItem.id);
      if (idPresent && idPresent.length > 0)
        return false;

      var typeIdPresent = toolbar.getElementsByAttribute("typeid", aItem.id);
      if (typeIdPresent && typeIdPresent.length > 0)
        return false;
    }
    toolbar = toolbar.nextSibling;
  }

  // There is no "app" attribute,
  // Let it be visible for every application.
  if (!aItem.hasAttribute("app"))
    return true;

  // Check if the item wants to be visible for current app
  var apps = aItem.getAttribute("app").split(" ");
  
  // True if the current app is included using "appname"
  if (apps.indexOf(currentApp) != -1)
    return true;

  return false;
}

/**
 * Creates a new palette item for a cloned template node and
 * adds it to the last slot in the palette.
 */
function appendPaletteItem(aItem)
{
  var paletteBox = document.getElementById("palette-box");
  wrapPaletteItem(aItem, paletteBox, null);
}

/**
 * Makes sure that an item that has been cloned from a template
 * is stripped of all properties that may adversely affect its
 * appearance in the palette.
 */
function cleanUpItemForPalette(aItem, aWrapper, aListItem)
{
  aWrapper.setAttribute("place", "palette");
  setWrapperType(aItem, aWrapper);

  if (aItem.hasAttribute("title"))
    aListItem.setAttribute("title", aItem.getAttribute("title"));
  if (aItem.hasAttribute("label"))
    aListItem.setAttribute("title", aItem.getAttribute("label"));
  else if (isSpecialItem(aItem)) {
    var stringBundle = document.getElementById("stringBundle");
    // Remove the common "toolbar" prefix to generate the string name.
    var title = stringBundle.getString(aItem.localName.slice(7) + "Title");
    aWrapper.setAttribute("title", title);
  }

  if (aItem.hasAttribute("tooltiptext")) 
    aListItem.setAttribute("tooltiptext", aItem.getAttribute("tooltiptext"));
  
  // Remove attributes that screw up our appearance.
  aItem.removeAttribute("command");
  aItem.removeAttribute("observes");
  aItem.removeAttribute("disabled");
  aItem.removeAttribute("type");
  aItem.removeAttribute("width");
  
  if (aItem.localName == "toolbaritem" && aItem.firstChild) {
    aItem.firstChild.removeAttribute("observes");

    // So the throbber doesn't throb in the dialog,
    // cute as that may be...
    aItem.firstChild.removeAttribute("busy");
  }
}

/**
 * Makes sure that an item that has been cloned from a template
 * is stripped of all properties that may adversely affect its
 * appearance in the toolbar.  Store critical properties on the 
 * wrapper so they can be put back on the item when we're done.
 */
function cleanupItemForToolbar(aItem, aWrapper)
{
  setWrapperType(aItem, aWrapper);
  aWrapper.setAttribute("place", "toolbar");

  if (aItem.hasAttribute("command")) {
    aWrapper.setAttribute("itemcommand", aItem.getAttribute("command"));
    aItem.removeAttribute("command");
  }

  if (aItem.disabled) {
    aWrapper.setAttribute("itemdisabled", "true");
    aItem.disabled = false;
  }
}

function setWrapperType(aItem, aWrapper)
{
  if (aItem.localName == "toolbarseparator") {
    aWrapper.setAttribute("type", "separator");
  } else if (aItem.localName == "toolbarspring") {
    aWrapper.setAttribute("type", "spring");
  } else if (aItem.localName == "toolbarspacer") {
    aWrapper.setAttribute("type", "spacer");
  } else if (aItem.localName == "toolbaritem" && aItem.firstChild) {
    aWrapper.setAttribute("type", aItem.firstChild.localName);
  }
}

function setDragActive(aItem, aValue)
{
  var node = aItem;
  var direction = window.getComputedStyle(aItem, null).direction;
  var value = direction == "ltr"? "left" : "right";
  if (aItem.localName == "toolbar") {
    node = aItem.lastChild;
    value = direction == "ltr"? "right" : "left";
  }
  
  if (!node)
    return;
  
  if (aValue) {
    if (!node.hasAttribute("dragover"))
      node.setAttribute("dragover", value);
  } else {
    node.removeAttribute("dragover");
  }
}

function addNewToolbar()
{
  var promptService = Components.classes["@mozilla.org/embedcomp/prompt-service;1"]
                                .getService(Components.interfaces.nsIPromptService);

  var stringBundle = document.getElementById("stringBundle");
  var message = stringBundle.getString("enterToolbarName");
  var title = stringBundle.getString("enterToolbarTitle");

  var name = {};

  while (true) {

    if (!promptService.prompt(window, title, message, name, null, {}))
      return;
    
    if (!name.value) {
      message = stringBundle.getFormattedString("enterToolbarBlank", [name.value]);
      continue;
    }

    var dupeFound = false;

     // Check for an existing toolbar with the same display name
    for (i = 0; i < gToolbox.childNodes.length; ++i) {
      var toolbar = gToolbox.childNodes[i];
      var toolbarName = toolbar.getAttribute("toolbarname");

      if (toolbarName == name.value &&
          toolbar.getAttribute("type") != "menubar" &&
          toolbar.nodeName == 'toolbar') {
        dupeFound = true;
        break;
      }
    }

    if (!dupeFound)
      break;

    message = stringBundle.getFormattedString("enterToolbarDup", [name.value]);
  }
    
  gToolbox.appendCustomToolbar(name.value, "");
  
  gToolboxChanged = true;
}

/**
 * Restore the default set of buttons to fixed toolbars,
 * remove all custom toolbars, and rebuild the palette.
 */
function restoreDefaultSet()
{
  // Unwrap the items on the toolbar.
  unwrapToolbarItems();

  // Remove all of the customized toolbars.
  var child = gToolbox.lastChild;
  while (child) {
    if (child.hasAttribute("customindex")) {
      var thisChild = child;
      child = child.previousSibling;
      thisChild.currentSet = "__empty";
      gToolbox.removeChild(thisChild);
    } else {
      child = child.previousSibling;
    }
  }

  // Restore the defaultset for fixed toolbars.
  var toolbar = gToolbox.firstChild;
  while (toolbar) {
    if (isCustomizableToolbar(toolbar)) {
      var defaultSet = toolbar.getAttribute("defaultset");
      if (defaultSet)
        toolbar.currentSet = defaultSet;
    }
    toolbar = toolbar.nextSibling;
  }

  // Now rebuild the palette.
  buildPalette();

  // Now re-wrap the items on the toolbar.
  wrapToolbarItems();

  toolboxChanged("reset");
}

/*
 * This method checks if a tool bar belongs to the currently shown application
 * by using the tags attribute of toolbar and the appname attrib of selected
 * list item. If the app list box is absent (i.e when configuring a dialog's toolbar),
 * it returns true.
 */
function isToolbarShown (aToolbar) {
  var selectedAppItem = document.getElementById("select-app-menulist").selectedItem;
  if (!selectedAppItem )
    return true;

  var tags = aToolbar.getAttribute("app");
  var selectedAppName  = selectedAppItem.getAttribute("appname");
  if (tags && tags.indexOf(selectedAppName) != -1) 
    return true;
  return false;
}

function setAttribute(aElt, aAttr, aVal)
{
 if (aVal)
    aElt.setAttribute(aAttr, aVal);
  else
    aElt.removeAttribute(aAttr);
}

function isCustomizableToolbar(aElt)
{
  return aElt.localName == "toolbar" &&
         aElt.getAttribute("customizable") == "true";
}

function isSpecialItem(aElt)
{
  return aElt.localName == "toolbarseparator" ||
         aElt.localName == "toolbarspring" ||
         aElt.localName == "toolbarspacer";
}

function isToolbarItem(aElt)
{
  return aElt.localName == "toolbarbutton" ||
         aElt.localName == "toolbaritem" ||
         aElt.localName == "toolbarseparator" ||
         aElt.localName == "toolbarspring" ||
         aElt.localName == "toolbarspacer";
}

///////////////////////////////////////////////////////////////////////////
//// Drag and Drop observers

function onToolbarDragStart(aEvent)
{
  nsDragAndDrop.startDrag(aEvent, dragStartObserver);
}

function onToolbarDragOver(aEvent)
{
  nsDragAndDrop.dragOver(aEvent, toolbarDNDObserver);
}

function onToolbarDrop(aEvent)
{
  nsDragAndDrop.drop(aEvent, toolbarDNDObserver);
}

function onToolbarDragLeave(aEvent)
{
  if (gCurrentDragOverItem)
    setDragActive(gCurrentDragOverItem, false);
}

var dragStartObserver =
{
  onDragStart: function (aEvent, aXferData, aDragAction) {
    var documentId = gToolboxDocument.documentElement.id;
    
    var item = aEvent.target;
    while (item && item.localName != "toolbarpaletteitem")
      item = item.parentNode;
    
    item.setAttribute("dragactive", "true");
    
    aXferData.data = new TransferDataSet();
    var data = new TransferData();
    var dataStr = item.firstChild.id + ":" + item.firstChild.getAttribute("typeid");
    data.addDataForFlavour("text/toolbarwrapper-id/"+documentId, dataStr);
    aXferData.data.push(data);
    aDragAction.action = Components.interfaces.nsIDragService.DRAGDROP_ACTION_MOVE;
  }
}

var toolbarDNDObserver =
{
  onDragOver: function (aEvent, aFlavour, aDragSession)
  {
    var toolbar = aEvent.target;
    var dropTarget = aEvent.target;
    while (toolbar && toolbar.localName != "toolbar") {
      dropTarget = toolbar;
      toolbar = toolbar.parentNode;
    }
    
    var previousDragItem = gCurrentDragOverItem;

    // Make sure we are dragging over a customizable toolbar.
    if (!isCustomizableToolbar(toolbar)) {
      gCurrentDragOverItem = null;
      return;
    }
    
    if (dropTarget.localName == "toolbar") {
      gCurrentDragOverItem = dropTarget;
    } else {
      gCurrentDragOverItem = null;

      var direction = window.getComputedStyle(dropTarget.parentNode, null).direction;
      var dropTargetCenter = dropTarget.boxObject.x + (dropTarget.boxObject.width / 2);
      var dragAfter;
      if (direction == "ltr")
        dragAfter = aEvent.clientX > dropTargetCenter;
      else
        dragAfter = aEvent.clientX < dropTargetCenter;
        
      if (dragAfter) {
        gCurrentDragOverItem = dropTarget.nextSibling;
        if (!gCurrentDragOverItem)
          gCurrentDragOverItem = toolbar;
      } else
        gCurrentDragOverItem = dropTarget;
    }    

    if (previousDragItem && gCurrentDragOverItem != previousDragItem) {
      setDragActive(previousDragItem, false);
    }
    
    setDragActive(gCurrentDragOverItem, true);
    
    aDragSession.canDrop = true;
  },
  
  onDrop: function (aEvent, aXferData, aDragSession)
  {
    if (!gCurrentDragOverItem)
      return;
    
    setDragActive(gCurrentDragOverItem, false);

    var draggedItemId = aXferData.data.split(":")[0];
    if (gCurrentDragOverItem.id == draggedItemId)
      return;

    var toolbar = aEvent.target;
    while (toolbar.localName != "toolbar")
      toolbar = toolbar.parentNode;

    var draggedPaletteWrapper = document.getElementById("wrapper-"+draggedItemId);       
    if (!draggedPaletteWrapper) {
      // The wrapper has been dragged from the toolbar.
      
      // Get the wrapper from the toolbar document and make sure that
      // it isn't being dropped on itself.
      var wrapper = gToolboxDocument.getElementById("wrapper-"+draggedItemId);
      if (wrapper == gCurrentDragOverItem)
        return;

      // Don't allow static kids (e.g., the menubar) to move.
      if (wrapper.parentNode.firstPermanentChild && wrapper.parentNode.firstPermanentChild.id == wrapper.firstChild.id)
        return;
      if (wrapper.parentNode.lastPermanentChild && wrapper.parentNode.lastPermanentChild.id == wrapper.firstChild.id)
        return;

      // Remove the item from its place in the toolbar.
      wrapper.parentNode.removeChild(wrapper);

      // Determine which toolbar we are dropping on.
      var dropToolbar = null;
      if (gCurrentDragOverItem.localName == "toolbar")
        dropToolbar = gCurrentDragOverItem;
      else
        dropToolbar = gCurrentDragOverItem.parentNode;
      
      // Insert the item into the toolbar.
      if (gCurrentDragOverItem != dropToolbar)
        dropToolbar.insertBefore(wrapper, gCurrentDragOverItem);
      else
        dropToolbar.appendChild(wrapper);
    } else {
      // The item has been dragged from the palette
      
      // Create a new wrapper for the item. We don't know the id yet.
      var wrapper = createWrapper("", gToolboxDocument);

      // Ask the toolbar to clone the item's template, place it inside the wrapper, and insert it in the toolbar.
      var newItem = toolbar.insertItem(draggedItemId, gCurrentDragOverItem == toolbar ? null : gCurrentDragOverItem, wrapper);
      
      // Prepare the item and wrapper to look good on the toolbar.
      cleanupItemForToolbar(newItem, wrapper);
      wrapper.id = "wrapper-"+newItem.id;
      wrapper.flex = newItem.flex;

      // Remove the wrapper from the palette.
      if (draggedItemId != "separator" &&
          draggedItemId != "spring" &&
          draggedItemId != "spacer")
      {
        var listItem = draggedPaletteWrapper.parentNode;
        var listView = listItem.parentNode;
        listView.removeChild(listItem);
      }
    }
    
    gCurrentDragOverItem = null;

    toolboxChanged();
  },
  
  _flavourSet: null,
  
  getSupportedFlavours: function ()
  {
    if (!this._flavourSet) {
      this._flavourSet = new FlavourSet();
      var documentId = gToolboxDocument.documentElement.id;
      this._flavourSet.appendFlavour("text/toolbarwrapper-id/"+documentId);
    }
    return this._flavourSet;
  }
}

var paletteDNDObserver =
{
  onDragOver: function (aEvent, aFlavour, aDragSession)
  {
    aDragSession.canDrop = true;
  },
  
  onDrop: function(aEvent, aXferData, aDragSession)
  {
    var ids = aXferData.data.split(":");
    var itemId = ids[0];
    var typeId = ids[1];
    if (typeId == "")
      typeId = itemId;
    
    var wrapper = gToolboxDocument.getElementById("wrapper-"+itemId);
    if (wrapper) {
      // Don't allow static kids (e.g., the menubar) to move.
      if (wrapper.parentNode.firstPermanentChild && wrapper.parentNode.firstPermanentChild.id == wrapper.firstChild.id)
        return;
      if (wrapper.parentNode.lastPermanentChild && wrapper.parentNode.lastPermanentChild.id == wrapper.firstChild.id)
        return;

      // The item was dragged out of the toolbar.
      wrapper.parentNode.removeChild(wrapper);
      
      var wrapperType = wrapper.getAttribute("type");
      if (wrapperType != "separator" && wrapperType != "spacer" && wrapperType != "spring") {
        // Find the template node in the toolbox palette
        var templateNode = gToolbox.palette.firstChild;
        while (templateNode) {
          if (templateNode.id == typeId)
            break;
          templateNode = templateNode.nextSibling;
        }
        if (!templateNode)
          return;
        
        // Clone the template and add it to our palette.
        var paletteItem = templateNode.cloneNode(true);
        appendPaletteItem(paletteItem);
      }
    }
    
    toolboxChanged();
  },
  
  _flavourSet: null,
  
  getSupportedFlavours: function ()
  {
    if (!this._flavourSet) {
      this._flavourSet = new FlavourSet();
      var documentId = gToolboxDocument.documentElement.id;
      this._flavourSet.appendFlavour("text/toolbarwrapper-id/"+documentId);
    }
    return this._flavourSet;
  }
}

