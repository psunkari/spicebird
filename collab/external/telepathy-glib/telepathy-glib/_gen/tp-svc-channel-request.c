#include "_gen/tp-svc-channel-request.h"

#include <telepathy-glib/dbus.h>
#include "_gen/signals-marshal.h"

static const DBusGObjectInfo _tp_svc_channel_request_object_info;

struct _TpSvcChannelRequestClass {
    GTypeInterface parent_class;
    tp_svc_channel_request_proceed_impl proceed;
    tp_svc_channel_request_cancel_impl cancel;
};

enum {
    SIGNAL_CHANNEL_REQUEST_Failed,
    SIGNAL_CHANNEL_REQUEST_Succeeded,
    N_CHANNEL_REQUEST_SIGNALS
};
static guint channel_request_signals[N_CHANNEL_REQUEST_SIGNALS] = {0};

static void tp_svc_channel_request_base_init (gpointer klass);

GType
tp_svc_channel_request_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelRequestClass),
        tp_svc_channel_request_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelRequest", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_request_proceed_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Proceed on interface org.freedesktop.Telepathy.ChannelRequest.
 */
static void
tp_svc_channel_request_proceed (TpSvcChannelRequest *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_request_proceed_impl impl = (TP_SVC_CHANNEL_REQUEST_GET_CLASS (self)->proceed);

  if (impl != NULL)
    {
      (impl) (self,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_request_implement_proceed:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Proceed D-Bus method
 *
 * Register an implementation for the Proceed method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_request_implement_proceed (TpSvcChannelRequestClass *klass, tp_svc_channel_request_proceed_impl impl)
{
  klass->proceed = impl;
}

/**
 * tp_svc_channel_request_cancel_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Cancel on interface org.freedesktop.Telepathy.ChannelRequest.
 */
static void
tp_svc_channel_request_cancel (TpSvcChannelRequest *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_request_cancel_impl impl = (TP_SVC_CHANNEL_REQUEST_GET_CLASS (self)->cancel);

  if (impl != NULL)
    {
      (impl) (self,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_request_implement_cancel:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Cancel D-Bus method
 *
 * Register an implementation for the Cancel method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_request_implement_cancel (TpSvcChannelRequestClass *klass, tp_svc_channel_request_cancel_impl impl)
{
  klass->cancel = impl;
}

/**
 * tp_svc_channel_request_emit_failed:
 * @instance: The object implementing this interface
 * @arg_Error: const gchar * (FIXME, generate documentation)
 * @arg_Message: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * Failed signal on interface org.freedesktop.Telepathy.ChannelRequest.
 */
void
tp_svc_channel_request_emit_failed (gpointer instance,
    const gchar *arg_Error,
    const gchar *arg_Message)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_REQUEST));
  g_signal_emit (instance,
      channel_request_signals[SIGNAL_CHANNEL_REQUEST_Failed],
      0,
      arg_Error,
      arg_Message);
}

/**
 * tp_svc_channel_request_emit_succeeded:
 * @instance: The object implementing this interface
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * Succeeded signal on interface org.freedesktop.Telepathy.ChannelRequest.
 */
void
tp_svc_channel_request_emit_succeeded (gpointer instance)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_REQUEST));
  g_signal_emit (instance,
      channel_request_signals[SIGNAL_CHANNEL_REQUEST_Succeeded],
      0);
}

static inline void
tp_svc_channel_request_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[6] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "o", 0, NULL, NULL }, /* Account */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "x", 0, NULL, NULL }, /* UserActionTime */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "s", 0, NULL, NULL }, /* PreferredHandler */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "aa{sv}", 0, NULL, NULL }, /* Requests */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "as", 0, NULL, NULL }, /* Interfaces */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_channel_request_get_type (),
      &_tp_svc_channel_request_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.ChannelRequest");
  properties[0].name = g_quark_from_static_string ("Account");
  properties[0].type = DBUS_TYPE_G_OBJECT_PATH;
  properties[1].name = g_quark_from_static_string ("UserActionTime");
  properties[1].type = G_TYPE_INT64;
  properties[2].name = g_quark_from_static_string ("PreferredHandler");
  properties[2].type = G_TYPE_STRING;
  properties[3].name = g_quark_from_static_string ("Requests");
  properties[3].type = (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE))));
  properties[4].name = g_quark_from_static_string ("Interfaces");
  properties[4].type = G_TYPE_STRV;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CHANNEL_REQUEST, &interface);

  /**
   * TpSvcChannelRequest::failed:
   * @arg_Error: const gchar * (FIXME, generate documentation)
   * @arg_Message: const gchar * (FIXME, generate documentation)
   *
   * The Failed D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_request_signals[SIGNAL_CHANNEL_REQUEST_Failed] =
  g_signal_new ("failed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__STRING_STRING,
      G_TYPE_NONE,
      2,
      G_TYPE_STRING,
      G_TYPE_STRING);

  /**
   * TpSvcChannelRequest::succeeded:
   *
   * The Succeeded D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_request_signals[SIGNAL_CHANNEL_REQUEST_Succeeded] =
  g_signal_new ("succeeded",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__VOID,
      G_TYPE_NONE,
      0);

}
static void
tp_svc_channel_request_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_request_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_request_methods[] = {
  { (GCallback) tp_svc_channel_request_proceed, g_cclosure_marshal_VOID__POINTER, 0 },
  { (GCallback) tp_svc_channel_request_cancel, g_cclosure_marshal_VOID__POINTER, 52 },
};

static const DBusGObjectInfo _tp_svc_channel_request_object_info = {
  0,
  _tp_svc_channel_request_methods,
  2,
"org.freedesktop.Telepathy.ChannelRequest\0Proceed\0A\0\0org.freedesktop.Telepathy.ChannelRequest\0Cancel\0A\0\0\0",
"org.freedesktop.Telepathy.ChannelRequest\0Failed\0org.freedesktop.Telepathy.ChannelRequest\0Succeeded\0\0",
"\0\0",
};


