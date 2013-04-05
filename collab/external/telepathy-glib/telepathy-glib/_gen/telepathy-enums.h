/* Generated from telepathy-glib



 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
TpConnMgrParamFlags:
 * @TP_CONN_MGR_PARAM_FLAG_REQUIRED: <![CDATA[           This parameter is required for connecting to the server.         ]]>
 * @TP_CONN_MGR_PARAM_FLAG_REGISTER: <![CDATA[           This parameter is required for registering an account on the           server.         ]]>
 * @TP_CONN_MGR_PARAM_FLAG_HAS_DEFAULT: <![CDATA[           This parameter has a default value, which is returned in           GetParameters; not providing this parameter is equivalent to           providing the default.         ]]>
 * @TP_CONN_MGR_PARAM_FLAG_SECRET: <![CDATA[           This parameter should be considered private or secret; for             instance, clients should store it in a "password safe" like             gnome-keyring or kwallet, omit it from debug logs, and use a             text input widget that hides the value of the parameter.            (Clients that support older connection managers may also treat             any parameter whose name contains "password" as though it had this             flag.)         ]]>
 * @TP_CONN_MGR_PARAM_FLAG_DBUS_PROPERTY: <![CDATA[           This parameter is also a D-Bus property on the resulting Connection; a           parameter named com.example.Duck.Macaroni with this flag           corresponds to the Macaroni property on the           com.example.Duck interface.  Its value can be queried           and possibly changed on an existing Connection using methods on the           org.freedesktop.DBus.Properties interface.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CONN_MGR_PARAM_FLAG_REQUIRED = 1,
    TP_CONN_MGR_PARAM_FLAG_REGISTER = 2,
    TP_CONN_MGR_PARAM_FLAG_HAS_DEFAULT = 4,
    TP_CONN_MGR_PARAM_FLAG_SECRET = 8,
    TP_CONN_MGR_PARAM_FLAG_DBUS_PROPERTY = 16,
} TpConnMgrParamFlags;

/**
 *
TpHandleType:
 * @TP_HANDLE_TYPE_NONE: <![CDATA[           A "null" handle type used to indicate the absence of a handle.           When a handle type and a handle appear as a pair, if the handle           type is zero, the handle must also be zero.         ]]>
 * @TP_HANDLE_TYPE_CONTACT: <![CDATA[           A contact         ]]>
 * @TP_HANDLE_TYPE_ROOM: <![CDATA[           A chat room         ]]>
 * @TP_HANDLE_TYPE_LIST: <![CDATA[           A server-generated contact list (see Channel.Interface.Group)         ]]>
 * @TP_HANDLE_TYPE_GROUP: <![CDATA[           A user-defined contact list (see Channel.Interface.Group)         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_HANDLE_TYPE_NONE = 0,
    TP_HANDLE_TYPE_CONTACT = 1,
    TP_HANDLE_TYPE_ROOM = 2,
    TP_HANDLE_TYPE_LIST = 3,
    TP_HANDLE_TYPE_GROUP = 4,
} TpHandleType;

/**
 * NUM_TP_HANDLE_TYPES:
 *
 * 1 higher than the highest valid value of #TpHandleType.
 */
#define NUM_TP_HANDLE_TYPES (4+1)

/**
 *
TpConnectionStatus:
 * @TP_CONNECTION_STATUS_CONNECTED: <![CDATA[             The connection is alive and all methods are available.         ]]>
 * @TP_CONNECTION_STATUS_CONNECTING: <![CDATA[             The connection has not yet been established, or has been             severed and reconnection is being attempted. Some methods may fail             until the connection has been established.         ]]>
 * @TP_CONNECTION_STATUS_DISCONNECTED: <![CDATA[             The connection has been severed and no method calls are             valid. The object may be removed from the bus at any time.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CONNECTION_STATUS_CONNECTED = 0,
    TP_CONNECTION_STATUS_CONNECTING = 1,
    TP_CONNECTION_STATUS_DISCONNECTED = 2,
} TpConnectionStatus;

/**
 * NUM_TP_CONNECTION_STATUSES:
 *
 * 1 higher than the highest valid value of #TpConnectionStatus.
 */
#define NUM_TP_CONNECTION_STATUSES (2+1)

/**
 *
TpConnectionStatusReason:
 * @TP_CONNECTION_STATUS_REASON_NONE_SPECIFIED: <![CDATA[           There is no reason set for this state change. Unknown status             reasons SHOULD be treated like this reason.            When disconnected for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Disconnected.         ]]>
 * @TP_CONNECTION_STATUS_REASON_REQUESTED: <![CDATA[           The change is in response to a user request. Changes to the             Connecting or Connected status SHOULD always indicate this reason;             changes to the Disconnected status SHOULD indicate this reason             if and only if the disconnection was requested by the user.            When disconnected for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Cancelled.         ]]>
 * @TP_CONNECTION_STATUS_REASON_NETWORK_ERROR: <![CDATA[           There was an error sending or receiving on the network socket.            When the status changes from Connecting to Disconnected for this             reason, the equivalent D-Bus error is either             org.freedesktop.Telepathy.Error.NetworkError,             org.freedesktop.Telepathy.Error.ConnectionRefused,             org.freedesktop.Telepathy.Error.ConnectionFailed             or some more specific error.            When the status changes from Connected to Disconnected for this             reason, the equivalent D-Bus error is either             org.freedesktop.Telepathy.Error.NetworkError,             org.freedesktop.Telepathy.Error.ConnectionLost             or some more specific error.         ]]>
 * @TP_CONNECTION_STATUS_REASON_AUTHENTICATION_FAILED: <![CDATA[           The username or password was invalid.            When disconnected for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.AuthenticationFailed.                    ]]>
 * @TP_CONNECTION_STATUS_REASON_ENCRYPTION_ERROR: <![CDATA[           There was an error negotiating SSL on this connection, or             encryption was unavailable and require-encryption was set when the             connection was created.            When disconnected for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.EncryptionNotAvailable             if encryption was not available at all, or             org.freedesktop.Telepathy.Error.EncryptionError             if encryption failed.         ]]>
 * @TP_CONNECTION_STATUS_REASON_NAME_IN_USE: <![CDATA[           In general, this reason indicates that the requested account             name or other identification could not be used due to conflict             with another connection. It can be divided into three cases:                         If the status change is from Connecting to Disconnected               and the 'register' parameter to RequestConnection was present               and true, the requested account could not be created on the               server because it already exists.               The equivalent D-Bus error is               org.freedesktop.Telepathy.Error.RegistrationExists.                           If the status change is from Connecting to Disconnected               but the 'register' parameter is absent or false, the connection               manager could not connect to the specified account because               a connection to that account already exists.               The equivalent D-Bus error is               org.freedesktop.Telepathy.Error.AlreadyConnected.                                 In some protocols, like XMPP (when connecting with the same                 JID and resource as an existing connection), the existing                 connection "wins" and the new one fails to connect.                                          If the status change is from Connected to Disconnected,               the existing connection was automatically disconnected because               a new connection to the same account (perhaps from a different               client or location) was established.               The equivalent D-Bus error is               org.freedesktop.Telepathy.Error.ConnectionReplaced.                                 In some protocols, like MSNP (when connecting twice with the                 same Passport), the new connection "wins" and the                 existing one is automatically disconnected.                                                ]]>
 * @TP_CONNECTION_STATUS_REASON_CERT_NOT_PROVIDED: <![CDATA[           The server did not provide a SSL certificate.            When disconnected for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Cert.NotProvided.                    ]]>
 * @TP_CONNECTION_STATUS_REASON_CERT_UNTRUSTED: <![CDATA[           The server's SSL certificate is signed by an untrusted certifying             authority. This error SHOULD NOT be used to represent a self-signed             certificate: use the more specific Cert_Self_Signed reason for             that.            When disconnected for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Cert.Untrusted.                    ]]>
 * @TP_CONNECTION_STATUS_REASON_CERT_EXPIRED: <![CDATA[           The server's SSL certificate has expired.            When disconnected for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Cert.Expired.                    ]]>
 * @TP_CONNECTION_STATUS_REASON_CERT_NOT_ACTIVATED: <![CDATA[           The server's SSL certificate is not yet valid.            When disconnected for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Cert.NotActivated.                    ]]>
 * @TP_CONNECTION_STATUS_REASON_CERT_HOSTNAME_MISMATCH: <![CDATA[           The server's SSL certificate did not match its hostname.            When disconnected for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Cert.HostnameMismatch.                    ]]>
 * @TP_CONNECTION_STATUS_REASON_CERT_FINGERPRINT_MISMATCH: <![CDATA[           The server's SSL certificate does not have the expected             fingerprint.            When disconnected for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Cert.FingerprintMismatch.                    ]]>
 * @TP_CONNECTION_STATUS_REASON_CERT_SELF_SIGNED: <![CDATA[           The server's SSL certificate is self-signed.            When disconnected for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Cert.HostnameMismatch.                    ]]>
 * @TP_CONNECTION_STATUS_REASON_CERT_OTHER_ERROR: <![CDATA[           There was some other error validating the server's SSL             certificate.            When disconnected for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Cert.Invalid.                    ]]>
 *
 * <![CDATA[         A reason why the status of the connection changed. Apart from           Requested, the values of this enumeration only make sense as           reasons why the status changed to Disconnected.       ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CONNECTION_STATUS_REASON_NONE_SPECIFIED = 0,
    TP_CONNECTION_STATUS_REASON_REQUESTED = 1,
    TP_CONNECTION_STATUS_REASON_NETWORK_ERROR = 2,
    TP_CONNECTION_STATUS_REASON_AUTHENTICATION_FAILED = 3,
    TP_CONNECTION_STATUS_REASON_ENCRYPTION_ERROR = 4,
    TP_CONNECTION_STATUS_REASON_NAME_IN_USE = 5,
    TP_CONNECTION_STATUS_REASON_CERT_NOT_PROVIDED = 6,
    TP_CONNECTION_STATUS_REASON_CERT_UNTRUSTED = 7,
    TP_CONNECTION_STATUS_REASON_CERT_EXPIRED = 8,
    TP_CONNECTION_STATUS_REASON_CERT_NOT_ACTIVATED = 9,
    TP_CONNECTION_STATUS_REASON_CERT_HOSTNAME_MISMATCH = 10,
    TP_CONNECTION_STATUS_REASON_CERT_FINGERPRINT_MISMATCH = 11,
    TP_CONNECTION_STATUS_REASON_CERT_SELF_SIGNED = 12,
    TP_CONNECTION_STATUS_REASON_CERT_OTHER_ERROR = 13,
} TpConnectionStatusReason;

/**
 * NUM_TP_CONNECTION_STATUS_REASONS:
 *
 * 1 higher than the highest valid value of #TpConnectionStatusReason.
 */
