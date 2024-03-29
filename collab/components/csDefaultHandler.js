/* -*- indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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
 * The Original Code is the Mozilla Firefox browser.
 *
 * The Initial Developer of the Original Code is
 * Benjamin Smedberg <benjamin@smedbergs.us>
 *
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *    Prasad Sunkari <prasad@synovel.com>
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

Components.utils.import("resource://gre/modules/XPCOMUtils.jsm");

const nsISupports              = Components.interfaces.nsISupports;

const nsICommandLine           = Components.interfaces.nsICommandLine;
const nsICommandLineHandler    = Components.interfaces.nsICommandLineHandler;
const nsICommandLineValidator  = Components.interfaces.nsICommandLineValidator;
const nsIDOMWindowInternal     = Components.interfaces.nsIDOMWindowInternal;
const nsIFactory               = Components.interfaces.nsIFactory;
const nsIFileURL               = Components.interfaces.nsIFileURL;
const nsINetUtil               = Components.interfaces.nsINetUtil;
const nsISupportsString        = Components.interfaces.nsISupportsString;
const nsIURIFixup              = Components.interfaces.nsIURIFixup;
const nsIURILoader             = Components.interfaces.nsIURILoader;
const nsIWindowMediator        = Components.interfaces.nsIWindowMediator;
const nsIWindowWatcher         = Components.interfaces.nsIWindowWatcher;

const NS_ERROR_ABORT = Components.results.NS_ERROR_ABORT;

const URI_INHERITS_SECURITY_CONTEXT = Components.interfaces.nsIProtocolHandler
                                        .URI_INHERITS_SECURITY_CONTEXT;

function resolveURIInternal(aCmdLine, aArgument) {
  var uri = aCmdLine.resolveURI(aArgument);

  if (!(uri instanceof nsIFileURL)) {
    return uri;
  }

  try {
    if (uri.file.exists())
      return uri;
  }
  catch (e) {
    Components.utils.reportError(e);
  }

  // We have interpreted the argument as a relative file URI, but the file
  // doesn't exist. Try URI fixup heuristics: see bug 290782.

  try {
    var urifixup = Components.classes["@mozilla.org/docshell/urifixup;1"]
                             .getService(nsIURIFixup);

    uri = urifixup.createFixupURI(aArgument, 0);
  }
  catch (e) {
    Components.utils.reportError(e);
  }

  return uri;
}

function handleIndexerResult(aFile) {
  // Do this here because xpcshell isn't too happy with this at startup
  Components.utils.import("resource://app/modules/MailUtils.js");
  // Make sure the folder tree is initialized
  MailUtils.discoverFolders();

  // Use the search integration module to convert the indexer result into a
  // message header
  Components.utils.import("resource://app/modules/SearchIntegration.js");
  let msgHdr = SearchIntegration.handleResult(aFile);

  // If we found a message header, open it, otherwise throw an exception
  if (msgHdr)
    MailUtils.displayMessage(msgHdr);
  else
    throw Components.results.NS_ERROR_FAILURE;
}

function mayOpenURI(uri)
{
  var ext = Components.classes["@mozilla.org/uriloader/external-protocol-service;1"]
    .getService(Components.interfaces.nsIExternalProtocolService);

  return ext.isExposedProtocol(uri.scheme);
}

function openURI(uri)
{
  if (!mayOpenURI(uri))
    throw Components.results.NS_ERROR_FAILURE;

  var io = Components.classes["@mozilla.org/network/io-service;1"]
                     .getService(Components.interfaces.nsIIOService);
  var channel = io.newChannelFromURI(uri);
  var loader = Components.classes["@mozilla.org/uriloader;1"]
                         .getService(Components.interfaces.nsIURILoader);

  // We cannot load a URI on startup asynchronously without protecting
  // the startup

  var loadgroup = Components.classes["@mozilla.org/network/load-group;1"]
                            .createInstance(Components.interfaces.nsILoadGroup);

  var appstartup = Components.classes["@mozilla.org/toolkit/app-startup;1"]
                             .getService(Components.interfaces.nsIAppStartup);

  var loadlistener = {
    onStartRequest: function ll_start(aRequest, aContext) {
      appstartup.enterLastWindowClosingSurvivalArea();
    },

    onStopRequest: function ll_stop(aRequest, aContext, aStatusCode) {
      appstartup.exitLastWindowClosingSurvivalArea();
    },

    QueryInterface: XPCOMUtils.generateQI([Components.interfaces.nsIRequestObserver,
                                           Components.interfaces.nsISupportsWeakReference])
  };

  loadgroup.groupObserver = loadlistener;

  var listener = {
    onStartURIOpen: function(uri) { return false; },
    doContent: function(ctype, preferred, request, handler) { return false; },
    isPreferred: function(ctype, desired) { return false; },
    canHandleContent: function(ctype, preferred, desired) { return false; },
    loadCookie: null,
    parentContentListener: null,
    getInterface: function(iid) {
      if (iid.equals(Components.interfaces.nsIURIContentListener))
        return this;

      if (iid.equals(Components.interfaces.nsILoadGroup))
        return loadgroup;

      throw Components.results.NS_ERROR_NO_INTERFACE;
    }
  };
  loader.openURI(channel, true, listener);
}

var csDefaultHandler = {
  QueryInterface: XPCOMUtils.generateQI([nsICommandLineHandler,
                                         nsICommandLineValidator,
                                         nsIFactory]),

  /* nsICommandLineHandler */

  handle : function csDefaultHandler_handle(cmdLine) {
    var uri;

    try {
      var remoteCommand = cmdLine.handleFlagWithParam("remote", true);
    }
    catch (e) {
      throw NS_ERROR_ABORT;
    }

    if (remoteCommand != null) {
      try {
        var a = /^\s*(\w+)\(([^\)]*)\)\s*$/.exec(remoteCommand);
        var remoteVerb = a[1].toLowerCase();
        var remoteParams = a[2].split(",");

        switch (remoteVerb) {
        case "openurl":
          var xuri = cmdLine.resolveURI(remoteParams[0]);
          openURI(xuri);
          break;

        case "mailto":
          var xuri = cmdLine.resolveURI("mailto:" + remoteParams[0]);
          openURI(xuri);
          break;

        case "xfedocommand":
          // xfeDoCommand(openBrowser)
          switch (remoteParams[0].toLowerCase()) {
          case "openinbox":
            var wm = Components.classes["@mozilla.org/appshell/window-mediator;1"]
                               .getService(nsIWindowMediator);
            var win = wm.getMostRecentWindow("collab:main");
            if (win) {
              win.focus();
            }
            else {
              var wwatch = Components.classes["@mozilla.org/embedcomp/window-watcher;1"]
                                     .getService(nsIWindowWatcher);

              // Bug 277798 - we have to pass an argument to openWindow(), or
              // else it won't honor the dialog=no instruction.
              var argstring = Components.classes["@mozilla.org/supports-string;1"]
                                        .createInstance(nsISupportsString);
              wwatch.openWindow(null, "chrome://collab/content/", "_blank",
                                "chrome,dialog=no,all", argstring);
            }
            break;

          case "composemessage":
            var wwatch = Components.classes["@mozilla.org/embedcomp/window-watcher;1"]
                                   .getService(nsIWindowWatcher);
            var argstring = Components.classes["@mozilla.org/supports-string;1"]
                                      .createInstance(nsISupportsString);
            remoteParams.shift();
            argstring.data = remoteParams.join(",");
            wwatch.openWindow(null, "chrome://messenger/content/messengercompose/messengercompose.xul", "_blank",
                              "chrome,dialog=no,all", argstring);
            break;

          default:
            throw Components.results.NS_ERROR_ABORT;
          }
          break;

        default:
          // Somebody sent us a remote command we don't know how to process:
          // just abort.
          throw Components.results.NS_ERROR_ABORT;
        }

        cmdLine.preventDefault = true;
      }
      catch (e) {
        // If we had a -remote flag but failed to process it, throw
        // NS_ERROR_ABORT so that the xremote code knows to return a failure
        // back to the handling code.
        dump(e);
        throw Components.results.NS_ERROR_ABORT;
      }
    }

    var chromeParam = cmdLine.handleFlagWithParam("chrome", false);
    if (chromeParam) {
      try {
        var features = "chrome,dialog=no,all";
        var wwatch = Components.classes["@mozilla.org/embedcomp/window-watcher;1"]
                               .getService(nsIWindowWatcher);
        var argstring = Components.classes["@mozilla.org/supports-string;1"]
                                  .createInstance(nsISupportsString);
        var uri = resolveURIInternal(cmdLine, chromeParam);
        var netutil = Components.classes["@mozilla.org/network/util;1"]
                                .getService(nsINetUtil);
        // only load URIs which do not inherit chrome privs
        if (!netutil.URIChainHasFlags(uri, URI_INHERITS_SECURITY_CONTEXT)) {
          wwatch.openWindow(null, uri.spec, "_blank",
                            "chrome,dialog=no,all", argstring);
          cmdLine.preventDefault = true;
        }
      }
      catch (e) {
        dump(e);
      }
    }

    var splashEnabled = false;
    if (!cmdLine.handleFlag("no-splash", false)) {
      var prefSvc = Components.classes["@mozilla.org/preferences-service;1"]
                              .getService(Components.interfaces.nsIPrefBranch2);
      try {
        splashEnabled = splashEnabled & prefSvc.getBoolPref("collab.splash.enabled");
      } catch (ex) {
        prefSvc.setBoolPref("collab.splash.enabled", true);
      }
      splashEnabled = true;
    }

    if (cmdLine.handleFlag("silent", false)) {
      cmdLine.preventDefault = true;
    }

    if (cmdLine.handleFlag("options", false)) {
      // Open the options window
      var wwatch = Components.classes["@mozilla.org/embedcomp/window-watcher;1"]
                             .getService(nsIWindowWatcher);
      wwatch.openWindow(null,
          "chrome://messenger/content/preferences/preferences.xul", "_blank",
          "chrome,dialog=no,all", null);
    }

    // The URI might be passed as the argument to the file parameter
    uri = cmdLine.handleFlagWithParam("file", false);

    var count = cmdLine.length;
    if (count) {
      var i = 0;
      while (i < count) {
        var curarg = cmdLine.getArgument(i);
        if (!curarg.match(/^-/))
          break;

        dump ("Warning: unrecognized command line flag " + curarg + "\n");
        // To emulate the pre-nsICommandLine behavior, we ignore the
        // argument after an unrecognized flag.
        i += 2;
        // xxxbsmedberg: make me use the console service!
      }

      if (i < count) {
        uri = cmdLine.getArgument(i);

        // mailto: URIs are frequently passed with spaces in them. They should be
        // escaped into %20, but we hack around bad clients, see bug 231032
        if (uri.match(/^mailto:/)) {
          while (++i < count) {
            var testarg = cmdLine.getArgument(i);
            if (testarg.match(/^-/))
              break;

            uri += " " + testarg;
          }
        }
      }
    }

    if (!uri && cmdLine.preventDefault)
      return;

    if (!uri && cmdLine.state != nsICommandLine.STATE_INITIAL_LAUNCH) {
      try {
        var wmed = Components.classes["@mozilla.org/appshell/window-mediator;1"]
                             .getService(nsIWindowMediator);

        var wlist = wmed.getEnumerator("collab:main");
        if (wlist.hasMoreElements()) {
          var window = wlist.getNext().QueryInterface(nsIDOMWindowInternal);
          window.focus();
          return;
        }
      }
      catch (e) {
        dump(e);
      }
    }

    if (uri) {
      if (/^feed:/i.test(uri)) {
        try {
          Components.classes["@mozilla.org/newsblog-feed-downloader;1"]
                    .getService(Components.interfaces.nsINewsBlogFeedDownloader)
                    .subscribeToFeed(uri, null, null);
        }
        catch (e) {
          // If feed handling is not installed, do nothing
        }
      }
      else if (/\.mozeml$/i.test(uri) || /\.wdseml$/i.test(uri)) {
        handleIndexerResult(cmdLine.resolveFile(uri));
        cmdLine.preventDefault = true;
      }
      else if (/\.eml$/i.test(uri)) {
        // Open this eml in a new message window
        let file = cmdLine.resolveFile(uri);
        // No point in trying to open a file if it doesn't exist or is empty
        if (file.exists() && file.fileSize > 0) {
          // Get the URL for this file
          let ios = Components.classes["@mozilla.org/network/io-service;1"]
                              .getService(Components.interfaces.nsIIOService);
          let fileURL = ios.newFileURI(file)
                           .QueryInterface(Components.interfaces.nsIFileURL);
          fileURL.query = "?type=application/x-message-display";

          let wwatch = Components.classes["@mozilla.org/embedcomp/window-watcher;1"]
                                 .getService(nsIWindowWatcher);
          wwatch.openWindow(null,
                            "chrome://messenger/content/messageWindow.xul",
                            "_blank", "all,chrome,dialog=no,status,toolbar",
                            fileURL);
          cmdLine.preventDefault = true;
        }
        else {
          let bundle = Components.classes["@mozilla.org/intl/stringbundle;1"]
                                 .getService(Components.interfaces.nsIStringBundleService)
                                 .createBundle("chrome://messenger/locale/messenger.properties");
          let title, message;
          if (!file.exists()) {
            title = bundle.GetStringFromName("fileNotFoundTitle");
            message = bundle.formatStringFromName("fileNotFoundMsg", [file.path], 1);
          }
          else {
            // The file is empty
            title = bundle.GetStringFromName("fileEmptyTitle");
            message = bundle.formatStringFromName("fileEmptyMsg", [file.path], 1);
          }

          let promptService = Components.classes["@mozilla.org/embedcomp/prompt-service;1"]
                                        .getService(Components.interfaces.nsIPromptService);
          promptService.alert(null, title, message);
        }
      }
      else {
        openURI(cmdLine.resolveURI(uri));
        // XXX: add error-handling here! (error dialog, if nothing else)
      }
    } else {
      var launchURL = "chrome://collab/content/";
      var windowParams = "chrome,dialog=no,all";
      if(splashEnabled) {
        launchURL = "chrome://collab/content/splash.xul";
        windowParams = "chrome,centerscreen,alwaysRaised=yes,titlebar=no,popup=yes";
      }

      var wwatch = Components.classes["@mozilla.org/embedcomp/window-watcher;1"]
                             .getService(nsIWindowWatcher);

      var argstring = Components.classes["@mozilla.org/supports-string;1"]
                                .createInstance(nsISupportsString);

      wwatch.openWindow(null, launchURL, "_blank", windowParams, argstring);
    }
  },

  /* nsICommandLineValidator */
  validate : function csDefaultHandler_validate(cmdLine) {
    var osintFlagIdx = cmdLine.findFlag("osint", false);
    if (osintFlagIdx == -1)
      return;

    // Other handlers may use osint so only handle the osint flag if the mail
    // or compose flag is also present and the command line is valid.
    var mailFlagIdx = cmdLine.findFlag("mail", false);
    var composeFlagIdx = cmdLine.findFlag("compose", false);
    if (mailFlagIdx == -1 && composeFlagIdx == -1)
      return;

    // If both flags are present use the first flag found so the command line
    // length test will fail.
    if (mailFlagIdx > -1 && composeFlagIdx > -1)
      var actionFlagIdx = mailFlagIdx > composeFlagIdx ? composeFlagIdx : mailFlagIdx;
    else
      actionFlagIdx = mailFlagIdx > -1 ? mailFlagIdx : composeFlagIdx;

    if (actionFlagIdx && (osintFlagIdx > -1)) {
      var param = cmdLine.getArgument(actionFlagIdx + 1);
      if (cmdLine.length != actionFlagIdx + 2 ||
          /Spicebird.(MAILTO|NEWS):/.test(param))
        throw NS_ERROR_ABORT;
      cmdLine.handleFlag("osint", false)
    }
  },

  helpInfo : "  -options             Open the options dialog.\n" +
             "  -file                Open the specified email file.\n" +
             "  -no-splash           Disable the splash screen.\n",

  /* nsIFactory */

  createInstance : function csDefaultHandler_CI(outer, iid) {
    if (outer != null)
      throw Components.results.NS_ERROR_NO_AGGREGATION;

    return this.QueryInterface(iid);
  },

  lockFactory : function csDefaultHandler_lock(lock) {
    /* no-op */
  }
};

function csDefaultCommandLineHandler() {}

csDefaultCommandLineHandler.prototype = {
  classDescription: "Collab default commandline handler",
  classID: Components.ID("{93244c58-0b15-4de1-b45b-f219a8dc3a40}"),
  contractID: "@synovel.com/collab/default-clh;1",

  QueryInterface: XPCOMUtils.generateQI([Components.interfaces.nsIModule]),

  _xpcom_categories:
    [ { category: "command-line-handler",
        entry: "x-default" },
      { category: "command-line-validator",
        entry: "b-default" } ],

  _xpcom_factory: csDefaultHandler
}

// NSGetModule: Return the nsIModule object.
function NSGetModule(compMgr, fileSpec) {
  return XPCOMUtils.generateModule([csDefaultCommandLineHandler]);
}
