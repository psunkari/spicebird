/* We don't want gtkdoc scanning this file, it'll get
 * confused by seeing function definitions, so mark it as: */
/*<private_header>*/

/**
 * tp_cli_channel_dispatcher_callback_for_create_channel:
 * @proxy: the proxy on which the call was made
 * @out_Request: Used to return an 'out' argument if @error is %NULL: A           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelRequest&lt;/tp:dbus-ref&gt;           object.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a CreateChannel method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_dispatcher_collect_callback_create_channel (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_Request;

  dbus_g_proxy_end_call (proxy, call, &error,
      DBUS_TYPE_G_OBJECT_PATH, &out_Request,
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
  g_value_take_boxed (args->values + 0, out_Request);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_dispatcher_invoke_callback_create_channel (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_dispatcher_callback_for_create_channel callback = (tp_cli_channel_dispatcher_callback_for_create_channel) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannelDispatcher *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannelDispatcher *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_dispatcher_call_create_channel:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Account: Used to pass an 'in' argument: The             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Account&lt;/tp:dbus-ref&gt;           for which the new channel is to be created.
 * @in_Requested_Properties: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A dictionary containing desirable properties. This has the same             semantics as the corresponding parameter to             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection.Interface.Requests.CreateChannel&lt;/tp:dbus-ref&gt;.           &lt;/p&gt;            &lt;p&gt;Certain properties will not necessarily make sense in this             dictionary: for instance,             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel&quot;&gt;TargetHandle&lt;/tp:dbus-ref&gt;             can only be given if the requester is able to interact with a             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection&lt;/tp:dbus-ref&gt;             to the desired account.&lt;/p&gt;
 * @in_User_Action_Time: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The time at which user action occurred, or 0 if this channel             request is for some reason not involving user action.             The &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelRequest&quot;&gt;UserActionTime&lt;/tp:dbus-ref&gt;             property will be set to this value, and it will eventually be             passed as the &lt;code&gt;User_Action_Time&lt;/code&gt; parameter of &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Handler&quot;&gt;HandleChannels&lt;/tp:dbus-ref&gt;.&lt;/p&gt;
 * @in_Preferred_Handler: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Either the well-known bus name (starting with             &lt;code&gt;org.freedesktop.Telepathy.Client.&lt;/code&gt;)             of the preferred handler for this             channel, or an empty string to indicate that any handler would be             acceptable. The channel dispatcher SHOULD dispatch as many as             possible of the resulting channels (ideally, all of them)             to that handler, and SHOULD remember the preferred handler             so it can try to dispatch subsequent channels in the same bundle             to the same handler.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This must be the well-known bus name, not the unique name,               to ensure that all handlers do indeed have the Client API,               and the Client object on the handler can be located easily.&lt;/p&gt;              &lt;p&gt;This is partly so the channel dispatcher can call               &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Handler&quot;&gt;HandleChannels&lt;/tp:dbus-ref&gt;               on it, and partly so the channel dispatcher               can recover state if it crashes and is restarted.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;If this is a well-known bus name and the handler has the             Requests interface, the channel dispatcher SHOULD             call &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Interface.Requests&quot;&gt;AddRequest&lt;/tp:dbus-ref&gt;             on that Handler after this method has returned.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This ordering allows a Handler which calls CreateChannel with               itself as the preferred handler to associate the call to               AddRequest with that call.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;This is copied to the ChannelRequest that is returned,             as the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelRequest&quot;&gt;PreferredHandler&lt;/tp:dbus-ref&gt;             property.&lt;/p&gt;
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
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Start a request to create a channel. This initially just creates a           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelRequest&lt;/tp:dbus-ref&gt;           object, which can be used to continue the request and track its           success or failure.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The request can take a long time - in the worst case, the             channel dispatcher has to ask the account manager to put the             account online, the account manager has to ask the operating             system to obtain an Internet connection, and the operating             system has to ask the user whether to activate an Internet             connection using an on-demand mechanism like dialup.&lt;/p&gt;            &lt;p&gt;This means that using a single D-Bus method call and response             to represent the whole request will tend to lead to that call             timing out, which is not the behaviour we want.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;If this method is called for an Account that is disabled, invalid           or otherwise unusable, no error is signalled until           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelRequest.Proceed&lt;/tp:dbus-ref&gt;           is called, at which point           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelRequest.Failed&lt;/tp:dbus-ref&gt;           is emitted with an appropriate error.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;This means there&apos;s only one code path for errors, apart from             InvalidArgument for &amp;quot;that request makes no sense&amp;quot;.&lt;/p&gt;            &lt;p&gt;It also means that the request will proceed if the account is             enabled after calling CreateChannel, but before calling             Proceed.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_dispatcher_call_create_channel (TpChannelDispatcher *proxy,
    gint timeout_ms,
    const gchar *in_Account,
    GHashTable *in_Requested_Properties,
    gint64 in_User_Action_Time,
    const gchar *in_Preferred_Handler,
    tp_cli_channel_dispatcher_callback_for_create_channel callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_DISPATCHER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL_DISPATCHER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "CreateChannel",
          DBUS_TYPE_G_OBJECT_PATH, in_Account,
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Requested_Properties,
          G_TYPE_INT64, in_User_Action_Time,
          G_TYPE_STRING, in_Preferred_Handler,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "CreateChannel", iface,
          _tp_cli_channel_dispatcher_invoke_callback_create_channel,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "CreateChannel",
              _tp_cli_channel_dispatcher_collect_callback_create_channel,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_OBJECT_PATH, in_Account,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Requested_Properties,
              G_TYPE_INT64, in_User_Action_Time,
              G_TYPE_STRING, in_Preferred_Handler,
              G_TYPE_INVALID));

      return data;
    }
}


/**
 * tp_cli_channel_dispatcher_callback_for_ensure_channel:
 * @proxy: the proxy on which the call was made
 * @out_Request: Used to return an 'out' argument if @error is %NULL: A           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelRequest&lt;/tp:dbus-ref&gt;           object.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a EnsureChannel method call
 * succeeds or fails.
 */
