#include "_gen/tp-svc-channel.h"

#include <telepathy-glib/dbus.h>
#include "_gen/signals-marshal.h"

static const DBusGObjectInfo _tp_svc_channel_object_info;

struct _TpSvcChannelClass {
    GTypeInterface parent_class;
    tp_svc_channel_close_impl close;
    tp_svc_channel_get_channel_type_impl get_channel_type;
    tp_svc_channel_get_handle_impl get_handle;
    tp_svc_channel_get_interfaces_impl get_interfaces;
};

enum {
    SIGNAL_CHANNEL_Closed,
    N_CHANNEL_SIGNALS
};
static guint channel_signals[N_CHANNEL_SIGNALS] = {0};

static void tp_svc_channel_base_init (gpointer klass);

GType
tp_svc_channel_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelClass),
        tp_svc_channel_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannel", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_close_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Close on interface org.freedesktop.Telepathy.Channel.
 */
static void
tp_svc_channel_close (TpSvcChannel *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_close_impl impl = (TP_SVC_CHANNEL_GET_CLASS (self)->close);

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
 * tp_svc_channel_implement_close:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Close D-Bus method
 *
 * Register an implementation for the Close method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_implement_close (TpSvcChannelClass *klass, tp_svc_channel_close_impl impl)
{
  klass->close = impl;
}

/**
 * tp_svc_channel_get_channel_type_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetChannelType on interface org.freedesktop.Telepathy.Channel.
 */
static void
tp_svc_channel_get_channel_type (TpSvcChannel *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_get_channel_type_impl impl = (TP_SVC_CHANNEL_GET_CLASS (self)->get_channel_type);

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
 * tp_svc_channel_implement_get_channel_type:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetChannelType D-Bus method
 *
 * Register an implementation for the GetChannelType method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_implement_get_channel_type (TpSvcChannelClass *klass, tp_svc_channel_get_channel_type_impl impl)
{
  klass->get_channel_type = impl;
}

/**
 * tp_svc_channel_get_handle_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetHandle on interface org.freedesktop.Telepathy.Channel.
 */
static void
tp_svc_channel_get_handle (TpSvcChannel *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_get_handle_impl impl = (TP_SVC_CHANNEL_GET_CLASS (self)->get_handle);

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
 * tp_svc_channel_implement_get_handle:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetHandle D-Bus method
 *
 * Register an implementation for the GetHandle method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_implement_get_handle (TpSvcChannelClass *klass, tp_svc_channel_get_handle_impl impl)
{
  klass->get_handle = impl;
}

/**
 * tp_svc_channel_get_interfaces_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetInterfaces on interface org.freedesktop.Telepathy.Channel.
 */
static void
tp_svc_channel_get_interfaces (TpSvcChannel *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_get_interfaces_impl impl = (TP_SVC_CHANNEL_GET_CLASS (self)->get_interfaces);

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
 * tp_svc_channel_implement_get_interfaces:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetInterfaces D-Bus method
 *
 * Register an implementation for the GetInterfaces method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_implement_get_interfaces (TpSvcChannelClass *klass, tp_svc_channel_get_interfaces_impl impl)
{
  klass->get_interfaces = impl;
}

/**
 * tp_svc_channel_emit_closed:
 * @instance: The object implementing this interface
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * Closed signal on interface org.freedesktop.Telepathy.Channel.
 */
void
tp_svc_channel_emit_closed (gpointer instance)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL));
  g_signal_emit (instance,
      channel_signals[SIGNAL_CHANNEL_Closed],
      0);
}

static inline void
tp_svc_channel_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[9] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "s", 0, NULL, NULL }, /* ChannelType */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "as", 0, NULL, NULL }, /* Interfaces */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* TargetHandle */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "s", 0, NULL, NULL }, /* TargetID */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* TargetHandleType */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "b", 0, NULL, NULL }, /* Requested */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* InitiatorHandle */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "s", 0, NULL, NULL }, /* InitiatorID */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_channel_get_type (),
      &_tp_svc_channel_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel");
  properties[0].name = g_quark_from_static_string ("ChannelType");
  properties[0].type = G_TYPE_STRING;
  properties[1].name = g_quark_from_static_string ("Interfaces");
  properties[1].type = G_TYPE_STRV;
  properties[2].name = g_quark_from_static_string ("TargetHandle");
  properties[2].type = G_TYPE_UINT;
  properties[3].name = g_quark_from_static_string ("TargetID");
  properties[3].type = G_TYPE_STRING;
  properties[4].name = g_quark_from_static_string ("TargetHandleType");
  properties[4].type = G_TYPE_UINT;
  properties[5].name = g_quark_from_static_string ("Requested");
  properties[5].type = G_TYPE_BOOLEAN;
  properties[6].name = g_quark_from_static_string ("InitiatorHandle");
  properties[6].type = G_TYPE_UINT;
  properties[7].name = g_quark_from_static_string ("InitiatorID");
  properties[7].type = G_TYPE_STRING;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CHANNEL, &interface);

  /**
   * TpSvcChannel::closed:
   *
   * The Closed D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_signals[SIGNAL_CHANNEL_Closed] =
  g_signal_new ("closed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__VOID,
      G_TYPE_NONE,
      0);

}
static void
tp_svc_channel_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_methods[] = {
  { (GCallback) tp_svc_channel_close, g_cclosure_marshal_VOID__POINTER, 0 },
  { (GCallback) tp_svc_channel_get_channel_type, g_cclosure_marshal_VOID__POINTER, 43 },
  { (GCallback) tp_svc_channel_get_handle, g_cclosure_marshal_VOID__POINTER, 116 },
  { (GCallback) tp_svc_channel_get_interfaces, g_cclosure_marshal_VOID__POINTER, 212 },
};

static const DBusGObjectInfo _tp_svc_channel_object_info = {
  0,
  _tp_svc_channel_methods,
  4,
"org.freedesktop.Telepathy.Channel\0Close\0A\0\0org.freedesktop.Telepathy.Channel\0GetChannelType\0A\0Channel_Type\0O\0F\0N\0s\0\0org.freedesktop.Telepathy.Channel\0GetHandle\0A\0Target_Handle_Type\0O\0F\0N\0u\0Target_Handle\0O\0F\0N\0u\0\0org.freedesktop.Telepathy.Channel\0GetInterfaces\0A\0Interfaces\0O\0F\0N\0as\0\0\0",
"org.freedesktop.Telepathy.Channel\0Closed\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_interface_call_state_object_info;

struct _TpSvcChannelInterfaceCallStateClass {
    GTypeInterface parent_class;
    tp_svc_channel_interface_call_state_get_call_states_impl get_call_states;
};

enum {
    SIGNAL_CHANNEL_INTERFACE_CALL_STATE_CallStateChanged,
    N_CHANNEL_INTERFACE_CALL_STATE_SIGNALS
};
static guint channel_interface_call_state_signals[N_CHANNEL_INTERFACE_CALL_STATE_SIGNALS] = {0};

static void tp_svc_channel_interface_call_state_base_init (gpointer klass);

GType
tp_svc_channel_interface_call_state_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelInterfaceCallStateClass),
        tp_svc_channel_interface_call_state_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelInterfaceCallState", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_interface_call_state_get_call_states_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetCallStates on interface org.freedesktop.Telepathy.Channel.Interface.CallState.
 */
static void
tp_svc_channel_interface_call_state_get_call_states (TpSvcChannelInterfaceCallState *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_call_state_get_call_states_impl impl = (TP_SVC_CHANNEL_INTERFACE_CALL_STATE_GET_CLASS (self)->get_call_states);

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
 * tp_svc_channel_interface_call_state_implement_get_call_states:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetCallStates D-Bus method
 *
 * Register an implementation for the GetCallStates method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_call_state_implement_get_call_states (TpSvcChannelInterfaceCallStateClass *klass, tp_svc_channel_interface_call_state_get_call_states_impl impl)
{
  klass->get_call_states = impl;
}

/**
 * tp_svc_channel_interface_call_state_emit_call_state_changed:
 * @instance: The object implementing this interface
 * @arg_Contact: guint  (FIXME, generate documentation)
 * @arg_State: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * CallStateChanged signal on interface org.freedesktop.Telepathy.Channel.Interface.CallState.
 */
void
tp_svc_channel_interface_call_state_emit_call_state_changed (gpointer instance,
    guint arg_Contact,
    guint arg_State)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_INTERFACE_CALL_STATE));
  g_signal_emit (instance,
      channel_interface_call_state_signals[SIGNAL_CHANNEL_INTERFACE_CALL_STATE_CallStateChanged],
      0,
      arg_Contact,
      arg_State);
}

static inline void
tp_svc_channel_interface_call_state_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_channel_interface_call_state_get_type (),
      &_tp_svc_channel_interface_call_state_object_info);

  /**
   * TpSvcChannelInterfaceCallState::call-state-changed:
   * @arg_Contact: guint  (FIXME, generate documentation)
   * @arg_State: guint  (FIXME, generate documentation)
   *
   * The CallStateChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_interface_call_state_signals[SIGNAL_CHANNEL_INTERFACE_CALL_STATE_CallStateChanged] =
  g_signal_new ("call-state-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT,
      G_TYPE_NONE,
      2,
      G_TYPE_UINT,
      G_TYPE_UINT);

}
static void
tp_svc_channel_interface_call_state_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_interface_call_state_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_interface_call_state_methods[] = {
  { (GCallback) tp_svc_channel_interface_call_state_get_call_states, g_cclosure_marshal_VOID__POINTER, 0 },
};

static const DBusGObjectInfo _tp_svc_channel_interface_call_state_object_info = {
  0,
  _tp_svc_channel_interface_call_state_methods,
  1,
"org.freedesktop.Telepathy.Channel.Interface.CallState\0GetCallStates\0A\0States\0O\0F\0N\0a{uu}\0\0\0",
"org.freedesktop.Telepathy.Channel.Interface.CallState\0CallStateChanged\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_interface_chat_state_object_info;

struct _TpSvcChannelInterfaceChatStateClass {
    GTypeInterface parent_class;
    tp_svc_channel_interface_chat_state_set_chat_state_impl set_chat_state;
};

enum {
    SIGNAL_CHANNEL_INTERFACE_CHAT_STATE_ChatStateChanged,
    N_CHANNEL_INTERFACE_CHAT_STATE_SIGNALS
};
static guint channel_interface_chat_state_signals[N_CHANNEL_INTERFACE_CHAT_STATE_SIGNALS] = {0};

static void tp_svc_channel_interface_chat_state_base_init (gpointer klass);

GType
tp_svc_channel_interface_chat_state_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelInterfaceChatStateClass),
        tp_svc_channel_interface_chat_state_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelInterfaceChatState", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_interface_chat_state_set_chat_state_impl:
 * @self: The object implementing this interface
 * @in_State: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SetChatState on interface org.freedesktop.Telepathy.Channel.Interface.ChatState.
 */
static void
tp_svc_channel_interface_chat_state_set_chat_state (TpSvcChannelInterfaceChatState *self,
    guint in_State,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_chat_state_set_chat_state_impl impl = (TP_SVC_CHANNEL_INTERFACE_CHAT_STATE_GET_CLASS (self)->set_chat_state);

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
 * tp_svc_channel_interface_chat_state_implement_set_chat_state:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SetChatState D-Bus method
 *
 * Register an implementation for the SetChatState method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_chat_state_implement_set_chat_state (TpSvcChannelInterfaceChatStateClass *klass, tp_svc_channel_interface_chat_state_set_chat_state_impl impl)
{
  klass->set_chat_state = impl;
}

/**
 * tp_svc_channel_interface_chat_state_emit_chat_state_changed:
 * @instance: The object implementing this interface
 * @arg_Contact: guint  (FIXME, generate documentation)
 * @arg_State: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * ChatStateChanged signal on interface org.freedesktop.Telepathy.Channel.Interface.ChatState.
 */
void
tp_svc_channel_interface_chat_state_emit_chat_state_changed (gpointer instance,
    guint arg_Contact,
    guint arg_State)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_INTERFACE_CHAT_STATE));
  g_signal_emit (instance,
      channel_interface_chat_state_signals[SIGNAL_CHANNEL_INTERFACE_CHAT_STATE_ChatStateChanged],
      0,
      arg_Contact,
      arg_State);
}

static inline void
tp_svc_channel_interface_chat_state_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_channel_interface_chat_state_get_type (),
      &_tp_svc_channel_interface_chat_state_object_info);

  /**
   * TpSvcChannelInterfaceChatState::chat-state-changed:
   * @arg_Contact: guint  (FIXME, generate documentation)
   * @arg_State: guint  (FIXME, generate documentation)
   *
   * The ChatStateChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_interface_chat_state_signals[SIGNAL_CHANNEL_INTERFACE_CHAT_STATE_ChatStateChanged] =
  g_signal_new ("chat-state-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT,
      G_TYPE_NONE,
      2,
      G_TYPE_UINT,
      G_TYPE_UINT);

}
static void
tp_svc_channel_interface_chat_state_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_interface_chat_state_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_interface_chat_state_methods[] = {
  { (GCallback) tp_svc_channel_interface_chat_state_set_chat_state, g_cclosure_marshal_VOID__UINT_POINTER, 0 },
};

static const DBusGObjectInfo _tp_svc_channel_interface_chat_state_object_info = {
  0,
  _tp_svc_channel_interface_chat_state_methods,
  1,
"org.freedesktop.Telepathy.Channel.Interface.ChatState\0SetChatState\0A\0State\0I\0u\0\0\0",
"org.freedesktop.Telepathy.Channel.Interface.ChatState\0ChatStateChanged\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_interface_dtmf_object_info;

struct _TpSvcChannelInterfaceDTMFClass {
    GTypeInterface parent_class;
    tp_svc_channel_interface_dtmf_start_tone_impl start_tone;
    tp_svc_channel_interface_dtmf_stop_tone_impl stop_tone;
};

static void tp_svc_channel_interface_dtmf_base_init (gpointer klass);

GType
tp_svc_channel_interface_dtmf_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelInterfaceDTMFClass),
        tp_svc_channel_interface_dtmf_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelInterfaceDTMF", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_interface_dtmf_start_tone_impl:
 * @self: The object implementing this interface
 * @in_Stream_ID: guint  (FIXME, generate documentation)
 * @in_Event: guchar  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * StartTone on interface org.freedesktop.Telepathy.Channel.Interface.DTMF.
 */
