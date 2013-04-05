/* -*- Mode: js2; tab-width: 4; indent-tabs-mode: nil; -*-
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
#   Sunil Mohan Adapa <sunil@synovel.com>, original author
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

/* components defined in this file */
const BLOG_ACCOUNT_MANGER_EXTENSION_CONTRACTID =
    "@mozilla.org/accountmanager/extension;1?name=blog";
const BLOG_ACCOUNT_MANGER_EXTENSION_CID =
    Components.ID("{71d536ec-3309-4b5c-9487-f6c3002e292e}");
const BLOG_MANAGER_CONTRACTID =
    "@synovel.com/blog/blog-manager;1";
const BLOG_MANAGER_CID =
    Components.ID("{0eb08a66-b640-40fb-ac72-a8d66fb8bae4}");

/* Some shortcuts */
const nsISupports                    = Components.interfaces.nsISupports;
const nsICategoryManager             = Components.interfaces.nsICategoryManager;
const nsIMsgAccountManagerExtension  = Components.interfaces.nsIMsgAccountManagerExtension;
const csIBlogManager                 = Components.interfaces.csIBlogManager;

/* Initialization code */
var gBlogModuleInitialized = false;

function loadScripts ()
{
  var loader = Components.classes["@mozilla.org/moz/jssubscript-loader;1"]
    .getService(Components.interfaces.mozIJSSubScriptLoader);
  loader.loadSubScript("chrome://collab-blog/content/BlogAccountManagerExtension.js");
  loader.loadSubScript("chrome://collab-blog/content/BlogManager.js");
  loader.loadSubScript("chrome://collab-blog/content/performancing_api.js");
  loader.loadSubScript("chrome://collab-blog/content/xmlrpc.js");
  loader.loadSubScript("chrome://collab-blog/content/BlogUtils.js");
}

/* factory for BlogAccountManagerExtension */
var BlogAccountManagerExtensionFactory = new Object();

BlogAccountManagerExtensionFactory.createInstance =
function (outer, iid) {
  try
  {
    if (!gBlogModuleInitialized)
    {
      loadScripts();
      gBlogModuleInitialized = true;
    }
  }
  catch (ex)
  {
    throw Components.results.NS_ERROR_FAILURE;
  }

  if (outer != null)
    throw Components.results.NS_ERROR_NO_AGGREGATION;

  if (!iid.equals(nsIMsgAccountManagerExtension) && !iid.equals(nsISupports))
    throw Components.results.NS_ERROR_INVALID_ARG;

  return new BlogAccountManagerExtension();
};

/* factory for BlogManager */
var BlogManagerFactory = new Object();

BlogManagerFactory.createInstance = 
function (outer, iid) {
  try
  {
    if (!gBlogModuleInitialized)
    {
      loadScripts();
      gBlogModuleInitialized = true;
    }
  }
  catch (ex)
  {
    throw Components.results.NS_ERROR_FAILURE;
  }

  if (outer != null)
    throw Components.results.NS_ERROR_NO_AGGREGATION;

  if (!iid.equals(csIBlogManager) && !iid.equals(nsISupports))
    throw Components.results.NS_ERROR_INVALID_ARG;

  return new BlogManager();
};

var BlogModule = new Object();

BlogModule.registerSelf =
function (compMgr, fileSpec, location, type)
{
  compMgr = compMgr.QueryInterface(Components.interfaces.nsIComponentRegistrar);
  compMgr.registerFactoryLocation(BLOG_ACCOUNT_MANGER_EXTENSION_CID,
                                  "Blog Account Manager Extension Service",
                                  BLOG_ACCOUNT_MANGER_EXTENSION_CONTRACTID, 
                                  fileSpec,
                                  location, 
                                  type);
  compMgr.registerFactoryLocation(BLOG_MANAGER_CID,
                                  "Blog Manager Service",
                                  BLOG_MANAGER_CONTRACTID, 
                                  fileSpec,
                                  location, 
                                  type);
  catman = Components.classes["@mozilla.org/categorymanager;1"].getService(nsICategoryManager);
  catman.addCategoryEntry("mailnews-accountmanager-extensions",
                          "blog account manager extension",
                          BLOG_ACCOUNT_MANGER_EXTENSION_CONTRACTID, true, true);
};

BlogModule.unregisterSelf =
function(compMgr, fileSpec, location)
{
  compMgr = compMgr.QueryInterface(Components.interfaces.nsIComponentRegistrar);
  compMgr.unregisterFactoryLocation(BLOG_MANGER_CID, fileSpec);
  compMgr.unregisterFactoryLocation(BLOG_ACCOUNT_MANGER_EXTENSION_CID, fileSpec);
  catman = Components.classes["@mozilla.org/categorymanager;1"].getService(nsICategoryManager);
  catman.deleteCategoryEntry("mailnews-accountmanager-extensions",
                             BLOG_ACCOUNT_MANGER_EXTENSION_CONTRACTID, true);
};

BlogModule.getClassObject =
function (compMgr, cid, iid) {
  if (cid.equals(BLOG_ACCOUNT_MANGER_EXTENSION_CID))
    return BlogAccountManagerExtensionFactory;

  if (cid.equals(BLOG_MANAGER_CID))
    return BlogManagerFactory;

  if (!iid.equals(Components.interfaces.nsIFactory))
    throw Components.results.NS_ERROR_NOT_IMPLEMENTED;

  throw Components.results.NS_ERROR_NO_INTERFACE;    
};

BlogModule.canUnload =
function(compMgr)
{
  return true;
};

/* entrypoint */
function NSGetModule(compMgr, fileSpec) {
  return BlogModule;
}
