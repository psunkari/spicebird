/* We don't want gtkdoc scanning this file, it'll get
 * confused by seeing function definitions, so mark it as: */
/*<private_header>*/

static inline void
tp_cli_add_signals_for_media_stream_handler (DBusGProxy *proxy)
{
  if (!tp_proxy_dbus_g_proxy_claim_for_signal_adding (proxy))
    return;
  dbus_g_proxy_add_signal (proxy, "AddRemoteCandidate",
      G_TYPE_STRING,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_DOUBLE, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))),
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "Close",
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "RemoveRemoteCandidate",
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "SetActiveCandidatePair",
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "SetRemoteCandidateList",
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_DOUBLE, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))), G_TYPE_INVALID)))),
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "SetRemoteCodecs",
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))),
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "SetStreamPlaying",
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "SetStreamSending",
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "StartTelephonyEvent",
      G_TYPE_UCHAR,
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "StopTelephonyEvent",
      G_TYPE_INVALID);
  dbus_g_proxy_add_signal (proxy, "SetStreamHeld",
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID);
}


/**
 * tp_cli_media_stream_handler_signal_callback_add_remote_candidate:
 * @proxy: The proxy on which tp_cli_media_stream_handler_connect_to_add_remote_candidate ()
 *  was called
 * @arg_Candidate_ID: String identifier for this candidate
 * @arg_Transports: Array of transports for this candidate with fields,           as defined in NewNativeCandidate
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal AddRemoteCandidate.
 */
static void
_tp_cli_media_stream_handler_collect_args_of_add_remote_candidate (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Candidate_ID,
    const GPtrArray *arg_Transports,
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
  g_value_set_string (args->values + 0, arg_Candidate_ID);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_DOUBLE, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))));
  g_value_set_boxed (args->values + 1, arg_Transports);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_media_stream_handler_invoke_callback_for_add_remote_candidate (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_signal_callback_add_remote_candidate callback =
      (tp_cli_media_stream_handler_signal_callback_add_remote_candidate) generic_callback;

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
 * tp_cli_media_stream_handler_connect_to_add_remote_candidate:
 * @proxy: A #TpMediaStreamHandler or subclass
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
 * Connect a handler to the signal AddRemoteCandidate.
 *
 * Signal emitted when the connection manager wishes to inform the         client of a new remote candidate.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_media_stream_handler_connect_to_add_remote_candidate (TpMediaStreamHandler *proxy,
    tp_cli_media_stream_handler_signal_callback_add_remote_candidate callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_STRING,
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_DOUBLE, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_MEDIA_STREAM_HANDLER, "AddRemoteCandidate",
      expected_types,
      G_CALLBACK (_tp_cli_media_stream_handler_collect_args_of_add_remote_candidate),
      _tp_cli_media_stream_handler_invoke_callback_for_add_remote_candidate,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_media_stream_handler_signal_callback_close:
 * @proxy: The proxy on which tp_cli_media_stream_handler_connect_to_close ()
 *  was called
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal Close.
 */
static void
_tp_cli_media_stream_handler_invoke_callback_for_close (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_signal_callback_close callback =
      (tp_cli_media_stream_handler_signal_callback_close) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      user_data,
      weak_object);

  if (args != NULL)
    g_value_array_free (args);

  g_object_unref (tpproxy);
}
/**
 * tp_cli_media_stream_handler_connect_to_close:
 * @proxy: A #TpMediaStreamHandler or subclass
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
 * Connect a handler to the signal Close.
 *
 * Signal emitted when the connection manager wishes the stream to be         closed.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_media_stream_handler_connect_to_close (TpMediaStreamHandler *proxy,
    tp_cli_media_stream_handler_signal_callback_close callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[1] = {
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_MEDIA_STREAM_HANDLER, "Close",
      expected_types,
      NULL, /* no args => no collector function */
      _tp_cli_media_stream_handler_invoke_callback_for_close,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_media_stream_handler_signal_callback_remove_remote_candidate:
 * @proxy: The proxy on which tp_cli_media_stream_handler_connect_to_remove_remote_candidate ()
 *  was called
 * @arg_Candidate_ID: String identifier for remote candidate to drop
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal RemoveRemoteCandidate.
 */
static void
_tp_cli_media_stream_handler_collect_args_of_remove_remote_candidate (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Candidate_ID,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_STRING);
  g_value_set_string (args->values + 0, arg_Candidate_ID);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_media_stream_handler_invoke_callback_for_remove_remote_candidate (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_signal_callback_remove_remote_candidate callback =
      (tp_cli_media_stream_handler_signal_callback_remove_remote_candidate) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_string (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_media_stream_handler_connect_to_remove_remote_candidate:
 * @proxy: A #TpMediaStreamHandler or subclass
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
 * Connect a handler to the signal RemoveRemoteCandidate.
 *
 * Signal emitted when the connection manager wishes to inform the         client that the remote end has removed a previously usable         candidate.          &lt;tp:rationale&gt;           It seemed like a good idea at the time, but wasn&apos;t.         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_media_stream_handler_connect_to_remove_remote_candidate (TpMediaStreamHandler *proxy,
    tp_cli_media_stream_handler_signal_callback_remove_remote_candidate callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      G_TYPE_STRING,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_MEDIA_STREAM_HANDLER, "RemoveRemoteCandidate",
      expected_types,
      G_CALLBACK (_tp_cli_media_stream_handler_collect_args_of_remove_remote_candidate),
      _tp_cli_media_stream_handler_invoke_callback_for_remove_remote_candidate,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_media_stream_handler_signal_callback_set_active_candidate_pair:
 * @proxy: The proxy on which tp_cli_media_stream_handler_connect_to_set_active_candidate_pair ()
 *  was called
 * @arg_Native_Candidate_ID: (Undocumented)
 * @arg_Remote_Candidate_ID: (Undocumented)
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal SetActiveCandidatePair.
 */
static void
_tp_cli_media_stream_handler_collect_args_of_set_active_candidate_pair (DBusGProxy *proxy G_GNUC_UNUSED,
    const gchar *arg_Native_Candidate_ID,
    const gchar *arg_Remote_Candidate_ID,
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
  g_value_set_string (args->values + 0, arg_Native_Candidate_ID);

  g_value_unset (args->values + 1);
  g_value_init (args->values + 1, G_TYPE_STRING);
  g_value_set_string (args->values + 1, arg_Remote_Candidate_ID);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_media_stream_handler_invoke_callback_for_set_active_candidate_pair (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_signal_callback_set_active_candidate_pair callback =
      (tp_cli_media_stream_handler_signal_callback_set_active_candidate_pair) generic_callback;

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
 * tp_cli_media_stream_handler_connect_to_set_active_candidate_pair:
 * @proxy: A #TpMediaStreamHandler or subclass
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
 * Connect a handler to the signal SetActiveCandidatePair.
 *
 * Emitted by the connection manager to inform the client that a         valid candidate pair has been discovered by the remote end         and streaming is in progress.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_media_stream_handler_connect_to_set_active_candidate_pair (TpMediaStreamHandler *proxy,
    tp_cli_media_stream_handler_signal_callback_set_active_candidate_pair callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[3] = {
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_MEDIA_STREAM_HANDLER, "SetActiveCandidatePair",
      expected_types,
      G_CALLBACK (_tp_cli_media_stream_handler_collect_args_of_set_active_candidate_pair),
      _tp_cli_media_stream_handler_invoke_callback_for_set_active_candidate_pair,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_media_stream_handler_signal_callback_set_remote_candidate_list:
 * @proxy: The proxy on which tp_cli_media_stream_handler_connect_to_set_remote_candidate_list ()
 *  was called
 * @arg_Remote_Candidates: A list of candidate id and a list of transports         as defined in NewNativeCandidate
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal SetRemoteCandidateList.
 */
static void
_tp_cli_media_stream_handler_collect_args_of_set_remote_candidate_list (DBusGProxy *proxy G_GNUC_UNUSED,
    const GPtrArray *arg_Remote_Candidates,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_DOUBLE, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))), G_TYPE_INVALID)))));
  g_value_set_boxed (args->values + 0, arg_Remote_Candidates);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_media_stream_handler_invoke_callback_for_set_remote_candidate_list (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_signal_callback_set_remote_candidate_list callback =
      (tp_cli_media_stream_handler_signal_callback_set_remote_candidate_list) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_media_stream_handler_connect_to_set_remote_candidate_list:
 * @proxy: A #TpMediaStreamHandler or subclass
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
 * Connect a handler to the signal SetRemoteCandidateList.
 *
 * Signal emitted when the connection manager wishes to inform the         client of all the available remote candidates at once.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_media_stream_handler_connect_to_set_remote_candidate_list (TpMediaStreamHandler *proxy,
    tp_cli_media_stream_handler_signal_callback_set_remote_candidate_list callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_STRING, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_DOUBLE, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))), G_TYPE_INVALID)))),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_MEDIA_STREAM_HANDLER, "SetRemoteCandidateList",
      expected_types,
      G_CALLBACK (_tp_cli_media_stream_handler_collect_args_of_set_remote_candidate_list),
      _tp_cli_media_stream_handler_invoke_callback_for_set_remote_candidate_list,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_media_stream_handler_signal_callback_set_remote_codecs:
 * @proxy: The proxy on which tp_cli_media_stream_handler_connect_to_set_remote_codecs ()
 *  was called
 * @arg_Codecs: Codecs supported by the remote peer.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal SetRemoteCodecs.
 */
