#include "_gen/tp-svc-generic.h"

#include <telepathy-glib/dbus.h>
#include "_gen/signals-marshal.h"

static const DBusGObjectInfo _tp_svc_dbus_introspectable_object_info;

struct _TpSvcDBusIntrospectableClass {
    GTypeInterface parent_class;
    tp_svc_dbus_introspectable_introspect_impl introspect;
};

static void tp_svc_dbus_introspectable_base_init (gpointer klass);

GType
tp_svc_dbus_introspectable_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcDBusIntrospectableClass),
        tp_svc_dbus_introspectable_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcDBusIntrospectable", &info, 0);
    }

  return type;
}

/**
 * tp_svc_dbus_introspectable_introspect_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Introspect on interface org.freedesktop.DBus.Introspectable.
 */
static void
tp_svc_dbus_introspectable_introspect (TpSvcDBusIntrospectable *self,
    DBusGMethodInvocation *context)
{
  tp_svc_dbus_introspectable_introspect_impl impl = (TP_SVC_DBUS_INTROSPECTABLE_GET_CLASS (self)->introspect);

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
 * tp_svc_dbus_introspectable_implement_introspect:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Introspect D-Bus method
 *
 * Register an implementation for the Introspect method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_dbus_introspectable_implement_introspect (TpSvcDBusIntrospectableClass *klass, tp_svc_dbus_introspectable_introspect_impl impl)
{
  klass->introspect = impl;
}

static inline void
tp_svc_dbus_introspectable_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_dbus_introspectable_get_type (),
      &_tp_svc_dbus_introspectable_object_info);

}
static void
tp_svc_dbus_introspectable_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_dbus_introspectable_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_dbus_introspectable_methods[] = {
  { (GCallback) tp_svc_dbus_introspectable_introspect, g_cclosure_marshal_VOID__POINTER, 0 },
};

static const DBusGObjectInfo _tp_svc_dbus_introspectable_object_info = {
  0,
  _tp_svc_dbus_introspectable_methods,
  1,
"org.freedesktop.DBus.Introspectable\0Introspect\0A\0XML_Data\0O\0F\0N\0s\0\0\0",
"\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_dbus_properties_object_info;

struct _TpSvcDBusPropertiesClass {
    GTypeInterface parent_class;
    tp_svc_dbus_properties_get_impl get;
    tp_svc_dbus_properties_set_impl set;
    tp_svc_dbus_properties_get_all_impl get_all;
};

static void tp_svc_dbus_properties_base_init (gpointer klass);

GType
tp_svc_dbus_properties_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcDBusPropertiesClass),
        tp_svc_dbus_properties_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcDBusProperties", &info, 0);
    }

  return type;
}

/**
 * tp_svc_dbus_properties_get_impl:
 * @self: The object implementing this interface
 * @in_Interface_Name: const gchar * (FIXME, generate documentation)
 * @in_Property_Name: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Get on interface org.freedesktop.DBus.Properties.
 */
