/* We don't want gtkdoc scanning this file, it'll get
 * confused by seeing function definitions, so mark it as: */
/*<private_header>*/

static inline void
tp_cli_add_signals_for_account_manager (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "AccountRemoved",
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "AccountValidityChanged",
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID);
}


/**
 * tp_cli_account_manager_signal_callback_account_removed:
 * @proxy: The proxy on which tp_cli_account_manager_connect_to_account_removed ()
 *  was called
 * @arg_Account: An Account, which must not be used any more.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal AccountRemoved.
 */
static void
_tp_cli_account_manager_collect_args_of_account_removed (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Account,
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
  g_value_set_boxed (args->values + 0, arg_Account);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_account_manager_invoke_callback_for_account_removed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_account_manager_signal_callback_account_removed callback =
      (tp_cli_account_manager_signal_callback_account_removed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_account_manager_connect_to_account_removed:
 * @proxy: A #TpAccountManager or subclass
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
 * Connect a handler to the signal AccountRemoved.
 *
 * The given account has been removed.          &lt;tp:rationale&gt;           This is effectively change notification for the valid and invalid           accounts lists. On emission of this signal, the Account indicated           will no longer be present in either of the lists.         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_account_manager_connect_to_account_removed (TpAccountManager *proxy,
    tp_cli_account_manager_signal_callback_account_removed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_ACCOUNT_MANAGER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_ACCOUNT_MANAGER, "AccountRemoved",
      expected_types,
      G_CALLBACK (_tp_cli_account_manager_collect_args_of_account_removed),
      _tp_cli_account_manager_invoke_callback_for_account_removed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_account_manager_signal_callback_account_validity_changed:
 * @proxy: The proxy on which tp_cli_account_manager_connect_to_account_validity_changed ()
 *  was called
 * @arg_Account: An Account.
 * @arg_Valid: True if the account is now valid.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal AccountValidityChanged.
 */
static void
_tp_cli_account_manager_collect_args_of_account_validity_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Account,
    gboolean arg_Valid,
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
  g_value_set_boxed (args->values + 0, arg_Account);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_BOOLEAN);
  g_value_set_boolean (args->values + 1, arg_Valid);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_account_manager_invoke_callback_for_account_validity_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_account_manager_signal_callback_account_validity_changed callback =
      (tp_cli_account_manager_signal_callback_account_validity_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      g_value_get_boolean (args->values + 1),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_account_manager_connect_to_account_validity_changed:
 * @proxy: A #TpAccountManager or subclass
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
 * Connect a handler to the signal AccountValidityChanged.
 *
 * The validity of the given account has changed. New accounts are         also indicated by this signal, as an account validity change         (usually to True) on an account that did not previously exist.          &lt;tp:rationale&gt;           This is effectively change notification for the valid and invalid           accounts lists.         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_account_manager_connect_to_account_validity_changed (TpAccountManager *proxy,
    tp_cli_account_manager_signal_callback_account_validity_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_ACCOUNT_MANAGER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_ACCOUNT_MANAGER, "AccountValidityChanged",
      expected_types,
      G_CALLBACK (_tp_cli_account_manager_collect_args_of_account_validity_changed),
      _tp_cli_account_manager_invoke_callback_for_account_validity_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_account_manager_callback_for_create_account:
 * @proxy: the proxy on which the call was made
 * @out_Account: Used to return an 'out' argument if @error is %NULL: The new &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Account&lt;/tp:dbus-ref&gt;.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a CreateAccount method call
 * succeeds or fails.
 */
static void
_tp_cli_account_manager_collect_callback_create_account (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_Account;

  dbus_g_proxy_end_call (proxy, call, &error,
      DBUS_TYPE_G_OBJECT_PATH, &out_Account,
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
  g_value_take_boxed (args->values + 0, out_Account);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_account_manager_invoke_callback_create_account (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_account_manager_callback_for_create_account callback = (tp_cli_account_manager_callback_for_create_account) generic_callback;

  if (error != NULL)
    {
      callback ((TpAccountManager *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpAccountManager *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_account_manager_call_create_account:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Connection_Manager: Used to pass an 'in' argument: The name of the connection manager, e.g. &amp;quot;salut&amp;quot;.
 * @in_Protocol: Used to pass an 'in' argument: The protocol, e.g. &amp;quot;local-xmpp&amp;quot;.
 * @in_Display_Name: Used to pass an 'in' argument: The initial value of the new account&apos;s &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Account&quot;&gt;DisplayName&lt;/tp:dbus-ref&gt;           property. The account manager SHOULD modify this to make it unique if           an Account already exists with the same display name, for instance by           appending a number or the &apos;account&apos; parameter. Account manager           implementations SHOULD accept an empty string, but account editing           user interfaces should avoid passing an empty string for this           parameter.            &lt;tp:rationale&gt;             &lt;p&gt;The account creation UI may ask the user for a name for the new               account. If the author of the UI chooses not to do this, the               account creation UI is better able to suggest a default display               name because it has protocol-specific knowledge which the account               manager does not.&lt;/p&gt;              &lt;p&gt;The account manager always knows the complete list of accounts so               it can easily tell whether it should append something to the               display name to avoid presenting two identically-named accounts to               the user.&lt;/p&gt;           &lt;/tp:rationale&gt;
 * @in_Parameters: Used to pass an 'in' argument: Initial parameter values, as would be passed to           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.ConnectionManager&quot;&gt;RequestConnection&lt;/tp:dbus-ref&gt;.
 * @in_Properties: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The values of any other properties to be set immediately on the             new Account.&lt;/p&gt;            &lt;p&gt;Only the properties mentioned in             &lt;tp:member-ref&gt;SupportedAccountProperties&lt;/tp:member-ref&gt; are             acceptable here. In particular, the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Account&quot;&gt;DisplayName&lt;/tp:dbus-ref&gt;             and &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Account&quot;&gt;Parameters&lt;/tp:dbus-ref&gt;             properties are never allowed here, since they are set using the other             arguments to this method.&lt;/p&gt;            &lt;p&gt;Account manager implementations SHOULD support creating accounts             with an empty value for this argument.&lt;/p&gt;
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
 * Start a CreateAccount method call.
 *
 * Request the creation of a new &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Account&lt;/tp:dbus-ref&gt;. The         account manager SHOULD NOT allow invalid accounts to be created.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_account_manager_call_create_account (TpAccountManager *proxy,
    gint timeout_ms,
    const gchar *in_Connection_Manager,
    const gchar *in_Protocol,
    const gchar *in_Display_Name,
    GHashTable *in_Parameters,
    GHashTable *in_Properties,
    tp_cli_account_manager_callback_for_create_account callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_ACCOUNT_MANAGER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_ACCOUNT_MANAGER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "CreateAccount",
          G_TYPE_STRING, in_Connection_Manager,
          G_TYPE_STRING, in_Protocol,
          G_TYPE_STRING, in_Display_Name,
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Parameters,
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Properties,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "CreateAccount", iface,
          _tp_cli_account_manager_invoke_callback_create_account,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "CreateAccount",
              _tp_cli_account_manager_collect_callback_create_account,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Connection_Manager,
              G_TYPE_STRING, in_Protocol,
              G_TYPE_STRING, in_Display_Name,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Parameters,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Properties,
              G_TYPE_INVALID));

      return data;
    }
}


/*
 * tp_cli_account_manager_add_signals:
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
tp_cli_account_manager_add_signals (TpProxy *self G_GNUC_UNUSED,
    guint quark,
    DBusGProxy *proxy,
    gpointer unused G_GNUC_UNUSED)
{
  if (quark == TP_IFACE_QUARK_ACCOUNT_MANAGER)
    tp_cli_add_signals_for_account_manager (proxy);
}