#define NUM_TP_CONNECTION_STATUS_REASONS (13+1)

/**
 *
TpConnectionAliasFlags:
 * @TP_CONNECTION_ALIAS_FLAG_USER_SET: <![CDATA[           The aliases of contacts on this connection may be changed by the             user of the service, not just by the contacts themselves. This is             the case on Jabber, for instance.           It is possible that aliases can be changed by the contacts too -             which alias takes precedence is not defined by this             specification, and depends on the server and/or connection manager             implementation.           This flag only applies to the aliases of "globally valid" contact             handles. At this time, clients should not expect to be able to             change the aliases corresponding to any channel-specific             handles. If this becomes possible in future, a new flag will             be defined.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CONNECTION_ALIAS_FLAG_USER_SET = 1,
} TpConnectionAliasFlags;

/**
 *
TpConnectionCapabilityFlags:
 * @TP_CONNECTION_CAPABILITY_FLAG_CREATE: <![CDATA[           The given channel type and handle can be given to RequestChannel           to create a new channel of this type.         ]]>
 * @TP_CONNECTION_CAPABILITY_FLAG_INVITE: <![CDATA[           The given contact can be invited to an existing channel of this type.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CONNECTION_CAPABILITY_FLAG_CREATE = 1,
    TP_CONNECTION_CAPABILITY_FLAG_INVITE = 2,
} TpConnectionCapabilityFlags;

/**
 *
TpConnectionPresenceType:
 * @TP_CONNECTION_PRESENCE_TYPE_UNSET: <![CDATA[           An invalid presence type used as a null value. This value MUST NOT           appear in the Statuses property,           or in the result of GetStatuses           on the deprecated Presence           interface.         ]]>
 * @TP_CONNECTION_PRESENCE_TYPE_OFFLINE: <![CDATA[           Offline         ]]>
 * @TP_CONNECTION_PRESENCE_TYPE_AVAILABLE: <![CDATA[           Available         ]]>
 * @TP_CONNECTION_PRESENCE_TYPE_AWAY: <![CDATA[           Away         ]]>
 * @TP_CONNECTION_PRESENCE_TYPE_EXTENDED_AWAY: <![CDATA[           Away for an extended time         ]]>
 * @TP_CONNECTION_PRESENCE_TYPE_HIDDEN: <![CDATA[           Hidden (invisible)         ]]>
 * @TP_CONNECTION_PRESENCE_TYPE_BUSY: <![CDATA[           Busy, Do Not Disturb.         ]]>
 * @TP_CONNECTION_PRESENCE_TYPE_UNKNOWN: <![CDATA[           Unknown, unable to determine presence for this contact, for example           if the protocol only allows presence of subscribed contacts.         ]]>
 * @TP_CONNECTION_PRESENCE_TYPE_ERROR: <![CDATA[           Error, an error occurred while trying to determine presence.  The           message, if set, is an error from the server.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CONNECTION_PRESENCE_TYPE_UNSET = 0,
    TP_CONNECTION_PRESENCE_TYPE_OFFLINE = 1,
    TP_CONNECTION_PRESENCE_TYPE_AVAILABLE = 2,
    TP_CONNECTION_PRESENCE_TYPE_AWAY = 3,
    TP_CONNECTION_PRESENCE_TYPE_EXTENDED_AWAY = 4,
    TP_CONNECTION_PRESENCE_TYPE_HIDDEN = 5,
    TP_CONNECTION_PRESENCE_TYPE_BUSY = 6,
    TP_CONNECTION_PRESENCE_TYPE_UNKNOWN = 7,
    TP_CONNECTION_PRESENCE_TYPE_ERROR = 8,
} TpConnectionPresenceType;

/**
 * NUM_TP_CONNECTION_PRESENCE_TYPES:
 *
 * 1 higher than the highest valid value of #TpConnectionPresenceType.
 */
#define NUM_TP_CONNECTION_PRESENCE_TYPES (8+1)

/**
 *
TpRichPresenceAccessControlType:
 * @TP_RICH_PRESENCE_ACCESS_CONTROL_TYPE_WHITELIST: <![CDATA[           The associated variant is a list of contacts (signature 'au',           Contact_Handle[]) who can see the extended presence information.         ]]>
 * @TP_RICH_PRESENCE_ACCESS_CONTROL_TYPE_PUBLISH_LIST: <![CDATA[           All contacts in the user's 'publish' contact list can see the           extended presence information. The associated variant is ignored.         ]]>
 * @TP_RICH_PRESENCE_ACCESS_CONTROL_TYPE_GROUP: <![CDATA[           The associated variant is a handle of type Group (signature 'u',           Group_Handle) representing a group of contacts who can see the           extended presence information.         ]]>
 * @TP_RICH_PRESENCE_ACCESS_CONTROL_TYPE_OPEN: <![CDATA[           Anyone with access to the service can see the extended presence           information.         ]]>
 *
 * <![CDATA[         A type of access control for Rich_Presence_Access_Control.         For most types, the exact access control is given by an associated         variant.                     These are the access control types from XMPP publish/subscribe           (XEP-0060).                ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_RICH_PRESENCE_ACCESS_CONTROL_TYPE_WHITELIST = 0,
    TP_RICH_PRESENCE_ACCESS_CONTROL_TYPE_PUBLISH_LIST = 1,
    TP_RICH_PRESENCE_ACCESS_CONTROL_TYPE_GROUP = 2,
    TP_RICH_PRESENCE_ACCESS_CONTROL_TYPE_OPEN = 3,
} TpRichPresenceAccessControlType;

/**
 * NUM_TP_RICH_PRESENCE_ACCESS_CONTROL_TYPES:
 *
 * 1 higher than the highest valid value of #TpRichPresenceAccessControlType.
 */
#define NUM_TP_RICH_PRESENCE_ACCESS_CONTROL_TYPES (3+1)

/**
 *
TpFileTransferState:
 * @TP_FILE_TRANSFER_STATE_NONE: <![CDATA[           An invalid state type used as a null value. This value MUST NOT           appear in the State property.         ]]>
 * @TP_FILE_TRANSFER_STATE_PENDING: <![CDATA[           The file transfer is waiting to be accepted/closed by the receiver.           The receiver has to call AcceptFile,           then wait for the state to change to Open and check the offset value.         ]]>
 * @TP_FILE_TRANSFER_STATE_ACCEPTED: <![CDATA[           The receiver has accepted the transfer. The sender now has to           call ProvideFile to actually start the transfer.           The receiver should now wait for the state to change to Open           and check the offset value.         ]]>
 * @TP_FILE_TRANSFER_STATE_OPEN: <![CDATA[           The file transfer is open for traffic.         ]]>
 * @TP_FILE_TRANSFER_STATE_COMPLETED: <![CDATA[           The file transfer has been completed successfully.         ]]>
 * @TP_FILE_TRANSFER_STATE_CANCELLED: <![CDATA[           The file transfer has been cancelled.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_FILE_TRANSFER_STATE_NONE = 0,
    TP_FILE_TRANSFER_STATE_PENDING = 1,
    TP_FILE_TRANSFER_STATE_ACCEPTED = 2,
    TP_FILE_TRANSFER_STATE_OPEN = 3,
    TP_FILE_TRANSFER_STATE_COMPLETED = 4,
    TP_FILE_TRANSFER_STATE_CANCELLED = 5,
} TpFileTransferState;

/**
 * NUM_TP_FILE_TRANSFER_STATES:
 *
 * 1 higher than the highest valid value of #TpFileTransferState.
 */
#define NUM_TP_FILE_TRANSFER_STATES (5+1)

