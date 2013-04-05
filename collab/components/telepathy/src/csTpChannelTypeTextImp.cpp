#include "csTpChannelImp.h"
#include "csTpChannelTypeTextImp.h"
#include "csTelepathyMacros.h"

#define NS_INTERFACE_TABLE_TAIL                                               \
    CS_TELEPATHY_INTERFACE_LIST_BEGIN                                         \
    CS_TELEPATHY_INTERFACE_ITEM(csITpChannelInterfaceGroup,                   \
      "org.freedesktop.Telepathy.Channel.Interface.Group")                    \
    CS_TELEPATHY_INTERFACE_ITEM(csITpChannelInterfaceChatState,               \
      "org.freedesktop.Telepathy.Channel.Interface.ChatState")                \
    CS_TELEPATHY_INTERFACE_ITEM(csITpChannelInterfaceMessages,                \
      "org.freedesktop.Telepathy.Channel.Interface.Messages")                 \
    CS_TELEPATHY_INTERFACE_ITEM(csITpChannelInterfacePassword,                \
      "org.freedesktop.Telepathy.Channel.Interface.Password")                 \
    CS_TELEPATHY_INTERFACE_ITEM(csITpChannelInterfaceDestroyable,             \
      "org.freedesktop.Telepathy.Channel.Interface.Destroyable")              \
    CS_TELEPATHY_INTERFACE_LIST_END

NS_IMPL_ISUPPORTS8(csTpChannelTypeTextImp,csITpChannelUtils,                    \
  csITpChannel,csITpChannelTypeText,csITpChannelInterfaceGroup,               \
  csITpChannelInterfaceChatState,csITpChannelInterfaceMessages,               \
  csITpChannelInterfacePassword,csITpChannelInterfaceDestroyable);

csTpChannelTypeTextImp::csTpChannelTypeTextImp()
{
}

csTpChannelTypeTextImp::~csTpChannelTypeTextImp()
{
}
