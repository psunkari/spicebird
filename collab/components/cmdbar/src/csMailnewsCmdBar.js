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
 *    Prasad Sunkari <prasad@synovel.com>
 *
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
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

const nsISupports              = Components.interfaces.nsISupports;
const nsIModule                = Components.interfaces.nsIModule;
const csICmdBarCommand         = Components.interfaces.csICmdBarCommand;
const csICmdBarParam           = Components.interfaces.csICmdBarParam;
const csICmdBarHandler         = Components.interfaces.csICmdBarHandler;

/**************************************************************
   Implementation of csICmdBarHandler and the |mail| command.
 **************************************************************/

const csMailnewsCmdBar_ContractID = "@synovel.com/collab/cmdbar/mailnews;1";
const csMailnewsCmdBar_CID = Components.ID("{3390f4d7-d275-42f7-a7dd-0c57f08699bd}");

function csMailnewsCmdBar() {
  this._params = Components.classes["@mozilla.org/array;1"]
                           .createInstance()
                           .QueryInterface(Components.interfaces.nsIMutableArray);
  this._cmdname = null;
  this._globals = null;
  this._commands = null;
  this._categoryMgr = Components.classes["@mozilla.org/categorymanager;1"]
                                .getService(Components.interfaces.nsICategoryManager);
}

csMailnewsCmdBar.prototype = {

  /* nsISupports */

  QueryInterface : function(aIID) {
    if (aIID.equals(csICmdBarHandler) ||
        aIID.equals(csICmdBarCommand) ||
        aIID.equals(nsISupports))
      return this;

    throw Components.results.NS_ERROR_NO_INTERFACE;
  },

  /* csICmdBarHandler */

  get commands() {
    if (!this._commands) {
      this._commands = Components.classes["@mozilla.org/array;1"]
                                 .createInstance()
                                 .QueryInterface(Components.interfaces.nsIMutableArray);

      var catEnum = this._categoryMgr.enumerateCategory("cmdbar-commands-mailnews");
      while (catEnum.hasMoreElements()) {
        var entry = catEnum.getNext()
                           .QueryInterface(Components.interfaces.nsISupportsCString);
        var cmdCID = this._categoryMgr.getCategoryEntry("cmdbar-commands-mailnews", entry);
        var command = Components.classes[cmdCID]
                                .getService(Components.interfaces.csICmdBarCommand);
        this._commands.appendElement(command, false);
      }

      var globalEnum = this.globalCommands.enumerate();
      while (globalEnum.hasMoreElements()) {
        var entry = globalEnum.getNext()
                              .QueryInterface(Components.interfaces.csICmdBarCommand);
        this._commands.appendElement(entry, false);
      }
    }

    return this._commands;
  },

  get globalCommands() {
    if (!this._globals) {
      this._globals = Components.classes["@mozilla.org/array;1"]
                                .createInstance()
                                .QueryInterface(Components.interfaces.nsIMutableArray);

      var catEnum = this._categoryMgr.enumerateCategory("cmdbar-commands-mailnews-global");
      while (catEnum.hasMoreElements()) {
        var entry = catEnum.getNext()
                            .QueryInterface(Components.interfaces.nsISupportsCString);
        var cmdCID = this._categoryMgr.getCategoryEntry("cmdbar-commands-mailnews-global", entry);
        var command = Components.classes[cmdCID]
                                .getService(Components.interfaces.csICmdBarCommand);
        this._globals.appendElement(command, false);
      }
    }

    return this._globals;
  },

  /* csICmdBarCommand */

  /*
   * Name of this command.
   * The string is matched against text given in the cmdbar.
   * Hence, supports localization.
   */
  get name() {
    if (!this._cmdname) {
      this._cmdname = 'mail';
    }

    return this._cmdname;
  },

  /*
   * A convenience function to create parameters
   */
  _createParam : function(aParamName, aTakesValue, aValueType, aRequireType) {
    var param = {
      name: aParamName,
      takesValue: aTakesValue,
      valueType: aValueType,
      requireType: aRequireType,
      QueryInterface : function QI(aIID) {
        if (aIID.equals(csICmdBarParam) || 
            aIID.equals(nsISupports))
          return this;
  
        throw Components.results.NS_ERROR_NO_INTERFACE;
      }
    }

    this._params.appendElement(param, false);
    return param;
  },

  /*
   * Return the list of parameters supported by this command
   */
  get params() {
    if (this._params.length == 0) {
      var csICmdBarParam = Components.interfaces.csICmdBarParam;

      this._to = this._createParam('to', true, "mail-addr-list", 
                                   csICmdBarParam.TYPE_REQUIRED);
      this._cc = this._createParam('cc', true, "mail-addr-list", 
                                   csICmdBarParam.TYPE_OPTIONAL);
      this._bcc = this._createParam('bcc', true, "mail-addr-list", 
                                    csICmdBarParam.TYPE_OPTIONAL);
      this._from = this._createParam('from', true, "mail-identity", 
                                     csICmdBarParam.TYPE_OPTIONAL);
      this._subject = this._createParam('subject', true, "string", 
                                        csICmdBarParam.TYPE_WARN);
      this._body = this._createParam('body', true, "string", 
                                     csICmdBarParam.TYPE_WARN);
    }

    return this._params;
  },

  /*
   * Given the commandline and the parameters
   * execute the command
   */
  doCommand : function(aParameterArray, aWindow) {
    try {
      if (aParameterArray.length == 1) {
        aWindow.setCurrentApp('mailnews'); 
      } else {
        var enumerator = aParameterArray.enumerate();
        var msgComposeService = Components.classes["@mozilla.org/messengercompose;1"]
                                          .getService(Components.interfaces.nsIMsgComposeService);
        var msgParams = Components.classes["@mozilla.org/messengercompose/composeparams;1"]
                                  .createInstance(Components.interfaces.nsIMsgComposeParams);
        var composeFields = Components.classes["@mozilla.org/messengercompose/composefields;1"]
                                      .createInstance(Components.interfaces.nsIMsgCompFields);
  
        // Make sure params list is populated
        // if there are any parameters
        this.params;

        while (enumerator.hasMoreElements()) {
          var entry = enumerator.getNext()
                                .QueryInterface(Components.interfaces.nsISupportsString);
          var str = entry.toString();
          var key = str.split(":")[0];
          var value = str.substring(key.length + 1, str.length);
          
          switch (key) {
            case this._to.name:
              composeFields.to = value;
              break;
            case this._cc.name:
              composeFields.cc = value;
              break;
            case this._bcc.name:
              composeFields.bcc = value;
              break;
            case this._from.name:
              composeFields.from = value;
              break;
            case this._subject.name:
              composeFields.subject = value;
              break;
            case this._body.name:
              composeFields.body = value;
              break;
          }
        }
        msgParams.type = Components.interfaces.nsIMsgCompType.New;
        msgParams.format = Components.interfaces.nsIMsgCompFormat.Default;
        msgParams.composeFields = composeFields;
        msgComposeService.OpenComposeWindowWithParams(null, msgParams);
      }
    } catch(ex) {
      dump(ex);
      return Components.results.NS_ERROR_FAILURE;
    }

    return Components.results.NS_OK;
  }
}