static void
tp_svc_dbus_properties_get (TpSvcDBusProperties *self,
    const gchar *in_Interface_Name,
    const gchar *in_Property_Name,
    DBusGMethodInvocation *context)
{
  tp_svc_dbus_properties_get_impl impl = (TP_SVC_DBUS_PROPERTIES_GET_CLASS (self)->get);

  if (impl != NULL)
    {
      (impl) (self,
        in_Interface_Name,
        in_Property_Name,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_dbus_properties_implement_get:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Get D-Bus method
 *
 * Register an implementation for the Get method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_dbus_properties_implement_get (TpSvcDBusPropertiesClass *klass, tp_svc_dbus_properties_get_impl impl)
{
  klass->get = impl;
}

/**
 * tp_svc_dbus_properties_set_impl:
 * @self: The object implementing this interface
 * @in_Interface_Name: const gchar * (FIXME, generate documentation)
 * @in_Property_Name: const gchar * (FIXME, generate documentation)
 * @in_Value: const GValue * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Set on interface org.freedesktop.DBus.Properties.
 */
static void
tp_svc_dbus_properties_set (TpSvcDBusProperties *self,
    const gchar *in_Interface_Name,
    const gchar *in_Property_Name,
    const GValue *in_Value,
    DBusGMethodInvocation *context)
{
  tp_svc_dbus_properties_set_impl impl = (TP_SVC_DBUS_PROPERTIES_GET_CLASS (self)->set);

  if (impl != NULL)
    {
      (impl) (self,
        in_Interface_Name,
        in_Property_Name,
        in_Value,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_dbus_properties_implement_set:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Set D-Bus method
 *
 * Register an implementation for the Set method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_dbus_properties_implement_set (TpSvcDBusPropertiesClass *klass, tp_svc_dbus_properties_set_impl impl)
{
  klass->set = impl;
}

/**
 * tp_svc_dbus_properties_get_all_impl:
 * @self: The object implementing this interface
 * @in_Interface_Name: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetAll on interface org.freedesktop.DBus.Properties.
 */
static void
tp_svc_dbus_properties_get_all (TpSvcDBusProperties *self,
    const gchar *in_Interface_Name,
    DBusGMethodInvocation *context)
{
  tp_svc_dbus_properties_get_all_impl impl = (TP_SVC_DBUS_PROPERTIES_GET_CLASS (self)->get_all);

  if (impl != NULL)
    {
      (impl) (self,
        in_Interface_Name,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_dbus_properties_implement_get_all:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetAll D-Bus method
 *
 * Register an implementation for the GetAll method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_dbus_properties_implement_get_all (TpSvcDBusPropertiesClass *klass, tp_svc_dbus_properties_get_all_impl impl)
{
  klass->get_all = impl;
}

static inline void
tp_svc_dbus_properties_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_dbus_properties_get_type (),
      &_tp_svc_dbus_properties_object_info);

}
static void
tp_svc_dbus_properties_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_dbus_properties_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_dbus_properties_methods[] = {
  { (GCallback) tp_svc_dbus_properties_get, _tp_marshal_VOID__STRING_STRING_POINTER, 0 },
  { (GCallback) tp_svc_dbus_properties_set, _tp_marshal_VOID__STRING_STRING_BOXED_POINTER, 90 },
  { (GCallback) tp_svc_dbus_properties_get_all, _tp_marshal_VOID__STRING_POINTER, 176 },
};

static const DBusGObjectInfo _tp_svc_dbus_properties_object_info = {
  0,
  _tp_svc_dbus_properties_methods,
  3,
"org.freedesktop.DBus.Properties\0Get\0A\0Interface_Name\0I\0s\0Property_Name\0I\0s\0Value\0O\0F\0N\0v\0\0org.freedesktop.DBus.Properties\0Set\0A\0Interface_Name\0I\0s\0Property_Name\0I\0s\0Value\0I\0v\0\0org.freedesktop.DBus.Properties\0GetAll\0A\0Interface_Name\0I\0s\0Properties\0O\0F\0N\0a{sv}\0\0\0",
"\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_properties_interface_object_info;

struct _TpSvcPropertiesInterfaceClass {
    GTypeInterface parent_class;
    tp_svc_properties_interface_get_properties_impl get_properties;
    tp_svc_properties_interface_list_properties_impl list_properties;
    tp_svc_properties_interface_set_properties_impl set_properties;
};

enum {
    SIGNAL_PROPERTIES_INTERFACE_PropertiesChanged,
    SIGNAL_PROPERTIES_INTERFACE_PropertyFlagsChanged,
    N_PROPERTIES_INTERFACE_SIGNALS
};
static guint properties_interface_signals[N_PROPERTIES_INTERFACE_SIGNALS] = {0};

static void tp_svc_properties_interface_base_init (gpointer klass);

GType
tp_svc_properties_interface_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcPropertiesInterfaceClass),
        tp_svc_properties_interface_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcPropertiesInterface", &info, 0);
    }

  return type;
}

/**
 * tp_svc_properties_interface_get_properties_impl:
 * @self: The object implementing this interface
 * @in_Properties: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetProperties on interface org.freedesktop.Telepathy.Properties.
 */
static void
tp_svc_properties_interface_get_properties (TpSvcPropertiesInterface *self,
    const GArray *in_Properties,
    DBusGMethodInvocation *context)
{
  tp_svc_properties_interface_get_properties_impl impl = (TP_SVC_PROPERTIES_INTERFACE_GET_CLASS (self)->get_properties);

  if (impl != NULL)
    {
      (impl) (self,
        in_Properties,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_properties_interface_implement_get_properties:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetProperties D-Bus method
 *
 * Register an implementation for the GetProperties method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_properties_interface_implement_get_properties (TpSvcPropertiesInterfaceClass *klass, tp_svc_properties_interface_get_properties_impl impl)
{
  klass->get_properties = impl;
}

/**
 * tp_svc_properties_interface_list_properties_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * ListProperties on interface org.freedesktop.Telepathy.Properties.
 */
static void
tp_svc_properties_interface_list_properties (TpSvcPropertiesInterface *self,
    DBusGMethodInvocation *context)
{
  tp_svc_properties_interface_list_properties_impl impl = (TP_SVC_PROPERTIES_INTERFACE_GET_CLASS (self)->list_properties);

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
 * tp_svc_properties_interface_implement_list_properties:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the ListProperties D-Bus method
 *
 * Register an implementation for the ListProperties method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_properties_interface_implement_list_properties (TpSvcPropertiesInterfaceClass *klass, tp_svc_properties_interface_list_properties_impl impl)
{
  klass->list_properties = impl;
}

/**
 * tp_svc_properties_interface_set_properties_impl:
 * @self: The object implementing this interface
 * @in_Properties: const GPtrArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SetProperties on interface org.freedesktop.Telepathy.Properties.
 */
static void
tp_svc_properties_interface_set_properties (TpSvcPropertiesInterface *self,
    const GPtrArray *in_Properties,
    DBusGMethodInvocation *context)
{
  tp_svc_properties_interface_set_properties_impl impl = (TP_SVC_PROPERTIES_INTERFACE_GET_CLASS (self)->set_properties);

  if (impl != NULL)
    {
      (impl) (self,
        in_Properties,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_properties_interface_implement_set_properties:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SetProperties D-Bus method
 *
 * Register an implementation for the SetProperties method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_properties_interface_implement_set_properties (TpSvcPropertiesInterfaceClass *klass, tp_svc_properties_interface_set_properties_impl impl)
{
  klass->set_properties = impl;
}

/**
 * tp_svc_properties_interface_emit_properties_changed:
 * @instance: The object implementing this interface
 * @arg_Properties: const GPtrArray * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * PropertiesChanged signal on interface org.freedesktop.Telepathy.Properties.
 */
void
tp_svc_properties_interface_emit_properties_changed (gpointer instance,
    const GPtrArray *arg_Properties)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_PROPERTIES_INTERFACE));
  g_signal_emit (instance,
      properties_interface_signals[SIGNAL_PROPERTIES_INTERFACE_PropertiesChanged],
      0,
      arg_Properties);
}

/**
 * tp_svc_properties_interface_emit_property_flags_changed:
 * @instance: The object implementing this interface
 * @arg_Properties: const GPtrArray * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * PropertyFlagsChanged signal on interface org.freedesktop.Telepathy.Properties.
 */
void
tp_svc_properties_interface_emit_property_flags_changed (gpointer instance,
    const GPtrArray *arg_Properties)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_PROPERTIES_INTERFACE));
  g_signal_emit (instance,
      properties_interface_signals[SIGNAL_PROPERTIES_INTERFACE_PropertyFlagsChanged],
      0,
      arg_Properties);
}

static inline void
tp_svc_properties_interface_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_properties_interface_get_type (),
      &_tp_svc_properties_interface_object_info);

  /**
   * TpSvcPropertiesInterface::properties-changed:
   * @arg_Properties: const GPtrArray * (FIXME, generate documentation)
   *
   * The PropertiesChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  properties_interface_signals[SIGNAL_PROPERTIES_INTERFACE_PropertiesChanged] =
  g_signal_new ("properties-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,
      1,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_VALUE, G_TYPE_INVALID)))));

  /**
   * TpSvcPropertiesInterface::property-flags-changed:
   * @arg_Properties: const GPtrArray * (FIXME, generate documentation)
   *
   * The PropertyFlagsChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  properties_interface_signals[SIGNAL_PROPERTIES_INTERFACE_PropertyFlagsChanged] =
  g_signal_new ("property-flags-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,
      1,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))));

}
static void
tp_svc_properties_interface_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_properties_interface_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_properties_interface_methods[] = {
  { (GCallback) tp_svc_properties_interface_get_properties, _tp_marshal_VOID__BOXED_POINTER, 0 },
  { (GCallback) tp_svc_properties_interface_list_properties, g_cclosure_marshal_VOID__POINTER, 89 },
  { (GCallback) tp_svc_properties_interface_set_properties, _tp_marshal_VOID__BOXED_POINTER, 179 },
};

static const DBusGObjectInfo _tp_svc_properties_interface_object_info = {
  0,
  _tp_svc_properties_interface_methods,
  3,
"org.freedesktop.Telepathy.Properties\0GetProperties\0A\0Properties\0I\0au\0Values\0O\0F\0N\0a(uv)\0\0org.freedesktop.Telepathy.Properties\0ListProperties\0A\0Available_Properties\0O\0F\0N\0a(ussu)\0\0org.freedesktop.Telepathy.Properties\0SetProperties\0A\0Properties\0I\0a(uv)\0\0\0",
"org.freedesktop.Telepathy.Properties\0PropertiesChanged\0org.freedesktop.Telepathy.Properties\0PropertyFlagsChanged\0\0",
"\0\0",
};


