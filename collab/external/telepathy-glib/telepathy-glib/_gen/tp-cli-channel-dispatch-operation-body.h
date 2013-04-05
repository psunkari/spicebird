/* We don't want gtkdoc scanning this file, it'll get
 * confused by seeing function definitions, so mark it as: */
/*<private_header>*/

static inline void
tp_cli_add_signals_for_channel_dispatch_operation (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "ChannelLost",
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "Finished",
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_dispatch_operation_signal_callback_channel_lost:
 * @proxy: The proxy on which tp_cli_channel_dispatch_operation_connect_to_channel_lost ()
 *  was called
 * @arg_Channel: The &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Channel&lt;/tp:dbus-ref&gt;           that closed.
 * @arg_Error: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The name of a D-Bus error indicating why the channel closed. If             no better reason can be found,             &lt;code&gt;org.freedesktop.Telepathy.Error.NotAvailable&lt;/code&gt; MAY             be used as a fallback; this means that this error SHOULD NOT be             given any more specific meaning.&lt;/p&gt;
 * @arg_Message: A string associated with the D-Bus error.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal ChannelLost.
 */
static void
_tp_cli_channel_dispatch_operation_collect_args_of_channel_lost (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Channel,
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
  g_value_init (args->values + 0, DBUS_TYPE_G_OBJECT_PATH);
  g_value_set_boxed (args->values + 0, arg_Channel);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_STRING);
  g_value_set_string (args->values + 1, arg_Error);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, G_TYPE_STRING);
  g_value_set_string (args->values + 2, arg_Message);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_dispatch_operation_invoke_callback_for_channel_lost (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_dispatch_operation_signal_callback_channel_lost callback =
      (tp_cli_channel_dispatch_operation_signal_callback_channel_lost) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      g_value_get_string (args->values + 1),
      g_value_get_string (args->values + 2),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_dispatch_operation_connect_to_channel_lost:
 * @proxy: A #TpChannelDispatchOperation or subclass
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
 * Connect a handler to the signal ChannelLost.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;A channel has closed before it could be claimed or handled. If           this is emitted for the last remaining channel in a channel           dispatch operation, it MUST immediately be followed by           &lt;tp:member-ref&gt;Finished&lt;/tp:member-ref&gt;.&lt;/p&gt;          &lt;p&gt;This signal MUST NOT be emitted until all Approvers that were           invoked have returned (successfully or with an error) from           their &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Approver&quot;&gt;AddDispatchOperation&lt;/tp:dbus-ref&gt;           method.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;This means that Approvers can connect to the ChannelLost signal             in a race-free way. Non-approver processes that discover             a channel dispatch operation in some way (such as observers)             will have to follow the usual &amp;quot;connect to signals then recover             state&amp;quot; model - first connect to ChannelLost and             &lt;tp:member-ref&gt;Finished&lt;/tp:member-ref&gt;,             then download &lt;tp:member-ref&gt;Channels&lt;/tp:member-ref&gt; (and             on error, perhaps assume that the operation has already             Finished).&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_dispatch_operation_connect_to_channel_lost (TpChannelDispatchOperation *proxy,
    tp_cli_channel_dispatch_operation_signal_callback_channel_lost callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[4] = {
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL_DISPATCH_OPERATION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_DISPATCH_OPERATION, "ChannelLost",
      expected_types,
      G_CALLBACK (_tp_cli_channel_dispatch_operation_collect_args_of_channel_lost),
      _tp_cli_channel_dispatch_operation_invoke_callback_for_channel_lost,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_dispatch_operation_signal_callback_finished:
 * @proxy: The proxy on which tp_cli_channel_dispatch_operation_connect_to_finished ()
 *  was called
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal Finished.
 */
static void
_tp_cli_channel_dispatch_operation_invoke_callback_for_finished (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_dispatch_operation_signal_callback_finished callback =
      (tp_cli_channel_dispatch_operation_signal_callback_finished) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      user_data,
      weak_object);

  if (args != NULL)
    g_value_array_free (args);

  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_dispatch_operation_connect_to_finished:
 * @proxy: A #TpChannelDispatchOperation or subclass
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
 * Connect a handler to the signal Finished.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Emitted when this dispatch operation finishes. The dispatch           operation is no longer present and further methods must not be           called on it.&lt;/p&gt;          &lt;p&gt;Approvers that have a user interface SHOULD stop notifying the user           about the channels in response to this signal; they MAY assume that           on errors, they would have received           &lt;tp:member-ref&gt;ChannelLost&lt;/tp:member-ref&gt; first.&lt;/p&gt;          &lt;p&gt;Its object path SHOULD NOT be reused for a subsequent dispatch           operation; the ChannelDispatcher MUST choose object paths           in a way that avoids immediate re-use.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;Otherwise, clients might accidentally call             &lt;tp:member-ref&gt;HandleWith&lt;/tp:member-ref&gt; or             &lt;tp:member-ref&gt;Claim&lt;/tp:member-ref&gt; on a new dispatch operation             instead of the one they intended to handle.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;This signal MUST NOT be emitted until all Approvers that were           invoked have returned (successfully or with an error) from           their &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Approver&quot;&gt;AddDispatchOperation&lt;/tp:dbus-ref&gt;           method.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;This means that Approvers can connect to the ChannelLost signal             in a race-free way. Non-approver processes that discover             a channel dispatch operation in some way (such as observers)             will have to follow the usual &amp;quot;connect to signals then recover             state&amp;quot; model - first connect to             &lt;tp:member-ref&gt;ChannelLost&lt;/tp:member-ref&gt; and             Finished, then download &lt;tp:member-ref&gt;Channels&lt;/tp:member-ref&gt;             (and on error, perhaps assume that the operation has already             Finished).&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_dispatch_operation_connect_to_finished (TpChannelDispatchOperation *proxy,
    tp_cli_channel_dispatch_operation_signal_callback_finished callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[1] = {
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL_DISPATCH_OPERATION (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_DISPATCH_OPERATION, "Finished",
      expected_types,
      NULL, /* no args => no collector function */
      _tp_cli_channel_dispatch_operation_invoke_callback_for_finished,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_dispatch_operation_callback_for_handle_with:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a HandleWith method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_dispatch_operation_collect_callback_handle_with (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_dispatch_operation_invoke_callback_handle_with (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_dispatch_operation_callback_for_handle_with callback = (tp_cli_channel_dispatch_operation_callback_for_handle_with) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannelDispatchOperation *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannelDispatchOperation *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_dispatch_operation_call_handle_with:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Handler: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The well-known bus name (starting with             &lt;code&gt;org.freedesktop.Telepathy.Client.&lt;/code&gt;) of the channel             handler that should handle the channel, or the empty string             if the client has no preferred channel handler.&lt;/p&gt;
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
 * Start a HandleWith method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Called by an approver to accept a channel bundle and request that           the given handler be used to handle it.&lt;/p&gt;          &lt;p&gt;If successful, this method will cause the ChannelDispatchOperation           object to disappear, emitting           &lt;tp:member-ref&gt;Finished&lt;/tp:member-ref&gt;.&lt;/p&gt;          &lt;p&gt;However, this method may fail because the dispatch has already been           completed and the object has already gone. If this occurs, it           indicates that another approver has asked for the bundle to be           handled by a particular handler. The approver MUST NOT attempt           to interact with the channels further in this case, unless it is           separately invoked as the handler.&lt;/p&gt;          &lt;p&gt;Approvers which are also channel handlers SHOULD use           &lt;tp:member-ref&gt;Claim&lt;/tp:member-ref&gt; instead           of HandleWith to request that they can handle a channel bundle           themselves.&lt;/p&gt;          &lt;p&gt;(FIXME: list some possible errors)&lt;/p&gt;          &lt;p&gt;If the channel handler raises an error from &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Handler&quot;&gt;HandleChannels&lt;/tp:dbus-ref&gt;,           this method           MAY respond by raising that same error, even if it is not           specifically documented here.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_dispatch_operation_call_handle_with (TpChannelDispatchOperation *proxy,
    gint timeout_ms,
    const gchar *in_Handler,
    tp_cli_channel_dispatch_operation_callback_for_handle_with callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_DISPATCH_OPERATION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL_DISPATCH_OPERATION (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "HandleWith",
          G_TYPE_STRING, in_Handler,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "HandleWith", iface,
          _tp_cli_channel_dispatch_operation_invoke_callback_handle_with,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "HandleWith",
              _tp_cli_channel_dispatch_operation_collect_callback_handle_with,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Handler,
              G_TYPE_INVALID));

      return data;
    }
}


/**
 * tp_cli_channel_dispatch_operation_callback_for_claim:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Claim method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_dispatch_operation_collect_callback_claim (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_channel_dispatch_operation_invoke_callback_claim (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_dispatch_operation_callback_for_claim callback = (tp_cli_channel_dispatch_operation_callback_for_claim) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannelDispatchOperation *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannelDispatchOperation *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_channel_dispatch_operation_call_claim:
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
 * Start a Claim method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Called by an approver to claim channels for handling           internally. If this method is called successfully, the process           calling this method becomes the handler for the channel, but           &lt;em&gt;does not&lt;/em&gt; have the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Handler&quot;&gt;HandleChannels&lt;/tp:dbus-ref&gt;           method called on it.&lt;/p&gt;          &lt;p&gt;Clients that call Claim on channels but do not immediately           close them SHOULD implement the Handler interface and its           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Handler&quot;&gt;HandledChannels&lt;/tp:dbus-ref&gt;           property.&lt;/p&gt;          &lt;p&gt;Approvers wishing to reject channels MUST call this method to           claim ownership of them, and MUST NOT call           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel&quot;&gt;Close&lt;/tp:dbus-ref&gt;           on the channels unless/until this method returns successfully.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The channel dispatcher can&apos;t know how best to close arbitrary             channel types, so it leaves it up to the approver to do so.             For instance, for Text channels it is necessary             to acknowledge any messages that have already been displayed to             the user first - ideally, the approver would display and then             acknowledge the messages - or to call &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Channel.Interface.Destroyable.Destroy&lt;/tp:dbus-ref&gt;             if the destructive behaviour of that method is desired.&lt;/p&gt;            &lt;p&gt;Similarly, an Approver for StreamedMedia channels can close the             channel with a reason (e.g. &amp;quot;busy&amp;quot;) if desired. The channel             dispatcher, which is designed to have no specific knowledge             of particular channel types, can&apos;t do that.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;If successful, this method will cause the ChannelDispatchOperation           object to disappear, emitting           &lt;tp:member-ref&gt;Finished&lt;/tp:member-ref&gt;, in the same way as for           &lt;tp:member-ref&gt;HandleWith&lt;/tp:member-ref&gt;.&lt;/p&gt;          &lt;p&gt;This method may fail because the dispatch operation has already           been completed. Again, see HandleWith for more details. The approver           MUST NOT attempt to interact with the channels further in this           case.&lt;/p&gt;          &lt;p&gt;(FIXME: list some other possible errors)&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_dispatch_operation_call_claim (TpChannelDispatchOperation *proxy,
    gint timeout_ms,
    tp_cli_channel_dispatch_operation_callback_for_claim callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_DISPATCH_OPERATION;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL_DISPATCH_OPERATION (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Claim",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Claim", iface,
          _tp_cli_channel_dispatch_operation_invoke_callback_claim,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Claim",
              _tp_cli_channel_dispatch_operation_collect_callback_claim,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}


/*
 * tp_cli_channel_dispatch_operation_add_signals:
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
tp_cli_channel_dispatch_operation_add_signals (TpProxy *self G_GNUC_UNUSED,
    guint quark,
    DBusGProxy *proxy,
    gpointer unused G_GNUC_UNUSED)
{
  if (quark == TP_IFACE_QUARK_CHANNEL_DISPATCH_OPERATION)
    tp_cli_add_signals_for_channel_dispatch_operation (proxy);
}