static void
tp_svc_channel_interface_dtmf_start_tone (TpSvcChannelInterfaceDTMF *self,
    guint in_Stream_ID,
    guchar in_Event,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_dtmf_start_tone_impl impl = (TP_SVC_CHANNEL_INTERFACE_DTMF_GET_CLASS (self)->start_tone);

  if (impl != NULL)
    {
      (impl) (self,
        in_Stream_ID,
        in_Event,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_interface_dtmf_implement_start_tone:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the StartTone D-Bus method
 *
 * Register an implementation for the StartTone method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_dtmf_implement_start_tone (TpSvcChannelInterfaceDTMFClass *klass, tp_svc_channel_interface_dtmf_start_tone_impl impl)
{
  klass->start_tone = impl;
}

/**
 * tp_svc_channel_interface_dtmf_stop_tone_impl:
 * @self: The object implementing this interface
 * @in_Stream_ID: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * StopTone on interface org.freedesktop.Telepathy.Channel.Interface.DTMF.
 */
static void
tp_svc_channel_interface_dtmf_stop_tone (TpSvcChannelInterfaceDTMF *self,
    guint in_Stream_ID,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_dtmf_stop_tone_impl impl = (TP_SVC_CHANNEL_INTERFACE_DTMF_GET_CLASS (self)->stop_tone);

  if (impl != NULL)
    {
      (impl) (self,
        in_Stream_ID,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_interface_dtmf_implement_stop_tone:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the StopTone D-Bus method
 *
 * Register an implementation for the StopTone method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_dtmf_implement_stop_tone (TpSvcChannelInterfaceDTMFClass *klass, tp_svc_channel_interface_dtmf_stop_tone_impl impl)
{
  klass->stop_tone = impl;
}

static inline void
tp_svc_channel_interface_dtmf_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_channel_interface_dtmf_get_type (),
      &_tp_svc_channel_interface_dtmf_object_info);

}
static void
tp_svc_channel_interface_dtmf_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_interface_dtmf_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_interface_dtmf_methods[] = {
  { (GCallback) tp_svc_channel_interface_dtmf_start_tone, _tp_marshal_VOID__UINT_UCHAR_POINTER, 0 },
  { (GCallback) tp_svc_channel_interface_dtmf_stop_tone, g_cclosure_marshal_VOID__UINT_POINTER, 86 },
};

static const DBusGObjectInfo _tp_svc_channel_interface_dtmf_object_info = {
  0,
  _tp_svc_channel_interface_dtmf_methods,
  2,
"org.freedesktop.Telepathy.Channel.Interface.DTMF\0StartTone\0A\0Stream_ID\0I\0u\0Event\0I\0y\0\0org.freedesktop.Telepathy.Channel.Interface.DTMF\0StopTone\0A\0Stream_ID\0I\0u\0\0\0",
"\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_interface_destroyable_object_info;

struct _TpSvcChannelInterfaceDestroyableClass {
    GTypeInterface parent_class;
    tp_svc_channel_interface_destroyable_destroy_impl destroy;
};

static void tp_svc_channel_interface_destroyable_base_init (gpointer klass);

GType
tp_svc_channel_interface_destroyable_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelInterfaceDestroyableClass),
        tp_svc_channel_interface_destroyable_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelInterfaceDestroyable", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_interface_destroyable_destroy_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Destroy on interface org.freedesktop.Telepathy.Channel.Interface.Destroyable.
 */
static void
tp_svc_channel_interface_destroyable_destroy (TpSvcChannelInterfaceDestroyable *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_destroyable_destroy_impl impl = (TP_SVC_CHANNEL_INTERFACE_DESTROYABLE_GET_CLASS (self)->destroy);

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
 * tp_svc_channel_interface_destroyable_implement_destroy:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Destroy D-Bus method
 *
 * Register an implementation for the Destroy method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_destroyable_implement_destroy (TpSvcChannelInterfaceDestroyableClass *klass, tp_svc_channel_interface_destroyable_destroy_impl impl)
{
  klass->destroy = impl;
}

static inline void
tp_svc_channel_interface_destroyable_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_channel_interface_destroyable_get_type (),
      &_tp_svc_channel_interface_destroyable_object_info);

}
static void
tp_svc_channel_interface_destroyable_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_interface_destroyable_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_interface_destroyable_methods[] = {
  { (GCallback) tp_svc_channel_interface_destroyable_destroy, g_cclosure_marshal_VOID__POINTER, 0 },
};

static const DBusGObjectInfo _tp_svc_channel_interface_destroyable_object_info = {
  0,
  _tp_svc_channel_interface_destroyable_methods,
  1,
"org.freedesktop.Telepathy.Channel.Interface.Destroyable\0Destroy\0A\0\0\0",
"\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_interface_group_object_info;

struct _TpSvcChannelInterfaceGroupClass {
    GTypeInterface parent_class;
    tp_svc_channel_interface_group_add_members_impl add_members;
    tp_svc_channel_interface_group_get_all_members_impl get_all_members;
    tp_svc_channel_interface_group_get_group_flags_impl get_group_flags;
    tp_svc_channel_interface_group_get_handle_owners_impl get_handle_owners;
    tp_svc_channel_interface_group_get_local_pending_members_impl get_local_pending_members;
    tp_svc_channel_interface_group_get_local_pending_members_with_info_impl get_local_pending_members_with_info;
    tp_svc_channel_interface_group_get_members_impl get_members;
    tp_svc_channel_interface_group_get_remote_pending_members_impl get_remote_pending_members;
    tp_svc_channel_interface_group_get_self_handle_impl get_self_handle;
    tp_svc_channel_interface_group_remove_members_impl remove_members;
    tp_svc_channel_interface_group_remove_members_with_reason_impl remove_members_with_reason;
};

enum {
    SIGNAL_CHANNEL_INTERFACE_GROUP_HandleOwnersChanged,
    SIGNAL_CHANNEL_INTERFACE_GROUP_SelfHandleChanged,
    SIGNAL_CHANNEL_INTERFACE_GROUP_GroupFlagsChanged,
    SIGNAL_CHANNEL_INTERFACE_GROUP_MembersChanged,
    SIGNAL_CHANNEL_INTERFACE_GROUP_MembersChangedDetailed,
    N_CHANNEL_INTERFACE_GROUP_SIGNALS
};
static guint channel_interface_group_signals[N_CHANNEL_INTERFACE_GROUP_SIGNALS] = {0};

static void tp_svc_channel_interface_group_base_init (gpointer klass);

GType
tp_svc_channel_interface_group_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelInterfaceGroupClass),
        tp_svc_channel_interface_group_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelInterfaceGroup", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_interface_group_add_members_impl:
 * @self: The object implementing this interface
 * @in_Contacts: const GArray * (FIXME, generate documentation)
 * @in_Message: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * AddMembers on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
static void
tp_svc_channel_interface_group_add_members (TpSvcChannelInterfaceGroup *self,
    const GArray *in_Contacts,
    const gchar *in_Message,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_group_add_members_impl impl = (TP_SVC_CHANNEL_INTERFACE_GROUP_GET_CLASS (self)->add_members);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contacts,
        in_Message,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_interface_group_implement_add_members:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the AddMembers D-Bus method
 *
 * Register an implementation for the AddMembers method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_group_implement_add_members (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_add_members_impl impl)
{
  klass->add_members = impl;
}

/**
 * tp_svc_channel_interface_group_get_all_members_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetAllMembers on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
static void
tp_svc_channel_interface_group_get_all_members (TpSvcChannelInterfaceGroup *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_group_get_all_members_impl impl = (TP_SVC_CHANNEL_INTERFACE_GROUP_GET_CLASS (self)->get_all_members);

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
 * tp_svc_channel_interface_group_implement_get_all_members:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetAllMembers D-Bus method
 *
 * Register an implementation for the GetAllMembers method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_group_implement_get_all_members (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_all_members_impl impl)
{
  klass->get_all_members = impl;
}

/**
 * tp_svc_channel_interface_group_get_group_flags_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetGroupFlags on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
static void
tp_svc_channel_interface_group_get_group_flags (TpSvcChannelInterfaceGroup *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_group_get_group_flags_impl impl = (TP_SVC_CHANNEL_INTERFACE_GROUP_GET_CLASS (self)->get_group_flags);

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
 * tp_svc_channel_interface_group_implement_get_group_flags:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetGroupFlags D-Bus method
 *
 * Register an implementation for the GetGroupFlags method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_group_implement_get_group_flags (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_group_flags_impl impl)
{
  klass->get_group_flags = impl;
}

/**
 * tp_svc_channel_interface_group_get_handle_owners_impl:
 * @self: The object implementing this interface
 * @in_Handles: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetHandleOwners on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
static void
tp_svc_channel_interface_group_get_handle_owners (TpSvcChannelInterfaceGroup *self,
    const GArray *in_Handles,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_group_get_handle_owners_impl impl = (TP_SVC_CHANNEL_INTERFACE_GROUP_GET_CLASS (self)->get_handle_owners);

  if (impl != NULL)
    {
      (impl) (self,
        in_Handles,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_interface_group_implement_get_handle_owners:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetHandleOwners D-Bus method
 *
 * Register an implementation for the GetHandleOwners method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_group_implement_get_handle_owners (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_handle_owners_impl impl)
{
  klass->get_handle_owners = impl;
}

/**
 * tp_svc_channel_interface_group_get_local_pending_members_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetLocalPendingMembers on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
static void
tp_svc_channel_interface_group_get_local_pending_members (TpSvcChannelInterfaceGroup *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_group_get_local_pending_members_impl impl = (TP_SVC_CHANNEL_INTERFACE_GROUP_GET_CLASS (self)->get_local_pending_members);

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
 * tp_svc_channel_interface_group_implement_get_local_pending_members:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetLocalPendingMembers D-Bus method
 *
 * Register an implementation for the GetLocalPendingMembers method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_group_implement_get_local_pending_members (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_local_pending_members_impl impl)
{
  klass->get_local_pending_members = impl;
}

/**
 * tp_svc_channel_interface_group_get_local_pending_members_with_info_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetLocalPendingMembersWithInfo on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
static void
tp_svc_channel_interface_group_get_local_pending_members_with_info (TpSvcChannelInterfaceGroup *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_group_get_local_pending_members_with_info_impl impl = (TP_SVC_CHANNEL_INTERFACE_GROUP_GET_CLASS (self)->get_local_pending_members_with_info);

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
 * tp_svc_channel_interface_group_implement_get_local_pending_members_with_info:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetLocalPendingMembersWithInfo D-Bus method
 *
 * Register an implementation for the GetLocalPendingMembersWithInfo method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_group_implement_get_local_pending_members_with_info (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_local_pending_members_with_info_impl impl)
{
  klass->get_local_pending_members_with_info = impl;
}

/**
 * tp_svc_channel_interface_group_get_members_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetMembers on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
static void
tp_svc_channel_interface_group_get_members (TpSvcChannelInterfaceGroup *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_group_get_members_impl impl = (TP_SVC_CHANNEL_INTERFACE_GROUP_GET_CLASS (self)->get_members);

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
 * tp_svc_channel_interface_group_implement_get_members:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetMembers D-Bus method
 *
 * Register an implementation for the GetMembers method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_group_implement_get_members (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_members_impl impl)
{
  klass->get_members = impl;
}

/**
 * tp_svc_channel_interface_group_get_remote_pending_members_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetRemotePendingMembers on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
static void
tp_svc_channel_interface_group_get_remote_pending_members (TpSvcChannelInterfaceGroup *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_group_get_remote_pending_members_impl impl = (TP_SVC_CHANNEL_INTERFACE_GROUP_GET_CLASS (self)->get_remote_pending_members);

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
 * tp_svc_channel_interface_group_implement_get_remote_pending_members:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetRemotePendingMembers D-Bus method
 *
 * Register an implementation for the GetRemotePendingMembers method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_group_implement_get_remote_pending_members (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_remote_pending_members_impl impl)
{
  klass->get_remote_pending_members = impl;
}

/**
 * tp_svc_channel_interface_group_get_self_handle_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetSelfHandle on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
static void
tp_svc_channel_interface_group_get_self_handle (TpSvcChannelInterfaceGroup *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_group_get_self_handle_impl impl = (TP_SVC_CHANNEL_INTERFACE_GROUP_GET_CLASS (self)->get_self_handle);

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
 * tp_svc_channel_interface_group_implement_get_self_handle:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetSelfHandle D-Bus method
 *
 * Register an implementation for the GetSelfHandle method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_group_implement_get_self_handle (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_get_self_handle_impl impl)
{
  klass->get_self_handle = impl;
}

/**
 * tp_svc_channel_interface_group_remove_members_impl:
 * @self: The object implementing this interface
 * @in_Contacts: const GArray * (FIXME, generate documentation)
 * @in_Message: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RemoveMembers on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
static void
tp_svc_channel_interface_group_remove_members (TpSvcChannelInterfaceGroup *self,
    const GArray *in_Contacts,
    const gchar *in_Message,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_group_remove_members_impl impl = (TP_SVC_CHANNEL_INTERFACE_GROUP_GET_CLASS (self)->remove_members);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contacts,
        in_Message,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_interface_group_implement_remove_members:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RemoveMembers D-Bus method
 *
 * Register an implementation for the RemoveMembers method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_group_implement_remove_members (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_remove_members_impl impl)
{
  klass->remove_members = impl;
}

/**
 * tp_svc_channel_interface_group_remove_members_with_reason_impl:
 * @self: The object implementing this interface
 * @in_Contacts: const GArray * (FIXME, generate documentation)
 * @in_Message: const gchar * (FIXME, generate documentation)
 * @in_Reason: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RemoveMembersWithReason on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
static void
tp_svc_channel_interface_group_remove_members_with_reason (TpSvcChannelInterfaceGroup *self,
    const GArray *in_Contacts,
    const gchar *in_Message,
    guint in_Reason,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_group_remove_members_with_reason_impl impl = (TP_SVC_CHANNEL_INTERFACE_GROUP_GET_CLASS (self)->remove_members_with_reason);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contacts,
        in_Message,
        in_Reason,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_interface_group_implement_remove_members_with_reason:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RemoveMembersWithReason D-Bus method
 *
 * Register an implementation for the RemoveMembersWithReason method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_group_implement_remove_members_with_reason (TpSvcChannelInterfaceGroupClass *klass, tp_svc_channel_interface_group_remove_members_with_reason_impl impl)
{
  klass->remove_members_with_reason = impl;
}

/**
 * tp_svc_channel_interface_group_emit_handle_owners_changed:
 * @instance: The object implementing this interface
 * @arg_Added: GHashTable * (FIXME, generate documentation)
 * @arg_Removed: const GArray * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * HandleOwnersChanged signal on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
void
tp_svc_channel_interface_group_emit_handle_owners_changed (gpointer instance,
    GHashTable *arg_Added,
    const GArray *arg_Removed)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_INTERFACE_GROUP));
  g_signal_emit (instance,
      channel_interface_group_signals[SIGNAL_CHANNEL_INTERFACE_GROUP_HandleOwnersChanged],
      0,
      arg_Added,
      arg_Removed);
}

/**
 * tp_svc_channel_interface_group_emit_self_handle_changed:
 * @instance: The object implementing this interface
 * @arg_Self_Handle: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * SelfHandleChanged signal on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
void
tp_svc_channel_interface_group_emit_self_handle_changed (gpointer instance,
    guint arg_Self_Handle)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_INTERFACE_GROUP));
  g_signal_emit (instance,
      channel_interface_group_signals[SIGNAL_CHANNEL_INTERFACE_GROUP_SelfHandleChanged],
      0,
      arg_Self_Handle);
}

/**
 * tp_svc_channel_interface_group_emit_group_flags_changed:
 * @instance: The object implementing this interface
 * @arg_Added: guint  (FIXME, generate documentation)
 * @arg_Removed: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * GroupFlagsChanged signal on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
void
tp_svc_channel_interface_group_emit_group_flags_changed (gpointer instance,
    guint arg_Added,
    guint arg_Removed)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_INTERFACE_GROUP));
  g_signal_emit (instance,
      channel_interface_group_signals[SIGNAL_CHANNEL_INTERFACE_GROUP_GroupFlagsChanged],
      0,
      arg_Added,
      arg_Removed);
}

/**
 * tp_svc_channel_interface_group_emit_members_changed:
 * @instance: The object implementing this interface
 * @arg_Message: const gchar * (FIXME, generate documentation)
 * @arg_Added: const GArray * (FIXME, generate documentation)
 * @arg_Removed: const GArray * (FIXME, generate documentation)
 * @arg_Local_Pending: const GArray * (FIXME, generate documentation)
 * @arg_Remote_Pending: const GArray * (FIXME, generate documentation)
 * @arg_Actor: guint  (FIXME, generate documentation)
 * @arg_Reason: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * MembersChanged signal on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
void
tp_svc_channel_interface_group_emit_members_changed (gpointer instance,
    const gchar *arg_Message,
    const GArray *arg_Added,
    const GArray *arg_Removed,
    const GArray *arg_Local_Pending,
    const GArray *arg_Remote_Pending,
    guint arg_Actor,
    guint arg_Reason)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_INTERFACE_GROUP));
  g_signal_emit (instance,
      channel_interface_group_signals[SIGNAL_CHANNEL_INTERFACE_GROUP_MembersChanged],
      0,
      arg_Message,
      arg_Added,
      arg_Removed,
      arg_Local_Pending,
      arg_Remote_Pending,
      arg_Actor,
      arg_Reason);
}

/**
 * tp_svc_channel_interface_group_emit_members_changed_detailed:
 * @instance: The object implementing this interface
 * @arg_Added: const GArray * (FIXME, generate documentation)
 * @arg_Removed: const GArray * (FIXME, generate documentation)
 * @arg_Local_Pending: const GArray * (FIXME, generate documentation)
 * @arg_Remote_Pending: const GArray * (FIXME, generate documentation)
 * @arg_Details: GHashTable * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * MembersChangedDetailed signal on interface org.freedesktop.Telepathy.Channel.Interface.Group.
 */
void
tp_svc_channel_interface_group_emit_members_changed_detailed (gpointer instance,
    const GArray *arg_Added,
    const GArray *arg_Removed,
    const GArray *arg_Local_Pending,
    const GArray *arg_Remote_Pending,
    GHashTable *arg_Details)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_INTERFACE_GROUP));
  g_signal_emit (instance,
      channel_interface_group_signals[SIGNAL_CHANNEL_INTERFACE_GROUP_MembersChangedDetailed],
      0,
      arg_Added,
      arg_Removed,
      arg_Local_Pending,
      arg_Remote_Pending,
      arg_Details);
}

static inline void
tp_svc_channel_interface_group_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[7] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* GroupFlags */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "a{uu}", 0, NULL, NULL }, /* HandleOwners */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "a(uuus)", 0, NULL, NULL }, /* LocalPendingMembers */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "au", 0, NULL, NULL }, /* Members */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "au", 0, NULL, NULL }, /* RemotePendingMembers */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* SelfHandle */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_channel_interface_group_get_type (),
      &_tp_svc_channel_interface_group_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Interface.Group");
  properties[0].name = g_quark_from_static_string ("GroupFlags");
  properties[0].type = G_TYPE_UINT;
  properties[1].name = g_quark_from_static_string ("HandleOwners");
  properties[1].type = (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_UINT));
  properties[2].name = g_quark_from_static_string ("LocalPendingMembers");
  properties[2].type = (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID))));
  properties[3].name = g_quark_from_static_string ("Members");
  properties[3].type = DBUS_TYPE_G_UINT_ARRAY;
  properties[4].name = g_quark_from_static_string ("RemotePendingMembers");
  properties[4].type = DBUS_TYPE_G_UINT_ARRAY;
  properties[5].name = g_quark_from_static_string ("SelfHandle");
  properties[5].type = G_TYPE_UINT;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CHANNEL_INTERFACE_GROUP, &interface);

  /**
   * TpSvcChannelInterfaceGroup::handle-owners-changed:
   * @arg_Added: GHashTable * (FIXME, generate documentation)
   * @arg_Removed: const GArray * (FIXME, generate documentation)
   *
   * The HandleOwnersChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_interface_group_signals[SIGNAL_CHANNEL_INTERFACE_GROUP_HandleOwnersChanged] =
  g_signal_new ("handle-owners-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__BOXED_BOXED,
      G_TYPE_NONE,
      2,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_UINT)),
      DBUS_TYPE_G_UINT_ARRAY);

  /**
   * TpSvcChannelInterfaceGroup::self-handle-changed:
   * @arg_Self_Handle: guint  (FIXME, generate documentation)
   *
   * The SelfHandleChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_interface_group_signals[SIGNAL_CHANNEL_INTERFACE_GROUP_SelfHandleChanged] =
  g_signal_new ("self-handle-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__UINT,
      G_TYPE_NONE,
      1,
      G_TYPE_UINT);

  /**
   * TpSvcChannelInterfaceGroup::group-flags-changed:
   * @arg_Added: guint  (FIXME, generate documentation)
   * @arg_Removed: guint  (FIXME, generate documentation)
   *
   * The GroupFlagsChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_interface_group_signals[SIGNAL_CHANNEL_INTERFACE_GROUP_GroupFlagsChanged] =
  g_signal_new ("group-flags-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT,
      G_TYPE_NONE,
      2,
      G_TYPE_UINT,
      G_TYPE_UINT);

  /**
   * TpSvcChannelInterfaceGroup::members-changed:
   * @arg_Message: const gchar * (FIXME, generate documentation)
   * @arg_Added: const GArray * (FIXME, generate documentation)
   * @arg_Removed: const GArray * (FIXME, generate documentation)
   * @arg_Local_Pending: const GArray * (FIXME, generate documentation)
   * @arg_Remote_Pending: const GArray * (FIXME, generate documentation)
   * @arg_Actor: guint  (FIXME, generate documentation)
   * @arg_Reason: guint  (FIXME, generate documentation)
   *
   * The MembersChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_interface_group_signals[SIGNAL_CHANNEL_INTERFACE_GROUP_MembersChanged] =
  g_signal_new ("members-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__STRING_BOXED_BOXED_BOXED_BOXED_UINT_UINT,
      G_TYPE_NONE,
      7,
      G_TYPE_STRING,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      G_TYPE_UINT,
      G_TYPE_UINT);

  /**
   * TpSvcChannelInterfaceGroup::members-changed-detailed:
   * @arg_Added: const GArray * (FIXME, generate documentation)
   * @arg_Removed: const GArray * (FIXME, generate documentation)
   * @arg_Local_Pending: const GArray * (FIXME, generate documentation)
   * @arg_Remote_Pending: const GArray * (FIXME, generate documentation)
   * @arg_Details: GHashTable * (FIXME, generate documentation)
   *
   * The MembersChangedDetailed D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_interface_group_signals[SIGNAL_CHANNEL_INTERFACE_GROUP_MembersChangedDetailed] =
  g_signal_new ("members-changed-detailed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__BOXED_BOXED_BOXED_BOXED_BOXED,
      G_TYPE_NONE,
      5,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)));

}
static void
tp_svc_channel_interface_group_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_interface_group_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_interface_group_methods[] = {
  { (GCallback) tp_svc_channel_interface_group_add_members, _tp_marshal_VOID__BOXED_STRING_POINTER, 0 },
  { (GCallback) tp_svc_channel_interface_group_get_all_members, g_cclosure_marshal_VOID__POINTER, 90 },
  { (GCallback) tp_svc_channel_interface_group_get_group_flags, g_cclosure_marshal_VOID__POINTER, 221 },
  { (GCallback) tp_svc_channel_interface_group_get_handle_owners, _tp_marshal_VOID__BOXED_POINTER, 308 },
  { (GCallback) tp_svc_channel_interface_group_get_local_pending_members, g_cclosure_marshal_VOID__POINTER, 406 },
  { (GCallback) tp_svc_channel_interface_group_get_local_pending_members_with_info, g_cclosure_marshal_VOID__POINTER, 499 },
  { (GCallback) tp_svc_channel_interface_group_get_members, g_cclosure_marshal_VOID__POINTER, 602 },
  { (GCallback) tp_svc_channel_interface_group_get_remote_pending_members, g_cclosure_marshal_VOID__POINTER, 683 },
  { (GCallback) tp_svc_channel_interface_group_get_self_handle, g_cclosure_marshal_VOID__POINTER, 777 },
  { (GCallback) tp_svc_channel_interface_group_remove_members, _tp_marshal_VOID__BOXED_STRING_POINTER, 864 },
  { (GCallback) tp_svc_channel_interface_group_remove_members_with_reason, _tp_marshal_VOID__BOXED_STRING_UINT_POINTER, 957 },
};

static const DBusGObjectInfo _tp_svc_channel_interface_group_object_info = {
  0,
  _tp_svc_channel_interface_group_methods,
  11,
"org.freedesktop.Telepathy.Channel.Interface.Group\0AddMembers\0A\0Contacts\0I\0au\0Message\0I\0s\0\0org.freedesktop.Telepathy.Channel.Interface.Group\0GetAllMembers\0A\0Members\0O\0F\0N\0au\0Local_Pending\0O\0F\0N\0au\0Remote_Pending\0O\0F\0N\0au\0\0org.freedesktop.Telepathy.Channel.Interface.Group\0GetGroupFlags\0A\0Group_Flags\0O\0F\0N\0u\0\0org.freedesktop.Telepathy.Channel.Interface.Group\0GetHandleOwners\0A\0Handles\0I\0au\0Owners\0O\0F\0N\0au\0\0org.freedesktop.Telepathy.Channel.Interface.Group\0GetLocalPendingMembers\0A\0Handles\0O\0F\0N\0au\0\0org.freedesktop.Telepathy.Channel.Interface.Group\0GetLocalPendingMembersWithInfo\0A\0Info\0O\0F\0N\0a(uuus)\0\0org.freedesktop.Telepathy.Channel.Interface.Group\0GetMembers\0A\0Handles\0O\0F\0N\0au\0\0org.freedesktop.Telepathy.Channel.Interface.Group\0GetRemotePendingMembers\0A\0Handles\0O\0F\0N\0au\0\0org.freedesktop.Telepathy.Channel.Interface.Group\0GetSelfHandle\0A\0Self_Handle\0O\0F\0N\0u\0\0org.freedesktop.Telepathy.Channel.Interface.Group\0RemoveMembers\0A\0Contacts\0I\0au\0Message\0I\0s\0\0org.freedesktop.Telepathy.Channel.Interface.Group\0RemoveMembersWithReason\0A\0Contacts\0I\0au\0Message\0I\0s\0Reason\0I\0u\0\0\0",
"org.freedesktop.Telepathy.Channel.Interface.Group\0HandleOwnersChanged\0org.freedesktop.Telepathy.Channel.Interface.Group\0SelfHandleChanged\0org.freedesktop.Telepathy.Channel.Interface.Group\0GroupFlagsChanged\0org.freedesktop.Telepathy.Channel.Interface.Group\0MembersChanged\0org.freedesktop.Telepathy.Channel.Interface.Group\0MembersChangedDetailed\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_interface_hold_object_info;

struct _TpSvcChannelInterfaceHoldClass {
    GTypeInterface parent_class;
    tp_svc_channel_interface_hold_get_hold_state_impl get_hold_state;
    tp_svc_channel_interface_hold_request_hold_impl request_hold;
};

enum {
    SIGNAL_CHANNEL_INTERFACE_HOLD_HoldStateChanged,
    N_CHANNEL_INTERFACE_HOLD_SIGNALS
};
static guint channel_interface_hold_signals[N_CHANNEL_INTERFACE_HOLD_SIGNALS] = {0};

static void tp_svc_channel_interface_hold_base_init (gpointer klass);

GType
tp_svc_channel_interface_hold_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelInterfaceHoldClass),
        tp_svc_channel_interface_hold_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelInterfaceHold", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_interface_hold_get_hold_state_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetHoldState on interface org.freedesktop.Telepathy.Channel.Interface.Hold.
 */
