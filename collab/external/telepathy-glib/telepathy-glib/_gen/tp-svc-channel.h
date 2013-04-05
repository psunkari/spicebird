#include <glib-object.h>
#include <dbus/dbus-glib.h>
#include <telepathy-glib/dbus-properties-mixin.h>

G_BEGIN_DECLS

/**
 * TpSvcChannel:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannel TpSvcChannel;

/**
 * TpSvcChannelClass:
 *
 * The class of TpSvcChannel.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (close);
 *   IMPLEMENT (get_channel_type);
 *   IMPLEMENT (get_handle);
 *   IMPLEMENT (get_interfaces);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelClass TpSvcChannelClass;

GType tp_svc_channel_get_type (void);
#define TP_TYPE_SVC_CHANNEL \
  (tp_svc_channel_get_type ())
#define TP_SVC_CHANNEL(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL, TpSvcChannel))
#define TP_IS_SVC_CHANNEL(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL))
#define TP_SVC_CHANNEL_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL, TpSvcChannelClass))


typedef void (*tp_svc_channel_close_impl) (TpSvcChannel *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_implement_close (TpSvcChannelClass *klass, tp_svc_channel_close_impl impl);
/**
 * tp_svc_channel_return_from_close:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_return_from_close (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_return_from_close (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_channel_get_channel_type_impl) (TpSvcChannel *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_implement_get_channel_type (TpSvcChannelClass *klass, tp_svc_channel_get_channel_type_impl impl);
/**
 * tp_svc_channel_return_from_get_channel_type:
 * @context: The D-Bus method invocation context
 * @out_Channel_Type: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_return_from_get_channel_type (DBusGMethodInvocation *context,
    const gchar *out_Channel_Type);
static inline void
tp_svc_channel_return_from_get_channel_type (DBusGMethodInvocation *context,
    const gchar *out_Channel_Type)
{
  dbus_g_method_return (context,
      out_Channel_Type);
}

typedef void (*tp_svc_channel_get_handle_impl) (TpSvcChannel *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_implement_get_handle (TpSvcChannelClass *klass, tp_svc_channel_get_handle_impl impl);
/**
 * tp_svc_channel_return_from_get_handle:
 * @context: The D-Bus method invocation context
 * @out_Target_Handle_Type: guint  (FIXME, generate documentation)
 * @out_Target_Handle: guint  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_return_from_get_handle (DBusGMethodInvocation *context,
    guint out_Target_Handle_Type,
    guint out_Target_Handle);
static inline void
tp_svc_channel_return_from_get_handle (DBusGMethodInvocation *context,
    guint out_Target_Handle_Type,
    guint out_Target_Handle)
{
  dbus_g_method_return (context,
      out_Target_Handle_Type,
      out_Target_Handle);
}

typedef void (*tp_svc_channel_get_interfaces_impl) (TpSvcChannel *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_implement_get_interfaces (TpSvcChannelClass *klass, tp_svc_channel_get_interfaces_impl impl);
/**
 * tp_svc_channel_return_from_get_interfaces:
 * @context: The D-Bus method invocation context
 * @out_Interfaces: const gchar ** (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_return_from_get_interfaces (DBusGMethodInvocation *context,
    const gchar **out_Interfaces);
static inline void
tp_svc_channel_return_from_get_interfaces (DBusGMethodInvocation *context,
    const gchar **out_Interfaces)
{
  dbus_g_method_return (context,
      out_Interfaces);
}

void tp_svc_channel_emit_closed (gpointer instance);

/**
 * TpSvcChannelInterfaceCallState:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelInterfaceCallState TpSvcChannelInterfaceCallState;

/**
 * TpSvcChannelInterfaceCallStateClass:
 *
 * The class of TpSvcChannelInterfaceCallState.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_interface_call_state (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_interface_call_state_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (get_call_states);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelInterfaceCallStateClass TpSvcChannelInterfaceCallStateClass;

GType tp_svc_channel_interface_call_state_get_type (void);
#define TP_TYPE_SVC_CHANNEL_INTERFACE_CALL_STATE \
  (tp_svc_channel_interface_call_state_get_type ())
#define TP_SVC_CHANNEL_INTERFACE_CALL_STATE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_CALL_STATE, TpSvcChannelInterfaceCallState))
#define TP_IS_SVC_CHANNEL_INTERFACE_CALL_STATE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_CALL_STATE))
#define TP_SVC_CHANNEL_INTERFACE_CALL_STATE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_CALL_STATE, TpSvcChannelInterfaceCallStateClass))


typedef void (*tp_svc_channel_interface_call_state_get_call_states_impl) (TpSvcChannelInterfaceCallState *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_call_state_implement_get_call_states (TpSvcChannelInterfaceCallStateClass *klass, tp_svc_channel_interface_call_state_get_call_states_impl impl);
/**
 * tp_svc_channel_interface_call_state_return_from_get_call_states:
 * @context: The D-Bus method invocation context
 * @out_States: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_call_state_return_from_get_call_states (DBusGMethodInvocation *context,
    GHashTable *out_States);
static inline void
tp_svc_channel_interface_call_state_return_from_get_call_states (DBusGMethodInvocation *context,
    GHashTable *out_States)
{
  dbus_g_method_return (context,
      out_States);
}

void tp_svc_channel_interface_call_state_emit_call_state_changed (gpointer instance,
    guint arg_Contact,
    guint arg_State);

/**
 * TpSvcChannelInterfaceChatState:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelInterfaceChatState TpSvcChannelInterfaceChatState;

/**
 * TpSvcChannelInterfaceChatStateClass:
 *
 * The class of TpSvcChannelInterfaceChatState.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_interface_chat_state (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_interface_chat_state_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (set_chat_state);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelInterfaceChatStateClass TpSvcChannelInterfaceChatStateClass;

GType tp_svc_channel_interface_chat_state_get_type (void);
#define TP_TYPE_SVC_CHANNEL_INTERFACE_CHAT_STATE \
  (tp_svc_channel_interface_chat_state_get_type ())
#define TP_SVC_CHANNEL_INTERFACE_CHAT_STATE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_CHAT_STATE, TpSvcChannelInterfaceChatState))
#define TP_IS_SVC_CHANNEL_INTERFACE_CHAT_STATE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_CHAT_STATE))
#define TP_SVC_CHANNEL_INTERFACE_CHAT_STATE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_CHAT_STATE, TpSvcChannelInterfaceChatStateClass))


typedef void (*tp_svc_channel_interface_chat_state_set_chat_state_impl) (TpSvcChannelInterfaceChatState *self,
    guint in_State,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_chat_state_implement_set_chat_state (TpSvcChannelInterfaceChatStateClass *klass, tp_svc_channel_interface_chat_state_set_chat_state_impl impl);
/**
 * tp_svc_channel_interface_chat_state_return_from_set_chat_state:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_chat_state_return_from_set_chat_state (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_interface_chat_state_return_from_set_chat_state (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

void tp_svc_channel_interface_chat_state_emit_chat_state_changed (gpointer instance,
    guint arg_Contact,
    guint arg_State);

/**
 * TpSvcChannelInterfaceDTMF:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelInterfaceDTMF TpSvcChannelInterfaceDTMF;

/**
 * TpSvcChannelInterfaceDTMFClass:
 *
 * The class of TpSvcChannelInterfaceDTMF.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_interface_dtmf (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_interface_dtmf_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (start_tone);
 *   IMPLEMENT (stop_tone);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelInterfaceDTMFClass TpSvcChannelInterfaceDTMFClass;

GType tp_svc_channel_interface_dtmf_get_type (void);
#define TP_TYPE_SVC_CHANNEL_INTERFACE_DTMF \
  (tp_svc_channel_interface_dtmf_get_type ())
#define TP_SVC_CHANNEL_INTERFACE_DTMF(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_DTMF, TpSvcChannelInterfaceDTMF))
#define TP_IS_SVC_CHANNEL_INTERFACE_DTMF(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_DTMF))
#define TP_SVC_CHANNEL_INTERFACE_DTMF_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_DTMF, TpSvcChannelInterfaceDTMFClass))


typedef void (*tp_svc_channel_interface_dtmf_start_tone_impl) (TpSvcChannelInterfaceDTMF *self,
    guint in_Stream_ID,
    guchar in_Event,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_dtmf_implement_start_tone (TpSvcChannelInterfaceDTMFClass *klass, tp_svc_channel_interface_dtmf_start_tone_impl impl);
/**
 * tp_svc_channel_interface_dtmf_return_from_start_tone:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_dtmf_return_from_start_tone (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_interface_dtmf_return_from_start_tone (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_channel_interface_dtmf_stop_tone_impl) (TpSvcChannelInterfaceDTMF *self,
    guint in_Stream_ID,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_dtmf_implement_stop_tone (TpSvcChannelInterfaceDTMFClass *klass, tp_svc_channel_interface_dtmf_stop_tone_impl impl);
/**
 * tp_svc_channel_interface_dtmf_return_from_stop_tone:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_dtmf_return_from_stop_tone (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_interface_dtmf_return_from_stop_tone (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}


/**
 * TpSvcChannelInterfaceDestroyable:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelInterfaceDestroyable TpSvcChannelInterfaceDestroyable;

/**
 * TpSvcChannelInterfaceDestroyableClass:
 *
 * The class of TpSvcChannelInterfaceDestroyable.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_interface_destroyable (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_interface_destroyable_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (destroy);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelInterfaceDestroyableClass TpSvcChannelInterfaceDestroyableClass;

GType tp_svc_channel_interface_destroyable_get_type (void);
#define TP_TYPE_SVC_CHANNEL_INTERFACE_DESTROYABLE \
  (tp_svc_channel_interface_destroyable_get_type ())
#define TP_SVC_CHANNEL_INTERFACE_DESTROYABLE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_DESTROYABLE, TpSvcChannelInterfaceDestroyable))
#define TP_IS_SVC_CHANNEL_INTERFACE_DESTROYABLE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_DESTROYABLE))
#define TP_SVC_CHANNEL_INTERFACE_DESTROYABLE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_DESTROYABLE, TpSvcChannelInterfaceDestroyableClass))


typedef void (*tp_svc_channel_interface_destroyable_destroy_impl) (TpSvcChannelInterfaceDestroyable *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_destroyable_implement_destroy (TpSvcChannelInterfaceDestroyableClass *klass, tp_svc_channel_interface_destroyable_destroy_impl impl);
/**
 * tp_svc_channel_interface_destroyable_return_from_destroy:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_destroyable_return_from_destroy (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_interface_destroyable_return_from_destroy (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}


/**
 * TpSvcChannelInterfaceGroup:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelInterfaceGroup TpSvcChannelInterfaceGroup;

/**
 * TpSvcChannelInterfaceGroupClass:
 *
 * The class of TpSvcChannelInterfaceGroup.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_interface_group (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_interface_group_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (add_members);
 *   IMPLEMENT (get_all_members);
 *   IMPLEMENT (get_group_flags);
 *   IMPLEMENT (get_handle_owners);
 *   IMPLEMENT (get_local_pending_members);
 *   IMPLEMENT (get_local_pending_members_with_info);
 *   IMPLEMENT (get_members);
 *   IMPLEMENT (get_remote_pending_members);
 *   IMPLEMENT (get_self_handle);
 *   IMPLEMENT (remove_members);
 *   IMPLEMENT (remove_members_with_reason);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelInterfaceGroupClass TpSvcChannelInterfaceGroupClass;

GType tp_svc_channel_interface_group_get_type (void);
#define TP_TYPE_SVC_CHANNEL_INTERFACE_GROUP \
  (tp_svc_channel_interface_group_get_type ())
#define TP_SVC_CHANNEL_INTERFACE_GROUP(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_GROUP, TpSvcChannelInterfaceGroup))
#define TP_IS_SVC_CHANNEL_INTERFACE_GROUP(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_GROUP))
#define TP_SVC_CHANNEL_INTERFACE_GROUP_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_GROUP, TpSvcChannelInterfaceGroupClass))


typedef void (*tp_svc_channel_interface_group_add_members_impl) (TpSvcChannelInterfaceGroup *self,
    const GArray *in_Contacts,
    const gchar *in_Message,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_group_implement_add_members (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_add_members_impl impl);
/**
 * tp_svc_channel_interface_group_return_from_add_members:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_group_return_from_add_members (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_interface_group_return_from_add_members (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_channel_interface_group_get_all_members_impl) (TpSvcChannelInterfaceGroup *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_group_implement_get_all_members (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_all_members_impl impl);
/**
 * tp_svc_channel_interface_group_return_from_get_all_members:
 * @context: The D-Bus method invocation context
 * @out_Members: const GArray * (FIXME, generate documentation)
 * @out_Local_Pending: const GArray * (FIXME, generate documentation)
 * @out_Remote_Pending: const GArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_group_return_from_get_all_members (DBusGMethodInvocation *context,
    const GArray *out_Members,
    const GArray *out_Local_Pending,
    const GArray *out_Remote_Pending);
static inline void
tp_svc_channel_interface_group_return_from_get_all_members (DBusGMethodInvocation *context,
    const GArray *out_Members,
    const GArray *out_Local_Pending,
    const GArray *out_Remote_Pending)
{
  dbus_g_method_return (context,
      out_Members,
      out_Local_Pending,
      out_Remote_Pending);
}

typedef void (*tp_svc_channel_interface_group_get_group_flags_impl) (TpSvcChannelInterfaceGroup *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_group_implement_get_group_flags (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_group_flags_impl impl);
/**
 * tp_svc_channel_interface_group_return_from_get_group_flags:
 * @context: The D-Bus method invocation context
 * @out_Group_Flags: guint  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_group_return_from_get_group_flags (DBusGMethodInvocation *context,
    guint out_Group_Flags);
static inline void
tp_svc_channel_interface_group_return_from_get_group_flags (DBusGMethodInvocation *context,
    guint out_Group_Flags)
{
  dbus_g_method_return (context,
      out_Group_Flags);
}

typedef void (*tp_svc_channel_interface_group_get_handle_owners_impl) (TpSvcChannelInterfaceGroup *self,
    const GArray *in_Handles,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_group_implement_get_handle_owners (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_handle_owners_impl impl);
/**
 * tp_svc_channel_interface_group_return_from_get_handle_owners:
 * @context: The D-Bus method invocation context
 * @out_Owners: const GArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_group_return_from_get_handle_owners (DBusGMethodInvocation *context,
    const GArray *out_Owners);
static inline void
tp_svc_channel_interface_group_return_from_get_handle_owners (DBusGMethodInvocation *context,
    const GArray *out_Owners)
{
  dbus_g_method_return (context,
      out_Owners);
}

typedef void (*tp_svc_channel_interface_group_get_local_pending_members_impl) (TpSvcChannelInterfaceGroup *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_group_implement_get_local_pending_members (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_local_pending_members_impl impl);
/**
 * tp_svc_channel_interface_group_return_from_get_local_pending_members:
 * @context: The D-Bus method invocation context
 * @out_Handles: const GArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_group_return_from_get_local_pending_members (DBusGMethodInvocation *context,
    const GArray *out_Handles);
static inline void
tp_svc_channel_interface_group_return_from_get_local_pending_members (DBusGMethodInvocation *context,
    const GArray *out_Handles)
{
  dbus_g_method_return (context,
      out_Handles);
}

typedef void (*tp_svc_channel_interface_group_get_local_pending_members_with_info_impl) (TpSvcChannelInterfaceGroup *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_group_implement_get_local_pending_members_with_info (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_local_pending_members_with_info_impl impl);
/**
 * tp_svc_channel_interface_group_return_from_get_local_pending_members_with_info:
 * @context: The D-Bus method invocation context
 * @out_Info: const GPtrArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_group_return_from_get_local_pending_members_with_info (DBusGMethodInvocation *context,
    const GPtrArray *out_Info);
static inline void
tp_svc_channel_interface_group_return_from_get_local_pending_members_with_info (DBusGMethodInvocation *context,
    const GPtrArray *out_Info)
{
  dbus_g_method_return (context,
      out_Info);
}

typedef void (*tp_svc_channel_interface_group_get_members_impl) (TpSvcChannelInterfaceGroup *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_group_implement_get_members (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_members_impl impl);
/**
 * tp_svc_channel_interface_group_return_from_get_members:
 * @context: The D-Bus method invocation context
 * @out_Handles: const GArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_group_return_from_get_members (DBusGMethodInvocation *context,
    const GArray *out_Handles);
static inline void
tp_svc_channel_interface_group_return_from_get_members (DBusGMethodInvocation *context,
    const GArray *out_Handles)
{
  dbus_g_method_return (context,
      out_Handles);
}

typedef void (*tp_svc_channel_interface_group_get_remote_pending_members_impl) (TpSvcChannelInterfaceGroup *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_group_implement_get_remote_pending_members (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_remote_pending_members_impl impl);
/**
 * tp_svc_channel_interface_group_return_from_get_remote_pending_members:
 * @context: The D-Bus method invocation context
 * @out_Handles: const GArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_group_return_from_get_remote_pending_members (DBusGMethodInvocation *context,
    const GArray *out_Handles);
static inline void
tp_svc_channel_interface_group_return_from_get_remote_pending_members (DBusGMethodInvocation *context,
    const GArray *out_Handles)
{
  dbus_g_method_return (context,
      out_Handles);
}

typedef void (*tp_svc_channel_interface_group_get_self_handle_impl) (TpSvcChannelInterfaceGroup *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_group_implement_get_self_handle (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_self_handle_impl impl);
/**
 * tp_svc_channel_interface_group_return_from_get_self_handle:
 * @context: The D-Bus method invocation context
 * @out_Self_Handle: guint  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_group_return_from_get_self_handle (DBusGMethodInvocation *context,
    guint out_Self_Handle);
static inline void
tp_svc_channel_interface_group_return_from_get_self_handle (DBusGMethodInvocation *context,
    guint out_Self_Handle)
{
  dbus_g_method_return (context,
      out_Self_Handle);
}

typedef void (*tp_svc_channel_interface_group_remove_members_impl) (TpSvcChannelInterfaceGroup *self,
    const GArray *in_Contacts,
    const gchar *in_Message,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_group_implement_remove_members (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_remove_members_impl impl);
/**
 * tp_svc_channel_interface_group_return_from_remove_members:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_group_return_from_remove_members (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_interface_group_return_from_remove_members (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_channel_interface_group_remove_members_with_reason_impl) (TpSvcChannelInterfaceGroup *self,
    const GArray *in_Contacts,
    const gchar *in_Message,
    guint in_Reason,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_group_implement_remove_members_with_reason (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_remove_members_with_reason_impl impl);
/**
 * tp_svc_channel_interface_group_return_from_remove_members_with_reason:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_group_return_from_remove_members_with_reason (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_interface_group_return_from_remove_members_with_reason (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

void tp_svc_channel_interface_group_emit_handle_owners_changed (gpointer instance,
    GHashTable *arg_Added,
    const GArray *arg_Removed);
void tp_svc_channel_interface_group_emit_self_handle_changed (gpointer instance,
    guint arg_Self_Handle);
void tp_svc_channel_interface_group_emit_group_flags_changed (gpointer instance,
    guint arg_Added,
    guint arg_Removed);
void tp_svc_channel_interface_group_emit_members_changed (gpointer instance,
    const gchar *arg_Message,
    const GArray *arg_Added,
    const GArray *arg_Removed,
    const GArray *arg_Local_Pending,
    const GArray *arg_Remote_Pending,
    guint arg_Actor,
    guint arg_Reason);
void tp_svc_channel_interface_group_emit_members_changed_detailed (gpointer instance,
    const GArray *arg_Added,
    const GArray *arg_Removed,
    const GArray *arg_Local_Pending,
    const GArray *arg_Remote_Pending,
    GHashTable *arg_Details);

/**
 * TpSvcChannelInterfaceHold:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelInterfaceHold TpSvcChannelInterfaceHold;

/**
 * TpSvcChannelInterfaceHoldClass:
 *
 * The class of TpSvcChannelInterfaceHold.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_interface_hold (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_interface_hold_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (get_hold_state);
 *   IMPLEMENT (request_hold);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelInterfaceHoldClass TpSvcChannelInterfaceHoldClass;

GType tp_svc_channel_interface_hold_get_type (void);
#define TP_TYPE_SVC_CHANNEL_INTERFACE_HOLD \
  (tp_svc_channel_interface_hold_get_type ())
#define TP_SVC_CHANNEL_INTERFACE_HOLD(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_HOLD, TpSvcChannelInterfaceHold))
#define TP_IS_SVC_CHANNEL_INTERFACE_HOLD(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_HOLD))
#define TP_SVC_CHANNEL_INTERFACE_HOLD_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_HOLD, TpSvcChannelInterfaceHoldClass))


typedef void (*tp_svc_channel_interface_hold_get_hold_state_impl) (TpSvcChannelInterfaceHold *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_hold_implement_get_hold_state (TpSvcChannelInterfaceHoldClass *klass, tp_svc_channel_interface_hold_get_hold_state_impl impl);
/**
 * tp_svc_channel_interface_hold_return_from_get_hold_state:
 * @context: The D-Bus method invocation context
 * @out_HoldState: guint  (FIXME, generate documentation)
 * @out_Reason: guint  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_hold_return_from_get_hold_state (DBusGMethodInvocation *context,
    guint out_HoldState,
    guint out_Reason);
static inline void
tp_svc_channel_interface_hold_return_from_get_hold_state (DBusGMethodInvocation *context,
    guint out_HoldState,
    guint out_Reason)
{
  dbus_g_method_return (context,
      out_HoldState,
      out_Reason);
}

typedef void (*tp_svc_channel_interface_hold_request_hold_impl) (TpSvcChannelInterfaceHold *self,
    gboolean in_Hold,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_hold_implement_request_hold (TpSvcChannelInterfaceHoldClass *klass, tp_svc_channel_interface_hold_request_hold_impl impl);
/**
 * tp_svc_channel_interface_hold_return_from_request_hold:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_hold_return_from_request_hold (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_interface_hold_return_from_request_hold (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

void tp_svc_channel_interface_hold_emit_hold_state_changed (gpointer instance,
    guint arg_HoldState,
    guint arg_Reason);

/**
 * TpSvcChannelInterfaceMediaSignalling:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelInterfaceMediaSignalling TpSvcChannelInterfaceMediaSignalling;

/**
 * TpSvcChannelInterfaceMediaSignallingClass:
 *
 * The class of TpSvcChannelInterfaceMediaSignalling.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_interface_media_signalling (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_interface_media_signalling_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (get_session_handlers);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelInterfaceMediaSignallingClass TpSvcChannelInterfaceMediaSignallingClass;

GType tp_svc_channel_interface_media_signalling_get_type (void);
#define TP_TYPE_SVC_CHANNEL_INTERFACE_MEDIA_SIGNALLING \
  (tp_svc_channel_interface_media_signalling_get_type ())
#define TP_SVC_CHANNEL_INTERFACE_MEDIA_SIGNALLING(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_MEDIA_SIGNALLING, TpSvcChannelInterfaceMediaSignalling))
#define TP_IS_SVC_CHANNEL_INTERFACE_MEDIA_SIGNALLING(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_MEDIA_SIGNALLING))
#define TP_SVC_CHANNEL_INTERFACE_MEDIA_SIGNALLING_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_MEDIA_SIGNALLING, TpSvcChannelInterfaceMediaSignallingClass))


typedef void (*tp_svc_channel_interface_media_signalling_get_session_handlers_impl) (TpSvcChannelInterfaceMediaSignalling *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_media_signalling_implement_get_session_handlers (TpSvcChannelInterfaceMediaSignallingClass *klass, tp_svc_channel_interface_media_signalling_get_session_handlers_impl impl);
/**
 * tp_svc_channel_interface_media_signalling_return_from_get_session_handlers:
 * @context: The D-Bus method invocation context
 * @out_Session_Handlers: const GPtrArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_media_signalling_return_from_get_session_handlers (DBusGMethodInvocation *context,
    const GPtrArray *out_Session_Handlers);
static inline void
tp_svc_channel_interface_media_signalling_return_from_get_session_handlers (DBusGMethodInvocation *context,
    const GPtrArray *out_Session_Handlers)
{
  dbus_g_method_return (context,
      out_Session_Handlers);
}

void tp_svc_channel_interface_media_signalling_emit_new_session_handler (gpointer instance,
    const gchar *arg_Session_Handler,
    const gchar *arg_Session_Type);

/**
 * TpSvcChannelInterfaceMessages:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelInterfaceMessages TpSvcChannelInterfaceMessages;

/**
 * TpSvcChannelInterfaceMessagesClass:
 *
 * The class of TpSvcChannelInterfaceMessages.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_interface_messages (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_interface_messages_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (send_message);
 *   IMPLEMENT (get_pending_message_content);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelInterfaceMessagesClass TpSvcChannelInterfaceMessagesClass;

GType tp_svc_channel_interface_messages_get_type (void);
#define TP_TYPE_SVC_CHANNEL_INTERFACE_MESSAGES \
  (tp_svc_channel_interface_messages_get_type ())
#define TP_SVC_CHANNEL_INTERFACE_MESSAGES(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_MESSAGES, TpSvcChannelInterfaceMessages))
#define TP_IS_SVC_CHANNEL_INTERFACE_MESSAGES(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_MESSAGES))
#define TP_SVC_CHANNEL_INTERFACE_MESSAGES_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_MESSAGES, TpSvcChannelInterfaceMessagesClass))


typedef void (*tp_svc_channel_interface_messages_send_message_impl) (TpSvcChannelInterfaceMessages *self,
    const GPtrArray *in_Message,
    guint in_Flags,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_messages_implement_send_message (TpSvcChannelInterfaceMessagesClass *klass, tp_svc_channel_interface_messages_send_message_impl impl);
/**
 * tp_svc_channel_interface_messages_return_from_send_message:
 * @context: The D-Bus method invocation context
 * @out_Token: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_messages_return_from_send_message (DBusGMethodInvocation *context,
    const gchar *out_Token);
static inline void
tp_svc_channel_interface_messages_return_from_send_message (DBusGMethodInvocation *context,
    const gchar *out_Token)
{
  dbus_g_method_return (context,
      out_Token);
}

typedef void (*tp_svc_channel_interface_messages_get_pending_message_content_impl) (TpSvcChannelInterfaceMessages *self,
    guint in_Message_ID,
    const GArray *in_Parts,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_messages_implement_get_pending_message_content (TpSvcChannelInterfaceMessagesClass *klass, tp_svc_channel_interface_messages_get_pending_message_content_impl impl);
/**
 * tp_svc_channel_interface_messages_return_from_get_pending_message_content:
 * @context: The D-Bus method invocation context
 * @out_Content: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_messages_return_from_get_pending_message_content (DBusGMethodInvocation *context,
    GHashTable *out_Content);
static inline void
tp_svc_channel_interface_messages_return_from_get_pending_message_content (DBusGMethodInvocation *context,
    GHashTable *out_Content)
{
  dbus_g_method_return (context,
      out_Content);
}

void tp_svc_channel_interface_messages_emit_message_sent (gpointer instance,
    const GPtrArray *arg_Content,
    guint arg_Flags,
    const gchar *arg_Message_Token);
void tp_svc_channel_interface_messages_emit_pending_messages_removed (gpointer instance,
    const GArray *arg_Message_IDs);
void tp_svc_channel_interface_messages_emit_message_received (gpointer instance,
    const GPtrArray *arg_Message);

/**
 * TpSvcChannelInterfacePassword:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelInterfacePassword TpSvcChannelInterfacePassword;

/**
 * TpSvcChannelInterfacePasswordClass:
 *
 * The class of TpSvcChannelInterfacePassword.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_interface_password (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_interface_password_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (get_password_flags);
 *   IMPLEMENT (provide_password);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelInterfacePasswordClass TpSvcChannelInterfacePasswordClass;

GType tp_svc_channel_interface_password_get_type (void);
#define TP_TYPE_SVC_CHANNEL_INTERFACE_PASSWORD \
  (tp_svc_channel_interface_password_get_type ())
#define TP_SVC_CHANNEL_INTERFACE_PASSWORD(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_PASSWORD, TpSvcChannelInterfacePassword))
#define TP_IS_SVC_CHANNEL_INTERFACE_PASSWORD(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_PASSWORD))
#define TP_SVC_CHANNEL_INTERFACE_PASSWORD_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_PASSWORD, TpSvcChannelInterfacePasswordClass))


typedef void (*tp_svc_channel_interface_password_get_password_flags_impl) (TpSvcChannelInterfacePassword *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_password_implement_get_password_flags (TpSvcChannelInterfacePasswordClass *klass, tp_svc_channel_interface_password_get_password_flags_impl impl);
/**
 * tp_svc_channel_interface_password_return_from_get_password_flags:
 * @context: The D-Bus method invocation context
 * @out_Password_Flags: guint  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_password_return_from_get_password_flags (DBusGMethodInvocation *context,
    guint out_Password_Flags);
static inline void
tp_svc_channel_interface_password_return_from_get_password_flags (DBusGMethodInvocation *context,
    guint out_Password_Flags)
{
  dbus_g_method_return (context,
      out_Password_Flags);
}

typedef void (*tp_svc_channel_interface_password_provide_password_impl) (TpSvcChannelInterfacePassword *self,
    const gchar *in_Password,
    DBusGMethodInvocation *context);
void tp_svc_channel_interface_password_implement_provide_password (TpSvcChannelInterfacePasswordClass *klass, tp_svc_channel_interface_password_provide_password_impl impl);
/**
 * tp_svc_channel_interface_password_return_from_provide_password:
 * @context: The D-Bus method invocation context
 * @out_Correct: gboolean  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_interface_password_return_from_provide_password (DBusGMethodInvocation *context,
    gboolean out_Correct);
static inline void
tp_svc_channel_interface_password_return_from_provide_password (DBusGMethodInvocation *context,
    gboolean out_Correct)
{
  dbus_g_method_return (context,
      out_Correct);
}

void tp_svc_channel_interface_password_emit_password_flags_changed (gpointer instance,
    guint arg_Added,
    guint arg_Removed);

/**
 * TpSvcChannelInterfaceTube:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelInterfaceTube TpSvcChannelInterfaceTube;

/**
 * TpSvcChannelInterfaceTubeClass:
 *
 * The class of TpSvcChannelInterfaceTube.
 * This interface has no D-Bus methods, so an
 * implementation can typically pass %NULL to
 * G_IMPLEMENT_INTERFACE() as the interface
 * initialization function.
 */