/**
 *
TpFileTransferStateChangeReason:
 * @TP_FILE_TRANSFER_STATE_CHANGE_REASON_NONE: <![CDATA[           No reason was specified.         ]]>
 * @TP_FILE_TRANSFER_STATE_CHANGE_REASON_REQUESTED: <![CDATA[           The change in state was requested.         ]]>
 * @TP_FILE_TRANSFER_STATE_CHANGE_REASON_LOCAL_STOPPED: <![CDATA[           The file transfer was cancelled by the local user.         ]]>
 * @TP_FILE_TRANSFER_STATE_CHANGE_REASON_REMOTE_STOPPED: <![CDATA[           The file transfer was cancelled by the remote user.         ]]>
 * @TP_FILE_TRANSFER_STATE_CHANGE_REASON_LOCAL_ERROR: <![CDATA[           The file transfer was cancelled because of a local error.         ]]>
 * @TP_FILE_TRANSFER_STATE_CHANGE_REASON_REMOTE_ERROR: <![CDATA[           The file transfer was cancelled because of a remote error.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_FILE_TRANSFER_STATE_CHANGE_REASON_NONE = 0,
    TP_FILE_TRANSFER_STATE_CHANGE_REASON_REQUESTED = 1,
    TP_FILE_TRANSFER_STATE_CHANGE_REASON_LOCAL_STOPPED = 2,
    TP_FILE_TRANSFER_STATE_CHANGE_REASON_REMOTE_STOPPED = 3,
    TP_FILE_TRANSFER_STATE_CHANGE_REASON_LOCAL_ERROR = 4,
    TP_FILE_TRANSFER_STATE_CHANGE_REASON_REMOTE_ERROR = 5,
} TpFileTransferStateChangeReason;

/**
 * NUM_TP_FILE_TRANSFER_STATE_CHANGE_REASONS:
 *
 * 1 higher than the highest valid value of #TpFileTransferStateChangeReason.
 */
#define NUM_TP_FILE_TRANSFER_STATE_CHANGE_REASONS (5+1)

/**
 *
TpFileHashType:
 * @TP_FILE_HASH_TYPE_NONE: <![CDATA[           No hash.         ]]>
 * @TP_FILE_HASH_TYPE_MD5: <![CDATA[           MD5 digest as a string of 32 ASCII hex digits.         ]]>
 * @TP_FILE_HASH_TYPE_SHA1: <![CDATA[           SHA1 digest as a string of ASCII hex digits.         ]]>
 * @TP_FILE_HASH_TYPE_SHA256: <![CDATA[           SHA256 digest as a string of ASCII hex digits.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_FILE_HASH_TYPE_NONE = 0,
    TP_FILE_HASH_TYPE_MD5 = 1,
    TP_FILE_HASH_TYPE_SHA1 = 2,
    TP_FILE_HASH_TYPE_SHA256 = 3,
} TpFileHashType;

/**
 * NUM_TP_FILE_HASH_TYPES:
 *
 * 1 higher than the highest valid value of #TpFileHashType.
 */
#define NUM_TP_FILE_HASH_TYPES (3+1)

/**
 *
TpMediaStreamType:
 * @TP_MEDIA_STREAM_TYPE_AUDIO: <![CDATA[An audio stream]]>
 * @TP_MEDIA_STREAM_TYPE_VIDEO: <![CDATA[A video stream]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_MEDIA_STREAM_TYPE_AUDIO = 0,
    TP_MEDIA_STREAM_TYPE_VIDEO = 1,
} TpMediaStreamType;

/**
 * NUM_TP_MEDIA_STREAM_TYPES:
 *
 * 1 higher than the highest valid value of #TpMediaStreamType.
 */
#define NUM_TP_MEDIA_STREAM_TYPES (1+1)

/**
 *
TpMediaStreamState:
 * @TP_MEDIA_STREAM_STATE_DISCONNECTED: <![CDATA[The stream is disconnected.]]>
 * @TP_MEDIA_STREAM_STATE_CONNECTING: <![CDATA[The stream is trying to connect.]]>
 * @TP_MEDIA_STREAM_STATE_CONNECTED: <![CDATA[The stream is connected.]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_MEDIA_STREAM_STATE_DISCONNECTED = 0,
    TP_MEDIA_STREAM_STATE_CONNECTING = 1,
    TP_MEDIA_STREAM_STATE_CONNECTED = 2,
} TpMediaStreamState;

/**
 * NUM_TP_MEDIA_STREAM_STATES:
 *
 * 1 higher than the highest valid value of #TpMediaStreamState.
 */
#define NUM_TP_MEDIA_STREAM_STATES (2+1)

/**
 *
TpMediaStreamDirection:
 * @TP_MEDIA_STREAM_DIRECTION_NONE: <![CDATA[Media are not being sent or received]]>
 * @TP_MEDIA_STREAM_DIRECTION_SEND: <![CDATA[Media are being sent, but not received]]>
 * @TP_MEDIA_STREAM_DIRECTION_RECEIVE: <![CDATA[Media are being received, but not sent]]>
 * @TP_MEDIA_STREAM_DIRECTION_BIDIRECTIONAL: <![CDATA[Media are being sent and received]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_MEDIA_STREAM_DIRECTION_NONE = 0,
    TP_MEDIA_STREAM_DIRECTION_SEND = 1,
    TP_MEDIA_STREAM_DIRECTION_RECEIVE = 2,
    TP_MEDIA_STREAM_DIRECTION_BIDIRECTIONAL = 3,
} TpMediaStreamDirection;

/**
 * NUM_TP_MEDIA_STREAM_DIRECTIONS:
 *
 * 1 higher than the highest valid value of #TpMediaStreamDirection.
 */
#define NUM_TP_MEDIA_STREAM_DIRECTIONS (3+1)

/**
 *
TpMediaStreamPendingSend:
 * @TP_MEDIA_STREAM_PENDING_LOCAL_SEND: <![CDATA[             The local user has been asked to send media by the remote user.             Call RequestStreamDirection to             indicate whether or not this is acceptable.         ]]>
 * @TP_MEDIA_STREAM_PENDING_REMOTE_SEND: <![CDATA[             The remote user has been asked to send media by the local user.             The StreamDirectionChanged signal             will be emitted when the remote user accepts or rejects this             change.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_MEDIA_STREAM_PENDING_LOCAL_SEND = 1,
    TP_MEDIA_STREAM_PENDING_REMOTE_SEND = 2,
} TpMediaStreamPendingSend;

/**
 *
TpChannelMediaCapabilities:
 * @TP_CHANNEL_MEDIA_CAPABILITY_AUDIO: <![CDATA[           The handle is capable of using audio streams within a media channel.         ]]>
 * @TP_CHANNEL_MEDIA_CAPABILITY_VIDEO: <![CDATA[           The handle is capable of using video streams within a media channel.         ]]>
 * @TP_CHANNEL_MEDIA_CAPABILITY_NAT_TRAVERSAL_STUN: <![CDATA[           The handle is capable of performing STUN to traverse NATs.         ]]>
 * @TP_CHANNEL_MEDIA_CAPABILITY_NAT_TRAVERSAL_GTALK_P2P: <![CDATA[           The handle is capable of establishing Google Talk peer-to-peer           connections (as implemented in libjingle 0.3) to traverse NATs.         ]]>
 * @TP_CHANNEL_MEDIA_CAPABILITY_NAT_TRAVERSAL_ICE_UDP: <![CDATA[           The handle is capable of establishing ICE UDP peer-to-peer           connections (as defined by the IETF MMUSIC working group) to traverse           NATs.         ]]>
 * @TP_CHANNEL_MEDIA_CAPABILITY_IMMUTABLE_STREAMS: <![CDATA[           Channels whose target handle is this contact will have           ImmutableStreams = True.         ]]>
 *
 * <![CDATA[         The channel-type-specific capability flags used for         Channel.Type.StreamedMedia in the Connection.Interface.Capabilities         interface. See the InitialAudio         property for details of the mechanisms that will replace this.       ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CHANNEL_MEDIA_CAPABILITY_AUDIO = 1,
    TP_CHANNEL_MEDIA_CAPABILITY_VIDEO = 2,
    TP_CHANNEL_MEDIA_CAPABILITY_NAT_TRAVERSAL_STUN = 4,
    TP_CHANNEL_MEDIA_CAPABILITY_NAT_TRAVERSAL_GTALK_P2P = 8,
    TP_CHANNEL_MEDIA_CAPABILITY_NAT_TRAVERSAL_ICE_UDP = 16,
    TP_CHANNEL_MEDIA_CAPABILITY_IMMUTABLE_STREAMS = 32,
} TpChannelMediaCapabilities;

/**
 *
TpChannelTextSendError:
 * @TP_CHANNEL_TEXT_SEND_ERROR_UNKNOWN: <![CDATA[         An unknown error occurred         ]]>
 * @TP_CHANNEL_TEXT_SEND_ERROR_OFFLINE: <![CDATA[         The requested contact was offline         ]]>
 * @TP_CHANNEL_TEXT_SEND_ERROR_INVALID_CONTACT: <![CDATA[         The requested contact is not valid         ]]>
 * @TP_CHANNEL_TEXT_SEND_ERROR_PERMISSION_DENIED: <![CDATA[         The user does not have permission to speak on this channel         ]]>
 * @TP_CHANNEL_TEXT_SEND_ERROR_TOO_LONG: <![CDATA[         The outgoing message was too long and was rejected by the server         ]]>
 * @TP_CHANNEL_TEXT_SEND_ERROR_NOT_IMPLEMENTED: <![CDATA[         The channel doesn't support sending text messages to the requested         contact         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CHANNEL_TEXT_SEND_ERROR_UNKNOWN = 0,
    TP_CHANNEL_TEXT_SEND_ERROR_OFFLINE = 1,
    TP_CHANNEL_TEXT_SEND_ERROR_INVALID_CONTACT = 2,
    TP_CHANNEL_TEXT_SEND_ERROR_PERMISSION_DENIED = 3,
    TP_CHANNEL_TEXT_SEND_ERROR_TOO_LONG = 4,
    TP_CHANNEL_TEXT_SEND_ERROR_NOT_IMPLEMENTED = 5,
} TpChannelTextSendError;

/**
 * NUM_TP_CHANNEL_TEXT_SEND_ERRORS:
 *
 * 1 higher than the highest valid value of #TpChannelTextSendError.
 */
