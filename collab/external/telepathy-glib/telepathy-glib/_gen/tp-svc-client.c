#include "_gen/tp-svc-client.h"

#include <telepathy-glib/dbus.h>
#include "_gen/signals-marshal.h"

static const DBusGObjectInfo _tp_svc_client_object_info;

struct _TpSvcClientClass {
    GTypeInterface parent_class;
};

static void tp_svc_client_base_init (gpointer klass);

GType
tp_svc_client_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcClientClass),
        tp_svc_client_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcClient", &info, 0);
    }

  return type;
}

static inline void
tp_svc_client_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[2] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "as", 0, NULL, NULL }, /* Interfaces */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_client_get_type (),
      &_tp_svc_client_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Client");
  properties[0].name = g_quark_from_static_string ("Interfaces");
  properties[0].type = G_TYPE_STRV;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CLIENT, &interface);

}
static void
tp_svc_client_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_client_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_client_methods[] = {
  { NULL, NULL, 0 }
};

static const DBusGObjectInfo _tp_svc_client_object_info = {
  0,
  _tp_svc_client_methods,
  0,
"\0",
"\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_client_approver_object_info;

struct _TpSvcClientApproverClass {
    GTypeInterface parent_class;
    tp_svc_client_approver_add_dispatch_operation_impl add_dispatch_operation;
};

static void tp_svc_client_approver_base_init (gpointer klass);

GType
tp_svc_client_approver_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcClientApproverClass),
        tp_svc_client_approver_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcClientApprover", &info, 0);
    }

  return type;
}

/**
 * tp_svc_client_approver_add_dispatch_operation_impl:
 * @self: The object implementing this interface
 * @in_Channels: const GPtrArray * (FIXME, generate documentation)
 * @in_DispatchOperation: const gchar * (FIXME, generate documentation)
 * @in_Properties: GHashTable * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * AddDispatchOperation on interface org.freedesktop.Telepathy.Client.Approver.
 */
static void
tp_svc_client_approver_add_dispatch_operation (TpSvcClientApprover *self,
    const GPtrArray *in_Channels,
    const gchar *in_DispatchOperation,
    GHashTable *in_Properties,
    DBusGMethodInvocation *context)
{
  tp_svc_client_approver_add_dispatch_operation_impl impl = (TP_SVC_CLIENT_APPROVER_GET_CLASS (self)->add_dispatch_operation);

  if (impl != NULL)
    {
      (impl) (self,
        in_Channels,
        in_DispatchOperation,
        in_Properties,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_client_approver_implement_add_dispatch_operation:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the AddDispatchOperation D-Bus method
 *
 * Register an implementation for the AddDispatchOperation method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_client_approver_implement_add_dispatch_operation (TpSvcClientApproverClass *klass, tp_svc_client_approver_add_dispatch_operation_impl impl)
{
  klass->add_dispatch_operation = impl;
}

static inline void
tp_svc_client_approver_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[2] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "aa{sv}", 0, NULL, NULL }, /* ApproverChannelFilter */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_client_approver_get_type (),
      &_tp_svc_client_approver_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Client.Approver");
  properties[0].name = g_quark_from_static_string ("ApproverChannelFilter");
  properties[0].type = (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE))));
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CLIENT_APPROVER, &interface);

}
static void
tp_svc_client_approver_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_client_approver_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_client_approver_methods[] = {
  { (GCallback) tp_svc_client_approver_add_dispatch_operation, _tp_marshal_VOID__BOXED_BOXED_BOXED_POINTER, 0 },
};

static const DBusGObjectInfo _tp_svc_client_approver_object_info = {
  0,
  _tp_svc_client_approver_methods,
  1,
"org.freedesktop.Telepathy.Client.Approver\0AddDispatchOperation\0A\0Channels\0I\0a(oa{sv})\0DispatchOperation\0I\0o\0Properties\0I\0a{sv}\0\0\0",
"\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_client_handler_object_info;

struct _TpSvcClientHandlerClass {
    GTypeInterface parent_class;
    tp_svc_client_handler_handle_channels_impl handle_channels;
};

static void tp_svc_client_handler_base_init (gpointer klass);

GType
tp_svc_client_handler_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcClientHandlerClass),
        tp_svc_client_handler_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcClientHandler", &info, 0);
    }

  return type;
}

/**
 * tp_svc_client_handler_handle_channels_impl:
 * @self: The object implementing this interface
 * @in_Account: const gchar * (FIXME, generate documentation)
 * @in_Connection: const gchar * (FIXME, generate documentation)
 * @in_Channels: const GPtrArray * (FIXME, generate documentation)
 * @in_Requests_Satisfied: const GPtrArray * (FIXME, generate documentation)
 * @in_User_Action_Time: guint64  (FIXME, generate documentation)
 * @in_Handler_Info: GHashTable * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * HandleChannels on interface org.freedesktop.Telepathy.Client.Handler.
 */
