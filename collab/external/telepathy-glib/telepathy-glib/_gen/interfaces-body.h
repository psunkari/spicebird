/* Generated from: telepathy-glib



 */

GQuark
tp_iface_quark_connection_manager (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.ConnectionManager");
    }

  return quark;
}

GQuark
tp_iface_quark_connection (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection");
    }

  return quark;
}

GQuark
tp_iface_quark_connection_interface_aliasing (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection.Interface.Aliasing");
    }

  return quark;
}

GQuark
tp_iface_quark_connection_interface_avatars (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection.Interface.Avatars");
    }

  return quark;
}

GQuark
tp_iface_quark_connection_interface_capabilities (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection.Interface.Capabilities");
    }

  return quark;
}

GQuark
tp_iface_quark_connection_interface_contact_capabilities (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection.Interface.ContactCapabilities");
    }

  return quark;
}

GQuark
tp_iface_quark_connection_interface_simple_presence (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection.Interface.SimplePresence");
    }

  return quark;
}

GQuark
tp_iface_quark_connection_interface_presence (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection.Interface.Presence");
    }

  return quark;
}

GQuark
tp_iface_quark_connection_interface_contacts (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection.Interface.Contacts");
    }

  return quark;
}

GQuark
tp_iface_quark_connection_interface_requests (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection.Interface.Requests");
    }

  return quark;
}

GQuark
tp_iface_quark_connection_interface_location (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Connection.Interface.Location");
    }

  return quark;
}

GQuark
tp_iface_quark_channel (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_type_contact_list (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Type.ContactList");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_type_file_transfer (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Type.FileTransfer");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_type_streamed_media (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Type.StreamedMedia");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_type_room_list (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Type.RoomList");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_type_text (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Type.Text");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_type_tubes (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Type.Tubes");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_type_stream_tube (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Type.StreamTube");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_type_dbus_tube (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Type.DBusTube");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_interface_call_state (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Interface.CallState");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_interface_chat_state (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Interface.ChatState");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_interface_destroyable (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Interface.Destroyable");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_interface_dtmf (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Interface.DTMF");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_interface_group (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Interface.Group");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_interface_hold (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Interface.Hold");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_interface_media_signalling (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Interface.MediaSignalling");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_interface_messages (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Interface.Messages");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_interface_password (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Interface.Password");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_interface_tube (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Channel.Interface.Tube");
    }

  return quark;
}

GQuark
tp_iface_quark_media_session_handler (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Media.SessionHandler");
    }

  return quark;
}

GQuark
tp_iface_quark_media_stream_handler (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Media.StreamHandler");
    }

  return quark;
}

GQuark
tp_iface_quark_dbus_peer (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.DBus.Peer");
    }

  return quark;
}

GQuark
tp_iface_quark_dbus_introspectable (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.DBus.Introspectable");
    }

  return quark;
}

GQuark
tp_iface_quark_dbus_properties (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.DBus.Properties");
    }

  return quark;
}

GQuark
tp_iface_quark_properties_interface (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Properties");
    }

  return quark;
}

GQuark
tp_iface_quark_dbus_daemon (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.DBus");
    }

  return quark;
}

GQuark
tp_iface_quark_account_manager (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.AccountManager");
    }

  return quark;
}

GQuark
tp_iface_quark_account (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Account");
    }

  return quark;
}

GQuark
tp_iface_quark_account_interface_avatar (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Account.Interface.Avatar");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_dispatcher (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.ChannelDispatcher");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_dispatcher_interface_operation_list (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.ChannelDispatcher.Interface.OperationList");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_dispatch_operation (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.ChannelDispatchOperation");
    }

  return quark;
}

GQuark
tp_iface_quark_channel_request (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.ChannelRequest");
    }

  return quark;
}

GQuark
tp_iface_quark_client (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Client");
    }

  return quark;
}

GQuark
tp_iface_quark_client_observer (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Client.Observer");
    }

  return quark;
}

GQuark
tp_iface_quark_client_approver (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Client.Approver");
    }

  return quark;
}

GQuark
tp_iface_quark_client_handler (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Client.Handler");
    }

  return quark;
}

GQuark
tp_iface_quark_client_interface_requests (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Client.Interface.Requests");
    }

  return quark;
}

GQuark
tp_iface_quark_debug (void)
{
  static GQuark quark = 0;

  if (G_UNLIKELY (quark == 0))
    {
      quark = g_quark_from_static_string ("org.freedesktop.Telepathy.Debug");
    }

  return quark;
}

