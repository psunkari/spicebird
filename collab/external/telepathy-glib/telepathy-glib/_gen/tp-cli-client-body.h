/* We don't want gtkdoc scanning this file, it'll get
 * confused by seeing function definitions, so mark it as: */
/*<private_header>*/

/**
 * tp_cli_client_approver_callback_for_add_dispatch_operation:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a AddDispatchOperation method call
 * succeeds or fails.
 */
static void
_tp_cli_client_approver_collect_callback_add_dispatch_operation (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_client_approver_invoke_callback_add_dispatch_operation (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_client_approver_callback_for_add_dispatch_operation callback = (tp_cli_client_approver_callback_for_add_dispatch_operation) generic_callback;

  if (error != NULL)
    {
      callback ((TpClient *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpClient *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_client_approver_call_add_dispatch_operation:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Channels: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The initial value of the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelDispatchOperation.Channels&lt;/tp:dbus-ref&gt;             property, containing the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Channel&lt;/tp:dbus-ref&gt;s             to be dispatched and their properties.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This can&apos;t be signalled to the approver through the Properties               parameter of this method, because Channels is not an immutable               property.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;This argument always contains all of the channels in the channel             dispatch operation, even if not all of them actually match             the &lt;tp:member-ref&gt;ApproverChannelFilter&lt;/tp:member-ref&gt;.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This seems the least bad way to handle such a situation;               see the discussion on               &lt;a href=&quot;http://bugs.freedesktop.org/show_bug.cgi?id=21090&quot;&gt;bug                 #21090&lt;/a&gt;.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;The actual channels to be dispatched may reduce as channels are             closed: this is signalled by &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelDispatchOperation.ChannelLost&lt;/tp:dbus-ref&gt;.           &lt;/p&gt;            &lt;p&gt;Approvers SHOULD connect to ChannelLost and &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelDispatchOperation.Finished&lt;/tp:dbus-ref&gt;.             (if desired) before returning from AddDispatchOperation, since             those signals are guaranteed not to be emitted until after all             AddDispatchOperation calls have returned (with success or failure)             or timed out.&lt;/p&gt;
 * @in_DispatchOperation: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelDispatchOperation&lt;/tp:dbus-ref&gt;             to be processed.&lt;/p&gt;
 * @in_Properties: Used to pass an 'in' argument: &lt;p&gt;Properties of the channel dispatch operation. The keys MUST be             fully qualified D-Bus property names. This MUST NOT include             properties that could change, SHOULD include as many properties as             possible given that constraint, and MUST include at least the             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelDispatchOperation&quot;&gt;Account&lt;/tp:dbus-ref&gt;,             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelDispatchOperation&quot;&gt;Connection&lt;/tp:dbus-ref&gt;             and &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelDispatchOperation&quot;&gt;PossibleHandlers&lt;/tp:dbus-ref&gt;             properties.&lt;/p&gt;
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
 * Start a AddDispatchOperation method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Called by the channel dispatcher when a ChannelDispatchOperation           in which the approver has registered an interest is created,           or when the approver starts up while such channel dispatch           operations already exist.&lt;/p&gt;          &lt;p&gt;The channel dispatcher SHOULD call this method on all approvers           at the same time. If an approver returns an error from this method,           the approver is assumed to be faulty.&lt;/p&gt;          &lt;p&gt;If no approvers return from this method           successfully (including situations where there are no matching           approvers at all), the channel dispatcher SHOULD consider this           to be an error, and recover by dispatching the channel to the           most preferred handler.&lt;/p&gt;          &lt;tp:rationale&gt;           Processes that aren&apos;t approvers (or don&apos;t at least ensure that there           is some approver) probably shouldn&apos;t be making connections           anyway, so there should always be at least one approver running.         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_client_approver_call_add_dispatch_operation (TpClient *proxy,
    gint timeout_ms,
    const GPtrArray *in_Channels,
    const gchar *in_DispatchOperation,
    GHashTable *in_Properties,
    tp_cli_client_approver_callback_for_add_dispatch_operation callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CLIENT_APPROVER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CLIENT (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "AddDispatchOperation",
          (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID)))), in_Channels,
          DBUS_TYPE_G_OBJECT_PATH, in_DispatchOperation,
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Properties,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "AddDispatchOperation", iface,
          _tp_cli_client_approver_invoke_callback_add_dispatch_operation,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "AddDispatchOperation",
              _tp_cli_client_approver_collect_callback_add_dispatch_operation,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID)))), in_Channels,
              DBUS_TYPE_G_OBJECT_PATH, in_DispatchOperation,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Properties,
              G_TYPE_INVALID));

      return data;
    }
}


