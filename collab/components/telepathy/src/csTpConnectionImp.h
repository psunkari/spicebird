#ifndef _CS_TELEPATHY_CONNECTIONWRAPPER_H_
#define _CS_TELEPATHY_CONNECTIONWRAPPER_H_

#include "csITpProxy.h"
#include "csITpConnectionUtils.h"

#include "csTpConnection.h"
#include "csTpConnectionInterfaceAvatars.h"
#include "csTpConnectionInterfaceAliasing.h"
#include "csTpConnectionInterfaceCapabilities.h"
#include "csTpConnectionInterfaceContactCapabilities.h"
#include "csTpConnectionInterfaceContacts.h"
#include "csTpConnectionInterfaceLocation.h"
#include "csTpConnectionInterfacePresence.h"
#include "csTpConnectionInterfaceRequests.h"
#include "csTpConnectionInterfaceSimplePresence.h"

#include "telepathy-glib/contact.h"

class csTpConnectionImp: public csITpProxy, public csITpConnectionUtils,
                         public csTpConnection,
                         public csTpConnectionInterfaceAvatars,
                         public csTpConnectionInterfaceAliasing,
                         public csTpConnectionInterfaceCapabilities,
                         public csTpConnectionInterfaceContactCapabilities,
                         public csTpConnectionInterfaceContacts,
                         public csTpConnectionInterfaceLocation,
                         public csTpConnectionInterfacePresence,
                         public csTpConnectionInterfaceRequests,
                         public csTpConnectionInterfaceSimplePresence
{
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPPROXY
  NS_DECL_CSITPCONNECTIONUTILS

  csTpConnectionImp();

  NS_SCRIPTABLE NS_IMETHOD
  CallCreateChannel(nsIArray *aRequest,
                    csITpConnectionInterfaceRequestsCreateChannelCB *cb);

  NS_SCRIPTABLE NS_IMETHOD
  CallSetAliases(nsIArray *aAliasesMap,
                 csITpConnectionInterfaceAliasingSetAliasesCB *cb);

  void HandleEarlyGotInterfaces(const gchar **interfaces, const GError *error);

private:
  ~csTpConnectionImp();

protected:
  TpDBusDaemon *m_BusDaemon;
  nsCOMPtr<nsIMutableArray> m_InterfacesReadyObservers;
  CS_TELEPATHY_DECL_PROXY
};

class csTpContact: public csITpContact
{
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPCONTACT

  static NS_METHOD Create(TpContact *contact, const nsACString &aObjectPath,
                          csITpContact** aContact);
  void HandleUpdate(TpContact *contact, GParamSpec *spec);

private:
  csTpContact(TpContact *contact, const nsACString &aObjectPath);
  ~csTpContact();

protected:
  TpContact *m_Contact;
  nsCString  m_ConnectionKey;  // ObjPath
  nsCOMPtr<nsIMutableArray> m_UpdateObservers;

};

#endif