static void
tp_svc_channel_interface_hold_get_hold_state (TpSvcChannelInterfaceHold *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_hold_get_hold_state_impl impl = (TP_SVC_CHANNEL_INTERFACE_HOLD_GET_CLASS (self)->get_hold_state);

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
 * tp_svc_channel_interface_hold_implement_get_hold_state:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetHoldState D-Bus method
 *
 * Register an implementation for the GetHoldState method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_hold_implement_get_hold_state (TpSvcChannelInterfaceHoldClass *klass, tp_svc_channel_interface_hold_get_hold_state_impl impl)
{
  klass->get_hold_state = impl;
}

/**
 * tp_svc_channel_interface_hold_request_hold_impl:
 * @self: The object implementing this interface
 * @in_Hold: gboolean  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RequestHold on interface org.freedesktop.Telepathy.Channel.Interface.Hold.
 */
static void
tp_svc_channel_interface_hold_request_hold (TpSvcChannelInterfaceHold *self,
    gboolean in_Hold,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_hold_request_hold_impl impl = (TP_SVC_CHANNEL_INTERFACE_HOLD_GET_CLASS (self)->request_hold);

  if (impl != NULL)
    {
      (impl) (self,
        in_Hold,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_interface_hold_implement_request_hold:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RequestHold D-Bus method
 *
 * Register an implementation for the RequestHold method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_hold_implement_request_hold (TpSvcChannelInterfaceHoldClass *klass, tp_svc_channel_interface_hold_request_hold_impl impl)
{
  klass->request_hold = impl;
}

/**
 * tp_svc_channel_interface_hold_emit_hold_state_changed:
 * @instance: The object implementing this interface
 * @arg_HoldState: guint  (FIXME, generate documentation)
 * @arg_Reason: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * HoldStateChanged signal on interface org.freedesktop.Telepathy.Channel.Interface.Hold.
 */
void
tp_svc_channel_interface_hold_emit_hold_state_changed (gpointer instance,
    guint arg_HoldState,
    guint arg_Reason)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_INTERFACE_HOLD));
  g_signal_emit (instance,
      channel_interface_hold_signals[SIGNAL_CHANNEL_INTERFACE_HOLD_HoldStateChanged],
      0,
      arg_HoldState,
      arg_Reason);
}

static inline void
tp_svc_channel_interface_hold_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_channel_interface_hold_get_type (),
      &_tp_svc_channel_interface_hold_object_info);

  /**
   * TpSvcChannelInterfaceHold::hold-state-changed:
   * @arg_HoldState: guint  (FIXME, generate documentation)
   * @arg_Reason: guint  (FIXME, generate documentation)
   *
   * The HoldStateChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_interface_hold_signals[SIGNAL_CHANNEL_INTERFACE_HOLD_HoldStateChanged] =
  g_signal_new ("hold-state-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT,
      G_TYPE_NONE,
      2,
      G_TYPE_UINT,
      G_TYPE_UINT);

}
static void
tp_svc_channel_interface_hold_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_interface_hold_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_interface_hold_methods[] = {
  { (GCallback) tp_svc_channel_interface_hold_get_hold_state, g_cclosure_marshal_VOID__POINTER, 0 },
  { (GCallback) tp_svc_channel_interface_hold_request_hold, _tp_marshal_VOID__BOOLEAN_POINTER, 98 },
};

static const DBusGObjectInfo _tp_svc_channel_interface_hold_object_info = {
  0,
  _tp_svc_channel_interface_hold_methods,
  2,
"org.freedesktop.Telepathy.Channel.Interface.Hold\0GetHoldState\0A\0HoldState\0O\0F\0N\0u\0Reason\0O\0F\0N\0u\0\0org.freedesktop.Telepathy.Channel.Interface.Hold\0RequestHold\0A\0Hold\0I\0b\0\0\0",
"org.freedesktop.Telepathy.Channel.Interface.Hold\0HoldStateChanged\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_interface_media_signalling_object_info;

struct _TpSvcChannelInterfaceMediaSignallingClass {
    GTypeInterface parent_class;
    tp_svc_channel_interface_media_signalling_get_session_handlers_impl get_session_handlers;
};

enum {
    SIGNAL_CHANNEL_INTERFACE_MEDIA_SIGNALLING_NewSessionHandler,
    N_CHANNEL_INTERFACE_MEDIA_SIGNALLING_SIGNALS
};
static guint channel_interface_media_signalling_signals[N_CHANNEL_INTERFACE_MEDIA_SIGNALLING_SIGNALS] = {0};

static void tp_svc_channel_interface_media_signalling_base_init (gpointer klass);

GType
tp_svc_channel_interface_media_signalling_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelInterfaceMediaSignallingClass),
        tp_svc_channel_interface_media_signalling_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelInterfaceMediaSignalling", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_interface_media_signalling_get_session_handlers_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetSessionHandlers on interface org.freedesktop.Telepathy.Channel.Interface.MediaSignalling.
 */
static void
tp_svc_channel_interface_media_signalling_get_session_handlers (TpSvcChannelInterfaceMediaSignalling *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_media_signalling_get_session_handlers_impl impl = (TP_SVC_CHANNEL_INTERFACE_MEDIA_SIGNALLING_GET_CLASS (self)->get_session_handlers);

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
 * tp_svc_channel_interface_media_signalling_implement_get_session_handlers:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetSessionHandlers D-Bus method
 *
 * Register an implementation for the GetSessionHandlers method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_media_signalling_implement_get_session_handlers (TpSvcChannelInterfaceMediaSignallingClass *klass, tp_svc_channel_interface_media_signalling_get_session_handlers_impl impl)
{
  klass->get_session_handlers = impl;
}

/**
 * tp_svc_channel_interface_media_signalling_emit_new_session_handler:
 * @instance: The object implementing this interface
 * @arg_Session_Handler: const gchar * (FIXME, generate documentation)
 * @arg_Session_Type: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * NewSessionHandler signal on interface org.freedesktop.Telepathy.Channel.Interface.MediaSignalling.
 */
void
tp_svc_channel_interface_media_signalling_emit_new_session_handler (gpointer instance,
    const gchar *arg_Session_Handler,
    const gchar *arg_Session_Type)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_INTERFACE_MEDIA_SIGNALLING));
  g_signal_emit (instance,
      channel_interface_media_signalling_signals[SIGNAL_CHANNEL_INTERFACE_MEDIA_SIGNALLING_NewSessionHandler],
      0,
      arg_Session_Handler,
      arg_Session_Type);
}

static inline void
tp_svc_channel_interface_media_signalling_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_channel_interface_media_signalling_get_type (),
      &_tp_svc_channel_interface_media_signalling_object_info);

  /**
   * TpSvcChannelInterfaceMediaSignalling::new-session-handler:
   * @arg_Session_Handler: const gchar * (FIXME, generate documentation)
   * @arg_Session_Type: const gchar * (FIXME, generate documentation)
   *
   * The NewSessionHandler D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_interface_media_signalling_signals[SIGNAL_CHANNEL_INTERFACE_MEDIA_SIGNALLING_NewSessionHandler] =
  g_signal_new ("new-session-handler",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__BOXED_STRING,
      G_TYPE_NONE,
      2,
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_STRING);

}
static void
tp_svc_channel_interface_media_signalling_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_interface_media_signalling_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_interface_media_signalling_methods[] = {
  { (GCallback) tp_svc_channel_interface_media_signalling_get_session_handlers, g_cclosure_marshal_VOID__POINTER, 0 },
};

static const DBusGObjectInfo _tp_svc_channel_interface_media_signalling_object_info = {
  0,
  _tp_svc_channel_interface_media_signalling_methods,
  1,
"org.freedesktop.Telepathy.Channel.Interface.MediaSignalling\0GetSessionHandlers\0A\0Session_Handlers\0O\0F\0N\0a(os)\0\0\0",
"org.freedesktop.Telepathy.Channel.Interface.MediaSignalling\0NewSessionHandler\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_interface_messages_object_info;

struct _TpSvcChannelInterfaceMessagesClass {
    GTypeInterface parent_class;
    tp_svc_channel_interface_messages_send_message_impl send_message;
    tp_svc_channel_interface_messages_get_pending_message_content_impl get_pending_message_content;
};

enum {
    SIGNAL_CHANNEL_INTERFACE_MESSAGES_MessageSent,
    SIGNAL_CHANNEL_INTERFACE_MESSAGES_PendingMessagesRemoved,
    SIGNAL_CHANNEL_INTERFACE_MESSAGES_MessageReceived,
    N_CHANNEL_INTERFACE_MESSAGES_SIGNALS
};
static guint channel_interface_messages_signals[N_CHANNEL_INTERFACE_MESSAGES_SIGNALS] = {0};

static void tp_svc_channel_interface_messages_base_init (gpointer klass);

GType
tp_svc_channel_interface_messages_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelInterfaceMessagesClass),
        tp_svc_channel_interface_messages_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelInterfaceMessages", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_interface_messages_send_message_impl:
 * @self: The object implementing this interface
 * @in_Message: const GPtrArray * (FIXME, generate documentation)
 * @in_Flags: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * SendMessage on interface org.freedesktop.Telepathy.Channel.Interface.Messages.
 */
static void
tp_svc_channel_interface_messages_send_message (TpSvcChannelInterfaceMessages *self,
    const GPtrArray *in_Message,
    guint in_Flags,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_messages_send_message_impl impl = (TP_SVC_CHANNEL_INTERFACE_MESSAGES_GET_CLASS (self)->send_message);

  if (impl != NULL)
    {
      (impl) (self,
        in_Message,
        in_Flags,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_interface_messages_implement_send_message:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the SendMessage D-Bus method
 *
 * Register an implementation for the SendMessage method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_messages_implement_send_message (TpSvcChannelInterfaceMessagesClass *klass, tp_svc_channel_interface_messages_send_message_impl impl)
{
  klass->send_message = impl;
}

/**
 * tp_svc_channel_interface_messages_get_pending_message_content_impl:
 * @self: The object implementing this interface
 * @in_Message_ID: guint  (FIXME, generate documentation)
 * @in_Parts: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetPendingMessageContent on interface org.freedesktop.Telepathy.Channel.Interface.Messages.
 */
static void
tp_svc_channel_interface_messages_get_pending_message_content (TpSvcChannelInterfaceMessages *self,
    guint in_Message_ID,
    const GArray *in_Parts,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_messages_get_pending_message_content_impl impl = (TP_SVC_CHANNEL_INTERFACE_MESSAGES_GET_CLASS (self)->get_pending_message_content);

  if (impl != NULL)
    {
      (impl) (self,
        in_Message_ID,
        in_Parts,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_interface_messages_implement_get_pending_message_content:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetPendingMessageContent D-Bus method
 *
 * Register an implementation for the GetPendingMessageContent method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_messages_implement_get_pending_message_content (TpSvcChannelInterfaceMessagesClass *klass, tp_svc_channel_interface_messages_get_pending_message_content_impl impl)
{
  klass->get_pending_message_content = impl;
}

/**
 * tp_svc_channel_interface_messages_emit_message_sent:
 * @instance: The object implementing this interface
 * @arg_Content: const GPtrArray * (FIXME, generate documentation)
 * @arg_Flags: guint  (FIXME, generate documentation)
 * @arg_Message_Token: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * MessageSent signal on interface org.freedesktop.Telepathy.Channel.Interface.Messages.
 */
void
tp_svc_channel_interface_messages_emit_message_sent (gpointer instance,
    const GPtrArray *arg_Content,
    guint arg_Flags,
    const gchar *arg_Message_Token)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_INTERFACE_MESSAGES));
  g_signal_emit (instance,
      channel_interface_messages_signals[SIGNAL_CHANNEL_INTERFACE_MESSAGES_MessageSent],
      0,
      arg_Content,
      arg_Flags,
      arg_Message_Token);
}

/**
 * tp_svc_channel_interface_messages_emit_pending_messages_removed:
 * @instance: The object implementing this interface
 * @arg_Message_IDs: const GArray * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * PendingMessagesRemoved signal on interface org.freedesktop.Telepathy.Channel.Interface.Messages.
 */
void
tp_svc_channel_interface_messages_emit_pending_messages_removed (gpointer instance,
    const GArray *arg_Message_IDs)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_INTERFACE_MESSAGES));
  g_signal_emit (instance,
      channel_interface_messages_signals[SIGNAL_CHANNEL_INTERFACE_MESSAGES_PendingMessagesRemoved],
      0,
      arg_Message_IDs);
}

/**
 * tp_svc_channel_interface_messages_emit_message_received:
 * @instance: The object implementing this interface
 * @arg_Message: const GPtrArray * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * MessageReceived signal on interface org.freedesktop.Telepathy.Channel.Interface.Messages.
 */
void
tp_svc_channel_interface_messages_emit_message_received (gpointer instance,
    const GPtrArray *arg_Message)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_INTERFACE_MESSAGES));
  g_signal_emit (instance,
      channel_interface_messages_signals[SIGNAL_CHANNEL_INTERFACE_MESSAGES_MessageReceived],
      0,
      arg_Message);
}

