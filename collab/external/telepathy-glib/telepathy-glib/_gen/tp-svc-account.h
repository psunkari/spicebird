#include <glib-object.h>
#include <dbus/dbus-glib.h>
#include <telepathy-glib/dbus-properties-mixin.h>

G_BEGIN_DECLS

/**
 * TpSvcAccount:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcAccount TpSvcAccount;

/**
 * TpSvcAccountClass:
 *
 * The class of TpSvcAccount.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_account (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_account_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (remove);
 *   IMPLEMENT (update_parameters);
 *   IMPLEMENT (reconnect);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcAccountClass TpSvcAccountClass;

GType tp_svc_account_get_type (void);
#define TP_TYPE_SVC_ACCOUNT \
  (tp_svc_account_get_type ())
#define TP_SVC_ACCOUNT(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_ACCOUNT, TpSvcAccount))
#define TP_IS_SVC_ACCOUNT(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_ACCOUNT))
#define TP_SVC_ACCOUNT_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_ACCOUNT, TpSvcAccountClass))


typedef void (*tp_svc_account_remove_impl) (TpSvcAccount *self,
    DBusGMethodInvocation *context);
void tp_svc_account_implement_remove (TpSvcAccountClass *klass, tp_svc_account_remove_impl impl);
/**
 * tp_svc_account_return_from_remove:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_account_return_from_remove (DBusGMethodInvocation *context);
static inline void
tp_svc_account_return_from_remove (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_account_update_parameters_impl) (TpSvcAccount *self,
    GHashTable *in_Set,
    const gchar **in_Unset,
    DBusGMethodInvocation *context);
void tp_svc_account_implement_update_parameters (TpSvcAccountClass *klass, tp_svc_account_update_parameters_impl impl);
/**
 * tp_svc_account_return_from_update_parameters:
 * @context: The D-Bus method invocation context
 * @out_Reconnect_Required: const gchar ** (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_account_return_from_update_parameters (DBusGMethodInvocation *context,
    const gchar **out_Reconnect_Required);
static inline void
tp_svc_account_return_from_update_parameters (DBusGMethodInvocation *context,
    const gchar **out_Reconnect_Required)
{
  dbus_g_method_return (context,
      out_Reconnect_Required);
}

typedef void (*tp_svc_account_reconnect_impl) (TpSvcAccount *self,
    DBusGMethodInvocation *context);
void tp_svc_account_implement_reconnect (TpSvcAccountClass *klass, tp_svc_account_reconnect_impl impl);
/**
 * tp_svc_account_return_from_reconnect:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_account_return_from_reconnect (DBusGMethodInvocation *context);
static inline void
tp_svc_account_return_from_reconnect (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

void tp_svc_account_emit_removed (gpointer instance);
void tp_svc_account_emit_account_property_changed (gpointer instance,
    GHashTable *arg_Properties);

/**
 * TpSvcAccountInterfaceAvatar:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcAccountInterfaceAvatar TpSvcAccountInterfaceAvatar;

/**
 * TpSvcAccountInterfaceAvatarClass:
 *
 * The class of TpSvcAccountInterfaceAvatar.
 * This interface has no D-Bus methods, so an
 * implementation can typically pass %NULL to
 * G_IMPLEMENT_INTERFACE() as the interface
 * initialization function.
 */
typedef struct _TpSvcAccountInterfaceAvatarClass TpSvcAccountInterfaceAvatarClass;

GType tp_svc_account_interface_avatar_get_type (void);
#define TP_TYPE_SVC_ACCOUNT_INTERFACE_AVATAR \
  (tp_svc_account_interface_avatar_get_type ())
#define TP_SVC_ACCOUNT_INTERFACE_AVATAR(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_ACCOUNT_INTERFACE_AVATAR, TpSvcAccountInterfaceAvatar))
#define TP_IS_SVC_ACCOUNT_INTERFACE_AVATAR(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_ACCOUNT_INTERFACE_AVATAR))
#define TP_SVC_ACCOUNT_INTERFACE_AVATAR_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_ACCOUNT_INTERFACE_AVATAR, TpSvcAccountInterfaceAvatarClass))


void tp_svc_account_interface_avatar_emit_avatar_changed (gpointer instance);


G_END_DECLS