static void
_tp_cli_media_stream_handler_collect_args_of_set_remote_codecs (DBusGProxy *proxy G_GNUC_UNUSED,
    const GPtrArray *arg_Codecs,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))));
  g_value_set_boxed (args->values + 0, arg_Codecs);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_media_stream_handler_invoke_callback_for_set_remote_codecs (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_signal_callback_set_remote_codecs callback =
      (tp_cli_media_stream_handler_signal_callback_set_remote_codecs) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boxed (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_media_stream_handler_connect_to_set_remote_codecs:
 * @proxy: A #TpMediaStreamHandler or subclass
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
 * Connect a handler to the signal SetRemoteCodecs.
 *
 * Signal emitted when the connection manager wishes to inform the         client of the codecs supported by the remote end. 	If these codecs are compatible with the remote codecs, then the client         must call &lt;tp:member-ref&gt;SupportedCodecs&lt;/tp:member-ref&gt;,         otherwise call &lt;tp:member-ref&gt;Error&lt;/tp:member-ref&gt;.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_media_stream_handler_connect_to_set_remote_codecs (TpMediaStreamHandler *proxy,
    tp_cli_media_stream_handler_signal_callback_set_remote_codecs callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))),
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_MEDIA_STREAM_HANDLER, "SetRemoteCodecs",
      expected_types,
      G_CALLBACK (_tp_cli_media_stream_handler_collect_args_of_set_remote_codecs),
      _tp_cli_media_stream_handler_invoke_callback_for_set_remote_codecs,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_media_stream_handler_signal_callback_set_stream_playing:
 * @proxy: The proxy on which tp_cli_media_stream_handler_connect_to_set_stream_playing ()
 *  was called
 * @arg_Playing: (Undocumented)
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal SetStreamPlaying.
 */
