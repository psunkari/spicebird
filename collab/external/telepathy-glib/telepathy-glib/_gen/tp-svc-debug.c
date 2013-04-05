#include "_gen/tp-svc-debug.h"

#include <telepathy-glib/dbus.h>
#include "_gen/signals-marshal.h"

static const DBusGObjectInfo _tp_svc_debug_object_info;

struct _TpSvcDebugClass {
    GTypeInterface parent_class;
    tp_svc_debug_get_messages_impl get_messages;
};

enum {
    SIGNAL_DEBUG_NewDebugMessage,
    N_DEBUG_SIGNALS
};
static guint debug_signals[N_DEBUG_SIGNALS] = {0};

static void tp_svc_debug_base_init (gpointer klass);

GType
tp_svc_debug_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcDebugClass),
        tp_svc_debug_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcDebug", &info, 0);
    }

  return type;
}

/**
 * tp_svc_debug_get_messages_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetMessages on interface org.freedesktop.Telepathy.Debug.
 */
static void
tp_svc_debug_get_messages (TpSvcDebug *self,
    DBusGMethodInvocation *context)
{
  tp_svc_debug_get_messages_impl impl = (TP_SVC_DEBUG_GET_CLASS (self)->get_messages);

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
 * tp_svc_debug_implement_get_messages:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetMessages D-Bus method
 *
 * Register an implementation for the GetMessages method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_debug_implement_get_messages (TpSvcDebugClass *klass, tp_svc_debug_get_messages_impl impl)
{
  klass->get_messages = impl;
}

/**
 * tp_svc_debug_emit_new_debug_message:
 * @instance: The object implementing this interface
 * @arg_time: gdouble  (FIXME, generate documentation)
 * @arg_domain: const gchar * (FIXME, generate documentation)
 * @arg_level: guint  (FIXME, generate documentation)
 * @arg_message: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * NewDebugMessage signal on interface org.freedesktop.Telepathy.Debug.
 */
void
tp_svc_debug_emit_new_debug_message (gpointer instance,
    gdouble arg_time,
    const gchar *arg_domain,
    guint arg_level,
    const gchar *arg_message)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_DEBUG));
  g_signal_emit (instance,
      debug_signals[SIGNAL_DEBUG_NewDebugMessage],
      0,
      arg_time,
      arg_domain,
      arg_level,
      arg_message);
}

static inline void
tp_svc_debug_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[2] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ | TP_DBUS_PROPERTIES_MIXIN_FLAG_WRITE, "b", 0, NULL, NULL }, /* Enabled */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_debug_get_type (),
      &_tp_svc_debug_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Debug");
  properties[0].name = g_quark_from_static_string ("Enabled");
  properties[0].type = G_TYPE_BOOLEAN;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_DEBUG, &interface);

  /**
   * TpSvcDebug::new-debug-message:
   * @arg_time: gdouble  (FIXME, generate documentation)
   * @arg_domain: const gchar * (FIXME, generate documentation)
   * @arg_level: guint  (FIXME, generate documentation)
   * @arg_message: const gchar * (FIXME, generate documentation)
   *
   * The NewDebugMessage D-Bus signal is emitted whenever this GObject signal is.
   */
  debug_signals[SIGNAL_DEBUG_NewDebugMessage] =
  g_signal_new ("new-debug-message",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__DOUBLE_STRING_UINT_STRING,
      G_TYPE_NONE,
      4,
      G_TYPE_DOUBLE,
      G_TYPE_STRING,
      G_TYPE_UINT,
      G_TYPE_STRING);

}
static void
tp_svc_debug_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_debug_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_debug_methods[] = {
  { (GCallback) tp_svc_debug_get_messages, g_cclosure_marshal_VOID__POINTER, 0 },
};

static const DBusGObjectInfo _tp_svc_debug_object_info = {
  0,
  _tp_svc_debug_methods,
  1,
"org.freedesktop.Telepathy.Debug\0GetMessages\0A\0Messages\0O\0F\0N\0a(dsus)\0\0\0",
"org.freedesktop.Telepathy.Debug\0NewDebugMessage\0\0",
"\0\0",
};


