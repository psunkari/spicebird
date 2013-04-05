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

var BlogUtils = {
  supportedTypes : [
    {
      displayName : "Drupal",
      type : "drupal",
      urlTemplate : "http://mydrupalsite.org/xmlrpc.php",
      useBooleanForPublish : true
    },
    {
      displayName : "Jeeran",
      type : "jeeran",
      urlTemplate : "http://api.jeeran.com/blogs/rpc.rem",
      useBooleanForPublish : false
    },
    {
      displayName : "MetaWeblog API",
      type : "metaweblog",
      urlTemplate : "http://myblogsite.com/xmlrpc.php",
      useBooleanForPublish : false
    },
    {
      displayName : "Roller",
      type : "roller",
      urlTemplate : "http://myblogsite.com/xmlrpc",
      useBooleanForPublish : false
    },
    {
      displayName : "Windows Live Spaces",
      type : "msnspaces",
      urlTemplate : "https://storage.msn.com/storageservice/MetaWeblog.rpc",
      useBooleanForPublish : false
    },
    {
      displayName : "Wordpress",
      type : "wordpress",
      urlTemplate : "http://myblog.wordpress.com/xmlrpc.php",
      useBooleanForPublish : false
    }
  ],

  createBlogAPIObject : function(type)
  {
    switch (type)
    {
      case "drupal":
      case "jeeran":
      case "metaweblog":
      case "roller":
      case "msnspaces":
      case "wordpress":
        return new performancingMetaweblogAPI();
    }

    return null;
  },
  
  getUsersBlogs : function(type, apiKey, rpcURL, userName, callbackFunction)
  {
    var password = {};
    var promptService = Components.classes["@mozilla.org/embedcomp/prompt-service;1"]
                          .getService(Components.interfaces.nsIPromptService);
    if (!promptService.promptPassword(window,
           this.getString("blog.enterYourPasswordForAccount.title"),
           this.getString("blog.enterYourPasswordForAccount.message",
                          [userName, rpcURL]),
           password, null, {}))
    {
      /* User cancelled the dialog */
      callbackFunction();
      return;
    }

    password = password.value;

    var blogAPI = this.createBlogAPIObject(type);
    blogAPI.doSetup();
    blogAPI.init(type, apiKey, rpcURL, "" /* ID */, "", userName, password,
                 true);
    var xmlRequest = blogAPI.getUsersBlogs();
    performancing_xmlcall.sendCommand(rpcURL, xmlRequest,
                                      this.onGetUsersBlogsResponse,
                                      [this, callbackFunction], "",
                                      performancing_xmlcall.processData);
  },

  onGetUsersBlogsResponse : function(responseObject, callbackData)
  {
    this_ = callbackData[0];
    callbackFunction = callbackData[1];

    if ("faultCode" in responseObject)
    {
      callbackFunction(responseObject.faultString);
      return false;
    }

    callbackFunction(responseObject);
    return true;
  },

  mBlogStringBundle: null,
  
  getString : function(id, params)
  {
    if (!this.mBlogStringBundle)
    {
      var src = 'chrome://collab-blog/locale/blog.properties';
      var stringBundleService =
        Components.classes["@mozilla.org/intl/stringbundle;1"]
        .getService(Components.interfaces.nsIStringBundleService);
      this.mBlogStringBundle = stringBundleService.createBundle(src);
    }

    if (this.mBlogStringBundle)
    {
      try {
        if (params)
          return this.mBlogStringBundle.formatStringFromName(id, params,
                                                             params.length);
        else
          return this.mBlogStringBundle.GetStringFromName(id);
      } catch (ex) {
        dump(ex);
      }
    }
  
    return id;
  }
};

