#include "_gen/tp-svc-connection.h"

#include <telepathy-glib/dbus.h>
#include "_gen/signals-marshal.h"

static const DBusGObjectInfo _tp_svc_connection_object_info;

struct _TpSvcConnectionClass {
    GTypeInterface parent_class;
    tp_svc_connection_connect_impl connect;
    tp_svc_connection_disconnect_impl disconnect;
    tp_svc_connection_get_interfaces_impl get_interfaces;
    tp_svc_connection_get_protocol_impl get_protocol;
    tp_svc_connection_get_self_handle_impl get_self_handle;
    tp_svc_connection_get_status_impl get_status;
    tp_svc_connection_hold_handles_impl hold_handles;
    tp_svc_connection_inspect_handles_impl inspect_handles;
    tp_svc_connection_list_channels_impl list_channels;
    tp_svc_connection_release_handles_impl release_handles;
    tp_svc_connection_request_channel_impl request_channel;
    tp_svc_connection_request_handles_impl request_handles;
};

enum {
    SIGNAL_CONNECTION_SelfHandleChanged,
    SIGNAL_CONNECTION_NewChannel,
    SIGNAL_CONNECTION_ConnectionError,
    SIGNAL_CONNECTION_StatusChanged,
    N_CONNECTION_SIGNALS
};
static guint connection_signals[N_CONNECTION_SIGNALS] = {0};

static void tp_svc_connection_base_init (gpointer klass);

GType
tp_svc_connection_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcConnectionClass),
        tp_svc_connection_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcConnection", &info, 0);
    }

  return type;
}

/**
 * tp_svc_connection_connect_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Connect on interface org.freedesktop.Telepathy.Connection.
 */