static void
tp_svc_client_handler_handle_channels (TpSvcClientHandler *self,
    const gchar *in_Account,
    const gchar *in_Connection,
    const GPtrArray *in_Channels,
    const GPtrArray *in_Requests_Satisfied,
    guint64 in_User_Action_Time,
    GHashTable *in_Handler_Info,
    DBusGMethodInvocation *context)
{
  tp_svc_client_handler_handle_channels_impl impl = (TP_SVC_CLIENT_HANDLER_GET_CLASS (self)->handle_channels);

  if (impl != NULL)
    {
      (impl) (self,
        in_Account,
        in_Connection,
        in_Channels,
        in_Requests_Satisfied,
        in_User_Action_Time,
        in_Handler_Info,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_client_handler_implement_handle_channels:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the HandleChannels D-Bus method
 *
 * Register an implementation for the HandleChannels method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_client_handler_implement_handle_channels (TpSvcClientHandlerClass *klass, tp_svc_client_handler_handle_channels_impl impl)
{
  klass->handle_channels = impl;
}

static inline void
tp_svc_client_handler_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[5] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "aa{sv}", 0, NULL, NULL }, /* HandlerChannelFilter */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "b", 0, NULL, NULL }, /* BypassApproval */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "as", 0, NULL, NULL }, /* Capabilities */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "ao", 0, NULL, NULL }, /* HandledChannels */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_client_handler_get_type (),
      &_tp_svc_client_handler_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Client.Handler");
  properties[0].name = g_quark_from_static_string ("HandlerChannelFilter");
  properties[0].type = (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE))));
  properties[1].name = g_quark_from_static_string ("BypassApproval");
  properties[1].type = G_TYPE_BOOLEAN;
  properties[2].name = g_quark_from_static_string ("Capabilities");
  properties[2].type = G_TYPE_STRV;
  properties[3].name = g_quark_from_static_string ("HandledChannels");
  properties[3].type = dbus_g_type_get_collection ("GPtrArray", DBUS_TYPE_G_OBJECT_PATH);
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CLIENT_HANDLER, &interface);

}
static void
tp_svc_client_handler_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_client_handler_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_client_handler_methods[] = {
  { (GCallback) tp_svc_client_handler_handle_channels, _tp_marshal_VOID__BOXED_BOXED_BOXED_BOXED_UINT64_BOXED_POINTER, 0 },
};

static const DBusGObjectInfo _tp_svc_client_handler_object_info = {
  0,
  _tp_svc_client_handler_methods,
  1,
"org.freedesktop.Telepathy.Client.Handler\0HandleChannels\0A\0Account\0I\0o\0Connection\0I\0o\0Channels\0I\0a(oa{sv})\0Requests_Satisfied\0I\0ao\0User_Action_Time\0I\0t\0Handler_Info\0I\0a{sv}\0\0\0",
"\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_client_interface_requests_object_info;

struct _TpSvcClientInterfaceRequestsClass {
    GTypeInterface parent_class;
    tp_svc_client_interface_requests_add_request_impl add_request;
    tp_svc_client_interface_requests_remove_request_impl remove_request;
};

static void tp_svc_client_interface_requests_base_init (gpointer klass);

GType
tp_svc_client_interface_requests_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcClientInterfaceRequestsClass),
        tp_svc_client_interface_requests_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcClientInterfaceRequests", &info, 0);
    }

  return type;
}

/**
 * tp_svc_client_interface_requests_add_request_impl:
 * @self: The object implementing this interface
 * @in_Request: const gchar * (FIXME, generate documentation)
 * @in_Properties: GHashTable * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * AddRequest on interface org.freedesktop.Telepathy.Client.Interface.Requests.
 */
