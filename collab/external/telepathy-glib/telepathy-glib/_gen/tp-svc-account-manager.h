#include <glib-object.h>
#include <dbus/dbus-glib.h>
#include <telepathy-glib/dbus-properties-mixin.h>

G_BEGIN_DECLS

/**
 * TpSvcAccountManager:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcAccountManager TpSvcAccountManager;

/**
 * TpSvcAccountManagerClass:
 *
 * The class of TpSvcAccountManager.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_account_manager (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_account_manager_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (create_account);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcAccountManagerClass TpSvcAccountManagerClass;

GType tp_svc_account_manager_get_type (void);
#define TP_TYPE_SVC_ACCOUNT_MANAGER \
  (tp_svc_account_manager_get_type ())
#define TP_SVC_ACCOUNT_MANAGER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_ACCOUNT_MANAGER, TpSvcAccountManager))
#define TP_IS_SVC_ACCOUNT_MANAGER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_ACCOUNT_MANAGER))
#define TP_SVC_ACCOUNT_MANAGER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_ACCOUNT_MANAGER, TpSvcAccountManagerClass))


typedef void (*tp_svc_account_manager_create_account_impl) (TpSvcAccountManager *self,
    const gchar *in_Connection_Manager,
    const gchar *in_Protocol,
    const gchar *in_Display_Name,
    GHashTable *in_Parameters,
    GHashTable *in_Properties,
    DBusGMethodInvocation *context);
void tp_svc_account_manager_implement_create_account (TpSvcAccountManagerClass *klass, tp_svc_account_manager_create_account_impl impl);
/**
 * tp_svc_account_manager_return_from_create_account:
 * @context: The D-Bus method invocation context
 * @out_Account: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_account_manager_return_from_create_account (DBusGMethodInvocation *context,
    const gchar *out_Account);
static inline void
tp_svc_account_manager_return_from_create_account (DBusGMethodInvocation *context,
    const gchar *out_Account)
{
  dbus_g_method_return (context,
      out_Account);
}

void tp_svc_account_manager_emit_account_removed (gpointer instance,
    const gchar *arg_Account);
void tp_svc_account_manager_emit_account_validity_changed (gpointer instance,
    const gchar *arg_Account,
    gboolean arg_Valid);


G_END_DECLS
