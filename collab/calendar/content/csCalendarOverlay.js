/* -*- Mode: javascript; tab-width: 20; indent-tabs-mode: nil; c-basic-offset: 4 -*-*/
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
 * The Original Code is Spicebird Calendar Code
 *
 * The Initial Developer of the Original Code is Prasad Sunkari.
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s): Prasad Sunkari <prasad@synovel.com>
 *                 Ashok Gudibandla <ashok@synovel.com>
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

const gCalendarAppName = "calendar";
const gTasksAppName = "tasks";

function doQuickAdd() {
   window.openDialog("chrome://calendar/content/csQuickAddEvent.xul", "Quick Add",
                        "chrome, modal, resizable,centerscreen,dialog=yes", null);
}

/**
  * This controller holds all the commands that can be triggered from other
  * applications. 
  */
var calCommonCmdController = {
   commands : {
         "calendar_new_event_command" : true,
         "calendar_new_todo_command" : true,
         "calendar_new_calendar_command" : true,
   },

   supportsCommand: function (aCommand) {
      if (aCommand in this.commands) 
         return true;
      return false;
   },

   isCommandEnabled: function (aCommand) {
      if (aCommand in this.commands) 
         return true;
      return false;
   },

   doCommand: function (aCommand) {
      switch(aCommand) {
         case "calendar_new_event_command" : 
            createEventWithDialog(getSelectedCalendar());
            break;
         case "calendar_new_todo_command" : 
            createTodoWithDialog(getSelectedTasksCalendar());
            break;
         case "calendar_new_calendar_command" : 
            openCalendarWizard();
            break;
      }
      return false;
   },

   updateCommands: function () {
        for (var command in this.commands) {
            goUpdateCommand(command);
        }
   },


   onEvent: function (aEvent) {
   },
};

var calendarAppController = {
   commands : {
      "cmd_selectAll": true,
      "cmd_new": true,
      "cmd_newTask": true,
      "cmd-weeks-in-multiweek-view": true,
      "cmd-view-assisting-timezone": true
   },

   updateCommands: function () {
      for (var command in this.commands)
         goUpdateCommand(command);
   },

   supportsCommand : function (cmd) {
      if (cmd in this.commands)
         return true;
      return false;
   },

   isCommandEnabled : function (cmd) {
      switch(cmd) {
         case "cmd_selectAll":
         case "cmd_new":
         case "cmd_newTask":
            return true;
         case "cmd-weeks-in-multiweek-view":
            return getViewDeck().selectedPanel.id == "multiweek-view" &&
                    getViewDeck().getAttribute("collapsed") != "true";
         case "cmd-view-assisting-timezone":
            return (getViewDeck().selectedPanel.id == "day-view" ||
                    getViewDeck().selectedPanel.id == "week-view") &&
                    getViewDeck().getAttribute("collapsed") != "true";
         default :
            return false;
       }
    },

   doCommand : function (cmd) {
      switch(cmd) {
         case "cmd_selectAll":
            selectAllEvents();
            break;
         case "cmd_new":
            goDoCommand('calendar_new_event_command');
            break;
         case "cmd_newTask":
            goDoCommand('calendar_new_todo_command');
            break;
         default :
            return false;
       }
    }
}

function updateAssistTzPopup() {
   var timezonePopup = document.getElementById("assist-tz-list-popup");
   var view = document.getElementById('week-view');

   while(timezonePopup.lastChild)
      timezonePopup.removeChild(timezonePopup.lastChild);

   function createItem (label, value, group) {
      var item = document.createElement("menuitem");
      item.setAttribute('label',label);
      item.setAttribute('value',value);
      if (value == view.assistTimezone) 
         item.setAttribute("checked", "true");
      if (group) {
         item.setAttribute('name','tz-group');
         item.setAttribute('type','radio');
      }
      return item;
   }

   timezonePopup.appendChild(createItem("None", "--none--", true));

   // Get the list of timezones
   var TimezonesComp =  Components.classes["@synovel.com/collab/collab/timezones;1"]
                              .getService().QueryInterface(Components.interfaces.csITimezones);
   var defaultTzIds = TimezonesComp.getDefaultTimezoneIds({});
   for(var i=0;i<defaultTzIds.length;i++)
   {
      var names = defaultTzIds[i].split('/');
      var label = names[names.length - 1];
      timezonePopup.appendChild(createItem(label, defaultTzIds[i], true));
   }
   timezonePopup.appendChild(document.createElement("menuseparator"));
   // Add 'More..' option
   timezonePopup.appendChild(createItem("More...", "--more--", false));
}

function changeAssistTimezone(tzId) {
   var weekView = document.getElementById('week-view');
   var dayView = document.getElementById('day-view');
   
   if (tzId == "--more--") {
      openTimezoneSelectDialog();
      return;
   } else {
      weekView.assistTimezone = tzId;
      dayView.assistTimezone = tzId;
   }
}

function csTaskMinimonthPick(aCurDate)
{
  return;  // TODO
}

function csCalMinimonthDblClick(aCurDate)
{
  let calendar = getCompositeCalendar().defaultCalendar;
  let startDate = jsDateToDateTime(aCurDate, currentView().timezone);
  createEventWithDialog(calendar, startDate, null, null, null, false);
}

