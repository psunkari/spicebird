#include "_gen/tp-svc-media-session-handler.h"

#include <telepathy-glib/dbus.h>
#include "_gen/signals-marshal.h"

static const DBusGObjectInfo _tp_svc_media_session_handler_object_info;

struct _TpSvcMediaSessionHandlerClass {
    GTypeInterface parent_class;
    tp_svc_media_session_handler_error_impl error;
    tp_svc_media_session_handler_ready_impl ready;
};

enum {
    SIGNAL_MEDIA_SESSION_HANDLER_NewStreamHandler,
    N_MEDIA_SESSION_HANDLER_SIGNALS
};
static guint media_session_handler_signals[N_MEDIA_SESSION_HANDLER_SIGNALS] = {0};

static void tp_svc_media_session_handler_base_init (gpointer klass);

GType
tp_svc_media_session_handler_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcMediaSessionHandlerClass),
        tp_svc_media_session_handler_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcMediaSessionHandler", &info, 0);
    }

  return type;
}

/**
 * tp_svc_media_session_handler_error_impl:
 * @self: The object implementing this interface
 * @in_Error_Code: guint  (FIXME, generate documentation)
 * @in_Message: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Error on interface org.freedesktop.Telepathy.Media.SessionHandler.
 */
static void
tp_svc_media_session_handler_error (TpSvcMediaSessionHandler *self,
    guint in_Error_Code,
    const gchar *in_Message,
    DBusGMethodInvocation *context)
{
  tp_svc_media_session_handler_error_impl impl = (TP_SVC_MEDIA_SESSION_HANDLER_GET_CLASS (self)->error);

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
 * tp_svc_media_session_handler_implement_error:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Error D-Bus method
 *
 * Register an implementation for the Error method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_media_session_handler_implement_error (TpSvcMediaSessionHandlerClass *klass, tp_svc_media_session_handler_error_impl impl)
{
  klass->error = impl;
}

/**
 * tp_svc_media_session_handler_ready_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Ready on interface org.freedesktop.Telepathy.Media.SessionHandler.
 */
static void
tp_svc_media_session_handler_ready (TpSvcMediaSessionHandler *self,
    DBusGMethodInvocation *context)
{
  tp_svc_media_session_handler_ready_impl impl = (TP_SVC_MEDIA_SESSION_HANDLER_GET_CLASS (self)->ready);

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
 * tp_svc_media_session_handler_implement_ready:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Ready D-Bus method
 *
 * Register an implementation for the Ready method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_media_session_handler_implement_ready (TpSvcMediaSessionHandlerClass *klass, tp_svc_media_session_handler_ready_impl impl)
{
  klass->ready = impl;
}

/**
 * tp_svc_media_session_handler_emit_new_stream_handler:
 * @instance: The object implementing this interface
 * @arg_Stream_Handler: const gchar * (FIXME, generate documentation)
 * @arg_ID: guint  (FIXME, generate documentation)
 * @arg_Media_Type: guint  (FIXME, generate documentation)
 * @arg_Direction: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * NewStreamHandler signal on interface org.freedesktop.Telepathy.Media.SessionHandler.
 */
void
tp_svc_media_session_handler_emit_new_stream_handler (gpointer instance,
    const gchar *arg_Stream_Handler,
    guint arg_ID,
    guint arg_Media_Type,
    guint arg_Direction)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_MEDIA_SESSION_HANDLER));
  g_signal_emit (instance,
      media_session_handler_signals[SIGNAL_MEDIA_SESSION_HANDLER_NewStreamHandler],
      0,
      arg_Stream_Handler,
      arg_ID,
      arg_Media_Type,
      arg_Direction);
}

static inline void
tp_svc_media_session_handler_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_media_session_handler_get_type (),
      &_tp_svc_media_session_handler_object_info);

  /**
   * TpSvcMediaSessionHandler::new-stream-handler:
   * @arg_Stream_Handler: const gchar * (FIXME, generate documentation)
   * @arg_ID: guint  (FIXME, generate documentation)
   * @arg_Media_Type: guint  (FIXME, generate documentation)
   * @arg_Direction: guint  (FIXME, generate documentation)
   *
   * The NewStreamHandler D-Bus signal is emitted whenever this GObject signal is.
   */
  media_session_handler_signals[SIGNAL_MEDIA_SESSION_HANDLER_NewStreamHandler] =
  g_signal_new ("new-stream-handler",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__BOXED_UINT_UINT_UINT,
      G_TYPE_NONE,
      4,
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT);

}
static void
tp_svc_media_session_handler_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_media_session_handler_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_media_session_handler_methods[] = {
  { (GCallback) tp_svc_media_session_handler_error, _tp_marshal_VOID__UINT_STRING_POINTER, 0 },
  { (GCallback) tp_svc_media_session_handler_ready, g_cclosure_marshal_VOID__POINTER, 83 },
};

static const DBusGObjectInfo _tp_svc_media_session_handler_object_info = {
  0,
  _tp_svc_media_session_handler_methods,
  2,
"org.freedesktop.Telepathy.Media.SessionHandler\0Error\0A\0Error_Code\0I\0u\0Message\0I\0s\0\0org.freedesktop.Telepathy.Media.SessionHandler\0Ready\0A\0\0\0",
"org.freedesktop.Telepathy.Media.SessionHandler\0NewStreamHandler\0\0",
"\0\0",
};


