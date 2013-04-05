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

/* some shortcuts */
const nsIMsgFolder           = Components.interfaces.nsIMsgFolder;
const nsIMsgLocalMailFolder  = Components.interfaces.nsIMsgLocalMailFolder;
const nsMsgFolderFlags       = Components.interfaces.nsMsgFolderFlags;

var   gTagService            = Components.classes["@mozilla.org/messenger/tagservice;1"]
                                 .getService(Components.interfaces.nsIMsgTagService);

function BlogManager()
{
}

BlogManager.prototype = {
  /********************************************
   * Member variables
   *******************************************/
  server: null,
  initialized: false,
  isSynchronizing: false,

  /********************************************
   * Getters for data from nsIIncomingServer
   *******************************************/
  get rpcURL ()
  {
    return this.server.getCharAttribute("rpcURL");
  },

  get domain ()
  {
    var ioService = Components.classes["@mozilla.org/network/io-service;1"].
                      getService(Components.interfaces.nsIIOService);
    var uri = ioService.newURI(this.rpcURL, null, null);
    return uri.host;
  },

  get apiKey ()
  {
    return this.server.getCharAttribute("apiKey");
  },

  get blogID ()
  {
    return this.server.getCharAttribute("blogID");
  },

  get userName ()
  {
    return this.server.getCharAttribute("userName");
  },

  get password ()
  {
    return this.server.password;
  },

  get useBooleanForPublish ()
  {
    return this.server.getBoolAttribute("useBooleanForPublish");
  },

  get noOfItemsToSync ()
  {
    return this.server.getIntAttribute("noOfItemsToSync");
  },

  get blogType ()
  {
    return this.server.getCharAttribute("blogType");
  },

  /********************************************
   * Internal Utility Funcitons
   *******************************************/
  getFolder: function(flag)
  {
    var rootFolder;
    if (this.server && (rootFolder = this.server.rootFolder))
    {
      var folders = rootFolder.getFoldersWithFlags(flag);
      folders = folders.QueryInterface(Components.interfaces.nsIArray);
      var enumerator = folders.enumerate();
      if (enumerator.hasMoreElements())
        return enumerator.getNext().QueryInterface(
                 Components.interfaces.nsIMsgFolder);
      return null;
    }
        
    return null;
  },
  
  /* Take all the non-standard response fields and convert them into
   * something useful for our scripting
   */
  normalizePostFields: function(post)
  {
    var p = new Object();

    p.messageId = null;
    if ("postid" in post)
    {
      p.messageId = this.getMessageIdFromPostId(post.postid);
      p.postId = post.postid;
    }
    else
    {
      if ("permaLink" in post)
        p.messageId = post.permaLink;
    }

    p.date = null;
    if ("dateCreated" in post) 
      p.date = post.dateCreated.toUTCString();
    else
      p.date = (new Date()).toUTCString();

    p.author = null;
    if ("wp_author_display_name" in post)
      p.author = post.wp_author_display_name;
    else
    {
      if ("userid" in post)
        p.author = post.userid;
    }

    p.title = null;
    if ("title" in post)
      p.title = post.title;

    p.postStatus = "publish";
    if ("post_status" in post)
      p.postStatus = post.post_status;

    p.categories = [];
    if ("categories" in post)
      for each (category in post.categories)
        p.categories.push(category);

    p.description = post.description;

    return p;
  },

  getPostIdFromMessageId: function(messageId)
  {
    return  messageId.split("@")[0];
  },

  getMessageIdFromPostId: function(postId)
  {
    return postId + "@" + this.domain;
  },
  
  checkAndAddCategory: function(category)
  {
    if (!gTagService.getKeyForTag(category))
      gTagService.addTag(category, '', '');
  },

  removeUpstreamDeletedMessages: function(db, leastPostDate, fetchedMessageIds)
  {
    if (db)
    {
      var enumerator = db.EnumerateMessages();
      while (enumerator.hasMoreElements())
      {
        var header = enumerator.getNext()
                       .QueryInterface(Components.interfaces.nsIMsgDBHdr);
        if (!(header.messageId in fetchedMessageIds) 
            && header.date > leastPostDate.getTime())
        {
          dump ("Deleting header " + header.messageId + " newer than " + leastPostDate.getTime() + " but not in retrieved list\n");
          db.DeleteHeader(header, null, true, true);
        }
      }
    }
  },

  getMimeMessageFromPost: function(post)
  {
    var message = "From - " + post.date + "\n" +
                  "X-Mozilla-Status: 0000\n" +
                  "X-Mozilla-Status2: 00000000\n" +
                  "Message-ID: <" + post.messageId + ">\n" +
                  "Date: " + post.date + "\n";
    if (post.author)
      message +=  "From: " + post.author + "\n";
    if (post.title)
      message +=  "Subject: " + post.title + "\n";
    message +=    "MIME-Version: 1.0\n" +
                  "Content-Type: text/html; charset=UTF-8\n" +
                  "Content-Transfer-Encoding: 8bit\n" +
                  "\n" +
                  post.description +
                  "\n";
    return message;
  },

  performPostAddOperations: function(message, post)
  {
    /* Add tags to the message */
    var keywords = post.categories.map(gTagService.getKeyForTag).join(" ");

    if (keywords)
    {
      var messages = Components.classes["@mozilla.org/supports-array;1"]
                       .createInstance(Components.interfaces.nsISupportsArray);
      messages.Clear();
      messages.AppendElement(message);
      message.folder.addKeywordsToMessages(messages, keywords);
    }
  },
  
  promptForPassword: function(aMsgWindow)
  {
    var okayValue = {};
    this.server.getPasswordWithUI(
      BlogUtils.getString("blog.enterYourPasswordForAccount.message",
                          [this.userName, this.domain]),
      BlogUtils.getString("blog.enterYourPasswordForAccount.title"),
      aMsgWindow, okayValue);
    return okayValue.value;
  },

  getMsgWindow: function()
  {
    try {
      var windowMediator = Components
                            .classes["@mozilla.org/appshell/window-mediator;1"]
                            .getService();
      windowMediator = windowMediator.QueryInterface(
                         Components.interfaces.nsIWindowMediator);
    
      return windowMediator.getMostRecentWindow("collab:main").msgWindow;
    } catch (ex) {
      dump(ex);
    }
    return null;
  },

  showStatusMessage: function(aMessage, aMsgWindow)
  {
    if (!aMsgWindow)
      aMsgWindow = this.getMsgWindow();

    if (!aMsgWindow || !aMsgWindow.statusFeedback)
      return;

    aMsgWindow.statusFeedback.showStatusString(aMessage);
  },

  startBusyMessage: function(aMessage, aMsgWindow)
  {
    if (!aMsgWindow)
      aMsgWindow = this.getMsgWindow();

    if (!aMsgWindow || !aMsgWindow.statusFeedback)
      return;

    aMsgWindow.statusFeedback.startMeteors();
    aMsgWindow.statusFeedback.showStatusString(aMessage);
  },

  stopBusyMessage: function(aMessage, aMsgWindow)
  {
    if (!aMsgWindow)
      aMsgWindow = this.getMsgWindow();

    if (!aMsgWindow || !aMsgWindow.statusFeedback)
      return;

    aMsgWindow.statusFeedback.stopMeteors();
    aMsgWindow.statusFeedback.showStatusString(aMessage);
  },

  /********************************************
   * Main work functions
   *******************************************/
  initAPI: function(aMsgWindow)
  {
    if (!this.initialized)
    {
      /* Initialization */
      this.blog = BlogUtils.createBlogAPIObject(this.blogType);
      this.blog.doSetup();
      this.initialized = true;
    }

    if (!this.password)
      if (!this.promptForPassword(aMsgWindow))
        return false;

    this.blog.init(this.blogType, this.apiKey, this.rpcURL, this.blogID,
                   "", this.userName, this.password, true);

    return true;
  },

  updateItems: function(aMsgWindow)
  {
    /* Check if a synchronization already in progress */
    if (this.isSynchronizing)
    {
      dump ("Already doing synchronizing, ignoring request\n");
      return;
    }

    if (!this.initAPI(aMsgWindow))
      return;

    this.isSynchronizing = true;

    try {
      this.startBusyMessage(BlogUtils.getString("blog.status.synchronizing"),
                            aMsgWindow);

      // TODO: We need to release this later 
      // or we will have circular dependency
      var xmlRequest = this.blog.getRecentPosts(this.noOfItemsToSync);
      performancing_xmlcall.sendCommand(this.rpcURL, xmlRequest,
                                        this.onUpdateItemsResponse,
                                        [this, aMsgWindow], "", 
                                        performancing_xmlcall.processData);
      dump ("updateItems: Request sent\n");
    } catch (ex) {
      this.isSynchronizing = false;
      dump ("Error placing a request to update items: " + ex + "\n");
    }
  },

  onUpdateItemsResponse: function(responseObject, additionalInfo, isAtom,
                                  theGUID)
  {
    dump ("onUpdateItemsResponse: response received\n");
    var this_ = additionalInfo[0];
    var aMsgWindow = additionalInfo[1];

    /* Handle errors returned by the server */
    if ("faultCode" in responseObject)
    {
      this_.isSynchronizing = false;
      this_.stopBusyMessage(BlogUtils.getString(
                              "blog.status.synchronizingFailed"), aMsgWindow);

      /* Login failed */
      if (responseObject.faultCode == 403)
      {
        aMsgWindow.promptDialog.alert(null, 
          BlogUtils.getString("blog.error.invalidCredentials",
                              [this_.userName, this_.domain]));

        /* The password is not correct, throw it off */
        this_.server.forgetPassword();

        /* Retry the same request again */
        this_.updateItems(aMsgWindow);
      }
      return false;
    }

    try 
    {
      var inboxFolder = this_.getFolder(nsMsgFolderFlags.Inbox);
      var draftsFolder = this_.getFolder(nsMsgFolderFlags.Drafts);
      var inboxDB, draftsDB;
      var inboxLocalFolder, draftsLocalFolder;

      if (!inboxFolder)
      {
        this_.isSynchronizing = false;
        this_.stopBusyMessage(BlogUtils.getString(
                              "blog.status.synchronizingFailed"), aMsgWindow);
        return Components.results.NS_ERROR_FAILURE;
      }

      this_.postCache = [];
      for each (post in responseObject)
        this_.postCache.push(this_.normalizePostFields(post));

      // TODO: add code to see if the cache is equal to the old cache
      // if we can ignore below

      inboxDB = inboxFolder.getMsgDatabase(null);
      inboxLocalFolder = inboxFolder.QueryInterface(nsIMsgLocalMailFolder);

      /* If drafts folder does not exist see if wee to create it */
      if (!draftsFolder)
      {
        var needDraftsFolder = false;
        for each (post in this_.postCache)
          if (post.postStatus == "draft")
          {
            needDraftsFolder = true;
            break;
          }
    
        if (needDraftsFolder)
        {
          /* Creating drafts folder */
          var rootFolder;
          if (this_.server && (rootFolder = this_.server.rootFolder))
          {
            draftsFolder = rootFolder.addSubfolder("Drafts");
            if (draftsFolder)
              draftsFolder.setFlag(MSG_FOLDER_FLAG_DRAFTS);
            draftsFolder = this_.getFolder(MSG_FOLDER_FLAG_DRAFTS);
          }
        }
      }

      if (draftsFolder)
      {
        draftsDB = draftsFolder.getMsgDatabase(null);
        draftsLocalFolder = draftsFolder.QueryInterface(nsIMsgLocalMailFolder);
      }

      var leastPostDate = null;
      var fetchedMessageIds = {};
      for each (post in this_.postCache)
      {
        var postDate = new Date(post.date);
        if (!leastPostDate || leastPostDate > postDate)
          leastPostDate = postDate;

        fetchedMessageIds[post.messageId] = true;

        var message = this_.getMimeMessageFromPost(post);

        var skipAddition = false;
        if (inboxDB)
        {
          var header = inboxDB.getMsgHdrForMessageID(post.messageId);
          if (header) // There is already a message with messageId, we need to update it
          {
            if (post.postStatus == "draft")
            { // This post should be in draft folder, so delete from here
              inboxDB.DeleteHeader(header, null, true, true);
            }
            else
            {
              // for now skip this message, later we can check if all the fields of
              // this message are the same and skip it otherwise delete it.
              dump ("Published message already exists in the inbox, not updating\n");
              //continue;
              skipAddition = true;
            }
          }
        }

        if (draftsDB)
        {
          var header = draftsDB.getMsgHdrForMessageID(post.messageId);
          if (header) // There is already a message with messageId, we need to update it
          {
            if (post.postStatus == "publish")
            { // This post should be in published folder, so delete from here
              draftsDB.DeleteHeader(header, null, true, true);
            }
            else
            {
              // for now skip this message, later we can check if all the fields of
              // this message are the same and skip it otherwise delete it.
              dump ("Drafts message already exists in the drafts, not updating\n");
              //continue;
              skipAddition = true;
            }
          }
        }
      
        if (!skipAddition)
        {
          if (post.postStatus == "publish" && inboxLocalFolder)
            inboxLocalFolder.addMessage(message);
          if (post.postStatus == "draft" && draftsLocalFolder)
            draftsLocalFolder.addMessage(message);
        }

        // Take care of tagging here
        for each (category in post.categories)
          this_.checkAndAddCategory(category);

        dump ("Title: " + post.title + "\n");
        //dump ("Description: " + post.description + "\n");
      }
    
      /*
       * If the number returned posts is less than the number requested, then it
       * means that all there are no more posts. So, delete all messages in the 
       * folder that with messageId not in the returned posts list
       */
      if (this_.noOfItemsToSync > this_.postCache.length)
        leastPostDate = new Date(0);

      /* Delete messages that have been deleted on the server */
      this_.removeUpstreamDeletedMessages(inboxDB, leastPostDate,
                                          fetchedMessageIds);
      this_.removeUpstreamDeletedMessages(draftsDB, leastPostDate,
                                          fetchedMessageIds);

      /* Update the status text */
      this_.stopBusyMessage(BlogUtils.getString("blog.status.synchronizingDone"),
                            aMsgWindow);
    }
    catch (ex)
    {
      this_.stopBusyMessage(
        BlogUtils.getString("blog.status.synchronizingFailed"), aMsgWindow);
      dump ("Synchronization failed: " + ex + "\n");
    }

    /* Finished Synchronizing */
    this_.isSynchronizing = false;

    return true;
  },

  removeItem: function(message) 
  {
    if (this.isSynchronizing)
    {
      dump ("Currently synchronizing, ignoring remove request" + message.messageId + "\n");
      return;
    }

    var postId = this.getPostIdFromMessageId(message.messageId);

    if (!this.initAPI(null))
      return;

    this.startBusyMessage(BlogUtils.getString("blog.status.unpublishingPost"));

    var xmlRequest = this.blog.deletePost(postId);
    performancing_xmlcall.sendCommand(this.rpcURL, xmlRequest, this.onRemoveItemsResponse, this, "", performancing_xmlcall.processData);
    dump ("removeItem: Request sent" + message.messageId + "\n");
    // TODO: Handle error and call updateItems here
  },

  onRemoveItemResponse: function(responseObject, additionalInfo, isAtom, theGUID)
  {
    dump ("onRemoveItemResponse: response received\n");
    var this_ = additionalInfo;

    if ("faultCode" in responseObject)
    {
      this_.stopBusyMessage(BlogUtils.getString("blog.status.unpublishingPostFailed"));
      return;
    }

    this_.stopBusyMessage(BlogUtils.getString("blog.status.unpublishedPost"));
  },

  addItem: function(message)
  {
    var publish = false; /* Whether to publish or keep as draft */

    /* If this item got added to any other folder other than inbox or drafts
     * We don't care
     */
    var inboxFolder = this.getFolder(nsMsgFolderFlags.Inbox);
    var draftsFolder = this.getFolder(nsMsgFolderFlags.Drafts);
    if (inboxFolder && inboxFolder.folderURL == message.folder.folderURL)
    {
      dump ("Item is in Inbox folder, will be published\n");
      publish = true;
    }
    else if (draftsFolder && draftsFolder.folderURL == message.folder.folderURL)
    {
      dump ("Item is in drafts folder, will not be published\n");
      publish = false;
    }
    else
      return;
    
    /* Check if we are aleady in the process of synchronizing */
    if (this.isSynchronizing)
    {
      /* Check if this call was made when we added this message during sync 
       * operation. If so, perform operations that have been postponed.
       */
      var postId = this.getPostIdFromMessageId(message.messageId);
    
      for each (post in this.postCache)
      {
        // TODO: Do a more proper comparision 
        if (postId == post.postId && 
            publish == (post.postStatus == "publish"))
        {
          this.performPostAddOperations (message, post);
          return;
        }
      }

      dump ("Adding an item " + message.messageId + " when synchronizing? \n");
      return;
    }

    /* This means that a message got landed from some where into a blog
     * folder
     */
    var self = this;

    var categories = [];
    var keywords = message.getStringProperty("keywords");
    if (keywords)
      categories = keywords.split(" ");
    if (categories.length)
      categories = categories.map(gTagService.getTagForKey);

    var publishDate = new Date();
    if (message.date)
      publishDate.setTime(message.date/1000);

    if (!this.useBooleanForPublish)
    {
      if (publish)
        publish = "bool1";
      else
        publish = "bool0";
    }

    var reader = new MessageReader();
    reader.readMessage (message, function (readContent) 
    {
      var body = reader.getBodyFromMessage(readContent);
      if (!self.initAPI(null))
        return false;

      self.startBusyMessage(BlogUtils.getString("blog.status.publishingPost"));

      var xmlRequest = self.blog.newPost(message.subject, body, categories, publishDate, publish);
      performancing_xmlcall.sendCommand(self.rpcURL, xmlRequest, self.onAddItemResponse, self, "", performancing_xmlcall.processData);
      dump ("AddItem: Request sent\n");
      return true;
    });
  },

  onAddItemResponse: function(responseObject, additionalInfo, isAtom, theGUID)
  {
    var this_ = additionalInfo;
    dump ("AddItem: Response received\n");

    if (typeof(responseObject) == "object" && "faultCode" in responseObject)
    {
      // XXX: Show error alert here.
      this_.stopBusyMessage(BlogUtils.getString("blog.status.publishingPostFailed"));
    }
    else
    {
      this_.stopBusyMessage(BlogUtils.getString("blog.status.publishedPost"));
    }

    /* after we made the newPost call, the item would have got assigned a new
     * post id etc. so, resyncing will remove the actual item and get a fresh
     * one.
     */
    this_.updateItems();
  }
};

