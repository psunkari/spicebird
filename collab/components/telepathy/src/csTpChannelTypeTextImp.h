#ifndef _CS_TELEPATHY_CHANNELTYPETEXTWRAPPER_H_
#define _CS_TELEPATHY_CHANNELTYPETEXTWRAPPER_H_

#include "csTpChannelImp.h"

#include "csTpChannelTypeText.h"
#include "csTpChannelInterfaceChatState.h"
#include "csTpChannelInterfaceDestroyable.h"
#include "csTpChannelInterfaceMessages.h"

class csTpChannelTypeTextImp: public csTpChannelImp,
                              public csTpChannelTypeText,
                              public csTpChannelInterfaceChatState,
                              public csTpChannelInterfaceDestroyable,
                              public csTpChannelInterfaceMessages
{
  NS_DECL_ISUPPORTS

  csTpChannelTypeTextImp();

private:
  ~csTpChannelTypeTextImp();
};

#endif
