/* -*- Mode: Java; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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
 * The Original Code is Mozilla Communicator client code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Alec Flett <alecf@netscape.com>
 *   Henrik Gemal <mozilla@gemal.dk>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
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

// be real hacky with document.getElementById until document.controls works
// with the new XUL widgets

var gSmtpUsername;
var gSmtpDescription;
var gSmtpUsernameLabel;
var gSmtpHostname;
var gSmtpPort;
var gSmtpUseSecAuth;
var gSmtpUseUsername;
var gSmtpAuthMethod;
var gSmtpTrySSL;
var gSmtpPrefBranch;
var gPrefBranch = Components.classes["@mozilla.org/preferences-service;1"].getService(Components.interfaces.nsIPrefBranch);
var gSmtpService = Components.classes["@mozilla.org/messengercompose/smtp;1"].getService(Components.interfaces.nsISmtpService);
var gSavedUsername = "";
var gPort;
var gDefaultPort;

function initSmtpSettings(server) {
    gSmtpUsername = document.getElementById("smtp.username");
    gSmtpDescription = document.getElementById("smtp.description");
    gSmtpUsernameLabel = document.getElementById("smtp.username.label");
    gSmtpHostname = document.getElementById("smtp.hostname");
    gSmtpPort = document.getElementById("smtp.port");
    gSmtpUseUsername = document.getElementById("smtp.useUsername");
    gSmtpAuthMethod = document.getElementById("smtp.authMethod");
    gSmtpTrySSL = document.getElementById("smtp.trySSL");
    gSmtpUseSecAuth = document.getElementById("smtp.useSecAuth");
    gDefaultPort = document.getElementById("smtp.defaultPort");
    gPort = document.getElementById("smtp.port");

    if (server) {
        gSmtpHostname.value = server.hostname;
        gSmtpDescription.value = server.description;
        gSmtpPort.value = server.port ? server.port : "";
        gSmtpUsername.value = server.username;
        gSmtpAuthMethod.setAttribute("value", server.authMethod);
        gSmtpTrySSL.value = (server.trySSL < 4) ? server.trySSL : 1;
        gSmtpUseSecAuth.checked = server.useSecAuth == "1";
    } else {
        const PREF_AUTH_ANY = 1; // From nsSmtpProtocol.h
        gSmtpAuthMethod.setAttribute("value", PREF_AUTH_ANY);
        const PREF_SECURE_NEVER = 0; // From nsSmtpProtocol.h
        gSmtpTrySSL.value = PREF_SECURE_NEVER;
    }

    gSmtpUseUsername.checked = (gSmtpAuthMethod.getAttribute("value") == "1");

    //dump("gSmtpAuthMethod = <" + gSmtpAuthMethod.localName + ">\n");
    //dump("gSmtpAuthMethod.value = " + gSmtpAuthMethod.getAttribute("value") + "\n");

    onUseUsername(gSmtpUseUsername, false);
    selectProtocol(false);
    if (gSmtpService.defaultServer)
      onLockPreference();

    //"STARTTLS, if available" is vulnerable to MITM attacks so we shouldn't
    // allow users to choose it anymore. Hide the option unless the user already
    // has it set.
    const PREF_SECURE_TRY_STARTTLS = 1; // From nsSmtpProtocol.h
    var hidden = (document.getElementById("smtp.trySSL").value != PREF_SECURE_TRY_STARTTLS);
    document.getElementById("connectionSecurityType-1").hidden = hidden;
}

// Disables xul elements that have associated preferences locked.
function onLockPreference()
{
    var defaultSmtpServerKey = gPrefBranch.getCharPref("mail.smtp.defaultserver");
    var finalPrefString = "mail.smtpserver." + defaultSmtpServerKey + "."; 

    var prefService = Components.classes["@mozilla.org/preferences-service;1"].getService(Components.interfaces.nsIPrefService);

    var allPrefElements = {
      hostname:     gSmtpHostname,
      description:  gSmtpDescription,
      port:         gSmtpPort,
      use_username: gSmtpUseUsername,
      try_ssl:      gSmtpTrySSL
    };

    gSmtpPrefBranch = prefService.getBranch(finalPrefString);
    disableIfLocked( allPrefElements );
} 

// Does the work of disabling an element given the array which contains xul id/prefstring pairs.
// Also saves the id/locked state in an array so that other areas of the code can avoid
// stomping on the disabled state indiscriminately.
function disableIfLocked( prefstrArray )
{
  for (var prefstring in prefstrArray)
    if (gSmtpPrefBranch.prefIsLocked(prefstring))
      prefstrArray[prefstring].disabled = true;
}

function saveSmtpSettings(server)
{
    gSmtpAuthMethod.setAttribute("value", gSmtpUseUsername.checked ? "1" : "0");

    //dump("Saving to " + server + "\n");
    if (server) {
        server.hostname = gSmtpHostname.value;
        server.description = gSmtpDescription.value;
        server.port = gSmtpPort.value;
        server.authMethod = (gSmtpUseUsername.checked ? 1 : 0);
        //dump("Saved authmethod = " + server.authMethod +
        //     " but checked = " + gSmtpUseUsername.checked + "\n");
        server.username = gSmtpUsername.value;
        server.trySSL = gSmtpTrySSL.value;
        server.useSecAuth = gSmtpUseSecAuth.checked;
    }
}

function onUseUsername(checkbox, dofocus)
{
    if (checkbox.checked) {
        // not only do we enable the elements when the check box is checked,
        // but we also make sure that it's not disabled (ie locked) as well.
        if (!checkbox.disabled) {
            gSmtpUsername.removeAttribute("disabled");
            gSmtpUsernameLabel.removeAttribute("disabled");
            gSmtpUseSecAuth.removeAttribute("disabled");
        }
        if (dofocus)
            gSmtpUsername.focus();
        if (gSavedUsername && gSavedUsername != "")
            gSmtpUsername.value = gSavedUsername;
    } else {
        gSavedUsername = gSmtpUsername.value;
        gSmtpUsername.value = "";
        gSmtpUsername.setAttribute("disabled", "true");
        gSmtpUsernameLabel.setAttribute("disabled", "true");
        gSmtpUseSecAuth.setAttribute("disabled", "true");
    }
}

/**
 * Resets the default port to SMTP or SMTPS, dependending on |gSmtpTrySSL| value,
 * and sets the port to use to this default, if that's appropriate.
 *
 * @param userAction false for dialog initialization,
 *                   true for user action.
 */
function selectProtocol(userAction) {
  const DEFAULT_SMTP_PORT = "25";
  const DEFAULT_SMTPS_PORT = "465";

  var otherDefaultPort;
  var prevDefaultPort = gDefaultPort.value;

  if (gSmtpTrySSL.value == 3) {
    gDefaultPort.value = DEFAULT_SMTPS_PORT;
    otherDefaultPort = DEFAULT_SMTP_PORT;
  } else {
    gDefaultPort.value = DEFAULT_SMTP_PORT;
    otherDefaultPort = DEFAULT_SMTPS_PORT;
  }

  // If the port is not set,
  // or the user is causing the default port to change,
  //   and the port is set to the default for the other protocol,
  // then set the port to the default for the new protocol.
  if ((gPort.value == "") ||
      (userAction && (gDefaultPort.value != prevDefaultPort) &&
       (gPort.value == otherDefaultPort)))
    gPort.value = gDefaultPort.value;
}
