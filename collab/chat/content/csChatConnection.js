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
# The Original Code is Spicebird code.
#
# The Initial Developer of the Original Code is
# Synovel Software Technologies
# Portions created by the Initial Developer are Copyright (C) 2009
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Prasad Sunkari <prasad@synovel.com> (Original Author)
#   Siva Edupuganti <sivakrishna@synovel.com>
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

/* 
 * Wrapper for a telepathy connection.
 */
function csChatConnectionWrapper(connection, ownConnection, accountKey)
{
  this.connection = connection;
  this.ownConnection = ownConnection;
  this.accountKey = ownConnection? accountKey: null;

  // id is the string that is shown with all error reports
  // If we have an associated account, use the account identifier, else
  // identifier of the user on this connection (updated after it is fetched).
  let account = csChatAccountManager.accounts[accountKey];
  this.id = (ownConnection && account)? account.account: null;

  // Contact handle => csITpContact
  this.contacts = {};

  // Channel targetID => csITpChannel
  this.contactGroups = {};

  // Channel targetID => csITpChannel
  this.contactLists = {};

  // Contact handle => Object (with the following members)
  //  groups is an array of groupID's
  this.contactsMetaInfo = {};

  // Channel targetID => Object (with the following members)
  //   localPending: Array of local pending members
  //   remotePending: Array of remote pending members
  //   members: Array of members of this group
  this.contactGroupsMetaInfo = {};
  this.contactListsMetaInfo = {};

  // List of functions waiting on creation of a channel.
  // Private: should not be used by code external to this object
  this._waitingForContactListQueue = [];

  // Spicebird statuses => Statuses supported on this connection
  // Private: should not be used by code external to this object
  this._knownStatusIds = null;

  // We need csITpProxy to get the objectPath (also the unique key)
  connection.QueryInterface(Ci.csITpProxy);

  // We need csITpConnectionUtils to see if the connection is ready
  connection.QueryInterface(Ci.csITpConnectionUtils);

  // Connect to the signals on Telepathy Connection.
  connection.QueryInterface(Ci.csITpConnection);
  connection.connectToStatusChanged(this);
  connection.connectToConnectionError(this);
  connection.connectToSelfHandleChanged(this);

  // If we own this connection, we would not have called connect on it yet.
  // Also, we should be requesting to connect with presence set to the
  // current global presence.
  if (ownConnection)
    connection.callWhenInterfacesReady(this);
  
  var self = this;
  var connectionReadyCB = {
    onConnectionReady: function() {
      self.init();
    },
    onConnectionReadyError: function(domain, code, desc) {}
  }
  connection.callWhenReady(connectionReadyCB);
}

