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
# Portions created by the Initial Developer are Copyright (C) 2009
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Prasad Sunkari <prasad@synovel.com> (Original Author)
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

var Ci = Components.interfaces;
var Cc = Components.classes;

/*
 * Text channel handler.
 * This function is executed in the scope of csChatConnectionWrapper object
 */
var csChatTextChannelDisplays = {};
function csChatTextChannelHandler(channelDetails, startup) {
  // Ignore text channels that already exist
  if (startup)
    return;

  var properties = {};
  var propertiesEnumerator = channelDetails.properties.enumerate();
  while (propertiesEnumerator.hasMoreElements()) {
    var property = propertiesEnumerator.getNext()
                                       .QueryInterface(Ci.csITpQualifiedPropertyValueMap);
    properties[property.key] = property.value;
  }

  var targetHandleType = properties["org.freedesktop.Telepathy.Channel.TargetHandleType"];
  var targetHandle = properties["org.freedesktop.Telepathy.Channel.TargetHandle"];

  var channel = Components.classes["@synovel.com/collab/telepathy/channel/text;1"]
                          .createInstance(Ci.csITpChannelUtils);
  channel.init(this.connection.objectPath, channelDetails.channel,
               "org.freedesktop.Telepathy.Channel.ChannelType.Text",
               targetHandleType, targetHandle);

  var key = this.objPath + ":" + targetHandleType + ":" + targetHandle;
  var channelReadyCB = {
    onChannelReady: function() {
      if (!csChatTextChannelDisplays[key]) {
        var win = window.openDialog("chrome://chat/content/csTextChatWindow.xul", "",
                                    "chrome,resizable,dialog=no", csChatWrapper, channel);
        csChatTextChannelDisplays[key] = win;
       
        // Window is closed, remove reference from cache.
        win.addEventListener("close", function(event) {
                                        csChatTextChannelDisplays[key] = null;
                                        return true;
                                      }, false);
      } else {
        csChatTextChannelDisplays[key].reinit(channel);
      }
    }
  }
  channel.callWhenReady(channelReadyCB);
}

function csChatLoad()
{
  csChatAccountManager.init();
  csChatWrapper.init();

  try {
    if (csChatWrapper.prefBranch.getBoolPref("log.enabled"))
      csChatContactListTests.init();
  } catch (ex) {}

  // Register default ContactList handler.
  csChatWrapper.registerChannelHandler('ContactList', 
                function(channel) { this.contactListHandler(channel); });
  csChatWrapper.registerChannelHandler('Text', csChatTextChannelHandler);

  window.addEventListener("unload", csChatUnload, false);
}

function csChatNetworkOnline(event)
{
  if (event.target.tagName != "window")
    return;

  csChatWrapper.networkOnline();
}

function csChatNetworkOffline(event)
{
  if (event.target.tagName != "window")
    return;

  csChatWrapper.networkOffline();
}

function csChatUnload()
{
  csChatWrapper.destroy();
}

// Enable app status in appInfo component
var chatAppInfoClass = Components.classes["@synovel.com/collab/chat/appinfo;1"];
if (chatAppInfoClass) {
    var chatAppInfo = chatAppInfoClass.getService(Components.interfaces.csIAppInfo);
    if (chatAppInfo)
        chatAppInfo.enabled = true;
}

window.addEventListener("load", csChatLoad, false);
window.addEventListener("online", csChatNetworkOnline, false);
window.addEventListener("offline", csChatNetworkOffline, false);
