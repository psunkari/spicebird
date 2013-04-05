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
#   Siva Edpuganti <sivakrishna@synovel.com> (Original Author)
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

function GetProtocolListCB(aManager, aProtocol)
{
  this.mManager = aManager;
  this.mProtocol = aProtocol;
  this.mSupportsProtocol = false;
}

GetProtocolListCB.prototype = {
  onAddItem: function(aStringItem)
  {
    if (aStringItem == this.mProtocol)
      this.mSupportsProtocol = true;
  },

  onError: function(aErrorStr)
  {
    dump("ERROR: protocol list CB - " + aErrorStr);
  }
};

function getProtocolManagers(aProtocol, aCallback)
{
  var mPendingList = [];
  var mProtocolManagers = [];

  for each (var manager in gTPManagers) {
    var protocolListCB = new GetProtocolListCB(manager.name, aProtocol);
    protocolListCB.onItemsComplete = function()
    {
      if (this.mSupportsProtocol)
        mProtocolManagers.push(this.mManager);

      var index = mPendingList.indexOf(this.mManager);
      if (index == -1)
        return;
     
      mPendingList.splice(index, 1);

      if (mPendingList.length == 0)
        aCallback(mProtocolManagers);
    }

    mPendingList.push(manager.name);
    manager.getProtocolList(protocolListCB);
  }
}

function createIMAccount(aParams)
{
  if (!aParams.account || !aParams.manager || !aParams.protocol) {
    dump('ERROR: Missing account/manager/protocol info. Cannot create IM account\n');
    return;
  }

  var prefService = Components.classes["@mozilla.org/preferences-service;1"]
                              .getService(Components.interfaces.nsIPrefService);
  var prefBranch = prefService.getBranch("collab.im.accounts.");

  // Get the next available key
  var prefKey;
  try {     
    for (prefKey = 0; prefKey < 10000; prefKey++) { 
      prefBranch.getCharPref(prefKey.toString() + ".account");    
    }         
  } catch (ex) { };

  for (var param in aParams) {
    switch (aParams[param].type) {
      case 'char':
        prefBranch.setCharPref(prefKey + '.' + param, aParams[param].value);
        break;
      case 'int':
        prefBranch.setIntPref(prefKey + '.' + param, aParams[param].value);
        break;
      case 'bool':
        prefBranch.setBoolPref(prefKey + '.' + param, aParams[param].value);
        break; 
    }
  }

  prefService.savePrefFile(null);

  var observerService = Components.classes["@mozilla.org/observer-service;1"]
                                  .getService(Components.interfaces.nsIObserverService);
  observerService.notifyObservers(null, "csIMAccountCreated", prefKey);
}
