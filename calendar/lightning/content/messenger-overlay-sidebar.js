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
 * The Original Code is Lightning code.
 *
 * The Initial Developer of the Original Code is Oracle Corporation
 * Portions created by the Initial Developer are Copyright (C) 2005
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Mike Shaver <shaver@mozilla.org>
 *   Vladimir Vukicevic <vladimir@pobox.com>
 *   Stuart Parmenter <stuart.parmenter@oracle.com>
 *   Dan Mosedale <dmose@mozilla.org>
 *   Joey Minta <jminta@gmail.com>
 *   Simon Paquet <bugzilla@babylonsounds.com>
 *   Stefan Sitter <ssitter@googlemail.com>
 *   Thomas Benisch <thomas.benisch@sun.com>
 *   Michael Buettner <michael.buettner@sun.com>
 *   Philipp Kewisch <mozilla@kewis.ch>
 *   Berend Cornelius <berend.cornelius@sun.com>
 *   Martin Schroeder <mschroeder@mozilla.x-home.org>
 *   Prasad Sunkari <prasad@synovel.com>
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

var gLastShownCalendarView = null;

var calendarTabType = {
  name: "calendar",
  panelId: "tabpanel-calendar",
  modes: {
    calendar: {
      type: "calendar",
      maxTabs: 1,
      openTab: function(aTab, aArgs) {
        aTab.title = aArgs["title"];
        if (!("background" in aArgs) || !aArgs["background"]) {
            // Only do calendar mode switching if the tab is opened in
            // foreground.
            ltnSwitch2Calendar();
        }

        if (("selectedDay" in aArgs) && aArgs.selectedDay != null) {
            currentView().goToDay(aArgs.selectedDay);
        }
        this.panel = document.getElementById("tabpanel-calendar");

        if (!aTab.title) {
          var StringBundle = document.getElementById("bundle_collab");
          aTab.title  = StringBundle.getString("calendarTitle");
        }
      },

      showTab: function(aTab) {
        ltnSwitch2Calendar();

        // Restore the previously focused element if any.
        var focusedElement = aTab.focusedElement;
        if (!focusedElement)
       	  focusedElement = document.getElementById("calendar-list-tree-widget");
        focusedElement.focus();
   
        // We need this for updateCommands to work fine.
        gCurrentApplication = "calendar";
        calendarController.updateCommands();
        calendarAppController.updateCommands();
      },
      closeTab: function(aTab) {
        if (gCurrentMode == "calendar") {
          // Only revert menu hacks if closing the active tab, otherwise we
          // would switch to mail mode even if in task mode and closing the
          // calendar tab.
          ltnSwitch2Mail();
        }
      },
      saveTabState: function(aTab) {},

      // Command handling
      supportsCommand: function(aCommand, aTab) {
        try {
          let controller = this.panel.controllers.getControllerForCommand(aCommand);
          if (controller)
            return true;
        } catch (ex) {};
        return false;
      },
      isCommandEnabled: function(aCommand, aTab) {
        try {
          let controller = this.panel.controllers.getControllerForCommand(aCommand);
          var enabled = false;
          if (controller)
            return controller.isCommandEnabled(aCommand);
        } catch (ex) {};

        return false;
      },
      doCommand: function(aCommand, aTab) {
        try {
          let controller = this.panel.controllers.getControllerForCommand(aCommand);
          if (controller && controller.isCommandEnabled(aCommand))
            controller.doCommand(aCommand);
        } catch (ex) {};
      }
    }
  }
};