#define NUM_TP_CHANNEL_TEXT_SEND_ERRORS (5+1)

/**
 *
TpChannelTextMessageType:
 * @TP_CHANNEL_TEXT_MESSAGE_TYPE_NORMAL: <![CDATA[         An ordinary chat message. Unknown types SHOULD be treated like this.         ]]>
 * @TP_CHANNEL_TEXT_MESSAGE_TYPE_ACTION: <![CDATA[         An action which might be presented to the user as         "* <sender> <action>", such as an IRC CTCP         ACTION (typically selected by the "/me" command). For example, the         text of the message might be "drinks more coffee".         ]]>
 * @TP_CHANNEL_TEXT_MESSAGE_TYPE_NOTICE: <![CDATA[         A one-off or automated message not necessarily expecting a reply         ]]>
 * @TP_CHANNEL_TEXT_MESSAGE_TYPE_AUTO_REPLY: <![CDATA[         An automatically-generated reply message.         ]]>
 * @TP_CHANNEL_TEXT_MESSAGE_TYPE_DELIVERY_REPORT: <![CDATA[           This message type MUST NOT appear unless the channel supports the           DeliveryReporting interface. The message MUST be as defined by           the DeliveryReporting interface.         ]]>
 *
 * <![CDATA[         The type of message.       ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CHANNEL_TEXT_MESSAGE_TYPE_NORMAL = 0,
    TP_CHANNEL_TEXT_MESSAGE_TYPE_ACTION = 1,
    TP_CHANNEL_TEXT_MESSAGE_TYPE_NOTICE = 2,
    TP_CHANNEL_TEXT_MESSAGE_TYPE_AUTO_REPLY = 3,
    TP_CHANNEL_TEXT_MESSAGE_TYPE_DELIVERY_REPORT = 4,
} TpChannelTextMessageType;

/**
 * NUM_TP_CHANNEL_TEXT_MESSAGE_TYPES:
 *
 * 1 higher than the highest valid value of #TpChannelTextMessageType.
 */
#define NUM_TP_CHANNEL_TEXT_MESSAGE_TYPES (4+1)

/**
 *
TpChannelTextMessageFlags:
 * @TP_CHANNEL_TEXT_MESSAGE_FLAG_TRUNCATED: <![CDATA[         The incoming message was truncated to a shorter length by the         server or the connection manager.         ]]>
 * @TP_CHANNEL_TEXT_MESSAGE_FLAG_NON_TEXT_CONTENT: <![CDATA[           The incoming message contained non-text content which cannot be             represented by this interface, but has been signalled             in the Messages             interface.            Connection managers SHOULD only set this flag if the non-text             content appears to be relatively significant (exactly how             significant is up to the implementor). The intention is that             if this flag is set, clients using this interface SHOULD inform             the user that part of the message was not understood.         ]]>
 * @TP_CHANNEL_TEXT_MESSAGE_FLAG_SCROLLBACK: <![CDATA[           The incoming message was part of a replay of message history.                         In XMPP multi-user chat, a few past messages are replayed               when you join a chatroom. A sufficiently capable IRC connection               manager could also set this flag on historical messages when               connected to a proxy like bip or irssi-proxy. The existence               of this flag allows loggers and UIs to use better heuristics               when eliminating duplicates (a simple implementation made               possible by this flag would be to avoid logging scrollback               at all).                    ]]>
 * @TP_CHANNEL_TEXT_MESSAGE_FLAG_RESCUED: <![CDATA[           The incoming message has been seen in a previous channel during             the lifetime of the Connection, but             had not been acknowledged             when that channel closed, causing an identical channel (the             channel in which the message now appears) to open.                         This means that a logger (which should already have seen the               message in the previous channel) is able to recognise and ignore               these replayed messages.                    ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CHANNEL_TEXT_MESSAGE_FLAG_TRUNCATED = 1,
    TP_CHANNEL_TEXT_MESSAGE_FLAG_NON_TEXT_CONTENT = 2,
    TP_CHANNEL_TEXT_MESSAGE_FLAG_SCROLLBACK = 4,
    TP_CHANNEL_TEXT_MESSAGE_FLAG_RESCUED = 8,
} TpChannelTextMessageFlags;

/**
 *
TpTubeType:
 * @TP_TUBE_TYPE_DBUS: <![CDATA[           The tube is D-Bus tube as described by the             org.freedesktop.Telepathy.Channel.Type.DBusTube interface.         ]]>
 * @TP_TUBE_TYPE_STREAM: <![CDATA[           The tube is stream tube as described by the             org.freedesktop.Telepathy.Channel.Type.StreamTube interface.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_TUBE_TYPE_DBUS = 0,
    TP_TUBE_TYPE_STREAM = 1,
} TpTubeType;

/**
 * NUM_TP_TUBE_TYPES:
 *
 * 1 higher than the highest valid value of #TpTubeType.
 */
#define NUM_TP_TUBE_TYPES (1+1)

/**
 *
TpTubeState:
 * @TP_TUBE_STATE_LOCAL_PENDING: <![CDATA[           The tube is waiting to be accepted/closed locally.         ]]>
 * @TP_TUBE_STATE_REMOTE_PENDING: <![CDATA[           The tube is waiting to be accepted/closed remotely.         ]]>
 * @TP_TUBE_STATE_OPEN: <![CDATA[           The tube is open for traffic.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_TUBE_STATE_LOCAL_PENDING = 0,
    TP_TUBE_STATE_REMOTE_PENDING = 1,
    TP_TUBE_STATE_OPEN = 2,
} TpTubeState;

/**
 * NUM_TP_TUBE_STATES:
 *
 * 1 higher than the highest valid value of #TpTubeState.
 */
#define NUM_TP_TUBE_STATES (2+1)

/**
 *
TpChannelCallStateFlags:
 * @TP_CHANNEL_CALL_STATE_RINGING: <![CDATA[           The contact has been alerted about the call but has not responded           (e.g. 180 Ringing in SIP).         ]]>
 * @TP_CHANNEL_CALL_STATE_QUEUED: <![CDATA[           The contact is temporarily unavailable, and the call has been placed           in a queue (e.g. 182 Queued in SIP, or call-waiting in telephony).         ]]>
 * @TP_CHANNEL_CALL_STATE_HELD: <![CDATA[           The contact has placed the call on hold, and will not receive           media from the local user or any other participants until they           unhold the call again.         ]]>
 * @TP_CHANNEL_CALL_STATE_FORWARDED: <![CDATA[           The initiator of the call originally called a contact other than the           current recipient of the call, but the call was then forwarded or           diverted.         ]]>
 * @TP_CHANNEL_CALL_STATE_IN_PROGRESS: <![CDATA[           Progress has been made in placing the outgoing call, but the           destination contact may not have been made aware of the call yet           (so the Ringing state is not appropriate). This corresponds to SIP's           status code 183 Session Progress, and could be used when the           outgoing call has reached a gateway, for instance.         ]]>
 *
 * <![CDATA[         A set of flags representing call states.       ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CHANNEL_CALL_STATE_RINGING = 1,
    TP_CHANNEL_CALL_STATE_QUEUED = 2,
    TP_CHANNEL_CALL_STATE_HELD = 4,
    TP_CHANNEL_CALL_STATE_FORWARDED = 8,
    TP_CHANNEL_CALL_STATE_IN_PROGRESS = 16,
} TpChannelCallStateFlags;

/**
 *
TpChannelChatState:
 * @TP_CHANNEL_CHAT_STATE_GONE: <![CDATA[         The contact has effectively ceased participating in the chat.         ]]>
 * @TP_CHANNEL_CHAT_STATE_INACTIVE: <![CDATA[         The contact has not been active for some time.         ]]>
 * @TP_CHANNEL_CHAT_STATE_ACTIVE: <![CDATA[         The contact is actively participating in the chat.         ]]>
 * @TP_CHANNEL_CHAT_STATE_PAUSED: <![CDATA[         The contact has paused composing a message.         ]]>
 * @TP_CHANNEL_CHAT_STATE_COMPOSING: <![CDATA[         The contact is composing a message to be sent to the chat.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CHANNEL_CHAT_STATE_GONE = 0,
    TP_CHANNEL_CHAT_STATE_INACTIVE = 1,
    TP_CHANNEL_CHAT_STATE_ACTIVE = 2,
    TP_CHANNEL_CHAT_STATE_PAUSED = 3,
    TP_CHANNEL_CHAT_STATE_COMPOSING = 4,
} TpChannelChatState;

/**
 * NUM_TP_CHANNEL_CHAT_STATES:
 *
 * 1 higher than the highest valid value of #TpChannelChatState.
 */