static inline void
tp_svc_channel_interface_messages_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[5] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "as", 0, NULL, NULL }, /* SupportedContentTypes */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* MessagePartSupportFlags */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "aaa{sv}", 0, NULL, NULL }, /* PendingMessages */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* DeliveryReportingSupport */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_channel_interface_messages_get_type (),
      &_tp_svc_channel_interface_messages_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Interface.Messages");
  properties[0].name = g_quark_from_static_string ("SupportedContentTypes");
  properties[0].type = G_TYPE_STRV;
  properties[1].name = g_quark_from_static_string ("MessagePartSupportFlags");
  properties[1].type = G_TYPE_UINT;
  properties[2].name = g_quark_from_static_string ("PendingMessages");
  properties[2].type = (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE))))));
  properties[3].name = g_quark_from_static_string ("DeliveryReportingSupport");
  properties[3].type = G_TYPE_UINT;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CHANNEL_INTERFACE_MESSAGES, &interface);

  /**
   * TpSvcChannelInterfaceMessages::message-sent:
   * @arg_Content: const GPtrArray * (FIXME, generate documentation)
   * @arg_Flags: guint  (FIXME, generate documentation)
   * @arg_Message_Token: const gchar * (FIXME, generate documentation)
   *
   * The MessageSent D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_interface_messages_signals[SIGNAL_CHANNEL_INTERFACE_MESSAGES_MessageSent] =
  g_signal_new ("message-sent",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__BOXED_UINT_STRING,
      G_TYPE_NONE,
      3,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))),
      G_TYPE_UINT,
      G_TYPE_STRING);

  /**
   * TpSvcChannelInterfaceMessages::pending-messages-removed:
   * @arg_Message_IDs: const GArray * (FIXME, generate documentation)
   *
   * The PendingMessagesRemoved D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_interface_messages_signals[SIGNAL_CHANNEL_INTERFACE_MESSAGES_PendingMessagesRemoved] =
  g_signal_new ("pending-messages-removed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,
      1,
      DBUS_TYPE_G_UINT_ARRAY);

  /**
   * TpSvcChannelInterfaceMessages::message-received:
   * @arg_Message: const GPtrArray * (FIXME, generate documentation)
   *
   * The MessageReceived D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_interface_messages_signals[SIGNAL_CHANNEL_INTERFACE_MESSAGES_MessageReceived] =
  g_signal_new ("message-received",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,
      1,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))));

}
static void
tp_svc_channel_interface_messages_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_interface_messages_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_interface_messages_methods[] = {
  { (GCallback) tp_svc_channel_interface_messages_send_message, _tp_marshal_VOID__BOXED_UINT_POINTER, 0 },
  { (GCallback) tp_svc_channel_interface_messages_get_pending_message_content, _tp_marshal_VOID__UINT_BOXED_POINTER, 109 },
};

static const DBusGObjectInfo _tp_svc_channel_interface_messages_object_info = {
  0,
  _tp_svc_channel_interface_messages_methods,
  2,
"org.freedesktop.Telepathy.Channel.Interface.Messages\0SendMessage\0A\0Message\0I\0aa{sv}\0Flags\0I\0u\0Token\0O\0F\0N\0s\0\0org.freedesktop.Telepathy.Channel.Interface.Messages\0GetPendingMessageContent\0A\0Message_ID\0I\0u\0Parts\0I\0au\0Content\0O\0F\0N\0a{uv}\0\0\0",
"org.freedesktop.Telepathy.Channel.Interface.Messages\0MessageSent\0org.freedesktop.Telepathy.Channel.Interface.Messages\0PendingMessagesRemoved\0org.freedesktop.Telepathy.Channel.Interface.Messages\0MessageReceived\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_interface_password_object_info;

struct _TpSvcChannelInterfacePasswordClass {
    GTypeInterface parent_class;
    tp_svc_channel_interface_password_get_password_flags_impl get_password_flags;
    tp_svc_channel_interface_password_provide_password_impl provide_password;
};

enum {
    SIGNAL_CHANNEL_INTERFACE_PASSWORD_PasswordFlagsChanged,
    N_CHANNEL_INTERFACE_PASSWORD_SIGNALS
};
static guint channel_interface_password_signals[N_CHANNEL_INTERFACE_PASSWORD_SIGNALS] = {0};

static void tp_svc_channel_interface_password_base_init (gpointer klass);

GType
tp_svc_channel_interface_password_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelInterfacePasswordClass),
        tp_svc_channel_interface_password_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelInterfacePassword", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_interface_password_get_password_flags_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetPasswordFlags on interface org.freedesktop.Telepathy.Channel.Interface.Password.
 */
static void
tp_svc_channel_interface_password_get_password_flags (TpSvcChannelInterfacePassword *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_password_get_password_flags_impl impl = (TP_SVC_CHANNEL_INTERFACE_PASSWORD_GET_CLASS (self)->get_password_flags);

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
 * tp_svc_channel_interface_password_implement_get_password_flags:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetPasswordFlags D-Bus method
 *
 * Register an implementation for the GetPasswordFlags method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_password_implement_get_password_flags (TpSvcChannelInterfacePasswordClass *klass, tp_svc_channel_interface_password_get_password_flags_impl impl)
{
  klass->get_password_flags = impl;
}

/**
 * tp_svc_channel_interface_password_provide_password_impl:
 * @self: The object implementing this interface
 * @in_Password: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * ProvidePassword on interface org.freedesktop.Telepathy.Channel.Interface.Password.
 */
static void
tp_svc_channel_interface_password_provide_password (TpSvcChannelInterfacePassword *self,
    const gchar *in_Password,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_interface_password_provide_password_impl impl = (TP_SVC_CHANNEL_INTERFACE_PASSWORD_GET_CLASS (self)->provide_password);

  if (impl != NULL)
    {
      (impl) (self,
        in_Password,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_interface_password_implement_provide_password:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the ProvidePassword D-Bus method
 *
 * Register an implementation for the ProvidePassword method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_interface_password_implement_provide_password (TpSvcChannelInterfacePasswordClass *klass, tp_svc_channel_interface_password_provide_password_impl impl)
{
  klass->provide_password = impl;
}

/**
 * tp_svc_channel_interface_password_emit_password_flags_changed:
 * @instance: The object implementing this interface
 * @arg_Added: guint  (FIXME, generate documentation)
 * @arg_Removed: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * PasswordFlagsChanged signal on interface org.freedesktop.Telepathy.Channel.Interface.Password.
 */
void
tp_svc_channel_interface_password_emit_password_flags_changed (gpointer instance,
    guint arg_Added,
    guint arg_Removed)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_INTERFACE_PASSWORD));
  g_signal_emit (instance,
      channel_interface_password_signals[SIGNAL_CHANNEL_INTERFACE_PASSWORD_PasswordFlagsChanged],
      0,
      arg_Added,
      arg_Removed);
}

static inline void
tp_svc_channel_interface_password_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_channel_interface_password_get_type (),
      &_tp_svc_channel_interface_password_object_info);

  /**
   * TpSvcChannelInterfacePassword::password-flags-changed:
   * @arg_Added: guint  (FIXME, generate documentation)
   * @arg_Removed: guint  (FIXME, generate documentation)
   *
   * The PasswordFlagsChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_interface_password_signals[SIGNAL_CHANNEL_INTERFACE_PASSWORD_PasswordFlagsChanged] =
  g_signal_new ("password-flags-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT,
      G_TYPE_NONE,
      2,
      G_TYPE_UINT,
      G_TYPE_UINT);

}
static void
tp_svc_channel_interface_password_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_interface_password_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_interface_password_methods[] = {
  { (GCallback) tp_svc_channel_interface_password_get_password_flags, g_cclosure_marshal_VOID__POINTER, 0 },
  { (GCallback) tp_svc_channel_interface_password_provide_password, _tp_marshal_VOID__STRING_POINTER, 96 },
};

static const DBusGObjectInfo _tp_svc_channel_interface_password_object_info = {
  0,
  _tp_svc_channel_interface_password_methods,
  2,
"org.freedesktop.Telepathy.Channel.Interface.Password\0GetPasswordFlags\0A\0Password_Flags\0O\0F\0N\0u\0\0org.freedesktop.Telepathy.Channel.Interface.Password\0ProvidePassword\0A\0Password\0I\0s\0Correct\0O\0F\0N\0b\0\0\0",
"org.freedesktop.Telepathy.Channel.Interface.Password\0PasswordFlagsChanged\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_interface_tube_object_info;

struct _TpSvcChannelInterfaceTubeClass {
    GTypeInterface parent_class;
};

enum {
    SIGNAL_CHANNEL_INTERFACE_TUBE_TubeChannelStateChanged,
    N_CHANNEL_INTERFACE_TUBE_SIGNALS
};
static guint channel_interface_tube_signals[N_CHANNEL_INTERFACE_TUBE_SIGNALS] = {0};

static void tp_svc_channel_interface_tube_base_init (gpointer klass);

GType
tp_svc_channel_interface_tube_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelInterfaceTubeClass),
        tp_svc_channel_interface_tube_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelInterfaceTube", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_interface_tube_emit_tube_channel_state_changed:
 * @instance: The object implementing this interface
 * @arg_State: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * TubeChannelStateChanged signal on interface org.freedesktop.Telepathy.Channel.Interface.Tube.
 */
void
tp_svc_channel_interface_tube_emit_tube_channel_state_changed (gpointer instance,
    guint arg_State)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_INTERFACE_TUBE));
  g_signal_emit (instance,
      channel_interface_tube_signals[SIGNAL_CHANNEL_INTERFACE_TUBE_TubeChannelStateChanged],
      0,
      arg_State);
}

static inline void
tp_svc_channel_interface_tube_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[3] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "a{sv}", 0, NULL, NULL }, /* Parameters */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* State */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_channel_interface_tube_get_type (),
      &_tp_svc_channel_interface_tube_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Interface.Tube");
  properties[0].name = g_quark_from_static_string ("Parameters");
  properties[0].type = (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE));
  properties[1].name = g_quark_from_static_string ("State");
  properties[1].type = G_TYPE_UINT;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CHANNEL_INTERFACE_TUBE, &interface);

  /**
   * TpSvcChannelInterfaceTube::tube-channel-state-changed:
   * @arg_State: guint  (FIXME, generate documentation)
   *
   * The TubeChannelStateChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_interface_tube_signals[SIGNAL_CHANNEL_INTERFACE_TUBE_TubeChannelStateChanged] =
  g_signal_new ("tube-channel-state-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__UINT,
      G_TYPE_NONE,
      1,
      G_TYPE_UINT);

}
static void
tp_svc_channel_interface_tube_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_interface_tube_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_interface_tube_methods[] = {
  { NULL, NULL, 0 }
};

static const DBusGObjectInfo _tp_svc_channel_interface_tube_object_info = {
  0,
  _tp_svc_channel_interface_tube_methods,
  0,
"\0",
"org.freedesktop.Telepathy.Channel.Interface.Tube\0TubeChannelStateChanged\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_type_contact_list_object_info;

struct _TpSvcChannelTypeContactListClass {
    GTypeInterface parent_class;
};

static void tp_svc_channel_type_contact_list_base_init (gpointer klass);

GType
tp_svc_channel_type_contact_list_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelTypeContactListClass),
        tp_svc_channel_type_contact_list_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelTypeContactList", &info, 0);
    }

  return type;
}

static inline void
tp_svc_channel_type_contact_list_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_channel_type_contact_list_get_type (),
      &_tp_svc_channel_type_contact_list_object_info);

}
static void
tp_svc_channel_type_contact_list_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_type_contact_list_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_type_contact_list_methods[] = {
  { NULL, NULL, 0 }
};

static const DBusGObjectInfo _tp_svc_channel_type_contact_list_object_info = {
  0,
  _tp_svc_channel_type_contact_list_methods,
  0,
"\0",
"\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_type_dbus_tube_object_info;

struct _TpSvcChannelTypeDBusTubeClass {
    GTypeInterface parent_class;
    tp_svc_channel_type_dbus_tube_offer_impl offer;
    tp_svc_channel_type_dbus_tube_accept_impl accept;
};

enum {
    SIGNAL_CHANNEL_TYPE_DBUS_TUBE_DBusNamesChanged,
    N_CHANNEL_TYPE_DBUS_TUBE_SIGNALS
};
static guint channel_type_dbus_tube_signals[N_CHANNEL_TYPE_DBUS_TUBE_SIGNALS] = {0};

static void tp_svc_channel_type_dbus_tube_base_init (gpointer klass);

GType
tp_svc_channel_type_dbus_tube_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelTypeDBusTubeClass),
        tp_svc_channel_type_dbus_tube_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelTypeDBusTube", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_type_dbus_tube_offer_impl:
 * @self: The object implementing this interface
 * @in_parameters: GHashTable * (FIXME, generate documentation)
 * @in_access_control: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Offer on interface org.freedesktop.Telepathy.Channel.Type.DBusTube.
 */
static void
tp_svc_channel_type_dbus_tube_offer (TpSvcChannelTypeDBusTube *self,
    GHashTable *in_parameters,
    guint in_access_control,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_dbus_tube_offer_impl impl = (TP_SVC_CHANNEL_TYPE_DBUS_TUBE_GET_CLASS (self)->offer);

  if (impl != NULL)
    {
      (impl) (self,
        in_parameters,
        in_access_control,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_dbus_tube_implement_offer:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Offer D-Bus method
 *
 * Register an implementation for the Offer method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_dbus_tube_implement_offer (TpSvcChannelTypeDBusTubeClass *klass, tp_svc_channel_type_dbus_tube_offer_impl impl)
{
  klass->offer = impl;
}

/**
 * tp_svc_channel_type_dbus_tube_accept_impl:
 * @self: The object implementing this interface
 * @in_access_control: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Accept on interface org.freedesktop.Telepathy.Channel.Type.DBusTube.
 */
static void
tp_svc_channel_type_dbus_tube_accept (TpSvcChannelTypeDBusTube *self,
    guint in_access_control,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_dbus_tube_accept_impl impl = (TP_SVC_CHANNEL_TYPE_DBUS_TUBE_GET_CLASS (self)->accept);

  if (impl != NULL)
    {
      (impl) (self,
        in_access_control,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_dbus_tube_implement_accept:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Accept D-Bus method
 *
 * Register an implementation for the Accept method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_dbus_tube_implement_accept (TpSvcChannelTypeDBusTubeClass *klass, tp_svc_channel_type_dbus_tube_accept_impl impl)
{
  klass->accept = impl;
}

/**
 * tp_svc_channel_type_dbus_tube_emit_dbus_names_changed:
 * @instance: The object implementing this interface
 * @arg_Added: GHashTable * (FIXME, generate documentation)
 * @arg_Removed: const GArray * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * DBusNamesChanged signal on interface org.freedesktop.Telepathy.Channel.Type.DBusTube.
 */
void
tp_svc_channel_type_dbus_tube_emit_dbus_names_changed (gpointer instance,
    GHashTable *arg_Added,
    const GArray *arg_Removed)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_DBUS_TUBE));
  g_signal_emit (instance,
      channel_type_dbus_tube_signals[SIGNAL_CHANNEL_TYPE_DBUS_TUBE_DBusNamesChanged],
      0,
      arg_Added,
      arg_Removed);
}

static inline void
tp_svc_channel_type_dbus_tube_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[4] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "s", 0, NULL, NULL }, /* ServiceName */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "a{us}", 0, NULL, NULL }, /* DBusNames */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "au", 0, NULL, NULL }, /* SupportedAccessControls */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_channel_type_dbus_tube_get_type (),
      &_tp_svc_channel_type_dbus_tube_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Type.DBusTube");
  properties[0].name = g_quark_from_static_string ("ServiceName");
  properties[0].type = G_TYPE_STRING;
  properties[1].name = g_quark_from_static_string ("DBusNames");
  properties[1].type = (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_STRING));
  properties[2].name = g_quark_from_static_string ("SupportedAccessControls");
  properties[2].type = DBUS_TYPE_G_UINT_ARRAY;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CHANNEL_TYPE_DBUS_TUBE, &interface);

  /**
   * TpSvcChannelTypeDBusTube::d-bus-names-changed:
   * @arg_Added: GHashTable * (FIXME, generate documentation)
   * @arg_Removed: const GArray * (FIXME, generate documentation)
   *
   * The DBusNamesChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_dbus_tube_signals[SIGNAL_CHANNEL_TYPE_DBUS_TUBE_DBusNamesChanged] =
  g_signal_new ("d-bus-names-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__BOXED_BOXED,
      G_TYPE_NONE,
      2,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_STRING)),
      DBUS_TYPE_G_UINT_ARRAY);

}
static void
tp_svc_channel_type_dbus_tube_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_type_dbus_tube_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_type_dbus_tube_methods[] = {
  { (GCallback) tp_svc_channel_type_dbus_tube_offer, _tp_marshal_VOID__BOXED_UINT_POINTER, 0 },
  { (GCallback) tp_svc_channel_type_dbus_tube_accept, g_cclosure_marshal_VOID__UINT_POINTER, 111 },
};

static const DBusGObjectInfo _tp_svc_channel_type_dbus_tube_object_info = {
  0,
  _tp_svc_channel_type_dbus_tube_methods,
  2,
"org.freedesktop.Telepathy.Channel.Type.DBusTube\0Offer\0A\0parameters\0I\0a{sv}\0access_control\0I\0u\0address\0O\0F\0N\0s\0\0org.freedesktop.Telepathy.Channel.Type.DBusTube\0Accept\0A\0access_control\0I\0u\0address\0O\0F\0N\0s\0\0\0",
"org.freedesktop.Telepathy.Channel.Type.DBusTube\0DBusNamesChanged\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_type_file_transfer_object_info;

struct _TpSvcChannelTypeFileTransferClass {
    GTypeInterface parent_class;
    tp_svc_channel_type_file_transfer_accept_file_impl accept_file;
    tp_svc_channel_type_file_transfer_provide_file_impl provide_file;
};

enum {
    SIGNAL_CHANNEL_TYPE_FILE_TRANSFER_FileTransferStateChanged,
    SIGNAL_CHANNEL_TYPE_FILE_TRANSFER_TransferredBytesChanged,
    SIGNAL_CHANNEL_TYPE_FILE_TRANSFER_InitialOffsetDefined,
    N_CHANNEL_TYPE_FILE_TRANSFER_SIGNALS
};
static guint channel_type_file_transfer_signals[N_CHANNEL_TYPE_FILE_TRANSFER_SIGNALS] = {0};

static void tp_svc_channel_type_file_transfer_base_init (gpointer klass);

GType
tp_svc_channel_type_file_transfer_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelTypeFileTransferClass),
        tp_svc_channel_type_file_transfer_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelTypeFileTransfer", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_type_file_transfer_accept_file_impl:
 * @self: The object implementing this interface
 * @in_Address_Type: guint  (FIXME, generate documentation)
 * @in_Access_Control: guint  (FIXME, generate documentation)
 * @in_Access_Control_Param: const GValue * (FIXME, generate documentation)
 * @in_Offset: guint64  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * AcceptFile on interface org.freedesktop.Telepathy.Channel.Type.FileTransfer.
 */
