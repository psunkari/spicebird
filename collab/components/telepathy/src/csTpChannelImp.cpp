#include "csTpChannelImp.h"
#include "csTpGenericTypes.h"
#include "csTelepathyMacros.h"

#include "nsMemory.h"

#define NS_INTERFACE_TABLE_TAIL                                               \
    CS_TELEPATHY_INTERFACE_LIST_BEGIN                                         \
    CS_TELEPATHY_INTERFACE_ITEM(csITpChannelInterfaceGroup,                   \
      "org.freedesktop.Telepathy.Channel.Interface.Group")                    \
    CS_TELEPATHY_INTERFACE_ITEM(csITpChannelInterfacePassword,                \
      "org.freedesktop.Telepathy.Channel.Interface.Password")                 \
    CS_TELEPATHY_INTERFACE_LIST_END

NS_IMPL_ISUPPORTS5(csTpChannelImp, csITpProxy, csITpChannelUtils, csITpChannel, \
  csITpChannelInterfaceGroup, csITpChannelInterfacePassword)

csTpChannelImp::csTpChannelImp()
{
  m_BusDaemon = tp_dbus_daemon_new(tp_get_bus());
  m_Proxy = NULL;
  
  CS_TELEPATHY_INIT_PROXY
}

csTpChannelImp::~csTpChannelImp()
{
  if (m_Proxy)
    g_object_unref(m_Proxy);

  m_Proxy = NULL;
}

NS_IMETHODIMP
csTpChannelImp::InitWithDetails(csITpChannelDetails *aChannelDetails)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
csTpChannelImp::Init(const nsACString &aConnectionObjectPath,
                     const nsACString &aObjectPath, const nsACString &aChannelType,
                     PRUint32 aHandleType, PRUint32 aHandle)
{
  if (m_Proxy)
    return NS_ERROR_ALREADY_INITIALIZED;

  GError *error = NULL;

  m_Connection = tp_connection_new(m_BusDaemon, NULL,
                                   nsCString(aConnectionObjectPath).get(), &error);
  if (!m_Connection) {
    g_print("ERROR: %s\n", error->message);
    return NS_ERROR_OUT_OF_MEMORY;
  }

  m_Proxy = tp_channel_new(m_Connection, nsCString(aObjectPath).get(),
                           nsCString(aChannelType).get(),
                           (TpHandleType)aHandleType, aHandle, &error);
  if (!m_Proxy) {
    g_print("ERROR: %s\n", error->message);
    return NS_ERROR_OUT_OF_MEMORY;
  }

  return NS_OK;
}

static void
ChannelReady(TpChannel *proxy, const GError *error, gpointer user_data)
{
  csITpChannelReadyCB *callback = (csITpChannelReadyCB *)user_data;

  if (error != NULL) {
    callback->OnChannelReadyError(nsDependentCString(g_quark_to_string(error->domain)),
                                  error->code, nsDependentCString(error->message));
    return;
  }

  callback->OnChannelReady();
  NS_IF_RELEASE(callback);
}

NS_IMETHODIMP
csTpChannelImp::CallWhenReady(csITpChannelReadyCB *cb)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  NS_IF_ADDREF(cb);
  tp_channel_call_when_ready(m_Proxy, ChannelReady, cb);

  return NS_OK;
}

NS_IMETHODIMP
csTpChannelImp::GetGroupHandleOwner(PRUint32 aHandle, PRUint32 *aOwnerHandle)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
csTpChannelImp::GetGroupMembers(PRUint32 *aMembersCount, PRUint32 **aMembers)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  nsresult rv = SupportsInterface("org.freedesktop.Telepathy.Channel.Interface.Group");
  NS_ENSURE_SUCCESS(rv, rv);

  const TpIntSet *members = tp_channel_group_get_members(m_Proxy);
  PRUint32 *handles = (PRUint32*)nsMemory::Alloc(sizeof(PRUint32) * tp_intset_size(members));
  
  PRUint32 counter = 0;
  TpIntSetIter iter = TP_INTSET_ITER_INIT(members);
  while(tp_intset_iter_next(&iter))
    handles[counter++] = iter.element;

  *aMembersCount = counter;
  *aMembers = handles;
  return NS_OK;
}

