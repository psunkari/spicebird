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
# Portions created by the Initial Developer are Copyright (C) 2007-2008
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Prasad Sunkari <prasad@synovel.com> (Original Author)
#   Ashok Gudibandla <ashok@synovel.com> 
#   Sivakrishna Edpuganti <sivakrishna@synovel.com> 
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

var gCurrentApplication = null;
var gHomeAppName = "home";

var gObserverService = Components.classes["@mozilla.org/observer-service;1"]
                        .getService(Components.interfaces.nsIObserverService);

var gIsCustomizeFrameworkToolbarWindowOpen = false;

// setCurrentApp will try to open tab.
// The tabType should implement shouldSwitchTo to select a particular
// tab to which a switch should happen (if at all it should)
function setCurrentApp(aCurrentApp)
{
  let tabcollab = document.getElementById("tabcollab");
  tabcollab.openTab(aCurrentApp, {switchToExisting: true});
}

function _updateToolbar()
{
    var toolbar = document.getElementById("framework-toolbox").firstChild.nextSibling;
    while (toolbar) {
        var re = new RegExp("\\b" + gCurrentApplication + "\\b");
        if (toolbar.getAttribute("app").match(re)) {
          toolbar.removeAttribute("collapsed");
        } else {
          if (!toolbar.hasAttribute("collapsed"))
            toolbar.setAttribute("collapsed", "true");
        }
        toolbar = toolbar.nextSibling;
    }
}

function _updateMenubar()
{
    // Force update menubar at the top level and mark the subsequent level as
    // dirty so that they are updated also but only if/when required.
    var menubar = document.getElementById("framework-menubar");
    menubar.setAttribute ("dirty", "true");
    csCreateAppMenus ("framework-menubar");

    var menu = menubar.firstChild;
    while (menu) {
        menu.firstChild.setAttribute("dirty", "true");
        menu = menu.nextSibling;
    }
}

function _updateStatusLabels(appName)
{
  var statusBar = document.getElementById("status-bar");
  var children = statusBar.getElementsByAttribute("app", "*");
  var re = new RegExp("\\b" + appName + "\\b");

  for (var i=0; i < children.length; i++ ) {
    var item = children[i];
    if (item.getAttribute("app").match(re))
      item.removeAttribute("collapsed");
    else 
      if (!item.hasAttribute("collapsed"))
        item.setAttribute("collapsed", "true");
  }
}

function closeTabOrWindow()
{
  let tabcollab = document.getElementById("tabcollab");
  if (tabcollab.tabInfo.length == 1) {
    if (pref.getBoolPref("collab.tabs.closeWindowWithLastTab"))
      window.close();
  } else {
    tabcollab.removeCurrentTab();
  }
}

function addCommonController (aController) {
   try {
      top.controllers.getControllerId(aController);
   }
   catch (e) { // not present.
      top.controllers.insertControllerAt(0, aController);
   }
}

function initCollabSuite()
{
}

var currentAppControllers = [];
function setAppControllers(aControllers)
{
   for each (var controller in aControllers)
      top.controllers.insertControllerAt(0, controller);

   currentAppControllers = aControllers;
}

function openAboutCollab()
{
#ifdef XP_MACOSX
  var wm = Components.classes["@mozilla.org/appshell/window-mediator;1"]
                     .getService(Components.interfaces.nsIWindowMediator);
  var win = wm.getMostRecentWindow("collab:about");
  if (win)  // If we have an open about dialog, just focus it.
    win.focus();
  else {
    // Define minimizable=no although it does nothing on OS X
    // (see Bug 287162); remove this comment once Bug 287162 is fixed...
    window.open("chrome://collab/content/about.xul", "About",
                "chrome, resizable=no, minimizable=no");
  }
#else
  window.openDialog("chrome://collab/content/about.xul", "About", "modal,centerscreen,chrome,resizable=no");
#endif
}

function getCurrentTab()
{
  var tabcollab = document.getElementById("tabcollab");
  return tabcollab? tabcollab.selectedItem: null;
}

function getLinkedTabPanel(aTab)
{
  if (aTab) {
    var tabpanelId = aTab.linkedPanel;
    if (tabpanelId)
      return document.getElementById(tabpanelId);
  }

  return null;
}

function getCurrentTabPanel()
{
  return getLinkedTabPanel(getCurrentTab());
}

