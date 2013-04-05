G_BEGIN_DECLS

typedef void (*tp_cli_channel_signal_callback_closed) (TpChannel *proxy,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_connect_to_closed (TpChannel *proxy,
    tp_cli_channel_signal_callback_closed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_callback_for_close) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_call_close (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_callback_for_close callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_run_close (TpChannel *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_callback_for_get_channel_type) (TpChannel *proxy,
    const gchar *out_Channel_Type,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_call_get_channel_type (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_callback_for_get_channel_type callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_run_get_channel_type (TpChannel *proxy,
    gint timeout_ms,
    gchar **out_Channel_Type,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_callback_for_get_handle) (TpChannel *proxy,
    guint out_Target_Handle_Type,
    guint out_Target_Handle,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_call_get_handle (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_callback_for_get_handle callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_run_get_handle (TpChannel *proxy,
    gint timeout_ms,
    guint *out_Target_Handle_Type,
    guint *out_Target_Handle,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_callback_for_get_interfaces) (TpChannel *proxy,
    const gchar **out_Interfaces,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_call_get_interfaces (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_callback_for_get_interfaces callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_run_get_interfaces (TpChannel *proxy,
    gint timeout_ms,
    gchar ***out_Interfaces,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_call_state_signal_callback_call_state_changed) (TpChannel *proxy,
    guint arg_Contact,
    guint arg_State,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_interface_call_state_connect_to_call_state_changed (TpChannel *proxy,
    tp_cli_channel_interface_call_state_signal_callback_call_state_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_interface_call_state_callback_for_get_call_states) (TpChannel *proxy,
    GHashTable *out_States,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_call_state_call_get_call_states (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_call_state_callback_for_get_call_states callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_call_state_run_get_call_states (TpChannel *proxy,
    gint timeout_ms,
    GHashTable **out_States,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_chat_state_signal_callback_chat_state_changed) (TpChannel *proxy,
    guint arg_Contact,
    guint arg_State,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_interface_chat_state_connect_to_chat_state_changed (TpChannel *proxy,
    tp_cli_channel_interface_chat_state_signal_callback_chat_state_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_interface_chat_state_callback_for_set_chat_state) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_chat_state_call_set_chat_state (TpChannel *proxy,
    gint timeout_ms,
    guint in_State,
    tp_cli_channel_interface_chat_state_callback_for_set_chat_state callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_chat_state_run_set_chat_state (TpChannel *proxy,
    gint timeout_ms,
    guint in_State,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_dtmf_callback_for_start_tone) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_dtmf_call_start_tone (TpChannel *proxy,
    gint timeout_ms,
    guint in_Stream_ID,
    guchar in_Event,
    tp_cli_channel_interface_dtmf_callback_for_start_tone callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_dtmf_run_start_tone (TpChannel *proxy,
    gint timeout_ms,
    guint in_Stream_ID,
    guchar in_Event,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_dtmf_callback_for_stop_tone) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_dtmf_call_stop_tone (TpChannel *proxy,
    gint timeout_ms,
    guint in_Stream_ID,
    tp_cli_channel_interface_dtmf_callback_for_stop_tone callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_dtmf_run_stop_tone (TpChannel *proxy,
    gint timeout_ms,
    guint in_Stream_ID,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_destroyable_callback_for_destroy) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_destroyable_call_destroy (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_destroyable_callback_for_destroy callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_destroyable_run_destroy (TpChannel *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_group_signal_callback_handle_owners_changed) (TpChannel *proxy,
    GHashTable *arg_Added,
    const GArray *arg_Removed,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_interface_group_connect_to_handle_owners_changed (TpChannel *proxy,
    tp_cli_channel_interface_group_signal_callback_handle_owners_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_interface_group_signal_callback_self_handle_changed) (TpChannel *proxy,
    guint arg_Self_Handle,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_interface_group_connect_to_self_handle_changed (TpChannel *proxy,
    tp_cli_channel_interface_group_signal_callback_self_handle_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_interface_group_signal_callback_group_flags_changed) (TpChannel *proxy,
    guint arg_Added,
    guint arg_Removed,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_interface_group_connect_to_group_flags_changed (TpChannel *proxy,
    tp_cli_channel_interface_group_signal_callback_group_flags_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_interface_group_signal_callback_members_changed) (TpChannel *proxy,
    const gchar *arg_Message,
    const GArray *arg_Added,
    const GArray *arg_Removed,
    const GArray *arg_Local_Pending,
    const GArray *arg_Remote_Pending,
    guint arg_Actor,
    guint arg_Reason,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_interface_group_connect_to_members_changed (TpChannel *proxy,
    tp_cli_channel_interface_group_signal_callback_members_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_interface_group_signal_callback_members_changed_detailed) (TpChannel *proxy,
    const GArray *arg_Added,
    const GArray *arg_Removed,
    const GArray *arg_Local_Pending,
    const GArray *arg_Remote_Pending,
    GHashTable *arg_Details,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_interface_group_connect_to_members_changed_detailed (TpChannel *proxy,
    tp_cli_channel_interface_group_signal_callback_members_changed_detailed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_interface_group_callback_for_add_members) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_group_call_add_members (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    const gchar *in_Message,
    tp_cli_channel_interface_group_callback_for_add_members callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_group_run_add_members (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    const gchar *in_Message,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_group_callback_for_get_all_members) (TpChannel *proxy,
    const GArray *out_Members,
    const GArray *out_Local_Pending,
    const GArray *out_Remote_Pending,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_group_call_get_all_members (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_group_callback_for_get_all_members callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_group_run_get_all_members (TpChannel *proxy,
    gint timeout_ms,
    GArray **out_Members,
    GArray **out_Local_Pending,
    GArray **out_Remote_Pending,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_group_callback_for_get_group_flags) (TpChannel *proxy,
    guint out_Group_Flags,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_group_call_get_group_flags (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_group_callback_for_get_group_flags callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_group_run_get_group_flags (TpChannel *proxy,
    gint timeout_ms,
    guint *out_Group_Flags,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_group_callback_for_get_handle_owners) (TpChannel *proxy,
    const GArray *out_Owners,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_group_call_get_handle_owners (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Handles,
    tp_cli_channel_interface_group_callback_for_get_handle_owners callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_group_run_get_handle_owners (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Handles,
    GArray **out_Owners,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_group_callback_for_get_local_pending_members) (TpChannel *proxy,
    const GArray *out_Handles,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_group_call_get_local_pending_members (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_group_callback_for_get_local_pending_members callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_group_run_get_local_pending_members (TpChannel *proxy,
    gint timeout_ms,
    GArray **out_Handles,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_group_callback_for_get_local_pending_members_with_info) (TpChannel *proxy,
    const GPtrArray *out_Info,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_group_call_get_local_pending_members_with_info (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_group_callback_for_get_local_pending_members_with_info callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_group_run_get_local_pending_members_with_info (TpChannel *proxy,
    gint timeout_ms,
    GPtrArray **out_Info,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_group_callback_for_get_members) (TpChannel *proxy,
    const GArray *out_Handles,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_group_call_get_members (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_group_callback_for_get_members callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_group_run_get_members (TpChannel *proxy,
    gint timeout_ms,
    GArray **out_Handles,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_group_callback_for_get_remote_pending_members) (TpChannel *proxy,
    const GArray *out_Handles,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_group_call_get_remote_pending_members (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_group_callback_for_get_remote_pending_members callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_group_run_get_remote_pending_members (TpChannel *proxy,
    gint timeout_ms,
    GArray **out_Handles,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_group_callback_for_get_self_handle) (TpChannel *proxy,
    guint out_Self_Handle,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_group_call_get_self_handle (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_group_callback_for_get_self_handle callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_group_run_get_self_handle (TpChannel *proxy,
    gint timeout_ms,
    guint *out_Self_Handle,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_group_callback_for_remove_members) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_group_call_remove_members (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    const gchar *in_Message,
    tp_cli_channel_interface_group_callback_for_remove_members callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_group_run_remove_members (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    const gchar *in_Message,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_group_callback_for_remove_members_with_reason) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_group_call_remove_members_with_reason (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    const gchar *in_Message,
    guint in_Reason,
    tp_cli_channel_interface_group_callback_for_remove_members_with_reason callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_group_run_remove_members_with_reason (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    const gchar *in_Message,
    guint in_Reason,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_hold_signal_callback_hold_state_changed) (TpChannel *proxy,
    guint arg_HoldState,
    guint arg_Reason,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_interface_hold_connect_to_hold_state_changed (TpChannel *proxy,
    tp_cli_channel_interface_hold_signal_callback_hold_state_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_interface_hold_callback_for_get_hold_state) (TpChannel *proxy,
    guint out_HoldState,
    guint out_Reason,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_hold_call_get_hold_state (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_hold_callback_for_get_hold_state callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_hold_run_get_hold_state (TpChannel *proxy,
    gint timeout_ms,
    guint *out_HoldState,
    guint *out_Reason,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_hold_callback_for_request_hold) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_hold_call_request_hold (TpChannel *proxy,
    gint timeout_ms,
    gboolean in_Hold,
    tp_cli_channel_interface_hold_callback_for_request_hold callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_hold_run_request_hold (TpChannel *proxy,
    gint timeout_ms,
    gboolean in_Hold,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_media_signalling_signal_callback_new_session_handler) (TpChannel *proxy,
    const gchar *arg_Session_Handler,
    const gchar *arg_Session_Type,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_interface_media_signalling_connect_to_new_session_handler (TpChannel *proxy,
    tp_cli_channel_interface_media_signalling_signal_callback_new_session_handler callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_interface_media_signalling_callback_for_get_session_handlers) (TpChannel *proxy,
    const GPtrArray *out_Session_Handlers,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_media_signalling_call_get_session_handlers (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_media_signalling_callback_for_get_session_handlers callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_media_signalling_run_get_session_handlers (TpChannel *proxy,
    gint timeout_ms,
    GPtrArray **out_Session_Handlers,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_messages_signal_callback_message_sent) (TpChannel *proxy,
    const GPtrArray *arg_Content,
    guint arg_Flags,
    const gchar *arg_Message_Token,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_interface_messages_connect_to_message_sent (TpChannel *proxy,
    tp_cli_channel_interface_messages_signal_callback_message_sent callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_interface_messages_signal_callback_pending_messages_removed) (TpChannel *proxy,
    const GArray *arg_Message_IDs,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_interface_messages_connect_to_pending_messages_removed (TpChannel *proxy,
    tp_cli_channel_interface_messages_signal_callback_pending_messages_removed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_interface_messages_signal_callback_message_received) (TpChannel *proxy,
    const GPtrArray *arg_Message,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_interface_messages_connect_to_message_received (TpChannel *proxy,
    tp_cli_channel_interface_messages_signal_callback_message_received callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_interface_messages_callback_for_send_message) (TpChannel *proxy,
    const gchar *out_Token,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_messages_call_send_message (TpChannel *proxy,
    gint timeout_ms,
    const GPtrArray *in_Message,
    guint in_Flags,
    tp_cli_channel_interface_messages_callback_for_send_message callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_messages_run_send_message (TpChannel *proxy,
    gint timeout_ms,
    const GPtrArray *in_Message,
    guint in_Flags,
    gchar **out_Token,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_messages_callback_for_get_pending_message_content) (TpChannel *proxy,
    GHashTable *out_Content,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_messages_call_get_pending_message_content (TpChannel *proxy,
    gint timeout_ms,
    guint in_Message_ID,
    const GArray *in_Parts,
    tp_cli_channel_interface_messages_callback_for_get_pending_message_content callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_messages_run_get_pending_message_content (TpChannel *proxy,
    gint timeout_ms,
    guint in_Message_ID,
    const GArray *in_Parts,
    GHashTable **out_Content,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_password_signal_callback_password_flags_changed) (TpChannel *proxy,
    guint arg_Added,
    guint arg_Removed,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_interface_password_connect_to_password_flags_changed (TpChannel *proxy,
    tp_cli_channel_interface_password_signal_callback_password_flags_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_interface_password_callback_for_get_password_flags) (TpChannel *proxy,
    guint out_Password_Flags,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_password_call_get_password_flags (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_password_callback_for_get_password_flags callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_password_run_get_password_flags (TpChannel *proxy,
    gint timeout_ms,
    guint *out_Password_Flags,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_password_callback_for_provide_password) (TpChannel *proxy,
    gboolean out_Correct,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_interface_password_call_provide_password (TpChannel *proxy,
    gint timeout_ms,
    const gchar *in_Password,
    tp_cli_channel_interface_password_callback_for_provide_password callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_interface_password_run_provide_password (TpChannel *proxy,
    gint timeout_ms,
    const gchar *in_Password,
    gboolean *out_Correct,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_interface_tube_signal_callback_tube_channel_state_changed) (TpChannel *proxy,
    guint arg_State,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_interface_tube_connect_to_tube_channel_state_changed (TpChannel *proxy,
    tp_cli_channel_interface_tube_signal_callback_tube_channel_state_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_dbus_tube_signal_callback_dbus_names_changed) (TpChannel *proxy,
    GHashTable *arg_Added,
    const GArray *arg_Removed,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_dbus_tube_connect_to_dbus_names_changed (TpChannel *proxy,
    tp_cli_channel_type_dbus_tube_signal_callback_dbus_names_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_dbus_tube_callback_for_offer) (TpChannel *proxy,
    const gchar *out_address,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_dbus_tube_call_offer (TpChannel *proxy,
    gint timeout_ms,
    GHashTable *in_parameters,
    guint in_access_control,
    tp_cli_channel_type_dbus_tube_callback_for_offer callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_dbus_tube_run_offer (TpChannel *proxy,
    gint timeout_ms,
    GHashTable *in_parameters,
    guint in_access_control,
    gchar **out_address,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_dbus_tube_callback_for_accept) (TpChannel *proxy,
    const gchar *out_address,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_dbus_tube_call_accept (TpChannel *proxy,
    gint timeout_ms,
    guint in_access_control,
    tp_cli_channel_type_dbus_tube_callback_for_accept callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_dbus_tube_run_accept (TpChannel *proxy,
    gint timeout_ms,
    guint in_access_control,
    gchar **out_address,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_file_transfer_signal_callback_file_transfer_state_changed) (TpChannel *proxy,
    guint arg_State,
    guint arg_Reason,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_file_transfer_connect_to_file_transfer_state_changed (TpChannel *proxy,
    tp_cli_channel_type_file_transfer_signal_callback_file_transfer_state_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_file_transfer_signal_callback_transferred_bytes_changed) (TpChannel *proxy,
    guint64 arg_Count,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_file_transfer_connect_to_transferred_bytes_changed (TpChannel *proxy,
    tp_cli_channel_type_file_transfer_signal_callback_transferred_bytes_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_file_transfer_signal_callback_initial_offset_defined) (TpChannel *proxy,
    guint64 arg_InitialOffset,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_file_transfer_connect_to_initial_offset_defined (TpChannel *proxy,
    tp_cli_channel_type_file_transfer_signal_callback_initial_offset_defined callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_file_transfer_callback_for_accept_file) (TpChannel *proxy,
    const GValue *out_Address,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_file_transfer_call_accept_file (TpChannel *proxy,
    gint timeout_ms,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    guint64 in_Offset,
    tp_cli_channel_type_file_transfer_callback_for_accept_file callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_file_transfer_run_accept_file (TpChannel *proxy,
    gint timeout_ms,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    guint64 in_Offset,
    GValue **out_Address,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_file_transfer_callback_for_provide_file) (TpChannel *proxy,
    const GValue *out_Address,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_file_transfer_call_provide_file (TpChannel *proxy,
    gint timeout_ms,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    tp_cli_channel_type_file_transfer_callback_for_provide_file callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_file_transfer_run_provide_file (TpChannel *proxy,
    gint timeout_ms,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    GValue **out_Address,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_room_list_signal_callback_got_rooms) (TpChannel *proxy,
    const GPtrArray *arg_Rooms,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_room_list_connect_to_got_rooms (TpChannel *proxy,
    tp_cli_channel_type_room_list_signal_callback_got_rooms callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_room_list_signal_callback_listing_rooms) (TpChannel *proxy,
    gboolean arg_Listing,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_room_list_connect_to_listing_rooms (TpChannel *proxy,
    tp_cli_channel_type_room_list_signal_callback_listing_rooms callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_room_list_callback_for_get_listing_rooms) (TpChannel *proxy,
    gboolean out_In_Progress,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_room_list_call_get_listing_rooms (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_room_list_callback_for_get_listing_rooms callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_room_list_run_get_listing_rooms (TpChannel *proxy,
    gint timeout_ms,
    gboolean *out_In_Progress,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_room_list_callback_for_list_rooms) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_room_list_call_list_rooms (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_room_list_callback_for_list_rooms callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_room_list_run_list_rooms (TpChannel *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_room_list_callback_for_stop_listing) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_room_list_call_stop_listing (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_room_list_callback_for_stop_listing callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_room_list_run_stop_listing (TpChannel *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_stream_tube_signal_callback_new_remote_connection) (TpChannel *proxy,
    guint arg_Handle,
    const GValue *arg_Connection_Param,
    guint arg_Connection_ID,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_stream_tube_connect_to_new_remote_connection (TpChannel *proxy,
    tp_cli_channel_type_stream_tube_signal_callback_new_remote_connection callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_stream_tube_signal_callback_new_local_connection) (TpChannel *proxy,
    guint arg_Connection_ID,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_stream_tube_connect_to_new_local_connection (TpChannel *proxy,
    tp_cli_channel_type_stream_tube_signal_callback_new_local_connection callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_stream_tube_signal_callback_connection_closed) (TpChannel *proxy,
    guint arg_Connection_ID,
    const gchar *arg_Error,
    const gchar *arg_Message,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_stream_tube_connect_to_connection_closed (TpChannel *proxy,
    tp_cli_channel_type_stream_tube_signal_callback_connection_closed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_stream_tube_callback_for_offer) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_stream_tube_call_offer (TpChannel *proxy,
    gint timeout_ms,
    guint in_address_type,
    const GValue *in_address,
    guint in_access_control,
    GHashTable *in_parameters,
    tp_cli_channel_type_stream_tube_callback_for_offer callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_stream_tube_run_offer (TpChannel *proxy,
    gint timeout_ms,
    guint in_address_type,
    const GValue *in_address,
    guint in_access_control,
    GHashTable *in_parameters,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_stream_tube_callback_for_accept) (TpChannel *proxy,
    const GValue *out_address,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_stream_tube_call_accept (TpChannel *proxy,
    gint timeout_ms,
    guint in_address_type,
    guint in_access_control,
    const GValue *in_access_control_param,
    tp_cli_channel_type_stream_tube_callback_for_accept callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_stream_tube_run_accept (TpChannel *proxy,
    gint timeout_ms,
    guint in_address_type,
    guint in_access_control,
    const GValue *in_access_control_param,
    GValue **out_address,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_streamed_media_signal_callback_stream_added) (TpChannel *proxy,
    guint arg_Stream_ID,
    guint arg_Contact_Handle,
    guint arg_Stream_Type,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_streamed_media_connect_to_stream_added (TpChannel *proxy,
    tp_cli_channel_type_streamed_media_signal_callback_stream_added callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_streamed_media_signal_callback_stream_direction_changed) (TpChannel *proxy,
    guint arg_Stream_ID,
    guint arg_Stream_Direction,
    guint arg_Pending_Flags,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_streamed_media_connect_to_stream_direction_changed (TpChannel *proxy,
    tp_cli_channel_type_streamed_media_signal_callback_stream_direction_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_streamed_media_signal_callback_stream_error) (TpChannel *proxy,
    guint arg_Stream_ID,
    guint arg_Error_Code,
    const gchar *arg_Message,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_streamed_media_connect_to_stream_error (TpChannel *proxy,
    tp_cli_channel_type_streamed_media_signal_callback_stream_error callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_streamed_media_signal_callback_stream_removed) (TpChannel *proxy,
    guint arg_Stream_ID,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_streamed_media_connect_to_stream_removed (TpChannel *proxy,
    tp_cli_channel_type_streamed_media_signal_callback_stream_removed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_streamed_media_signal_callback_stream_state_changed) (TpChannel *proxy,
    guint arg_Stream_ID,
    guint arg_Stream_State,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_streamed_media_connect_to_stream_state_changed (TpChannel *proxy,
    tp_cli_channel_type_streamed_media_signal_callback_stream_state_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_streamed_media_callback_for_list_streams) (TpChannel *proxy,
    const GPtrArray *out_Streams,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_streamed_media_call_list_streams (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_streamed_media_callback_for_list_streams callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_streamed_media_run_list_streams (TpChannel *proxy,
    gint timeout_ms,
    GPtrArray **out_Streams,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_streamed_media_callback_for_remove_streams) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_streamed_media_call_remove_streams (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Streams,
    tp_cli_channel_type_streamed_media_callback_for_remove_streams callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_streamed_media_run_remove_streams (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Streams,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_streamed_media_callback_for_request_stream_direction) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_streamed_media_call_request_stream_direction (TpChannel *proxy,
    gint timeout_ms,
    guint in_Stream_ID,
    guint in_Stream_Direction,
    tp_cli_channel_type_streamed_media_callback_for_request_stream_direction callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_streamed_media_run_request_stream_direction (TpChannel *proxy,
    gint timeout_ms,
    guint in_Stream_ID,
    guint in_Stream_Direction,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_streamed_media_callback_for_request_streams) (TpChannel *proxy,
    const GPtrArray *out_Streams,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_streamed_media_call_request_streams (TpChannel *proxy,
    gint timeout_ms,
    guint in_Contact_Handle,
    const GArray *in_Types,
    tp_cli_channel_type_streamed_media_callback_for_request_streams callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_streamed_media_run_request_streams (TpChannel *proxy,
    gint timeout_ms,
    guint in_Contact_Handle,
    const GArray *in_Types,
    GPtrArray **out_Streams,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_text_signal_callback_lost_message) (TpChannel *proxy,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_text_connect_to_lost_message (TpChannel *proxy,
    tp_cli_channel_type_text_signal_callback_lost_message callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_text_signal_callback_received) (TpChannel *proxy,
    guint arg_ID,
    guint arg_Timestamp,
    guint arg_Sender,
    guint arg_Type,
    guint arg_Flags,
    const gchar *arg_Text,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_text_connect_to_received (TpChannel *proxy,
    tp_cli_channel_type_text_signal_callback_received callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_text_signal_callback_send_error) (TpChannel *proxy,
    guint arg_Error,
    guint arg_Timestamp,
    guint arg_Type,
    const gchar *arg_Text,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_text_connect_to_send_error (TpChannel *proxy,
    tp_cli_channel_type_text_signal_callback_send_error callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_text_signal_callback_sent) (TpChannel *proxy,
    guint arg_Timestamp,
    guint arg_Type,
    const gchar *arg_Text,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_text_connect_to_sent (TpChannel *proxy,
    tp_cli_channel_type_text_signal_callback_sent callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_text_callback_for_acknowledge_pending_messages) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_text_call_acknowledge_pending_messages (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_IDs,
    tp_cli_channel_type_text_callback_for_acknowledge_pending_messages callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_text_run_acknowledge_pending_messages (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_IDs,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_text_callback_for_get_message_types) (TpChannel *proxy,
    const GArray *out_Available_Types,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_text_call_get_message_types (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_text_callback_for_get_message_types callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_text_run_get_message_types (TpChannel *proxy,
    gint timeout_ms,
    GArray **out_Available_Types,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_text_callback_for_list_pending_messages) (TpChannel *proxy,
    const GPtrArray *out_Pending_Messages,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_text_call_list_pending_messages (TpChannel *proxy,
    gint timeout_ms,
    gboolean in_Clear,
    tp_cli_channel_type_text_callback_for_list_pending_messages callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_text_run_list_pending_messages (TpChannel *proxy,
    gint timeout_ms,
    gboolean in_Clear,
    GPtrArray **out_Pending_Messages,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_text_callback_for_send) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_text_call_send (TpChannel *proxy,
    gint timeout_ms,
    guint in_Type,
    const gchar *in_Text,
    tp_cli_channel_type_text_callback_for_send callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_text_run_send (TpChannel *proxy,
    gint timeout_ms,
    guint in_Type,
    const gchar *in_Text,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_tubes_signal_callback_new_tube) (TpChannel *proxy,
    guint arg_ID,
    guint arg_Initiator,
    guint arg_Type,
    const gchar *arg_Service,
    GHashTable *arg_Parameters,
    guint arg_State,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_tubes_connect_to_new_tube (TpChannel *proxy,
    tp_cli_channel_type_tubes_signal_callback_new_tube callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_tubes_signal_callback_tube_state_changed) (TpChannel *proxy,
    guint arg_ID,
    guint arg_State,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_tubes_connect_to_tube_state_changed (TpChannel *proxy,
    tp_cli_channel_type_tubes_signal_callback_tube_state_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_tubes_signal_callback_tube_closed) (TpChannel *proxy,
    guint arg_ID,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_tubes_connect_to_tube_closed (TpChannel *proxy,
    tp_cli_channel_type_tubes_signal_callback_tube_closed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_tubes_signal_callback_d_bus_names_changed) (TpChannel *proxy,
    guint arg_ID,
    const GPtrArray *arg_Added,
    const GArray *arg_Removed,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_tubes_connect_to_d_bus_names_changed (TpChannel *proxy,
    tp_cli_channel_type_tubes_signal_callback_d_bus_names_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_tubes_signal_callback_stream_tube_new_connection) (TpChannel *proxy,
    guint arg_ID,
    guint arg_Handle,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_channel_type_tubes_connect_to_stream_tube_new_connection (TpChannel *proxy,
    tp_cli_channel_type_tubes_signal_callback_stream_tube_new_connection callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_channel_type_tubes_callback_for_get_available_stream_tube_types) (TpChannel *proxy,
    GHashTable *out_Available_Stream_Tube_Types,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_tubes_call_get_available_stream_tube_types (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_tubes_callback_for_get_available_stream_tube_types callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_tubes_run_get_available_stream_tube_types (TpChannel *proxy,
    gint timeout_ms,
    GHashTable **out_Available_Stream_Tube_Types,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_tubes_callback_for_get_available_tube_types) (TpChannel *proxy,
    const GArray *out_Available_Tube_Types,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_tubes_call_get_available_tube_types (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_tubes_callback_for_get_available_tube_types callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_tubes_run_get_available_tube_types (TpChannel *proxy,
    gint timeout_ms,
    GArray **out_Available_Tube_Types,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_tubes_callback_for_list_tubes) (TpChannel *proxy,
    const GPtrArray *out_Tubes,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_tubes_call_list_tubes (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_tubes_callback_for_list_tubes callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_tubes_run_list_tubes (TpChannel *proxy,
    gint timeout_ms,
    GPtrArray **out_Tubes,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_tubes_callback_for_offer_d_bus_tube) (TpChannel *proxy,
    guint out_Tube_ID,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_tubes_call_offer_d_bus_tube (TpChannel *proxy,
    gint timeout_ms,
    const gchar *in_Service,
    GHashTable *in_Parameters,
    tp_cli_channel_type_tubes_callback_for_offer_d_bus_tube callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_tubes_run_offer_d_bus_tube (TpChannel *proxy,
    gint timeout_ms,
    const gchar *in_Service,
    GHashTable *in_Parameters,
    guint *out_Tube_ID,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_tubes_callback_for_offer_stream_tube) (TpChannel *proxy,
    guint out_Tube_ID,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_tubes_call_offer_stream_tube (TpChannel *proxy,
    gint timeout_ms,
    const gchar *in_Service,
    GHashTable *in_Parameters,
    guint in_Address_Type,
    const GValue *in_Address,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    tp_cli_channel_type_tubes_callback_for_offer_stream_tube callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_tubes_run_offer_stream_tube (TpChannel *proxy,
    gint timeout_ms,
    const gchar *in_Service,
    GHashTable *in_Parameters,
    guint in_Address_Type,
    const GValue *in_Address,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    guint *out_Tube_ID,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_tubes_callback_for_accept_d_bus_tube) (TpChannel *proxy,
    const gchar *out_Address,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_tubes_call_accept_d_bus_tube (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    tp_cli_channel_type_tubes_callback_for_accept_d_bus_tube callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_tubes_run_accept_d_bus_tube (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    gchar **out_Address,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_tubes_callback_for_accept_stream_tube) (TpChannel *proxy,
    const GValue *out_Address,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_tubes_call_accept_stream_tube (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    tp_cli_channel_type_tubes_callback_for_accept_stream_tube callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_tubes_run_accept_stream_tube (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    GValue **out_Address,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_tubes_callback_for_close_tube) (TpChannel *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_tubes_call_close_tube (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    tp_cli_channel_type_tubes_callback_for_close_tube callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_tubes_run_close_tube (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_tubes_callback_for_get_d_bus_tube_address) (TpChannel *proxy,
    const gchar *out_Address,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_tubes_call_get_d_bus_tube_address (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    tp_cli_channel_type_tubes_callback_for_get_d_bus_tube_address callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_tubes_run_get_d_bus_tube_address (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    gchar **out_Address,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_tubes_callback_for_get_d_bus_names) (TpChannel *proxy,
    const GPtrArray *out_DBus_Names,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_tubes_call_get_d_bus_names (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    tp_cli_channel_type_tubes_callback_for_get_d_bus_names callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_tubes_run_get_d_bus_names (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    GPtrArray **out_DBus_Names,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_channel_type_tubes_callback_for_get_stream_tube_socket_address) (TpChannel *proxy,
    guint out_Address_Type,
    const GValue *out_Address,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_channel_type_tubes_call_get_stream_tube_socket_address (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    tp_cli_channel_type_tubes_callback_for_get_stream_tube_socket_address callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_channel_type_tubes_run_get_stream_tube_socket_address (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    guint *out_Address_Type,
    GValue **out_Address,
    GError **error,
    GMainLoop **loop);


G_END_DECLS
