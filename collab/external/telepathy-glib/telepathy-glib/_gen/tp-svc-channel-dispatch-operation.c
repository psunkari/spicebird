#include "_gen/tp-svc-channel-dispatch-operation.h"

#include <telepathy-glib/dbus.h>
#include "_gen/signals-marshal.h"

static const DBusGObjectInfo _tp_svc_channel_dispatch_operation_object_info;

struct _TpSvcChannelDispatchOperationClass {
    GTypeInterface parent_class;
    tp_svc_channel_dispatch_operation_handle_with_impl handle_with;
    tp_svc_channel_dispatch_operation_claim_impl claim;
};

enum {
    SIGNAL_CHANNEL_DISPATCH_OPERATION_ChannelLost,
    SIGNAL_CHANNEL_DISPATCH_OPERATION_Finished,
    N_CHANNEL_DISPATCH_OPERATION_SIGNALS
};
static guint channel_dispatch_operation_signals[N_CHANNEL_DISPATCH_OPERATION_SIGNALS] = {0};

static void tp_svc_channel_dispatch_operation_base_init (gpointer klass);

GType
tp_svc_channel_dispatch_operation_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelDispatchOperationClass),
        tp_svc_channel_dispatch_operation_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelDispatchOperation", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_dispatch_operation_handle_with_impl:
 * @self: The object implementing this interface
 * @in_Handler: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * HandleWith on interface org.freedesktop.Telepathy.ChannelDispatchOperation.
 */
static void
tp_svc_channel_dispatch_operation_handle_with (TpSvcChannelDispatchOperation *self,
    const gchar *in_Handler,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_dispatch_operation_handle_with_impl impl = (TP_SVC_CHANNEL_DISPATCH_OPERATION_GET_CLASS (self)->handle_with);

  if (impl != NULL)
    {
      (impl) (self,
        in_Handler,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_dispatch_operation_implement_handle_with:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the HandleWith D-Bus method
 *
 * Register an implementation for the HandleWith method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_dispatch_operation_implement_handle_with (TpSvcChannelDispatchOperationClass *klass, tp_svc_channel_dispatch_operation_handle_with_impl impl)
{
  klass->handle_with = impl;
}

/**
 * tp_svc_channel_dispatch_operation_claim_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Claim on interface org.freedesktop.Telepathy.ChannelDispatchOperation.
 */
static void
tp_svc_channel_dispatch_operation_claim (TpSvcChannelDispatchOperation *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_dispatch_operation_claim_impl impl = (TP_SVC_CHANNEL_DISPATCH_OPERATION_GET_CLASS (self)->claim);

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
 * tp_svc_channel_dispatch_operation_implement_claim:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Claim D-Bus method
 *
 * Register an implementation for the Claim method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_dispatch_operation_implement_claim (TpSvcChannelDispatchOperationClass *klass, tp_svc_channel_dispatch_operation_claim_impl impl)
{
  klass->claim = impl;
}

/**
 * tp_svc_channel_dispatch_operation_emit_channel_lost:
 * @instance: The object implementing this interface
 * @arg_Channel: const gchar * (FIXME, generate documentation)
 * @arg_Error: const gchar * (FIXME, generate documentation)
 * @arg_Message: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * ChannelLost signal on interface org.freedesktop.Telepathy.ChannelDispatchOperation.
 */
void
tp_svc_channel_dispatch_operation_emit_channel_lost (gpointer instance,
    const gchar *arg_Channel,
    const gchar *arg_Error,
    const gchar *arg_Message)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_DISPATCH_OPERATION));
  g_signal_emit (instance,
      channel_dispatch_operation_signals[SIGNAL_CHANNEL_DISPATCH_OPERATION_ChannelLost],
      0,
      arg_Channel,
      arg_Error,
      arg_Message);
}

/**
 * tp_svc_channel_dispatch_operation_emit_finished:
 * @instance: The object implementing this interface
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * Finished signal on interface org.freedesktop.Telepathy.ChannelDispatchOperation.
 */
void
tp_svc_channel_dispatch_operation_emit_finished (gpointer instance)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_DISPATCH_OPERATION));
  g_signal_emit (instance,
      channel_dispatch_operation_signals[SIGNAL_CHANNEL_DISPATCH_OPERATION_Finished],
      0);
}

static inline void
tp_svc_channel_dispatch_operation_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[6] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "as", 0, NULL, NULL }, /* Interfaces */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "o", 0, NULL, NULL }, /* Connection */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "o", 0, NULL, NULL }, /* Account */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "a(oa{sv})", 0, NULL, NULL }, /* Channels */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "as", 0, NULL, NULL }, /* PossibleHandlers */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_channel_dispatch_operation_get_type (),
      &_tp_svc_channel_dispatch_operation_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.ChannelDispatchOperation");
  properties[0].name = g_quark_from_static_string ("Interfaces");
  properties[0].type = G_TYPE_STRV;
  properties[1].name = g_quark_from_static_string ("Connection");
  properties[1].type = DBUS_TYPE_G_OBJECT_PATH;
  properties[2].name = g_quark_from_static_string ("Account");
  properties[2].type = DBUS_TYPE_G_OBJECT_PATH;
  properties[3].name = g_quark_from_static_string ("Channels");
  properties[3].type = (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID))));
  properties[4].name = g_quark_from_static_string ("PossibleHandlers");
  properties[4].type = G_TYPE_STRV;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CHANNEL_DISPATCH_OPERATION, &interface);

  /**
   * TpSvcChannelDispatchOperation::channel-lost:
   * @arg_Channel: const gchar * (FIXME, generate documentation)
   * @arg_Error: const gchar * (FIXME, generate documentation)
   * @arg_Message: const gchar * (FIXME, generate documentation)
   *
   * The ChannelLost D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_dispatch_operation_signals[SIGNAL_CHANNEL_DISPATCH_OPERATION_ChannelLost] =
  g_signal_new ("channel-lost",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__BOXED_STRING_STRING,
      G_TYPE_NONE,
      3,
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_STRING,
      G_TYPE_STRING);

  /**
   * TpSvcChannelDispatchOperation::finished:
   *
   * The Finished D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_dispatch_operation_signals[SIGNAL_CHANNEL_DISPATCH_OPERATION_Finished] =
  g_signal_new ("finished",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__VOID,
      G_TYPE_NONE,
      0);

}
static void
tp_svc_channel_dispatch_operation_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_dispatch_operation_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_dispatch_operation_methods[] = {
  { (GCallback) tp_svc_channel_dispatch_operation_handle_with, _tp_marshal_VOID__STRING_POINTER, 0 },
  { (GCallback) tp_svc_channel_dispatch_operation_claim, g_cclosure_marshal_VOID__POINTER, 77 },
};

static const DBusGObjectInfo _tp_svc_channel_dispatch_operation_object_info = {
  0,
  _tp_svc_channel_dispatch_operation_methods,
  2,
"org.freedesktop.Telepathy.ChannelDispatchOperation\0HandleWith\0A\0Handler\0I\0s\0\0org.freedesktop.Telepathy.ChannelDispatchOperation\0Claim\0A\0\0\0",
"org.freedesktop.Telepathy.ChannelDispatchOperation\0ChannelLost\0org.freedesktop.Telepathy.ChannelDispatchOperation\0Finished\0\0",
"\0\0",
};


