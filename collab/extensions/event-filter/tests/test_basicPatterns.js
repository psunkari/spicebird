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

var testPatterns = new Array (
//
// Date Patterns
//

// All numeric dates
"31/12",                "September 08, 2007 21:45:39 GMT",              [ ["2007/12/31 00:00:00 UTC", ""] ],
"31.12",                "September 08, 2007 21:45:39 GMT",              [ ["2007/12/31 00:00:00 UTC", ""] ],
"31-12",                "September 08, 2007 21:45:39 GMT",              [ ["2007/12/31 00:00:00 UTC", ""] ],
"31/12/40",             "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31-12-40",             "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31/12/2040",           "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31.12.2040",           "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31-12-2040",           "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31/Dec/2040",          "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31.Dec.2039",          "September 08, 2007 21:45:39 GMT",              [ ["2039/12/31 00:00:00 UTC", ""] ],
"31-Dec-2039",          "September 08, 2007 21:45:39 GMT",              [ ["2039/12/31 00:00:00 UTC", ""] ],
"31/12/2040",           "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"2040-12-31",           "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],

// Alpha numeric dates
"31 December, 2040",    "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31 December 2040",     "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"December 31, 2040",    "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"December 31 2040",     "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31 December, 40",      "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"December 31, 40",      "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31st Dec",             "September 08, 2007 21:45:39 GMT",              [ ["2007/12/31 00:00:00 UTC", ""] ],
"31 Dec",               "September 08, 2007 21:45:39 GMT",              [ ["2007/12/31 00:00:00 UTC", ""] ],
"31 Dec,2040",          "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31 Dec, 2040",         "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"dec 31",               "September 08, 2007 21:45:39 GMT",              [ ["2007/12/31 00:00:00 UTC", ""] ],
"dec 31st",             "September 08, 2007 21:45:39 GMT",              [ ["2007/12/31 00:00:00 UTC", ""] ],
"dec 31,40",            "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"dec 31,2040",          "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"dec 31, 2040",         "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],

// Dates preceded by week days
"Wednesday, 31st December, 2040", "September 08, 2007 21:45:39 GMT",    [ ["2040/12/31 00:00:00 UTC", ""] ],
"Sunday, December 31st, 2040", "September 08, 2007 21:45:39 GMT",       [ ["2040/12/31 00:00:00 UTC", ""] ],
"Wed, 31st December, 2040", "September 08, 2007 21:45:39 GMT",          [ ["2040/12/31 00:00:00 UTC", ""] ],
"Sun, December 31st, 2040", "September 08, 2007 21:45:39 GMT",          [ ["2040/12/31 00:00:00 UTC", ""] ],
"Wed 31st December, 2040", "September 08, 2007 21:45:39 GMT",           [ ["2040/12/31 00:00:00 UTC", ""] ],
"Sun December 31st, 2040", "September 08, 2007 21:45:39 GMT",           [ ["2040/12/31 00:00:00 UTC", ""] ],

// Numbers followed by st, nd etc.
"31st December, 2040",  "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31st December 2040",   "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"1st December, 2040",   "September 08, 2007 21:45:39 GMT",              [ ["2040/12/01 00:00:00 UTC", ""] ],
"2nd December, 2040",   "September 08, 2007 21:45:39 GMT",              [ ["2040/12/02 00:00:00 UTC", ""] ],
"3rd December, 2040",   "September 08, 2007 21:45:39 GMT",              [ ["2040/12/03 00:00:00 UTC", ""] ],
"4th December, 2040",   "September 08, 2007 21:45:39 GMT",              [ ["2040/12/04 00:00:00 UTC", ""] ],
"21st December, 2040",  "September 08, 2007 21:45:39 GMT",              [ ["2040/12/21 00:00:00 UTC", ""] ],
"22nd December, 2040",  "September 08, 2007 21:45:39 GMT",              [ ["2040/12/22 00:00:00 UTC", ""] ],
"23rd December, 2040",  "September 08, 2007 21:45:39 GMT",              [ ["2040/12/23 00:00:00 UTC", ""] ],
"24th December, 2040",  "September 08, 2007 21:45:39 GMT",              [ ["2040/12/24 00:00:00 UTC", ""] ],
"December 31st, 2040",  "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"December 31st 2040",   "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],

// Dates with out spaces
"1December2040",        "September 08, 2007 21:45:39 GMT",              [ ["2040/12/01 00:00:00 UTC", ""] ],
"01December2040",       "September 08, 2007 21:45:39 GMT",              [ ["2040/12/01 00:00:00 UTC", ""] ],
"31December2040",       "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31December40",         "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31Dec2040",            "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31Dec40",              "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31 Dec08",             "September 08, 2007 21:45:39 GMT",              [ ["2008/12/31 00:00:00 UTC", ""] ],
"31 Dec2008",           "September 08, 2007 21:45:39 GMT",              [ ["2008/12/31 00:00:00 UTC", ""] ],