static void
tp_svc_channel_type_file_transfer_accept_file (TpSvcChannelTypeFileTransfer *self,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    guint64 in_Offset,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_file_transfer_accept_file_impl impl = (TP_SVC_CHANNEL_TYPE_FILE_TRANSFER_GET_CLASS (self)->accept_file);

  if (impl != NULL)
    {
      (impl) (self,
        in_Address_Type,
        in_Access_Control,
        in_Access_Control_Param,
        in_Offset,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_file_transfer_implement_accept_file:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the AcceptFile D-Bus method
 *
 * Register an implementation for the AcceptFile method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_file_transfer_implement_accept_file (TpSvcChannelTypeFileTransferClass *klass, tp_svc_channel_type_file_transfer_accept_file_impl impl)
{
  klass->accept_file = impl;
}

/**
 * tp_svc_channel_type_file_transfer_provide_file_impl:
 * @self: The object implementing this interface
 * @in_Address_Type: guint  (FIXME, generate documentation)
 * @in_Access_Control: guint  (FIXME, generate documentation)
 * @in_Access_Control_Param: const GValue * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * ProvideFile on interface org.freedesktop.Telepathy.Channel.Type.FileTransfer.
 */
static void
tp_svc_channel_type_file_transfer_provide_file (TpSvcChannelTypeFileTransfer *self,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_file_transfer_provide_file_impl impl = (TP_SVC_CHANNEL_TYPE_FILE_TRANSFER_GET_CLASS (self)->provide_file);

  if (impl != NULL)
    {
      (impl) (self,
        in_Address_Type,
        in_Access_Control,
        in_Access_Control_Param,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_file_transfer_implement_provide_file:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the ProvideFile D-Bus method
 *
 * Register an implementation for the ProvideFile method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_file_transfer_implement_provide_file (TpSvcChannelTypeFileTransferClass *klass, tp_svc_channel_type_file_transfer_provide_file_impl impl)
{
  klass->provide_file = impl;
}

/**
 * tp_svc_channel_type_file_transfer_emit_file_transfer_state_changed:
 * @instance: The object implementing this interface
 * @arg_State: guint  (FIXME, generate documentation)
 * @arg_Reason: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * FileTransferStateChanged signal on interface org.freedesktop.Telepathy.Channel.Type.FileTransfer.
 */
void
tp_svc_channel_type_file_transfer_emit_file_transfer_state_changed (gpointer instance,
    guint arg_State,
    guint arg_Reason)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_FILE_TRANSFER));
  g_signal_emit (instance,
      channel_type_file_transfer_signals[SIGNAL_CHANNEL_TYPE_FILE_TRANSFER_FileTransferStateChanged],
      0,
      arg_State,
      arg_Reason);
}

/**
 * tp_svc_channel_type_file_transfer_emit_transferred_bytes_changed:
 * @instance: The object implementing this interface
 * @arg_Count: guint64  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * TransferredBytesChanged signal on interface org.freedesktop.Telepathy.Channel.Type.FileTransfer.
 */
void
tp_svc_channel_type_file_transfer_emit_transferred_bytes_changed (gpointer instance,
    guint64 arg_Count)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_FILE_TRANSFER));
  g_signal_emit (instance,
      channel_type_file_transfer_signals[SIGNAL_CHANNEL_TYPE_FILE_TRANSFER_TransferredBytesChanged],
      0,
      arg_Count);
}

/**
 * tp_svc_channel_type_file_transfer_emit_initial_offset_defined:
 * @instance: The object implementing this interface
 * @arg_InitialOffset: guint64  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * InitialOffsetDefined signal on interface org.freedesktop.Telepathy.Channel.Type.FileTransfer.
 */
void
tp_svc_channel_type_file_transfer_emit_initial_offset_defined (gpointer instance,
    guint64 arg_InitialOffset)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_FILE_TRANSFER));
  g_signal_emit (instance,
      channel_type_file_transfer_signals[SIGNAL_CHANNEL_TYPE_FILE_TRANSFER_InitialOffsetDefined],
      0,
      arg_InitialOffset);
}

static inline void
tp_svc_channel_type_file_transfer_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[12] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* State */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "s", 0, NULL, NULL }, /* ContentType */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "s", 0, NULL, NULL }, /* Filename */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "t", 0, NULL, NULL }, /* Size */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "u", 0, NULL, NULL }, /* ContentHashType */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "s", 0, NULL, NULL }, /* ContentHash */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "s", 0, NULL, NULL }, /* Description */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "x", 0, NULL, NULL }, /* Date */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "a{uau}", 0, NULL, NULL }, /* AvailableSocketTypes */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "t", 0, NULL, NULL }, /* TransferredBytes */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "t", 0, NULL, NULL }, /* InitialOffset */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_channel_type_file_transfer_get_type (),
      &_tp_svc_channel_type_file_transfer_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Type.FileTransfer");
  properties[0].name = g_quark_from_static_string ("State");
  properties[0].type = G_TYPE_UINT;
  properties[1].name = g_quark_from_static_string ("ContentType");
  properties[1].type = G_TYPE_STRING;
  properties[2].name = g_quark_from_static_string ("Filename");
  properties[2].type = G_TYPE_STRING;
  properties[3].name = g_quark_from_static_string ("Size");
  properties[3].type = G_TYPE_UINT64;
  properties[4].name = g_quark_from_static_string ("ContentHashType");
  properties[4].type = G_TYPE_UINT;
  properties[5].name = g_quark_from_static_string ("ContentHash");
  properties[5].type = G_TYPE_STRING;
  properties[6].name = g_quark_from_static_string ("Description");
  properties[6].type = G_TYPE_STRING;
  properties[7].name = g_quark_from_static_string ("Date");
  properties[7].type = G_TYPE_INT64;
  properties[8].name = g_quark_from_static_string ("AvailableSocketTypes");
  properties[8].type = (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, DBUS_TYPE_G_UINT_ARRAY));
  properties[9].name = g_quark_from_static_string ("TransferredBytes");
  properties[9].type = G_TYPE_UINT64;
  properties[10].name = g_quark_from_static_string ("InitialOffset");
  properties[10].type = G_TYPE_UINT64;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CHANNEL_TYPE_FILE_TRANSFER, &interface);

  /**
   * TpSvcChannelTypeFileTransfer::file-transfer-state-changed:
   * @arg_State: guint  (FIXME, generate documentation)
   * @arg_Reason: guint  (FIXME, generate documentation)
   *
   * The FileTransferStateChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_file_transfer_signals[SIGNAL_CHANNEL_TYPE_FILE_TRANSFER_FileTransferStateChanged] =
  g_signal_new ("file-transfer-state-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT,
      G_TYPE_NONE,
      2,
      G_TYPE_UINT,
      G_TYPE_UINT);

  /**
   * TpSvcChannelTypeFileTransfer::transferred-bytes-changed:
   * @arg_Count: guint64  (FIXME, generate documentation)
   *
   * The TransferredBytesChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_file_transfer_signals[SIGNAL_CHANNEL_TYPE_FILE_TRANSFER_TransferredBytesChanged] =
  g_signal_new ("transferred-bytes-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT64,
      G_TYPE_NONE,
      1,
      G_TYPE_UINT64);

  /**
   * TpSvcChannelTypeFileTransfer::initial-offset-defined:
   * @arg_InitialOffset: guint64  (FIXME, generate documentation)
   *
   * The InitialOffsetDefined D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_file_transfer_signals[SIGNAL_CHANNEL_TYPE_FILE_TRANSFER_InitialOffsetDefined] =
  g_signal_new ("initial-offset-defined",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT64,
      G_TYPE_NONE,
      1,
      G_TYPE_UINT64);

}
static void
tp_svc_channel_type_file_transfer_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_type_file_transfer_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_type_file_transfer_methods[] = {
  { (GCallback) tp_svc_channel_type_file_transfer_accept_file, _tp_marshal_VOID__UINT_UINT_BOXED_UINT64_POINTER, 0 },
  { (GCallback) tp_svc_channel_type_file_transfer_provide_file, _tp_marshal_VOID__UINT_UINT_BOXED_POINTER, 154 },
};

static const DBusGObjectInfo _tp_svc_channel_type_file_transfer_object_info = {
  0,
  _tp_svc_channel_type_file_transfer_methods,
  2,
"org.freedesktop.Telepathy.Channel.Type.FileTransfer\0AcceptFile\0A\0Address_Type\0I\0u\0Access_Control\0I\0u\0Access_Control_Param\0I\0v\0Offset\0I\0t\0Address\0O\0F\0N\0v\0\0org.freedesktop.Telepathy.Channel.Type.FileTransfer\0ProvideFile\0A\0Address_Type\0I\0u\0Access_Control\0I\0u\0Access_Control_Param\0I\0v\0Address\0O\0F\0N\0v\0\0\0",
"org.freedesktop.Telepathy.Channel.Type.FileTransfer\0FileTransferStateChanged\0org.freedesktop.Telepathy.Channel.Type.FileTransfer\0TransferredBytesChanged\0org.freedesktop.Telepathy.Channel.Type.FileTransfer\0InitialOffsetDefined\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_type_room_list_object_info;

struct _TpSvcChannelTypeRoomListClass {
    GTypeInterface parent_class;
    tp_svc_channel_type_room_list_get_listing_rooms_impl get_listing_rooms;
    tp_svc_channel_type_room_list_list_rooms_impl list_rooms;
    tp_svc_channel_type_room_list_stop_listing_impl stop_listing;
};

enum {
    SIGNAL_CHANNEL_TYPE_ROOM_LIST_GotRooms,
    SIGNAL_CHANNEL_TYPE_ROOM_LIST_ListingRooms,
    N_CHANNEL_TYPE_ROOM_LIST_SIGNALS
};
static guint channel_type_room_list_signals[N_CHANNEL_TYPE_ROOM_LIST_SIGNALS] = {0};

static void tp_svc_channel_type_room_list_base_init (gpointer klass);

GType
tp_svc_channel_type_room_list_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelTypeRoomListClass),
        tp_svc_channel_type_room_list_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelTypeRoomList", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_type_room_list_get_listing_rooms_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetListingRooms on interface org.freedesktop.Telepathy.Channel.Type.RoomList.
 */
static void
tp_svc_channel_type_room_list_get_listing_rooms (TpSvcChannelTypeRoomList *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_room_list_get_listing_rooms_impl impl = (TP_SVC_CHANNEL_TYPE_ROOM_LIST_GET_CLASS (self)->get_listing_rooms);

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
 * tp_svc_channel_type_room_list_implement_get_listing_rooms:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetListingRooms D-Bus method
 *
 * Register an implementation for the GetListingRooms method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_room_list_implement_get_listing_rooms (TpSvcChannelTypeRoomListClass *klass, tp_svc_channel_type_room_list_get_listing_rooms_impl impl)
{
  klass->get_listing_rooms = impl;
}

/**
 * tp_svc_channel_type_room_list_list_rooms_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * ListRooms on interface org.freedesktop.Telepathy.Channel.Type.RoomList.
 */
static void
tp_svc_channel_type_room_list_list_rooms (TpSvcChannelTypeRoomList *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_room_list_list_rooms_impl impl = (TP_SVC_CHANNEL_TYPE_ROOM_LIST_GET_CLASS (self)->list_rooms);

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
 * tp_svc_channel_type_room_list_implement_list_rooms:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the ListRooms D-Bus method
 *
 * Register an implementation for the ListRooms method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_room_list_implement_list_rooms (TpSvcChannelTypeRoomListClass *klass, tp_svc_channel_type_room_list_list_rooms_impl impl)
{
  klass->list_rooms = impl;
}

/**
 * tp_svc_channel_type_room_list_stop_listing_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * StopListing on interface org.freedesktop.Telepathy.Channel.Type.RoomList.
 */
static void
tp_svc_channel_type_room_list_stop_listing (TpSvcChannelTypeRoomList *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_room_list_stop_listing_impl impl = (TP_SVC_CHANNEL_TYPE_ROOM_LIST_GET_CLASS (self)->stop_listing);

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
 * tp_svc_channel_type_room_list_implement_stop_listing:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the StopListing D-Bus method
 *
 * Register an implementation for the StopListing method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_room_list_implement_stop_listing (TpSvcChannelTypeRoomListClass *klass, tp_svc_channel_type_room_list_stop_listing_impl impl)
{
  klass->stop_listing = impl;
}

/**
 * tp_svc_channel_type_room_list_emit_got_rooms:
 * @instance: The object implementing this interface
 * @arg_Rooms: const GPtrArray * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * GotRooms signal on interface org.freedesktop.Telepathy.Channel.Type.RoomList.
 */
void
tp_svc_channel_type_room_list_emit_got_rooms (gpointer instance,
    const GPtrArray *arg_Rooms)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_ROOM_LIST));
  g_signal_emit (instance,
      channel_type_room_list_signals[SIGNAL_CHANNEL_TYPE_ROOM_LIST_GotRooms],
      0,
      arg_Rooms);
}

/**
 * tp_svc_channel_type_room_list_emit_listing_rooms:
 * @instance: The object implementing this interface
 * @arg_Listing: gboolean  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * ListingRooms signal on interface org.freedesktop.Telepathy.Channel.Type.RoomList.
 */
void
tp_svc_channel_type_room_list_emit_listing_rooms (gpointer instance,
    gboolean arg_Listing)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_ROOM_LIST));
  g_signal_emit (instance,
      channel_type_room_list_signals[SIGNAL_CHANNEL_TYPE_ROOM_LIST_ListingRooms],
      0,
      arg_Listing);
}

static inline void
tp_svc_channel_type_room_list_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[2] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "s", 0, NULL, NULL }, /* Server */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_channel_type_room_list_get_type (),
      &_tp_svc_channel_type_room_list_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Type.RoomList");
  properties[0].name = g_quark_from_static_string ("Server");
  properties[0].type = G_TYPE_STRING;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CHANNEL_TYPE_ROOM_LIST, &interface);

  /**
   * TpSvcChannelTypeRoomList::got-rooms:
   * @arg_Rooms: const GPtrArray * (FIXME, generate documentation)
   *
   * The GotRooms D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_room_list_signals[SIGNAL_CHANNEL_TYPE_ROOM_LIST_GotRooms] =
  g_signal_new ("got-rooms",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,
      1,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID)))));

  /**
   * TpSvcChannelTypeRoomList::listing-rooms:
   * @arg_Listing: gboolean  (FIXME, generate documentation)
   *
   * The ListingRooms D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_room_list_signals[SIGNAL_CHANNEL_TYPE_ROOM_LIST_ListingRooms] =
  g_signal_new ("listing-rooms",
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
tp_svc_channel_type_room_list_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_type_room_list_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_type_room_list_methods[] = {
  { (GCallback) tp_svc_channel_type_room_list_get_listing_rooms, g_cclosure_marshal_VOID__POINTER, 0 },
  { (GCallback) tp_svc_channel_type_room_list_list_rooms, g_cclosure_marshal_VOID__POINTER, 87 },
  { (GCallback) tp_svc_channel_type_room_list_stop_listing, g_cclosure_marshal_VOID__POINTER, 148 },
};

static const DBusGObjectInfo _tp_svc_channel_type_room_list_object_info = {
  0,
  _tp_svc_channel_type_room_list_methods,
  3,
"org.freedesktop.Telepathy.Channel.Type.RoomList\0GetListingRooms\0A\0In_Progress\0O\0F\0N\0b\0\0org.freedesktop.Telepathy.Channel.Type.RoomList\0ListRooms\0A\0\0org.freedesktop.Telepathy.Channel.Type.RoomList\0StopListing\0A\0\0\0",
"org.freedesktop.Telepathy.Channel.Type.RoomList\0GotRooms\0org.freedesktop.Telepathy.Channel.Type.RoomList\0ListingRooms\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_type_stream_tube_object_info;

struct _TpSvcChannelTypeStreamTubeClass {
    GTypeInterface parent_class;
    tp_svc_channel_type_stream_tube_offer_impl offer;
    tp_svc_channel_type_stream_tube_accept_impl accept;
};

enum {
    SIGNAL_CHANNEL_TYPE_STREAM_TUBE_NewRemoteConnection,
    SIGNAL_CHANNEL_TYPE_STREAM_TUBE_NewLocalConnection,
    SIGNAL_CHANNEL_TYPE_STREAM_TUBE_ConnectionClosed,
    N_CHANNEL_TYPE_STREAM_TUBE_SIGNALS
};
static guint channel_type_stream_tube_signals[N_CHANNEL_TYPE_STREAM_TUBE_SIGNALS] = {0};

static void tp_svc_channel_type_stream_tube_base_init (gpointer klass);

GType
tp_svc_channel_type_stream_tube_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelTypeStreamTubeClass),
        tp_svc_channel_type_stream_tube_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelTypeStreamTube", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_type_stream_tube_offer_impl:
 * @self: The object implementing this interface
 * @in_address_type: guint  (FIXME, generate documentation)
 * @in_address: const GValue * (FIXME, generate documentation)
 * @in_access_control: guint  (FIXME, generate documentation)
 * @in_parameters: GHashTable * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Offer on interface org.freedesktop.Telepathy.Channel.Type.StreamTube.
 */
static void
tp_svc_channel_type_stream_tube_offer (TpSvcChannelTypeStreamTube *self,
    guint in_address_type,
    const GValue *in_address,
    guint in_access_control,
    GHashTable *in_parameters,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_stream_tube_offer_impl impl = (TP_SVC_CHANNEL_TYPE_STREAM_TUBE_GET_CLASS (self)->offer);

  if (impl != NULL)
    {
      (impl) (self,
        in_address_type,
        in_address,
        in_access_control,
        in_parameters,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_stream_tube_implement_offer:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Offer D-Bus method
 *
 * Register an implementation for the Offer method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_stream_tube_implement_offer (TpSvcChannelTypeStreamTubeClass *klass, tp_svc_channel_type_stream_tube_offer_impl impl)
{
  klass->offer = impl;
}

/**
 * tp_svc_channel_type_stream_tube_accept_impl:
 * @self: The object implementing this interface
 * @in_address_type: guint  (FIXME, generate documentation)
 * @in_access_control: guint  (FIXME, generate documentation)
 * @in_access_control_param: const GValue * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Accept on interface org.freedesktop.Telepathy.Channel.Type.StreamTube.
 */
static void
tp_svc_channel_type_stream_tube_accept (TpSvcChannelTypeStreamTube *self,
    guint in_address_type,
    guint in_access_control,
    const GValue *in_access_control_param,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_stream_tube_accept_impl impl = (TP_SVC_CHANNEL_TYPE_STREAM_TUBE_GET_CLASS (self)->accept);

  if (impl != NULL)
    {
      (impl) (self,
        in_address_type,
        in_access_control,
        in_access_control_param,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_stream_tube_implement_accept:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Accept D-Bus method
 *
 * Register an implementation for the Accept method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_stream_tube_implement_accept (TpSvcChannelTypeStreamTubeClass *klass, tp_svc_channel_type_stream_tube_accept_impl impl)
{
  klass->accept = impl;
}

/**
 * tp_svc_channel_type_stream_tube_emit_new_remote_connection:
 * @instance: The object implementing this interface
 * @arg_Handle: guint  (FIXME, generate documentation)
 * @arg_Connection_Param: const GValue * (FIXME, generate documentation)
 * @arg_Connection_ID: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * NewRemoteConnection signal on interface org.freedesktop.Telepathy.Channel.Type.StreamTube.
 */
void
tp_svc_channel_type_stream_tube_emit_new_remote_connection (gpointer instance,
    guint arg_Handle,
    const GValue *arg_Connection_Param,
    guint arg_Connection_ID)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_STREAM_TUBE));
  g_signal_emit (instance,
      channel_type_stream_tube_signals[SIGNAL_CHANNEL_TYPE_STREAM_TUBE_NewRemoteConnection],
      0,
      arg_Handle,
      arg_Connection_Param,
      arg_Connection_ID);
}

/**
 * tp_svc_channel_type_stream_tube_emit_new_local_connection:
 * @instance: The object implementing this interface
 * @arg_Connection_ID: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * NewLocalConnection signal on interface org.freedesktop.Telepathy.Channel.Type.StreamTube.
 */
void
tp_svc_channel_type_stream_tube_emit_new_local_connection (gpointer instance,
    guint arg_Connection_ID)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_STREAM_TUBE));
  g_signal_emit (instance,
      channel_type_stream_tube_signals[SIGNAL_CHANNEL_TYPE_STREAM_TUBE_NewLocalConnection],
      0,
      arg_Connection_ID);
}

