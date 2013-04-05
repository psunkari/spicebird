#include <glib-object.h>
#include <dbus/dbus-glib.h>
#include <telepathy-glib/dbus-properties-mixin.h>

G_BEGIN_DECLS

/**
 * TpSvcMediaStreamHandler:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcMediaStreamHandler TpSvcMediaStreamHandler;

/**
 * TpSvcMediaStreamHandlerClass:
 *
 * The class of TpSvcMediaStreamHandler.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_media_stream_handler (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_media_stream_handler_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (codec_choice);
 *   IMPLEMENT (error);
 *   IMPLEMENT (native_candidates_prepared);
 *   IMPLEMENT (new_active_candidate_pair);
 *   IMPLEMENT (new_native_candidate);
 *   IMPLEMENT (ready);
 *   IMPLEMENT (set_local_codecs);
 *   IMPLEMENT (stream_state);
 *   IMPLEMENT (supported_codecs);
 *   IMPLEMENT (codecs_updated);
 *   IMPLEMENT (hold_state);
 *   IMPLEMENT (unhold_failure);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcMediaStreamHandlerClass TpSvcMediaStreamHandlerClass;

GType tp_svc_media_stream_handler_get_type (void);
#define TP_TYPE_SVC_MEDIA_STREAM_HANDLER \
  (tp_svc_media_stream_handler_get_type ())
#define TP_SVC_MEDIA_STREAM_HANDLER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_MEDIA_STREAM_HANDLER, TpSvcMediaStreamHandler))
#define TP_IS_SVC_MEDIA_STREAM_HANDLER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_MEDIA_STREAM_HANDLER))
#define TP_SVC_MEDIA_STREAM_HANDLER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_MEDIA_STREAM_HANDLER, TpSvcMediaStreamHandlerClass))


typedef void (*tp_svc_media_stream_handler_codec_choice_impl) (TpSvcMediaStreamHandler *self,
    guint in_Codec_ID,
    DBusGMethodInvocation *context);
void tp_svc_media_stream_handler_implement_codec_choice (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_codec_choice_impl impl);
/**
 * tp_svc_media_stream_handler_return_from_codec_choice:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_media_stream_handler_return_from_codec_choice (DBusGMethodInvocation *context);
static inline void
tp_svc_media_stream_handler_return_from_codec_choice (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_media_stream_handler_error_impl) (TpSvcMediaStreamHandler *self,
    guint in_Error_Code,
    const gchar *in_Message,
    DBusGMethodInvocation *context);
void tp_svc_media_stream_handler_implement_error (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_error_impl impl);
/**
 * tp_svc_media_stream_handler_return_from_error:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_media_stream_handler_return_from_error (DBusGMethodInvocation *context);
static inline void
tp_svc_media_stream_handler_return_from_error (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_media_stream_handler_native_candidates_prepared_impl) (TpSvcMediaStreamHandler *self,
    DBusGMethodInvocation *context);
void tp_svc_media_stream_handler_implement_native_candidates_prepared (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_native_candidates_prepared_impl impl);
/**
 * tp_svc_media_stream_handler_return_from_native_candidates_prepared:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_media_stream_handler_return_from_native_candidates_prepared (DBusGMethodInvocation *context);
static inline void
tp_svc_media_stream_handler_return_from_native_candidates_prepared (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_media_stream_handler_new_active_candidate_pair_impl) (TpSvcMediaStreamHandler *self,
    const gchar *in_Native_Candidate_ID,
    const gchar *in_Remote_Candidate_ID,
    DBusGMethodInvocation *context);
void tp_svc_media_stream_handler_implement_new_active_candidate_pair (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_new_active_candidate_pair_impl impl);
/**
 * tp_svc_media_stream_handler_return_from_new_active_candidate_pair:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_media_stream_handler_return_from_new_active_candidate_pair (DBusGMethodInvocation *context);
static inline void
tp_svc_media_stream_handler_return_from_new_active_candidate_pair (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_media_stream_handler_new_native_candidate_impl) (TpSvcMediaStreamHandler *self,
    const gchar *in_Candidate_ID,
    const GPtrArray *in_Transports,
    DBusGMethodInvocation *context);
void tp_svc_media_stream_handler_implement_new_native_candidate (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_new_native_candidate_impl impl);
/**
 * tp_svc_media_stream_handler_return_from_new_native_candidate:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_media_stream_handler_return_from_new_native_candidate (DBusGMethodInvocation *context);
static inline void
tp_svc_media_stream_handler_return_from_new_native_candidate (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_media_stream_handler_ready_impl) (TpSvcMediaStreamHandler *self,
    const GPtrArray *in_Codecs,
    DBusGMethodInvocation *context);
void tp_svc_media_stream_handler_implement_ready (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_ready_impl impl);
/**
 * tp_svc_media_stream_handler_return_from_ready:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_media_stream_handler_return_from_ready (DBusGMethodInvocation *context);
static inline void
tp_svc_media_stream_handler_return_from_ready (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_media_stream_handler_set_local_codecs_impl) (TpSvcMediaStreamHandler *self,
    const GPtrArray *in_Codecs,
    DBusGMethodInvocation *context);
void tp_svc_media_stream_handler_implement_set_local_codecs (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_set_local_codecs_impl impl);
/**
 * tp_svc_media_stream_handler_return_from_set_local_codecs:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_media_stream_handler_return_from_set_local_codecs (DBusGMethodInvocation *context);
static inline void
tp_svc_media_stream_handler_return_from_set_local_codecs (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_media_stream_handler_stream_state_impl) (TpSvcMediaStreamHandler *self,
    guint in_State,
    DBusGMethodInvocation *context);
void tp_svc_media_stream_handler_implement_stream_state (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_stream_state_impl impl);
/**
 * tp_svc_media_stream_handler_return_from_stream_state:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_media_stream_handler_return_from_stream_state (DBusGMethodInvocation *context);
static inline void
tp_svc_media_stream_handler_return_from_stream_state (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_media_stream_handler_supported_codecs_impl) (TpSvcMediaStreamHandler *self,
    const GPtrArray *in_Codecs,
    DBusGMethodInvocation *context);
void tp_svc_media_stream_handler_implement_supported_codecs (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_supported_codecs_impl impl);
/**
 * tp_svc_media_stream_handler_return_from_supported_codecs:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_media_stream_handler_return_from_supported_codecs (DBusGMethodInvocation *context);
static inline void
tp_svc_media_stream_handler_return_from_supported_codecs (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_media_stream_handler_codecs_updated_impl) (TpSvcMediaStreamHandler *self,
    const GPtrArray *in_Codecs,
    DBusGMethodInvocation *context);
void tp_svc_media_stream_handler_implement_codecs_updated (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_codecs_updated_impl impl);
/**
 * tp_svc_media_stream_handler_return_from_codecs_updated:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_media_stream_handler_return_from_codecs_updated (DBusGMethodInvocation *context);
static inline void
tp_svc_media_stream_handler_return_from_codecs_updated (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_media_stream_handler_hold_state_impl) (TpSvcMediaStreamHandler *self,
    gboolean in_Held,
    DBusGMethodInvocation *context);
void tp_svc_media_stream_handler_implement_hold_state (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_hold_state_impl impl);
/**
 * tp_svc_media_stream_handler_return_from_hold_state:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_media_stream_handler_return_from_hold_state (DBusGMethodInvocation *context);
static inline void
tp_svc_media_stream_handler_return_from_hold_state (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_media_stream_handler_unhold_failure_impl) (TpSvcMediaStreamHandler *self,
    DBusGMethodInvocation *context);
void tp_svc_media_stream_handler_implement_unhold_failure (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_unhold_failure_impl impl);
/**
 * tp_svc_media_stream_handler_return_from_unhold_failure:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_media_stream_handler_return_from_unhold_failure (DBusGMethodInvocation *context);
static inline void
tp_svc_media_stream_handler_return_from_unhold_failure (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

void tp_svc_media_stream_handler_emit_add_remote_candidate (gpointer instance,
    const gchar *arg_Candidate_ID,
    const GPtrArray *arg_Transports);
void tp_svc_media_stream_handler_emit_close (gpointer instance);
void tp_svc_media_stream_handler_emit_remove_remote_candidate (gpointer instance,
    const gchar *arg_Candidate_ID);
void tp_svc_media_stream_handler_emit_set_active_candidate_pair (gpointer instance,
    const gchar *arg_Native_Candidate_ID,
    const gchar *arg_Remote_Candidate_ID);
void tp_svc_media_stream_handler_emit_set_remote_candidate_list (gpointer instance,
    const GPtrArray *arg_Remote_Candidates);
void tp_svc_media_stream_handler_emit_set_remote_codecs (gpointer instance,
    const GPtrArray *arg_Codecs);
void tp_svc_media_stream_handler_emit_set_stream_playing (gpointer instance,
    gboolean arg_Playing);
void tp_svc_media_stream_handler_emit_set_stream_sending (gpointer instance,
    gboolean arg_Sending);
void tp_svc_media_stream_handler_emit_start_telephony_event (gpointer instance,
    guchar arg_Event);
void tp_svc_media_stream_handler_emit_stop_telephony_event (gpointer instance);
void tp_svc_media_stream_handler_emit_set_stream_held (gpointer instance,
    gboolean arg_Held);


G_END_DECLS