#define NUM_TP_CHANNEL_CHAT_STATES (4+1)

/**
 *
TpDTMFEvent:
 * @TP_DTMF_EVENT_DIGIT_0: <![CDATA[0]]>
 * @TP_DTMF_EVENT_DIGIT_1: <![CDATA[1]]>
 * @TP_DTMF_EVENT_DIGIT_2: <![CDATA[2]]>
 * @TP_DTMF_EVENT_DIGIT_3: <![CDATA[3]]>
 * @TP_DTMF_EVENT_DIGIT_4: <![CDATA[4]]>
 * @TP_DTMF_EVENT_DIGIT_5: <![CDATA[5]]>
 * @TP_DTMF_EVENT_DIGIT_6: <![CDATA[6]]>
 * @TP_DTMF_EVENT_DIGIT_7: <![CDATA[7]]>
 * @TP_DTMF_EVENT_DIGIT_8: <![CDATA[8]]>
 * @TP_DTMF_EVENT_DIGIT_9: <![CDATA[9]]>
 * @TP_DTMF_EVENT_ASTERISK: <![CDATA[*]]>
 * @TP_DTMF_EVENT_HASH: <![CDATA[#]]>
 * @TP_DTMF_EVENT_LETTER_A: <![CDATA[A]]>
 * @TP_DTMF_EVENT_LETTER_B: <![CDATA[B]]>
 * @TP_DTMF_EVENT_LETTER_C: <![CDATA[C]]>
 * @TP_DTMF_EVENT_LETTER_D: <![CDATA[D]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_DTMF_EVENT_DIGIT_0 = 0,
    TP_DTMF_EVENT_DIGIT_1 = 1,
    TP_DTMF_EVENT_DIGIT_2 = 2,
    TP_DTMF_EVENT_DIGIT_3 = 3,
    TP_DTMF_EVENT_DIGIT_4 = 4,
    TP_DTMF_EVENT_DIGIT_5 = 5,
    TP_DTMF_EVENT_DIGIT_6 = 6,
    TP_DTMF_EVENT_DIGIT_7 = 7,
    TP_DTMF_EVENT_DIGIT_8 = 8,
    TP_DTMF_EVENT_DIGIT_9 = 9,
    TP_DTMF_EVENT_ASTERISK = 10,
    TP_DTMF_EVENT_HASH = 11,
    TP_DTMF_EVENT_LETTER_A = 12,
    TP_DTMF_EVENT_LETTER_B = 13,
    TP_DTMF_EVENT_LETTER_C = 14,
    TP_DTMF_EVENT_LETTER_D = 15,
} TpDTMFEvent;

/**
 * NUM_TP_DTMF_EVENTS:
 *
 * 1 higher than the highest valid value of #TpDTMFEvent.
 */
#define NUM_TP_DTMF_EVENTS (15+1)