typedef struct _TpSvcChannelInterfaceTubeClass TpSvcChannelInterfaceTubeClass;

GType tp_svc_channel_interface_tube_get_type (void);
#define TP_TYPE_SVC_CHANNEL_INTERFACE_TUBE \
  (tp_svc_channel_interface_tube_get_type ())
#define TP_SVC_CHANNEL_INTERFACE_TUBE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_TUBE, TpSvcChannelInterfaceTube))
#define TP_IS_SVC_CHANNEL_INTERFACE_TUBE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_TUBE))
#define TP_SVC_CHANNEL_INTERFACE_TUBE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_INTERFACE_TUBE, TpSvcChannelInterfaceTubeClass))


void tp_svc_channel_interface_tube_emit_tube_channel_state_changed (gpointer instance,
    guint arg_State);

/**
 * TpSvcChannelTypeContactList:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelTypeContactList TpSvcChannelTypeContactList;

/**
 * TpSvcChannelTypeContactListClass:
 *
 * The class of TpSvcChannelTypeContactList.
 * This interface has no D-Bus methods, so an
 * implementation can typically pass %NULL to
 * G_IMPLEMENT_INTERFACE() as the interface
 * initialization function.
 */
typedef struct _TpSvcChannelTypeContactListClass TpSvcChannelTypeContactListClass;