function collapseSliderBox()
{
    var sliderBox = document.getElementById("sliderbox-vbox");
    if(sliderBox)
      sliderBox.setAttribute("collapsed", "true");
}

function toggleStatusbar()
{
    var statusbar = document.getElementById("status-bar");
    if(!statusbar)
        return;

    if( statusbar.hidden == true )
        statusbar.hidden = false;
    else
        statusbar.hidden = true;
}

function csOrderNewMenu(element)
{
  if (!element)
    return;

  if (element.getAttribute("current-app") == gCurrentApplication)
    return;

  element.getElementsByAttribute("current-app-separator", "*")[0].setAttribute("app", gCurrentApplication);

  var children = [];
  while (element.lastChild)
    children.push(element.removeChild(element.lastChild));

  var re = new RegExp("\\b" + gCurrentApplication + "\\b");
  children.sort(function(elementA, elementB) {
                  if (elementA.getAttribute("app").match(re) && !elementB.getAttribute("app").match(re))
                    return -1;

                  if (elementB.getAttribute("app").match(re) && !elementA.getAttribute("app").match(re))
                    return 1;

                  return parseInt(elementA.getAttribute("weight")) > parseInt(elementB.getAttribute("weight"));
                });
  for each (var child in children)
    element.appendChild(child);

  csCreateAppMenusForElement(element);
  element.setAttribute("current-app", gCurrentApplication);
}

function csCreateAppMenus(aElementId)
{
    /* Obviously, I am not happy about it, there should be cleaner way */
    var element = document.getElementById(aElementId);
    if (!element)
        return;

    if (element.getAttribute("dirty") != "true")
        return;

    csCreateAppMenusForElement(element);
}

function csCreateAppMenusForElement(element)
{
    var children = element.getElementsByAttribute("app", "*");
    var re = new RegExp("\\b" + gCurrentApplication + "\\b");

    for (var i = 0; i < children.length; i++) {
      if (children[i].getAttribute("app").match(re))
        children[i].removeAttribute ("hidden");
      else if (children[i].getAttribute("showalways"))
          children[i].removeAttribute("hidden");
      else
        children[i].setAttribute ("hidden", "true");
    }

    /* Separator removal */
    var lastSeparator;
    var visibleNodeAppeared = false;
    for (var i = 0; i < element.childNodes.length; i++) {
      if (element.childNodes[i].tagName == "menuseparator")
        element.childNodes[i].removeAttribute ("hidden");

      if (element.childNodes[i].getAttribute ("hidden") == "true")
        continue;

      if (element.childNodes[i].tagName == "menuseparator") {
        /* This will eliminate separators appearing at the begining */
        if (!visibleNodeAppeared)
          element.childNodes[i].setAttribute ("hidden", "true");
          
        /* This will eliminate consecutive separators */
        if (lastSeparator)
          lastSeparator.setAttribute ("hidden", "true");

        lastSeparator = element.childNodes[i];
      } else {
        lastSeparator = null;
        visibleNodeAppeared = true;
      }
    }
    /* This will eliminate the tailing separators */
    if (lastSeparator)
      lastSeparator.setAttribute ("hidden", "true");

    element.removeAttribute("dirty");
}

function goUpdateCommandset(commandset)
{
  if (typeof(commandset) == "string")
    commandset = document.getElementById(commandset);

  for (var i = 0; i < commandset.childNodes.length; i++)
  {
    var commandID = commandset.childNodes[i].getAttribute("id");
    if (commandID)
      goUpdateCommand(commandID);
  }
}

function initFileMenu()
{
    csCreateAppMenus("file-menupopup"); 

    goUpdateCommand('cmd_print');
    goUpdateCommand('cmd_printPreview');

    document.commandDispatcher.updateCommands('create-menu-file');
}

function goUpdateCollabToolbarItems()
{
  // The edit menu commands get updated automatically
  // through another function call.
  goUpdateCommand('cmd_print');
  goUpdateCommand('cmd_printPreview');
}

function initEditMenu()
{
    csCreateAppMenus("edit-menupopup"); 

    document.commandDispatcher.updateCommands('create-menu-edit');
}