var tasksTabType = {
  name: "tasks",
  panelId: "tabpanel-tasks",
  modes: {
    tasks: {
      type: "tasks",
      maxTabs: 1,
      openTab: function(aTab, aArgs) {
        aTab.title = aArgs["title"];
        if (!("background" in aArgs) || !aArgs["background"]) {
            ltnSwitch2Task();
        }
        this.panel = document.getElementById("tabpanel-tasks");
        if (!aTab.title) {
          var StringBundle = document.getElementById("bundle_collab");
          aTab.title  = StringBundle.getString("tasksTitle");
        }
      },
      showTab: function(aTab) {
        ltnSwitch2Task();

        // Restore the previously focused element if any.
        var focusedElement = aTab.focusedElement;
        if (!focusedElement) {
          var taskTree = document.getElementById("calendar-task-tree");
          focusedElement = document.getAnonymousElementByAttribute(taskTree, "anonid", "calendar-task-tree");
        }
        focusedElement.focus();
       
        // We need this for updateCommands to work fine.
        gCurrentApplication = "tasks";
        calendarController.updateCommands();
       
        var filter = "all";
        if (document.getElementById("task-tree-filtergroup") &&
          document.getElementById("task-tree-filtergroup").value)
          filter = document.getElementById("task-tree-filtergroup").value;
       
        taskViewUpdate(filter);
      },
      closeTab: function(aTab) {
        if (gCurrentMode == "task") {
          // Only revert menu hacks if closing the active tab, otherwise we
          // would switch to mail mode even if in calendar mode and closing the
          // tasks tab.
          ltnSwitch2Mail();
        }
      },
      saveTabState: function(aTab) {},

      // Command handling
      supportsCommand: function(aCommand, aTab) {
        try {
          let controller = this.panel.controllers.getControllerForCommand(aCommand);
          if (controller)
            return true;
        } catch (ex) {};
        return false;
      },
      isCommandEnabled: function(aCommand, aTab) {
        try {
          let controller = this.panel.controllers.getControllerForCommand(aCommand);
          var enabled = false;
          if (controller)
            return controller.isCommandEnabled(aCommand);
        } catch (ex) {};

        return false;
      },
      doCommand: function(aCommand, aTab) {
        try {
          let controller = this.panel.controllers.getControllerForCommand(aCommand);
          if (controller && controller.isCommandEnabled(aCommand))
            controller.doCommand(aCommand);
        } catch (ex) {};
      }
    }
  }
};

function prepareCalendarToDoUnifinder()
{
    // Spicebird needs this empty function!
    //
    // This function is available in calendar-unifinder-todo.js and needs
    // calendar-unifinder-todo.xul to overlay the main window.
    // However, we don't have a today-pane and the overlay would not happen
}

// XXX: Need to handle multiple window scenarios
var calImipBarCollapseObserver = {
  observe: function(aSubject, aTopic, aData) {
    if (aTopic == "MsgClearNotifications" && aSubject == window.document) {
      document.getElementById("imip-bar").setAttribute("collapsed", true);
    }
  }
}

function ltnOnLoad(event) {

    // nuke the onload, or we get called every time there's
    // any load that occurs
    document.removeEventListener("load", ltnOnLoad, true);

    // Take care of common initialization
    commonInitCalendar();

    // Add an unload function to the window so we don't leak any listeners
    window.addEventListener("unload", ltnFinish, false);

    // Set up invitations manager
    scheduleInvitationsUpdate(FIRST_DELAY_STARTUP);
    getCalendarManager().addObserver(gInvitationsCalendarManagerObserver);

    let filter = document.getElementById("task-tree-filtergroup");
    filter.value = filter.value || "all";
    document.getElementById("modeBroadcaster").setAttribute("mode", gCurrentMode);

    // Lightning does not always collapse the imip-bar
    cal.getObserverService().addObserver(calImipBarCollapseObserver,
                                         "MsgClearNotifications", false);
}

/* Called at midnight to tell us to redraw date-specific widgets.  Do NOT call
 * this for normal refresh, since it also calls scheduleMidnightRefresh.
 */
function refreshUIBits() {
    try {
        getMinimonth().refreshDisplay();

        // refresh the current view, if it has ever been shown
        var cView = currentView();
        if (cView.initialized) {
            cView.goToDay(cView.selectedDay);
        }

        if (!TodayPane.showsToday()) {
            TodayPane.setDay(now());
        }

        // update the unifinder
        refreshEventTree();
    } catch (exc) {
        ASSERT(false, exc);
    }

    // schedule our next update...
    scheduleMidnightUpdate(refreshUIBits);
}

/**
 * Select the calendar view in the background, not switching to calendar mode if
 * in mail mode.
 */
function ltnSelectCalendarView(type) {
    gLastShownCalendarView = type;

    // Sunbird/Lightning Common view switching code
    switchToView(type);

}

/**
 * Show the calendar view, also switching to calendar mode if in mail mode
 */