static void
_tp_cli_channel_dispatcher_collect_callback_ensure_channel (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_Request;

  dbus_g_proxy_end_call (proxy, call, &error,
      DBUS_TYPE_G_OBJECT_PATH, &out_Request,
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
  g_value_take_boxed (args->values + 0, out_Request);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_channel_dispatcher_invoke_callback_ensure_channel (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_dispatcher_callback_for_ensure_channel callback = (tp_cli_channel_dispatcher_callback_for_ensure_channel) generic_callback;

  if (error != NULL)
    {
      callback ((TpChannelDispatcher *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpChannelDispatcher *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_channel_dispatcher_call_ensure_channel:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Account: Used to pass an 'in' argument: The             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Account&lt;/tp:dbus-ref&gt;           for which the new channel is to be created.
 * @in_Requested_Properties: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;A dictionary containing desirable properties. This has the same             semantics as the corresponding parameter to             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection.Interface.Requests.EnsureChannel&lt;/tp:dbus-ref&gt;.           &lt;/p&gt;            &lt;p&gt;Certain properties will not necessarily make sense in this             dictionary: for instance,             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel&quot;&gt;TargetHandle&lt;/tp:dbus-ref&gt;             can only be given if the requester is able to interact with a             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection&lt;/tp:dbus-ref&gt;             to the desired account.&lt;/p&gt;
 * @in_User_Action_Time: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The time at which user action occurred, or 0 if this channel             request is for some reason not involving user action.&lt;/p&gt;            &lt;p&gt;This parameter is used in the same way as the corresponding             parameter to &lt;tp:member-ref&gt;CreateChannel&lt;/tp:member-ref&gt;.&lt;/p&gt;
 * @in_Preferred_Handler: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Either the well-known bus name (starting with             &lt;code&gt;org.freedesktop.Telepathy.Client.&lt;/code&gt;)             of the preferred handler for this             channel, or an empty string to indicate that any handler would be             acceptable. The behaviour and rationale are the same as for the             corresponding parameter to             &lt;tp:member-ref&gt;CreateChannel&lt;/tp:member-ref&gt;, except as noted             here.&lt;/p&gt;            &lt;p&gt;If any new channels are created in response to this             request, the channel dispatcher SHOULD dispatch as many as             possible of the resulting channels (ideally, all of them)             to that handler, and SHOULD remember the preferred handler             so it can try to dispatch subsequent channels in the same bundle             to the same handler. If the requested channel already exists (that             is, &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection.Interface.Requests.EnsureChannel&lt;/tp:dbus-ref&gt;             returns &lt;code&gt;Yours=False&lt;/code&gt;) then the channel dispatcher             SHOULD re-dispatch the channel to its existing handler, and MUST             NOT dispatch it to this client (unless it is the existing handler);             the request is still deemed to have succeeded in this case.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;An address book application, for example, might call &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelDispatcher&quot;&gt;EnsureChannel&lt;/tp:dbus-ref&gt;               to ensure that a text channel with a particular contact is               displayed to the user; it does not care whether a new channel was               made. An IM client might call &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelDispatcher&quot;&gt;EnsureChannel&lt;/tp:dbus-ref&gt;               in response to the user double-clicking an entry in the contact               list, with itself as the &lt;code&gt;Preferred_Handler&lt;/code&gt;; if the               user already has a conversation with that contact in another               application, they would expect the existing window to be               presented, rather than their double-click leading to an error               message.  So the request should succeed, even if its               &lt;code&gt;Preferred_Handler&lt;/code&gt; is not used.&lt;/p&gt;           &lt;/tp:rationale&gt;
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
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Start a request to ensure that a channel exists, creating it if           necessary.  This initially just creates a &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelRequest&lt;/tp:dbus-ref&gt;           object, which can be used to continue the request and track its           success or failure.&lt;/p&gt;          &lt;p&gt;If this method is called for an Account that is disabled, invalid           or otherwise unusable, no error is signalled until           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelRequest.Proceed&lt;/tp:dbus-ref&gt;           is called, at which point           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelRequest.Failed&lt;/tp:dbus-ref&gt;           is emitted with an appropriate error.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The rationale is as for &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelDispatcher&quot;&gt;CreateChannel&lt;/tp:dbus-ref&gt;.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_channel_dispatcher_call_ensure_channel (TpChannelDispatcher *proxy,
    gint timeout_ms,
    const gchar *in_Account,
    GHashTable *in_Requested_Properties,
    gint64 in_User_Action_Time,
    const gchar *in_Preferred_Handler,
    tp_cli_channel_dispatcher_callback_for_ensure_channel callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CHANNEL_DISPATCHER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CHANNEL_DISPATCHER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "EnsureChannel",
          DBUS_TYPE_G_OBJECT_PATH, in_Account,
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Requested_Properties,
          G_TYPE_INT64, in_User_Action_Time,
          G_TYPE_STRING, in_Preferred_Handler,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "EnsureChannel", iface,
          _tp_cli_channel_dispatcher_invoke_callback_ensure_channel,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "EnsureChannel",
              _tp_cli_channel_dispatcher_collect_callback_ensure_channel,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_OBJECT_PATH, in_Account,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Requested_Properties,
              G_TYPE_INT64, in_User_Action_Time,
              G_TYPE_STRING, in_Preferred_Handler,
              G_TYPE_INVALID));

      return data;
    }
}


static inline void
tp_cli_add_signals_for_channel_dispatcher_interface_operation_list (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "NewDispatchOperation",
      DBUS_TYPE_G_OBJECT_PATH,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)),
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "DispatchOperationFinished",
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_INVALID);
}