function initViewMenu()
{
    // Try to update sidebar status
    var sidebarCommand = document.getElementById("cmd_viewSidebar");
    try {
      var collapsed = getCurrentTabPanel().isSidebarCollapsed();
      sidebarCommand.setAttribute("checked", !collapsed);
    } catch(ex) {}

    // Update statusbar status
    var statusbaritem = document.getElementById("view-statusbar-item");
    var statusbar = document.getElementById("status-bar");

    if(statusbar && statusbaritem) 
        statusbaritem.setAttribute("checked", !statusbar.hidden);

    csCreateAppMenus("view-menupopup"); 
    document.commandDispatcher.updateCommands('create-menu-view');
}

function initViewToolbarsPopup(aEvent, aToolboxID)
{
    var toolbox = document.getElementById(aToolboxID);
    if (!toolbox) 
      return;

    var toolbarsVisible = !toolbox.hasAttribute("toolbars") || 
                          (toolbox.getAttribute("toolbars") != "hidden");

    var mode = 'none';
    if (toolbarsVisible) 
      mode = toolbox.getAttribute('mode');

    let items = aEvent.target.getElementsByAttribute('mode', mode);
    if (items && items[0])
      items[0].setAttribute('checked', true);

    goUpdateCommand('cmd_customizeFWToolbar');
}

function initGoMenu()
{
    csCreateAppMenus ("go-menupopup");
    document.commandDispatcher.updateCommands('create-menu-go');
}

function initToolsMenu()
{
    csCreateAppMenus("tools-menupopup"); 
    document.commandDispatcher.updateCommands('create-menu-tools');
}

function initHelpMenu()
{
    document.commandDispatcher.updateCommands('create-menu-help');
    buildUpdateMenuItem();
}

function showJavascriptConsole()
{
    toOpenWindowByType("global:console", "chrome://global/content/console.xul");
}

function toOpenWindowByType(inType, uri, features)
{
    var windowManager = Components.classes['@mozilla.org/appshell/window-mediator;1'].getService();
    var windowManagerInterface = windowManager.QueryInterface(Components.interfaces.nsIWindowMediator);
    var topWindow = windowManagerInterface.getMostRecentWindow(inType);

    if (topWindow)
        topWindow.focus();
    else if (features)
        window.open(uri, "_blank", features);
    else
        window.open(uri, "_blank", "chrome,extrachrome,menubar,resizable,scrollbars,status,toolbar");
}

function showApplicationManager()
{
    const EMTYPE = "Extension:Manager";
    var wm = Components.classes["@mozilla.org/appshell/window-mediator;1"]
                       .getService(Components.interfaces.nsIWindowMediator);
    var theEM = wm.getMostRecentWindow(EMTYPE);
    if (theEM) {
        theEM.focus();
        return;
    }

    const EMURL = "chrome://mozapps/content/extensions/extensions.xul";
    const EMFEATURES = "chrome,menubar,extra-chrome,toolbar,dialog=no,resizable";
    window.openDialog(EMURL, "", EMFEATURES);
}

function CustomizeFrameworkToolbar()
{
    var menubar = document.getElementById("framework-menubar");
    for (var i = 0; i < menubar.childNodes.length; ++i)
        menubar.childNodes[i].setAttribute("disabled", true);

    gIsCustomizeFrameworkToolbarWindowOpen = true;

    window.openDialog("chrome://global/content/customizeToolbar.xul", 
                      "CustomizeToolbar", "chrome,all,dependent", 
                      document.getElementById("framework-toolbox"),
                      document.getElementById("tabcollab"));
}

function CustomizeFrameworkToolbarDone()
{
    var menubar = document.getElementById("framework-menubar");
    for (var i = 0; i < menubar.childNodes.length; ++i)
        menubar.childNodes[i].removeAttribute("disabled");

    gIsCustomizeFrameworkToolbarWindowOpen = false;

    setupHomeNewButton();
}

function setToolbarMode(aToolboxID, aModeValue)
{
  var toolbox = document.getElementById(aToolboxID);
  if (!toolbox) 
    return;

  if (aModeValue == 'none') {
    toolbox.setAttribute("toolbars", "hidden");
    document.persist(toolbox.id, "toolbars");
    return;
  } 
  toolbox.removeAttribute("toolbars");
  document.persist(toolbox.id, "toolbars");

  toolbox.setAttribute("mode", aModeValue);
  document.persist(toolbox.id, "mode");

  for (var i = 0; i < toolbox.childNodes.length; ++i) {
    var toolbar = toolbox.childNodes[i];
    if (toolbar.localName == "toolbar" && 
        toolbar.getAttribute("customizable") == "true" ) {
      toolbar.setAttribute("mode", aModeValue);
      document.persist(toolbar.id, "mode");
    }
  }
}

