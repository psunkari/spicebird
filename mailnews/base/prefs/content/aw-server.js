/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Alec Flett <alecf@netscape.com>
 *   Seth Spitzer <sspitzer@netscape.com>
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

var gPrefsBundle;
var gOnMailServersPage;
var gOnNewsServerPage;
var gHideIncoming;
var gProtocolInfo = null;

function hostnameIsIllegal(hostname)
{
  // XXX TODO do a complete check.
  // this only checks for illegal characters in the hostname
  // but hostnames like "...." and "_" and ".111" will get by
  // my test.  
  hostname = trim(hostname);
  return !hostname || /[^A-Za-z0-9.-]/.test(hostname);
}

function serverPageValidate() 
{
  // If this is for a server that doesn't require a username, check if the
  // account exists. For other types, we check after the user provides the
  // username (see aw-login.js).
  var canAdvance = true;

  if (gOnMailServersPage) {
    var incomingServerName = document.getElementById("incomingServer").value;
    var smtpserver = document.getElementById("smtphostname").value;

    var usingDefaultSMTP = document.getElementById("noSmtp").hidden;
    if ((!gHideIncoming && hostnameIsIllegal(incomingServerName)) ||
        (!usingDefaultSMTP && hostnameIsIllegal(smtpserver)))
      canAdvance = false;
  }
  if (gOnNewsServerPage) {
    var newsServerName = document.getElementById("newsServer").value;
    if (hostnameIsIllegal(newsServerName))
      canAdvance = false;
  }
  if (canAdvance && gProtocolInfo && !gProtocolInfo.requiresUsername) {
    var pageData = parent.GetPageData();
    var serverType = parent.getCurrentServerType(pageData);
    var hostName;
    if (gOnMailServersPage)
      hostName = incomingServerName;
    else if (gOnNewsServerPage)
      hostName = newsServerName;

    if (parent.AccountExists(null, hostName, serverType))
      canAdvance = false;
  }

  document.documentElement.canAdvance = canAdvance;
}

function serverPageUnload()
{
  var pageData = parent.GetPageData();

  if (gOnMailServersPage) {
    // If we have hidden the incoming server dialogs, we don't want
    // to set the server to an empty value here
    if (!gHideIncoming) {
      var incomingServerName = document.getElementById("incomingServer");
      setPageData(pageData, "server", "hostname", trim(incomingServerName.value));
    }
    var smtpserver = document.getElementById("smtphostname");
    setPageData(pageData, "server", "smtphostname", trim(smtpserver.value));
  }
  else if (gOnNewsServerPage) {
    var newsServerName = document.getElementById("newsServer");
    setPageData(pageData, "newsserver", "hostname", trim(newsServerName.value));
  }

  return true;
}