/**
 *
TpChannelGroupFlags:
 * @TP_CHANNEL_GROUP_FLAG_CAN_ADD: <![CDATA[             The AddMembers method can be used to             add or invite members who are             not already in the local pending list (which is always valid).         ]]>
 * @TP_CHANNEL_GROUP_FLAG_CAN_REMOVE: <![CDATA[             The RemoveMembers method can be used             to remove channel members             (removing those on the pending local list is always valid).         ]]>
 * @TP_CHANNEL_GROUP_FLAG_CAN_RESCIND: <![CDATA[             The RemoveMembers method can be used             on people on the remote             pending list.         ]]>
 * @TP_CHANNEL_GROUP_FLAG_MESSAGE_ADD: <![CDATA[             A message may be sent to the server when calling             AddMembers on             contacts who are not currently pending members.         ]]>
 * @TP_CHANNEL_GROUP_FLAG_MESSAGE_REMOVE: <![CDATA[             A message may be sent to the server when calling             RemoveMembers on             contacts who are currently channel members.         ]]>
 * @TP_CHANNEL_GROUP_FLAG_MESSAGE_ACCEPT: <![CDATA[             A message may be sent to the server when calling             AddMembers on             contacts who are locally pending.         ]]>
 * @TP_CHANNEL_GROUP_FLAG_MESSAGE_REJECT: <![CDATA[             A message may be sent to the server when calling             RemoveMembers on             contacts who are locally pending.         ]]>
 * @TP_CHANNEL_GROUP_FLAG_MESSAGE_RESCIND: <![CDATA[             A message may be sent to the server when calling             RemoveMembers on             contacts who are remote pending.         ]]>
 * @TP_CHANNEL_GROUP_FLAG_CHANNEL_SPECIFIC_HANDLES: <![CDATA[                        The members of this group have handles which are specific to             this channel, and are not valid as general-purpose handles on             the connection. Depending on the channel, it may be possible to             check the HandleOwners property or             call GetHandleOwners to find the             owners of these handles, which should be done if you wish to (e.g.)             subscribe to the contact's presence.                                    Connection managers must ensure that any given handle is not             simultaneously a general-purpose handle and a channel-specific             handle.                    ]]>
 * @TP_CHANNEL_GROUP_FLAG_ONLY_ONE_GROUP: <![CDATA[             Placing a contact in multiple groups of this type is not allowed             and will raise NotAvailable (on services where contacts may only             be in one user-defined group, user-defined groups will have             this flag).         ]]>
 * @TP_CHANNEL_GROUP_FLAG_HANDLE_OWNERS_NOT_AVAILABLE: <![CDATA[           In rooms with channel specific handles (ie Channel_Specific_Handles           flag is set), this flag indicates that no handle owners are           available, apart from the owner of the           SelfHandle.                         This used to be an important optimization to avoid repeated             GetHandleOwners calls, before we introduced the             HandleOwners property and             HandleOwnersChanged signal.                    ]]>
 * @TP_CHANNEL_GROUP_FLAG_PROPERTIES: <![CDATA[           This flag indicates that all the properties introduced in           specification 0.17.6 are fully supported.         ]]>
 * @TP_CHANNEL_GROUP_FLAG_MEMBERS_CHANGED_DETAILED: <![CDATA[           Indicates that MembersChangedDetailed           will be emitted for changes to this group's members in addition to           MembersChanged.           Clients can then connect to the former and ignore emission of the           latter. This flag's state MUST NOT change over the lifetime of a           channel.                         If it were allowed to change, client bindings would have to always             connect to MembersChanged just in case the flag ever went away (and             generally be unnecessarily complicated), which would mostly negate             the point of having this flag in the first place.                    ]]>
 * @TP_CHANNEL_GROUP_FLAG_MESSAGE_DEPART: <![CDATA[           A message may be sent to the server when calling           RemoveMembers on           the SelfHandle.                         This would be set for XMPP Multi-User Chat or IRC channels,             but not for a typical implementation of streamed media calls.                    ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CHANNEL_GROUP_FLAG_CAN_ADD = 1,
    TP_CHANNEL_GROUP_FLAG_CAN_REMOVE = 2,
    TP_CHANNEL_GROUP_FLAG_CAN_RESCIND = 4,
    TP_CHANNEL_GROUP_FLAG_MESSAGE_ADD = 8,
    TP_CHANNEL_GROUP_FLAG_MESSAGE_REMOVE = 16,
    TP_CHANNEL_GROUP_FLAG_MESSAGE_ACCEPT = 32,
    TP_CHANNEL_GROUP_FLAG_MESSAGE_REJECT = 64,
    TP_CHANNEL_GROUP_FLAG_MESSAGE_RESCIND = 128,
    TP_CHANNEL_GROUP_FLAG_CHANNEL_SPECIFIC_HANDLES = 256,
    TP_CHANNEL_GROUP_FLAG_ONLY_ONE_GROUP = 512,
    TP_CHANNEL_GROUP_FLAG_HANDLE_OWNERS_NOT_AVAILABLE = 1024,
    TP_CHANNEL_GROUP_FLAG_PROPERTIES = 2048,
    TP_CHANNEL_GROUP_FLAG_MEMBERS_CHANGED_DETAILED = 4096,
    TP_CHANNEL_GROUP_FLAG_MESSAGE_DEPART = 8192,
} TpChannelGroupFlags;

/**
 *
TpChannelGroupChangeReason:
 * @TP_CHANNEL_GROUP_CHANGE_REASON_NONE: <![CDATA[           No reason was provided for this change.            In particular, this reason SHOULD be used when representing             users joining a named chatroom in the usual way, users leaving             a chatroom by their own request, and normal termination of a             StreamedMedia call by the remote user.            If the SelfHandle is removed from             a group for this reason and the actor is not the SelfHandle, the             equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Terminated.            If the SelfHandle is removed from a group for this reason and             the actor is also the SelfHandle, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Cancelled.         ]]>
 * @TP_CHANNEL_GROUP_CHANGE_REASON_OFFLINE: <![CDATA[           The change is due to a user going offline. Also used when             user is already offline, but this wasn't known previously.            If a one-to-one StreamedMedia             call fails because the contact being called is offline, the             connection manager SHOULD indicate this by removing both the             SelfHandle and the other contact's             handle from the Group interface with reason Offline.                         For 1-1 calls, the call terminates as a result of removing the             remote contact, so the SelfHandle should be removed at the same             time as the remote contact and for the same reason.                       If a handle is removed from a group for this reason, the             equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Offline.         ]]>
 * @TP_CHANNEL_GROUP_CHANGE_REASON_KICKED: <![CDATA[           The change is due to a kick operation.            If the SelfHandle is removed             from a group for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Channel.Kicked.                    ]]>
 * @TP_CHANNEL_GROUP_CHANGE_REASON_BUSY: <![CDATA[           The change is due to a busy indication.            If a one-to-one StreamedMedia             call fails because the contact being called is busy, the             connection manager SHOULD indicate this by removing both the             SelfHandle and the other contact's             handle from the Group interface with reason Busy.                         For 1-1 calls, the call terminates as a result of removing the             remote contact, so the SelfHandle should be removed at the same             time as the remote contact and for the same reason.                       If the SelfHandle is removed             from a group for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Busy.                    ]]>
 * @TP_CHANNEL_GROUP_CHANGE_REASON_INVITED: <![CDATA[           The change is due to an invitation. This reason SHOULD only be used           when contacts are added to the remote-pending set (to indicate that           the contact has been invited) or to the members (to indicate that           the contact has accepted the invitation).                         Otherwise, what would it mean?                    ]]>
 * @TP_CHANNEL_GROUP_CHANGE_REASON_BANNED: <![CDATA[           The change is due to a kick+ban operation.            If the SelfHandle is removed             from a group for this reason, the equivalent D-Bus error is             org.freedesktop.Telepathy.Error.Channel.Banned.                    ]]>
 * @TP_CHANNEL_GROUP_CHANGE_REASON_ERROR: <![CDATA[             The change is due to an error occurring.         ]]>
 * @TP_CHANNEL_GROUP_CHANGE_REASON_INVALID_CONTACT: <![CDATA[           The change is because the requested contact does not exist.            For instance, if the user invites a nonexistent contact to a             chatroom or attempts to call a nonexistent contact, this could             be indicated by the CM adding that contact's handle to             remote-pending for reason None or Invited, then removing it for             reason Invalid_Contact. In the case of a 1-1 StreamedMedia             call, the CM SHOULD remove the self handle from the Group             in the same signal.                         For 1-1 calls, the call terminates as a result of removing the             remote contact, so the SelfHandle should be removed at the same             time as the remote contact and for the same reason.                       If a contact is removed from a group for this reason, the             equivalent D-Bus error is             org.freedesktop.Telepathy.Error.DoesNotExist.                    ]]>
 * @TP_CHANNEL_GROUP_CHANGE_REASON_NO_ANSWER: <![CDATA[           The change is because the requested contact did not respond.            If a one-to-one StreamedMedia             call fails because the contact being called did not respond, the             connection manager SHOULD indicate this by removing both the             SelfHandle and the other contact's             handle from the Group interface with reason No_Answer.                         Documenting existing practice.                       If a contact is removed from a group for this reason, the             equivalent D-Bus error is             org.freedesktop.Telepathy.Error.NoAnswer.                    ]]>
 * @TP_CHANNEL_GROUP_CHANGE_REASON_RENAMED: <![CDATA[           The change is because a contact's unique identifier changed.           There must be exactly one handle in the removed set and exactly           one handle in one of the added sets. The Renamed           signal on the           Renaming           interface will have been emitted for the same handles,           shortly before this MembersChanged signal is emitted.         ]]>
 * @TP_CHANNEL_GROUP_CHANGE_REASON_PERMISSION_DENIED: <![CDATA[           The change is because there was no permission to contact the             requested handle.            If a contact is removed from a group for this reason, the             equivalent D-Bus error is             org.freedesktop.Telepathy.Error.PermissionDenied.                    ]]>
 * @TP_CHANNEL_GROUP_CHANGE_REASON_SEPARATED: <![CDATA[           If members are removed with this reason code, the change is             because the group has split into unconnected parts which can only             communicate within themselves (e.g. netsplits on IRC use this             reason code).                                   If members are added with this reason code, the change is because             unconnected parts of the group have rejoined. If this channel             carries messages (e.g. Text             or Tubes             channels) applications must             assume that the contacts being added are likely to have missed some             messages as a result of the separation, and that the contacts             in the group are likely to have missed some messages from the             contacts being added.                      Note that from the added contacts' perspective, they have been             in the group all along, and the contacts we indicate to be in             the group (including the local user) have just rejoined             the group with reason Separated. Application protocols in Tubes             should be prepared to cope with this situation.                       The SelfHandle SHOULD NOT be             removed from channels with this reason.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CHANNEL_GROUP_CHANGE_REASON_NONE = 0,
    TP_CHANNEL_GROUP_CHANGE_REASON_OFFLINE = 1,
    TP_CHANNEL_GROUP_CHANGE_REASON_KICKED = 2,
    TP_CHANNEL_GROUP_CHANGE_REASON_BUSY = 3,
    TP_CHANNEL_GROUP_CHANGE_REASON_INVITED = 4,
    TP_CHANNEL_GROUP_CHANGE_REASON_BANNED = 5,
    TP_CHANNEL_GROUP_CHANGE_REASON_ERROR = 6,
    TP_CHANNEL_GROUP_CHANGE_REASON_INVALID_CONTACT = 7,
    TP_CHANNEL_GROUP_CHANGE_REASON_NO_ANSWER = 8,
    TP_CHANNEL_GROUP_CHANGE_REASON_RENAMED = 9,
    TP_CHANNEL_GROUP_CHANGE_REASON_PERMISSION_DENIED = 10,
    TP_CHANNEL_GROUP_CHANGE_REASON_SEPARATED = 11,
} TpChannelGroupChangeReason;

/**
 * NUM_TP_CHANNEL_GROUP_CHANGE_REASONS:
 *
 * 1 higher than the highest valid value of #TpChannelGroupChangeReason.
 */
#define NUM_TP_CHANNEL_GROUP_CHANGE_REASONS (11+1)

/**
 *
TpLocalHoldState:
 * @TP_LOCAL_HOLD_STATE_UNHELD: <![CDATA[           All streams are unheld (the call is active). New channels SHOULD           have this hold state.         ]]>
 * @TP_LOCAL_HOLD_STATE_HELD: <![CDATA[           All streams are held (the call is on hold)         ]]>
 * @TP_LOCAL_HOLD_STATE_PENDING_HOLD: <![CDATA[           The connection manager is attempting to move to state Held, but           has not yet completed that operation. It is unspecified whether           any, all or none of the streams making up the channel are on hold.         ]]>
 * @TP_LOCAL_HOLD_STATE_PENDING_UNHOLD: <![CDATA[           The connection manager is attempting to move to state Held, but           has not yet completed that operation. It is unspecified whether           any, all or none of the streams making up the channel are on hold.         ]]>
 *
 * <![CDATA[         The hold state of a channel.       ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_LOCAL_HOLD_STATE_UNHELD = 0,
    TP_LOCAL_HOLD_STATE_HELD = 1,
    TP_LOCAL_HOLD_STATE_PENDING_HOLD = 2,
    TP_LOCAL_HOLD_STATE_PENDING_UNHOLD = 3,
} TpLocalHoldState;

/**
 * NUM_TP_LOCAL_HOLD_STATES:
 *
 * 1 higher than the highest valid value of #TpLocalHoldState.
 */
#define NUM_TP_LOCAL_HOLD_STATES (3+1)

/**
 *
TpLocalHoldStateReason:
 * @TP_LOCAL_HOLD_STATE_REASON_NONE: <![CDATA[           The reason cannot be described by any of the predefined values           (connection managers SHOULD avoid this reason, but clients MUST           handle it gracefully)         ]]>
 * @TP_LOCAL_HOLD_STATE_REASON_REQUESTED: <![CDATA[           The change is in response to a user request         ]]>
 * @TP_LOCAL_HOLD_STATE_REASON_RESOURCE_NOT_AVAILABLE: <![CDATA[           The change is because some resource was not available         ]]>
 *
 * <![CDATA[         The reason for a change to the Local_Hold_State. Clients MUST         treat unknown values as equivalent to Local_Hold_State_Reason_None.       ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_LOCAL_HOLD_STATE_REASON_NONE = 0,
    TP_LOCAL_HOLD_STATE_REASON_REQUESTED = 1,
    TP_LOCAL_HOLD_STATE_REASON_RESOURCE_NOT_AVAILABLE = 2,
} TpLocalHoldStateReason;

/**
 * NUM_TP_LOCAL_HOLD_STATE_REASONS:
 *
 * 1 higher than the highest valid value of #TpLocalHoldStateReason.
 */
#define NUM_TP_LOCAL_HOLD_STATE_REASONS (2+1)