/*
 * Provides framework level handlers for few commands.
 * Also checks of any of the installed application is ready to
 * handle other commands and hands them off to the corresponding
 * application
 */
var csDefaultController = 
{    
    supportsCommand: function(aCommand) 
    {
        switch (aCommand)
        {
            case "cmd_pageSetup":
            case "cmd_viewSidebar":
            case "cmd_customizeFWToolbar":
                return true;
        }
        return false;
    },

    isCommandEnabled: function(aCommand)
    {
        switch (aCommand)
        {
            case "cmd_pageSetup":
                return true;
            case "cmd_viewSidebar":
                var tabPanel = getCurrentTabPanel();
                return tabPanel && tabPanel.hasSidebar();
            case "cmd_customizeFWToolbar":
                return !gIsCustomizeFrameworkToolbarWindowOpen;
        }
        return false;
    },

    doCommand: function(aCommand)
    {
        if (!this.isCommandEnabled(aCommand))
            return;

        switch (aCommand)
        {
            case "cmd_pageSetup":
                return PrintUtils.showPageSetup();
            case "cmd_viewSidebar":
                var tabPanel = getCurrentTabPanel();
                if ("toggleSidebar" in tabPanel)
                  return tabPanel.toggleSidebar();
            case "cmd_customizeFWToolbar":
                return CustomizeFrameworkToolbar();
        }
        return false;
    },
};

/**
 * Opens the update manager and checks for updates to the application.
 */

function checkForUpdates()
{
  var um =
      Components.classes["@mozilla.org/updates/update-manager;1"].
      getService(Components.interfaces.nsIUpdateManager);
  var prompter =
      Components.classes["@mozilla.org/updates/update-prompt;1"].
      createInstance(Components.interfaces.nsIUpdatePrompt);

  // If there's an update ready to be applied, show the "Update Downloaded"
  // UI instead and let the user know they have to restart the application for
  // the changes to be applied.
  if (um.activeUpdate && um.activeUpdate.state == "pending")
    prompter.showUpdateDownloaded(um.activeUpdate);
  else
  prompter.checkForUpdates();
}

// XXX: check and use
function buildUpdateMenuItem()
{
  var updates =
      Components.classes["@mozilla.org/updates/update-service;1"].
      getService(Components.interfaces.nsIApplicationUpdateService);
  var um =
      Components.classes["@mozilla.org/updates/update-manager;1"].
      getService(Components.interfaces.nsIUpdateManager);

  // Disable the UI if the update enabled pref has been locked by the
  // administrator or if we cannot update for some other reason
  var checkForUpdates = document.getElementById("help-update-item");
  var canUpdate = updates.canUpdate;
  checkForUpdates.setAttribute("disabled", !canUpdate);
  if (!canUpdate)
    return;

  var collabBundle = document.getElementById("bundle_collab");
  var activeUpdate = um.activeUpdate;

  // If there's an active update, substitute its name into the label
  // we show for this item, otherwise display a generic label.
  function getStringWithUpdateName(key) {
    if (activeUpdate && activeUpdate.name)
      return collabBundle.getFormattedString(key, [activeUpdate.name]);
    return collabBundle.getString(key + "Fallback");
    }

  // By default, show "Check for Updates..."
  var key = "default";
  if (activeUpdate) {
    switch (activeUpdate.state) {
    case "downloading":
      // If we're downloading an update at present, show the text:
      // "Downloading Firefox x.x..." otherwise we're paused, and show
      // "Resume Downloading Firefox x.x..."
      key = updates.isDownloading ? "downloading" : "resume";
      break;
    case "pending":
      // If we're waiting for the user to restart, show: "Apply Downloaded
      // Updates Now..."
      key = "pending";
      break;
    }
  }

  checkForUpdates.label = getStringWithUpdateName("updatesItem_" + key);
  if (um.activeUpdate && updates.isDownloading)
    checkForUpdates.setAttribute("loading", "true");
  else
    checkForUpdates.removeAttribute("loading");
}

