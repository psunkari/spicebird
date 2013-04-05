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

function onAccountWizardAdvanced (event)
{
  var pageData = GetPageData();

  if (gCurrentAccountData && gCurrentAccountData.incomingServer &&
      gCurrentAccountData.incomingServer.type == "blog")
  {
    var wizardAccountTypePage = document.getElementById("accounttype");
    setNextPage("accnamepage", "ispPage12");
    setNextPage("ispPage11", "accnamepage");
    setNextPage("ispPage10", "ispPage11");
    setNextPage("ispPage9", "ispPage10");
    setNextPage("accounttype", "ispPage9");
  }

  return true;
}

var wizardPage = document.getElementById("accounttype");
if (wizardPage)
{
  wizardPage.addEventListener("pageadvanced", acctTypePageUnload, false);
  wizardPage.addEventListener("pageadvanced", onAccountWizardAdvanced, false);
}

/*
 * Finish Account Hook
 */
var blogFinishAccountOldHook = this.FinishAccountHook;
this.FinishAccountHook = function (domain)
{
  var server = gCurrentAccount.incomingServer;
  var pageData = GetPageData();

  if (server && server.type == "blog")
  {
    server.setUnicharAttribute("rpcURL",
                               pageData["server"]["rpcURL"].value);
    server.setUnicharAttribute("blogType",
                               pageData["server"]["blogType"].value);
    server.setUnicharAttribute("blogID",
                               pageData["server"]["blogID"].value);
    server.setUnicharAttribute("apiKey",
                               pageData["server"]["apiKey"].value);
    server.setIntAttribute("noOfItemsToSync",
                           pageData["server"]["noOfItemsToSync"].value);
    server.setBoolAttribute("useBooleanForPublish",
                            pageData["server"]["useBooleanForPublish"].value);
  }

  /* Now call old saved hook */
  if (this.blogFinishAccountOldHook != undefined)
    blogFinishAccountOldHook(domain);
};


/*
 * Blog address page
 */
function blogAddressPageInit ()
{
  /* Fill the available list of blog types */
  var types = BlogUtils.supportedTypes;
  var typeMenuList = document.getElementById("blogType");
  typeMenuList.removeAllItems();
  for (var i = 0; i < types.length; i++)
  {
    typeMenuList.appendItem(types[i].displayName, types[i].type);
    typeMenuList.getItemAtIndex(i).urlTemplate = types[i].urlTemplate;
  }

  if (typeMenuList.itemCount > 0)
  {
    typeMenuList.selectedIndex = 0;
    onBlogTypeChanged({currentTarget: typeMenuList});
  }

  return true;
}

function onBlogTypeChanged(event)
{
  var selectedItem = event.currentTarget.selectedItem;

  var urlTemplateElement = document.getElementById("urlTemplate");
  var valueFormat = urlTemplateElement.getAttribute("valueFormat");
  value = valueFormat.replace(/%s/,
                              event.currentTarget.selectedItem.urlTemplate);
  urlTemplateElement.setAttribute("value", value);
  
  var address = document.getElementById("blogAddress");
  if (!address.value)
    address.value = selectedItem.urlTemplate;
  else
  {
    for (var i = 0; i < BlogUtils.supportedTypes.length; i++)
    {
      if (BlogUtils.supportedTypes[i].urlTemplate == address.value)
      {
        address.value = selectedItem.urlTemplate;
        break;
      }
    }
  }
}

function blogAddressPageValidate()
{
  var address = document.getElementById("blogAddress").value;

  if (!address)
  {
    window.alert(BlogUtils.getString("blog.error.pleaseEnterBlogAddress"));
    return false;
  } 
  else
  {
    var ioService = Components.classes["@mozilla.org/network/io-service;1"].
	                  getService(Components.interfaces.nsIIOService);
	try {
	  var uri = ioService.newURI(address, null, null);
	} catch (ex) {
	  window.alert(BlogUtils.getString("blog.error.invalidURL"));
	  return false;
	}

	if (uri.scheme != "http" && uri.scheme != "https")
	{
	  window.alert(BlogUtils.getString("blog.error.blogURLNotHTTP"));
	  return false;
	}

    var blogType = document.getElementById("blogType").selectedItem.value;
    var useBooleanForPublish = false;

    for (var i = 0; i < BlogUtils.supportedTypes.length; i++)
    {
      if (BlogUtils.supportedTypes[i].type == blogType)
      {
        useBooleanForPublish = BlogUtils.supportedTypes[i]
                                 .useBooleanForPublish;
        break;
      }
    }

	var pageData = parent.GetPageData();
	setPageData(pageData, "server", "hostname", uri.host);
	setPageData(pageData, "server", "rpcURL", address);
	setPageData(pageData, "server", "blogType", blogType);
    setPageData(pageData, "server", "apiKey", "12345678");
    setPageData(pageData, "server", "noOfItemsToSync", 100);
    setPageData(pageData, "server", "useBooleanForPublish",
                useBooleanForPublish);
  }

  return true;
}

