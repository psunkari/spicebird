#include <glib-object.h>
#include <dbus/dbus-glib.h>
#include <telepathy-glib/dbus-properties-mixin.h>

G_BEGIN_DECLS

/**
 * TpSvcChannelRequest:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelRequest TpSvcChannelRequest;

/**
 * TpSvcChannelRequestClass:
 *
 * The class of TpSvcChannelRequest.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_request (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_request_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (proceed);
 *   IMPLEMENT (cancel);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelRequestClass TpSvcChannelRequestClass;

GType tp_svc_channel_request_get_type (void);
#define TP_TYPE_SVC_CHANNEL_REQUEST \
  (tp_svc_channel_request_get_type ())
#define TP_SVC_CHANNEL_REQUEST(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_REQUEST, TpSvcChannelRequest))
#define TP_IS_SVC_CHANNEL_REQUEST(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_REQUEST))
#define TP_SVC_CHANNEL_REQUEST_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_REQUEST, TpSvcChannelRequestClass))


typedef void (*tp_svc_channel_request_proceed_impl) (TpSvcChannelRequest *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_request_implement_proceed (TpSvcChannelRequestClass *klass, tp_svc_channel_request_proceed_impl impl);
/**
 * tp_svc_channel_request_return_from_proceed:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_request_return_from_proceed (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_request_return_from_proceed (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_channel_request_cancel_impl) (TpSvcChannelRequest *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_request_implement_cancel (TpSvcChannelRequestClass *klass, tp_svc_channel_request_cancel_impl impl);
/**
 * tp_svc_channel_request_return_from_cancel:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_request_return_from_cancel (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_request_return_from_cancel (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

void tp_svc_channel_request_emit_failed (gpointer instance,
    const gchar *arg_Error,
    const gchar *arg_Message);
void tp_svc_channel_request_emit_succeeded (gpointer instance);


G_END_DECLS
