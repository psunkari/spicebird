
/**
 * TP_ERROR_STR_NETWORK_ERROR:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.NetworkError
 *
 * Raised when there is an error reading from or writing to the network.
 */
#define TP_ERROR_STR_NETWORK_ERROR "org.freedesktop.Telepathy.Error.NetworkError"

/**
 * TP_ERROR_STR_NOT_IMPLEMENTED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.NotImplemented
 *
 * Raised when the requested method, channel, etc is not available on this connection.
 */
#define TP_ERROR_STR_NOT_IMPLEMENTED "org.freedesktop.Telepathy.Error.NotImplemented"

/**
 * TP_ERROR_STR_INVALID_ARGUMENT:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.InvalidArgument
 *
 * Raised when one of the provided arguments is invalid.
 */
#define TP_ERROR_STR_INVALID_ARGUMENT "org.freedesktop.Telepathy.Error.InvalidArgument"

/**
 * TP_ERROR_STR_NOT_AVAILABLE:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.NotAvailable
 *
 * Raised when the requested functionality is temporarily unavailable.
 */
#define TP_ERROR_STR_NOT_AVAILABLE "org.freedesktop.Telepathy.Error.NotAvailable"

/**
 * TP_ERROR_STR_PERMISSION_DENIED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.PermissionDenied
 *
 * The user is not permitted to perform the requested operation.
 */
#define TP_ERROR_STR_PERMISSION_DENIED "org.freedesktop.Telepathy.Error.PermissionDenied"

/**
 * TP_ERROR_STR_DISCONNECTED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Disconnected
 *
 * The connection is not currently connected and cannot be used.       This error may also be raised when operations are performed on a       Connection for which       &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection&quot;&gt;StatusChanged&lt;/tp:dbus-ref&gt;       has signalled status Disconnected for reason None.        &lt;tp:rationale&gt;         The second usage corresponds to None in the         &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt; enum; if a better reason         is available, the corresponding error should be used instead.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_DISCONNECTED "org.freedesktop.Telepathy.Error.Disconnected"

/**
 * TP_ERROR_STR_INVALID_HANDLE:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.InvalidHandle
 *
 * The handle specified is unknown on this channel or connection.
 */
#define TP_ERROR_STR_INVALID_HANDLE "org.freedesktop.Telepathy.Error.InvalidHandle"

/**
 * TP_ERROR_STR_CHANNEL_BANNED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Channel.Banned
 *
 * You are banned from the channel.
 */
#define TP_ERROR_STR_CHANNEL_BANNED "org.freedesktop.Telepathy.Error.Channel.Banned"

/**
 * TP_ERROR_STR_CHANNEL_FULL:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Channel.Full
 *
 * The channel is full.
 */
#define TP_ERROR_STR_CHANNEL_FULL "org.freedesktop.Telepathy.Error.Channel.Full"

/**
 * TP_ERROR_STR_CHANNEL_INVITE_ONLY:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Channel.InviteOnly
 *
 * The requested channel is invite-only.
 */
#define TP_ERROR_STR_CHANNEL_INVITE_ONLY "org.freedesktop.Telepathy.Error.Channel.InviteOnly"

/**
 * TP_ERROR_STR_NOT_YOURS:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.NotYours
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;       &lt;p&gt;The requested channel or other resource already exists, and another         user interface in this session is responsible for it.&lt;/p&gt;        &lt;p&gt;User interfaces SHOULD handle this error unobtrusively, since it         indicates that some other user interface is already processing the         channel.&lt;/p&gt;
 */
#define TP_ERROR_STR_NOT_YOURS "org.freedesktop.Telepathy.Error.NotYours"

