#include <glib-object.h>
#include <dbus/dbus-glib.h>
#include <telepathy-glib/dbus-properties-mixin.h>

G_BEGIN_DECLS

/**
 * TpSvcChannelDispatcher:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelDispatcher TpSvcChannelDispatcher;

/**
 * TpSvcChannelDispatcherClass:
 *
 * The class of TpSvcChannelDispatcher.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_dispatcher (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_dispatcher_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (create_channel);
 *   IMPLEMENT (ensure_channel);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelDispatcherClass TpSvcChannelDispatcherClass;

GType tp_svc_channel_dispatcher_get_type (void);
#define TP_TYPE_SVC_CHANNEL_DISPATCHER \
  (tp_svc_channel_dispatcher_get_type ())
#define TP_SVC_CHANNEL_DISPATCHER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_DISPATCHER, TpSvcChannelDispatcher))
#define TP_IS_SVC_CHANNEL_DISPATCHER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_DISPATCHER))
#define TP_SVC_CHANNEL_DISPATCHER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_DISPATCHER, TpSvcChannelDispatcherClass))


typedef void (*tp_svc_channel_dispatcher_create_channel_impl) (TpSvcChannelDispatcher *self,
    const gchar *in_Account,
    GHashTable *in_Requested_Properties,
    gint64 in_User_Action_Time,
    const gchar *in_Preferred_Handler,
    DBusGMethodInvocation *context);
void tp_svc_channel_dispatcher_implement_create_channel (TpSvcChannelDispatcherClass *klass, tp_svc_channel_dispatcher_create_channel_impl impl);
/**
 * tp_svc_channel_dispatcher_return_from_create_channel:
 * @context: The D-Bus method invocation context
 * @out_Request: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_dispatcher_return_from_create_channel (DBusGMethodInvocation *context,
    const gchar *out_Request);
static inline void
tp_svc_channel_dispatcher_return_from_create_channel (DBusGMethodInvocation *context,
    const gchar *out_Request)
{
  dbus_g_method_return (context,
      out_Request);
}

typedef void (*tp_svc_channel_dispatcher_ensure_channel_impl) (TpSvcChannelDispatcher *self,
    const gchar *in_Account,
    GHashTable *in_Requested_Properties,
    gint64 in_User_Action_Time,
    const gchar *in_Preferred_Handler,
    DBusGMethodInvocation *context);
void tp_svc_channel_dispatcher_implement_ensure_channel (TpSvcChannelDispatcherClass *klass, tp_svc_channel_dispatcher_ensure_channel_impl impl);
/**
 * tp_svc_channel_dispatcher_return_from_ensure_channel:
 * @context: The D-Bus method invocation context
 * @out_Request: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_dispatcher_return_from_ensure_channel (DBusGMethodInvocation *context,
    const gchar *out_Request);
static inline void
tp_svc_channel_dispatcher_return_from_ensure_channel (DBusGMethodInvocation *context,
    const gchar *out_Request)
{
  dbus_g_method_return (context,
      out_Request);
}


/**
 * TpSvcChannelDispatcherInterfaceOperationList:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelDispatcherInterfaceOperationList TpSvcChannelDispatcherInterfaceOperationList;

/**
 * TpSvcChannelDispatcherInterfaceOperationListClass:
 *
 * The class of TpSvcChannelDispatcherInterfaceOperationList.
 * This interface has no D-Bus methods, so an
 * implementation can typically pass %NULL to
 * G_IMPLEMENT_INTERFACE() as the interface
 * initialization function.
 */
typedef struct _TpSvcChannelDispatcherInterfaceOperationListClass TpSvcChannelDispatcherInterfaceOperationListClass;

GType tp_svc_channel_dispatcher_interface_operation_list_get_type (void);
#define TP_TYPE_SVC_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST \
  (tp_svc_channel_dispatcher_interface_operation_list_get_type ())
#define TP_SVC_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST, TpSvcChannelDispatcherInterfaceOperationList))
#define TP_IS_SVC_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST))
#define TP_SVC_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST, TpSvcChannelDispatcherInterfaceOperationListClass))


void tp_svc_channel_dispatcher_interface_operation_list_emit_new_dispatch_operation (gpointer instance,
    const gchar *arg_Dispatch_Operation,
    GHashTable *arg_Properties);
void tp_svc_channel_dispatcher_interface_operation_list_emit_dispatch_operation_finished (gpointer instance,
    const gchar *arg_Dispatch_Operation);


G_END_DECLS
