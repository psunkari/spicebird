#ifndef _CS_TELEPATHY_CHANNELWRAPPER_H_
#define _CS_TELEPATHY_CHANNELWRAPPER_H_

#include "csITpChannelUtils.h"
#include "csITpProxy.h"
#include "csTpChannel.h"
#include "csTpChannelInterfaceGroup.h"
#include "csTpChannelInterfacePassword.h"

class csTpChannelImp: public csITpChannelUtils, public csITpProxy,
                      public csTpChannel,
                      public csTpChannelInterfaceGroup,
                      public csTpChannelInterfacePassword
{
  NS_DECL_ISUPPORTS
  NS_DECL_CSITPPROXY
  NS_DECL_CSITPCHANNELUTILS

  csTpChannelImp();

protected:
  ~csTpChannelImp();

  TpDBusDaemon *m_BusDaemon;
  TpConnection *m_Connection;
  CS_TELEPATHY_DECL_PROXY
};

#endif