/*********************************************************
   Implements csICmdBarArgument to support address lists
 *********************************************************/

function csMailnewsCmdBarAddressList() {}

csMailnewsCmdBarAddressList.prototype = {

  type:"mail-addr-list",

  getValues: function() {
  },

  validate: function() {
  }
}

/***********************************************************
   Implements csICmdBarArgument to support mail identities
 ***********************************************************/

function csMailnewsCmdBarIdentity() {}

csMailnewsCmdBarIdentity.prototype = {

  type:"mail-identity",

  getValues: function() {
  },

  validate: function() {
  }
}

/***********
   Factory
 ***********/

var csMailnewsCmdBarFactory = {
  QueryInterface : function(aIID) {
    if (aIID.equals(nsIFactory ) ||
        aIID.equals(nsISupports))
      return this;

    throw Components.results.NS_ERROR_NO_INTERFACE;
  },

  createInstance : function(aOuter, aIID) {
    if (aOuter != null) {
      throw Components.results.NS_ERROR_NO_AGGREGATION;
    }

    return (new csMailnewsCmdBar()).QueryInterface(aIID);
  },

  lockFactory : function(lock) {},
}

/**********
   Module 
 **********/

var csMailnewsCmdBarModule = {
  
  /* nsISupports */

  QueryInterface : function QI(aIID) {
    if (aIID.equals(nsIModule) || 
        aIID.equals(nsISupports))
      return this;

    throw Components.results.NS_ERROR_NO_INTERFACE;
  },

  /* nsIModule */

  getClassObject : function (compMgr, cid, aIID) {
    if (cid.equals(csMailnewsCmdBar_CID))
      return csMailnewsCmdBarFactory;

    throw Components.results.NS_ERROR_FAILURE;
  },
    
  registerSelf: function mod_regself(aCompMgr, aFileSpec, aLocation, aType) {

    /* Register the factory */
    var compReg = aCompMgr.QueryInterface(Components.interfaces.nsIComponentRegistrar);
    compReg.registerFactoryLocation(csMailnewsCmdBar_CID, 
                                    "csMailnewsCmdBar",
                                    csMailnewsCmdBar_ContractID, 
                                    aFileSpec, aLocation, aType);


    /* Register to Category Manager */
    var catMan = Components.classes["@mozilla.org/categorymanager;1"]
                           .getService(Components.interfaces.nsICategoryManager);

    catMan.addCategoryEntry("cmdbar-handlers", "mailnews",
                            csMailnewsCmdBar_ContractID, true, true);
    catMan.addCategoryEntry("cmdbar-commands-mailnews-global", "mail",
                            csMailnewsCmdBar_ContractID, true, true);
  },
    
  unregisterSelf : function mod_unregself(compMgr, location, type) {
    var compReg = compMgr.QueryInterface(nsIComponentRegistrar);
    compReg.unregisterFactoryLocation(csMailnewsCmdBar_CID, location);

    var catMan = Components.classes["@mozilla.org/categorymanager;1"]
                           .getService(Components.interfaces.nsICategoryManager);

    catMan.deleteCategoryEntry("cmdbar-handlers", "mailnews", true);
    catMan.deleteCategoryEntry("cmdbar-commands-mailnews-global", "mail", true);
  },

  canUnload: function(compMgr) {
    return true;
  }
}

/* NSGetModule */

function NSGetModule(compMgr, fileSpec) {
  return csMailnewsCmdBarModule;
}