/**
 * tp_svc_channel_type_stream_tube_emit_connection_closed:
 * @instance: The object implementing this interface
 * @arg_Connection_ID: guint  (FIXME, generate documentation)
 * @arg_Error: const gchar * (FIXME, generate documentation)
 * @arg_Message: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * ConnectionClosed signal on interface org.freedesktop.Telepathy.Channel.Type.StreamTube.
 */
void
tp_svc_channel_type_stream_tube_emit_connection_closed (gpointer instance,
    guint arg_Connection_ID,
    const gchar *arg_Error,
    const gchar *arg_Message)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_STREAM_TUBE));
  g_signal_emit (instance,
      channel_type_stream_tube_signals[SIGNAL_CHANNEL_TYPE_STREAM_TUBE_ConnectionClosed],
      0,
      arg_Connection_ID,
      arg_Error,
      arg_Message);
}

static inline void
tp_svc_channel_type_stream_tube_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[3] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "s", 0, NULL, NULL }, /* Service */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "a{uau}", 0, NULL, NULL }, /* SupportedSocketTypes */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_channel_type_stream_tube_get_type (),
      &_tp_svc_channel_type_stream_tube_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Type.StreamTube");
  properties[0].name = g_quark_from_static_string ("Service");
  properties[0].type = G_TYPE_STRING;
  properties[1].name = g_quark_from_static_string ("SupportedSocketTypes");
  properties[1].type = (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, DBUS_TYPE_G_UINT_ARRAY));
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CHANNEL_TYPE_STREAM_TUBE, &interface);

  /**
   * TpSvcChannelTypeStreamTube::new-remote-connection:
   * @arg_Handle: guint  (FIXME, generate documentation)
   * @arg_Connection_Param: const GValue * (FIXME, generate documentation)
   * @arg_Connection_ID: guint  (FIXME, generate documentation)
   *
   * The NewRemoteConnection D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_stream_tube_signals[SIGNAL_CHANNEL_TYPE_STREAM_TUBE_NewRemoteConnection] =
  g_signal_new ("new-remote-connection",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_BOXED_UINT,
      G_TYPE_NONE,
      3,
      G_TYPE_UINT,
      G_TYPE_VALUE,
      G_TYPE_UINT);

  /**
   * TpSvcChannelTypeStreamTube::new-local-connection:
   * @arg_Connection_ID: guint  (FIXME, generate documentation)
   *
   * The NewLocalConnection D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_stream_tube_signals[SIGNAL_CHANNEL_TYPE_STREAM_TUBE_NewLocalConnection] =
  g_signal_new ("new-local-connection",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__UINT,
      G_TYPE_NONE,
      1,
      G_TYPE_UINT);

  /**
   * TpSvcChannelTypeStreamTube::connection-closed:
   * @arg_Connection_ID: guint  (FIXME, generate documentation)
   * @arg_Error: const gchar * (FIXME, generate documentation)
   * @arg_Message: const gchar * (FIXME, generate documentation)
   *
   * The ConnectionClosed D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_stream_tube_signals[SIGNAL_CHANNEL_TYPE_STREAM_TUBE_ConnectionClosed] =
  g_signal_new ("connection-closed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_STRING_STRING,
      G_TYPE_NONE,
      3,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_STRING);

}
static void
tp_svc_channel_type_stream_tube_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_type_stream_tube_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_type_stream_tube_methods[] = {
  { (GCallback) tp_svc_channel_type_stream_tube_offer, _tp_marshal_VOID__UINT_BOXED_UINT_BOXED_POINTER, 0 },
  { (GCallback) tp_svc_channel_type_stream_tube_accept, _tp_marshal_VOID__UINT_UINT_BOXED_POINTER, 126 },
};

static const DBusGObjectInfo _tp_svc_channel_type_stream_tube_object_info = {
  0,
  _tp_svc_channel_type_stream_tube_methods,
  2,
"org.freedesktop.Telepathy.Channel.Type.StreamTube\0Offer\0A\0address_type\0I\0u\0address\0I\0v\0access_control\0I\0u\0parameters\0I\0a{sv}\0\0org.freedesktop.Telepathy.Channel.Type.StreamTube\0Accept\0A\0address_type\0I\0u\0access_control\0I\0u\0access_control_param\0I\0v\0address\0O\0F\0N\0v\0\0\0",
"org.freedesktop.Telepathy.Channel.Type.StreamTube\0NewRemoteConnection\0org.freedesktop.Telepathy.Channel.Type.StreamTube\0NewLocalConnection\0org.freedesktop.Telepathy.Channel.Type.StreamTube\0ConnectionClosed\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_type_streamed_media_object_info;

struct _TpSvcChannelTypeStreamedMediaClass {
    GTypeInterface parent_class;
    tp_svc_channel_type_streamed_media_list_streams_impl list_streams;
    tp_svc_channel_type_streamed_media_remove_streams_impl remove_streams;
    tp_svc_channel_type_streamed_media_request_stream_direction_impl request_stream_direction;
    tp_svc_channel_type_streamed_media_request_streams_impl request_streams;
};

enum {
    SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamAdded,
    SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamDirectionChanged,
    SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamError,
    SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamRemoved,
    SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamStateChanged,
    N_CHANNEL_TYPE_STREAMED_MEDIA_SIGNALS
};
static guint channel_type_streamed_media_signals[N_CHANNEL_TYPE_STREAMED_MEDIA_SIGNALS] = {0};

static void tp_svc_channel_type_streamed_media_base_init (gpointer klass);

GType
tp_svc_channel_type_streamed_media_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelTypeStreamedMediaClass),
        tp_svc_channel_type_streamed_media_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelTypeStreamedMedia", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_type_streamed_media_list_streams_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * ListStreams on interface org.freedesktop.Telepathy.Channel.Type.StreamedMedia.
 */
static void
tp_svc_channel_type_streamed_media_list_streams (TpSvcChannelTypeStreamedMedia *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_streamed_media_list_streams_impl impl = (TP_SVC_CHANNEL_TYPE_STREAMED_MEDIA_GET_CLASS (self)->list_streams);

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
 * tp_svc_channel_type_streamed_media_implement_list_streams:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the ListStreams D-Bus method
 *
 * Register an implementation for the ListStreams method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_streamed_media_implement_list_streams (TpSvcChannelTypeStreamedMediaClass *klass, tp_svc_channel_type_streamed_media_list_streams_impl impl)
{
  klass->list_streams = impl;
}

/**
 * tp_svc_channel_type_streamed_media_remove_streams_impl:
 * @self: The object implementing this interface
 * @in_Streams: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RemoveStreams on interface org.freedesktop.Telepathy.Channel.Type.StreamedMedia.
 */
static void
tp_svc_channel_type_streamed_media_remove_streams (TpSvcChannelTypeStreamedMedia *self,
    const GArray *in_Streams,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_streamed_media_remove_streams_impl impl = (TP_SVC_CHANNEL_TYPE_STREAMED_MEDIA_GET_CLASS (self)->remove_streams);

  if (impl != NULL)
    {
      (impl) (self,
        in_Streams,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_streamed_media_implement_remove_streams:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RemoveStreams D-Bus method
 *
 * Register an implementation for the RemoveStreams method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_streamed_media_implement_remove_streams (TpSvcChannelTypeStreamedMediaClass *klass, tp_svc_channel_type_streamed_media_remove_streams_impl impl)
{
  klass->remove_streams = impl;
}

/**
 * tp_svc_channel_type_streamed_media_request_stream_direction_impl:
 * @self: The object implementing this interface
 * @in_Stream_ID: guint  (FIXME, generate documentation)
 * @in_Stream_Direction: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RequestStreamDirection on interface org.freedesktop.Telepathy.Channel.Type.StreamedMedia.
 */
static void
tp_svc_channel_type_streamed_media_request_stream_direction (TpSvcChannelTypeStreamedMedia *self,
    guint in_Stream_ID,
    guint in_Stream_Direction,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_streamed_media_request_stream_direction_impl impl = (TP_SVC_CHANNEL_TYPE_STREAMED_MEDIA_GET_CLASS (self)->request_stream_direction);

  if (impl != NULL)
    {
      (impl) (self,
        in_Stream_ID,
        in_Stream_Direction,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_streamed_media_implement_request_stream_direction:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RequestStreamDirection D-Bus method
 *
 * Register an implementation for the RequestStreamDirection method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_streamed_media_implement_request_stream_direction (TpSvcChannelTypeStreamedMediaClass *klass, tp_svc_channel_type_streamed_media_request_stream_direction_impl impl)
{
  klass->request_stream_direction = impl;
}

/**
 * tp_svc_channel_type_streamed_media_request_streams_impl:
 * @self: The object implementing this interface
 * @in_Contact_Handle: guint  (FIXME, generate documentation)
 * @in_Types: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * RequestStreams on interface org.freedesktop.Telepathy.Channel.Type.StreamedMedia.
 */
static void
tp_svc_channel_type_streamed_media_request_streams (TpSvcChannelTypeStreamedMedia *self,
    guint in_Contact_Handle,
    const GArray *in_Types,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_streamed_media_request_streams_impl impl = (TP_SVC_CHANNEL_TYPE_STREAMED_MEDIA_GET_CLASS (self)->request_streams);

  if (impl != NULL)
    {
      (impl) (self,
        in_Contact_Handle,
        in_Types,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_streamed_media_implement_request_streams:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the RequestStreams D-Bus method
 *
 * Register an implementation for the RequestStreams method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_streamed_media_implement_request_streams (TpSvcChannelTypeStreamedMediaClass *klass, tp_svc_channel_type_streamed_media_request_streams_impl impl)
{
  klass->request_streams = impl;
}

/**
 * tp_svc_channel_type_streamed_media_emit_stream_added:
 * @instance: The object implementing this interface
 * @arg_Stream_ID: guint  (FIXME, generate documentation)
 * @arg_Contact_Handle: guint  (FIXME, generate documentation)
 * @arg_Stream_Type: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * StreamAdded signal on interface org.freedesktop.Telepathy.Channel.Type.StreamedMedia.
 */
void
tp_svc_channel_type_streamed_media_emit_stream_added (gpointer instance,
    guint arg_Stream_ID,
    guint arg_Contact_Handle,
    guint arg_Stream_Type)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_STREAMED_MEDIA));
  g_signal_emit (instance,
      channel_type_streamed_media_signals[SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamAdded],
      0,
      arg_Stream_ID,
      arg_Contact_Handle,
      arg_Stream_Type);
}

/**
 * tp_svc_channel_type_streamed_media_emit_stream_direction_changed:
 * @instance: The object implementing this interface
 * @arg_Stream_ID: guint  (FIXME, generate documentation)
 * @arg_Stream_Direction: guint  (FIXME, generate documentation)
 * @arg_Pending_Flags: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * StreamDirectionChanged signal on interface org.freedesktop.Telepathy.Channel.Type.StreamedMedia.
 */
void
tp_svc_channel_type_streamed_media_emit_stream_direction_changed (gpointer instance,
    guint arg_Stream_ID,
    guint arg_Stream_Direction,
    guint arg_Pending_Flags)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_STREAMED_MEDIA));
  g_signal_emit (instance,
      channel_type_streamed_media_signals[SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamDirectionChanged],
      0,
      arg_Stream_ID,
      arg_Stream_Direction,
      arg_Pending_Flags);
}

/**
 * tp_svc_channel_type_streamed_media_emit_stream_error:
 * @instance: The object implementing this interface
 * @arg_Stream_ID: guint  (FIXME, generate documentation)
 * @arg_Error_Code: guint  (FIXME, generate documentation)
 * @arg_Message: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * StreamError signal on interface org.freedesktop.Telepathy.Channel.Type.StreamedMedia.
 */
void
tp_svc_channel_type_streamed_media_emit_stream_error (gpointer instance,
    guint arg_Stream_ID,
    guint arg_Error_Code,
    const gchar *arg_Message)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_STREAMED_MEDIA));
  g_signal_emit (instance,
      channel_type_streamed_media_signals[SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamError],
      0,
      arg_Stream_ID,
      arg_Error_Code,
      arg_Message);
}

/**
 * tp_svc_channel_type_streamed_media_emit_stream_removed:
 * @instance: The object implementing this interface
 * @arg_Stream_ID: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * StreamRemoved signal on interface org.freedesktop.Telepathy.Channel.Type.StreamedMedia.
 */
void
tp_svc_channel_type_streamed_media_emit_stream_removed (gpointer instance,
    guint arg_Stream_ID)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_STREAMED_MEDIA));
  g_signal_emit (instance,
      channel_type_streamed_media_signals[SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamRemoved],
      0,
      arg_Stream_ID);
}

/**
 * tp_svc_channel_type_streamed_media_emit_stream_state_changed:
 * @instance: The object implementing this interface
 * @arg_Stream_ID: guint  (FIXME, generate documentation)
 * @arg_Stream_State: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * StreamStateChanged signal on interface org.freedesktop.Telepathy.Channel.Type.StreamedMedia.
 */
void
tp_svc_channel_type_streamed_media_emit_stream_state_changed (gpointer instance,
    guint arg_Stream_ID,
    guint arg_Stream_State)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_STREAMED_MEDIA));
  g_signal_emit (instance,
      channel_type_streamed_media_signals[SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamStateChanged],
      0,
      arg_Stream_ID,
      arg_Stream_State);
}

static inline void
tp_svc_channel_type_streamed_media_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  static TpDBusPropertiesMixinPropInfo properties[4] = {
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "b", 0, NULL, NULL }, /* InitialAudio */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "b", 0, NULL, NULL }, /* InitialVideo */
      { 0, TP_DBUS_PROPERTIES_MIXIN_FLAG_READ, "b", 0, NULL, NULL }, /* ImmutableStreams */
      { 0, 0, NULL, 0, NULL, NULL }
  };
  static TpDBusPropertiesMixinIfaceInfo interface =
      { 0, properties, NULL, NULL };

  dbus_g_object_type_install_info (tp_svc_channel_type_streamed_media_get_type (),
      &_tp_svc_channel_type_streamed_media_object_info);

  interface.dbus_interface = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Type.StreamedMedia");
  properties[0].name = g_quark_from_static_string ("InitialAudio");
  properties[0].type = G_TYPE_BOOLEAN;
  properties[1].name = g_quark_from_static_string ("InitialVideo");
  properties[1].type = G_TYPE_BOOLEAN;
  properties[2].name = g_quark_from_static_string ("ImmutableStreams");
  properties[2].type = G_TYPE_BOOLEAN;
  tp_svc_interface_set_dbus_properties_info (TP_TYPE_SVC_CHANNEL_TYPE_STREAMED_MEDIA, &interface);

  /**
   * TpSvcChannelTypeStreamedMedia::stream-added:
   * @arg_Stream_ID: guint  (FIXME, generate documentation)
   * @arg_Contact_Handle: guint  (FIXME, generate documentation)
   * @arg_Stream_Type: guint  (FIXME, generate documentation)
   *
   * The StreamAdded D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_streamed_media_signals[SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamAdded] =
  g_signal_new ("stream-added",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT_UINT,
      G_TYPE_NONE,
      3,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT);

  /**
   * TpSvcChannelTypeStreamedMedia::stream-direction-changed:
   * @arg_Stream_ID: guint  (FIXME, generate documentation)
   * @arg_Stream_Direction: guint  (FIXME, generate documentation)
   * @arg_Pending_Flags: guint  (FIXME, generate documentation)
   *
   * The StreamDirectionChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_streamed_media_signals[SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamDirectionChanged] =
  g_signal_new ("stream-direction-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT_UINT,
      G_TYPE_NONE,
      3,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT);

  /**
   * TpSvcChannelTypeStreamedMedia::stream-error:
   * @arg_Stream_ID: guint  (FIXME, generate documentation)
   * @arg_Error_Code: guint  (FIXME, generate documentation)
   * @arg_Message: const gchar * (FIXME, generate documentation)
   *
   * The StreamError D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_streamed_media_signals[SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamError] =
  g_signal_new ("stream-error",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT_STRING,
      G_TYPE_NONE,
      3,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING);

  /**
   * TpSvcChannelTypeStreamedMedia::stream-removed:
   * @arg_Stream_ID: guint  (FIXME, generate documentation)
   *
   * The StreamRemoved D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_streamed_media_signals[SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamRemoved] =
  g_signal_new ("stream-removed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__UINT,
      G_TYPE_NONE,
      1,
      G_TYPE_UINT);

  /**
   * TpSvcChannelTypeStreamedMedia::stream-state-changed:
   * @arg_Stream_ID: guint  (FIXME, generate documentation)
   * @arg_Stream_State: guint  (FIXME, generate documentation)
   *
   * The StreamStateChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_streamed_media_signals[SIGNAL_CHANNEL_TYPE_STREAMED_MEDIA_StreamStateChanged] =
  g_signal_new ("stream-state-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT,
      G_TYPE_NONE,
      2,
      G_TYPE_UINT,
      G_TYPE_UINT);

}
static void
tp_svc_channel_type_streamed_media_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_type_streamed_media_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_type_streamed_media_methods[] = {
  { (GCallback) tp_svc_channel_type_streamed_media_list_streams, g_cclosure_marshal_VOID__POINTER, 0 },
  { (GCallback) tp_svc_channel_type_streamed_media_remove_streams, _tp_marshal_VOID__BOXED_POINTER, 92 },
  { (GCallback) tp_svc_channel_type_streamed_media_request_stream_direction, _tp_marshal_VOID__UINT_UINT_POINTER, 175 },
  { (GCallback) tp_svc_channel_type_streamed_media_request_streams, _tp_marshal_VOID__UINT_BOXED_POINTER, 289 },
};

static const DBusGObjectInfo _tp_svc_channel_type_streamed_media_object_info = {
  0,
  _tp_svc_channel_type_streamed_media_methods,
  4,
"org.freedesktop.Telepathy.Channel.Type.StreamedMedia\0ListStreams\0A\0Streams\0O\0F\0N\0a(uuuuuu)\0\0org.freedesktop.Telepathy.Channel.Type.StreamedMedia\0RemoveStreams\0A\0Streams\0I\0au\0\0org.freedesktop.Telepathy.Channel.Type.StreamedMedia\0RequestStreamDirection\0A\0Stream_ID\0I\0u\0Stream_Direction\0I\0u\0\0org.freedesktop.Telepathy.Channel.Type.StreamedMedia\0RequestStreams\0A\0Contact_Handle\0I\0u\0Types\0I\0au\0Streams\0O\0F\0N\0a(uuuuuu)\0\0\0",
"org.freedesktop.Telepathy.Channel.Type.StreamedMedia\0StreamAdded\0org.freedesktop.Telepathy.Channel.Type.StreamedMedia\0StreamDirectionChanged\0org.freedesktop.Telepathy.Channel.Type.StreamedMedia\0StreamError\0org.freedesktop.Telepathy.Channel.Type.StreamedMedia\0StreamRemoved\0org.freedesktop.Telepathy.Channel.Type.StreamedMedia\0StreamStateChanged\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_type_text_object_info;

struct _TpSvcChannelTypeTextClass {
    GTypeInterface parent_class;
    tp_svc_channel_type_text_acknowledge_pending_messages_impl acknowledge_pending_messages;
    tp_svc_channel_type_text_get_message_types_impl get_message_types;
    tp_svc_channel_type_text_list_pending_messages_impl list_pending_messages;
    tp_svc_channel_type_text_send_impl send;
};

enum {
    SIGNAL_CHANNEL_TYPE_TEXT_LostMessage,
    SIGNAL_CHANNEL_TYPE_TEXT_Received,
    SIGNAL_CHANNEL_TYPE_TEXT_SendError,
    SIGNAL_CHANNEL_TYPE_TEXT_Sent,
    N_CHANNEL_TYPE_TEXT_SIGNALS
};
static guint channel_type_text_signals[N_CHANNEL_TYPE_TEXT_SIGNALS] = {0};

static void tp_svc_channel_type_text_base_init (gpointer klass);

GType
tp_svc_channel_type_text_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelTypeTextClass),
        tp_svc_channel_type_text_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelTypeText", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_type_text_acknowledge_pending_messages_impl:
 * @self: The object implementing this interface
 * @in_IDs: const GArray * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * AcknowledgePendingMessages on interface org.freedesktop.Telepathy.Channel.Type.Text.
 */
