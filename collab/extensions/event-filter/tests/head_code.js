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
 * The Initial Developer of the Original Code is Synovel Software.
 * Portions created by the Initial Developer are Copyright (C) 2007
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Ashok <ashok@synovel.com>
 *   Sri Hari Prasad <hari@synovel.com>
 *  Sivakrishna Edpuganti <sivakrishna@synovel.com>
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

const USEC_PER_MSEC = 1000;

function check_patterns ()
{
    var obj = Components.classes["@synovel.com/collab/calendar/event-filter;1"].
              getService(Components.interfaces.csIEventFilter);
    
    // Use tempTestPatterns for debugging a particular case
    //testPatterns = tempTestPatterns;
    
    for (var i = 0; i < testPatterns.length; i+=3) {
    
        var testResult = true;
        var contextDate = new Date (testPatterns[i+1]);
        obj.contextDate = contextDate * USEC_PER_MSEC;
        obj.nowDate = contextDate * USEC_PER_MSEC;
        var matches;
        var timezone = 0;
        if ((matches = (/GMT(.*)/).exec (testPatterns[i+1]))) {
            var value = parseInt (matches[1], 10);
            if (!isNaN (value)) {
                if (Math.abs (value) >= 100) {
                    timezone = Math.round (Math.abs (value) / 100) * 60 +
                               (Math.abs (value) - Math.round (Math.abs (value) / 100) * 100)
                    if (value < 0)
                        timezone = -timezone;
                }
            }
        }
        obj.contextTimezone = -timezone; // Set the current time zone to UTC

        var matchedEvents = obj.extractEvents(testPatterns[i], null, {});
        
        if (matchedEvents.length != testPatterns[i+2].length)
            testResult = false;
        else {
            for (var j = 0;  j < matchedEvents.length; j++) {
                if (matchedEvents[j].startDate.isValid == false)
                    testResult = false;
                if (matchedEvents[j].startDate != testPatterns[i+2][j][0])
                    testResult = false;
                if (matchedEvents[j].title != testPatterns[i+2][j][1])
                    testResult = false;
                }
        }

        if (testResult == false) {
            dump ("===> Testcase failed, pattern: " + testPatterns[i] + "\n");
            dump ("Test output: \n");
            for (j = 0; j < matchedEvents.length; j++) {
                    dump (j + ") Time = " + matchedEvents[j].startDate + " Event = " + matchedEvents[j].title + "\n");
                }
                dump ("Test expectation: \n");
            for (j = 0; j < testPatterns[i+2].length; j++) {
                    dump (j + ") Time = " + testPatterns[i+2][j][0] + " Event = " + testPatterns[i+2][j][1] + "\n");
            }
            return false;
        }
    }

    return true;
}
