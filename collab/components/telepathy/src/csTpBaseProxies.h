#ifndef _CSTPBASEPROXIES_H_
#define _CSTPBASEPROXIES_H_

#include "telepathy-glib/connection-manager.h"
#include "telepathy-glib/connection.h"
#include "telepathy-glib/channel-dispatch-operation.h"
#include "telepathy-glib/channel-dispatcher.h"
#include "telepathy-glib/channel-request.h"
#include "telepathy-glib/channel.h"

class _csTpConnectionManagerProxyBase
{
  protected:
    TpConnectionManager *m_Proxy;
};

class _csTpConnectionProxyBase
{
  protected:
    TpConnection *m_Proxy;
};

class _csTpChannelProxyBase
{
  protected:
    TpChannel *m_Proxy;
};

class _csTpChannelDispatcherProxyBase
{
  protected:
    TpChannelDispatcher *m_Proxy;
};

class _csTpChannelDispatchOperationProxyBase
{
  protected:
    TpChannelDispatchOperation *m_Proxy;
};

class _csTpChannelRequestProxyBase
{
  protected:
    TpChannelRequest *m_Proxy;
};

#endif