function OnLoadCollab()
{
  var toolbox = document.getElementById("framework-toolbox");
  toolbox.customizeDone = CustomizeFrameworkToolbarDone;
  top.controllers.appendController(csDefaultController);
  gHomeApplets.create();

  // Check if the splash screen is waiting to be closed
  var windowMediator = Components.classes["@mozilla.org/appshell/window-mediator;1"]
                                 .getService(Components.interfaces.nsIWindowMediator);
  var splash = windowMediator.getMostRecentWindow("splash:window");
  if (splash)
    splash.close();

  // Is my window larger than the screen?
  if (document.documentElement.hasAttribute("width")) {
    var width = document.documentElement.getAttribute("width");
    var height = document.documentElement.getAttribute("height");

    if (parseInt(width) > screen.availWidth)
      document.documentElement.setAttribute("width", screen.availWidth * .95)

    if (parseInt(height) > screen.availHeight)
      document.documentElement.setAttribute("height", screen.availHeight * .8)

  // We are running Spicebird for the first time
  } else {
    var defaultWidth, defaultHeight;
    if (screen.availHeight <= 600) {
      document.documentElement.setAttribute("sizemode", "maximized");
      defaultWidth = 800;
      defaultHeight = 565;
    } else {
      defaultWidth = screen.availWidth <= 1024 ? screen.availWidth * .95 : screen.availWidth * .8;
      defaultHeight = screen.availHeight * .8;
    }

    document.documentElement.setAttribute("width", defaultWidth);
    document.documentElement.setAttribute("height", defaultHeight);
  }

  var tabcollab = document.getElementById ("tabcollab");
  if (tabcollab) {
    tabcollab.registerTabType(homeTabType);
    tabcollab.registerTabMonitor(collabTabMonitor);
    tabcollab.openFirstTab()
  }

  // This also registers the contentTabType ("contentTab")
  specialTabs.openSpecialTabsOnStartup();

  setupHomeNewButton();
}


function setupHomeNewButton()
{
  // new toolbarbutton if present on the home toolbar,
  // should be of type menu (not menu-button)
  let toolbar = document.getElementById("home-primary-toolbar");
  let toolbuttons = toolbar.getElementsByAttribute("typeid", "new-toolbutton");
  if (toolbuttons && toolbuttons[0])
    toolbuttons[0].setAttribute("type", "menu");
}

function openTimezoneSelectDialog() {
   window.openDialog("chrome://collab/content/timezoneSelect.xul",
                    "",
                    "chrome,modal=yes,resizable=no, width=400, height=500, centerscreen",
                    null);
}

/*
 * Tab type for the dashboard.
 */
var homeTabType = {
  name: "home",
  panelId: "applications-home",

  // Currently only one mode - home/dashboard
  modes: {
    home: {
      isDefault: true,
      type: "home",
      maxTabs: 1,     // Currently only one dashboard

      openFirstTab: function(aTab) {
        aTab.title = 'Home';
      },
      
      showTab: function(aTab) {
        if (typeof aTab.focusedElement != 'undefined' && aTab.focusedElement)
          aTab.focusedElement.focus();
      },
      
      onTitleChanged: function(aTab, aTabNode) {
        aTab.title = 'Home';
      },
      
      openTab: function(aTab, aArgs) {},
      persistTab: function(aTab) {},
      restoreTab: function(aTab) {},
      saveTabState: function(aTab) {},
      closeTab: function(aTab) {}
    }
  }
};

/*
 * collabTabMonitor monitors changes to the tabs and makes
 * the necessary changes to menus, toolbars and statusbar panels that
 * change with the currently active application.
 */
var collabTabMonitor = {
  onTabTitleChanged: function() {},
  onTabSwitched: function(aTab, aOldTab) {
    // Set appropriate value to current application for legacy tab model.
    // Usage of gCurrentApplication can be replaced by current tab type.
    gCurrentApplication = aTab.mode.type;

    function isElementChild(aParentElement, aChildElement) {
      var element = aChildElement;
      while (element && element != top) {
        if (element.isEqualNode(aParentElement))
          return true;
        element = element.parentNode;
      }
      return false;
    }
    
    // Store the focused element if its in the old tab.
    if (aOldTab) {
      let focusedElement = document.commandDispatcher.focusedElement;
      let oldTabPanel = aOldTab.panel || aOldTab.mode.tabType.panel;
      if (isElementChild(oldTabPanel, focusedElement))
        aOldTab.focusedElement = focusedElement;
    }

    // Update the user interface
    _updateToolbar();
    _updateMenubar();
    _updateStatusLabels(gCurrentApplication);
  }
};

