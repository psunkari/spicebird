/*
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
# The Original Code is Mozilla Communicator client code, released
# March 31, 1998.
#
# The Initial Developer of the Original Code is
# Netscape Communications Corporation.
# Portions created by the Initial Developer are Copyright (C) 1998
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   William A. ("PowerGUI") Law <law@netscape.com>
#   Blake Ross <blakeross@telocity.com>
#   Gervase Markham <gerv@gerv.net>
#   Phil Ringnalda <philringnalda@gmail.com>
#   Prasad Sunkari <prasad@synovel.com> (Spicebird Chat port)
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
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

/*
 * XXX: This should be converted to be a much simpler class that can be
 * used for any iframe/browser.  All "id" based stuff should be moved out,
 * dependency on window.content should be removed.
 *                                              -- Prasad Sunkari
 */

function csTextChatContextMenu(aXulMenu) {
  this.target         = null;
  this.menu           = null;
  this.onTextInput    = false;
  this.onImage        = false;
  this.onLoadedImage  = false;
  this.onCanvas       = false;
  this.onVideo        = false;
  this.onAudio        = false;
  this.onPlayableMedia = false;
  this.onLink         = false;
  this.onMailtoLink   = false;
  this.onSaveableLink = false;
  this.onMetaDataItem = false;
  this.onMathML       = false;
  this.link           = false;
  this.linkURL        = "";
  this.linkURI        = null;
  this.linkProtocol   = null;
  this.mediaURL       = "";
  this.inFrame        = false;
  this.isContentSelected = false;
  this.inDirList      = false;
  this.shouldDisplay  = true;

  this.initMenu(aXulMenu);
}