NS_IMETHODIMP
csTpChannelImp::GetGroupLocalPending(PRUint32 *aMembersCount, PRUint32 **aMembers)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  nsresult rv = SupportsInterface("org.freedesktop.Telepathy.Channel.Interface.Group");
  NS_ENSURE_SUCCESS(rv, rv);

  const TpIntSet *members = tp_channel_group_get_local_pending(m_Proxy);
  PRUint32 *handles = (PRUint32*)nsMemory::Alloc(sizeof(PRUint32) * tp_intset_size(members));
  
  PRUint32 counter = 0;
  TpIntSetIter iter = TP_INTSET_ITER_INIT(members);
  while(tp_intset_iter_next(&iter))
    handles[counter++] = iter.element;

  *aMembersCount = counter;
  *aMembers = handles;
  return NS_OK;
}

NS_IMETHODIMP
csTpChannelImp::GetGroupRemotePending(PRUint32 *aMembersCount, PRUint32 **aMembers)
{
  if (!m_Proxy)
    return NS_ERROR_NOT_INITIALIZED;

  nsresult rv = SupportsInterface("org.freedesktop.Telepathy.Channel.Interface.Group");
  NS_ENSURE_SUCCESS(rv, rv);

  const TpIntSet *members = tp_channel_group_get_remote_pending(m_Proxy);
  PRUint32 *handles = (PRUint32*)nsMemory::Alloc(sizeof(PRUint32) * tp_intset_size(members));
  
  PRUint32 counter = 0;
  TpIntSetIter iter = TP_INTSET_ITER_INIT(members);
  while(tp_intset_iter_next(&iter))
    handles[counter++] = iter.element;

  *aMembersCount = counter;
  *aMembers = handles;
  return NS_OK;
}

NS_IMETHODIMP
csTpChannelImp::GetGroupLocalPendingInfo(PRUint32 aHandle, PRUint32 *aActor,
                                         PRUint32 *aReason, char **aMessage,
                                         PRBool *_retval)
{
  return NS_ERROR_NOT_IMPLEMENTED;
}
  
NS_IMETHODIMP
csTpChannelImp::GetChannelReady(PRBool *aChannelReady)
{
  g_object_get(m_Proxy, "channel-ready", aChannelReady, NULL);
  return NS_OK;
}

NS_IMETHODIMP
csTpChannelImp::GetChannelProperties(nsIArray **aProperties)
{
  GHashTable *properties;
  g_object_get(m_Proxy, "channel-properties", &properties, NULL);

  nsCOMPtr<nsIArray> array;
  csTpQualifiedPropertyValueMap::Create(properties, getter_AddRefs(array));

  NS_ADDREF(*aProperties = array);
  return NS_OK;
}

NS_IMETHODIMP
csTpChannelImp::GetGroupFlags(PRUint32 *aGroupFlags)
{
  g_object_get(m_Proxy, "group-flags", aGroupFlags, NULL);
  return NS_OK;
}

NS_IMETHODIMP
csTpChannelImp::GetGroupSelfHandle(PRUint32 *aSelfHandle)
{
  g_object_get(m_Proxy, "group-self-handle", aSelfHandle, NULL);
  return NS_OK;
}

NS_IMETHODIMP
csTpChannelImp::GetIdentifier(nsACString &aIdentifier)
{
  char *ident;
  g_object_get(m_Proxy, "identifier", &ident, NULL);
  aIdentifier.Assign(ident);
  return NS_OK;
}

NS_IMETHODIMP
csTpChannelImp::GetConnectionObjectPath(nsACString &aObjectPath)
{
  TpConnection *connection;
  g_object_get(m_Proxy, "connection", &connection, NULL);

  char *objectPath;
  g_object_get(connection, "object-path", &objectPath, NULL);
  aObjectPath.Assign(objectPath);

  return NS_OK;
}

CS_TELEPATHY_IMPL_PROXY(csTpChannelImp, m_Proxy);