function serverPageInit() {
  gOnMailServersPage = (document.documentElement.currentPage.id == "serverpage");
  gOnNewsServerPage = (document.documentElement.currentPage.id == "newsserver");
  if (gOnNewsServerPage)
  {
    var newsServer = document.getElementById("newsServer");
    var pageData = parent.GetPageData();
    try 
    {
      newsServer.value = pageData.newsserver.hostname.value;
    }
    catch (ex){}
  }
    
  gHideIncoming = false;
  if (gCurrentAccountData && gCurrentAccountData.wizardHideIncoming)
    gHideIncoming = true;
  
  var incomingServerbox = document.getElementById("incomingServerbox");
  var serverTypeBox = document.getElementById("serverTypeBox");
  if (incomingServerbox && serverTypeBox) {
    if (gHideIncoming) {
      incomingServerbox.setAttribute("hidden", "true");
      serverTypeBox.setAttribute("hidden", "true");
    }
    else {
      incomingServerbox.removeAttribute("hidden");
      serverTypeBox.removeAttribute("hidden");
    }
  }
  
  // Server type selection (pop3 or imap) is for mail accounts only
  var pageData = parent.GetPageData();
  var isMailAccount = pageData.accounttype.mailaccount.value;
  var isOtherAccount = pageData.accounttype.otheraccount.value;
  if (isMailAccount && !gHideIncoming) {
    var serverTypeRadioGroup = document.getElementById("servertype");
    /* 
     * Check to see if the radiogroup has any value. If there is no
     * value, this must be the first time user visting this page in the
     * account setup process. So, the default is set to pop3. If there 
     * is a value (it's used automatically), user has already visited 
     * page and server type selection is done. Once user visits the page, 
     * the server type value from then on will persist (whether the selection 
     * came from the default or the user action).
     */
    if (!serverTypeRadioGroup.value) {
      /*
       * if server type was set to imap in isp data, then
       * we preset the server type radio group accordingly,
       * otherwise, use pop3 as the default.
       */
      var serverTypeRadioItem = document.getElementById(pageData.server &&
           pageData.server.servertype && pageData.server.servertype.value == "imap" ?
               "imap" : "pop3");
      serverTypeRadioGroup.selectedItem = serverTypeRadioItem;      // Set pop3 server type as default selection
    }
    setServerType();
    setDeferStorage(); // set the initial value correctly
  }
  else if (isOtherAccount) {
    document.getElementById("incomingServerSeparator").hidden = true;
    document.getElementById("deferStorageBox").hidden = true;
  }

  gPrefsBundle = document.getElementById("bundle_prefs");
  var smtpServer = null;
  var smtpCreateNewServer = gCurrentAccountData && gCurrentAccountData.smtpCreateNewServer;

  // Don't use the default smtp server if smtp server creation was explicitly
  // requested in isp rdf.
  // If we're reusing the default smtp we should not set the smtp hostname.
  if (parent.smtpService.defaultServer && !smtpCreateNewServer) {
    smtpServer = parent.smtpService.defaultServer;
    reusingDefaultSmtp = true;
    setPageData(pageData, "identity", "smtpServerKey", "");
  }

  var noSmtpBox = document.getElementById("noSmtp");
  var haveSmtpBox = document.getElementById("haveSmtp");

  var boxToHide;
  var boxToShow;

  if (pageData.server && pageData.server.hostname) {
    var incomingServerTextBox = document.getElementById("incomingServer");
    if (incomingServerTextBox && incomingServerTextBox.value == "")
      incomingServerTextBox.value = pageData.server.hostname.value;
  }

  if (pageData.server && pageData.server.smtphostname && smtpCreateNewServer) {
    var smtpTextBox = document.getElementById("smtphostname");
    if (smtpTextBox && smtpTextBox.value == "")
      smtpTextBox.value = pageData.server.smtphostname.value;
  }

  if (smtpServer && smtpServer.hostname) {
    // we have a hostname, so modify and show the static text and 
    // store the value of the default smtp server in the textbox.
    modifyStaticText(smtpServer.hostname, "1")
    boxToShow = haveSmtpBox;
    boxToHide = noSmtpBox;
  }
  else {
    // no default hostname yet
    boxToShow = noSmtpBox;
    boxToHide = haveSmtpBox;
  }

  if (boxToHide)
    boxToHide.setAttribute("hidden", "true");

  if (boxToShow)
    boxToShow.removeAttribute("hidden");

  var type = parent.getCurrentServerType(pageData);
  gProtocolInfo = Components.classes["@mozilla.org/messenger/protocol/info;1?type=" + type]
                            .getService(Components.interfaces.nsIMsgProtocolInfo);
  serverPageValidate();
}

function modifyStaticText(smtpMod, smtpBox)
{
  // modify the value in the smtp display if we already have a 
  // smtp server so that the single string displays the hostname
  // or username for the smtp server.
  var smtpStatic = document.getElementById("smtpStaticText"+smtpBox);
  if (smtpStatic && smtpStatic.hasChildNodes())
    smtpStatic.childNodes[0].nodeValue = smtpStatic.getAttribute("prefix") +
                                         smtpMod + smtpStatic.getAttribute("suffix");  
}
 
function setServerType()
{
  var pageData = parent.GetPageData();
  var serverType = document.getElementById("servertype").value;
  var deferStorageBox = document.getElementById("deferStorageBox");
  deferStorageBox.hidden = serverType == "imap";
  document.getElementById("incomingServerSeparator").hidden = false;
  setPageData(pageData, "server", "servertype", serverType);
}

function setDeferStorage()
{
  var pageData = parent.GetPageData();
  var deferStorage = (document.getElementById("deferStorage")).checked;
  setPageData(pageData, "server", "deferStorage", deferStorage);
}