static void
tp_svc_connection_connect (TpSvcConnection *self,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_connect_impl impl = (TP_SVC_CONNECTION_GET_CLASS (self)->connect);

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
 * tp_svc_connection_implement_connect:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Connect D-Bus method
 *
 * Register an implementation for the Connect method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_implement_connect (TpSvcConnectionClass *klass, tp_svc_connection_connect_impl impl)
{
  klass->connect = impl;
}

/**
 * tp_svc_connection_disconnect_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Disconnect on interface org.freedesktop.Telepathy.Connection.
 */
static void
tp_svc_connection_disconnect (TpSvcConnection *self,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_disconnect_impl impl = (TP_SVC_CONNECTION_GET_CLASS (self)->disconnect);

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
 * tp_svc_connection_implement_disconnect:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Disconnect D-Bus method
 *
 * Register an implementation for the Disconnect method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_implement_disconnect (TpSvcConnectionClass *klass, tp_svc_connection_disconnect_impl impl)
{
  klass->disconnect = impl;
}

/**
 * tp_svc_connection_get_interfaces_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetInterfaces on interface org.freedesktop.Telepathy.Connection.
 */
static void
tp_svc_connection_get_interfaces (TpSvcConnection *self,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_get_interfaces_impl impl = (TP_SVC_CONNECTION_GET_CLASS (self)->get_interfaces);

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
 * tp_svc_connection_implement_get_interfaces:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetInterfaces D-Bus method
 *
 * Register an implementation for the GetInterfaces method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_implement_get_interfaces (TpSvcConnectionClass *klass, tp_svc_connection_get_interfaces_impl impl)
{
  klass->get_interfaces = impl;
}

/**
 * tp_svc_connection_get_protocol_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetProtocol on interface org.freedesktop.Telepathy.Connection.
 */
static void
tp_svc_connection_get_protocol (TpSvcConnection *self,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_get_protocol_impl impl = (TP_SVC_CONNECTION_GET_CLASS (self)->get_protocol);

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
 * tp_svc_connection_implement_get_protocol:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetProtocol D-Bus method
 *
 * Register an implementation for the GetProtocol method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_implement_get_protocol (TpSvcConnectionClass *klass, tp_svc_connection_get_protocol_impl impl)
{
  klass->get_protocol = impl;
}

/**
 * tp_svc_connection_get_self_handle_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetSelfHandle on interface org.freedesktop.Telepathy.Connection.
 */
static void
tp_svc_connection_get_self_handle (TpSvcConnection *self,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_get_self_handle_impl impl = (TP_SVC_CONNECTION_GET_CLASS (self)->get_self_handle);

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
 * tp_svc_connection_implement_get_self_handle:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetSelfHandle D-Bus method
 *
 * Register an implementation for the GetSelfHandle method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_implement_get_self_handle (TpSvcConnectionClass *klass, tp_svc_connection_get_self_handle_impl impl)
{
  klass->get_self_handle = impl;
}

/**
 * tp_svc_connection_get_status_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetStatus on interface org.freedesktop.Telepathy.Connection.
 */
static void
tp_svc_connection_get_status (TpSvcConnection *self,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_get_status_impl impl = (TP_SVC_CONNECTION_GET_CLASS (self)->get_status);

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
 * tp_svc_connection_implement_get_status:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetStatus D-Bus method
 *
 * Register an implementation for the GetStatus method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_implement_get_status (TpSvcConnectionClass *klass, tp_svc_connection_get_status_impl impl)
{
  klass->get_status = impl;
}

/**
 * tp_svc_connection_hold_handles_impl:
 * @self: The object implementing this interface
 * @in_Handle_Type: guint  (FIXME, generate documentation)
 * @in_Handles: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * HoldHandles on interface org.freedesktop.Telepathy.Connection.
 */
static void
tp_svc_connection_hold_handles (TpSvcConnection *self,
    guint in_Handle_Type,
    const GArray *in_Handles,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_hold_handles_impl impl = (TP_SVC_CONNECTION_GET_CLASS (self)->hold_handles);

  if (impl != NULL)
    {
      (impl) (self,
        in_Handle_Type,
        in_Handles,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_implement_hold_handles:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the HoldHandles D-Bus method
 *
 * Register an implementation for the HoldHandles method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_implement_hold_handles (TpSvcConnectionClass *klass, tp_svc_connection_hold_handles_impl impl)
{
  klass->hold_handles = impl;
}

/**
 * tp_svc_connection_inspect_handles_impl:
 * @self: The object implementing this interface
 * @in_Handle_Type: guint  (FIXME, generate documentation)
 * @in_Handles: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * InspectHandles on interface org.freedesktop.Telepathy.Connection.
 */
static void
tp_svc_connection_inspect_handles (TpSvcConnection *self,
    guint in_Handle_Type,
    const GArray *in_Handles,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_inspect_handles_impl impl = (TP_SVC_CONNECTION_GET_CLASS (self)->inspect_handles);

  if (impl != NULL)
    {
      (impl) (self,
        in_Handle_Type,
        in_Handles,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_implement_inspect_handles:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the InspectHandles D-Bus method
 *
 * Register an implementation for the InspectHandles method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_implement_inspect_handles (TpSvcConnectionClass *klass, tp_svc_connection_inspect_handles_impl impl)
{
  klass->inspect_handles = impl;
}

/**
 * tp_svc_connection_list_channels_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * ListChannels on interface org.freedesktop.Telepathy.Connection.
 */
static void
tp_svc_connection_list_channels (TpSvcConnection *self,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_list_channels_impl impl = (TP_SVC_CONNECTION_GET_CLASS (self)->list_channels);

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
 * tp_svc_connection_implement_list_channels:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the ListChannels D-Bus method
 *
 * Register an implementation for the ListChannels method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_implement_list_channels (TpSvcConnectionClass *klass, tp_svc_connection_list_channels_impl impl)
{
  klass->list_channels = impl;
}

/**
 * tp_svc_connection_release_handles_impl:
 * @self: The object implementing this interface
 * @in_Handle_Type: guint  (FIXME, generate documentation)
 * @in_Handles: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * ReleaseHandles on interface org.freedesktop.Telepathy.Connection.
 */
static void
tp_svc_connection_release_handles (TpSvcConnection *self,
    guint in_Handle_Type,
    const GArray *in_Handles,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_release_handles_impl impl = (TP_SVC_CONNECTION_GET_CLASS (self)->release_handles);

  if (impl != NULL)
    {
      (impl) (self,
        in_Handle_Type,
        in_Handles,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_implement_release_handles:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the ReleaseHandles D-Bus method
 *
 * Register an implementation for the ReleaseHandles method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_implement_release_handles (TpSvcConnectionClass *klass, tp_svc_connection_release_handles_impl impl)
{
  klass->release_handles = impl;
}

/**
 * tp_svc_connection_request_channel_impl:
 * @self: The object implementing this interface
 * @in_Type: const gchar * (FIXME, generate documentation)
 * @in_Handle_Type: guint  (FIXME, generate documentation)
 * @in_Handle: guint  (FIXME, generate documentation)
 * @in_Suppress_Handler: gboolean  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RequestChannel on interface org.freedesktop.Telepathy.Connection.
 */
static void
tp_svc_connection_request_channel (TpSvcConnection *self,
    const gchar *in_Type,
    guint in_Handle_Type,
    guint in_Handle,
    gboolean in_Suppress_Handler,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_request_channel_impl impl = (TP_SVC_CONNECTION_GET_CLASS (self)->request_channel);

  if (impl != NULL)
    {
      (impl) (self,
        in_Type,
        in_Handle_Type,
        in_Handle,
        in_Suppress_Handler,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_implement_request_channel:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RequestChannel D-Bus method
 *
 * Register an implementation for the RequestChannel method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_implement_request_channel (TpSvcConnectionClass *klass, tp_svc_connection_request_channel_impl impl)
{
  klass->request_channel = impl;
}

/**
 * tp_svc_connection_request_handles_impl:
 * @self: The object implementing this interface
 * @in_Handle_Type: guint  (FIXME, generate documentation)
 * @in_Identifiers: const gchar ** (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RequestHandles on interface org.freedesktop.Telepathy.Connection.
 */
static void
tp_svc_connection_request_handles (TpSvcConnection *self,
    guint in_Handle_Type,
    const gchar **in_Identifiers,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_request_handles_impl impl = (TP_SVC_CONNECTION_GET_CLASS (self)->request_handles);

  if (impl != NULL)
    {
      (impl) (self,
        in_Handle_Type,
        in_Identifiers,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_implement_request_handles:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RequestHandles D-Bus method
 *
 * Register an implementation for the RequestHandles method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_implement_request_handles (TpSvcConnectionClass *klass, tp_svc_connection_request_handles_impl impl)
{
  klass->request_handles = impl;
}

/**
 * tp_svc_connection_emit_self_handle_changed:
 * @instance: The object implementing this interface
 * @arg_Self_Handle: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * SelfHandleChanged signal on interface org.freedesktop.Telepathy.Connection.
 */
void
tp_svc_connection_emit_self_handle_changed (gpointer instance,
    guint arg_Self_Handle)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CONNECTION));
  g_signal_emit (instance,
      connection_signals[SIGNAL_CONNECTION_SelfHandleChanged],
      0,
      arg_Self_Handle);
}

/**
 * tp_svc_connection_emit_new_channel:
 * @instance: The object implementing this interface
 * @arg_Object_Path: const gchar * (FIXME, generate documentation)
 * @arg_Channel_Type: const gchar * (FIXME, generate documentation)
 * @arg_Handle_Type: guint  (FIXME, generate documentation)
 * @arg_Handle: guint  (FIXME, generate documentation)
 * @arg_Suppress_Handler: gboolean  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * NewChannel signal on interface org.freedesktop.Telepathy.Connection.
 */
void
tp_svc_connection_emit_new_channel (gpointer instance,
    const gchar *arg_Object_Path,
    const gchar *arg_Channel_Type,
    guint arg_Handle_Type,
    guint arg_Handle,
    gboolean arg_Suppress_Handler)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CONNECTION));
  g_signal_emit (instance,
      connection_signals[SIGNAL_CONNECTION_NewChannel],
      0,
      arg_Object_Path,
      arg_Channel_Type,
      arg_Handle_Type,
      arg_Handle,
      arg_Suppress_Handler);
}

/**
 * tp_svc_connection_emit_connection_error:
 * @instance: The object implementing this interface
 * @arg_Error: const gchar * (FIXME, generate documentation)
 * @arg_Details: GHashTable * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * ConnectionError signal on interface org.freedesktop.Telepathy.Connection.
 */
void
tp_svc_connection_emit_connection_error (gpointer instance,
    const gchar *arg_Error,
    GHashTable *arg_Details)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CONNECTION));
  g_signal_emit (instance,
      connection_signals[SIGNAL_CONNECTION_ConnectionError],
      0,
      arg_Error,
      arg_Details);
}

/**
 * tp_svc_connection_emit_status_changed:
 * @instance: The object implementing this interface
 * @arg_Status: guint  (FIXME, generate documentation)
 * @arg_Reason: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * StatusChanged signal on interface org.freedesktop.Telepathy.Connection.
 */
void
tp_svc_connection_emit_status_changed (gpointer instance,
    guint arg_Status,
    guint arg_Reason)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CONNECTION));
  g_signal_emit (instance,
      connection_signals[SIGNAL_CONNECTION_StatusChanged],
      0,
      arg_Status,
      arg_Reason);
}

static inline void
tp_svc_connection_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[2] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* SelfHandle */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_connection_get_type (),
      &_tp_svc_connection_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection");
  properties[0].name = g_quark_from_static_string ("SelfHandle");
  properties[0].type = G_TYPE_UINT;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CONNECTION, &interface);

  /**
   * TpSvcConnection::self-handle-changed:
   * @arg_Self_Handle: guint  (FIXME, generate documentation)
   *
   * The SelfHandleChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  connection_signals[SIGNAL_CONNECTION_SelfHandleChanged] =
  g_signal_new ("self-handle-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__UINT,
      G_TYPE_NONE,
      1,
      G_TYPE_UINT);

  /**
   * TpSvcConnection::new-channel:
   * @arg_Object_Path: const gchar * (FIXME, generate documentation)
   * @arg_Channel_Type: const gchar * (FIXME, generate documentation)
   * @arg_Handle_Type: guint  (FIXME, generate documentation)
   * @arg_Handle: guint  (FIXME, generate documentation)
   * @arg_Suppress_Handler: gboolean  (FIXME, generate documentation)
   *
   * The NewChannel D-Bus signal is emitted whenever this GObject signal is.
   */
  connection_signals[SIGNAL_CONNECTION_NewChannel] =
  g_signal_new ("new-channel",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__BOXED_STRING_UINT_UINT_BOOLEAN,
      G_TYPE_NONE,
      5,
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_STRING,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_BOOLEAN);

  /**
   * TpSvcConnection::connection-error:
   * @arg_Error: const gchar * (FIXME, generate documentation)
   * @arg_Details: GHashTable * (FIXME, generate documentation)
   *
   * The ConnectionError D-Bus signal is emitted whenever this GObject signal is.
   */
  connection_signals[SIGNAL_CONNECTION_ConnectionError] =
  g_signal_new ("connection-error",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__STRING_BOXED,
      G_TYPE_NONE,
      2,
      G_TYPE_STRING,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)));

  /**
   * TpSvcConnection::status-changed:
   * @arg_Status: guint  (FIXME, generate documentation)
   * @arg_Reason: guint  (FIXME, generate documentation)
   *
   * The StatusChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  connection_signals[SIGNAL_CONNECTION_StatusChanged] =
  g_signal_new ("status-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT,
      G_TYPE_NONE,
      2,
      G_TYPE_UINT,
      G_TYPE_UINT);

}
static void
tp_svc_connection_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_connection_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_connection_methods[] = {
  { (GCallback) tp_svc_connection_connect, g_cclosure_marshal_VOID__POINTER, 0 },
  { (GCallback) tp_svc_connection_disconnect, g_cclosure_marshal_VOID__POINTER, 48 },
  { (GCallback) tp_svc_connection_get_interfaces, g_cclosure_marshal_VOID__POINTER, 99 },
  { (GCallback) tp_svc_connection_get_protocol, g_cclosure_marshal_VOID__POINTER, 173 },
  { (GCallback) tp_svc_connection_get_self_handle, g_cclosure_marshal_VOID__POINTER, 242 },
  { (GCallback) tp_svc_connection_get_status, g_cclosure_marshal_VOID__POINTER, 316 },
  { (GCallback) tp_svc_connection_hold_handles, _tp_marshal_VOID__UINT_BOXED_POINTER, 381 },
  { (GCallback) tp_svc_connection_inspect_handles, _tp_marshal_VOID__UINT_BOXED_POINTER, 462 },
  { (GCallback) tp_svc_connection_list_channels, g_cclosure_marshal_VOID__POINTER, 567 },
  { (GCallback) tp_svc_connection_release_handles, _tp_marshal_VOID__UINT_BOXED_POINTER, 647 },
  { (GCallback) tp_svc_connection_request_channel, _tp_marshal_VOID__STRING_UINT_UINT_BOOLEAN_POINTER, 731 },
  { (GCallback) tp_svc_connection_request_handles, _tp_marshal_VOID__UINT_BOXED_POINTER, 863 },
};

static const DBusGObjectInfo _tp_svc_connection_object_info = {
  0,
  _tp_svc_connection_methods,
  12,
"org.freedesktop.Telepathy.Connection\0Connect\0A\0\0org.freedesktop.Telepathy.Connection\0Disconnect\0A\0\0org.freedesktop.Telepathy.Connection\0GetInterfaces\0A\0Interfaces\0O\0F\0N\0as\0\0org.freedesktop.Telepathy.Connection\0GetProtocol\0A\0Protocol\0O\0F\0N\0s\0\0org.freedesktop.Telepathy.Connection\0GetSelfHandle\0A\0Self_Handle\0O\0F\0N\0u\0\0org.freedesktop.Telepathy.Connection\0GetStatus\0A\0Status\0O\0F\0N\0u\0\0org.freedesktop.Telepathy.Connection\0HoldHandles\0A\0Handle_Type\0I\0u\0Handles\0I\0au\0\0org.freedesktop.Telepathy.Connection\0InspectHandles\0A\0Handle_Type\0I\0u\0Handles\0I\0au\0Identifiers\0O\0F\0N\0as\0\0org.freedesktop.Telepathy.Connection\0ListChannels\0A\0Channel_Info\0O\0F\0N\0a(osuu)\0\0org.freedesktop.Telepathy.Connection\0ReleaseHandles\0A\0Handle_Type\0I\0u\0Handles\0I\0au\0\0org.freedesktop.Telepathy.Connection\0RequestChannel\0A\0Type\0I\0s\0Handle_Type\0I\0u\0Handle\0I\0u\0Suppress_Handler\0I\0b\0Object_Path\0O\0F\0N\0o\0\0org.freedesktop.Telepathy.Connection\0RequestHandles\0A\0Handle_Type\0I\0u\0Identifiers\0I\0as\0Handles\0O\0F\0N\0au\0\0\0",
"org.freedesktop.Telepathy.Connection\0SelfHandleChanged\0org.freedesktop.Telepathy.Connection\0NewChannel\0org.freedesktop.Telepathy.Connection\0ConnectionError\0org.freedesktop.Telepathy.Connection\0StatusChanged\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_connection_interface_aliasing_object_info;

struct _TpSvcConnectionInterfaceAliasingClass {
    GTypeInterface parent_class;
    tp_svc_connection_interface_aliasing_get_alias_flags_impl get_alias_flags;
    tp_svc_connection_interface_aliasing_request_aliases_impl request_aliases;
    tp_svc_connection_interface_aliasing_get_aliases_impl get_aliases;
    tp_svc_connection_interface_aliasing_set_aliases_impl set_aliases;
};

enum {
    SIGNAL_CONNECTION_INTERFACE_ALIASING_AliasesChanged,
    N_CONNECTION_INTERFACE_ALIASING_SIGNALS
};
static guint connection_interface_aliasing_signals[N_CONNECTION_INTERFACE_ALIASING_SIGNALS] = {0};

static void tp_svc_connection_interface_aliasing_base_init (gpointer klass);

GType
tp_svc_connection_interface_aliasing_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcConnectionInterfaceAliasingClass),
        tp_svc_connection_interface_aliasing_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcConnectionInterfaceAliasing", &info, 0);
    }

  return type;
}

/**
 * tp_svc_connection_interface_aliasing_get_alias_flags_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetAliasFlags on interface org.freedesktop.Telepathy.Connection.Interface.Aliasing.
 */
static void
tp_svc_connection_interface_aliasing_get_alias_flags (TpSvcConnectionInterfaceAliasing *self,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_aliasing_get_alias_flags_impl impl = (TP_SVC_CONNECTION_INTERFACE_ALIASING_GET_CLASS (self)->get_alias_flags);

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
 * tp_svc_connection_interface_aliasing_implement_get_alias_flags:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetAliasFlags D-Bus method
 *
 * Register an implementation for the GetAliasFlags method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_aliasing_implement_get_alias_flags (TpSvcConnectionInterfaceAliasingClass *klass, tp_svc_connection_interface_aliasing_get_alias_flags_impl impl)
{
  klass->get_alias_flags = impl;
}

/**
 * tp_svc_connection_interface_aliasing_request_aliases_impl:
 * @self: The object implementing this interface
 * @in_Contacts: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RequestAliases on interface org.freedesktop.Telepathy.Connection.Interface.Aliasing.
 */
static void
tp_svc_connection_interface_aliasing_request_aliases (TpSvcConnectionInterfaceAliasing *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_aliasing_request_aliases_impl impl = (TP_SVC_CONNECTION_INTERFACE_ALIASING_GET_CLASS (self)->request_aliases);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contacts,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_aliasing_implement_request_aliases:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RequestAliases D-Bus method
 *
 * Register an implementation for the RequestAliases method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_aliasing_implement_request_aliases (TpSvcConnectionInterfaceAliasingClass *klass, tp_svc_connection_interface_aliasing_request_aliases_impl impl)
{
  klass->request_aliases = impl;
}

/**
 * tp_svc_connection_interface_aliasing_get_aliases_impl:
 * @self: The object implementing this interface
 * @in_Contacts: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetAliases on interface org.freedesktop.Telepathy.Connection.Interface.Aliasing.
 */
static void
tp_svc_connection_interface_aliasing_get_aliases (TpSvcConnectionInterfaceAliasing *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_aliasing_get_aliases_impl impl = (TP_SVC_CONNECTION_INTERFACE_ALIASING_GET_CLASS (self)->get_aliases);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contacts,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_aliasing_implement_get_aliases:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetAliases D-Bus method
 *
 * Register an implementation for the GetAliases method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_aliasing_implement_get_aliases (TpSvcConnectionInterfaceAliasingClass *klass, tp_svc_connection_interface_aliasing_get_aliases_impl impl)
{
  klass->get_aliases = impl;
}

/**
 * tp_svc_connection_interface_aliasing_set_aliases_impl:
 * @self: The object implementing this interface
 * @in_Aliases: GHashTable * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SetAliases on interface org.freedesktop.Telepathy.Connection.Interface.Aliasing.
 */
static void
tp_svc_connection_interface_aliasing_set_aliases (TpSvcConnectionInterfaceAliasing *self,
    GHashTable *in_Aliases,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_aliasing_set_aliases_impl impl = (TP_SVC_CONNECTION_INTERFACE_ALIASING_GET_CLASS (self)->set_aliases);

  if (impl != NULL)
    {
      (impl) (self,
        in_Aliases,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_aliasing_implement_set_aliases:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SetAliases D-Bus method
 *
 * Register an implementation for the SetAliases method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_aliasing_implement_set_aliases (TpSvcConnectionInterfaceAliasingClass *klass, tp_svc_connection_interface_aliasing_set_aliases_impl impl)
{
  klass->set_aliases = impl;
}

/**
 * tp_svc_connection_interface_aliasing_emit_aliases_changed:
 * @instance: The object implementing this interface
 * @arg_Aliases: const GPtrArray * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * AliasesChanged signal on interface org.freedesktop.Telepathy.Connection.Interface.Aliasing.
 */
void
tp_svc_connection_interface_aliasing_emit_aliases_changed (gpointer instance,
    const GPtrArray *arg_Aliases)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CONNECTION_INTERFACE_ALIASING));
  g_signal_emit (instance,
      connection_interface_aliasing_signals[SIGNAL_CONNECTION_INTERFACE_ALIASING_AliasesChanged],
      0,
      arg_Aliases);
}

static inline void
tp_svc_connection_interface_aliasing_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_connection_interface_aliasing_get_type (),
      &_tp_svc_connection_interface_aliasing_object_info);

  /**
   * TpSvcConnectionInterfaceAliasing::aliases-changed:
   * @arg_Aliases: const GPtrArray * (FIXME, generate documentation)
   *
   * The AliasesChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  connection_interface_aliasing_signals[SIGNAL_CONNECTION_INTERFACE_ALIASING_AliasesChanged] =
  g_signal_new ("aliases-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,
      1,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID)))));

}
static void
tp_svc_connection_interface_aliasing_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_connection_interface_aliasing_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_connection_interface_aliasing_methods[] = {
  { (GCallback) tp_svc_connection_interface_aliasing_get_alias_flags, g_cclosure_marshal_VOID__POINTER, 0 },
  { (GCallback) tp_svc_connection_interface_aliasing_request_aliases, _tp_marshal_VOID__BOXED_POINTER, 93 },
  { (GCallback) tp_svc_connection_interface_aliasing_get_aliases, _tp_marshal_VOID__BOXED_POINTER, 198 },
  { (GCallback) tp_svc_connection_interface_aliasing_set_aliases, _tp_marshal_VOID__BOXED_POINTER, 302 },
};

static const DBusGObjectInfo _tp_svc_connection_interface_aliasing_object_info = {
  0,
  _tp_svc_connection_interface_aliasing_methods,
  4,
"org.freedesktop.Telepathy.Connection.Interface.Aliasing\0GetAliasFlags\0A\0Alias_Flags\0O\0F\0N\0u\0\0org.freedesktop.Telepathy.Connection.Interface.Aliasing\0RequestAliases\0A\0Contacts\0I\0au\0Aliases\0O\0F\0N\0as\0\0org.freedesktop.Telepathy.Connection.Interface.Aliasing\0GetAliases\0A\0Contacts\0I\0au\0Aliases\0O\0F\0N\0a{us}\0\0org.freedesktop.Telepathy.Connection.Interface.Aliasing\0SetAliases\0A\0Aliases\0I\0a{us}\0\0\0",
"org.freedesktop.Telepathy.Connection.Interface.Aliasing\0AliasesChanged\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_connection_interface_avatars_object_info;

struct _TpSvcConnectionInterfaceAvatarsClass {
    GTypeInterface parent_class;
    tp_svc_connection_interface_avatars_get_avatar_requirements_impl get_avatar_requirements;
    tp_svc_connection_interface_avatars_get_avatar_tokens_impl get_avatar_tokens;
    tp_svc_connection_interface_avatars_get_known_avatar_tokens_impl get_known_avatar_tokens;
    tp_svc_connection_interface_avatars_request_avatar_impl request_avatar;
    tp_svc_connection_interface_avatars_request_avatars_impl request_avatars;
    tp_svc_connection_interface_avatars_set_avatar_impl set_avatar;
    tp_svc_connection_interface_avatars_clear_avatar_impl clear_avatar;
};

enum {
    SIGNAL_CONNECTION_INTERFACE_AVATARS_AvatarUpdated,
    SIGNAL_CONNECTION_INTERFACE_AVATARS_AvatarRetrieved,
    N_CONNECTION_INTERFACE_AVATARS_SIGNALS
};
static guint connection_interface_avatars_signals[N_CONNECTION_INTERFACE_AVATARS_SIGNALS] = {0};

static void tp_svc_connection_interface_avatars_base_init (gpointer klass);

GType
tp_svc_connection_interface_avatars_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcConnectionInterfaceAvatarsClass),
        tp_svc_connection_interface_avatars_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcConnectionInterfaceAvatars", &info, 0);
    }

  return type;
}

/**
 * tp_svc_connection_interface_avatars_get_avatar_requirements_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetAvatarRequirements on interface org.freedesktop.Telepathy.Connection.Interface.Avatars.
 */
static void
tp_svc_connection_interface_avatars_get_avatar_requirements (TpSvcConnectionInterfaceAvatars *self,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_avatars_get_avatar_requirements_impl impl = (TP_SVC_CONNECTION_INTERFACE_AVATARS_GET_CLASS (self)->get_avatar_requirements);

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
 * tp_svc_connection_interface_avatars_implement_get_avatar_requirements:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetAvatarRequirements D-Bus method
 *
 * Register an implementation for the GetAvatarRequirements method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_avatars_implement_get_avatar_requirements (TpSvcConnectionInterfaceAvatarsClass *klass, tp_svc_connection_interface_avatars_get_avatar_requirements_impl impl)
{
  klass->get_avatar_requirements = impl;
}

/**
 * tp_svc_connection_interface_avatars_get_avatar_tokens_impl:
 * @self: The object implementing this interface
 * @in_Contacts: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetAvatarTokens on interface org.freedesktop.Telepathy.Connection.Interface.Avatars.
 */
static void
tp_svc_connection_interface_avatars_get_avatar_tokens (TpSvcConnectionInterfaceAvatars *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_avatars_get_avatar_tokens_impl impl = (TP_SVC_CONNECTION_INTERFACE_AVATARS_GET_CLASS (self)->get_avatar_tokens);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contacts,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_avatars_implement_get_avatar_tokens:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetAvatarTokens D-Bus method
 *
 * Register an implementation for the GetAvatarTokens method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_avatars_implement_get_avatar_tokens (TpSvcConnectionInterfaceAvatarsClass *klass, tp_svc_connection_interface_avatars_get_avatar_tokens_impl impl)
{
  klass->get_avatar_tokens = impl;
}

/**
 * tp_svc_connection_interface_avatars_get_known_avatar_tokens_impl:
 * @self: The object implementing this interface
 * @in_Contacts: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetKnownAvatarTokens on interface org.freedesktop.Telepathy.Connection.Interface.Avatars.
 */
static void
tp_svc_connection_interface_avatars_get_known_avatar_tokens (TpSvcConnectionInterfaceAvatars *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_avatars_get_known_avatar_tokens_impl impl = (TP_SVC_CONNECTION_INTERFACE_AVATARS_GET_CLASS (self)->get_known_avatar_tokens);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contacts,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_avatars_implement_get_known_avatar_tokens:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetKnownAvatarTokens D-Bus method
 *
 * Register an implementation for the GetKnownAvatarTokens method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_avatars_implement_get_known_avatar_tokens (TpSvcConnectionInterfaceAvatarsClass *klass, tp_svc_connection_interface_avatars_get_known_avatar_tokens_impl impl)
{
  klass->get_known_avatar_tokens = impl;
}

/**
 * tp_svc_connection_interface_avatars_request_avatar_impl:
 * @self: The object implementing this interface
 * @in_Contact: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RequestAvatar on interface org.freedesktop.Telepathy.Connection.Interface.Avatars.
 */
static void
tp_svc_connection_interface_avatars_request_avatar (TpSvcConnectionInterfaceAvatars *self,
    guint in_Contact,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_avatars_request_avatar_impl impl = (TP_SVC_CONNECTION_INTERFACE_AVATARS_GET_CLASS (self)->request_avatar);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contact,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_avatars_implement_request_avatar:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RequestAvatar D-Bus method
 *
 * Register an implementation for the RequestAvatar method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_avatars_implement_request_avatar (TpSvcConnectionInterfaceAvatarsClass *klass, tp_svc_connection_interface_avatars_request_avatar_impl impl)
{
  klass->request_avatar = impl;
}

/**
 * tp_svc_connection_interface_avatars_request_avatars_impl:
 * @self: The object implementing this interface
 * @in_Contacts: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RequestAvatars on interface org.freedesktop.Telepathy.Connection.Interface.Avatars.
 */
static void
tp_svc_connection_interface_avatars_request_avatars (TpSvcConnectionInterfaceAvatars *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_avatars_request_avatars_impl impl = (TP_SVC_CONNECTION_INTERFACE_AVATARS_GET_CLASS (self)->request_avatars);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contacts,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_avatars_implement_request_avatars:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RequestAvatars D-Bus method
 *
 * Register an implementation for the RequestAvatars method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_avatars_implement_request_avatars (TpSvcConnectionInterfaceAvatarsClass *klass, tp_svc_connection_interface_avatars_request_avatars_impl impl)
{
  klass->request_avatars = impl;
}

/**
 * tp_svc_connection_interface_avatars_set_avatar_impl:
 * @self: The object implementing this interface
 * @in_Avatar: const GArray * (FIXME, generate documentation)
 * @in_MIME_Type: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SetAvatar on interface org.freedesktop.Telepathy.Connection.Interface.Avatars.
 */
static void
tp_svc_connection_interface_avatars_set_avatar (TpSvcConnectionInterfaceAvatars *self,
    const GArray *in_Avatar,
    const gchar *in_MIME_Type,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_avatars_set_avatar_impl impl = (TP_SVC_CONNECTION_INTERFACE_AVATARS_GET_CLASS (self)->set_avatar);

  if (impl != NULL)
    {
      (impl) (self,
        in_Avatar,
        in_MIME_Type,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_avatars_implement_set_avatar:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SetAvatar D-Bus method
 *
 * Register an implementation for the SetAvatar method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_avatars_implement_set_avatar (TpSvcConnectionInterfaceAvatarsClass *klass, tp_svc_connection_interface_avatars_set_avatar_impl impl)
{
  klass->set_avatar = impl;
}

/**
 * tp_svc_connection_interface_avatars_clear_avatar_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * ClearAvatar on interface org.freedesktop.Telepathy.Connection.Interface.Avatars.
 */
static void
tp_svc_connection_interface_avatars_clear_avatar (TpSvcConnectionInterfaceAvatars *self,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_avatars_clear_avatar_impl impl = (TP_SVC_CONNECTION_INTERFACE_AVATARS_GET_CLASS (self)->clear_avatar);

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
 * tp_svc_connection_interface_avatars_implement_clear_avatar:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the ClearAvatar D-Bus method
 *
 * Register an implementation for the ClearAvatar method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_avatars_implement_clear_avatar (TpSvcConnectionInterfaceAvatarsClass *klass, tp_svc_connection_interface_avatars_clear_avatar_impl impl)
{
  klass->clear_avatar = impl;
}

/**
 * tp_svc_connection_interface_avatars_emit_avatar_updated:
 * @instance: The object implementing this interface
 * @arg_Contact: guint  (FIXME, generate documentation)
 * @arg_New_Avatar_Token: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * AvatarUpdated signal on interface org.freedesktop.Telepathy.Connection.Interface.Avatars.
 */
void
tp_svc_connection_interface_avatars_emit_avatar_updated (gpointer instance,
    guint arg_Contact,
    const gchar *arg_New_Avatar_Token)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CONNECTION_INTERFACE_AVATARS));
  g_signal_emit (instance,
      connection_interface_avatars_signals[SIGNAL_CONNECTION_INTERFACE_AVATARS_AvatarUpdated],
      0,
      arg_Contact,
      arg_New_Avatar_Token);
}

/**
 * tp_svc_connection_interface_avatars_emit_avatar_retrieved:
 * @instance: The object implementing this interface
 * @arg_Contact: guint  (FIXME, generate documentation)
 * @arg_Token: const gchar * (FIXME, generate documentation)
 * @arg_Avatar: const GArray * (FIXME, generate documentation)
 * @arg_Type: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * AvatarRetrieved signal on interface org.freedesktop.Telepathy.Connection.Interface.Avatars.
 */
void
tp_svc_connection_interface_avatars_emit_avatar_retrieved (gpointer instance,
    guint arg_Contact,
    const gchar *arg_Token,
    const GArray *arg_Avatar,
    const gchar *arg_Type)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CONNECTION_INTERFACE_AVATARS));
  g_signal_emit (instance,
      connection_interface_avatars_signals[SIGNAL_CONNECTION_INTERFACE_AVATARS_AvatarRetrieved],
      0,
      arg_Contact,
      arg_Token,
      arg_Avatar,
      arg_Type);
}

static inline void
tp_svc_connection_interface_avatars_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[9] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "as", 0, NULL, NULL }, /* SupportedAvatarMIMETypes */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* MinimumAvatarHeight */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* MinimumAvatarWidth */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* RecommendedAvatarHeight */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* RecommendedAvatarWidth */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* MaximumAvatarHeight */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* MaximumAvatarWidth */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* MaximumAvatarBytes */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_connection_interface_avatars_get_type (),
      &_tp_svc_connection_interface_avatars_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection.Interface.Avatars");
  properties[0].name = g_quark_from_static_string ("SupportedAvatarMIMETypes");
  properties[0].type = G_TYPE_STRV;
  properties[1].name = g_quark_from_static_string ("MinimumAvatarHeight");
  properties[1].type = G_TYPE_UINT;
  properties[2].name = g_quark_from_static_string ("MinimumAvatarWidth");
  properties[2].type = G_TYPE_UINT;
  properties[3].name = g_quark_from_static_string ("RecommendedAvatarHeight");
  properties[3].type = G_TYPE_UINT;
  properties[4].name = g_quark_from_static_string ("RecommendedAvatarWidth");
  properties[4].type = G_TYPE_UINT;
  properties[5].name = g_quark_from_static_string ("MaximumAvatarHeight");
  properties[5].type = G_TYPE_UINT;
  properties[6].name = g_quark_from_static_string ("MaximumAvatarWidth");
  properties[6].type = G_TYPE_UINT;
  properties[7].name = g_quark_from_static_string ("MaximumAvatarBytes");
  properties[7].type = G_TYPE_UINT;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CONNECTION_INTERFACE_AVATARS, &interface);

  /**
   * TpSvcConnectionInterfaceAvatars::avatar-updated:
   * @arg_Contact: guint  (FIXME, generate documentation)
   * @arg_New_Avatar_Token: const gchar * (FIXME, generate documentation)
   *
   * The AvatarUpdated D-Bus signal is emitted whenever this GObject signal is.
   */
  connection_interface_avatars_signals[SIGNAL_CONNECTION_INTERFACE_AVATARS_AvatarUpdated] =
  g_signal_new ("avatar-updated",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_STRING,
      G_TYPE_NONE,
      2,
      G_TYPE_UINT,
      G_TYPE_STRING);

  /**
   * TpSvcConnectionInterfaceAvatars::avatar-retrieved:
   * @arg_Contact: guint  (FIXME, generate documentation)
   * @arg_Token: const gchar * (FIXME, generate documentation)
   * @arg_Avatar: const GArray * (FIXME, generate documentation)
   * @arg_Type: const gchar * (FIXME, generate documentation)
   *
   * The AvatarRetrieved D-Bus signal is emitted whenever this GObject signal is.
   */
  connection_interface_avatars_signals[SIGNAL_CONNECTION_INTERFACE_AVATARS_AvatarRetrieved] =
  g_signal_new ("avatar-retrieved",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_STRING_BOXED_STRING,
      G_TYPE_NONE,
      4,
      G_TYPE_UINT,
      G_TYPE_STRING,
      dbus_g_type_get_collection ("GArray", G_TYPE_UCHAR),
      G_TYPE_STRING);

}
static void
tp_svc_connection_interface_avatars_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_connection_interface_avatars_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_connection_interface_avatars_methods[] = {
  { (GCallback) tp_svc_connection_interface_avatars_get_avatar_requirements, g_cclosure_marshal_VOID__POINTER, 0 },
  { (GCallback) tp_svc_connection_interface_avatars_get_avatar_tokens, _tp_marshal_VOID__BOXED_POINTER, 192 },
  { (GCallback) tp_svc_connection_interface_avatars_get_known_avatar_tokens, _tp_marshal_VOID__BOXED_POINTER, 296 },
  { (GCallback) tp_svc_connection_interface_avatars_request_avatar, g_cclosure_marshal_VOID__UINT_POINTER, 408 },
  { (GCallback) tp_svc_connection_interface_avatars_request_avatars, _tp_marshal_VOID__BOXED_POINTER, 524 },
  { (GCallback) tp_svc_connection_interface_avatars_set_avatar, _tp_marshal_VOID__BOXED_STRING_POINTER, 611 },
  { (GCallback) tp_svc_connection_interface_avatars_clear_avatar, g_cclosure_marshal_VOID__POINTER, 719 },
};

static const DBusGObjectInfo _tp_svc_connection_interface_avatars_object_info = {
  0,
  _tp_svc_connection_interface_avatars_methods,
  7,
"org.freedesktop.Telepathy.Connection.Interface.Avatars\0GetAvatarRequirements\0A\0MIME_Types\0O\0F\0N\0as\0Min_Width\0O\0F\0N\0q\0Min_Height\0O\0F\0N\0q\0Max_Width\0O\0F\0N\0q\0Max_Height\0O\0F\0N\0q\0Max_Bytes\0O\0F\0N\0u\0\0org.freedesktop.Telepathy.Connection.Interface.Avatars\0GetAvatarTokens\0A\0Contacts\0I\0au\0Tokens\0O\0F\0N\0as\0\0org.freedesktop.Telepathy.Connection.Interface.Avatars\0GetKnownAvatarTokens\0A\0Contacts\0I\0au\0Tokens\0O\0F\0N\0a{us}\0\0org.freedesktop.Telepathy.Connection.Interface.Avatars\0RequestAvatar\0A\0Contact\0I\0u\0Data\0O\0F\0N\0ay\0MIME_Type\0O\0F\0N\0s\0\0org.freedesktop.Telepathy.Connection.Interface.Avatars\0RequestAvatars\0A\0Contacts\0I\0au\0\0org.freedesktop.Telepathy.Connection.Interface.Avatars\0SetAvatar\0A\0Avatar\0I\0ay\0MIME_Type\0I\0s\0Token\0O\0F\0N\0s\0\0org.freedesktop.Telepathy.Connection.Interface.Avatars\0ClearAvatar\0A\0\0\0",
"org.freedesktop.Telepathy.Connection.Interface.Avatars\0AvatarUpdated\0org.freedesktop.Telepathy.Connection.Interface.Avatars\0AvatarRetrieved\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_connection_interface_capabilities_object_info;

struct _TpSvcConnectionInterfaceCapabilitiesClass {
    GTypeInterface parent_class;
    tp_svc_connection_interface_capabilities_advertise_capabilities_impl advertise_capabilities;
    tp_svc_connection_interface_capabilities_get_capabilities_impl get_capabilities;
};

enum {
    SIGNAL_CONNECTION_INTERFACE_CAPABILITIES_CapabilitiesChanged,
    N_CONNECTION_INTERFACE_CAPABILITIES_SIGNALS
};
static guint connection_interface_capabilities_signals[N_CONNECTION_INTERFACE_CAPABILITIES_SIGNALS] = {0};

static void tp_svc_connection_interface_capabilities_base_init (gpointer klass);

GType
tp_svc_connection_interface_capabilities_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcConnectionInterfaceCapabilitiesClass),
        tp_svc_connection_interface_capabilities_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcConnectionInterfaceCapabilities", &info, 0);
    }

  return type;
}

/**
 * tp_svc_connection_interface_capabilities_advertise_capabilities_impl:
 * @self: The object implementing this interface
 * @in_Add: const GPtrArray * (FIXME, generate documentation)
 * @in_Remove: const gchar ** (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * AdvertiseCapabilities on interface org.freedesktop.Telepathy.Connection.Interface.Capabilities.
 */
static void
tp_svc_connection_interface_capabilities_advertise_capabilities (TpSvcConnectionInterfaceCapabilities *self,
    const GPtrArray *in_Add,
    const gchar **in_Remove,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_capabilities_advertise_capabilities_impl impl = (TP_SVC_CONNECTION_INTERFACE_CAPABILITIES_GET_CLASS (self)->advertise_capabilities);

  if (impl != NULL)
    {
      (impl) (self,
        in_Add,
        in_Remove,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_capabilities_implement_advertise_capabilities:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the AdvertiseCapabilities D-Bus method
 *
 * Register an implementation for the AdvertiseCapabilities method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_capabilities_implement_advertise_capabilities (TpSvcConnectionInterfaceCapabilitiesClass *klass, tp_svc_connection_interface_capabilities_advertise_capabilities_impl impl)
{
  klass->advertise_capabilities = impl;
}

/**
 * tp_svc_connection_interface_capabilities_get_capabilities_impl:
 * @self: The object implementing this interface
 * @in_Handles: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetCapabilities on interface org.freedesktop.Telepathy.Connection.Interface.Capabilities.
 */
static void
tp_svc_connection_interface_capabilities_get_capabilities (TpSvcConnectionInterfaceCapabilities *self,
    const GArray *in_Handles,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_capabilities_get_capabilities_impl impl = (TP_SVC_CONNECTION_INTERFACE_CAPABILITIES_GET_CLASS (self)->get_capabilities);

  if (impl != NULL)
    {
      (impl) (self,
        in_Handles,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_capabilities_implement_get_capabilities:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetCapabilities D-Bus method
 *
 * Register an implementation for the GetCapabilities method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_capabilities_implement_get_capabilities (TpSvcConnectionInterfaceCapabilitiesClass *klass, tp_svc_connection_interface_capabilities_get_capabilities_impl impl)
{
  klass->get_capabilities = impl;
}

/**
 * tp_svc_connection_interface_capabilities_emit_capabilities_changed:
 * @instance: The object implementing this interface
 * @arg_Caps: const GPtrArray * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * CapabilitiesChanged signal on interface org.freedesktop.Telepathy.Connection.Interface.Capabilities.
 */
void
tp_svc_connection_interface_capabilities_emit_capabilities_changed (gpointer instance,
    const GPtrArray *arg_Caps)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CONNECTION_INTERFACE_CAPABILITIES));
  g_signal_emit (instance,
      connection_interface_capabilities_signals[SIGNAL_CONNECTION_INTERFACE_CAPABILITIES_CapabilitiesChanged],
      0,
      arg_Caps);
}

static inline void
tp_svc_connection_interface_capabilities_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_connection_interface_capabilities_get_type (),
      &_tp_svc_connection_interface_capabilities_object_info);

  /**
   * TpSvcConnectionInterfaceCapabilities::capabilities-changed:
   * @arg_Caps: const GPtrArray * (FIXME, generate documentation)
   *
   * The CapabilitiesChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  connection_interface_capabilities_signals[SIGNAL_CONNECTION_INTERFACE_CAPABILITIES_CapabilitiesChanged] =
  g_signal_new ("capabilities-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,
      1,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))));

}
static void
tp_svc_connection_interface_capabilities_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_connection_interface_capabilities_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_connection_interface_capabilities_methods[] = {
  { (GCallback) tp_svc_connection_interface_capabilities_advertise_capabilities, _tp_marshal_VOID__BOXED_BOXED_POINTER, 0 },
  { (GCallback) tp_svc_connection_interface_capabilities_get_capabilities, _tp_marshal_VOID__BOXED_POINTER, 139 },
};

static const DBusGObjectInfo _tp_svc_connection_interface_capabilities_object_info = {
  0,
  _tp_svc_connection_interface_capabilities_methods,
  2,
"org.freedesktop.Telepathy.Connection.Interface.Capabilities\0AdvertiseCapabilities\0A\0Add\0I\0a(su)\0Remove\0I\0as\0Self_Capabilities\0O\0F\0N\0a(su)\0\0org.freedesktop.Telepathy.Connection.Interface.Capabilities\0GetCapabilities\0A\0Handles\0I\0au\0Contact_Capabilities\0O\0F\0N\0a(usuu)\0\0\0",
"org.freedesktop.Telepathy.Connection.Interface.Capabilities\0CapabilitiesChanged\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_connection_interface_contact_capabilities_object_info;

struct _TpSvcConnectionInterfaceContactCapabilitiesClass {
    GTypeInterface parent_class;
    tp_svc_connection_interface_contact_capabilities_update_capabilities_impl update_capabilities;
    tp_svc_connection_interface_contact_capabilities_get_contact_capabilities_impl get_contact_capabilities;
};

enum {
    SIGNAL_CONNECTION_INTERFACE_CONTACT_CAPABILITIES_ContactCapabilitiesChanged,
    N_CONNECTION_INTERFACE_CONTACT_CAPABILITIES_SIGNALS
};
static guint connection_interface_contact_capabilities_signals[N_CONNECTION_INTERFACE_CONTACT_CAPABILITIES_SIGNALS] = {0};

static void tp_svc_connection_interface_contact_capabilities_base_init (gpointer klass);

GType
tp_svc_connection_interface_contact_capabilities_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcConnectionInterfaceContactCapabilitiesClass),
        tp_svc_connection_interface_contact_capabilities_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcConnectionInterfaceContactCapabilities", &info, 0);
    }

  return type;
}

/**
 * tp_svc_connection_interface_contact_capabilities_update_capabilities_impl:
 * @self: The object implementing this interface
 * @in_Handler_Capabilities: const GPtrArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * UpdateCapabilities on interface org.freedesktop.Telepathy.Connection.Interface.ContactCapabilities.
 */
static void
tp_svc_connection_interface_contact_capabilities_update_capabilities (TpSvcConnectionInterfaceContactCapabilities *self,
    const GPtrArray *in_Handler_Capabilities,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_contact_capabilities_update_capabilities_impl impl = (TP_SVC_CONNECTION_INTERFACE_CONTACT_CAPABILITIES_GET_CLASS (self)->update_capabilities);

  if (impl != NULL)
    {
      (impl) (self,
        in_Handler_Capabilities,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_contact_capabilities_implement_update_capabilities:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the UpdateCapabilities D-Bus method
 *
 * Register an implementation for the UpdateCapabilities method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_contact_capabilities_implement_update_capabilities (TpSvcConnectionInterfaceContactCapabilitiesClass *klass, tp_svc_connection_interface_contact_capabilities_update_capabilities_impl impl)
{
  klass->update_capabilities = impl;
}

/**
 * tp_svc_connection_interface_contact_capabilities_get_contact_capabilities_impl:
 * @self: The object implementing this interface
 * @in_handles: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetContactCapabilities on interface org.freedesktop.Telepathy.Connection.Interface.ContactCapabilities.
 */
static void
tp_svc_connection_interface_contact_capabilities_get_contact_capabilities (TpSvcConnectionInterfaceContactCapabilities *self,
    const GArray *in_handles,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_contact_capabilities_get_contact_capabilities_impl impl = (TP_SVC_CONNECTION_INTERFACE_CONTACT_CAPABILITIES_GET_CLASS (self)->get_contact_capabilities);

  if (impl != NULL)
    {
      (impl) (self,
        in_handles,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_contact_capabilities_implement_get_contact_capabilities:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetContactCapabilities D-Bus method
 *
 * Register an implementation for the GetContactCapabilities method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_contact_capabilities_implement_get_contact_capabilities (TpSvcConnectionInterfaceContactCapabilitiesClass *klass, tp_svc_connection_interface_contact_capabilities_get_contact_capabilities_impl impl)
{
  klass->get_contact_capabilities = impl;
}

/**
 * tp_svc_connection_interface_contact_capabilities_emit_contact_capabilities_changed:
 * @instance: The object implementing this interface
 * @arg_caps: GHashTable * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * ContactCapabilitiesChanged signal on interface org.freedesktop.Telepathy.Connection.Interface.ContactCapabilities.
 */
void
tp_svc_connection_interface_contact_capabilities_emit_contact_capabilities_changed (gpointer instance,
    GHashTable *arg_caps)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACT_CAPABILITIES));
  g_signal_emit (instance,
      connection_interface_contact_capabilities_signals[SIGNAL_CONNECTION_INTERFACE_CONTACT_CAPABILITIES_ContactCapabilitiesChanged],
      0,
      arg_caps);
}

static inline void
tp_svc_connection_interface_contact_capabilities_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_connection_interface_contact_capabilities_get_type (),
      &_tp_svc_connection_interface_contact_capabilities_object_info);

  /**
   * TpSvcConnectionInterfaceContactCapabilities::contact-capabilities-changed:
   * @arg_caps: GHashTable * (FIXME, generate documentation)
   *
   * The ContactCapabilitiesChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  connection_interface_contact_capabilities_signals[SIGNAL_CONNECTION_INTERFACE_CONTACT_CAPABILITIES_ContactCapabilitiesChanged] =
  g_signal_new ("contact-capabilities-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,
      1,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_STRV, G_TYPE_INVALID)))))));

}
static void
tp_svc_connection_interface_contact_capabilities_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_connection_interface_contact_capabilities_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_connection_interface_contact_capabilities_methods[] = {
  { (GCallback) tp_svc_connection_interface_contact_capabilities_update_capabilities, _tp_marshal_VOID__BOXED_POINTER, 0 },
  { (GCallback) tp_svc_connection_interface_contact_capabilities_get_contact_capabilities, _tp_marshal_VOID__BOXED_POINTER, 125 },
};

static const DBusGObjectInfo _tp_svc_connection_interface_contact_capabilities_object_info = {
  0,
  _tp_svc_connection_interface_contact_capabilities_methods,
  2,
"org.freedesktop.Telepathy.Connection.Interface.ContactCapabilities\0UpdateCapabilities\0A\0Handler_Capabilities\0I\0a(saa{sv}as)\0\0org.freedesktop.Telepathy.Connection.Interface.ContactCapabilities\0GetContactCapabilities\0A\0handles\0I\0au\0Contact_Capabilities\0O\0F\0N\0a{ua(a{sv}as)}\0\0\0",
"org.freedesktop.Telepathy.Connection.Interface.ContactCapabilities\0ContactCapabilitiesChanged\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_connection_interface_contacts_object_info;

struct _TpSvcConnectionInterfaceContactsClass {
    GTypeInterface parent_class;
    tp_svc_connection_interface_contacts_get_contact_attributes_impl get_contact_attributes;
};

static void tp_svc_connection_interface_contacts_base_init (gpointer klass);

GType
tp_svc_connection_interface_contacts_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcConnectionInterfaceContactsClass),
        tp_svc_connection_interface_contacts_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcConnectionInterfaceContacts", &info, 0);
    }

  return type;
}

/**
 * tp_svc_connection_interface_contacts_get_contact_attributes_impl:
 * @self: The object implementing this interface
 * @in_Handles: const GArray * (FIXME, generate documentation)
 * @in_Interfaces: const gchar ** (FIXME, generate documentation)
 * @in_Hold: gboolean  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetContactAttributes on interface org.freedesktop.Telepathy.Connection.Interface.Contacts.
 */
static void
tp_svc_connection_interface_contacts_get_contact_attributes (TpSvcConnectionInterfaceContacts *self,
    const GArray *in_Handles,
    const gchar **in_Interfaces,
    gboolean in_Hold,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_contacts_get_contact_attributes_impl impl = (TP_SVC_CONNECTION_INTERFACE_CONTACTS_GET_CLASS (self)->get_contact_attributes);

  if (impl != NULL)
    {
      (impl) (self,
        in_Handles,
        in_Interfaces,
        in_Hold,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_contacts_implement_get_contact_attributes:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetContactAttributes D-Bus method
 *
 * Register an implementation for the GetContactAttributes method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_contacts_implement_get_contact_attributes (TpSvcConnectionInterfaceContactsClass *klass, tp_svc_connection_interface_contacts_get_contact_attributes_impl impl)
{
  klass->get_contact_attributes = impl;
}

static inline void
tp_svc_connection_interface_contacts_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[2] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "as", 0, NULL, NULL }, /* ContactAttributeInterfaces */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_connection_interface_contacts_get_type (),
      &_tp_svc_connection_interface_contacts_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection.Interface.Contacts");
  properties[0].name = g_quark_from_static_string ("ContactAttributeInterfaces");
  properties[0].type = G_TYPE_STRV;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACTS, &interface);

}
static void
tp_svc_connection_interface_contacts_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_connection_interface_contacts_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_connection_interface_contacts_methods[] = {
  { (GCallback) tp_svc_connection_interface_contacts_get_contact_attributes, _tp_marshal_VOID__BOXED_BOXED_BOOLEAN_POINTER, 0 },
};

static const DBusGObjectInfo _tp_svc_connection_interface_contacts_object_info = {
  0,
  _tp_svc_connection_interface_contacts_methods,
  1,
"org.freedesktop.Telepathy.Connection.Interface.Contacts\0GetContactAttributes\0A\0Handles\0I\0au\0Interfaces\0I\0as\0Hold\0I\0b\0Attributes\0O\0F\0N\0a{ua{sv}}\0\0\0",
"\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_connection_interface_location_object_info;

struct _TpSvcConnectionInterfaceLocationClass {
    GTypeInterface parent_class;
    tp_svc_connection_interface_location_get_locations_impl get_locations;
    tp_svc_connection_interface_location_request_location_impl request_location;
    tp_svc_connection_interface_location_set_location_impl set_location;
};

enum {
    SIGNAL_CONNECTION_INTERFACE_LOCATION_LocationUpdated,
    N_CONNECTION_INTERFACE_LOCATION_SIGNALS
};
static guint connection_interface_location_signals[N_CONNECTION_INTERFACE_LOCATION_SIGNALS] = {0};

static void tp_svc_connection_interface_location_base_init (gpointer klass);

GType
tp_svc_connection_interface_location_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcConnectionInterfaceLocationClass),
        tp_svc_connection_interface_location_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcConnectionInterfaceLocation", &info, 0);
    }

  return type;
}

/**
 * tp_svc_connection_interface_location_get_locations_impl:
 * @self: The object implementing this interface
 * @in_Contacts: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetLocations on interface org.freedesktop.Telepathy.Connection.Interface.Location.
 */
static void
tp_svc_connection_interface_location_get_locations (TpSvcConnectionInterfaceLocation *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_location_get_locations_impl impl = (TP_SVC_CONNECTION_INTERFACE_LOCATION_GET_CLASS (self)->get_locations);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contacts,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_location_implement_get_locations:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetLocations D-Bus method
 *
 * Register an implementation for the GetLocations method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_location_implement_get_locations (TpSvcConnectionInterfaceLocationClass *klass, tp_svc_connection_interface_location_get_locations_impl impl)
{
  klass->get_locations = impl;
}

/**
 * tp_svc_connection_interface_location_request_location_impl:
 * @self: The object implementing this interface
 * @in_Contact: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RequestLocation on interface org.freedesktop.Telepathy.Connection.Interface.Location.
 */
static void
tp_svc_connection_interface_location_request_location (TpSvcConnectionInterfaceLocation *self,
    guint in_Contact,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_location_request_location_impl impl = (TP_SVC_CONNECTION_INTERFACE_LOCATION_GET_CLASS (self)->request_location);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contact,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_location_implement_request_location:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RequestLocation D-Bus method
 *
 * Register an implementation for the RequestLocation method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_location_implement_request_location (TpSvcConnectionInterfaceLocationClass *klass, tp_svc_connection_interface_location_request_location_impl impl)
{
  klass->request_location = impl;
}

/**
 * tp_svc_connection_interface_location_set_location_impl:
 * @self: The object implementing this interface
 * @in_Location: GHashTable * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SetLocation on interface org.freedesktop.Telepathy.Connection.Interface.Location.
 */
static void
tp_svc_connection_interface_location_set_location (TpSvcConnectionInterfaceLocation *self,
    GHashTable *in_Location,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_location_set_location_impl impl = (TP_SVC_CONNECTION_INTERFACE_LOCATION_GET_CLASS (self)->set_location);

  if (impl != NULL)
    {
      (impl) (self,
        in_Location,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_location_implement_set_location:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SetLocation D-Bus method
 *
 * Register an implementation for the SetLocation method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_location_implement_set_location (TpSvcConnectionInterfaceLocationClass *klass, tp_svc_connection_interface_location_set_location_impl impl)
{
  klass->set_location = impl;
}

/**
 * tp_svc_connection_interface_location_emit_location_updated:
 * @instance: The object implementing this interface
 * @arg_Contact: guint  (FIXME, generate documentation)
 * @arg_Location: GHashTable * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * LocationUpdated signal on interface org.freedesktop.Telepathy.Connection.Interface.Location.
 */
void
tp_svc_connection_interface_location_emit_location_updated (gpointer instance,
    guint arg_Contact,
    GHashTable *arg_Location)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CONNECTION_INTERFACE_LOCATION));
  g_signal_emit (instance,
      connection_interface_location_signals[SIGNAL_CONNECTION_INTERFACE_LOCATION_LocationUpdated],
      0,
      arg_Contact,
      arg_Location);
}

static inline void
tp_svc_connection_interface_location_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[3] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "au", 0, NULL, NULL }, /* LocationAccessControlTypes */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ | TP_DBUS_PROPERTIES_MIXIN_FLAG_WRITE, "(uv)", 0, NULL, NULL }, /* LocationAccessControl */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_connection_interface_location_get_type (),
      &_tp_svc_connection_interface_location_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection.Interface.Location");
  properties[0].name = g_quark_from_static_string ("LocationAccessControlTypes");
  properties[0].type = DBUS_TYPE_G_UINT_ARRAY;
  properties[1].name = g_quark_from_static_string ("LocationAccessControl");
  properties[1].type = (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_VALUE, G_TYPE_INVALID));
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CONNECTION_INTERFACE_LOCATION, &interface);

  /**
   * TpSvcConnectionInterfaceLocation::location-updated:
   * @arg_Contact: guint  (FIXME, generate documentation)
   * @arg_Location: GHashTable * (FIXME, generate documentation)
   *
   * The LocationUpdated D-Bus signal is emitted whenever this GObject signal is.
   */
  connection_interface_location_signals[SIGNAL_CONNECTION_INTERFACE_LOCATION_LocationUpdated] =
  g_signal_new ("location-updated",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_BOXED,
      G_TYPE_NONE,
      2,
      G_TYPE_UINT,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)));

}
static void
tp_svc_connection_interface_location_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_connection_interface_location_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_connection_interface_location_methods[] = {
  { (GCallback) tp_svc_connection_interface_location_get_locations, _tp_marshal_VOID__BOXED_POINTER, 0 },
  { (GCallback) tp_svc_connection_interface_location_request_location, g_cclosure_marshal_VOID__UINT_POINTER, 112 },
  { (GCallback) tp_svc_connection_interface_location_set_location, _tp_marshal_VOID__BOXED_POINTER, 220 },
};

static const DBusGObjectInfo _tp_svc_connection_interface_location_object_info = {
  0,
  _tp_svc_connection_interface_location_methods,
  3,
"org.freedesktop.Telepathy.Connection.Interface.Location\0GetLocations\0A\0Contacts\0I\0au\0Locations\0O\0F\0N\0a{ua{sv}}\0\0org.freedesktop.Telepathy.Connection.Interface.Location\0RequestLocation\0A\0Contact\0I\0u\0Location\0O\0F\0N\0a{sv}\0\0org.freedesktop.Telepathy.Connection.Interface.Location\0SetLocation\0A\0Location\0I\0a{sv}\0\0\0",
"org.freedesktop.Telepathy.Connection.Interface.Location\0LocationUpdated\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_connection_interface_presence_object_info;

struct _TpSvcConnectionInterfacePresenceClass {
    GTypeInterface parent_class;
    tp_svc_connection_interface_presence_add_status_impl add_status;
    tp_svc_connection_interface_presence_clear_status_impl clear_status;
    tp_svc_connection_interface_presence_get_presence_impl get_presence;
    tp_svc_connection_interface_presence_get_statuses_impl get_statuses;
    tp_svc_connection_interface_presence_remove_status_impl remove_status;
    tp_svc_connection_interface_presence_request_presence_impl request_presence;
    tp_svc_connection_interface_presence_set_last_activity_time_impl set_last_activity_time;
    tp_svc_connection_interface_presence_set_status_impl set_status;
};

enum {
    SIGNAL_CONNECTION_INTERFACE_PRESENCE_PresenceUpdate,
    N_CONNECTION_INTERFACE_PRESENCE_SIGNALS
};
static guint connection_interface_presence_signals[N_CONNECTION_INTERFACE_PRESENCE_SIGNALS] = {0};

static void tp_svc_connection_interface_presence_base_init (gpointer klass);

GType
tp_svc_connection_interface_presence_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcConnectionInterfacePresenceClass),
        tp_svc_connection_interface_presence_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcConnectionInterfacePresence", &info, 0);
    }

  return type;
}

/**
 * tp_svc_connection_interface_presence_add_status_impl:
 * @self: The object implementing this interface
 * @in_Status: const gchar * (FIXME, generate documentation)
 * @in_Parameters: GHashTable * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * AddStatus on interface org.freedesktop.Telepathy.Connection.Interface.Presence.
 */
static void
tp_svc_connection_interface_presence_add_status (TpSvcConnectionInterfacePresence *self,
    const gchar *in_Status,
    GHashTable *in_Parameters,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_presence_add_status_impl impl = (TP_SVC_CONNECTION_INTERFACE_PRESENCE_GET_CLASS (self)->add_status);

  if (impl != NULL)
    {
      (impl) (self,
        in_Status,
        in_Parameters,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_presence_implement_add_status:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the AddStatus D-Bus method
 *
 * Register an implementation for the AddStatus method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_presence_implement_add_status (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_add_status_impl impl)
{
  klass->add_status = impl;
}

/**
 * tp_svc_connection_interface_presence_clear_status_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * ClearStatus on interface org.freedesktop.Telepathy.Connection.Interface.Presence.
 */
static void
tp_svc_connection_interface_presence_clear_status (TpSvcConnectionInterfacePresence *self,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_presence_clear_status_impl impl = (TP_SVC_CONNECTION_INTERFACE_PRESENCE_GET_CLASS (self)->clear_status);

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
 * tp_svc_connection_interface_presence_implement_clear_status:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the ClearStatus D-Bus method
 *
 * Register an implementation for the ClearStatus method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_presence_implement_clear_status (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_clear_status_impl impl)
{
  klass->clear_status = impl;
}

/**
 * tp_svc_connection_interface_presence_get_presence_impl:
 * @self: The object implementing this interface
 * @in_Contacts: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetPresence on interface org.freedesktop.Telepathy.Connection.Interface.Presence.
 */
static void
tp_svc_connection_interface_presence_get_presence (TpSvcConnectionInterfacePresence *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_presence_get_presence_impl impl = (TP_SVC_CONNECTION_INTERFACE_PRESENCE_GET_CLASS (self)->get_presence);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contacts,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_presence_implement_get_presence:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetPresence D-Bus method
 *
 * Register an implementation for the GetPresence method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_presence_implement_get_presence (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_get_presence_impl impl)
{
  klass->get_presence = impl;
}

/**
 * tp_svc_connection_interface_presence_get_statuses_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetStatuses on interface org.freedesktop.Telepathy.Connection.Interface.Presence.
 */
static void
tp_svc_connection_interface_presence_get_statuses (TpSvcConnectionInterfacePresence *self,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_presence_get_statuses_impl impl = (TP_SVC_CONNECTION_INTERFACE_PRESENCE_GET_CLASS (self)->get_statuses);

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
 * tp_svc_connection_interface_presence_implement_get_statuses:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetStatuses D-Bus method
 *
 * Register an implementation for the GetStatuses method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_presence_implement_get_statuses (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_get_statuses_impl impl)
{
  klass->get_statuses = impl;
}

/**
 * tp_svc_connection_interface_presence_remove_status_impl:
 * @self: The object implementing this interface
 * @in_Status: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RemoveStatus on interface org.freedesktop.Telepathy.Connection.Interface.Presence.
 */
static void
tp_svc_connection_interface_presence_remove_status (TpSvcConnectionInterfacePresence *self,
    const gchar *in_Status,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_presence_remove_status_impl impl = (TP_SVC_CONNECTION_INTERFACE_PRESENCE_GET_CLASS (self)->remove_status);

  if (impl != NULL)
    {
      (impl) (self,
        in_Status,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_presence_implement_remove_status:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RemoveStatus D-Bus method
 *
 * Register an implementation for the RemoveStatus method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_presence_implement_remove_status (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_remove_status_impl impl)
{
  klass->remove_status = impl;
}

/**
 * tp_svc_connection_interface_presence_request_presence_impl:
 * @self: The object implementing this interface
 * @in_Contacts: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RequestPresence on interface org.freedesktop.Telepathy.Connection.Interface.Presence.
 */
static void
tp_svc_connection_interface_presence_request_presence (TpSvcConnectionInterfacePresence *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_presence_request_presence_impl impl = (TP_SVC_CONNECTION_INTERFACE_PRESENCE_GET_CLASS (self)->request_presence);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contacts,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_presence_implement_request_presence:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RequestPresence D-Bus method
 *
 * Register an implementation for the RequestPresence method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_presence_implement_request_presence (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_request_presence_impl impl)
{
  klass->request_presence = impl;
}

/**
 * tp_svc_connection_interface_presence_set_last_activity_time_impl:
 * @self: The object implementing this interface
 * @in_Time: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SetLastActivityTime on interface org.freedesktop.Telepathy.Connection.Interface.Presence.
 */
static void
tp_svc_connection_interface_presence_set_last_activity_time (TpSvcConnectionInterfacePresence *self,
    guint in_Time,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_presence_set_last_activity_time_impl impl = (TP_SVC_CONNECTION_INTERFACE_PRESENCE_GET_CLASS (self)->set_last_activity_time);

  if (impl != NULL)
    {
      (impl) (self,
        in_Time,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_presence_implement_set_last_activity_time:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SetLastActivityTime D-Bus method
 *
 * Register an implementation for the SetLastActivityTime method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_presence_implement_set_last_activity_time (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_set_last_activity_time_impl impl)
{
  klass->set_last_activity_time = impl;
}

/**
 * tp_svc_connection_interface_presence_set_status_impl:
 * @self: The object implementing this interface
 * @in_Statuses: GHashTable * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SetStatus on interface org.freedesktop.Telepathy.Connection.Interface.Presence.
 */
static void
tp_svc_connection_interface_presence_set_status (TpSvcConnectionInterfacePresence *self,
    GHashTable *in_Statuses,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_presence_set_status_impl impl = (TP_SVC_CONNECTION_INTERFACE_PRESENCE_GET_CLASS (self)->set_status);

  if (impl != NULL)
    {
      (impl) (self,
        in_Statuses,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_presence_implement_set_status:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SetStatus D-Bus method
 *
 * Register an implementation for the SetStatus method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_presence_implement_set_status (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_set_status_impl impl)
{
  klass->set_status = impl;
}

/**
 * tp_svc_connection_interface_presence_emit_presence_update:
 * @instance: The object implementing this interface
 * @arg_Presence: GHashTable * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * PresenceUpdate signal on interface org.freedesktop.Telepathy.Connection.Interface.Presence.
 */
void
tp_svc_connection_interface_presence_emit_presence_update (gpointer instance,
    GHashTable *arg_Presence)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CONNECTION_INTERFACE_PRESENCE));
  g_signal_emit (instance,
      connection_interface_presence_signals[SIGNAL_CONNECTION_INTERFACE_PRESENCE_PresenceUpdate],
      0,
      arg_Presence);
}

static inline void
tp_svc_connection_interface_presence_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_connection_interface_presence_get_type (),
      &_tp_svc_connection_interface_presence_object_info);

  /**
   * TpSvcConnectionInterfacePresence::presence-update:
   * @arg_Presence: GHashTable * (FIXME, generate documentation)
   *
   * The PresenceUpdate D-Bus signal is emitted whenever this GObject signal is.
   */
  connection_interface_presence_signals[SIGNAL_CONNECTION_INTERFACE_PRESENCE_PresenceUpdate] =
  g_signal_new ("presence-update",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,
      1,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), G_TYPE_INVALID)))));

}
static void
tp_svc_connection_interface_presence_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_connection_interface_presence_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_connection_interface_presence_methods[] = {
  { (GCallback) tp_svc_connection_interface_presence_add_status, _tp_marshal_VOID__STRING_BOXED_POINTER, 0 },
  { (GCallback) tp_svc_connection_interface_presence_clear_status, g_cclosure_marshal_VOID__POINTER, 99 },
  { (GCallback) tp_svc_connection_interface_presence_get_presence, _tp_marshal_VOID__BOXED_POINTER, 170 },
  { (GCallback) tp_svc_connection_interface_presence_get_statuses, g_cclosure_marshal_VOID__POINTER, 287 },
  { (GCallback) tp_svc_connection_interface_presence_remove_status, _tp_marshal_VOID__STRING_POINTER, 398 },
  { (GCallback) tp_svc_connection_interface_presence_request_presence, _tp_marshal_VOID__BOXED_POINTER, 481 },
  { (GCallback) tp_svc_connection_interface_presence_set_last_activity_time, g_cclosure_marshal_VOID__UINT_POINTER, 570 },
  { (GCallback) tp_svc_connection_interface_presence_set_status, _tp_marshal_VOID__BOXED_POINTER, 658 },
};

static const DBusGObjectInfo _tp_svc_connection_interface_presence_object_info = {
  0,
  _tp_svc_connection_interface_presence_methods,
  8,
"org.freedesktop.Telepathy.Connection.Interface.Presence\0AddStatus\0A\0Status\0I\0s\0Parameters\0I\0a{sv}\0\0org.freedesktop.Telepathy.Connection.Interface.Presence\0ClearStatus\0A\0\0org.freedesktop.Telepathy.Connection.Interface.Presence\0GetPresence\0A\0Contacts\0I\0au\0Presence\0O\0F\0N\0a{u(ua{sa{sv}})}\0\0org.freedesktop.Telepathy.Connection.Interface.Presence\0GetStatuses\0A\0Available_Statuses\0O\0F\0N\0a{s(ubba{ss})}\0\0org.freedesktop.Telepathy.Connection.Interface.Presence\0RemoveStatus\0A\0Status\0I\0s\0\0org.freedesktop.Telepathy.Connection.Interface.Presence\0RequestPresence\0A\0Contacts\0I\0au\0\0org.freedesktop.Telepathy.Connection.Interface.Presence\0SetLastActivityTime\0A\0Time\0I\0u\0\0org.freedesktop.Telepathy.Connection.Interface.Presence\0SetStatus\0A\0Statuses\0I\0a{sa{sv}}\0\0\0",
"org.freedesktop.Telepathy.Connection.Interface.Presence\0PresenceUpdate\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_connection_interface_requests_object_info;

struct _TpSvcConnectionInterfaceRequestsClass {
    GTypeInterface parent_class;
    tp_svc_connection_interface_requests_create_channel_impl create_channel;
    tp_svc_connection_interface_requests_ensure_channel_impl ensure_channel;
};

enum {
    SIGNAL_CONNECTION_INTERFACE_REQUESTS_NewChannels,
    SIGNAL_CONNECTION_INTERFACE_REQUESTS_ChannelClosed,
    N_CONNECTION_INTERFACE_REQUESTS_SIGNALS
};
static guint connection_interface_requests_signals[N_CONNECTION_INTERFACE_REQUESTS_SIGNALS] = {0};

static void tp_svc_connection_interface_requests_base_init (gpointer klass);

GType
tp_svc_connection_interface_requests_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcConnectionInterfaceRequestsClass),
        tp_svc_connection_interface_requests_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcConnectionInterfaceRequests", &info, 0);
    }

  return type;
}

/**
 * tp_svc_connection_interface_requests_create_channel_impl:
 * @self: The object implementing this interface
 * @in_Request: GHashTable * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * CreateChannel on interface org.freedesktop.Telepathy.Connection.Interface.Requests.
 */
static void
tp_svc_connection_interface_requests_create_channel (TpSvcConnectionInterfaceRequests *self,
    GHashTable *in_Request,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_requests_create_channel_impl impl = (TP_SVC_CONNECTION_INTERFACE_REQUESTS_GET_CLASS (self)->create_channel);

  if (impl != NULL)
    {
      (impl) (self,
        in_Request,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_requests_implement_create_channel:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the CreateChannel D-Bus method
 *
 * Register an implementation for the CreateChannel method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_requests_implement_create_channel (TpSvcConnectionInterfaceRequestsClass *klass, tp_svc_connection_interface_requests_create_channel_impl impl)
{
  klass->create_channel = impl;
}

/**
 * tp_svc_connection_interface_requests_ensure_channel_impl:
 * @self: The object implementing this interface
 * @in_Request: GHashTable * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * EnsureChannel on interface org.freedesktop.Telepathy.Connection.Interface.Requests.
 */
static void
tp_svc_connection_interface_requests_ensure_channel (TpSvcConnectionInterfaceRequests *self,
    GHashTable *in_Request,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_requests_ensure_channel_impl impl = (TP_SVC_CONNECTION_INTERFACE_REQUESTS_GET_CLASS (self)->ensure_channel);

  if (impl != NULL)
    {
      (impl) (self,
        in_Request,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_requests_implement_ensure_channel:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the EnsureChannel D-Bus method
 *
 * Register an implementation for the EnsureChannel method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_requests_implement_ensure_channel (TpSvcConnectionInterfaceRequestsClass *klass, tp_svc_connection_interface_requests_ensure_channel_impl impl)
{
  klass->ensure_channel = impl;
}

/**
 * tp_svc_connection_interface_requests_emit_new_channels:
 * @instance: The object implementing this interface
 * @arg_Channels: const GPtrArray * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * NewChannels signal on interface org.freedesktop.Telepathy.Connection.Interface.Requests.
 */
void
tp_svc_connection_interface_requests_emit_new_channels (gpointer instance,
    const GPtrArray *arg_Channels)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CONNECTION_INTERFACE_REQUESTS));
  g_signal_emit (instance,
      connection_interface_requests_signals[SIGNAL_CONNECTION_INTERFACE_REQUESTS_NewChannels],
      0,
      arg_Channels);
}

/**
 * tp_svc_connection_interface_requests_emit_channel_closed:
 * @instance: The object implementing this interface
 * @arg_Removed: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * ChannelClosed signal on interface org.freedesktop.Telepathy.Connection.Interface.Requests.
 */
void
tp_svc_connection_interface_requests_emit_channel_closed (gpointer instance,
    const gchar *arg_Removed)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CONNECTION_INTERFACE_REQUESTS));
  g_signal_emit (instance,
      connection_interface_requests_signals[SIGNAL_CONNECTION_INTERFACE_REQUESTS_ChannelClosed],
      0,
      arg_Removed);
}

static inline void
tp_svc_connection_interface_requests_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[3] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "a(oa{sv})", 0, NULL, NULL }, /* Channels */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "a(a{sv}as)", 0, NULL, NULL }, /* RequestableChannelClasses */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_connection_interface_requests_get_type (),
      &_tp_svc_connection_interface_requests_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection.Interface.Requests");
  properties[0].name = g_quark_from_static_string ("Channels");
  properties[0].type = (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID))));
  properties[1].name = g_quark_from_static_string ("RequestableChannelClasses");
  properties[1].type = (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_STRV, G_TYPE_INVALID))));
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CONNECTION_INTERFACE_REQUESTS, &interface);

  /**
   * TpSvcConnectionInterfaceRequests::new-channels:
   * @arg_Channels: const GPtrArray * (FIXME, generate documentation)
   *
   * The NewChannels D-Bus signal is emitted whenever this GObject signal is.
   */
  connection_interface_requests_signals[SIGNAL_CONNECTION_INTERFACE_REQUESTS_NewChannels] =
  g_signal_new ("new-channels",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,
      1,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID)))));

  /**
   * TpSvcConnectionInterfaceRequests::channel-closed:
   * @arg_Removed: const gchar * (FIXME, generate documentation)
   *
   * The ChannelClosed D-Bus signal is emitted whenever this GObject signal is.
   */
  connection_interface_requests_signals[SIGNAL_CONNECTION_INTERFACE_REQUESTS_ChannelClosed] =
  g_signal_new ("channel-closed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,
      1,
      DBUS_TYPE_G_OBJECT_PATH);

}
static void
tp_svc_connection_interface_requests_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_connection_interface_requests_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_connection_interface_requests_methods[] = {
  { (GCallback) tp_svc_connection_interface_requests_create_channel, _tp_marshal_VOID__BOXED_POINTER, 0 },
  { (GCallback) tp_svc_connection_interface_requests_ensure_channel, _tp_marshal_VOID__BOXED_POINTER, 128 },
};

