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
# Portions created by the Initial Developer are Copyright (C) 2008
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Ashok Gudibandla <ashok@synovel.com> (Original Author)
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

window.addEventListener("paneload", loadAppList, false);

var gApplicationListLoaded = false;

function loadAppList(aEvent)
{
  if (gApplicationListLoaded || aEvent.target.id != "paneGeneral")
    return;

  /* Mail home screen setting is disabled */
  var startPageGroup = aEvent.target.getElementsByTagName("groupbox")[1];
  startPageGroup.setAttribute("collapsed", "true");

  var list = document.getElementById("application-list");
  var catman = Components.classes["@mozilla.org/categorymanager;1"]
                         .getService(Components.interfaces.nsICategoryManager);
  var catEnum = catman.enumerateCategory("installed-applications");

  while (catEnum.hasMoreElements()) {
    var entry = catEnum.getNext()
                  .QueryInterface(Components.interfaces.nsISupportsCString);
    var appCID = catman.getCategoryEntry("installed-applications", entry);
    var appInfo = Components.classes[appCID]
                            .getService(Components.interfaces.csIAppInfo);
    var checkBox = document.createElement("checkbox");

    checkBox.setAttribute("label", appInfo.getDisplayName());
    checkBox.setAttribute("appname", appInfo.name);
    checkBox.setAttribute("oncommand", "updateEnabledApplications(event)");
    checkBox.appInfo = appInfo; // Attach appInfo to this item for use latter.
    if (appInfo.enabled)
      checkBox.setAttribute("checked", "true");
    if (appInfo.name == "mailnews")
      checkBox.setAttribute("disabled", "true");
    list.appendChild(checkBox);
  }

  gApplicationListLoaded = true;
}

function enableApplicationCheckbox(aApplicationName, aEnable)
{
  var list = document.getElementById("application-list");

  var applicationItem = list.getElementsByAttribute("appname",
                                                    aApplicationName)[0];
  applicationItem.checked = aEnable;
}

function updateEnabledApplications(aEvent)
{
  var target = aEvent.target;
  var dirService = Components.classes["@mozilla.org/file/directory_service;1"]
                             .getService(Components.interfaces.nsIProperties);
  var profileAppManifest = dirService.get("ProfD", Components.interfaces.nsIFile);
  profileAppManifest.append("applications.manifest");

  // Check for inter dependencies between applications first
  // and enable/disable the corresponding applications.
  var list = document.getElementById("application-list");
  if(target.checked)
    // enable the base apps for the currently enabled one
    for each (var reqApp in target.appInfo.getRequiredApps({}))
      enableApplicationCheckbox(reqApp, true);
  else {
    // application disabled. Disable all dependant apps
    var disabledApp = target.appInfo.name;
    for(var i = 0; i < list.childNodes.length; i++) {
      var appInfo = list.childNodes[i].appInfo;
      if (!appInfo)
        continue;

      var reqiredApps = appInfo.getRequiredApps({});
      if (reqiredApps.indexOf(disabledApp) != -1)
        // a required app for appInfo was disabled. So, disable this.
        enableApplicationCheckbox(appInfo.name, false);
    }
  }

  // Calculate the list of overalays to add
  var overlaysToAdd = [];
  for (var i = 0; i < list.childNodes.length; i++) {
    var checkBox = list.childNodes[i];
    if(!checkBox.checked || !checkBox.appInfo)
      continue;

    var overlays = checkBox.appInfo.getOverlays({}); // Array of csIOverlayInfo
    for each (var overlay in overlays) 
      overlaysToAdd.push(overlay);
  }

  // Sort on priority basis
  overlaysToAdd = overlaysToAdd.sort(
                    function(item1, item2) {
                      return item1.priority - item2.priority;
                    });

  // Now update the manifest file.
  var foStream = Components
                   .classes["@mozilla.org/network/file-output-stream;1"]
                   .createInstance(Components.interfaces.nsIFileOutputStream);
  const PR_WRONLY = 0x02;
  const PR_CREATE_FILE = 0x08;
  const PR_TRUNCATE = 0x20;
  foStream.init(profileAppManifest, PR_TRUNCATE | PR_CREATE_FILE | PR_WRONLY, -1, 0); 
  var src = "";
  for each (var overlay in overlaysToAdd)
    src = src + "overlay " + overlay.target + " " + overlay.overlay + "\n";
  foStream.write(src, src.length);
  foStream.close();
}
