/* We don't want gtkdoc scanning this file, it'll get
 * confused by seeing function definitions, so mark it as: */
/*<private_header>*/

static inline void
tp_cli_add_signals_for_channel_request (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "Failed",
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "Succeeded",
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_request_signal_callback_failed:
 * @proxy: The proxy on which tp_cli_channel_request_connect_to_failed ()
 *  was called
 * @arg_Error: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The name of a D-Bus error. This can come from various sources,             including the error raised by &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection.Interface.Requests&quot;&gt;CreateChannel&lt;/tp:dbus-ref&gt;,             or an error generated             to represent failure to establish the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection&lt;/tp:dbus-ref&gt;.&lt;/p&gt;
 * @arg_Message: If the first argument of the D-Bus error message was a string,           that string. Otherwise, an empty string.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal Failed.
 */
static void
_tp_cli_channel_request_collect_args_of_failed (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Error,
    const gchar *arg_Message,
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
  g_value_init (args->values + 1, G_TYPE_STRING);
  g_value_set_string (args->values + 1, arg_Message);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_request_invoke_callback_for_failed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_request_signal_callback_failed callback =
      (tp_cli_channel_request_signal_callback_failed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_string (args->values + 0),
      g_value_get_string (args->values + 1),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_request_connect_to_failed:
 * @proxy: A #TpChannelRequest or subclass
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
 * Connect a handler to the signal Failed.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;The channel request has failed. It is no longer present,           and further methods must not be called on it.&lt;/p&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_request_connect_to_failed (TpChannelRequest *proxy,
    tp_cli_channel_request_signal_callback_failed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL_REQUEST (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_REQUEST, "Failed",
      expected_types,
      G_CALLBACK (_tp_cli_channel_request_collect_args_of_failed),
      _tp_cli_channel_request_invoke_callback_for_failed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_request_signal_callback_succeeded:
 * @proxy: The proxy on which tp_cli_channel_request_connect_to_succeeded ()
 *  was called
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal Succeeded.
 */
static void
_tp_cli_channel_request_invoke_callback_for_succeeded (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_request_signal_callback_succeeded callback =
      (tp_cli_channel_request_signal_callback_succeeded) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      user_data,
      weak_object);

  if (args != NULL)
    g_value_array_free (args);

  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_request_connect_to_succeeded:
 * @proxy: A #TpChannelRequest or subclass
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
 * Connect a handler to the signal Succeeded.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;The channel request has succeeded. It is no longer present,           and further methods must not be called on it.&lt;/p&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_request_connect_to_succeeded (TpChannelRequest *proxy,
    tp_cli_channel_request_signal_callback_succeeded callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[1] = {
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL_REQUEST (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_REQUEST, "Succeeded",
      expected_types,
      NULL, /* no args => no collector function */
      _tp_cli_channel_request_invoke_callback_for_succeeded,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_request_callback_for_proceed:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Proceed method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_request_collect_callback_proceed (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_request_invoke_callback_proceed (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_request_callback_for_proceed callback = (tp_cli_channel_request_callback_for_proceed) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannelRequest *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannelRequest *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_request_call_proceed:
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
 * Start a Proceed method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Proceed with the channel request.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The client that created this object calls this method             when it has connected signal handlers for             &lt;tp:member-ref&gt;Succeeded&lt;/tp:member-ref&gt; and             &lt;tp:member-ref&gt;Failed&lt;/tp:member-ref&gt;.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;Clients other than the client which created the ChannelRequest           MUST NOT call this method.&lt;/p&gt;          &lt;p&gt;This method SHOULD return immediately; on success, the request           might still fail, but this will be indicated asynchronously           by the &lt;tp:member-ref&gt;Failed&lt;/tp:member-ref&gt; signal.&lt;/p&gt;          &lt;p&gt;Proceed cannot fail, unless clients have got the life-cycle           of a ChannelRequest seriously wrong (e.g. a client calls this           method twice, or a client that did not create the ChannelRequest           calls this method). If it fails, clients SHOULD assume that the           whole ChannelRequest has become useless.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_request_call_proceed (TpChannelRequest *proxy,
    gint timeout_ms,
    tp_cli_channel_request_callback_for_proceed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_REQUEST;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL_REQUEST (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Proceed",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Proceed", iface,
          _tp_cli_channel_request_invoke_callback_proceed,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Proceed",
              _tp_cli_channel_request_collect_callback_proceed,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}


/**
 * tp_cli_channel_request_callback_for_cancel:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Cancel method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_request_collect_callback_cancel (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_request_invoke_callback_cancel (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_request_callback_for_cancel callback = (tp_cli_channel_request_callback_for_cancel) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannelRequest *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannelRequest *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_request_call_cancel:
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
 * Start a Cancel method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Cancel the channel request. The precise effect depends on the           current progress of the request.&lt;/p&gt;          &lt;p&gt;If the connection manager has not already been asked to create           a channel, then &lt;tp:member-ref&gt;Failed&lt;/tp:member-ref&gt; is emitted           immediately, and the channel request is removed.&lt;/p&gt;          &lt;p&gt;If the connection manager has already been asked to create a           channel but has not produced one yet (e.g. if &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection.Interface.Requests.CreateChannel&lt;/tp:dbus-ref&gt;           has been called, but has not yet returned), then the           ChannelDispatcher will remember that the request has been cancelled.           When the channel appears, it will be closed (if it was newly           created and can be closed), and will not be dispatched to a           handler.&lt;/p&gt;          &lt;p&gt;If the connection manager has already returned a channel, but the           channel has not yet been dispatched to a handler           then the channel dispatcher will not dispatch that           channel to a handler. If the channel was newly created for this           request, the channel dispatcher will close it with &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel&quot;&gt;Close&lt;/tp:dbus-ref&gt;;           otherwise, the channel dispatcher will ignore it. In either case,           &lt;tp:member-ref&gt;Failed&lt;/tp:member-ref&gt; will be emitted when processing           has been completed.&lt;/p&gt;          &lt;p&gt;If &lt;tp:member-ref&gt;Failed&lt;/tp:member-ref&gt; is emitted in response to           this method, the error SHOULD be           &lt;code&gt;org.freedesktop.Telepathy.Error.Cancelled&lt;/code&gt;.&lt;/p&gt;          &lt;p&gt;If the channel has already been dispatched to a handler, then           it&apos;s too late to call this method, and the channel request will           no longer exist.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_request_call_cancel (TpChannelRequest *proxy,
    gint timeout_ms,
    tp_cli_channel_request_callback_for_cancel callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_REQUEST;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL_REQUEST (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Cancel",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Cancel", iface,
          _tp_cli_channel_request_invoke_callback_cancel,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Cancel",
              _tp_cli_channel_request_collect_callback_cancel,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}


/*
 * tp_cli_channel_request_add_signals:
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
tp_cli_channel_request_add_signals (TpProxy *self G_GNUC_UNUSED,
    guint quark,
    DBusGProxy *proxy,
    gpointer unused G_GNUC_UNUSED)
{
  if (quark == TP_IFACE_QUARK_CHANNEL_REQUEST)
    tp_cli_add_signals_for_channel_request (proxy);
}