GType tp_svc_channel_type_contact_list_get_type (void);
#define TP_TYPE_SVC_CHANNEL_TYPE_CONTACT_LIST \
  (tp_svc_channel_type_contact_list_get_type ())
#define TP_SVC_CHANNEL_TYPE_CONTACT_LIST(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_TYPE_CONTACT_LIST, TpSvcChannelTypeContactList))
#define TP_IS_SVC_CHANNEL_TYPE_CONTACT_LIST(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_TYPE_CONTACT_LIST))
#define TP_SVC_CHANNEL_TYPE_CONTACT_LIST_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_TYPE_CONTACT_LIST, TpSvcChannelTypeContactListClass))



/**
 * TpSvcChannelTypeDBusTube:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelTypeDBusTube TpSvcChannelTypeDBusTube;

/**
 * TpSvcChannelTypeDBusTubeClass:
 *
 * The class of TpSvcChannelTypeDBusTube.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_type_dbus_tube (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_type_dbus_tube_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (offer);
 *   IMPLEMENT (accept);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelTypeDBusTubeClass TpSvcChannelTypeDBusTubeClass;

GType tp_svc_channel_type_dbus_tube_get_type (void);
#define TP_TYPE_SVC_CHANNEL_TYPE_DBUS_TUBE \
  (tp_svc_channel_type_dbus_tube_get_type ())
#define TP_SVC_CHANNEL_TYPE_DBUS_TUBE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_TYPE_DBUS_TUBE, TpSvcChannelTypeDBusTube))
#define TP_IS_SVC_CHANNEL_TYPE_DBUS_TUBE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_TYPE_DBUS_TUBE))
#define TP_SVC_CHANNEL_TYPE_DBUS_TUBE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_TYPE_DBUS_TUBE, TpSvcChannelTypeDBusTubeClass))


typedef void (*tp_svc_channel_type_dbus_tube_offer_impl) (TpSvcChannelTypeDBusTube *self,
    GHashTable *in_parameters,
    guint in_access_control,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_dbus_tube_implement_offer (TpSvcChannelTypeDBusTubeClass *klass, tp_svc_channel_type_dbus_tube_offer_impl impl);
/**
 * tp_svc_channel_type_dbus_tube_return_from_offer:
 * @context: The D-Bus method invocation context
 * @out_address: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_dbus_tube_return_from_offer (DBusGMethodInvocation *context,
    const gchar *out_address);
static inline void
tp_svc_channel_type_dbus_tube_return_from_offer (DBusGMethodInvocation *context,
    const gchar *out_address)
{
  dbus_g_method_return (context,
      out_address);
}

typedef void (*tp_svc_channel_type_dbus_tube_accept_impl) (TpSvcChannelTypeDBusTube *self,
    guint in_access_control,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_dbus_tube_implement_accept (TpSvcChannelTypeDBusTubeClass *klass, tp_svc_channel_type_dbus_tube_accept_impl impl);
/**
 * tp_svc_channel_type_dbus_tube_return_from_accept:
 * @context: The D-Bus method invocation context
 * @out_address: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_dbus_tube_return_from_accept (DBusGMethodInvocation *context,
    const gchar *out_address);
static inline void
tp_svc_channel_type_dbus_tube_return_from_accept (DBusGMethodInvocation *context,
    const gchar *out_address)
{
  dbus_g_method_return (context,
      out_address);
}

void tp_svc_channel_type_dbus_tube_emit_dbus_names_changed (gpointer instance,
    GHashTable *arg_Added,
    const GArray *arg_Removed);

/**
 * TpSvcChannelTypeFileTransfer:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelTypeFileTransfer TpSvcChannelTypeFileTransfer;

/**
 * TpSvcChannelTypeFileTransferClass:
 *
 * The class of TpSvcChannelTypeFileTransfer.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_type_file_transfer (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_type_file_transfer_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (accept_file);
 *   IMPLEMENT (provide_file);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelTypeFileTransferClass TpSvcChannelTypeFileTransferClass;

GType tp_svc_channel_type_file_transfer_get_type (void);
#define TP_TYPE_SVC_CHANNEL_TYPE_FILE_TRANSFER \
  (tp_svc_channel_type_file_transfer_get_type ())
#define TP_SVC_CHANNEL_TYPE_FILE_TRANSFER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_TYPE_FILE_TRANSFER, TpSvcChannelTypeFileTransfer))
#define TP_IS_SVC_CHANNEL_TYPE_FILE_TRANSFER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_TYPE_FILE_TRANSFER))
#define TP_SVC_CHANNEL_TYPE_FILE_TRANSFER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_TYPE_FILE_TRANSFER, TpSvcChannelTypeFileTransferClass))


typedef void (*tp_svc_channel_type_file_transfer_accept_file_impl) (TpSvcChannelTypeFileTransfer *self,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    guint64 in_Offset,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_file_transfer_implement_accept_file (TpSvcChannelTypeFileTransferClass *klass, tp_svc_channel_type_file_transfer_accept_file_impl impl);
/**
 * tp_svc_channel_type_file_transfer_return_from_accept_file:
 * @context: The D-Bus method invocation context
 * @out_Address: const GValue * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_file_transfer_return_from_accept_file (DBusGMethodInvocation *context,
    const GValue *out_Address);
static inline void
tp_svc_channel_type_file_transfer_return_from_accept_file (DBusGMethodInvocation *context,
    const GValue *out_Address)
{
  dbus_g_method_return (context,
      out_Address);
}

typedef void (*tp_svc_channel_type_file_transfer_provide_file_impl) (TpSvcChannelTypeFileTransfer *self,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_file_transfer_implement_provide_file (TpSvcChannelTypeFileTransferClass *klass, tp_svc_channel_type_file_transfer_provide_file_impl impl);
/**
 * tp_svc_channel_type_file_transfer_return_from_provide_file:
 * @context: The D-Bus method invocation context
 * @out_Address: const GValue * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_file_transfer_return_from_provide_file (DBusGMethodInvocation *context,
    const GValue *out_Address);
static inline void
tp_svc_channel_type_file_transfer_return_from_provide_file (DBusGMethodInvocation *context,
    const GValue *out_Address)
{
  dbus_g_method_return (context,
      out_Address);
}

void tp_svc_channel_type_file_transfer_emit_file_transfer_state_changed (gpointer instance,
    guint arg_State,
    guint arg_Reason);
void tp_svc_channel_type_file_transfer_emit_transferred_bytes_changed (gpointer instance,
    guint64 arg_Count);
void tp_svc_channel_type_file_transfer_emit_initial_offset_defined (gpointer instance,
    guint64 arg_InitialOffset);

/**
 * TpSvcChannelTypeRoomList:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelTypeRoomList TpSvcChannelTypeRoomList;

/**
 * TpSvcChannelTypeRoomListClass:
 *
 * The class of TpSvcChannelTypeRoomList.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_type_room_list (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_type_room_list_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (get_listing_rooms);
 *   IMPLEMENT (list_rooms);
 *   IMPLEMENT (stop_listing);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelTypeRoomListClass TpSvcChannelTypeRoomListClass;

GType tp_svc_channel_type_room_list_get_type (void);
#define TP_TYPE_SVC_CHANNEL_TYPE_ROOM_LIST \
  (tp_svc_channel_type_room_list_get_type ())
#define TP_SVC_CHANNEL_TYPE_ROOM_LIST(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_TYPE_ROOM_LIST, TpSvcChannelTypeRoomList))
#define TP_IS_SVC_CHANNEL_TYPE_ROOM_LIST(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_TYPE_ROOM_LIST))
#define TP_SVC_CHANNEL_TYPE_ROOM_LIST_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_TYPE_ROOM_LIST, TpSvcChannelTypeRoomListClass))


typedef void (*tp_svc_channel_type_room_list_get_listing_rooms_impl) (TpSvcChannelTypeRoomList *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_room_list_implement_get_listing_rooms (TpSvcChannelTypeRoomListClass *klass, tp_svc_channel_type_room_list_get_listing_rooms_impl impl);
/**
 * tp_svc_channel_type_room_list_return_from_get_listing_rooms:
 * @context: The D-Bus method invocation context
 * @out_In_Progress: gboolean  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_room_list_return_from_get_listing_rooms (DBusGMethodInvocation *context,
    gboolean out_In_Progress);
static inline void
tp_svc_channel_type_room_list_return_from_get_listing_rooms (DBusGMethodInvocation *context,
    gboolean out_In_Progress)
{
  dbus_g_method_return (context,
      out_In_Progress);
}

typedef void (*tp_svc_channel_type_room_list_list_rooms_impl) (TpSvcChannelTypeRoomList *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_room_list_implement_list_rooms (TpSvcChannelTypeRoomListClass *klass, tp_svc_channel_type_room_list_list_rooms_impl impl);
/**
 * tp_svc_channel_type_room_list_return_from_list_rooms:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_room_list_return_from_list_rooms (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_type_room_list_return_from_list_rooms (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_channel_type_room_list_stop_listing_impl) (TpSvcChannelTypeRoomList *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_room_list_implement_stop_listing (TpSvcChannelTypeRoomListClass *klass, tp_svc_channel_type_room_list_stop_listing_impl impl);
/**
 * tp_svc_channel_type_room_list_return_from_stop_listing:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_room_list_return_from_stop_listing (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_type_room_list_return_from_stop_listing (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

void tp_svc_channel_type_room_list_emit_got_rooms (gpointer instance,
    const GPtrArray *arg_Rooms);
void tp_svc_channel_type_room_list_emit_listing_rooms (gpointer instance,
    gboolean arg_Listing);

/**
 * TpSvcChannelTypeStreamTube:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelTypeStreamTube TpSvcChannelTypeStreamTube;

/**
 * TpSvcChannelTypeStreamTubeClass:
 *
 * The class of TpSvcChannelTypeStreamTube.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_type_stream_tube (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_type_stream_tube_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (offer);
 *   IMPLEMENT (accept);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelTypeStreamTubeClass TpSvcChannelTypeStreamTubeClass;

GType tp_svc_channel_type_stream_tube_get_type (void);
#define TP_TYPE_SVC_CHANNEL_TYPE_STREAM_TUBE \
  (tp_svc_channel_type_stream_tube_get_type ())
#define TP_SVC_CHANNEL_TYPE_STREAM_TUBE(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_TYPE_STREAM_TUBE, TpSvcChannelTypeStreamTube))
#define TP_IS_SVC_CHANNEL_TYPE_STREAM_TUBE(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_TYPE_STREAM_TUBE))
#define TP_SVC_CHANNEL_TYPE_STREAM_TUBE_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_TYPE_STREAM_TUBE, TpSvcChannelTypeStreamTubeClass))


typedef void (*tp_svc_channel_type_stream_tube_offer_impl) (TpSvcChannelTypeStreamTube *self,
    guint in_address_type,
    const GValue *in_address,
    guint in_access_control,
    GHashTable *in_parameters,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_stream_tube_implement_offer (TpSvcChannelTypeStreamTubeClass *klass, tp_svc_channel_type_stream_tube_offer_impl impl);
/**
 * tp_svc_channel_type_stream_tube_return_from_offer:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_stream_tube_return_from_offer (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_type_stream_tube_return_from_offer (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_channel_type_stream_tube_accept_impl) (TpSvcChannelTypeStreamTube *self,
    guint in_address_type,
    guint in_access_control,
    const GValue *in_access_control_param,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_stream_tube_implement_accept (TpSvcChannelTypeStreamTubeClass *klass, tp_svc_channel_type_stream_tube_accept_impl impl);
/**
 * tp_svc_channel_type_stream_tube_return_from_accept:
 * @context: The D-Bus method invocation context
 * @out_address: const GValue * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_stream_tube_return_from_accept (DBusGMethodInvocation *context,
    const GValue *out_address);
static inline void
tp_svc_channel_type_stream_tube_return_from_accept (DBusGMethodInvocation *context,
    const GValue *out_address)
{
  dbus_g_method_return (context,
      out_address);
}

void tp_svc_channel_type_stream_tube_emit_new_remote_connection (gpointer instance,
    guint arg_Handle,
    const GValue *arg_Connection_Param,
    guint arg_Connection_ID);
void tp_svc_channel_type_stream_tube_emit_new_local_connection (gpointer instance,
    guint arg_Connection_ID);
void tp_svc_channel_type_stream_tube_emit_connection_closed (gpointer instance,
    guint arg_Connection_ID,
    const gchar *arg_Error,
    const gchar *arg_Message);

/**
 * TpSvcChannelTypeStreamedMedia:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelTypeStreamedMedia TpSvcChannelTypeStreamedMedia;

/**
 * TpSvcChannelTypeStreamedMediaClass:
 *
 * The class of TpSvcChannelTypeStreamedMedia.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_type_streamed_media (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_type_streamed_media_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (list_streams);
 *   IMPLEMENT (remove_streams);
 *   IMPLEMENT (request_stream_direction);
 *   IMPLEMENT (request_streams);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelTypeStreamedMediaClass TpSvcChannelTypeStreamedMediaClass;

GType tp_svc_channel_type_streamed_media_get_type (void);
#define TP_TYPE_SVC_CHANNEL_TYPE_STREAMED_MEDIA \
  (tp_svc_channel_type_streamed_media_get_type ())
#define TP_SVC_CHANNEL_TYPE_STREAMED_MEDIA(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_TYPE_STREAMED_MEDIA, TpSvcChannelTypeStreamedMedia))
#define TP_IS_SVC_CHANNEL_TYPE_STREAMED_MEDIA(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_TYPE_STREAMED_MEDIA))
#define TP_SVC_CHANNEL_TYPE_STREAMED_MEDIA_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_TYPE_STREAMED_MEDIA, TpSvcChannelTypeStreamedMediaClass))


typedef void (*tp_svc_channel_type_streamed_media_list_streams_impl) (TpSvcChannelTypeStreamedMedia *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_streamed_media_implement_list_streams (TpSvcChannelTypeStreamedMediaClass *klass, tp_svc_channel_type_streamed_media_list_streams_impl impl);
/**
 * tp_svc_channel_type_streamed_media_return_from_list_streams:
 * @context: The D-Bus method invocation context
 * @out_Streams: const GPtrArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_streamed_media_return_from_list_streams (DBusGMethodInvocation *context,
    const GPtrArray *out_Streams);
static inline void
tp_svc_channel_type_streamed_media_return_from_list_streams (DBusGMethodInvocation *context,
    const GPtrArray *out_Streams)
{
  dbus_g_method_return (context,
      out_Streams);
}

typedef void (*tp_svc_channel_type_streamed_media_remove_streams_impl) (TpSvcChannelTypeStreamedMedia *self,
    const GArray *in_Streams,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_streamed_media_implement_remove_streams (TpSvcChannelTypeStreamedMediaClass *klass, tp_svc_channel_type_streamed_media_remove_streams_impl impl);
/**
 * tp_svc_channel_type_streamed_media_return_from_remove_streams:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_streamed_media_return_from_remove_streams (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_type_streamed_media_return_from_remove_streams (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_channel_type_streamed_media_request_stream_direction_impl) (TpSvcChannelTypeStreamedMedia *self,
    guint in_Stream_ID,
    guint in_Stream_Direction,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_streamed_media_implement_request_stream_direction (TpSvcChannelTypeStreamedMediaClass *klass, tp_svc_channel_type_streamed_media_request_stream_direction_impl impl);
/**
 * tp_svc_channel_type_streamed_media_return_from_request_stream_direction:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_streamed_media_return_from_request_stream_direction (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_type_streamed_media_return_from_request_stream_direction (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_channel_type_streamed_media_request_streams_impl) (TpSvcChannelTypeStreamedMedia *self,
    guint in_Contact_Handle,
    const GArray *in_Types,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_streamed_media_implement_request_streams (TpSvcChannelTypeStreamedMediaClass *klass, tp_svc_channel_type_streamed_media_request_streams_impl impl);
/**
 * tp_svc_channel_type_streamed_media_return_from_request_streams:
 * @context: The D-Bus method invocation context
 * @out_Streams: const GPtrArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_streamed_media_return_from_request_streams (DBusGMethodInvocation *context,
    const GPtrArray *out_Streams);
static inline void
tp_svc_channel_type_streamed_media_return_from_request_streams (DBusGMethodInvocation *context,
    const GPtrArray *out_Streams)
{
  dbus_g_method_return (context,
      out_Streams);
}

void tp_svc_channel_type_streamed_media_emit_stream_added (gpointer instance,
    guint arg_Stream_ID,
    guint arg_Contact_Handle,
    guint arg_Stream_Type);
void tp_svc_channel_type_streamed_media_emit_stream_direction_changed (gpointer instance,
    guint arg_Stream_ID,
    guint arg_Stream_Direction,
    guint arg_Pending_Flags);
void tp_svc_channel_type_streamed_media_emit_stream_error (gpointer instance,
    guint arg_Stream_ID,
    guint arg_Error_Code,
    const gchar *arg_Message);
void tp_svc_channel_type_streamed_media_emit_stream_removed (gpointer instance,
    guint arg_Stream_ID);
void tp_svc_channel_type_streamed_media_emit_stream_state_changed (gpointer instance,
    guint arg_Stream_ID,
    guint arg_Stream_State);

/**
 * TpSvcChannelTypeText:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelTypeText TpSvcChannelTypeText;

/**
 * TpSvcChannelTypeTextClass:
 *
 * The class of TpSvcChannelTypeText.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_type_text (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_type_text_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (acknowledge_pending_messages);
 *   IMPLEMENT (get_message_types);
 *   IMPLEMENT (list_pending_messages);
 *   IMPLEMENT (send);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelTypeTextClass TpSvcChannelTypeTextClass;

GType tp_svc_channel_type_text_get_type (void);
#define TP_TYPE_SVC_CHANNEL_TYPE_TEXT \
  (tp_svc_channel_type_text_get_type ())
#define TP_SVC_CHANNEL_TYPE_TEXT(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_TYPE_TEXT, TpSvcChannelTypeText))
#define TP_IS_SVC_CHANNEL_TYPE_TEXT(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_TYPE_TEXT))
#define TP_SVC_CHANNEL_TYPE_TEXT_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_TYPE_TEXT, TpSvcChannelTypeTextClass))


typedef void (*tp_svc_channel_type_text_acknowledge_pending_messages_impl) (TpSvcChannelTypeText *self,
    const GArray *in_IDs,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_text_implement_acknowledge_pending_messages (TpSvcChannelTypeTextClass *klass, tp_svc_channel_type_text_acknowledge_pending_messages_impl impl);
/**
 * tp_svc_channel_type_text_return_from_acknowledge_pending_messages:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_text_return_from_acknowledge_pending_messages (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_type_text_return_from_acknowledge_pending_messages (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_channel_type_text_get_message_types_impl) (TpSvcChannelTypeText *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_text_implement_get_message_types (TpSvcChannelTypeTextClass *klass, tp_svc_channel_type_text_get_message_types_impl impl);
/**
 * tp_svc_channel_type_text_return_from_get_message_types:
 * @context: The D-Bus method invocation context
 * @out_Available_Types: const GArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_text_return_from_get_message_types (DBusGMethodInvocation *context,
    const GArray *out_Available_Types);
static inline void
tp_svc_channel_type_text_return_from_get_message_types (DBusGMethodInvocation *context,
    const GArray *out_Available_Types)
{
  dbus_g_method_return (context,
      out_Available_Types);
}

typedef void (*tp_svc_channel_type_text_list_pending_messages_impl) (TpSvcChannelTypeText *self,
    gboolean in_Clear,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_text_implement_list_pending_messages (TpSvcChannelTypeTextClass *klass, tp_svc_channel_type_text_list_pending_messages_impl impl);
/**
 * tp_svc_channel_type_text_return_from_list_pending_messages:
 * @context: The D-Bus method invocation context
 * @out_Pending_Messages: const GPtrArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_text_return_from_list_pending_messages (DBusGMethodInvocation *context,
    const GPtrArray *out_Pending_Messages);
static inline void
tp_svc_channel_type_text_return_from_list_pending_messages (DBusGMethodInvocation *context,
    const GPtrArray *out_Pending_Messages)
{
  dbus_g_method_return (context,
      out_Pending_Messages);
}

typedef void (*tp_svc_channel_type_text_send_impl) (TpSvcChannelTypeText *self,
    guint in_Type,
    const gchar *in_Text,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_text_implement_send (TpSvcChannelTypeTextClass *klass, tp_svc_channel_type_text_send_impl impl);
/**
 * tp_svc_channel_type_text_return_from_send:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_text_return_from_send (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_type_text_return_from_send (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

void tp_svc_channel_type_text_emit_lost_message (gpointer instance);
void tp_svc_channel_type_text_emit_received (gpointer instance,
    guint arg_ID,
    guint arg_Timestamp,
    guint arg_Sender,
    guint arg_Type,
    guint arg_Flags,
    const gchar *arg_Text);
void tp_svc_channel_type_text_emit_send_error (gpointer instance,
    guint arg_Error,
    guint arg_Timestamp,
    guint arg_Type,
    const gchar *arg_Text);
void tp_svc_channel_type_text_emit_sent (gpointer instance,
    guint arg_Timestamp,
    guint arg_Type,
    const gchar *arg_Text);

/**
 * TpSvcChannelTypeTubes:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcChannelTypeTubes TpSvcChannelTypeTubes;

/**
 * TpSvcChannelTypeTubesClass:
 *
 * The class of TpSvcChannelTypeTubes.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_channel_type_tubes (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_channel_type_tubes_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (get_available_stream_tube_types);
 *   IMPLEMENT (get_available_tube_types);
 *   IMPLEMENT (list_tubes);
 *   IMPLEMENT (offer_d_bus_tube);
 *   IMPLEMENT (offer_stream_tube);
 *   IMPLEMENT (accept_d_bus_tube);
 *   IMPLEMENT (accept_stream_tube);
 *   IMPLEMENT (close_tube);
 *   IMPLEMENT (get_d_bus_tube_address);
 *   IMPLEMENT (get_d_bus_names);
 *   IMPLEMENT (get_stream_tube_socket_address);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcChannelTypeTubesClass TpSvcChannelTypeTubesClass;

GType tp_svc_channel_type_tubes_get_type (void);
#define TP_TYPE_SVC_CHANNEL_TYPE_TUBES \
  (tp_svc_channel_type_tubes_get_type ())
#define TP_SVC_CHANNEL_TYPE_TUBES(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CHANNEL_TYPE_TUBES, TpSvcChannelTypeTubes))
#define TP_IS_SVC_CHANNEL_TYPE_TUBES(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CHANNEL_TYPE_TUBES))
#define TP_SVC_CHANNEL_TYPE_TUBES_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CHANNEL_TYPE_TUBES, TpSvcChannelTypeTubesClass))


typedef void (*tp_svc_channel_type_tubes_get_available_stream_tube_types_impl) (TpSvcChannelTypeTubes *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_tubes_implement_get_available_stream_tube_types (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_get_available_stream_tube_types_impl impl);
/**
 * tp_svc_channel_type_tubes_return_from_get_available_stream_tube_types:
 * @context: The D-Bus method invocation context
 * @out_Available_Stream_Tube_Types: GHashTable * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_tubes_return_from_get_available_stream_tube_types (DBusGMethodInvocation *context,
    GHashTable *out_Available_Stream_Tube_Types);
static inline void
tp_svc_channel_type_tubes_return_from_get_available_stream_tube_types (DBusGMethodInvocation *context,
    GHashTable *out_Available_Stream_Tube_Types)
{
  dbus_g_method_return (context,
      out_Available_Stream_Tube_Types);
}

typedef void (*tp_svc_channel_type_tubes_get_available_tube_types_impl) (TpSvcChannelTypeTubes *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_tubes_implement_get_available_tube_types (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_get_available_tube_types_impl impl);
/**
 * tp_svc_channel_type_tubes_return_from_get_available_tube_types:
 * @context: The D-Bus method invocation context
 * @out_Available_Tube_Types: const GArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_tubes_return_from_get_available_tube_types (DBusGMethodInvocation *context,
    const GArray *out_Available_Tube_Types);
static inline void
tp_svc_channel_type_tubes_return_from_get_available_tube_types (DBusGMethodInvocation *context,
    const GArray *out_Available_Tube_Types)
{
  dbus_g_method_return (context,
      out_Available_Tube_Types);
}

typedef void (*tp_svc_channel_type_tubes_list_tubes_impl) (TpSvcChannelTypeTubes *self,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_tubes_implement_list_tubes (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_list_tubes_impl impl);
/**
 * tp_svc_channel_type_tubes_return_from_list_tubes:
 * @context: The D-Bus method invocation context
 * @out_Tubes: const GPtrArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_tubes_return_from_list_tubes (DBusGMethodInvocation *context,
    const GPtrArray *out_Tubes);
static inline void
tp_svc_channel_type_tubes_return_from_list_tubes (DBusGMethodInvocation *context,
    const GPtrArray *out_Tubes)
{
  dbus_g_method_return (context,
      out_Tubes);
}

typedef void (*tp_svc_channel_type_tubes_offer_d_bus_tube_impl) (TpSvcChannelTypeTubes *self,
    const gchar *in_Service,
    GHashTable *in_Parameters,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_tubes_implement_offer_d_bus_tube (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_offer_d_bus_tube_impl impl);
/**
 * tp_svc_channel_type_tubes_return_from_offer_d_bus_tube:
 * @context: The D-Bus method invocation context
 * @out_Tube_ID: guint  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_tubes_return_from_offer_d_bus_tube (DBusGMethodInvocation *context,
    guint out_Tube_ID);
static inline void
tp_svc_channel_type_tubes_return_from_offer_d_bus_tube (DBusGMethodInvocation *context,
    guint out_Tube_ID)
{
  dbus_g_method_return (context,
      out_Tube_ID);
}

typedef void (*tp_svc_channel_type_tubes_offer_stream_tube_impl) (TpSvcChannelTypeTubes *self,
    const gchar *in_Service,
    GHashTable *in_Parameters,
    guint in_Address_Type,
    const GValue *in_Address,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_tubes_implement_offer_stream_tube (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_offer_stream_tube_impl impl);
/**
 * tp_svc_channel_type_tubes_return_from_offer_stream_tube:
 * @context: The D-Bus method invocation context
 * @out_Tube_ID: guint  (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_tubes_return_from_offer_stream_tube (DBusGMethodInvocation *context,
    guint out_Tube_ID);
static inline void
tp_svc_channel_type_tubes_return_from_offer_stream_tube (DBusGMethodInvocation *context,
    guint out_Tube_ID)
{
  dbus_g_method_return (context,
      out_Tube_ID);
}

typedef void (*tp_svc_channel_type_tubes_accept_d_bus_tube_impl) (TpSvcChannelTypeTubes *self,
    guint in_ID,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_tubes_implement_accept_d_bus_tube (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_accept_d_bus_tube_impl impl);
/**
 * tp_svc_channel_type_tubes_return_from_accept_d_bus_tube:
 * @context: The D-Bus method invocation context
 * @out_Address: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_tubes_return_from_accept_d_bus_tube (DBusGMethodInvocation *context,
    const gchar *out_Address);
static inline void
tp_svc_channel_type_tubes_return_from_accept_d_bus_tube (DBusGMethodInvocation *context,
    const gchar *out_Address)
{
  dbus_g_method_return (context,
      out_Address);
}

typedef void (*tp_svc_channel_type_tubes_accept_stream_tube_impl) (TpSvcChannelTypeTubes *self,
    guint in_ID,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_tubes_implement_accept_stream_tube (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_accept_stream_tube_impl impl);
/**
 * tp_svc_channel_type_tubes_return_from_accept_stream_tube:
 * @context: The D-Bus method invocation context
 * @out_Address: const GValue * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_tubes_return_from_accept_stream_tube (DBusGMethodInvocation *context,
    const GValue *out_Address);
static inline void
tp_svc_channel_type_tubes_return_from_accept_stream_tube (DBusGMethodInvocation *context,
    const GValue *out_Address)
{
  dbus_g_method_return (context,
      out_Address);
}

typedef void (*tp_svc_channel_type_tubes_close_tube_impl) (TpSvcChannelTypeTubes *self,
    guint in_ID,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_tubes_implement_close_tube (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_close_tube_impl impl);
/**
 * tp_svc_channel_type_tubes_return_from_close_tube:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_tubes_return_from_close_tube (DBusGMethodInvocation *context);
static inline void
tp_svc_channel_type_tubes_return_from_close_tube (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_channel_type_tubes_get_d_bus_tube_address_impl) (TpSvcChannelTypeTubes *self,
    guint in_ID,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_tubes_implement_get_d_bus_tube_address (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_get_d_bus_tube_address_impl impl);
/**
 * tp_svc_channel_type_tubes_return_from_get_d_bus_tube_address:
 * @context: The D-Bus method invocation context
 * @out_Address: const gchar * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_tubes_return_from_get_d_bus_tube_address (DBusGMethodInvocation *context,
    const gchar *out_Address);
static inline void
tp_svc_channel_type_tubes_return_from_get_d_bus_tube_address (DBusGMethodInvocation *context,
    const gchar *out_Address)
{
  dbus_g_method_return (context,
      out_Address);
}

typedef void (*tp_svc_channel_type_tubes_get_d_bus_names_impl) (TpSvcChannelTypeTubes *self,
    guint in_ID,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_tubes_implement_get_d_bus_names (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_get_d_bus_names_impl impl);
/**
 * tp_svc_channel_type_tubes_return_from_get_d_bus_names:
 * @context: The D-Bus method invocation context
 * @out_DBus_Names: const GPtrArray * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_tubes_return_from_get_d_bus_names (DBusGMethodInvocation *context,
    const GPtrArray *out_DBus_Names);
static inline void
tp_svc_channel_type_tubes_return_from_get_d_bus_names (DBusGMethodInvocation *context,
    const GPtrArray *out_DBus_Names)
{
  dbus_g_method_return (context,
      out_DBus_Names);
}

typedef void (*tp_svc_channel_type_tubes_get_stream_tube_socket_address_impl) (TpSvcChannelTypeTubes *self,
    guint in_ID,
    DBusGMethodInvocation *context);
void tp_svc_channel_type_tubes_implement_get_stream_tube_socket_address (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_get_stream_tube_socket_address_impl impl);
/**
 * tp_svc_channel_type_tubes_return_from_get_stream_tube_socket_address:
 * @context: The D-Bus method invocation context
 * @out_Address_Type: guint  (FIXME, generate documentation)
 * @out_Address: const GValue * (FIXME, generate documentation)
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_channel_type_tubes_return_from_get_stream_tube_socket_address (DBusGMethodInvocation *context,
    guint out_Address_Type,
    const GValue *out_Address);
static inline void
tp_svc_channel_type_tubes_return_from_get_stream_tube_socket_address (DBusGMethodInvocation *context,
    guint out_Address_Type,
    const GValue *out_Address)
{
  dbus_g_method_return (context,
      out_Address_Type,
      out_Address);
}

void tp_svc_channel_type_tubes_emit_new_tube (gpointer instance,
    guint arg_ID,
    guint arg_Initiator,
    guint arg_Type,
    const gchar *arg_Service,
    GHashTable *arg_Parameters,
    guint arg_State);
void tp_svc_channel_type_tubes_emit_tube_state_changed (gpointer instance,
    guint arg_ID,
    guint arg_State);
void tp_svc_channel_type_tubes_emit_tube_closed (gpointer instance,
    guint arg_ID);
void tp_svc_channel_type_tubes_emit_d_bus_names_changed (gpointer instance,
    guint arg_ID,
    const GPtrArray *arg_Added,
    const GArray *arg_Removed);
void tp_svc_channel_type_tubes_emit_stream_tube_new_connection (gpointer instance,
    guint arg_ID,
    guint arg_Handle);


G_END_DECLS