/**
 * tp_cli_client_handler_callback_for_handle_channels:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a HandleChannels method call
 * succeeds or fails.
 */
static void
_tp_cli_client_handler_collect_callback_handle_channels (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_client_handler_invoke_callback_handle_channels (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_client_handler_callback_for_handle_channels callback = (tp_cli_client_handler_callback_for_handle_channels) generic_callback;

  if (error != NULL)
    {
      callback ((TpClient *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpClient *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_client_handler_call_handle_channels:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Account: Used to pass an 'in' argument: The           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Account&lt;/tp:dbus-ref&gt;           with which the channels are associated. The           well-known bus name to use is that of the           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;AccountManager&lt;/tp:dbus-ref&gt;.
 * @in_Connection: Used to pass an 'in' argument: The Connection with which the channels are associated. The           well-known bus name to use can be derived from this object           path by removing the leading &apos;/&apos; and replacing all subsequent           &apos;/&apos; by &apos;.&apos;.
 * @in_Channels: Used to pass an 'in' argument: The channels and their immutable properties. Their well-known           bus name is the same as that of the Connection.
 * @in_Requests_Satisfied: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The requests satisfied by these channels.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;If the handler implements Requests, this tells it               that these channels match previous &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Interface.Requests&quot;&gt;AddRequest&lt;/tp:dbus-ref&gt;               calls that it may have received.&lt;/p&gt;              &lt;p&gt;There can be more than one, if they were EnsureChannel               requests.&lt;/p&gt;           &lt;/tp:rationale&gt;
 * @in_User_Action_Time: Used to pass an 'in' argument: The time at which user action occurred, or 0 if this channel           is to be handled for some reason not involving user action.           Handlers SHOULD use this for focus-stealing prevention,           if applicable.
 * @in_Handler_Info: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Additional information about these channels. No keys are             currently defined.&lt;/p&gt;            &lt;p&gt;If keys are defined for this dictionary, all will be optional;             handlers MAY safely ignore any entry in this dictionary.&lt;/p&gt;
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
 * Start a HandleChannels method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Called by the channel dispatcher when this client should handle these           channels, or when this client should present channels that it is already           handling to the user (e.g. bring them into the foreground).&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;Clients are expected to know what channels they&apos;re already handling,             and which channel object path corresponds to which window or tab.             This can easily be done using a hash table keyed by channels&apos; object             paths.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;This method can raise any D-Bus error. If it does, the           handler is assumed to have failed or crashed, and the channel           dispatcher MUST recover in an implementation-specific way; it MAY           attempt to dispatch the channels to another handler, or close the           channels.&lt;/p&gt;          &lt;p&gt;If closing the channels, it is RECOMMENDED that the channel           dispatcher attempts to close the channels using           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Channel.Close&lt;/tp:dbus-ref&gt;,           but resorts to calling           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Channel.Interface.Destroyable.Destroy&lt;/tp:dbus-ref&gt;           (if available) or ignoring the channel (if not) if the same handler           repeatedly fails to handle channels.&lt;/p&gt;          &lt;p&gt;After HandleChannels returns successfully, the client process is           considered to be responsible for the channel until it its unique           name disappears from the bus.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;If a process has multiple Client bus names - some temporary and             some long-lived - and drops one of the temporary bus names in order             to reduce the set of channels that it will handle, any channels             that it is already handling should remain unaffected.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_client_handler_call_handle_channels (TpClient *proxy,
    gint timeout_ms,
    const gchar *in_Account,
    const gchar *in_Connection,
    const GPtrArray *in_Channels,
    const GPtrArray *in_Requests_Satisfied,
    guint64 in_User_Action_Time,
    GHashTable *in_Handler_Info,
    tp_cli_client_handler_callback_for_handle_channels callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CLIENT_HANDLER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CLIENT (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "HandleChannels",
          DBUS_TYPE_G_OBJECT_PATH, in_Account,
          DBUS_TYPE_G_OBJECT_PATH, in_Connection,
          (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID)))), in_Channels,
          dbus_g_type_get_collection ("GPtrArray", DBUS_TYPE_G_OBJECT_PATH), in_Requests_Satisfied,
          G_TYPE_UINT64, in_User_Action_Time,
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Handler_Info,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "HandleChannels", iface,
          _tp_cli_client_handler_invoke_callback_handle_channels,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "HandleChannels",
              _tp_cli_client_handler_collect_callback_handle_channels,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_OBJECT_PATH, in_Account,
              DBUS_TYPE_G_OBJECT_PATH, in_Connection,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID)))), in_Channels,
              dbus_g_type_get_collection ("GPtrArray", DBUS_TYPE_G_OBJECT_PATH), in_Requests_Satisfied,
              G_TYPE_UINT64, in_User_Action_Time,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Handler_Info,
              G_TYPE_INVALID));

      return data;
    }
}