static void
_tp_cli_media_stream_handler_collect_args_of_set_stream_playing (DBusGProxy *proxy G_GNUC_UNUSED,
    gboolean arg_Playing,
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
  g_value_set_boolean (args->values + 0, arg_Playing);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_media_stream_handler_invoke_callback_for_set_stream_playing (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_signal_callback_set_stream_playing callback =
      (tp_cli_media_stream_handler_signal_callback_set_stream_playing) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boolean (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_media_stream_handler_connect_to_set_stream_playing:
 * @proxy: A #TpMediaStreamHandler or subclass
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
 * Connect a handler to the signal SetStreamPlaying.
 *
 * If emitted with argument TRUE, this means that the connection manager         wishes to set the stream playing; this means that the streaming         implementation should expect to receive data. If emitted with argument         FALSE this signal is basically meaningless and should be ignored.          &lt;tp:rationale&gt;           We&apos;re very sorry.         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_media_stream_handler_connect_to_set_stream_playing (TpMediaStreamHandler *proxy,
    tp_cli_media_stream_handler_signal_callback_set_stream_playing callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_MEDIA_STREAM_HANDLER, "SetStreamPlaying",
      expected_types,
      G_CALLBACK (_tp_cli_media_stream_handler_collect_args_of_set_stream_playing),
      _tp_cli_media_stream_handler_invoke_callback_for_set_stream_playing,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_media_stream_handler_signal_callback_set_stream_sending:
 * @proxy: The proxy on which tp_cli_media_stream_handler_connect_to_set_stream_sending ()
 *  was called
 * @arg_Sending: (Undocumented)
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal SetStreamSending.
 */
static void
_tp_cli_media_stream_handler_collect_args_of_set_stream_sending (DBusGProxy *proxy G_GNUC_UNUSED,
    gboolean arg_Sending,
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
  g_value_set_boolean (args->values + 0, arg_Sending);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_media_stream_handler_invoke_callback_for_set_stream_sending (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_signal_callback_set_stream_sending callback =
      (tp_cli_media_stream_handler_signal_callback_set_stream_sending) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boolean (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_media_stream_handler_connect_to_set_stream_sending:
 * @proxy: A #TpMediaStreamHandler or subclass
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
 * Connect a handler to the signal SetStreamSending.
 *
 * Signal emitted when the connection manager wishes to set whether or not         the stream sends to the remote end.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_media_stream_handler_connect_to_set_stream_sending (TpMediaStreamHandler *proxy,
    tp_cli_media_stream_handler_signal_callback_set_stream_sending callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_MEDIA_STREAM_HANDLER, "SetStreamSending",
      expected_types,
      G_CALLBACK (_tp_cli_media_stream_handler_collect_args_of_set_stream_sending),
      _tp_cli_media_stream_handler_invoke_callback_for_set_stream_sending,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_media_stream_handler_signal_callback_start_telephony_event:
 * @proxy: The proxy on which tp_cli_media_stream_handler_connect_to_start_telephony_event ()
 *  was called
 * @arg_Event: A telephony event code as defined by RFC 4733.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal StartTelephonyEvent.
 */
static void
_tp_cli_media_stream_handler_collect_args_of_start_telephony_event (DBusGProxy *proxy G_GNUC_UNUSED,
    guchar arg_Event,
    TpProxySignalConnection *sc)
{
  GValueArray *args = g_value_array_new (1);
  GValue blank = { 0 };
  guint i;

  g_value_init (&blank, G_TYPE_INT);

  for (i = 0; i < 1; i++)
    g_value_array_append (args, &blank);

  g_value_unset (args->values + 0);
  g_value_init (args->values + 0, G_TYPE_UCHAR);
  g_value_set_uchar (args->values + 0, arg_Event);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_media_stream_handler_invoke_callback_for_start_telephony_event (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_signal_callback_start_telephony_event callback =
      (tp_cli_media_stream_handler_signal_callback_start_telephony_event) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_uchar (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_media_stream_handler_connect_to_start_telephony_event:
 * @proxy: A #TpMediaStreamHandler or subclass
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
 * Connect a handler to the signal StartTelephonyEvent.
 *
 * Request that a telephony event (as defined by RFC 4733) is transmitted         over this stream until StopTelephonyEvent is called.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_media_stream_handler_connect_to_start_telephony_event (TpMediaStreamHandler *proxy,
    tp_cli_media_stream_handler_signal_callback_start_telephony_event callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      G_TYPE_UCHAR,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_MEDIA_STREAM_HANDLER, "StartTelephonyEvent",
      expected_types,
      G_CALLBACK (_tp_cli_media_stream_handler_collect_args_of_start_telephony_event),
      _tp_cli_media_stream_handler_invoke_callback_for_start_telephony_event,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_media_stream_handler_signal_callback_stop_telephony_event:
 * @proxy: The proxy on which tp_cli_media_stream_handler_connect_to_stop_telephony_event ()
 *  was called
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal StopTelephonyEvent.
 */
static void
_tp_cli_media_stream_handler_invoke_callback_for_stop_telephony_event (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_signal_callback_stop_telephony_event callback =
      (tp_cli_media_stream_handler_signal_callback_stop_telephony_event) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      user_data,
      weak_object);

  if (args != NULL)
    g_value_array_free (args);

  g_object_unref (tpproxy);
}
/**
 * tp_cli_media_stream_handler_connect_to_stop_telephony_event:
 * @proxy: A #TpMediaStreamHandler or subclass
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
 * Connect a handler to the signal StopTelephonyEvent.
 *
 * Request that any ongoing telephony events (as defined by RFC 4733)         being transmitted over this stream are stopped.
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_media_stream_handler_connect_to_stop_telephony_event (TpMediaStreamHandler *proxy,
    tp_cli_media_stream_handler_signal_callback_stop_telephony_event callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[1] = {
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_MEDIA_STREAM_HANDLER, "StopTelephonyEvent",
      expected_types,
      NULL, /* no args => no collector function */
      _tp_cli_media_stream_handler_invoke_callback_for_stop_telephony_event,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_media_stream_handler_signal_callback_set_stream_held:
 * @proxy: The proxy on which tp_cli_media_stream_handler_connect_to_set_stream_held ()
 *  was called
 * @arg_Held: If true, the stream is to be placed on hold.
 * @user_data: User-supplied data
 * @weak_object: User-supplied weakly referenced object
 *
 * Represents the signature of a callback for the signal SetStreamHeld.
 */
static void
_tp_cli_media_stream_handler_collect_args_of_set_stream_held (DBusGProxy *proxy G_GNUC_UNUSED,
    gboolean arg_Held,
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
  g_value_set_boolean (args->values + 0, arg_Held);

  tp_proxy_signal_connection_v0_take_results (sc, args);
}
static void
_tp_cli_media_stream_handler_invoke_callback_for_set_stream_held (TpProxy *tpproxy,
    GError *error G_GNUC_UNUSED,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_signal_callback_set_stream_held callback =
      (tp_cli_media_stream_handler_signal_callback_set_stream_held) generic_callback;

  if (callback != NULL)
    callback (g_object_ref (tpproxy),
      g_value_get_boolean (args->values + 0),
      user_data,
      weak_object);

  g_value_array_free (args);
  g_object_unref (tpproxy);
}
/**
 * tp_cli_media_stream_handler_connect_to_set_stream_held:
 * @proxy: A #TpMediaStreamHandler or subclass
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
 * Connect a handler to the signal SetStreamHeld.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Emitted when the connection manager wishes to place the stream on           hold (so the streaming client should free hardware or software           resources) or take the stream off hold (so the streaming client           should reacquire the necessary resources).&lt;/p&gt;          &lt;p&gt;When placing a channel&apos;s streams on hold, the connection manager           SHOULD notify the remote contact that this will be done (if           appropriate in the protocol) before it emits this signal.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;It is assumed that relinquishing a resource will not fail.             If it does, the call is probably doomed anyway.&lt;/p&gt;         &lt;/tp:rationale&gt;          &lt;p&gt;When unholding a channel&apos;s streams, the connection manager           SHOULD emit this signal and wait for success to be indicated           via HoldState before it notifies the remote contact that the           channel has been taken off hold.&lt;/p&gt;          &lt;tp:rationale&gt;           &lt;p&gt;This means that if a resource is unavailable, the remote             contact will never even be told that we tried to acquire it.&lt;/p&gt;         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxySignalConnection containing all of the
 * above, which can be used to disconnect the signal; or
 * %NULL if the proxy does not have the desired interface
 * or has become invalid.
 */
TpProxySignalConnection *
tp_cli_media_stream_handler_connect_to_set_stream_held (TpMediaStreamHandler *proxy,
    tp_cli_media_stream_handler_signal_callback_set_stream_held callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object,
    GError **error)
{
  GType expected_types[2] = {
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
  g_return_val_if_fail (callback != NULL, NULL);

  return tp_proxy_signal_connection_v0_new ((TpProxy *) proxy,
      TP_IFACE_QUARK_MEDIA_STREAM_HANDLER, "SetStreamHeld",
      expected_types,
      G_CALLBACK (_tp_cli_media_stream_handler_collect_args_of_set_stream_held),
      _tp_cli_media_stream_handler_invoke_callback_for_set_stream_held,
      G_CALLBACK (callback), user_data, destroy,
      weak_object, error);
}

/**
 * tp_cli_media_stream_handler_callback_for_codec_choice:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a CodecChoice method call
 * succeeds or fails.
 */
static void
_tp_cli_media_stream_handler_collect_callback_codec_choice (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_media_stream_handler_invoke_callback_codec_choice (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_callback_for_codec_choice callback = (tp_cli_media_stream_handler_callback_for_codec_choice) generic_callback;

  if (error != NULL)
    {
      callback ((TpMediaStreamHandler *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpMediaStreamHandler *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_media_stream_handler_call_codec_choice:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Codec_ID: Used to pass an 'in' argument: (Undocumented)
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
 * Start a CodecChoice method call.
 *
 * Inform the connection manager of codec used to receive data.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_media_stream_handler_call_codec_choice (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    guint in_Codec_ID,
    tp_cli_media_stream_handler_callback_for_codec_choice callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "CodecChoice",
          G_TYPE_UINT, in_Codec_ID,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "CodecChoice", iface,
          _tp_cli_media_stream_handler_invoke_callback_codec_choice,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "CodecChoice",
              _tp_cli_media_stream_handler_collect_callback_codec_choice,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Codec_ID,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_media_stream_handler_run_state_codec_choice;
static void
_tp_cli_media_stream_handler_finish_running_codec_choice (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_media_stream_handler_run_state_codec_choice *state = user_data;

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
 * tp_cli_media_stream_handler_run_codec_choice:
 * @proxy: A #TpMediaStreamHandler or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Codec_ID: Used to pass an 'in' argument: (Undocumented)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method CodecChoice and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Inform the connection manager of codec used to receive data.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_media_stream_handler_run_codec_choice (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    guint in_Codec_ID,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  TpProxyPendingCall *pc;
  _tp_cli_media_stream_handler_run_state_codec_choice state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "CodecChoice", iface,
      _tp_cli_media_stream_handler_finish_running_codec_choice,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "CodecChoice",
          _tp_cli_media_stream_handler_collect_callback_codec_choice,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Codec_ID,
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
 * tp_cli_media_stream_handler_callback_for_error:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Error method call
 * succeeds or fails.
 */
static void
_tp_cli_media_stream_handler_collect_callback_error (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_media_stream_handler_invoke_callback_error (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_callback_for_error callback = (tp_cli_media_stream_handler_callback_for_error) generic_callback;

  if (error != NULL)
    {
      callback ((TpMediaStreamHandler *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpMediaStreamHandler *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_media_stream_handler_call_error:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Error_Code: Used to pass an 'in' argument: ID of error, from the MediaStreamError enumeration
 * @in_Message: Used to pass an 'in' argument: String describing the error
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
 * Start a Error method call.
 *
 * Inform the connection manager that an error occured in this stream. The         connection manager should emit the StreamError signal for the stream on         the relevant channel, and remove the stream from the session.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_media_stream_handler_call_error (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    guint in_Error_Code,
    const gchar *in_Message,
    tp_cli_media_stream_handler_callback_for_error callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Error",
          G_TYPE_UINT, in_Error_Code,
          G_TYPE_STRING, in_Message,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Error", iface,
          _tp_cli_media_stream_handler_invoke_callback_error,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Error",
              _tp_cli_media_stream_handler_collect_callback_error,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_UINT, in_Error_Code,
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
} _tp_cli_media_stream_handler_run_state_error;
static void
_tp_cli_media_stream_handler_finish_running_error (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_media_stream_handler_run_state_error *state = user_data;

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
 * tp_cli_media_stream_handler_run_error:
 * @proxy: A #TpMediaStreamHandler or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Error_Code: Used to pass an 'in' argument: ID of error, from the MediaStreamError enumeration
 * @in_Message: Used to pass an 'in' argument: String describing the error
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Error and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Inform the connection manager that an error occured in this stream. The         connection manager should emit the StreamError signal for the stream on         the relevant channel, and remove the stream from the session.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_media_stream_handler_run_error (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    guint in_Error_Code,
    const gchar *in_Message,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  TpProxyPendingCall *pc;
  _tp_cli_media_stream_handler_run_state_error state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Error", iface,
      _tp_cli_media_stream_handler_finish_running_error,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Error",
          _tp_cli_media_stream_handler_collect_callback_error,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_UINT, in_Error_Code,
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
 * tp_cli_media_stream_handler_callback_for_native_candidates_prepared:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a NativeCandidatesPrepared method call
 * succeeds or fails.
 */
static void
_tp_cli_media_stream_handler_collect_callback_native_candidates_prepared (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_media_stream_handler_invoke_callback_native_candidates_prepared (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_callback_for_native_candidates_prepared callback = (tp_cli_media_stream_handler_callback_for_native_candidates_prepared) generic_callback;

  if (error != NULL)
    {
      callback ((TpMediaStreamHandler *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpMediaStreamHandler *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_media_stream_handler_call_native_candidates_prepared:
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
 * Start a NativeCandidatesPrepared method call.
 *
 * Informs the connection manager that all possible native candisates         have been discovered for the moment.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_media_stream_handler_call_native_candidates_prepared (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    tp_cli_media_stream_handler_callback_for_native_candidates_prepared callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "NativeCandidatesPrepared",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "NativeCandidatesPrepared", iface,
          _tp_cli_media_stream_handler_invoke_callback_native_candidates_prepared,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "NativeCandidatesPrepared",
              _tp_cli_media_stream_handler_collect_callback_native_candidates_prepared,
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
} _tp_cli_media_stream_handler_run_state_native_candidates_prepared;
static void
_tp_cli_media_stream_handler_finish_running_native_candidates_prepared (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_media_stream_handler_run_state_native_candidates_prepared *state = user_data;

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
 * tp_cli_media_stream_handler_run_native_candidates_prepared:
 * @proxy: A #TpMediaStreamHandler or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method NativeCandidatesPrepared and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Informs the connection manager that all possible native candisates         have been discovered for the moment.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_media_stream_handler_run_native_candidates_prepared (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  TpProxyPendingCall *pc;
  _tp_cli_media_stream_handler_run_state_native_candidates_prepared state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "NativeCandidatesPrepared", iface,
      _tp_cli_media_stream_handler_finish_running_native_candidates_prepared,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "NativeCandidatesPrepared",
          _tp_cli_media_stream_handler_collect_callback_native_candidates_prepared,
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
 * tp_cli_media_stream_handler_callback_for_new_active_candidate_pair:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a NewActiveCandidatePair method call
 * succeeds or fails.
 */
static void
_tp_cli_media_stream_handler_collect_callback_new_active_candidate_pair (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_media_stream_handler_invoke_callback_new_active_candidate_pair (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_callback_for_new_active_candidate_pair callback = (tp_cli_media_stream_handler_callback_for_new_active_candidate_pair) generic_callback;

  if (error != NULL)
    {
      callback ((TpMediaStreamHandler *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpMediaStreamHandler *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_media_stream_handler_call_new_active_candidate_pair:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Native_Candidate_ID: Used to pass an 'in' argument: (Undocumented)
 * @in_Remote_Candidate_ID: Used to pass an 'in' argument: (Undocumented)
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
 * Start a NewActiveCandidatePair method call.
 *
 * Informs the connection manager that a valid candidate pair         has been discovered and streaming is in progress.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_media_stream_handler_call_new_active_candidate_pair (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    const gchar *in_Native_Candidate_ID,
    const gchar *in_Remote_Candidate_ID,
    tp_cli_media_stream_handler_callback_for_new_active_candidate_pair callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "NewActiveCandidatePair",
          G_TYPE_STRING, in_Native_Candidate_ID,
          G_TYPE_STRING, in_Remote_Candidate_ID,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "NewActiveCandidatePair", iface,
          _tp_cli_media_stream_handler_invoke_callback_new_active_candidate_pair,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "NewActiveCandidatePair",
              _tp_cli_media_stream_handler_collect_callback_new_active_candidate_pair,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Native_Candidate_ID,
              G_TYPE_STRING, in_Remote_Candidate_ID,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_media_stream_handler_run_state_new_active_candidate_pair;
static void
_tp_cli_media_stream_handler_finish_running_new_active_candidate_pair (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_media_stream_handler_run_state_new_active_candidate_pair *state = user_data;

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
 * tp_cli_media_stream_handler_run_new_active_candidate_pair:
 * @proxy: A #TpMediaStreamHandler or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Native_Candidate_ID: Used to pass an 'in' argument: (Undocumented)
 * @in_Remote_Candidate_ID: Used to pass an 'in' argument: (Undocumented)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method NewActiveCandidatePair and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Informs the connection manager that a valid candidate pair         has been discovered and streaming is in progress.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_media_stream_handler_run_new_active_candidate_pair (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    const gchar *in_Native_Candidate_ID,
    const gchar *in_Remote_Candidate_ID,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  TpProxyPendingCall *pc;
  _tp_cli_media_stream_handler_run_state_new_active_candidate_pair state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "NewActiveCandidatePair", iface,
      _tp_cli_media_stream_handler_finish_running_new_active_candidate_pair,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "NewActiveCandidatePair",
          _tp_cli_media_stream_handler_collect_callback_new_active_candidate_pair,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_STRING, in_Native_Candidate_ID,
              G_TYPE_STRING, in_Remote_Candidate_ID,
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
 * tp_cli_media_stream_handler_callback_for_new_native_candidate:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a NewNativeCandidate method call
 * succeeds or fails.
 */
static void
_tp_cli_media_stream_handler_collect_callback_new_native_candidate (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_media_stream_handler_invoke_callback_new_native_candidate (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_callback_for_new_native_candidate callback = (tp_cli_media_stream_handler_callback_for_new_native_candidate) generic_callback;

  if (error != NULL)
    {
      callback ((TpMediaStreamHandler *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpMediaStreamHandler *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_media_stream_handler_call_new_native_candidate:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Candidate_ID: Used to pass an 'in' argument: String identifier for this candidate
 * @in_Transports: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           Array of transports for this candidate, with fields:           &lt;ul&gt;             &lt;li&gt;component number&lt;/li&gt;             &lt;li&gt;IP address (as a string)&lt;/li&gt;             &lt;li&gt;port&lt;/li&gt;             &lt;li&gt;base network protocol (one of the values of MediaStreamBaseProto)&lt;/li&gt;             &lt;li&gt;proto subtype (e.g. RTP)&lt;/li&gt;             &lt;li&gt;proto profile (e.g. AVP)&lt;/li&gt;             &lt;li&gt;our preference value of this transport (double in range 0.0-1.0               inclusive); 1 signals the most preferred transport&lt;/li&gt;             &lt;li&gt;transport type, one of the values of MediaStreamTransportType&lt;/li&gt;             &lt;li&gt;username if authentication is required&lt;/li&gt;             &lt;li&gt;password if authentication is required&lt;/li&gt;           &lt;/ul&gt;
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
 * Start a NewNativeCandidate method call.
 *
 * Inform this MediaStreamHandler that a new native transport candidate         has been ascertained.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_media_stream_handler_call_new_native_candidate (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    const gchar *in_Candidate_ID,
    const GPtrArray *in_Transports,
    tp_cli_media_stream_handler_callback_for_new_native_candidate callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "NewNativeCandidate",
          G_TYPE_STRING, in_Candidate_ID,
          (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_DOUBLE, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))), in_Transports,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "NewNativeCandidate", iface,
          _tp_cli_media_stream_handler_invoke_callback_new_native_candidate,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "NewNativeCandidate",
              _tp_cli_media_stream_handler_collect_callback_new_native_candidate,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_STRING, in_Candidate_ID,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_DOUBLE, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))), in_Transports,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_media_stream_handler_run_state_new_native_candidate;
static void
_tp_cli_media_stream_handler_finish_running_new_native_candidate (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_media_stream_handler_run_state_new_native_candidate *state = user_data;

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
 * tp_cli_media_stream_handler_run_new_native_candidate:
 * @proxy: A #TpMediaStreamHandler or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Candidate_ID: Used to pass an 'in' argument: String identifier for this candidate
 * @in_Transports: Used to pass an 'in' argument: &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           Array of transports for this candidate, with fields:           &lt;ul&gt;             &lt;li&gt;component number&lt;/li&gt;             &lt;li&gt;IP address (as a string)&lt;/li&gt;             &lt;li&gt;port&lt;/li&gt;             &lt;li&gt;base network protocol (one of the values of MediaStreamBaseProto)&lt;/li&gt;             &lt;li&gt;proto subtype (e.g. RTP)&lt;/li&gt;             &lt;li&gt;proto profile (e.g. AVP)&lt;/li&gt;             &lt;li&gt;our preference value of this transport (double in range 0.0-1.0               inclusive); 1 signals the most preferred transport&lt;/li&gt;             &lt;li&gt;transport type, one of the values of MediaStreamTransportType&lt;/li&gt;             &lt;li&gt;username if authentication is required&lt;/li&gt;             &lt;li&gt;password if authentication is required&lt;/li&gt;           &lt;/ul&gt;
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method NewNativeCandidate and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Inform this MediaStreamHandler that a new native transport candidate         has been ascertained.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_media_stream_handler_run_new_native_candidate (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    const gchar *in_Candidate_ID,
    const GPtrArray *in_Transports,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  TpProxyPendingCall *pc;
  _tp_cli_media_stream_handler_run_state_new_native_candidate state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "NewNativeCandidate", iface,
      _tp_cli_media_stream_handler_finish_running_new_native_candidate,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "NewNativeCandidate",
          _tp_cli_media_stream_handler_collect_callback_new_native_candidate,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_STRING, in_Candidate_ID,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_DOUBLE, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INVALID)))), in_Transports,
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
 * tp_cli_media_stream_handler_callback_for_ready:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a Ready method call
 * succeeds or fails.
 */
static void
_tp_cli_media_stream_handler_collect_callback_ready (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_media_stream_handler_invoke_callback_ready (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_callback_for_ready callback = (tp_cli_media_stream_handler_callback_for_ready) generic_callback;

  if (error != NULL)
    {
      callback ((TpMediaStreamHandler *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpMediaStreamHandler *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_media_stream_handler_call_ready:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Codecs: Used to pass an 'in' argument: Locally-supported codecs.
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
 * Start a Ready method call.
 *
 * Inform the connection manager that a client is ready to handle         this StreamHandler. Also provide it with info about all supported         codecs.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_media_stream_handler_call_ready (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    const GPtrArray *in_Codecs,
    tp_cli_media_stream_handler_callback_for_ready callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "Ready",
          (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))), in_Codecs,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "Ready", iface,
          _tp_cli_media_stream_handler_invoke_callback_ready,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "Ready",
              _tp_cli_media_stream_handler_collect_callback_ready,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))), in_Codecs,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_media_stream_handler_run_state_ready;
static void
_tp_cli_media_stream_handler_finish_running_ready (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_media_stream_handler_run_state_ready *state = user_data;

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
 * tp_cli_media_stream_handler_run_ready:
 * @proxy: A #TpMediaStreamHandler or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Codecs: Used to pass an 'in' argument: Locally-supported codecs.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method Ready and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Inform the connection manager that a client is ready to handle         this StreamHandler. Also provide it with info about all supported         codecs.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_media_stream_handler_run_ready (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    const GPtrArray *in_Codecs,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  TpProxyPendingCall *pc;
  _tp_cli_media_stream_handler_run_state_ready state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "Ready", iface,
      _tp_cli_media_stream_handler_finish_running_ready,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "Ready",
          _tp_cli_media_stream_handler_collect_callback_ready,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))), in_Codecs,
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
 * tp_cli_media_stream_handler_callback_for_set_local_codecs:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a SetLocalCodecs method call
 * succeeds or fails.
 */
static void
_tp_cli_media_stream_handler_collect_callback_set_local_codecs (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_media_stream_handler_invoke_callback_set_local_codecs (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_callback_for_set_local_codecs callback = (tp_cli_media_stream_handler_callback_for_set_local_codecs) generic_callback;

  if (error != NULL)
    {
      callback ((TpMediaStreamHandler *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpMediaStreamHandler *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_media_stream_handler_call_set_local_codecs:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Codecs: Used to pass an 'in' argument: Locally-supported codecs
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
 * Start a SetLocalCodecs method call.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Used to provide codecs after Ready(), so the media client can go           ready for an incoming call and exchange candidates/codecs before           knowing what local codecs are available.&lt;/p&gt;          &lt;p&gt;This is useful for gatewaying calls between two connection managers.           Given an incoming call, you need to call           &lt;tp:member-ref&gt;Ready&lt;/tp:member-ref&gt; to get the remote codecs before           you can use them as the &amp;quot;local&amp;quot; codecs to place the outgoing call,           and hence receive the outgoing call&apos;s remote codecs to use as the           incoming call&apos;s &amp;quot;local&amp;quot; codecs.&lt;/p&gt;          &lt;p&gt;In this situation, you would pass an empty list of codecs to the           incoming call&apos;s Ready method, then later call SetLocalCodecs on the           incoming call in order to respond to the offer.&lt;/p&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_media_stream_handler_call_set_local_codecs (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    const GPtrArray *in_Codecs,
    tp_cli_media_stream_handler_callback_for_set_local_codecs callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "SetLocalCodecs",
          (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))), in_Codecs,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "SetLocalCodecs", iface,
          _tp_cli_media_stream_handler_invoke_callback_set_local_codecs,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "SetLocalCodecs",
              _tp_cli_media_stream_handler_collect_callback_set_local_codecs,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))), in_Codecs,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_media_stream_handler_run_state_set_local_codecs;
static void
_tp_cli_media_stream_handler_finish_running_set_local_codecs (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_media_stream_handler_run_state_set_local_codecs *state = user_data;

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
 * tp_cli_media_stream_handler_run_set_local_codecs:
 * @proxy: A #TpMediaStreamHandler or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Codecs: Used to pass an 'in' argument: Locally-supported codecs
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method SetLocalCodecs and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Used to provide codecs after Ready(), so the media client can go           ready for an incoming call and exchange candidates/codecs before           knowing what local codecs are available.&lt;/p&gt;          &lt;p&gt;This is useful for gatewaying calls between two connection managers.           Given an incoming call, you need to call           &lt;tp:member-ref&gt;Ready&lt;/tp:member-ref&gt; to get the remote codecs before           you can use them as the &amp;quot;local&amp;quot; codecs to place the outgoing call,           and hence receive the outgoing call&apos;s remote codecs to use as the           incoming call&apos;s &amp;quot;local&amp;quot; codecs.&lt;/p&gt;          &lt;p&gt;In this situation, you would pass an empty list of codecs to the           incoming call&apos;s Ready method, then later call SetLocalCodecs on the           incoming call in order to respond to the offer.&lt;/p&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_media_stream_handler_run_set_local_codecs (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    const GPtrArray *in_Codecs,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  TpProxyPendingCall *pc;
  _tp_cli_media_stream_handler_run_state_set_local_codecs state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "SetLocalCodecs", iface,
      _tp_cli_media_stream_handler_finish_running_set_local_codecs,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "SetLocalCodecs",
          _tp_cli_media_stream_handler_collect_callback_set_local_codecs,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))), in_Codecs,
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
 * tp_cli_media_stream_handler_callback_for_stream_state:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a StreamState method call
 * succeeds or fails.
 */
static void
_tp_cli_media_stream_handler_collect_callback_stream_state (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_media_stream_handler_invoke_callback_stream_state (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_callback_for_stream_state callback = (tp_cli_media_stream_handler_callback_for_stream_state) generic_callback;

  if (error != NULL)
    {
      callback ((TpMediaStreamHandler *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpMediaStreamHandler *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_media_stream_handler_call_stream_state:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_State: Used to pass an 'in' argument: (Undocumented)
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
 * Start a StreamState method call.
 *
 * Informs the connection manager of the stream&apos;s current state, as         as specified in Channel.Type.StreamedMedia::ListStreams.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_media_stream_handler_call_stream_state (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    guint in_State,
    tp_cli_media_stream_handler_callback_for_stream_state callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "StreamState",
          G_TYPE_UINT, in_State,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "StreamState", iface,
          _tp_cli_media_stream_handler_invoke_callback_stream_state,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "StreamState",
              _tp_cli_media_stream_handler_collect_callback_stream_state,
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
} _tp_cli_media_stream_handler_run_state_stream_state;
static void
_tp_cli_media_stream_handler_finish_running_stream_state (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_media_stream_handler_run_state_stream_state *state = user_data;

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
 * tp_cli_media_stream_handler_run_stream_state:
 * @proxy: A #TpMediaStreamHandler or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_State: Used to pass an 'in' argument: (Undocumented)
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method StreamState and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Informs the connection manager of the stream&apos;s current state, as         as specified in Channel.Type.StreamedMedia::ListStreams.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_media_stream_handler_run_stream_state (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    guint in_State,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  TpProxyPendingCall *pc;
  _tp_cli_media_stream_handler_run_state_stream_state state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "StreamState", iface,
      _tp_cli_media_stream_handler_finish_running_stream_state,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "StreamState",
          _tp_cli_media_stream_handler_collect_callback_stream_state,
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
 * tp_cli_media_stream_handler_callback_for_supported_codecs:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a SupportedCodecs method call
 * succeeds or fails.
 */
static void
_tp_cli_media_stream_handler_collect_callback_supported_codecs (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_media_stream_handler_invoke_callback_supported_codecs (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_callback_for_supported_codecs callback = (tp_cli_media_stream_handler_callback_for_supported_codecs) generic_callback;

  if (error != NULL)
    {
      callback ((TpMediaStreamHandler *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpMediaStreamHandler *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_media_stream_handler_call_supported_codecs:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Codecs: Used to pass an 'in' argument: Locally supported codecs.
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
 * Start a SupportedCodecs method call.
 *
 * Inform the connection manager of the supported codecs for this session.         This is called after the connection manager has emitted SetRemoteCodecs         to notify what codecs are supported by the peer, and will thus be an         intersection of all locally supported codecs (passed to Ready)         and those supported by the peer.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_media_stream_handler_call_supported_codecs (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    const GPtrArray *in_Codecs,
    tp_cli_media_stream_handler_callback_for_supported_codecs callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "SupportedCodecs",
          (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))), in_Codecs,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "SupportedCodecs", iface,
          _tp_cli_media_stream_handler_invoke_callback_supported_codecs,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "SupportedCodecs",
              _tp_cli_media_stream_handler_collect_callback_supported_codecs,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))), in_Codecs,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_media_stream_handler_run_state_supported_codecs;
static void
_tp_cli_media_stream_handler_finish_running_supported_codecs (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_media_stream_handler_run_state_supported_codecs *state = user_data;

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
 * tp_cli_media_stream_handler_run_supported_codecs:
 * @proxy: A #TpMediaStreamHandler or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Codecs: Used to pass an 'in' argument: Locally supported codecs.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method SupportedCodecs and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Inform the connection manager of the supported codecs for this session.         This is called after the connection manager has emitted SetRemoteCodecs         to notify what codecs are supported by the peer, and will thus be an         intersection of all locally supported codecs (passed to Ready)         and those supported by the peer.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_media_stream_handler_run_supported_codecs (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    const GPtrArray *in_Codecs,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  TpProxyPendingCall *pc;
  _tp_cli_media_stream_handler_run_state_supported_codecs state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "SupportedCodecs", iface,
      _tp_cli_media_stream_handler_finish_running_supported_codecs,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "SupportedCodecs",
          _tp_cli_media_stream_handler_collect_callback_supported_codecs,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))), in_Codecs,
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
 * tp_cli_media_stream_handler_callback_for_codecs_updated:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a CodecsUpdated method call
 * succeeds or fails.
 */
static void
_tp_cli_media_stream_handler_collect_callback_codecs_updated (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_media_stream_handler_invoke_callback_codecs_updated (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_callback_for_codecs_updated callback = (tp_cli_media_stream_handler_callback_for_codecs_updated) generic_callback;

  if (error != NULL)
    {
      callback ((TpMediaStreamHandler *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpMediaStreamHandler *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_media_stream_handler_call_codecs_updated:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Codecs: Used to pass an 'in' argument: Locally supported codecs, which SHOULD be the same as were previously           in effect, but possibly with different parameters.
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
 * Start a CodecsUpdated method call.
 *
 * Inform the connection manager that the parameters of the supported         codecs for this session have changed. The connection manager should         send the new parameters to the remote contact.          &lt;tp:rationale&gt;           This is required for H.264 and Theora, for example.         &lt;/tp:rationale&gt;
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_media_stream_handler_call_codecs_updated (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    const GPtrArray *in_Codecs,
    tp_cli_media_stream_handler_callback_for_codecs_updated callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "CodecsUpdated",
          (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))), in_Codecs,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "CodecsUpdated", iface,
          _tp_cli_media_stream_handler_invoke_callback_codecs_updated,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "CodecsUpdated",
              _tp_cli_media_stream_handler_collect_callback_codecs_updated,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))), in_Codecs,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_media_stream_handler_run_state_codecs_updated;
static void
_tp_cli_media_stream_handler_finish_running_codecs_updated (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_media_stream_handler_run_state_codecs_updated *state = user_data;

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
 * tp_cli_media_stream_handler_run_codecs_updated:
 * @proxy: A #TpMediaStreamHandler or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Codecs: Used to pass an 'in' argument: Locally supported codecs, which SHOULD be the same as were previously           in effect, but possibly with different parameters.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method CodecsUpdated and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Inform the connection manager that the parameters of the supported         codecs for this session have changed. The connection manager should         send the new parameters to the remote contact.          &lt;tp:rationale&gt;           This is required for H.264 and Theora, for example.         &lt;/tp:rationale&gt;
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_media_stream_handler_run_codecs_updated (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    const GPtrArray *in_Codecs,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  TpProxyPendingCall *pc;
  _tp_cli_media_stream_handler_run_state_codecs_updated state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "CodecsUpdated", iface,
      _tp_cli_media_stream_handler_finish_running_codecs_updated,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "CodecsUpdated",
          _tp_cli_media_stream_handler_collect_callback_codecs_updated,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              (dbus_g_type_get_collection ("GPtrArray", (dbus_g_type_get_struct ("GValueArray", G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_UINT, DBUS_TYPE_G_STRING_STRING_HASHTABLE, G_TYPE_INVALID)))), in_Codecs,
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
 * tp_cli_media_stream_handler_callback_for_hold_state:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a HoldState method call
 * succeeds or fails.
 */
static void
_tp_cli_media_stream_handler_collect_callback_hold_state (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_media_stream_handler_invoke_callback_hold_state (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_callback_for_hold_state callback = (tp_cli_media_stream_handler_callback_for_hold_state) generic_callback;

  if (error != NULL)
    {
      callback ((TpMediaStreamHandler *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpMediaStreamHandler *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_media_stream_handler_call_hold_state:
 * @proxy: the #TpProxy
 * @timeout_ms: the timeout in milliseconds, or -1 to use the
 *   default
 * @in_Held: Used to pass an 'in' argument: If true, the stream is now on hold.
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
 * Start a HoldState method call.
 *
 * Notify the connection manager that the stream&apos;s hold state has         been changed successfully in response to SetStreamHeld.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_media_stream_handler_call_hold_state (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    gboolean in_Held,
    tp_cli_media_stream_handler_callback_for_hold_state callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "HoldState",
          G_TYPE_BOOLEAN, in_Held,
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "HoldState", iface,
          _tp_cli_media_stream_handler_invoke_callback_hold_state,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "HoldState",
              _tp_cli_media_stream_handler_collect_callback_hold_state,
              data,
              tp_proxy_pending_call_v0_completed,
              timeout_ms,
              G_TYPE_BOOLEAN, in_Held,
              G_TYPE_INVALID));

      return data;
    }
}

typedef struct {
    GMainLoop *loop;
    GError **error;
    unsigned success:1;
    unsigned completed:1;
} _tp_cli_media_stream_handler_run_state_hold_state;
static void
_tp_cli_media_stream_handler_finish_running_hold_state (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_media_stream_handler_run_state_hold_state *state = user_data;

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
 * tp_cli_media_stream_handler_run_hold_state:
 * @proxy: A #TpMediaStreamHandler or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @in_Held: Used to pass an 'in' argument: If true, the stream is now on hold.
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method HoldState and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Notify the connection manager that the stream&apos;s hold state has         been changed successfully in response to SetStreamHeld.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_media_stream_handler_run_hold_state (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    gboolean in_Held,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  TpProxyPendingCall *pc;
  _tp_cli_media_stream_handler_run_state_hold_state state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "HoldState", iface,
      _tp_cli_media_stream_handler_finish_running_hold_state,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "HoldState",
          _tp_cli_media_stream_handler_collect_callback_hold_state,
          pc,
          tp_proxy_pending_call_v0_completed,
          timeout_ms,
              G_TYPE_BOOLEAN, in_Held,
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
 * tp_cli_media_stream_handler_callback_for_unhold_failure:
 * @proxy: the proxy on which the call was made
 * @error: %NULL on success, or an error on failure
 * @user_data: user-supplied data
 * @weak_object: user-supplied object
 *
 * Signature of the callback called when a UnholdFailure method call
 * succeeds or fails.
 */
static void
_tp_cli_media_stream_handler_collect_callback_unhold_failure (DBusGProxy *proxy,
    DBusGProxyCall *call,
    gpointer user_data)
{
  GError *error = NULL;

  dbus_g_proxy_end_call (proxy, call, &error,
      G_TYPE_INVALID);
  tp_proxy_pending_call_v0_take_results (user_data, error,NULL);
}
static void
_tp_cli_media_stream_handler_invoke_callback_unhold_failure (TpProxy *self,
    GError *error,
    GValueArray *args,
    GCallback generic_callback,
    gpointer user_data,
    GObject *weak_object)
{
  tp_cli_media_stream_handler_callback_for_unhold_failure callback = (tp_cli_media_stream_handler_callback_for_unhold_failure) generic_callback;

  if (error != NULL)
    {
      callback ((TpMediaStreamHandler *) self,
          error, user_data, weak_object);
      g_error_free (error);
      return;
    }
  callback ((TpMediaStreamHandler *) self,
      error, user_data, weak_object);

  if (args != NULL)
    g_value_array_free (args);
}

/**
 * tp_cli_media_stream_handler_call_unhold_failure:
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
 * Start a UnholdFailure method call.
 *
 * Notify the connection manager that an attempt to reacquire the         necessary hardware or software resources to unhold the stream,         in response to SetStreamHeld, has failed.
 *
 * Returns: a #TpProxyPendingCall representing the call in
 *  progress. It is borrowed from the object, and will become
 *  invalid when the callback is called, the call is
 *  cancelled or the #TpProxy becomes invalid.
 */
TpProxyPendingCall *
tp_cli_media_stream_handler_call_unhold_failure (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    tp_cli_media_stream_handler_callback_for_unhold_failure callback,
    gpointer user_data,
    GDestroyNotify destroy,
    GObject *weak_object)
{
  GError *error = NULL;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  DBusGProxy *iface;

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), NULL);
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
      dbus_g_proxy_call_no_reply (iface, "UnholdFailure",
          G_TYPE_INVALID);
      return NULL;
    }
  else
    {
      TpProxyPendingCall *data;

      data = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
          interface, "UnholdFailure", iface,
          _tp_cli_media_stream_handler_invoke_callback_unhold_failure,
          G_CALLBACK (callback), user_data, destroy,
          weak_object, FALSE);
      tp_proxy_pending_call_v0_take_pending_call (data,
          dbus_g_proxy_begin_call_with_timeout (iface,
              "UnholdFailure",
              _tp_cli_media_stream_handler_collect_callback_unhold_failure,
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
} _tp_cli_media_stream_handler_run_state_unhold_failure;
static void
_tp_cli_media_stream_handler_finish_running_unhold_failure (TpProxy *self G_GNUC_UNUSED,
    GError *error,
    GValueArray *args,
    GCallback unused G_GNUC_UNUSED,
    gpointer user_data G_GNUC_UNUSED,
    GObject *unused2 G_GNUC_UNUSED)
{
  _tp_cli_media_stream_handler_run_state_unhold_failure *state = user_data;

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
 * tp_cli_media_stream_handler_run_unhold_failure:
 * @proxy: A #TpMediaStreamHandler or subclass
 * @timeout_ms: Timeout in milliseconds, or -1 for default
 * @error: If not %NULL, used to return errors if %FALSE 
 *  is returned
 * @loop: If not %NULL, set before re-entering 
 *  the main loop, to point to a #GMainLoop 
 *  which can be used to cancel this call with 
 *  g_main_loop_quit(), causing a return of 
 *  %FALSE with @error set to %TP_DBUS_ERROR_CANCELLED
 *
 * Call the method UnholdFailure and run the main loop
 * until it returns. Before calling this method, you must
 * add a reference to any borrowed objects you need to keep,
 * and generally ensure that everything is in a consistent
 * state.
 *
 * Notify the connection manager that an attempt to reacquire the         necessary hardware or software resources to unhold the stream,         in response to SetStreamHeld, has failed.
 *
 * Returns: TRUE on success, FALSE and sets @error on error
 */
gboolean
tp_cli_media_stream_handler_run_unhold_failure (TpMediaStreamHandler *proxy,
    gint timeout_ms,
    GError **error,
    GMainLoop **loop)
{
  DBusGProxy *iface;
  GQuark interface = TP_IFACE_QUARK_MEDIA_STREAM_HANDLER;
  TpProxyPendingCall *pc;
  _tp_cli_media_stream_handler_run_state_unhold_failure state = {
      NULL /* loop */, error,
      FALSE /* completed */, FALSE /* success */ };

  g_return_val_if_fail (TP_IS_MEDIA_STREAM_HANDLER (proxy), FALSE);

  iface = tp_proxy_borrow_interface_by_id
       ((TpProxy *) proxy, interface, error);

  if (iface == NULL)
    return FALSE;

  state.loop = g_main_loop_new (NULL, FALSE);

  pc = tp_proxy_pending_call_v0_new ((TpProxy *) proxy,
      interface, "UnholdFailure", iface,
      _tp_cli_media_stream_handler_finish_running_unhold_failure,
      NULL, &state, NULL, NULL, TRUE);

  if (loop != NULL)
    *loop = state.loop;

  tp_proxy_pending_call_v0_take_pending_call (pc,
      dbus_g_proxy_begin_call_with_timeout (iface,
          "UnholdFailure",
          _tp_cli_media_stream_handler_collect_callback_unhold_failure,
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


/*
 * tp_cli_media_stream_handler_add_signals:
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
tp_cli_media_stream_handler_add_signals (TpProxy *self G_GNUC_UNUSED,
    guint quark,
    DBusGProxy *proxy,
    gpointer unused G_GNUC_UNUSED)
{
  if (quark == TP_IFACE_QUARK_MEDIA_STREAM_HANDLER)
    tp_cli_add_signals_for_media_stream_handler (proxy);
}
