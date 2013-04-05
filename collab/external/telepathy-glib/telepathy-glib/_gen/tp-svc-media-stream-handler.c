#include "_gen/tp-svc-media-stream-handler.h"

#include <telepathy-glib/dbus.h>
#include "_gen/signals-marshal.h"

static const DBusGObjectInfo _tp_svc_media_stream_handler_object_info;

struct _TpSvcMediaStreamHandlerClass {
    GTypeInterface parent_class;
    tp_svc_media_stream_handler_codec_choice_impl codec_choice;
    tp_svc_media_stream_handler_error_impl error;
    tp_svc_media_stream_handler_native_candidates_prepared_impl native_candidates_prepared;
    tp_svc_media_stream_handler_new_active_candidate_pair_impl new_active_candidate_pair;
    tp_svc_media_stream_handler_new_native_candidate_impl new_native_candidate;
    tp_svc_media_stream_handler_ready_impl ready;
    tp_svc_media_stream_handler_set_local_codecs_impl set_local_codecs;
    tp_svc_media_stream_handler_stream_state_impl stream_state;
    tp_svc_media_stream_handler_supported_codecs_impl supported_codecs;
    tp_svc_media_stream_handler_codecs_updated_impl codecs_updated;
    tp_svc_media_stream_handler_hold_state_impl hold_state;
    tp_svc_media_stream_handler_unhold_failure_impl unhold_failure;
};

enum {
    SIGNAL_MEDIA_STREAM_HANDLER_AddRemoteCandidate,
    SIGNAL_MEDIA_STREAM_HANDLER_Close,
    SIGNAL_MEDIA_STREAM_HANDLER_RemoveRemoteCandidate,
    SIGNAL_MEDIA_STREAM_HANDLER_SetActiveCandidatePair,
    SIGNAL_MEDIA_STREAM_HANDLER_SetRemoteCandidateList,
    SIGNAL_MEDIA_STREAM_HANDLER_SetRemoteCodecs,
    SIGNAL_MEDIA_STREAM_HANDLER_SetStreamPlaying,
    SIGNAL_MEDIA_STREAM_HANDLER_SetStreamSending,
    SIGNAL_MEDIA_STREAM_HANDLER_StartTelephonyEvent,
    SIGNAL_MEDIA_STREAM_HANDLER_StopTelephonyEvent,
    SIGNAL_MEDIA_STREAM_HANDLER_SetStreamHeld,
    N_MEDIA_STREAM_HANDLER_SIGNALS
};
static guint media_stream_handler_signals[N_MEDIA_STREAM_HANDLER_SIGNALS] = {0};

static void tp_svc_media_stream_handler_base_init (gpointer klass);

GType
tp_svc_media_stream_handler_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcMediaStreamHandlerClass),
        tp_svc_media_stream_handler_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcMediaStreamHandler", &info, 0);
    }

  return type;
}

