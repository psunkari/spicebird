/* We don't want gtkdoc scanning this file, it'll get
 * confused by seeing function definitions, so mark it as: */
/*<private_header>*/

static inline void
tp_cli_add_signals_for_connection_manager (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "NewConnection",
      G_TYPE_STRING,
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_STRING,
      G_TYPE_INVALID);
}


/**
 * tp_cli_connection_manager_signal_callback_new_connection:
 * @proxy: The proxy on which tp_cli_connection_manager_connect_to_new_connection ()
 *  was called
 * @arg_Bus_Name: The D-Bus service where the connection object can be found
 * @arg_Object_Path: The object path of the Connection object on this service
 * @arg_Protocol: The identifier for the protocol this connection uses
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal NewConnection.
 */
static void
_tp_cli_connection_manager_collect_args_of_new_connection (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Bus_Name,
    const gchar *arg_Object_Path,
    const gchar *arg_Protocol,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (3);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 3; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_STRING);
  g_value_set_string (args->values + 0, arg_Bus_Name);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, DBUS_TYPE_G_OBJECT_PATH);
  g_value_set_boxed (args->values + 1, arg_Object_Path);

  g_value_unset (args->values + 2);
  g_value_init (args->values + 2, G_TYPE_STRING);
  g_value_set_string (args->values + 2, arg_Protocol);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_connection_manager_invoke_callback_for_new_connection (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_manager_signal_callback_new_connection callback =
      (tp_cli_connection_manager_signal_callback_new_connection) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_string (args->values + 0),
      g_value_get_boxed (args->values + 1),
      g_value_get_string (args->values + 2),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_connection_manager_connect_to_new_connection:
 * @proxy: A #TpConnectionManager or subclass
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
 * Connect a handler to the signal NewConnection.
 *
 * Emitted when a new &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection&lt;/tp:dbus-ref&gt; object         is created.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_connection_manager_connect_to_new_connection (TpConnectionManager *proxy,
    tp_cli_connection_manager_signal_callback_new_connection callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[4] = {
      G_TYPE_STRING,
      DBUS_TYPE_G_OBJECT_PATH,
      G_TYPE_STRING,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_CONNECTION_MANAGER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_CONNECTION_MANAGER, "NewConnection",
      expected_types,
      G_CALLBACK (_tp_cli_connection_manager_collect_args_of_new_connection),
      _tp_cli_connection_manager_invoke_callback_for_new_connection,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_connection_manager_callback_for_get_parameters:
 * @proxy: the proxy on which the call was made
 * @out_Parameters: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structs representing possible parameters.
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetParameters method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_manager_collect_callback_get_parameters (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GPtrArray *out_Parameters;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_VALUE, G_TYPE_INVALID)))), &out_Parameters,
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
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_VALUE, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Parameters);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_manager_invoke_callback_get_parameters (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_manager_callback_for_get_parameters callback = (tp_cli_connection_manager_callback_for_get_parameters) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnectionManager *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnectionManager *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_manager_call_get_parameters:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Protocol: Used to pass an 'in' argument: The required protocol name
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
 * Start a GetParameters method call.
 *
 * Get a list of the parameters which must or may be provided to the         &lt;tp:member-ref&gt;RequestConnection&lt;/tp:member-ref&gt; method when connecting         to the given protocol,         or registering (the boolean &amp;quot;register&amp;quot; parameter is available,         and set to true).
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_manager_call_get_parameters (TpConnectionManager *proxy,
    gint timeout_ms,
    const gchar *in_Protocol,
    tp_cli_connection_manager_callback_for_get_parameters callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_MANAGER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION_MANAGER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetParameters",
          G_TYPE_STRING, in_Protocol,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetParameters", iface,
          _tp_cli_connection_manager_invoke_callback_get_parameters,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetParameters",
              _tp_cli_connection_manager_collect_callback_get_parameters,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Protocol,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GPtrArray **out_Parameters;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_manager_run_state_get_parameters;
static void
_tp_cli_connection_manager_finish_running_get_parameters (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_manager_run_state_get_parameters *state = user_data;

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

  if (state->out_Parameters != NULL)
    *state->out_Parameters = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_manager_run_get_parameters:
 * @proxy: A #TpConnectionManager or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Protocol: Used to pass an 'in' argument: The required protocol name
 * @out_Parameters: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of structs representing possible parameters.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetParameters and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Get a list of the parameters which must or may be provided to the         &lt;tp:member-ref&gt;RequestConnection&lt;/tp:member-ref&gt; method when connecting         to the given protocol,         or registering (the boolean &amp;quot;register&amp;quot; parameter is available,         and set to true).
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_manager_run_get_parameters (TpConnectionManager *proxy,
    gint timeout_ms,
    const gchar *in_Protocol,
    GPtrArray **out_Parameters,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_MANAGER;
  TpProxyPendingCall *pc;
  _tp_cli_connection_manager_run_state_get_parameters state = {
      NULL /* loop */, error,
    out_Parameters,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION_MANAGER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetParameters", iface,
      _tp_cli_connection_manager_finish_running_get_parameters,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetParameters",
          _tp_cli_connection_manager_collect_callback_get_parameters,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_STRING, in_Protocol,
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
 * tp_cli_connection_manager_callback_for_list_protocols:
 * @proxy: the proxy on which the call was made
 * @out_Protocols: Used to return an 'out' argument if @error is %NULL: A array of string protocol identifiers supported by this manager
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a ListProtocols method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_manager_collect_callback_list_protocols (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar **out_Protocols;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRV, &out_Protocols,
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
  g_value_take_boxed (args->values + 0, out_Protocols);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_manager_invoke_callback_list_protocols (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_manager_callback_for_list_protocols callback = (tp_cli_connection_manager_callback_for_list_protocols) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnectionManager *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnectionManager *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_manager_call_list_protocols:
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
 * Start a ListProtocols method call.
 *
 * Get a list of protocol identifiers that are implemented by this         connection manager.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_manager_call_list_protocols (TpConnectionManager *proxy,
    gint timeout_ms,
    tp_cli_connection_manager_callback_for_list_protocols callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_MANAGER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION_MANAGER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "ListProtocols",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "ListProtocols", iface,
          _tp_cli_connection_manager_invoke_callback_list_protocols,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "ListProtocols",
              _tp_cli_connection_manager_collect_callback_list_protocols,
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
    gchar ***out_Protocols;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_manager_run_state_list_protocols;
static void
_tp_cli_connection_manager_finish_running_list_protocols (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_manager_run_state_list_protocols *state = user_data;

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

  if (state->out_Protocols != NULL)
    *state->out_Protocols = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_manager_run_list_protocols:
 * @proxy: A #TpConnectionManager or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Protocols: Used to return an 'out' argument if %TRUE is returned: A array of string protocol identifiers supported by this manager
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method ListProtocols and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Get a list of protocol identifiers that are implemented by this         connection manager.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_manager_run_list_protocols (TpConnectionManager *proxy,
    gint timeout_ms,
    gchar ***out_Protocols,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_MANAGER;
  TpProxyPendingCall *pc;
  _tp_cli_connection_manager_run_state_list_protocols state = {
      NULL /* loop */, error,
    out_Protocols,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION_MANAGER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "ListProtocols", iface,
      _tp_cli_connection_manager_finish_running_list_protocols,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "ListProtocols",
          _tp_cli_connection_manager_collect_callback_list_protocols,
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
 * tp_cli_connection_manager_callback_for_request_connection:
 * @proxy: the proxy on which the call was made
 * @out_Bus_Name: Used to return an 'out' argument if @error is %NULL: A D-Bus service name where the new Connection object can be found
 * @out_Object_Path: Used to return an 'out' argument if @error is %NULL: The D-Bus object path to the Connection on this service
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a RequestConnection method call
 * succeeds or fails.
 */
static void
_tp_cli_connection_manager_collect_callback_request_connection (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_Bus_Name;
  gchar *out_Object_Path;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRING, &out_Bus_Name,
      DBUS_TYPE_G_OBJECT_PATH, &out_Object_Path,
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
  g_value_init (args->values + 0, G_TYPE_STRING);
  g_value_take_string (args->values + 0, out_Bus_Name);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, DBUS_TYPE_G_OBJECT_PATH);
  g_value_take_boxed (args->values + 1, out_Object_Path);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_connection_manager_invoke_callback_request_connection (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_connection_manager_callback_for_request_connection callback = (tp_cli_connection_manager_callback_for_request_connection) generic_callback;

  if (error != NULL)
    {
      callback ((TpConnectionManager *) self,
          NULL,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpConnectionManager *) self,
      g_value_get_string (args->values + 0),
      g_value_get_boxed (args->values + 1),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_manager_call_request_connection:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Protocol: Used to pass an 'in' argument: The protocol identifier
 * @in_Parameters: Used to pass an 'in' argument: A dictionary mapping parameter names to values of the appropriate           type, as indicated by &lt;tp:member-ref&gt;GetParameters&lt;/tp:member-ref&gt;           and the above well-known list.
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
 * Start a RequestConnection method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request a           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection&lt;/tp:dbus-ref&gt;           object representing a given account on a given           protocol with the given parameters. The method returns the bus name           and the object path where the new Connection object can be found,           which should have the status of Connection_Status_Disconnected, to           allow signal handlers to be attached before connecting is started           with the           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection&quot;&gt;Connect&lt;/tp:dbus-ref&gt;           method.&lt;/p&gt;          &lt;p&gt;The parameters which must and may be provided in the parameters         dictionary can be discovered with the         &lt;tp:member-ref&gt;GetParameters&lt;/tp:member-ref&gt; method. These         parameters, their types, and their default values may be cached         in files so that all available connection managers do not need to be         started to discover which protocols are available.&lt;/p&gt;          &lt;p&gt;To request values for these parameters from the user, a client must         have prior knowledge of the meaning of the parameter names, so the         following well-known names and types should be used where appropriate:&lt;/p&gt;          &lt;dl&gt;           &lt;dt&gt;account (s)&lt;/dt&gt;           &lt;dd&gt;The identifier for the user&apos;s account on the server&lt;/dd&gt;            &lt;dt&gt;server (s)&lt;/dt&gt;           &lt;dd&gt;A fully qualified domain name or numeric IPv4 or IPv6 address.             Using the fully-qualified domain name form is recommended whenever             possible. If this parameter is specified and the account for that             protocol also specifies a server, this parameter should override             that in the user id.&lt;/dd&gt;            &lt;dt&gt;port (q)&lt;/dt&gt;           &lt;dd&gt;A TCP or UDP port number. If this parameter is specified and the             account for that protocol also specifies a port, this parameter             should override that in the account.&lt;/dd&gt;            &lt;dt&gt;password (s)&lt;/dt&gt;           &lt;dd&gt;A password associated with the account.&lt;/dd&gt;            &lt;dt&gt;require-encryption (b)&lt;/dt&gt;           &lt;dd&gt;Require encryption for this connection. A connection should fail             to connect if require-encryption is set and an encrypted connection             is not possible.&lt;/dd&gt;            &lt;dt&gt;register (b)&lt;/dt&gt;           &lt;dd&gt;This account should be created on the server if it does not             already exist.&lt;/dd&gt;            &lt;dt&gt;ident (s)&lt;/dt&gt;           &lt;dd&gt;The local username to report to the server if necessary, such as             in IRC.&lt;/dd&gt;            &lt;dt&gt;fullname (s)&lt;/dt&gt;           &lt;dd&gt;The user&apos;s full name if the service requires this when             authenticating or registering.&lt;/dd&gt;            &lt;dt&gt;stun-server (s)&lt;/dt&gt;           &lt;dd&gt;The IP address or FQDN of a STUN server to use for NAT traversal,             without any &amp;quot;:port&amp;quot; suffix.&lt;/dd&gt;            &lt;dt&gt;stun-port (q)&lt;/dt&gt;           &lt;dd&gt;The UDP port number on the stun-server to use for STUN. Only             significant if the stun-server is also supplied.&lt;/dd&gt;            &lt;dt&gt;keepalive-interval (u)&lt;/dt&gt;           &lt;dd&gt;The time in seconds between pings sent to the server to ensure             that the connection is still alive, or &lt;tt&gt;0&lt;/tt&gt; to disable such             pings.&lt;/dd&gt;         &lt;/dl&gt;          &lt;p&gt;Every successful RequestConnection call will cause the emission of a         &lt;tp:member-ref&gt;NewConnection&lt;/tp:member-ref&gt; signal for the same newly         created connection. The         requester can use the returned object path and service name         independently of the emission of that signal. In that case this signal         emission is most useful for, e.g. other processes that are monitoring         the creation of new connections.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_connection_manager_call_request_connection (TpConnectionManager *proxy,
    gint timeout_ms,
    const gchar *in_Protocol,
    GHashTable *in_Parameters,
    tp_cli_connection_manager_callback_for_request_connection callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_MANAGER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_CONNECTION_MANAGER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "RequestConnection",
          G_TYPE_STRING, in_Protocol,
          (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Parameters,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "RequestConnection", iface,
          _tp_cli_connection_manager_invoke_callback_request_connection,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "RequestConnection",
              _tp_cli_connection_manager_collect_callback_request_connection,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Protocol,
              (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), in_Parameters,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    gchar **out_Bus_Name;
    gchar **out_Object_Path;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_connection_manager_run_state_request_connection;
static void
_tp_cli_connection_manager_finish_running_request_connection (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_connection_manager_run_state_request_connection *state = user_data;

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

  if (state->out_Bus_Name != NULL)
    *state->out_Bus_Name = g_value_dup_string (args->values + 0);

  if (state->out_Object_Path != NULL)
    *state->out_Object_Path = g_value_dup_boxed (args->values + 1);

  g_value_array_free (args);
}

/**
 * tp_cli_connection_manager_run_request_connection:
 * @proxy: A #TpConnectionManager or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Protocol: Used to pass an 'in' argument: The protocol identifier
 * @in_Parameters: Used to pass an 'in' argument: A dictionary mapping parameter names to values of the appropriate           type, as indicated by &lt;tp:member-ref&gt;GetParameters&lt;/tp:member-ref&gt;           and the above well-known list.
 * @out_Bus_Name: Used to return an 'out' argument if %TRUE is returned: A D-Bus service name where the new Connection object can be found
 * @out_Object_Path: Used to return an 'out' argument if %TRUE is returned: The D-Bus object path to the Connection on this service
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method RequestConnection and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Request a           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Connection&lt;/tp:dbus-ref&gt;           object representing a given account on a given           protocol with the given parameters. The method returns the bus name           and the object path where the new Connection object can be found,           which should have the status of Connection_Status_Disconnected, to           allow signal handlers to be attached before connecting is started           with the           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection&quot;&gt;Connect&lt;/tp:dbus-ref&gt;           method.&lt;/p&gt;          &lt;p&gt;The parameters which must and may be provided in the parameters         dictionary can be discovered with the         &lt;tp:member-ref&gt;GetParameters&lt;/tp:member-ref&gt; method. These         parameters, their types, and their default values may be cached         in files so that all available connection managers do not need to be         started to discover which protocols are available.&lt;/p&gt;          &lt;p&gt;To request values for these parameters from the user, a client must         have prior knowledge of the meaning of the parameter names, so the         following well-known names and types should be used where appropriate:&lt;/p&gt;          &lt;dl&gt;           &lt;dt&gt;account (s)&lt;/dt&gt;           &lt;dd&gt;The identifier for the user&apos;s account on the server&lt;/dd&gt;            &lt;dt&gt;server (s)&lt;/dt&gt;           &lt;dd&gt;A fully qualified domain name or numeric IPv4 or IPv6 address.             Using the fully-qualified domain name form is recommended whenever             possible. If this parameter is specified and the account for that             protocol also specifies a server, this parameter should override             that in the user id.&lt;/dd&gt;            &lt;dt&gt;port (q)&lt;/dt&gt;           &lt;dd&gt;A TCP or UDP port number. If this parameter is specified and the             account for that protocol also specifies a port, this parameter             should override that in the account.&lt;/dd&gt;            &lt;dt&gt;password (s)&lt;/dt&gt;           &lt;dd&gt;A password associated with the account.&lt;/dd&gt;            &lt;dt&gt;require-encryption (b)&lt;/dt&gt;           &lt;dd&gt;Require encryption for this connection. A connection should fail             to connect if require-encryption is set and an encrypted connection             is not possible.&lt;/dd&gt;            &lt;dt&gt;register (b)&lt;/dt&gt;           &lt;dd&gt;This account should be created on the server if it does not             already exist.&lt;/dd&gt;            &lt;dt&gt;ident (s)&lt;/dt&gt;           &lt;dd&gt;The local username to report to the server if necessary, such as             in IRC.&lt;/dd&gt;            &lt;dt&gt;fullname (s)&lt;/dt&gt;           &lt;dd&gt;The user&apos;s full name if the service requires this when             authenticating or registering.&lt;/dd&gt;            &lt;dt&gt;stun-server (s)&lt;/dt&gt;           &lt;dd&gt;The IP address or FQDN of a STUN server to use for NAT traversal,             without any &amp;quot;:port&amp;quot; suffix.&lt;/dd&gt;            &lt;dt&gt;stun-port (q)&lt;/dt&gt;           &lt;dd&gt;The UDP port number on the stun-server to use for STUN. Only             significant if the stun-server is also supplied.&lt;/dd&gt;            &lt;dt&gt;keepalive-interval (u)&lt;/dt&gt;           &lt;dd&gt;The time in seconds between pings sent to the server to ensure             that the connection is still alive, or &lt;tt&gt;0&lt;/tt&gt; to disable such             pings.&lt;/dd&gt;         &lt;/dl&gt;          &lt;p&gt;Every successful RequestConnection call will cause the emission of a         &lt;tp:member-ref&gt;NewConnection&lt;/tp:member-ref&gt; signal for the same newly         created connection. The         requester can use the returned object path and service name         independently of the emission of that signal. In that case this signal         emission is most useful for, e.g. other processes that are monitoring         the creation of new connections.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_connection_manager_run_request_connection (TpConnectionManager *proxy,
    gint timeout_ms,
    const gchar *in_Protocol,
    GHashTable *in_Parameters,
    gchar **out_Bus_Name,
    gchar **out_Object_Path,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_CONNECTION_MANAGER;
  TpProxyPendingCall *pc;
  _tp_cli_connection_manager_run_state_request_connection state = {
      NULL /* loop */, error,
    out_Bus_Name,
    out_Object_Path,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_CONNECTION_MANAGER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "RequestConnection", iface,
      _tp_cli_connection_manager_finish_running_request_connection,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "RequestConnection",
          _tp_cli_connection_manager_collect_callback_request_connection,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_STRING, in_Protocol,
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


/*
 * tp_cli_connection_manager_add_signals:
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
tp_cli_connection_manager_add_signals (TpProxy *self G_GNUC_UNUSED,
    guint quark,
    DBusGProxy *proxy,
    gpointer unused G_GNUC_UNUSED)
{
  if (quark == TP_IFACE_QUARK_CONNECTION_MANAGER)
    tp_cli_add_signals_for_connection_manager (proxy);
}