function csTaskMinimonthDblClick(aCurDate)
{
  let calendar = getTasksCompositeCalendar().defaultCalendar;
  let dueDate = jsDateToDateTime(aCurDate, currentView().timezone);
  createTodoWithDialog(calendar, dueDate, null, null, null);
}

function csToggleCompletedTasks()
{
    var showCommand = document.getElementById("show-completed-checkbox");
    var tasksTree = document.getElementById("calendar-task-tree");

    if (!showCommand)
        return;

    if (showCommand.hasAttribute("checked"))
        showCommand.removeAttribute("checked");
    else
        showCommand.setAttribute("checked", "true");

    if (tasksTree) {
        tasksTree.showCompleted = showCommand.hasAttribute("checked");
        tasksTree.refresh();
    }
}

function refreshTasksTree()
{
  let taskTree = document.getElementById("calendar-task-tree");
  taskTree.refresh();
}

function taskSearchbarKeyPress( searchTextItem, event )
{
    clearSearchTimer();

    if (event && event.keyCode == event.DOM_VK_RETURN) {
        filterTasksInTree(searchTextItem.value);
        return; 
    }
    else if (event && event.keyCode == event.DOM_VK_ESCAPE) {
      searchTextItem.value = "";
      clearSearchTimer();
      var taskTree = document.getElementById("calendar-task-tree");
      taskTree.refresh();
      return;
    }
    
    // make a new timer
    gSearchTimeout = setTimeout( function(){ filterTasksInTree(searchTextItem.value); }, 500 );
}

function filterTasksInTree(aText) {
  var regex = new RegExp (aText, "i");
  var taskTree = document.getElementById("calendar-task-tree");
  taskTree.search(regex);
}

function getTasksMinimonth () {
  return document.getElementById("taskminicalendar");
}

var tasksCmdController = {
   supportsCommand : function (cmd) {
      switch(cmd) {
         case "cmd_selectAll":
         case "cmd_delete":
         case "cmd_new":
            return true;
         default :
            return false;
       }
    },

   isCommandEnabled : function (cmd) {
      switch(cmd) {
         case "cmd_selectAll":
         case "cmd_delete":
            return calendarController.isCommandEnabled("calendar_delete_todo_command");
         case "cmd_new":
            return true;
         default :
            return false;
       }
    },

   doCommand : function (cmd) {
      switch(cmd) {
         case "cmd_selectAll":
            document.getElementById("calendar-task-tree").mTreeView.selection.selectAll();
            break;
         case "cmd_delete":
            calendarController.goDoCommand("calendar_delete_todo_command");
            break;
         case "cmd_new":
            goDoCommand('calendar_new_todo_command');
            break;
         default :
            return false;
       }
    }
}

function tasksInit() {
    var tabcollab = document.getElementById("tabcollab");
    if (tabcollab) {
        tabcollab.registerTabType(tasksTabType);
        tabcollab.openTab("tasks", {title: 'Tasks', background: true});
    }

    var controllers = document.getElementById("tabpanel-tasks").controllers;
    controllers.appendController(tasksCmdController);
    controllers.appendController(calendarController);

    var taskTree = document.getElementById("calendar-task-tree");
    var showCompleted = document.getElementById("show-completed-checkbox");
    if (taskTree && showCompleted)
        taskTree.showCompleted = showCompleted.hasAttribute("checked");

    getSelectedTasks = function(aEvent) {
        var taskTree = document.getElementById("calendar-task-tree");
        if (taskTree != null) {
            return taskTree.selectedTasks;
        } else {
            return [];
        }
    }
}

// Enable app status in appInfo component
var calendarAppInfoClass = Components.classes["@synovel.com/collab/calendar-appinfo;1"];
if (calendarAppInfoClass) {
    var calendarAppInfo = calendarAppInfoClass.getService(Components.interfaces.csIAppInfo);
    if (calendarAppInfo)
        calendarAppInfo.enabled = true;
}

function collabCalendarInit() {
    var tabcollab = document.getElementById("tabcollab");
    if (tabcollab) {
        tabcollab.registerTabType(calendarTabType);
        tabcollab.openTab("calendar", {background: true});
    }
   
    var controllers = document.getElementById("tabpanel-calendar").controllers;
    controllers.appendController(calendarAppController);
    controllers.appendController(calendarController);

    ltnOnLoad();

    addCommonController(calCommonCmdController);
    calCommonCmdController.updateCommands();
}

/*
 * Duplicate of method changeContextMenuForTask
 * used to update menubar popup for tasks.
 */
function changeMenuForTask(aEvent) {
    var tasks = getSelectedTasks(aEvent);
    var task = null;
    var tasksSelected = (tasks.length > 0);
    applyAttributeToMenuChildren(aEvent.target, "disabled", (!tasksSelected));
    document.getElementById("calendar_new_todo_command").removeAttribute("disabled");
    if (tasksSelected) {
        if (isPropertyValueSame(tasks, "isCompleted")) {
            setBooleanAttribute(document.getElementById("task-menu-markcompleted"), "checked", tasks[0].isCompleted);
        } else {
            document.getElementById("task-menu-markcompleted").setAttribute("checked", false);
        }
    }
}

function changeNumberOfWeeks(aMenuItem) {
    var mwView = document.getElementById("multiweek-view");
    mwView.weeksInView = aMenuItem.value;
}

addEventListener("load", collabCalendarInit, true);
addEventListener("load", tasksInit, true);
