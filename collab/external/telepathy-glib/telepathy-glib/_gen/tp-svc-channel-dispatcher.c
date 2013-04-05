#include "_gen/tp-svc-channel-dispatcher.h"

#include <telepathy-glib/dbus.h>
#include "_gen/signals-marshal.h"

static const DBusGObjectInfo _tp_svc_channel_dispatcher_object_info;

struct _TpSvcChannelDispatcherClass {
    GTypeInterface parent_class;
    tp_svc_channel_dispatcher_create_channel_impl create_channel;
    tp_svc_channel_dispatcher_ensure_channel_impl ensure_channel;
};

static void tp_svc_channel_dispatcher_base_init (gpointer klass);

GType
tp_svc_channel_dispatcher_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelDispatcherClass),
        tp_svc_channel_dispatcher_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelDispatcher", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_dispatcher_create_channel_impl:
 * @self: The object implementing this interface
 * @in_Account: const gchar * (FIXME, generate documentation)
 * @in_Requested_Properties: GHashTable * (FIXME, generate documentation)
 * @in_User_Action_Time: gint64  (FIXME, generate documentation)
 * @in_Preferred_Handler: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * CreateChannel on interface org.freedesktop.Telepathy.ChannelDispatcher.
 */
static void
tp_svc_channel_dispatcher_create_channel (TpSvcChannelDispatcher *self,
    const gchar *in_Account,
    GHashTable *in_Requested_Properties,
    gint64 in_User_Action_Time,
    const gchar *in_Preferred_Handler,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_dispatcher_create_channel_impl impl = (TP_SVC_CHANNEL_DISPATCHER_GET_CLASS (self)->create_channel);

  if (impl != NULL)
    {
      (impl) (self,
        in_Account,
        in_Requested_Properties,
        in_User_Action_Time,
        in_Preferred_Handler,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_dispatcher_implement_create_channel:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the CreateChannel D-Bus method
 *
 * Register an implementation for the CreateChannel method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_dispatcher_implement_create_channel (TpSvcChannelDispatcherClass *klass, tp_svc_channel_dispatcher_create_channel_impl impl)
{
  klass->create_channel = impl;
}

/**
 * tp_svc_channel_dispatcher_ensure_channel_impl:
 * @self: The object implementing this interface
 * @in_Account: const gchar * (FIXME, generate documentation)
 * @in_Requested_Properties: GHashTable * (FIXME, generate documentation)
 * @in_User_Action_Time: gint64  (FIXME, generate documentation)
 * @in_Preferred_Handler: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * EnsureChannel on interface org.freedesktop.Telepathy.ChannelDispatcher.
 */
static void
tp_svc_channel_dispatcher_ensure_channel (TpSvcChannelDispatcher *self,
    const gchar *in_Account,
    GHashTable *in_Requested_Properties,
    gint64 in_User_Action_Time,
    const gchar *in_Preferred_Handler,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_dispatcher_ensure_channel_impl impl = (TP_SVC_CHANNEL_DISPATCHER_GET_CLASS (self)->ensure_channel);

  if (impl != NULL)
    {
      (impl) (self,
        in_Account,
        in_Requested_Properties,
        in_User_Action_Time,
        in_Preferred_Handler,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_dispatcher_implement_ensure_channel:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the EnsureChannel D-Bus method
 *
 * Register an implementation for the EnsureChannel method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_dispatcher_implement_ensure_channel (TpSvcChannelDispatcherClass *klass, tp_svc_channel_dispatcher_ensure_channel_impl impl)
{
  klass->ensure_channel = impl;
}

static inline void
tp_svc_channel_dispatcher_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[2] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "as", 0, NULL, NULL }, /* Interfaces */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_channel_dispatcher_get_type (),
      &_tp_svc_channel_dispatcher_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.ChannelDispatcher");
  properties[0].name = g_quark_from_static_string ("Interfaces");
  properties[0].type = G_TYPE_STRV;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CHANNEL_DISPATCHER, &interface);

}
static void
tp_svc_channel_dispatcher_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_dispatcher_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_dispatcher_methods[] = {
  { (GCallback) tp_svc_channel_dispatcher_create_channel, _tp_marshal_VOID__BOXED_BOXED_INT64_STRING_POINTER, 0 },
  { (GCallback) tp_svc_channel_dispatcher_ensure_channel, _tp_marshal_VOID__BOXED_BOXED_INT64_STRING_POINTER, 161 },
};

static const DBusGObjectInfo _tp_svc_channel_dispatcher_object_info = {
  0,
  _tp_svc_channel_dispatcher_methods,
  2,
"org.freedesktop.Telepathy.ChannelDispatcher\0CreateChannel\0A\0Account\0I\0o\0Requested_Properties\0I\0a{sv}\0User_Action_Time\0I\0x\0Preferred_Handler\0I\0s\0Request\0O\0F\0N\0o\0\0org.freedesktop.Telepathy.ChannelDispatcher\0EnsureChannel\0A\0Account\0I\0o\0Requested_Properties\0I\0a{sv}\0User_Action_Time\0I\0x\0Preferred_Handler\0I\0s\0Request\0O\0F\0N\0o\0\0\0",
"\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_dispatcher_interface_operation_list_object_info;

struct _TpSvcChannelDispatcherInterfaceOperationListClass {
    GTypeInterface parent_class;
};

enum {
    SIGNAL_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST_NewDispatchOperation,
    SIGNAL_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST_DispatchOperationFinished,
    N_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST_SIGNALS
};
static guint channel_dispatcher_interface_operation_list_signals[N_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST_SIGNALS] = {0};

static void tp_svc_channel_dispatcher_interface_operation_list_base_init (gpointer klass);

GType
tp_svc_channel_dispatcher_interface_operation_list_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelDispatcherInterfaceOperationListClass),
        tp_svc_channel_dispatcher_interface_operation_list_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelDispatcherInterfaceOperationList", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_dispatcher_interface_operation_list_emit_new_dispatch_operation:
 * @instance: The object implementing this interface
 * @arg_Dispatch_Operation: const gchar * (FIXME, generate documentation)
 * @arg_Properties: GHashTable * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * NewDispatchOperation signal on interface org.freedesktop.Telepathy.ChannelDispatcher.Interface.OperationList.
 */
void
tp_svc_channel_dispatcher_interface_operation_list_emit_new_dispatch_operation (gpointer instance,
    const gchar *arg_Dispatch_Operation,
    GHashTable *arg_Properties)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST));
  g_signal_emit (instance,
      channel_dispatcher_interface_operation_list_signals[SIGNAL_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST_NewDispatchOperation],
      0,
      arg_Dispatch_Operation,
      arg_Properties);
}