/**
 * tp_svc_media_stream_handler_codec_choice_impl:
 * @self: The object implementing this interface
 * @in_Codec_ID: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * CodecChoice on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
static void
tp_svc_media_stream_handler_codec_choice (TpSvcMediaStreamHandler *self,
    guint in_Codec_ID,
    DBusGMethodInvocation *context)
{
  tp_svc_media_stream_handler_codec_choice_impl impl = (TP_SVC_MEDIA_STREAM_HANDLER_GET_CLASS (self)->codec_choice);

  if (impl != NULL)
    {
      (impl) (self,
        in_Codec_ID,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_media_stream_handler_implement_codec_choice:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the CodecChoice D-Bus method
 *
 * Register an implementation for the CodecChoice method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_media_stream_handler_implement_codec_choice (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_codec_choice_impl impl)
{
  klass->codec_choice = impl;
}

/**
 * tp_svc_media_stream_handler_error_impl:
 * @self: The object implementing this interface
 * @in_Error_Code: guint  (FIXME, generate documentation)
 * @in_Message: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Error on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
static void
tp_svc_media_stream_handler_error (TpSvcMediaStreamHandler *self,
    guint in_Error_Code,
    const gchar *in_Message,
    DBusGMethodInvocation *context)
{
  tp_svc_media_stream_handler_error_impl impl = (TP_SVC_MEDIA_STREAM_HANDLER_GET_CLASS (self)->error);

  if (impl != NULL)
    {
      (impl) (self,
        in_Error_Code,
        in_Message,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_media_stream_handler_implement_error:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Error D-Bus method
 *
 * Register an implementation for the Error method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_media_stream_handler_implement_error (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_error_impl impl)
{
  klass->error = impl;
}

/**
 * tp_svc_media_stream_handler_native_candidates_prepared_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * NativeCandidatesPrepared on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
static void
tp_svc_media_stream_handler_native_candidates_prepared (TpSvcMediaStreamHandler *self,
    DBusGMethodInvocation *context)
{
  tp_svc_media_stream_handler_native_candidates_prepared_impl impl = (TP_SVC_MEDIA_STREAM_HANDLER_GET_CLASS (self)->native_candidates_prepared);

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
 * tp_svc_media_stream_handler_implement_native_candidates_prepared:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the NativeCandidatesPrepared D-Bus method
 *
 * Register an implementation for the NativeCandidatesPrepared method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_media_stream_handler_implement_native_candidates_prepared (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_native_candidates_prepared_impl impl)
{
  klass->native_candidates_prepared = impl;
}

/**
 * tp_svc_media_stream_handler_new_active_candidate_pair_impl:
 * @self: The object implementing this interface
 * @in_Native_Candidate_ID: const gchar * (FIXME, generate documentation)
 * @in_Remote_Candidate_ID: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * NewActiveCandidatePair on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
static void
tp_svc_media_stream_handler_new_active_candidate_pair (TpSvcMediaStreamHandler *self,
    const gchar *in_Native_Candidate_ID,
    const gchar *in_Remote_Candidate_ID,
    DBusGMethodInvocation *context)
{
  tp_svc_media_stream_handler_new_active_candidate_pair_impl impl = (TP_SVC_MEDIA_STREAM_HANDLER_GET_CLASS (self)->new_active_candidate_pair);

  if (impl != NULL)
    {
      (impl) (self,
        in_Native_Candidate_ID,
        in_Remote_Candidate_ID,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_media_stream_handler_implement_new_active_candidate_pair:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the NewActiveCandidatePair D-Bus method
 *
 * Register an implementation for the NewActiveCandidatePair method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_media_stream_handler_implement_new_active_candidate_pair (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_new_active_candidate_pair_impl impl)
{
  klass->new_active_candidate_pair = impl;
}

/**
 * tp_svc_media_stream_handler_new_native_candidate_impl:
 * @self: The object implementing this interface
 * @in_Candidate_ID: const gchar * (FIXME, generate documentation)
 * @in_Transports: const GPtrArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * NewNativeCandidate on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
static void
tp_svc_media_stream_handler_new_native_candidate (TpSvcMediaStreamHandler *self,
    const gchar *in_Candidate_ID,
    const GPtrArray *in_Transports,
    DBusGMethodInvocation *context)
{
  tp_svc_media_stream_handler_new_native_candidate_impl impl = (TP_SVC_MEDIA_STREAM_HANDLER_GET_CLASS (self)->new_native_candidate);

  if (impl != NULL)
    {
      (impl) (self,
        in_Candidate_ID,
        in_Transports,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_media_stream_handler_implement_new_native_candidate:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the NewNativeCandidate D-Bus method
 *
 * Register an implementation for the NewNativeCandidate method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_media_stream_handler_implement_new_native_candidate (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_new_native_candidate_impl impl)
{
  klass->new_native_candidate = impl;
}

/**
 * tp_svc_media_stream_handler_ready_impl:
 * @self: The object implementing this interface
 * @in_Codecs: const GPtrArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Ready on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
static void
tp_svc_media_stream_handler_ready (TpSvcMediaStreamHandler *self,
    const GPtrArray *in_Codecs,
    DBusGMethodInvocation *context)
{
  tp_svc_media_stream_handler_ready_impl impl = (TP_SVC_MEDIA_STREAM_HANDLER_GET_CLASS (self)->ready);

  if (impl != NULL)
    {
      (impl) (self,
        in_Codecs,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_media_stream_handler_implement_ready:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Ready D-Bus method
 *
 * Register an implementation for the Ready method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_media_stream_handler_implement_ready (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_ready_impl impl)
{
  klass->ready = impl;
}

/**
 * tp_svc_media_stream_handler_set_local_codecs_impl:
 * @self: The object implementing this interface
 * @in_Codecs: const GPtrArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SetLocalCodecs on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
static void
tp_svc_media_stream_handler_set_local_codecs (TpSvcMediaStreamHandler *self,
    const GPtrArray *in_Codecs,
    DBusGMethodInvocation *context)
{
  tp_svc_media_stream_handler_set_local_codecs_impl impl = (TP_SVC_MEDIA_STREAM_HANDLER_GET_CLASS (self)->set_local_codecs);

  if (impl != NULL)
    {
      (impl) (self,
        in_Codecs,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_media_stream_handler_implement_set_local_codecs:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SetLocalCodecs D-Bus method
 *
 * Register an implementation for the SetLocalCodecs method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_media_stream_handler_implement_set_local_codecs (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_set_local_codecs_impl impl)
{
  klass->set_local_codecs = impl;
}

/**
 * tp_svc_media_stream_handler_stream_state_impl:
 * @self: The object implementing this interface
 * @in_State: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * StreamState on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
static void
tp_svc_media_stream_handler_stream_state (TpSvcMediaStreamHandler *self,
    guint in_State,
    DBusGMethodInvocation *context)
{
  tp_svc_media_stream_handler_stream_state_impl impl = (TP_SVC_MEDIA_STREAM_HANDLER_GET_CLASS (self)->stream_state);

  if (impl != NULL)
    {
      (impl) (self,
        in_State,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_media_stream_handler_implement_stream_state:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the StreamState D-Bus method
 *
 * Register an implementation for the StreamState method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_media_stream_handler_implement_stream_state (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_stream_state_impl impl)
{
  klass->stream_state = impl;
}

/**
 * tp_svc_media_stream_handler_supported_codecs_impl:
 * @self: The object implementing this interface
 * @in_Codecs: const GPtrArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SupportedCodecs on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
static void
tp_svc_media_stream_handler_supported_codecs (TpSvcMediaStreamHandler *self,
    const GPtrArray *in_Codecs,
    DBusGMethodInvocation *context)
{
  tp_svc_media_stream_handler_supported_codecs_impl impl = (TP_SVC_MEDIA_STREAM_HANDLER_GET_CLASS (self)->supported_codecs);

  if (impl != NULL)
    {
      (impl) (self,
        in_Codecs,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_media_stream_handler_implement_supported_codecs:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SupportedCodecs D-Bus method
 *
 * Register an implementation for the SupportedCodecs method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_media_stream_handler_implement_supported_codecs (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_supported_codecs_impl impl)
{
  klass->supported_codecs = impl;
}

/**
 * tp_svc_media_stream_handler_codecs_updated_impl:
 * @self: The object implementing this interface
 * @in_Codecs: const GPtrArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * CodecsUpdated on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
static void
tp_svc_media_stream_handler_codecs_updated (TpSvcMediaStreamHandler *self,
    const GPtrArray *in_Codecs,
    DBusGMethodInvocation *context)
{
  tp_svc_media_stream_handler_codecs_updated_impl impl = (TP_SVC_MEDIA_STREAM_HANDLER_GET_CLASS (self)->codecs_updated);

  if (impl != NULL)
    {
      (impl) (self,
        in_Codecs,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_media_stream_handler_implement_codecs_updated:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the CodecsUpdated D-Bus method
 *
 * Register an implementation for the CodecsUpdated method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_media_stream_handler_implement_codecs_updated (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_codecs_updated_impl impl)
{
  klass->codecs_updated = impl;
}

/**
 * tp_svc_media_stream_handler_hold_state_impl:
 * @self: The object implementing this interface
 * @in_Held: gboolean  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * HoldState on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
static void
tp_svc_media_stream_handler_hold_state (TpSvcMediaStreamHandler *self,
    gboolean in_Held,
    DBusGMethodInvocation *context)
{
  tp_svc_media_stream_handler_hold_state_impl impl = (TP_SVC_MEDIA_STREAM_HANDLER_GET_CLASS (self)->hold_state);

  if (impl != NULL)
    {
      (impl) (self,
        in_Held,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_media_stream_handler_implement_hold_state:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the HoldState D-Bus method
 *
 * Register an implementation for the HoldState method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_media_stream_handler_implement_hold_state (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_hold_state_impl impl)
{
  klass->hold_state = impl;
}

/**
 * tp_svc_media_stream_handler_unhold_failure_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * UnholdFailure on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
static void
tp_svc_media_stream_handler_unhold_failure (TpSvcMediaStreamHandler *self,
    DBusGMethodInvocation *context)
{
  tp_svc_media_stream_handler_unhold_failure_impl impl = (TP_SVC_MEDIA_STREAM_HANDLER_GET_CLASS (self)->unhold_failure);

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
 * tp_svc_media_stream_handler_implement_unhold_failure:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the UnholdFailure D-Bus method
 *
 * Register an implementation for the UnholdFailure method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_media_stream_handler_implement_unhold_failure (TpSvcMediaStreamHandlerClass *klass, tp_svc_media_stream_handler_unhold_failure_impl impl)
{
  klass->unhold_failure = impl;
}

/**
 * tp_svc_media_stream_handler_emit_add_remote_candidate:
 * @instance: The object implementing this interface
 * @arg_Candidate_ID: const gchar * (FIXME, generate documentation)
 * @arg_Transports: const GPtrArray * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * AddRemoteCandidate signal on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
void
tp_svc_media_stream_handler_emit_add_remote_candidate (gpointer instance,
    const gchar *arg_Candidate_ID,
    const GPtrArray *arg_Transports)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_MEDIA_STREAM_HANDLER));
  g_signal_emit (instance,
      media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_AddRemoteCandidate],
      0,
      arg_Candidate_ID,
      arg_Transports);
}

/**
 * tp_svc_media_stream_handler_emit_close:
 * @instance: The object implementing this interface
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * Close signal on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
void
tp_svc_media_stream_handler_emit_close (gpointer instance)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_MEDIA_STREAM_HANDLER));
  g_signal_emit (instance,
      media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_Close],
      0);
}

/**
 * tp_svc_media_stream_handler_emit_remove_remote_candidate:
 * @instance: The object implementing this interface
 * @arg_Candidate_ID: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * RemoveRemoteCandidate signal on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
void
tp_svc_media_stream_handler_emit_remove_remote_candidate (gpointer instance,
    const gchar *arg_Candidate_ID)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_MEDIA_STREAM_HANDLER));
  g_signal_emit (instance,
      media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_RemoveRemoteCandidate],
      0,
      arg_Candidate_ID);
}

/**
 * tp_svc_media_stream_handler_emit_set_active_candidate_pair:
 * @instance: The object implementing this interface
 * @arg_Native_Candidate_ID: const gchar * (FIXME, generate documentation)
 * @arg_Remote_Candidate_ID: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * SetActiveCandidatePair signal on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
void
tp_svc_media_stream_handler_emit_set_active_candidate_pair (gpointer instance,
    const gchar *arg_Native_Candidate_ID,
    const gchar *arg_Remote_Candidate_ID)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_MEDIA_STREAM_HANDLER));
  g_signal_emit (instance,
      media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_SetActiveCandidatePair],
      0,
      arg_Native_Candidate_ID,
      arg_Remote_Candidate_ID);
}

/**
 * tp_svc_media_stream_handler_emit_set_remote_candidate_list:
 * @instance: The object implementing this interface
 * @arg_Remote_Candidates: const GPtrArray * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * SetRemoteCandidateList signal on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
void
tp_svc_media_stream_handler_emit_set_remote_candidate_list (gpointer instance,
    const GPtrArray *arg_Remote_Candidates)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_MEDIA_STREAM_HANDLER));
  g_signal_emit (instance,
      media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_SetRemoteCandidateList],
      0,
      arg_Remote_Candidates);
}

/**
 * tp_svc_media_stream_handler_emit_set_remote_codecs:
 * @instance: The object implementing this interface
 * @arg_Codecs: const GPtrArray * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * SetRemoteCodecs signal on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
void
tp_svc_media_stream_handler_emit_set_remote_codecs (gpointer instance,
    const GPtrArray *arg_Codecs)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_MEDIA_STREAM_HANDLER));
  g_signal_emit (instance,
      media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_SetRemoteCodecs],
      0,
      arg_Codecs);
}

/**
 * tp_svc_media_stream_handler_emit_set_stream_playing:
 * @instance: The object implementing this interface
 * @arg_Playing: gboolean  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * SetStreamPlaying signal on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
void
tp_svc_media_stream_handler_emit_set_stream_playing (gpointer instance,
    gboolean arg_Playing)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_MEDIA_STREAM_HANDLER));
  g_signal_emit (instance,
      media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_SetStreamPlaying],
      0,
      arg_Playing);
}

/**
 * tp_svc_media_stream_handler_emit_set_stream_sending:
 * @instance: The object implementing this interface
 * @arg_Sending: gboolean  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * SetStreamSending signal on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
void
tp_svc_media_stream_handler_emit_set_stream_sending (gpointer instance,
    gboolean arg_Sending)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_MEDIA_STREAM_HANDLER));
  g_signal_emit (instance,
      media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_SetStreamSending],
      0,
      arg_Sending);
}

/**
 * tp_svc_media_stream_handler_emit_start_telephony_event:
 * @instance: The object implementing this interface
 * @arg_Event: guchar  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * StartTelephonyEvent signal on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
void
tp_svc_media_stream_handler_emit_start_telephony_event (gpointer instance,
    guchar arg_Event)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_MEDIA_STREAM_HANDLER));
  g_signal_emit (instance,
      media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_StartTelephonyEvent],
      0,
      arg_Event);
}

/**
 * tp_svc_media_stream_handler_emit_stop_telephony_event:
 * @instance: The object implementing this interface
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * StopTelephonyEvent signal on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
void
tp_svc_media_stream_handler_emit_stop_telephony_event (gpointer instance)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_MEDIA_STREAM_HANDLER));
  g_signal_emit (instance,
      media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_StopTelephonyEvent],
      0);
}

/**
 * tp_svc_media_stream_handler_emit_set_stream_held:
 * @instance: The object implementing this interface
 * @arg_Held: gboolean  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * SetStreamHeld signal on interface org.freedesktop.Telepathy.Media.StreamHandler.
 */