function ltnShowCalendarView(type)
{
    gLastShownCalendarView = type;

    if (gCurrentMode != 'calendar') {
        // This function in turn calls showCalendarView(), so return afterwards.
        ltnSwitch2Calendar();
        return;
    }

    ltnSelectCalendarView(type);
    document.commandDispatcher.updateCommands('calendar_view_commands');
}

function ltnFinish() {
    getCalendarManager().removeObserver(gInvitationsCalendarManagerObserver);
    // Common finish steps
    commonFinishCalendar();
    
    cal.getObserverService().removeObserver(calImipBarCollapseObserver,
                                            "MsgClearNotifications");
}

// == invitations link
const FIRST_DELAY_STARTUP = 100;
const FIRST_DELAY_RESCHEDULE = 100;
const FIRST_DELAY_REGISTER = 10000;
const FIRST_DELAY_UNREGISTER = 0;

var gInvitationsOperationListener = {
    mCount: 0,

    onOperationComplete: function sBOL_onOperationComplete(aCalendar,
                                                           aStatus,
                                                           aOperationType,
                                                           aId,
                                                           aDetail) {
        let invitationsBox = document.getElementById("calendar-invitations-panel");
        if (Components.isSuccessCode(aStatus)) {
            let value = ltnGetString("lightning", "invitationsLink.label", [this.mCount]);
            document.getElementById("calendar-invitations-label").value = value;
            setElementValue(invitationsBox, this.mCount < 1 && "true", "hidden");
        } else {
            invitationsBox.setAttribute("hidden", "true");
        }
        this.mCount = 0;
    },

    onGetResult: function sBOL_onGetResult(aCalendar,
                                           aStatus,
                                           aItemType,
                                           aDetail,
                                           aCount,
                                           aItems) {
        if (Components.isSuccessCode(aStatus)) {
            this.mCount += aCount;
        }
    }
};

var gInvitationsCalendarManagerObserver = {
    mSideBar: this,

    onCalendarRegistered: function cMO_onCalendarRegistered(aCalendar) {
        this.mSideBar.rescheduleInvitationsUpdate(FIRST_DELAY_REGISTER);
    },

    onCalendarUnregistering: function cMO_onCalendarUnregistering(aCalendar) {
        this.mSideBar.rescheduleInvitationsUpdate(FIRST_DELAY_UNREGISTER);
    },

    onCalendarDeleting: function cMO_onCalendarDeleting(aCalendar) {
    }
};

function scheduleInvitationsUpdate(firstDelay) {
    gInvitationsCalendarManagerObserver.mCount = 0;
    getInvitationsManager().scheduleInvitationsUpdate(firstDelay,
                                                      gInvitationsOperationListener);
}

function rescheduleInvitationsUpdate(firstDelay) {
    getInvitationsManager().cancelInvitationsUpdate();
    scheduleInvitationsUpdate(firstDelay);
}

function openInvitationsDialog() {
    getInvitationsManager().cancelInvitationsUpdate();
    gInvitationsCalendarManagerObserver.mCount = 0;
    getInvitationsManager().openInvitationsDialog(
        gInvitationsOperationListener,
        function oiD_callback() {
            scheduleInvitationsUpdate(FIRST_DELAY_RESCHEDULE);
        });
}

/**
 * the current mode is set to a string defining the current
 * mode we're in. allowed values are:
 *  - 'mode'
 *  - 'mail'
 *  - 'calendar'
 *  - 'task'
 */
var gCurrentMode = 'mail';

/**
 * ltnSwitch2Mail() switches to the mail mode
 */

function ltnSwitch2Mail() {
  if (gCurrentMode == 'mail')
    return;

  gCurrentMode = 'mail';
  document.getElementById("modeBroadcaster").setAttribute("mode", gCurrentMode);
}

/**
 * ltnSwitch2Calendar() switches to the calendar mode
 */

function ltnSwitch2Calendar() {
  if (gCurrentMode == 'calendar')
    return;

  gCurrentMode = 'calendar';
  document.getElementById("modeBroadcaster").setAttribute("mode", gCurrentMode);
}

/**
 * ltnSwitch2Task() switches to the task mode
 */

function ltnSwitch2Task() {
  if (gCurrentMode == 'task')
    return;

  gCurrentMode = 'task';
  document.getElementById("modeBroadcaster").setAttribute("mode", gCurrentMode);

}