/*
 * User name page
 */
function blogUserNamePageInit()
{
    return true;
}

function blogUserNamePageValidate()
{
  var userName = document.getElementById("blogUserName").value;

  if(!userName)
  {
    window.alert(BlogUtils.getString("blog.error.pleaseEnterUserName"));
	return false;
  }

  var pageData = GetPageData();
  setPageData(pageData, "login", "username", userName);

  return true;
}

/*
 * Blog ID page
 */
function blogIDPageInit()
{
  document.documentElement.canAdvance = false;

  var statusText = document.getElementById("statusText");
  var errorText = document.getElementById("errorText");
  var blogIDBox = document.getElementById("blogIDBox");

  statusText.removeAttribute("collapsed");
  errorText.setAttribute("collapsed", "true");
  blogIDBox.setAttribute("collapsed", "true");

  var pageData = parent.GetPageData();
  var blogType = pageData["server"]["blogType"].value;
  var rpcURL = pageData["server"]["rpcURL"].value;
  var userName = pageData["login"]["username"].value;
  BlogUtils.getUsersBlogs(blogType, "", rpcURL, userName,
                          onGetUsersBlogsResponse);
}

function onGetUsersBlogsResponse(result)
{
  var statusText = document.getElementById("statusText");
  var errorText = document.getElementById("errorText");
  var blogIDBox = document.getElementById("blogIDBox");

  if (result == null)
  {
    /* User cancelled the password input */
    statusText.setAttribute("collapsed", "true");
    errorText.removeAttribute("collapsed");
    errorText.setAttribute("value",
      BlogUtils.getString("blog.error.pleaseEnterPassword"));
    blogIDBox.setAttribute("collapsed", "true");
  }
  else if (typeof result == "string")
  {
    /* We have an error */
    statusText.setAttribute("collapsed", "true");
    errorText.removeAttribute("collapsed");
    errorText.setAttribute("value", 
      BlogUtils.getString("blog.error.genericErrorRetrievingBlogList") + " " + result);
    blogIDBox.setAttribute("collapsed", "true");
  }
  else if (typeof result == "object")
  {
    /* We have proper response */
    statusText.setAttribute("collapsed", "true");
    errorText.setAttribute("collapsed", "true");
    blogIDBox.removeAttribute("collapsed");

    var menuList = document.getElementById("blogID");
    menuList.removeAllItems();
    for (var i = 0; i < result.length; i++)
      menuList.appendItem(result[i].blogName, result[i].blogid);
    if (menuList.itemCount > 0)
      menuList.selectedIndex = 0;

    document.documentElement.canAdvance = true;
  }
}

function blogIDPageValidate()
{
  var selectedBlog = document.getElementById("blogID").selectedItem;

  var pageData = parent.GetPageData();
  setPageData(pageData, "server", "blogID", selectedBlog.value);
  setPageData(pageData, "server", "blogName", selectedBlog.label);
  
  document.getElementById("prettyName").value = selectedBlog.label;
}

function onBlogIDPageHide()
{
  document.documentElement.canAdvance = true;
}

/*
 * Summary page
 */
function blogDonePageInit()
{
  var pageData = GetPageData();
  var blogType = pageData["server"]["blogType"].value;

  var blogTypePrettyName = "";

  for (var i = 0; i < BlogUtils.supportedTypes.length; i++)
  {
    if (BlogUtils.supportedTypes[i].type == blogType)
    {
      blogTypePrettyName = BlogUtils.supportedTypes[i].displayName;
      break;
    }
  }

  document.getElementById("blogFinishAccountName").value =
    pageData["accname"]["prettyName"].value;
  document.getElementById("blogFinishBlogType").value = blogTypePrettyName;
  document.getElementById("blogFinishAPIAddress").value = 
    pageData["server"]["rpcURL"].value;
  document.getElementById("blogFinishUserName").value = 
    pageData["login"]["username"].value;
  document.getElementById("blogFinishBlogID").value = 
    pageData["server"]["blogName"].value;
}
