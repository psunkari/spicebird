/* We don't want gtkdoc scanning this file, it'll get
 * confused by seeing function definitions, so mark it as: */
/*<private_header>*/

static inline void
tp_cli_add_signals_for_account (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "Removed",
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "AccountPropertyChanged",
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)),
      G_TYPE_INVALID);
}


/**
 * tp_cli_account_signal_callback_removed:
 * @proxy: The proxy on which tp_cli_account_connect_to_removed ()
 *  was called
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal Removed.
 */
static void
_tp_cli_account_invoke_callback_for_removed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_account_signal_callback_removed callback =
      (tp_cli_account_signal_callback_removed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      user_data,
      weak_object);

  if (args != NULL)
    g_value_array_free (args);

  g_object_unref (tpproxy);
}
/**
 * tp_cli_account_connect_to_removed:
 * @proxy: A #TpAccount or subclass
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
 * Connect a handler to the signal Removed.
 *
 * This account has been removed.          &lt;tp:rationale&gt;           This is redundant with &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.AccountManager&quot;&gt;AccountRemoved&lt;/tp:dbus-ref&gt;,           but it&apos;s still worth having,           to avoid having to bind to AccountManager.AccountRemoved to tell           you whether your Account is valid — ideally, an account-editing UI           should only care about a single Account.         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_account_connect_to_removed (TpAccount *proxy,
    tp_cli_account_signal_callback_removed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[1] = {
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_ACCOUNT (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_ACCOUNT, "Removed",
      expected_types,
      NULL, /* no args => no collector function */
      _tp_cli_account_invoke_callback_for_removed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_account_signal_callback_account_property_changed:
 * @proxy: The proxy on which tp_cli_account_connect_to_account_property_changed ()
 *  was called
 * @arg_Properties: A map from property names in this namespace (e.g.           &lt;tp:member-ref&gt;Nickname&lt;/tp:member-ref&gt;) to           values. Properties whose values have not changed SHOULD be           omitted, but this need not be done.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal AccountPropertyChanged.
 */