static void
tp_svc_client_interface_requests_add_request (TpSvcClientInterfaceRequests *self,
    const gchar *in_Request,
    GHashTable *in_Properties,
    DBusGMethodInvocation *context)
{
  tp_svc_client_interface_requests_add_request_impl impl = (TP_SVC_CLIENT_INTERFACE_REQUESTS_GET_CLASS (self)->add_request);

  if (impl != NULL)
    {
      (impl) (self,
        in_Request,
        in_Properties,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_client_interface_requests_implement_add_request:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the AddRequest D-Bus method
 *
 * Register an implementation for the AddRequest method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_client_interface_requests_implement_add_request (TpSvcClientInterfaceRequestsClass *klass, tp_svc_client_interface_requests_add_request_impl impl)
{
  klass->add_request = impl;
}

/**
 * tp_svc_client_interface_requests_remove_request_impl:
 * @self: The object implementing this interface
 * @in_Request: const gchar * (FIXME, generate documentation)
 * @in_Error: const gchar * (FIXME, generate documentation)
 * @in_Message: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RemoveRequest on interface org.freedesktop.Telepathy.Client.Interface.Requests.
 */
static void
tp_svc_client_interface_requests_remove_request (TpSvcClientInterfaceRequests *self,
    const gchar *in_Request,
    const gchar *in_Error,
    const gchar *in_Message,
    DBusGMethodInvocation *context)
{
  tp_svc_client_interface_requests_remove_request_impl impl = (TP_SVC_CLIENT_INTERFACE_REQUESTS_GET_CLASS (self)->remove_request);

  if (impl != NULL)
    {
      (impl) (self,
        in_Request,
        in_Error,
        in_Message,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_client_interface_requests_implement_remove_request:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RemoveRequest D-Bus method
 *
 * Register an implementation for the RemoveRequest method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_client_interface_requests_implement_remove_request (TpSvcClientInterfaceRequestsClass *klass, tp_svc_client_interface_requests_remove_request_impl impl)
{
  klass->remove_request = impl;
}

static inline void
tp_svc_client_interface_requests_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_client_interface_requests_get_type (),
      &_tp_svc_client_interface_requests_object_info);

}
static void
tp_svc_client_interface_requests_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_client_interface_requests_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_client_interface_requests_methods[] = {
  { (GCallback) tp_svc_client_interface_requests_add_request, _tp_marshal_VOID__BOXED_BOXED_POINTER, 0 },
  { (GCallback) tp_svc_client_interface_requests_remove_request, _tp_marshal_VOID__BOXED_STRING_STRING_POINTER, 97 },
};

static const DBusGObjectInfo _tp_svc_client_interface_requests_object_info = {
  0,
  _tp_svc_client_interface_requests_methods,
  2,
"org.freedesktop.Telepathy.Client.Interface.Requests\0AddRequest\0A\0Request\0I\0o\0Properties\0I\0a{sv}\0\0org.freedesktop.Telepathy.Client.Interface.Requests\0RemoveRequest\0A\0Request\0I\0o\0Error\0I\0s\0Message\0I\0s\0\0\0",
"\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_client_observer_object_info;

struct _TpSvcClientObserverClass {
    GTypeInterface parent_class;
    tp_svc_client_observer_observe_channels_impl observe_channels;
};

static void tp_svc_client_observer_base_init (gpointer klass);

GType
tp_svc_client_observer_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcClientObserverClass),
        tp_svc_client_observer_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcClientObserver", &info, 0);
    }

  return type;
}

/**
 * tp_svc_client_observer_observe_channels_impl:
 * @self: The object implementing this interface
 * @in_Account: const gchar * (FIXME, generate documentation)
 * @in_Connection: const gchar * (FIXME, generate documentation)
 * @in_Channels: const GPtrArray * (FIXME, generate documentation)
 * @in_Dispatch_Operation: const gchar * (FIXME, generate documentation)
 * @in_Requests_Satisfied: const GPtrArray * (FIXME, generate documentation)
 * @in_Observer_Info: GHashTable * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * ObserveChannels on interface org.freedesktop.Telepathy.Client.Observer.
 */
static void
tp_svc_client_observer_observe_channels (TpSvcClientObserver *self,
    const gchar *in_Account,
    const gchar *in_Connection,
    const GPtrArray *in_Channels,
    const gchar *in_Dispatch_Operation,
    const GPtrArray *in_Requests_Satisfied,
    GHashTable *in_Observer_Info,
    DBusGMethodInvocation *context)
{
  tp_svc_client_observer_observe_channels_impl impl = (TP_SVC_CLIENT_OBSERVER_GET_CLASS (self)->observe_channels);

  if (impl != NULL)
    {
      (impl) (self,
        in_Account,
        in_Connection,
        in_Channels,
        in_Dispatch_Operation,
        in_Requests_Satisfied,
        in_Observer_Info,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_client_observer_implement_observe_channels:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the ObserveChannels D-Bus method
 *
 * Register an implementation for the ObserveChannels method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_client_observer_implement_observe_channels (TpSvcClientObserverClass *klass, tp_svc_client_observer_observe_channels_impl impl)
{
  klass->observe_channels = impl;
}

static inline void
tp_svc_client_observer_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[2] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "aa{sv}", 0, NULL, NULL }, /* ObserverChannelFilter */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_client_observer_get_type (),
      &_tp_svc_client_observer_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Client.Observer");
  properties[0].name = g_quark_from_static_string ("ObserverChannelFilter");
  properties[0].type = (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE))));
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CLIENT_OBSERVER, &interface);

}
static void
tp_svc_client_observer_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_client_observer_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_client_observer_methods[] = {
  { (GCallback) tp_svc_client_observer_observe_channels, _tp_marshal_VOID__BOXED_BOXED_BOXED_BOXED_BOXED_BOXED_POINTER, 0 },
};

static const DBusGObjectInfo _tp_svc_client_observer_object_info = {
  0,
  _tp_svc_client_observer_methods,
  1,
"org.freedesktop.Telepathy.Client.Observer\0ObserveChannels\0A\0Account\0I\0o\0Connection\0I\0o\0Channels\0I\0a(oa{sv})\0Dispatch_Operation\0I\0o\0Requests_Satisfied\0I\0ao\0Observer_Info\0I\0a{sv}\0\0\0",
"\0\0",
"\0\0",
};


