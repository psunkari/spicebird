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
// Sliding Window Century Detection Patterns
//

"31 December, 97",      "September 08, 2007 21:45:39 GMT",              [ ],
"31 December, 40",      "September 08, 2007 21:45:39 GMT",              [ ["2040/12/31 00:00:00 UTC", ""] ],
"31 December, 01",      "September 08, 2057 21:45:39 GMT",              [ ["2101/12/31 00:00:00 UTC", ""] ],

// Border cases
"31 December, 99",      "September 08, 2049 21:45:39 GMT",              [ ],
"31 December, 00",      "September 08, 2050 21:45:39 GMT",              [ ],
"31 December, 01",      "September 08, 2051 21:45:39 GMT",              [ ],
"31 December, 00",      "September 08, 2051 21:45:39 GMT",              [ ["2100/12/31 00:00:00 UTC", ""] ],

"",                     "",                                             []
);

function run_test ()
{
    do_check_true (check_patterns ());
}