/**
 * tp_cli_client_interface_requests_callback_for_add_request:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a AddRequest method call
 * succeeds or fails.
 */
static void
_tp_cli_client_interface_requests_collect_callback_add_request (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_client_interface_requests_invoke_callback_add_request (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_client_interface_requests_callback_for_add_request callback = (tp_cli_client_interface_requests_callback_for_add_request) generic_callback;

  if (error != NULL)
    {
      callback ((TpClient *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpClient *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_client_interface_requests_call_add_request:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Request: Used to pass an 'in' argument: The &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelRequest&lt;/tp:dbus-ref&gt;           object, which MUST have been returned by &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelDispatcher&quot;&gt;CreateChannel&lt;/tp:dbus-ref&gt;           or &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelDispatcher&quot;&gt;EnsureChannel&lt;/tp:dbus-ref&gt;           before this method is called.            &lt;tp:rationale&gt;             See those methods for the rationale of this ordering.           &lt;/tp:rationale&gt;
 * @in_Properties: Used to pass an 'in' argument: &lt;p&gt;Some of the properties of the ChannelRequest. To avoid race             conditions, this dictionary MUST NOT include properties whose             values could subsequently change. It SHOULD include as many             properties as possible, given that constraint.&lt;/p&gt;            &lt;p&gt;In particular, the properties &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelRequest&quot;&gt;Requests&lt;/tp:dbus-ref&gt;             and &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelRequest&quot;&gt;UserActionTime&lt;/tp:dbus-ref&gt;             MUST be included.&lt;/p&gt;
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
 * Start a AddRequest method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Called by the ChannelDispatcher to indicate that channels have been           requested, and that if the request is successful, they will probably           be handled by this Handler. The ChannelDispatcher SHOULD only           call this method on one handler per request.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;This allows the UI to start preparing to handle the channels             in advance (e.g. render a window with an &amp;quot;in progress&amp;quot; message),             improving perceived responsiveness.&lt;/p&gt;            &lt;p&gt;The use of &amp;quot;probably&amp;quot; is because you can&apos;t necessarily tell from             a channel request which handler will handle particular channels.             A reasonable heuristic would be to match the request against the             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Handler&quot;&gt;HandlerChannelFilter&lt;/tp:dbus-ref&gt;,             and respect the preferred handler (if any).&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;If the request succeeds and is given to the expected Handler,           the Requests_Satisfied parameter to           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Handler&quot;&gt;HandleChannels&lt;/tp:dbus-ref&gt;           can be used to match the channel to a previous AddRequest call.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;This lets the UI direct the channels to the window that it             already opened.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;If the request fails, the expected handler is notified by the           channel dispatcher calling its           &lt;tp:member-ref&gt;RemoveRequest&lt;/tp:member-ref&gt; method.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;This lets the UI close the window or display the error.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;The channel dispatcher SHOULD remember which handler was notified,           and if the channel request succeeds, it SHOULD dispatch the channels           to the expected handler, unless the channels do not match that           handler&apos;s &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Handler&quot;&gt;HandlerChannelFilter&lt;/tp:dbus-ref&gt;.           If the channels are not dispatched to the expected handler, the           handler that was expected is notified by the channel dispatcher           calling its &lt;tp:member-ref&gt;RemoveRequest&lt;/tp:member-ref&gt; method           with the NotYours error.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;Expected handling is for the UI to close the window it             previously opened.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;Handlers SHOULD NOT return an error from this method; errors           returned from this method SHOULD NOT alter the channel dispatcher&apos;s           behaviour.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;Calls to this method are merely a notification.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_client_interface_requests_call_add_request (TpClient *proxy,
    gint timeout_ms,
    const gchar *in_Request,
    GHashTable *in_Properties,
    tp_cli_client_interface_requests_callback_for_add_request callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CLIENT_INTERFACE_REQUESTS;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CLIENT (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "AddRequest",
          DBUS_TYPE_G_OBJECT_PATH, in_Request,
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Properties,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "AddRequest", iface,
          _tp_cli_client_interface_requests_invoke_callback_add_request,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "AddRequest",
              _tp_cli_client_interface_requests_collect_callback_add_request,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_OBJECT_PATH, in_Request,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Properties,
              G_TYPE_INVALID));

      return data;
    }
}


/**
 * tp_cli_client_interface_requests_callback_for_remove_request:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RemoveRequest method call
 * succeeds or fails.
 */
static void
_tp_cli_client_interface_requests_collect_callback_remove_request (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_client_interface_requests_invoke_callback_remove_request (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_client_interface_requests_callback_for_remove_request callback = (tp_cli_client_interface_requests_callback_for_remove_request) generic_callback;

  if (error != NULL)
    {
      callback ((TpClient *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpClient *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_client_interface_requests_call_remove_request:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Request: Used to pass an 'in' argument: The request that failed.
 * @in_Error: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The name of the D-Bus error with which the request failed.&lt;/p&gt;            &lt;p&gt;If this is &lt;code&gt;org.freedesktop.Telepathy.Error.NotYours&lt;/code&gt;,             this indicates that the request succeeded, but all the resulting             channels were given to some other handler.&lt;/p&gt;
 * @in_Message: Used to pass an 'in' argument: Any message supplied with the D-Bus error.
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
 * Start a RemoveRequest method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Called by the ChannelDispatcher to indicate that a request           previously passed to &lt;tp:member-ref&gt;AddRequest&lt;/tp:member-ref&gt;           has failed and should be disregarded.&lt;/p&gt;          &lt;p&gt;Handlers SHOULD NOT return an error from this method; errors           returned from this method SHOULD NOT alter the channel dispatcher&apos;s           behaviour.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;Calls to this method are merely a notification.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_client_interface_requests_call_remove_request (TpClient *proxy,
    gint timeout_ms,
    const gchar *in_Request,
    const gchar *in_Error,
    const gchar *in_Message,
    tp_cli_client_interface_requests_callback_for_remove_request callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CLIENT_INTERFACE_REQUESTS;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CLIENT (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "RemoveRequest",
          DBUS_TYPE_G_OBJECT_PATH, in_Request,
          G_TYPE_STRING, in_Error,
          G_TYPE_STRING, in_Message,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RemoveRequest", iface,
          _tp_cli_client_interface_requests_invoke_callback_remove_request,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RemoveRequest",
              _tp_cli_client_interface_requests_collect_callback_remove_request,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_OBJECT_PATH, in_Request,
              G_TYPE_STRING, in_Error,
              G_TYPE_STRING, in_Message,
              G_TYPE_INVALID));

      return data;
    }
}


/**
 * tp_cli_client_observer_callback_for_observe_channels:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a ObserveChannels method call
 * succeeds or fails.
 */
static void
_tp_cli_client_observer_collect_callback_observe_channels (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_client_observer_invoke_callback_observe_channels (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_client_observer_callback_for_observe_channels callback = (tp_cli_client_observer_callback_for_observe_channels) generic_callback;

  if (error != NULL)
    {
      callback ((TpClient *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpClient *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_client_observer_call_observe_channels:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Account: Used to pass an 'in' argument: The           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Account&lt;/tp:dbus-ref&gt;           with which the channels are associated. The           well-known bus name to use is that of the           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;AccountManager&lt;/tp:dbus-ref&gt;.
 * @in_Connection: Used to pass an 'in' argument: The           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection&lt;/tp:dbus-ref&gt;           with which the channels are associated. The           well-known bus name to use can be derived from this object           path by removing the leading &apos;/&apos; and replacing all subsequent           &apos;/&apos; by &apos;.&apos;.
 * @in_Channels: Used to pass an 'in' argument: The &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Channel&lt;/tp:dbus-ref&gt;s           and their properties. Their well-known bus names are all the same as           that of the Connection.
 * @in_Dispatch_Operation: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The path to the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelDispatchOperation&lt;/tp:dbus-ref&gt;             for these channels, or the special value &apos;/&apos; if there is no             ChannelDispatchOperation (because the channels were requested, not             incoming).&lt;/p&gt;            &lt;p&gt;If the Observer calls &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelDispatchOperation&quot;&gt;Claim&lt;/tp:dbus-ref&gt;             or &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelDispatchOperation&quot;&gt;HandleWith&lt;/tp:dbus-ref&gt;             on the dispatch operation, it MUST be careful to avoid deadlock,             since these methods cannot return until the Observer has returned             from &lt;tp:member-ref&gt;ObserveChannels&lt;/tp:member-ref&gt;.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This allows an Observer to &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ChannelDispatchOperation&quot;&gt;Claim&lt;/tp:dbus-ref&gt;               a set of channels without having to match up calls to this method               with calls to &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Approver&quot;&gt;AddDispatchOperation&lt;/tp:dbus-ref&gt;.&lt;/p&gt;           &lt;/tp:rationale&gt;
 * @in_Requests_Satisfied: Used to pass an 'in' argument: The requests satisfied by these channels.            &lt;tp:rationale&gt;             If the same process is an Observer and a Handler, it can be useful             to be given this information as soon as possible (it will also             be passed to &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client&quot;&gt;Handler.HandleChannels&lt;/tp:dbus-ref&gt;).           &lt;/tp:rationale&gt;
 * @in_Observer_Info: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Additional information about these channels. No keys are             currently defined.&lt;/p&gt;            &lt;p&gt;If keys are defined for this dictionary, all will be optional;             observers MAY safely ignore any entry in this dictionary.&lt;/p&gt;
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
 * Start a ObserveChannels method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Called by the channel dispatcher when channels in which the           observer has registered an interest are announced in a &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection.Interface.Requests&quot;&gt;NewChannels&lt;/tp:dbus-ref&gt;           signal.&lt;/p&gt;          &lt;p&gt;If the same NewChannels signal announces some channels that match           the filter, and some that do not, then only a subset of the channels           (those that do match the filter) are passed to this method.&lt;/p&gt;          &lt;p&gt;If the channel dispatcher will split up the channels from a single           NewChannels signal and dispatch them separately (for instance           because no installed Handler can handle all of them), it will call           ObserveChannels several times.&lt;/p&gt;          &lt;p&gt;The observer MUST NOT return from this method call until it is ready           for a handler for the channel to run (which may change the channel&apos;s           state).&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The channel dispatcher must wait for observers to start up,             to avoid the following race: text channel logger (observer) gets             ObserveChannels, text channel handler gets             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Handler&quot;&gt;HandleChannels&lt;/tp:dbus-ref&gt;             channel handler starts up faster and acknowledges messages,             logger never sees those messages.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;The channel dispatcher SHOULD NOT change its behaviour based on           whether this method succeeds or fails: there are no defined D-Bus           errors for this method, and if it fails, this only indicates that           an Observer is somehow broken.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;The expected error response in the channel dispatcher is to             log a warning, and otherwise continue as though this method             had succeeded.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_client_observer_call_observe_channels (TpClient *proxy,
    gint timeout_ms,
    const gchar *in_Account,
    const gchar *in_Connection,
    const GPtrArray *in_Channels,
    const gchar *in_Dispatch_Operation,
    const GPtrArray *in_Requests_Satisfied,
    GHashTable *in_Observer_Info,
    tp_cli_client_observer_callback_for_observe_channels callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CLIENT_OBSERVER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CLIENT (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "ObserveChannels",
          DBUS_TYPE_G_OBJECT_PATH, in_Account,
          DBUS_TYPE_G_OBJECT_PATH, in_Connection,
          (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID)))), in_Channels,
          DBUS_TYPE_G_OBJECT_PATH, in_Dispatch_Operation,
          dbus_g_type_get_collection ("GPtrArray", DBUS_TYPE_G_OBJECT_PATH), in_Requests_Satisfied,
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Observer_Info,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "ObserveChannels", iface,
          _tp_cli_client_observer_invoke_callback_observe_channels,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "ObserveChannels",
              _tp_cli_client_observer_collect_callback_observe_channels,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_OBJECT_PATH, in_Account,
              DBUS_TYPE_G_OBJECT_PATH, in_Connection,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", DBUS_TYPE_G_OBJECT_PATH, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), G_TYPE_INVALID)))), in_Channels,
              DBUS_TYPE_G_OBJECT_PATH, in_Dispatch_Operation,
              dbus_g_type_get_collection ("GPtrArray", DBUS_TYPE_G_OBJECT_PATH), in_Requests_Satisfied,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Observer_Info,
              G_TYPE_INVALID));

      return data;
    }
}


/*
 * tp_cli_client_add_signals:
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
tp_cli_client_add_signals (TpProxy *self G_GNUC_UNUSED,
    guint quark,
    DBusGProxy *proxy,
    gpointer unused G_GNUC_UNUSED)
{
}
