/* We don't want gtkdoc scanning this file, it'll get
 * confused by seeing function definitions, so mark it as: */
/*<private_header>*/

static inline void
tp_cli_add_signals_for_channel (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "Closed",
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_signal_callback_closed:
 * @proxy: The proxy on which tp_cli_channel_connect_to_closed ()
 *  was called
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal Closed.
 */
static void
_tp_cli_channel_invoke_callback_for_closed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_signal_callback_closed callback =
      (tp_cli_channel_signal_callback_closed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      user_data,
      weak_object);

  if (args != NULL)
    g_value_array_free (args);

  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_connect_to_closed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal Closed.
 *
 * Emitted when the channel has been closed. Method calls on the         channel are no longer valid after this signal has been emitted,         and the connection manager may then remove the object from the bus         at any point.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_connect_to_closed (TpChannel *proxy,
    tp_cli_channel_signal_callback_closed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[1] = {
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL, "Closed",
      expected_types,
      NULL, /* no args => no collector function */
      _tp_cli_channel_invoke_callback_for_closed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_callback_for_close:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Close method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_collect_callback_close (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_invoke_callback_close (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_callback_for_close callback = (tp_cli_channel_callback_for_close) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_call_close:
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
 * Start a Close method call.
 *
 * Request that the channel be closed. This is not the case until         the &lt;tp:member-ref&gt;Closed&lt;/tp:member-ref&gt; signal has been emitted, and         depending on the connection         manager this may simply remove you from the channel on the server,         rather than causing it to stop existing entirely. Some channels         such as contact list channels may not be closed.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_call_close (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_callback_for_close callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Close",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Close", iface,
          _tp_cli_channel_invoke_callback_close,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Close",
              _tp_cli_channel_collect_callback_close,
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
} _tp_cli_channel_run_state_close;
static void
_tp_cli_channel_finish_running_close (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_run_state_close *state = user_data;

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
 * tp_cli_channel_run_close:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Close and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Request that the channel be closed. This is not the case until         the &lt;tp:member-ref&gt;Closed&lt;/tp:member-ref&gt; signal has been emitted, and         depending on the connection         manager this may simply remove you from the channel on the server,         rather than causing it to stop existing entirely. Some channels         such as contact list channels may not be closed.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_run_close (TpChannel *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL;
  TpProxyPendingCall *pc;
  _tp_cli_channel_run_state_close state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Close", iface,
      _tp_cli_channel_finish_running_close,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Close",
          _tp_cli_channel_collect_callback_close,
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
 * tp_cli_channel_callback_for_get_channel_type:
 * @proxy: the proxy on which the call was made
 * @out_Channel_Type: Used to return an 'out' argument if @error is %NULL: The interface name
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetChannelType method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_collect_callback_get_channel_type (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_Channel_Type;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRING, &out_Channel_Type,
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
  g_value_take_string (args->values + 0, out_Channel_Type);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_invoke_callback_get_channel_type (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_callback_for_get_channel_type callback = (tp_cli_channel_callback_for_get_channel_type) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_string (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_call_get_channel_type:
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
 * Start a GetChannelType method call.
 *
 * Returns the interface name for the type of this channel.  Clients         SHOULD use the &lt;tp:member-ref&gt;ChannelType&lt;/tp:member-ref&gt; property         instead, falling back to this method only if necessary.          &lt;tp:rationale&gt;           The GetAll method lets clients retrieve all properties in one           round-trip.         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_call_get_channel_type (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_callback_for_get_channel_type callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetChannelType",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetChannelType", iface,
          _tp_cli_channel_invoke_callback_get_channel_type,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetChannelType",
              _tp_cli_channel_collect_callback_get_channel_type,
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
    gchar **out_Channel_Type;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_run_state_get_channel_type;
static void
_tp_cli_channel_finish_running_get_channel_type (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_run_state_get_channel_type *state = user_data;

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

  if (state->out_Channel_Type != NULL)
    *state->out_Channel_Type = g_value_dup_string (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_run_get_channel_type:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Channel_Type: Used to return an 'out' argument if %TRUE is returned: The interface name
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetChannelType and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns the interface name for the type of this channel.  Clients         SHOULD use the &lt;tp:member-ref&gt;ChannelType&lt;/tp:member-ref&gt; property         instead, falling back to this method only if necessary.          &lt;tp:rationale&gt;           The GetAll method lets clients retrieve all properties in one           round-trip.         &lt;/tp:rationale&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_run_get_channel_type (TpChannel *proxy,
    gint timeout_ms,
    gchar **out_Channel_Type,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL;
  TpProxyPendingCall *pc;
  _tp_cli_channel_run_state_get_channel_type state = {
      NULL /* loop */, error,
    out_Channel_Type,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetChannelType", iface,
      _tp_cli_channel_finish_running_get_channel_type,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetChannelType",
          _tp_cli_channel_collect_callback_get_channel_type,
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
 * tp_cli_channel_callback_for_get_handle:
 * @proxy: the proxy on which the call was made
 * @out_Target_Handle_Type: Used to return an 'out' argument if @error is %NULL: The same as TargetHandleType.
 * @out_Target_Handle: Used to return an 'out' argument if @error is %NULL: The same as TargetHandle.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetHandle method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_collect_callback_get_handle (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  guint out_Target_Handle_Type;
  guint out_Target_Handle;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_UINT, &out_Target_Handle_Type,
      G_TYPE_UINT, &out_Target_Handle,
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
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, out_Target_Handle_Type);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, out_Target_Handle);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_invoke_callback_get_handle (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_callback_for_get_handle callback = (tp_cli_channel_callback_for_get_handle) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          0,
          0,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_uint (args->values + 0),
      g_value_get_uint (args->values + 1),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_call_get_handle:
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
 * Start a GetHandle method call.
 *
 * Returns the handle type and number if this channel represents a         communication with a particular contact, room or server-stored list, or         zero if it is transient and defined only by its contents. Clients         SHOULD use the &lt;tp:member-ref&gt;TargetHandle&lt;/tp:member-ref&gt; and         &lt;tp:member-ref&gt;TargetHandleType&lt;/tp:member-ref&gt; properties instead,         falling back to this method only if necessary.          &lt;tp:rationale&gt;           The GetAll method lets clients retrieve all properties in one           round-trip.         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_call_get_handle (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_callback_for_get_handle callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetHandle",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetHandle", iface,
          _tp_cli_channel_invoke_callback_get_handle,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetHandle",
              _tp_cli_channel_collect_callback_get_handle,
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
    guint *out_Target_Handle_Type;
    guint *out_Target_Handle;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_run_state_get_handle;
static void
_tp_cli_channel_finish_running_get_handle (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_run_state_get_handle *state = user_data;

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

  if (state->out_Target_Handle_Type != NULL)
    *state->out_Target_Handle_Type = g_value_get_uint (args->values + 0);

  if (state->out_Target_Handle != NULL)
    *state->out_Target_Handle = g_value_get_uint (args->values + 1);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_run_get_handle:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Target_Handle_Type: Used to return an 'out' argument if %TRUE is returned: The same as TargetHandleType.
 * @out_Target_Handle: Used to return an 'out' argument if %TRUE is returned: The same as TargetHandle.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetHandle and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns the handle type and number if this channel represents a         communication with a particular contact, room or server-stored list, or         zero if it is transient and defined only by its contents. Clients         SHOULD use the &lt;tp:member-ref&gt;TargetHandle&lt;/tp:member-ref&gt; and         &lt;tp:member-ref&gt;TargetHandleType&lt;/tp:member-ref&gt; properties instead,         falling back to this method only if necessary.          &lt;tp:rationale&gt;           The GetAll method lets clients retrieve all properties in one           round-trip.         &lt;/tp:rationale&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_run_get_handle (TpChannel *proxy,
    gint timeout_ms,
    guint *out_Target_Handle_Type,
    guint *out_Target_Handle,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL;
  TpProxyPendingCall *pc;
  _tp_cli_channel_run_state_get_handle state = {
      NULL /* loop */, error,
    out_Target_Handle_Type,
    out_Target_Handle,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetHandle", iface,
      _tp_cli_channel_finish_running_get_handle,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetHandle",
          _tp_cli_channel_collect_callback_get_handle,
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
 * tp_cli_channel_callback_for_get_interfaces:
 * @proxy: the proxy on which the call was made
 * @out_Interfaces: Used to return an 'out' argument if @error is %NULL: An array of the D-Bus interface names
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetInterfaces method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_collect_callback_get_interfaces (DBusGProxy *proxy,
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
_tp_cli_channel_invoke_callback_get_interfaces (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_callback_for_get_interfaces callback = (tp_cli_channel_callback_for_get_interfaces) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_call_get_interfaces:
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
 * Get the optional interfaces implemented by the channel.         Clients SHOULD use the &lt;tp:member-ref&gt;Interfaces&lt;/tp:member-ref&gt;         property instead, falling back to this method only if necessary.          &lt;tp:rationale&gt;           The GetAll method lets clients retrieve all properties in one           round-trip.         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_call_get_interfaces (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_callback_for_get_interfaces callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
          _tp_cli_channel_invoke_callback_get_interfaces,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetInterfaces",
              _tp_cli_channel_collect_callback_get_interfaces,
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
} _tp_cli_channel_run_state_get_interfaces;
static void
_tp_cli_channel_finish_running_get_interfaces (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_run_state_get_interfaces *state = user_data;

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
 * tp_cli_channel_run_get_interfaces:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Interfaces: Used to return an 'out' argument if %TRUE is returned: An array of the D-Bus interface names
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
 * Get the optional interfaces implemented by the channel.         Clients SHOULD use the &lt;tp:member-ref&gt;Interfaces&lt;/tp:member-ref&gt;         property instead, falling back to this method only if necessary.          &lt;tp:rationale&gt;           The GetAll method lets clients retrieve all properties in one           round-trip.         &lt;/tp:rationale&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_run_get_interfaces (TpChannel *proxy,
    gint timeout_ms,
    gchar ***out_Interfaces,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL;
  TpProxyPendingCall *pc;
  _tp_cli_channel_run_state_get_interfaces state = {
      NULL /* loop */, error,
    out_Interfaces,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetInterfaces", iface,
      _tp_cli_channel_finish_running_get_interfaces,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetInterfaces",
          _tp_cli_channel_collect_callback_get_interfaces,
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
tp_cli_add_signals_for_channel_interface_call_state (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "CallStateChanged",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_interface_call_state_signal_callback_call_state_changed:
 * @proxy: The proxy on which tp_cli_channel_interface_call_state_connect_to_call_state_changed ()
 *  was called
 * @arg_Contact: An integer handle for the contact.
 * @arg_State: The new state for this contact.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal CallStateChanged.
 */
static void
_tp_cli_channel_interface_call_state_collect_args_of_call_state_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Contact,
    guint arg_State,
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
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_State);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_interface_call_state_invoke_callback_for_call_state_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_call_state_signal_callback_call_state_changed callback =
      (tp_cli_channel_interface_call_state_signal_callback_call_state_changed) generic_callback;

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
 * tp_cli_channel_interface_call_state_connect_to_call_state_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal CallStateChanged.
 *
 * Emitted when the state of a member of the channel has changed.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_interface_call_state_connect_to_call_state_changed (TpChannel *proxy,
    tp_cli_channel_interface_call_state_signal_callback_call_state_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_INTERFACE_CALL_STATE, "CallStateChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_interface_call_state_collect_args_of_call_state_changed),
      _tp_cli_channel_interface_call_state_invoke_callback_for_call_state_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_interface_call_state_callback_for_get_call_states:
 * @proxy: the proxy on which the call was made
 * @out_States: Used to return an 'out' argument if @error is %NULL: The current call states. Participants where the call state flags           would be 0 (all unset) may be omitted from this mapping.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetCallStates method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_call_state_collect_callback_get_call_states (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GHashTable *out_States;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_UINT)), &out_States,
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
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_UINT)));
  g_value_take_boxed (args->values + 0, out_States);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_interface_call_state_invoke_callback_get_call_states (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_call_state_callback_for_get_call_states callback = (tp_cli_channel_interface_call_state_callback_for_get_call_states) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_call_state_call_get_call_states:
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
 * Start a GetCallStates method call.
 *
 * Get the current call states for all contacts involved in this call.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_call_state_call_get_call_states (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_call_state_callback_for_get_call_states callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_CALL_STATE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetCallStates",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetCallStates", iface,
          _tp_cli_channel_interface_call_state_invoke_callback_get_call_states,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetCallStates",
              _tp_cli_channel_interface_call_state_collect_callback_get_call_states,
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
    GHashTable **out_States;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_call_state_run_state_get_call_states;
static void
_tp_cli_channel_interface_call_state_finish_running_get_call_states (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_call_state_run_state_get_call_states *state = user_data;

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

  if (state->out_States != NULL)
    *state->out_States = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_call_state_run_get_call_states:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_States: Used to return an 'out' argument if %TRUE is returned: The current call states. Participants where the call state flags           would be 0 (all unset) may be omitted from this mapping.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetCallStates and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Get the current call states for all contacts involved in this call.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_call_state_run_get_call_states (TpChannel *proxy,
    gint timeout_ms,
    GHashTable **out_States,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_CALL_STATE;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_call_state_run_state_get_call_states state = {
      NULL /* loop */, error,
    out_States,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetCallStates", iface,
      _tp_cli_channel_interface_call_state_finish_running_get_call_states,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetCallStates",
          _tp_cli_channel_interface_call_state_collect_callback_get_call_states,
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
tp_cli_add_signals_for_channel_interface_chat_state (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "ChatStateChanged",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_interface_chat_state_signal_callback_chat_state_changed:
 * @proxy: The proxy on which tp_cli_channel_interface_chat_state_connect_to_chat_state_changed ()
 *  was called
 * @arg_Contact: An integer handle for the contact.
 * @arg_State: The new state of this contact.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal ChatStateChanged.
 */
static void
_tp_cli_channel_interface_chat_state_collect_args_of_chat_state_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Contact,
    guint arg_State,
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
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_State);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_interface_chat_state_invoke_callback_for_chat_state_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_chat_state_signal_callback_chat_state_changed callback =
      (tp_cli_channel_interface_chat_state_signal_callback_chat_state_changed) generic_callback;

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
 * tp_cli_channel_interface_chat_state_connect_to_chat_state_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal ChatStateChanged.
 *
 * Emitted when the state of a member of the channel has changed.         This includes local state.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_interface_chat_state_connect_to_chat_state_changed (TpChannel *proxy,
    tp_cli_channel_interface_chat_state_signal_callback_chat_state_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_INTERFACE_CHAT_STATE, "ChatStateChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_interface_chat_state_collect_args_of_chat_state_changed),
      _tp_cli_channel_interface_chat_state_invoke_callback_for_chat_state_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_interface_chat_state_callback_for_set_chat_state:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a SetChatState method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_chat_state_collect_callback_set_chat_state (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_interface_chat_state_invoke_callback_set_chat_state (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_chat_state_callback_for_set_chat_state callback = (tp_cli_channel_interface_chat_state_callback_for_set_chat_state) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_chat_state_call_set_chat_state:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_State: Used to pass an 'in' argument: The new state.
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
 * Start a SetChatState method call.
 *
 * Set the local state and notify other members of the channel that it         has changed.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_chat_state_call_set_chat_state (TpChannel *proxy,
    gint timeout_ms,
    guint in_State,
    tp_cli_channel_interface_chat_state_callback_for_set_chat_state callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_CHAT_STATE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "SetChatState",
          G_TYPE_UINT, in_State,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "SetChatState", iface,
          _tp_cli_channel_interface_chat_state_invoke_callback_set_chat_state,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "SetChatState",
              _tp_cli_channel_interface_chat_state_collect_callback_set_chat_state,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_State,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_chat_state_run_state_set_chat_state;
static void
_tp_cli_channel_interface_chat_state_finish_running_set_chat_state (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_chat_state_run_state_set_chat_state *state = user_data;

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
 * tp_cli_channel_interface_chat_state_run_set_chat_state:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_State: Used to pass an 'in' argument: The new state.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method SetChatState and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Set the local state and notify other members of the channel that it         has changed.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_chat_state_run_set_chat_state (TpChannel *proxy,
    gint timeout_ms,
    guint in_State,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_CHAT_STATE;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_chat_state_run_state_set_chat_state state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "SetChatState", iface,
      _tp_cli_channel_interface_chat_state_finish_running_set_chat_state,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "SetChatState",
          _tp_cli_channel_interface_chat_state_collect_callback_set_chat_state,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_State,
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
 * tp_cli_channel_interface_dtmf_callback_for_start_tone:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a StartTone method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_dtmf_collect_callback_start_tone (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_interface_dtmf_invoke_callback_start_tone (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_dtmf_callback_for_start_tone callback = (tp_cli_channel_interface_dtmf_callback_for_start_tone) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_dtmf_call_start_tone:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Stream_ID: Used to pass an 'in' argument: A stream ID as defined in the StreamedMedia channel type.
 * @in_Event: Used to pass an 'in' argument: A numeric event code from the DTMF_Event enum.
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
 * Start a StartTone method call.
 *
 * Start sending a DTMF tone on this stream. Where possible, the tone         will continue until &lt;tp:member-ref&gt;StopTone&lt;/tp:member-ref&gt; is called.         On certain protocols, it may         only be possible to send events with a predetermined length. In this         case, the implementation may emit a fixed-length tone, and the StopTone         method call should return NotAvailable.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_dtmf_call_start_tone (TpChannel *proxy,
    gint timeout_ms,
    guint in_Stream_ID,
    guchar in_Event,
    tp_cli_channel_interface_dtmf_callback_for_start_tone callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_DTMF;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "StartTone",
          G_TYPE_UINT, in_Stream_ID,
          G_TYPE_UCHAR, in_Event,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "StartTone", iface,
          _tp_cli_channel_interface_dtmf_invoke_callback_start_tone,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "StartTone",
              _tp_cli_channel_interface_dtmf_collect_callback_start_tone,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Stream_ID,
              G_TYPE_UCHAR, in_Event,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_dtmf_run_state_start_tone;
static void
_tp_cli_channel_interface_dtmf_finish_running_start_tone (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_dtmf_run_state_start_tone *state = user_data;

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
 * tp_cli_channel_interface_dtmf_run_start_tone:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Stream_ID: Used to pass an 'in' argument: A stream ID as defined in the StreamedMedia channel type.
 * @in_Event: Used to pass an 'in' argument: A numeric event code from the DTMF_Event enum.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method StartTone and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Start sending a DTMF tone on this stream. Where possible, the tone         will continue until &lt;tp:member-ref&gt;StopTone&lt;/tp:member-ref&gt; is called.         On certain protocols, it may         only be possible to send events with a predetermined length. In this         case, the implementation may emit a fixed-length tone, and the StopTone         method call should return NotAvailable.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_dtmf_run_start_tone (TpChannel *proxy,
    gint timeout_ms,
    guint in_Stream_ID,
    guchar in_Event,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_DTMF;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_dtmf_run_state_start_tone state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "StartTone", iface,
      _tp_cli_channel_interface_dtmf_finish_running_start_tone,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "StartTone",
          _tp_cli_channel_interface_dtmf_collect_callback_start_tone,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Stream_ID,
              G_TYPE_UCHAR, in_Event,
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
 * tp_cli_channel_interface_dtmf_callback_for_stop_tone:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a StopTone method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_dtmf_collect_callback_stop_tone (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_interface_dtmf_invoke_callback_stop_tone (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_dtmf_callback_for_stop_tone callback = (tp_cli_channel_interface_dtmf_callback_for_stop_tone) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_dtmf_call_stop_tone:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Stream_ID: Used to pass an 'in' argument: A stream ID as defined in the StreamedMedia channel type.
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
 * Start a StopTone method call.
 *
 * Stop sending any DTMF tone which has been started using the         &lt;tp:member-ref&gt;StartTone&lt;/tp:member-ref&gt;         method. If there is no current tone, this method will do nothing.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_dtmf_call_stop_tone (TpChannel *proxy,
    gint timeout_ms,
    guint in_Stream_ID,
    tp_cli_channel_interface_dtmf_callback_for_stop_tone callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_DTMF;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "StopTone",
          G_TYPE_UINT, in_Stream_ID,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "StopTone", iface,
          _tp_cli_channel_interface_dtmf_invoke_callback_stop_tone,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "StopTone",
              _tp_cli_channel_interface_dtmf_collect_callback_stop_tone,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Stream_ID,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_dtmf_run_state_stop_tone;
static void
_tp_cli_channel_interface_dtmf_finish_running_stop_tone (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_dtmf_run_state_stop_tone *state = user_data;

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
 * tp_cli_channel_interface_dtmf_run_stop_tone:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Stream_ID: Used to pass an 'in' argument: A stream ID as defined in the StreamedMedia channel type.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method StopTone and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Stop sending any DTMF tone which has been started using the         &lt;tp:member-ref&gt;StartTone&lt;/tp:member-ref&gt;         method. If there is no current tone, this method will do nothing.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_dtmf_run_stop_tone (TpChannel *proxy,
    gint timeout_ms,
    guint in_Stream_ID,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_DTMF;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_dtmf_run_state_stop_tone state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "StopTone", iface,
      _tp_cli_channel_interface_dtmf_finish_running_stop_tone,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "StopTone",
          _tp_cli_channel_interface_dtmf_collect_callback_stop_tone,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Stream_ID,
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
 * tp_cli_channel_interface_destroyable_callback_for_destroy:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Destroy method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_destroyable_collect_callback_destroy (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_interface_destroyable_invoke_callback_destroy (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_destroyable_callback_for_destroy callback = (tp_cli_channel_interface_destroyable_callback_for_destroy) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_destroyable_call_destroy:
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
 * Start a Destroy method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Close the channel abruptly, possibly with loss of data. The           connection manager MUST NOT re-create the channel unless/until           more events occur.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The main motivating situation for this method is that when a Text             channel with pending messages is closed with Close, it comes back             as an incoming channel (to avoid a race between Close and an             incoming message). If Destroy is called on a Text channel, the CM             should delete all pending messages and close the channel, and             the channel shouldn&apos;t be re-created until/unless another message             arrives.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;Most clients SHOULD call           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Channel.Close&lt;/tp:dbus-ref&gt;           instead. However, if a client explicitly intends to destroy the           channel with possible loss of data, it SHOULD call this method           if this interface is supported (according to the           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Channel.Interfaces&lt;/tp:dbus-ref&gt;           property), falling back to Close if not.&lt;/p&gt;          &lt;p&gt;In particular, channel dispatchers SHOULD use this method if           available when terminating channels that cannot be handled           correctly (for instance, if no handler has been installed for           a channel type, or if the handler crashes repeatedly).&lt;/p&gt;          &lt;p&gt;Connection managers do not need to implement this interface on           channels where Close and Destroy would be equivalent.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;Callers need to be able to fall back to Close in any case.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_destroyable_call_destroy (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_destroyable_callback_for_destroy callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_DESTROYABLE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Destroy",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Destroy", iface,
          _tp_cli_channel_interface_destroyable_invoke_callback_destroy,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Destroy",
              _tp_cli_channel_interface_destroyable_collect_callback_destroy,
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
} _tp_cli_channel_interface_destroyable_run_state_destroy;
static void
_tp_cli_channel_interface_destroyable_finish_running_destroy (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_destroyable_run_state_destroy *state = user_data;

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
 * tp_cli_channel_interface_destroyable_run_destroy:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Destroy and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Close the channel abruptly, possibly with loss of data. The           connection manager MUST NOT re-create the channel unless/until           more events occur.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The main motivating situation for this method is that when a Text             channel with pending messages is closed with Close, it comes back             as an incoming channel (to avoid a race between Close and an             incoming message). If Destroy is called on a Text channel, the CM             should delete all pending messages and close the channel, and             the channel shouldn&apos;t be re-created until/unless another message             arrives.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;Most clients SHOULD call           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Channel.Close&lt;/tp:dbus-ref&gt;           instead. However, if a client explicitly intends to destroy the           channel with possible loss of data, it SHOULD call this method           if this interface is supported (according to the           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Channel.Interfaces&lt;/tp:dbus-ref&gt;           property), falling back to Close if not.&lt;/p&gt;          &lt;p&gt;In particular, channel dispatchers SHOULD use this method if           available when terminating channels that cannot be handled           correctly (for instance, if no handler has been installed for           a channel type, or if the handler crashes repeatedly).&lt;/p&gt;          &lt;p&gt;Connection managers do not need to implement this interface on           channels where Close and Destroy would be equivalent.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;Callers need to be able to fall back to Close in any case.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_destroyable_run_destroy (TpChannel *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_DESTROYABLE;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_destroyable_run_state_destroy state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Destroy", iface,
      _tp_cli_channel_interface_destroyable_finish_running_destroy,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Destroy",
          _tp_cli_channel_interface_destroyable_collect_callback_destroy,
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
tp_cli_add_signals_for_channel_interface_group (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "HandleOwnersChanged",
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_UINT)),
      DBUS_TYPE_G_UINT_ARRAY,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "SelfHandleChanged",
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "GroupFlagsChanged",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "MembersChanged",
      G_TYPE_STRING,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "MembersChangedDetailed",
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)),
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_interface_group_signal_callback_handle_owners_changed:
 * @proxy: The proxy on which tp_cli_channel_interface_group_connect_to_handle_owners_changed ()
 *  was called
 * @arg_Added: A map from channel-specific handles to their owners, in which the           keys include all the handles that were added to the keys of the           HandleOwners property, and all the handles in that property whose           owner has changed
 * @arg_Removed: The channel-specific handles that were removed from the keys of the           HandleOwners property, as a result of the contact leaving this group           in a previous &lt;tp:member-ref&gt;MembersChanged&lt;/tp:member-ref&gt; signal
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal HandleOwnersChanged.
 */
static void
_tp_cli_channel_interface_group_collect_args_of_handle_owners_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    GHashTable *arg_Added,
    const GArray *arg_Removed,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (2);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 2; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_UINT)));
  g_value_set_boxed (args->values + 0, arg_Added);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, DBUS_TYPE_G_UINT_ARRAY);
  g_value_set_boxed (args->values + 1, arg_Removed);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_interface_group_invoke_callback_for_handle_owners_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_signal_callback_handle_owners_changed callback =
      (tp_cli_channel_interface_group_signal_callback_handle_owners_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      g_value_get_boxed (args->values + 1),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_interface_group_connect_to_handle_owners_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal HandleOwnersChanged.
 *
 * Emitted whenever the &lt;tp:member-ref&gt;HandleOwners&lt;/tp:member-ref&gt;         property changes.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_interface_group_connect_to_handle_owners_changed (TpChannel *proxy,
    tp_cli_channel_interface_group_signal_callback_handle_owners_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_UINT)),
      DBUS_TYPE_G_UINT_ARRAY,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP, "HandleOwnersChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_interface_group_collect_args_of_handle_owners_changed),
      _tp_cli_channel_interface_group_invoke_callback_for_handle_owners_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_interface_group_signal_callback_self_handle_changed:
 * @proxy: The proxy on which tp_cli_channel_interface_group_connect_to_self_handle_changed ()
 *  was called
 * @arg_Self_Handle: The new value of the SelfHandle property.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal SelfHandleChanged.
 */
static void
_tp_cli_channel_interface_group_collect_args_of_self_handle_changed (DBusGProxy *proxy G_GNUC_UNUSED,
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
_tp_cli_channel_interface_group_invoke_callback_for_self_handle_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_signal_callback_self_handle_changed callback =
      (tp_cli_channel_interface_group_signal_callback_self_handle_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_interface_group_connect_to_self_handle_changed:
 * @proxy: A #TpChannel or subclass
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
 * Emitted whenever the &lt;tp:member-ref&gt;SelfHandle&lt;/tp:member-ref&gt; property         changes.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_interface_group_connect_to_self_handle_changed (TpChannel *proxy,
    tp_cli_channel_interface_group_signal_callback_self_handle_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP, "SelfHandleChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_interface_group_collect_args_of_self_handle_changed),
      _tp_cli_channel_interface_group_invoke_callback_for_self_handle_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_interface_group_signal_callback_group_flags_changed:
 * @proxy: The proxy on which tp_cli_channel_interface_group_connect_to_group_flags_changed ()
 *  was called
 * @arg_Added: A bitwise OR of the flags which have been set
 * @arg_Removed: A bitwise OR of the flags which have been cleared
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal GroupFlagsChanged.
 */
static void
_tp_cli_channel_interface_group_collect_args_of_group_flags_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Added,
    guint arg_Removed,
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
  g_value_set_uint (args->values + 0, arg_Added);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Removed);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_interface_group_invoke_callback_for_group_flags_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_signal_callback_group_flags_changed callback =
      (tp_cli_channel_interface_group_signal_callback_group_flags_changed) generic_callback;

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
 * tp_cli_channel_interface_group_connect_to_group_flags_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal GroupFlagsChanged.
 *
 * Emitted when the flags as returned by         &lt;tp:member-ref&gt;GetGroupFlags&lt;/tp:member-ref&gt; are changed.         The user interface should be updated as appropriate.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_interface_group_connect_to_group_flags_changed (TpChannel *proxy,
    tp_cli_channel_interface_group_signal_callback_group_flags_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP, "GroupFlagsChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_interface_group_collect_args_of_group_flags_changed),
      _tp_cli_channel_interface_group_invoke_callback_for_group_flags_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_interface_group_signal_callback_members_changed:
 * @proxy: The proxy on which tp_cli_channel_interface_group_connect_to_members_changed ()
 *  was called
 * @arg_Message: A string message from the server, or blank if not
 * @arg_Added: A list of members added to the channel
 * @arg_Removed: A list of members removed from the channel
 * @arg_Local_Pending: A list of members who are pending local approval
 * @arg_Remote_Pending: A list of members who are pending remote approval
 * @arg_Actor: The contact handle of the person who made the change, or 0           if not known
 * @arg_Reason: A reason for the change
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal MembersChanged.
 */
static void
_tp_cli_channel_interface_group_collect_args_of_members_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Message,
    const GArray *arg_Added,
    const GArray *arg_Removed,
    const GArray *arg_Local_Pending,
    const GArray *arg_Remote_Pending,
    guint arg_Actor,
    guint arg_Reason,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (7);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 7; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_STRING);
  g_value_set_string (args->values + 0, arg_Message);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, DBUS_TYPE_G_UINT_ARRAY);
  g_value_set_boxed (args->values + 1, arg_Added);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, DBUS_TYPE_G_UINT_ARRAY);
  g_value_set_boxed (args->values + 2, arg_Removed);

  g_value_unset (args->values + 3);
  g_value_init (args->values + 3, DBUS_TYPE_G_UINT_ARRAY);
  g_value_set_boxed (args->values + 3, arg_Local_Pending);

  g_value_unset (args->values + 4);
  g_value_init (args->values + 4, DBUS_TYPE_G_UINT_ARRAY);
  g_value_set_boxed (args->values + 4, arg_Remote_Pending);

  g_value_unset (args->values + 5);
  g_value_init (args->values + 5, G_TYPE_UINT);
  g_value_set_uint (args->values + 5, arg_Actor);

  g_value_unset (args->values + 6);
  g_value_init (args->values + 6, G_TYPE_UINT);
  g_value_set_uint (args->values + 6, arg_Reason);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_interface_group_invoke_callback_for_members_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_signal_callback_members_changed callback =
      (tp_cli_channel_interface_group_signal_callback_members_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_string (args->values + 0),
      g_value_get_boxed (args->values + 1),
      g_value_get_boxed (args->values + 2),
      g_value_get_boxed (args->values + 3),
      g_value_get_boxed (args->values + 4),
      g_value_get_uint (args->values + 5),
      g_value_get_uint (args->values + 6),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_interface_group_connect_to_members_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal MembersChanged.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Emitted when contacts join any of the three lists (members, local           pending or remote pending) or when they leave any of the three lists.           There may also be a message from the server regarding this change,           which may be displayed to the user if desired.&lt;/p&gt;          &lt;p&gt;All channel-specific handles that are mentioned in this signal           MUST be represented in the value of the           &lt;tp:member-ref&gt;HandleOwners&lt;/tp:member-ref&gt; property.           In practice, this will mean that           &lt;tp:member-ref&gt;HandleOwnersChanged&lt;/tp:member-ref&gt; is           emitted &lt;em&gt;before&lt;/em&gt; emitting a MembersChanged signal in which           channel-specific handles are added, but that it is emitted           &lt;em&gt;after&lt;/em&gt; emitting a MembersChanged signal in which           channel-specific handles are removed.&lt;/p&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_interface_group_connect_to_members_changed (TpChannel *proxy,
    tp_cli_channel_interface_group_signal_callback_members_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[8] = {
      G_TYPE_STRING,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP, "MembersChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_interface_group_collect_args_of_members_changed),
      _tp_cli_channel_interface_group_invoke_callback_for_members_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_interface_group_signal_callback_members_changed_detailed:
 * @proxy: The proxy on which tp_cli_channel_interface_group_connect_to_members_changed_detailed ()
 *  was called
 * @arg_Added: A list of members added to the channel
 * @arg_Removed: A list of members removed from the channel
 * @arg_Local_Pending: A list of members who are pending local approval
 * @arg_Remote_Pending: A list of members who are pending remote approval
 * @arg_Details: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Information about the change, which may include the following             well-known keys:&lt;/p&gt;            &lt;dl&gt;             &lt;dt&gt;actor (u — &lt;tp:type&gt;Contact_Handle&lt;/tp:type&gt;)&lt;/dt&gt;             &lt;dd&gt;The contact handle of the person who made the change; 0 or               omitted if unknown or not applicable.&lt;/dd&gt;              &lt;dt&gt;change-reason (u — &lt;tp:type&gt;Channel_Group_Change_Reason&lt;/tp:type&gt;)&lt;/dt&gt;             &lt;dd&gt;A reason for the change.&lt;/dd&gt;              &lt;dt&gt;contact-ids (a{us} — &lt;tp:type&gt;Handle_Identifier_Map&lt;/tp:type&gt;)&lt;/dt&gt;             &lt;dd&gt;               &lt;p&gt;The string identifiers for handles mentioned in this signal, to               give clients the minimal information necessary to react to the               event without waiting for round-trips.  Connection managers               SHOULD include the identifiers for members added to the group and               for the actor (if any); they MAY omit the identifiers for handles               which have been removed from the group.&lt;/p&gt;                &lt;tp:rationale&gt;                 &lt;p&gt;On IRC, an event such as a netsplit could cause the vast                 majority of a channel to leave.  Given that clients should                 already know the identifiers of a channel&apos;s members, including                 potentially hundreds of strings in the netsplit signal is                 unnecessary.&lt;/p&gt;               &lt;/tp:rationale&gt;                &lt;p&gt;Clients MUST NOT assume that the presence or absence of a                 handle in this mapping is meaningful. This mapping is merely                 an optimization for round-trip reduction, and connection                 managers MAY add additional handles, omit some handles, or                 omit the mapping completely.&lt;/p&gt;             &lt;/dd&gt;              &lt;dt&gt;message (s)&lt;/dt&gt;             &lt;dd&gt;A string message from the server regarding the change&lt;/dd&gt;              &lt;dt&gt;error (s — &lt;tp:type&gt;DBus_Error_Name&lt;/tp:type&gt;)&lt;/dt&gt;             &lt;dd&gt;A (possibly implementation-specific) DBus error describing the               change, providing more specific information than the               &lt;tp:type&gt;Channel_Group_Change_Reason&lt;/tp:type&gt; enum allows. This               MUST only be present if it is strictly more informative than               &apos;change-reason&apos;; if present, &apos;change-reason&apos; MUST be set to the               closest available reason.                &lt;tp:rationale&gt;                 A SIP connection manager might want to signal &amp;quot;402 Payment                 required&amp;quot; as something more specific than Error or                 Permission_Denied so that a SIP-aware UI could handle it                 specially; including a namespaced error permits this to be done                 without &lt;tp:type&gt;Channel_Group_Change_Reason&lt;/tp:type&gt; being                 extended to encompass every error any CM ever wants to report.               &lt;/tp:rationale&gt;             &lt;/dd&gt;              &lt;dt&gt;debug-message (s)&lt;/dt&gt;             &lt;dd&gt;Debugging information on the change. SHOULD NOT be shown to               users in normal circumstances.&lt;/dd&gt;           &lt;/dl&gt;
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal MembersChangedDetailed.
 */
static void
_tp_cli_channel_interface_group_collect_args_of_members_changed_detailed (DBusGProxy *proxy G_GNUC_UNUSED,
    const GArray *arg_Added,
    const GArray *arg_Removed,
    const GArray *arg_Local_Pending,
    const GArray *arg_Remote_Pending,
    GHashTable *arg_Details,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (5);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 5; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, DBUS_TYPE_G_UINT_ARRAY);
  g_value_set_boxed (args->values + 0, arg_Added);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, DBUS_TYPE_G_UINT_ARRAY);
  g_value_set_boxed (args->values + 1, arg_Removed);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, DBUS_TYPE_G_UINT_ARRAY);
  g_value_set_boxed (args->values + 2, arg_Local_Pending);

  g_value_unset (args->values + 3);
  g_value_init (args->values + 3, DBUS_TYPE_G_UINT_ARRAY);
  g_value_set_boxed (args->values + 3, arg_Remote_Pending);

  g_value_unset (args->values + 4);
  g_value_init (args->values + 4, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)));
  g_value_set_boxed (args->values + 4, arg_Details);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_interface_group_invoke_callback_for_members_changed_detailed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_signal_callback_members_changed_detailed callback =
      (tp_cli_channel_interface_group_signal_callback_members_changed_detailed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      g_value_get_boxed (args->values + 1),
      g_value_get_boxed (args->values + 2),
      g_value_get_boxed (args->values + 3),
      g_value_get_boxed (args->values + 4),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_interface_group_connect_to_members_changed_detailed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal MembersChangedDetailed.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Emitted when contacts join any of the three lists (members, local           pending or remote pending) or when they leave any of the three           lists. This signal provides a superset of the information provided by           &lt;tp:member-ref&gt;MembersChanged&lt;/tp:member-ref&gt;;           if the channel&apos;s &lt;tp:member-ref&gt;GroupFlags&lt;/tp:member-ref&gt;           contains Members_Changed_Detailed, then clients may listen exclusively           to this signal in preference to that signal.&lt;/p&gt;          &lt;p&gt;All channel-specific handles that are mentioned in this signal           MUST be represented in the value of the           &lt;tp:member-ref&gt;HandleOwners&lt;/tp:member-ref&gt; property.  In practice,           this will mean that           &lt;tp:member-ref&gt;HandleOwnersChanged&lt;/tp:member-ref&gt; is emitted           &lt;em&gt;before&lt;/em&gt; emitting a MembersChangedDetailed signal in which           channel-specific handles are added, but that it is emitted           &lt;em&gt;after&lt;/em&gt; emitting a MembersChangedDetailed signal in which           channel-specific handles are removed.&lt;/p&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_interface_group_connect_to_members_changed_detailed (TpChannel *proxy,
    tp_cli_channel_interface_group_signal_callback_members_changed_detailed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[6] = {
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      DBUS_TYPE_G_UINT_ARRAY,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP, "MembersChangedDetailed",
      expected_types,
      G_CALLBACK (_tp_cli_channel_interface_group_collect_args_of_members_changed_detailed),
      _tp_cli_channel_interface_group_invoke_callback_for_members_changed_detailed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_interface_group_callback_for_add_members:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a AddMembers method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_group_collect_callback_add_members (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_interface_group_invoke_callback_add_members (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_callback_for_add_members callback = (tp_cli_channel_interface_group_callback_for_add_members) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_call_add_members:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contacts: Used to pass an 'in' argument: An array of contact handles to invite to the channel
 * @in_Message: Used to pass an 'in' argument: A string message, which can be blank if desired
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
 * Start a AddMembers method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Invite all the given contacts into the channel, or accept requests for           channel membership for contacts on the pending local list.&lt;/p&gt;          &lt;p&gt;A message may be provided along with the request, which will be sent         to the server if supported. See the CHANNEL_GROUP_FLAG_MESSAGE_ADD and         CHANNEL_GROUP_FLAG_MESSAGE_ACCEPT         &lt;tp:member-ref&gt;GroupFlags&lt;/tp:member-ref&gt; to see in which cases this         message should be provided.&lt;/p&gt;          &lt;p&gt;Attempting to add contacts who are already members is allowed;           connection managers must silently accept this, without error.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_group_call_add_members (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    const gchar *in_Message,
    tp_cli_channel_interface_group_callback_for_add_members callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "AddMembers",
          DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_STRING, in_Message,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "AddMembers", iface,
          _tp_cli_channel_interface_group_invoke_callback_add_members,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "AddMembers",
              _tp_cli_channel_interface_group_collect_callback_add_members,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_STRING, in_Message,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_group_run_state_add_members;
static void
_tp_cli_channel_interface_group_finish_running_add_members (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_group_run_state_add_members *state = user_data;

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
 * tp_cli_channel_interface_group_run_add_members:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contacts: Used to pass an 'in' argument: An array of contact handles to invite to the channel
 * @in_Message: Used to pass an 'in' argument: A string message, which can be blank if desired
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method AddMembers and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Invite all the given contacts into the channel, or accept requests for           channel membership for contacts on the pending local list.&lt;/p&gt;          &lt;p&gt;A message may be provided along with the request, which will be sent         to the server if supported. See the CHANNEL_GROUP_FLAG_MESSAGE_ADD and         CHANNEL_GROUP_FLAG_MESSAGE_ACCEPT         &lt;tp:member-ref&gt;GroupFlags&lt;/tp:member-ref&gt; to see in which cases this         message should be provided.&lt;/p&gt;          &lt;p&gt;Attempting to add contacts who are already members is allowed;           connection managers must silently accept this, without error.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_group_run_add_members (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    const gchar *in_Message,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_group_run_state_add_members state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "AddMembers", iface,
      _tp_cli_channel_interface_group_finish_running_add_members,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "AddMembers",
          _tp_cli_channel_interface_group_collect_callback_add_members,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_STRING, in_Message,
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
 * tp_cli_channel_interface_group_callback_for_get_all_members:
 * @proxy: the proxy on which the call was made
 * @out_Members: Used to return an 'out' argument if @error is %NULL: array of handles of current members
 * @out_Local_Pending: Used to return an 'out' argument if @error is %NULL: array of handles of local pending members
 * @out_Remote_Pending: Used to return an 'out' argument if @error is %NULL: array of handles of remote pending members
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetAllMembers method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_group_collect_callback_get_all_members (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GArray *out_Members;
  GArray *out_Local_Pending;
  GArray *out_Remote_Pending;

  dbus_g_proxy_end_call (proxy, call, &error,
      DBUS_TYPE_G_UINT_ARRAY, &out_Members,
      DBUS_TYPE_G_UINT_ARRAY, &out_Local_Pending,
      DBUS_TYPE_G_UINT_ARRAY, &out_Remote_Pending,
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
  g_value_init (args->values + 0, DBUS_TYPE_G_UINT_ARRAY);
  g_value_take_boxed (args->values + 0, out_Members);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, DBUS_TYPE_G_UINT_ARRAY);
  g_value_take_boxed (args->values + 1, out_Local_Pending);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, DBUS_TYPE_G_UINT_ARRAY);
  g_value_take_boxed (args->values + 2, out_Remote_Pending);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_interface_group_invoke_callback_get_all_members (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_callback_for_get_all_members callback = (tp_cli_channel_interface_group_callback_for_get_all_members) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          NULL,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      g_value_get_boxed (args->values + 1),
      g_value_get_boxed (args->values + 2),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_call_get_all_members:
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
 * Start a GetAllMembers method call.
 *
 * Returns arrays of all current, local and remote pending channel         members.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_group_call_get_all_members (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_group_callback_for_get_all_members callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
            NULL,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetAllMembers",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetAllMembers", iface,
          _tp_cli_channel_interface_group_invoke_callback_get_all_members,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetAllMembers",
              _tp_cli_channel_interface_group_collect_callback_get_all_members,
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
    GArray **out_Members;
    GArray **out_Local_Pending;
    GArray **out_Remote_Pending;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_group_run_state_get_all_members;
static void
_tp_cli_channel_interface_group_finish_running_get_all_members (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_group_run_state_get_all_members *state = user_data;

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

  if (state->out_Members != NULL)
    *state->out_Members = g_value_dup_boxed (args->values + 0);

  if (state->out_Local_Pending != NULL)
    *state->out_Local_Pending = g_value_dup_boxed (args->values + 1);

  if (state->out_Remote_Pending != NULL)
    *state->out_Remote_Pending = g_value_dup_boxed (args->values + 2);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_run_get_all_members:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Members: Used to return an 'out' argument if %TRUE is returned: array of handles of current members
 * @out_Local_Pending: Used to return an 'out' argument if %TRUE is returned: array of handles of local pending members
 * @out_Remote_Pending: Used to return an 'out' argument if %TRUE is returned: array of handles of remote pending members
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetAllMembers and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns arrays of all current, local and remote pending channel         members.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_group_run_get_all_members (TpChannel *proxy,
    gint timeout_ms,
    GArray **out_Members,
    GArray **out_Local_Pending,
    GArray **out_Remote_Pending,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_group_run_state_get_all_members state = {
      NULL /* loop */, error,
    out_Members,
    out_Local_Pending,
    out_Remote_Pending,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetAllMembers", iface,
      _tp_cli_channel_interface_group_finish_running_get_all_members,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetAllMembers",
          _tp_cli_channel_interface_group_collect_callback_get_all_members,
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
 * tp_cli_channel_interface_group_callback_for_get_group_flags:
 * @proxy: the proxy on which the call was made
 * @out_Group_Flags: Used to return an 'out' argument if @error is %NULL: The value of the GroupFlags property
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetGroupFlags method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_group_collect_callback_get_group_flags (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  guint out_Group_Flags;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_UINT, &out_Group_Flags,
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
  g_value_set_uint (args->values + 0, out_Group_Flags);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_interface_group_invoke_callback_get_group_flags (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_callback_for_get_group_flags callback = (tp_cli_channel_interface_group_callback_for_get_group_flags) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          0,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_uint (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_call_get_group_flags:
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
 * Start a GetGroupFlags method call.
 *
 * Returns the value of the &lt;tp:member-ref&gt;GroupFlags&lt;/tp:member-ref&gt; property.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_group_call_get_group_flags (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_group_callback_for_get_group_flags callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetGroupFlags",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetGroupFlags", iface,
          _tp_cli_channel_interface_group_invoke_callback_get_group_flags,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetGroupFlags",
              _tp_cli_channel_interface_group_collect_callback_get_group_flags,
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
    guint *out_Group_Flags;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_group_run_state_get_group_flags;
static void
_tp_cli_channel_interface_group_finish_running_get_group_flags (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_group_run_state_get_group_flags *state = user_data;

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

  if (state->out_Group_Flags != NULL)
    *state->out_Group_Flags = g_value_get_uint (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_run_get_group_flags:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Group_Flags: Used to return an 'out' argument if %TRUE is returned: The value of the GroupFlags property
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetGroupFlags and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns the value of the &lt;tp:member-ref&gt;GroupFlags&lt;/tp:member-ref&gt; property.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_group_run_get_group_flags (TpChannel *proxy,
    gint timeout_ms,
    guint *out_Group_Flags,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_group_run_state_get_group_flags state = {
      NULL /* loop */, error,
    out_Group_Flags,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetGroupFlags", iface,
      _tp_cli_channel_interface_group_finish_running_get_group_flags,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetGroupFlags",
          _tp_cli_channel_interface_group_collect_callback_get_group_flags,
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
 * tp_cli_channel_interface_group_callback_for_get_handle_owners:
 * @proxy: the proxy on which the call was made
 * @out_Owners: Used to return an 'out' argument if @error is %NULL: An array of integer handles representing the owner handles of           the given room members, in the same order, or 0 if the           owner is not available
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetHandleOwners method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_group_collect_callback_get_handle_owners (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GArray *out_Owners;

  dbus_g_proxy_end_call (proxy, call, &error,
      DBUS_TYPE_G_UINT_ARRAY, &out_Owners,
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
  g_value_take_boxed (args->values + 0, out_Owners);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_interface_group_invoke_callback_get_handle_owners (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_callback_for_get_handle_owners callback = (tp_cli_channel_interface_group_callback_for_get_handle_owners) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_call_get_handle_owners:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Handles: Used to pass an 'in' argument: A list of integer handles representing members of the channel
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
 * Start a GetHandleOwners method call.
 *
 * If the CHANNEL_GROUP_FLAG_CHANNEL_SPECIFIC_HANDLES flag is set on         the channel, then the handles of the group members are specific         to this channel, and are not meaningful in a connection-wide         context such as contact lists. This method allows you to find         the owner of the handle if it can be discovered in this channel,         or 0 if the owner is not available.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_group_call_get_handle_owners (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Handles,
    tp_cli_channel_interface_group_callback_for_get_handle_owners callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetHandleOwners",
          DBUS_TYPE_G_UINT_ARRAY, in_Handles,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetHandleOwners", iface,
          _tp_cli_channel_interface_group_invoke_callback_get_handle_owners,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetHandleOwners",
              _tp_cli_channel_interface_group_collect_callback_get_handle_owners,
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
    GArray **out_Owners;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_group_run_state_get_handle_owners;
static void
_tp_cli_channel_interface_group_finish_running_get_handle_owners (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_group_run_state_get_handle_owners *state = user_data;

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

  if (state->out_Owners != NULL)
    *state->out_Owners = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_run_get_handle_owners:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Handles: Used to pass an 'in' argument: A list of integer handles representing members of the channel
 * @out_Owners: Used to return an 'out' argument if %TRUE is returned: An array of integer handles representing the owner handles of           the given room members, in the same order, or 0 if the           owner is not available
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetHandleOwners and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * If the CHANNEL_GROUP_FLAG_CHANNEL_SPECIFIC_HANDLES flag is set on         the channel, then the handles of the group members are specific         to this channel, and are not meaningful in a connection-wide         context such as contact lists. This method allows you to find         the owner of the handle if it can be discovered in this channel,         or 0 if the owner is not available.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_group_run_get_handle_owners (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Handles,
    GArray **out_Owners,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_group_run_state_get_handle_owners state = {
      NULL /* loop */, error,
    out_Owners,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetHandleOwners", iface,
      _tp_cli_channel_interface_group_finish_running_get_handle_owners,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetHandleOwners",
          _tp_cli_channel_interface_group_collect_callback_get_handle_owners,
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


/**
 * tp_cli_channel_interface_group_callback_for_get_local_pending_members:
 * @proxy: the proxy on which the call was made
 * @out_Handles: Used to return an 'out' argument if @error is %NULL: (Undocumented)
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetLocalPendingMembers method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_group_collect_callback_get_local_pending_members (DBusGProxy *proxy,
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
_tp_cli_channel_interface_group_invoke_callback_get_local_pending_members (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_callback_for_get_local_pending_members callback = (tp_cli_channel_interface_group_callback_for_get_local_pending_members) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_call_get_local_pending_members:
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
 * Start a GetLocalPendingMembers method call.
 *
 * Returns the To_Be_Added handle (only) for each structure in the         &lt;tp:member-ref&gt;LocalPendingMembers&lt;/tp:member-ref&gt; property.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_group_call_get_local_pending_members (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_group_callback_for_get_local_pending_members callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetLocalPendingMembers",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetLocalPendingMembers", iface,
          _tp_cli_channel_interface_group_invoke_callback_get_local_pending_members,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetLocalPendingMembers",
              _tp_cli_channel_interface_group_collect_callback_get_local_pending_members,
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
    GArray **out_Handles;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_group_run_state_get_local_pending_members;
static void
_tp_cli_channel_interface_group_finish_running_get_local_pending_members (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_group_run_state_get_local_pending_members *state = user_data;

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
 * tp_cli_channel_interface_group_run_get_local_pending_members:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Handles: Used to return an 'out' argument if %TRUE is returned: (Undocumented)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetLocalPendingMembers and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns the To_Be_Added handle (only) for each structure in the         &lt;tp:member-ref&gt;LocalPendingMembers&lt;/tp:member-ref&gt; property.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_group_run_get_local_pending_members (TpChannel *proxy,
    gint timeout_ms,
    GArray **out_Handles,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_group_run_state_get_local_pending_members state = {
      NULL /* loop */, error,
    out_Handles,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetLocalPendingMembers", iface,
      _tp_cli_channel_interface_group_finish_running_get_local_pending_members,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetLocalPendingMembers",
          _tp_cli_channel_interface_group_collect_callback_get_local_pending_members,
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
 * tp_cli_channel_interface_group_callback_for_get_local_pending_members_with_info:
 * @proxy: the proxy on which the call was made
 * @out_Info: Used to return an 'out' argument if @error is %NULL: An array of structs containing:           &lt;ul&gt;             &lt;li&gt;               A handle representing the contact requesting channel membership             &lt;/li&gt;             &lt;li&gt;               A handle representing the contact making the request, or 0 if               unknown             &lt;/li&gt;             &lt;li&gt;               The reason for the request: one of the values of               &lt;tp:type&gt;Channel_Group_Change_Reason&lt;/tp:type&gt;             &lt;/li&gt;             &lt;li&gt;               A string message containing the reason for the request if any (or               blank if none)             &lt;/li&gt;           &lt;/ul&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetLocalPendingMembersWithInfo method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_group_collect_callback_get_local_pending_members_with_info (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GPtrArray *out_Info;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID)))), &out_Info,
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
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Info);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_interface_group_invoke_callback_get_local_pending_members_with_info (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_callback_for_get_local_pending_members_with_info callback = (tp_cli_channel_interface_group_callback_for_get_local_pending_members_with_info) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_call_get_local_pending_members_with_info:
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
 * Start a GetLocalPendingMembersWithInfo method call.
 *
 * Returns the &lt;tp:member-ref&gt;LocalPendingMembers&lt;/tp:member-ref&gt; property.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_group_call_get_local_pending_members_with_info (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_group_callback_for_get_local_pending_members_with_info callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetLocalPendingMembersWithInfo",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetLocalPendingMembersWithInfo", iface,
          _tp_cli_channel_interface_group_invoke_callback_get_local_pending_members_with_info,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetLocalPendingMembersWithInfo",
              _tp_cli_channel_interface_group_collect_callback_get_local_pending_members_with_info,
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
    GPtrArray **out_Info;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_group_run_state_get_local_pending_members_with_info;
static void
_tp_cli_channel_interface_group_finish_running_get_local_pending_members_with_info (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_group_run_state_get_local_pending_members_with_info *state = user_data;

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

  if (state->out_Info != NULL)
    *state->out_Info = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_run_get_local_pending_members_with_info:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Info: Used to return an 'out' argument if %TRUE is returned: An array of structs containing:           &lt;ul&gt;             &lt;li&gt;               A handle representing the contact requesting channel membership             &lt;/li&gt;             &lt;li&gt;               A handle representing the contact making the request, or 0 if               unknown             &lt;/li&gt;             &lt;li&gt;               The reason for the request: one of the values of               &lt;tp:type&gt;Channel_Group_Change_Reason&lt;/tp:type&gt;             &lt;/li&gt;             &lt;li&gt;               A string message containing the reason for the request if any (or               blank if none)             &lt;/li&gt;           &lt;/ul&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetLocalPendingMembersWithInfo and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns the &lt;tp:member-ref&gt;LocalPendingMembers&lt;/tp:member-ref&gt; property.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_group_run_get_local_pending_members_with_info (TpChannel *proxy,
    gint timeout_ms,
    GPtrArray **out_Info,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_group_run_state_get_local_pending_members_with_info state = {
      NULL /* loop */, error,
    out_Info,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetLocalPendingMembersWithInfo", iface,
      _tp_cli_channel_interface_group_finish_running_get_local_pending_members_with_info,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetLocalPendingMembersWithInfo",
          _tp_cli_channel_interface_group_collect_callback_get_local_pending_members_with_info,
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
 * tp_cli_channel_interface_group_callback_for_get_members:
 * @proxy: the proxy on which the call was made
 * @out_Handles: Used to return an 'out' argument if @error is %NULL: (Undocumented)
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetMembers method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_group_collect_callback_get_members (DBusGProxy *proxy,
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
_tp_cli_channel_interface_group_invoke_callback_get_members (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_callback_for_get_members callback = (tp_cli_channel_interface_group_callback_for_get_members) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_call_get_members:
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
 * Start a GetMembers method call.
 *
 * Returns the &lt;tp:member-ref&gt;Members&lt;/tp:member-ref&gt; property.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_group_call_get_members (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_group_callback_for_get_members callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetMembers",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetMembers", iface,
          _tp_cli_channel_interface_group_invoke_callback_get_members,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetMembers",
              _tp_cli_channel_interface_group_collect_callback_get_members,
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
    GArray **out_Handles;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_group_run_state_get_members;
static void
_tp_cli_channel_interface_group_finish_running_get_members (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_group_run_state_get_members *state = user_data;

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
 * tp_cli_channel_interface_group_run_get_members:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Handles: Used to return an 'out' argument if %TRUE is returned: (Undocumented)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetMembers and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns the &lt;tp:member-ref&gt;Members&lt;/tp:member-ref&gt; property.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_group_run_get_members (TpChannel *proxy,
    gint timeout_ms,
    GArray **out_Handles,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_group_run_state_get_members state = {
      NULL /* loop */, error,
    out_Handles,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetMembers", iface,
      _tp_cli_channel_interface_group_finish_running_get_members,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetMembers",
          _tp_cli_channel_interface_group_collect_callback_get_members,
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
 * tp_cli_channel_interface_group_callback_for_get_remote_pending_members:
 * @proxy: the proxy on which the call was made
 * @out_Handles: Used to return an 'out' argument if @error is %NULL: (Undocumented)
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetRemotePendingMembers method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_group_collect_callback_get_remote_pending_members (DBusGProxy *proxy,
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
_tp_cli_channel_interface_group_invoke_callback_get_remote_pending_members (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_callback_for_get_remote_pending_members callback = (tp_cli_channel_interface_group_callback_for_get_remote_pending_members) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_call_get_remote_pending_members:
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
 * Start a GetRemotePendingMembers method call.
 *
 * Returns an array of handles representing contacts who have been         invited to the channel and are awaiting remote approval.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_group_call_get_remote_pending_members (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_group_callback_for_get_remote_pending_members callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetRemotePendingMembers",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetRemotePendingMembers", iface,
          _tp_cli_channel_interface_group_invoke_callback_get_remote_pending_members,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetRemotePendingMembers",
              _tp_cli_channel_interface_group_collect_callback_get_remote_pending_members,
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
    GArray **out_Handles;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_group_run_state_get_remote_pending_members;
static void
_tp_cli_channel_interface_group_finish_running_get_remote_pending_members (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_group_run_state_get_remote_pending_members *state = user_data;

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
 * tp_cli_channel_interface_group_run_get_remote_pending_members:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Handles: Used to return an 'out' argument if %TRUE is returned: (Undocumented)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetRemotePendingMembers and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns an array of handles representing contacts who have been         invited to the channel and are awaiting remote approval.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_group_run_get_remote_pending_members (TpChannel *proxy,
    gint timeout_ms,
    GArray **out_Handles,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_group_run_state_get_remote_pending_members state = {
      NULL /* loop */, error,
    out_Handles,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetRemotePendingMembers", iface,
      _tp_cli_channel_interface_group_finish_running_get_remote_pending_members,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetRemotePendingMembers",
          _tp_cli_channel_interface_group_collect_callback_get_remote_pending_members,
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
 * tp_cli_channel_interface_group_callback_for_get_self_handle:
 * @proxy: the proxy on which the call was made
 * @out_Self_Handle: Used to return an 'out' argument if @error is %NULL: (Undocumented)
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetSelfHandle method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_group_collect_callback_get_self_handle (DBusGProxy *proxy,
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
_tp_cli_channel_interface_group_invoke_callback_get_self_handle (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_callback_for_get_self_handle callback = (tp_cli_channel_interface_group_callback_for_get_self_handle) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          0,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_uint (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_call_get_self_handle:
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
 * Returns the value of the &lt;tp:member-ref&gt;SelfHandle&lt;/tp:member-ref&gt;         property.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_group_call_get_self_handle (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_group_callback_for_get_self_handle callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
          _tp_cli_channel_interface_group_invoke_callback_get_self_handle,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetSelfHandle",
              _tp_cli_channel_interface_group_collect_callback_get_self_handle,
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
} _tp_cli_channel_interface_group_run_state_get_self_handle;
static void
_tp_cli_channel_interface_group_finish_running_get_self_handle (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_group_run_state_get_self_handle *state = user_data;

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
 * tp_cli_channel_interface_group_run_get_self_handle:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Self_Handle: Used to return an 'out' argument if %TRUE is returned: (Undocumented)
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
 * Returns the value of the &lt;tp:member-ref&gt;SelfHandle&lt;/tp:member-ref&gt;         property.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_group_run_get_self_handle (TpChannel *proxy,
    gint timeout_ms,
    guint *out_Self_Handle,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_group_run_state_get_self_handle state = {
      NULL /* loop */, error,
    out_Self_Handle,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetSelfHandle", iface,
      _tp_cli_channel_interface_group_finish_running_get_self_handle,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetSelfHandle",
          _tp_cli_channel_interface_group_collect_callback_get_self_handle,
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
 * tp_cli_channel_interface_group_callback_for_remove_members:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RemoveMembers method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_group_collect_callback_remove_members (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_interface_group_invoke_callback_remove_members (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_callback_for_remove_members callback = (tp_cli_channel_interface_group_callback_for_remove_members) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_call_remove_members:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contacts: Used to pass an 'in' argument: An array of contact handles to remove from the channel
 * @in_Message: Used to pass an 'in' argument: A string message, which can be blank if desired
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
 * Start a RemoveMembers method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Requests the removal of contacts from a channel, reject their           request for channel membership on the pending local list, or           rescind their invitation on the pending remote list.&lt;/p&gt;          &lt;p&gt;If the &lt;tp:member-ref&gt;SelfHandle&lt;/tp:member-ref&gt; is in a Group,           it can be removed via this method, in order to leave the group           gracefully. This is the recommended way to leave a chatroom, close           or reject a &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Type&quot;&gt;StreamedMedia&lt;/tp:dbus-ref&gt;           call, and so on.&lt;/p&gt;          &lt;p&gt;Accordingly, connection managers SHOULD support           doing this, regardless of the value of           &lt;tp:member-ref&gt;GroupFlags&lt;/tp:member-ref&gt;.           If doing so fails with PermissionDenied, this is considered to a bug           in the connection manager, but clients MUST recover by falling back           to closing the channel with the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel&quot;&gt;Close&lt;/tp:dbus-ref&gt;           method.&lt;/p&gt;          &lt;p&gt;Removing any contact from the local pending list is always           allowed. Removing contacts other than the           &lt;tp:member-ref&gt;SelfHandle&lt;/tp:member-ref&gt; from the channel&apos;s members           is allowed if and only if Channel_Group_Flag_Can_Remove is in the           &lt;tp:member-ref&gt;GroupFlags&lt;/tp:member-ref&gt;,           while removing contacts other than the           &lt;tp:member-ref&gt;SelfHandle&lt;/tp:member-ref&gt; from the remote pending list           is allowed if and only if Channel_Group_Flag_Can_Rescind is in the           &lt;tp:member-ref&gt;GroupFlags&lt;/tp:member-ref&gt;.&lt;/p&gt;          &lt;p&gt;A message may be provided along with the request, which will be           sent to the server if supported. See the           Channel_Group_Flag_Message_Remove,           Channel_Group_Flag_Message_Depart,           Channel_Group_Flag_Message_Reject and           Channel_Group_Flag_Message_Rescind           &lt;tp:member-ref&gt;GroupFlags&lt;/tp:member-ref&gt; to see in which cases this           message should be provided.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_group_call_remove_members (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    const gchar *in_Message,
    tp_cli_channel_interface_group_callback_for_remove_members callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "RemoveMembers",
          DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_STRING, in_Message,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RemoveMembers", iface,
          _tp_cli_channel_interface_group_invoke_callback_remove_members,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RemoveMembers",
              _tp_cli_channel_interface_group_collect_callback_remove_members,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_STRING, in_Message,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_group_run_state_remove_members;
static void
_tp_cli_channel_interface_group_finish_running_remove_members (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_group_run_state_remove_members *state = user_data;

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
 * tp_cli_channel_interface_group_run_remove_members:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contacts: Used to pass an 'in' argument: An array of contact handles to remove from the channel
 * @in_Message: Used to pass an 'in' argument: A string message, which can be blank if desired
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RemoveMembers and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Requests the removal of contacts from a channel, reject their           request for channel membership on the pending local list, or           rescind their invitation on the pending remote list.&lt;/p&gt;          &lt;p&gt;If the &lt;tp:member-ref&gt;SelfHandle&lt;/tp:member-ref&gt; is in a Group,           it can be removed via this method, in order to leave the group           gracefully. This is the recommended way to leave a chatroom, close           or reject a &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Type&quot;&gt;StreamedMedia&lt;/tp:dbus-ref&gt;           call, and so on.&lt;/p&gt;          &lt;p&gt;Accordingly, connection managers SHOULD support           doing this, regardless of the value of           &lt;tp:member-ref&gt;GroupFlags&lt;/tp:member-ref&gt;.           If doing so fails with PermissionDenied, this is considered to a bug           in the connection manager, but clients MUST recover by falling back           to closing the channel with the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel&quot;&gt;Close&lt;/tp:dbus-ref&gt;           method.&lt;/p&gt;          &lt;p&gt;Removing any contact from the local pending list is always           allowed. Removing contacts other than the           &lt;tp:member-ref&gt;SelfHandle&lt;/tp:member-ref&gt; from the channel&apos;s members           is allowed if and only if Channel_Group_Flag_Can_Remove is in the           &lt;tp:member-ref&gt;GroupFlags&lt;/tp:member-ref&gt;,           while removing contacts other than the           &lt;tp:member-ref&gt;SelfHandle&lt;/tp:member-ref&gt; from the remote pending list           is allowed if and only if Channel_Group_Flag_Can_Rescind is in the           &lt;tp:member-ref&gt;GroupFlags&lt;/tp:member-ref&gt;.&lt;/p&gt;          &lt;p&gt;A message may be provided along with the request, which will be           sent to the server if supported. See the           Channel_Group_Flag_Message_Remove,           Channel_Group_Flag_Message_Depart,           Channel_Group_Flag_Message_Reject and           Channel_Group_Flag_Message_Rescind           &lt;tp:member-ref&gt;GroupFlags&lt;/tp:member-ref&gt; to see in which cases this           message should be provided.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_group_run_remove_members (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    const gchar *in_Message,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_group_run_state_remove_members state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RemoveMembers", iface,
      _tp_cli_channel_interface_group_finish_running_remove_members,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RemoveMembers",
          _tp_cli_channel_interface_group_collect_callback_remove_members,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_STRING, in_Message,
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
 * tp_cli_channel_interface_group_callback_for_remove_members_with_reason:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RemoveMembersWithReason method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_group_collect_callback_remove_members_with_reason (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_interface_group_invoke_callback_remove_members_with_reason (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_group_callback_for_remove_members_with_reason callback = (tp_cli_channel_interface_group_callback_for_remove_members_with_reason) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_group_call_remove_members_with_reason:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contacts: Used to pass an 'in' argument: An array of contact handles to remove from the channel
 * @in_Message: Used to pass an 'in' argument: A string message, which can be blank if desired
 * @in_Reason: Used to pass an 'in' argument: A reason for the change
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
 * Start a RemoveMembersWithReason method call.
 *
 * As &lt;tp:member-ref&gt;RemoveMembers&lt;/tp:member-ref&gt;, but a reason code may         be provided where         appropriate. The reason code may be ignored if the underlying         protocol is unable to represent the given reason.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_group_call_remove_members_with_reason (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    const gchar *in_Message,
    guint in_Reason,
    tp_cli_channel_interface_group_callback_for_remove_members_with_reason callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "RemoveMembersWithReason",
          DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
          G_TYPE_STRING, in_Message,
          G_TYPE_UINT, in_Reason,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RemoveMembersWithReason", iface,
          _tp_cli_channel_interface_group_invoke_callback_remove_members_with_reason,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RemoveMembersWithReason",
              _tp_cli_channel_interface_group_collect_callback_remove_members_with_reason,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_STRING, in_Message,
              G_TYPE_UINT, in_Reason,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_group_run_state_remove_members_with_reason;
static void
_tp_cli_channel_interface_group_finish_running_remove_members_with_reason (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_group_run_state_remove_members_with_reason *state = user_data;

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
 * tp_cli_channel_interface_group_run_remove_members_with_reason:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contacts: Used to pass an 'in' argument: An array of contact handles to remove from the channel
 * @in_Message: Used to pass an 'in' argument: A string message, which can be blank if desired
 * @in_Reason: Used to pass an 'in' argument: A reason for the change
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RemoveMembersWithReason and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * As &lt;tp:member-ref&gt;RemoveMembers&lt;/tp:member-ref&gt;, but a reason code may         be provided where         appropriate. The reason code may be ignored if the underlying         protocol is unable to represent the given reason.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_group_run_remove_members_with_reason (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Contacts,
    const gchar *in_Message,
    guint in_Reason,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_group_run_state_remove_members_with_reason state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RemoveMembersWithReason", iface,
      _tp_cli_channel_interface_group_finish_running_remove_members_with_reason,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RemoveMembersWithReason",
          _tp_cli_channel_interface_group_collect_callback_remove_members_with_reason,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Contacts,
              G_TYPE_STRING, in_Message,
              G_TYPE_UINT, in_Reason,
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
tp_cli_add_signals_for_channel_interface_hold (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "HoldStateChanged",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_interface_hold_signal_callback_hold_state_changed:
 * @proxy: The proxy on which tp_cli_channel_interface_hold_connect_to_hold_state_changed ()
 *  was called
 * @arg_HoldState: The state of the channel
 * @arg_Reason: The reason for the state change
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal HoldStateChanged.
 */
static void
_tp_cli_channel_interface_hold_collect_args_of_hold_state_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_HoldState,
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
  g_value_set_uint (args->values + 0, arg_HoldState);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Reason);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_interface_hold_invoke_callback_for_hold_state_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_hold_signal_callback_hold_state_changed callback =
      (tp_cli_channel_interface_hold_signal_callback_hold_state_changed) generic_callback;

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
 * tp_cli_channel_interface_hold_connect_to_hold_state_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal HoldStateChanged.
 *
 * Emitted to indicate that the hold state has changed for this channel.         This may occur as a consequence of you requesting a change with         &lt;tp:member-ref&gt;RequestHold&lt;/tp:member-ref&gt;, or the state changing as a         result of a request from         another process.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_interface_hold_connect_to_hold_state_changed (TpChannel *proxy,
    tp_cli_channel_interface_hold_signal_callback_hold_state_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_INTERFACE_HOLD, "HoldStateChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_interface_hold_collect_args_of_hold_state_changed),
      _tp_cli_channel_interface_hold_invoke_callback_for_hold_state_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_interface_hold_callback_for_get_hold_state:
 * @proxy: the proxy on which the call was made
 * @out_HoldState: Used to return an 'out' argument if @error is %NULL: The state of the channel
 * @out_Reason: Used to return an 'out' argument if @error is %NULL: The reason why the channel is in that state
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetHoldState method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_hold_collect_callback_get_hold_state (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  guint out_HoldState;
  guint out_Reason;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_UINT, &out_HoldState,
      G_TYPE_UINT, &out_Reason,
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
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, out_HoldState);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, out_Reason);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_interface_hold_invoke_callback_get_hold_state (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_hold_callback_for_get_hold_state callback = (tp_cli_channel_interface_hold_callback_for_get_hold_state) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          0,
          0,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_uint (args->values + 0),
      g_value_get_uint (args->values + 1),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_hold_call_get_hold_state:
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
 * Start a GetHoldState method call.
 *
 * Return whether the local user has placed the channel on hold.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_hold_call_get_hold_state (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_hold_callback_for_get_hold_state callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_HOLD;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
            0,
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetHoldState",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetHoldState", iface,
          _tp_cli_channel_interface_hold_invoke_callback_get_hold_state,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetHoldState",
              _tp_cli_channel_interface_hold_collect_callback_get_hold_state,
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
    guint *out_HoldState;
    guint *out_Reason;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_hold_run_state_get_hold_state;
static void
_tp_cli_channel_interface_hold_finish_running_get_hold_state (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_hold_run_state_get_hold_state *state = user_data;

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

  if (state->out_HoldState != NULL)
    *state->out_HoldState = g_value_get_uint (args->values + 0);

  if (state->out_Reason != NULL)
    *state->out_Reason = g_value_get_uint (args->values + 1);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_hold_run_get_hold_state:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_HoldState: Used to return an 'out' argument if %TRUE is returned: The state of the channel
 * @out_Reason: Used to return an 'out' argument if %TRUE is returned: The reason why the channel is in that state
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetHoldState and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Return whether the local user has placed the channel on hold.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_hold_run_get_hold_state (TpChannel *proxy,
    gint timeout_ms,
    guint *out_HoldState,
    guint *out_Reason,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_HOLD;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_hold_run_state_get_hold_state state = {
      NULL /* loop */, error,
    out_HoldState,
    out_Reason,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetHoldState", iface,
      _tp_cli_channel_interface_hold_finish_running_get_hold_state,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetHoldState",
          _tp_cli_channel_interface_hold_collect_callback_get_hold_state,
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
 * tp_cli_channel_interface_hold_callback_for_request_hold:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RequestHold method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_hold_collect_callback_request_hold (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_interface_hold_invoke_callback_request_hold (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_hold_callback_for_request_hold callback = (tp_cli_channel_interface_hold_callback_for_request_hold) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_hold_call_request_hold:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Hold: Used to pass an 'in' argument: A boolean indicating whether or not the channel should be on hold
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
 * Start a RequestHold method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that the channel be put on hold (be instructed not to send           any media streams to you) or be taken off hold.&lt;/p&gt;          &lt;p&gt;If the connection manager can immediately tell that the requested           state change could not possibly succeed, this method SHOULD           return the NotAvailable error. If the requested state is the           same as the current state, this method SHOULD return successfully           without doing anything.&lt;/p&gt;          &lt;p&gt;Otherwise, this method SHOULD immediately set the hold state to           Local_Hold_State_Pending_Hold or Local_Hold_State_Pending_Unhold           (as appropriate), emitting           &lt;tp:member-ref&gt;HoldStateChanged&lt;/tp:member-ref&gt; if this is a change,           and return successfully.&lt;/p&gt;          &lt;p&gt;The eventual success or failure of the request is indicated by a           subsequent HoldStateChanged signal, changing the hold state to           Local_Hold_State_Held or Local_Hold_State_Unheld.&lt;/p&gt;          &lt;p&gt;If the channel has multiple streams, and the connection manager           succeeds in changing the hold state of one stream but fails to           change the hold state of another, it SHOULD attempt to revert           all streams to their previous hold states.&lt;/p&gt;          &lt;p&gt;The following state transitions SHOULD be used, where           appropriate:&lt;/p&gt;          &lt;ul&gt;           &lt;li&gt;Successful hold:             (Unheld, any reason) → (Pending_Hold, Requested) →             (Held, Requested)           &lt;/li&gt;           &lt;li&gt;Successful unhold:             (Held, any reason) → (Pending_Unhold, Requested) →             (Unheld, Requested)           &lt;/li&gt;           &lt;li&gt;Attempting to unhold fails at the first attempt to acquire a             resource:             (Held, any reason) → (Pending_Unhold, Requested) →             (Held, Resource_Not_Available)           &lt;/li&gt;           &lt;li&gt;Attempting to unhold acquires one resource, but fails to acquire             a second, and takes time to release the first:             (Held, any reason) → (Pending_Unhold, Requested) →             (Pending_Hold, Resource_Not_Available) →             (Held, Resource_Not_Available)           &lt;/li&gt;         &lt;/ul&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_hold_call_request_hold (TpChannel *proxy,
    gint timeout_ms,
    gboolean in_Hold,
    tp_cli_channel_interface_hold_callback_for_request_hold callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_HOLD;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "RequestHold",
          G_TYPE_BOOLEAN, in_Hold,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RequestHold", iface,
          _tp_cli_channel_interface_hold_invoke_callback_request_hold,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RequestHold",
              _tp_cli_channel_interface_hold_collect_callback_request_hold,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_BOOLEAN, in_Hold,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_hold_run_state_request_hold;
static void
_tp_cli_channel_interface_hold_finish_running_request_hold (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_hold_run_state_request_hold *state = user_data;

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
 * tp_cli_channel_interface_hold_run_request_hold:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Hold: Used to pass an 'in' argument: A boolean indicating whether or not the channel should be on hold
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RequestHold and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that the channel be put on hold (be instructed not to send           any media streams to you) or be taken off hold.&lt;/p&gt;          &lt;p&gt;If the connection manager can immediately tell that the requested           state change could not possibly succeed, this method SHOULD           return the NotAvailable error. If the requested state is the           same as the current state, this method SHOULD return successfully           without doing anything.&lt;/p&gt;          &lt;p&gt;Otherwise, this method SHOULD immediately set the hold state to           Local_Hold_State_Pending_Hold or Local_Hold_State_Pending_Unhold           (as appropriate), emitting           &lt;tp:member-ref&gt;HoldStateChanged&lt;/tp:member-ref&gt; if this is a change,           and return successfully.&lt;/p&gt;          &lt;p&gt;The eventual success or failure of the request is indicated by a           subsequent HoldStateChanged signal, changing the hold state to           Local_Hold_State_Held or Local_Hold_State_Unheld.&lt;/p&gt;          &lt;p&gt;If the channel has multiple streams, and the connection manager           succeeds in changing the hold state of one stream but fails to           change the hold state of another, it SHOULD attempt to revert           all streams to their previous hold states.&lt;/p&gt;          &lt;p&gt;The following state transitions SHOULD be used, where           appropriate:&lt;/p&gt;          &lt;ul&gt;           &lt;li&gt;Successful hold:             (Unheld, any reason) → (Pending_Hold, Requested) →             (Held, Requested)           &lt;/li&gt;           &lt;li&gt;Successful unhold:             (Held, any reason) → (Pending_Unhold, Requested) →             (Unheld, Requested)           &lt;/li&gt;           &lt;li&gt;Attempting to unhold fails at the first attempt to acquire a             resource:             (Held, any reason) → (Pending_Unhold, Requested) →             (Held, Resource_Not_Available)           &lt;/li&gt;           &lt;li&gt;Attempting to unhold acquires one resource, but fails to acquire             a second, and takes time to release the first:             (Held, any reason) → (Pending_Unhold, Requested) →             (Pending_Hold, Resource_Not_Available) →             (Held, Resource_Not_Available)           &lt;/li&gt;         &lt;/ul&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_hold_run_request_hold (TpChannel *proxy,
    gint timeout_ms,
    gboolean in_Hold,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_HOLD;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_hold_run_state_request_hold state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RequestHold", iface,
      _tp_cli_channel_interface_hold_finish_running_request_hold,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RequestHold",
          _tp_cli_channel_interface_hold_collect_callback_request_hold,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
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
tp_cli_add_signals_for_channel_interface_media_signalling (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "NewSessionHandler",
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_STRING,
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_interface_media_signalling_signal_callback_new_session_handler:
 * @proxy: The proxy on which tp_cli_channel_interface_media_signalling_connect_to_new_session_handler ()
 *  was called
 * @arg_Session_Handler: Object path of the new &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Media.SessionHandler&lt;/tp:dbus-ref&gt;           object
 * @arg_Session_Type: String indicating type of session, eg &amp;quot;rtp&amp;quot;
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal NewSessionHandler.
 */
static void
_tp_cli_channel_interface_media_signalling_collect_args_of_new_session_handler (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Session_Handler,
    const gchar *arg_Session_Type,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (2);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 2; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, DBUS_TYPE_G_OBJECT_PATH);
  g_value_set_boxed (args->values + 0, arg_Session_Handler);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_STRING);
  g_value_set_string (args->values + 1, arg_Session_Type);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_interface_media_signalling_invoke_callback_for_new_session_handler (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_media_signalling_signal_callback_new_session_handler callback =
      (tp_cli_channel_interface_media_signalling_signal_callback_new_session_handler) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      g_value_get_string (args->values + 1),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_interface_media_signalling_connect_to_new_session_handler:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal NewSessionHandler.
 *
 * Signal that a session handler object has been created. The client         should create a session object and create streams for the streams         within.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_interface_media_signalling_connect_to_new_session_handler (TpChannel *proxy,
    tp_cli_channel_interface_media_signalling_signal_callback_new_session_handler callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_STRING,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_INTERFACE_MEDIA_SIGNALLING, "NewSessionHandler",
      expected_types,
      G_CALLBACK (_tp_cli_channel_interface_media_signalling_collect_args_of_new_session_handler),
      _tp_cli_channel_interface_media_signalling_invoke_callback_for_new_session_handler,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_interface_media_signalling_callback_for_get_session_handlers:
 * @proxy: the proxy on which the call was made
 * @out_Session_Handlers: Used to return an 'out' argument if @error is %NULL: (Undocumented)
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetSessionHandlers method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_media_signalling_collect_callback_get_session_handlers (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GPtrArray *out_Session_Handlers;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, G_TYPE_STRING, G_TYPE_INVALID)))), &out_Session_Handlers,
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
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, G_TYPE_STRING, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Session_Handlers);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_interface_media_signalling_invoke_callback_get_session_handlers (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_media_signalling_callback_for_get_session_handlers callback = (tp_cli_channel_interface_media_signalling_callback_for_get_session_handlers) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_media_signalling_call_get_session_handlers:
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
 * Start a GetSessionHandlers method call.
 *
 * Returns all currently active session handlers on this channel         as a list of (session_handler_path, type).
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_media_signalling_call_get_session_handlers (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_media_signalling_callback_for_get_session_handlers callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_MEDIA_SIGNALLING;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetSessionHandlers",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetSessionHandlers", iface,
          _tp_cli_channel_interface_media_signalling_invoke_callback_get_session_handlers,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetSessionHandlers",
              _tp_cli_channel_interface_media_signalling_collect_callback_get_session_handlers,
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
    GPtrArray **out_Session_Handlers;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_media_signalling_run_state_get_session_handlers;
static void
_tp_cli_channel_interface_media_signalling_finish_running_get_session_handlers (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_media_signalling_run_state_get_session_handlers *state = user_data;

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

  if (state->out_Session_Handlers != NULL)
    *state->out_Session_Handlers = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_media_signalling_run_get_session_handlers:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Session_Handlers: Used to return an 'out' argument if %TRUE is returned: (Undocumented)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetSessionHandlers and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns all currently active session handlers on this channel         as a list of (session_handler_path, type).
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_media_signalling_run_get_session_handlers (TpChannel *proxy,
    gint timeout_ms,
    GPtrArray **out_Session_Handlers,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_MEDIA_SIGNALLING;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_media_signalling_run_state_get_session_handlers state = {
      NULL /* loop */, error,
    out_Session_Handlers,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetSessionHandlers", iface,
      _tp_cli_channel_interface_media_signalling_finish_running_get_session_handlers,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetSessionHandlers",
          _tp_cli_channel_interface_media_signalling_collect_callback_get_session_handlers,
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
tp_cli_add_signals_for_channel_interface_messages (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "MessageSent",
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))),
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "PendingMessagesRemoved",
      DBUS_TYPE_G_UINT_ARRAY,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "MessageReceived",
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))),
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_interface_messages_signal_callback_message_sent:
 * @proxy: The proxy on which tp_cli_channel_interface_messages_connect_to_message_sent ()
 *  was called
 * @arg_Content: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The message content (see &lt;tp:type&gt;Message_Part&lt;/tp:type&gt; for full             details). If the message that was passed to SendMessage has a             formatted text part that the connection manager recognises, but no             text/plain alternative, the CM MUST use the formatted text part to             generate a text/plain alternative which is also included in this             signal argument.&lt;/p&gt;            &lt;p&gt;If the connection manager can predict that the message will be             altered during transmission, this argument SHOULD reflect what             other contacts will receive, rather than being a copy of the             argument to SendMessage (if the message is truncated,             formatting or alternatives are dropped, etc., then the edited             version SHOULD appear in this signal).&lt;/p&gt;
 * @arg_Flags: &lt;p&gt;Flags affecting how the message was sent.  The flags might be a             subset of those passed to SendMessage if the caller requested             unsupported flags.&lt;/p&gt;
 * @arg_Message_Token: An opaque token used to match any incoming delivery or failure           reports against this message, or an empty string if the message           is not readily identifiable.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal MessageSent.
 */
static void
_tp_cli_channel_interface_messages_collect_args_of_message_sent (DBusGProxy *proxy G_GNUC_UNUSED,
    const GPtrArray *arg_Content,
    guint arg_Flags,
    const gchar *arg_Message_Token,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (3);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 3; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))));
  g_value_set_boxed (args->values + 0, arg_Content);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Flags);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, G_TYPE_STRING);
  g_value_set_string (args->values + 2, arg_Message_Token);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_interface_messages_invoke_callback_for_message_sent (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_messages_signal_callback_message_sent callback =
      (tp_cli_channel_interface_messages_signal_callback_message_sent) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      g_value_get_uint (args->values + 1),
      g_value_get_string (args->values + 2),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_interface_messages_connect_to_message_sent:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal MessageSent.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Signals that a message has been submitted for sending. This           MUST be emitted exactly once per emission of the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Type.Text&quot;&gt;Sent&lt;/tp:dbus-ref&gt;           signal on the           Text interface.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;This signal allows a process that is not the caller of             SendMessage to log sent messages. The double signal-emission             provides compatibility with older clients. Clients supporting             Messages should listen for Messages.MessageSent only (if the             channel has the Messages interface) or Text.Sent only             (otherwise).&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_interface_messages_connect_to_message_sent (TpChannel *proxy,
    tp_cli_channel_interface_messages_signal_callback_message_sent callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[4] = {
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))),
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_INTERFACE_MESSAGES, "MessageSent",
      expected_types,
      G_CALLBACK (_tp_cli_channel_interface_messages_collect_args_of_message_sent),
      _tp_cli_channel_interface_messages_invoke_callback_for_message_sent,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_interface_messages_signal_callback_pending_messages_removed:
 * @proxy: The proxy on which tp_cli_channel_interface_messages_connect_to_pending_messages_removed ()
 *  was called
 * @arg_Message_IDs: The messages that have been removed from the pending message list.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal PendingMessagesRemoved.
 */
static void
_tp_cli_channel_interface_messages_collect_args_of_pending_messages_removed (DBusGProxy *proxy G_GNUC_UNUSED,
    const GArray *arg_Message_IDs,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, DBUS_TYPE_G_UINT_ARRAY);
  g_value_set_boxed (args->values + 0, arg_Message_IDs);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_interface_messages_invoke_callback_for_pending_messages_removed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_messages_signal_callback_pending_messages_removed callback =
      (tp_cli_channel_interface_messages_signal_callback_pending_messages_removed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_interface_messages_connect_to_pending_messages_removed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal PendingMessagesRemoved.
 *
 * The messages with the given IDs have been removed from the         &lt;tp:member-ref&gt;PendingMessages&lt;/tp:member-ref&gt; list. Clients SHOULD NOT         attempt to acknowledge those messages.          &lt;tp:rationale&gt;           This completes change notification for the PendingMessages property           (previously, there was change notification when pending messages           were added, but not when they were removed).         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_interface_messages_connect_to_pending_messages_removed (TpChannel *proxy,
    tp_cli_channel_interface_messages_signal_callback_pending_messages_removed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      DBUS_TYPE_G_UINT_ARRAY,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_INTERFACE_MESSAGES, "PendingMessagesRemoved",
      expected_types,
      G_CALLBACK (_tp_cli_channel_interface_messages_collect_args_of_pending_messages_removed),
      _tp_cli_channel_interface_messages_invoke_callback_for_pending_messages_removed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_interface_messages_signal_callback_message_received:
 * @proxy: The proxy on which tp_cli_channel_interface_messages_connect_to_message_received ()
 *  was called
 * @arg_Message: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           The message content, including any attachments or alternatives
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal MessageReceived.
 */
static void
_tp_cli_channel_interface_messages_collect_args_of_message_received (DBusGProxy *proxy G_GNUC_UNUSED,
    const GPtrArray *arg_Message,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))));
  g_value_set_boxed (args->values + 0, arg_Message);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_interface_messages_invoke_callback_for_message_received (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_messages_signal_callback_message_received callback =
      (tp_cli_channel_interface_messages_signal_callback_message_received) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_interface_messages_connect_to_message_received:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal MessageReceived.
 *
 * Signals that a message has been received and added to the pending         messages queue. This MUST be emitted exactly once per emission of the         &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Type.Text&quot;&gt;Received&lt;/tp:dbus-ref&gt;         signal on the Text interface.          &lt;tp:rationale&gt;           The double signal-emission provides compatibility with older           clients. Clients supporting Messages should listen for           Messages.MessageReceived only (if the channel has the Messages           interface) or Text.Received only (otherwise).         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_interface_messages_connect_to_message_received (TpChannel *proxy,
    tp_cli_channel_interface_messages_signal_callback_message_received callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_INTERFACE_MESSAGES, "MessageReceived",
      expected_types,
      G_CALLBACK (_tp_cli_channel_interface_messages_collect_args_of_message_received),
      _tp_cli_channel_interface_messages_invoke_callback_for_message_received,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_interface_messages_callback_for_send_message:
 * @proxy: the proxy on which the call was made
 * @out_Token: Used to return an 'out' argument if @error is %NULL: An opaque token used to match any incoming delivery or failure           reports against this message, or an empty string if the message           is not readily identifiable.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a SendMessage method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_messages_collect_callback_send_message (DBusGProxy *proxy,
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
_tp_cli_channel_interface_messages_invoke_callback_send_message (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_messages_callback_for_send_message callback = (tp_cli_channel_interface_messages_callback_for_send_message) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_string (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_messages_call_send_message:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Message: Used to pass an 'in' argument: The message content, including any attachments or alternatives
 * @in_Flags: Used to pass an 'in' argument: Flags affecting how the message is sent.
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
 * Start a SendMessage method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Submit a message to the server for sending.           If this method returns successfully, the message has been submitted           to the server and the &lt;tp:member-ref&gt;MessageSent&lt;/tp:member-ref&gt;           signal is emitted. A corresponding           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Type.Text&quot;&gt;Sent&lt;/tp:dbus-ref&gt;           signal on the Text interface MUST also be emitted.&lt;/p&gt;          &lt;p&gt;This method MUST return before the MessageSent signal is           emitted.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;This means that the process sending the message is the first             to see the &lt;tp:type&gt;Sent_Message_Token&lt;/tp:type&gt;, and can             relate the message to the corresponding             &lt;tp:member-ref&gt;MessageSent&lt;/tp:member-ref&gt; signal by comparing             message tokens (if supported by the protocol).&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;If this method fails, message submission to the server has failed           and no signal on this interface (or the Text interface) is           emitted.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_messages_call_send_message (TpChannel *proxy,
    gint timeout_ms,
    const GPtrArray *in_Message,
    guint in_Flags,
    tp_cli_channel_interface_messages_callback_for_send_message callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_MESSAGES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "SendMessage",
          (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), in_Message,
          G_TYPE_UINT, in_Flags,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "SendMessage", iface,
          _tp_cli_channel_interface_messages_invoke_callback_send_message,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "SendMessage",
              _tp_cli_channel_interface_messages_collect_callback_send_message,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), in_Message,
              G_TYPE_UINT, in_Flags,
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
} _tp_cli_channel_interface_messages_run_state_send_message;
static void
_tp_cli_channel_interface_messages_finish_running_send_message (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_messages_run_state_send_message *state = user_data;

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
 * tp_cli_channel_interface_messages_run_send_message:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Message: Used to pass an 'in' argument: The message content, including any attachments or alternatives
 * @in_Flags: Used to pass an 'in' argument: Flags affecting how the message is sent.
 * @out_Token: Used to return an 'out' argument if %TRUE is returned: An opaque token used to match any incoming delivery or failure           reports against this message, or an empty string if the message           is not readily identifiable.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method SendMessage and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Submit a message to the server for sending.           If this method returns successfully, the message has been submitted           to the server and the &lt;tp:member-ref&gt;MessageSent&lt;/tp:member-ref&gt;           signal is emitted. A corresponding           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Type.Text&quot;&gt;Sent&lt;/tp:dbus-ref&gt;           signal on the Text interface MUST also be emitted.&lt;/p&gt;          &lt;p&gt;This method MUST return before the MessageSent signal is           emitted.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;This means that the process sending the message is the first             to see the &lt;tp:type&gt;Sent_Message_Token&lt;/tp:type&gt;, and can             relate the message to the corresponding             &lt;tp:member-ref&gt;MessageSent&lt;/tp:member-ref&gt; signal by comparing             message tokens (if supported by the protocol).&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;If this method fails, message submission to the server has failed           and no signal on this interface (or the Text interface) is           emitted.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_messages_run_send_message (TpChannel *proxy,
    gint timeout_ms,
    const GPtrArray *in_Message,
    guint in_Flags,
    gchar **out_Token,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_MESSAGES;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_messages_run_state_send_message state = {
      NULL /* loop */, error,
    out_Token,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "SendMessage", iface,
      _tp_cli_channel_interface_messages_finish_running_send_message,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "SendMessage",
          _tp_cli_channel_interface_messages_collect_callback_send_message,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)))), in_Message,
              G_TYPE_UINT, in_Flags,
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
 * tp_cli_channel_interface_messages_callback_for_get_pending_message_content:
 * @proxy: the proxy on which the call was made
 * @out_Content: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The content of the requested parts. The keys in this mapping             are positions in the array of message parts; the values are             either of type &apos;s&apos; or &apos;ay&apos; (UTF-8 text string, or byte array),             following the same rules as for the value of the &apos;content&apos; key in             the &lt;tp:type&gt;Message_Part&lt;/tp:type&gt; mappings.&lt;/p&gt;            &lt;p&gt;If the one of the requested part numbers was greater than zero             but referred to a part that had no content (i.e. it had no             &apos;content-type&apos; key or no &apos;content&apos; key), it is simply omitted from             this mapping; this is not considered to be an error condition.&lt;/p&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetPendingMessageContent method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_messages_collect_callback_get_pending_message_content (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GHashTable *out_Content;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_VALUE)), &out_Content,
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
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_VALUE)));
  g_value_take_boxed (args->values + 0, out_Content);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_interface_messages_invoke_callback_get_pending_message_content (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_messages_callback_for_get_pending_message_content callback = (tp_cli_channel_interface_messages_callback_for_get_pending_message_content) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_messages_call_get_pending_message_content:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Message_ID: Used to pass an 'in' argument: The ID of a pending message
 * @in_Parts: Used to pass an 'in' argument: The desired entries in the array of message parts, identified by           their position. The &amp;quot;headers&amp;quot; part (which is not a valid argument           to this method) is considered to be part 0, so the valid part           numbers start at 1 (for the second Message_Part).
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
 * Start a GetPendingMessageContent method call.
 *
 * Retrieve the content of one or more parts of a pending message.         Note that this function may take a considerable amount of time         to return if the part&apos;s &apos;needs-retrieval&apos; flag is true; consider         extending the default D-Bus method call timeout. Additional API is         likely to be added in future, to stream large message parts.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_messages_call_get_pending_message_content (TpChannel *proxy,
    gint timeout_ms,
    guint in_Message_ID,
    const GArray *in_Parts,
    tp_cli_channel_interface_messages_callback_for_get_pending_message_content callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_MESSAGES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetPendingMessageContent",
          G_TYPE_UINT, in_Message_ID,
          DBUS_TYPE_G_UINT_ARRAY, in_Parts,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetPendingMessageContent", iface,
          _tp_cli_channel_interface_messages_invoke_callback_get_pending_message_content,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetPendingMessageContent",
              _tp_cli_channel_interface_messages_collect_callback_get_pending_message_content,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Message_ID,
              DBUS_TYPE_G_UINT_ARRAY, in_Parts,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GHashTable **out_Content;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_messages_run_state_get_pending_message_content;
static void
_tp_cli_channel_interface_messages_finish_running_get_pending_message_content (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_messages_run_state_get_pending_message_content *state = user_data;

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

  if (state->out_Content != NULL)
    *state->out_Content = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_messages_run_get_pending_message_content:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Message_ID: Used to pass an 'in' argument: The ID of a pending message
 * @in_Parts: Used to pass an 'in' argument: The desired entries in the array of message parts, identified by           their position. The &amp;quot;headers&amp;quot; part (which is not a valid argument           to this method) is considered to be part 0, so the valid part           numbers start at 1 (for the second Message_Part).
 * @out_Content: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The content of the requested parts. The keys in this mapping             are positions in the array of message parts; the values are             either of type &apos;s&apos; or &apos;ay&apos; (UTF-8 text string, or byte array),             following the same rules as for the value of the &apos;content&apos; key in             the &lt;tp:type&gt;Message_Part&lt;/tp:type&gt; mappings.&lt;/p&gt;            &lt;p&gt;If the one of the requested part numbers was greater than zero             but referred to a part that had no content (i.e. it had no             &apos;content-type&apos; key or no &apos;content&apos; key), it is simply omitted from             this mapping; this is not considered to be an error condition.&lt;/p&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetPendingMessageContent and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Retrieve the content of one or more parts of a pending message.         Note that this function may take a considerable amount of time         to return if the part&apos;s &apos;needs-retrieval&apos; flag is true; consider         extending the default D-Bus method call timeout. Additional API is         likely to be added in future, to stream large message parts.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_messages_run_get_pending_message_content (TpChannel *proxy,
    gint timeout_ms,
    guint in_Message_ID,
    const GArray *in_Parts,
    GHashTable **out_Content,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_MESSAGES;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_messages_run_state_get_pending_message_content state = {
      NULL /* loop */, error,
    out_Content,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetPendingMessageContent", iface,
      _tp_cli_channel_interface_messages_finish_running_get_pending_message_content,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetPendingMessageContent",
          _tp_cli_channel_interface_messages_collect_callback_get_pending_message_content,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Message_ID,
              DBUS_TYPE_G_UINT_ARRAY, in_Parts,
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
tp_cli_add_signals_for_channel_interface_password (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "PasswordFlagsChanged",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_interface_password_signal_callback_password_flags_changed:
 * @proxy: The proxy on which tp_cli_channel_interface_password_connect_to_password_flags_changed ()
 *  was called
 * @arg_Added: A bitwise OR of the flags which have been set
 * @arg_Removed: A bitwise OR of the flags which have been cleared
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal PasswordFlagsChanged.
 */
static void
_tp_cli_channel_interface_password_collect_args_of_password_flags_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Added,
    guint arg_Removed,
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
  g_value_set_uint (args->values + 0, arg_Added);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Removed);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_interface_password_invoke_callback_for_password_flags_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_password_signal_callback_password_flags_changed callback =
      (tp_cli_channel_interface_password_signal_callback_password_flags_changed) generic_callback;

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
 * tp_cli_channel_interface_password_connect_to_password_flags_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal PasswordFlagsChanged.
 *
 * Emitted when the flags as returned by         &lt;tp:member-ref&gt;GetPasswordFlags&lt;/tp:member-ref&gt; are changed.         The user interface should be updated as appropriate.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_interface_password_connect_to_password_flags_changed (TpChannel *proxy,
    tp_cli_channel_interface_password_signal_callback_password_flags_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_INTERFACE_PASSWORD, "PasswordFlagsChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_interface_password_collect_args_of_password_flags_changed),
      _tp_cli_channel_interface_password_invoke_callback_for_password_flags_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_interface_password_callback_for_get_password_flags:
 * @proxy: the proxy on which the call was made
 * @out_Password_Flags: Used to return an 'out' argument if @error is %NULL: An integer with the logical OR of all the flags set           (values of ChannelPasswordFlags)
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetPasswordFlags method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_password_collect_callback_get_password_flags (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  guint out_Password_Flags;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_UINT, &out_Password_Flags,
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
  g_value_set_uint (args->values + 0, out_Password_Flags);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_interface_password_invoke_callback_get_password_flags (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_password_callback_for_get_password_flags callback = (tp_cli_channel_interface_password_callback_for_get_password_flags) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          0,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_uint (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_password_call_get_password_flags:
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
 * Start a GetPasswordFlags method call.
 *
 * Returns the bitwise-OR of the flags relevant to the password on this         channel.  The user interface can use this to present information about         which operations are currently valid.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_password_call_get_password_flags (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_interface_password_callback_for_get_password_flags callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_PASSWORD;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetPasswordFlags",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetPasswordFlags", iface,
          _tp_cli_channel_interface_password_invoke_callback_get_password_flags,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetPasswordFlags",
              _tp_cli_channel_interface_password_collect_callback_get_password_flags,
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
    guint *out_Password_Flags;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_password_run_state_get_password_flags;
static void
_tp_cli_channel_interface_password_finish_running_get_password_flags (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_password_run_state_get_password_flags *state = user_data;

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

  if (state->out_Password_Flags != NULL)
    *state->out_Password_Flags = g_value_get_uint (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_password_run_get_password_flags:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Password_Flags: Used to return an 'out' argument if %TRUE is returned: An integer with the logical OR of all the flags set           (values of ChannelPasswordFlags)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetPasswordFlags and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns the bitwise-OR of the flags relevant to the password on this         channel.  The user interface can use this to present information about         which operations are currently valid.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_password_run_get_password_flags (TpChannel *proxy,
    gint timeout_ms,
    guint *out_Password_Flags,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_PASSWORD;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_password_run_state_get_password_flags state = {
      NULL /* loop */, error,
    out_Password_Flags,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetPasswordFlags", iface,
      _tp_cli_channel_interface_password_finish_running_get_password_flags,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetPasswordFlags",
          _tp_cli_channel_interface_password_collect_callback_get_password_flags,
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
 * tp_cli_channel_interface_password_callback_for_provide_password:
 * @proxy: the proxy on which the call was made
 * @out_Correct: Used to return an 'out' argument if @error is %NULL: (Undocumented)
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a ProvidePassword method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_interface_password_collect_callback_provide_password (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gboolean out_Correct;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_BOOLEAN, &out_Correct,
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
  g_value_init (args->values + 0, G_TYPE_BOOLEAN);
  g_value_set_boolean (args->values + 0, out_Correct);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_interface_password_invoke_callback_provide_password (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_password_callback_for_provide_password callback = (tp_cli_channel_interface_password_callback_for_provide_password) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          0,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boolean (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_password_call_provide_password:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Password: Used to pass an 'in' argument: The password
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
 * Start a ProvidePassword method call.
 *
 * Provide the password so that the channel can be joined. Must be         called with the correct password in order for channel joining to         proceed if the &apos;provide&apos; password flag is set.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_interface_password_call_provide_password (TpChannel *proxy,
    gint timeout_ms,
    const gchar *in_Password,
    tp_cli_channel_interface_password_callback_for_provide_password callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_PASSWORD;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "ProvidePassword",
          G_TYPE_STRING, in_Password,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "ProvidePassword", iface,
          _tp_cli_channel_interface_password_invoke_callback_provide_password,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "ProvidePassword",
              _tp_cli_channel_interface_password_collect_callback_provide_password,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Password,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gboolean *out_Correct;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_interface_password_run_state_provide_password;
static void
_tp_cli_channel_interface_password_finish_running_provide_password (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_interface_password_run_state_provide_password *state = user_data;

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

  if (state->out_Correct != NULL)
    *state->out_Correct = g_value_get_boolean (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_interface_password_run_provide_password:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Password: Used to pass an 'in' argument: The password
 * @out_Correct: Used to return an 'out' argument if %TRUE is returned: (Undocumented)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method ProvidePassword and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Provide the password so that the channel can be joined. Must be         called with the correct password in order for channel joining to         proceed if the &apos;provide&apos; password flag is set.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_interface_password_run_provide_password (TpChannel *proxy,
    gint timeout_ms,
    const gchar *in_Password,
    gboolean *out_Correct,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_INTERFACE_PASSWORD;
  TpProxyPendingCall *pc;
  _tp_cli_channel_interface_password_run_state_provide_password state = {
      NULL /* loop */, error,
    out_Correct,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "ProvidePassword", iface,
      _tp_cli_channel_interface_password_finish_running_provide_password,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "ProvidePassword",
          _tp_cli_channel_interface_password_collect_callback_provide_password,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_STRING, in_Password,
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
tp_cli_add_signals_for_channel_interface_tube (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "TubeChannelStateChanged",
      G_TYPE_UINT,
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_interface_tube_signal_callback_tube_channel_state_changed:
 * @proxy: The proxy on which tp_cli_channel_interface_tube_connect_to_tube_channel_state_changed ()
 *  was called
 * @arg_State: The new state of the tube.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal TubeChannelStateChanged.
 */
static void
_tp_cli_channel_interface_tube_collect_args_of_tube_channel_state_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_State,
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
  g_value_set_uint (args->values + 0, arg_State);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_interface_tube_invoke_callback_for_tube_channel_state_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_interface_tube_signal_callback_tube_channel_state_changed callback =
      (tp_cli_channel_interface_tube_signal_callback_tube_channel_state_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_interface_tube_connect_to_tube_channel_state_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal TubeChannelStateChanged.
 *
 * Emitted when the state of the tube channel changes. Valid state         transitions are documented with &lt;tp:type&gt;Tube_Channel_State&lt;/tp:type&gt;.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_interface_tube_connect_to_tube_channel_state_changed (TpChannel *proxy,
    tp_cli_channel_interface_tube_signal_callback_tube_channel_state_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_INTERFACE_TUBE, "TubeChannelStateChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_interface_tube_collect_args_of_tube_channel_state_changed),
      _tp_cli_channel_interface_tube_invoke_callback_for_tube_channel_state_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

static inline void
tp_cli_add_signals_for_channel_type_dbus_tube (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "DBusNamesChanged",
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_STRING)),
      DBUS_TYPE_G_UINT_ARRAY,
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_type_dbus_tube_signal_callback_dbus_names_changed:
 * @proxy: The proxy on which tp_cli_channel_type_dbus_tube_connect_to_dbus_names_changed ()
 *  was called
 * @arg_Added: Array of handles and D-Bus names of new participants.
 * @arg_Removed: Array of handles of former participants.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal DBusNamesChanged.
 */
static void
_tp_cli_channel_type_dbus_tube_collect_args_of_dbus_names_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    GHashTable *arg_Added,
    const GArray *arg_Removed,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (2);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 2; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_STRING)));
  g_value_set_boxed (args->values + 0, arg_Added);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, DBUS_TYPE_G_UINT_ARRAY);
  g_value_set_boxed (args->values + 1, arg_Removed);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_dbus_tube_invoke_callback_for_dbus_names_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_dbus_tube_signal_callback_dbus_names_changed callback =
      (tp_cli_channel_type_dbus_tube_signal_callback_dbus_names_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      g_value_get_boxed (args->values + 1),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_dbus_tube_connect_to_dbus_names_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal DBusNamesChanged.
 *
 * Emitted on a multi-user (i.e. Handle_Type_Room) D-Bus tube when a         participant opens or closes the tube.  This provides change         notification for the &lt;tp:member-ref&gt;DBusNames&lt;/tp:member-ref&gt; property.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_dbus_tube_connect_to_dbus_names_changed (TpChannel *proxy,
    tp_cli_channel_type_dbus_tube_signal_callback_dbus_names_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, G_TYPE_STRING)),
      DBUS_TYPE_G_UINT_ARRAY,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_DBUS_TUBE, "DBusNamesChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_dbus_tube_collect_args_of_dbus_names_changed),
      _tp_cli_channel_type_dbus_tube_invoke_callback_for_dbus_names_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_dbus_tube_callback_for_offer:
 * @proxy: the proxy on which the call was made
 * @out_address: Used to return an 'out' argument if @error is %NULL: The string describing the address of the private bus. The client           SHOULD NOT attempt to connect to the address until the tube is open.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Offer method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_dbus_tube_collect_callback_offer (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_address;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRING, &out_address,
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
  g_value_take_string (args->values + 0, out_address);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_dbus_tube_invoke_callback_offer (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_dbus_tube_callback_for_offer callback = (tp_cli_channel_type_dbus_tube_callback_for_offer) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_string (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_dbus_tube_call_offer:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_parameters: Used to pass an 'in' argument: The dictionary of arbitrary           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface.Tube&quot;&gt;Parameters&lt;/tp:dbus-ref&gt;           to send with the tube offer.
 * @in_access_control: Used to pass an 'in' argument: The access control the connection manager applies to the D-Bus socket.
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
 * Start a Offer method call.
 *
 * Offers a D-Bus tube providing the service specified.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_dbus_tube_call_offer (TpChannel *proxy,
    gint timeout_ms,
    GHashTable *in_parameters,
    guint in_access_control,
    tp_cli_channel_type_dbus_tube_callback_for_offer callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_DBUS_TUBE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Offer",
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_parameters,
          G_TYPE_UINT, in_access_control,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Offer", iface,
          _tp_cli_channel_type_dbus_tube_invoke_callback_offer,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Offer",
              _tp_cli_channel_type_dbus_tube_collect_callback_offer,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_parameters,
              G_TYPE_UINT, in_access_control,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gchar **out_address;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_dbus_tube_run_state_offer;
static void
_tp_cli_channel_type_dbus_tube_finish_running_offer (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_dbus_tube_run_state_offer *state = user_data;

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

  if (state->out_address != NULL)
    *state->out_address = g_value_dup_string (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_dbus_tube_run_offer:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_parameters: Used to pass an 'in' argument: The dictionary of arbitrary           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface.Tube&quot;&gt;Parameters&lt;/tp:dbus-ref&gt;           to send with the tube offer.
 * @in_access_control: Used to pass an 'in' argument: The access control the connection manager applies to the D-Bus socket.
 * @out_address: Used to return an 'out' argument if %TRUE is returned: The string describing the address of the private bus. The client           SHOULD NOT attempt to connect to the address until the tube is open.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Offer and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Offers a D-Bus tube providing the service specified.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_dbus_tube_run_offer (TpChannel *proxy,
    gint timeout_ms,
    GHashTable *in_parameters,
    guint in_access_control,
    gchar **out_address,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_DBUS_TUBE;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_dbus_tube_run_state_offer state = {
      NULL /* loop */, error,
    out_address,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Offer", iface,
      _tp_cli_channel_type_dbus_tube_finish_running_offer,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Offer",
          _tp_cli_channel_type_dbus_tube_collect_callback_offer,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_parameters,
              G_TYPE_UINT, in_access_control,
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
 * tp_cli_channel_type_dbus_tube_callback_for_accept:
 * @proxy: the proxy on which the call was made
 * @out_address: Used to return an 'out' argument if @error is %NULL: The string describing the address of the private bus. The client           SHOULD NOT attempt to connect to the address until the tube is open.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Accept method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_dbus_tube_collect_callback_accept (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_address;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRING, &out_address,
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
  g_value_take_string (args->values + 0, out_address);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_dbus_tube_invoke_callback_accept (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_dbus_tube_callback_for_accept callback = (tp_cli_channel_type_dbus_tube_callback_for_accept) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_string (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_dbus_tube_call_accept:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_access_control: Used to pass an 'in' argument: The access control the connection manager applies to the D-Bus socket.
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
 * Start a Accept method call.
 *
 * Accept a D-Bus tube that&apos;s in the &amp;quot;local pending&amp;quot; state. The         connection manager will attempt to open the tube. The tube remains in         the &amp;quot;local pending&amp;quot; state until the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface.Tube&quot;&gt;TubeChannelStateChanged&lt;/tp:dbus-ref&gt;         signal is emitted.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_dbus_tube_call_accept (TpChannel *proxy,
    gint timeout_ms,
    guint in_access_control,
    tp_cli_channel_type_dbus_tube_callback_for_accept callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_DBUS_TUBE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Accept",
          G_TYPE_UINT, in_access_control,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Accept", iface,
          _tp_cli_channel_type_dbus_tube_invoke_callback_accept,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Accept",
              _tp_cli_channel_type_dbus_tube_collect_callback_accept,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_access_control,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gchar **out_address;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_dbus_tube_run_state_accept;
static void
_tp_cli_channel_type_dbus_tube_finish_running_accept (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_dbus_tube_run_state_accept *state = user_data;

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

  if (state->out_address != NULL)
    *state->out_address = g_value_dup_string (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_dbus_tube_run_accept:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_access_control: Used to pass an 'in' argument: The access control the connection manager applies to the D-Bus socket.
 * @out_address: Used to return an 'out' argument if %TRUE is returned: The string describing the address of the private bus. The client           SHOULD NOT attempt to connect to the address until the tube is open.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Accept and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Accept a D-Bus tube that&apos;s in the &amp;quot;local pending&amp;quot; state. The         connection manager will attempt to open the tube. The tube remains in         the &amp;quot;local pending&amp;quot; state until the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface.Tube&quot;&gt;TubeChannelStateChanged&lt;/tp:dbus-ref&gt;         signal is emitted.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_dbus_tube_run_accept (TpChannel *proxy,
    gint timeout_ms,
    guint in_access_control,
    gchar **out_address,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_DBUS_TUBE;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_dbus_tube_run_state_accept state = {
      NULL /* loop */, error,
    out_address,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Accept", iface,
      _tp_cli_channel_type_dbus_tube_finish_running_accept,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Accept",
          _tp_cli_channel_type_dbus_tube_collect_callback_accept,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_access_control,
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
tp_cli_add_signals_for_channel_type_file_transfer (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "FileTransferStateChanged",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "TransferredBytesChanged",
      G_TYPE_UINT64,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "InitialOffsetDefined",
      G_TYPE_UINT64,
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_type_file_transfer_signal_callback_file_transfer_state_changed:
 * @proxy: The proxy on which tp_cli_channel_type_file_transfer_connect_to_file_transfer_state_changed ()
 *  was called
 * @arg_State: The new state of the file transfer; see the File_Transfer_State enumeration.
 * @arg_Reason: The reason for the state change; see the File_Transfer_State_Change_Reason           enumeration.           The value will always be File_Transfer_State_Change_Reason_None, except           when changing state to cancelled.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal FileTransferStateChanged.
 */
static void
_tp_cli_channel_type_file_transfer_collect_args_of_file_transfer_state_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_State,
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
  g_value_set_uint (args->values + 0, arg_State);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Reason);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_file_transfer_invoke_callback_for_file_transfer_state_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_file_transfer_signal_callback_file_transfer_state_changed callback =
      (tp_cli_channel_type_file_transfer_signal_callback_file_transfer_state_changed) generic_callback;

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
 * tp_cli_channel_type_file_transfer_connect_to_file_transfer_state_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal FileTransferStateChanged.
 *
 * Emitted when the state of a file transfer changes.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_file_transfer_connect_to_file_transfer_state_changed (TpChannel *proxy,
    tp_cli_channel_type_file_transfer_signal_callback_file_transfer_state_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_FILE_TRANSFER, "FileTransferStateChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_file_transfer_collect_args_of_file_transfer_state_changed),
      _tp_cli_channel_type_file_transfer_invoke_callback_for_file_transfer_state_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_file_transfer_signal_callback_transferred_bytes_changed:
 * @proxy: The proxy on which tp_cli_channel_type_file_transfer_connect_to_transferred_bytes_changed ()
 *  was called
 * @arg_Count: The number of already transferred bytes.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal TransferredBytesChanged.
 */
static void
_tp_cli_channel_type_file_transfer_collect_args_of_transferred_bytes_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint64 arg_Count,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT64);
  g_value_set_uint64 (args->values + 0, arg_Count);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_file_transfer_invoke_callback_for_transferred_bytes_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_file_transfer_signal_callback_transferred_bytes_changed callback =
      (tp_cli_channel_type_file_transfer_signal_callback_transferred_bytes_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint64 (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_file_transfer_connect_to_transferred_bytes_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal TransferredBytesChanged.
 *
 * Emitted when the number of transferred bytes changes. This will not be         signalled with every single byte change. Instead, the most frequent         this signal will be emitted is once a second. This should be         sufficient, and the &lt;tp:member-ref&gt;TransferredBytes&lt;/tp:member-ref&gt;         property SHOULD NOT be polled.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_file_transfer_connect_to_transferred_bytes_changed (TpChannel *proxy,
    tp_cli_channel_type_file_transfer_signal_callback_transferred_bytes_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      G_TYPE_UINT64,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_FILE_TRANSFER, "TransferredBytesChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_file_transfer_collect_args_of_transferred_bytes_changed),
      _tp_cli_channel_type_file_transfer_invoke_callback_for_transferred_bytes_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_file_transfer_signal_callback_initial_offset_defined:
 * @proxy: The proxy on which tp_cli_channel_type_file_transfer_connect_to_initial_offset_defined ()
 *  was called
 * @arg_InitialOffset: The value of the &lt;tp:member-ref&gt;InitialOffset&lt;/tp:member-ref&gt; property.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal InitialOffsetDefined.
 */
static void
_tp_cli_channel_type_file_transfer_collect_args_of_initial_offset_defined (DBusGProxy *proxy G_GNUC_UNUSED,
    guint64 arg_InitialOffset,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT64);
  g_value_set_uint64 (args->values + 0, arg_InitialOffset);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_file_transfer_invoke_callback_for_initial_offset_defined (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_file_transfer_signal_callback_initial_offset_defined callback =
      (tp_cli_channel_type_file_transfer_signal_callback_initial_offset_defined) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint64 (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_file_transfer_connect_to_initial_offset_defined:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal InitialOffsetDefined.
 *
 * Emitted when the value of the &lt;tp:member-ref&gt;InitialOffset&lt;/tp:member-ref&gt;         property has been negotiated. This signal MUST be emitted before the channel         becomes Open and clients have to use this offset when transferring the         file.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_file_transfer_connect_to_initial_offset_defined (TpChannel *proxy,
    tp_cli_channel_type_file_transfer_signal_callback_initial_offset_defined callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      G_TYPE_UINT64,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_FILE_TRANSFER, "InitialOffsetDefined",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_file_transfer_collect_args_of_initial_offset_defined),
      _tp_cli_channel_type_file_transfer_invoke_callback_for_initial_offset_defined,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_file_transfer_callback_for_accept_file:
 * @proxy: the proxy on which the call was made
 * @out_Address: Used to return an 'out' argument if @error is %NULL: The address on which the connection manager will listen for           connections for this file transfer.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a AcceptFile method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_file_transfer_collect_callback_accept_file (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GValue *out_Address = g_new0 (GValue, 1);

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_VALUE, out_Address,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      g_free (out_Address);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_VALUE);
  g_value_take_boxed (args->values + 0, out_Address);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_file_transfer_invoke_callback_accept_file (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_file_transfer_callback_for_accept_file callback = (tp_cli_channel_type_file_transfer_callback_for_accept_file) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_file_transfer_call_accept_file:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Address_Type: Used to pass an 'in' argument: The type of address the connection manager should listen on.
 * @in_Access_Control: Used to pass an 'in' argument: The type of access control the connection manager should apply to           the socket.
 * @in_Access_Control_Param: Used to pass an 'in' argument: A parameter for the access control type, to be interpreted as           specified in the documentation for the Socket_Access_Control enum.
 * @in_Offset: Used to pass an 'in' argument: The desired offset in bytes where the file transfer should start.           The offset is taken from the beginning of the file. Specifying an           offset of zero will start the transfer from the beginning of the           file. The offset that is actually given in the           &lt;tp:member-ref&gt;InitialOffset&lt;/tp:member-ref&gt; property can differ           from this argument where the requested offset is not supported.           (For example, some protocols do not support offsets at all so           the InitialOffset property will always be 0.)
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
 * Start a AcceptFile method call.
 *
 * Accept a file transfer that&apos;s in the Pending state. The file         transfer&apos;s state becomes Accepted after this method is called.         At this point the client can connect to the socket. CM MUST emit         &lt;tp:member-ref&gt;InitialOffsetDefined&lt;/tp:member-ref&gt; and change         the state to Open before writing to the socket.         Then &lt;tp:member-ref&gt;InitialOffset&lt;/tp:member-ref&gt; should be respected in case         its value differs from the offset that was specified as an argument         to AcceptFile.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_file_transfer_call_accept_file (TpChannel *proxy,
    gint timeout_ms,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    guint64 in_Offset,
    tp_cli_channel_type_file_transfer_callback_for_accept_file callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_FILE_TRANSFER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "AcceptFile",
          G_TYPE_UINT, in_Address_Type,
          G_TYPE_UINT, in_Access_Control,
          G_TYPE_VALUE, in_Access_Control_Param,
          G_TYPE_UINT64, in_Offset,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "AcceptFile", iface,
          _tp_cli_channel_type_file_transfer_invoke_callback_accept_file,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "AcceptFile",
              _tp_cli_channel_type_file_transfer_collect_callback_accept_file,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Address_Type,
              G_TYPE_UINT, in_Access_Control,
              G_TYPE_VALUE, in_Access_Control_Param,
              G_TYPE_UINT64, in_Offset,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GValue **out_Address;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_file_transfer_run_state_accept_file;
static void
_tp_cli_channel_type_file_transfer_finish_running_accept_file (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_file_transfer_run_state_accept_file *state = user_data;

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

  if (state->out_Address != NULL)
    *state->out_Address = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_file_transfer_run_accept_file:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Address_Type: Used to pass an 'in' argument: The type of address the connection manager should listen on.
 * @in_Access_Control: Used to pass an 'in' argument: The type of access control the connection manager should apply to           the socket.
 * @in_Access_Control_Param: Used to pass an 'in' argument: A parameter for the access control type, to be interpreted as           specified in the documentation for the Socket_Access_Control enum.
 * @in_Offset: Used to pass an 'in' argument: The desired offset in bytes where the file transfer should start.           The offset is taken from the beginning of the file. Specifying an           offset of zero will start the transfer from the beginning of the           file. The offset that is actually given in the           &lt;tp:member-ref&gt;InitialOffset&lt;/tp:member-ref&gt; property can differ           from this argument where the requested offset is not supported.           (For example, some protocols do not support offsets at all so           the InitialOffset property will always be 0.)
 * @out_Address: Used to return an 'out' argument if %TRUE is returned: The address on which the connection manager will listen for           connections for this file transfer.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method AcceptFile and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Accept a file transfer that&apos;s in the Pending state. The file         transfer&apos;s state becomes Accepted after this method is called.         At this point the client can connect to the socket. CM MUST emit         &lt;tp:member-ref&gt;InitialOffsetDefined&lt;/tp:member-ref&gt; and change         the state to Open before writing to the socket.         Then &lt;tp:member-ref&gt;InitialOffset&lt;/tp:member-ref&gt; should be respected in case         its value differs from the offset that was specified as an argument         to AcceptFile.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_file_transfer_run_accept_file (TpChannel *proxy,
    gint timeout_ms,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    guint64 in_Offset,
    GValue **out_Address,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_FILE_TRANSFER;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_file_transfer_run_state_accept_file state = {
      NULL /* loop */, error,
    out_Address,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "AcceptFile", iface,
      _tp_cli_channel_type_file_transfer_finish_running_accept_file,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "AcceptFile",
          _tp_cli_channel_type_file_transfer_collect_callback_accept_file,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Address_Type,
              G_TYPE_UINT, in_Access_Control,
              G_TYPE_VALUE, in_Access_Control_Param,
              G_TYPE_UINT64, in_Offset,
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
 * tp_cli_channel_type_file_transfer_callback_for_provide_file:
 * @proxy: the proxy on which the call was made
 * @out_Address: Used to return an 'out' argument if @error is %NULL: The address on which the connection manager will listen for           connections for this file transfer.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a ProvideFile method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_file_transfer_collect_callback_provide_file (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GValue *out_Address = g_new0 (GValue, 1);

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_VALUE, out_Address,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      g_free (out_Address);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_VALUE);
  g_value_take_boxed (args->values + 0, out_Address);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_file_transfer_invoke_callback_provide_file (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_file_transfer_callback_for_provide_file callback = (tp_cli_channel_type_file_transfer_callback_for_provide_file) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_file_transfer_call_provide_file:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Address_Type: Used to pass an 'in' argument: The type of address the connection manager should listen on.
 * @in_Access_Control: Used to pass an 'in' argument: The type of access control the connection manager should apply to           the socket.
 * @in_Access_Control_Param: Used to pass an 'in' argument: A parameter for the access control type, to be interpreted as           specified in the documentation for the Socket_Access_Control enum.
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
 * Start a ProvideFile method call.
 *
 * Provide the file for an outgoing file transfer which has been offered.         Opens a socket that the client can use to provide a file to the connection manager.         The channel MUST have been requested, and will change state         to Open when this method is called if its state was Accepted.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_file_transfer_call_provide_file (TpChannel *proxy,
    gint timeout_ms,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    tp_cli_channel_type_file_transfer_callback_for_provide_file callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_FILE_TRANSFER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "ProvideFile",
          G_TYPE_UINT, in_Address_Type,
          G_TYPE_UINT, in_Access_Control,
          G_TYPE_VALUE, in_Access_Control_Param,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "ProvideFile", iface,
          _tp_cli_channel_type_file_transfer_invoke_callback_provide_file,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "ProvideFile",
              _tp_cli_channel_type_file_transfer_collect_callback_provide_file,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Address_Type,
              G_TYPE_UINT, in_Access_Control,
              G_TYPE_VALUE, in_Access_Control_Param,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GValue **out_Address;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_file_transfer_run_state_provide_file;
static void
_tp_cli_channel_type_file_transfer_finish_running_provide_file (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_file_transfer_run_state_provide_file *state = user_data;

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

  if (state->out_Address != NULL)
    *state->out_Address = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_file_transfer_run_provide_file:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Address_Type: Used to pass an 'in' argument: The type of address the connection manager should listen on.
 * @in_Access_Control: Used to pass an 'in' argument: The type of access control the connection manager should apply to           the socket.
 * @in_Access_Control_Param: Used to pass an 'in' argument: A parameter for the access control type, to be interpreted as           specified in the documentation for the Socket_Access_Control enum.
 * @out_Address: Used to return an 'out' argument if %TRUE is returned: The address on which the connection manager will listen for           connections for this file transfer.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method ProvideFile and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Provide the file for an outgoing file transfer which has been offered.         Opens a socket that the client can use to provide a file to the connection manager.         The channel MUST have been requested, and will change state         to Open when this method is called if its state was Accepted.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_file_transfer_run_provide_file (TpChannel *proxy,
    gint timeout_ms,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    GValue **out_Address,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_FILE_TRANSFER;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_file_transfer_run_state_provide_file state = {
      NULL /* loop */, error,
    out_Address,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "ProvideFile", iface,
      _tp_cli_channel_type_file_transfer_finish_running_provide_file,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "ProvideFile",
          _tp_cli_channel_type_file_transfer_collect_callback_provide_file,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Address_Type,
              G_TYPE_UINT, in_Access_Control,
              G_TYPE_VALUE, in_Access_Control_Param,
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
tp_cli_add_signals_for_channel_type_room_list (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "GotRooms",
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID)))),
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "ListingRooms",
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_type_room_list_signal_callback_got_rooms:
 * @proxy: The proxy on which tp_cli_channel_type_room_list_connect_to_got_rooms ()
 *  was called
 * @arg_Rooms: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structs containing:           &lt;ul&gt;             &lt;li&gt;an integer room handle&lt;/li&gt;             &lt;li&gt;a string representing the D-Bus interface name of the channel type&lt;/li&gt;             &lt;li&gt;a dictionary mapping string keys to variant boxed information&lt;/li&gt;           &lt;/ul&gt;
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal GotRooms.
 */
static void
_tp_cli_channel_type_room_list_collect_args_of_got_rooms (DBusGProxy *proxy G_GNUC_UNUSED,
    const GPtrArray *arg_Rooms,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID)))));
  g_value_set_boxed (args->values + 0, arg_Rooms);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_room_list_invoke_callback_for_got_rooms (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_room_list_signal_callback_got_rooms callback =
      (tp_cli_channel_type_room_list_signal_callback_got_rooms) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_room_list_connect_to_got_rooms:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal GotRooms.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Emitted when information about rooms on the server becomes available.         The array contains the room handle (as can be passed to the         &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection&quot;&gt;RequestChannel&lt;/tp:dbus-ref&gt;         method with HANDLE_TYPE_ROOM), the channel         type, and a dictionary containing further information about the         room as available. The following well-known keys and types are         recommended for use where appropriate:&lt;/p&gt;          &lt;dl&gt;           &lt;dt&gt;handle-name (s)&lt;/dt&gt;           &lt;dd&gt;The identifier of the room (as would be returned by             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection&quot;&gt;InspectHandles&lt;/tp:dbus-ref&gt;)&lt;/dd&gt;            &lt;dt&gt;name (s)&lt;/dt&gt;           &lt;dd&gt;The human-readable name of the room if different from the handle&lt;/dd&gt;            &lt;dt&gt;description (s)&lt;/dt&gt;           &lt;dd&gt;A description of the room&apos;s overall purpose&lt;/dd&gt;            &lt;dt&gt;subject (s)&lt;/dt&gt;           &lt;dd&gt;The current subject of conversation in the room&lt;/dd&gt;            &lt;dt&gt;members (u)&lt;/dt&gt;           &lt;dd&gt;The number of members in the room&lt;/dd&gt;            &lt;dt&gt;password (b)&lt;/dt&gt;           &lt;dd&gt;True if the room requires a password to enter&lt;/dd&gt;            &lt;dt&gt;invite-only (b)&lt;/dt&gt;           &lt;dd&gt;True if you cannot join the room, but must be invited&lt;/dd&gt;         &lt;/dl&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_room_list_connect_to_got_rooms (TpChannel *proxy,
    tp_cli_channel_type_room_list_signal_callback_got_rooms callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID)))),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_ROOM_LIST, "GotRooms",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_room_list_collect_args_of_got_rooms),
      _tp_cli_channel_type_room_list_invoke_callback_for_got_rooms,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_room_list_signal_callback_listing_rooms:
 * @proxy: The proxy on which tp_cli_channel_type_room_list_connect_to_listing_rooms ()
 *  was called
 * @arg_Listing: A boolean indicating if room listing is in progress
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal ListingRooms.
 */
static void
_tp_cli_channel_type_room_list_collect_args_of_listing_rooms (DBusGProxy *proxy G_GNUC_UNUSED,
    gboolean arg_Listing,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_BOOLEAN);
  g_value_set_boolean (args->values + 0, arg_Listing);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_room_list_invoke_callback_for_listing_rooms (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_room_list_signal_callback_listing_rooms callback =
      (tp_cli_channel_type_room_list_signal_callback_listing_rooms) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boolean (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_room_list_connect_to_listing_rooms:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal ListingRooms.
 *
 * Emitted to indicate whether or not room listing request is currently         in progress.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_room_list_connect_to_listing_rooms (TpChannel *proxy,
    tp_cli_channel_type_room_list_signal_callback_listing_rooms callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_ROOM_LIST, "ListingRooms",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_room_list_collect_args_of_listing_rooms),
      _tp_cli_channel_type_room_list_invoke_callback_for_listing_rooms,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_room_list_callback_for_get_listing_rooms:
 * @proxy: the proxy on which the call was made
 * @out_In_Progress: Used to return an 'out' argument if @error is %NULL: A boolean indicating if room listing is in progress
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetListingRooms method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_room_list_collect_callback_get_listing_rooms (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gboolean out_In_Progress;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_BOOLEAN, &out_In_Progress,
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
  g_value_init (args->values + 0, G_TYPE_BOOLEAN);
  g_value_set_boolean (args->values + 0, out_In_Progress);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_room_list_invoke_callback_get_listing_rooms (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_room_list_callback_for_get_listing_rooms callback = (tp_cli_channel_type_room_list_callback_for_get_listing_rooms) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          0,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boolean (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_room_list_call_get_listing_rooms:
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
 * Start a GetListingRooms method call.
 *
 * Check to see if there is already a room list request in progress         on this channel.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_room_list_call_get_listing_rooms (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_room_list_callback_for_get_listing_rooms callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_ROOM_LIST;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetListingRooms",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetListingRooms", iface,
          _tp_cli_channel_type_room_list_invoke_callback_get_listing_rooms,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetListingRooms",
              _tp_cli_channel_type_room_list_collect_callback_get_listing_rooms,
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
    gboolean *out_In_Progress;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_room_list_run_state_get_listing_rooms;
static void
_tp_cli_channel_type_room_list_finish_running_get_listing_rooms (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_room_list_run_state_get_listing_rooms *state = user_data;

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

  if (state->out_In_Progress != NULL)
    *state->out_In_Progress = g_value_get_boolean (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_room_list_run_get_listing_rooms:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_In_Progress: Used to return an 'out' argument if %TRUE is returned: A boolean indicating if room listing is in progress
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetListingRooms and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Check to see if there is already a room list request in progress         on this channel.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_room_list_run_get_listing_rooms (TpChannel *proxy,
    gint timeout_ms,
    gboolean *out_In_Progress,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_ROOM_LIST;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_room_list_run_state_get_listing_rooms state = {
      NULL /* loop */, error,
    out_In_Progress,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetListingRooms", iface,
      _tp_cli_channel_type_room_list_finish_running_get_listing_rooms,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetListingRooms",
          _tp_cli_channel_type_room_list_collect_callback_get_listing_rooms,
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
 * tp_cli_channel_type_room_list_callback_for_list_rooms:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a ListRooms method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_room_list_collect_callback_list_rooms (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_type_room_list_invoke_callback_list_rooms (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_room_list_callback_for_list_rooms callback = (tp_cli_channel_type_room_list_callback_for_list_rooms) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_type_room_list_call_list_rooms:
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
 * Start a ListRooms method call.
 *
 * Request the list of rooms from the server. The         &lt;tp:member-ref&gt;ListingRooms&lt;/tp:member-ref&gt; (True) signal should be         emitted when this request is being processed,         &lt;tp:member-ref&gt;GotRooms&lt;/tp:member-ref&gt; when any room information is         received, and &lt;tp:member-ref&gt;ListingRooms&lt;/tp:member-ref&gt; (False) when         the request is complete.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_room_list_call_list_rooms (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_room_list_callback_for_list_rooms callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_ROOM_LIST;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "ListRooms",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "ListRooms", iface,
          _tp_cli_channel_type_room_list_invoke_callback_list_rooms,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "ListRooms",
              _tp_cli_channel_type_room_list_collect_callback_list_rooms,
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
} _tp_cli_channel_type_room_list_run_state_list_rooms;
static void
_tp_cli_channel_type_room_list_finish_running_list_rooms (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_room_list_run_state_list_rooms *state = user_data;

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
 * tp_cli_channel_type_room_list_run_list_rooms:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method ListRooms and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Request the list of rooms from the server. The         &lt;tp:member-ref&gt;ListingRooms&lt;/tp:member-ref&gt; (True) signal should be         emitted when this request is being processed,         &lt;tp:member-ref&gt;GotRooms&lt;/tp:member-ref&gt; when any room information is         received, and &lt;tp:member-ref&gt;ListingRooms&lt;/tp:member-ref&gt; (False) when         the request is complete.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_room_list_run_list_rooms (TpChannel *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_ROOM_LIST;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_room_list_run_state_list_rooms state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "ListRooms", iface,
      _tp_cli_channel_type_room_list_finish_running_list_rooms,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "ListRooms",
          _tp_cli_channel_type_room_list_collect_callback_list_rooms,
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
 * tp_cli_channel_type_room_list_callback_for_stop_listing:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a StopListing method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_room_list_collect_callback_stop_listing (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_type_room_list_invoke_callback_stop_listing (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_room_list_callback_for_stop_listing callback = (tp_cli_channel_type_room_list_callback_for_stop_listing) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_type_room_list_call_stop_listing:
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
 * Start a StopListing method call.
 *
 * Stop the room listing if it&apos;s in progress, but don&apos;t close the channel.         The &lt;tp:member-ref&gt;ListingRooms&lt;/tp:member-ref&gt; (False) signal should         be emitted when the listing stops.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_room_list_call_stop_listing (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_room_list_callback_for_stop_listing callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_ROOM_LIST;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "StopListing",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "StopListing", iface,
          _tp_cli_channel_type_room_list_invoke_callback_stop_listing,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "StopListing",
              _tp_cli_channel_type_room_list_collect_callback_stop_listing,
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
} _tp_cli_channel_type_room_list_run_state_stop_listing;
static void
_tp_cli_channel_type_room_list_finish_running_stop_listing (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_room_list_run_state_stop_listing *state = user_data;

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
 * tp_cli_channel_type_room_list_run_stop_listing:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method StopListing and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Stop the room listing if it&apos;s in progress, but don&apos;t close the channel.         The &lt;tp:member-ref&gt;ListingRooms&lt;/tp:member-ref&gt; (False) signal should         be emitted when the listing stops.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_room_list_run_stop_listing (TpChannel *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_ROOM_LIST;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_room_list_run_state_stop_listing state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "StopListing", iface,
      _tp_cli_channel_type_room_list_finish_running_stop_listing,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "StopListing",
          _tp_cli_channel_type_room_list_collect_callback_stop_listing,
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
tp_cli_add_signals_for_channel_type_stream_tube (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "NewRemoteConnection",
      G_TYPE_UINT,
      G_TYPE_VALUE,
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "NewLocalConnection",
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "ConnectionClosed",
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_type_stream_tube_signal_callback_new_remote_connection:
 * @proxy: The proxy on which tp_cli_channel_type_stream_tube_connect_to_new_remote_connection ()
 *  was called
 * @arg_Handle: The handle of the participant who opened the new connection
 * @arg_Connection_Param: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A parameter which can be used by the listening process to identify           the connection. Note that this parameter has a meaningful value           only in the Socket_Access_Control_Port and           Socket_Access_Control_Credentials cases. If a different           Socket_Access_Control has been chosen when offering the tube, this           parameter should be ignored.&lt;/p&gt;            &lt;p&gt;In the Socket_Access_Control_Port case, the variant           contains a struct Socket_Address_IPv4 (or Socket_Address_IPv6)           containing the address from which the CM is connected to the client           application.&lt;/p&gt;            &lt;p&gt;In the Socket_Access_Control_Credentials case, the variant           contains the byte (D-Bus signature &apos;y&apos;) that has been sent with           the credentials.&lt;/p&gt;
 * @arg_Connection_ID: The unique ID associated with this connection. This ID will be used           to identifiy the connection when reporting errors with           &lt;tp:member-ref&gt;ConnectionClosed&lt;/tp:member-ref&gt;.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal NewRemoteConnection.
 */
static void
_tp_cli_channel_type_stream_tube_collect_args_of_new_remote_connection (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Handle,
    const GValue *arg_Connection_Param,
    guint arg_Connection_ID,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (3);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 3; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, arg_Handle);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_VALUE);
  g_value_set_boxed (args->values + 1, arg_Connection_Param);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, G_TYPE_UINT);
  g_value_set_uint (args->values + 2, arg_Connection_ID);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_stream_tube_invoke_callback_for_new_remote_connection (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_stream_tube_signal_callback_new_remote_connection callback =
      (tp_cli_channel_type_stream_tube_signal_callback_new_remote_connection) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      g_value_get_boxed (args->values + 1),
      g_value_get_uint (args->values + 2),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_stream_tube_connect_to_new_remote_connection:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal NewRemoteConnection.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Emitted each time a participant opens a new connection to its         socket.&lt;/p&gt;          &lt;p&gt;This signal is only fired on the offering side.&lt;/p&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_stream_tube_connect_to_new_remote_connection (TpChannel *proxy,
    tp_cli_channel_type_stream_tube_signal_callback_new_remote_connection callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[4] = {
      G_TYPE_UINT,
      G_TYPE_VALUE,
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_STREAM_TUBE, "NewRemoteConnection",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_stream_tube_collect_args_of_new_remote_connection),
      _tp_cli_channel_type_stream_tube_invoke_callback_for_new_remote_connection,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_stream_tube_signal_callback_new_local_connection:
 * @proxy: The proxy on which tp_cli_channel_type_stream_tube_connect_to_new_local_connection ()
 *  was called
 * @arg_Connection_ID: The unique ID associated with this connection. This ID will be used           to identifiy the connection when reporting errors with           &lt;tp:member-ref&gt;ConnectionClosed&lt;/tp:member-ref&gt;.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal NewLocalConnection.
 */
static void
_tp_cli_channel_type_stream_tube_collect_args_of_new_local_connection (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Connection_ID,
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
  g_value_set_uint (args->values + 0, arg_Connection_ID);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_stream_tube_invoke_callback_for_new_local_connection (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_stream_tube_signal_callback_new_local_connection callback =
      (tp_cli_channel_type_stream_tube_signal_callback_new_local_connection) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_stream_tube_connect_to_new_local_connection:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal NewLocalConnection.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Emitted when the tube application connects to the CM&apos;s socket.&lt;/p&gt;          &lt;p&gt;This signal is only fired on the accepting side.&lt;/p&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_stream_tube_connect_to_new_local_connection (TpChannel *proxy,
    tp_cli_channel_type_stream_tube_signal_callback_new_local_connection callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_STREAM_TUBE, "NewLocalConnection",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_stream_tube_collect_args_of_new_local_connection),
      _tp_cli_channel_type_stream_tube_invoke_callback_for_new_local_connection,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_stream_tube_signal_callback_connection_closed:
 * @proxy: The proxy on which tp_cli_channel_type_stream_tube_connect_to_connection_closed ()
 *  was called
 * @arg_Connection_ID: The ID of the connection.
 * @arg_Error: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The name of a D-Bus error describing the error that occurred.&lt;/p&gt;            &lt;p&gt;The following errors can be used:&lt;/p&gt;           &lt;ul&gt;             &lt;li&gt;&lt;code&gt;org.freedesktop.Telepathy.Error.Cancelled&lt;/code&gt;:                user closed the socket or the tube.&lt;/li&gt;             &lt;li&gt;&lt;code&gt;org.freedesktop.Telepathy.Error.ConnectionLost&lt;/code&gt;:                the bytestream relaying connection&apos;s data has been broken.&lt;/li&gt;             &lt;li&gt;&lt;code&gt;org.freedesktop.Telepathy.Error.ConnectionRefused&lt;/code&gt;:                the tube offer refused the connection.&lt;/li&gt;           &lt;/ul&gt;
 * @arg_Message: A debug message.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal ConnectionClosed.
 */
static void
_tp_cli_channel_type_stream_tube_collect_args_of_connection_closed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Connection_ID,
    const gchar *arg_Error,
    const gchar *arg_Message,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (3);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 3; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, arg_Connection_ID);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_STRING);
  g_value_set_string (args->values + 1, arg_Error);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, G_TYPE_STRING);
  g_value_set_string (args->values + 2, arg_Message);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_stream_tube_invoke_callback_for_connection_closed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_stream_tube_signal_callback_connection_closed callback =
      (tp_cli_channel_type_stream_tube_signal_callback_connection_closed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      g_value_get_string (args->values + 1),
      g_value_get_string (args->values + 2),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_stream_tube_connect_to_connection_closed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal ConnectionClosed.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Emitted when a connection has been closed.&lt;/p&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_stream_tube_connect_to_connection_closed (TpChannel *proxy,
    tp_cli_channel_type_stream_tube_signal_callback_connection_closed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[4] = {
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_STREAM_TUBE, "ConnectionClosed",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_stream_tube_collect_args_of_connection_closed),
      _tp_cli_channel_type_stream_tube_invoke_callback_for_connection_closed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_stream_tube_callback_for_offer:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Offer method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_stream_tube_collect_callback_offer (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_type_stream_tube_invoke_callback_offer (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_stream_tube_callback_for_offer callback = (tp_cli_channel_type_stream_tube_callback_for_offer) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_type_stream_tube_call_offer:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_address_type: Used to pass an 'in' argument: The type of the listening address of the local service, as a member of           Socket_Address_Type.
 * @in_address: Used to pass an 'in' argument: The listening address of the local service, as indicated by the           address_type.
 * @in_access_control: Used to pass an 'in' argument: The access control the local service applies to the local socket,           specified so the connection manager can behave appropriately           when it connects.
 * @in_parameters: Used to pass an 'in' argument: The dictionary of arbitrary           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface.Tube&quot;&gt;Parameters&lt;/tp:dbus-ref&gt;           to send with the tube offer.
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
 * Start a Offer method call.
 *
 * Offer a stream tube exporting the local socket specified.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_stream_tube_call_offer (TpChannel *proxy,
    gint timeout_ms,
    guint in_address_type,
    const GValue *in_address,
    guint in_access_control,
    GHashTable *in_parameters,
    tp_cli_channel_type_stream_tube_callback_for_offer callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_STREAM_TUBE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Offer",
          G_TYPE_UINT, in_address_type,
          G_TYPE_VALUE, in_address,
          G_TYPE_UINT, in_access_control,
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_parameters,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Offer", iface,
          _tp_cli_channel_type_stream_tube_invoke_callback_offer,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Offer",
              _tp_cli_channel_type_stream_tube_collect_callback_offer,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_address_type,
              G_TYPE_VALUE, in_address,
              G_TYPE_UINT, in_access_control,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_parameters,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_stream_tube_run_state_offer;
static void
_tp_cli_channel_type_stream_tube_finish_running_offer (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_stream_tube_run_state_offer *state = user_data;

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
 * tp_cli_channel_type_stream_tube_run_offer:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_address_type: Used to pass an 'in' argument: The type of the listening address of the local service, as a member of           Socket_Address_Type.
 * @in_address: Used to pass an 'in' argument: The listening address of the local service, as indicated by the           address_type.
 * @in_access_control: Used to pass an 'in' argument: The access control the local service applies to the local socket,           specified so the connection manager can behave appropriately           when it connects.
 * @in_parameters: Used to pass an 'in' argument: The dictionary of arbitrary           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface.Tube&quot;&gt;Parameters&lt;/tp:dbus-ref&gt;           to send with the tube offer.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Offer and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Offer a stream tube exporting the local socket specified.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_stream_tube_run_offer (TpChannel *proxy,
    gint timeout_ms,
    guint in_address_type,
    const GValue *in_address,
    guint in_access_control,
    GHashTable *in_parameters,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_STREAM_TUBE;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_stream_tube_run_state_offer state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Offer", iface,
      _tp_cli_channel_type_stream_tube_finish_running_offer,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Offer",
          _tp_cli_channel_type_stream_tube_collect_callback_offer,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_address_type,
              G_TYPE_VALUE, in_address,
              G_TYPE_UINT, in_access_control,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_parameters,
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
 * tp_cli_channel_type_stream_tube_callback_for_accept:
 * @proxy: the proxy on which the call was made
 * @out_address: Used to return an 'out' argument if @error is %NULL: The address on which the connection manager will listen for           connections to this tube. The client should not attempt to connect           to the address until the tube is open.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Accept method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_stream_tube_collect_callback_accept (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GValue *out_address = g_new0 (GValue, 1);

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_VALUE, out_address,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      g_free (out_address);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_VALUE);
  g_value_take_boxed (args->values + 0, out_address);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_stream_tube_invoke_callback_accept (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_stream_tube_callback_for_accept callback = (tp_cli_channel_type_stream_tube_callback_for_accept) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_stream_tube_call_accept:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_address_type: Used to pass an 'in' argument: The type of address the connection manager should listen on.
 * @in_access_control: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The type of access control the connection manager should apply to           the socket.&lt;/p&gt;            &lt;p&gt;Note that if you plan to establish more than one connection           through the tube, the Socket_Access_Control_Port access control           can&apos;t be used as you can&apos;t connect more than once from the same           port.&lt;/p&gt;
 * @in_access_control_param: Used to pass an 'in' argument: A parameter for the access control type, to be interpreted as           specified in the documentation for the Socket_Access_Control enum.
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
 * Start a Accept method call.
 *
 * Accept a stream tube that&apos;s in the &amp;quot;local pending&amp;quot; state. The         connection manager will attempt to open the tube. The tube remains in         the &amp;quot;local pending&amp;quot; state until the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface.Tube&quot;&gt;TubeChannelStateChanged&lt;/tp:dbus-ref&gt;         signal is emitted.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_stream_tube_call_accept (TpChannel *proxy,
    gint timeout_ms,
    guint in_address_type,
    guint in_access_control,
    const GValue *in_access_control_param,
    tp_cli_channel_type_stream_tube_callback_for_accept callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_STREAM_TUBE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Accept",
          G_TYPE_UINT, in_address_type,
          G_TYPE_UINT, in_access_control,
          G_TYPE_VALUE, in_access_control_param,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Accept", iface,
          _tp_cli_channel_type_stream_tube_invoke_callback_accept,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Accept",
              _tp_cli_channel_type_stream_tube_collect_callback_accept,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_address_type,
              G_TYPE_UINT, in_access_control,
              G_TYPE_VALUE, in_access_control_param,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GValue **out_address;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_stream_tube_run_state_accept;
static void
_tp_cli_channel_type_stream_tube_finish_running_accept (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_stream_tube_run_state_accept *state = user_data;

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

  if (state->out_address != NULL)
    *state->out_address = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_stream_tube_run_accept:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_address_type: Used to pass an 'in' argument: The type of address the connection manager should listen on.
 * @in_access_control: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The type of access control the connection manager should apply to           the socket.&lt;/p&gt;            &lt;p&gt;Note that if you plan to establish more than one connection           through the tube, the Socket_Access_Control_Port access control           can&apos;t be used as you can&apos;t connect more than once from the same           port.&lt;/p&gt;
 * @in_access_control_param: Used to pass an 'in' argument: A parameter for the access control type, to be interpreted as           specified in the documentation for the Socket_Access_Control enum.
 * @out_address: Used to return an 'out' argument if %TRUE is returned: The address on which the connection manager will listen for           connections to this tube. The client should not attempt to connect           to the address until the tube is open.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Accept and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Accept a stream tube that&apos;s in the &amp;quot;local pending&amp;quot; state. The         connection manager will attempt to open the tube. The tube remains in         the &amp;quot;local pending&amp;quot; state until the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface.Tube&quot;&gt;TubeChannelStateChanged&lt;/tp:dbus-ref&gt;         signal is emitted.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_stream_tube_run_accept (TpChannel *proxy,
    gint timeout_ms,
    guint in_address_type,
    guint in_access_control,
    const GValue *in_access_control_param,
    GValue **out_address,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_STREAM_TUBE;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_stream_tube_run_state_accept state = {
      NULL /* loop */, error,
    out_address,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Accept", iface,
      _tp_cli_channel_type_stream_tube_finish_running_accept,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Accept",
          _tp_cli_channel_type_stream_tube_collect_callback_accept,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_address_type,
              G_TYPE_UINT, in_access_control,
              G_TYPE_VALUE, in_access_control_param,
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
tp_cli_add_signals_for_channel_type_streamed_media (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "StreamAdded",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "StreamDirectionChanged",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "StreamError",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "StreamRemoved",
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "StreamStateChanged",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_type_streamed_media_signal_callback_stream_added:
 * @proxy: The proxy on which tp_cli_channel_type_streamed_media_connect_to_stream_added ()
 *  was called
 * @arg_Stream_ID: The stream identifier (as defined in           &lt;tp:member-ref&gt;ListStreams&lt;/tp:member-ref&gt;)
 * @arg_Contact_Handle: The contact handle who the stream is with (or 0 if it           represents more than a single member)
 * @arg_Stream_Type: The stream type (a value from MediaStreamType)
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal StreamAdded.
 */
static void
_tp_cli_channel_type_streamed_media_collect_args_of_stream_added (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Stream_ID,
    guint arg_Contact_Handle,
    guint arg_Stream_Type,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (3);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 3; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, arg_Stream_ID);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Contact_Handle);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, G_TYPE_UINT);
  g_value_set_uint (args->values + 2, arg_Stream_Type);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_streamed_media_invoke_callback_for_stream_added (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_streamed_media_signal_callback_stream_added callback =
      (tp_cli_channel_type_streamed_media_signal_callback_stream_added) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      g_value_get_uint (args->values + 1),
      g_value_get_uint (args->values + 2),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_streamed_media_connect_to_stream_added:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal StreamAdded.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Emitted when a new stream has been added to this channel.           Clients SHOULD assume that the stream&apos;s           &lt;tp:type&gt;Media_Stream_State&lt;/tp:type&gt; is initially Disconnected.&lt;/p&gt;          &lt;p&gt;If a connection manager needs to represent the addition of a stream           whose state is already Connecting or Connected, it MUST do this           by emitting StreamAdded, closely followed by           &lt;tp:member-ref&gt;StreamStateChanged&lt;/tp:member-ref&gt; indicating a           change to the appropriate state.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;Historically, it was not clear from the StreamAdded signal what             the state of the stream was. telepathy-spec 0.17.22             clarified this.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;Similarly, clients SHOULD assume that the initial           &lt;tp:type&gt;Media_Stream_Direction&lt;/tp:type&gt; of a newly added stream           is Receive, and that the initial           &lt;tp:type&gt;Media_Stream_Pending_Send&lt;/tp:type&gt; is           Pending_Local_Send.&lt;/p&gt;          &lt;p&gt;If a connection manager needs to represent the addition of a stream           whose direction or pending-send differs from those initial values,           it MUST do so by emitting StreamAdded, closely followed by           &lt;tp:member-ref&gt;StreamDirectionChanged&lt;/tp:member-ref&gt; indicating a           change to the appropriate direction and pending-send state.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;StreamAdded doesn&apos;t itself indicate the stream&apos;s direction; this             is unfortunate, but is preserved for compatibility.&lt;/p&gt;            &lt;p&gt;This is the appropriate direction for streams added by a remote             contact on existing connection managers, and does not violate             user privacy by automatically sending audio or video (audio streams             start off muted, video streams start off not sending). For             streams added by the local user using the client receiving the             signal, the true direction can also be determined from the return             value of the &lt;tp:member-ref&gt;RequestStreams&lt;/tp:member-ref&gt;             method.&lt;/p&gt;            &lt;p&gt;Existing clients typically operate by maintaining a separate             idea of the directions that they would like the streams to have,             and enforcing these intended directions by calling             &lt;tp:member-ref&gt;RequestStreamDirection&lt;/tp:member-ref&gt; whenever             needed.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_streamed_media_connect_to_stream_added (TpChannel *proxy,
    tp_cli_channel_type_streamed_media_signal_callback_stream_added callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[4] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_STREAMED_MEDIA, "StreamAdded",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_streamed_media_collect_args_of_stream_added),
      _tp_cli_channel_type_streamed_media_invoke_callback_for_stream_added,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_streamed_media_signal_callback_stream_direction_changed:
 * @proxy: The proxy on which tp_cli_channel_type_streamed_media_connect_to_stream_direction_changed ()
 *  was called
 * @arg_Stream_ID: The stream identifier (as defined in &lt;tp:member-ref&gt;ListStreams&lt;/tp:member-ref&gt;)
 * @arg_Stream_Direction: The new stream direction (as defined in ListStreams)
 * @arg_Pending_Flags: The new pending send flags (as defined in ListStreams)
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal StreamDirectionChanged.
 */
static void
_tp_cli_channel_type_streamed_media_collect_args_of_stream_direction_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Stream_ID,
    guint arg_Stream_Direction,
    guint arg_Pending_Flags,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (3);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 3; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, arg_Stream_ID);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Stream_Direction);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, G_TYPE_UINT);
  g_value_set_uint (args->values + 2, arg_Pending_Flags);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_streamed_media_invoke_callback_for_stream_direction_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_streamed_media_signal_callback_stream_direction_changed callback =
      (tp_cli_channel_type_streamed_media_signal_callback_stream_direction_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      g_value_get_uint (args->values + 1),
      g_value_get_uint (args->values + 2),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_streamed_media_connect_to_stream_direction_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal StreamDirectionChanged.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Emitted when the direction or pending flags of a stream are           changed.&lt;/p&gt;          &lt;p&gt;If the MEDIA_STREAM_PENDING_LOCAL_SEND flag is set, the remote user           has requested that we begin sending on this stream.           &lt;tp:member-ref&gt;RequestStreamDirection&lt;/tp:member-ref&gt;           should be called to indicate whether or not this change is           acceptable.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;This allows for a MSN-style user interface, &amp;quot;Fred has asked you             to enable your webcam. (Accept | Reject)&amp;quot;, if desired.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_streamed_media_connect_to_stream_direction_changed (TpChannel *proxy,
    tp_cli_channel_type_streamed_media_signal_callback_stream_direction_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[4] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_STREAMED_MEDIA, "StreamDirectionChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_streamed_media_collect_args_of_stream_direction_changed),
      _tp_cli_channel_type_streamed_media_invoke_callback_for_stream_direction_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_streamed_media_signal_callback_stream_error:
 * @proxy: The proxy on which tp_cli_channel_type_streamed_media_connect_to_stream_error ()
 *  was called
 * @arg_Stream_ID: The stream identifier (as defined in         &lt;tp:member-ref&gt;ListStreams&lt;/tp:member-ref&gt;)
 * @arg_Error_Code: A stream error number, one of the values of MediaStreamError
 * @arg_Message: A string describing the error (for debugging purposes only)
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal StreamError.
 */
static void
_tp_cli_channel_type_streamed_media_collect_args_of_stream_error (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Stream_ID,
    guint arg_Error_Code,
    const gchar *arg_Message,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (3);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 3; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, arg_Stream_ID);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Error_Code);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, G_TYPE_STRING);
  g_value_set_string (args->values + 2, arg_Message);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_streamed_media_invoke_callback_for_stream_error (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_streamed_media_signal_callback_stream_error callback =
      (tp_cli_channel_type_streamed_media_signal_callback_stream_error) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      g_value_get_uint (args->values + 1),
      g_value_get_string (args->values + 2),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_streamed_media_connect_to_stream_error:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal StreamError.
 *
 * Emitted when a stream encounters an error.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_streamed_media_connect_to_stream_error (TpChannel *proxy,
    tp_cli_channel_type_streamed_media_signal_callback_stream_error callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[4] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_STREAMED_MEDIA, "StreamError",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_streamed_media_collect_args_of_stream_error),
      _tp_cli_channel_type_streamed_media_invoke_callback_for_stream_error,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_streamed_media_signal_callback_stream_removed:
 * @proxy: The proxy on which tp_cli_channel_type_streamed_media_connect_to_stream_removed ()
 *  was called
 * @arg_Stream_ID: stream_id - the stream identifier (as defined in         &lt;tp:member-ref&gt;ListStreams&lt;/tp:member-ref&gt;)
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal StreamRemoved.
 */
static void
_tp_cli_channel_type_streamed_media_collect_args_of_stream_removed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Stream_ID,
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
  g_value_set_uint (args->values + 0, arg_Stream_ID);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_streamed_media_invoke_callback_for_stream_removed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_streamed_media_signal_callback_stream_removed callback =
      (tp_cli_channel_type_streamed_media_signal_callback_stream_removed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_streamed_media_connect_to_stream_removed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal StreamRemoved.
 *
 * Emitted when a stream has been removed from this channel.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_streamed_media_connect_to_stream_removed (TpChannel *proxy,
    tp_cli_channel_type_streamed_media_signal_callback_stream_removed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_STREAMED_MEDIA, "StreamRemoved",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_streamed_media_collect_args_of_stream_removed),
      _tp_cli_channel_type_streamed_media_invoke_callback_for_stream_removed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_streamed_media_signal_callback_stream_state_changed:
 * @proxy: The proxy on which tp_cli_channel_type_streamed_media_connect_to_stream_state_changed ()
 *  was called
 * @arg_Stream_ID: The stream identifier (as defined in           &lt;tp:member-ref&gt;ListStreams&lt;/tp:member-ref&gt;)
 * @arg_Stream_State: The new stream state (as defined in ListStreams)
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal StreamStateChanged.
 */
static void
_tp_cli_channel_type_streamed_media_collect_args_of_stream_state_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Stream_ID,
    guint arg_Stream_State,
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
  g_value_set_uint (args->values + 0, arg_Stream_ID);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Stream_State);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_streamed_media_invoke_callback_for_stream_state_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_streamed_media_signal_callback_stream_state_changed callback =
      (tp_cli_channel_type_streamed_media_signal_callback_stream_state_changed) generic_callback;

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
 * tp_cli_channel_type_streamed_media_connect_to_stream_state_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal StreamStateChanged.
 *
 * Emitted when a member&apos;s stream&apos;s state changes.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_streamed_media_connect_to_stream_state_changed (TpChannel *proxy,
    tp_cli_channel_type_streamed_media_signal_callback_stream_state_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_STREAMED_MEDIA, "StreamStateChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_streamed_media_collect_args_of_stream_state_changed),
      _tp_cli_channel_type_streamed_media_invoke_callback_for_stream_state_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_streamed_media_callback_for_list_streams:
 * @proxy: the proxy on which the call was made
 * @out_Streams: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structs containing:           &lt;ul&gt;           &lt;li&gt;the stream identifier&lt;/li&gt;           &lt;li&gt;the contact handle who the stream is with (or 0 if the stream             represents more than a single member)&lt;/li&gt;           &lt;li&gt;the type of the stream&lt;/li&gt;           &lt;li&gt;the current stream state&lt;/li&gt;           &lt;li&gt;the current direction of the stream&lt;/li&gt;           &lt;li&gt;the current pending send flags&lt;/li&gt;           &lt;/ul&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a ListStreams method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_streamed_media_collect_callback_list_streams (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GPtrArray *out_Streams;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))), &out_Streams,
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
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Streams);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_streamed_media_invoke_callback_list_streams (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_streamed_media_callback_for_list_streams callback = (tp_cli_channel_type_streamed_media_callback_for_list_streams) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_streamed_media_call_list_streams:
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
 * Start a ListStreams method call.
 *
 * Returns an array of structs representing the streams currently active         within this channel. Each stream is identified by an unsigned integer         which is unique for each stream within the channel.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_streamed_media_call_list_streams (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_streamed_media_callback_for_list_streams callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_STREAMED_MEDIA;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "ListStreams",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "ListStreams", iface,
          _tp_cli_channel_type_streamed_media_invoke_callback_list_streams,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "ListStreams",
              _tp_cli_channel_type_streamed_media_collect_callback_list_streams,
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
    GPtrArray **out_Streams;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_streamed_media_run_state_list_streams;
static void
_tp_cli_channel_type_streamed_media_finish_running_list_streams (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_streamed_media_run_state_list_streams *state = user_data;

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

  if (state->out_Streams != NULL)
    *state->out_Streams = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_streamed_media_run_list_streams:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Streams: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structs containing:           &lt;ul&gt;           &lt;li&gt;the stream identifier&lt;/li&gt;           &lt;li&gt;the contact handle who the stream is with (or 0 if the stream             represents more than a single member)&lt;/li&gt;           &lt;li&gt;the type of the stream&lt;/li&gt;           &lt;li&gt;the current stream state&lt;/li&gt;           &lt;li&gt;the current direction of the stream&lt;/li&gt;           &lt;li&gt;the current pending send flags&lt;/li&gt;           &lt;/ul&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method ListStreams and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns an array of structs representing the streams currently active         within this channel. Each stream is identified by an unsigned integer         which is unique for each stream within the channel.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_streamed_media_run_list_streams (TpChannel *proxy,
    gint timeout_ms,
    GPtrArray **out_Streams,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_STREAMED_MEDIA;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_streamed_media_run_state_list_streams state = {
      NULL /* loop */, error,
    out_Streams,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "ListStreams", iface,
      _tp_cli_channel_type_streamed_media_finish_running_list_streams,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "ListStreams",
          _tp_cli_channel_type_streamed_media_collect_callback_list_streams,
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
 * tp_cli_channel_type_streamed_media_callback_for_remove_streams:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RemoveStreams method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_streamed_media_collect_callback_remove_streams (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_type_streamed_media_invoke_callback_remove_streams (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_streamed_media_callback_for_remove_streams callback = (tp_cli_channel_type_streamed_media_callback_for_remove_streams) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_type_streamed_media_call_remove_streams:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Streams: Used to pass an 'in' argument: An array of stream identifiers (as defined in           &lt;tp:member-ref&gt;ListStreams&lt;/tp:member-ref&gt;)
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
 * Start a RemoveStreams method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that the given streams are removed. If all streams are           removed, the channel MAY close.&lt;/p&gt;          &lt;p&gt;Clients SHOULD NOT attempt to terminate calls by removing all the           streams; instead, clients SHOULD terminate calls by removing the           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface&quot;&gt;Group.SelfHandle&lt;/tp:dbus-ref&gt;           from the channel, using either           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface.Group&quot;&gt;RemoveMembers&lt;/tp:dbus-ref&gt;           or           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface.Group&quot;&gt;RemoveMembersWithReason&lt;/tp:dbus-ref&gt;.           &lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_streamed_media_call_remove_streams (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Streams,
    tp_cli_channel_type_streamed_media_callback_for_remove_streams callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_STREAMED_MEDIA;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "RemoveStreams",
          DBUS_TYPE_G_UINT_ARRAY, in_Streams,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RemoveStreams", iface,
          _tp_cli_channel_type_streamed_media_invoke_callback_remove_streams,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RemoveStreams",
              _tp_cli_channel_type_streamed_media_collect_callback_remove_streams,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Streams,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_streamed_media_run_state_remove_streams;
static void
_tp_cli_channel_type_streamed_media_finish_running_remove_streams (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_streamed_media_run_state_remove_streams *state = user_data;

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
 * tp_cli_channel_type_streamed_media_run_remove_streams:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Streams: Used to pass an 'in' argument: An array of stream identifiers (as defined in           &lt;tp:member-ref&gt;ListStreams&lt;/tp:member-ref&gt;)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RemoveStreams and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that the given streams are removed. If all streams are           removed, the channel MAY close.&lt;/p&gt;          &lt;p&gt;Clients SHOULD NOT attempt to terminate calls by removing all the           streams; instead, clients SHOULD terminate calls by removing the           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface&quot;&gt;Group.SelfHandle&lt;/tp:dbus-ref&gt;           from the channel, using either           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface.Group&quot;&gt;RemoveMembers&lt;/tp:dbus-ref&gt;           or           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface.Group&quot;&gt;RemoveMembersWithReason&lt;/tp:dbus-ref&gt;.           &lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_streamed_media_run_remove_streams (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_Streams,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_STREAMED_MEDIA;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_streamed_media_run_state_remove_streams state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RemoveStreams", iface,
      _tp_cli_channel_type_streamed_media_finish_running_remove_streams,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RemoveStreams",
          _tp_cli_channel_type_streamed_media_collect_callback_remove_streams,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Streams,
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
 * tp_cli_channel_type_streamed_media_callback_for_request_stream_direction:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RequestStreamDirection method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_streamed_media_collect_callback_request_stream_direction (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_type_streamed_media_invoke_callback_request_stream_direction (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_streamed_media_callback_for_request_stream_direction callback = (tp_cli_channel_type_streamed_media_callback_for_request_stream_direction) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_type_streamed_media_call_request_stream_direction:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Stream_ID: Used to pass an 'in' argument: The stream identifier (as defined in           &lt;tp:member-ref&gt;ListStreams&lt;/tp:member-ref&gt;)
 * @in_Stream_Direction: Used to pass an 'in' argument: The desired stream direction (a value of MediaStreamDirection)
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
 * Start a RequestStreamDirection method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request a change in the direction of an existing stream. In particular,         this might be useful to stop sending media of a particular type,         or inform the peer that you are no longer using media that is being         sent to you.&lt;/p&gt;          &lt;p&gt;Depending on the protocol, streams which are no longer sending in         either direction should be removed and a         &lt;tp:member-ref&gt;StreamRemoved&lt;/tp:member-ref&gt; signal emitted.         Some direction changes can be enforced locally (for example,         BIDIRECTIONAL -&amp;gt; RECEIVE can be achieved by merely stopping sending),         others may not be possible on some protocols, and some need agreement         from the remote end. In this case, the MEDIA_STREAM_PENDING_REMOTE_SEND         flag will be set in the         &lt;tp:member-ref&gt;StreamDirectionChanged&lt;/tp:member-ref&gt; signal, and the         signal         emitted again without the flag to indicate the resulting direction when         the remote end has accepted or rejected the change.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_streamed_media_call_request_stream_direction (TpChannel *proxy,
    gint timeout_ms,
    guint in_Stream_ID,
    guint in_Stream_Direction,
    tp_cli_channel_type_streamed_media_callback_for_request_stream_direction callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_STREAMED_MEDIA;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "RequestStreamDirection",
          G_TYPE_UINT, in_Stream_ID,
          G_TYPE_UINT, in_Stream_Direction,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RequestStreamDirection", iface,
          _tp_cli_channel_type_streamed_media_invoke_callback_request_stream_direction,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RequestStreamDirection",
              _tp_cli_channel_type_streamed_media_collect_callback_request_stream_direction,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Stream_ID,
              G_TYPE_UINT, in_Stream_Direction,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_streamed_media_run_state_request_stream_direction;
static void
_tp_cli_channel_type_streamed_media_finish_running_request_stream_direction (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_streamed_media_run_state_request_stream_direction *state = user_data;

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
 * tp_cli_channel_type_streamed_media_run_request_stream_direction:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Stream_ID: Used to pass an 'in' argument: The stream identifier (as defined in           &lt;tp:member-ref&gt;ListStreams&lt;/tp:member-ref&gt;)
 * @in_Stream_Direction: Used to pass an 'in' argument: The desired stream direction (a value of MediaStreamDirection)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RequestStreamDirection and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request a change in the direction of an existing stream. In particular,         this might be useful to stop sending media of a particular type,         or inform the peer that you are no longer using media that is being         sent to you.&lt;/p&gt;          &lt;p&gt;Depending on the protocol, streams which are no longer sending in         either direction should be removed and a         &lt;tp:member-ref&gt;StreamRemoved&lt;/tp:member-ref&gt; signal emitted.         Some direction changes can be enforced locally (for example,         BIDIRECTIONAL -&amp;gt; RECEIVE can be achieved by merely stopping sending),         others may not be possible on some protocols, and some need agreement         from the remote end. In this case, the MEDIA_STREAM_PENDING_REMOTE_SEND         flag will be set in the         &lt;tp:member-ref&gt;StreamDirectionChanged&lt;/tp:member-ref&gt; signal, and the         signal         emitted again without the flag to indicate the resulting direction when         the remote end has accepted or rejected the change.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_streamed_media_run_request_stream_direction (TpChannel *proxy,
    gint timeout_ms,
    guint in_Stream_ID,
    guint in_Stream_Direction,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_STREAMED_MEDIA;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_streamed_media_run_state_request_stream_direction state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RequestStreamDirection", iface,
      _tp_cli_channel_type_streamed_media_finish_running_request_stream_direction,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RequestStreamDirection",
          _tp_cli_channel_type_streamed_media_collect_callback_request_stream_direction,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Stream_ID,
              G_TYPE_UINT, in_Stream_Direction,
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
 * tp_cli_channel_type_streamed_media_callback_for_request_streams:
 * @proxy: the proxy on which the call was made
 * @out_Streams: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structs (in the same order as the given stream types)           containing:           &lt;ul&gt;             &lt;li&gt;the stream identifier&lt;/li&gt;             &lt;li&gt;the contact handle who the stream is with (or 0 if the stream               represents more than a single member)&lt;/li&gt;             &lt;li&gt;the type of the stream&lt;/li&gt;             &lt;li&gt;the current stream state&lt;/li&gt;             &lt;li&gt;the current direction of the stream&lt;/li&gt;             &lt;li&gt;the current pending send flags&lt;/li&gt;           &lt;/ul&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RequestStreams method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_streamed_media_collect_callback_request_streams (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GPtrArray *out_Streams;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))), &out_Streams,
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
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Streams);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_streamed_media_invoke_callback_request_streams (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_streamed_media_callback_for_request_streams callback = (tp_cli_channel_type_streamed_media_callback_for_request_streams) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_streamed_media_call_request_streams:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Contact_Handle: Used to pass an 'in' argument: A contact handle with whom to establish the streams
 * @in_Types: Used to pass an 'in' argument: An array of stream types (values of MediaStreamType)
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
 * Start a RequestStreams method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that streams be established to exchange the given types of         media with the given member. In general this will try and establish a         bidirectional stream, but on some protocols it may not be possible to         indicate to the peer that you would like to receive media, so a         send-only stream will be created initially. In the cases where the         stream requires remote agreement (eg you wish to receive media from         them), the &lt;tp:member-ref&gt;StreamDirectionChanged&lt;/tp:member-ref&gt; signal         will be emitted with the         MEDIA_STREAM_PENDING_REMOTE_SEND flag set, and the signal emitted again         with the flag cleared when the remote end has replied.&lt;/p&gt;          &lt;p&gt;If streams of the requested types already exist, calling this           method results in the creation of additional streams. Accordingly,           clients wishing to have exactly one audio stream or exactly one           video stream SHOULD check for the current streams using           &lt;tp:member-ref&gt;ListStreams&lt;/tp:member-ref&gt; before calling this           method.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_streamed_media_call_request_streams (TpChannel *proxy,
    gint timeout_ms,
    guint in_Contact_Handle,
    const GArray *in_Types,
    tp_cli_channel_type_streamed_media_callback_for_request_streams callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_STREAMED_MEDIA;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "RequestStreams",
          G_TYPE_UINT, in_Contact_Handle,
          DBUS_TYPE_G_UINT_ARRAY, in_Types,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RequestStreams", iface,
          _tp_cli_channel_type_streamed_media_invoke_callback_request_streams,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RequestStreams",
              _tp_cli_channel_type_streamed_media_collect_callback_request_streams,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Contact_Handle,
              DBUS_TYPE_G_UINT_ARRAY, in_Types,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GPtrArray **out_Streams;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_streamed_media_run_state_request_streams;
static void
_tp_cli_channel_type_streamed_media_finish_running_request_streams (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_streamed_media_run_state_request_streams *state = user_data;

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

  if (state->out_Streams != NULL)
    *state->out_Streams = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_streamed_media_run_request_streams:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Contact_Handle: Used to pass an 'in' argument: A contact handle with whom to establish the streams
 * @in_Types: Used to pass an 'in' argument: An array of stream types (values of MediaStreamType)
 * @out_Streams: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structs (in the same order as the given stream types)           containing:           &lt;ul&gt;             &lt;li&gt;the stream identifier&lt;/li&gt;             &lt;li&gt;the contact handle who the stream is with (or 0 if the stream               represents more than a single member)&lt;/li&gt;             &lt;li&gt;the type of the stream&lt;/li&gt;             &lt;li&gt;the current stream state&lt;/li&gt;             &lt;li&gt;the current direction of the stream&lt;/li&gt;             &lt;li&gt;the current pending send flags&lt;/li&gt;           &lt;/ul&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RequestStreams and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that streams be established to exchange the given types of         media with the given member. In general this will try and establish a         bidirectional stream, but on some protocols it may not be possible to         indicate to the peer that you would like to receive media, so a         send-only stream will be created initially. In the cases where the         stream requires remote agreement (eg you wish to receive media from         them), the &lt;tp:member-ref&gt;StreamDirectionChanged&lt;/tp:member-ref&gt; signal         will be emitted with the         MEDIA_STREAM_PENDING_REMOTE_SEND flag set, and the signal emitted again         with the flag cleared when the remote end has replied.&lt;/p&gt;          &lt;p&gt;If streams of the requested types already exist, calling this           method results in the creation of additional streams. Accordingly,           clients wishing to have exactly one audio stream or exactly one           video stream SHOULD check for the current streams using           &lt;tp:member-ref&gt;ListStreams&lt;/tp:member-ref&gt; before calling this           method.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_streamed_media_run_request_streams (TpChannel *proxy,
    gint timeout_ms,
    guint in_Contact_Handle,
    const GArray *in_Types,
    GPtrArray **out_Streams,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_STREAMED_MEDIA;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_streamed_media_run_state_request_streams state = {
      NULL /* loop */, error,
    out_Streams,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RequestStreams", iface,
      _tp_cli_channel_type_streamed_media_finish_running_request_streams,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RequestStreams",
          _tp_cli_channel_type_streamed_media_collect_callback_request_streams,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Contact_Handle,
              DBUS_TYPE_G_UINT_ARRAY, in_Types,
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
tp_cli_add_signals_for_channel_type_text (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "LostMessage",
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "Received",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "SendError",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "Sent",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_type_text_signal_callback_lost_message:
 * @proxy: The proxy on which tp_cli_channel_type_text_connect_to_lost_message ()
 *  was called
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal LostMessage.
 */
static void
_tp_cli_channel_type_text_invoke_callback_for_lost_message (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_text_signal_callback_lost_message callback =
      (tp_cli_channel_type_text_signal_callback_lost_message) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      user_data,
      weak_object);

  if (args != NULL)
    g_value_array_free (args);

  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_text_connect_to_lost_message:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal LostMessage.
 *
 * This signal is emitted to indicate that an incoming message was         not able to be stored and forwarded by the connection manager         due to lack of memory.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_text_connect_to_lost_message (TpChannel *proxy,
    tp_cli_channel_type_text_signal_callback_lost_message callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[1] = {
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_TEXT, "LostMessage",
      expected_types,
      NULL, /* no args => no collector function */
      _tp_cli_channel_type_text_invoke_callback_for_lost_message,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_text_signal_callback_received:
 * @proxy: The proxy on which tp_cli_channel_type_text_connect_to_received ()
 *  was called
 * @arg_ID: A numeric identifier for acknowledging the message
 * @arg_Timestamp: A Unix timestamp indicating when the message was received
 * @arg_Sender: The handle of the contact who sent the message
 * @arg_Type: The type of the message (normal, action, notice, etc.)
 * @arg_Flags: A bitwise OR of the message flags
 * @arg_Text: The text of the message
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal Received.
 */
static void
_tp_cli_channel_type_text_collect_args_of_received (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_ID,
    guint arg_Timestamp,
    guint arg_Sender,
    guint arg_Type,
    guint arg_Flags,
    const gchar *arg_Text,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (6);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 6; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, arg_ID);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Timestamp);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, G_TYPE_UINT);
  g_value_set_uint (args->values + 2, arg_Sender);

  g_value_unset (args->values + 3);
  g_value_init (args->values + 3, G_TYPE_UINT);
  g_value_set_uint (args->values + 3, arg_Type);

  g_value_unset (args->values + 4);
  g_value_init (args->values + 4, G_TYPE_UINT);
  g_value_set_uint (args->values + 4, arg_Flags);

  g_value_unset (args->values + 5);
  g_value_init (args->values + 5, G_TYPE_STRING);
  g_value_set_string (args->values + 5, arg_Text);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_text_invoke_callback_for_received (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_text_signal_callback_received callback =
      (tp_cli_channel_type_text_signal_callback_received) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      g_value_get_uint (args->values + 1),
      g_value_get_uint (args->values + 2),
      g_value_get_uint (args->values + 3),
      g_value_get_uint (args->values + 4),
      g_value_get_string (args->values + 5),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_text_connect_to_received:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal Received.
 *
 * Signals that a message with the given id, timestamp, sender, type         and text has been received on this channel. Applications that catch         this signal and reliably inform the user of the message should         acknowledge that they have dealt with the message with the         &lt;tp:member-ref&gt;AcknowledgePendingMessages&lt;/tp:member-ref&gt; method.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_text_connect_to_received (TpChannel *proxy,
    tp_cli_channel_type_text_signal_callback_received callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[7] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_TEXT, "Received",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_text_collect_args_of_received),
      _tp_cli_channel_type_text_invoke_callback_for_received,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_text_signal_callback_send_error:
 * @proxy: The proxy on which tp_cli_channel_type_text_connect_to_send_error ()
 *  was called
 * @arg_Error: The error that occurred
 * @arg_Timestamp: The Unix timestamp indicating when the message was sent
 * @arg_Type: The message type
 * @arg_Text: The text of the message
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal SendError.
 */
static void
_tp_cli_channel_type_text_collect_args_of_send_error (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Error,
    guint arg_Timestamp,
    guint arg_Type,
    const gchar *arg_Text,
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
  g_value_set_uint (args->values + 0, arg_Error);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Timestamp);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, G_TYPE_UINT);
  g_value_set_uint (args->values + 2, arg_Type);

  g_value_unset (args->values + 3);
  g_value_init (args->values + 3, G_TYPE_STRING);
  g_value_set_string (args->values + 3, arg_Text);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_text_invoke_callback_for_send_error (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_text_signal_callback_send_error callback =
      (tp_cli_channel_type_text_signal_callback_send_error) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      g_value_get_uint (args->values + 1),
      g_value_get_uint (args->values + 2),
      g_value_get_string (args->values + 3),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_text_connect_to_send_error:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal SendError.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Signals that an outgoing message has failed to send. The error           will be one of the values from ChannelTextSendError.&lt;/p&gt;          &lt;p&gt;This signal should only be emitted for messages for which           &lt;tp:member-ref&gt;Sent&lt;/tp:member-ref&gt; has already been emitted and           &lt;tp:member-ref&gt;Send&lt;/tp:member-ref&gt; has already returned success.&lt;/p&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_text_connect_to_send_error (TpChannel *proxy,
    tp_cli_channel_type_text_signal_callback_send_error callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[5] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_TEXT, "SendError",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_text_collect_args_of_send_error),
      _tp_cli_channel_type_text_invoke_callback_for_send_error,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_text_signal_callback_sent:
 * @proxy: The proxy on which tp_cli_channel_type_text_connect_to_sent ()
 *  was called
 * @arg_Timestamp: Unix timestamp indicating when the message was sent
 * @arg_Type: The message type (normal, action, notice, etc) from           ChannelTextMessageType
 * @arg_Text: The text of the message. If the message was, or will be, altered           during transmission, this argument SHOULD reflect what other           contacts will receive rather than being a copy of the argument           to &lt;tp:member-ref&gt;Send&lt;/tp:member-ref&gt;.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal Sent.
 */
static void
_tp_cli_channel_type_text_collect_args_of_sent (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_Timestamp,
    guint arg_Type,
    const gchar *arg_Text,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (3);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 3; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, arg_Timestamp);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Type);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, G_TYPE_STRING);
  g_value_set_string (args->values + 2, arg_Text);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_text_invoke_callback_for_sent (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_text_signal_callback_sent callback =
      (tp_cli_channel_type_text_signal_callback_sent) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      g_value_get_uint (args->values + 1),
      g_value_get_string (args->values + 2),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_text_connect_to_sent:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal Sent.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Signals that a message has been submitted for sending.&lt;/p&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_text_connect_to_sent (TpChannel *proxy,
    tp_cli_channel_type_text_signal_callback_sent callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[4] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_TEXT, "Sent",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_text_collect_args_of_sent),
      _tp_cli_channel_type_text_invoke_callback_for_sent,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_text_callback_for_acknowledge_pending_messages:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a AcknowledgePendingMessages method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_text_collect_callback_acknowledge_pending_messages (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_type_text_invoke_callback_acknowledge_pending_messages (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_text_callback_for_acknowledge_pending_messages callback = (tp_cli_channel_type_text_callback_for_acknowledge_pending_messages) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_type_text_call_acknowledge_pending_messages:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_IDs: Used to pass an 'in' argument: The IDs of the messages to acknowledge
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
 * Start a AcknowledgePendingMessages method call.
 *
 * Inform the channel that you have handled messages by displaying them to         the user (or equivalent), so they can be removed from the pending queue.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_text_call_acknowledge_pending_messages (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_IDs,
    tp_cli_channel_type_text_callback_for_acknowledge_pending_messages callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TEXT;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "AcknowledgePendingMessages",
          DBUS_TYPE_G_UINT_ARRAY, in_IDs,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "AcknowledgePendingMessages", iface,
          _tp_cli_channel_type_text_invoke_callback_acknowledge_pending_messages,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "AcknowledgePendingMessages",
              _tp_cli_channel_type_text_collect_callback_acknowledge_pending_messages,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_IDs,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_text_run_state_acknowledge_pending_messages;
static void
_tp_cli_channel_type_text_finish_running_acknowledge_pending_messages (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_text_run_state_acknowledge_pending_messages *state = user_data;

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
 * tp_cli_channel_type_text_run_acknowledge_pending_messages:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_IDs: Used to pass an 'in' argument: The IDs of the messages to acknowledge
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method AcknowledgePendingMessages and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Inform the channel that you have handled messages by displaying them to         the user (or equivalent), so they can be removed from the pending queue.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_text_run_acknowledge_pending_messages (TpChannel *proxy,
    gint timeout_ms,
    const GArray *in_IDs,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TEXT;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_text_run_state_acknowledge_pending_messages state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "AcknowledgePendingMessages", iface,
      _tp_cli_channel_type_text_finish_running_acknowledge_pending_messages,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "AcknowledgePendingMessages",
          _tp_cli_channel_type_text_collect_callback_acknowledge_pending_messages,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_IDs,
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
 * tp_cli_channel_type_text_callback_for_get_message_types:
 * @proxy: the proxy on which the call was made
 * @out_Available_Types: Used to return an 'out' argument if @error is %NULL: An array of integer message types (ChannelTextMessageType)
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetMessageTypes method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_text_collect_callback_get_message_types (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GArray *out_Available_Types;

  dbus_g_proxy_end_call (proxy, call, &error,
      DBUS_TYPE_G_UINT_ARRAY, &out_Available_Types,
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
  g_value_take_boxed (args->values + 0, out_Available_Types);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_text_invoke_callback_get_message_types (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_text_callback_for_get_message_types callback = (tp_cli_channel_type_text_callback_for_get_message_types) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_text_call_get_message_types:
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
 * Start a GetMessageTypes method call.
 *
 * Return an array indicating which types of message may be sent on this         channel.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_text_call_get_message_types (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_text_callback_for_get_message_types callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TEXT;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetMessageTypes",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetMessageTypes", iface,
          _tp_cli_channel_type_text_invoke_callback_get_message_types,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetMessageTypes",
              _tp_cli_channel_type_text_collect_callback_get_message_types,
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
    GArray **out_Available_Types;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_text_run_state_get_message_types;
static void
_tp_cli_channel_type_text_finish_running_get_message_types (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_text_run_state_get_message_types *state = user_data;

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

  if (state->out_Available_Types != NULL)
    *state->out_Available_Types = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_text_run_get_message_types:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Available_Types: Used to return an 'out' argument if %TRUE is returned: An array of integer message types (ChannelTextMessageType)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetMessageTypes and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Return an array indicating which types of message may be sent on this         channel.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_text_run_get_message_types (TpChannel *proxy,
    gint timeout_ms,
    GArray **out_Available_Types,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TEXT;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_text_run_state_get_message_types state = {
      NULL /* loop */, error,
    out_Available_Types,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetMessageTypes", iface,
      _tp_cli_channel_type_text_finish_running_get_message_types,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetMessageTypes",
          _tp_cli_channel_type_text_collect_callback_get_message_types,
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
 * tp_cli_channel_type_text_callback_for_list_pending_messages:
 * @proxy: the proxy on which the call was made
 * @out_Pending_Messages: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structs representing the pending queue. Each contains:           &lt;ul&gt;             &lt;li&gt;a numeric identifier&lt;/li&gt;             &lt;li&gt;a Unix timestamp indicating when the message was received&lt;/li&gt;             &lt;li&gt;the contact handle for the contact who sent the message&lt;/li&gt;             &lt;li&gt;the message type, taken from ChannelTextMessageType&lt;/li&gt;             &lt;li&gt;the bitwise-OR of the message flags from ChannelTextMessageFlags&lt;/li&gt;             &lt;li&gt;the text of the message&lt;/li&gt;           &lt;/ul&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a ListPendingMessages method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_text_collect_callback_list_pending_messages (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GPtrArray *out_Pending_Messages;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID)))), &out_Pending_Messages,
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
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Pending_Messages);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_text_invoke_callback_list_pending_messages (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_text_callback_for_list_pending_messages callback = (tp_cli_channel_type_text_callback_for_list_pending_messages) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_text_call_list_pending_messages:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Clear: Used to pass an 'in' argument: If true, behave as if           &lt;tp:member-ref&gt;AcknowledgePendingMessages&lt;/tp:member-ref&gt; had also           been called.
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
 * Start a ListPendingMessages method call.
 *
 * List the messages currently in the pending queue, and optionally         remove then all.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_text_call_list_pending_messages (TpChannel *proxy,
    gint timeout_ms,
    gboolean in_Clear,
    tp_cli_channel_type_text_callback_for_list_pending_messages callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TEXT;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "ListPendingMessages",
          G_TYPE_BOOLEAN, in_Clear,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "ListPendingMessages", iface,
          _tp_cli_channel_type_text_invoke_callback_list_pending_messages,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "ListPendingMessages",
              _tp_cli_channel_type_text_collect_callback_list_pending_messages,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_BOOLEAN, in_Clear,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GPtrArray **out_Pending_Messages;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_text_run_state_list_pending_messages;
static void
_tp_cli_channel_type_text_finish_running_list_pending_messages (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_text_run_state_list_pending_messages *state = user_data;

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

  if (state->out_Pending_Messages != NULL)
    *state->out_Pending_Messages = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_text_run_list_pending_messages:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Clear: Used to pass an 'in' argument: If true, behave as if           &lt;tp:member-ref&gt;AcknowledgePendingMessages&lt;/tp:member-ref&gt; had also           been called.
 * @out_Pending_Messages: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structs representing the pending queue. Each contains:           &lt;ul&gt;             &lt;li&gt;a numeric identifier&lt;/li&gt;             &lt;li&gt;a Unix timestamp indicating when the message was received&lt;/li&gt;             &lt;li&gt;the contact handle for the contact who sent the message&lt;/li&gt;             &lt;li&gt;the message type, taken from ChannelTextMessageType&lt;/li&gt;             &lt;li&gt;the bitwise-OR of the message flags from ChannelTextMessageFlags&lt;/li&gt;             &lt;li&gt;the text of the message&lt;/li&gt;           &lt;/ul&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method ListPendingMessages and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * List the messages currently in the pending queue, and optionally         remove then all.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_text_run_list_pending_messages (TpChannel *proxy,
    gint timeout_ms,
    gboolean in_Clear,
    GPtrArray **out_Pending_Messages,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TEXT;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_text_run_state_list_pending_messages state = {
      NULL /* loop */, error,
    out_Pending_Messages,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "ListPendingMessages", iface,
      _tp_cli_channel_type_text_finish_running_list_pending_messages,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "ListPendingMessages",
          _tp_cli_channel_type_text_collect_callback_list_pending_messages,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_BOOLEAN, in_Clear,
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
 * tp_cli_channel_type_text_callback_for_send:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Send method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_text_collect_callback_send (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_type_text_invoke_callback_send (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_text_callback_for_send callback = (tp_cli_channel_type_text_callback_for_send) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_type_text_call_send:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Type: Used to pass an 'in' argument: An integer indicating the type of the message
 * @in_Text: Used to pass an 'in' argument: The message to send
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
 * Start a Send method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that a message be sent on this channel. When the message has           been submitted for delivery, this method will return and the           &lt;tp:member-ref&gt;Sent&lt;/tp:member-ref&gt; signal will be emitted. If the           message cannot be submitted for delivery, the method returns an error           and no signal is emitted.&lt;/p&gt;          &lt;p&gt;This method SHOULD return before the Sent signal is           emitted.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;When a Text channel implements the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface&quot;&gt;Messages&lt;/tp:dbus-ref&gt;             interface, that &amp;quot;SHOULD&amp;quot; becomes a &amp;quot;MUST&amp;quot;.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_text_call_send (TpChannel *proxy,
    gint timeout_ms,
    guint in_Type,
    const gchar *in_Text,
    tp_cli_channel_type_text_callback_for_send callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TEXT;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Send",
          G_TYPE_UINT, in_Type,
          G_TYPE_STRING, in_Text,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Send", iface,
          _tp_cli_channel_type_text_invoke_callback_send,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Send",
              _tp_cli_channel_type_text_collect_callback_send,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Type,
              G_TYPE_STRING, in_Text,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_text_run_state_send;
static void
_tp_cli_channel_type_text_finish_running_send (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_text_run_state_send *state = user_data;

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
 * tp_cli_channel_type_text_run_send:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Type: Used to pass an 'in' argument: An integer indicating the type of the message
 * @in_Text: Used to pass an 'in' argument: The message to send
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Send and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request that a message be sent on this channel. When the message has           been submitted for delivery, this method will return and the           &lt;tp:member-ref&gt;Sent&lt;/tp:member-ref&gt; signal will be emitted. If the           message cannot be submitted for delivery, the method returns an error           and no signal is emitted.&lt;/p&gt;          &lt;p&gt;This method SHOULD return before the Sent signal is           emitted.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;When a Text channel implements the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.Interface&quot;&gt;Messages&lt;/tp:dbus-ref&gt;             interface, that &amp;quot;SHOULD&amp;quot; becomes a &amp;quot;MUST&amp;quot;.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_text_run_send (TpChannel *proxy,
    gint timeout_ms,
    guint in_Type,
    const gchar *in_Text,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TEXT;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_text_run_state_send state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Send", iface,
      _tp_cli_channel_type_text_finish_running_send,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Send",
          _tp_cli_channel_type_text_collect_callback_send,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Type,
              G_TYPE_STRING, in_Text,
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
tp_cli_add_signals_for_channel_type_tubes (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "NewTube",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)),
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "TubeStateChanged",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "TubeClosed",
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "DBusNamesChanged",
      G_TYPE_UINT,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID)))),
      DBUS_TYPE_G_UINT_ARRAY,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "StreamTubeNewConnection",
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_type_tubes_signal_callback_new_tube:
 * @proxy: The proxy on which tp_cli_channel_type_tubes_connect_to_new_tube ()
 *  was called
 * @arg_ID: The ID of the new tube.
 * @arg_Initiator: The handle of the contact who initiated the tube.
 * @arg_Type: The tube type, as defined by the Tube_Type enum.
 * @arg_Service: A string representing the service that will be used over the tube.
 * @arg_Parameters: The new tube&apos;s properties.
 * @arg_State: The new tube&apos;s state.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal NewTube.
 */
static void
_tp_cli_channel_type_tubes_collect_args_of_new_tube (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_ID,
    guint arg_Initiator,
    guint arg_Type,
    const gchar *arg_Service,
    GHashTable *arg_Parameters,
    guint arg_State,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (6);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 6; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, arg_ID);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Initiator);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, G_TYPE_UINT);
  g_value_set_uint (args->values + 2, arg_Type);

  g_value_unset (args->values + 3);
  g_value_init (args->values + 3, G_TYPE_STRING);
  g_value_set_string (args->values + 3, arg_Service);

  g_value_unset (args->values + 4);
  g_value_init (args->values + 4, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)));
  g_value_set_boxed (args->values + 4, arg_Parameters);

  g_value_unset (args->values + 5);
  g_value_init (args->values + 5, G_TYPE_UINT);
  g_value_set_uint (args->values + 5, arg_State);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_for_new_tube (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_signal_callback_new_tube callback =
      (tp_cli_channel_type_tubes_signal_callback_new_tube) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      g_value_get_uint (args->values + 1),
      g_value_get_uint (args->values + 2),
      g_value_get_string (args->values + 3),
      g_value_get_boxed (args->values + 4),
      g_value_get_uint (args->values + 5),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_tubes_connect_to_new_tube:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal NewTube.
 *
 * Emitted when a tube is created.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_tubes_connect_to_new_tube (TpChannel *proxy,
    tp_cli_channel_type_tubes_signal_callback_new_tube callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[7] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)),
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_TUBES, "NewTube",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_tubes_collect_args_of_new_tube),
      _tp_cli_channel_type_tubes_invoke_callback_for_new_tube,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_tubes_signal_callback_tube_state_changed:
 * @proxy: The proxy on which tp_cli_channel_type_tubes_connect_to_tube_state_changed ()
 *  was called
 * @arg_ID: The ID of the tube that changed state.
 * @arg_State: The new state of the tube; see the Tube_State enumeration.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal TubeStateChanged.
 */
static void
_tp_cli_channel_type_tubes_collect_args_of_tube_state_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_ID,
    guint arg_State,
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
  g_value_set_uint (args->values + 0, arg_ID);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_State);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_for_tube_state_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_signal_callback_tube_state_changed callback =
      (tp_cli_channel_type_tubes_signal_callback_tube_state_changed) generic_callback;

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
 * tp_cli_channel_type_tubes_connect_to_tube_state_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal TubeStateChanged.
 *
 * Emitted when the state of a tube changes.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_tubes_connect_to_tube_state_changed (TpChannel *proxy,
    tp_cli_channel_type_tubes_signal_callback_tube_state_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_TUBES, "TubeStateChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_tubes_collect_args_of_tube_state_changed),
      _tp_cli_channel_type_tubes_invoke_callback_for_tube_state_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_tubes_signal_callback_tube_closed:
 * @proxy: The proxy on which tp_cli_channel_type_tubes_connect_to_tube_closed ()
 *  was called
 * @arg_ID: The ID of the tube that was closed.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal TubeClosed.
 */
static void
_tp_cli_channel_type_tubes_collect_args_of_tube_closed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_ID,
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
  g_value_set_uint (args->values + 0, arg_ID);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_for_tube_closed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_signal_callback_tube_closed callback =
      (tp_cli_channel_type_tubes_signal_callback_tube_closed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_tubes_connect_to_tube_closed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal TubeClosed.
 *
 * Emitted when a tube has been closed. The ID of a closed tube is no        longer valid. The ID may later be reused for a new tube.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_tubes_connect_to_tube_closed (TpChannel *proxy,
    tp_cli_channel_type_tubes_signal_callback_tube_closed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_TUBES, "TubeClosed",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_tubes_collect_args_of_tube_closed),
      _tp_cli_channel_type_tubes_invoke_callback_for_tube_closed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_tubes_signal_callback_d_bus_names_changed:
 * @proxy: The proxy on which tp_cli_channel_type_tubes_connect_to_d_bus_names_changed ()
 *  was called
 * @arg_ID: The ID of the tube whose names have changed.
 * @arg_Added: Array of handles and D-Bus names of new participants.
 * @arg_Removed: Array of handles of former participants.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal DBusNamesChanged.
 */
static void
_tp_cli_channel_type_tubes_collect_args_of_d_bus_names_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_ID,
    const GPtrArray *arg_Added,
    const GArray *arg_Removed,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (3);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 3; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, arg_ID);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID)))));
  g_value_set_boxed (args->values + 1, arg_Added);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, DBUS_TYPE_G_UINT_ARRAY);
  g_value_set_boxed (args->values + 2, arg_Removed);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_for_d_bus_names_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_signal_callback_d_bus_names_changed callback =
      (tp_cli_channel_type_tubes_signal_callback_d_bus_names_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uint (args->values + 0),
      g_value_get_boxed (args->values + 1),
      g_value_get_boxed (args->values + 2),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_type_tubes_connect_to_d_bus_names_changed:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal DBusNamesChanged.
 *
 * Emitted on a multi-user (i.e. Handle_Type_Room) D-Bus tube when a         participant opens or closes the tube.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_tubes_connect_to_d_bus_names_changed (TpChannel *proxy,
    tp_cli_channel_type_tubes_signal_callback_d_bus_names_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[4] = {
      G_TYPE_UINT,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID)))),
      DBUS_TYPE_G_UINT_ARRAY,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_TUBES, "DBusNamesChanged",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_tubes_collect_args_of_d_bus_names_changed),
      _tp_cli_channel_type_tubes_invoke_callback_for_d_bus_names_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_tubes_signal_callback_stream_tube_new_connection:
 * @proxy: The proxy on which tp_cli_channel_type_tubes_connect_to_stream_tube_new_connection ()
 *  was called
 * @arg_ID: The ID of the tube
 * @arg_Handle: The handle of the participant who opened the new connection
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal StreamTubeNewConnection.
 */
static void
_tp_cli_channel_type_tubes_collect_args_of_stream_tube_new_connection (DBusGProxy *proxy G_GNUC_UNUSED,
    guint arg_ID,
    guint arg_Handle,
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
  g_value_set_uint (args->values + 0, arg_ID);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_UINT);
  g_value_set_uint (args->values + 1, arg_Handle);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_for_stream_tube_new_connection (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_signal_callback_stream_tube_new_connection callback =
      (tp_cli_channel_type_tubes_signal_callback_stream_tube_new_connection) generic_callback;

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
 * tp_cli_channel_type_tubes_connect_to_stream_tube_new_connection:
 * @proxy: A #TpChannel or subclass
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
 * Connect a handler to the signal StreamTubeNewConnection.
 *
 * Emitted on a stream tube when a participant opens a new connection         to its socket.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_type_tubes_connect_to_stream_tube_new_connection (TpChannel *proxy,
    tp_cli_channel_type_tubes_signal_callback_stream_tube_new_connection callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_TYPE_TUBES, "StreamTubeNewConnection",
      expected_types,
      G_CALLBACK (_tp_cli_channel_type_tubes_collect_args_of_stream_tube_new_connection),
      _tp_cli_channel_type_tubes_invoke_callback_for_stream_tube_new_connection,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_type_tubes_callback_for_get_available_stream_tube_types:
 * @proxy: the proxy on which the call was made
 * @out_Available_Stream_Tube_Types: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A mapping from address types (members of Socket_Address_Type) to           arrays of access-control type (members of Socket_Access_Control)           that the connection manager supports for stream tubes with that           address type. For simplicity, if a CM supports offering a           particular type of tube, it is assumed to support accepting it.&lt;/p&gt;            &lt;p&gt;A typical value for a host without IPv6 support:&lt;/p&gt;            &lt;pre&gt;             {               Socket_Address_Type_IPv4:                 [Socket_Access_Control_Localhost, Socket_Access_Control_Port,                  Socket_Access_Control_Netmask],               Socket_Address_Type_Unix:                 [Socket_Access_Control_Localhost, Socket_Access_Control_Credentials]             }           &lt;/pre&gt;            &lt;p&gt;If stream tubes are not supported, this will be an empty             dictionary.&lt;/p&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetAvailableStreamTubeTypes method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_tubes_collect_callback_get_available_stream_tube_types (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GHashTable *out_Available_Stream_Tube_Types;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, DBUS_TYPE_G_UINT_ARRAY)), &out_Available_Stream_Tube_Types,
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
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_UINT, DBUS_TYPE_G_UINT_ARRAY)));
  g_value_take_boxed (args->values + 0, out_Available_Stream_Tube_Types);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_get_available_stream_tube_types (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_callback_for_get_available_stream_tube_types callback = (tp_cli_channel_type_tubes_callback_for_get_available_stream_tube_types) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_call_get_available_stream_tube_types:
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
 * Start a GetAvailableStreamTubeTypes method call.
 *
 * List the available address types and access-control types         for stream tubes.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_tubes_call_get_available_stream_tube_types (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_tubes_callback_for_get_available_stream_tube_types callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetAvailableStreamTubeTypes",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetAvailableStreamTubeTypes", iface,
          _tp_cli_channel_type_tubes_invoke_callback_get_available_stream_tube_types,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetAvailableStreamTubeTypes",
              _tp_cli_channel_type_tubes_collect_callback_get_available_stream_tube_types,
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
    GHashTable **out_Available_Stream_Tube_Types;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_tubes_run_state_get_available_stream_tube_types;
static void
_tp_cli_channel_type_tubes_finish_running_get_available_stream_tube_types (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_tubes_run_state_get_available_stream_tube_types *state = user_data;

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

  if (state->out_Available_Stream_Tube_Types != NULL)
    *state->out_Available_Stream_Tube_Types = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_run_get_available_stream_tube_types:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Available_Stream_Tube_Types: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A mapping from address types (members of Socket_Address_Type) to           arrays of access-control type (members of Socket_Access_Control)           that the connection manager supports for stream tubes with that           address type. For simplicity, if a CM supports offering a           particular type of tube, it is assumed to support accepting it.&lt;/p&gt;            &lt;p&gt;A typical value for a host without IPv6 support:&lt;/p&gt;            &lt;pre&gt;             {               Socket_Address_Type_IPv4:                 [Socket_Access_Control_Localhost, Socket_Access_Control_Port,                  Socket_Access_Control_Netmask],               Socket_Address_Type_Unix:                 [Socket_Access_Control_Localhost, Socket_Access_Control_Credentials]             }           &lt;/pre&gt;            &lt;p&gt;If stream tubes are not supported, this will be an empty             dictionary.&lt;/p&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetAvailableStreamTubeTypes and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * List the available address types and access-control types         for stream tubes.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_tubes_run_get_available_stream_tube_types (TpChannel *proxy,
    gint timeout_ms,
    GHashTable **out_Available_Stream_Tube_Types,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_tubes_run_state_get_available_stream_tube_types state = {
      NULL /* loop */, error,
    out_Available_Stream_Tube_Types,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetAvailableStreamTubeTypes", iface,
      _tp_cli_channel_type_tubes_finish_running_get_available_stream_tube_types,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetAvailableStreamTubeTypes",
          _tp_cli_channel_type_tubes_collect_callback_get_available_stream_tube_types,
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
 * tp_cli_channel_type_tubes_callback_for_get_available_tube_types:
 * @proxy: the proxy on which the call was made
 * @out_Available_Tube_Types: Used to return an 'out' argument if @error is %NULL: An array of the available tube types, as defined by the Tube_Type           enum.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetAvailableTubeTypes method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_tubes_collect_callback_get_available_tube_types (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GArray *out_Available_Tube_Types;

  dbus_g_proxy_end_call (proxy, call, &error,
      DBUS_TYPE_G_UINT_ARRAY, &out_Available_Tube_Types,
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
  g_value_take_boxed (args->values + 0, out_Available_Tube_Types);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_get_available_tube_types (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_callback_for_get_available_tube_types callback = (tp_cli_channel_type_tubes_callback_for_get_available_tube_types) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_call_get_available_tube_types:
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
 * Start a GetAvailableTubeTypes method call.
 *
 * (Undocumented)
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_tubes_call_get_available_tube_types (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_tubes_callback_for_get_available_tube_types callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetAvailableTubeTypes",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetAvailableTubeTypes", iface,
          _tp_cli_channel_type_tubes_invoke_callback_get_available_tube_types,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetAvailableTubeTypes",
              _tp_cli_channel_type_tubes_collect_callback_get_available_tube_types,
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
    GArray **out_Available_Tube_Types;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_tubes_run_state_get_available_tube_types;
static void
_tp_cli_channel_type_tubes_finish_running_get_available_tube_types (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_tubes_run_state_get_available_tube_types *state = user_data;

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

  if (state->out_Available_Tube_Types != NULL)
    *state->out_Available_Tube_Types = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_run_get_available_tube_types:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Available_Tube_Types: Used to return an 'out' argument if %TRUE is returned: An array of the available tube types, as defined by the Tube_Type           enum.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetAvailableTubeTypes and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * (Undocumented)
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_tubes_run_get_available_tube_types (TpChannel *proxy,
    gint timeout_ms,
    GArray **out_Available_Tube_Types,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_tubes_run_state_get_available_tube_types state = {
      NULL /* loop */, error,
    out_Available_Tube_Types,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetAvailableTubeTypes", iface,
      _tp_cli_channel_type_tubes_finish_running_get_available_tube_types,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetAvailableTubeTypes",
          _tp_cli_channel_type_tubes_collect_callback_get_available_tube_types,
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
 * tp_cli_channel_type_tubes_callback_for_list_tubes:
 * @proxy: the proxy on which the call was made
 * @out_Tubes: Used to return an 'out' argument if @error is %NULL: Return an array of tuples, each representing a tube, with the          following members:           &lt;ul&gt;            &lt;li&gt;the tube&apos;s ID&lt;/li&gt;            &lt;li&gt;the tube&apos;s initiator&lt;/li&gt;            &lt;li&gt;the tube&apos;s type&lt;/li&gt;            &lt;li&gt;the tube&apos;s service&lt;/li&gt;            &lt;li&gt;the tube&apos;s parameters&lt;/li&gt;            &lt;li&gt;the tube&apos;s state&lt;/li&gt;          &lt;/ul&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a ListTubes method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_tubes_collect_callback_list_tubes (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GPtrArray *out_Tubes;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_UINT, G_TYPE_INVALID)))), &out_Tubes,
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
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_UINT, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Tubes);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_list_tubes (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_callback_for_list_tubes callback = (tp_cli_channel_type_tubes_callback_for_list_tubes) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_call_list_tubes:
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
 * Start a ListTubes method call.
 *
 * (Undocumented)
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_tubes_call_list_tubes (TpChannel *proxy,
    gint timeout_ms,
    tp_cli_channel_type_tubes_callback_for_list_tubes callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "ListTubes",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "ListTubes", iface,
          _tp_cli_channel_type_tubes_invoke_callback_list_tubes,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "ListTubes",
              _tp_cli_channel_type_tubes_collect_callback_list_tubes,
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
    GPtrArray **out_Tubes;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_tubes_run_state_list_tubes;
static void
_tp_cli_channel_type_tubes_finish_running_list_tubes (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_tubes_run_state_list_tubes *state = user_data;

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

  if (state->out_Tubes != NULL)
    *state->out_Tubes = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_run_list_tubes:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Tubes: Used to return an 'out' argument if %TRUE is returned: Return an array of tuples, each representing a tube, with the          following members:           &lt;ul&gt;            &lt;li&gt;the tube&apos;s ID&lt;/li&gt;            &lt;li&gt;the tube&apos;s initiator&lt;/li&gt;            &lt;li&gt;the tube&apos;s type&lt;/li&gt;            &lt;li&gt;the tube&apos;s service&lt;/li&gt;            &lt;li&gt;the tube&apos;s parameters&lt;/li&gt;            &lt;li&gt;the tube&apos;s state&lt;/li&gt;          &lt;/ul&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method ListTubes and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * (Undocumented)
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_tubes_run_list_tubes (TpChannel *proxy,
    gint timeout_ms,
    GPtrArray **out_Tubes,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_tubes_run_state_list_tubes state = {
      NULL /* loop */, error,
    out_Tubes,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "ListTubes", iface,
      _tp_cli_channel_type_tubes_finish_running_list_tubes,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "ListTubes",
          _tp_cli_channel_type_tubes_collect_callback_list_tubes,
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
 * tp_cli_channel_type_tubes_callback_for_offer_d_bus_tube:
 * @proxy: the proxy on which the call was made
 * @out_Tube_ID: Used to return an 'out' argument if @error is %NULL: The ID of the new tube.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a OfferDBusTube method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_tubes_collect_callback_offer_d_bus_tube (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  guint out_Tube_ID;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_UINT, &out_Tube_ID,
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
  g_value_set_uint (args->values + 0, out_Tube_ID);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_offer_d_bus_tube (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_callback_for_offer_d_bus_tube callback = (tp_cli_channel_type_tubes_callback_for_offer_d_bus_tube) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          0,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_uint (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_call_offer_d_bus_tube:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Service: Used to pass an 'in' argument: A string representing the service name that will be used over the           tube.           It should be a well-known D-Bus service name, of the form           com.example.ServiceName.
 * @in_Parameters: Used to pass an 'in' argument: A dictionary of properties for the new tube; the allowable keys,           types and values are defined by the service. Connection managers           must support the value being any primitive (non-container)           D-Bus type, or a byte array &apos;ay&apos;.
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
 * Start a OfferDBusTube method call.
 *
 * Offers a D-Bus tube providing the service specified.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_tubes_call_offer_d_bus_tube (TpChannel *proxy,
    gint timeout_ms,
    const gchar *in_Service,
    GHashTable *in_Parameters,
    tp_cli_channel_type_tubes_callback_for_offer_d_bus_tube callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "OfferDBusTube",
          G_TYPE_STRING, in_Service,
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Parameters,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "OfferDBusTube", iface,
          _tp_cli_channel_type_tubes_invoke_callback_offer_d_bus_tube,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "OfferDBusTube",
              _tp_cli_channel_type_tubes_collect_callback_offer_d_bus_tube,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Service,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Parameters,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    guint *out_Tube_ID;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_tubes_run_state_offer_d_bus_tube;
static void
_tp_cli_channel_type_tubes_finish_running_offer_d_bus_tube (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_tubes_run_state_offer_d_bus_tube *state = user_data;

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

  if (state->out_Tube_ID != NULL)
    *state->out_Tube_ID = g_value_get_uint (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_run_offer_d_bus_tube:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Service: Used to pass an 'in' argument: A string representing the service name that will be used over the           tube.           It should be a well-known D-Bus service name, of the form           com.example.ServiceName.
 * @in_Parameters: Used to pass an 'in' argument: A dictionary of properties for the new tube; the allowable keys,           types and values are defined by the service. Connection managers           must support the value being any primitive (non-container)           D-Bus type, or a byte array &apos;ay&apos;.
 * @out_Tube_ID: Used to return an 'out' argument if %TRUE is returned: The ID of the new tube.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method OfferDBusTube and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Offers a D-Bus tube providing the service specified.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_tubes_run_offer_d_bus_tube (TpChannel *proxy,
    gint timeout_ms,
    const gchar *in_Service,
    GHashTable *in_Parameters,
    guint *out_Tube_ID,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_tubes_run_state_offer_d_bus_tube state = {
      NULL /* loop */, error,
    out_Tube_ID,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "OfferDBusTube", iface,
      _tp_cli_channel_type_tubes_finish_running_offer_d_bus_tube,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "OfferDBusTube",
          _tp_cli_channel_type_tubes_collect_callback_offer_d_bus_tube,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_STRING, in_Service,
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
 * tp_cli_channel_type_tubes_callback_for_offer_stream_tube:
 * @proxy: the proxy on which the call was made
 * @out_Tube_ID: Used to return an 'out' argument if @error is %NULL: The ID of the new tube.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a OfferStreamTube method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_tubes_collect_callback_offer_stream_tube (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  guint out_Tube_ID;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_UINT, &out_Tube_ID,
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
  g_value_set_uint (args->values + 0, out_Tube_ID);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_offer_stream_tube (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_callback_for_offer_stream_tube callback = (tp_cli_channel_type_tubes_callback_for_offer_stream_tube) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          0,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_uint (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_call_offer_stream_tube:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Service: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           A string representing the service name that will be used over the           tube.           It should be a well-known TCP service name as defined by           &lt;a href=&quot;http://www.iana.org/assignments/port-numbers&quot;&gt;             http://www.iana.org/assignments/port-numbers&lt;/a&gt; or           &lt;a href=&quot;http://www.dns-sd.org/ServiceTypes.html&quot;&gt;             http://www.dns-sd.org/ServiceTypes.html&lt;/a&gt;, for instance           &amp;quot;rsync&amp;quot; or &amp;quot;daap&amp;quot;.
 * @in_Parameters: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A dictionary of properties for the new tube; the allowable keys,           types and values are defined by the service. Connection managers           must support the value being any primitive (non-container)           D-Bus type, or a byte array &apos;ay&apos;.&lt;/p&gt;           &lt;p&gt;These should usually be the same key-value pairs specified for           use in the DNS-SD TXT record for that service.&lt;/p&gt;
 * @in_Address_Type: Used to pass an 'in' argument: The type of the listening address of the local service, as a member of           Socket_Address_Type.
 * @in_Address: Used to pass an 'in' argument: The listening address of the local service, as indicated by the           address_type.
 * @in_Access_Control: Used to pass an 'in' argument: The access control the local service applies to the local socket,           specified so the connection manager can behave appropriately           when it connects.
 * @in_Access_Control_Param: Used to pass an 'in' argument: A parameter for the access control type, to be interpreted as           specified in the documentation for the Socket_Access_Control enum.
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
 * Start a OfferStreamTube method call.
 *
 * Offer a stream tube exporting the local socket specified.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_tubes_call_offer_stream_tube (TpChannel *proxy,
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
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "OfferStreamTube",
          G_TYPE_STRING, in_Service,
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Parameters,
          G_TYPE_UINT, in_Address_Type,
          G_TYPE_VALUE, in_Address,
          G_TYPE_UINT, in_Access_Control,
          G_TYPE_VALUE, in_Access_Control_Param,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "OfferStreamTube", iface,
          _tp_cli_channel_type_tubes_invoke_callback_offer_stream_tube,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "OfferStreamTube",
              _tp_cli_channel_type_tubes_collect_callback_offer_stream_tube,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Service,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Parameters,
              G_TYPE_UINT, in_Address_Type,
              G_TYPE_VALUE, in_Address,
              G_TYPE_UINT, in_Access_Control,
              G_TYPE_VALUE, in_Access_Control_Param,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    guint *out_Tube_ID;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_tubes_run_state_offer_stream_tube;
static void
_tp_cli_channel_type_tubes_finish_running_offer_stream_tube (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_tubes_run_state_offer_stream_tube *state = user_data;

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

  if (state->out_Tube_ID != NULL)
    *state->out_Tube_ID = g_value_get_uint (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_run_offer_stream_tube:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Service: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           A string representing the service name that will be used over the           tube.           It should be a well-known TCP service name as defined by           &lt;a href=&quot;http://www.iana.org/assignments/port-numbers&quot;&gt;             http://www.iana.org/assignments/port-numbers&lt;/a&gt; or           &lt;a href=&quot;http://www.dns-sd.org/ServiceTypes.html&quot;&gt;             http://www.dns-sd.org/ServiceTypes.html&lt;/a&gt;, for instance           &amp;quot;rsync&amp;quot; or &amp;quot;daap&amp;quot;.
 * @in_Parameters: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A dictionary of properties for the new tube; the allowable keys,           types and values are defined by the service. Connection managers           must support the value being any primitive (non-container)           D-Bus type, or a byte array &apos;ay&apos;.&lt;/p&gt;           &lt;p&gt;These should usually be the same key-value pairs specified for           use in the DNS-SD TXT record for that service.&lt;/p&gt;
 * @in_Address_Type: Used to pass an 'in' argument: The type of the listening address of the local service, as a member of           Socket_Address_Type.
 * @in_Address: Used to pass an 'in' argument: The listening address of the local service, as indicated by the           address_type.
 * @in_Access_Control: Used to pass an 'in' argument: The access control the local service applies to the local socket,           specified so the connection manager can behave appropriately           when it connects.
 * @in_Access_Control_Param: Used to pass an 'in' argument: A parameter for the access control type, to be interpreted as           specified in the documentation for the Socket_Access_Control enum.
 * @out_Tube_ID: Used to return an 'out' argument if %TRUE is returned: The ID of the new tube.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method OfferStreamTube and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Offer a stream tube exporting the local socket specified.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_tubes_run_offer_stream_tube (TpChannel *proxy,
    gint timeout_ms,
    const gchar *in_Service,
    GHashTable *in_Parameters,
    guint in_Address_Type,
    const GValue *in_Address,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    guint *out_Tube_ID,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_tubes_run_state_offer_stream_tube state = {
      NULL /* loop */, error,
    out_Tube_ID,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "OfferStreamTube", iface,
      _tp_cli_channel_type_tubes_finish_running_offer_stream_tube,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "OfferStreamTube",
          _tp_cli_channel_type_tubes_collect_callback_offer_stream_tube,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_STRING, in_Service,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Parameters,
              G_TYPE_UINT, in_Address_Type,
              G_TYPE_VALUE, in_Address,
              G_TYPE_UINT, in_Access_Control,
              G_TYPE_VALUE, in_Access_Control_Param,
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
 * tp_cli_channel_type_tubes_callback_for_accept_d_bus_tube:
 * @proxy: the proxy on which the call was made
 * @out_Address: Used to return an 'out' argument if @error is %NULL: The string describing the address of the private bus. The client           should not attempt to connect to the address until the tube is open.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a AcceptDBusTube method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_tubes_collect_callback_accept_d_bus_tube (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_Address;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRING, &out_Address,
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
  g_value_take_string (args->values + 0, out_Address);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_accept_d_bus_tube (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_callback_for_accept_d_bus_tube callback = (tp_cli_channel_type_tubes_callback_for_accept_d_bus_tube) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_string (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_call_accept_d_bus_tube:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_ID: Used to pass an 'in' argument: The ID of the tube to accept.
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
 * Start a AcceptDBusTube method call.
 *
 * Accept a D-Bus tube that&apos;s in the &amp;quot;local pending&amp;quot; state. The         connection manager will attempt to open the tube. The tube remains in         the &amp;quot;local pending&amp;quot; state until the TubeStateChanged signal is         emitted.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_tubes_call_accept_d_bus_tube (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    tp_cli_channel_type_tubes_callback_for_accept_d_bus_tube callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "AcceptDBusTube",
          G_TYPE_UINT, in_ID,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "AcceptDBusTube", iface,
          _tp_cli_channel_type_tubes_invoke_callback_accept_d_bus_tube,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "AcceptDBusTube",
              _tp_cli_channel_type_tubes_collect_callback_accept_d_bus_tube,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_ID,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gchar **out_Address;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_tubes_run_state_accept_d_bus_tube;
static void
_tp_cli_channel_type_tubes_finish_running_accept_d_bus_tube (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_tubes_run_state_accept_d_bus_tube *state = user_data;

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

  if (state->out_Address != NULL)
    *state->out_Address = g_value_dup_string (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_run_accept_d_bus_tube:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_ID: Used to pass an 'in' argument: The ID of the tube to accept.
 * @out_Address: Used to return an 'out' argument if %TRUE is returned: The string describing the address of the private bus. The client           should not attempt to connect to the address until the tube is open.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method AcceptDBusTube and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Accept a D-Bus tube that&apos;s in the &amp;quot;local pending&amp;quot; state. The         connection manager will attempt to open the tube. The tube remains in         the &amp;quot;local pending&amp;quot; state until the TubeStateChanged signal is         emitted.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_tubes_run_accept_d_bus_tube (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    gchar **out_Address,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_tubes_run_state_accept_d_bus_tube state = {
      NULL /* loop */, error,
    out_Address,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "AcceptDBusTube", iface,
      _tp_cli_channel_type_tubes_finish_running_accept_d_bus_tube,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "AcceptDBusTube",
          _tp_cli_channel_type_tubes_collect_callback_accept_d_bus_tube,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_ID,
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
 * tp_cli_channel_type_tubes_callback_for_accept_stream_tube:
 * @proxy: the proxy on which the call was made
 * @out_Address: Used to return an 'out' argument if @error is %NULL: The address on which the connection manager will listen for           connections to this tube. The client should not attempt to connect           to the address until the tube is open.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a AcceptStreamTube method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_tubes_collect_callback_accept_stream_tube (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GValue *out_Address = g_new0 (GValue, 1);

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_VALUE, out_Address,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      g_free (out_Address);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_VALUE);
  g_value_take_boxed (args->values + 0, out_Address);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_accept_stream_tube (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_callback_for_accept_stream_tube callback = (tp_cli_channel_type_tubes_callback_for_accept_stream_tube) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_call_accept_stream_tube:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_ID: Used to pass an 'in' argument: The ID of the tube to accept.
 * @in_Address_Type: Used to pass an 'in' argument: The type of address the connection manager should listen on.
 * @in_Access_Control: Used to pass an 'in' argument: The type of access control the connection manager should apply to           the socket.
 * @in_Access_Control_Param: Used to pass an 'in' argument: A parameter for the access control type, to be interpreted as           specified in the documentation for the Socket_Access_Control enum.
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
 * Start a AcceptStreamTube method call.
 *
 * Accept a stream tube that&apos;s in the &amp;quot;local pending&amp;quot; state. The         connection manager will attempt to open the tube. The tube remains in         the &amp;quot;local pending&amp;quot; state until the TubeStateChanged signal is         emitted.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_tubes_call_accept_stream_tube (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    tp_cli_channel_type_tubes_callback_for_accept_stream_tube callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "AcceptStreamTube",
          G_TYPE_UINT, in_ID,
          G_TYPE_UINT, in_Address_Type,
          G_TYPE_UINT, in_Access_Control,
          G_TYPE_VALUE, in_Access_Control_Param,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "AcceptStreamTube", iface,
          _tp_cli_channel_type_tubes_invoke_callback_accept_stream_tube,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "AcceptStreamTube",
              _tp_cli_channel_type_tubes_collect_callback_accept_stream_tube,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_ID,
              G_TYPE_UINT, in_Address_Type,
              G_TYPE_UINT, in_Access_Control,
              G_TYPE_VALUE, in_Access_Control_Param,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GValue **out_Address;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_tubes_run_state_accept_stream_tube;
static void
_tp_cli_channel_type_tubes_finish_running_accept_stream_tube (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_tubes_run_state_accept_stream_tube *state = user_data;

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

  if (state->out_Address != NULL)
    *state->out_Address = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_run_accept_stream_tube:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_ID: Used to pass an 'in' argument: The ID of the tube to accept.
 * @in_Address_Type: Used to pass an 'in' argument: The type of address the connection manager should listen on.
 * @in_Access_Control: Used to pass an 'in' argument: The type of access control the connection manager should apply to           the socket.
 * @in_Access_Control_Param: Used to pass an 'in' argument: A parameter for the access control type, to be interpreted as           specified in the documentation for the Socket_Access_Control enum.
 * @out_Address: Used to return an 'out' argument if %TRUE is returned: The address on which the connection manager will listen for           connections to this tube. The client should not attempt to connect           to the address until the tube is open.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method AcceptStreamTube and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Accept a stream tube that&apos;s in the &amp;quot;local pending&amp;quot; state. The         connection manager will attempt to open the tube. The tube remains in         the &amp;quot;local pending&amp;quot; state until the TubeStateChanged signal is         emitted.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_tubes_run_accept_stream_tube (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    guint in_Address_Type,
    guint in_Access_Control,
    const GValue *in_Access_Control_Param,
    GValue **out_Address,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_tubes_run_state_accept_stream_tube state = {
      NULL /* loop */, error,
    out_Address,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "AcceptStreamTube", iface,
      _tp_cli_channel_type_tubes_finish_running_accept_stream_tube,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "AcceptStreamTube",
          _tp_cli_channel_type_tubes_collect_callback_accept_stream_tube,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_ID,
              G_TYPE_UINT, in_Address_Type,
              G_TYPE_UINT, in_Access_Control,
              G_TYPE_VALUE, in_Access_Control_Param,
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
 * tp_cli_channel_type_tubes_callback_for_close_tube:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a CloseTube method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_tubes_collect_callback_close_tube (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_close_tube (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_callback_for_close_tube callback = (tp_cli_channel_type_tubes_callback_for_close_tube) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_call_close_tube:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_ID: Used to pass an 'in' argument: The ID of the tube to close.
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
 * Start a CloseTube method call.
 *
 * Close a tube.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_tubes_call_close_tube (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    tp_cli_channel_type_tubes_callback_for_close_tube callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "CloseTube",
          G_TYPE_UINT, in_ID,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "CloseTube", iface,
          _tp_cli_channel_type_tubes_invoke_callback_close_tube,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "CloseTube",
              _tp_cli_channel_type_tubes_collect_callback_close_tube,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_ID,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_tubes_run_state_close_tube;
static void
_tp_cli_channel_type_tubes_finish_running_close_tube (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_tubes_run_state_close_tube *state = user_data;

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
 * tp_cli_channel_type_tubes_run_close_tube:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_ID: Used to pass an 'in' argument: The ID of the tube to close.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method CloseTube and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Close a tube.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_tubes_run_close_tube (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_tubes_run_state_close_tube state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "CloseTube", iface,
      _tp_cli_channel_type_tubes_finish_running_close_tube,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "CloseTube",
          _tp_cli_channel_type_tubes_collect_callback_close_tube,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_ID,
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
 * tp_cli_channel_type_tubes_callback_for_get_d_bus_tube_address:
 * @proxy: the proxy on which the call was made
 * @out_Address: Used to return an 'out' argument if @error is %NULL: The bus address.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetDBusTubeAddress method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_tubes_collect_callback_get_d_bus_tube_address (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_Address;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRING, &out_Address,
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
  g_value_take_string (args->values + 0, out_Address);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_get_d_bus_tube_address (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_callback_for_get_d_bus_tube_address callback = (tp_cli_channel_type_tubes_callback_for_get_d_bus_tube_address) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_string (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_call_get_d_bus_tube_address:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_ID: Used to pass an 'in' argument: The ID of the tube to get an address for.
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
 * Start a GetDBusTubeAddress method call.
 *
 * For a D-Bus tube, return a string describing the address of the         private bus.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_tubes_call_get_d_bus_tube_address (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    tp_cli_channel_type_tubes_callback_for_get_d_bus_tube_address callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetDBusTubeAddress",
          G_TYPE_UINT, in_ID,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetDBusTubeAddress", iface,
          _tp_cli_channel_type_tubes_invoke_callback_get_d_bus_tube_address,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetDBusTubeAddress",
              _tp_cli_channel_type_tubes_collect_callback_get_d_bus_tube_address,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_ID,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gchar **out_Address;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_tubes_run_state_get_d_bus_tube_address;
static void
_tp_cli_channel_type_tubes_finish_running_get_d_bus_tube_address (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_tubes_run_state_get_d_bus_tube_address *state = user_data;

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

  if (state->out_Address != NULL)
    *state->out_Address = g_value_dup_string (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_run_get_d_bus_tube_address:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_ID: Used to pass an 'in' argument: The ID of the tube to get an address for.
 * @out_Address: Used to return an 'out' argument if %TRUE is returned: The bus address.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetDBusTubeAddress and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * For a D-Bus tube, return a string describing the address of the         private bus.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_tubes_run_get_d_bus_tube_address (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    gchar **out_Address,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_tubes_run_state_get_d_bus_tube_address state = {
      NULL /* loop */, error,
    out_Address,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetDBusTubeAddress", iface,
      _tp_cli_channel_type_tubes_finish_running_get_d_bus_tube_address,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetDBusTubeAddress",
          _tp_cli_channel_type_tubes_collect_callback_get_d_bus_tube_address,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_ID,
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
 * tp_cli_channel_type_tubes_callback_for_get_d_bus_names:
 * @proxy: the proxy on which the call was made
 * @out_DBus_Names: Used to return an 'out' argument if @error is %NULL: An array of structures, each containing a contact handle and a D-Bus           bus name.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetDBusNames method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_tubes_collect_callback_get_d_bus_names (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GPtrArray *out_DBus_Names;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID)))), &out_DBus_Names,
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
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_DBus_Names);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_get_d_bus_names (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_callback_for_get_d_bus_names callback = (tp_cli_channel_type_tubes_callback_for_get_d_bus_names) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_call_get_d_bus_names:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_ID: Used to pass an 'in' argument: The ID of the tube to get names for.
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
 * Start a GetDBusNames method call.
 *
 * For a multi-user (i.e. Handle_Type_Room) D-Bus tube, obtain a mapping         between contact handles and their unique bus names on this tube.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_tubes_call_get_d_bus_names (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    tp_cli_channel_type_tubes_callback_for_get_d_bus_names callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetDBusNames",
          G_TYPE_UINT, in_ID,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetDBusNames", iface,
          _tp_cli_channel_type_tubes_invoke_callback_get_d_bus_names,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetDBusNames",
              _tp_cli_channel_type_tubes_collect_callback_get_d_bus_names,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_ID,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GPtrArray **out_DBus_Names;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_tubes_run_state_get_d_bus_names;
static void
_tp_cli_channel_type_tubes_finish_running_get_d_bus_names (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_tubes_run_state_get_d_bus_names *state = user_data;

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

  if (state->out_DBus_Names != NULL)
    *state->out_DBus_Names = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_run_get_d_bus_names:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_ID: Used to pass an 'in' argument: The ID of the tube to get names for.
 * @out_DBus_Names: Used to return an 'out' argument if %TRUE is returned: An array of structures, each containing a contact handle and a D-Bus           bus name.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetDBusNames and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * For a multi-user (i.e. Handle_Type_Room) D-Bus tube, obtain a mapping         between contact handles and their unique bus names on this tube.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_tubes_run_get_d_bus_names (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    GPtrArray **out_DBus_Names,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_tubes_run_state_get_d_bus_names state = {
      NULL /* loop */, error,
    out_DBus_Names,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetDBusNames", iface,
      _tp_cli_channel_type_tubes_finish_running_get_d_bus_names,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetDBusNames",
          _tp_cli_channel_type_tubes_collect_callback_get_d_bus_names,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_ID,
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
 * tp_cli_channel_type_tubes_callback_for_get_stream_tube_socket_address:
 * @proxy: the proxy on which the call was made
 * @out_Address_Type: Used to return an 'out' argument if @error is %NULL: The type of the listening address of the socket, as a member of           Socket_Address_Type.
 * @out_Address: Used to return an 'out' argument if @error is %NULL: The listening address of the socket, as indicated by the           address_type.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetStreamTubeSocketAddress method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_type_tubes_collect_callback_get_stream_tube_socket_address (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  guint out_Address_Type;
  GValue *out_Address = g_new0 (GValue, 1);

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_UINT, &out_Address_Type,
      G_TYPE_VALUE, out_Address,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      g_free (out_Address);
      return;
    }

  args = g_value_array_new (2);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 2; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UINT);
  g_value_set_uint (args->values + 0, out_Address_Type);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_VALUE);
  g_value_take_boxed (args->values + 1, out_Address);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_type_tubes_invoke_callback_get_stream_tube_socket_address (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_type_tubes_callback_for_get_stream_tube_socket_address callback = (tp_cli_channel_type_tubes_callback_for_get_stream_tube_socket_address) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannel *) self,
          0,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannel *) self,
      g_value_get_uint (args->values + 0),
      g_value_get_boxed (args->values + 1),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_call_get_stream_tube_socket_address:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_ID: Used to pass an 'in' argument: The ID of the stream tube to get the socket for.
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
 * Start a GetStreamTubeSocketAddress method call.
 *
 * For a stream tube, obtain the address of the socket used to         communicate over this tube.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_type_tubes_call_get_stream_tube_socket_address (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    tp_cli_channel_type_tubes_callback_for_get_stream_tube_socket_address callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), NULL);
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
            error, user_data, weak_object);

      if (destroy != NULL)
        destroy (user_data);

      g_error_free (error);
      return NULL;
    }

  if (callback == NULL)
    {
      dbus_g_proxy_call_no_reply (iface, "GetStreamTubeSocketAddress",
          G_TYPE_UINT, in_ID,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetStreamTubeSocketAddress", iface,
          _tp_cli_channel_type_tubes_invoke_callback_get_stream_tube_socket_address,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetStreamTubeSocketAddress",
              _tp_cli_channel_type_tubes_collect_callback_get_stream_tube_socket_address,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_ID,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    guint *out_Address_Type;
    GValue **out_Address;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_channel_type_tubes_run_state_get_stream_tube_socket_address;
static void
_tp_cli_channel_type_tubes_finish_running_get_stream_tube_socket_address (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_channel_type_tubes_run_state_get_stream_tube_socket_address *state = user_data;

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

  if (state->out_Address_Type != NULL)
    *state->out_Address_Type = g_value_get_uint (args->values + 0);

  if (state->out_Address != NULL)
    *state->out_Address = g_value_dup_boxed (args->values + 1);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_type_tubes_run_get_stream_tube_socket_address:
 * @proxy: A #TpChannel or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_ID: Used to pass an 'in' argument: The ID of the stream tube to get the socket for.
 * @out_Address_Type: Used to return an 'out' argument if %TRUE is returned: The type of the listening address of the socket, as a member of           Socket_Address_Type.
 * @out_Address: Used to return an 'out' argument if %TRUE is returned: The listening address of the socket, as indicated by the           address_type.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetStreamTubeSocketAddress and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * For a stream tube, obtain the address of the socket used to         communicate over this tube.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_channel_type_tubes_run_get_stream_tube_socket_address (TpChannel *proxy,
    gint timeout_ms,
    guint in_ID,
    guint *out_Address_Type,
    GValue **out_Address,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_TYPE_TUBES;
  TpProxyPendingCall *pc;
  _tp_cli_channel_type_tubes_run_state_get_stream_tube_socket_address state = {
      NULL /* loop */, error,
    out_Address_Type,
    out_Address,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CHANNEL (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetStreamTubeSocketAddress", iface,
      _tp_cli_channel_type_tubes_finish_running_get_stream_tube_socket_address,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetStreamTubeSocketAddress",
          _tp_cli_channel_type_tubes_collect_callback_get_stream_tube_socket_address,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_ID,
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
 * tp_cli_channel_add_signals:
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
tp_cli_channel_add_signals (TpProxy *self G_GNUC_UNUSED,
    guint quark,
    DBusGProxy *proxy,
    gpointer unused G_GNUC_UNUSED)
{
  if (quark == TP_IFACE_QUARK_CHANNEL)
    tp_cli_add_signals_for_channel (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_INTERFACE_CALL_STATE)
    tp_cli_add_signals_for_channel_interface_call_state (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_INTERFACE_CHAT_STATE)
    tp_cli_add_signals_for_channel_interface_chat_state (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_INTERFACE_GROUP)
    tp_cli_add_signals_for_channel_interface_group (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_INTERFACE_HOLD)
    tp_cli_add_signals_for_channel_interface_hold (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_INTERFACE_MEDIA_SIGNALLING)
    tp_cli_add_signals_for_channel_interface_media_signalling (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_INTERFACE_MESSAGES)
    tp_cli_add_signals_for_channel_interface_messages (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_INTERFACE_PASSWORD)
    tp_cli_add_signals_for_channel_interface_password (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_INTERFACE_TUBE)
    tp_cli_add_signals_for_channel_interface_tube (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_TYPE_DBUS_TUBE)
    tp_cli_add_signals_for_channel_type_dbus_tube (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_TYPE_FILE_TRANSFER)
    tp_cli_add_signals_for_channel_type_file_transfer (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_TYPE_ROOM_LIST)
    tp_cli_add_signals_for_channel_type_room_list (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_TYPE_STREAM_TUBE)
    tp_cli_add_signals_for_channel_type_stream_tube (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_TYPE_STREAMED_MEDIA)
    tp_cli_add_signals_for_channel_type_streamed_media (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_TYPE_TEXT)
    tp_cli_add_signals_for_channel_type_text (proxy);
  if (quark == TP_IFACE_QUARK_CHANNEL_TYPE_TUBES)
    tp_cli_add_signals_for_channel_type_tubes (proxy);
}