// Testing separators
"(31st December 2040)", "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"[31st December 2040]", "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"{31st December 2040}", "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31st December 2040.",  "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
" 31st December 2040 ", "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"-31st December 2040-", "September 08, 2007 21:45:39 GMT",              [ ],
"a31st December 2007a", "September 08, 2007 21:45:39 GMT",              [ ],
"31st December 20099",  "September 08, 2007 21:45:39 GMT",              [ ["2007/12/31 00:00:00 UTC", ""] ],

// Some date patterns that should not be matched
"31/13/2040",           "September 08, 2007 21:45:39 GMT",              [ ],
"31/13/40",             "September 08, 2007 21:45:39 GMT",              [ ],
"31/13",                "September 08, 2007 21:45:39 GMT",              [ ],
"99/99/99",             "September 08, 2007 21:45:39 GMT",              [ ],
"06-12-31",             "September 08, 2007 21:45:39 GMT",              [ ["2031/12/06 00:00:00 UTC", ""] ],

// 
// Time patterns
//

"0930 Hrs",             "September 08, 2007 08:45:39 GMT",              [ ["2007/09/08 09:30:00 UTC", ""] ],
"930 Hrs",              "September 08, 2007 08:45:39 GMT",              [ ["2007/09/08 09:30:00 UTC", ""] ],
"09:30 Hrs",            "September 08, 2007 08:45:39 GMT",              [ ["2007/09/08 09:30:00 UTC", ""] ],
"0930 Hours",           "September 08, 2007 08:45:39 GMT",              [ ["2007/09/08 09:30:00 UTC", ""] ],
"09:30 Hours",          "September 08, 2007 08:45:39 GMT",              [ ["2007/09/08 09:30:00 UTC", ""] ],
"9 AM",                 "September 08, 2007 08:45:39 GMT",              [ ["2007/09/08 09:00:00 UTC", ""] ],
"9AM",                  "September 08, 2007 08:45:39 GMT",              [ ["2007/09/08 09:00:00 UTC", ""] ],
"1030 AM",              "September 08, 2007 09:45:39 GMT",              [ ["2007/09/08 10:30:00 UTC", ""] ],
"1030 PM",              "September 08, 2007 09:45:39 GMT",              [ ["2007/09/08 22:30:00 UTC", ""] ],
"10:30AM",              "September 08, 2007 09:45:39 GMT",              [ ["2007/09/08 10:30:00 UTC", ""] ],
"10:30PM",              "September 08, 2007 09:45:39 GMT",              [ ["2007/09/08 22:30:00 UTC", ""] ],
"10:30 AM",             "September 08, 2007 09:45:39 GMT",              [ ["2007/09/08 10:30:00 UTC", ""] ],
"10:30 PM",             "September 08, 2007 09:45:39 GMT",              [ ["2007/09/08 22:30:00 UTC", ""] ],
"10:60",                "September 08, 2007 09:45:39 GMT",              [ ],
"10:30",                "September 08, 2007 09:45:39 GMT",              [ ["2007/09/08 10:30:00 UTC", ""] ],
"10:30:45",             "September 08, 2007 09:45:39 GMT",              [ ["2007/09/08 10:30:45 UTC", ""] ],
//"1030 Evening",         "September 08, 2007 09:45:39 GMT",              [ ["2007/09/08 22:30:00 UTC", ""] ], // FIXME: more patterns
//"1030 Morning",         "September 08, 2007 09:45:39 GMT",              [ ["2007/09/08 10:30:00 UTC", ""] ],
//"1030 Night",           "September 08, 2007 09:45:39 GMT",              [ ["2007/09/08 22:30:00 UTC", ""] ],
//"1030 Afternoon",       "September 08, 2007 09:45:39 GMT",              [ ["2007/09/08 22:30:00 UTC", ""] ],

// Testing o' clock
"9 o'Clock",            "September 08, 2007 08:45:39 GMT",              [ ["2007/09/08 09:00:00 UTC", ""] ],
"9 oclock",             "September 08, 2007 08:45:39 GMT",              [ ["2007/09/08 09:00:00 UTC", ""] ],
"9 o clock",            "September 08, 2007 08:45:39 GMT",              [ ["2007/09/08 09:00:00 UTC", ""] ],

