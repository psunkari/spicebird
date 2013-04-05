G_BEGIN_DECLS

typedef void (*tp_cli_channel_request_signal_callback_failed) (TpChannelRequest *proxy,
    const gchar *arg_Error,
    const gchar *arg_Message,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_request_connect_to_failed (TpChannelRequest *proxy,
    tp_cli_channel_request_signal_callback_failed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_request_signal_callback_succeeded) (TpChannelRequest *proxy,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_request_connect_to_succeeded (TpChannelRequest *proxy,
    tp_cli_channel_request_signal_callback_succeeded callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_request_callback_for_proceed) (TpChannelRequest *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_request_call_proceed (TpChannelRequest *proxy,
    gint timeout_ms,
    tp_cli_channel_request_callback_for_proceed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);


typedef void (*tp_cli_channel_request_callback_for_cancel) (TpChannelRequest *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_request_call_cancel (TpChannelRequest *proxy,
    gint timeout_ms,
    tp_cli_channel_request_callback_for_cancel callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);


G_END_DECLS
