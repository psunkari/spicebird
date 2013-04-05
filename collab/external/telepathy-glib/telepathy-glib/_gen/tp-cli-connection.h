G_BEGIN_DECLS

typedef void (*tp_cli_connection_signal_callback_self_handle_changed) (TpConnection *proxy,
    guint arg_Self_Handle,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_connection_connect_to_self_handle_changed (TpConnection *proxy,
    tp_cli_connection_signal_callback_self_handle_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_connection_signal_callback_new_channel) (TpConnection *proxy,
    const gchar *arg_Object_Path,
    const gchar *arg_Channel_Type,
    guint arg_Handle_Type,
    guint arg_Handle,
    gboolean arg_Suppress_Handler,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_connection_connect_to_new_channel (TpConnection *proxy,
    tp_cli_connection_signal_callback_new_channel callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_connection_signal_callback_connection_error) (TpConnection *proxy,
    const gchar *arg_Error,
    GHashTable *arg_Details,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_connection_connect_to_connection_error (TpConnection *proxy,
    tp_cli_connection_signal_callback_connection_error callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_connection_signal_callback_status_changed) (TpConnection *proxy,
    guint arg_Status,
    guint arg_Reason,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_connection_connect_to_status_changed (TpConnection *proxy,
    tp_cli_connection_signal_callback_status_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_connection_callback_for_connect) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_call_connect (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_callback_for_connect callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_run_connect (TpConnection *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_callback_for_disconnect) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_call_disconnect (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_callback_for_disconnect callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_run_disconnect (TpConnection *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_callback_for_get_interfaces) (TpConnection *proxy,
    const gchar **out_Interfaces,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_call_get_interfaces (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_callback_for_get_interfaces callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_run_get_interfaces (TpConnection *proxy,
    gint timeout_ms,
    gchar ***out_Interfaces,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_callback_for_get_protocol) (TpConnection *proxy,
    const gchar *out_Protocol,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_call_get_protocol (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_callback_for_get_protocol callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_run_get_protocol (TpConnection *proxy,
    gint timeout_ms,
    gchar **out_Protocol,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_callback_for_get_self_handle) (TpConnection *proxy,
    guint out_Self_Handle,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_call_get_self_handle (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_callback_for_get_self_handle callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_run_get_self_handle (TpConnection *proxy,
    gint timeout_ms,
    guint *out_Self_Handle,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_callback_for_get_status) (TpConnection *proxy,
    guint out_Status,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_call_get_status (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_callback_for_get_status callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_run_get_status (TpConnection *proxy,
    gint timeout_ms,
    guint *out_Status,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_callback_for_hold_handles) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_call_hold_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const GArray *in_Handles,
    tp_cli_connection_callback_for_hold_handles callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_run_hold_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const GArray *in_Handles,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_callback_for_inspect_handles) (TpConnection *proxy,
    const gchar **out_Identifiers,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_call_inspect_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const GArray *in_Handles,
    tp_cli_connection_callback_for_inspect_handles callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_run_inspect_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const GArray *in_Handles,
    gchar ***out_Identifiers,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_callback_for_list_channels) (TpConnection *proxy,
    const GPtrArray *out_Channel_Info,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_call_list_channels (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_callback_for_list_channels callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_run_list_channels (TpConnection *proxy,
    gint timeout_ms,
    GPtrArray **out_Channel_Info,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_callback_for_release_handles) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_call_release_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const GArray *in_Handles,
    tp_cli_connection_callback_for_release_handles callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_run_release_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const GArray *in_Handles,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_callback_for_request_channel) (TpConnection *proxy,
    const gchar *out_Object_Path,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_call_request_channel (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Type,
    guint in_Handle_Type,
    guint in_Handle,
    gboolean in_Suppress_Handler,
    tp_cli_connection_callback_for_request_channel callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_run_request_channel (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Type,
    guint in_Handle_Type,
    guint in_Handle,
    gboolean in_Suppress_Handler,
    gchar **out_Object_Path,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_callback_for_request_handles) (TpConnection *proxy,
    const GArray *out_Handles,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_call_request_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const gchar **in_Identifiers,
    tp_cli_connection_callback_for_request_handles callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_run_request_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const gchar **in_Identifiers,
    GArray **out_Handles,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_aliasing_signal_callback_aliases_changed) (TpConnection *proxy,
    const GPtrArray *arg_Aliases,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_connection_interface_aliasing_connect_to_aliases_changed (TpConnection *proxy,
    tp_cli_connection_interface_aliasing_signal_callback_aliases_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_connection_interface_aliasing_callback_for_get_alias_flags) (TpConnection *proxy,
    guint out_Alias_Flags,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_aliasing_call_get_alias_flags (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_interface_aliasing_callback_for_get_alias_flags callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_aliasing_run_get_alias_flags (TpConnection *proxy,
    gint timeout_ms,
    guint *out_Alias_Flags,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_aliasing_callback_for_request_aliases) (TpConnection *proxy,
    const gchar **out_Aliases,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_aliasing_call_request_aliases (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_aliasing_callback_for_request_aliases callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_aliasing_run_request_aliases (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    gchar ***out_Aliases,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_aliasing_callback_for_get_aliases) (TpConnection *proxy,
    GHashTable *out_Aliases,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_aliasing_call_get_aliases (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_aliasing_callback_for_get_aliases callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_aliasing_run_get_aliases (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    GHashTable **out_Aliases,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_aliasing_callback_for_set_aliases) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_aliasing_call_set_aliases (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Aliases,
    tp_cli_connection_interface_aliasing_callback_for_set_aliases callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_aliasing_run_set_aliases (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Aliases,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_avatars_signal_callback_avatar_updated) (TpConnection *proxy,
    guint arg_Contact,
    const gchar *arg_New_Avatar_Token,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_connection_interface_avatars_connect_to_avatar_updated (TpConnection *proxy,
    tp_cli_connection_interface_avatars_signal_callback_avatar_updated callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_connection_interface_avatars_signal_callback_avatar_retrieved) (TpConnection *proxy,
    guint arg_Contact,
    const gchar *arg_Token,
    const GArray *arg_Avatar,
    const gchar *arg_Type,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_connection_interface_avatars_connect_to_avatar_retrieved (TpConnection *proxy,
    tp_cli_connection_interface_avatars_signal_callback_avatar_retrieved callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_connection_interface_avatars_callback_for_get_avatar_requirements) (TpConnection *proxy,
    const gchar **out_MIME_Types,
    guint out_Min_Width,
    guint out_Min_Height,
    guint out_Max_Width,
    guint out_Max_Height,
    guint out_Max_Bytes,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_avatars_call_get_avatar_requirements (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_interface_avatars_callback_for_get_avatar_requirements callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_avatars_run_get_avatar_requirements (TpConnection *proxy,
    gint timeout_ms,
    gchar ***out_MIME_Types,
    guint *out_Min_Width,
    guint *out_Min_Height,
    guint *out_Max_Width,
    guint *out_Max_Height,
    guint *out_Max_Bytes,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_avatars_callback_for_get_avatar_tokens) (TpConnection *proxy,
    const gchar **out_Tokens,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_avatars_call_get_avatar_tokens (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_avatars_callback_for_get_avatar_tokens callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_avatars_run_get_avatar_tokens (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    gchar ***out_Tokens,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_avatars_callback_for_get_known_avatar_tokens) (TpConnection *proxy,
    GHashTable *out_Tokens,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_avatars_call_get_known_avatar_tokens (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_avatars_callback_for_get_known_avatar_tokens callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_avatars_run_get_known_avatar_tokens (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    GHashTable **out_Tokens,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_avatars_callback_for_request_avatar) (TpConnection *proxy,
    const GArray *out_Data,
    const gchar *out_MIME_Type,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_avatars_call_request_avatar (TpConnection *proxy,
    gint timeout_ms,
    guint in_Contact,
    tp_cli_connection_interface_avatars_callback_for_request_avatar callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_avatars_run_request_avatar (TpConnection *proxy,
    gint timeout_ms,
    guint in_Contact,
    GArray **out_Data,
    gchar **out_MIME_Type,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_avatars_callback_for_request_avatars) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_avatars_call_request_avatars (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_avatars_callback_for_request_avatars callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_avatars_run_request_avatars (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_avatars_callback_for_set_avatar) (TpConnection *proxy,
    const gchar *out_Token,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_avatars_call_set_avatar (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Avatar,
    const gchar *in_MIME_Type,
    tp_cli_connection_interface_avatars_callback_for_set_avatar callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_avatars_run_set_avatar (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Avatar,
    const gchar *in_MIME_Type,
    gchar **out_Token,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_avatars_callback_for_clear_avatar) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_avatars_call_clear_avatar (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_interface_avatars_callback_for_clear_avatar callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_avatars_run_clear_avatar (TpConnection *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_capabilities_signal_callback_capabilities_changed) (TpConnection *proxy,
    const GPtrArray *arg_Caps,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_connection_interface_capabilities_connect_to_capabilities_changed (TpConnection *proxy,
    tp_cli_connection_interface_capabilities_signal_callback_capabilities_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_connection_interface_capabilities_callback_for_advertise_capabilities) (TpConnection *proxy,
    const GPtrArray *out_Self_Capabilities,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_capabilities_call_advertise_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GPtrArray *in_Add,
    const gchar **in_Remove,
    tp_cli_connection_interface_capabilities_callback_for_advertise_capabilities callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_capabilities_run_advertise_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GPtrArray *in_Add,
    const gchar **in_Remove,
    GPtrArray **out_Self_Capabilities,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_capabilities_callback_for_get_capabilities) (TpConnection *proxy,
    const GPtrArray *out_Contact_Capabilities,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_capabilities_call_get_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Handles,
    tp_cli_connection_interface_capabilities_callback_for_get_capabilities callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_capabilities_run_get_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Handles,
    GPtrArray **out_Contact_Capabilities,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_contact_capabilities_signal_callback_contact_capabilities_changed) (TpConnection *proxy,
    GHashTable *arg_caps,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_connection_interface_contact_capabilities_connect_to_contact_capabilities_changed (TpConnection *proxy,
    tp_cli_connection_interface_contact_capabilities_signal_callback_contact_capabilities_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_connection_interface_contact_capabilities_callback_for_update_capabilities) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_contact_capabilities_call_update_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GPtrArray *in_Handler_Capabilities,
    tp_cli_connection_interface_contact_capabilities_callback_for_update_capabilities callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_contact_capabilities_run_update_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GPtrArray *in_Handler_Capabilities,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_contact_capabilities_callback_for_get_contact_capabilities) (TpConnection *proxy,
    GHashTable *out_Contact_Capabilities,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_contact_capabilities_call_get_contact_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_handles,
    tp_cli_connection_interface_contact_capabilities_callback_for_get_contact_capabilities callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_contact_capabilities_run_get_contact_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_handles,
    GHashTable **out_Contact_Capabilities,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_contacts_callback_for_get_contact_attributes) (TpConnection *proxy,
    GHashTable *out_Attributes,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_contacts_call_get_contact_attributes (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Handles,
    const gchar **in_Interfaces,
    gboolean in_Hold,
    tp_cli_connection_interface_contacts_callback_for_get_contact_attributes callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_contacts_run_get_contact_attributes (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Handles,
    const gchar **in_Interfaces,
    gboolean in_Hold,
    GHashTable **out_Attributes,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_location_signal_callback_location_updated) (TpConnection *proxy,
    guint arg_Contact,
    GHashTable *arg_Location,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_connection_interface_location_connect_to_location_updated (TpConnection *proxy,
    tp_cli_connection_interface_location_signal_callback_location_updated callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_connection_interface_location_callback_for_get_locations) (TpConnection *proxy,
    GHashTable *out_Locations,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_location_call_get_locations (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_location_callback_for_get_locations callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_location_run_get_locations (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    GHashTable **out_Locations,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_location_callback_for_request_location) (TpConnection *proxy,
    GHashTable *out_Location,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_location_call_request_location (TpConnection *proxy,
    gint timeout_ms,
    guint in_Contact,
    tp_cli_connection_interface_location_callback_for_request_location callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_location_run_request_location (TpConnection *proxy,
    gint timeout_ms,
    guint in_Contact,
    GHashTable **out_Location,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_location_callback_for_set_location) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_location_call_set_location (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Location,
    tp_cli_connection_interface_location_callback_for_set_location callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_location_run_set_location (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Location,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_presence_signal_callback_presence_update) (TpConnection *proxy,
    GHashTable *arg_Presence,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_connection_interface_presence_connect_to_presence_update (TpConnection *proxy,
    tp_cli_connection_interface_presence_signal_callback_presence_update callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_connection_interface_presence_callback_for_add_status) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_presence_call_add_status (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Status,
    GHashTable *in_Parameters,
    tp_cli_connection_interface_presence_callback_for_add_status callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_presence_run_add_status (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Status,
    GHashTable *in_Parameters,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_presence_callback_for_clear_status) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_presence_call_clear_status (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_interface_presence_callback_for_clear_status callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_presence_run_clear_status (TpConnection *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_presence_callback_for_get_presence) (TpConnection *proxy,
    GHashTable *out_Presence,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_presence_call_get_presence (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_presence_callback_for_get_presence callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_presence_run_get_presence (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    GHashTable **out_Presence,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_presence_callback_for_get_statuses) (TpConnection *proxy,
    GHashTable *out_Available_Statuses,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_presence_call_get_statuses (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_interface_presence_callback_for_get_statuses callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_presence_run_get_statuses (TpConnection *proxy,
    gint timeout_ms,
    GHashTable **out_Available_Statuses,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_presence_callback_for_remove_status) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_presence_call_remove_status (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Status,
    tp_cli_connection_interface_presence_callback_for_remove_status callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_presence_run_remove_status (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Status,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_presence_callback_for_request_presence) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_presence_call_request_presence (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_presence_callback_for_request_presence callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_presence_run_request_presence (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_presence_callback_for_set_last_activity_time) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_presence_call_set_last_activity_time (TpConnection *proxy,
    gint timeout_ms,
    guint in_Time,
    tp_cli_connection_interface_presence_callback_for_set_last_activity_time callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_presence_run_set_last_activity_time (TpConnection *proxy,
    gint timeout_ms,
    guint in_Time,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_presence_callback_for_set_status) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_presence_call_set_status (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Statuses,
    tp_cli_connection_interface_presence_callback_for_set_status callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_presence_run_set_status (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Statuses,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_requests_signal_callback_new_channels) (TpConnection *proxy,
    const GPtrArray *arg_Channels,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_connection_interface_requests_connect_to_new_channels (TpConnection *proxy,
    tp_cli_connection_interface_requests_signal_callback_new_channels callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_connection_interface_requests_signal_callback_channel_closed) (TpConnection *proxy,
    const gchar *arg_Removed,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_connection_interface_requests_connect_to_channel_closed (TpConnection *proxy,
    tp_cli_connection_interface_requests_signal_callback_channel_closed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_connection_interface_requests_callback_for_create_channel) (TpConnection *proxy,
    const gchar *out_Channel,
    GHashTable *out_Properties,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_requests_call_create_channel (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Request,
    tp_cli_connection_interface_requests_callback_for_create_channel callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_requests_run_create_channel (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Request,
    gchar **out_Channel,
    GHashTable **out_Properties,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_requests_callback_for_ensure_channel) (TpConnection *proxy,
    gboolean out_Yours,
    const gchar *out_Channel,
    GHashTable *out_Properties,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_requests_call_ensure_channel (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Request,
    tp_cli_connection_interface_requests_callback_for_ensure_channel callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_requests_run_ensure_channel (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Request,
    gboolean *out_Yours,
    gchar **out_Channel,
    GHashTable **out_Properties,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_simple_presence_signal_callback_presences_changed) (TpConnection *proxy,
    GHashTable *arg_Presence,
    gpointer user_data, GObject *weak_object);
TpProxySignalConnection *tp_cli_connection_interface_simple_presence_connect_to_presences_changed (TpConnection *proxy,
    tp_cli_connection_interface_simple_presence_signal_callback_presences_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error);

typedef void (*tp_cli_connection_interface_simple_presence_callback_for_set_presence) (TpConnection *proxy,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_simple_presence_call_set_presence (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Status,
    const gchar *in_Status_Message,
    tp_cli_connection_interface_simple_presence_callback_for_set_presence callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_simple_presence_run_set_presence (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Status,
    const gchar *in_Status_Message,
    GError **error,
    GMainLoop **loop);


typedef void (*tp_cli_connection_interface_simple_presence_callback_for_get_presences) (TpConnection *proxy,
    GHashTable *out_Presence,
    const GError *error, gpointer user_data,
    GObject *weak_object);

TpProxyPendingCall *tp_cli_connection_interface_simple_presence_call_get_presences (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_simple_presence_callback_for_get_presences callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object);

gboolean tp_cli_connection_interface_simple_presence_run_get_presences (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    GHashTable **out_Presence,
    GError **error,
    GMainLoop **loop);


G_END_DECLS
