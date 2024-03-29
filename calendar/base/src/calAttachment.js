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
 * The Original Code is Oracle Corporation code.
 *
 * The Initial Developer of the Original Code is Oracle Corporation
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Stuart Parmenter <pavlov@pavlov.net>
 *   Joey Minta <jminta@gmail.com>
 *   Fred Jendrzejewski <fred.jen@web.de>
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

Components.utils.import("resource://calendar/modules/calIteratorUtils.jsm");

//
// calAttachment.js
//
function calAttachment() {
    this.wrappedJSObject = this;
    this.mProperties = new calPropertyBag();
}

calAttachment.prototype = {
    mEncoding: null,
    mUri: null,
    mType: null,

    QueryInterface: function (aIID) {
        return doQueryInterface(this,
                                calAttachment.prototype,
                                aIID,
                                null,
                                this);
    },

    /**
     * nsIClassInfo
     */

    getInterfaces: function cA_getInterfaces(aCount) {
        var ifaces = [
            Components.interfaces.nsISupports,
            Components.interfaces.calIAttachment,
            Components.interfaces.nsIClassInfo
        ];
        aCount.value = ifaces.length;
        return ifaces;
    },

    getHelperForLanguage: function cA_getHelperForLanguage(language) {
        return null;
    },

    contractID: "@mozilla.org/calendar/attachment;1",
    classDescription: "Calendar Item Attachment",
    classID: Components.ID("{5f76b352-ab75-4c2b-82c9-9206dbbf8571}"),
    implementationLanguage: Components.interfaces.nsIProgrammingLanguage.JAVASCRIPT,
    flags: 0,

    /**
     * calIAttachment
     */

    get uri cA_get_uri() {
        return this.mUri;
    },
    set uri cA_set_uri(aUri) {
        return (this.mUri = aUri);
    },

    get formatType cA_get_formatType() {
        return this.mType;
    },
    set formatType cA_set_formatType(aType) {
        return (this.mType = aType);
    },

    get encoding cA_get_encoding() {
        return this.mEncoding
    },
    set encoding cA_set_encoding(aValue) {
        return (this.mEncoding = aValue);
    },

    get icalProperty cA_get_icalProperty(attProp) {
        var icssvc = getIcsService();
        var icalatt = icssvc.createIcalProperty("ATTACH");
        if (this.mUri) {
            icalatt.value = this.mUri.spec;
        }

        if (this.mType) {
            icalatt.setParameter("FMTTYPE", this.mType);
        }

        if (this.mEncoding) {
            icalatt.setParameter("ENCODING", this.mEncoding);
        }

        for each (let [key, value] in this.mProperties) {
            icalatt.setParameter(key, value);
        }
        return icalatt;
    },

    set icalProperty cA_set_icalProperty(attProp) {
        // Reset the property bag for the parameters, it will be re-initialized
        // from the ical property.
        this.mProperties = new calPropertyBag();

        //TODO: handle local uris in a sensible way
        // handle the VALUE = BINARY parameter
        if (attProp.value) {
            this.mUri = makeURL(attProp.value);
        }

        for each (let [name, value] in cal.ical.paramIterator(attProp)) {
            switch (name) {
                case "FMTTYPE":
                    this.mType = value;
                    break;
                case "ENCODING":
                    this.mEncoding = value;
                    break;
                default:
                    this.setParameter(name, value);
                    break;
            }
        }
    },

    getParameter: function (aName) {
        return this.mProperties.getProperty(aName);
    },

    setParameter: function (aName, aValue) {
        this.mProperties.setProperty(aName, aValue);
    },

    deleteParameter: function (aName) {
        this.mProperties.deleteProperty(aName);
    },

    clone: function cA_clone() {
        let newAttachment = new calAttachment();
        newAttachment.mType = this.mType;
        newAttachment.mEncoding = this.mEncoding;
        newAttachment.mUri = this.mUri;
        for each (let [name, value] in this.mProperties) {
            newAttachment.mProperties.setProperty(name, value);
        }
        return newAttachment;
    }
};
