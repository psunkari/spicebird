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

var gCollabChatPrefs = {

  init: function()
  {
    this.updateChatStatus();
    this.readSoundLocation();
    this.updatePlaySound();
  },

  updateChatStatus: function()
  {
    var autologin = document.getElementById("im-autologin-checkbox").checked;
    document.getElementById("im-autologin-label").disabled = !autologin;
    document.getElementById("im-autologin-status-menulist").disabled = !autologin;
  },

  readSoundLocation: function()
  {
    var loc = document.getElementById("im-sound-url-location");
    loc.value = document.getElementById("im-sound-url").value;
    if (loc.value)
    {
      loc.label = this.convertURLToLocalFile(loc.value).leafName;
      loc.image = "moz-icon://" + loc.label + "?size=16";
    }
    return undefined;
  },

  convertURLToLocalFile: function(aFileURL)
  {
    // convert the file url into a nsILocalFile
    if (aFileURL)
    {
      var ios = Components.classes["@mozilla.org/network/io-service;1"]
                          .getService(Components.interfaces.nsIIOService);
      var fph = ios.getProtocolHandler("file")
                   .QueryInterface(Components.interfaces
                                             .nsIFileProtocolHandler);
      return fph.getFileFromURLSpec(aFileURL);
    } else
      return null;
  },

  previewSound: function ()
  {  
    var sound = Components.classes["@mozilla.org/sound;1"]
                          .createInstance(Components.interfaces.nsISound);
    
    var soundLocation;
    soundLocation = document.getElementById('im-sound-type-group').value == 1 ? 
                    document.getElementById('im-sound-url-location').value :
                    "_moz_mailbeep"

    if (soundLocation.indexOf("file://") == -1) 
      sound.playSystemSound(soundLocation);
    else 
    {
      try {
        var ioService = Components.classes["@mozilla.org/network/io-service;1"]
                                  .getService(Components.interfaces.nsIIOService);
        sound.play(ioService.newURI(soundLocation, null, null));
      } catch (ex) {}
    }
  },
  
  browseForSoundFile: function ()
  {
    const nsIFilePicker = Components.interfaces.nsIFilePicker;
    var fp = Components.classes["@mozilla.org/filepicker;1"]
                       .createInstance(nsIFilePicker);

    // if we already have a sound file, then use the path for that sound file
    // as the initial path in the dialog.
    var field = document.getElementById("im-sound-url-location");
    var localFile = this.convertURLToLocalFile(field.value);
    if (localFile)
      fp.displayDirectory = localFile.parent;

    // XXX todo, persist the last sound directory and pass it in
    fp.init(window, field.getAttribute("pickerTitle"), nsIFilePicker.modeOpen);
    fp.appendFilter("*.wav", "*.wav");

    var ret = fp.show();
    if (ret == nsIFilePicker.returnOK) {
      // convert the nsILocalFile into a nsIFile url 
      document.getElementById("im-sound-url").value = fp.fileURL.spec;
      this.readSoundLocation(); // XXX We shouldn't have to be doing this by hand
      this.updatePlaySound();
    }
  },
  
  updatePlaySound: function()
  {
    var soundsDisabled = !document.getElementById('im-sound-checkbox').checked;
    var soundTypeEl = document.getElementById('im-sound-type-group');

    soundTypeEl.disabled = soundsDisabled;
    document.getElementById('im-sound-browse')
            .disabled = soundsDisabled || soundTypeEl.value != 1;
    document.getElementById('im-sound-preview')
            .disabled = soundsDisabled || soundTypeEl.value != 1; 
    document.getElementById("im-sound-newconv-checkbox")
            .disabled = soundsDisabled;
  }
}
