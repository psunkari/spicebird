
var csChatContactListTests = {

  printContact: function (contact, item) {
    return;
    switch(item) {
      case "alias":
        dump("  Alias: " + contact.alias + "\n");
        break;
      case "avatar-token":
        dump("  Avatar: " + contact.avatarToken + "\n");
        break;
      case "presence-status":
        dump("  Presence Status: " + contact.presenceStatus + "\n");
        dump("  Presence Message: " + contact.presenceMessage + "\n");
        dump("  Presence Type: " + contact.presenceType + "\n");
        break;
      default:
        dump("  Account   : " + contact.connectionKey + "\n");
        dump("  Identifier: " + contact.identifier + "\n");
        dump("  Alias     : " + contact.alias + "\n");
        dump("  Avatar    : " + contact.avatarToken + "\n");
        dump("  Presence  : " + contact.presenceStatus + " (" + contact.presenceMessage + ")\n");
    }
  },
  
  onNewContacts: function(contacts) {
    for each (var contact in contacts) {
      dump("Got new contact: " + contact.handle + "\n");
      csChatContactListTests.printContact(contact);
    }
  },
  
  onContactUpdated: function(contact, item) {
    dump("Contact updated: " + contact.identifier + ":" + item + "\n");
    csChatContactListTests.printContact(contact, item);
  },
  
  onNewGroup: function(id, type, members, localPending, remotePending) {
    dump("New Group: " + id + " (" + type + ")\n");
    dump("  Members: " + members + "\n");
    dump("  LocalPending: " + localPending + "\n");
    dump("  RemotePending: " + remotePending + "\n");
  },
  
  onGroupUpdated: function(id, type, add, remove, localPendingAdd, localPendingRemove,
                           remotePendingAdd, remotePendingRemove, details) {
    dump("Group Updated: " + id + " (" + type + ")\n");
    dump("  Added: " + add + "\n");
    dump("  Removed: " + remove + "\n");
    dump("  LocalPending Added: " + localPendingAdd + "\n");
    dump("  LocalPending Removed: " + localPendingRemove + "\n");
    dump("  RemotePending Added: " + remotePendingAdd + "\n");
    dump("  RemotePending Removed: " + remotePendingRemove + "\n");
  },
  
  init: function() {
    var self = this;
    csChatWrapper.registerNewContactsListener(csChatContactListTests.onNewContacts);
    csChatWrapper.registerContactUpdateListener(csChatContactListTests.onContactUpdated);
    csChatWrapper.registerContactGroupUpdateListener(csChatContactListTests.onGroupUpdated);
    csChatWrapper.registerNewContactGroupListener(csChatContactListTests.onNewGroup);
  }
}