/**
 *
TpMessagePartSupportFlags:
 * @TP_MESSAGE_PART_SUPPORT_FLAG_ONE_ATTACHMENT: <![CDATA[           SendMessage will accept messages           containing a textual message body,           plus a single attachment of any type listed in the           SupportedContentTypes property. It does not make sense for this           flag to be set if Message_Part_Support_Flag_Data_Only is not also set           (because the connection manager can trivially provide an empty text           part if necessary).         ]]>
 * @TP_MESSAGE_PART_SUPPORT_FLAG_MULTIPLE_ATTACHMENTS: <![CDATA[           SendMessage will accept messages containing a textual message body,           plus an arbitrary number of attachments of any type listed in the           SupportedContentTypes property. It does not make sense for this           flag to be set if Message_Part_Support_Flag_One_Attachment is not           also set.         ]]>
 *
 * <![CDATA[         Flags indicating the level of support for message parts on this           channel. They are designed such that setting more flags always           implies that the channel has more capabilities.          If no flags are set, this indicates that messages may contain           a single message part whose content-type is any of the types           from SupportedContentTypes, possibly with some alternatives.          There is no flag indicating support for alternatives. This is           because the SendMessage implementation can always accept messages           containing alternatives, even if the underlying protocol does not,           by deleting all alternatives except the first (most preferred)           that is supported.                     Each of the flags so far implies the previous flag, so we could           have used a simple enumeration here; however, we've defined           the message-part support indicator as a flag set for future           expansion.                   See SupportedContentTypes for some           examples.       ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_MESSAGE_PART_SUPPORT_FLAG_ONE_ATTACHMENT = 1,
    TP_MESSAGE_PART_SUPPORT_FLAG_MULTIPLE_ATTACHMENTS = 2,
} TpMessagePartSupportFlags;

/**
 *
TpMessageSendingFlags:
 * @TP_MESSAGE_SENDING_FLAG_REPORT_DELIVERY: <![CDATA[           Provide a successful delivery report if possible, even if this is             not the default for this protocol. Ignored if delivery reports are             not possible on this protocol.                         In some protocols, like XMPP, it is not conventional to request               or send positive delivery notifications.                       Delivery failure reports SHOULD always be sent, but if this flag             is present, the connection manager MAY also try harder to obtain             failed delivery reports or allow them to be matched to outgoing             messages.         ]]>
 *
 * <![CDATA[         Flags altering the way a message is sent. The "most usual" action         should always be to have these flags unset.       ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_MESSAGE_SENDING_FLAG_REPORT_DELIVERY = 1,
} TpMessageSendingFlags;

/**
 *
TpDeliveryStatus:
 * @TP_DELIVERY_STATUS_UNKNOWN: <![CDATA[           The message's disposition is unknown.           Clients SHOULD consider all messages to have status           Delivery_Status_Unknown unless otherwise specified; connection           managers SHOULD NOT signal this delivery status explicitly.         ]]>
 * @TP_DELIVERY_STATUS_DELIVERED: <![CDATA[           The message has been delivered to the intended recipient.         ]]>
 * @TP_DELIVERY_STATUS_TEMPORARILY_FAILED: <![CDATA[           Delivery of the message has failed. Clients SHOULD notify the user,           but MAY automatically try sending another copy of the message.                         Similar to errors with type="wait" in XMPP; analogous to             4xx errors in SMTP.                    ]]>
 * @TP_DELIVERY_STATUS_PERMANENTLY_FAILED: <![CDATA[           Delivery of the message has failed. Clients SHOULD NOT try again           unless by specific user action. If the user does not modify the           message or alter configuration before re-sending, this error is           likely to happen again.                         Similar to errors with type="cancel", type="modify"             or type="auth" in XMPP; analogous to 5xx errors in SMTP.                    ]]>
 * @TP_DELIVERY_STATUS_ACCEPTED: <![CDATA[           An intermediate server has accepted the message but the message           has not been yet delivered to the ultimate recipient. The           connection manager might send a Failed report or Delivered report           later.                         Similar to "202 Accepted" success code in SIP; analogous to             251 and 252 responses in SMTP.                    ]]>
 *
 * <![CDATA[         The status of a message as indicated by a delivery report.          If this enum is extended in future specifications, this should           only be to add new, non-overlapping conditions (i.e. all failures           should still be signalled as either Temporarily_Failed           or Permanently_Failed). If additional detail is required (e.g.           distinguishing between the various types of permanent failure) this           will be done using additional keys in the Message_Part.       ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_DELIVERY_STATUS_UNKNOWN = 0,
    TP_DELIVERY_STATUS_DELIVERED = 1,
    TP_DELIVERY_STATUS_TEMPORARILY_FAILED = 2,
    TP_DELIVERY_STATUS_PERMANENTLY_FAILED = 3,
    TP_DELIVERY_STATUS_ACCEPTED = 4,
} TpDeliveryStatus;

/**
 * NUM_TP_DELIVERY_STATUSES:
 *
 * 1 higher than the highest valid value of #TpDeliveryStatus.
 */
#define NUM_TP_DELIVERY_STATUSES (4+1)

/**
 *
TpDeliveryReportingSupportFlags:
 * @TP_DELIVERY_REPORTING_SUPPORT_FLAG_RECEIVE_FAILURES: <![CDATA[           Clients MAY expect to receive negative delivery reports if           Message_Sending_Flag_Report_Delivery is specified when sending.                         If senders want delivery reports, they should ask for them.             If they don't want delivery reports, they can just ignore them,             so there's no need to have capability discovery for what will             happen if a delivery report isn't requested.                    ]]>
 * @TP_DELIVERY_REPORTING_SUPPORT_FLAG_RECEIVE_SUCCESSES: <![CDATA[           Clients MAY expect to receive positive delivery reports if           Message_Sending_Flag_Report_Delivery is specified when sending.                         Same rationale as Receive_Failures.                    ]]>
 *
 * <![CDATA[         Flags indicating the level of support for delivery reporting on this         channel. Any future flags added to this set will conform to the         convention that the presence of an extra flag implies that         more operations will succeed.       ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_DELIVERY_REPORTING_SUPPORT_FLAG_RECEIVE_FAILURES = 1,
    TP_DELIVERY_REPORTING_SUPPORT_FLAG_RECEIVE_SUCCESSES = 2,
} TpDeliveryReportingSupportFlags;

/**
 *
TpChannelPasswordFlags:
 * @TP_CHANNEL_PASSWORD_FLAG_PROVIDE: <![CDATA[           The ProvidePassword method must be           called now for the user to join the channel         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_CHANNEL_PASSWORD_FLAG_PROVIDE = 8,
} TpChannelPasswordFlags;

/**
 *
TpTubeChannelState:
 * @TP_TUBE_CHANNEL_STATE_LOCAL_PENDING: <![CDATA[           The initiator offered the tube. The tube is waiting to be           accepted/closed locally. If the client accepts the tube, the tube's           state will be Open.         ]]>
 * @TP_TUBE_CHANNEL_STATE_REMOTE_PENDING: <![CDATA[           The tube is waiting to be accepted/closed remotely. If the           recipient accepts the tube, the tube's state will be Open.         ]]>
 * @TP_TUBE_CHANNEL_STATE_OPEN: <![CDATA[           The initiator offered the tube and the recipient accepted it. The           tube is open for traffic. The tube's state stays in this state until           it is closed.         ]]>
 * @TP_TUBE_CHANNEL_STATE_NOT_OFFERED: <![CDATA[           The tube channel has been requested but the tube is not yet offered.           The client should offer the tube to the recipient and the tube's           state will be Remote_Pending. The method used to offer the tube           depends on the tube type.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_TUBE_CHANNEL_STATE_LOCAL_PENDING = 0,
    TP_TUBE_CHANNEL_STATE_REMOTE_PENDING = 1,
    TP_TUBE_CHANNEL_STATE_OPEN = 2,
    TP_TUBE_CHANNEL_STATE_NOT_OFFERED = 3,
} TpTubeChannelState;

/**
 * NUM_TP_TUBE_CHANNEL_STATES:
 *
 * 1 higher than the highest valid value of #TpTubeChannelState.
 */
#define NUM_TP_TUBE_CHANNEL_STATES (3+1)

/**
 *
TpSocketAddressType:
 * @TP_SOCKET_ADDRESS_TYPE_UNIX: <![CDATA[           A Unix socket. The address variant contains a byte-array, signature 'ay',           containing the path of the socket.         ]]>
 * @TP_SOCKET_ADDRESS_TYPE_ABSTRACT_UNIX: <![CDATA[           An abstract Unix socket. The address variant contains a byte-array,           signature 'ay', containing the path of the socket including the           leading null byte.         ]]>
 * @TP_SOCKET_ADDRESS_TYPE_IPV4: <![CDATA[           An IPv4 socket. The address variant contains a Socket_Address_IPv4,           i.e. a structure with signature (sq)           in which the string is an IPv4 dotted-quad address literal           (and must not be a DNS name), while the 16-bit unsigned integer is           the port number.         ]]>
 * @TP_SOCKET_ADDRESS_TYPE_IPV6: <![CDATA[           An IPv6 socket. The address variant contains a Socket_Address_IPv6,           i.e. a structure with signature (sq)           in which the string is an IPv6 address literal as specified in           RFC2373 (and must not be a DNS name), while the 16-bit unsigned           integer is the port number.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_SOCKET_ADDRESS_TYPE_UNIX = 0,
    TP_SOCKET_ADDRESS_TYPE_ABSTRACT_UNIX = 1,
    TP_SOCKET_ADDRESS_TYPE_IPV4 = 2,
    TP_SOCKET_ADDRESS_TYPE_IPV6 = 3,
} TpSocketAddressType;

/**
 * NUM_TP_SOCKET_ADDRESS_TYPES:
 *
 * 1 higher than the highest valid value of #TpSocketAddressType.
 */
