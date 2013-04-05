/* We don't want gtkdoc scanning this file, it'll get
 * confused by seeing function definitions, so mark it as: */
/*<private_header>*/

/**
 * tp_cli_dbus_introspectable_callback_for_introspect:
 * @proxy: the proxy on which the call was made
 * @out_XML_Data: Used to return an 'out' argument if @error is %NULL: (Undocumented)
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Introspect method call
 * succeeds or fails.
 */
static void
_tp_cli_dbus_introspectable_collect_callback_introspect (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_XML_Data;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRING, &out_XML_Data,
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
  g_value_take_string (args->values + 0, out_XML_Data);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_dbus_introspectable_invoke_callback_introspect (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_dbus_introspectable_callback_for_introspect callback = (tp_cli_dbus_introspectable_callback_for_introspect) generic_callback;

  if (error != NULL)
    {
      callback ((TpProxy *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpProxy *) self,
      g_value_get_string (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_dbus_introspectable_call_introspect:
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
 * Start a Introspect method call.
 *
 * (Undocumented)
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_dbus_introspectable_call_introspect (gpointer proxy,
    gint timeout_ms,
    tp_cli_dbus_introspectable_callback_for_introspect callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_DBUS_INTROSPECTABLE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_PROXY (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Introspect",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Introspect", iface,
          _tp_cli_dbus_introspectable_invoke_callback_introspect,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Introspect",
              _tp_cli_dbus_introspectable_collect_callback_introspect,
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
    gchar **out_XML_Data;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_dbus_introspectable_run_state_introspect;
static void
_tp_cli_dbus_introspectable_finish_running_introspect (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_dbus_introspectable_run_state_introspect *state = user_data;

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

  if (state->out_XML_Data != NULL)
    *state->out_XML_Data = g_value_dup_string (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_dbus_introspectable_run_introspect:
 * @proxy: A #TpProxy or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_XML_Data: Used to return an 'out' argument if %TRUE is returned: (Undocumented)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Introspect and run the main loop
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
tp_cli_dbus_introspectable_run_introspect (gpointer proxy,
    gint timeout_ms,
    gchar **out_XML_Data,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_DBUS_INTROSPECTABLE;
  TpProxyPendingCall *pc;
  _tp_cli_dbus_introspectable_run_state_introspect state = {
      NULL /* loop */, error,
    out_XML_Data,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_PROXY (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Introspect", iface,
      _tp_cli_dbus_introspectable_finish_running_introspect,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Introspect",
          _tp_cli_dbus_introspectable_collect_callback_introspect,
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
 * tp_cli_dbus_peer_callback_for_ping:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Ping method call
 * succeeds or fails.
 */
static void
_tp_cli_dbus_peer_collect_callback_ping (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_dbus_peer_invoke_callback_ping (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_dbus_peer_callback_for_ping callback = (tp_cli_dbus_peer_callback_for_ping) generic_callback;

  if (error != NULL)
    {
      callback ((TpProxy *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpProxy *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_dbus_peer_call_ping:
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
 * Start a Ping method call.
 *
 * (Undocumented)
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_dbus_peer_call_ping (gpointer proxy,
    gint timeout_ms,
    tp_cli_dbus_peer_callback_for_ping callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_DBUS_PEER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_PROXY (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Ping",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Ping", iface,
          _tp_cli_dbus_peer_invoke_callback_ping,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Ping",
              _tp_cli_dbus_peer_collect_callback_ping,
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
} _tp_cli_dbus_peer_run_state_ping;
static void
_tp_cli_dbus_peer_finish_running_ping (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_dbus_peer_run_state_ping *state = user_data;

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
 * tp_cli_dbus_peer_run_ping:
 * @proxy: A #TpProxy or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Ping and run the main loop
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
tp_cli_dbus_peer_run_ping (gpointer proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_DBUS_PEER;
  TpProxyPendingCall *pc;
  _tp_cli_dbus_peer_run_state_ping state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_PROXY (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Ping", iface,
      _tp_cli_dbus_peer_finish_running_ping,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Ping",
          _tp_cli_dbus_peer_collect_callback_ping,
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
 * tp_cli_dbus_peer_callback_for_get_machine_id:
 * @proxy: the proxy on which the call was made
 * @out_Machine_UUID: Used to return an 'out' argument if @error is %NULL: (Undocumented)
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetMachineId method call
 * succeeds or fails.
 */
static void
_tp_cli_dbus_peer_collect_callback_get_machine_id (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  gchar *out_Machine_UUID;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_STRING, &out_Machine_UUID,
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
  g_value_take_string (args->values + 0, out_Machine_UUID);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_dbus_peer_invoke_callback_get_machine_id (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_dbus_peer_callback_for_get_machine_id callback = (tp_cli_dbus_peer_callback_for_get_machine_id) generic_callback;

  if (error != NULL)
    {
      callback ((TpProxy *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpProxy *) self,
      g_value_get_string (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_dbus_peer_call_get_machine_id:
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
 * Start a GetMachineId method call.
 *
 * (Undocumented)
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_dbus_peer_call_get_machine_id (gpointer proxy,
    gint timeout_ms,
    tp_cli_dbus_peer_callback_for_get_machine_id callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_DBUS_PEER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_PROXY (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetMachineId",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetMachineId", iface,
          _tp_cli_dbus_peer_invoke_callback_get_machine_id,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetMachineId",
              _tp_cli_dbus_peer_collect_callback_get_machine_id,
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
    gchar **out_Machine_UUID;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_dbus_peer_run_state_get_machine_id;
static void
_tp_cli_dbus_peer_finish_running_get_machine_id (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_dbus_peer_run_state_get_machine_id *state = user_data;

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

  if (state->out_Machine_UUID != NULL)
    *state->out_Machine_UUID = g_value_dup_string (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_dbus_peer_run_get_machine_id:
 * @proxy: A #TpProxy or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Machine_UUID: Used to return an 'out' argument if %TRUE is returned: (Undocumented)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetMachineId and run the main loop
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
tp_cli_dbus_peer_run_get_machine_id (gpointer proxy,
    gint timeout_ms,
    gchar **out_Machine_UUID,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_DBUS_PEER;
  TpProxyPendingCall *pc;
  _tp_cli_dbus_peer_run_state_get_machine_id state = {
      NULL /* loop */, error,
    out_Machine_UUID,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_PROXY (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetMachineId", iface,
      _tp_cli_dbus_peer_finish_running_get_machine_id,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetMachineId",
          _tp_cli_dbus_peer_collect_callback_get_machine_id,
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
 * tp_cli_dbus_properties_callback_for_get:
 * @proxy: the proxy on which the call was made
 * @out_Value: Used to return an 'out' argument if @error is %NULL: (Undocumented)
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Get method call
 * succeeds or fails.
 */
static void
_tp_cli_dbus_properties_collect_callback_get (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GValue *out_Value = g_new0 (GValue, 1);

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_VALUE, out_Value,
      G_TYPE_INVALID);

  if (error != NULL)
    {
      tp_proxy_pending_call_v0_take_results (user_data, error,
          NULL);
      g_free (out_Value);
      return;
    }

  args = g_value_array_new (1);
  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_VALUE);
  g_value_take_boxed (args->values + 0, out_Value);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_dbus_properties_invoke_callback_get (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_dbus_properties_callback_for_get callback = (tp_cli_dbus_properties_callback_for_get) generic_callback;

  if (error != NULL)
    {
      callback ((TpProxy *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpProxy *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_dbus_properties_call_get:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Interface_Name: Used to pass an 'in' argument: (Undocumented)
 * @in_Property_Name: Used to pass an 'in' argument: (Undocumented)
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
 * Start a Get method call.
 *
 * (Undocumented)
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_dbus_properties_call_get (gpointer proxy,
    gint timeout_ms,
    const gchar *in_Interface_Name,
    const gchar *in_Property_Name,
    tp_cli_dbus_properties_callback_for_get callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_DBUS_PROPERTIES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_PROXY (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Get",
          G_TYPE_STRING, in_Interface_Name,
          G_TYPE_STRING, in_Property_Name,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Get", iface,
          _tp_cli_dbus_properties_invoke_callback_get,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Get",
              _tp_cli_dbus_properties_collect_callback_get,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Interface_Name,
              G_TYPE_STRING, in_Property_Name,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GValue **out_Value;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_dbus_properties_run_state_get;
static void
_tp_cli_dbus_properties_finish_running_get (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_dbus_properties_run_state_get *state = user_data;

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

  if (state->out_Value != NULL)
    *state->out_Value = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_dbus_properties_run_get:
 * @proxy: A #TpProxy or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Interface_Name: Used to pass an 'in' argument: (Undocumented)
 * @in_Property_Name: Used to pass an 'in' argument: (Undocumented)
 * @out_Value: Used to return an 'out' argument if %TRUE is returned: (Undocumented)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Get and run the main loop
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
tp_cli_dbus_properties_run_get (gpointer proxy,
    gint timeout_ms,
    const gchar *in_Interface_Name,
    const gchar *in_Property_Name,
    GValue **out_Value,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_DBUS_PROPERTIES;
  TpProxyPendingCall *pc;
  _tp_cli_dbus_properties_run_state_get state = {
      NULL /* loop */, error,
    out_Value,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_PROXY (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Get", iface,
      _tp_cli_dbus_properties_finish_running_get,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Get",
          _tp_cli_dbus_properties_collect_callback_get,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_STRING, in_Interface_Name,
              G_TYPE_STRING, in_Property_Name,
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
 * tp_cli_dbus_properties_callback_for_set:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Set method call
 * succeeds or fails.
 */
static void
_tp_cli_dbus_properties_collect_callback_set (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_dbus_properties_invoke_callback_set (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_dbus_properties_callback_for_set callback = (tp_cli_dbus_properties_callback_for_set) generic_callback;

  if (error != NULL)
    {
      callback ((TpProxy *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpProxy *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_dbus_properties_call_set:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Interface_Name: Used to pass an 'in' argument: (Undocumented)
 * @in_Property_Name: Used to pass an 'in' argument: (Undocumented)
 * @in_Value: Used to pass an 'in' argument: (Undocumented)
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
 * Start a Set method call.
 *
 * (Undocumented)
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_dbus_properties_call_set (gpointer proxy,
    gint timeout_ms,
    const gchar *in_Interface_Name,
    const gchar *in_Property_Name,
    const GValue *in_Value,
    tp_cli_dbus_properties_callback_for_set callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_DBUS_PROPERTIES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_PROXY (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Set",
          G_TYPE_STRING, in_Interface_Name,
          G_TYPE_STRING, in_Property_Name,
          G_TYPE_VALUE, in_Value,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Set", iface,
          _tp_cli_dbus_properties_invoke_callback_set,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Set",
              _tp_cli_dbus_properties_collect_callback_set,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Interface_Name,
              G_TYPE_STRING, in_Property_Name,
              G_TYPE_VALUE, in_Value,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_dbus_properties_run_state_set;
static void
_tp_cli_dbus_properties_finish_running_set (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_dbus_properties_run_state_set *state = user_data;

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
 * tp_cli_dbus_properties_run_set:
 * @proxy: A #TpProxy or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Interface_Name: Used to pass an 'in' argument: (Undocumented)
 * @in_Property_Name: Used to pass an 'in' argument: (Undocumented)
 * @in_Value: Used to pass an 'in' argument: (Undocumented)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Set and run the main loop
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
tp_cli_dbus_properties_run_set (gpointer proxy,
    gint timeout_ms,
    const gchar *in_Interface_Name,
    const gchar *in_Property_Name,
    const GValue *in_Value,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_DBUS_PROPERTIES;
  TpProxyPendingCall *pc;
  _tp_cli_dbus_properties_run_state_set state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_PROXY (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Set", iface,
      _tp_cli_dbus_properties_finish_running_set,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Set",
          _tp_cli_dbus_properties_collect_callback_set,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_STRING, in_Interface_Name,
              G_TYPE_STRING, in_Property_Name,
              G_TYPE_VALUE, in_Value,
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
 * tp_cli_dbus_properties_callback_for_get_all:
 * @proxy: the proxy on which the call was made
 * @out_Properties: Used to return an 'out' argument if @error is %NULL: (Undocumented)
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetAll method call
 * succeeds or fails.
 */
static void
_tp_cli_dbus_properties_collect_callback_get_all (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GHashTable *out_Properties;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_VALUE)), &out_Properties,
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
  g_value_take_boxed (args->values + 0, out_Properties);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_dbus_properties_invoke_callback_get_all (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_dbus_properties_callback_for_get_all callback = (tp_cli_dbus_properties_callback_for_get_all) generic_callback;

  if (error != NULL)
    {
      callback ((TpProxy *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpProxy *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_dbus_properties_call_get_all:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Interface_Name: Used to pass an 'in' argument: (Undocumented)
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
 * Start a GetAll method call.
 *
 * (Undocumented)
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_dbus_properties_call_get_all (gpointer proxy,
    gint timeout_ms,
    const gchar *in_Interface_Name,
    tp_cli_dbus_properties_callback_for_get_all callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_DBUS_PROPERTIES;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_PROXY (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetAll",
          G_TYPE_STRING, in_Interface_Name,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetAll", iface,
          _tp_cli_dbus_properties_invoke_callback_get_all,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetAll",
              _tp_cli_dbus_properties_collect_callback_get_all,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Interface_Name,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GHashTable **out_Properties;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_dbus_properties_run_state_get_all;
static void
_tp_cli_dbus_properties_finish_running_get_all (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_dbus_properties_run_state_get_all *state = user_data;

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

  if (state->out_Properties != NULL)
    *state->out_Properties = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_dbus_properties_run_get_all:
 * @proxy: A #TpProxy or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Interface_Name: Used to pass an 'in' argument: (Undocumented)
 * @out_Properties: Used to return an 'out' argument if %TRUE is returned: (Undocumented)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetAll and run the main loop
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
tp_cli_dbus_properties_run_get_all (gpointer proxy,
    gint timeout_ms,
    const gchar *in_Interface_Name,
    GHashTable **out_Properties,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_DBUS_PROPERTIES;
  TpProxyPendingCall *pc;
  _tp_cli_dbus_properties_run_state_get_all state = {
      NULL /* loop */, error,
    out_Properties,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_PROXY (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetAll", iface,
      _tp_cli_dbus_properties_finish_running_get_all,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetAll",
          _tp_cli_dbus_properties_collect_callback_get_all,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_STRING, in_Interface_Name,
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
tp_cli_add_signals_for_properties_interface (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "PropertiesChanged",
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_VALUE, G_TYPE_INVALID)))),
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "PropertyFlagsChanged",
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))),
      G_TYPE_INVALID);
}


/**
 * tp_cli_properties_interface_signal_callback_properties_changed:
 * @proxy: The proxy on which tp_cli_properties_interface_connect_to_properties_changed ()
 *  was called
 * @arg_Properties: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;An array of structs containing:&lt;/p&gt;           &lt;ul&gt;             &lt;li&gt;integer identifiers&lt;/li&gt;             &lt;li&gt;variant boxed values&lt;/li&gt;           &lt;/ul&gt;           &lt;p&gt;The array should contain only properties whose values have             actually changed.&lt;/p&gt;
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal PropertiesChanged.
 */
static void
_tp_cli_properties_interface_collect_args_of_properties_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    const GPtrArray *arg_Properties,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_VALUE, G_TYPE_INVALID)))));
  g_value_set_boxed (args->values + 0, arg_Properties);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_properties_interface_invoke_callback_for_properties_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_properties_interface_signal_callback_properties_changed callback =
      (tp_cli_properties_interface_signal_callback_properties_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_properties_interface_connect_to_properties_changed:
 * @proxy: A #TpProxy or subclass
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
 * Connect a handler to the signal PropertiesChanged.
 *
 * Emitted when the value of readable properties has changed.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_properties_interface_connect_to_properties_changed (gpointer proxy,
    tp_cli_properties_interface_signal_callback_properties_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_VALUE, G_TYPE_INVALID)))),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_PROXY (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_PROPERTIES_INTERFACE, "PropertiesChanged",
      expected_types,
      G_CALLBACK (_tp_cli_properties_interface_collect_args_of_properties_changed),
      _tp_cli_properties_interface_invoke_callback_for_properties_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_properties_interface_signal_callback_property_flags_changed:
 * @proxy: The proxy on which tp_cli_properties_interface_connect_to_property_flags_changed ()
 *  was called
 * @arg_Properties: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;An array of structs containing:&lt;/p&gt;           &lt;ul&gt;             &lt;li&gt;integer identifiers&lt;/li&gt;             &lt;li&gt;a bitwise OR of the current flags&lt;/li&gt;           &lt;/ul&gt;           &lt;p&gt;The array should contain only properties whose flags have actually             changed.&lt;/p&gt;
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal PropertyFlagsChanged.
 */
static void
_tp_cli_properties_interface_collect_args_of_property_flags_changed (DBusGProxy *proxy G_GNUC_UNUSED,
    const GPtrArray *arg_Properties,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))));
  g_value_set_boxed (args->values + 0, arg_Properties);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_properties_interface_invoke_callback_for_property_flags_changed (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_properties_interface_signal_callback_property_flags_changed callback =
      (tp_cli_properties_interface_signal_callback_property_flags_changed) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_properties_interface_connect_to_property_flags_changed:
 * @proxy: A #TpProxy or subclass
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
 * Connect a handler to the signal PropertyFlagsChanged.
 *
 * Emitted when the flags of some room properties have changed.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_properties_interface_connect_to_property_flags_changed (gpointer proxy,
    tp_cli_properties_interface_signal_callback_property_flags_changed callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_UINT, G_TYPE_INVALID)))),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_PROXY (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_PROPERTIES_INTERFACE, "PropertyFlagsChanged",
      expected_types,
      G_CALLBACK (_tp_cli_properties_interface_collect_args_of_property_flags_changed),
      _tp_cli_properties_interface_invoke_callback_for_property_flags_changed,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_properties_interface_callback_for_get_properties:
 * @proxy: the proxy on which the call was made
 * @out_Values: Used to return an 'out' argument if @error is %NULL: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;An array of structs containing:&lt;/p&gt;           &lt;ul&gt;             &lt;li&gt;integer identifiers&lt;/li&gt;             &lt;li&gt;variant boxed values&lt;/li&gt;           &lt;/ul&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a GetProperties method call
 * succeeds or fails.
 */
static void
_tp_cli_properties_interface_collect_callback_get_properties (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GPtrArray *out_Values;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_VALUE, G_TYPE_INVALID)))), &out_Values,
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
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_VALUE, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Values);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_properties_interface_invoke_callback_get_properties (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_properties_interface_callback_for_get_properties callback = (tp_cli_properties_interface_callback_for_get_properties) generic_callback;

  if (error != NULL)
    {
      callback ((TpProxy *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpProxy *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_properties_interface_call_get_properties:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Properties: Used to pass an 'in' argument: An array of property identifiers
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
 * Start a GetProperties method call.
 *
 * Returns an array of (identifier, value) pairs containing the current         values of the given properties.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_properties_interface_call_get_properties (gpointer proxy,
    gint timeout_ms,
    const GArray *in_Properties,
    tp_cli_properties_interface_callback_for_get_properties callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_PROPERTIES_INTERFACE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_PROXY (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "GetProperties",
          DBUS_TYPE_G_UINT_ARRAY, in_Properties,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "GetProperties", iface,
          _tp_cli_properties_interface_invoke_callback_get_properties,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "GetProperties",
              _tp_cli_properties_interface_collect_callback_get_properties,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Properties,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    GPtrArray **out_Values;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_properties_interface_run_state_get_properties;
static void
_tp_cli_properties_interface_finish_running_get_properties (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_properties_interface_run_state_get_properties *state = user_data;

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

  if (state->out_Values != NULL)
    *state->out_Values = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_properties_interface_run_get_properties:
 * @proxy: A #TpProxy or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Properties: Used to pass an 'in' argument: An array of property identifiers
 * @out_Values: Used to return an 'out' argument if %TRUE is returned: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;An array of structs containing:&lt;/p&gt;           &lt;ul&gt;             &lt;li&gt;integer identifiers&lt;/li&gt;             &lt;li&gt;variant boxed values&lt;/li&gt;           &lt;/ul&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method GetProperties and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns an array of (identifier, value) pairs containing the current         values of the given properties.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_properties_interface_run_get_properties (gpointer proxy,
    gint timeout_ms,
    const GArray *in_Properties,
    GPtrArray **out_Values,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_PROPERTIES_INTERFACE;
  TpProxyPendingCall *pc;
  _tp_cli_properties_interface_run_state_get_properties state = {
      NULL /* loop */, error,
    out_Values,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_PROXY (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "GetProperties", iface,
      _tp_cli_properties_interface_finish_running_get_properties,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "GetProperties",
          _tp_cli_properties_interface_collect_callback_get_properties,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              DBUS_TYPE_G_UINT_ARRAY, in_Properties,
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
 * tp_cli_properties_interface_callback_for_list_properties:
 * @proxy: the proxy on which the call was made
 * @out_Available_Properties: Used to return an 'out' argument if @error is %NULL: An array of structs containing:           &lt;ul&gt;             &lt;li&gt;an integer identifier&lt;/li&gt;             &lt;li&gt;a string property name&lt;/li&gt;             &lt;li&gt;a string representing the D-Bus signature of this property&lt;/li&gt;             &lt;li&gt;a bitwise OR of the flags applicable to this property&lt;/li&gt;           &lt;/ul&gt;
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a ListProperties method call
 * succeeds or fails.
 */
static void
_tp_cli_properties_interface_collect_callback_list_properties (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;
  GValueArray *args;
  GValue blank = { 0 };
  guint i;
  GPtrArray *out_Available_Properties;

  dbus_g_proxy_end_call (proxy, call, &error,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_INVALID)))), &out_Available_Properties,
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
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_INVALID)))));
  g_value_take_boxed (args->values + 0, out_Available_Properties);
  tp_proxy_pending_call_v0_take_results (user_data, NULL, args);
}
static void
_tp_cli_properties_interface_invoke_callback_list_properties (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_properties_interface_callback_for_list_properties callback = (tp_cli_properties_interface_callback_for_list_properties) generic_callback;

  if (error != NULL)
    {
      callback ((TpProxy *) self,
          NULL,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpProxy *) self,
      g_value_get_boxed (args->values + 0),
      error, user_data, weak_object);

  g_value_array_free (args);
}

/**
 * tp_cli_properties_interface_call_list_properties:
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
 * Start a ListProperties method call.
 *
 * Returns a dictionary of the properties available on this channel.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_properties_interface_call_list_properties (gpointer proxy,
    gint timeout_ms,
    tp_cli_properties_interface_callback_for_list_properties callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_PROPERTIES_INTERFACE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_PROXY (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "ListProperties",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "ListProperties", iface,
          _tp_cli_properties_interface_invoke_callback_list_properties,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "ListProperties",
              _tp_cli_properties_interface_collect_callback_list_properties,
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
    GPtrArray **out_Available_Properties;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_properties_interface_run_state_list_properties;
static void
_tp_cli_properties_interface_finish_running_list_properties (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_properties_interface_run_state_list_properties *state = user_data;

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

  if (state->out_Available_Properties != NULL)
    *state->out_Available_Properties = g_value_dup_boxed (args->values + 0);

  g_value_array_free (args);
}

/**
 * tp_cli_properties_interface_run_list_properties:
 * @proxy: A #TpProxy or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @out_Available_Properties: Used to return an 'out' argument if %TRUE is returned: An array of structs containing:           &lt;ul&gt;             &lt;li&gt;an integer identifier&lt;/li&gt;             &lt;li&gt;a string property name&lt;/li&gt;             &lt;li&gt;a string representing the D-Bus signature of this property&lt;/li&gt;             &lt;li&gt;a bitwise OR of the flags applicable to this property&lt;/li&gt;           &lt;/ul&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method ListProperties and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Returns a dictionary of the properties available on this channel.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_properties_interface_run_list_properties (gpointer proxy,
    gint timeout_ms,
    GPtrArray **out_Available_Properties,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_PROPERTIES_INTERFACE;
  TpProxyPendingCall *pc;
  _tp_cli_properties_interface_run_state_list_properties state = {
      NULL /* loop */, error,
    out_Available_Properties,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_PROXY (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "ListProperties", iface,
      _tp_cli_properties_interface_finish_running_list_properties,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "ListProperties",
          _tp_cli_properties_interface_collect_callback_list_properties,
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
 * tp_cli_properties_interface_callback_for_set_properties:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a SetProperties method call
 * succeeds or fails.
 */
static void
_tp_cli_properties_interface_collect_callback_set_properties (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_properties_interface_invoke_callback_set_properties (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_properties_interface_callback_for_set_properties callback = (tp_cli_properties_interface_callback_for_set_properties) generic_callback;

  if (error != NULL)
    {
      callback ((TpProxy *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpProxy *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_properties_interface_call_set_properties:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Properties: Used to pass an 'in' argument: An array mapping integer property identifiers to boxed values
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
 * Start a SetProperties method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Takes an array of (identifier, value) pairs containing desired           values to set the given properties. In the case of any errors, no           properties will be changed. When the changes have been acknowledged           by the server, the PropertiesChanged signal will be emitted.&lt;/p&gt;          &lt;p&gt;All properties given must have the PROPERTY_FLAG_WRITE flag, or         PermissionDenied will be returned. If any variants are of the wrong         type, NotAvailable will be returned.  If any given property identifiers         are invalid, InvalidArgument will be returned.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_properties_interface_call_set_properties (gpointer proxy,
    gint timeout_ms,
    const GPtrArray *in_Properties,
    tp_cli_properties_interface_callback_for_set_properties callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_PROPERTIES_INTERFACE;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_PROXY (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "SetProperties",
          (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_VALUE, G_TYPE_INVALID)))), in_Properties,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "SetProperties", iface,
          _tp_cli_properties_interface_invoke_callback_set_properties,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "SetProperties",
              _tp_cli_properties_interface_collect_callback_set_properties,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_VALUE, G_TYPE_INVALID)))), in_Properties,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_properties_interface_run_state_set_properties;
static void
_tp_cli_properties_interface_finish_running_set_properties (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_properties_interface_run_state_set_properties *state = user_data;

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
 * tp_cli_properties_interface_run_set_properties:
 * @proxy: A #TpProxy or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Properties: Used to pass an 'in' argument: An array mapping integer property identifiers to boxed values
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method SetProperties and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Takes an array of (identifier, value) pairs containing desired           values to set the given properties. In the case of any errors, no           properties will be changed. When the changes have been acknowledged           by the server, the PropertiesChanged signal will be emitted.&lt;/p&gt;          &lt;p&gt;All properties given must have the PROPERTY_FLAG_WRITE flag, or         PermissionDenied will be returned. If any variants are of the wrong         type, NotAvailable will be returned.  If any given property identifiers         are invalid, InvalidArgument will be returned.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_properties_interface_run_set_properties (gpointer proxy,
    gint timeout_ms,
    const GPtrArray *in_Properties,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_PROPERTIES_INTERFACE;
  TpProxyPendingCall *pc;
  _tp_cli_properties_interface_run_state_set_properties state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_PROXY (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "SetProperties", iface,
      _tp_cli_properties_interface_finish_running_set_properties,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "SetProperties",
          _tp_cli_properties_interface_collect_callback_set_properties,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_VALUE, G_TYPE_INVALID)))), in_Properties,
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
 * tp_cli_generic_add_signals:
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
tp_cli_generic_add_signals (TpProxy *self G_GNUC_UNUSED,
    guint quark,
    DBusGProxy *proxy,
    gpointer unused G_GNUC_UNUSED)
{
  if (quark == TP_IFACE_QUARK_PROPERTIES_INTERFACE)
    tp_cli_add_signals_for_properties_interface (proxy);
}