csTextChatContextMenu.prototype = {
  /**
   * Init: set properties based on the clicked-on element and the state of
   * the world, then determine which context menu items to show based on
   * those properties.
   */
  initMenu : function CM_initMenu(aPopup) {
    this.menu = aPopup;

    // Get contextual info.
    this.setTarget(document.popupNode);
    this.isContentSelected = this.isContentSelection();

    this.initItems();
  },
  initItems : function CM_initItems() {
    this.initSaveItems();
    this.initClipboardItems();
    this.initMediaPlayerItems();
    this.initMailItems();
    this.initSeparators();
  },
  initSaveItems : function CM_initSaveItems() {
    this.showItem("textChatContext-savelink", this.onSaveableLink);
    this.showItem("textChatContext-saveimage", this.onLoadedImage);
  },
  initClipboardItems : function CM_initClipboardItems() {
    // Copy depends on whether there is selected text.
    // Enabling this context menu item is now done through the global
    // command updating system.

    goUpdateGlobalEditMenuItems();

    this.showItem("textChatContext-copy", this.isContentSelected || this.onTextInput);
    this.showItem("textChatContext-selectall", true);
    this.showItem("textChatContext-copyemail", this.onMailtoLink);
    this.showItem("textChatContext-copylink", this.onLink);
    this.showItem("textChatContext-copyimage", this.onImage);
  },
  initMediaPlayerItems: function CM_initMediaPlayerItems() {
    let onMedia = this.onVideo || this.onAudio;
    // Several mutually exclusive items.... play/pause, mute/unmute, show/hide
    this.showItem("textChatContext-media-play", onMedia && this.target.paused);
    this.showItem("textChatContext-media-pause", onMedia && !this.target.paused);
    this.showItem("textChatContext-media-mute", onMedia && !this.target.muted);
    this.showItem("textChatContext-media-unmute", onMedia && this.target.muted);
    if (onMedia) {
      let hasError = this.target.error != null;
      this.setItemAttr("textChatContext-media-play", "disabled", hasError);
      this.setItemAttr("textChatContext-media-pause", "disabled", hasError);
      this.setItemAttr("textChatContext-media-mute", "disabled", hasError);
      this.setItemAttr("textChatContext-media-unmute", "disabled", hasError);
    }
  },
  initMailItems: function CM_initMailItems() {
    this.showItem("textChatContext-composeemailto", this.onMailtoLink);
    this.showItem("textChatContext-addemail", this.onMailtoLink);
  },
  initSeparators: function CM_initSeparators() {
    const contextSeparators = [
      "textChatContext-sep-link", "textChatContext-sep-open",
      "textChatContext-sep-edit", "textChatContext-sep-copy"
    ];
    contextSeparators.forEach(this.hideIfAppropriate, this);
  
    this.checkLastSeparator(this.menu);
  },


  /**
   * Set the csTextChatContextMenu properties based on the selected node and
   * its ancestors.
   */
  setTarget : function CM_setTarget(aNode) {
    const xulNS =
      "http://www.mozilla.org/keymaster/gatekeeper/there.is.only.xul";
    if (aNode.namespaceURI == xulNS) {
      this.shouldDisplay = false;
      return;
    }
    this.onImage        = false;
    this.onLoadedImage  = false;
    this.onMetaDataItem = false;
    this.onTextInput    = false;
    this.imageURL       = "";
    this.onLink         = false;
    this.onVideo        = false;
    this.onAudio        = false;
    this.mediaURL       = "";
    this.linkURL        = "";
    this.linkURI        = null;
    this.linkProtocol   = null;
    this.onMathML       = false;
    this.inFrame        = false;

    this.target = aNode;

    // First, do checks for nodes that never have children.
    if (this.target.nodeType == Node.ELEMENT_NODE) {
      if (this.target instanceof Components.interfaces.nsIImageLoadingContent &&
          this.target.currentURI) {
        this.onImage = true;
        this.onMetaDataItem = true;

        var request = this.target.getRequest(Components.interfaces.nsIImageLoadingContent.CURRENT_REQUEST);
        if (request && (request.imageStatus & request.STATUS_SIZE_AVAILABLE))
          this.onLoadedImage = true;

        this.imageURL = this.target.currentURI.spec;
      } else if (this.target instanceof HTMLInputElement) {
        this.onTextInput = this.isTargetATextBox(this.target);
      } else if (this.target instanceof HTMLTextAreaElement) {
        this.onTextInput = true;
      } else if (this.target instanceof HTMLCanvasElement) {
        this.onCanvas = true;
      } else if (this.target instanceof HTMLVideoElement) {
        this.onVideo = true;
        this.onPlayableMedia = true;
        this.mediaURL = this.target.currentSrc || this.target.src;
      } else if (this.target instanceof HTMLAudioElement) {
        this.onAudio = true;
        this.onPlayableMedia = true;
        this.mediaURL = this.target.currentSrc || this.target.src;
      // Browser supports background images here but we don't need to.
      } else if (content && "HTTPIndex" in content &&
                 content.HTTPIndex instanceof Components.interfaces.nsIHTTPIndex) {
        this.inDirList = true;
        // Bubble outward till we get to an element with URL attribute
        // (which should be the href).
        var root = this.target;
        while (root && !this.link) {
          if (root.tagName == "tree") {
            // Hit root of tree; must have clicked in empty space;
            // thus, no link.
            break;
          }
          if (root.getAttribute("URL")) {
            // Build pseudo link object so link-related functions work.
            this.onLink = true;
            this.link = { href : root.getAttribute("URL"),
                          getAttribute: function (aAttr) {
                            if (aAttr == "title") {
                              return root.firstChild.firstChild
                                         .getAttribute("label");
                            }
                            return "";
                          }
                        };
            // If element is a directory, then you can't save it.
            this.onSaveableLink = root.getAttribute("container") != "true";
          } else {
            root = root.parentNode;
          }
        }
      }
    }

    // Second, bubble out, looking for items of interest that might be
    // parents of the click target, picking the innermost of each.
    const XMLNS = "http://www.w3.org/XML/1998/namespace";
    var elem = this.target;
    while (elem) {
      if (elem.nodeType == Node.ELEMENT_NODE) {
        // Link?
        if (!this.onLink &&
            ((elem instanceof HTMLAnchorElement && elem.href) ||
             elem instanceof HTMLAreaElement && elem.href ||
             elem instanceof HTMLLinkElement ||
             elem.getAttributeNS("http://www.w3.org/1999/xlink", "type") == "simple")) {

          // Target is a link or a descendant of a link.
          this.onLink = true;
          this.onMetaDataItem = true;
          // Remember corresponding element.
          this.link = elem;
          this.linkURL = this.getLinkURL();
          this.linkURI = this.getLinkURI();
          this.linkProtocol = this.getLinkProtocol();
          this.onMailtoLink = (this.linkProtocol == "mailto");
          this.onSaveableLink = this.isLinkSaveable();
        }

        // Text input?
        if (!this.onTextInput) {
          this.onTextInput = this.isTargetATextBox(elem);
        }

        // Metadata item?
        if (!this.onMetaDataItem) {
          if ((elem instanceof HTMLQuoteElement && elem.cite) ||
              (elem instanceof HTMLTableElement && elem.summary) ||
              (elem instanceof HTMLModElement &&
                (elem.cite || elem.dateTime)) ||
              (elem instanceof HTMLElement &&
                (elem.title || elem.lang)) ||
              (elem.getAttributeNS(XMLNS, "lang"))) {
            this.onMetaDataItem = true;
          }
        }

        // Browser supports background images here but we don't need to.
      }
      elem = elem.parentNode;
    }

    // See if the user clicked on MathML.
    const NS_MathML = "http://www.w3.org/1998/Math/MathML";
    if ((this.target.nodeType == Node.TEXT_NODE &&
         this.target.parentNode.namespaceURI == NS_MathML) ||
        (this.target.namespaceURI == NS_MathML))
      this.onMathML = true;

    // See if the user clicked in a frame.
    if (!window.content || this.target.ownerDocument != window.content.document) {
      this.inFrame = true;
    }
  },

  /**
   * Get a computed style property for an element.
   * @param  aElem
   *         A DOM node
   * @param  aProp
   *         The desired CSS property
   * @return the value of the property
   */
  getComputedStyle: function CM_getComputedStyle(aElem, aProp) {
    return aElem.ownerDocument.defaultView.getComputedStyle(aElem, "")
                .getPropertyValue(aProp);
  },

  /**
   * Generate a URL string from a computed style property, for things like
   * |style="background-image:url(...)"|
   * @return a "url"-type computed style attribute value, with the "url(" and
   *         ")" stripped.
   */
  getComputedURL: function CM_getComputedURL(aElem, aProp) {
    var url = aElem.ownerDocument.defaultView.getComputedStyle(aElem, "")
                   .getPropertyCSSValue(aProp);
    return (url.primitiveType == CSSPrimitiveValue.CSS_URI) ? url.getStringValue() : null;
  },

  /**
   * Determine whether the clicked-on link can be saved, and whether it
   * may be saved according to the ScriptSecurityManager.
   * @return true if the protocol can be persisted and if the target has
   *         permission to link to the URL, false if not
   */
  isLinkSaveable : function CM_isLinkSaveable() {
    try {
      const nsIScriptSecurityManager =
        Components.interfaces.nsIScriptSecurityManager;
      var secMan = Components.classes["@mozilla.org/scriptsecuritymanager;1"]
                             .getService(nsIScriptSecurityManager);
      secMan.checkLoadURIWithPrincipal(this.target.nodePrincipal, this.linkURI,
                                       nsIScriptSecurityManager.STANDARD);
    } catch (e) {
      // Don't save things we can't link to.
      return false;
    }

    // We don't do the Right Thing for news/snews yet, so turn them off
    // until we do.
    return this.linkProtocol && !(
             this.linkProtocol == "mailto" ||
             this.linkProtocol == "javascript" ||
             this.linkProtocol == "news" ||
             this.linkProtocol == "snews");
  },

  /**
   * Save URL of clicked-on link.
   */
  saveLink : function CM_saveLink() {
    saveURL(this.linkURL, this.linkText(), null, true);
  },

  /**
   * Save a clicked-on image.
   */
  saveImage : function CM_saveImage() {
    saveURL(this.imageURL, null, "SaveImageTitle", false);
  },

  /**
   * Extract email addresses from a mailto: link
   */
  getEmail : function CM_getEmail() {
    // Copy the comma-separated list of email addresses only.
    // There are other ways of embedding email addresses in a mailto:
    // link, but such complex parsing is beyond us.

    const kMailToLength = 7; // length of "mailto:"

    var url = this.linkURL;
    var qmark = url.indexOf("?");
    var addresses;

    if (qmark > kMailToLength) {
      addresses = url.substring(kMailToLength, qmark);
    } else {
      addresses = url.substr(kMailToLength);
    }

    // Let's try to unescape it using a character set.
    try {
      var characterSet = this.target.ownerDocument.characterSet;
      const textToSubURI = Components.classes["@mozilla.org/intl/texttosuburi;1"]
                                     .getService(Components.interfaces.nsITextToSubURI);
      addresses = textToSubURI.unEscapeURIForUI(characterSet, addresses);
    }
    catch(ex) {
      // Do nothing.
    }

    return addresses;
  },

  /**
   * Extract email addresses from a mailto: link and put them on the clipboard.
   */
  copyEmail : function CM_copyEmail() {
    var addresses = this.getEmail();
    var clipboard = Components.classes["@mozilla.org/widget/clipboardhelper;1"]
                              .getService(Components.interfaces.nsIClipboardHelper);
    clipboard.copyString(addresses);
  },

  /**
   * If available try to compose an email to the addresses.
   */
  composeEmailTo : function CM_composeEmailTo() {
    let fields = Components.classes["@mozilla.org/messengercompose/composefields;1"]
                           .createInstance(Components.interfaces.nsIMsgCompFields);
    let params = Components.classes["@mozilla.org/messengercompose/composeparams;1"]
                           .createInstance(Components.interfaces.nsIMsgComposeParams);
    let accountManager = Components.classes["@mozilla.org/messenger/account-manager;1"]
                                   .getService(Components.interfaces.nsIMsgAccountManager);
    let composeService = Components.classes["@mozilla.org/messengercompose;1"]
                                   .getService(Components.interfaces.nsIMsgComposeService);

    if (!fields || !params || !accountManager || !composeService)
      return;

    fields.to = this.getEmail();
    params.type = Components.interfaces.nsIMsgCompType.New;
    params.format = Components.interfaces.nsIMsgCompFormat.Default;

    if ((typeof gFolderDisplay !== 'undefined') &&
        gFolderDisplay.displayedFolder) {
      params.identity = accountManager.getFirstIdentityForServer(
                          gFolderDisplay.displayedFolder.server);
    }
    params.composeFields = fields;
    composeService.OpenComposeWindowWithParams(null, params);
  },

  /**
   * Try to add e-mail address to address book.
   */
  addEmail : function CM_addEmail() {
    var addresses = this.getEmail();
    window.openDialog("chrome://messenger/content/addressbook/abNewCardDialog.xul",
                      "",
                       "chrome,resizable=no,titlebar,modal,centerscreen",
                      {primaryEmail: addresses});
  },


  ///////////////
  // Utilities //
  ///////////////

  /**
   * Set a DOM node's hidden property by passing in the node's id or the
   * element itself.
   * @param aItemOrId
   *        a DOM node or the id of a DOM node
   * @param aShow
   *        true to show, false to hide
   */
  showItem : function CM_showItem(aItemOrId, aShow) {
    var item = aItemOrId.constructor == String ? document.getElementById(aItemOrId) : aItemOrId;
    item.hidden = !aShow;
  },

  /**
   * Set a DOM node's disabled property by passing in the node's id or the
   * element itself.
   *
   * @param aItemOrId  A DOM node or the id of a DOM node
   * @param aEnabled   True to enable the element, false to disable.
   */
  enableItem: function CM_enableItem(aItemOrId, aEnabled) {
    var item = aItemOrId.constructor == String ? document.getElementById(aItemOrId) : aItemOrId;
    item.disabled = !aEnabled;
  },

  /**
   * Most menu items are visible if there's 1 or 0 messages selected, and
   * enabled if there's exactly one selected. Handle those here.
   * Exception: playable media is selected, in which case, don't show them.
   *
   * @param aID   the id of the element to display/enable
   * @param aHide (optional)  an additional criteria to evaluate when we
   *              decide whether to display the element. If false, we'll hide
   *              the item no matter what messages are selected
   */
  setSingleSelection: function CM_setSingleSelection(aID, aHide) {
    var hide = aHide != undefined ? aHide : true;
    this.showItem(aID, this.numSelectedMessages == 1 && !this.hideMailItems &&
                  hide && !this.onPlayableMedia);
    this.enableItem(aID, this.numSelectedMessages == 1);
  },

  /**
   * Set given attribute of specified context-menu item. If the
   * value is null, then it removes the attribute (which works
   * nicely for the disabled attribute).
   * @param  aId
   *         The id of an element
   * @param  aAttr
   *         The attribute name
   * @param  aVal
   *         The value to set the attribute to, or null to remove the attribute
   */
  setItemAttr : function CM_setItemAttr(aId, aAttr, aVal) {
    var elem = document.getElementById(aId);
    if (elem) {
      if (aVal == null) {
        // null indicates attr should be removed.
        elem.removeAttribute(aAttr);
      } else {
        // Set attr=val.
        elem.setAttribute(aAttr, aVal);
      }
    }
  },

  /**
   * Get an absolute URL for clicked-on link, from the href property or by
   * resolving an XLink URL by hand.
   * @return the string absolute URL for the clicked-on link
   */
  getLinkURL : function CM_getLinkURL() {
    if (this.link.href) {
      return this.link.href;
    }
    var href = this.link.getAttributeNS("http://www.w3.org/1999/xlink","href");
    if (!href || !href.match(/\S/)) {
       // Without this we try to save as the current doc,
       // for example, HTML case also throws if empty.
      throw "Empty href";
    }
    href = this.makeURLAbsolute(this.link.baseURI,href);
    return href;
  },

  /**
   * Generate a URI object from the linkURL spec
   * @return an nsIURI if possible, or null if not
   */
  getLinkURI: function CM_getLinkURI() {
    var ioService = Components.classes["@mozilla.org/network/io-service;1"]
                              .getService(Components.interfaces.nsIIOService);
    try {
      return ioService.newURI(this.linkURL, null, null);
    } catch (ex) {
      // e.g. empty URL string
    }
    return null;
  },

  /**
   * Get the scheme for the clicked-on linkURI, if present.
   * @return a scheme, possibly undefined, or null if there's no linkURI
   */
  getLinkProtocol: function CM_getLinkProtocol() {
    if (this.linkURI)
      return this.linkURI.scheme; // can be |undefined|

    return null;
  },

  /**
   * Get some text, any text, for the clicked-on link.
   * @return the link text, title, alt, href, or "" if everything fails
   */
  linkText : function CM_linkText() {
    var text = gatherTextUnder(this.link);
    if (!text || !text.match(/\S/)) {
      text = this.link.getAttribute("title");
      if (!text || !text.match(/\S/)) {
        text = this.link.getAttribute("alt");
        if (!text || !text.match(/\S/)) {
          if (this.link.href) {
            text = this.link.href;
          } else {
            text = getAttributeNS("http://www.w3.org/1999/xlink", "href");
            if (text && text.match(/\S/)) {
              text = this.makeURLAbsolute(this.link.baseURI, text);
            }
          }
        }
      }
    }

    return text;
  },

  /**
   * Determines whether the focused window has something selected.
   * @return true if there is a selection, false if not
   */
  isContentSelection : function CM_isContentSelection() {
    return !document.commandDispatcher.focusedWindow.getSelection().isCollapsed;
  },

  /**
   * Convert relative URL to absolute, using a provided <base>.
   * @param  aBase
   *         The URL string to use as the base
   * @param  aUrl
   *         The possibly-relative URL string
   * @return The string absolute URL
   */
  makeURLAbsolute : function CM_makeURLAbsolute(aBase, aUrl) {
    // Construct nsIURL.
    var ioService = Components.classes["@mozilla.org/network/io-service;1"]
                              .getService(Components.interfaces.nsIIOService);
    var baseURI  = ioService.newURI(aBase, null, null);

    return ioService.newURI(baseURI.resolve(aUrl), null, null).spec;
  },

  /**
   * Determine whether a DOM node is a text or password input, or a textarea.
   * @param  aNode
   *         The DOM node to check
   * @return true for textboxes, false for other elements
   */
  isTargetATextBox : function CM_isTargetATextBox(aNode) {
    if (aNode instanceof HTMLInputElement)
      return (aNode.type == "text" || aNode.type == "password");

    return (aNode instanceof HTMLTextAreaElement);
  },

  /**
   * Hide a separator based on whether there are any non-hidden items between
   * it and the previous separator.
   *
   * @param aSeparatorID  The id of the separator element.
   */
  hideIfAppropriate: function CM_hideIfAppropriate(aSeparatorID) {
    this.showItem(aSeparatorID, this.shouldShowSeparator(aSeparatorID));
  },

  /**
   * Determine whether a separator should be shown based on whether
   * there are any non-hidden items between it and the previous separator.
   * @param  aSeparatorID
   *         The id of the separator element
   * @return true if the separator should be shown, false if not
   */
  shouldShowSeparator : function CM_shouldShowSeparator(aSeparatorID) {
    var separator = document.getElementById(aSeparatorID);
    if (separator) {
      var sibling = separator.previousSibling;
      while (sibling && sibling.localName != "menuseparator") {
        if (sibling.getAttribute("hidden") != "true")
          return true;
        sibling = sibling.previousSibling;
      }
    }
    return false;
  },

  /**
   * Ensures that there isn't a separator shown at the bottom of the menu.
   *
   * @param aPopup  The menu to check.
   */
  checkLastSeparator: function CM_checkLastSeparator(aPopup) {
    let sibling = aPopup.lastChild;
    while (sibling) {
      if (sibling.getAttribute("hidden") != "true") {
        if (sibling.localName == "menuseparator") {
          // If we got here then the item is a menuseparator and everything
          // below it hidden.
          sibling.setAttribute("hidden", true);
          return;
        }
        else
          return;
      }
      sibling = sibling.previousSibling;
    }
  },

  openInBrowser: function CM_openInBrowser() {
    let uri = Components.classes["@mozilla.org/network/io-service;1"]
                        .getService(Components.interfaces.nsIIOService)
                        .newURI(content.document.location, null, null);

    Components.classes["@mozilla.org/uriloader/external-protocol-service;1"]
              .getService(Components.interfaces.nsIExternalProtocolService)
              .loadURI(uri);
  },

  openLinkInBrowser: function CM_openLinkInBrowser() {
    Components.classes["@mozilla.org/uriloader/external-protocol-service;1"]
      .getService(Components.interfaces.nsIExternalProtocolService)
      .loadURI(this.linkURI);
  },

  mediaCommand : function CM_mediaCommand(command) {
    var media = this.target;

    switch (command) {
      case "play":
        media.play();
        break;
      case "pause":
        media.pause();
        break;
      case "mute":
        media.muted = true;
        break;
      case "unmute":
        media.muted = false;
        break;
      // XXX hide controls & show controls don't work in emails as Javascript is
      // disabled. May want to consider later for RSS feeds.
    }
  }
};

/* XXX: The things here are very specific to text chat window */
var gTextChatContextMenu = null;
function onTextChatContextMenuHiding(event)
{
  if (event.target != event.currentTarget)
    return true;

  gTextChatContextMenu = null;
}

function onTextChatContextMenuShowing(event)
{
  if (event.target != event.currentTarget)
    return true;

  gTextChatContextMenu = new csTextChatContextMenu(event.target);
  return true;
}
