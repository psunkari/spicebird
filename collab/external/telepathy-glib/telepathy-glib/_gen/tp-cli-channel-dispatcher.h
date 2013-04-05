G_BEGIN_DECLS

typedef void (*tp_cli_channel_dispatcher_callback_for_create_channel) (TpChannelDispatcher *proxy,
    const gchar *out_Request,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_dispatcher_call_create_channel (TpChannelDispatcher *proxy,
    gint timeout_ms,
    const gchar *in_Account,
    GHashTable *in_Requested_Properties,
    gint64 in_User_Action_Time,
    const gchar *in_Preferred_Handler,
    tp_cli_channel_dispatcher_callback_for_create_channel callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);


typedef void (*tp_cli_channel_dispatcher_callback_for_ensure_channel) (TpChannelDispatcher *proxy,
    const gchar *out_Request,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_dispatcher_call_ensure_channel (TpChannelDispatcher *proxy,
    gint timeout_ms,
    const gchar *in_Account,
    GHashTable *in_Requested_Properties,
    gint64 in_User_Action_Time,
    const gchar *in_Preferred_Handler,
    tp_cli_channel_dispatcher_callback_for_ensure_channel callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);


typedef void (*tp_cli_channel_dispatcher_interface_operation_list_signal_callback_new_dispatch_operation) (TpChannelDispatcher *proxy,
    const gchar *arg_Dispatch_Operation,
    GHashTable *arg_Properties,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_dispatcher_interface_operation_list_connect_to_new_dispatch_operation (TpChannelDispatcher *proxy,
    tp_cli_channel_dispatcher_interface_operation_list_signal_callback_new_dispatch_operation callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_dispatcher_interface_operation_list_signal_callback_dispatch_operation_finished) (TpChannelDispatcher *proxy,
    const gchar *arg_Dispatch_Operation,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_dispatcher_interface_operation_list_connect_to_dispatch_operation_finished (TpChannelDispatcher *proxy,
    tp_cli_channel_dispatcher_interface_operation_list_signal_callback_dispatch_operation_finished callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

G_END_DECLS
