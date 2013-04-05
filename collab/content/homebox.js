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
#   Prasad Sunkari <prasad@synovel.com>
# Portions created by the Initial Developer are Copyright (C) 2007-2008
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#
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

var gXferDataHeight = 0;
var gPreviewNode = null;
var gCurrentDragItem = null;

/*
 * homeDNDObserver: This object is used by homebox.xml for DragDrop
 *                  on the Spicebird home screen.  DragNDrop would
 *                  not work without this object
 */

var homeDNDObserver = {
    onDragStart: function(aEvent, aXferData, aDragAction) {
        var item = aEvent.target;
        
        if (aEvent.originalTarget.tagName != "xul:label" ||
            aEvent.originalTarget.getAttribute("anonid") != "applet-title-label")
            return;

        while (item && item.getAttribute("class") != "homeapplet") 
            item = item.parentNode;

        if (item.getAttribute("class") != "homeapplet")
            return;

        aXferData.data = new TransferDataSet();
        gXferDataHeight = window.getComputedStyle(item, null).height;

        var data = new TransferData();
        data.addDataForFlavour("text/homeapplet-id", item.id);
        aXferData.data.push(data);
        aDragAction.action = Components.interfaces.nsIDragService.DRAGDROP_ACTION_MOVE;
        item.setAttribute("dragactive", "true");
        gCurrentDragItem = item;

        if (!gPreviewNode) {
            gPreviewNode = document.createElementNS("http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul","box");
            gPreviewNode.setAttribute("class", "homebox-preview-item");
        }
    },

    onDragOver: function(aEvent, aFlavour, aDragSession) {
        var dock = aEvent.target;
        var dropTarget = aEvent.target;

        while (dock && dock.getAttribute("class") != "homebox-dock") {
            dropTarget = dock;
            dock = dock.parentNode;
        }

        if (dropTarget.getAttribute("class") == "homebox-dock") {
            var item = dropTarget.childNodes[0];

            if (!item) {
                appendPreviewNode(dropTarget);
            } else {
                var center = item.boxObject.y + (item.boxObject.height / 2);

                while (item && aEvent.clientY > center) {
                    item = item.nextSibling;
                    if (item)
                        center = item.boxObject.y + (item.boxObject.height / 2);
                }
                if (item) {
                    insertPreviewNode(item, false);
                } else {
                    appendPreviewNode(dropTarget);
                }
            }
        } else {
            var center = dropTarget.boxObject.y + (dropTarget.boxObject.height / 2);
            var after = aEvent.clientY > center;
      
            insertPreviewNode(dropTarget, after);
        }

        aDragSession.canDrop = true;
    },

    onDrop: function(aEvent, aXferData, aDragSession) {
        var itemId = aXferData.data;
        var item = document.getElementById(itemId);
        item.removeAttribute("dragactive");
        item.removeAttribute("hidden");

        if (gPreviewNode && gPreviewNode.parentNode) {
            var previewParent = gPreviewNode.parentNode;

            item.destroy();
            previewParent.insertBefore(item, gPreviewNode);
            previewParent.removeChild(gPreviewNode);

            // Update the weight - both prefs and attribute
            var node = previewParent.firstChild;
            var weight = Number(0);
            do {
                var key = node.getAttribute("homekey");
                node.setAttribute("weight", weight);
                gHomeApplets.setWeight(key, weight);
                weight++;
            } while (node = node.nextSibling); 
                
            // Set the right column - both prefs and attribute
            var column = parseInt(previewParent.getAttribute("column"), 10);
            if( column != parseInt(item.getAttribute("column"), 10)) {
                var key = item.getAttribute("homekey");
                item.setAttribute("column", column);
                gHomeApplets.setColumn(key, column);
            }
        }
    },

    getSupportedFlavours: function ()
    {
        if (!this._flavourSet) {
            this._flavourSet = new FlavourSet();
            this._flavourSet.appendFlavour("text/homeapplet-id");
        }
        return this._flavourSet;
    }
}

function doDragExit(aEvent) 
{
    if (aEvent.target.getAttribute("anonid") != "homebox-vbox") 
        return;
        
    if (gPreviewNode.parentNode) {
        gPreviewNode.parentNode.removeChild(gPreviewNode);
        gCurrentDragItem.removeAttribute("hidden");
    }
}

function appendPreviewNode(aParent)
{
    gPreviewNode.style.height = gXferDataHeight;
    aParent.appendChild(gPreviewNode);
    gCurrentDragItem.setAttribute("hidden", "true");
}

function insertPreviewNode(aSibling, aAfter)
{
    var node = aAfter ? aSibling.nextSibling : aSibling;

    gPreviewNode.style.height = gXferDataHeight;
    aSibling.parentNode.insertBefore(gPreviewNode, node);
    gCurrentDragItem.setAttribute("hidden", "true");
}