void
tp_svc_media_stream_handler_emit_set_stream_held (gpointer instance,
    gboolean arg_Held)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_MEDIA_STREAM_HANDLER));
  g_signal_emit (instance,
      media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_SetStreamHeld],
      0,
      arg_Held);
}

static inline void
tp_svc_media_stream_handler_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[5] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "a(sq)", 0, NULL, NULL }, /* STUNServers */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "b", 0, NULL, NULL }, /* CreatedLocally */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "s", 0, NULL, NULL }, /* NATTraversal */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "aa{sv}", 0, NULL, NULL }, /* RelayInfo */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_media_stream_handler_get_type (),
      &_tp_svc_media_stream_handler_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Media.StreamHandler");
  properties[0].name = g_quark_from_static_string ("STUNServers");
  properties[0].type = (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, G_TYPE_UINT, G_TYPE_INVALID))));
  properties[1].name = g_quark_from_static_string ("CreatedLocally");
  properties[1].type = G_TYPE_BOOLEAN;
  properties[2].name = g_quark_from_static_string ("NATTraversal");
  properties[2].type = G_TYPE_STRING;
  properties[3].name = g_quark_from_static_string ("RelayInfo");
  properties[3].type = (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE))));
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_MEDIA_STREAM_HANDLER, &interface);

  /**
   * TpSvcMediaStreamHandler::add-remote-candidate:
   * @arg_Candidate_ID: const gchar * (FIXME, generate documentation)
   * @arg_Transports: const GPtrArray * (FIXME, generate documentation)
   *
   * The AddRemoteCandidate D-Bus signal is emitted whenever this GObject signal is.
   */
  media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_AddRemoteCandidate] =
  g_signal_new ("add-remote-candidate",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__STRING_BOXED,
      G_TYPE_NONE,
      2,
      G_TYPE_STRING,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_DOUBLE, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))));

  /**
   * TpSvcMediaStreamHandler::close:
   *
   * The Close D-Bus signal is emitted whenever this GObject signal is.
   */
  media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_Close] =
  g_signal_new ("close",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__VOID,
      G_TYPE_NONE,
      0);

  /**
   * TpSvcMediaStreamHandler::remove-remote-candidate:
   * @arg_Candidate_ID: const gchar * (FIXME, generate documentation)
   *
   * The RemoveRemoteCandidate D-Bus signal is emitted whenever this GObject signal is.
   */
  media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_RemoveRemoteCandidate] =
  g_signal_new ("remove-remote-candidate",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__STRING,
      G_TYPE_NONE,
      1,
      G_TYPE_STRING);

  /**
   * TpSvcMediaStreamHandler::set-active-candidate-pair:
   * @arg_Native_Candidate_ID: const gchar * (FIXME, generate documentation)
   * @arg_Remote_Candidate_ID: const gchar * (FIXME, generate documentation)
   *
   * The SetActiveCandidatePair D-Bus signal is emitted whenever this GObject signal is.
   */
  media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_SetActiveCandidatePair] =
  g_signal_new ("set-active-candidate-pair",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__STRING_STRING,
      G_TYPE_NONE,
      2,
      G_TYPE_STRING,
      G_TYPE_STRING);

  /**
   * TpSvcMediaStreamHandler::set-remote-candidate-list:
   * @arg_Remote_Candidates: const GPtrArray * (FIXME, generate documentation)
   *
   * The SetRemoteCandidateList D-Bus signal is emitted whenever this GObject signal is.
   */
  media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_SetRemoteCandidateList] =
  g_signal_new ("set-remote-candidate-list",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,
      1,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_DOUBLE, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))), G_TYPE_INVALID)))));

  /**
   * TpSvcMediaStreamHandler::set-remote-codecs:
   * @arg_Codecs: const GPtrArray * (FIXME, generate documentation)
   *
   * The SetRemoteCodecs D-Bus signal is emitted whenever this GObject signal is.
   */
  media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_SetRemoteCodecs] =
  g_signal_new ("set-remote-codecs",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,
      1,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))));

  /**
   * TpSvcMediaStreamHandler::set-stream-playing:
   * @arg_Playing: gboolean  (FIXME, generate documentation)
   *
   * The SetStreamPlaying D-Bus signal is emitted whenever this GObject signal is.
   */
  media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_SetStreamPlaying] =
  g_signal_new ("set-stream-playing",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOOLEAN,
      G_TYPE_NONE,
      1,
      G_TYPE_BOOLEAN);

  /**
   * TpSvcMediaStreamHandler::set-stream-sending:
   * @arg_Sending: gboolean  (FIXME, generate documentation)
   *
   * The SetStreamSending D-Bus signal is emitted whenever this GObject signal is.
   */
  media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_SetStreamSending] =
  g_signal_new ("set-stream-sending",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOOLEAN,
      G_TYPE_NONE,
      1,
      G_TYPE_BOOLEAN);

  /**
   * TpSvcMediaStreamHandler::start-telephony-event:
   * @arg_Event: guchar  (FIXME, generate documentation)
   *
   * The StartTelephonyEvent D-Bus signal is emitted whenever this GObject signal is.
   */
  media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_StartTelephonyEvent] =
  g_signal_new ("start-telephony-event",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__UCHAR,
      G_TYPE_NONE,
      1,
      G_TYPE_UCHAR);

  /**
   * TpSvcMediaStreamHandler::stop-telephony-event:
   *
   * The StopTelephonyEvent D-Bus signal is emitted whenever this GObject signal is.
   */
  media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_StopTelephonyEvent] =
  g_signal_new ("stop-telephony-event",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__VOID,
      G_TYPE_NONE,
      0);

  /**
   * TpSvcMediaStreamHandler::set-stream-held:
   * @arg_Held: gboolean  (FIXME, generate documentation)
   *
   * The SetStreamHeld D-Bus signal is emitted whenever this GObject signal is.
   */
  media_stream_handler_signals[SIGNAL_MEDIA_STREAM_HANDLER_SetStreamHeld] =
  g_signal_new ("set-stream-held",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOOLEAN,
      G_TYPE_NONE,
      1,
      G_TYPE_BOOLEAN);

}
static void
tp_svc_media_stream_handler_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_media_stream_handler_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_media_stream_handler_methods[] = {
  { (GCallback) tp_svc_media_stream_handler_codec_choice, g_cclosure_marshal_VOID__UINT_POINTER, 0 },
  { (GCallback) tp_svc_media_stream_handler_error, _tp_marshal_VOID__UINT_STRING_POINTER, 74 },
  { (GCallback) tp_svc_media_stream_handler_native_candidates_prepared, g_cclosure_marshal_VOID__POINTER, 156 },
  { (GCallback) tp_svc_media_stream_handler_new_active_candidate_pair, _tp_marshal_VOID__STRING_STRING_POINTER, 230 },
  { (GCallback) tp_svc_media_stream_handler_new_native_candidate, _tp_marshal_VOID__STRING_BOXED_POINTER, 350 },
  { (GCallback) tp_svc_media_stream_handler_ready, _tp_marshal_VOID__BOXED_POINTER, 462 },
  { (GCallback) tp_svc_media_stream_handler_set_local_codecs, _tp_marshal_VOID__BOXED_POINTER, 540 },
  { (GCallback) tp_svc_media_stream_handler_stream_state, g_cclosure_marshal_VOID__UINT_POINTER, 627 },
  { (GCallback) tp_svc_media_stream_handler_supported_codecs, _tp_marshal_VOID__BOXED_POINTER, 698 },
  { (GCallback) tp_svc_media_stream_handler_codecs_updated, _tp_marshal_VOID__BOXED_POINTER, 786 },
  { (GCallback) tp_svc_media_stream_handler_hold_state, _tp_marshal_VOID__BOOLEAN_POINTER, 872 },
  { (GCallback) tp_svc_media_stream_handler_unhold_failure, g_cclosure_marshal_VOID__POINTER, 940 },
};