static void
tp_svc_channel_type_text_acknowledge_pending_messages (TpSvcChannelTypeText *self,
    const GArray *in_IDs,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_text_acknowledge_pending_messages_impl impl = (TP_SVC_CHANNEL_TYPE_TEXT_GET_CLASS (self)->acknowledge_pending_messages);

  if (impl != NULL)
    {
      (impl) (self,
        in_IDs,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_text_implement_acknowledge_pending_messages:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the AcknowledgePendingMessages D-Bus method
 *
 * Register an implementation for the AcknowledgePendingMessages method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_text_implement_acknowledge_pending_messages (TpSvcChannelTypeTextClass *klass, tp_svc_channel_type_text_acknowledge_pending_messages_impl impl)
{
  klass->acknowledge_pending_messages = impl;
}

/**
 * tp_svc_channel_type_text_get_message_types_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetMessageTypes on interface org.freedesktop.Telepathy.Channel.Type.Text.
 */
static void
tp_svc_channel_type_text_get_message_types (TpSvcChannelTypeText *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_text_get_message_types_impl impl = (TP_SVC_CHANNEL_TYPE_TEXT_GET_CLASS (self)->get_message_types);

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
 * tp_svc_channel_type_text_implement_get_message_types:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetMessageTypes D-Bus method
 *
 * Register an implementation for the GetMessageTypes method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_text_implement_get_message_types (TpSvcChannelTypeTextClass *klass, tp_svc_channel_type_text_get_message_types_impl impl)
{
  klass->get_message_types = impl;
}

/**
 * tp_svc_channel_type_text_list_pending_messages_impl:
 * @self: The object implementing this interface
 * @in_Clear: gboolean  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * ListPendingMessages on interface org.freedesktop.Telepathy.Channel.Type.Text.
 */
static void
tp_svc_channel_type_text_list_pending_messages (TpSvcChannelTypeText *self,
    gboolean in_Clear,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_text_list_pending_messages_impl impl = (TP_SVC_CHANNEL_TYPE_TEXT_GET_CLASS (self)->list_pending_messages);

  if (impl != NULL)
    {
      (impl) (self,
        in_Clear,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_text_implement_list_pending_messages:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the ListPendingMessages D-Bus method
 *
 * Register an implementation for the ListPendingMessages method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_text_implement_list_pending_messages (TpSvcChannelTypeTextClass *klass, tp_svc_channel_type_text_list_pending_messages_impl impl)
{
  klass->list_pending_messages = impl;
}

/**
 * tp_svc_channel_type_text_send_impl:
 * @self: The object implementing this interface
 * @in_Type: guint  (FIXME, generate documentation)
 * @in_Text: const gchar * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * Send on interface org.freedesktop.Telepathy.Channel.Type.Text.
 */
static void
tp_svc_channel_type_text_send (TpSvcChannelTypeText *self,
    guint in_Type,
    const gchar *in_Text,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_text_send_impl impl = (TP_SVC_CHANNEL_TYPE_TEXT_GET_CLASS (self)->send);

  if (impl != NULL)
    {
      (impl) (self,
        in_Type,
        in_Text,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_text_implement_send:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the Send D-Bus method
 *
 * Register an implementation for the Send method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_text_implement_send (TpSvcChannelTypeTextClass *klass, tp_svc_channel_type_text_send_impl impl)
{
  klass->send = impl;
}

/**
 * tp_svc_channel_type_text_emit_lost_message:
 * @instance: The object implementing this interface
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * LostMessage signal on interface org.freedesktop.Telepathy.Channel.Type.Text.
 */
void
tp_svc_channel_type_text_emit_lost_message (gpointer instance)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_TEXT));
  g_signal_emit (instance,
      channel_type_text_signals[SIGNAL_CHANNEL_TYPE_TEXT_LostMessage],
      0);
}

/**
 * tp_svc_channel_type_text_emit_received:
 * @instance: The object implementing this interface
 * @arg_ID: guint  (FIXME, generate documentation)
 * @arg_Timestamp: guint  (FIXME, generate documentation)
 * @arg_Sender: guint  (FIXME, generate documentation)
 * @arg_Type: guint  (FIXME, generate documentation)
 * @arg_Flags: guint  (FIXME, generate documentation)
 * @arg_Text: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * Received signal on interface org.freedesktop.Telepathy.Channel.Type.Text.
 */
void
tp_svc_channel_type_text_emit_received (gpointer instance,
    guint arg_ID,
    guint arg_Timestamp,
    guint arg_Sender,
    guint arg_Type,
    guint arg_Flags,
    const gchar *arg_Text)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_TEXT));
  g_signal_emit (instance,
      channel_type_text_signals[SIGNAL_CHANNEL_TYPE_TEXT_Received],
      0,
      arg_ID,
      arg_Timestamp,
      arg_Sender,
      arg_Type,
      arg_Flags,
      arg_Text);
}

/**
 * tp_svc_channel_type_text_emit_send_error:
 * @instance: The object implementing this interface
 * @arg_Error: guint  (FIXME, generate documentation)
 * @arg_Timestamp: guint  (FIXME, generate documentation)
 * @arg_Type: guint  (FIXME, generate documentation)
 * @arg_Text: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * SendError signal on interface org.freedesktop.Telepathy.Channel.Type.Text.
 */
void
tp_svc_channel_type_text_emit_send_error (gpointer instance,
    guint arg_Error,
    guint arg_Timestamp,
    guint arg_Type,
    const gchar *arg_Text)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_TEXT));
  g_signal_emit (instance,
      channel_type_text_signals[SIGNAL_CHANNEL_TYPE_TEXT_SendError],
      0,
      arg_Error,
      arg_Timestamp,
      arg_Type,
      arg_Text);
}

/**
 * tp_svc_channel_type_text_emit_sent:
 * @instance: The object implementing this interface
 * @arg_Timestamp: guint  (FIXME, generate documentation)
 * @arg_Type: guint  (FIXME, generate documentation)
 * @arg_Text: const gchar * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * Sent signal on interface org.freedesktop.Telepathy.Channel.Type.Text.
 */
void
tp_svc_channel_type_text_emit_sent (gpointer instance,
    guint arg_Timestamp,
    guint arg_Type,
    const gchar *arg_Text)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_TEXT));
  g_signal_emit (instance,
      channel_type_text_signals[SIGNAL_CHANNEL_TYPE_TEXT_Sent],
      0,
      arg_Timestamp,
      arg_Type,
      arg_Text);
}

static inline void
tp_svc_channel_type_text_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_channel_type_text_get_type (),
      &_tp_svc_channel_type_text_object_info);

  /**
   * TpSvcChannelTypeText::lost-message:
   *
   * The LostMessage D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_text_signals[SIGNAL_CHANNEL_TYPE_TEXT_LostMessage] =
  g_signal_new ("lost-message",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__VOID,
      G_TYPE_NONE,
      0);

  /**
   * TpSvcChannelTypeText::received:
   * @arg_ID: guint  (FIXME, generate documentation)
   * @arg_Timestamp: guint  (FIXME, generate documentation)
   * @arg_Sender: guint  (FIXME, generate documentation)
   * @arg_Type: guint  (FIXME, generate documentation)
   * @arg_Flags: guint  (FIXME, generate documentation)
   * @arg_Text: const gchar * (FIXME, generate documentation)
   *
   * The Received D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_text_signals[SIGNAL_CHANNEL_TYPE_TEXT_Received] =
  g_signal_new ("received",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT_UINT_UINT_UINT_STRING,
      G_TYPE_NONE,
      6,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING);

  /**
   * TpSvcChannelTypeText::send-error:
   * @arg_Error: guint  (FIXME, generate documentation)
   * @arg_Timestamp: guint  (FIXME, generate documentation)
   * @arg_Type: guint  (FIXME, generate documentation)
   * @arg_Text: const gchar * (FIXME, generate documentation)
   *
   * The SendError D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_text_signals[SIGNAL_CHANNEL_TYPE_TEXT_SendError] =
  g_signal_new ("send-error",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT_UINT_STRING,
      G_TYPE_NONE,
      4,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING);

  /**
   * TpSvcChannelTypeText::sent:
   * @arg_Timestamp: guint  (FIXME, generate documentation)
   * @arg_Type: guint  (FIXME, generate documentation)
   * @arg_Text: const gchar * (FIXME, generate documentation)
   *
   * The Sent D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_text_signals[SIGNAL_CHANNEL_TYPE_TEXT_Sent] =
  g_signal_new ("sent",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT_STRING,
      G_TYPE_NONE,
      3,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING);

}
static void
tp_svc_channel_type_text_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_type_text_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_type_text_methods[] = {
  { (GCallback) tp_svc_channel_type_text_acknowledge_pending_messages, _tp_marshal_VOID__BOXED_POINTER, 0 },
  { (GCallback) tp_svc_channel_type_text_get_message_types, g_cclosure_marshal_VOID__POINTER, 83 },
  { (GCallback) tp_svc_channel_type_text_list_pending_messages, _tp_marshal_VOID__BOOLEAN_POINTER, 171 },
  { (GCallback) tp_svc_channel_type_text_send, _tp_marshal_VOID__UINT_STRING_POINTER, 281 },
};

static const DBusGObjectInfo _tp_svc_channel_type_text_object_info = {
  0,
  _tp_svc_channel_type_text_methods,
  4,
"org.freedesktop.Telepathy.Channel.Type.Text\0AcknowledgePendingMessages\0A\0IDs\0I\0au\0\0org.freedesktop.Telepathy.Channel.Type.Text\0GetMessageTypes\0A\0Available_Types\0O\0F\0N\0au\0\0org.freedesktop.Telepathy.Channel.Type.Text\0ListPendingMessages\0A\0Clear\0I\0b\0Pending_Messages\0O\0F\0N\0a(uuuuus)\0\0org.freedesktop.Telepathy.Channel.Type.Text\0Send\0A\0Type\0I\0u\0Text\0I\0s\0\0\0",
"org.freedesktop.Telepathy.Channel.Type.Text\0LostMessage\0org.freedesktop.Telepathy.Channel.Type.Text\0Received\0org.freedesktop.Telepathy.Channel.Type.Text\0SendError\0org.freedesktop.Telepathy.Channel.Type.Text\0Sent\0\0",
"\0\0",
};

static const DBusGObjectInfo _tp_svc_channel_type_tubes_object_info;

struct _TpSvcChannelTypeTubesClass {
    GTypeInterface parent_class;
    tp_svc_channel_type_tubes_get_available_stream_tube_types_impl get_available_stream_tube_types;
    tp_svc_channel_type_tubes_get_available_tube_types_impl get_available_tube_types;
    tp_svc_channel_type_tubes_list_tubes_impl list_tubes;
    tp_svc_channel_type_tubes_offer_d_bus_tube_impl offer_d_bus_tube;
    tp_svc_channel_type_tubes_offer_stream_tube_impl offer_stream_tube;
    tp_svc_channel_type_tubes_accept_d_bus_tube_impl accept_d_bus_tube;
    tp_svc_channel_type_tubes_accept_stream_tube_impl accept_stream_tube;
    tp_svc_channel_type_tubes_close_tube_impl close_tube;
    tp_svc_channel_type_tubes_get_d_bus_tube_address_impl get_d_bus_tube_address;
    tp_svc_channel_type_tubes_get_d_bus_names_impl get_d_bus_names;
    tp_svc_channel_type_tubes_get_stream_tube_socket_address_impl get_stream_tube_socket_address;
};

enum {
    SIGNAL_CHANNEL_TYPE_TUBES_NewTube,
    SIGNAL_CHANNEL_TYPE_TUBES_TubeStateChanged,
    SIGNAL_CHANNEL_TYPE_TUBES_TubeClosed,
    SIGNAL_CHANNEL_TYPE_TUBES_DBusNamesChanged,
    SIGNAL_CHANNEL_TYPE_TUBES_StreamTubeNewConnection,
    N_CHANNEL_TYPE_TUBES_SIGNALS
};
static guint channel_type_tubes_signals[N_CHANNEL_TYPE_TUBES_SIGNALS] = {0};

static void tp_svc_channel_type_tubes_base_init (gpointer klass);

GType
tp_svc_channel_type_tubes_get_type (void)
{
  static GType type = 0;

  if (G_UNLIKELY (type == 0))
    {
      static const GTypeInfo info = {
        sizeof (TpSvcChannelTypeTubesClass),
        tp_svc_channel_type_tubes_base_init, /* base_init */
        NULL, /* base_finalize */
        NULL, /* class_init */
        NULL, /* class_finalize */
        NULL, /* class_data */
        0,
        0, /* n_preallocs */
        NULL /* instance_init */
      };

      type = g_type_register_static (G_TYPE_INTERFACE,
          "TpSvcChannelTypeTubes", &info, 0);
    }

  return type;
}