/*
 *  A class to read a message given its URI
 */
function MessageReader ()
{
  this.scriptableInputStream = null;
}

MessageReader.prototype = 
{
  readMessage: function (message, callback)
  {
    this.callback = callback;
    var uri = message.folder.generateMessageURI(message.messageKey);

    /* Implementing functions from nsMsgUtils.cpp: 
     * GetMessageServiceContractIDForURI and GetMessageServiceFromURI
     */
    var protocol = uri.split(":")[0];
    if (protocol == "file" && uri.indexOf("application/x-message-display") != -1)
      protocol = "mailbox";
    var messageService = Components.classes["@mozilla.org/messenger/messageservice;1?type=" + protocol]
                       .getService(Components.interfaces.nsIMsgMessageService);
    
    // TODO: set the window
    messageService.streamMessage(uri, this, null /*window*/, null, 
                                 false /*convert data*/, null /*filter*/);
  },

  getBodyFromMessage: function(message)
  {
    /* Assuming there will be headers, the first occurance of a \n is
     * where we have the start of the body. Assuming non-multi-part message */
    return message.match(/(?:\r?\n){2}((?:[\s]|.)*)/m)[1];
  },

  QueryInterface: function (aIID)
  {
    if (aIID.equals(Components.interfaces.nsIStreamListener) ||
        aIID.equals(Components.interfaces.nsIRequestObserver) ||
        aIID.equals(Components.interfaces.nsISupports))
      return this;
    throw Components.results.NS_NOINTERFACE;
  },
  
  onStartRequest: function (aRequest, aContext)
  {
    this.contentRead = "";
  },

  onDataAvailable: function (aRequest, aContext, aInputStream, aOffset, aCount)
  {
    if (!this.scriptableInputStream)
    {
      this.scriptableInputStream = Components.classes["@mozilla.org/scriptableinputstream;1"]
        .createInstance(Components.interfaces.nsIScriptableInputStream);
      this.scriptableInputStream.init(aInputStream);
    }

    this.contentRead += this.scriptableInputStream.read(aCount);
  },
  
  onStopRequest: function (aRequest, aContext, aStatusCode)
  {
    this.callback(this.contentRead);
    this.callback = null;
  }
};