/**
 * TP_ERROR_STR_CANCELLED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Cancelled
 *
 * Raised by an ongoing request if it is cancelled by user request before       it has completed, or when operations are performed on an object which       the user has asked to close (for instance, a Connection where the user       has called Disconnect, or a Channel where the user has called Close).        &lt;tp:rationale&gt;         The second form can be used to correspond to the Requested member in         the &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt; enum, or to         to represent the situation where disconnecting a Connection,         closing a Channel, etc. has been requested by the user but this         request has not yet been acted on, for instance because the         service will only act on the request when it has finished processing         an event queue.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_CANCELLED "org.freedesktop.Telepathy.Error.Cancelled"

/**
 * TP_ERROR_STR_AUTHENTICATION_FAILED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.AuthenticationFailed
 *
 * Raised when authentication with a service was unsuccessful.       &lt;tp:rationale&gt;         This corresponds to Authentication_Failed in the         &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt; enum.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_AUTHENTICATION_FAILED "org.freedesktop.Telepathy.Error.AuthenticationFailed"

/**
 * TP_ERROR_STR_ENCRYPTION_NOT_AVAILABLE:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.EncryptionNotAvailable
 *
 * Raised if a user request insisted that encryption should be used,       but encryption was not actually available.        &lt;tp:rationale&gt;         This corresponds to part of Encryption_Error in the         &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt; enum. It&apos;s been separated         into a distinct error here because the two concepts that were part         of EncryptionError seem to be things that could reasonably appear         differently in the UI.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_ENCRYPTION_NOT_AVAILABLE "org.freedesktop.Telepathy.Error.EncryptionNotAvailable"

/**
 * TP_ERROR_STR_ENCRYPTION_ERROR:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.EncryptionError
 *
 * Raised if encryption appears to be available, but could not actually be       used (for instance if SSL/TLS negotiation fails).       &lt;tp:rationale&gt;         This corresponds to part of Encryption_Error in the         &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt; enum.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_ENCRYPTION_ERROR "org.freedesktop.Telepathy.Error.EncryptionError"

/**
 * TP_ERROR_STR_CERT_NOT_PROVIDED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Cert.NotProvided
 *
 * Raised if the server did not provide a SSL/TLS certificate. This error       MUST NOT be used to represent the absence of a client certificate       provided by the Telepathy connection manager.       &lt;tp:rationale&gt;         This corresponds to Cert_Not_Provided in the         &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt; enum. That error         explicitly applied only to server SSL certificates, so this one         is similarly limited; having the CM present a client certificate         is a possible future feature, but it should have its own error         handling.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_CERT_NOT_PROVIDED "org.freedesktop.Telepathy.Error.Cert.NotProvided"

/**
 * TP_ERROR_STR_CERT_UNTRUSTED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Cert.Untrusted
 *
 * Raised if the server provided a SSL/TLS certificate signed by an       untrusted certifying authority. This error SHOULD NOT be used to       represent a self-signed certificate: see the Self Signed error for that.       &lt;tp:rationale&gt;         This corresponds to Cert_Untrusted in the         &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt; enum, with a clarification         to avoid ambiguity.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_CERT_UNTRUSTED "org.freedesktop.Telepathy.Error.Cert.Untrusted"

/**
 * TP_ERROR_STR_CERT_EXPIRED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Cert.Expired
 *
 * Raised if the server provided an expired SSL/TLS certificate.       &lt;tp:rationale&gt;         This corresponds to Cert_Expired in the         &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt; enum.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_CERT_EXPIRED "org.freedesktop.Telepathy.Error.Cert.Expired"

/**
 * TP_ERROR_STR_CERT_NOT_ACTIVATED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Cert.NotActivated
 *
 * Raised if the server provided an SSL/TLS certificate that will become       valid at some point in the future.       &lt;tp:rationale&gt;         This corresponds to Cert_Not_Activated in the         &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt; enum.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_CERT_NOT_ACTIVATED "org.freedesktop.Telepathy.Error.Cert.NotActivated"

/**
 * TP_ERROR_STR_CERT_FINGERPRINT_MISMATCH:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Cert.FingerprintMismatch
 *
 * Raised if the server provided an SSL/TLS certificate that did not have       the expected fingerprint.       &lt;tp:rationale&gt;         This corresponds to Cert_Fingerprint_Mismatch in the         &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt; enum.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_CERT_FINGERPRINT_MISMATCH "org.freedesktop.Telepathy.Error.Cert.FingerprintMismatch"

/**
 * TP_ERROR_STR_CERT_HOSTNAME_MISMATCH:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Cert.HostnameMismatch
 *
 * Raised if the server provided an SSL/TLS certificate that did not match       its hostname.       &lt;tp:rationale&gt;         This corresponds to Cert_Hostname_Mismatch in the         &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt; enum.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_CERT_HOSTNAME_MISMATCH "org.freedesktop.Telepathy.Error.Cert.HostnameMismatch"

/**
 * TP_ERROR_STR_CERT_SELF_SIGNED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Cert.SelfSigned
 *
 * Raised if the server provided an SSL/TLS certificate that is self-signed       and untrusted.       &lt;tp:rationale&gt;         This corresponds to Cert_Hostname_Mismatch in the         &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt; enum.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_CERT_SELF_SIGNED "org.freedesktop.Telepathy.Error.Cert.SelfSigned"

/**
 * TP_ERROR_STR_CERT_INVALID:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Cert.Invalid
 *
 * Raised if the server provided an SSL/TLS certificate that is       unacceptable in some way that does not have a more specific error.       &lt;tp:rationale&gt;         This corresponds to Cert_Other_Error in the         &lt;tp:type&gt;Connection_Status_Reason&lt;/tp:type&gt; enum.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_CERT_INVALID "org.freedesktop.Telepathy.Error.Cert.Invalid"

/**
 * TP_ERROR_STR_NOT_CAPABLE:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.NotCapable
 *
 * Raised when requested functionality is unavailable due to contact     not having required capabilities.
 */
