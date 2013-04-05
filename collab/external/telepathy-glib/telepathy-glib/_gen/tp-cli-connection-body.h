/* We don't want gtkdoc scanning this file, it'll get
 * confused by seeing function definitions, so mark it as: */
/*<private_header>*/

static inline void
tp_cli_add_signals_for_connection (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "SelfHandleChanged",
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "NewChannel",
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_STRING,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "ConnectionError",
      G_TYPE_STRING,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)),
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "StatusChanged",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
}


/**
 * tp_cli_connection_signal_callback_self_handle_changed:
 * @proxy: The proxy on which tp_cli_connection_connect_to_self_handle_changed ()
 *  was called
 * @arg_Self_Handle: The new value of the SelfHandle property.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal SelfHandleChanged.
 */
static void
_tp_cli_connection_collect_args_of_self_handle_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Self_Handle,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, arg_Self_Handle);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_invoke_callback_for_self_handle_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_signal_callback_self_handle_changed callback =
      (tp_cli_connection_signal_callback_self_handle_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_connect_to_self_handle_changed:
 * @proxy: A #TpConnection or subclass
 * @callback: Callback to be called when the signal is
 *   received
 * @user_data: User-supplied data for the callback
 * @destroy: Destructor for the user-supplied data, which
 *   will be called when this signal is disconnected, or
 *   before this function returns %NULL
 * @weak_object: A #GObject which will be weakly referenced; 
 *   if it is destroyed, this callback will automatically be
 *   disconnected
 * @error: If not %NULL, used to raise an error if %NULL is
 *   returned
 *
 * Connect a handler to the signal SelfHandleChanged.
 *
 * Emitted whenever the &lt;tp:member-ref&gt;SelfHandle&lt;/tp:member-ref&gt; property         changes. If the connection         is not yet in the CONNECTED state, this signal is not guaranteed         to be emitted.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_connect_to_self_handle_changed (TpConnection *proxy,
    tp_cli_connection_signal_callback_self_handle_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION, "SelfHandleChanged",
      expected_types,
      G_CALLBACK (_tp_cli_connection_collect_args_of_self_handle_changed),
      _tp_cli_connection_invoke_callback_for_self_handle_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_signal_callback_new_channel:
 * @proxy: The proxy on which tp_cli_connection_connect_to_new_channel ()
 *  was called
 * @arg_Object_Path: A D-Bus object path for the channel object on this service
 * @arg_Channel_Type: A D-Bus interface name representing the channel type
 * @arg_Handle_Type: An integer representing the type of handle this channel           communicates with, or Handle_Type_None if no handle is specified
 * @arg_Handle: A handle indicating the specific contact, room or list this           channel communicates with, or zero if no handle is specified
 * @arg_Suppress_Handler: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;If true, the channel was requested by a client that intends to             present it to the user itself (i.e. it passed suppress_handler=TRUE             to the &lt;tp:member-ref&gt;RequestChannel&lt;/tp:member-ref&gt; method), so no             other handler should be             launched. Clients MAY assume that channels where this is true             were created by a user request.&lt;/p&gt;            &lt;p&gt;If false, either the channel was created due to incoming             information from the service, or the channel was requested by             a local client that does not intend to handle the channel itself             (this usage is deprecated).&lt;/p&gt;            &lt;p&gt;Clients MUST NOT assume that only incoming channels will have             this flag set to false.&lt;/p&gt;
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal NewChannel.
 */
static void
_tp_cli_connection_collect_args_of_new_channel (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Object_Path,
    const gchar *arg_Channel_Type,
    guint arg_Handle_Type,
    guint arg_Handle,
    gboolean arg_Suppress_Handler,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (5);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 5; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, DBUS_TYPE_G_OBJECT_PATH);
  g_value_set_boxed (args->values + 0, arg_Object_Path);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_STRING);
  g_value_set_string (args->values + 1, arg_Channel_Type);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, G_TYPE_UINT);
  g_value_set_uint (args->values + 2, arg_Handle_Type);

  g_value_unset (args->values + 3);
  g_value_init (args->values + 3, G_TYPE_UINT);
  g_value_set_uint (args->values + 3, arg_Handle);

  g_value_unset (args->values + 4);
  g_value_init (args->values + 4, G_TYPE_BOOLEAN);
  g_value_set_boolean (args->values + 4, arg_Suppress_Handler);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_invoke_callback_for_new_channel (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_signal_callback_new_channel callback =
      (tp_cli_connection_signal_callback_new_channel) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      g_value_get_string (args->values + 1),
      g_value_get_uint (args->values + 2),
      g_value_get_uint (args->values + 3),
      g_value_get_boolean (args->values + 4),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_connect_to_new_channel:
 * @proxy: A #TpConnection or subclass
 * @callback: Callback to be called when the signal is
 *   received
 * @user_data: User-supplied data for the callback
 * @destroy: Destructor for the user-supplied data, which
 *   will be called when this signal is disconnected, or
 *   before this function returns %NULL
 * @weak_object: A #GObject which will be weakly referenced; 
 *   if it is destroyed, this callback will automatically be
 *   disconnected
 * @error: If not %NULL, used to raise an error if %NULL is
 *   returned
 *
 * Connect a handler to the signal NewChannel.
 *
 * Emitted when a new Channel object is created, either through user         request or incoming information from the service.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_connect_to_new_channel (TpConnection *proxy,
    tp_cli_connection_signal_callback_new_channel callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[6] = {
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_STRING,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION, "NewChannel",
      expected_types,
      G_CALLBACK (_tp_cli_connection_collect_args_of_new_channel),
      _tp_cli_connection_invoke_callback_for_new_channel,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_signal_callback_connection_error:
 * @proxy: The proxy on which tp_cli_connection_connect_to_connection_error ()
 *  was called
 * @arg_Error: The name of a D-Bus error describing the error that occurred,           which may correspond to a           &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt;, or may be a more           specific Telepathy error           (such as           &lt;code&gt;org.freedesktop.Telepathy.Errors.ConnectionRefused&lt;/code&gt;           for Connection_Status_Reason_Network_Error)           or a protocol-specific or connection-manager-specific error in a           suitable namespace.            &lt;tp:rationale&gt;             For instance, a SIP connection manager could signal             &amp;quot;402 Payment Required&amp;quot; as an error in a             connection-manager-specific namespace, or a link-local             XMPP implementation that used Avahi could provide the error             given to it by the avahi-daemon.           &lt;/tp:rationale&gt;
 * @arg_Details: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Additional information about the error, which may include             the following well-known keys:&lt;/p&gt;            &lt;dl&gt;             &lt;dt&gt;debug-message (s)&lt;/dt&gt;             &lt;dd&gt;Debugging information on the change, corresponding to the               message part of a D-Bus error message, which SHOULD NOT be               displayed to users under normal circumstances&lt;/dd&gt;           &lt;/dl&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This argument allows for future extensions. For instance,               if indicating DNS lookup failure, we could define a key               that indicates the hostname that could not be found.&lt;/p&gt;           &lt;/tp:rationale&gt;
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal ConnectionError.
 */
static void
_tp_cli_connection_collect_args_of_connection_error (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Error,
    GHashTable *arg_Details,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (2);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 2; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_STRING);
  g_value_set_string (args->values + 0, arg_Error);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)));
  g_value_set_boxed (args->values + 1, arg_Details);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_invoke_callback_for_connection_error (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_signal_callback_connection_error callback =
      (tp_cli_connection_signal_callback_connection_error) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_string (args->values + 0),
      g_value_get_boxed (args->values + 1),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_connect_to_connection_error:
 * @proxy: A #TpConnection or subclass
 * @callback: Callback to be called when the signal is
 *   received
 * @user_data: User-supplied data for the callback
 * @destroy: Destructor for the user-supplied data, which
 *   will be called when this signal is disconnected, or
 *   before this function returns %NULL
 * @weak_object: A #GObject which will be weakly referenced; 
 *   if it is destroyed, this callback will automatically be
 *   disconnected
 * @error: If not %NULL, used to raise an error if %NULL is
 *   returned
 *
 * Connect a handler to the signal ConnectionError.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Emitted when an error occurs that renders this connection unusable.         &lt;/p&gt;          &lt;p&gt;Whenever this signal is emitted, it MUST immediately be followed by           a &lt;tp:member-ref&gt;StatusChanged&lt;/tp:member-ref&gt; signal with status           Connection_Status_Reason_Disconnected and an appropriate reason           code.&lt;/p&gt;          &lt;p&gt;Connection managers SHOULD emit this signal on disconnection, but           need not do so. Clients MUST support connection managers that emit           StatusChanged(Disconnected, ...) without first emitting           ConnectionError.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;This signal provides additional information about the reason             for disconnection. The reason for connection is always             straightforward - it was requested - so it does not need further             explanation. However, on errors, it can be useful to provide             additional information.&lt;/p&gt;            &lt;p&gt;The &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt; is not given             here, since it will be signalled in             &lt;tp:member-ref&gt;StatusChanged&lt;/tp:member-ref&gt;. A reasonable client             implementation would be to store the information given by this             signal until StatusChanged is received, at which point the             information given by this signal can be used to supplement the             StatusChanged signal.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_connect_to_connection_error (TpConnection *proxy,
    tp_cli_connection_signal_callback_connection_error callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_STRING,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION, "ConnectionError",
      expected_types,
      G_CALLBACK (_tp_cli_connection_collect_args_of_connection_error),
      _tp_cli_connection_invoke_callback_for_connection_error,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_signal_callback_status_changed:
 * @proxy: The proxy on which tp_cli_connection_connect_to_status_changed ()
 *  was called
 * @arg_Status: An integer indicating the new status, as defined by ConnectionStatus
 * @arg_Reason: An integer indicating the reason for the status change, as defined           by ConnectionStatusReason
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal StatusChanged.
 */
static void
_tp_cli_connection_collect_args_of_status_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Status,
    guint arg_Reason,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (2);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 2; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, arg_Status);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Reason);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_invoke_callback_for_status_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_signal_callback_status_changed callback =
      (tp_cli_connection_signal_callback_status_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      g_value_get_uint (args->values + 1),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_connect_to_status_changed:
 * @proxy: A #TpConnection or subclass
 * @callback: Callback to be called when the signal is
 *   received
 * @user_data: User-supplied data for the callback
 * @destroy: Destructor for the user-supplied data, which
 *   will be called when this signal is disconnected, or
 *   before this function returns %NULL
 * @weak_object: A #GObject which will be weakly referenced; 
 *   if it is destroyed, this callback will automatically be
 *   disconnected
 * @error: If not %NULL, used to raise an error if %NULL is
 *   returned
 *
 * Connect a handler to the signal StatusChanged.
 *
 * Emitted when the status of the connection changes.  All states and         reasons have numerical values, as defined in ConnectionStatus         and ConnectionStatusReason.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_connect_to_status_changed (TpConnection *proxy,
    tp_cli_connection_signal_callback_status_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION, "StatusChanged",
      expected_types,
      G_CALLBACK (_tp_cli_connection_collect_args_of_status_changed),
      _tp_cli_connection_invoke_callback_for_status_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_callback_for_connect:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Connect method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_collect_callback_connect (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_invoke_callback_connect (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_callback_for_connect callback = (tp_cli_connection_callback_for_connect) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_call_connect:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a Connect method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that the connection be established. This will be done           asynchronously and errors will be returned by emitting           &lt;tp:member-ref&gt;StatusChanged&lt;/tp:member-ref&gt; signals.&lt;/p&gt;          &lt;p&gt;Calling this method on a Connection that is already connecting           or connected is allowed, and has no effect.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_call_connect (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_callback_for_connect callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "Connect",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Connect", iface,
          _tp_cli_connection_invoke_callback_connect,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Connect",
              _tp_cli_connection_collect_callback_connect,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_run_state_connect;
static void
_tp_cli_connection_finish_running_connect (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_run_state_connect *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_run_connect:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Connect and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that the connection be established. This will be done           asynchronously and errors will be returned by emitting           &lt;tp:member-ref&gt;StatusChanged&lt;/tp:member-ref&gt; signals.&lt;/p&gt;          &lt;p&gt;Calling this method on a Connection that is already connecting           or connected is allowed, and has no effect.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_run_connect (TpConnection *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_run_state_connect state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Connect", iface,
      _tp_cli_connection_finish_running_connect,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Connect",
          _tp_cli_connection_collect_callback_connect,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_callback_for_disconnect:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Disconnect method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_collect_callback_disconnect (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_invoke_callback_disconnect (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_callback_for_disconnect callback = (tp_cli_connection_callback_for_disconnect) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_call_disconnect:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a Disconnect method call.
 *
 * Request that the connection be closed. This closes the connection if         it&apos;s not already in DISCONNECTED state, and destroys the connection         object.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_call_disconnect (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_callback_for_disconnect callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "Disconnect",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Disconnect", iface,
          _tp_cli_connection_invoke_callback_disconnect,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Disconnect",
              _tp_cli_connection_collect_callback_disconnect,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_run_state_disconnect;
static void
_tp_cli_connection_finish_running_disconnect (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_run_state_disconnect *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_run_disconnect:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Disconnect and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Request that the connection be closed. This closes the connection if         it&apos;s not already in DISCONNECTED state, and destroys the connection         object.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_run_disconnect (TpConnection *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_run_state_disconnect state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Disconnect", iface,
      _tp_cli_connection_finish_running_disconnect,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Disconnect",
          _tp_cli_connection_collect_callback_disconnect,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_callback_for_get_interfaces:
 * @proxy: the proxy on which the call was made
 * @out_Interfaces: Used to return an 'out' argument if @error is %NULL: An array of D-Bus interface names
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetInterfaces method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_collect_callback_get_interfaces (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar **out_Interfaces;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRV, &out_Interfaces,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_STRV);
  g_value_take_boxed (args->values + 0, out_Interfaces);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_invoke_callback_get_interfaces (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_callback_for_get_interfaces callback = (tp_cli_connection_callback_for_get_interfaces) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_call_get_interfaces:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetInterfaces method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Get the optional interfaces supported by this connection.           Before the connection status changes to CONNECTED, the return           from this method may change at any time, but it is guaranteed that           interfaces will only be added, not removed. After the connection           status changes to CONNECTED, the return from this method cannot           change further.&lt;/p&gt;          &lt;p&gt;There is no explicit change notification; reasonable behaviour           for a client would be to retrieve the interfaces list once           initially, and once more when it becomes CONNECTED.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;In some connection managers, certain capabilities of a connection             are known to be implemented for all connections (e.g. support             for SimplePresence), and some interfaces (like SimplePresence) can             even be used before connecting. Other capabilities may             or may not exist, depending on server functionality; by the time             the connection goes CONNECTED, the connection manager is expected             to have evaluated the server&apos;s functionality and enabled any extra             interfaces for the remainder of the Connection&apos;s lifetime.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_call_get_interfaces (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_callback_for_get_interfaces callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            NULL,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetInterfaces",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetInterfaces", iface,
          _tp_cli_connection_invoke_callback_get_interfaces,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetInterfaces",
              _tp_cli_connection_collect_callback_get_interfaces,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gchar ***out_Interfaces;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_run_state_get_interfaces;
static void
_tp_cli_connection_finish_running_get_interfaces (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_run_state_get_interfaces *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Interfaces != NULL)
    *state->out_Interfaces = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_run_get_interfaces:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Interfaces: Used to return an 'out' argument if %TRUE is returned: An array of D-Bus interface names
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetInterfaces and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Get the optional interfaces supported by this connection.           Before the connection status changes to CONNECTED, the return           from this method may change at any time, but it is guaranteed that           interfaces will only be added, not removed. After the connection           status changes to CONNECTED, the return from this method cannot           change further.&lt;/p&gt;          &lt;p&gt;There is no explicit change notification; reasonable behaviour           for a client would be to retrieve the interfaces list once           initially, and once more when it becomes CONNECTED.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;In some connection managers, certain capabilities of a connection             are known to be implemented for all connections (e.g. support             for SimplePresence), and some interfaces (like SimplePresence) can             even be used before connecting. Other capabilities may             or may not exist, depending on server functionality; by the time             the connection goes CONNECTED, the connection manager is expected             to have evaluated the server&apos;s functionality and enabled any extra             interfaces for the remainder of the Connection&apos;s lifetime.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_run_get_interfaces (TpConnection *proxy,
    gint timeout_ms,
    gchar ***out_Interfaces,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_run_state_get_interfaces state = {
      NULL /* loop */, error,
    out_Interfaces,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetInterfaces", iface,
      _tp_cli_connection_finish_running_get_interfaces,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetInterfaces",
          _tp_cli_connection_collect_callback_get_interfaces,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_callback_for_get_protocol:
 * @proxy: the proxy on which the call was made
 * @out_Protocol: Used to return an 'out' argument if @error is %NULL: A string identifier for the protocol
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetProtocol method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_collect_callback_get_protocol (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_Protocol;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRING, &out_Protocol,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_STRING);
  g_value_take_string (args->values + 0, out_Protocol);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_invoke_callback_get_protocol (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_callback_for_get_protocol callback = (tp_cli_connection_callback_for_get_protocol) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_string (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_call_get_protocol:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetProtocol method call.
 *
 * Get the protocol this connection is using.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_call_get_protocol (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_callback_for_get_protocol callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            NULL,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetProtocol",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetProtocol", iface,
          _tp_cli_connection_invoke_callback_get_protocol,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetProtocol",
              _tp_cli_connection_collect_callback_get_protocol,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gchar **out_Protocol;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_run_state_get_protocol;
static void
_tp_cli_connection_finish_running_get_protocol (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_run_state_get_protocol *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Protocol != NULL)
    *state->out_Protocol = g_value_dup_string (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_run_get_protocol:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Protocol: Used to return an 'out' argument if %TRUE is returned: A string identifier for the protocol
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetProtocol and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Get the protocol this connection is using.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_run_get_protocol (TpConnection *proxy,
    gint timeout_ms,
    gchar **out_Protocol,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_run_state_get_protocol state = {
      NULL /* loop */, error,
    out_Protocol,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetProtocol", iface,
      _tp_cli_connection_finish_running_get_protocol,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetProtocol",
          _tp_cli_connection_collect_callback_get_protocol,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_callback_for_get_self_handle:
 * @proxy: the proxy on which the call was made
 * @out_Self_Handle: Used to return an 'out' argument if @error is %NULL: The value of the &lt;tp:member-ref&gt;SelfHandle&lt;/tp:member-ref&gt; property
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetSelfHandle method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_collect_callback_get_self_handle (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  guint out_Self_Handle;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_UINT, &out_Self_Handle,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, out_Self_Handle);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_invoke_callback_get_self_handle (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_callback_for_get_self_handle callback = (tp_cli_connection_callback_for_get_self_handle) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          0,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_uint (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_call_get_self_handle:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetSelfHandle method call.
 *
 * Returns the value of the SelfHandle property. Change notification         is via the SelfHandleChanged signal.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_call_get_self_handle (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_callback_for_get_self_handle callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetSelfHandle",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetSelfHandle", iface,
          _tp_cli_connection_invoke_callback_get_self_handle,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetSelfHandle",
              _tp_cli_connection_collect_callback_get_self_handle,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    guint *out_Self_Handle;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_run_state_get_self_handle;
static void
_tp_cli_connection_finish_running_get_self_handle (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_run_state_get_self_handle *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Self_Handle != NULL)
    *state->out_Self_Handle = g_value_get_uint (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_run_get_self_handle:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Self_Handle: Used to return an 'out' argument if %TRUE is returned: The value of the &lt;tp:member-ref&gt;SelfHandle&lt;/tp:member-ref&gt; property
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetSelfHandle and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns the value of the SelfHandle property. Change notification         is via the SelfHandleChanged signal.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_run_get_self_handle (TpConnection *proxy,
    gint timeout_ms,
    guint *out_Self_Handle,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_run_state_get_self_handle state = {
      NULL /* loop */, error,
    out_Self_Handle,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetSelfHandle", iface,
      _tp_cli_connection_finish_running_get_self_handle,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetSelfHandle",
          _tp_cli_connection_collect_callback_get_self_handle,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_callback_for_get_status:
 * @proxy: the proxy on which the call was made
 * @out_Status: Used to return an 'out' argument if @error is %NULL: An integer representing the current status
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetStatus method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_collect_callback_get_status (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  guint out_Status;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_UINT, &out_Status,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, out_Status);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_invoke_callback_get_status (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_callback_for_get_status callback = (tp_cli_connection_callback_for_get_status) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          0,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_uint (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_call_get_status:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetStatus method call.
 *
 * Get the current status as defined in the         &lt;tp:member-ref&gt;StatusChanged&lt;/tp:member-ref&gt; signal.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_call_get_status (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_callback_for_get_status callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetStatus",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetStatus", iface,
          _tp_cli_connection_invoke_callback_get_status,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetStatus",
              _tp_cli_connection_collect_callback_get_status,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    guint *out_Status;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_run_state_get_status;
static void
_tp_cli_connection_finish_running_get_status (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_run_state_get_status *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Status != NULL)
    *state->out_Status = g_value_get_uint (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_run_get_status:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Status: Used to return an 'out' argument if %TRUE is returned: An integer representing the current status
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetStatus and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Get the current status as defined in the         &lt;tp:member-ref&gt;StatusChanged&lt;/tp:member-ref&gt; signal.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_run_get_status (TpConnection *proxy,
    gint timeout_ms,
    guint *out_Status,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_run_state_get_status state = {
      NULL /* loop */, error,
    out_Status,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetStatus", iface,
      _tp_cli_connection_finish_running_get_status,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetStatus",
          _tp_cli_connection_collect_callback_get_status,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_callback_for_hold_handles:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a HoldHandles method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_collect_callback_hold_handles (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_invoke_callback_hold_handles (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_callback_for_hold_handles callback = (tp_cli_connection_callback_for_hold_handles) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_call_hold_handles:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Handle_Type: Used to pass an 'in' argument: The type of handle to be held
 * @in_Handles: Used to pass an 'in' argument: A array of integer handles to hold
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a HoldHandles method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Notify the connection manger that your client is holding a copy         of handles which may not be in use in any existing channel or         list, and were not obtained by using the         &lt;tp:member-ref&gt;RequestHandles&lt;/tp:member-ref&gt; method. For         example, a handle observed in an emitted signal, or displayed         somewhere in the UI that is not associated with a channel. The         connection manager must not deallocate a handle where any clients         have used this method to indicate it is in use until the         &lt;tp:member-ref&gt;ReleaseHandles&lt;/tp:member-ref&gt;         method is called, or the clients disappear from the bus.&lt;/p&gt;          &lt;p&gt;Note that HoldHandles is idempotent - calling it multiple times           is equivalent to calling it once. If a handle is &amp;quot;referenced&amp;quot; by           several components which share a D-Bus unique name, the client           should perform reference counting internally, and only call           ReleaseHandles when none of the cooperating components need the           handle any longer.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_call_hold_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const GArray *in_Handles,
    tp_cli_connection_callback_for_hold_handles callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "HoldHandles",
          G_TYPE_UINT, in_Handle_Type,
          DBUS_TYPE_G_UINT_ARRAY, in_Handles,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "HoldHandles", iface,
          _tp_cli_connection_invoke_callback_hold_handles,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "HoldHandles",
              _tp_cli_connection_collect_callback_hold_handles,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Handle_Type,
              DBUS_TYPE_G_UINT_ARRAY, in_Handles,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_run_state_hold_handles;
static void
_tp_cli_connection_finish_running_hold_handles (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_run_state_hold_handles *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_run_hold_handles:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Handle_Type: Used to pass an 'in' argument: The type of handle to be held
 * @in_Handles: Used to pass an 'in' argument: A array of integer handles to hold
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method HoldHandles and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Notify the connection manger that your client is holding a copy         of handles which may not be in use in any existing channel or         list, and were not obtained by using the         &lt;tp:member-ref&gt;RequestHandles&lt;/tp:member-ref&gt; method. For         example, a handle observed in an emitted signal, or displayed         somewhere in the UI that is not associated with a channel. The         connection manager must not deallocate a handle where any clients         have used this method to indicate it is in use until the         &lt;tp:member-ref&gt;ReleaseHandles&lt;/tp:member-ref&gt;         method is called, or the clients disappear from the bus.&lt;/p&gt;          &lt;p&gt;Note that HoldHandles is idempotent - calling it multiple times           is equivalent to calling it once. If a handle is &amp;quot;referenced&amp;quot; by           several components which share a D-Bus unique name, the client           should perform reference counting internally, and only call           ReleaseHandles when none of the cooperating components need the           handle any longer.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_run_hold_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const GArray *in_Handles,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_run_state_hold_handles state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "HoldHandles", iface,
      _tp_cli_connection_finish_running_hold_handles,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "HoldHandles",
          _tp_cli_connection_collect_callback_hold_handles,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Handle_Type,
              DBUS_TYPE_G_UINT_ARRAY, in_Handles,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_callback_for_inspect_handles:
 * @proxy: the proxy on which the call was made
 * @out_Identifiers: Used to return an 'out' argument if @error is %NULL: An array of identifiers corresponding to the given handles, in the same order.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a InspectHandles method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_collect_callback_inspect_handles (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar **out_Identifiers;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRV, &out_Identifiers,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_STRV);
  g_value_take_boxed (args->values + 0, out_Identifiers);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_invoke_callback_inspect_handles (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_callback_for_inspect_handles callback = (tp_cli_connection_callback_for_inspect_handles) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_call_inspect_handles:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Handle_Type: Used to pass an 'in' argument: The type of handle to be inspected
 * @in_Handles: Used to pass an 'in' argument: An array of integer handles of this type
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a InspectHandles method call.
 *
 * Return a string representation for a number of handles of a given         type.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_call_inspect_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const GArray *in_Handles,
    tp_cli_connection_callback_for_inspect_handles callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            NULL,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "InspectHandles",
          G_TYPE_UINT, in_Handle_Type,
          DBUS_TYPE_G_UINT_ARRAY, in_Handles,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "InspectHandles", iface,
          _tp_cli_connection_invoke_callback_inspect_handles,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "InspectHandles",
              _tp_cli_connection_collect_callback_inspect_handles,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Handle_Type,
              DBUS_TYPE_G_UINT_ARRAY, in_Handles,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gchar ***out_Identifiers;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_run_state_inspect_handles;
static void
_tp_cli_connection_finish_running_inspect_handles (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_run_state_inspect_handles *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Identifiers != NULL)
    *state->out_Identifiers = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_run_inspect_handles:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Handle_Type: Used to pass an 'in' argument: The type of handle to be inspected
 * @in_Handles: Used to pass an 'in' argument: An array of integer handles of this type
 * @out_Identifiers: Used to return an 'out' argument if %TRUE is returned: An array of identifiers corresponding to the given handles, in the same order.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method InspectHandles and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Return a string representation for a number of handles of a given         type.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_run_inspect_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const GArray *in_Handles,
    gchar ***out_Identifiers,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_run_state_inspect_handles state = {
      NULL /* loop */, error,
    out_Identifiers,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "InspectHandles", iface,
      _tp_cli_connection_finish_running_inspect_handles,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "InspectHandles",
          _tp_cli_connection_collect_callback_inspect_handles,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Handle_Type,
              DBUS_TYPE_G_UINT_ARRAY, in_Handles,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_callback_for_list_channels:
 * @proxy: the proxy on which the call was made
 * @out_Channel_Info: Used to return an 'out' argument if @error is %NULL: An array of structs representing channels.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a ListChannels method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_collect_callback_list_channels (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GPtrArray *out_Channel_Info;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))), &out_Channel_Info,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Channel_Info);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_invoke_callback_list_channels (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_callback_for_list_channels callback = (tp_cli_connection_callback_for_list_channels) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_call_list_channels:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a ListChannels method call.
 *
 * List all the channels which currently exist on this connection.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_call_list_channels (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_callback_for_list_channels callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            NULL,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "ListChannels",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "ListChannels", iface,
          _tp_cli_connection_invoke_callback_list_channels,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "ListChannels",
              _tp_cli_connection_collect_callback_list_channels,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GPtrArray **out_Channel_Info;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_run_state_list_channels;
static void
_tp_cli_connection_finish_running_list_channels (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_run_state_list_channels *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Channel_Info != NULL)
    *state->out_Channel_Info = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_run_list_channels:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Channel_Info: Used to return an 'out' argument if %TRUE is returned: An array of structs representing channels.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method ListChannels and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * List all the channels which currently exist on this connection.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_run_list_channels (TpConnection *proxy,
    gint timeout_ms,
    GPtrArray **out_Channel_Info,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_run_state_list_channels state = {
      NULL /* loop */, error,
    out_Channel_Info,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "ListChannels", iface,
      _tp_cli_connection_finish_running_list_channels,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "ListChannels",
          _tp_cli_connection_collect_callback_list_channels,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_callback_for_release_handles:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a ReleaseHandles method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_collect_callback_release_handles (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_invoke_callback_release_handles (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_callback_for_release_handles callback = (tp_cli_connection_callback_for_release_handles) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_call_release_handles:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Handle_Type: Used to pass an 'in' argument: An integer handle type (as defined in RequestHandle)
 * @in_Handles: Used to pass an 'in' argument: An array of integer handles being held by the client
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a ReleaseHandles method call.
 *
 * Explicitly notify the connection manager that your client is no         longer holding any references to the given handles, and that they         may be deallocated if they are not held by any other clients or         referenced by any existing channels. See HoldHandles for notes.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_call_release_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const GArray *in_Handles,
    tp_cli_connection_callback_for_release_handles callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "ReleaseHandles",
          G_TYPE_UINT, in_Handle_Type,
          DBUS_TYPE_G_UINT_ARRAY, in_Handles,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "ReleaseHandles", iface,
          _tp_cli_connection_invoke_callback_release_handles,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "ReleaseHandles",
              _tp_cli_connection_collect_callback_release_handles,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Handle_Type,
              DBUS_TYPE_G_UINT_ARRAY, in_Handles,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_run_state_release_handles;
static void
_tp_cli_connection_finish_running_release_handles (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_run_state_release_handles *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_run_release_handles:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Handle_Type: Used to pass an 'in' argument: An integer handle type (as defined in RequestHandle)
 * @in_Handles: Used to pass an 'in' argument: An array of integer handles being held by the client
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method ReleaseHandles and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Explicitly notify the connection manager that your client is no         longer holding any references to the given handles, and that they         may be deallocated if they are not held by any other clients or         referenced by any existing channels. See HoldHandles for notes.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_run_release_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const GArray *in_Handles,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_run_state_release_handles state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "ReleaseHandles", iface,
      _tp_cli_connection_finish_running_release_handles,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "ReleaseHandles",
          _tp_cli_connection_collect_callback_release_handles,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Handle_Type,
              DBUS_TYPE_G_UINT_ARRAY, in_Handles,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_callback_for_request_channel:
 * @proxy: the proxy on which the call was made
 * @out_Object_Path: Used to return an 'out' argument if @error is %NULL: The D-Bus object path for the channel created or retrieved
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RequestChannel method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_collect_callback_request_channel (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_Object_Path;

  dbus_g_proxy_end_call (proxy, call, &error,
      DBUS_TYPE_G_OBJECT_PATH, &out_Object_Path,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, DBUS_TYPE_G_OBJECT_PATH);
  g_value_take_boxed (args->values + 0, out_Object_Path);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_invoke_callback_request_channel (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_callback_for_request_channel callback = (tp_cli_connection_callback_for_request_channel) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_call_request_channel:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Type: Used to pass an 'in' argument: A D-Bus interface name representing base channel type
 * @in_Handle_Type: Used to pass an 'in' argument: An integer representing the handle type, or Handle_Type_None if           no handle is specified
 * @in_Handle: Used to pass an 'in' argument: A nonzero integer handle representing a contact, room, list etc.           according to handle_type, or zero if the handle_type is           Handle_Type_None
 * @in_Suppress_Handler: Used to pass an 'in' argument: &lt;p&gt;Clients SHOULD always set this to true.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;The historical meaning was that clients that did not               intend to take responsibility for displaying the channel to               the user could set this to FALSE, in which case the channel               dispatcher would launch an appropriate channel handler.&lt;/p&gt;              &lt;p&gt;However, clients whose functionality relies on having a               working channel dispatcher should obtain that functionality by               calling methods on the channel dispatcher, so that they will               get an appropriate error if the channel dispatcher is missing               or not working.&lt;/p&gt;              &lt;p&gt;The channel dispatcher itself should set this to true too,               so that it will ignore the               &lt;tp:member-ref&gt;NewChannel&lt;/tp:member-ref&gt; signal that results               from the creation of the channel. It can then dispatch the               channel returned from this method to an               appropriate handler.&lt;/p&gt;              &lt;p&gt;So, there is no sensible use-case for setting this to false,               and setting it to false can result in unhandled channels (in               the case where clients assume that a channel dispatcher is               present, but it isn&apos;t).&lt;/p&gt;           &lt;/tp:rationale&gt;
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a RequestChannel method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request a channel satisfying the specified type and communicating           with the contact, room, list etc. indicated by the given           handle_type and handle. The handle_type and handle may both be           zero to request the creation of a new, empty channel, which may           or may not be possible, depending on the protocol and channel           type.&lt;/p&gt;          &lt;p&gt;On success, the returned channel will always be of the requested           type (i.e. implement the requested channel-type interface).&lt;/p&gt;          &lt;p&gt;If a new, empty channel is requested, on success the returned           channel will always be an &amp;quot;anonymous&amp;quot; channel for which the type           and handle are both zero.&lt;/p&gt;          &lt;p&gt;If a channel to a contact, room etc. is requested, on success, the           returned channel may either be a new or existing channel to           the requested entity (i.e. its           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel&quot;&gt;TargetHandleType&lt;/tp:dbus-ref&gt;           and &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel&quot;&gt;TargetHandle&lt;/tp:dbus-ref&gt;           properties are the           requested handle type and handle), or a newly created &amp;quot;anonymous&amp;quot;           channel associated with the requested handle in some           implementation-specific way.&lt;/p&gt;          &lt;p&gt;For example, for a contact handle, the returned channel           might be &amp;quot;anonymous&amp;quot;, but implement the groups interface and have           the requested contact already present among the members.&lt;/p&gt;          &lt;p&gt;If the request cannot be satisfied, an error is raised and no           channel is created.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_call_request_channel (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Type,
    guint in_Handle_Type,
    guint in_Handle,
    gboolean in_Suppress_Handler,
    tp_cli_connection_callback_for_request_channel callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            NULL,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "RequestChannel",
          G_TYPE_STRING, in_Type,
          G_TYPE_UINT, in_Handle_Type,
          G_TYPE_UINT, in_Handle,
          G_TYPE_BOOLEAN, in_Suppress_Handler,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RequestChannel", iface,
          _tp_cli_connection_invoke_callback_request_channel,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RequestChannel",
              _tp_cli_connection_collect_callback_request_channel,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Type,
              G_TYPE_UINT, in_Handle_Type,
              G_TYPE_UINT, in_Handle,
              G_TYPE_BOOLEAN, in_Suppress_Handler,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gchar **out_Object_Path;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_run_state_request_channel;
static void
_tp_cli_connection_finish_running_request_channel (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_run_state_request_channel *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Object_Path != NULL)
    *state->out_Object_Path = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_run_request_channel:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Type: Used to pass an 'in' argument: A D-Bus interface name representing base channel type
 * @in_Handle_Type: Used to pass an 'in' argument: An integer representing the handle type, or Handle_Type_None if           no handle is specified
 * @in_Handle: Used to pass an 'in' argument: A nonzero integer handle representing a contact, room, list etc.           according to handle_type, or zero if the handle_type is           Handle_Type_None
 * @in_Suppress_Handler: Used to pass an 'in' argument: &lt;p&gt;Clients SHOULD always set this to true.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;The historical meaning was that clients that did not               intend to take responsibility for displaying the channel to               the user could set this to FALSE, in which case the channel               dispatcher would launch an appropriate channel handler.&lt;/p&gt;              &lt;p&gt;However, clients whose functionality relies on having a               working channel dispatcher should obtain that functionality by               calling methods on the channel dispatcher, so that they will               get an appropriate error if the channel dispatcher is missing               or not working.&lt;/p&gt;              &lt;p&gt;The channel dispatcher itself should set this to true too,               so that it will ignore the               &lt;tp:member-ref&gt;NewChannel&lt;/tp:member-ref&gt; signal that results               from the creation of the channel. It can then dispatch the               channel returned from this method to an               appropriate handler.&lt;/p&gt;              &lt;p&gt;So, there is no sensible use-case for setting this to false,               and setting it to false can result in unhandled channels (in               the case where clients assume that a channel dispatcher is               present, but it isn&apos;t).&lt;/p&gt;           &lt;/tp:rationale&gt;
 * @out_Object_Path: Used to return an 'out' argument if %TRUE is returned: The D-Bus object path for the channel created or retrieved
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RequestChannel and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request a channel satisfying the specified type and communicating           with the contact, room, list etc. indicated by the given           handle_type and handle. The handle_type and handle may both be           zero to request the creation of a new, empty channel, which may           or may not be possible, depending on the protocol and channel           type.&lt;/p&gt;          &lt;p&gt;On success, the returned channel will always be of the requested           type (i.e. implement the requested channel-type interface).&lt;/p&gt;          &lt;p&gt;If a new, empty channel is requested, on success the returned           channel will always be an &amp;quot;anonymous&amp;quot; channel for which the type           and handle are both zero.&lt;/p&gt;          &lt;p&gt;If a channel to a contact, room etc. is requested, on success, the           returned channel may either be a new or existing channel to           the requested entity (i.e. its           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel&quot;&gt;TargetHandleType&lt;/tp:dbus-ref&gt;           and &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel&quot;&gt;TargetHandle&lt;/tp:dbus-ref&gt;           properties are the           requested handle type and handle), or a newly created &amp;quot;anonymous&amp;quot;           channel associated with the requested handle in some           implementation-specific way.&lt;/p&gt;          &lt;p&gt;For example, for a contact handle, the returned channel           might be &amp;quot;anonymous&amp;quot;, but implement the groups interface and have           the requested contact already present among the members.&lt;/p&gt;          &lt;p&gt;If the request cannot be satisfied, an error is raised and no           channel is created.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_run_request_channel (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Type,
    guint in_Handle_Type,
    guint in_Handle,
    gboolean in_Suppress_Handler,
    gchar **out_Object_Path,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_run_state_request_channel state = {
      NULL /* loop */, error,
    out_Object_Path,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RequestChannel", iface,
      _tp_cli_connection_finish_running_request_channel,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RequestChannel",
          _tp_cli_connection_collect_callback_request_channel,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_STRING, in_Type,
              G_TYPE_UINT, in_Handle_Type,
              G_TYPE_UINT, in_Handle,
              G_TYPE_BOOLEAN, in_Suppress_Handler,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_callback_for_request_handles:
 * @proxy: the proxy on which the call was made
 * @out_Handles: Used to return an 'out' argument if @error is %NULL: An array of integer handle numbers in the same order as the given identifiers.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RequestHandles method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_collect_callback_request_handles (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GArray *out_Handles;

  dbus_g_proxy_end_call (proxy, call, &error,
      DBUS_TYPE_G_UINT_ARRAY, &out_Handles,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, DBUS_TYPE_G_UINT_ARRAY);
  g_value_take_boxed (args->values + 0, out_Handles);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_invoke_callback_request_handles (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_callback_for_request_handles callback = (tp_cli_connection_callback_for_request_handles) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_call_request_handles:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Handle_Type: Used to pass an 'in' argument: The type of handle required
 * @in_Identifiers: Used to pass an 'in' argument: An array of identifiers of entities to request handles for
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a RequestHandles method call.
 *
 * Request several handles from the connection manager which represent a         number of contacts, rooms or server-stored lists on the service. The         connection manager should record that these handles are in use by the         client who invokes this method, and must not deallocate the handles         until the client disconnects from the bus or calls the         &lt;tp:member-ref&gt;ReleaseHandles&lt;/tp:member-ref&gt;         method. Where the identifier refers to an entity that already has a         handle in this connection manager, this handle should be returned         instead. The handle number 0 must not be returned by the connection         manager.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_call_request_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const gchar **in_Identifiers,
    tp_cli_connection_callback_for_request_handles callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            NULL,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "RequestHandles",
          G_TYPE_UINT, in_Handle_Type,
          G_TYPE_STRV, in_Identifiers,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RequestHandles", iface,
          _tp_cli_connection_invoke_callback_request_handles,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RequestHandles",
              _tp_cli_connection_collect_callback_request_handles,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Handle_Type,
              G_TYPE_STRV, in_Identifiers,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GArray **out_Handles;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_run_state_request_handles;
static void
_tp_cli_connection_finish_running_request_handles (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_run_state_request_handles *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Handles != NULL)
    *state->out_Handles = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_run_request_handles:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Handle_Type: Used to pass an 'in' argument: The type of handle required
 * @in_Identifiers: Used to pass an 'in' argument: An array of identifiers of entities to request handles for
 * @out_Handles: Used to return an 'out' argument if %TRUE is returned: An array of integer handle numbers in the same order as the given identifiers.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RequestHandles and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Request several handles from the connection manager which represent a         number of contacts, rooms or server-stored lists on the service. The         connection manager should record that these handles are in use by the         client who invokes this method, and must not deallocate the handles         until the client disconnects from the bus or calls the         &lt;tp:member-ref&gt;ReleaseHandles&lt;/tp:member-ref&gt;         method. Where the identifier refers to an entity that already has a         handle in this connection manager, this handle should be returned         instead. The handle number 0 must not be returned by the connection         manager.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_run_request_handles (TpConnection *proxy,
    gint timeout_ms,
    guint in_Handle_Type,
    const gchar **in_Identifiers,
    GArray **out_Handles,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_run_state_request_handles state = {
      NULL /* loop */, error,
    out_Handles,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RequestHandles", iface,
      _tp_cli_connection_finish_running_request_handles,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RequestHandles",
          _tp_cli_connection_collect_callback_request_handles,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Handle_Type,
              G_TYPE_STRV, in_Identifiers,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


static inline void
tp_cli_add_signals_for_connection_interface_aliasing (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "AliasesChanged",
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID)))),
      G_TYPE_INVALID);
}


/**
 * tp_cli_connection_interface_aliasing_signal_callback_aliases_changed:
 * @proxy: The proxy on which tp_cli_connection_interface_aliasing_connect_to_aliases_changed ()
 *  was called
 * @arg_Aliases: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array containing structs of:           &lt;ul&gt;             &lt;li&gt;the handle representing the contact&lt;/li&gt;             &lt;li&gt;the new alias&lt;/li&gt;           &lt;/ul&gt;
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal AliasesChanged.
 */
static void
_tp_cli_connection_interface_aliasing_collect_args_of_aliases_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    const GPtrArray *arg_Aliases,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID)))));
  g_value_set_boxed (args->values + 0, arg_Aliases);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_interface_aliasing_invoke_callback_for_aliases_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_aliasing_signal_callback_aliases_changed callback =
      (tp_cli_connection_interface_aliasing_signal_callback_aliases_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_interface_aliasing_connect_to_aliases_changed:
 * @proxy: A #TpConnection or subclass
 * @callback: Callback to be called when the signal is
 *   received
 * @user_data: User-supplied data for the callback
 * @destroy: Destructor for the user-supplied data, which
 *   will be called when this signal is disconnected, or
 *   before this function returns %NULL
 * @weak_object: A #GObject which will be weakly referenced; 
 *   if it is destroyed, this callback will automatically be
 *   disconnected
 * @error: If not %NULL, used to raise an error if %NULL is
 *   returned
 *
 * Connect a handler to the signal AliasesChanged.
 *
 * Signal emitted when a contact&apos;s alias (or that of the user) is changed.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_interface_aliasing_connect_to_aliases_changed (TpConnection *proxy,
    tp_cli_connection_interface_aliasing_signal_callback_aliases_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID)))),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION_INTERFACE_ALIASING, "AliasesChanged",
      expected_types,
      G_CALLBACK (_tp_cli_connection_interface_aliasing_collect_args_of_aliases_changed),
      _tp_cli_connection_interface_aliasing_invoke_callback_for_aliases_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_interface_aliasing_callback_for_get_alias_flags:
 * @proxy: the proxy on which the call was made
 * @out_Alias_Flags: Used to return an 'out' argument if @error is %NULL: An integer with a bitwise OR of flags from ConnectionAliasFlags
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetAliasFlags method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_aliasing_collect_callback_get_alias_flags (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  guint out_Alias_Flags;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_UINT, &out_Alias_Flags,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, out_Alias_Flags);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_aliasing_invoke_callback_get_alias_flags (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_aliasing_callback_for_get_alias_flags callback = (tp_cli_connection_interface_aliasing_callback_for_get_alias_flags) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          0,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_uint (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_aliasing_call_get_alias_flags:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetAliasFlags method call.
 *
 * Return a bitwise OR of flags detailing the behaviour of aliases on this         connection.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_aliasing_call_get_alias_flags (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_interface_aliasing_callback_for_get_alias_flags callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_ALIASING;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetAliasFlags",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetAliasFlags", iface,
          _tp_cli_connection_interface_aliasing_invoke_callback_get_alias_flags,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetAliasFlags",
              _tp_cli_connection_interface_aliasing_collect_callback_get_alias_flags,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    guint *out_Alias_Flags;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_aliasing_run_state_get_alias_flags;
static void
_tp_cli_connection_interface_aliasing_finish_running_get_alias_flags (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_aliasing_run_state_get_alias_flags *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Alias_Flags != NULL)
    *state->out_Alias_Flags = g_value_get_uint (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_aliasing_run_get_alias_flags:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Alias_Flags: Used to return an 'out' argument if %TRUE is returned: An integer with a bitwise OR of flags from ConnectionAliasFlags
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetAliasFlags and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Return a bitwise OR of flags detailing the behaviour of aliases on this         connection.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_aliasing_run_get_alias_flags (TpConnection *proxy,
    gint timeout_ms,
    guint *out_Alias_Flags,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_ALIASING;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_aliasing_run_state_get_alias_flags state = {
      NULL /* loop */, error,
    out_Alias_Flags,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetAliasFlags", iface,
      _tp_cli_connection_interface_aliasing_finish_running_get_alias_flags,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetAliasFlags",
          _tp_cli_connection_interface_aliasing_collect_callback_get_alias_flags,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_aliasing_callback_for_request_aliases:
 * @proxy: the proxy on which the call was made
 * @out_Aliases: Used to return an 'out' argument if @error is %NULL: A list of aliases in the same order as the contact handles
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RequestAliases method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_aliasing_collect_callback_request_aliases (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar **out_Aliases;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRV, &out_Aliases,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_STRV);
  g_value_take_boxed (args->values + 0, out_Aliases);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_aliasing_invoke_callback_request_aliases (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_aliasing_callback_for_request_aliases callback = (tp_cli_connection_interface_aliasing_callback_for_request_aliases) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_aliasing_call_request_aliases:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contacts: Used to pass an 'in' argument: An array of handles representing contacts
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a RequestAliases method call.
 *
 * Request the value of several contacts&apos; aliases at once.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_aliasing_call_request_aliases (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_aliasing_callback_for_request_aliases callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_ALIASING;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            NULL,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "RequestAliases",
          DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RequestAliases", iface,
          _tp_cli_connection_interface_aliasing_invoke_callback_request_aliases,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RequestAliases",
              _tp_cli_connection_interface_aliasing_collect_callback_request_aliases,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gchar ***out_Aliases;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_aliasing_run_state_request_aliases;
static void
_tp_cli_connection_interface_aliasing_finish_running_request_aliases (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_aliasing_run_state_request_aliases *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Aliases != NULL)
    *state->out_Aliases = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_aliasing_run_request_aliases:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contacts: Used to pass an 'in' argument: An array of handles representing contacts
 * @out_Aliases: Used to return an 'out' argument if %TRUE is returned: A list of aliases in the same order as the contact handles
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RequestAliases and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Request the value of several contacts&apos; aliases at once.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_aliasing_run_request_aliases (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    gchar ***out_Aliases,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_ALIASING;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_aliasing_run_state_request_aliases state = {
      NULL /* loop */, error,
    out_Aliases,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RequestAliases", iface,
      _tp_cli_connection_interface_aliasing_finish_running_request_aliases,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RequestAliases",
          _tp_cli_connection_interface_aliasing_collect_callback_request_aliases,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_aliasing_callback_for_get_aliases:
 * @proxy: the proxy on which the call was made
 * @out_Aliases: Used to return an 'out' argument if @error is %NULL: A dictionary mapping contact handles to aliases
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetAliases method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_aliasing_collect_callback_get_aliases (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GHashTable *out_Aliases;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_STRING)), &out_Aliases,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_STRING)));
  g_value_take_boxed (args->values + 0, out_Aliases);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_aliasing_invoke_callback_get_aliases (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_aliasing_callback_for_get_aliases callback = (tp_cli_connection_interface_aliasing_callback_for_get_aliases) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_aliasing_call_get_aliases:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contacts: Used to pass an 'in' argument: An array of handles representing contacts
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetAliases method call.
 *
 * Request the value of several contacts&apos; aliases at once. This SHOULD         only return cached aliases, falling back on the contact identifier         (i.e. the string corresponding to the handle) if none is present. Also         if there was no cached alias, a request SHOULD be started of which the         result is later signalled by         &lt;tp:member-ref&gt;AliasesChanged&lt;/tp:member-ref&gt;.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_aliasing_call_get_aliases (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_aliasing_callback_for_get_aliases callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_ALIASING;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetAliases",
          DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetAliases", iface,
          _tp_cli_connection_interface_aliasing_invoke_callback_get_aliases,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetAliases",
              _tp_cli_connection_interface_aliasing_collect_callback_get_aliases,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GHashTable **out_Aliases;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_aliasing_run_state_get_aliases;
static void
_tp_cli_connection_interface_aliasing_finish_running_get_aliases (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_aliasing_run_state_get_aliases *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Aliases != NULL)
    *state->out_Aliases = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_aliasing_run_get_aliases:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contacts: Used to pass an 'in' argument: An array of handles representing contacts
 * @out_Aliases: Used to return an 'out' argument if %TRUE is returned: A dictionary mapping contact handles to aliases
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetAliases and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Request the value of several contacts&apos; aliases at once. This SHOULD         only return cached aliases, falling back on the contact identifier         (i.e. the string corresponding to the handle) if none is present. Also         if there was no cached alias, a request SHOULD be started of which the         result is later signalled by         &lt;tp:member-ref&gt;AliasesChanged&lt;/tp:member-ref&gt;.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_aliasing_run_get_aliases (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    GHashTable **out_Aliases,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_ALIASING;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_aliasing_run_state_get_aliases state = {
      NULL /* loop */, error,
    out_Aliases,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetAliases", iface,
      _tp_cli_connection_interface_aliasing_finish_running_get_aliases,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetAliases",
          _tp_cli_connection_interface_aliasing_collect_callback_get_aliases,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_aliasing_callback_for_set_aliases:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a SetAliases method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_aliasing_collect_callback_set_aliases (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_interface_aliasing_invoke_callback_set_aliases (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_aliasing_callback_for_set_aliases callback = (tp_cli_connection_interface_aliasing_callback_for_set_aliases) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_aliasing_call_set_aliases:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Aliases: Used to pass an 'in' argument: A dictionary mapping integer handles of contacts           to strings of the new alias to set.
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a SetAliases method call.
 *
 * Request that the alias of the given contact be changed. Success will be         indicated by emitting an &lt;tp:member-ref&gt;AliasesChanged&lt;/tp:member-ref&gt;         signal. On connections where the CONNECTION_ALIAS_FLAG_USER_SET flag is         not set, this method will only ever succeed if the contact is the         user&apos;s own handle (as returned by &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection.GetSelfHandle&lt;/tp:dbus-ref&gt;).
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_aliasing_call_set_aliases (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Aliases,
    tp_cli_connection_interface_aliasing_callback_for_set_aliases callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_ALIASING;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "SetAliases",
          (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_STRING)), in_Aliases,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "SetAliases", iface,
          _tp_cli_connection_interface_aliasing_invoke_callback_set_aliases,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "SetAliases",
              _tp_cli_connection_interface_aliasing_collect_callback_set_aliases,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_STRING)), in_Aliases,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_aliasing_run_state_set_aliases;
static void
_tp_cli_connection_interface_aliasing_finish_running_set_aliases (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_aliasing_run_state_set_aliases *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_aliasing_run_set_aliases:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Aliases: Used to pass an 'in' argument: A dictionary mapping integer handles of contacts           to strings of the new alias to set.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method SetAliases and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Request that the alias of the given contact be changed. Success will be         indicated by emitting an &lt;tp:member-ref&gt;AliasesChanged&lt;/tp:member-ref&gt;         signal. On connections where the CONNECTION_ALIAS_FLAG_USER_SET flag is         not set, this method will only ever succeed if the contact is the         user&apos;s own handle (as returned by &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection.GetSelfHandle&lt;/tp:dbus-ref&gt;).
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_aliasing_run_set_aliases (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Aliases,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_ALIASING;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_aliasing_run_state_set_aliases state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "SetAliases", iface,
      _tp_cli_connection_interface_aliasing_finish_running_set_aliases,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "SetAliases",
          _tp_cli_connection_interface_aliasing_collect_callback_set_aliases,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_STRING)), in_Aliases,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


static inline void
tp_cli_add_signals_for_connection_interface_avatars (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "AvatarUpdated",
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "AvatarRetrieved",
      G_TYPE_UINT,
      G_TYPE_STRING,
      dbus_g_type_get_collection ("GArray", G_TYPE_UCHAR),
      G_TYPE_STRING,
      G_TYPE_INVALID);
}


/**
 * tp_cli_connection_interface_avatars_signal_callback_avatar_updated:
 * @proxy: The proxy on which tp_cli_connection_interface_avatars_connect_to_avatar_updated ()
 *  was called
 * @arg_Contact: An integer handle for the contact whose avatar has changed
 * @arg_New_Avatar_Token: Unique token for their new avatar
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal AvatarUpdated.
 */
static void
_tp_cli_connection_interface_avatars_collect_args_of_avatar_updated (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Contact,
    const gchar *arg_New_Avatar_Token,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (2);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 2; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, arg_Contact);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_STRING);
  g_value_set_string (args->values + 1, arg_New_Avatar_Token);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_interface_avatars_invoke_callback_for_avatar_updated (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_avatars_signal_callback_avatar_updated callback =
      (tp_cli_connection_interface_avatars_signal_callback_avatar_updated) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      g_value_get_string (args->values + 1),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_interface_avatars_connect_to_avatar_updated:
 * @proxy: A #TpConnection or subclass
 * @callback: Callback to be called when the signal is
 *   received
 * @user_data: User-supplied data for the callback
 * @destroy: Destructor for the user-supplied data, which
 *   will be called when this signal is disconnected, or
 *   before this function returns %NULL
 * @weak_object: A #GObject which will be weakly referenced; 
 *   if it is destroyed, this callback will automatically be
 *   disconnected
 * @error: If not %NULL, used to raise an error if %NULL is
 *   returned
 *
 * Connect a handler to the signal AvatarUpdated.
 *
 * Emitted when the avatar for a contact has been updated, or first         discovered on this connection. If the token differs from the token         associated with the client&apos;s cached avatar for this contact, the new         avatar should be requested with         &lt;tp:member-ref&gt;RequestAvatars&lt;/tp:member-ref&gt;.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_interface_avatars_connect_to_avatar_updated (TpConnection *proxy,
    tp_cli_connection_interface_avatars_signal_callback_avatar_updated callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS, "AvatarUpdated",
      expected_types,
      G_CALLBACK (_tp_cli_connection_interface_avatars_collect_args_of_avatar_updated),
      _tp_cli_connection_interface_avatars_invoke_callback_for_avatar_updated,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_interface_avatars_signal_callback_avatar_retrieved:
 * @proxy: The proxy on which tp_cli_connection_interface_avatars_connect_to_avatar_retrieved ()
 *  was called
 * @arg_Contact: The contact whose avatar has been retrieved
 * @arg_Token: The token corresponding to the avatar
 * @arg_Avatar: An array of bytes containing the image data
 * @arg_Type: A string containing the image MIME type (eg image/jpeg), or empty if           unknown
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal AvatarRetrieved.
 */
static void
_tp_cli_connection_interface_avatars_collect_args_of_avatar_retrieved (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Contact,
    const gchar *arg_Token,
    const GArray *arg_Avatar,
    const gchar *arg_Type,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (4);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 4; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, arg_Contact);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_STRING);
  g_value_set_string (args->values + 1, arg_Token);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, dbus_g_type_get_collection ("GArray", G_TYPE_UCHAR));
  g_value_set_boxed (args->values + 2, arg_Avatar);

  g_value_unset (args->values + 3);
  g_value_init (args->values + 3, G_TYPE_STRING);
  g_value_set_string (args->values + 3, arg_Type);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_interface_avatars_invoke_callback_for_avatar_retrieved (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_avatars_signal_callback_avatar_retrieved callback =
      (tp_cli_connection_interface_avatars_signal_callback_avatar_retrieved) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      g_value_get_string (args->values + 1),
      g_value_get_boxed (args->values + 2),
      g_value_get_string (args->values + 3),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_interface_avatars_connect_to_avatar_retrieved:
 * @proxy: A #TpConnection or subclass
 * @callback: Callback to be called when the signal is
 *   received
 * @user_data: User-supplied data for the callback
 * @destroy: Destructor for the user-supplied data, which
 *   will be called when this signal is disconnected, or
 *   before this function returns %NULL
 * @weak_object: A #GObject which will be weakly referenced; 
 *   if it is destroyed, this callback will automatically be
 *   disconnected
 * @error: If not %NULL, used to raise an error if %NULL is
 *   returned
 *
 * Connect a handler to the signal AvatarRetrieved.
 *
 * Emitted when the avatar for a contact has been retrieved.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_interface_avatars_connect_to_avatar_retrieved (TpConnection *proxy,
    tp_cli_connection_interface_avatars_signal_callback_avatar_retrieved callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[5] = {
      G_TYPE_UINT,
      G_TYPE_STRING,
      dbus_g_type_get_collection ("GArray", G_TYPE_UCHAR),
      G_TYPE_STRING,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS, "AvatarRetrieved",
      expected_types,
      G_CALLBACK (_tp_cli_connection_interface_avatars_collect_args_of_avatar_retrieved),
      _tp_cli_connection_interface_avatars_invoke_callback_for_avatar_retrieved,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_interface_avatars_callback_for_get_avatar_requirements:
 * @proxy: the proxy on which the call was made
 * @out_MIME_Types: Used to return an 'out' argument if @error is %NULL: An array of supported MIME types (eg image/jpeg)
 * @out_Min_Width: Used to return an 'out' argument if @error is %NULL: The minimum image width in pixels
 * @out_Min_Height: Used to return an 'out' argument if @error is %NULL: The minimum image height in pixels
 * @out_Max_Width: Used to return an 'out' argument if @error is %NULL: The maximum image width in pixels, or 0 if there is no limit
 * @out_Max_Height: Used to return an 'out' argument if @error is %NULL: The maximum image height in pixels, or 0 if there is no limit
 * @out_Max_Bytes: Used to return an 'out' argument if @error is %NULL: The maximum image size in bytes, or 0 if there is no limit
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetAvatarRequirements method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_avatars_collect_callback_get_avatar_requirements (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar **out_MIME_Types;
  guint out_Min_Width;
  guint out_Min_Height;
  guint out_Max_Width;
  guint out_Max_Height;
  guint out_Max_Bytes;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRV, &out_MIME_Types,
      G_TYPE_UINT, &out_Min_Width,
      G_TYPE_UINT, &out_Min_Height,
      G_TYPE_UINT, &out_Max_Width,
      G_TYPE_UINT, &out_Max_Height,
      G_TYPE_UINT, &out_Max_Bytes,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (6);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 6; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_STRV);
  g_value_take_boxed (args->values + 0, out_MIME_Types);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, out_Min_Width);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, G_TYPE_UINT);
  g_value_set_uint (args->values + 2, out_Min_Height);

  g_value_unset (args->values + 3);
  g_value_init (args->values + 3, G_TYPE_UINT);
  g_value_set_uint (args->values + 3, out_Max_Width);

  g_value_unset (args->values + 4);
  g_value_init (args->values + 4, G_TYPE_UINT);
  g_value_set_uint (args->values + 4, out_Max_Height);

  g_value_unset (args->values + 5);
  g_value_init (args->values + 5, G_TYPE_UINT);
  g_value_set_uint (args->values + 5, out_Max_Bytes);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_avatars_invoke_callback_get_avatar_requirements (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_avatars_callback_for_get_avatar_requirements callback = (tp_cli_connection_interface_avatars_callback_for_get_avatar_requirements) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          0,
          0,
          0,
          0,
          0,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      g_value_get_uint (args->values + 1),
      g_value_get_uint (args->values + 2),
      g_value_get_uint (args->values + 3),
      g_value_get_uint (args->values + 4),
      g_value_get_uint (args->values + 5),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_avatars_call_get_avatar_requirements:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetAvatarRequirements method call.
 *
 * Get the required format of avatars on this connection.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_avatars_call_get_avatar_requirements (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_interface_avatars_callback_for_get_avatar_requirements callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            NULL,
            0,
            0,
            0,
            0,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetAvatarRequirements",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetAvatarRequirements", iface,
          _tp_cli_connection_interface_avatars_invoke_callback_get_avatar_requirements,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetAvatarRequirements",
              _tp_cli_connection_interface_avatars_collect_callback_get_avatar_requirements,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gchar ***out_MIME_Types;
    guint *out_Min_Width;
    guint *out_Min_Height;
    guint *out_Max_Width;
    guint *out_Max_Height;
    guint *out_Max_Bytes;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_avatars_run_state_get_avatar_requirements;
static void
_tp_cli_connection_interface_avatars_finish_running_get_avatar_requirements (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_avatars_run_state_get_avatar_requirements *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_MIME_Types != NULL)
    *state->out_MIME_Types = g_value_dup_boxed (args->values + 0);

  if (state->out_Min_Width != NULL)
    *state->out_Min_Width = g_value_get_uint (args->values + 1);

  if (state->out_Min_Height != NULL)
    *state->out_Min_Height = g_value_get_uint (args->values + 2);

  if (state->out_Max_Width != NULL)
    *state->out_Max_Width = g_value_get_uint (args->values + 3);

  if (state->out_Max_Height != NULL)
    *state->out_Max_Height = g_value_get_uint (args->values + 4);

  if (state->out_Max_Bytes != NULL)
    *state->out_Max_Bytes = g_value_get_uint (args->values + 5);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_avatars_run_get_avatar_requirements:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_MIME_Types: Used to return an 'out' argument if %TRUE is returned: An array of supported MIME types (eg image/jpeg)
 * @out_Min_Width: Used to return an 'out' argument if %TRUE is returned: The minimum image width in pixels
 * @out_Min_Height: Used to return an 'out' argument if %TRUE is returned: The minimum image height in pixels
 * @out_Max_Width: Used to return an 'out' argument if %TRUE is returned: The maximum image width in pixels, or 0 if there is no limit
 * @out_Max_Height: Used to return an 'out' argument if %TRUE is returned: The maximum image height in pixels, or 0 if there is no limit
 * @out_Max_Bytes: Used to return an 'out' argument if %TRUE is returned: The maximum image size in bytes, or 0 if there is no limit
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetAvatarRequirements and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Get the required format of avatars on this connection.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_avatars_run_get_avatar_requirements (TpConnection *proxy,
    gint timeout_ms,
    gchar ***out_MIME_Types,
    guint *out_Min_Width,
    guint *out_Min_Height,
    guint *out_Max_Width,
    guint *out_Max_Height,
    guint *out_Max_Bytes,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_avatars_run_state_get_avatar_requirements state = {
      NULL /* loop */, error,
    out_MIME_Types,
    out_Min_Width,
    out_Min_Height,
    out_Max_Width,
    out_Max_Height,
    out_Max_Bytes,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetAvatarRequirements", iface,
      _tp_cli_connection_interface_avatars_finish_running_get_avatar_requirements,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetAvatarRequirements",
          _tp_cli_connection_interface_avatars_collect_callback_get_avatar_requirements,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_avatars_callback_for_get_avatar_tokens:
 * @proxy: the proxy on which the call was made
 * @out_Tokens: Used to return an 'out' argument if @error is %NULL: An array of avatar tokens or empty strings (if no avatar is set) in the           same order as the given array of contact handles
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetAvatarTokens method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_avatars_collect_callback_get_avatar_tokens (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar **out_Tokens;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRV, &out_Tokens,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_STRV);
  g_value_take_boxed (args->values + 0, out_Tokens);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_avatars_invoke_callback_get_avatar_tokens (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_avatars_callback_for_get_avatar_tokens callback = (tp_cli_connection_interface_avatars_callback_for_get_avatar_tokens) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_avatars_call_get_avatar_tokens:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contacts: Used to pass an 'in' argument: An array of handles representing contacts
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetAvatarTokens method call.
 *
 * Get the unique tokens for all of the given contacts&apos; avatars.          Using this method in new Telepathy clients is deprecated; use         &lt;tp:member-ref&gt;GetKnownAvatarTokens&lt;/tp:member-ref&gt; instead.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_avatars_call_get_avatar_tokens (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_avatars_callback_for_get_avatar_tokens callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            NULL,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetAvatarTokens",
          DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetAvatarTokens", iface,
          _tp_cli_connection_interface_avatars_invoke_callback_get_avatar_tokens,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetAvatarTokens",
              _tp_cli_connection_interface_avatars_collect_callback_get_avatar_tokens,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gchar ***out_Tokens;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_avatars_run_state_get_avatar_tokens;
static void
_tp_cli_connection_interface_avatars_finish_running_get_avatar_tokens (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_avatars_run_state_get_avatar_tokens *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Tokens != NULL)
    *state->out_Tokens = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_avatars_run_get_avatar_tokens:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contacts: Used to pass an 'in' argument: An array of handles representing contacts
 * @out_Tokens: Used to return an 'out' argument if %TRUE is returned: An array of avatar tokens or empty strings (if no avatar is set) in the           same order as the given array of contact handles
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetAvatarTokens and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Get the unique tokens for all of the given contacts&apos; avatars.          Using this method in new Telepathy clients is deprecated; use         &lt;tp:member-ref&gt;GetKnownAvatarTokens&lt;/tp:member-ref&gt; instead.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_avatars_run_get_avatar_tokens (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    gchar ***out_Tokens,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_avatars_run_state_get_avatar_tokens state = {
      NULL /* loop */, error,
    out_Tokens,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetAvatarTokens", iface,
      _tp_cli_connection_interface_avatars_finish_running_get_avatar_tokens,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetAvatarTokens",
          _tp_cli_connection_interface_avatars_collect_callback_get_avatar_tokens,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_avatars_callback_for_get_known_avatar_tokens:
 * @proxy: the proxy on which the call was made
 * @out_Tokens: Used to return an 'out' argument if @error is %NULL: A dictionary of handles mapped to avatar tokens, containing only           the known avatar tokens.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetKnownAvatarTokens method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_avatars_collect_callback_get_known_avatar_tokens (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GHashTable *out_Tokens;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_STRING)), &out_Tokens,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_STRING)));
  g_value_take_boxed (args->values + 0, out_Tokens);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_avatars_invoke_callback_get_known_avatar_tokens (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_avatars_callback_for_get_known_avatar_tokens callback = (tp_cli_connection_interface_avatars_callback_for_get_known_avatar_tokens) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_avatars_call_get_known_avatar_tokens:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contacts: Used to pass an 'in' argument: An array of handles representing contacts
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetKnownAvatarTokens method call.
 *
 * Get the unique tokens for the given contacts&apos; avatars. These tokens         can be persisted across connections, and should be used by the client         to check whether the avatars have been updated.  For handles other than         the self handle, only tokens that are already known are returned; an         empty token means the given contact has no avatar.  However, a CM must         always have the tokens for the self handle if one is set (even if it is         set to no avatar).  On protocols where the avatar does not persist         between connections, a CM should omit the self handle from the returned         map until an avatar is explicitly set or cleared.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_avatars_call_get_known_avatar_tokens (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_avatars_callback_for_get_known_avatar_tokens callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetKnownAvatarTokens",
          DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetKnownAvatarTokens", iface,
          _tp_cli_connection_interface_avatars_invoke_callback_get_known_avatar_tokens,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetKnownAvatarTokens",
              _tp_cli_connection_interface_avatars_collect_callback_get_known_avatar_tokens,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GHashTable **out_Tokens;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_avatars_run_state_get_known_avatar_tokens;
static void
_tp_cli_connection_interface_avatars_finish_running_get_known_avatar_tokens (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_avatars_run_state_get_known_avatar_tokens *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Tokens != NULL)
    *state->out_Tokens = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_avatars_run_get_known_avatar_tokens:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contacts: Used to pass an 'in' argument: An array of handles representing contacts
 * @out_Tokens: Used to return an 'out' argument if %TRUE is returned: A dictionary of handles mapped to avatar tokens, containing only           the known avatar tokens.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetKnownAvatarTokens and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Get the unique tokens for the given contacts&apos; avatars. These tokens         can be persisted across connections, and should be used by the client         to check whether the avatars have been updated.  For handles other than         the self handle, only tokens that are already known are returned; an         empty token means the given contact has no avatar.  However, a CM must         always have the tokens for the self handle if one is set (even if it is         set to no avatar).  On protocols where the avatar does not persist         between connections, a CM should omit the self handle from the returned         map until an avatar is explicitly set or cleared.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_avatars_run_get_known_avatar_tokens (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    GHashTable **out_Tokens,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_avatars_run_state_get_known_avatar_tokens state = {
      NULL /* loop */, error,
    out_Tokens,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetKnownAvatarTokens", iface,
      _tp_cli_connection_interface_avatars_finish_running_get_known_avatar_tokens,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetKnownAvatarTokens",
          _tp_cli_connection_interface_avatars_collect_callback_get_known_avatar_tokens,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_avatars_callback_for_request_avatar:
 * @proxy: the proxy on which the call was made
 * @out_Data: Used to return an 'out' argument if @error is %NULL: An array of bytes containing the image data
 * @out_MIME_Type: Used to return an 'out' argument if @error is %NULL: A string containing the image MIME type (eg image/jpeg), or empty if         unknown
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RequestAvatar method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_avatars_collect_callback_request_avatar (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GArray *out_Data;
  gchar *out_MIME_Type;

  dbus_g_proxy_end_call (proxy, call, &error,
      dbus_g_type_get_collection ("GArray", G_TYPE_UCHAR), &out_Data,
      G_TYPE_STRING, &out_MIME_Type,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (2);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 2; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, dbus_g_type_get_collection ("GArray", G_TYPE_UCHAR));
  g_value_take_boxed (args->values + 0, out_Data);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_STRING);
  g_value_take_string (args->values + 1, out_MIME_Type);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_avatars_invoke_callback_request_avatar (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_avatars_callback_for_request_avatar callback = (tp_cli_connection_interface_avatars_callback_for_request_avatar) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      g_value_get_string (args->values + 1),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_avatars_call_request_avatar:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contact: Used to pass an 'in' argument: An integer handle for the contact to request the avatar for
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a RequestAvatar method call.
 *
 * Request the avatar for a given contact. Using this method in new         Telepathy clients is deprecated; use RequestAvatars instead.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_avatars_call_request_avatar (TpConnection *proxy,
    gint timeout_ms,
    guint in_Contact,
    tp_cli_connection_interface_avatars_callback_for_request_avatar callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            NULL,
            NULL,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "RequestAvatar",
          G_TYPE_UINT, in_Contact,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RequestAvatar", iface,
          _tp_cli_connection_interface_avatars_invoke_callback_request_avatar,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RequestAvatar",
              _tp_cli_connection_interface_avatars_collect_callback_request_avatar,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Contact,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GArray **out_Data;
    gchar **out_MIME_Type;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_avatars_run_state_request_avatar;
static void
_tp_cli_connection_interface_avatars_finish_running_request_avatar (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_avatars_run_state_request_avatar *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Data != NULL)
    *state->out_Data = g_value_dup_boxed (args->values + 0);

  if (state->out_MIME_Type != NULL)
    *state->out_MIME_Type = g_value_dup_string (args->values + 1);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_avatars_run_request_avatar:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contact: Used to pass an 'in' argument: An integer handle for the contact to request the avatar for
 * @out_Data: Used to return an 'out' argument if %TRUE is returned: An array of bytes containing the image data
 * @out_MIME_Type: Used to return an 'out' argument if %TRUE is returned: A string containing the image MIME type (eg image/jpeg), or empty if         unknown
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RequestAvatar and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Request the avatar for a given contact. Using this method in new         Telepathy clients is deprecated; use RequestAvatars instead.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_avatars_run_request_avatar (TpConnection *proxy,
    gint timeout_ms,
    guint in_Contact,
    GArray **out_Data,
    gchar **out_MIME_Type,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_avatars_run_state_request_avatar state = {
      NULL /* loop */, error,
    out_Data,
    out_MIME_Type,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RequestAvatar", iface,
      _tp_cli_connection_interface_avatars_finish_running_request_avatar,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RequestAvatar",
          _tp_cli_connection_interface_avatars_collect_callback_request_avatar,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Contact,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_avatars_callback_for_request_avatars:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RequestAvatars method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_avatars_collect_callback_request_avatars (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_interface_avatars_invoke_callback_request_avatars (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_avatars_callback_for_request_avatars callback = (tp_cli_connection_interface_avatars_callback_for_request_avatars) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_avatars_call_request_avatars:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contacts: Used to pass an 'in' argument: The contacts to retrieve avatars for
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a RequestAvatars method call.
 *
 * Request avatars for a number of contacts. The         &lt;tp:member-ref&gt;AvatarRetrieved&lt;/tp:member-ref&gt; signal is emitted for         each avatar retrieved. If the handles are valid but retrieving an         avatar fails (for any reason, including the contact not having an         avatar) the AvatarRetrieved signal is not emitted for that contact.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_avatars_call_request_avatars (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_avatars_callback_for_request_avatars callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "RequestAvatars",
          DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RequestAvatars", iface,
          _tp_cli_connection_interface_avatars_invoke_callback_request_avatars,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RequestAvatars",
              _tp_cli_connection_interface_avatars_collect_callback_request_avatars,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_avatars_run_state_request_avatars;
static void
_tp_cli_connection_interface_avatars_finish_running_request_avatars (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_avatars_run_state_request_avatars *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_avatars_run_request_avatars:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contacts: Used to pass an 'in' argument: The contacts to retrieve avatars for
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RequestAvatars and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Request avatars for a number of contacts. The         &lt;tp:member-ref&gt;AvatarRetrieved&lt;/tp:member-ref&gt; signal is emitted for         each avatar retrieved. If the handles are valid but retrieving an         avatar fails (for any reason, including the contact not having an         avatar) the AvatarRetrieved signal is not emitted for that contact.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_avatars_run_request_avatars (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_avatars_run_state_request_avatars state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RequestAvatars", iface,
      _tp_cli_connection_interface_avatars_finish_running_request_avatars,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RequestAvatars",
          _tp_cli_connection_interface_avatars_collect_callback_request_avatars,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_avatars_callback_for_set_avatar:
 * @proxy: the proxy on which the call was made
 * @out_Token: Used to return an 'out' argument if @error is %NULL: The string token of the new avatar
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a SetAvatar method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_avatars_collect_callback_set_avatar (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_Token;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRING, &out_Token,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_STRING);
  g_value_take_string (args->values + 0, out_Token);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_avatars_invoke_callback_set_avatar (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_avatars_callback_for_set_avatar callback = (tp_cli_connection_interface_avatars_callback_for_set_avatar) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_string (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_avatars_call_set_avatar:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Avatar: Used to pass an 'in' argument: An array of bytes representing the avatar image data
 * @in_MIME_Type: Used to pass an 'in' argument: A string representing the image MIME type
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a SetAvatar method call.
 *
 * Set a new avatar image for this connection. The avatar image must         respect the requirements obtained by         &lt;tp:member-ref&gt;GetAvatarRequirements&lt;/tp:member-ref&gt;.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_avatars_call_set_avatar (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Avatar,
    const gchar *in_MIME_Type,
    tp_cli_connection_interface_avatars_callback_for_set_avatar callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            NULL,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "SetAvatar",
          dbus_g_type_get_collection ("GArray", G_TYPE_UCHAR), in_Avatar,
          G_TYPE_STRING, in_MIME_Type,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "SetAvatar", iface,
          _tp_cli_connection_interface_avatars_invoke_callback_set_avatar,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "SetAvatar",
              _tp_cli_connection_interface_avatars_collect_callback_set_avatar,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              dbus_g_type_get_collection ("GArray", G_TYPE_UCHAR), in_Avatar,
              G_TYPE_STRING, in_MIME_Type,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gchar **out_Token;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_avatars_run_state_set_avatar;
static void
_tp_cli_connection_interface_avatars_finish_running_set_avatar (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_avatars_run_state_set_avatar *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Token != NULL)
    *state->out_Token = g_value_dup_string (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_avatars_run_set_avatar:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Avatar: Used to pass an 'in' argument: An array of bytes representing the avatar image data
 * @in_MIME_Type: Used to pass an 'in' argument: A string representing the image MIME type
 * @out_Token: Used to return an 'out' argument if %TRUE is returned: The string token of the new avatar
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method SetAvatar and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Set a new avatar image for this connection. The avatar image must         respect the requirements obtained by         &lt;tp:member-ref&gt;GetAvatarRequirements&lt;/tp:member-ref&gt;.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_avatars_run_set_avatar (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Avatar,
    const gchar *in_MIME_Type,
    gchar **out_Token,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_avatars_run_state_set_avatar state = {
      NULL /* loop */, error,
    out_Token,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "SetAvatar", iface,
      _tp_cli_connection_interface_avatars_finish_running_set_avatar,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "SetAvatar",
          _tp_cli_connection_interface_avatars_collect_callback_set_avatar,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              dbus_g_type_get_collection ("GArray", G_TYPE_UCHAR), in_Avatar,
              G_TYPE_STRING, in_MIME_Type,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_avatars_callback_for_clear_avatar:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a ClearAvatar method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_avatars_collect_callback_clear_avatar (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_interface_avatars_invoke_callback_clear_avatar (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_avatars_callback_for_clear_avatar callback = (tp_cli_connection_interface_avatars_callback_for_clear_avatar) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_avatars_call_clear_avatar:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a ClearAvatar method call.
 *
 * Remove the avatar image for this connection.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_avatars_call_clear_avatar (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_interface_avatars_callback_for_clear_avatar callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "ClearAvatar",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "ClearAvatar", iface,
          _tp_cli_connection_interface_avatars_invoke_callback_clear_avatar,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "ClearAvatar",
              _tp_cli_connection_interface_avatars_collect_callback_clear_avatar,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_avatars_run_state_clear_avatar;
static void
_tp_cli_connection_interface_avatars_finish_running_clear_avatar (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_avatars_run_state_clear_avatar *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_avatars_run_clear_avatar:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method ClearAvatar and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Remove the avatar image for this connection.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_avatars_run_clear_avatar (TpConnection *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_avatars_run_state_clear_avatar state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "ClearAvatar", iface,
      _tp_cli_connection_interface_avatars_finish_running_clear_avatar,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "ClearAvatar",
          _tp_cli_connection_interface_avatars_collect_callback_clear_avatar,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


static inline void
tp_cli_add_signals_for_connection_interface_capabilities (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "CapabilitiesChanged",
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))),
      G_TYPE_INVALID);
}


/**
 * tp_cli_connection_interface_capabilities_signal_callback_capabilities_changed:
 * @proxy: The proxy on which tp_cli_connection_interface_capabilities_connect_to_capabilities_changed ()
 *  was called
 * @arg_Caps: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structures containing:           &lt;ul&gt;             &lt;li&gt;an integer handle representing the contact&lt;/li&gt;             &lt;li&gt;a string channel type&lt;/li&gt;             &lt;li&gt;a bitwise OR of the contact&apos;s old generic capability flags&lt;/li&gt;             &lt;li&gt;a bitwise OR of the contact&apos;s new generic capability flags&lt;/li&gt;             &lt;li&gt;a bitwise OR of the contact&apos;s old type specific capability flags&lt;/li&gt;             &lt;li&gt;a bitwise OR of the contact&apos;s new type specific capability flags&lt;/li&gt;           &lt;/ul&gt;
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal CapabilitiesChanged.
 */
static void
_tp_cli_connection_interface_capabilities_collect_args_of_capabilities_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    const GPtrArray *arg_Caps,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))));
  g_value_set_boxed (args->values + 0, arg_Caps);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_interface_capabilities_invoke_callback_for_capabilities_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_capabilities_signal_callback_capabilities_changed callback =
      (tp_cli_connection_interface_capabilities_signal_callback_capabilities_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_interface_capabilities_connect_to_capabilities_changed:
 * @proxy: A #TpConnection or subclass
 * @callback: Callback to be called when the signal is
 *   received
 * @user_data: User-supplied data for the callback
 * @destroy: Destructor for the user-supplied data, which
 *   will be called when this signal is disconnected, or
 *   before this function returns %NULL
 * @weak_object: A #GObject which will be weakly referenced; 
 *   if it is destroyed, this callback will automatically be
 *   disconnected
 * @error: If not %NULL, used to raise an error if %NULL is
 *   returned
 *
 * Connect a handler to the signal CapabilitiesChanged.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Announce that there has been a change of capabilities on the           given handle.&lt;/p&gt;          &lt;p&gt;If the handle is zero, the capabilities refer to the connection           itself, in some poorly defined way. This usage is deprecated and           clients should ignore it.&lt;/p&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_interface_capabilities_connect_to_capabilities_changed (TpConnection *proxy,
    tp_cli_connection_interface_capabilities_signal_callback_capabilities_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION_INTERFACE_CAPABILITIES, "CapabilitiesChanged",
      expected_types,
      G_CALLBACK (_tp_cli_connection_interface_capabilities_collect_args_of_capabilities_changed),
      _tp_cli_connection_interface_capabilities_invoke_callback_for_capabilities_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_interface_capabilities_callback_for_advertise_capabilities:
 * @proxy: the proxy on which the call was made
 * @out_Self_Capabilities: Used to return an 'out' argument if @error is %NULL: An array of structures describing the current capabilities containing:           &lt;ul&gt;             &lt;li&gt;a string channel type&lt;/li&gt;             &lt;li&gt;a bitwise OR of type specific capability flags&lt;/li&gt;           &lt;/ul&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a AdvertiseCapabilities method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_capabilities_collect_callback_advertise_capabilities (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GPtrArray *out_Self_Capabilities;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, G_TYPE_UINT, G_TYPE_INVALID)))), &out_Self_Capabilities,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, G_TYPE_UINT, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Self_Capabilities);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_capabilities_invoke_callback_advertise_capabilities (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_capabilities_callback_for_advertise_capabilities callback = (tp_cli_connection_interface_capabilities_callback_for_advertise_capabilities) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_capabilities_call_advertise_capabilities:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Add: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structures containing:           &lt;ul&gt;             &lt;li&gt;a string channel type&lt;/li&gt;             &lt;li&gt;a bitwise OR of type specific capability flags&lt;/li&gt;           &lt;/ul&gt;
 * @in_Remove: Used to pass an 'in' argument: An array of D-Bus interface names of channel types to remove
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a AdvertiseCapabilities method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Used by user interfaces to indicate which channel types they are able         to handle on this connection. Because these may be provided by         different client processes, this method accepts channel types to add         and remove from the set already advertised on this connection. The type         of advertised capabilities (create versus invite) is protocol-dependent         and hence cannot be set by the this method. In the case of a client         adding an already advertised channel type but with new channel type         specific flags, the connection manager should simply add the new flags         to the set of advertised capabilities.&lt;/p&gt;          &lt;p&gt;Upon a successful invocation of this method, the         &lt;tp:member-ref&gt;CapabilitiesChanged&lt;/tp:member-ref&gt;         signal will be emitted for the user&apos;s own handle ( &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection.GetSelfHandle&lt;/tp:dbus-ref&gt;)         by the connection manager to indicate the changes         that have been made.  This signal should also be monitored to ensure         that the set is kept accurate - for example, a client may remove         capabilities or type specific capability flags when it exits         which are still provided by another client.&lt;/p&gt;          &lt;p&gt;On connections managed by the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelDispatcher&lt;/tp:dbus-ref&gt;,           this method SHOULD NOT be used by clients other than the           ChannelDispatcher itself.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_capabilities_call_advertise_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GPtrArray *in_Add,
    const gchar **in_Remove,
    tp_cli_connection_interface_capabilities_callback_for_advertise_capabilities callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_CAPABILITIES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            NULL,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "AdvertiseCapabilities",
          (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, G_TYPE_UINT, G_TYPE_INVALID)))), in_Add,
          G_TYPE_STRV, in_Remove,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "AdvertiseCapabilities", iface,
          _tp_cli_connection_interface_capabilities_invoke_callback_advertise_capabilities,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "AdvertiseCapabilities",
              _tp_cli_connection_interface_capabilities_collect_callback_advertise_capabilities,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, G_TYPE_UINT, G_TYPE_INVALID)))), in_Add,
              G_TYPE_STRV, in_Remove,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GPtrArray **out_Self_Capabilities;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_capabilities_run_state_advertise_capabilities;
static void
_tp_cli_connection_interface_capabilities_finish_running_advertise_capabilities (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_capabilities_run_state_advertise_capabilities *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Self_Capabilities != NULL)
    *state->out_Self_Capabilities = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_capabilities_run_advertise_capabilities:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Add: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structures containing:           &lt;ul&gt;             &lt;li&gt;a string channel type&lt;/li&gt;             &lt;li&gt;a bitwise OR of type specific capability flags&lt;/li&gt;           &lt;/ul&gt;
 * @in_Remove: Used to pass an 'in' argument: An array of D-Bus interface names of channel types to remove
 * @out_Self_Capabilities: Used to return an 'out' argument if %TRUE is returned: An array of structures describing the current capabilities containing:           &lt;ul&gt;             &lt;li&gt;a string channel type&lt;/li&gt;             &lt;li&gt;a bitwise OR of type specific capability flags&lt;/li&gt;           &lt;/ul&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method AdvertiseCapabilities and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Used by user interfaces to indicate which channel types they are able         to handle on this connection. Because these may be provided by         different client processes, this method accepts channel types to add         and remove from the set already advertised on this connection. The type         of advertised capabilities (create versus invite) is protocol-dependent         and hence cannot be set by the this method. In the case of a client         adding an already advertised channel type but with new channel type         specific flags, the connection manager should simply add the new flags         to the set of advertised capabilities.&lt;/p&gt;          &lt;p&gt;Upon a successful invocation of this method, the         &lt;tp:member-ref&gt;CapabilitiesChanged&lt;/tp:member-ref&gt;         signal will be emitted for the user&apos;s own handle ( &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection.GetSelfHandle&lt;/tp:dbus-ref&gt;)         by the connection manager to indicate the changes         that have been made.  This signal should also be monitored to ensure         that the set is kept accurate - for example, a client may remove         capabilities or type specific capability flags when it exits         which are still provided by another client.&lt;/p&gt;          &lt;p&gt;On connections managed by the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelDispatcher&lt;/tp:dbus-ref&gt;,           this method SHOULD NOT be used by clients other than the           ChannelDispatcher itself.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_capabilities_run_advertise_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GPtrArray *in_Add,
    const gchar **in_Remove,
    GPtrArray **out_Self_Capabilities,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_CAPABILITIES;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_capabilities_run_state_advertise_capabilities state = {
      NULL /* loop */, error,
    out_Self_Capabilities,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "AdvertiseCapabilities", iface,
      _tp_cli_connection_interface_capabilities_finish_running_advertise_capabilities,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "AdvertiseCapabilities",
          _tp_cli_connection_interface_capabilities_collect_callback_advertise_capabilities,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, G_TYPE_UINT, G_TYPE_INVALID)))), in_Add,
              G_TYPE_STRV, in_Remove,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_capabilities_callback_for_get_capabilities:
 * @proxy: the proxy on which the call was made
 * @out_Contact_Capabilities: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structures containing:           &lt;ul&gt;             &lt;li&gt;an integer handle representing the contact&lt;/li&gt;             &lt;li&gt;a string channel type&lt;/li&gt;             &lt;li&gt;a bitwise OR of generic capability flags for the type&lt;/li&gt;             &lt;li&gt;a bitwise OR of type specific capability flags for the type&lt;/li&gt;           &lt;/ul&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetCapabilities method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_capabilities_collect_callback_get_capabilities (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GPtrArray *out_Contact_Capabilities;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))), &out_Contact_Capabilities,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Contact_Capabilities);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_capabilities_invoke_callback_get_capabilities (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_capabilities_callback_for_get_capabilities callback = (tp_cli_connection_interface_capabilities_callback_for_get_capabilities) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_capabilities_call_get_capabilities:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Handles: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;An array of contact handles for this connection.&lt;/p&gt;            &lt;p&gt;This may include zero, which originally meant a query for             capabilities available on the connection itself. This usage             is deprecated; clients SHOULD NOT do this, and connection managers             SHOULD proceed as though zero had not been present in this             list.&lt;/p&gt;
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetCapabilities method call.
 *
 * Returns an array of capabilities for the given contact handles.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_capabilities_call_get_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Handles,
    tp_cli_connection_interface_capabilities_callback_for_get_capabilities callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_CAPABILITIES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            NULL,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetCapabilities",
          DBUS_TYPE_G_UINT_ARRAY, in_Handles,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetCapabilities", iface,
          _tp_cli_connection_interface_capabilities_invoke_callback_get_capabilities,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetCapabilities",
              _tp_cli_connection_interface_capabilities_collect_callback_get_capabilities,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Handles,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GPtrArray **out_Contact_Capabilities;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_capabilities_run_state_get_capabilities;
static void
_tp_cli_connection_interface_capabilities_finish_running_get_capabilities (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_capabilities_run_state_get_capabilities *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Contact_Capabilities != NULL)
    *state->out_Contact_Capabilities = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_capabilities_run_get_capabilities:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Handles: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;An array of contact handles for this connection.&lt;/p&gt;            &lt;p&gt;This may include zero, which originally meant a query for             capabilities available on the connection itself. This usage             is deprecated; clients SHOULD NOT do this, and connection managers             SHOULD proceed as though zero had not been present in this             list.&lt;/p&gt;
 * @out_Contact_Capabilities: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structures containing:           &lt;ul&gt;             &lt;li&gt;an integer handle representing the contact&lt;/li&gt;             &lt;li&gt;a string channel type&lt;/li&gt;             &lt;li&gt;a bitwise OR of generic capability flags for the type&lt;/li&gt;             &lt;li&gt;a bitwise OR of type specific capability flags for the type&lt;/li&gt;           &lt;/ul&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetCapabilities and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns an array of capabilities for the given contact handles.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_capabilities_run_get_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Handles,
    GPtrArray **out_Contact_Capabilities,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_CAPABILITIES;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_capabilities_run_state_get_capabilities state = {
      NULL /* loop */, error,
    out_Contact_Capabilities,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetCapabilities", iface,
      _tp_cli_connection_interface_capabilities_finish_running_get_capabilities,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetCapabilities",
          _tp_cli_connection_interface_capabilities_collect_callback_get_capabilities,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Handles,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


static inline void
tp_cli_add_signals_for_connection_interface_contact_capabilities (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "ContactCapabilitiesChanged",
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_STRV, G_TYPE_INVALID)))))),
      G_TYPE_INVALID);
}


/**
 * tp_cli_connection_interface_contact_capabilities_signal_callback_contact_capabilities_changed:
 * @proxy: The proxy on which tp_cli_connection_interface_contact_capabilities_connect_to_contact_capabilities_changed ()
 *  was called
 * @arg_caps: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           All the capabilities of the contacts
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal ContactCapabilitiesChanged.
 */
static void
_tp_cli_connection_interface_contact_capabilities_collect_args_of_contact_capabilities_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    GHashTable *arg_caps,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_STRV, G_TYPE_INVALID)))))));
  g_value_set_boxed (args->values + 0, arg_caps);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_interface_contact_capabilities_invoke_callback_for_contact_capabilities_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_contact_capabilities_signal_callback_contact_capabilities_changed callback =
      (tp_cli_connection_interface_contact_capabilities_signal_callback_contact_capabilities_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_interface_contact_capabilities_connect_to_contact_capabilities_changed:
 * @proxy: A #TpConnection or subclass
 * @callback: Callback to be called when the signal is
 *   received
 * @user_data: User-supplied data for the callback
 * @destroy: Destructor for the user-supplied data, which
 *   will be called when this signal is disconnected, or
 *   before this function returns %NULL
 * @weak_object: A #GObject which will be weakly referenced; 
 *   if it is destroyed, this callback will automatically be
 *   disconnected
 * @error: If not %NULL, used to raise an error if %NULL is
 *   returned
 *
 * Connect a handler to the signal ContactCapabilitiesChanged.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Announce that there has been a change of capabilities on the           given handles. A single signal can be emitted for several         contacts.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The underlying protocol can get several contacts&apos; capabilities at             the same time.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_interface_contact_capabilities_connect_to_contact_capabilities_changed (TpConnection *proxy,
    tp_cli_connection_interface_contact_capabilities_signal_callback_contact_capabilities_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_STRV, G_TYPE_INVALID)))))),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION_INTERFACE_CONTACT_CAPABILITIES, "ContactCapabilitiesChanged",
      expected_types,
      G_CALLBACK (_tp_cli_connection_interface_contact_capabilities_collect_args_of_contact_capabilities_changed),
      _tp_cli_connection_interface_contact_capabilities_invoke_callback_for_contact_capabilities_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_interface_contact_capabilities_callback_for_update_capabilities:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a UpdateCapabilities method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_contact_capabilities_collect_callback_update_capabilities (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_interface_contact_capabilities_invoke_callback_update_capabilities (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_contact_capabilities_callback_for_update_capabilities callback = (tp_cli_connection_interface_contact_capabilities_callback_for_update_capabilities) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_contact_capabilities_call_update_capabilities:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Handler_Capabilities: Used to pass an 'in' argument: &lt;p&gt;The capabilities of one or more clients.&lt;/p&gt;            &lt;p&gt;For each client in the given list, any capabilities previously             advertised for the same client name are discarded, then replaced by             the capabilities indicated.&lt;/p&gt;            &lt;p&gt;As a result, if a client becomes unavailable, this method SHOULD             be called with a &lt;tp:type&gt;Handler_Capabilities&lt;/tp:type&gt; structure             containing its name, an empty list of channel classes, and an             empty list of capabilities. When this is done, the connection             manager SHOULD free all memory associated with that client name.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This method takes a list of clients so that               when the channel dispatcher first calls it (with a list of all               the Handlers that are initially available), the changes can be               made atomically, with only one transmission of updated               capabilities to the network. Afterwards, the channel dispatcher               will call this method with a single-element list every time               a Handler becomes available or unavailable.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;The connection manager MUST ignore any channel classes and client             capabilities for which there is no representation in the protocol             or no support in the connection manager.&lt;/p&gt;
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a UpdateCapabilities method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Alter the connection&apos;s advertised capabilities to include           the intersection of the given clients&apos; capabilities with what the           connection manager is able to implement.&lt;/p&gt;          &lt;p&gt;On connections managed by the ChannelDispatcher, processes other           than the ChannelDispatcher SHOULD NOT call this method, and the           ChannelDispatcher SHOULD use this method to advertise the           capabilities of all the registered &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Client.Handler&lt;/tp:dbus-ref&gt;           implementations.On connections not managed by the ChannelDispatcher,           clients MAY use this method directly, to indicate the channels they           will handle and the extra capabilities they have.&lt;/p&gt;          &lt;p&gt;Upon a successful invocation of this method, the connection manager           will only emit the           &lt;tp:member-ref&gt;ContactCapabilitiesChanged&lt;/tp:member-ref&gt; signal           for the user&apos;s &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection&quot;&gt;SelfHandle&lt;/tp:dbus-ref&gt;           if, in the underlying protocol, the new capabilities are distinct           from the previous state.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The connection manager will essentially intersect the provided             capabilities and the channel classes it implements. Therefore,             certain properties which are never fixed for a channel class             (such as the target handle, or the Parameters property of a tube             channel) will almost certainly not be advertised.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;This method MAY be called on a newly-created connection while it           is still in the DISCONNECTED state, to request that when the           connection connects, it will do so with the appropriate           capabilities. Doing so MUST NOT fail.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_contact_capabilities_call_update_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GPtrArray *in_Handler_Capabilities,
    tp_cli_connection_interface_contact_capabilities_callback_for_update_capabilities callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_CONTACT_CAPABILITIES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "UpdateCapabilities",
          (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), G_TYPE_STRV, G_TYPE_INVALID)))), in_Handler_Capabilities,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "UpdateCapabilities", iface,
          _tp_cli_connection_interface_contact_capabilities_invoke_callback_update_capabilities,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "UpdateCapabilities",
              _tp_cli_connection_interface_contact_capabilities_collect_callback_update_capabilities,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), G_TYPE_STRV, G_TYPE_INVALID)))), in_Handler_Capabilities,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_contact_capabilities_run_state_update_capabilities;
static void
_tp_cli_connection_interface_contact_capabilities_finish_running_update_capabilities (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_contact_capabilities_run_state_update_capabilities *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_contact_capabilities_run_update_capabilities:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Handler_Capabilities: Used to pass an 'in' argument: &lt;p&gt;The capabilities of one or more clients.&lt;/p&gt;            &lt;p&gt;For each client in the given list, any capabilities previously             advertised for the same client name are discarded, then replaced by             the capabilities indicated.&lt;/p&gt;            &lt;p&gt;As a result, if a client becomes unavailable, this method SHOULD             be called with a &lt;tp:type&gt;Handler_Capabilities&lt;/tp:type&gt; structure             containing its name, an empty list of channel classes, and an             empty list of capabilities. When this is done, the connection             manager SHOULD free all memory associated with that client name.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This method takes a list of clients so that               when the channel dispatcher first calls it (with a list of all               the Handlers that are initially available), the changes can be               made atomically, with only one transmission of updated               capabilities to the network. Afterwards, the channel dispatcher               will call this method with a single-element list every time               a Handler becomes available or unavailable.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;The connection manager MUST ignore any channel classes and client             capabilities for which there is no representation in the protocol             or no support in the connection manager.&lt;/p&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method UpdateCapabilities and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Alter the connection&apos;s advertised capabilities to include           the intersection of the given clients&apos; capabilities with what the           connection manager is able to implement.&lt;/p&gt;          &lt;p&gt;On connections managed by the ChannelDispatcher, processes other           than the ChannelDispatcher SHOULD NOT call this method, and the           ChannelDispatcher SHOULD use this method to advertise the           capabilities of all the registered &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Client.Handler&lt;/tp:dbus-ref&gt;           implementations.On connections not managed by the ChannelDispatcher,           clients MAY use this method directly, to indicate the channels they           will handle and the extra capabilities they have.&lt;/p&gt;          &lt;p&gt;Upon a successful invocation of this method, the connection manager           will only emit the           &lt;tp:member-ref&gt;ContactCapabilitiesChanged&lt;/tp:member-ref&gt; signal           for the user&apos;s &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection&quot;&gt;SelfHandle&lt;/tp:dbus-ref&gt;           if, in the underlying protocol, the new capabilities are distinct           from the previous state.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The connection manager will essentially intersect the provided             capabilities and the channel classes it implements. Therefore,             certain properties which are never fixed for a channel class             (such as the target handle, or the Parameters property of a tube             channel) will almost certainly not be advertised.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;This method MAY be called on a newly-created connection while it           is still in the DISCONNECTED state, to request that when the           connection connects, it will do so with the appropriate           capabilities. Doing so MUST NOT fail.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_contact_capabilities_run_update_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GPtrArray *in_Handler_Capabilities,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_CONTACT_CAPABILITIES;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_contact_capabilities_run_state_update_capabilities state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "UpdateCapabilities", iface,
      _tp_cli_connection_interface_contact_capabilities_finish_running_update_capabilities,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "UpdateCapabilities",
          _tp_cli_connection_interface_contact_capabilities_collect_callback_update_capabilities,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), G_TYPE_STRV, G_TYPE_INVALID)))), in_Handler_Capabilities,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_contact_capabilities_callback_for_get_contact_capabilities:
 * @proxy: the proxy on which the call was made
 * @out_Contact_Capabilities: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structures containing:           &lt;ul&gt;             &lt;li&gt;a dictionary mapping the channel properties to their values.&lt;/li&gt;             &lt;li&gt;an array of additional allowed properties&lt;/li&gt;           &lt;/ul&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetContactCapabilities method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_contact_capabilities_collect_callback_get_contact_capabilities (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GHashTable *out_Contact_Capabilities;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_STRV, G_TYPE_INVALID)))))), &out_Contact_Capabilities,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_STRV, G_TYPE_INVALID)))))));
  g_value_take_boxed (args->values + 0, out_Contact_Capabilities);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_contact_capabilities_invoke_callback_get_contact_capabilities (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_contact_capabilities_callback_for_get_contact_capabilities callback = (tp_cli_connection_interface_contact_capabilities_callback_for_get_contact_capabilities) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_contact_capabilities_call_get_contact_capabilities:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_handles: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;An array of contact handles for this connection.&lt;/p&gt;            &lt;p&gt;The handle zero MUST NOT be included in the request.&lt;/p&gt;
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetContactCapabilities method call.
 *
 * Returns an array of enhanced capabilities for the given contact handles.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_contact_capabilities_call_get_contact_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_handles,
    tp_cli_connection_interface_contact_capabilities_callback_for_get_contact_capabilities callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_CONTACT_CAPABILITIES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetContactCapabilities",
          DBUS_TYPE_G_UINT_ARRAY, in_handles,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetContactCapabilities", iface,
          _tp_cli_connection_interface_contact_capabilities_invoke_callback_get_contact_capabilities,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetContactCapabilities",
              _tp_cli_connection_interface_contact_capabilities_collect_callback_get_contact_capabilities,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_handles,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GHashTable **out_Contact_Capabilities;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_contact_capabilities_run_state_get_contact_capabilities;
static void
_tp_cli_connection_interface_contact_capabilities_finish_running_get_contact_capabilities (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_contact_capabilities_run_state_get_contact_capabilities *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Contact_Capabilities != NULL)
    *state->out_Contact_Capabilities = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_contact_capabilities_run_get_contact_capabilities:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_handles: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;An array of contact handles for this connection.&lt;/p&gt;            &lt;p&gt;The handle zero MUST NOT be included in the request.&lt;/p&gt;
 * @out_Contact_Capabilities: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structures containing:           &lt;ul&gt;             &lt;li&gt;a dictionary mapping the channel properties to their values.&lt;/li&gt;             &lt;li&gt;an array of additional allowed properties&lt;/li&gt;           &lt;/ul&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetContactCapabilities and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns an array of enhanced capabilities for the given contact handles.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_contact_capabilities_run_get_contact_capabilities (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_handles,
    GHashTable **out_Contact_Capabilities,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_CONTACT_CAPABILITIES;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_contact_capabilities_run_state_get_contact_capabilities state = {
      NULL /* loop */, error,
    out_Contact_Capabilities,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetContactCapabilities", iface,
      _tp_cli_connection_interface_contact_capabilities_finish_running_get_contact_capabilities,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetContactCapabilities",
          _tp_cli_connection_interface_contact_capabilities_collect_callback_get_contact_capabilities,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_handles,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_contacts_callback_for_get_contact_attributes:
 * @proxy: the proxy on which the call was made
 * @out_Attributes: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A dictionary mapping the contact handles to contact attributes.             If any of the requested handles are in fact invalid, they are             simply omitted from this mapping. If contact attributes are not             immediately known, the behaviour is defined by the interface;             the attribute should either be omitted from the result or             replaced with a default value.&lt;/p&gt;            &lt;p&gt;Each contact&apos;s attributes will always include at least the             identifier that would be obtained by inspecting the handle             (&lt;code&gt;org.freedesktop.Telepathy.Connection/contact-id&lt;/code&gt;).&lt;/p&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetContactAttributes method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_contacts_collect_callback_get_contact_attributes (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GHashTable *out_Attributes;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), &out_Attributes,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))));
  g_value_take_boxed (args->values + 0, out_Attributes);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_contacts_invoke_callback_get_contact_attributes (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_contacts_callback_for_get_contact_attributes callback = (tp_cli_connection_interface_contacts_callback_for_get_contact_attributes) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_contacts_call_get_contact_attributes:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Handles: Used to pass an 'in' argument: An array of handles representing contacts.
 * @in_Interfaces: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A list of strings indicating which D-Bus interfaces the calling             process is interested in. All supported attributes from these             interfaces, whose values can be obtained without additional network             activity, will be in the reply.&lt;/p&gt;            &lt;p&gt;It is an error to request interfaces that are not supported by             this Connection (i.e. mentioned in the             &lt;tp:member-ref&gt;ContactAttributeInterfaces&lt;/tp:member-ref&gt;             property).&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This makes it possible to distinguish between interfaces for               which the Connection has nothing to say (e.g. we don&apos;t know the               avatar tokens of any of the contacts, so we omitted them all),               and interfaces for which this API isn&apos;t supported.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;Attributes from the interface             &lt;tp:dbus-ref&gt;org.freedesktop.Telepathy.Connection&lt;/tp:dbus-ref&gt;             are always returned, and need not be requested explicitly.&lt;/p&gt;            &lt;p&gt;As well as returning cached information immediately, the             connection MAY start asynchronous requests to obtain better             values for the contact attributes. If better values are later             obtained by this process, they will be indicated with the usual             signals (such as &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection.Interface.Aliasing&quot;&gt;AliasesChanged&lt;/tp:dbus-ref&gt;).&lt;/p&gt;            &lt;tp:rationale&gt;             For instance, an XMPP connection manager could download vCards             in response to a request for &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection.Interface&quot;&gt;Aliasing&lt;/tp:dbus-ref&gt;             attributes.           &lt;/tp:rationale&gt;
 * @in_Hold: Used to pass an 'in' argument: If true, all handles in the result have been held on behalf of the           calling process, as if by a call to           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection.HoldHandles&lt;/tp:dbus-ref&gt;.            &lt;tp:rationale&gt;             For further round-trip avoidance.           &lt;/tp:rationale&gt;
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetContactAttributes method call.
 *
 * Return any number of contact attributes for the given handles.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_contacts_call_get_contact_attributes (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Handles,
    const gchar **in_Interfaces,
    gboolean in_Hold,
    tp_cli_connection_interface_contacts_callback_for_get_contact_attributes callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_CONTACTS;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetContactAttributes",
          DBUS_TYPE_G_UINT_ARRAY, in_Handles,
          G_TYPE_STRV, in_Interfaces,
          G_TYPE_BOOLEAN, in_Hold,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetContactAttributes", iface,
          _tp_cli_connection_interface_contacts_invoke_callback_get_contact_attributes,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetContactAttributes",
              _tp_cli_connection_interface_contacts_collect_callback_get_contact_attributes,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Handles,
              G_TYPE_STRV, in_Interfaces,
              G_TYPE_BOOLEAN, in_Hold,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GHashTable **out_Attributes;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_contacts_run_state_get_contact_attributes;
static void
_tp_cli_connection_interface_contacts_finish_running_get_contact_attributes (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_contacts_run_state_get_contact_attributes *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Attributes != NULL)
    *state->out_Attributes = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_contacts_run_get_contact_attributes:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Handles: Used to pass an 'in' argument: An array of handles representing contacts.
 * @in_Interfaces: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A list of strings indicating which D-Bus interfaces the calling             process is interested in. All supported attributes from these             interfaces, whose values can be obtained without additional network             activity, will be in the reply.&lt;/p&gt;            &lt;p&gt;It is an error to request interfaces that are not supported by             this Connection (i.e. mentioned in the             &lt;tp:member-ref&gt;ContactAttributeInterfaces&lt;/tp:member-ref&gt;             property).&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This makes it possible to distinguish between interfaces for               which the Connection has nothing to say (e.g. we don&apos;t know the               avatar tokens of any of the contacts, so we omitted them all),               and interfaces for which this API isn&apos;t supported.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;Attributes from the interface             &lt;tp:dbus-ref&gt;org.freedesktop.Telepathy.Connection&lt;/tp:dbus-ref&gt;             are always returned, and need not be requested explicitly.&lt;/p&gt;            &lt;p&gt;As well as returning cached information immediately, the             connection MAY start asynchronous requests to obtain better             values for the contact attributes. If better values are later             obtained by this process, they will be indicated with the usual             signals (such as &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection.Interface.Aliasing&quot;&gt;AliasesChanged&lt;/tp:dbus-ref&gt;).&lt;/p&gt;            &lt;tp:rationale&gt;             For instance, an XMPP connection manager could download vCards             in response to a request for &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection.Interface&quot;&gt;Aliasing&lt;/tp:dbus-ref&gt;             attributes.           &lt;/tp:rationale&gt;
 * @in_Hold: Used to pass an 'in' argument: If true, all handles in the result have been held on behalf of the           calling process, as if by a call to           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection.HoldHandles&lt;/tp:dbus-ref&gt;.            &lt;tp:rationale&gt;             For further round-trip avoidance.           &lt;/tp:rationale&gt;
 * @out_Attributes: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A dictionary mapping the contact handles to contact attributes.             If any of the requested handles are in fact invalid, they are             simply omitted from this mapping. If contact attributes are not             immediately known, the behaviour is defined by the interface;             the attribute should either be omitted from the result or             replaced with a default value.&lt;/p&gt;            &lt;p&gt;Each contact&apos;s attributes will always include at least the             identifier that would be obtained by inspecting the handle             (&lt;code&gt;org.freedesktop.Telepathy.Connection/contact-id&lt;/code&gt;).&lt;/p&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetContactAttributes and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Return any number of contact attributes for the given handles.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_contacts_run_get_contact_attributes (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Handles,
    const gchar **in_Interfaces,
    gboolean in_Hold,
    GHashTable **out_Attributes,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_CONTACTS;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_contacts_run_state_get_contact_attributes state = {
      NULL /* loop */, error,
    out_Attributes,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetContactAttributes", iface,
      _tp_cli_connection_interface_contacts_finish_running_get_contact_attributes,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetContactAttributes",
          _tp_cli_connection_interface_contacts_collect_callback_get_contact_attributes,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Handles,
              G_TYPE_STRV, in_Interfaces,
              G_TYPE_BOOLEAN, in_Hold,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


static inline void
tp_cli_add_signals_for_connection_interface_location (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "LocationUpdated",
      G_TYPE_UINT,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)),
      G_TYPE_INVALID);
}


/**
 * tp_cli_connection_interface_location_signal_callback_location_updated:
 * @proxy: The proxy on which tp_cli_connection_interface_location_connect_to_location_updated ()
 *  was called
 * @arg_Contact: The contact
 * @arg_Location: The contact&apos;s location, or empty to indicate that nothing is known           about the contact&apos;s location.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal LocationUpdated.
 */
static void
_tp_cli_connection_interface_location_collect_args_of_location_updated (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Contact,
    GHashTable *arg_Location,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (2);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 2; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, arg_Contact);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)));
  g_value_set_boxed (args->values + 1, arg_Location);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_interface_location_invoke_callback_for_location_updated (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_location_signal_callback_location_updated callback =
      (tp_cli_connection_interface_location_signal_callback_location_updated) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      g_value_get_boxed (args->values + 1),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_interface_location_connect_to_location_updated:
 * @proxy: A #TpConnection or subclass
 * @callback: Callback to be called when the signal is
 *   received
 * @user_data: User-supplied data for the callback
 * @destroy: Destructor for the user-supplied data, which
 *   will be called when this signal is disconnected, or
 *   before this function returns %NULL
 * @weak_object: A #GObject which will be weakly referenced; 
 *   if it is destroyed, this callback will automatically be
 *   disconnected
 * @error: If not %NULL, used to raise an error if %NULL is
 *   returned
 *
 * Connect a handler to the signal LocationUpdated.
 *
 * Emitted when a contact&apos;s location changes or becomes known.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_interface_location_connect_to_location_updated (TpConnection *proxy,
    tp_cli_connection_interface_location_signal_callback_location_updated callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_UINT,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION_INTERFACE_LOCATION, "LocationUpdated",
      expected_types,
      G_CALLBACK (_tp_cli_connection_interface_location_collect_args_of_location_updated),
      _tp_cli_connection_interface_location_invoke_callback_for_location_updated,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_interface_location_callback_for_get_locations:
 * @proxy: the proxy on which the call was made
 * @out_Locations: Used to return an 'out' argument if @error is %NULL: The contacts&apos; locations, if already known. Contacts whose locations           are not already known are omitted from the mapping; contacts known           to have no location information appear in the mapping with an empty           Location dictionary.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetLocations method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_location_collect_callback_get_locations (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GHashTable *out_Locations;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), &out_Locations,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))));
  g_value_take_boxed (args->values + 0, out_Locations);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_location_invoke_callback_get_locations (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_location_callback_for_get_locations callback = (tp_cli_connection_interface_location_callback_for_get_locations) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_location_call_get_locations:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contacts: Used to pass an 'in' argument: The contacts whose locations should be returned or signalled.
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetLocations method call.
 *
 * Return the current locations of the given contacts, if they are         already known. If any of the given contacts&apos; locations are not known,         request their current locations, but return immediately without waiting         for a reply; if a reply with a non-empty location is later received         for those contacts, the &lt;tp:member-ref&gt;LocationUpdated&lt;/tp:member-ref&gt;         signal will be emitted for them.          &lt;tp:rationale&gt;           This method is appropriate for &amp;quot;lazy&amp;quot; location finding, for instance           displaying the location (if available) of everyone in your contact           list.         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_location_call_get_locations (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_location_callback_for_get_locations callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_LOCATION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetLocations",
          DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetLocations", iface,
          _tp_cli_connection_interface_location_invoke_callback_get_locations,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetLocations",
              _tp_cli_connection_interface_location_collect_callback_get_locations,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GHashTable **out_Locations;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_location_run_state_get_locations;
static void
_tp_cli_connection_interface_location_finish_running_get_locations (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_location_run_state_get_locations *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Locations != NULL)
    *state->out_Locations = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_location_run_get_locations:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contacts: Used to pass an 'in' argument: The contacts whose locations should be returned or signalled.
 * @out_Locations: Used to return an 'out' argument if %TRUE is returned: The contacts&apos; locations, if already known. Contacts whose locations           are not already known are omitted from the mapping; contacts known           to have no location information appear in the mapping with an empty           Location dictionary.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetLocations and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Return the current locations of the given contacts, if they are         already known. If any of the given contacts&apos; locations are not known,         request their current locations, but return immediately without waiting         for a reply; if a reply with a non-empty location is later received         for those contacts, the &lt;tp:member-ref&gt;LocationUpdated&lt;/tp:member-ref&gt;         signal will be emitted for them.          &lt;tp:rationale&gt;           This method is appropriate for &amp;quot;lazy&amp;quot; location finding, for instance           displaying the location (if available) of everyone in your contact           list.         &lt;/tp:rationale&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_location_run_get_locations (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    GHashTable **out_Locations,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_LOCATION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_location_run_state_get_locations state = {
      NULL /* loop */, error,
    out_Locations,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetLocations", iface,
      _tp_cli_connection_interface_location_finish_running_get_locations,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetLocations",
          _tp_cli_connection_interface_location_collect_callback_get_locations,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_location_callback_for_request_location:
 * @proxy: the proxy on which the call was made
 * @out_Location: Used to return an 'out' argument if @error is %NULL: The contact&apos;s location. It MAY be empty, indicating that no location           information was found.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RequestLocation method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_location_collect_callback_request_location (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GHashTable *out_Location;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), &out_Location,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)));
  g_value_take_boxed (args->values + 0, out_Location);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_location_invoke_callback_request_location (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_location_callback_for_request_location callback = (tp_cli_connection_interface_location_callback_for_request_location) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_location_call_request_location:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contact: Used to pass an 'in' argument: The contact whose location should be returned.
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a RequestLocation method call.
 *
 * Return the current location of the given contact. If necessary, make         a request to the server for up-to-date information, and wait for a         reply.          &lt;tp:rationale&gt;           This method is appropriate for use in a &amp;quot;Contact Information...&amp;quot;           dialog; it can be used to show progress information (while waiting           for the method to return), and can distinguish between various error           conditions.         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_location_call_request_location (TpConnection *proxy,
    gint timeout_ms,
    guint in_Contact,
    tp_cli_connection_interface_location_callback_for_request_location callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_LOCATION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "RequestLocation",
          G_TYPE_UINT, in_Contact,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RequestLocation", iface,
          _tp_cli_connection_interface_location_invoke_callback_request_location,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RequestLocation",
              _tp_cli_connection_interface_location_collect_callback_request_location,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Contact,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GHashTable **out_Location;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_location_run_state_request_location;
static void
_tp_cli_connection_interface_location_finish_running_request_location (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_location_run_state_request_location *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Location != NULL)
    *state->out_Location = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_location_run_request_location:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contact: Used to pass an 'in' argument: The contact whose location should be returned.
 * @out_Location: Used to return an 'out' argument if %TRUE is returned: The contact&apos;s location. It MAY be empty, indicating that no location           information was found.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RequestLocation and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Return the current location of the given contact. If necessary, make         a request to the server for up-to-date information, and wait for a         reply.          &lt;tp:rationale&gt;           This method is appropriate for use in a &amp;quot;Contact Information...&amp;quot;           dialog; it can be used to show progress information (while waiting           for the method to return), and can distinguish between various error           conditions.         &lt;/tp:rationale&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_location_run_request_location (TpConnection *proxy,
    gint timeout_ms,
    guint in_Contact,
    GHashTable **out_Location,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_LOCATION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_location_run_state_request_location state = {
      NULL /* loop */, error,
    out_Location,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RequestLocation", iface,
      _tp_cli_connection_interface_location_finish_running_request_location,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RequestLocation",
          _tp_cli_connection_interface_location_collect_callback_request_location,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Contact,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_location_callback_for_set_location:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a SetLocation method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_location_collect_callback_set_location (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_interface_location_invoke_callback_set_location (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_location_callback_for_set_location callback = (tp_cli_connection_interface_location_callback_for_set_location) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_location_call_set_location:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Location: Used to pass an 'in' argument: The location to advertise. If the user wants to obscure their           exact location by reducing the precision or accuracy, clients           MUST do this themselves, rather than relying on the connection           manager to do so. Clients that interact with more than one           connection SHOULD advertise the same reduced-accuracy location           to all of them, so that contacts cannot obtain an undesirably           accurate location by assuming that random errors have been added           and averaging the locations advertised on multiple connections.
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a SetLocation method call.
 *
 * Set the local user&apos;s own location.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_location_call_set_location (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Location,
    tp_cli_connection_interface_location_callback_for_set_location callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_LOCATION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "SetLocation",
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Location,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "SetLocation", iface,
          _tp_cli_connection_interface_location_invoke_callback_set_location,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "SetLocation",
              _tp_cli_connection_interface_location_collect_callback_set_location,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Location,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_location_run_state_set_location;
static void
_tp_cli_connection_interface_location_finish_running_set_location (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_location_run_state_set_location *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_location_run_set_location:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Location: Used to pass an 'in' argument: The location to advertise. If the user wants to obscure their           exact location by reducing the precision or accuracy, clients           MUST do this themselves, rather than relying on the connection           manager to do so. Clients that interact with more than one           connection SHOULD advertise the same reduced-accuracy location           to all of them, so that contacts cannot obtain an undesirably           accurate location by assuming that random errors have been added           and averaging the locations advertised on multiple connections.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method SetLocation and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Set the local user&apos;s own location.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_location_run_set_location (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Location,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_LOCATION;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_location_run_state_set_location state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "SetLocation", iface,
      _tp_cli_connection_interface_location_finish_running_set_location,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "SetLocation",
          _tp_cli_connection_interface_location_collect_callback_set_location,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Location,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


static inline void
tp_cli_add_signals_for_connection_interface_presence (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "PresenceUpdate",
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), G_TYPE_INVALID)))),
      G_TYPE_INVALID);
}


/**
 * tp_cli_connection_interface_presence_signal_callback_presence_update:
 * @proxy: The proxy on which tp_cli_connection_interface_presence_connect_to_presence_update ()
 *  was called
 * @arg_Presence: A dictionary of contact handles mapped to a struct containing         a UNIX timestamp of the last activity time (in UTC), and         a dictionary mapping the contact&apos;s current status identifiers to           a dictionary of optional parameter names mapped to their           variant-boxed values
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal PresenceUpdate.
 */
static void
_tp_cli_connection_interface_presence_collect_args_of_presence_update (DBusGProxy *proxy G_GNUC_UNUSED,
    GHashTable *arg_Presence,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), G_TYPE_INVALID)))));
  g_value_set_boxed (args->values + 0, arg_Presence);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_interface_presence_invoke_callback_for_presence_update (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_presence_signal_callback_presence_update callback =
      (tp_cli_connection_interface_presence_signal_callback_presence_update) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_interface_presence_connect_to_presence_update:
 * @proxy: A #TpConnection or subclass
 * @callback: Callback to be called when the signal is
 *   received
 * @user_data: User-supplied data for the callback
 * @destroy: Destructor for the user-supplied data, which
 *   will be called when this signal is disconnected, or
 *   before this function returns %NULL
 * @weak_object: A #GObject which will be weakly referenced; 
 *   if it is destroyed, this callback will automatically be
 *   disconnected
 * @error: If not %NULL, used to raise an error if %NULL is
 *   returned
 *
 * Connect a handler to the signal PresenceUpdate.
 *
 * This signal should be emitted when your own presence has been changed,         or the presence of the member of any of the connection&apos;s channels has         been changed, or when the presence requested by         &lt;tp:member-ref&gt;RequestPresence&lt;/tp:member-ref&gt; is available.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_interface_presence_connect_to_presence_update (TpConnection *proxy,
    tp_cli_connection_interface_presence_signal_callback_presence_update callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), G_TYPE_INVALID)))),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE, "PresenceUpdate",
      expected_types,
      G_CALLBACK (_tp_cli_connection_interface_presence_collect_args_of_presence_update),
      _tp_cli_connection_interface_presence_invoke_callback_for_presence_update,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_interface_presence_callback_for_add_status:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a AddStatus method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_presence_collect_callback_add_status (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_interface_presence_invoke_callback_add_status (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_presence_callback_for_add_status callback = (tp_cli_connection_interface_presence_callback_for_add_status) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_call_add_status:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Status: Used to pass an 'in' argument: The string identifier of the desired status
 * @in_Parameters: Used to pass an 'in' argument: A dictionary of optional parameter names mapped to their variant-boxed values
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a AddStatus method call.
 *
 * Request that a single presence status is published for the user, along         with any desired parameters. Changes will be indicated by         &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt; signals being emitted.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_presence_call_add_status (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Status,
    GHashTable *in_Parameters,
    tp_cli_connection_interface_presence_callback_for_add_status callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "AddStatus",
          G_TYPE_STRING, in_Status,
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Parameters,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "AddStatus", iface,
          _tp_cli_connection_interface_presence_invoke_callback_add_status,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "AddStatus",
              _tp_cli_connection_interface_presence_collect_callback_add_status,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Status,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Parameters,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_presence_run_state_add_status;
static void
_tp_cli_connection_interface_presence_finish_running_add_status (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_presence_run_state_add_status *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_run_add_status:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Status: Used to pass an 'in' argument: The string identifier of the desired status
 * @in_Parameters: Used to pass an 'in' argument: A dictionary of optional parameter names mapped to their variant-boxed values
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method AddStatus and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Request that a single presence status is published for the user, along         with any desired parameters. Changes will be indicated by         &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt; signals being emitted.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_presence_run_add_status (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Status,
    GHashTable *in_Parameters,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_presence_run_state_add_status state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "AddStatus", iface,
      _tp_cli_connection_interface_presence_finish_running_add_status,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "AddStatus",
          _tp_cli_connection_interface_presence_collect_callback_add_status,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_STRING, in_Status,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Parameters,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_presence_callback_for_clear_status:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a ClearStatus method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_presence_collect_callback_clear_status (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_interface_presence_invoke_callback_clear_status (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_presence_callback_for_clear_status callback = (tp_cli_connection_interface_presence_callback_for_clear_status) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_call_clear_status:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a ClearStatus method call.
 *
 * Request that all of a user&apos;s presence statuses be removed. Be aware         that this request may simply result in the statuses being replaced by a         default available status. Changes will be indicated by         &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt; signals being emitted.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_presence_call_clear_status (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_interface_presence_callback_for_clear_status callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "ClearStatus",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "ClearStatus", iface,
          _tp_cli_connection_interface_presence_invoke_callback_clear_status,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "ClearStatus",
              _tp_cli_connection_interface_presence_collect_callback_clear_status,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_presence_run_state_clear_status;
static void
_tp_cli_connection_interface_presence_finish_running_clear_status (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_presence_run_state_clear_status *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_run_clear_status:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method ClearStatus and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Request that all of a user&apos;s presence statuses be removed. Be aware         that this request may simply result in the statuses being replaced by a         default available status. Changes will be indicated by         &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt; signals being emitted.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_presence_run_clear_status (TpConnection *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_presence_run_state_clear_status state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "ClearStatus", iface,
      _tp_cli_connection_interface_presence_finish_running_clear_status,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "ClearStatus",
          _tp_cli_connection_interface_presence_collect_callback_clear_status,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_presence_callback_for_get_presence:
 * @proxy: the proxy on which the call was made
 * @out_Presence: Used to return an 'out' argument if @error is %NULL: Presence information in the same format as for the           &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt; signal
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetPresence method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_presence_collect_callback_get_presence (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GHashTable *out_Presence;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), G_TYPE_INVALID)))), &out_Presence,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Presence);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_presence_invoke_callback_get_presence (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_presence_callback_for_get_presence callback = (tp_cli_connection_interface_presence_callback_for_get_presence) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_call_get_presence:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contacts: Used to pass an 'in' argument: An array of the contacts whose presence should be obtained
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetPresence method call.
 *
 * Get presence previously emitted by         &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt; for the given contacts.         Data is returned in the same structure as the PresenceUpdate signal.         Using this method in favour of         &lt;tp:member-ref&gt;RequestPresence&lt;/tp:member-ref&gt; has the advantage that         it will not wake up each client connected to the PresenceUpdate signal.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_presence_call_get_presence (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_presence_callback_for_get_presence callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetPresence",
          DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetPresence", iface,
          _tp_cli_connection_interface_presence_invoke_callback_get_presence,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetPresence",
              _tp_cli_connection_interface_presence_collect_callback_get_presence,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GHashTable **out_Presence;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_presence_run_state_get_presence;
static void
_tp_cli_connection_interface_presence_finish_running_get_presence (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_presence_run_state_get_presence *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Presence != NULL)
    *state->out_Presence = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_run_get_presence:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contacts: Used to pass an 'in' argument: An array of the contacts whose presence should be obtained
 * @out_Presence: Used to return an 'out' argument if %TRUE is returned: Presence information in the same format as for the           &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt; signal
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetPresence and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Get presence previously emitted by         &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt; for the given contacts.         Data is returned in the same structure as the PresenceUpdate signal.         Using this method in favour of         &lt;tp:member-ref&gt;RequestPresence&lt;/tp:member-ref&gt; has the advantage that         it will not wake up each client connected to the PresenceUpdate signal.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_presence_run_get_presence (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    GHashTable **out_Presence,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_presence_run_state_get_presence state = {
      NULL /* loop */, error,
    out_Presence,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetPresence", iface,
      _tp_cli_connection_interface_presence_finish_running_get_presence,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetPresence",
          _tp_cli_connection_interface_presence_collect_callback_get_presence,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_presence_callback_for_get_statuses:
 * @proxy: the proxy on which the call was made
 * @out_Available_Statuses: Used to return an 'out' argument if @error is %NULL: A dictionary of string identifiers mapped to a struct for each status, containing:         &lt;ul&gt;           &lt;li&gt;a type value from one of the values above&lt;/li&gt;           &lt;li&gt;a boolean to indicate if this status may be set on yourself&lt;/li&gt;           &lt;li&gt;a boolean to indicate if this is an exclusive status which you             may not set alongside any other&lt;/li&gt;           &lt;li&gt;a dictionary of valid optional string argument names mapped to             their types&lt;/li&gt;         &lt;/ul&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetStatuses method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_presence_collect_callback_get_statuses (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GHashTable *out_Available_Statuses;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))), &out_Available_Statuses,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_BOOLEAN, G_TYPE_BOOLEAN, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Available_Statuses);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_presence_invoke_callback_get_statuses (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_presence_callback_for_get_statuses callback = (tp_cli_connection_interface_presence_callback_for_get_statuses) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_call_get_statuses:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetStatuses method call.
 *
 * Get a dictionary of the valid presence statuses for this connection.         This is only available when online because only some statuses will         be available on some servers.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_presence_call_get_statuses (TpConnection *proxy,
    gint timeout_ms,
    tp_cli_connection_interface_presence_callback_for_get_statuses callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetStatuses",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetStatuses", iface,
          _tp_cli_connection_interface_presence_invoke_callback_get_statuses,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetStatuses",
              _tp_cli_connection_interface_presence_collect_callback_get_statuses,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GHashTable **out_Available_Statuses;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_presence_run_state_get_statuses;
static void
_tp_cli_connection_interface_presence_finish_running_get_statuses (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_presence_run_state_get_statuses *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Available_Statuses != NULL)
    *state->out_Available_Statuses = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_run_get_statuses:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Available_Statuses: Used to return an 'out' argument if %TRUE is returned: A dictionary of string identifiers mapped to a struct for each status, containing:         &lt;ul&gt;           &lt;li&gt;a type value from one of the values above&lt;/li&gt;           &lt;li&gt;a boolean to indicate if this status may be set on yourself&lt;/li&gt;           &lt;li&gt;a boolean to indicate if this is an exclusive status which you             may not set alongside any other&lt;/li&gt;           &lt;li&gt;a dictionary of valid optional string argument names mapped to             their types&lt;/li&gt;         &lt;/ul&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetStatuses and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Get a dictionary of the valid presence statuses for this connection.         This is only available when online because only some statuses will         be available on some servers.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_presence_run_get_statuses (TpConnection *proxy,
    gint timeout_ms,
    GHashTable **out_Available_Statuses,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_presence_run_state_get_statuses state = {
      NULL /* loop */, error,
    out_Available_Statuses,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetStatuses", iface,
      _tp_cli_connection_interface_presence_finish_running_get_statuses,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetStatuses",
          _tp_cli_connection_interface_presence_collect_callback_get_statuses,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_presence_callback_for_remove_status:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RemoveStatus method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_presence_collect_callback_remove_status (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_interface_presence_invoke_callback_remove_status (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_presence_callback_for_remove_status callback = (tp_cli_connection_interface_presence_callback_for_remove_status) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_call_remove_status:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Status: Used to pass an 'in' argument: The string identifier of the status not to publish anymore for the user
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a RemoveStatus method call.
 *
 * Request that the given presence status is no longer published for the         user. Changes will be indicated by         &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt; signals being emitted. As         with &lt;tp:member-ref&gt;ClearStatus&lt;/tp:member-ref&gt;, removing a status may         actually result in it being replaced by a default available status.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_presence_call_remove_status (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Status,
    tp_cli_connection_interface_presence_callback_for_remove_status callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "RemoveStatus",
          G_TYPE_STRING, in_Status,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RemoveStatus", iface,
          _tp_cli_connection_interface_presence_invoke_callback_remove_status,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RemoveStatus",
              _tp_cli_connection_interface_presence_collect_callback_remove_status,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Status,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_presence_run_state_remove_status;
static void
_tp_cli_connection_interface_presence_finish_running_remove_status (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_presence_run_state_remove_status *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_run_remove_status:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Status: Used to pass an 'in' argument: The string identifier of the status not to publish anymore for the user
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RemoveStatus and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Request that the given presence status is no longer published for the         user. Changes will be indicated by         &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt; signals being emitted. As         with &lt;tp:member-ref&gt;ClearStatus&lt;/tp:member-ref&gt;, removing a status may         actually result in it being replaced by a default available status.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_presence_run_remove_status (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Status,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_presence_run_state_remove_status state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RemoveStatus", iface,
      _tp_cli_connection_interface_presence_finish_running_remove_status,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RemoveStatus",
          _tp_cli_connection_interface_presence_collect_callback_remove_status,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_STRING, in_Status,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_presence_callback_for_request_presence:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RequestPresence method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_presence_collect_callback_request_presence (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_interface_presence_invoke_callback_request_presence (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_presence_callback_for_request_presence callback = (tp_cli_connection_interface_presence_callback_for_request_presence) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_call_request_presence:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contacts: Used to pass an 'in' argument: An array of the contacts whose presence should be obtained
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a RequestPresence method call.
 *
 * Request the presence for contacts on this connection. A &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt;         signal will be emitted when they are received. This is not the same as         subscribing to the presence of a contact, which must be done using the         &apos;subscription&apos; &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Type&quot;&gt;ContactList&lt;/tp:dbus-ref&gt;,         and on some protocols presence information may not be available unless         a subscription exists.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_presence_call_request_presence (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_presence_callback_for_request_presence callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "RequestPresence",
          DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RequestPresence", iface,
          _tp_cli_connection_interface_presence_invoke_callback_request_presence,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RequestPresence",
              _tp_cli_connection_interface_presence_collect_callback_request_presence,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_presence_run_state_request_presence;
static void
_tp_cli_connection_interface_presence_finish_running_request_presence (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_presence_run_state_request_presence *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_run_request_presence:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contacts: Used to pass an 'in' argument: An array of the contacts whose presence should be obtained
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RequestPresence and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Request the presence for contacts on this connection. A &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt;         signal will be emitted when they are received. This is not the same as         subscribing to the presence of a contact, which must be done using the         &apos;subscription&apos; &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Type&quot;&gt;ContactList&lt;/tp:dbus-ref&gt;,         and on some protocols presence information may not be available unless         a subscription exists.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_presence_run_request_presence (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_presence_run_state_request_presence state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RequestPresence", iface,
      _tp_cli_connection_interface_presence_finish_running_request_presence,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RequestPresence",
          _tp_cli_connection_interface_presence_collect_callback_request_presence,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_presence_callback_for_set_last_activity_time:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a SetLastActivityTime method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_presence_collect_callback_set_last_activity_time (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_interface_presence_invoke_callback_set_last_activity_time (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_presence_callback_for_set_last_activity_time callback = (tp_cli_connection_interface_presence_callback_for_set_last_activity_time) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_call_set_last_activity_time:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Time: Used to pass an 'in' argument: A UNIX timestamp of the user&apos;s last activity time (in UTC)
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a SetLastActivityTime method call.
 *
 * Request that the recorded last activity time for the user be updated on         the server.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_presence_call_set_last_activity_time (TpConnection *proxy,
    gint timeout_ms,
    guint in_Time,
    tp_cli_connection_interface_presence_callback_for_set_last_activity_time callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "SetLastActivityTime",
          G_TYPE_UINT, in_Time,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "SetLastActivityTime", iface,
          _tp_cli_connection_interface_presence_invoke_callback_set_last_activity_time,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "SetLastActivityTime",
              _tp_cli_connection_interface_presence_collect_callback_set_last_activity_time,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Time,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_presence_run_state_set_last_activity_time;
static void
_tp_cli_connection_interface_presence_finish_running_set_last_activity_time (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_presence_run_state_set_last_activity_time *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_run_set_last_activity_time:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Time: Used to pass an 'in' argument: A UNIX timestamp of the user&apos;s last activity time (in UTC)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method SetLastActivityTime and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Request that the recorded last activity time for the user be updated on         the server.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_presence_run_set_last_activity_time (TpConnection *proxy,
    gint timeout_ms,
    guint in_Time,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_presence_run_state_set_last_activity_time state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "SetLastActivityTime", iface,
      _tp_cli_connection_interface_presence_finish_running_set_last_activity_time,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "SetLastActivityTime",
          _tp_cli_connection_interface_presence_collect_callback_set_last_activity_time,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Time,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_presence_callback_for_set_status:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a SetStatus method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_presence_collect_callback_set_status (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_interface_presence_invoke_callback_set_status (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_presence_callback_for_set_status callback = (tp_cli_connection_interface_presence_callback_for_set_status) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_call_set_status:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Statuses: Used to pass an 'in' argument: A dictionary mapping status identifiers to dictionaries, which           map optional parameter names to their variant-boxed values
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a SetStatus method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that the user&apos;s presence be changed to the given statuses           and desired parameters. Changes will be reflected by           &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt;           signals being emitted.&lt;/p&gt;          &lt;p&gt;Statuses whose &lt;tp:type&gt;Connection_Presence_Type&lt;/tp:type&gt;           is Offline, Error or Unknown MUST NOT be passed to this           function. Connection managers SHOULD reject these statuses.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The same rationale as for &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection.Interface&quot;&gt;SimplePresence.SetPresence&lt;/tp:dbus-ref&gt;             applies.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;On certain protocols, this method may be           called on a newly-created connection which is still in the           DISCONNECTED state, and will sign on with the requested status.           If the requested status is not available after signing on,           NotAvailable will be returned and the connection will remain           offline, or if the protocol does not support signing on with           a certain status, Disconnected will be returned.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_presence_call_set_status (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Statuses,
    tp_cli_connection_interface_presence_callback_for_set_status callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "SetStatus",
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), in_Statuses,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "SetStatus", iface,
          _tp_cli_connection_interface_presence_invoke_callback_set_status,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "SetStatus",
              _tp_cli_connection_interface_presence_collect_callback_set_status,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), in_Statuses,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_presence_run_state_set_status;
static void
_tp_cli_connection_interface_presence_finish_running_set_status (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_presence_run_state_set_status *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_presence_run_set_status:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Statuses: Used to pass an 'in' argument: A dictionary mapping status identifiers to dictionaries, which           map optional parameter names to their variant-boxed values
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method SetStatus and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that the user&apos;s presence be changed to the given statuses           and desired parameters. Changes will be reflected by           &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt;           signals being emitted.&lt;/p&gt;          &lt;p&gt;Statuses whose &lt;tp:type&gt;Connection_Presence_Type&lt;/tp:type&gt;           is Offline, Error or Unknown MUST NOT be passed to this           function. Connection managers SHOULD reject these statuses.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The same rationale as for &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection.Interface&quot;&gt;SimplePresence.SetPresence&lt;/tp:dbus-ref&gt;             applies.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;On certain protocols, this method may be           called on a newly-created connection which is still in the           DISCONNECTED state, and will sign on with the requested status.           If the requested status is not available after signing on,           NotAvailable will be returned and the connection will remain           offline, or if the protocol does not support signing on with           a certain status, Disconnected will be returned.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_presence_run_set_status (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Statuses,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_presence_run_state_set_status state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "SetStatus", iface,
      _tp_cli_connection_interface_presence_finish_running_set_status,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "SetStatus",
          _tp_cli_connection_interface_presence_collect_callback_set_status,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), in_Statuses,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


static inline void
tp_cli_add_signals_for_connection_interface_requests (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "NewChannels",
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID)))),
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "ChannelClosed",
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_INVALID);
}


/**
 * tp_cli_connection_interface_requests_signal_callback_new_channels:
 * @proxy: The proxy on which tp_cli_connection_interface_requests_connect_to_new_channels ()
 *  was called
 * @arg_Channels: The channels and their details. All channels that are signalled           together like this MUST have the same           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.FUTURE&quot;&gt;Bundle&lt;/tp:dbus-ref&gt;           property, which may           either refer to an existing bundle, or establish a new bundle.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal NewChannels.
 */
static void
_tp_cli_connection_interface_requests_collect_args_of_new_channels (DBusGProxy *proxy G_GNUC_UNUSED,
    const GPtrArray *arg_Channels,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID)))));
  g_value_set_boxed (args->values + 0, arg_Channels);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_interface_requests_invoke_callback_for_new_channels (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_requests_signal_callback_new_channels callback =
      (tp_cli_connection_interface_requests_signal_callback_new_channels) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_interface_requests_connect_to_new_channels:
 * @proxy: A #TpConnection or subclass
 * @callback: Callback to be called when the signal is
 *   received
 * @user_data: User-supplied data for the callback
 * @destroy: Destructor for the user-supplied data, which
 *   will be called when this signal is disconnected, or
 *   before this function returns %NULL
 * @weak_object: A #GObject which will be weakly referenced; 
 *   if it is destroyed, this callback will automatically be
 *   disconnected
 * @error: If not %NULL, used to raise an error if %NULL is
 *   returned
 *
 * Connect a handler to the signal NewChannels.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;New channels have been created. The connection manager SHOULD emit           a single signal for any group of closely related channels that are           created at the same time, so that the channel dispatcher can try to           dispatch them to a handler as a unit.&lt;/p&gt;          &lt;p&gt;In particular, if additional channels are created as a side-effect           of a call to &lt;tp:member-ref&gt;CreateChannel&lt;/tp:member-ref&gt;,           these channels SHOULD appear in the same NewChannels signal as           the channel that satisfies the request.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;Joining a MUC Tube in XMPP requires joining the corresponding             MUC (chatroom), so a &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Type&quot;&gt;Text&lt;/tp:dbus-ref&gt;             channel can be created as a side-effect.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;Every time NewChannels is emitted, it MUST be followed by           a &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection.NewChannel&lt;/tp:dbus-ref&gt;           signal for each channel.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The double signal emission is for the benefit of older Telepathy             clients, which won&apos;t be listening for NewChannels.&lt;/p&gt;            &lt;p&gt;The more informative NewChannels signal comes first so that             clients that did not examine the connection to find             out whether Requests is supported will see the more informative             signal for each channel first, and then ignore the less             informative signal because it announces a new channel of which             they are already aware.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_interface_requests_connect_to_new_channels (TpConnection *proxy,
    tp_cli_connection_interface_requests_signal_callback_new_channels callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID)))),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION_INTERFACE_REQUESTS, "NewChannels",
      expected_types,
      G_CALLBACK (_tp_cli_connection_interface_requests_collect_args_of_new_channels),
      _tp_cli_connection_interface_requests_invoke_callback_for_new_channels,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_interface_requests_signal_callback_channel_closed:
 * @proxy: The proxy on which tp_cli_connection_interface_requests_connect_to_channel_closed ()
 *  was called
 * @arg_Removed: The channel which has been removed from the Channels property
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal ChannelClosed.
 */
static void
_tp_cli_connection_interface_requests_collect_args_of_channel_closed (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Removed,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, DBUS_TYPE_G_OBJECT_PATH);
  g_value_set_boxed (args->values + 0, arg_Removed);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_interface_requests_invoke_callback_for_channel_closed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_requests_signal_callback_channel_closed callback =
      (tp_cli_connection_interface_requests_signal_callback_channel_closed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_interface_requests_connect_to_channel_closed:
 * @proxy: A #TpConnection or subclass
 * @callback: Callback to be called when the signal is
 *   received
 * @user_data: User-supplied data for the callback
 * @destroy: Destructor for the user-supplied data, which
 *   will be called when this signal is disconnected, or
 *   before this function returns %NULL
 * @weak_object: A #GObject which will be weakly referenced; 
 *   if it is destroyed, this callback will automatically be
 *   disconnected
 * @error: If not %NULL, used to raise an error if %NULL is
 *   returned
 *
 * Connect a handler to the signal ChannelClosed.
 *
 * Emitted when a channel is closed and hence disappears from the         &lt;tp:member-ref&gt;Channels&lt;/tp:member-ref&gt; property.          &lt;tp:rationale&gt;           This is redundant with the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel&quot;&gt;Closed&lt;/tp:dbus-ref&gt;           signal on the channel itself, but it does provide full change           notification for the Channels property.         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_interface_requests_connect_to_channel_closed (TpConnection *proxy,
    tp_cli_connection_interface_requests_signal_callback_channel_closed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION_INTERFACE_REQUESTS, "ChannelClosed",
      expected_types,
      G_CALLBACK (_tp_cli_connection_interface_requests_collect_args_of_channel_closed),
      _tp_cli_connection_interface_requests_invoke_callback_for_channel_closed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_interface_requests_callback_for_create_channel:
 * @proxy: the proxy on which the call was made
 * @out_Channel: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The Channel object, which MUST NOT be signalled with             &lt;tp:member-ref&gt;NewChannels&lt;/tp:member-ref&gt; until after this method             returns.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This allows the requester to alter its handling of               NewChannels by knowing whether one of the channels satisfied               a request it made.&lt;/p&gt;           &lt;/tp:rationale&gt;
 * @out_Properties: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Properties of the channel that was produced, equivalent to             the properties in &lt;tp:type&gt;Channel_Details&lt;/tp:type&gt;.             Connection managers MUST NOT include properties here whose             values can change, for the same reasons as in             &lt;tp:type&gt;Channel_Details&lt;/tp:type&gt;.&lt;/p&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a CreateChannel method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_requests_collect_callback_create_channel (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_Channel;
  GHashTable *out_Properties;

  dbus_g_proxy_end_call (proxy, call, &error,
      DBUS_TYPE_G_OBJECT_PATH, &out_Channel,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), &out_Properties,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (2);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 2; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, DBUS_TYPE_G_OBJECT_PATH);
  g_value_take_boxed (args->values + 0, out_Channel);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)));
  g_value_take_boxed (args->values + 1, out_Properties);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_requests_invoke_callback_create_channel (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_requests_callback_for_create_channel callback = (tp_cli_connection_interface_requests_callback_for_create_channel) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      g_value_get_boxed (args->values + 1),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_requests_call_create_channel:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Request: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A dictionary containing desirable properties, which MUST include             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel&quot;&gt;ChannelType&lt;/tp:dbus-ref&gt;.             Some properties             are defined such that only an exact match makes sense, and             connection managers MUST NOT satisfy a request with a channel             where that property does not match; some properties are defined             such that the connection manager MAY treat the request as merely             a hint, and make a best-effort attempt to satisfy it. This is             documented separately for each property.&lt;/p&gt;            &lt;p&gt;If this dictionary contains a property whose semantics             are not known to the connection manager, this method MUST fail             without side-effects (in particular it must not create a new             channel).&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This is necessary if we want to be able to invent properties               in future that, when used in a request, are hard requirements               rather than just hints. A connection manager that did not know               the semantics of those properties could incorrectly return a               new channel that did not satisfy the requirements.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;The connection manager MUST NOT respond successfully,             and SHOULD NOT create a new channel or cause any other             side-effects, unless it can create a new channel that satisfies             the client&apos;s requirements.&lt;/p&gt;            &lt;p&gt;Properties that will be set by this argument need not have write             access after the channel has been created - indeed, it is             expected that most will be read-only.&lt;/p&gt;
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a CreateChannel method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that an entirely new channel is created.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;There is deliberately no flag corresponding to the             suppress_handler argument to             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection.RequestChannel&lt;/tp:dbus-ref&gt;,             because passing a FALSE value for that argument is deprecated.             Requests made using this interface always behave as though             suppress_handler was TRUE.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_requests_call_create_channel (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Request,
    tp_cli_connection_interface_requests_callback_for_create_channel callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_REQUESTS;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            NULL,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "CreateChannel",
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Request,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "CreateChannel", iface,
          _tp_cli_connection_interface_requests_invoke_callback_create_channel,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "CreateChannel",
              _tp_cli_connection_interface_requests_collect_callback_create_channel,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Request,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gchar **out_Channel;
    GHashTable **out_Properties;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_requests_run_state_create_channel;
static void
_tp_cli_connection_interface_requests_finish_running_create_channel (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_requests_run_state_create_channel *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Channel != NULL)
    *state->out_Channel = g_value_dup_boxed (args->values + 0);

  if (state->out_Properties != NULL)
    *state->out_Properties = g_value_dup_boxed (args->values + 1);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_requests_run_create_channel:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Request: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A dictionary containing desirable properties, which MUST include             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel&quot;&gt;ChannelType&lt;/tp:dbus-ref&gt;.             Some properties             are defined such that only an exact match makes sense, and             connection managers MUST NOT satisfy a request with a channel             where that property does not match; some properties are defined             such that the connection manager MAY treat the request as merely             a hint, and make a best-effort attempt to satisfy it. This is             documented separately for each property.&lt;/p&gt;            &lt;p&gt;If this dictionary contains a property whose semantics             are not known to the connection manager, this method MUST fail             without side-effects (in particular it must not create a new             channel).&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This is necessary if we want to be able to invent properties               in future that, when used in a request, are hard requirements               rather than just hints. A connection manager that did not know               the semantics of those properties could incorrectly return a               new channel that did not satisfy the requirements.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;The connection manager MUST NOT respond successfully,             and SHOULD NOT create a new channel or cause any other             side-effects, unless it can create a new channel that satisfies             the client&apos;s requirements.&lt;/p&gt;            &lt;p&gt;Properties that will be set by this argument need not have write             access after the channel has been created - indeed, it is             expected that most will be read-only.&lt;/p&gt;
 * @out_Channel: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The Channel object, which MUST NOT be signalled with             &lt;tp:member-ref&gt;NewChannels&lt;/tp:member-ref&gt; until after this method             returns.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This allows the requester to alter its handling of               NewChannels by knowing whether one of the channels satisfied               a request it made.&lt;/p&gt;           &lt;/tp:rationale&gt;
 * @out_Properties: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Properties of the channel that was produced, equivalent to             the properties in &lt;tp:type&gt;Channel_Details&lt;/tp:type&gt;.             Connection managers MUST NOT include properties here whose             values can change, for the same reasons as in             &lt;tp:type&gt;Channel_Details&lt;/tp:type&gt;.&lt;/p&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method CreateChannel and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that an entirely new channel is created.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;There is deliberately no flag corresponding to the             suppress_handler argument to             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection.RequestChannel&lt;/tp:dbus-ref&gt;,             because passing a FALSE value for that argument is deprecated.             Requests made using this interface always behave as though             suppress_handler was TRUE.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_requests_run_create_channel (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Request,
    gchar **out_Channel,
    GHashTable **out_Properties,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_REQUESTS;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_requests_run_state_create_channel state = {
      NULL /* loop */, error,
    out_Channel,
    out_Properties,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "CreateChannel", iface,
      _tp_cli_connection_interface_requests_finish_running_create_channel,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "CreateChannel",
          _tp_cli_connection_interface_requests_collect_callback_create_channel,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Request,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_requests_callback_for_ensure_channel:
 * @proxy: the proxy on which the call was made
 * @out_Yours: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;If false, the caller of EnsureChannel MUST assume that some             other process is handling this channel; if true, the caller of             EnsureChannel SHOULD handle it themselves or delegate it to another             client.&lt;/p&gt;            &lt;p&gt;If the creation of a channel makes several calls to EnsureChannel             (and no other requests) successful, exactly one of those calls MUST             return a true value for this argument.&lt;/p&gt;            &lt;p&gt;If the creation of a channel makes other requests successful,             the value returned for this argument MUST be such that exactly             one of the clients making requests ends up responsible for the             channel. In particular, if             &lt;tp:member-ref&gt;CreateChannel&lt;/tp:member-ref&gt; returns a channel             &lt;em&gt;C&lt;/em&gt;, any EnsureChannel calls that also return &lt;em&gt;C&lt;/em&gt;             MUST return a false value for this argument.&lt;/p&gt;
 * @out_Channel: Used to return an 'out' argument if @error is %NULL: The Channel object. If it was created as a result of this method           call, it MUST NOT be signalled by           &lt;tp:member-ref&gt;NewChannels&lt;/tp:member-ref&gt; until after this method           returns.            &lt;tp:rationale&gt;             &lt;p&gt;This allows the requester to alter its handling of               NewChannels by knowing whether one of the channels satisfied               a request it made.&lt;/p&gt;           &lt;/tp:rationale&gt;
 * @out_Properties: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Properties of the channel that was produced, equivalent to             the properties in &lt;tp:type&gt;Channel_Details&lt;/tp:type&gt;.             Connection managers MUST NOT include properties here whose             values can change, for the same reasons as in             &lt;tp:type&gt;Channel_Details&lt;/tp:type&gt;.&lt;/p&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a EnsureChannel method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_requests_collect_callback_ensure_channel (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gboolean out_Yours;
  gchar *out_Channel;
  GHashTable *out_Properties;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_BOOLEAN, &out_Yours,
      DBUS_TYPE_G_OBJECT_PATH, &out_Channel,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), &out_Properties,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (3);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 3; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_BOOLEAN);
  g_value_set_boolean (args->values + 0, out_Yours);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, DBUS_TYPE_G_OBJECT_PATH);
  g_value_take_boxed (args->values + 1, out_Channel);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)));
  g_value_take_boxed (args->values + 2, out_Properties);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_requests_invoke_callback_ensure_channel (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_requests_callback_for_ensure_channel callback = (tp_cli_connection_interface_requests_callback_for_ensure_channel) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          0,
          NULL,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boolean (args->values + 0),
      g_value_get_boxed (args->values + 1),
      g_value_get_boxed (args->values + 2),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_requests_call_ensure_channel:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Request: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A dictionary containing desirable properties, with the same             semantics as the corresponding parameter to             &lt;tp:member-ref&gt;CreateChannel&lt;/tp:member-ref&gt;.&lt;/p&gt;
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a EnsureChannel method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that channels are ensured to exist.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The connection manager is in the best position to determine which             existing channels could satisfy which requests.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_requests_call_ensure_channel (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Request,
    tp_cli_connection_interface_requests_callback_for_ensure_channel callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_REQUESTS;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            0,
            NULL,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "EnsureChannel",
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Request,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "EnsureChannel", iface,
          _tp_cli_connection_interface_requests_invoke_callback_ensure_channel,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "EnsureChannel",
              _tp_cli_connection_interface_requests_collect_callback_ensure_channel,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Request,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gboolean *out_Yours;
    gchar **out_Channel;
    GHashTable **out_Properties;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_requests_run_state_ensure_channel;
static void
_tp_cli_connection_interface_requests_finish_running_ensure_channel (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_requests_run_state_ensure_channel *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Yours != NULL)
    *state->out_Yours = g_value_get_boolean (args->values + 0);

  if (state->out_Channel != NULL)
    *state->out_Channel = g_value_dup_boxed (args->values + 1);

  if (state->out_Properties != NULL)
    *state->out_Properties = g_value_dup_boxed (args->values + 2);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_requests_run_ensure_channel:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Request: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A dictionary containing desirable properties, with the same             semantics as the corresponding parameter to             &lt;tp:member-ref&gt;CreateChannel&lt;/tp:member-ref&gt;.&lt;/p&gt;
 * @out_Yours: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;If false, the caller of EnsureChannel MUST assume that some             other process is handling this channel; if true, the caller of             EnsureChannel SHOULD handle it themselves or delegate it to another             client.&lt;/p&gt;            &lt;p&gt;If the creation of a channel makes several calls to EnsureChannel             (and no other requests) successful, exactly one of those calls MUST             return a true value for this argument.&lt;/p&gt;            &lt;p&gt;If the creation of a channel makes other requests successful,             the value returned for this argument MUST be such that exactly             one of the clients making requests ends up responsible for the             channel. In particular, if             &lt;tp:member-ref&gt;CreateChannel&lt;/tp:member-ref&gt; returns a channel             &lt;em&gt;C&lt;/em&gt;, any EnsureChannel calls that also return &lt;em&gt;C&lt;/em&gt;             MUST return a false value for this argument.&lt;/p&gt;
 * @out_Channel: Used to return an 'out' argument if %TRUE is returned: The Channel object. If it was created as a result of this method           call, it MUST NOT be signalled by           &lt;tp:member-ref&gt;NewChannels&lt;/tp:member-ref&gt; until after this method           returns.            &lt;tp:rationale&gt;             &lt;p&gt;This allows the requester to alter its handling of               NewChannels by knowing whether one of the channels satisfied               a request it made.&lt;/p&gt;           &lt;/tp:rationale&gt;
 * @out_Properties: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Properties of the channel that was produced, equivalent to             the properties in &lt;tp:type&gt;Channel_Details&lt;/tp:type&gt;.             Connection managers MUST NOT include properties here whose             values can change, for the same reasons as in             &lt;tp:type&gt;Channel_Details&lt;/tp:type&gt;.&lt;/p&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method EnsureChannel and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that channels are ensured to exist.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The connection manager is in the best position to determine which             existing channels could satisfy which requests.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_requests_run_ensure_channel (TpConnection *proxy,
    gint timeout_ms,
    GHashTable *in_Request,
    gboolean *out_Yours,
    gchar **out_Channel,
    GHashTable **out_Properties,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_REQUESTS;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_requests_run_state_ensure_channel state = {
      NULL /* loop */, error,
    out_Yours,
    out_Channel,
    out_Properties,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "EnsureChannel", iface,
      _tp_cli_connection_interface_requests_finish_running_ensure_channel,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "EnsureChannel",
          _tp_cli_connection_interface_requests_collect_callback_ensure_channel,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Request,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


static inline void
tp_cli_add_signals_for_connection_interface_simple_presence (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "PresencesChanged",
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))),
      G_TYPE_INVALID);
}


/**
 * tp_cli_connection_interface_simple_presence_signal_callback_presences_changed:
 * @proxy: The proxy on which tp_cli_connection_interface_simple_presence_connect_to_presences_changed ()
 *  was called
 * @arg_Presence: A dictionary of contact handles mapped to the status,           presence type and status message.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal PresencesChanged.
 */
static void
_tp_cli_connection_interface_simple_presence_collect_args_of_presences_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    GHashTable *arg_Presence,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))));
  g_value_set_boxed (args->values + 0, arg_Presence);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_interface_simple_presence_invoke_callback_for_presences_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_simple_presence_signal_callback_presences_changed callback =
      (tp_cli_connection_interface_simple_presence_signal_callback_presences_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_interface_simple_presence_connect_to_presences_changed:
 * @proxy: A #TpConnection or subclass
 * @callback: Callback to be called when the signal is
 *   received
 * @user_data: User-supplied data for the callback
 * @destroy: Destructor for the user-supplied data, which
 *   will be called when this signal is disconnected, or
 *   before this function returns %NULL
 * @weak_object: A #GObject which will be weakly referenced; 
 *   if it is destroyed, this callback will automatically be
 *   disconnected
 * @error: If not %NULL, used to raise an error if %NULL is
 *   returned
 *
 * Connect a handler to the signal PresencesChanged.
 *
 * This signal should be emitted when your own presence has been changed,         or the presence of the member of any of the connection&apos;s channels has         been changed.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_interface_simple_presence_connect_to_presences_changed (TpConnection *proxy,
    tp_cli_connection_interface_simple_presence_signal_callback_presences_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION_INTERFACE_SIMPLE_PRESENCE, "PresencesChanged",
      expected_types,
      G_CALLBACK (_tp_cli_connection_interface_simple_presence_collect_args_of_presences_changed),
      _tp_cli_connection_interface_simple_presence_invoke_callback_for_presences_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_interface_simple_presence_callback_for_set_presence:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a SetPresence method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_simple_presence_collect_callback_set_presence (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_connection_interface_simple_presence_invoke_callback_set_presence (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_simple_presence_callback_for_set_presence callback = (tp_cli_connection_interface_simple_presence_callback_for_set_presence) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_simple_presence_call_set_presence:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Status: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The string identifier of the desired status. Possible status             identifiers are defined in the             &lt;tp:member-ref&gt;Statuses&lt;/tp:member-ref&gt; property.&lt;/p&gt;            &lt;p&gt;Clients MUST NOT set a status whose string value they do not             recognise, even if its presence type in Statuses             matches what the user requested.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;Suppose a protocol has statuses that include &apos;phone&apos; (of type               BUSY) and &apos;in-a-meeting&apos; (of type BUSY), but there is no               generic &apos;busy&apos; status.&lt;/p&gt;              &lt;p&gt;If the user requests &amp;quot;Busy&amp;quot; status from a menu, a               client author might be tempted to pick an arbitrary status               that has type BUSY. However, on this protocol, neither of               the choices would be appropriate, and incorrect information               about the user would be conveyed.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;Statuses whose &lt;tp:type&gt;Connection_Presence_Type&lt;/tp:type&gt;             is Offline, Error or Unknown MUST NOT be passed to this             function. Connection managers SHOULD reject these statuses.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;To go offline, call &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection&quot;&gt;Disconnect&lt;/tp:dbus-ref&gt;             instead. The &amp;quot;error&amp;quot; and &amp;quot;unknown&amp;quot; statuses make no sense.&lt;/p&gt;           &lt;/tp:rationale&gt;
 * @in_Status_Message: Used to pass an 'in' argument: The status message associated with the current status.
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a SetPresence method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that the presence status and status message are published for           the connection.  Changes will be indicated by           &lt;tp:member-ref&gt;PresencesChanged&lt;/tp:member-ref&gt;           signals being emitted.&lt;/p&gt;          &lt;p&gt;This method may be called on a newly-created connection while it           is still in the DISCONNECTED state, to request that when the           connection connects, it will do so with the selected status.&lt;/p&gt;          &lt;p&gt;In DISCONNECTED state the           &lt;tp:member-ref&gt;Statuses&lt;/tp:member-ref&gt;           property will indicate which statuses are allowed to be set           while DISCONNECTED (none, if the Connection Manager doesn&apos;t allow           this). This value MUST NOT be cached, as the set of allowed           presences might change upon connecting.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_simple_presence_call_set_presence (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Status,
    const gchar *in_Status_Message,
    tp_cli_connection_interface_simple_presence_callback_for_set_presence callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_SIMPLE_PRESENCE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "SetPresence",
          G_TYPE_STRING, in_Status,
          G_TYPE_STRING, in_Status_Message,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "SetPresence", iface,
          _tp_cli_connection_interface_simple_presence_invoke_callback_set_presence,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "SetPresence",
              _tp_cli_connection_interface_simple_presence_collect_callback_set_presence,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Status,
              G_TYPE_STRING, in_Status_Message,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_simple_presence_run_state_set_presence;
static void
_tp_cli_connection_interface_simple_presence_finish_running_set_presence (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_simple_presence_run_state_set_presence *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_simple_presence_run_set_presence:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Status: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The string identifier of the desired status. Possible status             identifiers are defined in the             &lt;tp:member-ref&gt;Statuses&lt;/tp:member-ref&gt; property.&lt;/p&gt;            &lt;p&gt;Clients MUST NOT set a status whose string value they do not             recognise, even if its presence type in Statuses             matches what the user requested.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;Suppose a protocol has statuses that include &apos;phone&apos; (of type               BUSY) and &apos;in-a-meeting&apos; (of type BUSY), but there is no               generic &apos;busy&apos; status.&lt;/p&gt;              &lt;p&gt;If the user requests &amp;quot;Busy&amp;quot; status from a menu, a               client author might be tempted to pick an arbitrary status               that has type BUSY. However, on this protocol, neither of               the choices would be appropriate, and incorrect information               about the user would be conveyed.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;Statuses whose &lt;tp:type&gt;Connection_Presence_Type&lt;/tp:type&gt;             is Offline, Error or Unknown MUST NOT be passed to this             function. Connection managers SHOULD reject these statuses.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;To go offline, call &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection&quot;&gt;Disconnect&lt;/tp:dbus-ref&gt;             instead. The &amp;quot;error&amp;quot; and &amp;quot;unknown&amp;quot; statuses make no sense.&lt;/p&gt;           &lt;/tp:rationale&gt;
 * @in_Status_Message: Used to pass an 'in' argument: The status message associated with the current status.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method SetPresence and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that the presence status and status message are published for           the connection.  Changes will be indicated by           &lt;tp:member-ref&gt;PresencesChanged&lt;/tp:member-ref&gt;           signals being emitted.&lt;/p&gt;          &lt;p&gt;This method may be called on a newly-created connection while it           is still in the DISCONNECTED state, to request that when the           connection connects, it will do so with the selected status.&lt;/p&gt;          &lt;p&gt;In DISCONNECTED state the           &lt;tp:member-ref&gt;Statuses&lt;/tp:member-ref&gt;           property will indicate which statuses are allowed to be set           while DISCONNECTED (none, if the Connection Manager doesn&apos;t allow           this). This value MUST NOT be cached, as the set of allowed           presences might change upon connecting.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_simple_presence_run_set_presence (TpConnection *proxy,
    gint timeout_ms,
    const gchar *in_Status,
    const gchar *in_Status_Message,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_SIMPLE_PRESENCE;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_simple_presence_run_state_set_presence state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "SetPresence", iface,
      _tp_cli_connection_interface_simple_presence_finish_running_set_presence,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "SetPresence",
          _tp_cli_connection_interface_simple_presence_collect_callback_set_presence,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_STRING, in_Status,
              G_TYPE_STRING, in_Status_Message,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/**
 * tp_cli_connection_interface_simple_presence_callback_for_get_presences:
 * @proxy: the proxy on which the call was made
 * @out_Presence: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Presence information in the same format as for the             &lt;tp:member-ref&gt;PresencesChanged&lt;/tp:member-ref&gt; signal.             The returned mapping MUST include an entry for each contact             in the method&apos;s argument.&lt;/p&gt;            &lt;p&gt;The definition of the connection presence types Unknown             and Offline means that if a connection manager will return             Unknown for contacts not on the subscribe list, it MUST delay             the reply to this method call until it has found out which             contacts are, in fact, on the subscribe list.&lt;/p&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetPresences method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_interface_simple_presence_collect_callback_get_presences (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GHashTable *out_Presence;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))), &out_Presence,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Presence);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_interface_simple_presence_invoke_callback_get_presences (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_interface_simple_presence_callback_for_get_presences callback = (tp_cli_connection_interface_simple_presence_callback_for_get_presences) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnection *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnection *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_simple_presence_call_get_presences:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contacts: Used to pass an 'in' argument: An array of the contacts whose presence should be obtained.
 * @callback: called when the method call succeeds or fails;
 *   may be %NULL to make a "fire and forget" call with no 
 *   reply tracking
 * @user_data: user-supplied data passed to the callback;
 *   must be %NULL if @callback is %NULL
 * @destroy: called with the user_data as argument, after the
 *   call has succeeded, failed or been cancelled;
 *   must be %NULL if @callback is %NULL
 * @weak_object: If not %NULL, a #GObject which will be 
 *   weakly referenced; if it is destroyed, this call 
 *   will automatically be cancelled. Must be %NULL if 
 *   @callback is %NULL
 *
 * Start a GetPresences method call.
 *
 * Get presence previously emitted by         &lt;tp:member-ref&gt;PresencesChanged&lt;/tp:member-ref&gt; for the given         contacts. Data is returned in the same structure as the         PresencesChanged signal; no additional network requests are made.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_interface_simple_presence_call_get_presences (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    tp_cli_connection_interface_simple_presence_callback_for_get_presences callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_SIMPLE_PRESENCE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), NULL);
  g_return_val_if_fail (callback != NULL || user_data == NULL, NULL);
  g_return_val_if_fail (callback != NULL || destroy == NULL, NULL);
  g_return_val_if_fail (callback != NULL || weak_object == NULL, NULL);

  iface = tp_proxy_borrow_interface_by_id (
      (TpProxy *) proxy,
      interface, &error);

  if (iface == NULL)
    {
      if (callback != NULL)
        callback (proxy,
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetPresences",
          DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetPresences", iface,
          _tp_cli_connection_interface_simple_presence_invoke_callback_get_presences,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetPresences",
              _tp_cli_connection_interface_simple_presence_collect_callback_get_presences,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GHashTable **out_Presence;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_interface_simple_presence_run_state_get_presences;
static void
_tp_cli_connection_interface_simple_presence_finish_running_get_presences (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_interface_simple_presence_run_state_get_presences *state = user_data;

  state->success = (error == NULL);
  state->completed = TRUE;
  g_main_loop_quit (state->loop);

  if (error != NULL)
    {
      if (state->error != NULL)
        *state->error = error;
      else
        g_error_free (error);

      return;
    }

  if (state->out_Presence != NULL)
    *state->out_Presence = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_interface_simple_presence_run_get_presences:
 * @proxy: A #TpConnection or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contacts: Used to pass an 'in' argument: An array of the contacts whose presence should be obtained.
 * @out_Presence: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Presence information in the same format as for the             &lt;tp:member-ref&gt;PresencesChanged&lt;/tp:member-ref&gt; signal.             The returned mapping MUST include an entry for each contact             in the method&apos;s argument.&lt;/p&gt;            &lt;p&gt;The definition of the connection presence types Unknown             and Offline means that if a connection manager will return             Unknown for contacts not on the subscribe list, it MUST delay             the reply to this method call until it has found out which             contacts are, in fact, on the subscribe list.&lt;/p&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetPresences and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Get presence previously emitted by         &lt;tp:member-ref&gt;PresencesChanged&lt;/tp:member-ref&gt; for the given         contacts. Data is returned in the same structure as the         PresencesChanged signal; no additional network requests are made.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_interface_simple_presence_run_get_presences (TpConnection *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    GHashTable **out_Presence,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_INTERFACE_SIMPLE_PRESENCE;
  TpProxyPendingCall *pc;
  _tp_cli_connection_interface_simple_presence_run_state_get_presences state = {
      NULL /* loop */, error,
    out_Presence,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetPresences", iface,
      _tp_cli_connection_interface_simple_presence_finish_running_get_presences,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetPresences",
          _tp_cli_connection_interface_simple_presence_collect_callback_get_presences,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_INVALID));

  if (!state.completed)
    g_main_loop_run (state.loop);

  if (!state.completed)
    tp_proxy_pending_call_cancel (pc);

  if (loop != NULL)
    *loop = NULL;

  g_main_loop_unref (state.loop);

  return state.success;
}


/*
 * tp_cli_connection_add_signals:
 * @self: the #TpProxy
 * @quark: a quark whose string value is the interface
 *   name whose signals should be added
 * @proxy: the D-Bus proxy to which to add the signals
 * @unused: not used for anything
 *
 * Tell dbus-glib that @proxy has the signatures of all
 * signals on the given interface, if it's one we
 * support.
 *
 * This function should be used as a signal handler for
 * #TpProxy::interface-added.
 */
static void
tp_cli_connection_add_signals (TpProxy *self G_GNUC_UNUSED,
    guint quark,
    DBusGProxy *proxy,
    gpointer unused G_GNUC_UNUSED)
{
  if (quark == TP_IFACE_QUARK_CONNECTION)
    tp_cli_add_signals_for_connection (proxy);
  if (quark == TP_IFACE_QUARK_CONNECTION_INTERFACE_ALIASING)
    tp_cli_add_signals_for_connection_interface_aliasing (proxy);
  if (quark == TP_IFACE_QUARK_CONNECTION_INTERFACE_AVATARS)
    tp_cli_add_signals_for_connection_interface_avatars (proxy);
  if (quark == TP_IFACE_QUARK_CONNECTION_INTERFACE_CAPABILITIES)
    tp_cli_add_signals_for_connection_interface_capabilities (proxy);
  if (quark == TP_IFACE_QUARK_CONNECTION_INTERFACE_CONTACT_CAPABILITIES)
    tp_cli_add_signals_for_connection_interface_contact_capabilities (proxy);
  if (quark == TP_IFACE_QUARK_CONNECTION_INTERFACE_LOCATION)
    tp_cli_add_signals_for_connection_interface_location (proxy);
  if (quark == TP_IFACE_QUARK_CONNECTION_INTERFACE_PRESENCE)
    tp_cli_add_signals_for_connection_interface_presence (proxy);
  if (quark == TP_IFACE_QUARK_CONNECTION_INTERFACE_REQUESTS)
    tp_cli_add_signals_for_connection_interface_requests (proxy);
  if (quark == TP_IFACE_QUARK_CONNECTION_INTERFACE_SIMPLE_PRESENCE)
    tp_cli_add_signals_for_connection_interface_simple_presence (proxy);
}
