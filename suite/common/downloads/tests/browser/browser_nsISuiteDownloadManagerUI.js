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
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Mozilla Corporation.
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Shawn Wilsher <me@shawnwilsher.com> (Original Author)
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

function test_visibility_open()
{
  var dmui = Components.classes["@mozilla.org/download-manager-ui;1"]
                       .getService(Components.interfaces.nsIDownloadManagerUI);
  is(dmui.visible, true,
     "nsIDownloadManagerUI indicates that the UI is visible");
}

function test_visibility_closed(aWin)
{
  var dmui = Components.classes["@mozilla.org/download-manager-ui;1"]
                       .getService(Components.interfaces.nsIDownloadManagerUI);

  function dmWindowClosedListener() {
    aWin.removeEventListener("unload", dmWindowClosedListener, false);
    is(dmui.visible, false,
       "nsIDownloadManagerUI indicates that the UI is not visible");
    finish();
  }
  aWin.addEventListener("unload", dmWindowClosedListener, false);
  aWin.close();
}

var testFuncs = [
    test_visibility_open
  , test_visibility_closed /* all tests after this *must* expect there to be
                              no open window, otherwise they will fail! */
];

function test()
{
  var dm = Components.classes["@mozilla.org/download-manager;1"]
                     .getService(Components.interfaces.nsIDownloadManager);
  var db = dm.DBConnection;

  // First, we populate the database with some fake data
  db.executeSimpleSQL("DELETE FROM moz_downloads");

  // See if the DM is already open, and if it is, close it!
  var wm = Components.classes["@mozilla.org/appshell/window-mediator;1"]
                     .getService(Components.interfaces.nsIWindowMediator);
  var win = wm.getMostRecentWindow("Download:Manager");
  if (win)
    win.close();

  // OK, now that all the data is in, let's pull up the UI
  Components.classes["@mozilla.org/download-manager-ui;1"]
            .getService(Components.interfaces.nsISuiteDownloadManagerUI).showManager();

  let obs = Components.classes["@mozilla.org/observer-service;1"]
                      .getService(Components.interfaces.nsIObserverService);
  const DLMGR_UI_DONE = "download-manager-ui-done";

  let testObs = {
    observe: function(aSubject, aTopic, aData) {
      obs.removeObserver(testObs, DLMGR_UI_DONE);
      var win = wm.getMostRecentWindow("Download:Manager");

      // Now we can run our tests
      for each (var t in testFuncs)
        t(win);

      // finish will be called by the last test that also hides the DM UI
    }
  };

  waitForExplicitFinish();
  obs.addObserver(testObs, DLMGR_UI_DONE, false);
}