#define TP_ERROR_STR_NOT_CAPABLE "org.freedesktop.Telepathy.Error.NotCapable"

/**
 * TP_ERROR_STR_OFFLINE:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Offline
 *
 * Raised when requested functionality is unavailable because a contact is       offline.        &lt;tp:rationale&gt;         This corresponds to Offline in the         &lt;tp:type&gt;Channel_Group_Change_Reason&lt;/tp:type&gt; enum.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_OFFLINE "org.freedesktop.Telepathy.Error.Offline"

/**
 * TP_ERROR_STR_CHANNEL_KICKED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Channel.Kicked
 *
 * Used to represent a user being ejected from a channel by another user,       for instance being kicked from a chatroom.        &lt;tp:rationale&gt;         This corresponds to Kicked in the         &lt;tp:type&gt;Channel_Group_Change_Reason&lt;/tp:type&gt; enum.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_CHANNEL_KICKED "org.freedesktop.Telepathy.Error.Channel.Kicked"

/**
 * TP_ERROR_STR_BUSY:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Busy
 *
 * Used to represent a user being removed from a channel because of a       &amp;quot;busy&amp;quot; indication. This error SHOULD NOT be used to represent a server       or other infrastructure being too busy to process a request - for that,       see ServerBusy.        &lt;tp:rationale&gt;         This corresponds to Busy in the         &lt;tp:type&gt;Channel_Group_Change_Reason&lt;/tp:type&gt; enum.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_BUSY "org.freedesktop.Telepathy.Error.Busy"

/**
 * TP_ERROR_STR_NO_ANSWER:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.NoAnswer
 *
 * Used to represent a user being removed from a channel because they did       not respond, e.g. to a StreamedMedia call.        &lt;tp:rationale&gt;         This corresponds to No_Answer in the         &lt;tp:type&gt;Channel_Group_Change_Reason&lt;/tp:type&gt; enum.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_NO_ANSWER "org.freedesktop.Telepathy.Error.NoAnswer"

/**
 * TP_ERROR_STR_DOES_NOT_EXIST:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.DoesNotExist
 *
 * Raised when the requested user does not, in fact, exist.        &lt;tp:rationale&gt;         This corresponds to Invalid_Contact in the         &lt;tp:type&gt;Channel_Group_Change_Reason&lt;/tp:type&gt; enum, but can also be         used to represent other things not existing (like chatrooms, perhaps).       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_DOES_NOT_EXIST "org.freedesktop.Telepathy.Error.DoesNotExist"

/**
 * TP_ERROR_STR_TERMINATED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.Terminated
 *
 * Raised when a channel is terminated for an unspecified reason. In       particular, this error SHOULD be used whenever normal termination of       a 1-1 StreamedMedia call by the remote user is represented as a D-Bus       error name.        &lt;tp:rationale&gt;         This corresponds to None in the         &lt;tp:type&gt;Channel_Group_Change_Reason&lt;/tp:type&gt; enum.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_TERMINATED "org.freedesktop.Telepathy.Error.Terminated"

/**
 * TP_ERROR_STR_CONNECTION_REFUSED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.ConnectionRefused
 *
 * Raised when a connection is refused.
 */
