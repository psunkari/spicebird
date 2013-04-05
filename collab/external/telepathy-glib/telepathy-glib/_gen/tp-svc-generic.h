#include <glib-object.h>
#include <dbus/dbus-glib.h>

G_BEGIN_DECLS

/**
 * TpSvcDBusIntrospectable:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcDBusIntrospectable TpSvcDBusIntrospectable;

/**
 * TpSvcDBusIntrospectableClass:
 *
 * The class of TpSvcDBusIntrospectable.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_dbus_introspectable (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_dbus_introspectable_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (introspect);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcDBusIntrospectableClass TpSvcDBusIntrospectableClass;

GType tp_svc_dbus_introspectable_get_type (void);
#define TP_TYPE_SVC_DBUS_INTROSPECTABLE \
  (tp_svc_dbus_introspectable_get_type ())
#define TP_SVC_DBUS_INTROSPECTABLE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_DBUS_INTROSPECTABLE, TpSvcDBusIntrospectable))
#define TP_IS_SVC_DBUS_INTROSPECTABLE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_DBUS_INTROSPECTABLE))
#define TP_SVC_DBUS_INTROSPECTABLE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_DBUS_INTROSPECTABLE, TpSvcDBusIntrospectableClass))


typedef void (*tp_svc_dbus_introspectable_introspect_impl) (TpSvcDBusIntrospectable *self,
    DBusGMethodInvocation *context);
void tp_svc_dbus_introspectable_implement_introspect (TpSvcDBusIntrospectableClass *klass, tp_svc_dbus_introspectable_introspect_impl impl);
/**
 * tp_svc_dbus_introspectable_return_from_introspect:
 * @context: The D-Bus method invocation context
 * @out_XML_Data: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_dbus_introspectable_return_from_introspect (DBusGMethodInvocation *context,
    const gchar *out_XML_Data);
static inline void
tp_svc_dbus_introspectable_return_from_introspect (DBusGMethodInvocation *context,
    const gchar *out_XML_Data)
{
  dbus_g_method_return (context,
      out_XML_Data);
}


/**
 * TpSvcDBusProperties:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcDBusProperties TpSvcDBusProperties;

/**
 * TpSvcDBusPropertiesClass:
 *
 * The class of TpSvcDBusProperties.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_dbus_properties (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_dbus_properties_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (get);
 *   IMPLEMENT (set);
 *   IMPLEMENT (get_all);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcDBusPropertiesClass TpSvcDBusPropertiesClass;

GType tp_svc_dbus_properties_get_type (void);
#define TP_TYPE_SVC_DBUS_PROPERTIES \
  (tp_svc_dbus_properties_get_type ())
#define TP_SVC_DBUS_PROPERTIES(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_DBUS_PROPERTIES, TpSvcDBusProperties))
#define TP_IS_SVC_DBUS_PROPERTIES(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_DBUS_PROPERTIES))
#define TP_SVC_DBUS_PROPERTIES_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_DBUS_PROPERTIES, TpSvcDBusPropertiesClass))


typedef void (*tp_svc_dbus_properties_get_impl) (TpSvcDBusProperties *self,
    const gchar *in_Interface_Name,
    const gchar *in_Property_Name,
    DBusGMethodInvocation *context);
void tp_svc_dbus_properties_implement_get (TpSvcDBusPropertiesClass *klass, tp_svc_dbus_properties_get_impl impl);
/**
 * tp_svc_dbus_properties_return_from_get:
 * @context: The D-Bus method invocation context
 * @out_Value: const GValue * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_dbus_properties_return_from_get (DBusGMethodInvocation *context,
    const GValue *out_Value);
static inline void
tp_svc_dbus_properties_return_from_get (DBusGMethodInvocation *context,
    const GValue *out_Value)
{
  dbus_g_method_return (context,
      out_Value);
}

typedef void (*tp_svc_dbus_properties_set_impl) (TpSvcDBusProperties *self,
    const gchar *in_Interface_Name,
    const gchar *in_Property_Name,
    const GValue *in_Value,
    DBusGMethodInvocation *context);
void tp_svc_dbus_properties_implement_set (TpSvcDBusPropertiesClass *klass, tp_svc_dbus_properties_set_impl impl);
/**
 * tp_svc_dbus_properties_return_from_set:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_dbus_properties_return_from_set (DBusGMethodInvocation *context);
static inline void
tp_svc_dbus_properties_return_from_set (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_dbus_properties_get_all_impl) (TpSvcDBusProperties *self,
    const gchar *in_Interface_Name,
    DBusGMethodInvocation *context);
void tp_svc_dbus_properties_implement_get_all (TpSvcDBusPropertiesClass *klass, tp_svc_dbus_properties_get_all_impl impl);
/**
 * tp_svc_dbus_properties_return_from_get_all:
 * @context: The D-Bus method invocation context
 * @out_Properties: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_dbus_properties_return_from_get_all (DBusGMethodInvocation *context,
    GHashTable *out_Properties);
static inline void
tp_svc_dbus_properties_return_from_get_all (DBusGMethodInvocation *context,
    GHashTable *out_Properties)
{
  dbus_g_method_return (context,
      out_Properties);
}


/**
 * TpSvcPropertiesInterface:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcPropertiesInterface TpSvcPropertiesInterface;

/**
 * TpSvcPropertiesInterfaceClass:
 *
 * The class of TpSvcPropertiesInterface.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_properties_interface (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_properties_interface_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (get_properties);
 *   IMPLEMENT (list_properties);
 *   IMPLEMENT (set_properties);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcPropertiesInterfaceClass TpSvcPropertiesInterfaceClass;

GType tp_svc_properties_interface_get_type (void);
#define TP_TYPE_SVC_PROPERTIES_INTERFACE \
  (tp_svc_properties_interface_get_type ())
#define TP_SVC_PROPERTIES_INTERFACE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_PROPERTIES_INTERFACE, TpSvcPropertiesInterface))
#define TP_IS_SVC_PROPERTIES_INTERFACE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_PROPERTIES_INTERFACE))
#define TP_SVC_PROPERTIES_INTERFACE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_PROPERTIES_INTERFACE, TpSvcPropertiesInterfaceClass))


typedef void (*tp_svc_properties_interface_get_properties_impl) (TpSvcPropertiesInterface *self,
    const GArray *in_Properties,
    DBusGMethodInvocation *context);
void tp_svc_properties_interface_implement_get_properties (TpSvcPropertiesInterfaceClass *klass, tp_svc_properties_interface_get_properties_impl impl);
/**
 * tp_svc_properties_interface_return_from_get_properties:
 * @context: The D-Bus method invocation context
 * @out_Values: const GPtrArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_properties_interface_return_from_get_properties (DBusGMethodInvocation *context,
    const GPtrArray *out_Values);
static inline void
tp_svc_properties_interface_return_from_get_properties (DBusGMethodInvocation *context,
    const GPtrArray *out_Values)
{
  dbus_g_method_return (context,
      out_Values);
}

typedef void (*tp_svc_properties_interface_list_properties_impl) (TpSvcPropertiesInterface *self,
    DBusGMethodInvocation *context);
void tp_svc_properties_interface_implement_list_properties (TpSvcPropertiesInterfaceClass *klass, tp_svc_properties_interface_list_properties_impl impl);
/**
 * tp_svc_properties_interface_return_from_list_properties:
 * @context: The D-Bus method invocation context
 * @out_Available_Properties: const GPtrArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_properties_interface_return_from_list_properties (DBusGMethodInvocation *context,
    const GPtrArray *out_Available_Properties);
static inline void
tp_svc_properties_interface_return_from_list_properties (DBusGMethodInvocation *context,
    const GPtrArray *out_Available_Properties)
{
  dbus_g_method_return (context,
      out_Available_Properties);
}

typedef void (*tp_svc_properties_interface_set_properties_impl) (TpSvcPropertiesInterface *self,
    const GPtrArray *in_Properties,
    DBusGMethodInvocation *context);
void tp_svc_properties_interface_implement_set_properties (TpSvcPropertiesInterfaceClass *klass, tp_svc_properties_interface_set_properties_impl impl);
/**
 * tp_svc_properties_interface_return_from_set_properties:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_properties_interface_return_from_set_properties (DBusGMethodInvocation *context);
static inline void
tp_svc_properties_interface_return_from_set_properties (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

void tp_svc_properties_interface_emit_properties_changed (gpointer instance,
    const GPtrArray *arg_Properties);
void tp_svc_properties_interface_emit_property_flags_changed (gpointer instance,
    const GPtrArray *arg_Properties);


G_END_DECLS