/**
 * tp_cli_channel_dispatcher_interface_operation_list_signal_callback_new_dispatch_operation:
 * @proxy: The proxy on which tp_cli_channel_dispatcher_interface_operation_list_connect_to_new_dispatch_operation ()
 *  was called
 * @arg_Dispatch_Operation: The dispatch operation that was created.
 * @arg_Properties: The same properties that would appear in the Properties member of           &lt;tp:type-ref&gt;Dispatch_Operation_Details&lt;/tp:type-ref&gt;.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal NewDispatchOperation.
 */
static void
_tp_cli_channel_dispatcher_interface_operation_list_collect_args_of_new_dispatch_operation (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Dispatch_Operation,
    GHashTable *arg_Properties,
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
  g_value_set_boxed (args->values + 0, arg_Dispatch_Operation);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)));
  g_value_set_boxed (args->values + 1, arg_Properties);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_dispatcher_interface_operation_list_invoke_callback_for_new_dispatch_operation (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_dispatcher_interface_operation_list_signal_callback_new_dispatch_operation callback =
      (tp_cli_channel_dispatcher_interface_operation_list_signal_callback_new_dispatch_operation) generic_callback;

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
 * tp_cli_channel_dispatcher_interface_operation_list_connect_to_new_dispatch_operation:
 * @proxy: A #TpChannelDispatcher or subclass
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
 * Connect a handler to the signal NewDispatchOperation.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Emitted when a dispatch operation is added to           &lt;tp:member-ref&gt;DispatchOperations&lt;/tp:member-ref&gt;.&lt;/p&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_dispatcher_interface_operation_list_connect_to_new_dispatch_operation (TpChannelDispatcher *proxy,
    tp_cli_channel_dispatcher_interface_operation_list_signal_callback_new_dispatch_operation callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      DBUS_TYPE_G_OBJECT_PATH,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL_DISPATCHER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST, "NewDispatchOperation",
      expected_types,
      G_CALLBACK (_tp_cli_channel_dispatcher_interface_operation_list_collect_args_of_new_dispatch_operation),
      _tp_cli_channel_dispatcher_interface_operation_list_invoke_callback_for_new_dispatch_operation,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_channel_dispatcher_interface_operation_list_signal_callback_dispatch_operation_finished:
 * @proxy: The proxy on which tp_cli_channel_dispatcher_interface_operation_list_connect_to_dispatch_operation_finished ()
 *  was called
 * @arg_Dispatch_Operation: The dispatch operation that was closed.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal DispatchOperationFinished.
 */
static void
_tp_cli_channel_dispatcher_interface_operation_list_collect_args_of_dispatch_operation_finished (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Dispatch_Operation,
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
  g_value_set_boxed (args->values + 0, arg_Dispatch_Operation);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_channel_dispatcher_interface_operation_list_invoke_callback_for_dispatch_operation_finished (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_channel_dispatcher_interface_operation_list_signal_callback_dispatch_operation_finished callback =
      (tp_cli_channel_dispatcher_interface_operation_list_signal_callback_dispatch_operation_finished) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_channel_dispatcher_interface_operation_list_connect_to_dispatch_operation_finished:
 * @proxy: A #TpChannelDispatcher or subclass
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
 * Connect a handler to the signal DispatchOperationFinished.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         Emitted when a dispatch operation finishes (i.e. exactly once per         emission of &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelDispatchOperation.Finished&lt;/tp:dbus-ref&gt;).          &lt;tp:rationale&gt;           Strictly speaking this is redundant with           ChannelDispatchOperation.Finished, but it provides full           change-notification for the           &lt;tp:member-ref&gt;DispatchOperations&lt;/tp:member-ref&gt; property.         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_channel_dispatcher_interface_operation_list_connect_to_dispatch_operation_finished (TpChannelDispatcher *proxy,
    tp_cli_channel_dispatcher_interface_operation_list_signal_callback_dispatch_operation_finished callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CHANNEL_DISPATCHER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST, "DispatchOperationFinished",
      expected_types,
      G_CALLBACK (_tp_cli_channel_dispatcher_interface_operation_list_collect_args_of_dispatch_operation_finished),
      _tp_cli_channel_dispatcher_interface_operation_list_invoke_callback_for_dispatch_operation_finished,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/*
 * tp_cli_channel_dispatcher_add_signals:
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
tp_cli_channel_dispatcher_add_signals (TpProxy *self G_GNUC_UNUSED,
    guint quark,
    DBusGProxy *proxy,
    gpointer unused G_GNUC_UNUSED)
{
  if (quark == TP_IFACE_QUARK_CHANNEL_DISPATCHER_INTERFACE_OPERATION_LIST)
    tp_cli_add_signals_for_channel_dispatcher_interface_operation_list (proxy);
}