// Time patterns that should not be matched
"+0530 IST",            "September 08, 2007 21:45:39 GMT",              [ ],
"-800 PST",             "September 08, 2007 21:45:39 GMT",              [ ],
"-08:00 PST",           "September 08, 2007 21:45:39 GMT",              [ ],
"Indian Standard Time", "September 08, 2007 21:45:39 GMT",              [ ],
"GMT+8",                "September 08, 2007 21:45:39 UTC",              [ ],
"GMT-830",              "September 08, 2007 21:45:39 UTC",              [ ],
"GMT+0530",             "September 08, 2007 21:45:39 UTC",              [ ],

// Relative date patterns
"on 20th",              "September 08, 2007 21:45:39 GMT",              [ ], // FIXME:
"today",                "September 08, 2007 21:45:39 GMT",              [ ["2007/09/08 00:00:00 UTC", ""] ],
"tomorrow 1",           "September 08, 2007 21:45:39 GMT",              [ ["2007/09/09 00:00:00 UTC", ""] ],
"tomorrow 2",           "September 30, 2007 21:45:39 GMT",              [ ["2007/10/01 00:00:00 UTC", ""] ],
"tomorrow 3",           "October 31, 2007 21:45:39 GMT",                [ ["2007/11/01 00:00:00 UTC", ""] ],
"tomorrow 4",           "October 30, 2007 21:45:39 GMT",                [ ["2007/10/31 00:00:00 UTC", ""] ],
"tomorrow 5",           "October 30, 2007 21:45:39 GMT",                [ ["2007/10/31 00:00:00 UTC", ""] ],
"day after tomorrow",   "October 30, 2007 21:45:39 GMT",                [ ["2007/11/01 00:00:00 UTC", ""] ],
"day after tomorrow",   "September 30, 2007 21:45:39 GMT",              [ ["2007/10/02 00:00:00 UTC", ""] ],
"day after tomorrow",   "September 29, 2007 21:45:39 GMT",              [ ["2007/10/01 00:00:00 UTC", ""] ],

// Relative week patterns
"tuesday",              "September 08, 2007 21:45:39 GMT",              [ ["2007/09/11 00:00:00 UTC", ""] ],
"saturday",             "September 08, 2007 21:45:39 GMT",              [ ["2007/09/15 00:00:00 UTC", ""] ],
"friday",               "September 08, 2007 21:45:39 GMT",              [ ["2007/09/14 00:00:00 UTC", ""] ],
"monday",               "September 30, 2007 21:45:39 GMT",              [ ["2007/10/01 00:00:00 UTC", ""] ],
"sunday",               "September 30, 2007 21:45:39 GMT",              [ ["2007/10/07 00:00:00 UTC", ""] ],

// Testing Timezones 
//"10:30 +0530 IST",      "September 08, 2007 21:45:39 GMT",              [ ["", ""] ],
//"10:30 -800 PST",       "September 08, 2007 21:45:39 GMT",              [ ["", ""] ],
//"10:30 -08:00 PST",     "September 08, 2007 21:45:39 GMT",              [ ["", ""] ],
//"10:30 Indian Standard Time", "September 08, 2007 21:45:39 GMT",        [ ["", ""] ],
"20:30 GMT+8",          "September 08, 2007 09:45:39 UTC",              [ ["2007/09/08 12:30:00 UTC", ""] ],
"20:30 GMT-8",          "September 08, 2007 09:45:39 UTC",              [ ["2007/09/09 04:30:00 UTC", ""] ],
"10:30 GMT-830",        "September 08, 2007 10:45:39 UTC",              [ ["2007/09/08 19:00:00 UTC", ""] ],
"10:30 GMT+0530",       "September 08, 2007 02:45:39 UTC",              [ ["2007/09/08 05:00:00 UTC", ""] ],
"10:30 (GMT+8)",        "September 08, 2007 01:45:39 UTC",              [ ["2007/09/08 02:30:00 UTC", ""] ],
"10:30 (GMT-830)",      "September 08, 2007 10:45:39 UTC",              [ ["2007/09/08 19:00:00 UTC", ""] ],
"10:30 (GMT+0530)",     "September 08, 2007 02:45:39 UTC",              [ ["2007/09/08 05:00:00 UTC", ""] ],
"20:30 UTC+8",          "September 08, 2007 09:45:39 UTC",              [ ["2007/09/08 12:30:00 UTC", ""] ],
"10:30 UTC-830",        "September 08, 2007 10:45:39 UTC",              [ ["2007/09/08 19:00:00 UTC", ""] ],
"10:30 (UTC+0530)",     "September 08, 2007 02:45:39 UTC",              [ ["2007/09/08 05:00:00 UTC", ""] ],

"",                     "",                                             []
);

function run_test ()
{
    do_check_true (check_patterns ());
}