#define TP_ERROR_STR_CONNECTION_REFUSED "org.freedesktop.Telepathy.Error.ConnectionRefused"

/**
 * TP_ERROR_STR_CONNECTION_FAILED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.ConnectionFailed
 *
 * Raised when a connection can&apos;t be established.
 */
#define TP_ERROR_STR_CONNECTION_FAILED "org.freedesktop.Telepathy.Error.ConnectionFailed"

/**
 * TP_ERROR_STR_CONNECTION_LOST:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.ConnectionLost
 *
 * Raised when a connection is broken.
 */
#define TP_ERROR_STR_CONNECTION_LOST "org.freedesktop.Telepathy.Error.ConnectionLost"

/**
 * TP_ERROR_STR_ALREADY_CONNECTED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.AlreadyConnected
 *
 * Raised when the user attempts to connect to an account but they are       already connected (perhaps from another client or computer), and the       protocol or account settings do not allow this.        &lt;tp:rationale&gt;         XMPP can have this behaviour if the user chooses the same resource         in both clients (it is server-dependent whether the result is         AlreadyConnected on the new connection, ConnectionReplaced on the         old connection, or two successful connections).       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_ALREADY_CONNECTED "org.freedesktop.Telepathy.Error.AlreadyConnected"

/**
 * TP_ERROR_STR_CONNECTION_REPLACED:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.ConnectionReplaced
 *
 * Raised by an existing connection to an account if it is replaced by       a new connection (perhaps from another client or computer).        &lt;tp:rationale&gt;         In MSNP, when connecting twice with the same Passport, the new         connection &amp;quot;wins&amp;quot; and the old one is automatically disconnected.         XMPP can also have this behaviour if the user chooses the same         resource in two clients (it is server-dependent whether the result is         AlreadyConnected on the new connection, ConnectionReplaced on the         old connection, or two successful connections).       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_CONNECTION_REPLACED "org.freedesktop.Telepathy.Error.ConnectionReplaced"

/**
 * TP_ERROR_STR_REGISTRATION_EXISTS:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.RegistrationExists
 *
 * Raised during in-band registration if the server indicates that the       requested account already exists.
 */
#define TP_ERROR_STR_REGISTRATION_EXISTS "org.freedesktop.Telepathy.Error.RegistrationExists"

/**
 * TP_ERROR_STR_SERVICE_BUSY:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.ServiceBusy
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;       Raised if a server or some other piece of infrastructure cannot process       the request, e.g. due to resource limitations. Clients MAY try again       later.        &lt;tp:rationale&gt;         This is not the same error as Busy, which indicates that a         &lt;em&gt;user&lt;/em&gt; is busy.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_SERVICE_BUSY "org.freedesktop.Telepathy.Error.ServiceBusy"

/**
 * TP_ERROR_STR_RESOURCE_UNAVAILABLE:
 *
 * The D-Bus error name org.freedesktop.Telepathy.Error.ResourceUnavailable
 *
 * Raised if a request cannot be satisfied because a process local to the       user has insufficient resources. Clients MAY try again       later.        &lt;tp:rationale&gt;         For instance, the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelDispatcher&lt;/tp:dbus-ref&gt;         might raise this error for some or all channel requests if it has         detected that there is not enough free memory.       &lt;/tp:rationale&gt;
 */
#define TP_ERROR_STR_RESOURCE_UNAVAILABLE "org.freedesktop.Telepathy.Error.ResourceUnavailable"
