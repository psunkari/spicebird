#include <glib-object.h>
#include <dbus/dbus-glib.h>
#include <telepathy-glib/dbus-properties-mixin.h>

G_BEGIN_DECLS

/**
 * TpSvcChannelDispatchOperation:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelDispatchOperation TpSvcChannelDispatchOperation;

/**
 * TpSvcChannelDispatchOperationClass:
 *
 * The class of TpSvcChannelDispatchOperation.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_dispatch_operation (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_dispatch_operation_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (handle_with);
 *   IMPLEMENT (claim);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelDispatchOperationClass TpSvcChannelDispatchOperationClass;

GType tp_svc_channel_dispatch_operation_get_type (void);
#define TP_TYPE_SVC_CHANNEL_DISPATCH_OPERATION \
  (tp_svc_channel_dispatch_operation_get_type ())
#define TP_SVC_CHANNEL_DISPATCH_OPERATION(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_DISPATCH_OPERATION, TpSvcChannelDispatchOperation))
#define TP_IS_SVC_CHANNEL_DISPATCH_OPERATION(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_DISPATCH_OPERATION))
#define TP_SVC_CHANNEL_DISPATCH_OPERATION_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_DISPATCH_OPERATION, TpSvcChannelDispatchOperationClass))


typedef void (*tp_svc_channel_dispatch_operation_handle_with_impl) (TpSvcChannelDispatchOperation *self,
    const gchar *in_Handler,
    DBusGMethodInvocation *context);
void tp_svc_channel_dispatch_operation_implement_handle_with (TpSvcChannelDispatchOperationClass *klass, tp_svc_channel_dispatch_operation_handle_with_impl impl);
/**
 * tp_svc_channel_dispatch_operation_return_from_handle_with:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_dispatch_operation_return_from_handle_with (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_dispatch_operation_return_from_handle_with (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_channel_dispatch_operation_claim_impl) (TpSvcChannelDispatchOperation *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_dispatch_operation_implement_claim (TpSvcChannelDispatchOperationClass *klass, tp_svc_channel_dispatch_operation_claim_impl impl);
/**
 * tp_svc_channel_dispatch_operation_return_from_claim:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_dispatch_operation_return_from_claim (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_dispatch_operation_return_from_claim (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

void tp_svc_channel_dispatch_operation_emit_channel_lost (gpointer instance,
    const gchar *arg_Channel,
    const gchar *arg_Error,
    const gchar *arg_Message);
void tp_svc_channel_dispatch_operation_emit_finished (gpointer instance);


G_END_DECLS
