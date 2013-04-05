#ifndef _CS_TELEPATHY_CONNECTIONMANAGERWRAPPER_H_
#define _CS_TELEPATHY_CONNECTIONMANAGERWRAPPER_H_

#include "csITpProxy.h"
#include "csITpConnectionManagerUtils.h"
#include "csTpConnectionManager.h"

class csTpConnectionManagerImp: public csITpProxy,
                                public csITpConnectionManagerUtils,
                                public csTpConnectionManager
{
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPPROXY
  NS_DECL_CSITPCONNECTIONMANAGERUTILS

  NS_SCRIPTABLE NS_IMETHOD CallListProtocols(csITpConnectionManagerListProtocolsCB *cb);
  NS_SCRIPTABLE NS_IMETHOD CallRequestConnection(const nsACString & aProtocol, nsIArray *aParameters, csITpConnectionManagerRequestConnectionCB *cb);

  csTpConnectionManagerImp();

private:
  ~csTpConnectionManagerImp();

protected:
  CS_TELEPATHY_DECL_PROXY
  
  TpDBusDaemon *m_BusDaemon;
};

#endif