static const DBusGObjectInfo _tp_svc_connection_interface_requests_object_info = {
  0,
  _tp_svc_connection_interface_requests_methods,
  2,
"org.freedesktop.Telepathy.Connection.Interface.Requests\0CreateChannel\0A\0Request\0I\0a{sv}\0Channel\0O\0F\0N\0o\0Properties\0O\0F\0N\0a{sv}\0\0org.freedesktop.Telepathy.Connection.Interface.Requests\0EnsureChannel\0A\0Request\0I\0a{sv}\0Yours\0O\0F\0N\0b\0Channel\0O\0F\0N\0o\0Properties\0O\0F\0N\0a{sv}\0\0\0",
"org.freedesktop.Telepathy.Connection.Interface.Requests\0NewChannels\0org.freedesktop.Telepathy.Connection.Interface.Requests\0ChannelClosed\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_connection_interface_simple_presence_object_info;

struct _TpSvcConnectionInterfaceSimplePresenceClass {
    GTypeInterface parent_class;
    tp_svc_connection_interface_simple_presence_set_presence_impl set_presence;
    tp_svc_connection_interface_simple_presence_get_presences_impl get_presences;
};

enum {
    SIGNAL_CONNECTION_INTERFACE_SIMPLE_PRESENCE_PresencesChanged,
    N_CONNECTION_INTERFACE_SIMPLE_PRESENCE_SIGNALS
};
static guint connection_interface_simple_presence_signals[N_CONNECTION_INTERFACE_SIMPLE_PRESENCE_SIGNALS] = {0};

static void tp_svc_connection_interface_simple_presence_base_init (gpointer klass);

GType
tp_svc_connection_interface_simple_presence_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcConnectionInterfaceSimplePresenceClass),
        tp_svc_connection_interface_simple_presence_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcConnectionInterfaceSimplePresence", &info, 0);
    }

  return type;
}

