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
function onBlogAddressingWidgetLoad()
{
  var menulist = document.getElementById("addressCol1#1");
  // XXX: l10n?
  menulist.appendItem("Blog:", "addr_blog");

  // Yuck!
  var originalCommandHandler = menulist.getAttribute("oncommand");
  menulist.setAttribute("oncommand", 
    originalCommandHandler + ";onAwPopupValueChanged(this);");
}

function onAwPopupValueChanged(menulist)
{
  var row = menulist.id.slice(menulist.id.lastIndexOf('#') + 1);
  var blogMenu = awBlogGetMenu(row);
  var inputElement = awGetInputElement(row);

  if (menulist.selectedItem.getAttribute("value") == "addr_blog")
  {
    /*
    var nextRow = parseInt(row) + 1;
    var nextInputElement = awGetInputElement(nextRow);
    if (!nextInputElement)
    {
      awAppendNewRow(true);

      var nextBlogMenu = awBlogGetMenu(nextRow);
      nextBlogMenu.addAttribute("collapsed", "true");
      nextInputElement = awGetInputElement(nextRow);
      nextInputElement.removeAttribute("collapsed");
      nextInputElement.setAttribute("value", "");
    }
    */

    if (!blogMenu)
      blogMenu = awBlogAddMenu(row);

    blogMenu.removeAttribute("collapsed");
    inputElement.setAttribute("collapsed", "true");
    inputElement.value = "";

    awDeleteAllOtherRows(row);
  }
  else
  {
    if (blogMenu)
    {
      blogMenu.setAttribute("collapsed", "true");
      inputElement.removeAttribute("collapsed");
    }
  }
}

/* Delete all the rows but the current row */
function awDeleteAllOtherRows(row)
{
  var maxRecipients = top.MAX_RECIPIENTS;
  for (var currentRow = maxRecipients; currentRow >= 1; currentRow--)
    if (row != currentRow)
      awRemoveRow(currentRow);

  awSetInputAndPopupId(awGetInputElement(row), awGetPopupElement(row), 1);

  awTestRowSequence();
}

function awBlogGetMenu(row)
{
  var inputElement = awGetInputElement(row);
  var blogMenuLists = inputElement.parentNode.getElementsByTagName("menulist");
  if (blogMenuLists.length > 0)
    return blogMenuLists[0];
  return null;
}

function awBlogAddMenu(row)
{
  var blogs = awBlogGetBlogsList();

  var blogMenu = document.createElement("menulist");
  awGetInputElement(row).parentNode.appendChild(blogMenu);
  blogMenu.setAttribute("flex", "1");
  blogMenu.setAttribute("oncommand", "return awBlogOnBlogChanged(event);");

  var menuPopup = document.createElement("menupopup");
  blogMenu.appendChild(menuPopup);

  for each (blog in blogs)
  {
    var menuItem = document.createElement("menuitem");
    menuPopup.appendChild(menuItem);
    menuItem.setAttribute("label", blog.name);
    menuItem.setAttribute("value", blog.uri);
  }

  if (blogMenu.itemCount > 0)
  {
    blogMenu.selectedIndex = 0;
    awBlogOnBlogChanged({currentTarget : blogMenu});
  }

  return blogMenu;
}

function awBlogOnBlogChanged(event)
{
  var compFields = gMsgCompose.compFields;
  if (compFields)
    compFields.fcc2 = event.currentTarget.selectedItem.value;
}

function awBlogGetBlogsList()
{
  var accountManager = Components
    .classes["@mozilla.org/messenger/account-manager;1"]
    .getService(Components.interfaces.nsIMsgAccountManager);
  var accounts = queryISupportsArray(accountManager.accounts,
                                     Components.interfaces.nsIMsgAccount);

  var result = [];
  for (var i in accounts)
  {
    var server = accounts[i].incomingServer;
    if (server.type == "blog")
    {
      var folders = server.rootFolder.getFoldersWithFlags(
                         Components.interfaces.nsMsgFolderFlags.Inbox);
      folders = folders.QueryInterface(Components.interfaces.nsIArray);
      var enumerator = folders.enumerate();
      if (enumerator.hasMoreElements())
      {
        var folder = enumerator.getNext().QueryInterface(
                       Components.interfaces.nsIMsgFolder);
        result.push({"name" : server.prettyName, "uri" : folder.URI});
      }
    }
  }

  return result;
}

window.addEventListener("load", onBlogAddressingWidgetLoad, false);