/**
 * tp_svc_channel_dispatcher_interface_operation_list_emit_dispatch_operation_finished:
 * @instance: The object implementing this interface
 * @arg_Dispatch_Operation: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * DispatchOperationFinished signal on interface org.freedesktop.Telepathy.ChannelDispatcher.Interface.OperationList.
 */
void
tp_svc_channel_dispatcher_interface_operation_list_emit_dispatch_operation_finished (gpointer instance,
    const gchar *arg_Dispatch_Operation)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST));
  g_signal_emit (instance,
      channel_dispatcher_interface_operation_list_signals[SIGNAL_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST_DispatchOperationFinished],
      0,
      arg_Dispatch_Operation);
}

static inline void
tp_svc_channel_dispatcher_interface_operation_list_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[2] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "a(oa{sv})", 0, NULL, NULL }, /* DispatchOperations */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_channel_dispatcher_interface_operation_list_get_type (),
      &_tp_svc_channel_dispatcher_interface_operation_list_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.ChannelDispatcher.Interface.OperationList");
  properties[0].name = g_quark_from_static_string ("DispatchOperations");
  properties[0].type = (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID))));
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST, &interface);

  /**
   * TpSvcChannelDispatcherInterfaceOperationList::new-dispatch-operation:
   * @arg_Dispatch_Operation: const gchar * (FIXME, generate documentation)
   * @arg_Properties: GHashTable * (FIXME, generate documentation)
   *
   * The NewDispatchOperation D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_dispatcher_interface_operation_list_signals[SIGNAL_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST_NewDispatchOperation] =
  g_signal_new ("new-dispatch-operation",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__BOXED_BOXED,
      G_TYPE_NONE,
      2,
      DBUS_TYPE_G_OBJECT_PATH,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)));

  /**
   * TpSvcChannelDispatcherInterfaceOperationList::dispatch-operation-finished:
   * @arg_Dispatch_Operation: const gchar * (FIXME, generate documentation)
   *
   * The DispatchOperationFinished D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_dispatcher_interface_operation_list_signals[SIGNAL_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST_DispatchOperationFinished] =
  g_signal_new ("dispatch-operation-finished",
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
tp_svc_channel_dispatcher_interface_operation_list_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_dispatcher_interface_operation_list_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_dispatcher_interface_operation_list_methods[] = {
  { NULL, NULL, 0 }
};

static const DBusGObjectInfo _tp_svc_channel_dispatcher_interface_operation_list_object_info = {
  0,
  _tp_svc_channel_dispatcher_interface_operation_list_methods,
  0,
"\0",
"org.freedesktop.Telepathy.ChannelDispatcher.Interface.OperationList\0NewDispatchOperation\0org.freedesktop.Telepathy.ChannelDispatcher.Interface.OperationList\0DispatchOperationFinished\0\0",
"\0\0",
};