/**
 * tp_svc_connection_interface_simple_presence_set_presence_impl:
 * @self: The object implementing this interface
 * @in_Status: const gchar * (FIXME, generate documentation)
 * @in_Status_Message: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SetPresence on interface org.freedesktop.Telepathy.Connection.Interface.SimplePresence.
 */
static void
tp_svc_connection_interface_simple_presence_set_presence (TpSvcConnectionInterfaceSimplePresence *self,
    const gchar *in_Status,
    const gchar *in_Status_Message,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_simple_presence_set_presence_impl impl = (TP_SVC_CONNECTION_INTERFACE_SIMPLE_PRESENCE_GET_CLASS (self)->set_presence);

  if (impl != NULL)
    {
      (impl) (self,
        in_Status,
        in_Status_Message,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_simple_presence_implement_set_presence:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SetPresence D-Bus method
 *
 * Register an implementation for the SetPresence method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_simple_presence_implement_set_presence (TpSvcConnectionInterfaceSimplePresenceClass *klass, tp_svc_connection_interface_simple_presence_set_presence_impl impl)
{
  klass->set_presence = impl;
}

/**
 * tp_svc_connection_interface_simple_presence_get_presences_impl:
 * @self: The object implementing this interface
 * @in_Contacts: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetPresences on interface org.freedesktop.Telepathy.Connection.Interface.SimplePresence.
 */
static void
tp_svc_connection_interface_simple_presence_get_presences (TpSvcConnectionInterfaceSimplePresence *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context)
{
  tp_svc_connection_interface_simple_presence_get_presences_impl impl = (TP_SVC_CONNECTION_INTERFACE_SIMPLE_PRESENCE_GET_CLASS (self)->get_presences);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contacts,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_connection_interface_simple_presence_implement_get_presences:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetPresences D-Bus method
 *
 * Register an implementation for the GetPresences method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_connection_interface_simple_presence_implement_get_presences (TpSvcConnectionInterfaceSimplePresenceClass *klass, tp_svc_connection_interface_simple_presence_get_presences_impl impl)
{
  klass->get_presences = impl;
}

/**
 * tp_svc_connection_interface_simple_presence_emit_presences_changed:
 * @instance: The object implementing this interface
 * @arg_Presence: GHashTable * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * PresencesChanged signal on interface org.freedesktop.Telepathy.Connection.Interface.SimplePresence.
 */
void
tp_svc_connection_interface_simple_presence_emit_presences_changed (gpointer instance,
    GHashTable *arg_Presence)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CONNECTION_INTERFACE_SIMPLE_PRESENCE));
  g_signal_emit (instance,
      connection_interface_simple_presence_signals[SIGNAL_CONNECTION_INTERFACE_SIMPLE_PRESENCE_PresencesChanged],
      0,
      arg_Presence);
}

static inline void
tp_svc_connection_interface_simple_presence_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[2] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "a{s(ubb)}", 0, NULL, NULL }, /* Statuses */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_connection_interface_simple_presence_get_type (),
      &_tp_svc_connection_interface_simple_presence_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection.Interface.SimplePresence");
  properties[0].name = g_quark_from_static_string ("Statuses");
  properties[0].type = (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, G_TYPE_INVALID))));
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CONNECTION_INTERFACE_SIMPLE_PRESENCE, &interface);

  /**
   * TpSvcConnectionInterfaceSimplePresence::presences-changed:
   * @arg_Presence: GHashTable * (FIXME, generate documentation)
   *
   * The PresencesChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  connection_interface_simple_presence_signals[SIGNAL_CONNECTION_INTERFACE_SIMPLE_PRESENCE_PresencesChanged] =
  g_signal_new ("presences-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,
      1,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))));

}
static void
tp_svc_connection_interface_simple_presence_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_connection_interface_simple_presence_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_connection_interface_simple_presence_methods[] = {
  { (GCallback) tp_svc_connection_interface_simple_presence_set_presence, _tp_marshal_VOID__STRING_STRING_POINTER, 0 },
  { (GCallback) tp_svc_connection_interface_simple_presence_get_presences, _tp_marshal_VOID__BOXED_POINTER, 107 },
};

static const DBusGObjectInfo _tp_svc_connection_interface_simple_presence_object_info = {
  0,
  _tp_svc_connection_interface_simple_presence_methods,
  2,
"org.freedesktop.Telepathy.Connection.Interface.SimplePresence\0SetPresence\0A\0Status\0I\0s\0Status_Message\0I\0s\0\0org.freedesktop.Telepathy.Connection.Interface.SimplePresence\0GetPresences\0A\0Contacts\0I\0au\0Presence\0O\0F\0N\0a{u(uss)}\0\0\0",
"org.freedesktop.Telepathy.Connection.Interface.SimplePresence\0PresencesChanged\0\0",
"\0\0",
};