static const DBusGObjectInfo _tp_svc_media_stream_handler_object_info = {
  0,
  _tp_svc_media_stream_handler_methods,
  12,
"org.freedesktop.Telepathy.Media.StreamHandler\0CodecChoice\0A\0Codec_ID\0I\0u\0\0org.freedesktop.Telepathy.Media.StreamHandler\0Error\0A\0Error_Code\0I\0u\0Message\0I\0s\0\0org.freedesktop.Telepathy.Media.StreamHandler\0NativeCandidatesPrepared\0A\0\0org.freedesktop.Telepathy.Media.StreamHandler\0NewActiveCandidatePair\0A\0Native_Candidate_ID\0I\0s\0Remote_Candidate_ID\0I\0s\0\0org.freedesktop.Telepathy.Media.StreamHandler\0NewNativeCandidate\0A\0Candidate_ID\0I\0s\0Transports\0I\0a(usuussduss)\0\0org.freedesktop.Telepathy.Media.StreamHandler\0Ready\0A\0Codecs\0I\0a(usuuua{ss})\0\0org.freedesktop.Telepathy.Media.StreamHandler\0SetLocalCodecs\0A\0Codecs\0I\0a(usuuua{ss})\0\0org.freedesktop.Telepathy.Media.StreamHandler\0StreamState\0A\0State\0I\0u\0\0org.freedesktop.Telepathy.Media.StreamHandler\0SupportedCodecs\0A\0Codecs\0I\0a(usuuua{ss})\0\0org.freedesktop.Telepathy.Media.StreamHandler\0CodecsUpdated\0A\0Codecs\0I\0a(usuuua{ss})\0\0org.freedesktop.Telepathy.Media.StreamHandler\0HoldState\0A\0Held\0I\0b\0\0org.freedesktop.Telepathy.Media.StreamHandler\0UnholdFailure\0A\0\0\0",
"org.freedesktop.Telepathy.Media.StreamHandler\0AddRemoteCandidate\0org.freedesktop.Telepathy.Media.StreamHandler\0Close\0org.freedesktop.Telepathy.Media.StreamHandler\0RemoveRemoteCandidate\0org.freedesktop.Telepathy.Media.StreamHandler\0SetActiveCandidatePair\0org.freedesktop.Telepathy.Media.StreamHandler\0SetRemoteCandidateList\0org.freedesktop.Telepathy.Media.StreamHandler\0SetRemoteCodecs\0org.freedesktop.Telepathy.Media.StreamHandler\0SetStreamPlaying\0org.freedesktop.Telepathy.Media.StreamHandler\0SetStreamSending\0org.freedesktop.Telepathy.Media.StreamHandler\0StartTelephonyEvent\0org.freedesktop.Telepathy.Media.StreamHandler\0StopTelephonyEvent\0org.freedesktop.Telepathy.Media.StreamHandler\0SetStreamHeld\0\0",
"\0\0",
};


