#include <glib-object.h>
#include <dbus/dbus-glib.h>
#include <telepathy-glib/dbus-properties-mixin.h>

G_BEGIN_DECLS

/**
 * TpSvcConnection:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcConnection TpSvcConnection;

/**
 * TpSvcConnectionClass:
 *
 * The class of TpSvcConnection.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_connection (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_connection_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (connect);
 *   IMPLEMENT (disconnect);
 *   IMPLEMENT (get_interfaces);
 *   IMPLEMENT (get_protocol);
 *   IMPLEMENT (get_self_handle);
 *   IMPLEMENT (get_status);
 *   IMPLEMENT (hold_handles);
 *   IMPLEMENT (inspect_handles);
 *   IMPLEMENT (list_channels);
 *   IMPLEMENT (release_handles);
 *   IMPLEMENT (request_channel);
 *   IMPLEMENT (request_handles);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcConnectionClass TpSvcConnectionClass;

GType tp_svc_connection_get_type (void);
#define TP_TYPE_SVC_CONNECTION \
  (tp_svc_connection_get_type ())
#define TP_SVC_CONNECTION(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CONNECTION, TpSvcConnection))
#define TP_IS_SVC_CONNECTION(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CONNECTION))
#define TP_SVC_CONNECTION_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CONNECTION, TpSvcConnectionClass))


typedef void (*tp_svc_connection_connect_impl) (TpSvcConnection *self,
    DBusGMethodInvocation *context);
void tp_svc_connection_implement_connect (TpSvcConnectionClass *klass, tp_svc_connection_connect_impl impl);
/**
 * tp_svc_connection_return_from_connect:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_return_from_connect (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_return_from_connect (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_connection_disconnect_impl) (TpSvcConnection *self,
    DBusGMethodInvocation *context);
void tp_svc_connection_implement_disconnect (TpSvcConnectionClass *klass, tp_svc_connection_disconnect_impl impl);
/**
 * tp_svc_connection_return_from_disconnect:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_return_from_disconnect (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_return_from_disconnect (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_connection_get_interfaces_impl) (TpSvcConnection *self,
    DBusGMethodInvocation *context);
void tp_svc_connection_implement_get_interfaces (TpSvcConnectionClass *klass, tp_svc_connection_get_interfaces_impl impl);
/**
 * tp_svc_connection_return_from_get_interfaces:
 * @context: The D-Bus method invocation context
 * @out_Interfaces: const gchar ** (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_return_from_get_interfaces (DBusGMethodInvocation *context,
    const gchar **out_Interfaces);
static inline void
tp_svc_connection_return_from_get_interfaces (DBusGMethodInvocation *context,
    const gchar **out_Interfaces)
{
  dbus_g_method_return (context,
      out_Interfaces);
}

typedef void (*tp_svc_connection_get_protocol_impl) (TpSvcConnection *self,
    DBusGMethodInvocation *context);
void tp_svc_connection_implement_get_protocol (TpSvcConnectionClass *klass, tp_svc_connection_get_protocol_impl impl);
/**
 * tp_svc_connection_return_from_get_protocol:
 * @context: The D-Bus method invocation context
 * @out_Protocol: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_return_from_get_protocol (DBusGMethodInvocation *context,
    const gchar *out_Protocol);
static inline void
tp_svc_connection_return_from_get_protocol (DBusGMethodInvocation *context,
    const gchar *out_Protocol)
{
  dbus_g_method_return (context,
      out_Protocol);
}

typedef void (*tp_svc_connection_get_self_handle_impl) (TpSvcConnection *self,
    DBusGMethodInvocation *context);
void tp_svc_connection_implement_get_self_handle (TpSvcConnectionClass *klass, tp_svc_connection_get_self_handle_impl impl);
/**
 * tp_svc_connection_return_from_get_self_handle:
 * @context: The D-Bus method invocation context
 * @out_Self_Handle: guint  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_return_from_get_self_handle (DBusGMethodInvocation *context,
    guint out_Self_Handle);
static inline void
tp_svc_connection_return_from_get_self_handle (DBusGMethodInvocation *context,
    guint out_Self_Handle)
{
  dbus_g_method_return (context,
      out_Self_Handle);
}

typedef void (*tp_svc_connection_get_status_impl) (TpSvcConnection *self,
    DBusGMethodInvocation *context);
void tp_svc_connection_implement_get_status (TpSvcConnectionClass *klass, tp_svc_connection_get_status_impl impl);
/**
 * tp_svc_connection_return_from_get_status:
 * @context: The D-Bus method invocation context
 * @out_Status: guint  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_return_from_get_status (DBusGMethodInvocation *context,
    guint out_Status);
static inline void
tp_svc_connection_return_from_get_status (DBusGMethodInvocation *context,
    guint out_Status)
{
  dbus_g_method_return (context,
      out_Status);
}

typedef void (*tp_svc_connection_hold_handles_impl) (TpSvcConnection *self,
    guint in_Handle_Type,
    const GArray *in_Handles,
    DBusGMethodInvocation *context);
void tp_svc_connection_implement_hold_handles (TpSvcConnectionClass *klass, tp_svc_connection_hold_handles_impl impl);
/**
 * tp_svc_connection_return_from_hold_handles:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_return_from_hold_handles (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_return_from_hold_handles (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_connection_inspect_handles_impl) (TpSvcConnection *self,
    guint in_Handle_Type,
    const GArray *in_Handles,
    DBusGMethodInvocation *context);
void tp_svc_connection_implement_inspect_handles (TpSvcConnectionClass *klass, tp_svc_connection_inspect_handles_impl impl);
/**
 * tp_svc_connection_return_from_inspect_handles:
 * @context: The D-Bus method invocation context
 * @out_Identifiers: const gchar ** (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_return_from_inspect_handles (DBusGMethodInvocation *context,
    const gchar **out_Identifiers);
static inline void
tp_svc_connection_return_from_inspect_handles (DBusGMethodInvocation *context,
    const gchar **out_Identifiers)
{
  dbus_g_method_return (context,
      out_Identifiers);
}

typedef void (*tp_svc_connection_list_channels_impl) (TpSvcConnection *self,
    DBusGMethodInvocation *context);
void tp_svc_connection_implement_list_channels (TpSvcConnectionClass *klass, tp_svc_connection_list_channels_impl impl);
/**
 * tp_svc_connection_return_from_list_channels:
 * @context: The D-Bus method invocation context
 * @out_Channel_Info: const GPtrArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_return_from_list_channels (DBusGMethodInvocation *context,
    const GPtrArray *out_Channel_Info);
static inline void
tp_svc_connection_return_from_list_channels (DBusGMethodInvocation *context,
    const GPtrArray *out_Channel_Info)
{
  dbus_g_method_return (context,
      out_Channel_Info);
}

typedef void (*tp_svc_connection_release_handles_impl) (TpSvcConnection *self,
    guint in_Handle_Type,
    const GArray *in_Handles,
    DBusGMethodInvocation *context);
void tp_svc_connection_implement_release_handles (TpSvcConnectionClass *klass, tp_svc_connection_release_handles_impl impl);
/**
 * tp_svc_connection_return_from_release_handles:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_return_from_release_handles (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_return_from_release_handles (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_connection_request_channel_impl) (TpSvcConnection *self,
    const gchar *in_Type,
    guint in_Handle_Type,
    guint in_Handle,
    gboolean in_Suppress_Handler,
    DBusGMethodInvocation *context);
void tp_svc_connection_implement_request_channel (TpSvcConnectionClass *klass, tp_svc_connection_request_channel_impl impl);
/**
 * tp_svc_connection_return_from_request_channel:
 * @context: The D-Bus method invocation context
 * @out_Object_Path: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_return_from_request_channel (DBusGMethodInvocation *context,
    const gchar *out_Object_Path);
static inline void
tp_svc_connection_return_from_request_channel (DBusGMethodInvocation *context,
    const gchar *out_Object_Path)
{
  dbus_g_method_return (context,
      out_Object_Path);
}

typedef void (*tp_svc_connection_request_handles_impl) (TpSvcConnection *self,
    guint in_Handle_Type,
    const gchar **in_Identifiers,
    DBusGMethodInvocation *context);
void tp_svc_connection_implement_request_handles (TpSvcConnectionClass *klass, tp_svc_connection_request_handles_impl impl);
/**
 * tp_svc_connection_return_from_request_handles:
 * @context: The D-Bus method invocation context
 * @out_Handles: const GArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_return_from_request_handles (DBusGMethodInvocation *context,
    const GArray *out_Handles);
static inline void
tp_svc_connection_return_from_request_handles (DBusGMethodInvocation *context,
    const GArray *out_Handles)
{
  dbus_g_method_return (context,
      out_Handles);
}

void tp_svc_connection_emit_self_handle_changed (gpointer instance,
    guint arg_Self_Handle);
void tp_svc_connection_emit_new_channel (gpointer instance,
    const gchar *arg_Object_Path,
    const gchar *arg_Channel_Type,
    guint arg_Handle_Type,
    guint arg_Handle,
    gboolean arg_Suppress_Handler);
void tp_svc_connection_emit_connection_error (gpointer instance,
    const gchar *arg_Error,
    GHashTable *arg_Details);
void tp_svc_connection_emit_status_changed (gpointer instance,
    guint arg_Status,
    guint arg_Reason);

/**
 * TpSvcConnectionInterfaceAliasing:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcConnectionInterfaceAliasing TpSvcConnectionInterfaceAliasing;

/**
 * TpSvcConnectionInterfaceAliasingClass:
 *
 * The class of TpSvcConnectionInterfaceAliasing.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_connection_interface_aliasing (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_connection_interface_aliasing_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (get_alias_flags);
 *   IMPLEMENT (request_aliases);
 *   IMPLEMENT (get_aliases);
 *   IMPLEMENT (set_aliases);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcConnectionInterfaceAliasingClass TpSvcConnectionInterfaceAliasingClass;

GType tp_svc_connection_interface_aliasing_get_type (void);
#define TP_TYPE_SVC_CONNECTION_INTERFACE_ALIASING \
  (tp_svc_connection_interface_aliasing_get_type ())
#define TP_SVC_CONNECTION_INTERFACE_ALIASING(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_ALIASING, TpSvcConnectionInterfaceAliasing))
#define TP_IS_SVC_CONNECTION_INTERFACE_ALIASING(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_ALIASING))
#define TP_SVC_CONNECTION_INTERFACE_ALIASING_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_ALIASING, TpSvcConnectionInterfaceAliasingClass))


typedef void (*tp_svc_connection_interface_aliasing_get_alias_flags_impl) (TpSvcConnectionInterfaceAliasing *self,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_aliasing_implement_get_alias_flags (TpSvcConnectionInterfaceAliasingClass *klass, tp_svc_connection_interface_aliasing_get_alias_flags_impl impl);
/**
 * tp_svc_connection_interface_aliasing_return_from_get_alias_flags:
 * @context: The D-Bus method invocation context
 * @out_Alias_Flags: guint  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_aliasing_return_from_get_alias_flags (DBusGMethodInvocation *context,
    guint out_Alias_Flags);
static inline void
tp_svc_connection_interface_aliasing_return_from_get_alias_flags (DBusGMethodInvocation *context,
    guint out_Alias_Flags)
{
  dbus_g_method_return (context,
      out_Alias_Flags);
}

typedef void (*tp_svc_connection_interface_aliasing_request_aliases_impl) (TpSvcConnectionInterfaceAliasing *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_aliasing_implement_request_aliases (TpSvcConnectionInterfaceAliasingClass *klass, tp_svc_connection_interface_aliasing_request_aliases_impl impl);
/**
 * tp_svc_connection_interface_aliasing_return_from_request_aliases:
 * @context: The D-Bus method invocation context
 * @out_Aliases: const gchar ** (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_aliasing_return_from_request_aliases (DBusGMethodInvocation *context,
    const gchar **out_Aliases);
static inline void
tp_svc_connection_interface_aliasing_return_from_request_aliases (DBusGMethodInvocation *context,
    const gchar **out_Aliases)
{
  dbus_g_method_return (context,
      out_Aliases);
}

typedef void (*tp_svc_connection_interface_aliasing_get_aliases_impl) (TpSvcConnectionInterfaceAliasing *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_aliasing_implement_get_aliases (TpSvcConnectionInterfaceAliasingClass *klass, tp_svc_connection_interface_aliasing_get_aliases_impl impl);
/**
 * tp_svc_connection_interface_aliasing_return_from_get_aliases:
 * @context: The D-Bus method invocation context
 * @out_Aliases: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_aliasing_return_from_get_aliases (DBusGMethodInvocation *context,
    GHashTable *out_Aliases);
static inline void
tp_svc_connection_interface_aliasing_return_from_get_aliases (DBusGMethodInvocation *context,
    GHashTable *out_Aliases)
{
  dbus_g_method_return (context,
      out_Aliases);
}

typedef void (*tp_svc_connection_interface_aliasing_set_aliases_impl) (TpSvcConnectionInterfaceAliasing *self,
    GHashTable *in_Aliases,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_aliasing_implement_set_aliases (TpSvcConnectionInterfaceAliasingClass *klass, tp_svc_connection_interface_aliasing_set_aliases_impl impl);
/**
 * tp_svc_connection_interface_aliasing_return_from_set_aliases:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_aliasing_return_from_set_aliases (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_interface_aliasing_return_from_set_aliases (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

void tp_svc_connection_interface_aliasing_emit_aliases_changed (gpointer instance,
    const GPtrArray *arg_Aliases);

/**
 * TpSvcConnectionInterfaceAvatars:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcConnectionInterfaceAvatars TpSvcConnectionInterfaceAvatars;

/**
 * TpSvcConnectionInterfaceAvatarsClass:
 *
 * The class of TpSvcConnectionInterfaceAvatars.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_connection_interface_avatars (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_connection_interface_avatars_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (get_avatar_requirements);
 *   IMPLEMENT (get_avatar_tokens);
 *   IMPLEMENT (get_known_avatar_tokens);
 *   IMPLEMENT (request_avatar);
 *   IMPLEMENT (request_avatars);
 *   IMPLEMENT (set_avatar);
 *   IMPLEMENT (clear_avatar);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcConnectionInterfaceAvatarsClass TpSvcConnectionInterfaceAvatarsClass;

GType tp_svc_connection_interface_avatars_get_type (void);
#define TP_TYPE_SVC_CONNECTION_INTERFACE_AVATARS \
  (tp_svc_connection_interface_avatars_get_type ())
#define TP_SVC_CONNECTION_INTERFACE_AVATARS(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_AVATARS, TpSvcConnectionInterfaceAvatars))
#define TP_IS_SVC_CONNECTION_INTERFACE_AVATARS(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_AVATARS))
#define TP_SVC_CONNECTION_INTERFACE_AVATARS_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_AVATARS, TpSvcConnectionInterfaceAvatarsClass))


typedef void (*tp_svc_connection_interface_avatars_get_avatar_requirements_impl) (TpSvcConnectionInterfaceAvatars *self,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_avatars_implement_get_avatar_requirements (TpSvcConnectionInterfaceAvatarsClass *klass, tp_svc_connection_interface_avatars_get_avatar_requirements_impl impl);
/**
 * tp_svc_connection_interface_avatars_return_from_get_avatar_requirements:
 * @context: The D-Bus method invocation context
 * @out_MIME_Types: const gchar ** (FIXME, generate documentation)
 * @out_Min_Width: guint  (FIXME, generate documentation)
 * @out_Min_Height: guint  (FIXME, generate documentation)
 * @out_Max_Width: guint  (FIXME, generate documentation)
 * @out_Max_Height: guint  (FIXME, generate documentation)
 * @out_Max_Bytes: guint  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_avatars_return_from_get_avatar_requirements (DBusGMethodInvocation *context,
    const gchar **out_MIME_Types,
    guint out_Min_Width,
    guint out_Min_Height,
    guint out_Max_Width,
    guint out_Max_Height,
    guint out_Max_Bytes);
static inline void
tp_svc_connection_interface_avatars_return_from_get_avatar_requirements (DBusGMethodInvocation *context,
    const gchar **out_MIME_Types,
    guint out_Min_Width,
    guint out_Min_Height,
    guint out_Max_Width,
    guint out_Max_Height,
    guint out_Max_Bytes)
{
  dbus_g_method_return (context,
      out_MIME_Types,
      out_Min_Width,
      out_Min_Height,
      out_Max_Width,
      out_Max_Height,
      out_Max_Bytes);
}

typedef void (*tp_svc_connection_interface_avatars_get_avatar_tokens_impl) (TpSvcConnectionInterfaceAvatars *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_avatars_implement_get_avatar_tokens (TpSvcConnectionInterfaceAvatarsClass *klass, tp_svc_connection_interface_avatars_get_avatar_tokens_impl impl);
/**
 * tp_svc_connection_interface_avatars_return_from_get_avatar_tokens:
 * @context: The D-Bus method invocation context
 * @out_Tokens: const gchar ** (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_avatars_return_from_get_avatar_tokens (DBusGMethodInvocation *context,
    const gchar **out_Tokens);
static inline void
tp_svc_connection_interface_avatars_return_from_get_avatar_tokens (DBusGMethodInvocation *context,
    const gchar **out_Tokens)
{
  dbus_g_method_return (context,
      out_Tokens);
}

typedef void (*tp_svc_connection_interface_avatars_get_known_avatar_tokens_impl) (TpSvcConnectionInterfaceAvatars *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_avatars_implement_get_known_avatar_tokens (TpSvcConnectionInterfaceAvatarsClass *klass, tp_svc_connection_interface_avatars_get_known_avatar_tokens_impl impl);
/**
 * tp_svc_connection_interface_avatars_return_from_get_known_avatar_tokens:
 * @context: The D-Bus method invocation context
 * @out_Tokens: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_avatars_return_from_get_known_avatar_tokens (DBusGMethodInvocation *context,
    GHashTable *out_Tokens);
static inline void
tp_svc_connection_interface_avatars_return_from_get_known_avatar_tokens (DBusGMethodInvocation *context,
    GHashTable *out_Tokens)
{
  dbus_g_method_return (context,
      out_Tokens);
}

typedef void (*tp_svc_connection_interface_avatars_request_avatar_impl) (TpSvcConnectionInterfaceAvatars *self,
    guint in_Contact,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_avatars_implement_request_avatar (TpSvcConnectionInterfaceAvatarsClass *klass, tp_svc_connection_interface_avatars_request_avatar_impl impl);
/**
 * tp_svc_connection_interface_avatars_return_from_request_avatar:
 * @context: The D-Bus method invocation context
 * @out_Data: const GArray * (FIXME, generate documentation)
 * @out_MIME_Type: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_avatars_return_from_request_avatar (DBusGMethodInvocation *context,
    const GArray *out_Data,
    const gchar *out_MIME_Type);
static inline void
tp_svc_connection_interface_avatars_return_from_request_avatar (DBusGMethodInvocation *context,
    const GArray *out_Data,
    const gchar *out_MIME_Type)
{
  dbus_g_method_return (context,
      out_Data,
      out_MIME_Type);
}

typedef void (*tp_svc_connection_interface_avatars_request_avatars_impl) (TpSvcConnectionInterfaceAvatars *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_avatars_implement_request_avatars (TpSvcConnectionInterfaceAvatarsClass *klass, tp_svc_connection_interface_avatars_request_avatars_impl impl);
/**
 * tp_svc_connection_interface_avatars_return_from_request_avatars:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_avatars_return_from_request_avatars (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_interface_avatars_return_from_request_avatars (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_connection_interface_avatars_set_avatar_impl) (TpSvcConnectionInterfaceAvatars *self,
    const GArray *in_Avatar,
    const gchar *in_MIME_Type,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_avatars_implement_set_avatar (TpSvcConnectionInterfaceAvatarsClass *klass, tp_svc_connection_interface_avatars_set_avatar_impl impl);
/**
 * tp_svc_connection_interface_avatars_return_from_set_avatar:
 * @context: The D-Bus method invocation context
 * @out_Token: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_avatars_return_from_set_avatar (DBusGMethodInvocation *context,
    const gchar *out_Token);
static inline void
tp_svc_connection_interface_avatars_return_from_set_avatar (DBusGMethodInvocation *context,
    const gchar *out_Token)
{
  dbus_g_method_return (context,
      out_Token);
}

typedef void (*tp_svc_connection_interface_avatars_clear_avatar_impl) (TpSvcConnectionInterfaceAvatars *self,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_avatars_implement_clear_avatar (TpSvcConnectionInterfaceAvatarsClass *klass, tp_svc_connection_interface_avatars_clear_avatar_impl impl);
/**
 * tp_svc_connection_interface_avatars_return_from_clear_avatar:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_avatars_return_from_clear_avatar (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_interface_avatars_return_from_clear_avatar (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

void tp_svc_connection_interface_avatars_emit_avatar_updated (gpointer instance,
    guint arg_Contact,
    const gchar *arg_New_Avatar_Token);
void tp_svc_connection_interface_avatars_emit_avatar_retrieved (gpointer instance,
    guint arg_Contact,
    const gchar *arg_Token,
    const GArray *arg_Avatar,
    const gchar *arg_Type);

/**
 * TpSvcConnectionInterfaceCapabilities:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcConnectionInterfaceCapabilities TpSvcConnectionInterfaceCapabilities;

/**
 * TpSvcConnectionInterfaceCapabilitiesClass:
 *
 * The class of TpSvcConnectionInterfaceCapabilities.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_connection_interface_capabilities (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_connection_interface_capabilities_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (advertise_capabilities);
 *   IMPLEMENT (get_capabilities);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcConnectionInterfaceCapabilitiesClass TpSvcConnectionInterfaceCapabilitiesClass;

GType tp_svc_connection_interface_capabilities_get_type (void);
#define TP_TYPE_SVC_CONNECTION_INTERFACE_CAPABILITIES \
  (tp_svc_connection_interface_capabilities_get_type ())
#define TP_SVC_CONNECTION_INTERFACE_CAPABILITIES(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_CAPABILITIES, TpSvcConnectionInterfaceCapabilities))
#define TP_IS_SVC_CONNECTION_INTERFACE_CAPABILITIES(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_CAPABILITIES))
#define TP_SVC_CONNECTION_INTERFACE_CAPABILITIES_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_CAPABILITIES, TpSvcConnectionInterfaceCapabilitiesClass))


typedef void (*tp_svc_connection_interface_capabilities_advertise_capabilities_impl) (TpSvcConnectionInterfaceCapabilities *self,
    const GPtrArray *in_Add,
    const gchar **in_Remove,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_capabilities_implement_advertise_capabilities (TpSvcConnectionInterfaceCapabilitiesClass *klass, tp_svc_connection_interface_capabilities_advertise_capabilities_impl impl);
/**
 * tp_svc_connection_interface_capabilities_return_from_advertise_capabilities:
 * @context: The D-Bus method invocation context
 * @out_Self_Capabilities: const GPtrArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_capabilities_return_from_advertise_capabilities (DBusGMethodInvocation *context,
    const GPtrArray *out_Self_Capabilities);
static inline void
tp_svc_connection_interface_capabilities_return_from_advertise_capabilities (DBusGMethodInvocation *context,
    const GPtrArray *out_Self_Capabilities)
{
  dbus_g_method_return (context,
      out_Self_Capabilities);
}

typedef void (*tp_svc_connection_interface_capabilities_get_capabilities_impl) (TpSvcConnectionInterfaceCapabilities *self,
    const GArray *in_Handles,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_capabilities_implement_get_capabilities (TpSvcConnectionInterfaceCapabilitiesClass *klass, tp_svc_connection_interface_capabilities_get_capabilities_impl impl);
/**
 * tp_svc_connection_interface_capabilities_return_from_get_capabilities:
 * @context: The D-Bus method invocation context
 * @out_Contact_Capabilities: const GPtrArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_capabilities_return_from_get_capabilities (DBusGMethodInvocation *context,
    const GPtrArray *out_Contact_Capabilities);
static inline void
tp_svc_connection_interface_capabilities_return_from_get_capabilities (DBusGMethodInvocation *context,
    const GPtrArray *out_Contact_Capabilities)
{
  dbus_g_method_return (context,
      out_Contact_Capabilities);
}

void tp_svc_connection_interface_capabilities_emit_capabilities_changed (gpointer instance,
    const GPtrArray *arg_Caps);

/**
 * TpSvcConnectionInterfaceContactCapabilities:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcConnectionInterfaceContactCapabilities TpSvcConnectionInterfaceContactCapabilities;

/**
 * TpSvcConnectionInterfaceContactCapabilitiesClass:
 *
 * The class of TpSvcConnectionInterfaceContactCapabilities.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_connection_interface_contact_capabilities (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_connection_interface_contact_capabilities_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (update_capabilities);
 *   IMPLEMENT (get_contact_capabilities);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcConnectionInterfaceContactCapabilitiesClass TpSvcConnectionInterfaceContactCapabilitiesClass;

GType tp_svc_connection_interface_contact_capabilities_get_type (void);
#define TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACT_CAPABILITIES \
  (tp_svc_connection_interface_contact_capabilities_get_type ())
#define TP_SVC_CONNECTION_INTERFACE_CONTACT_CAPABILITIES(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACT_CAPABILITIES, TpSvcConnectionInterfaceContactCapabilities))
#define TP_IS_SVC_CONNECTION_INTERFACE_CONTACT_CAPABILITIES(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACT_CAPABILITIES))
#define TP_SVC_CONNECTION_INTERFACE_CONTACT_CAPABILITIES_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACT_CAPABILITIES, TpSvcConnectionInterfaceContactCapabilitiesClass))


typedef void (*tp_svc_connection_interface_contact_capabilities_update_capabilities_impl) (TpSvcConnectionInterfaceContactCapabilities *self,
    const GPtrArray *in_Handler_Capabilities,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_contact_capabilities_implement_update_capabilities (TpSvcConnectionInterfaceContactCapabilitiesClass *klass, tp_svc_connection_interface_contact_capabilities_update_capabilities_impl impl);
/**
 * tp_svc_connection_interface_contact_capabilities_return_from_update_capabilities:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_contact_capabilities_return_from_update_capabilities (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_interface_contact_capabilities_return_from_update_capabilities (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_connection_interface_contact_capabilities_get_contact_capabilities_impl) (TpSvcConnectionInterfaceContactCapabilities *self,
    const GArray *in_handles,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_contact_capabilities_implement_get_contact_capabilities (TpSvcConnectionInterfaceContactCapabilitiesClass *klass, tp_svc_connection_interface_contact_capabilities_get_contact_capabilities_impl impl);
/**
 * tp_svc_connection_interface_contact_capabilities_return_from_get_contact_capabilities:
 * @context: The D-Bus method invocation context
 * @out_Contact_Capabilities: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_contact_capabilities_return_from_get_contact_capabilities (DBusGMethodInvocation *context,
    GHashTable *out_Contact_Capabilities);
static inline void
tp_svc_connection_interface_contact_capabilities_return_from_get_contact_capabilities (DBusGMethodInvocation *context,
    GHashTable *out_Contact_Capabilities)
{
  dbus_g_method_return (context,
      out_Contact_Capabilities);
}

void tp_svc_connection_interface_contact_capabilities_emit_contact_capabilities_changed (gpointer instance,
    GHashTable *arg_caps);

/**
 * TpSvcConnectionInterfaceContacts:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcConnectionInterfaceContacts TpSvcConnectionInterfaceContacts;

/**
 * TpSvcConnectionInterfaceContactsClass:
 *
 * The class of TpSvcConnectionInterfaceContacts.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_connection_interface_contacts (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_connection_interface_contacts_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (get_contact_attributes);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcConnectionInterfaceContactsClass TpSvcConnectionInterfaceContactsClass;

GType tp_svc_connection_interface_contacts_get_type (void);
#define TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACTS \
  (tp_svc_connection_interface_contacts_get_type ())
#define TP_SVC_CONNECTION_INTERFACE_CONTACTS(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACTS, TpSvcConnectionInterfaceContacts))
#define TP_IS_SVC_CONNECTION_INTERFACE_CONTACTS(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACTS))
#define TP_SVC_CONNECTION_INTERFACE_CONTACTS_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_CONTACTS, TpSvcConnectionInterfaceContactsClass))


typedef void (*tp_svc_connection_interface_contacts_get_contact_attributes_impl) (TpSvcConnectionInterfaceContacts *self,
    const GArray *in_Handles,
    const gchar **in_Interfaces,
    gboolean in_Hold,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_contacts_implement_get_contact_attributes (TpSvcConnectionInterfaceContactsClass *klass, tp_svc_connection_interface_contacts_get_contact_attributes_impl impl);
/**
 * tp_svc_connection_interface_contacts_return_from_get_contact_attributes:
 * @context: The D-Bus method invocation context
 * @out_Attributes: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_contacts_return_from_get_contact_attributes (DBusGMethodInvocation *context,
    GHashTable *out_Attributes);
static inline void
tp_svc_connection_interface_contacts_return_from_get_contact_attributes (DBusGMethodInvocation *context,
    GHashTable *out_Attributes)
{
  dbus_g_method_return (context,
      out_Attributes);
}


/**
 * TpSvcConnectionInterfaceLocation:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcConnectionInterfaceLocation TpSvcConnectionInterfaceLocation;

/**
 * TpSvcConnectionInterfaceLocationClass:
 *
 * The class of TpSvcConnectionInterfaceLocation.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_connection_interface_location (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_connection_interface_location_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (get_locations);
 *   IMPLEMENT (request_location);
 *   IMPLEMENT (set_location);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcConnectionInterfaceLocationClass TpSvcConnectionInterfaceLocationClass;

GType tp_svc_connection_interface_location_get_type (void);
#define TP_TYPE_SVC_CONNECTION_INTERFACE_LOCATION \
  (tp_svc_connection_interface_location_get_type ())
#define TP_SVC_CONNECTION_INTERFACE_LOCATION(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_LOCATION, TpSvcConnectionInterfaceLocation))
#define TP_IS_SVC_CONNECTION_INTERFACE_LOCATION(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_LOCATION))
#define TP_SVC_CONNECTION_INTERFACE_LOCATION_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_LOCATION, TpSvcConnectionInterfaceLocationClass))


typedef void (*tp_svc_connection_interface_location_get_locations_impl) (TpSvcConnectionInterfaceLocation *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_location_implement_get_locations (TpSvcConnectionInterfaceLocationClass *klass, tp_svc_connection_interface_location_get_locations_impl impl);
/**
 * tp_svc_connection_interface_location_return_from_get_locations:
 * @context: The D-Bus method invocation context
 * @out_Locations: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_location_return_from_get_locations (DBusGMethodInvocation *context,
    GHashTable *out_Locations);
static inline void
tp_svc_connection_interface_location_return_from_get_locations (DBusGMethodInvocation *context,
    GHashTable *out_Locations)
{
  dbus_g_method_return (context,
      out_Locations);
}

typedef void (*tp_svc_connection_interface_location_request_location_impl) (TpSvcConnectionInterfaceLocation *self,
    guint in_Contact,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_location_implement_request_location (TpSvcConnectionInterfaceLocationClass *klass, tp_svc_connection_interface_location_request_location_impl impl);
/**
 * tp_svc_connection_interface_location_return_from_request_location:
 * @context: The D-Bus method invocation context
 * @out_Location: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_location_return_from_request_location (DBusGMethodInvocation *context,
    GHashTable *out_Location);
static inline void
tp_svc_connection_interface_location_return_from_request_location (DBusGMethodInvocation *context,
    GHashTable *out_Location)
{
  dbus_g_method_return (context,
      out_Location);
}

typedef void (*tp_svc_connection_interface_location_set_location_impl) (TpSvcConnectionInterfaceLocation *self,
    GHashTable *in_Location,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_location_implement_set_location (TpSvcConnectionInterfaceLocationClass *klass, tp_svc_connection_interface_location_set_location_impl impl);
/**
 * tp_svc_connection_interface_location_return_from_set_location:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_location_return_from_set_location (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_interface_location_return_from_set_location (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

void tp_svc_connection_interface_location_emit_location_updated (gpointer instance,
    guint arg_Contact,
    GHashTable *arg_Location);

/**
 * TpSvcConnectionInterfacePresence:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcConnectionInterfacePresence TpSvcConnectionInterfacePresence;

/**
 * TpSvcConnectionInterfacePresenceClass:
 *
 * The class of TpSvcConnectionInterfacePresence.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_connection_interface_presence (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_connection_interface_presence_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (add_status);
 *   IMPLEMENT (clear_status);
 *   IMPLEMENT (get_presence);
 *   IMPLEMENT (get_statuses);
 *   IMPLEMENT (remove_status);
 *   IMPLEMENT (request_presence);
 *   IMPLEMENT (set_last_activity_time);
 *   IMPLEMENT (set_status);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcConnectionInterfacePresenceClass TpSvcConnectionInterfacePresenceClass;

GType tp_svc_connection_interface_presence_get_type (void);
#define TP_TYPE_SVC_CONNECTION_INTERFACE_PRESENCE \
  (tp_svc_connection_interface_presence_get_type ())
#define TP_SVC_CONNECTION_INTERFACE_PRESENCE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_PRESENCE, TpSvcConnectionInterfacePresence))
#define TP_IS_SVC_CONNECTION_INTERFACE_PRESENCE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_PRESENCE))
#define TP_SVC_CONNECTION_INTERFACE_PRESENCE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_PRESENCE, TpSvcConnectionInterfacePresenceClass))


typedef void (*tp_svc_connection_interface_presence_add_status_impl) (TpSvcConnectionInterfacePresence *self,
    const gchar *in_Status,
    GHashTable *in_Parameters,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_presence_implement_add_status (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_add_status_impl impl);
/**
 * tp_svc_connection_interface_presence_return_from_add_status:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_presence_return_from_add_status (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_interface_presence_return_from_add_status (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_connection_interface_presence_clear_status_impl) (TpSvcConnectionInterfacePresence *self,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_presence_implement_clear_status (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_clear_status_impl impl);
/**
 * tp_svc_connection_interface_presence_return_from_clear_status:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_presence_return_from_clear_status (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_interface_presence_return_from_clear_status (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_connection_interface_presence_get_presence_impl) (TpSvcConnectionInterfacePresence *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_presence_implement_get_presence (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_get_presence_impl impl);
/**
 * tp_svc_connection_interface_presence_return_from_get_presence:
 * @context: The D-Bus method invocation context
 * @out_Presence: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_presence_return_from_get_presence (DBusGMethodInvocation *context,
    GHashTable *out_Presence);
static inline void
tp_svc_connection_interface_presence_return_from_get_presence (DBusGMethodInvocation *context,
    GHashTable *out_Presence)
{
  dbus_g_method_return (context,
      out_Presence);
}

typedef void (*tp_svc_connection_interface_presence_get_statuses_impl) (TpSvcConnectionInterfacePresence *self,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_presence_implement_get_statuses (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_get_statuses_impl impl);
/**
 * tp_svc_connection_interface_presence_return_from_get_statuses:
 * @context: The D-Bus method invocation context
 * @out_Available_Statuses: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_presence_return_from_get_statuses (DBusGMethodInvocation *context,
    GHashTable *out_Available_Statuses);
static inline void
tp_svc_connection_interface_presence_return_from_get_statuses (DBusGMethodInvocation *context,
    GHashTable *out_Available_Statuses)
{
  dbus_g_method_return (context,
      out_Available_Statuses);
}

typedef void (*tp_svc_connection_interface_presence_remove_status_impl) (TpSvcConnectionInterfacePresence *self,
    const gchar *in_Status,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_presence_implement_remove_status (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_remove_status_impl impl);
/**
 * tp_svc_connection_interface_presence_return_from_remove_status:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_presence_return_from_remove_status (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_interface_presence_return_from_remove_status (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_connection_interface_presence_request_presence_impl) (TpSvcConnectionInterfacePresence *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_presence_implement_request_presence (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_request_presence_impl impl);
/**
 * tp_svc_connection_interface_presence_return_from_request_presence:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_presence_return_from_request_presence (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_interface_presence_return_from_request_presence (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_connection_interface_presence_set_last_activity_time_impl) (TpSvcConnectionInterfacePresence *self,
    guint in_Time,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_presence_implement_set_last_activity_time (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_set_last_activity_time_impl impl);
/**
 * tp_svc_connection_interface_presence_return_from_set_last_activity_time:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_presence_return_from_set_last_activity_time (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_interface_presence_return_from_set_last_activity_time (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_connection_interface_presence_set_status_impl) (TpSvcConnectionInterfacePresence *self,
    GHashTable *in_Statuses,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_presence_implement_set_status (TpSvcConnectionInterfacePresenceClass *klass, tp_svc_connection_interface_presence_set_status_impl impl);
/**
 * tp_svc_connection_interface_presence_return_from_set_status:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_presence_return_from_set_status (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_interface_presence_return_from_set_status (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

void tp_svc_connection_interface_presence_emit_presence_update (gpointer instance,
    GHashTable *arg_Presence);

/**
 * TpSvcConnectionInterfaceRequests:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcConnectionInterfaceRequests TpSvcConnectionInterfaceRequests;

/**
 * TpSvcConnectionInterfaceRequestsClass:
 *
 * The class of TpSvcConnectionInterfaceRequests.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_connection_interface_requests (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_connection_interface_requests_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (create_channel);
 *   IMPLEMENT (ensure_channel);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcConnectionInterfaceRequestsClass TpSvcConnectionInterfaceRequestsClass;

GType tp_svc_connection_interface_requests_get_type (void);
#define TP_TYPE_SVC_CONNECTION_INTERFACE_REQUESTS \
  (tp_svc_connection_interface_requests_get_type ())
#define TP_SVC_CONNECTION_INTERFACE_REQUESTS(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_REQUESTS, TpSvcConnectionInterfaceRequests))
#define TP_IS_SVC_CONNECTION_INTERFACE_REQUESTS(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_REQUESTS))
#define TP_SVC_CONNECTION_INTERFACE_REQUESTS_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_REQUESTS, TpSvcConnectionInterfaceRequestsClass))


typedef void (*tp_svc_connection_interface_requests_create_channel_impl) (TpSvcConnectionInterfaceRequests *self,
    GHashTable *in_Request,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_requests_implement_create_channel (TpSvcConnectionInterfaceRequestsClass *klass, tp_svc_connection_interface_requests_create_channel_impl impl);
/**
 * tp_svc_connection_interface_requests_return_from_create_channel:
 * @context: The D-Bus method invocation context
 * @out_Channel: const gchar * (FIXME, generate documentation)
 * @out_Properties: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_requests_return_from_create_channel (DBusGMethodInvocation *context,
    const gchar *out_Channel,
    GHashTable *out_Properties);
static inline void
tp_svc_connection_interface_requests_return_from_create_channel (DBusGMethodInvocation *context,
    const gchar *out_Channel,
    GHashTable *out_Properties)
{
  dbus_g_method_return (context,
      out_Channel,
      out_Properties);
}

typedef void (*tp_svc_connection_interface_requests_ensure_channel_impl) (TpSvcConnectionInterfaceRequests *self,
    GHashTable *in_Request,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_requests_implement_ensure_channel (TpSvcConnectionInterfaceRequestsClass *klass, tp_svc_connection_interface_requests_ensure_channel_impl impl);
/**
 * tp_svc_connection_interface_requests_return_from_ensure_channel:
 * @context: The D-Bus method invocation context
 * @out_Yours: gboolean  (FIXME, generate documentation)
 * @out_Channel: const gchar * (FIXME, generate documentation)
 * @out_Properties: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_requests_return_from_ensure_channel (DBusGMethodInvocation *context,
    gboolean out_Yours,
    const gchar *out_Channel,
    GHashTable *out_Properties);
static inline void
tp_svc_connection_interface_requests_return_from_ensure_channel (DBusGMethodInvocation *context,
    gboolean out_Yours,
    const gchar *out_Channel,
    GHashTable *out_Properties)
{
  dbus_g_method_return (context,
      out_Yours,
      out_Channel,
      out_Properties);
}

void tp_svc_connection_interface_requests_emit_new_channels (gpointer instance,
    const GPtrArray *arg_Channels);
void tp_svc_connection_interface_requests_emit_channel_closed (gpointer instance,
    const gchar *arg_Removed);

/**
 * TpSvcConnectionInterfaceSimplePresence:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcConnectionInterfaceSimplePresence TpSvcConnectionInterfaceSimplePresence;

/**
 * TpSvcConnectionInterfaceSimplePresenceClass:
 *
 * The class of TpSvcConnectionInterfaceSimplePresence.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_connection_interface_simple_presence (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_connection_interface_simple_presence_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (set_presence);
 *   IMPLEMENT (get_presences);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcConnectionInterfaceSimplePresenceClass TpSvcConnectionInterfaceSimplePresenceClass;

GType tp_svc_connection_interface_simple_presence_get_type (void);
#define TP_TYPE_SVC_CONNECTION_INTERFACE_SIMPLE_PRESENCE \
  (tp_svc_connection_interface_simple_presence_get_type ())
#define TP_SVC_CONNECTION_INTERFACE_SIMPLE_PRESENCE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_SIMPLE_PRESENCE, TpSvcConnectionInterfaceSimplePresence))
#define TP_IS_SVC_CONNECTION_INTERFACE_SIMPLE_PRESENCE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_SIMPLE_PRESENCE))
#define TP_SVC_CONNECTION_INTERFACE_SIMPLE_PRESENCE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CONNECTION_INTERFACE_SIMPLE_PRESENCE, TpSvcConnectionInterfaceSimplePresenceClass))


typedef void (*tp_svc_connection_interface_simple_presence_set_presence_impl) (TpSvcConnectionInterfaceSimplePresence *self,
    const gchar *in_Status,
    const gchar *in_Status_Message,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_simple_presence_implement_set_presence (TpSvcConnectionInterfaceSimplePresenceClass *klass, tp_svc_connection_interface_simple_presence_set_presence_impl impl);
/**
 * tp_svc_connection_interface_simple_presence_return_from_set_presence:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_simple_presence_return_from_set_presence (DBusGMethodInvocation *context);
static inline void
tp_svc_connection_interface_simple_presence_return_from_set_presence (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_connection_interface_simple_presence_get_presences_impl) (TpSvcConnectionInterfaceSimplePresence *self,
    const GArray *in_Contacts,
    DBusGMethodInvocation *context);
void tp_svc_connection_interface_simple_presence_implement_get_presences (TpSvcConnectionInterfaceSimplePresenceClass *klass, tp_svc_connection_interface_simple_presence_get_presences_impl impl);
/**
 * tp_svc_connection_interface_simple_presence_return_from_get_presences:
 * @context: The D-Bus method invocation context
 * @out_Presence: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_connection_interface_simple_presence_return_from_get_presences (DBusGMethodInvocation *context,
    GHashTable *out_Presence);
static inline void
tp_svc_connection_interface_simple_presence_return_from_get_presences (DBusGMethodInvocation *context,
    GHashTable *out_Presence)
{
  dbus_g_method_return (context,
      out_Presence);
}

void tp_svc_connection_interface_simple_presence_emit_presences_changed (gpointer instance,
    GHashTable *arg_Presence);


G_END_DECLS
