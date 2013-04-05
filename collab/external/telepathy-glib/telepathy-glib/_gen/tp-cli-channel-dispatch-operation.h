G_BEGIN_DECLS

typedef void (*tp_cli_channel_dispatch_operation_signal_callback_channel_lost) (TpChannelDispatchOperation *proxy,
    const gchar *arg_Channel,
    const gchar *arg_Error,
    const gchar *arg_Message,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_dispatch_operation_connect_to_channel_lost (TpChannelDispatchOperation *proxy,
    tp_cli_channel_dispatch_operation_signal_callback_channel_lost callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_dispatch_operation_signal_callback_finished) (TpChannelDispatchOperation *proxy,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_dispatch_operation_connect_to_finished (TpChannelDispatchOperation *proxy,
    tp_cli_channel_dispatch_operation_signal_callback_finished callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_dispatch_operation_callback_for_handle_with) (TpChannelDispatchOperation *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_dispatch_operation_call_handle_with (TpChannelDispatchOperation *proxy,
    gint timeout_ms,
    const gchar *in_Handler,
    tp_cli_channel_dispatch_operation_callback_for_handle_with callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);


typedef void (*tp_cli_channel_dispatch_operation_callback_for_claim) (TpChannelDispatchOperation *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_dispatch_operation_call_claim (TpChannelDispatchOperation *proxy,
    gint timeout_ms,
    tp_cli_channel_dispatch_operation_callback_for_claim callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);


G_END_DECLS