/**
 * tp_svc_channel_type_tubes_get_available_stream_tube_types_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetAvailableStreamTubeTypes on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
static void
tp_svc_channel_type_tubes_get_available_stream_tube_types (TpSvcChannelTypeTubes *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_tubes_get_available_stream_tube_types_impl impl = (TP_SVC_CHANNEL_TYPE_TUBES_GET_CLASS (self)->get_available_stream_tube_types);

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
 * tp_svc_channel_type_tubes_implement_get_available_stream_tube_types:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetAvailableStreamTubeTypes D-Bus method
 *
 * Register an implementation for the GetAvailableStreamTubeTypes method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_tubes_implement_get_available_stream_tube_types (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_get_available_stream_tube_types_impl impl)
{
  klass->get_available_stream_tube_types = impl;
}

/**
 * tp_svc_channel_type_tubes_get_available_tube_types_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetAvailableTubeTypes on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
static void
tp_svc_channel_type_tubes_get_available_tube_types (TpSvcChannelTypeTubes *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_tubes_get_available_tube_types_impl impl = (TP_SVC_CHANNEL_TYPE_TUBES_GET_CLASS (self)->get_available_tube_types);

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
 * tp_svc_channel_type_tubes_implement_get_available_tube_types:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetAvailableTubeTypes D-Bus method
 *
 * Register an implementation for the GetAvailableTubeTypes method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_tubes_implement_get_available_tube_types (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_get_available_tube_types_impl impl)
{
  klass->get_available_tube_types = impl;
}

/**
 * tp_svc_channel_type_tubes_list_tubes_impl:
 * @self: The object implementing this interface
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * ListTubes on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
static void
tp_svc_channel_type_tubes_list_tubes (TpSvcChannelTypeTubes *self,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_tubes_list_tubes_impl impl = (TP_SVC_CHANNEL_TYPE_TUBES_GET_CLASS (self)->list_tubes);

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
 * tp_svc_channel_type_tubes_implement_list_tubes:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the ListTubes D-Bus method
 *
 * Register an implementation for the ListTubes method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_tubes_implement_list_tubes (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_list_tubes_impl impl)
{
  klass->list_tubes = impl;
}

/**
 * tp_svc_channel_type_tubes_offer_d_bus_tube_impl:
 * @self: The object implementing this interface
 * @in_Service: const gchar * (FIXME, generate documentation)
 * @in_Parameters: GHashTable * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * OfferDBusTube on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
static void
tp_svc_channel_type_tubes_offer_d_bus_tube (TpSvcChannelTypeTubes *self,
    const gchar *in_Service,
    GHashTable *in_Parameters,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_tubes_offer_d_bus_tube_impl impl = (TP_SVC_CHANNEL_TYPE_TUBES_GET_CLASS (self)->offer_d_bus_tube);

  if (impl != NULL)
    {
      (impl) (self,
        in_Service,
        in_Parameters,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_tubes_implement_offer_d_bus_tube:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the OfferDBusTube D-Bus method
 *
 * Register an implementation for the OfferDBusTube method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_tubes_implement_offer_d_bus_tube (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_offer_d_bus_tube_impl impl)
{
  klass->offer_d_bus_tube = impl;
}

/**
 * tp_svc_channel_type_tubes_offer_stream_tube_impl:
 * @self: The object implementing this interface
 * @in_Service: const gchar * (FIXME, generate documentation)
 * @in_Parameters: GHashTable * (FIXME, generate documentation)
 * @in_Address_Type: guint  (FIXME, generate documentation)
 * @in_Address: const GValue * (FIXME, generate documentation)
 * @in_Access_Control: guint  (FIXME, generate documentation)
 * @in_Access_Control_Param: const GValue * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * OfferStreamTube on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
static void
tp_svc_channel_type_tubes_offer_stream_tube (TpSvcChannelTypeTubes *self,
    const gchar *in_Service,
    GHashTable *in_Parameters,
    guint in_Address_Type,
    const GValue *in_Address,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_tubes_offer_stream_tube_impl impl = (TP_SVC_CHANNEL_TYPE_TUBES_GET_CLASS (self)->offer_stream_tube);

  if (impl != NULL)
    {
      (impl) (self,
        in_Service,
        in_Parameters,
        in_Address_Type,
        in_Address,
        in_Access_Control,
        in_Access_Control_Param,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_tubes_implement_offer_stream_tube:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the OfferStreamTube D-Bus method
 *
 * Register an implementation for the OfferStreamTube method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_tubes_implement_offer_stream_tube (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_offer_stream_tube_impl impl)
{
  klass->offer_stream_tube = impl;
}

/**
 * tp_svc_channel_type_tubes_accept_d_bus_tube_impl:
 * @self: The object implementing this interface
 * @in_ID: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * AcceptDBusTube on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
static void
tp_svc_channel_type_tubes_accept_d_bus_tube (TpSvcChannelTypeTubes *self,
    guint in_ID,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_tubes_accept_d_bus_tube_impl impl = (TP_SVC_CHANNEL_TYPE_TUBES_GET_CLASS (self)->accept_d_bus_tube);

  if (impl != NULL)
    {
      (impl) (self,
        in_ID,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_tubes_implement_accept_d_bus_tube:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the AcceptDBusTube D-Bus method
 *
 * Register an implementation for the AcceptDBusTube method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_tubes_implement_accept_d_bus_tube (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_accept_d_bus_tube_impl impl)
{
  klass->accept_d_bus_tube = impl;
}

/**
 * tp_svc_channel_type_tubes_accept_stream_tube_impl:
 * @self: The object implementing this interface
 * @in_ID: guint  (FIXME, generate documentation)
 * @in_Address_Type: guint  (FIXME, generate documentation)
 * @in_Access_Control: guint  (FIXME, generate documentation)
 * @in_Access_Control_Param: const GValue * (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * AcceptStreamTube on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
static void
tp_svc_channel_type_tubes_accept_stream_tube (TpSvcChannelTypeTubes *self,
    guint in_ID,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_tubes_accept_stream_tube_impl impl = (TP_SVC_CHANNEL_TYPE_TUBES_GET_CLASS (self)->accept_stream_tube);

  if (impl != NULL)
    {
      (impl) (self,
        in_ID,
        in_Address_Type,
        in_Access_Control,
        in_Access_Control_Param,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_tubes_implement_accept_stream_tube:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the AcceptStreamTube D-Bus method
 *
 * Register an implementation for the AcceptStreamTube method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_tubes_implement_accept_stream_tube (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_accept_stream_tube_impl impl)
{
  klass->accept_stream_tube = impl;
}

/**
 * tp_svc_channel_type_tubes_close_tube_impl:
 * @self: The object implementing this interface
 * @in_ID: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * CloseTube on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
static void
tp_svc_channel_type_tubes_close_tube (TpSvcChannelTypeTubes *self,
    guint in_ID,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_tubes_close_tube_impl impl = (TP_SVC_CHANNEL_TYPE_TUBES_GET_CLASS (self)->close_tube);

  if (impl != NULL)
    {
      (impl) (self,
        in_ID,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_tubes_implement_close_tube:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the CloseTube D-Bus method
 *
 * Register an implementation for the CloseTube method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_tubes_implement_close_tube (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_close_tube_impl impl)
{
  klass->close_tube = impl;
}

/**
 * tp_svc_channel_type_tubes_get_d_bus_tube_address_impl:
 * @self: The object implementing this interface
 * @in_ID: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetDBusTubeAddress on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
static void
tp_svc_channel_type_tubes_get_d_bus_tube_address (TpSvcChannelTypeTubes *self,
    guint in_ID,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_tubes_get_d_bus_tube_address_impl impl = (TP_SVC_CHANNEL_TYPE_TUBES_GET_CLASS (self)->get_d_bus_tube_address);

  if (impl != NULL)
    {
      (impl) (self,
        in_ID,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_tubes_implement_get_d_bus_tube_address:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetDBusTubeAddress D-Bus method
 *
 * Register an implementation for the GetDBusTubeAddress method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_tubes_implement_get_d_bus_tube_address (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_get_d_bus_tube_address_impl impl)
{
  klass->get_d_bus_tube_address = impl;
}

/**
 * tp_svc_channel_type_tubes_get_d_bus_names_impl:
 * @self: The object implementing this interface
 * @in_ID: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetDBusNames on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
static void
tp_svc_channel_type_tubes_get_d_bus_names (TpSvcChannelTypeTubes *self,
    guint in_ID,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_tubes_get_d_bus_names_impl impl = (TP_SVC_CHANNEL_TYPE_TUBES_GET_CLASS (self)->get_d_bus_names);

  if (impl != NULL)
    {
      (impl) (self,
        in_ID,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_tubes_implement_get_d_bus_names:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetDBusNames D-Bus method
 *
 * Register an implementation for the GetDBusNames method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_tubes_implement_get_d_bus_names (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_get_d_bus_names_impl impl)
{
  klass->get_d_bus_names = impl;
}

/**
 * tp_svc_channel_type_tubes_get_stream_tube_socket_address_impl:
 * @self: The object implementing this interface
 * @in_ID: guint  (FIXME, generate documentation)
 * @context: Used to return values or throw an error
 *
 * The signature of an implementation of the D-Bus method
 * GetStreamTubeSocketAddress on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
static void
tp_svc_channel_type_tubes_get_stream_tube_socket_address (TpSvcChannelTypeTubes *self,
    guint in_ID,
    DBusGMethodInvocation *context)
{
  tp_svc_channel_type_tubes_get_stream_tube_socket_address_impl impl = (TP_SVC_CHANNEL_TYPE_TUBES_GET_CLASS (self)->get_stream_tube_socket_address);

  if (impl != NULL)
    {
      (impl) (self,
        in_ID,
        context);
    }
  else
    {
      tp_dbus_g_method_return_not_implemented (context);
    }
}

/**
 * tp_svc_channel_type_tubes_implement_get_stream_tube_socket_address:
 * @klass: A class whose instances implement this interface
 * @impl: A callback used to implement the GetStreamTubeSocketAddress D-Bus method
 *
 * Register an implementation for the GetStreamTubeSocketAddress method in the vtable
 * of an implementation of this interface. To be called from
 * the interface init function.
 */
void
tp_svc_channel_type_tubes_implement_get_stream_tube_socket_address (TpSvcChannelTypeTubesClass *klass, tp_svc_channel_type_tubes_get_stream_tube_socket_address_impl impl)
{
  klass->get_stream_tube_socket_address = impl;
}

/**
 * tp_svc_channel_type_tubes_emit_new_tube:
 * @instance: The object implementing this interface
 * @arg_ID: guint  (FIXME, generate documentation)
 * @arg_Initiator: guint  (FIXME, generate documentation)
 * @arg_Type: guint  (FIXME, generate documentation)
 * @arg_Service: const gchar * (FIXME, generate documentation)
 * @arg_Parameters: GHashTable * (FIXME, generate documentation)
 * @arg_State: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * NewTube signal on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
void
tp_svc_channel_type_tubes_emit_new_tube (gpointer instance,
    guint arg_ID,
    guint arg_Initiator,
    guint arg_Type,
    const gchar *arg_Service,
    GHashTable *arg_Parameters,
    guint arg_State)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_TUBES));
  g_signal_emit (instance,
      channel_type_tubes_signals[SIGNAL_CHANNEL_TYPE_TUBES_NewTube],
      0,
      arg_ID,
      arg_Initiator,
      arg_Type,
      arg_Service,
      arg_Parameters,
      arg_State);
}

/**
 * tp_svc_channel_type_tubes_emit_tube_state_changed:
 * @instance: The object implementing this interface
 * @arg_ID: guint  (FIXME, generate documentation)
 * @arg_State: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * TubeStateChanged signal on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
void
tp_svc_channel_type_tubes_emit_tube_state_changed (gpointer instance,
    guint arg_ID,
    guint arg_State)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_TUBES));
  g_signal_emit (instance,
      channel_type_tubes_signals[SIGNAL_CHANNEL_TYPE_TUBES_TubeStateChanged],
      0,
      arg_ID,
      arg_State);
}

/**
 * tp_svc_channel_type_tubes_emit_tube_closed:
 * @instance: The object implementing this interface
 * @arg_ID: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * TubeClosed signal on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
void
tp_svc_channel_type_tubes_emit_tube_closed (gpointer instance,
    guint arg_ID)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_TUBES));
  g_signal_emit (instance,
      channel_type_tubes_signals[SIGNAL_CHANNEL_TYPE_TUBES_TubeClosed],
      0,
      arg_ID);
}

/**
 * tp_svc_channel_type_tubes_emit_d_bus_names_changed:
 * @instance: The object implementing this interface
 * @arg_ID: guint  (FIXME, generate documentation)
 * @arg_Added: const GPtrArray * (FIXME, generate documentation)
 * @arg_Removed: const GArray * (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * DBusNamesChanged signal on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
void
tp_svc_channel_type_tubes_emit_d_bus_names_changed (gpointer instance,
    guint arg_ID,
    const GPtrArray *arg_Added,
    const GArray *arg_Removed)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_TUBES));
  g_signal_emit (instance,
      channel_type_tubes_signals[SIGNAL_CHANNEL_TYPE_TUBES_DBusNamesChanged],
      0,
      arg_ID,
      arg_Added,
      arg_Removed);
}

/**
 * tp_svc_channel_type_tubes_emit_stream_tube_new_connection:
 * @instance: The object implementing this interface
 * @arg_ID: guint  (FIXME, generate documentation)
 * @arg_Handle: guint  (FIXME, generate documentation)
 *
 * Type-safe wrapper around g_signal_emit to emit the
 * StreamTubeNewConnection signal on interface org.freedesktop.Telepathy.Channel.Type.Tubes.
 */
void
tp_svc_channel_type_tubes_emit_stream_tube_new_connection (gpointer instance,
    guint arg_ID,
    guint arg_Handle)
{
  g_assert (instance != NULL);
  g_assert (G_TYPE_CHECK_INSTANCE_TYPE (instance, TP_TYPE_SVC_CHANNEL_TYPE_TUBES));
  g_signal_emit (instance,
      channel_type_tubes_signals[SIGNAL_CHANNEL_TYPE_TUBES_StreamTubeNewConnection],
      0,
      arg_ID,
      arg_Handle);
}

static inline void
tp_svc_channel_type_tubes_base_init_once (gpointer klass G_GNUC_UNUSED)
{
  dbus_g_object_type_install_info (tp_svc_channel_type_tubes_get_type (),
      &_tp_svc_channel_type_tubes_object_info);

  /**
   * TpSvcChannelTypeTubes::new-tube:
   * @arg_ID: guint  (FIXME, generate documentation)
   * @arg_Initiator: guint  (FIXME, generate documentation)
   * @arg_Type: guint  (FIXME, generate documentation)
   * @arg_Service: const gchar * (FIXME, generate documentation)
   * @arg_Parameters: GHashTable * (FIXME, generate documentation)
   * @arg_State: guint  (FIXME, generate documentation)
   *
   * The NewTube D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_tubes_signals[SIGNAL_CHANNEL_TYPE_TUBES_NewTube] =
  g_signal_new ("new-tube",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT_UINT_STRING_BOXED_UINT,
      G_TYPE_NONE,
      6,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)),
      G_TYPE_UINT);

  /**
   * TpSvcChannelTypeTubes::tube-state-changed:
   * @arg_ID: guint  (FIXME, generate documentation)
   * @arg_State: guint  (FIXME, generate documentation)
   *
   * The TubeStateChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_tubes_signals[SIGNAL_CHANNEL_TYPE_TUBES_TubeStateChanged] =
  g_signal_new ("tube-state-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT,
      G_TYPE_NONE,
      2,
      G_TYPE_UINT,
      G_TYPE_UINT);

  /**
   * TpSvcChannelTypeTubes::tube-closed:
   * @arg_ID: guint  (FIXME, generate documentation)
   *
   * The TubeClosed D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_tubes_signals[SIGNAL_CHANNEL_TYPE_TUBES_TubeClosed] =
  g_signal_new ("tube-closed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      g_cclosure_marshal_VOID__UINT,
      G_TYPE_NONE,
      1,
      G_TYPE_UINT);

  /**
   * TpSvcChannelTypeTubes::d-bus-names-changed:
   * @arg_ID: guint  (FIXME, generate documentation)
   * @arg_Added: const GPtrArray * (FIXME, generate documentation)
   * @arg_Removed: const GArray * (FIXME, generate documentation)
   *
   * The DBusNamesChanged D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_tubes_signals[SIGNAL_CHANNEL_TYPE_TUBES_DBusNamesChanged] =
  g_signal_new ("d-bus-names-changed",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_BOXED_BOXED,
      G_TYPE_NONE,
      3,
      G_TYPE_UINT,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID)))),
      DBUS_TYPE_G_UINT_ARRAY);

  /**
   * TpSvcChannelTypeTubes::stream-tube-new-connection:
   * @arg_ID: guint  (FIXME, generate documentation)
   * @arg_Handle: guint  (FIXME, generate documentation)
   *
   * The StreamTubeNewConnection D-Bus signal is emitted whenever this GObject signal is.
   */
  channel_type_tubes_signals[SIGNAL_CHANNEL_TYPE_TUBES_StreamTubeNewConnection] =
  g_signal_new ("stream-tube-new-connection",
      G_OBJECT_CLASS_TYPE (klass),
      G_SIGNAL_RUN_LAST|G_SIGNAL_DETAILED,
      0,
      NULL, NULL,
      _tp_marshal_VOID__UINT_UINT,
      G_TYPE_NONE,
      2,
      G_TYPE_UINT,
      G_TYPE_UINT);

}
static void
tp_svc_channel_type_tubes_base_init (gpointer klass)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      initialized = TRUE;
      tp_svc_channel_type_tubes_base_init_once (klass);
    }
}
static const DBusGMethodInfo _tp_svc_channel_type_tubes_methods[] = {
  { (GCallback) tp_svc_channel_type_tubes_get_available_stream_tube_types, g_cclosure_marshal_VOID__POINTER, 0 },
  { (GCallback) tp_svc_channel_type_tubes_get_available_tube_types, g_cclosure_marshal_VOID__POINTER, 117 },
  { (GCallback) tp_svc_channel_type_tubes_list_tubes, g_cclosure_marshal_VOID__POINTER, 217 },
  { (GCallback) tp_svc_channel_type_tubes_offer_d_bus_tube, _tp_marshal_VOID__STRING_BOXED_POINTER, 301 },
  { (GCallback) tp_svc_channel_type_tubes_offer_stream_tube, _tp_marshal_VOID__STRING_BOXED_UINT_BOXED_UINT_BOXED_POINTER, 410 },
  { (GCallback) tp_svc_channel_type_tubes_accept_d_bus_tube, g_cclosure_marshal_VOID__UINT_POINTER, 594 },
  { (GCallback) tp_svc_channel_type_tubes_accept_stream_tube, _tp_marshal_VOID__UINT_UINT_UINT_BOXED_POINTER, 680 },
  { (GCallback) tp_svc_channel_type_tubes_close_tube, g_cclosure_marshal_VOID__UINT_POINTER, 829 },
  { (GCallback) tp_svc_channel_type_tubes_get_d_bus_tube_address, g_cclosure_marshal_VOID__UINT_POINTER, 894 },
  { (GCallback) tp_svc_channel_type_tubes_get_d_bus_names, g_cclosure_marshal_VOID__UINT_POINTER, 984 },
  { (GCallback) tp_svc_channel_type_tubes_get_stream_tube_socket_address, g_cclosure_marshal_VOID__UINT_POINTER, 1075 },
};

static const DBusGObjectInfo _tp_svc_channel_type_tubes_object_info = {
  0,
  _tp_svc_channel_type_tubes_methods,
  11,
"org.freedesktop.Telepathy.Channel.Type.Tubes\0GetAvailableStreamTubeTypes\0A\0Available_Stream_Tube_Types\0O\0F\0N\0a{uau}\0\0org.freedesktop.Telepathy.Channel.Type.Tubes\0GetAvailableTubeTypes\0A\0Available_Tube_Types\0O\0F\0N\0au\0\0org.freedesktop.Telepathy.Channel.Type.Tubes\0ListTubes\0A\0Tubes\0O\0F\0N\0a(uuusa{sv}u)\0\0org.freedesktop.Telepathy.Channel.Type.Tubes\0OfferDBusTube\0A\0Service\0I\0s\0Parameters\0I\0a{sv}\0Tube_ID\0O\0F\0N\0u\0\0org.freedesktop.Telepathy.Channel.Type.Tubes\0OfferStreamTube\0A\0Service\0I\0s\0Parameters\0I\0a{sv}\0Address_Type\0I\0u\0Address\0I\0v\0Access_Control\0I\0u\0Access_Control_Param\0I\0v\0Tube_ID\0O\0F\0N\0u\0\0org.freedesktop.Telepathy.Channel.Type.Tubes\0AcceptDBusTube\0A\0ID\0I\0u\0Address\0O\0F\0N\0s\0\0org.freedesktop.Telepathy.Channel.Type.Tubes\0AcceptStreamTube\0A\0ID\0I\0u\0Address_Type\0I\0u\0Access_Control\0I\0u\0Access_Control_Param\0I\0v\0Address\0O\0F\0N\0v\0\0org.freedesktop.Telepathy.Channel.Type.Tubes\0CloseTube\0A\0ID\0I\0u\0\0org.freedesktop.Telepathy.Channel.Type.Tubes\0GetDBusTubeAddress\0A\0ID\0I\0u\0Address\0O\0F\0N\0s\0\0org.freedesktop.Telepathy.Channel.Type.Tubes\0GetDBusNames\0A\0ID\0I\0u\0DBus_Names\0O\0F\0N\0a(us)\0\0org.freedesktop.Telepathy.Channel.Type.Tubes\0GetStreamTubeSocketAddress\0A\0ID\0I\0u\0Address_Type\0O\0F\0N\0u\0Address\0O\0F\0N\0v\0\0\0",
"org.freedesktop.Telepathy.Channel.Type.Tubes\0NewTube\0org.freedesktop.Telepathy.Channel.Type.Tubes\0TubeStateChanged\0org.freedesktop.Telepathy.Channel.Type.Tubes\0TubeClosed\0org.freedesktop.Telepathy.Channel.Type.Tubes\0DBusNamesChanged\0org.freedesktop.Telepathy.Channel.Type.Tubes\0StreamTubeNewConnection\0\0",
"\0\0",
};