#define NUM_TP_SOCKET_ADDRESS_TYPES (3+1)

/**
 *
TpSocketAccessControl:
 * @TP_SOCKET_ACCESS_CONTROL_LOCALHOST: <![CDATA[           The IP or Unix socket can be accessed by any local user (e.g.           a Unix socket that accepts all local connections, or an IP socket           listening on 127.0.0.1 (or ::1) or rejecting connections not from           that address). The associated variant must be ignored.         ]]>
 * @TP_SOCKET_ACCESS_CONTROL_PORT: <![CDATA[           May only be used on IP sockets. The associated variant must contain           a struct Socket_Address_IPv4 (or Socket_Address_IPv6)           containing the string form of an IP address of the appropriate           version, and a port number. The socket can only be accessed if the           connecting process has that address and port number; all other           connections will be rejected.         ]]>
 * @TP_SOCKET_ACCESS_CONTROL_NETMASK: <![CDATA[           May only be used on IP sockets. The associated variant must contain           a struct Socket_Netmask_IPv4 (or Socket_Netmask_IPv6) with           signature (sy), containing the string form of an           IP address of the appropriate version, and a prefix length "n".           The socket can only be accessed if the first n bits of the           connecting address match the first n bits of the given address.         ]]>
 * @TP_SOCKET_ACCESS_CONTROL_CREDENTIALS: <![CDATA[           May only be used on UNIX sockets.             The connecting process must send a byte when             it first connects, which is not considered to be part of the data             stream. If the operating system uses sendmsg() with SCM_CREDS or             SCM_CREDENTIALS to pass credentials over sockets, the connecting             process must do so if possible; if not, it must still send the             byte.            The listening process will disconnect the connection unless it             can determine by OS-specific means that the connecting process             has the same user ID as the listening process.            The associated variant must be ignored.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_SOCKET_ACCESS_CONTROL_LOCALHOST = 0,
    TP_SOCKET_ACCESS_CONTROL_PORT = 1,
    TP_SOCKET_ACCESS_CONTROL_NETMASK = 2,
    TP_SOCKET_ACCESS_CONTROL_CREDENTIALS = 3,
} TpSocketAccessControl;

/**
 * NUM_TP_SOCKET_ACCESS_CONTROLS:
 *
 * 1 higher than the highest valid value of #TpSocketAccessControl.
 */
#define NUM_TP_SOCKET_ACCESS_CONTROLS (3+1)

/**
 *
TpMediaStreamError:
 * @TP_MEDIA_STREAM_ERROR_UNKNOWN: <![CDATA[           An unknown error occured.         ]]>
 * @TP_MEDIA_STREAM_ERROR_EOS: <![CDATA[           The end of the stream was reached.         ]]>
 * @TP_MEDIA_STREAM_ERROR_CODEC_NEGOTIATION_FAILED: <![CDATA[           There are no common codecs between the local side           and the other particpants in the call. The possible codecs are not           signalled here: the streaming implementation is assumed to report           them in an implementation-dependent way, e.g. Farsight should use           GstMissingElement.         ]]>
 * @TP_MEDIA_STREAM_ERROR_CONNECTION_FAILED: <![CDATA[           A network connection for the Media could not be established or was           lost.         ]]>
 * @TP_MEDIA_STREAM_ERROR_NETWORK_ERROR: <![CDATA[           There was an error in the networking stack           (other than the connection failure).         ]]>
 * @TP_MEDIA_STREAM_ERROR_NO_CODECS: <![CDATA[           There are no installed codecs for this media type.         ]]>
 * @TP_MEDIA_STREAM_ERROR_INVALID_CM_BEHAVIOR: <![CDATA[           The CM is doing something wrong.         ]]>
 * @TP_MEDIA_STREAM_ERROR_MEDIA_ERROR: <![CDATA[           There was an error in the media processing stack.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_MEDIA_STREAM_ERROR_UNKNOWN = 0,
    TP_MEDIA_STREAM_ERROR_EOS = 1,
    TP_MEDIA_STREAM_ERROR_CODEC_NEGOTIATION_FAILED = 2,
    TP_MEDIA_STREAM_ERROR_CONNECTION_FAILED = 3,
    TP_MEDIA_STREAM_ERROR_NETWORK_ERROR = 4,
    TP_MEDIA_STREAM_ERROR_NO_CODECS = 5,
    TP_MEDIA_STREAM_ERROR_INVALID_CM_BEHAVIOR = 6,
    TP_MEDIA_STREAM_ERROR_MEDIA_ERROR = 7,
} TpMediaStreamError;

/**
 * NUM_TP_MEDIA_STREAM_ERRORS:
 *
 * 1 higher than the highest valid value of #TpMediaStreamError.
 */
#define NUM_TP_MEDIA_STREAM_ERRORS (7+1)

/**
 *
TpMediaStreamBaseProto:
 * @TP_MEDIA_STREAM_BASE_PROTO_UDP: <![CDATA[UDP (User Datagram Protocol)]]>
 * @TP_MEDIA_STREAM_BASE_PROTO_TCP: <![CDATA[TCP (Transmission Control Protocol)]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_MEDIA_STREAM_BASE_PROTO_UDP = 0,
    TP_MEDIA_STREAM_BASE_PROTO_TCP = 1,
} TpMediaStreamBaseProto;

/**
 * NUM_TP_MEDIA_STREAM_BASE_PROTOS:
 *
 * 1 higher than the highest valid value of #TpMediaStreamBaseProto.
 */
#define NUM_TP_MEDIA_STREAM_BASE_PROTOS (1+1)

/**
 *
TpMediaStreamTransportType:
 * @TP_MEDIA_STREAM_TRANSPORT_TYPE_LOCAL: <![CDATA[           A local address         ]]>
 * @TP_MEDIA_STREAM_TRANSPORT_TYPE_DERIVED: <![CDATA[           An external address derived by a method such as STUN         ]]>
 * @TP_MEDIA_STREAM_TRANSPORT_TYPE_RELAY: <![CDATA[           An external stream relay         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_MEDIA_STREAM_TRANSPORT_TYPE_LOCAL = 0,
    TP_MEDIA_STREAM_TRANSPORT_TYPE_DERIVED = 1,
    TP_MEDIA_STREAM_TRANSPORT_TYPE_RELAY = 2,
} TpMediaStreamTransportType;

/**
 * NUM_TP_MEDIA_STREAM_TRANSPORT_TYPES:
 *
 * 1 higher than the highest valid value of #TpMediaStreamTransportType.
 */
#define NUM_TP_MEDIA_STREAM_TRANSPORT_TYPES (2+1)

/**
 *
TpPropertyFlags:
 * @TP_PROPERTY_FLAG_READ: <![CDATA[The property can be read]]>
 * @TP_PROPERTY_FLAG_WRITE: <![CDATA[The property can be written]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_PROPERTY_FLAG_READ = 1,
    TP_PROPERTY_FLAG_WRITE = 2,
} TpPropertyFlags;

/**
 *
TpDebugLevel:
 * @TP_DEBUG_LEVEL_ERROR: <![CDATA[           Log level for errors. Error messages are always fatal, resulting           in the service terminating after something completely           unexpected occurred.         ]]>
 * @TP_DEBUG_LEVEL_CRITICAL: <![CDATA[           Log level for critical messages. Critical messages are messages           that the service might predict and it is up to the service itself           to decide whether to terminate following a critical message.         ]]>
 * @TP_DEBUG_LEVEL_WARNING: <![CDATA[           Log level for warnings.         ]]>
 * @TP_DEBUG_LEVEL_MESSAGE: <![CDATA[           Log level for messages.         ]]>
 * @TP_DEBUG_LEVEL_INFO: <![CDATA[           Log level for information messages.         ]]>
 * @TP_DEBUG_LEVEL_DEBUG: <![CDATA[           Log level for debug messages.         ]]>
 *
 * Bitfield/set of flags generated from the Telepathy specification.
 */
typedef enum {
    TP_DEBUG_LEVEL_ERROR = 0,
    TP_DEBUG_LEVEL_CRITICAL = 1,
    TP_DEBUG_LEVEL_WARNING = 2,
    TP_DEBUG_LEVEL_MESSAGE = 3,
    TP_DEBUG_LEVEL_INFO = 4,
    TP_DEBUG_LEVEL_DEBUG = 5,
} TpDebugLevel;

/**
 * NUM_TP_DEBUG_LEVELS:
 *
 * 1 higher than the highest valid value of #TpDebugLevel.
 */
#define NUM_TP_DEBUG_LEVELS (5+1)


#ifdef __cplusplus
}
#endif