csChatConnectionWrapper.prototype = {
  get key() {
    return this.connection.objectPath;
  },

  init: function() {
    // Requests may not be present in older implementations
    if (this.connection instanceof Ci.csITpConnectionInterfaceRequests) {
      this.connection.getPropertyChannels(this);
      this.connection.connectToNewChannels(this);
    }

    this.selfHandle = this.connection.selfHandle;
    this.addContactHandles([this.selfHandle], null);

    if (this.connection instanceof Ci.csITpConnectionInterfaceSimplePresence) {
      this.connection.getPropertyStatuses(this);
    }

   /*
    if (this.connection instanceof Ci.csITpConnectionInterfaceAliasing) {
      let account = csChatAccountManager.accounts[this.accountKey];
      this.updateUserAlias(this.selfHandle, account.localNick? account.localNick: this.id);
    }
    */
  },

  disconnect: function() {
    this.connection.callDisconnect(null);
  },

  destroy: function() {
    if (this.ownConnection)
      this.connection.callDisconnect(null);

    // Disconnect from various signals we subscribed to.
    this.connection.disconnectFromStatusChanged(this);
    this.connection.disconnectFromConnectionError(this);
    this.connection.disconnectFromSelfHandleChanged(this);
    this.connection.disconnectFromNewChannels(this);

    // Free the cached contacts
    this.contacts = []

    this.connection = null;
  },

  // If presence is supported by the connection even before
  // actually connecting to the server, set the initial presence.
  onConnectionInterfacesReady: function() {
    if (this.connection instanceof Ci.csITpConnectionInterfaceSimplePresence)
      this.connection.getPropertyStatuses(this);
    else
      this.connection.callConnect(null);
  },

  // Fallback to not having set initial presence.
  onConnectionInterfacesReadyError: function(domain, code, desc) {
    this.connection.callConnect(null);
  },

  isChannelSupported: function(aChannelType, aTargetHandleType) {
    return true;
  },

  requestChannel: function(aChannelType, aTargetHandleType, aTargetHandle) {
    if (!this.connection instanceof Ci.csITpConnectionInterfaceRequests)
      return;

    if (!this.isChannelSupported(aChannelType, aTargetHandleType))
      return;

    var values = Cc["@mozilla.org/array;1"].createInstance(Ci.nsIMutableArray);
    
    var value = new csChatTpChannelParam("ChannelType", aChannelType);
    values.appendElement(value, false);
    
    value = new csChatTpChannelParam("TargetHandleType", aTargetHandleType);
    values.appendElement(value, false);

    value = new csChatTpChannelParam("TargetHandle", aTargetHandle);
    values.appendElement(value, false);

    // Request the channel.
    // XXX: Currently, we are ignoring the return values of the call and
    // instead handle the NewChannels signal.  Soon, we will have to make
    // a distinction between channels that we requested and others.
    this.connection.callCreateChannel(values, null);
  },

  // Test if we have a known, supported status of that type and
  // set it on the connecton. Return false if we could not find one.
  setPresenceStatus: function(aOnlineStatus, aStatusMessage) {
    if (!this._knownStatusIds)
      return false;

    var supported = this._knownStatusIds[aOnlineStatus];
    if (!supported)
      return false;

    var match = aOnlineStatus;
    var index = supported.indexOf(aOnlineStatus);
    if (index == -1)
      match = this._knownStatusIds[aOnlineStatus][0];

    this.connection.callSetPresence(match, aStatusMessage, null);
  },

  getPropertyStatusesDone: function(statuses) {
    var enumerator = statuses.enumerate();
    this._knownStatusIds = {};

    while(enumerator.hasMoreElements()) {
      var status = enumerator.getNext().QueryInterface(Ci.csITpSimpleStatusSpecMap);
      var spec = status.spec.QueryInterface(Ci.csITpSimpleStatusSpec);
      if (spec.maySetOnSelf) {
        var knownStatusId = csChatWrapper.statusMap[status.identifier];
        if (knownStatusId) {
          if (this._knownStatusIds[knownStatusId])
            this._knownStatusIds[knownStatusId].push(status.identifier);
          else
            this._knownStatusIds[knownStatusId] = [status.identifier];
        }
      }
    }

    // If the connection status is disconnected and has no status reason
    // we try to connect with the csChatWrapper's global status
    if (this.connection.status == Ci.csITpConnection.Connection_Status_Disconnected &&
        this.connection.statusReason == Ci.csITpConnection.Connection_Status_Reason_None_Specified) {
      this.setPresenceStatus(csChatWrapper.presence.requestedStatus,
                             csChatWrapper.presence.requestedMessage);
      this.connection.callConnect(null);
    }
  },
  getPropertyStatusesError: function(domain, code, desc) {
    csChatWrapper.reportError(csChatWrapper.NOTIFICATION_INFO,
                              ["GetPropertyStatuses", this.id], domain, code);
  },

  // Channels property of the requests interface
  getPropertyChannelsDone: function(channels) {
    this.dispatchChannels(channels, true);
  },
  getPropertyChannelsError: function(code, desc) {
    csChatWrapper.reportError(csChatWrapper.NOTIFICATION_INFO,
                              ["GetPropertyChannels", this.id], domain, code);
  },

  onNewChannels: function(channels) {
    this.dispatchChannels(channels, false);
  },

  onStatusChanged: function(status, reason) {
    csChatWrapper.connectionStateChanged(this.key, status, reason);
  },

  connectionError: null,
  onConnectionError: function(error, details) {
    // Strip off "org.freedesktop.Telepathy.Error." from the error string.
    this.connectionError = {error: error.slice(32), details: details};
  },

  onSelfHandleChanged: function(handle) {
    csChatWrapper.connectionHandleChanged(this.key, handle);
  },

  // NewChannels signal observer for requests interface
  dispatchChannels: function(channels, startup) {
    var enumerator = channels.enumerate();
    while (enumerator.hasMoreElements()) {
      var channel = enumerator.getNext().QueryInterface(Ci.csITpChannelDetails);
      var type = "";

      var properties = channel.properties.enumerate();
      while (properties.hasMoreElements()) {
        var property = properties.getNext().QueryInterface(Ci.csITpQualifiedPropertyValueMap);
        if (property.key == "org.freedesktop.Telepathy.Channel.ChannelType") {
          type = property.value.split(".")[5];
          break;
        }
      }

      // Pass it on to the handlers.
      for each (var handler in csChatWrapper.getChannelHandlers(type))
        handler.apply(this, [channel, startup]);
    }
  },

  // Private: Not to be used by code outside this class.
  // Return array of elements in A that are not present in B
  _diff: function(one, two) {
    var A = (typeof one == 'object')? one: [];
    var B = (typeof two == 'object')? two: [];

    return [x for each (x in A) if (B.indexOf(x) < 0)];
  },

  // Runs in the scope of the connection (which is myself)
  contactListHandler: function(channelDetails, startup) {
    var properties = {};
    var propertiesEnumerator = channelDetails.properties.enumerate();
    while (propertiesEnumerator.hasMoreElements()) {
      var property = propertiesEnumerator.getNext()
                                         .QueryInterface(Ci.csITpQualifiedPropertyValueMap);
      properties[property.key] = property.value;
    }

    var targetHandleType = properties["org.freedesktop.Telepathy.Channel.TargetHandleType"];
    var targetHandle = properties["org.freedesktop.Telepathy.Channel.TargetHandle"];
    var targetId = properties["org.freedesktop.Telepathy.Channel.TargetID"];

    if (targetHandleType != Ci.csITpConnection.Handle_Type_List &&
        targetHandleType != Ci.csITpConnection.Handle_Type_Group)
      return;

    var channel = Components.classes["@synovel.com/collab/telepathy/channel;1"]
                            .createInstance(Ci.csITpChannelUtils);
    channel.init(this.connection.objectPath, channelDetails.channel,
                 "org.freedesktop.Telepathy.Channel.ChannelType.ContactList",
                 targetHandleType, targetHandle);

    var isServerDefined = (targetHandleType == Ci.csITpConnection.Handle_Type_List);

    var self = this;
    var channelReadyCB = {
      onChannelReady: function() {
        var members = channel.getGroupMembers({});
        var localPending = channel.getGroupLocalPending({});
        var remotePending = channel.getGroupRemotePending({});

        // Cache the channel object and some meta information about them.
        var metaInfo = { properties: properties, members: members,
                         localPending: localPending, remotePending: remotePending };

        var onContactsAdded = function() {
          if (isServerDefined) {
            self.contactLists[targetId] = channel;
            self.contactListsMetaInfo[targetId] = metaInfo;
          }
          else {
            self.contactGroups[targetId] = channel;
            self.contactGroupsMetaInfo[targetId] = metaInfo;

            for each (var member in members)
              self._addGroupToCachedContact(member, targetId);
          }

          for each (var handler in csChatWrapper.getNewContactGroupListeners())
            handler.apply(self, [targetId, targetHandleType,
                                 members, localPending, remotePending]);

          self._handleLocalPending(targetId, targetHandleType, localPending);
        }
        self.addContactHandles(members.concat(localPending)
                                      .concat(remotePending), onContactsAdded);

        var updateObserver = {
          onMembersChangedDetailed: function(addedCount, added,
                  removedCount, removed, localPendingCount, localPending,
                  remotePendingCount, remotePending, details) {

            var info = isServerDefined? self.contactListsMetaInfo[targetId]:
                                        self.contactGroupsMetaInfo[targetId];

            // Calculate differences on both local and remote pending contacts.
            var localPendingAdded     = self._diff(localPending, info.localPending);
            var localPendingRemoved   = self._diff(info.localPending, localPending);
            var remotePendingAdded    = self._diff(remotePending, info.remotePending);
            var remotePendingRemoved  = self._diff(info.remotePending, remotePending);

            // Cache the current pending lists
            info.localPending = localPending;
            info.remotePending = remotePending;

            // Update contacts if the update is on a user-defined group
            if (!isServerDefined) {
              for each (var member in added)
                self._addGroupToCachedContact(member, targetId);

              for each (var member in removed)
                self._removeGroupFromCachedContact(member, targetId);
            }

            var newHandles = added.concat(localPendingAdded).concat(remotePendingAdded);
            var onContactsAdded = function() {
              for each (var handler in csChatWrapper.getContactGroupUpdateListeners())
                handler.apply(self, [targetId, targetHandleType, added,
                                     removed, localPendingAdded, localPendingRemoved,
                                     remotePendingAdded, remotePendingRemoved]);
                
              self._handleLocalPending(targetId, targetHandleType, localPendingAdded);
            }

            self.addContactHandles(newHandles, onContactsAdded);
          }
        }

        var closeObserver = {
          onClosed: function() {
            for each (var handler in csChatWrapper.getContactGroupDeleteListeners())
              handler.apply(self, [targetId, targetHandleType]);
          }
        }

        channel.QueryInterface(Ci.csITpChannelInterfaceGroup);
        channel.connectToMembersChangedDetailed(updateObserver);

        channel.QueryInterface(Ci.csITpChannel);
        channel.connectToClosed(closeObserver);

        // Execute any tasks that are waiting for this channel to be ready.
        var newQueue = [];
        for each(var task in self._waitingForContactListQueue) {
          if (task.targetHandleType == targetHandleType && 
             (task.targetId == targetId || task.targetHandle == targetHandle)) {
            task.handler.apply(self, [channel]);

            if (!task.keepInQueue)
              continue;
          } 

          newQueue.push(task);
        }
        self._waitingForContactListQueue = newQueue;
      }
    }
    channel.callWhenReady(channelReadyCB);
  },

  _handleLocalPending: function(contactListId, contactListType, handles) {
    var self = this;
    var afterUserPrompt = function(contact, result) {
      if (result != 0 && result != 2)
        return;

      var channel = contactListType == Ci.csITpConnection.Handle_Type_List?
                    self.contactLists[contactListId]: self.contactGroups[contactListId];

      if (result == 0)
        channel.callAddMembers(1, [contact.handle], null, null);
      else
        channel.callRemoveMembers(1, [contact.handle], null, null);

      // XXX: Unsure if this is required.
      // If we accepted a subscription request, lets also subscribe to that contact.
      if (contactListType == Ci.csITpConnection.Handle_Type_List &&
          contactListId == 'publish' && result == 0 && self.contactLists['subscribe']) {
        self.contactLists['subscribe'].callAddMembers(1, [contact.handle], null, null);
      }
    }

    for each (var handle in handles)
      csChatWrapper.showSubscriptionRequest(this, this.contacts[handle], afterUserPrompt);
  },

  /* Private: Add group to cached contact meta info */
  _addGroupToCachedContact: function(handle, groupId) {
    if (this.contactsMetaInfo[handle] === undefined)
      this.contactsMetaInfo[handle] = {};

    if (this.contactsMetaInfo[handle].groups === undefined)
      this.contactsMetaInfo[handle].groups = [];

    this.contactsMetaInfo[handle].groups.push(groupId);
  },

  /* Private: Remove group from cached contact meta info */
  _removeGroupFromCachedContact: function(handle, groupId) {
    var groups = this.contactsMetaInfo[handle].groups;
    groups.splice(groups.indexOf(groupId), 1);
  },

  onContactUpdate: function(contact, type) {
    // Presence updates always come thrice - status, type and message.
    // All three are emitted together after the TpContact struct is updated.
    if (type == "presence-type" || type == "presence-message")
      return;

    if (contact.handle == this.selfHandle)
      csChatWrapper.myDetailsUpdated(contact, type);

    for each (var handler in csChatWrapper.getContactUpdateListeners())
      handler.apply(this, [contact, type]);
  },

  updateUserAlias: function(handle, alias) {
      // Create a handle-alias pair
      var handleAliasPair = {
        QueryInterface: function(aIID) {
          if (!aIID.equals(Components.interfaces.csITpAliasMap) &&
              !aIID.equals(Components.interfaces.nsISupports))
            throw Components.results.NS_ERROR_NO_INTERFACE;
    
          return this;
        },
        get handle() { return handle; },
        get alias() { return alias; }
      }

      var aliases = Cc["@mozilla.org/array;1"].createInstance(Ci.nsIMutableArray);
      aliases.appendElement(handleAliasPair, false);

      // Call back for set alias
      var SetAliasesCB = {
        onSetAliasesDone: function() {},
        onSetAliasesError: function(domain, code, desc) {
          csChatWrapper.reportError(csChatWrapper.NOTIFICATION_INFO,
                                    ["SetAliasError", alias], domain, code);
        }
      }
      this.connection.callSetAliases(aliases, SetAliasesCB);
  },

  /*
   * Given the contact handle, update the contact. Currently we only
   * support setting alias and adding user to the groups.
   * XXX: Check for the aliasing flags to see if we can set an alias or not!
   *
   * @handle is the contacts handle
   * @details is an object with changes (alias, groups as keys)
   */
  updateContact: function(handle, details) {
    if (!details)
      return;

    var self = this;

    // If we have aliasing, and an alias was passed update the alias.
    if (this.connection instanceof Ci.csITpConnectionInterfaceAliasing && details.alias)
      this.updateUserAlias(handle, details.alias);

    // Finally, see if any group informatio was passed.  If yes, update groups.
    // TODO: Check if the connection supports groups at all
    if (!details.groups)
      return;

    // Do we have info for this contact?  If not start with empty groups.
    var currentGroups = this.contactsMetaInfo[handle]?
                        this.contactsMetaInfo[handle].groups: [];

    var groupsAdded = this._diff(details.groups, currentGroups);
    var groupsRemoved = this._diff(currentGroups, details.groups);

    for each (var groupId in groupsAdded) {
      var channel = this.contactGroups[groupId]
      if (channel) {
        channel.callAddMembers(1, [handle], null, null);
      } else {
        var GotHandles = {
          onRequestHandlesDone: function(count, handles) {
            if (count != 1)
              return;

            // Let adding to group be done when the channel is ready
            self._waitingForContactListQueue.push({
              targetId: groupId,
              targetHandleType: Ci.csITpConnection.Handle_Type_Group,
              handler: function(channel) {
                if (channel)
                  channel.callAddMembers(1, [handle], null, null);
              }
            })

            // Request channel
            self.requestChannel("org.freedesktop.Telepathy.Channel.Type.ContactList",
                                Ci.csITpConnection.Handle_Type_Group, handles[0]);
          },
          onRequestHandlesError: function(domain, code, desc) {
            csChatWrapper.reportError(csChatWrapper.NOTIFICATION_WARNING,
                                      ["CreateNewGroup", groupId], domain, code);
          }
        }
        this.connection.callRequestHandles(Ci.csITpConnection.Handle_Type_Group,
                                           1, [groupId], GotHandles);
      }
    }

    for each (var groupId in groupsRemoved) {
      var channel = this.contactGroups[groupId]
      if (channel)
        channel.callRemoveMembers(1, [handle], null, null);
    }
  },

  /*
   * Add a new contact. Request a handle for the new contact and add
   * it to the "subscribe" channel.  Also call updateContact to
   * set other attributes to that contact (alias & groups)
   *
   * @details is an object with details about the new contact containing
   *          username: The account id of the new user
   *          alias: Optional alias to be set on the user
   *          groups: Groups into which the user should be added
   */
  addContact: function(details) {
    if (!details || !details.identifier || details.identifier == "")
      return;

    var self = this;
    var GotHandles = {
      onRequestHandlesDone: function(count, handles) {
        if (count != 1)
          return;

        // Request subscription
        var channel = self.contactLists["subscribe"]
        if (channel)
          channel.callAddMembers(1, [handles[0]], null, null);

        // Update other details of this user
        self.updateContact(handles[0], details);
      },
      onRequestHandlesError: function(domain, code, desc) {
        csChatWrapper.reportError(csChatWrapper.NOTIFICATION_WARNING,
                                  ["AddContact", details.identifier, self.id],
                                  domain, code);
      }
    }
    this.connection.callRequestHandles(Ci.csITpConnection.Handle_Type_Contact,
                                       1, [details.identifier], GotHandles);
  },

  /* 
   * Remove a contact - stop sending your presence information to the contact
   * as well as unsubscribe from the users presence notifications.
   *
   * @handle is the target contact's handle.
   */
  removeContact: function(handle) {
    var publish = this.contactLists["publish"];
    if (publish)
      publish.callRemoveMembers(1, [handle], null, null);

    var subscribe = this.contactLists["subscribe"];
    if (subscribe)
      subscribe.callRemoveMembers(1, [handle], null, null);
  },

  myself: null,
  addContactHandles: function(members, postGotContacts) {
    var self = this;
    var toRequest = members.filter(function(element, index, arr) {
                                     return !self.contacts[element];
                                   })

    if (toRequest.length == 0)
      return postGotContacts();

    var getContactsByHandleCB = {
      onGetContactsByHandleDone: function(contacts, failedCount, failed) {
        var enumerator = contacts.enumerate();
        var newContacts = [];
     
        while (enumerator.hasMoreElements()) {
          var contact = enumerator.getNext().QueryInterface(Ci.csITpContact);
          if (!self.contacts[contact.handle]) {
            contact.addUpdateObserver(self);
            if (contact.handle == self.selfHandle) {
              self.myself = contact;
              if (!self.ownConnection)
                self.id = contact.identifier

              csChatWrapper.myDetailsUpdated(contact, 'presence-status');
            }
            
            newContacts.push(contact);
            self.contacts[contact.handle] = contact;
          }
        }
     
        if (newContacts.length > 0)
          for each (var handler in csChatWrapper.getNewContactsListeners())
            handler.apply(self, [newContacts]);

        // Notify contact group listeners
        if (postGotContacts && typeof postGotContacts == "function")
          postGotContacts();
      },
      
      onGetContactsByHandleError: function(domain, code, desc) {
        csChatWrapper.reportError(csChatWrapper.NOTIFICATION_WARNING,
                                  ["GetContactsByHandle", self.id], domain, code);
      }
    }

    var features = [Ci.csITpContact.Contact_Feature_Alias,
                    Ci.csITpContact.Contact_Feature_Avatar_Token,
                    Ci.csITpContact.Contact_Feature_Presence];
    this.connection.getContactsByHandle(toRequest.length, toRequest,
                                        3, features, getContactsByHandleCB);
  }
}

/*
 * Helper for passing parameter when creating a connection
 */
function csChatTpChannelParam(key, value) {
  this._key = "org.freedesktop.Telepathy.Channel." + key;
  this._value = value;
}
csChatTpChannelParam.prototype = {
  get key() { return this._key; },
  get value() { return this._value; },
  QueryInterface: function(aIID) {
    if (!aIID.equals(Ci.csITpQualifiedPropertyValueMap) &&
        !aIID.equals(Ci.nsISupports))
      throw Components.results.NS_ERROR_NO_INTERFACE;
    return this;
  }
}

