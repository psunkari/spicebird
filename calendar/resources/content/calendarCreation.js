/* -*- Mode: javascript; tab-width: 20; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * ***** BEGIN LICENSE BLOCK *****
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
 * The Original Code is Calendar Code.
 *
 * The Initial Developer of the Original Code is
 * Michiel van Leeuwen <mvl@exedo.nl>.
 * Portions created by the Initial Developer are Copyright (C) 2005
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Gary van der Merwe <garyvdm@gmail.com>
 *   Philipp Kewisch <mozilla@kewis.ch>
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

var gCalendar;

function initLocationPage()
{
    checkRequired();
}

function initCustomizePage() {
    initNameFromURI();
    checkRequired();

    var suppressAlarmsRow = document.getElementById("customize-suppressAlarms-row");
    suppressAlarmsRow.hidden =
        (gCalendar && gCalendar.getProperty("capabilities.alarms.popup.supported") === false);
}

function checkRequired() {
    var canAdvance = true;
    var curPage = document.getElementById('calendar-wizard').currentPage;
    if (curPage) {
        var eList = curPage.getElementsByAttribute('required', 'true');
        for (var i = 0; i < eList.length && canAdvance; ++i) {
            canAdvance = (eList[i].value != "");
        }
        if (canAdvance && document.getElementById("calendar-uri").value &&
            curPage.pageid == "locationPage") {
            canAdvance = checkURL();
        }
        document.getElementById('calendar-wizard').canAdvance = canAdvance;
    }
}

function onInitialAdvance() {
    var type = document.getElementById('calendar-type').selectedItem.value;
    var page = document.getElementsByAttribute('pageid', 'initialPage')[0];
    if (type == 'local') {
        prepareCreateCalendar();
        page.next = 'customizePage';
    } else {
        page.next = 'locationPage';
    }
}

/**
 * Create the calendar, so that the customize page can already check for
 * calendar capabilities of the provider.
 */
function prepareCreateCalendar() {
    gCalendar = null;
    var provider;
    var uri;
    var type = document.getElementById('calendar-type').selectedItem.value;
    if (type == 'local') {
        provider = 'storage';
        uri = 'moz-profile-calendar://?id=2';
    } else {
        uri = document.getElementById("calendar-uri").value;
        provider = document.getElementById('calendar-format').selectedItem.value;
    }

    var calManager = getCalendarManager();
    var cals = calManager.getCalendars({});
    do {
        var already = cals.filter(function (c) { return c.uri.spec == uri; })
        if (already.length) {
            if (type != 'local') {
                // signalError("Already have calendar at this URI.");
                Components.utils.reportError("Already have calendar with URI " + uri);
                return false;
            }
            uri = uri.replace(/id=(\d+)/,
                              function (s, id) { return "id=" + (Number(id) + 1); });
        }
    } while (already.length);

    try {
        gCalendar = calManager.createCalendar(provider, makeURL(uri));
    } catch (ex) {
        dump(ex);
        return false;
    }

    return true;
}

/**
 * The actual process of registering the created calendar.
 */
function doCreateCalendar() {
    var cal_name = document.getElementById("calendar-name").value;
    var cal_color = document.getElementById('calendar-color').color;
    var calManager = getCalendarManager();

    gCalendar.name = cal_name;
    gCalendar.setProperty('color', cal_color);

    if (!document.getElementById("fire-alarms").checked) {
        gCalendar.setProperty('suppressAlarms', true);
    }

    calManager.registerCalendar(gCalendar);
    return true;
}

function initNameFromURI() {
    var path = document.getElementById("calendar-uri").value;
    var nameField = document.getElementById("calendar-name");
    if (!path || nameField.value)
        return;

    var fullPathRegex = new RegExp("([^/:]+)[.]ics$");
    var captures = path.match(fullPathRegex);
    if (captures && captures.length >= 1) {
        nameField.value = decodeURIComponent(captures[1]);
    }
}

//Don't let the wizard advance if the URL isn't valid, since the calendar
//creation will fail.
function checkURL() {
    try {
        makeURL(document.getElementById("calendar-uri").value);
    }
    catch (ex) {
        return false;
    }
    return true;
}

function setCanRewindFalse() {
   document.getElementById('calendar-wizard').canRewind = false;
}