static void
_tp_cli_account_collect_args_of_account_property_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    GHashTable *arg_Properties,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)));
  g_value_set_boxed (args->values + 0, arg_Properties);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_account_invoke_callback_for_account_property_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_account_signal_callback_account_property_changed callback =
      (tp_cli_account_signal_callback_account_property_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_account_connect_to_account_property_changed:
 * @proxy: A #TpAccount or subclass
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
 * Connect a handler to the signal AccountPropertyChanged.
 *
 * The values of one or more properties on this interface (that do not         specify that this signal does not apply to them) may have changed.         This does not cover properties of other interfaces, which must         provide their own change notification if appropriate.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_account_connect_to_account_property_changed (TpAccount *proxy,
    tp_cli_account_signal_callback_account_property_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_ACCOUNT (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_ACCOUNT, "AccountPropertyChanged",
      expected_types,
      G_CALLBACK (_tp_cli_account_collect_args_of_account_property_changed),
      _tp_cli_account_invoke_callback_for_account_property_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_account_callback_for_remove:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Remove method call
 * succeeds or fails.
 */
static void
_tp_cli_account_collect_callback_remove (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_account_invoke_callback_remove (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_account_callback_for_remove callback = (tp_cli_account_callback_for_remove) generic_callback;

  if (error != NULL)
    {
      callback ((TpAccount *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpAccount *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_account_call_remove:
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
 * Start a Remove method call.
 *
 * Delete the account.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_account_call_remove (TpAccount *proxy,
    gint timeout_ms,
    tp_cli_account_callback_for_remove callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_ACCOUNT;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_ACCOUNT (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Remove",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Remove", iface,
          _tp_cli_account_invoke_callback_remove,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Remove",
              _tp_cli_account_collect_callback_remove,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}


/**
 * tp_cli_account_callback_for_update_parameters:
 * @proxy: the proxy on which the call was made
 * @out_Reconnect_Required: Used to return an 'out' argument if @error is %NULL: A list of the names of parameters with changes that will not take           effect until the account is reconnected (this may be empty, e.g. if           all the parameters are D-Bus properties or parameters for which the           account manager has specific support). User interfaces that           require &amp;quot;instant apply&amp;quot; semantics MAY call           &lt;tp:member-ref&gt;Reconnect&lt;/tp:member-ref&gt; in response to receiving           a non-empty list.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a UpdateParameters method call
 * succeeds or fails.
 */
static void
_tp_cli_account_collect_callback_update_parameters (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar **out_Reconnect_Required;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRV, &out_Reconnect_Required,
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
  g_value_take_boxed (args->values + 0, out_Reconnect_Required);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_account_invoke_callback_update_parameters (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_account_callback_for_update_parameters callback = (tp_cli_account_callback_for_update_parameters) generic_callback;

  if (error != NULL)
    {
      callback ((TpAccount *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpAccount *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_account_call_update_parameters:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Set: Used to pass an 'in' argument: A mapping from parameter names to their values. These parameters           should be stored for future use.
 * @in_Unset: Used to pass an 'in' argument: A list of the names of parameters to be removed from the set of           stored values, allowing the default values to be used.           If the given parameters were not, in fact, stored, or even if they           do not exist at all, the account manager MUST accept this without           error.
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
 * Start a UpdateParameters method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Change the value of the &lt;tp:member-ref&gt;Parameters&lt;/tp:member-ref&gt;           property.&lt;/p&gt;          &lt;p&gt;If any of the changed parameters&apos;           &lt;tp:type&gt;Conn_Mgr_Param_Flags&lt;/tp:type&gt; include           &lt;code&gt;DBus_Property&lt;/code&gt;, the change will be applied to the           corresponding D-Bus Property on the active           &lt;tp:member-ref&gt;Connection&lt;/tp:member-ref&gt;, if there is one. Changes to           other parameters will not take effect until the next time the account           is disconnected and reconnected.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;In general, reconnecting is a destructive operation that shouldn&apos;t             happen as a side-effect. In particular, migration tools that             twiddle the settings of all accounts shouldn&apos;t cause an automatic             disconnect and reconnect.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_account_call_update_parameters (TpAccount *proxy,
    gint timeout_ms,
    GHashTable *in_Set,
    const gchar **in_Unset,
    tp_cli_account_callback_for_update_parameters callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_ACCOUNT;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_ACCOUNT (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "UpdateParameters",
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Set,
          G_TYPE_STRV, in_Unset,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "UpdateParameters", iface,
          _tp_cli_account_invoke_callback_update_parameters,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "UpdateParameters",
              _tp_cli_account_collect_callback_update_parameters,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Set,
              G_TYPE_STRV, in_Unset,
              G_TYPE_INVALID));

      return data;
    }
}


/**
 * tp_cli_account_callback_for_reconnect:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Reconnect method call
 * succeeds or fails.
 */
static void
_tp_cli_account_collect_callback_reconnect (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_account_invoke_callback_reconnect (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_account_callback_for_reconnect callback = (tp_cli_account_callback_for_reconnect) generic_callback;

  if (error != NULL)
    {
      callback ((TpAccount *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpAccount *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_account_call_reconnect:
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
 * Start a Reconnect method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Re-connect this account. If the account is currently disconnected           and the requested presence is offline, or if the account           is not &lt;tp:member-ref&gt;Enabled&lt;/tp:member-ref&gt; or not           &lt;tp:member-ref&gt;Valid&lt;/tp:member-ref&gt;, this does nothing.&lt;/p&gt;          &lt;p&gt;If the account is disconnected and the requested presence is not           offline, this forces an attempt to connect with the requested           presence immediately.&lt;/p&gt;          &lt;p&gt;If the account is connecting or connected, this is equivalent to           remembering the current value of           &lt;tp:member-ref&gt;RequestedPresence&lt;/tp:member-ref&gt;, setting its value           to (OFFLINE, &amp;quot;offline&amp;quot;, &amp;quot;&amp;quot;), waiting for the change to take effect,           then setting its value to the value that was previously           remembered.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;Clients desiring &amp;quot;instant apply&amp;quot; semantics for CM parameters MAY             call this method to achieve that.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;In particular, if the account&apos;s           &lt;tp:member-ref&gt;Connection&lt;/tp:member-ref&gt; is in the Connecting           state, calling this method causes the attempt to connect to be           aborted and re-tried.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;This is necessary to ensure that the new parameters are             picked up.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_account_call_reconnect (TpAccount *proxy,
    gint timeout_ms,
    tp_cli_account_callback_for_reconnect callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_ACCOUNT;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_ACCOUNT (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Reconnect",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Reconnect", iface,
          _tp_cli_account_invoke_callback_reconnect,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Reconnect",
              _tp_cli_account_collect_callback_reconnect,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_INVALID));

      return data;
    }
}


static inline void
tp_cli_add_signals_for_account_interface_avatar (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "AvatarChanged",
      G_TYPE_INVALID);
}


/**
 * tp_cli_account_interface_avatar_signal_callback_avatar_changed:
 * @proxy: The proxy on which tp_cli_account_interface_avatar_connect_to_avatar_changed ()
 *  was called
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal AvatarChanged.
 */
static void
_tp_cli_account_interface_avatar_invoke_callback_for_avatar_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_account_interface_avatar_signal_callback_avatar_changed callback =
      (tp_cli_account_interface_avatar_signal_callback_avatar_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      user_data,
      weak_object);

  if (args != NULL)
    g_value_array_free (args);

  g_object_unref (tpproxy);
}
/**
 * tp_cli_account_interface_avatar_connect_to_avatar_changed:
 * @proxy: A #TpAccount or subclass
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
 * Connect a handler to the signal AvatarChanged.
 *
 * Emitted when the Avatar property changes.          &lt;tp:rationale&gt;The avatar itself is deliberately not included in this           signal, to reduce bus traffic in the (likely common) case where no           running application cares about the user&apos;s own avatar.&lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_account_interface_avatar_connect_to_avatar_changed (TpAccount *proxy,
    tp_cli_account_interface_avatar_signal_callback_avatar_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[1] = {
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_ACCOUNT (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_ACCOUNT_INTERFACE_AVATAR, "AvatarChanged",
      expected_types,
      NULL, /* no args => no collector function */
      _tp_cli_account_interface_avatar_invoke_callback_for_avatar_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/*
 * tp_cli_account_add_signals:
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
tp_cli_account_add_signals (TpProxy *self G_GNUC_UNUSED,
    guint quark,
    DBusGProxy *proxy,
    gpointer unused G_GNUC_UNUSED)
{
  if (quark == TP_IFACE_QUARK_ACCOUNT)
    tp_cli_add_signals_for_account (proxy);
  if (quark == TP_IFACE_QUARK_ACCOUNT_INTERFACE_AVATAR)
    tp_cli_add_signals_for_account_interface_avatar (proxy);
}
