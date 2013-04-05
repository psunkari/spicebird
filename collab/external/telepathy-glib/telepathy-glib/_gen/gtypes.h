/* Auto-generated, do not edit.
 *
 * This file may be distributed under the same terms
 * as the specification from which it was generated.
 */

/**
 * TP_HASH_TYPE_ALIAS_MAP:
 *
 * A dictionary whose keys are contact handles and whose         values are aliases.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{us}</literal>.
 *
 * Keys (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Handle</literal>):
 * (Undocumented)
 *
 * Values (D-Bus type <literal>s</literal>,
 * named <literal>Alias</literal>):
 * (Undocumented)
 *
 */
#define TP_HASH_TYPE_ALIAS_MAP (tp_type_dbus_hash_us ())

/**
 * TP_HASH_TYPE_AVATAR_TOKEN_MAP:
 *
 * A dictionary whose keys are contact handles and whose         values are avatar tokens.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{us}</literal>.
 *
 * Keys (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Handle</literal>):
 * (Undocumented)
 *
 * Values (D-Bus type <literal>s</literal>,
 * type <literal>Avatar_Token</literal>,
 * named <literal>Token</literal>):
 * (Undocumented)
 *
 */
#define TP_HASH_TYPE_AVATAR_TOKEN_MAP (tp_type_dbus_hash_us ())

/**
 * TP_HASH_TYPE_CONTACT_CAPABILITIES_MAP:
 *
 * A mapping from contact handle to their capabilities.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{ua(a{sv}as)}</literal>.
 *
 * Keys (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Key</literal>):
 * A contact handle.
 *
 * Values (D-Bus type <literal>a(a{sv}as)</literal>,
 * type <literal>Requestable_Channel_Class[]</literal>,
 * named <literal>Value</literal>):
 * The contact capabilities.
 *
 */
#define TP_HASH_TYPE_CONTACT_CAPABILITIES_MAP (tp_type_dbus_hash_ua_28a_7bsv_7das_29 ())

/**
 * TP_ARRAY_TYPE_CONTACT_CAPABILITIES_MAP_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_HASH_TYPE_CONTACT_CAPABILITIES_MAP.
 */
#define TP_ARRAY_TYPE_CONTACT_CAPABILITIES_MAP_LIST (tp_type_dbus_array_of_a_7bua_28a_7bsv_7das_29_7d ())

/**
 * TP_HASH_TYPE_SIMPLE_CONTACT_PRESENCES:
 *
 * Mapping returned by &lt;tp:member-ref&gt;GetPresences&lt;/tp:member-ref&gt;         and signalled by &lt;tp:member-ref&gt;PresencesChanged&lt;/tp:member-ref&gt;,         indicating the presence of a number of contacts.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{u(uss)}</literal>.
 *
 * Keys (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Contact</literal>):
 * A contact
 *
 * Values (D-Bus type <literal>(uss)</literal>,
 * type <literal>Simple_Presence</literal>,
 * named <literal>Presence</literal>):
 * The contact&apos;s presence
 *
 */
#define TP_HASH_TYPE_SIMPLE_CONTACT_PRESENCES (tp_type_dbus_hash_u_28uss_29 ())

/**
 * TP_HASH_TYPE_SIMPLE_STATUS_SPEC_MAP:
 *
 * A mapping describing possible statuses.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{s(ubb)}</literal>.
 *
 * Keys (D-Bus type <literal>s</literal>,
 * named <literal>Identifier</literal>):
 * The string identifier of this status.
 *
 * Values (D-Bus type <literal>(ubb)</literal>,
 * type <literal>Simple_Status_Spec</literal>,
 * named <literal>Spec</literal>):
 * Details of this status.
 *
 */
#define TP_HASH_TYPE_SIMPLE_STATUS_SPEC_MAP (tp_type_dbus_hash_s_28ubb_29 ())

/**
 * TP_HASH_TYPE_MULTIPLE_STATUS_MAP:
 *
 * Mapping used in         &lt;tp:type&gt;Last_Activity_And_Statuses&lt;/tp:type&gt; and passed to         &lt;tp:member-ref&gt;SetStatus&lt;/tp:member-ref&gt;, representing a collection of         statuses. Use of this mapping with more than one member is         deprecated.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{sa{sv}}</literal>.
 *
 * Keys (D-Bus type <literal>s</literal>,
 * named <literal>Status</literal>):
 * (Undocumented)
 *
 * Values (D-Bus type <literal>a{sv}</literal>,
 * type <literal>String_Variant_Map</literal>,
 * named <literal>Parameters</literal>):
 * (Undocumented)
 *
 */
#define TP_HASH_TYPE_MULTIPLE_STATUS_MAP (tp_type_dbus_hash_sa_7bsv_7d ())

/**
 * TP_HASH_TYPE_CONTACT_PRESENCES:
 *
 * Mapping returned by         &lt;tp:member-ref&gt;GetPresence&lt;/tp:member-ref&gt; and signalled by         &lt;tp:member-ref&gt;PresenceUpdate&lt;/tp:member-ref&gt;, where the keys are         contacts and the values represent their presences.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{u(ua{sa{sv}})}</literal>.
 *
 * Keys (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Contact</literal>):
 * (Undocumented)
 *
 * Values (D-Bus type <literal>(ua{sa{sv}})</literal>,
 * type <literal>Last_Activity_And_Statuses</literal>,
 * named <literal>Presence</literal>):
 * (Undocumented)
 *
 */
#define TP_HASH_TYPE_CONTACT_PRESENCES (tp_type_dbus_hash_u_28ua_7bsa_7bsv_7d_7d_29 ())

/**
 * TP_HASH_TYPE_STATUS_SPEC_MAP:
 *
 * (Undocumented)
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{s(ubba{ss})}</literal>.
 *
 * Keys (D-Bus type <literal>s</literal>,
 * named <literal>Identifier</literal>):
 * (Undocumented)
 *
 * Values (D-Bus type <literal>(ubba{ss})</literal>,
 * type <literal>Status_Spec</literal>,
 * named <literal>Spec</literal>):
 * (Undocumented)
 *
 */
#define TP_HASH_TYPE_STATUS_SPEC_MAP (tp_type_dbus_hash_s_28ubba_7bss_7d_29 ())

/**
 * TP_HASH_TYPE_SINGLE_CONTACT_ATTRIBUTES_MAP:
 *
 * Some of the attributes of a single contact.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{sv}</literal>.
 *
 * Keys (D-Bus type <literal>s</literal>,
 * type <literal>Contact_Attribute</literal>,
 * named <literal>Attribute</literal>):
 * The name of the attribute
 *
 * Values (D-Bus type <literal>v</literal>,
 * named <literal>Value</literal>):
 * The value of the attribute
 *
 */
#define TP_HASH_TYPE_SINGLE_CONTACT_ATTRIBUTES_MAP (tp_type_dbus_hash_sv ())

/**
 * TP_HASH_TYPE_CONTACT_ATTRIBUTES_MAP:
 *
 * Mapping returned by         &lt;tp:member-ref&gt;GetContactAttributes&lt;/tp:member-ref&gt;, representing a         collection of Contacts and their requested attributes.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{ua{sv}}</literal>.
 *
 * Keys (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Contact</literal>):
 * A contact
 *
 * Values (D-Bus type <literal>a{sv}</literal>,
 * type <literal>Single_Contact_Attributes_Map</literal>,
 * named <literal>Attributes</literal>):
 * Attributes of that contact
 *
 */
#define TP_HASH_TYPE_CONTACT_ATTRIBUTES_MAP (tp_type_dbus_hash_ua_7bsv_7d ())

/**
 * TP_HASH_TYPE_CHANNEL_CLASS:
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Mapping representing a class of channels that can be requested           from a connection manager, can be handled by a user interface,           are supported by a contact, etc.&lt;/p&gt;          &lt;p&gt;Classes of channel are identified by the fixed values of           a subset of their properties.&lt;/p&gt;          &lt;p&gt;Channel classes SHOULD always include the keys           &lt;tp:dbus-ref&gt;org.freedesktop.Telepathy.Channel.ChannelType&lt;/tp:dbus-ref&gt;           and           &lt;tp:dbus-ref&gt;org.freedesktop.Telepathy.Channel.TargetHandleType&lt;/tp:dbus-ref&gt;.           &lt;/p&gt;
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{sv}</literal>.
 *
 * Keys (D-Bus type <literal>s</literal>,
 * type <literal>DBus_Qualified_Member</literal>,
 * named <literal>Key</literal>):
 * A D-Bus interface name, followed by a dot and a D-Bus property name.
 *
 * Values (D-Bus type <literal>v</literal>,
 * named <literal>Value</literal>):
 * The value of the property.
 *
 */
#define TP_HASH_TYPE_CHANNEL_CLASS (tp_type_dbus_hash_sv ())

/**
 * TP_ARRAY_TYPE_CHANNEL_CLASS_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_HASH_TYPE_CHANNEL_CLASS.
 */
#define TP_ARRAY_TYPE_CHANNEL_CLASS_LIST (tp_type_dbus_array_of_a_7bsv_7d ())

/**
 * TP_HASH_TYPE_LOCATION:
 *
 * A user&apos;s location, represented as an extensible mapping.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{sv}</literal>.
 *
 * Keys (D-Bus type <literal>s</literal>,
 * named <literal>Key</literal>):
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;            &lt;p&gt;Civic addresses are represented by the following well-known             keys (all of which have string values), which should be kept in             sync with those used in XEP-0080 and in the Geoclue project:&lt;/p&gt;            &lt;ul&gt;             &lt;li&gt;countrycode - s: an ISO-3166-1 alpha-2 (two-letter) country               code, e.g. &amp;quot;us&amp;quot;, &amp;quot;gb&amp;quot;, &amp;quot;fr&amp;quot;&lt;/li&gt;             &lt;li&gt;country - s: a country name in unspecified locale, e.g.               &amp;quot;USA&amp;quot;&lt;/li&gt;             &lt;li&gt;region - s: an administrative region of the nation, such as a               state or province&lt;/li&gt;             &lt;li&gt;locality - s: a locality within the administrative region, such               as a town or city&lt;/li&gt;             &lt;li&gt;area - s: a named area such as a campus or neighborhood&lt;/li&gt;             &lt;li&gt;postalcode - s: a code used for postal delivery&lt;/li&gt;             &lt;li&gt;street - s: a thoroughfare within the locality, or a crossing of               two thoroughfares&lt;/li&gt;           &lt;/ul&gt;            &lt;p&gt;The following address keys are defined in XEP-0080 but not by             Geoclue, and are also allowed:&lt;/p&gt;            &lt;ul&gt;             &lt;li&gt;building - s: a specific building on a street or in an area&lt;/li&gt;             &lt;li&gt;floor - s: a particular floor in a building&lt;/li&gt;             &lt;li&gt;room - s: a particular room in a building&lt;/li&gt;             &lt;li&gt;text - s: any more specific information, e.g.               &amp;quot;Northwest corner of the lobby&amp;quot;&lt;/li&gt;             &lt;li&gt;description - s: A natural-language name for or description of               the location, e.g. &amp;quot;Bill&apos;s house&amp;quot;&lt;/li&gt;             &lt;li&gt;uri - s: a URI representing the location or pointing to more               information about it&lt;/li&gt;           &lt;/ul&gt;            &lt;p&gt;Since the previous strings have data intended to be read by users,             the language used should be stated using:&lt;/p&gt;            &lt;ul&gt;             &lt;li&gt;language - s: a specific language or locale of location               information in a format compatible to RFC 4646. Note that UTF-8               is the only allowed encoding, e.g. &amp;quot;en&amp;quot; or &amp;quot;fr-CA&amp;quot;.&lt;/li&gt;           &lt;/ul&gt;            &lt;p&gt;Positions are represented by the following well-known keys:&lt;/p&gt;            &lt;ul&gt;             &lt;li&gt;lat - d: latitude in decimal degrees north, -90 to +90,               relative to the WGS-84 datum               &lt;tp:rationale&gt;                 This is from XEP-0080; the XEP allows use of a different                 datum, but recommends this one. We enforce sanity by requiring                 a consistent datum: a minimal compliant implementation of this                 specification in terms of XEP-0080 would simply ignore the                 &amp;lt;lat&amp;gt; and &amp;lt;lon&amp;gt; elements if &amp;lt;datum&amp;gt; exists                 and has a value other than WGS-84, while an advanced                 implementation might correct for the different datum.               &lt;/tp:rationale&gt;             &lt;/li&gt;             &lt;li&gt;lon - d: Longitude in decimal degrees east, -180 to +180,               relative to the WGS-84 datum               &lt;tp:rationale&gt;                 Same rationale as &apos;lat&apos;               &lt;/tp:rationale&gt;             &lt;/li&gt;             &lt;li&gt;alt - d: altitude in metres above sea level (negative               if below sea level)               &lt;tp:rationale&gt;                 This is from XEP-0080               &lt;/tp:rationale&gt;             &lt;/li&gt;              &lt;!-- Potentially to be reinstated later:                  http://bugs.freedesktop.org/show_bug.cgi?id=19585             &lt;li&gt;accuracy-level - i (&lt;tp:type&gt;Location_Accuracy_Level&lt;/tp:type&gt;):               an indication of accuracy, which SHOULD be omitted if it would be               Location_Accuracy_Level_None or               Location_Accuracy_Level_Detailed               &lt;tp:rationale&gt;                 This is a struct field in GeoClue; the name is new in this                 specification, and was chosen in an attempt to avoid clashing                 with any future XEP-0080 terminology.               &lt;/tp:rationale&gt;             &lt;/li&gt;             --&gt;              &lt;li&gt;accuracy - d: horizontal position error in metres if               known               &lt;tp:rationale&gt;                 This is from XEP-0080               &lt;/tp:rationale&gt;             &lt;/li&gt;           &lt;/ul&gt;            &lt;p&gt;Velocities are represented by the following well-known keys:&lt;/p&gt;            &lt;ul&gt;             &lt;li&gt;speed - d: speed in metres per second               &lt;tp:rationale&gt;                 This is from XEP-0080               &lt;/tp:rationale&gt;             &lt;/li&gt;             &lt;li&gt;bearing - d: direction of movement in decimal degrees,               where North is 0 and East is 90               &lt;tp:rationale&gt;                 This is from XEP-0080, and is equivalent to the struct field                 called &amp;quot;direction&amp;quot; in GeoClue               &lt;/tp:rationale&gt;             &lt;/li&gt;           &lt;/ul&gt;            &lt;p&gt;Other well-known keys:&lt;/p&gt;            &lt;ul&gt;             &lt;li&gt;timestamp - x (&lt;tp:type&gt;Unix_Timestamp64&lt;/tp:type&gt;): the time               that the contact was at this location, in seconds since               1970-01-01T00:00:00Z (i.e. the beginning of 1970 in UTC)               &lt;tp:rationale&gt;                 XEP-0080 uses an ISO 8601 string for this, but a number of                 seconds since the epoch is probably easier to work with.               &lt;/tp:rationale&gt;             &lt;/li&gt;           &lt;/ul&gt;
 *
 * Values (D-Bus type <literal>v</literal>,
 * named <literal>Value</literal>):
 * The value corresponding to the well-known key.
 *
 */
#define TP_HASH_TYPE_LOCATION (tp_type_dbus_hash_sv ())

/**
 * TP_HASH_TYPE_CONTACT_LOCATIONS:
 *
 * A map from contacts to their locations.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{ua{sv}}</literal>.
 *
 * Keys (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Contact</literal>):
 * A contact
 *
 * Values (D-Bus type <literal>a{sv}</literal>,
 * type <literal>Location</literal>,
 * named <literal>Location</literal>):
 * The contact&apos;s location, which MAY be empty to indicate           that the contact&apos;s location is unknown
 *
 */
#define TP_HASH_TYPE_CONTACT_LOCATIONS (tp_type_dbus_hash_ua_7bsv_7d ())

/**
 * TP_HASH_TYPE_SUPPORTED_SOCKET_MAP:
 *
 * The supported socket address and access-control types         for tubes. See GetAvailableStreamTubeTypes.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{uau}</literal>.
 *
 * Keys (D-Bus type <literal>u</literal>,
 * type <literal>Socket_Address_Type</literal>,
 * named <literal>Address_Type</literal>):
 * (Undocumented)
 *
 * Values (D-Bus type <literal>au</literal>,
 * type <literal>Socket_Access_Control[]</literal>,
 * named <literal>Access_Control</literal>):
 * (Undocumented)
 *
 */
#define TP_HASH_TYPE_SUPPORTED_SOCKET_MAP (tp_type_dbus_hash_uau ())

/**
 * TP_HASH_TYPE_DBUS_TUBE_PARTICIPANTS:
 *
 * Represents the participants in a multi-user D-Bus tube, as         used by the &lt;tp:member-ref&gt;DBusNames&lt;/tp:member-ref&gt; property and the         &lt;tp:member-ref&gt;DBusNamesChanged&lt;/tp:member-ref&gt; signal.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{us}</literal>.
 *
 * Keys (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Handle</literal>):
 * The handle of a participant in this D-Bus tube.
 *
 * Values (D-Bus type <literal>s</literal>,
 * type <literal>DBus_Unique_Name</literal>,
 * named <literal>Unique_Name</literal>):
 * That participant&apos;s unique name.
 *
 */
#define TP_HASH_TYPE_DBUS_TUBE_PARTICIPANTS (tp_type_dbus_hash_us ())

/**
 * TP_HASH_TYPE_CHANNEL_CALL_STATE_MAP:
 *
 * A map from contacts to call states.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{uu}</literal>.
 *
 * Keys (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Contact</literal>):
 * A contact involved in this call.
 *
 * Values (D-Bus type <literal>u</literal>,
 * type <literal>Channel_Call_State_Flags</literal>,
 * named <literal>State</literal>):
 * State flags for the given contact.
 *
 */
#define TP_HASH_TYPE_CHANNEL_CALL_STATE_MAP (tp_type_dbus_hash_uu ())

/**
 * TP_HASH_TYPE_HANDLE_OWNER_MAP:
 *
 * A map from channel-specific handles to their owners.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{uu}</literal>.
 *
 * Keys (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Channel_Specific_Handle</literal>):
 * A nonzero channel-specific handle
 *
 * Values (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Global_Handle</literal>):
 * The global handle that owns the corresponding channel-specific           handle, or 0 if this could not be determined
 *
 */
#define TP_HASH_TYPE_HANDLE_OWNER_MAP (tp_type_dbus_hash_uu ())

/**
 * TP_HASH_TYPE_HANDLE_IDENTIFIER_MAP:
 *
 * A map from handles to the corresponding normalized string identifier.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{us}</literal>.
 *
 * Keys (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Handle</literal>):
 * A nonzero handle
 *
 * Values (D-Bus type <literal>s</literal>,
 * named <literal>Identifier</literal>):
 * The same string that would be returned by &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection&quot;&gt;InspectHandles&lt;/tp:dbus-ref&gt;           for this handle.
 *
 */
#define TP_HASH_TYPE_HANDLE_IDENTIFIER_MAP (tp_type_dbus_hash_us ())

/**
 * TP_HASH_TYPE_MESSAGE_PART:
 *
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;         &lt;p&gt;Part of a message&apos;s content. In practice, this mapping never           appears in isolation - messages are represented by a list of           &lt;tp:type&gt;Message_Part&lt;/tp:type&gt; mappings.&lt;/p&gt;          &lt;p&gt;An example of how a message might           look, in a Python-like syntax:&lt;/p&gt;            &lt;pre&gt; [   {     &apos;message-token&apos;: &apos;9de9546a-3400-4419-a505-3ea270cb834c&apos;,     &apos;message-sender&apos;: 42,     &apos;message-sent&apos;: 1210067943,     &apos;message-received&apos;: 1210067947,     &apos;message-type&apos;: 0,              # = Channel_Text_Message_Type_Normal     &apos;pending-message-id&apos;: 437,   },   { &apos;alternative&apos;: &apos;main&apos;,     &apos;content-type&apos;: &apos;text/html&apos;,     &apos;content&apos;: &apos;Here is a photo of my cat:&amp;lt;br /&amp;gt;&apos; +                &apos;&amp;lt;img src=&amp;quot;cid:catphoto&amp;quot; alt=&amp;quot;lol!&amp;quot; /&amp;gt;&apos; +                &apos;&amp;lt;br /&amp;gt;Isn&apos;t it cute?&apos;,   },   { &apos;alternative&apos;: &apos;main&apos;,     &apos;content-type&apos;: &apos;text/plain&apos;,     &apos;content&apos;: &apos;Here is a photo of my cat:\n[IMG: lol!]\nIsn&apos;t it cute?&apos;,   },   { &apos;identifier&apos;: &apos;catphoto&apos;,     &apos;content-type&apos;: &apos;image/jpeg&apos;,     &apos;size&apos;: 101000,     &apos;needs-retrieval&apos;: True,   }, ]           &lt;/pre&gt;          &lt;div&gt;           &lt;p&gt;The first part of the message contains &amp;quot;headers&amp;quot; which refer             to the entire message.&lt;/p&gt;            &lt;p&gt;It is an error for a connection manager to put keys referring             to the message as a whole in the second or subsequent             Message_Part, but clients MUST recover from this error by ignoring             these keys in the second and subsequent parts.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;Instead of representing messages as aa{sv} where the first               dictionary is special (a dictionary of headers), we could have               used a signature like (a{sv}aa{sv}) to separate out the headers               and the body parts.&lt;/p&gt;              &lt;p&gt;However, this would make access to the messages more awkward.               In Python, the syntax for access to a header field would remain               &lt;code&gt;message[0][&apos;message-type&apos;]&lt;/code&gt;, but access to a body               field in the second body part would change from               message[2][&apos;content&apos;] to message[1][1][&apos;content&apos;]. In GLib,               the message would change from being a               GPtrArray(GHashTable) to being a               GValueArray(GHashTable, GPtrArray(GHashTable)) which is rather               inconvenient to dereference.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;Well-known keys for the message as a whole, and the corresponding             value types, include:&lt;/p&gt;            &lt;dl&gt;             &lt;dt&gt;message-token (s)&lt;/dt&gt;             &lt;dd&gt;An opaque, globally-unique identifier for the entire message.               This MAY be treated as if it were a MIME Message-ID, e.g. for               the mid: and cid: URI schemes. If omitted, there is no suitable               token.&lt;/dd&gt;              &lt;dt&gt;message-sent (x - &lt;tp:type&gt;Unix_Timestamp64&lt;/tp:type&gt;)&lt;/dt&gt;             &lt;dd&gt;The time the message was sent (if unavailable, the time               it arrived at a central server MAY be used). Omitted if no               reasonable approximation is available; SHOULD always be present               on outgoing messages.&lt;/dd&gt;              &lt;dt&gt;message-received (x - &lt;tp:type&gt;Unix_Timestamp64&lt;/tp:type&gt;)&lt;/dt&gt;             &lt;dd&gt;The time the message was received locally. SHOULD always               be present.&lt;/dd&gt;              &lt;dt&gt;message-sender (u - &lt;tp:type&gt;Contact_Handle&lt;/tp:type&gt;)&lt;/dt&gt;             &lt;dd&gt;The contact who sent the message. If 0 or omitted, the contact               who sent the message could not be determined.&lt;/dd&gt;              &lt;dt&gt;message-type (u - &lt;tp:type&gt;Channel_Text_Message_Type&lt;/tp:type&gt;)             &lt;/dt&gt;             &lt;dd&gt;The type of message; if omitted,               Channel_Text_Message_Type_Normal MUST be assumed. MAY               be omitted for normal chat messages.&lt;/dd&gt;              &lt;dt&gt;pending-message-id (u - &lt;tp:type&gt;Message_ID&lt;/tp:type&gt;)&lt;/dt&gt;             &lt;dd&gt;The incoming message ID. This MUST NOT be present on outgoing               messages. Clients SHOULD NOT store this key - it is only valid               for as long as the message remains unacknowledged.&lt;/dd&gt;              &lt;dt&gt;interface (s - &lt;tp:type&gt;DBus_Interface&lt;/tp:type&gt;)&lt;/dt&gt;             &lt;dd&gt;This message is specific to the given interface, which is               neither Text nor Messages. It SHOULD be ignored if that               interface is not supported. (Note that an &apos;interface&apos; key               can also appear on the second and subsequent parts, where               it indicates that that part (only) should be ignored if               unsupported.)&lt;/dd&gt;              &lt;dt&gt;scrollback (b)&lt;/dt&gt;             &lt;dd&gt;If present and true, the incoming message was part of a               replay of message history (this matches the Scrollback flag in               &lt;tp:type&gt;Channel_Text_Message_Flags&lt;/tp:type&gt;). This flag               does not make sense on outgoing messages and SHOULD NOT               appear there.&lt;/dd&gt;              &lt;dt&gt;rescued (b)&lt;/dt&gt;             &lt;dd&gt;If present and true, the incoming message has been seen in               a previous channel during the lifetime of the Connection,               but had not been acknowledged when that channel closed, causing               an identical channel (in which the message now appears) to open.               This matches the Rescued flag in               &lt;tp:type&gt;Channel_Text_Message_Flags&lt;/tp:type&gt;; it               does not make sense on outgoing messages, and SHOULD NOT               appear there.&lt;/dd&gt;           &lt;/dl&gt;         &lt;/div&gt;          &lt;div&gt;           &lt;p&gt;The second and subsequent parts contain the message&apos;s             content, including plain text, formatted text and/or attached             files.&lt;/p&gt;            &lt;p&gt;It is an error for a connection manager to put keys referring             to the message body in the first Message_Part;             clients MUST recover from this error by ignoring             these keys in first part.&lt;/p&gt;            &lt;p&gt;In any group of parts with the same non-empty value for the             &amp;quot;alternative&amp;quot; key (which represent alternative versions of the             same content), more faithful versions of the intended message MUST             come before less faithful versions (note that this order is the             opposite of MIME &amp;quot;multipart/alternative&amp;quot; parts). Clients SHOULD             display the first alternative that they understand.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;Specifying the preference order means that if the underlying               protocol doesn&apos;t support alternatives, the CM can safely delete               everything apart from the first supported alternative when               sending messages.&lt;/p&gt;              &lt;p&gt;The order is the reverse of MIME because MIME&apos;s rationale for               placing the &amp;quot;plainest&amp;quot; part first (legibility in pre-MIME UAs)               does not apply to us, and placing the most preferred part               first simplifies display (a client can iterate the message               in order, display the first alternative that it understands,               and skip displaying all subsequent parts with the same               &amp;quot;alternative&amp;quot; key).&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;Clients SHOULD present all parts that are not redundant             alternatives in the order they appear in this array, possibly             excluding parts that are referenced by another displayed part.             It is implementation-specific how the parts are presented to the             user.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;This allows CMs to assume that all parts are actually shown to               the user, even if they are not explicitly referenced - we do               not yet recommend formatted text, and there is no way for               plain text to reference an attachment since it has no concept of               markup or references. This also forces clients to do something               sensible with messages that consist entirely of &amp;quot;attachments&amp;quot;,               with no &amp;quot;body&amp;quot; at all.&lt;/p&gt;              &lt;p&gt;For instance, when displaying the above example, a client that               understands the HTML part should display the JPEG image once,               between the two lines &amp;quot;Here is a photo of my cat:&amp;quot; and               &amp;quot;Isn&apos;t it cute?&amp;quot;; it may additionally present the image in some               way for a second time, after &amp;quot;Isn&apos;t it cute?&amp;quot;, or may choose               not to.&lt;/p&gt;              &lt;p&gt;A client that does not understand HTML, displaying the same               message, should display the plain-text part, followed by the JPEG               image.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;Well-known keys for the second and subsequent parts, and the             corresponding value types, include:&lt;/p&gt;            &lt;dl&gt;             &lt;dt&gt;identifier (s)&lt;/dt&gt;             &lt;dd&gt;An opaque identifier for this part.               Parts of a message MAY reference other parts by treating               this identifier as if it were a MIME Content-ID and using               the cid: URI scheme.&lt;/dd&gt;              &lt;dt&gt;alternative (s)&lt;/dt&gt;             &lt;dd&gt;               &lt;p&gt;If present, this part of the message is an alternative for                 all other parts with the same value for &amp;quot;alternative&amp;quot;.                 Clients SHOULD only display one of them (this is expected to                 be used for XHTML messages in a future version of this                 specification).&lt;/p&gt;                &lt;p&gt;If omitted, this part is not an alternative for any other                 part.&lt;/p&gt;                &lt;p&gt;Parts of a message MAY reference the group of alternatives                 as a whole (i.e. a reference to whichever of them is chosen)                 by treating this identifier as if it were the MIME Content-ID                 of a multipart/alternative part, and using the cid: URI                 scheme.&lt;/p&gt;             &lt;/dd&gt;              &lt;dt&gt;content-type (s)&lt;/dt&gt;             &lt;dd&gt;               &lt;p&gt;The MIME type of this part. See the documentation                 for ReceivedMessage for notes on the special status of                 &amp;quot;text/plain&amp;quot; parts.&lt;/p&gt;                &lt;p&gt;Connection managers MUST NOT signal parts without a                 &apos;content-type&apos; key; if a protocol provides no way to determine                 the MIME type, the connection manager is responsible for                 guessing it, but MAY fall back to &amp;quot;text/plain&amp;quot; for text and                 &amp;quot;application/octet-stream&amp;quot; for non-text.&lt;/p&gt;                &lt;p&gt;Clients MUST ignore parts without a &apos;content-type&apos; key, which                 are reserved for future expansion.&lt;/p&gt;             &lt;/dd&gt;              &lt;dt&gt;lang (s)&lt;/dt&gt;             &lt;dd&gt;The natural language of this part, identified by a               RFC 3066 language tag.                &lt;tp:rationale&gt;                 XMPP allows alternative-selection by language as well as                 by content-type.               &lt;/tp:rationale&gt;             &lt;/dd&gt;              &lt;dt&gt;size (u)&lt;/dt&gt;             &lt;dd&gt;The size in bytes (if needs-retrieval is true, this MAY be an               estimated or approximate size). SHOULD be omitted if &apos;content&apos;               is provided.                &lt;tp:rationale&gt;                 There&apos;s no point in providing the size if you&apos;re already                 providing all the content.               &lt;/tp:rationale&gt;               &lt;/dd&gt;              &lt;dt&gt;needs-retrieval (b)&lt;/dt&gt;             &lt;dd&gt;If false or omitted, the connection               manager already holds this part in memory. If present and true,               this part will be retrieved on demand (like MIME&apos;s               message/external-body), so clients should expect retrieval to               take time; if this specification is later extended to provide a               streaming version of GetPendingMessageContent, clients should               use it for parts with this flag.&lt;/dd&gt;              &lt;dt&gt;truncated (b)&lt;/dt&gt;             &lt;dd&gt;The content available via the &apos;content&apos; key or               GetPendingMessageContent has been truncated by the server               or connection manager (equivalent to               Channel_Text_Message_Flag_Truncated in the Text interface).             &lt;/dd&gt;              &lt;dt&gt;content (s or ay)&lt;/dt&gt;             &lt;dd&gt;The part&apos;s content, if it is available and               sufficiently small to include here (implies that               &apos;needs-retrieval&apos; is false or omitted). Otherwise, omitted.               If the part is human-readable text or HTML, the value for this               key MUST be a UTF-8 string (D-Bus signature &apos;s&apos;).               If the part is not text, the value MUST be a byte-array               (D-Bus signature &apos;ay&apos;). If the part is a text-based format               that is not the main body of the message (e.g. an iCalendar               or an attached XML document), the value SHOULD be a UTF-8 string,               transcoding from another charset to UTF-8 if necessary, but               MAY be a byte-array (of unspecified character set) if               transcoding fails or the source charset is not known.&lt;/dd&gt;                &lt;!-- FIXME: &quot;sufficiently small to include&quot; is not currently               defined; we should add some API so clients can tell the                 CM how large a message it should emit in the signal.--&gt;              &lt;dt&gt;interface (s - &lt;tp:type&gt;DBus_Interface&lt;/tp:type&gt;)&lt;/dt&gt;             &lt;dd&gt;This part is specific to the given interface, which is               neither Text nor Messages. It SHOULD be ignored if that               interface is not supported. (Note that an &apos;interface&apos; key               can also appear on the first part, where it indicates that the               entire message should be ignored if unsupported.)&lt;/dd&gt;           &lt;/dl&gt;          &lt;/div&gt;           &lt;div&gt;           &lt;p&gt;Delivery reports are also represented as messages, of type             Channel_Text_Message_Type_Delivery_Report, with the             Non_Text_Content flag in the Text interface.&lt;/p&gt;            &lt;p&gt;Whenever a message of type             Channel_Text_Message_Type_Delivery_Report is signalled for a             delivery error report, Channel.Type.Text.SendError SHOULD also             be emitted; whenever Channel.Type.Text.SendError is emitted by a             channel which supports this interface, a message of type             Channel_Text_Message_Type_Delivery_Report MUST also be emitted.&lt;/p&gt;            &lt;p&gt;The corresponding message in the Messages interface MUST contain             &amp;quot;headers&amp;quot; for the delivery report, as specified below, in its             first Message_Part.&lt;/p&gt;            &lt;dl&gt;             &lt;dt&gt;message-sender (u - Contact_Handle as defined above)&lt;/dt&gt;             &lt;dd&gt;MUST be the intended recipient of the original message, if               available (zero or omitted if the intended recipient is               unavailable or is not a contact, e.g. a chatroom), even if the               delivery report actually came from an intermediate server.&lt;/dd&gt;              &lt;dt&gt;message-type (u - Channel_Text_Message_Type as defined               above)&lt;/dt&gt;             &lt;dd&gt;MUST be Channel_Text_Message_Type_Delivery_Report.&lt;/dd&gt;              &lt;dt&gt;delivery-status (u - Delivery_Status)&lt;/dt&gt;             &lt;dd&gt;The status of the message. All delivery reports MUST contain               this key in the first Message_Part.&lt;/dd&gt;              &lt;dt&gt;delivery-token (s - Sent_Message_Token)&lt;/dt&gt;              &lt;dd&gt;               &lt;p&gt;An identifier for the message to which this delivery report                 refers. MUST NOT be an empty string. Omitted if not                 available.&lt;/p&gt;                &lt;p&gt;Clients may match this against the token produced by the                 SendMessage method and MessageSent signal. A status report                 with no token could match any sent message, and a sent                 message with an empty token could match any status report.                 If multiple sent messages match, clients SHOULD use some                 reasonable heuristic.&lt;/p&gt;                &lt;tp:rationale&gt;                 In an ideal world, we could unambiguously match reports                 against messages; however, deployed protocols are not ideal,                 and not all reports and messages can be matched.               &lt;/tp:rationale&gt;             &lt;/dd&gt;              &lt;dt&gt;delivery-error (u - Channel_Text_Send_Error)&lt;/dt&gt;             &lt;dd&gt;               The reason for the failure. MUST be omitted if this was a               successful delivery; SHOULD be omitted if it would be               Channel_Text_Send_Error_Unknown.             &lt;/dd&gt;              &lt;dt&gt;delivery-dbus-error (s - DBus_Error_Name)&lt;/dt&gt;             &lt;dd&gt;               The reason for the failure, specified as a (possibly               implementation-specific) D-Bus error. MUST be omitted if this was               a successful delivery. If set, the &apos;delivery-error&apos; key SHOULD be               set to the closest available value.             &lt;/dd&gt;              &lt;dt&gt;delivery-error-message (s)&lt;/dt&gt;             &lt;dd&gt;               Debugging information on why the message could not be delivered.               MUST be omitted if this was a successful delivery; MAY always be               omitted.             &lt;/dd&gt;              &lt;dt&gt;delivery-echo (aa{sv} - Message_Part[])&lt;/dt&gt;             &lt;dd&gt;               &lt;p&gt;The message content, as defined by the Messages interface.                 Omitted if no content is available. Content MAY have been                 truncated, message parts MAY have been removed, and message                 parts MAY have had their content removed (i.e. the message part                 metadata is present, but the &apos;content&apos; key is not).&lt;/p&gt;                &lt;tp:rationale&gt;                 Some protocols, like XMPP, echo the failing message back to                 the sender. This is sometimes the only way to match it                 against the sent message, so we include it here.               &lt;/tp:rationale&gt;                &lt;p&gt;Unlike in the Messages interface, content not visible                 in the value for this key cannot be retrieved by another                 means, so the connection manager SHOULD be more                 aggressive about including (possibly truncated) message                 content in the &apos;content&apos; key.&lt;/p&gt;                &lt;tp:rationale&gt;                 The Messages interface needs to allow all content to be                 retrieved, but in this interface, the content we provide is                 merely a hint; so some is better than none, and it doesn&apos;t                 seem worth providing an API as complex as Messages&apos;                 GetPendingMessageContent for the echoed message.               &lt;/tp:rationale&gt;             &lt;/dd&gt;            &lt;/dl&gt;            &lt;p&gt;The second and subsequent Message_Part dictionaries, if present,             are a human-readable report from the IM service.&lt;/p&gt;            &lt;p&gt;Clients MUST NOT attempt to send delivery reports using the             SendMessage method in the Messages API, and connection managers             MUST NOT allow this to be done. If support for sending delivery             reports is later added, it will be part of this interface.&lt;/p&gt;            &lt;p&gt;Some example delivery reports in a Python-like syntax (in which             arrays are indicated by [a, b] and dictionaries by {k1: v1, k2: v2})             follow.&lt;/p&gt;            &lt;dl&gt;             &lt;dt&gt;A minimal delivery report indicating permanent failure of the               sent message whose token was               &lt;code&gt;b9a991bd-8845-4d7f-a704-215186f43bb4&lt;/code&gt; for an unknown               reason&lt;/dt&gt;             &lt;dd&gt;&lt;pre&gt; [{ # header &apos;message-sender&apos;: 123, &apos;message-type&apos;: Channel_Text_Message_Type_Delivery_Report, &apos;delivery-status&apos;: Delivery_Status_Permanently_Failed, &apos;delivery-token&apos;: &apos;b9a991bd-8845-4d7f-a704-215186f43bb4&apos;, } # no body ] &lt;/pre&gt;&lt;/dd&gt;              &lt;dt&gt;A delivery report where the failed message is echoed back to the               sender rather than being referenced by ID, and the failure reason               is that this protocol cannot send messages to offline contacts               such as the contact with handle 123&lt;/dt&gt;             &lt;dd&gt;&lt;pre&gt; [{ # header &apos;message-sender&apos;: 123, &apos;message-type&apos;: Channel_Text_Message_Type_Delivery_Report, &apos;delivery-status&apos;: Delivery_Status_Temporarily_Failed, &apos;delivery-error&apos;: Channel_Text_Send_Error_Offline, &apos;delivery-echo&apos;:     [{ # header of original message     &apos;message-sender&apos;: 1,     &apos;message-sent&apos;: 1210067943,     },     { # body of original message     &apos;content-type&apos;: &apos;text/plain&apos;,     &apos;content&apos;: &apos;Hello, world!&apos;,     }]   ],  # no body ] &lt;/pre&gt;&lt;/dd&gt;              &lt;dt&gt;A maximally complex delivery report: the server reports a               bilingual human-readable failure message because the user sent               a message &amp;quot;Hello, world!&amp;quot; with token               &lt;code&gt;b9a991bd-8845-4d7f-a704-215186f43bb4&lt;/code&gt; to a contact               with handle 123, but that handle represents a contact who does not               actually exist&lt;/dt&gt;             &lt;dd&gt;&lt;pre&gt; [{ # header &apos;message-sender&apos;: 123, &apos;message-type&apos;: Channel_Text_Message_Type_Delivery_Report, &apos;delivery-status&apos;: Delivery_Status_Permanently_Failed, &apos;delivery-error&apos;: Channel_Text_Send_Error_Invalid_Contact, &apos;delivery-token&apos;: &apos;b9a991bd-8845-4d7f-a704-215186f43bb4&apos;, &apos;delivery-echo&apos;:     [{ # header of original message     &apos;message-sender&apos;: 1,     &apos;message-sent&apos;: 1210067943,     },     { # body of original message     &apos;content-type&apos;: &apos;text/plain&apos;,     &apos;content&apos;: &apos;Hello, world!&apos;,     }]   ], }, { # message from server (alternative in English) &apos;alternative&apos;: &apos;404&apos;, &apos;content-type&apos;: &apos;text/plain&apos;, &apos;lang&apos;: &apos;en&apos;, &apos;content&apos;: &apos;I have no contact with that name&apos;, }, { # message from server (alternative in German) &apos;alternative&apos;: &apos;404&apos;. &apos;content-type&apos;: &apos;text/plain&apos;, &apos;lang&apos;: &apos;de&apos;, &apos;content&apos;, &apos;Ich habe keinen Kontakt mit diesem Namen&apos;, } ] &lt;/pre&gt;&lt;/dd&gt;              &lt;dt&gt;A minimal delivery report indicating successful delivery               of the sent message whose token was               &lt;code&gt;b9a991bd-8845-4d7f-a704-215186f43bb4&lt;/code&gt;&lt;/dt&gt;             &lt;dd&gt;&lt;pre&gt; [{ # header &apos;message-sender&apos;: 123, &apos;message-type&apos;: Channel_Text_Message_Type_Delivery_Report, &apos;delivery-status&apos;: Delivery_Status_Delivered, &apos;delivery-token&apos;: &apos;b9a991bd-8845-4d7f-a704-215186f43bb4&apos;, } # no body ] &lt;/pre&gt;&lt;/dd&gt;            &lt;/dl&gt;          &lt;/div&gt;
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{sv}</literal>.
 *
 * Keys (D-Bus type <literal>s</literal>,
 * named <literal>Key</literal>):
 * A key, which SHOULD be one of the well-known keys specified, if           possible.
 *
 * Values (D-Bus type <literal>v</literal>,
 * named <literal>Value</literal>):
 * The value corresponding to the given key, which must be of one of           the types indicated.
 *
 */
#define TP_HASH_TYPE_MESSAGE_PART (tp_type_dbus_hash_sv ())

/**
 * TP_ARRAY_TYPE_MESSAGE_PART_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_HASH_TYPE_MESSAGE_PART.
 */
#define TP_ARRAY_TYPE_MESSAGE_PART_LIST (tp_type_dbus_array_of_a_7bsv_7d ())

/**
 * TP_HASH_TYPE_MESSAGE_PART_CONTENT_MAP:
 *
 * A mapping from message part indexes to their content, as returned by         &lt;tp:member-ref&gt;GetPendingMessageContent&lt;/tp:member-ref&gt;.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{uv}</literal>.
 *
 * Keys (D-Bus type <literal>u</literal>,
 * type <literal>Message_Part_Index</literal>,
 * named <literal>Part</literal>):
 * Indexes into the array of &lt;tp:type&gt;Message_Part&lt;/tp:type&gt;s that           represents a message. The &amp;quot;headers&amp;quot; part (which is not a valid           argument to GetPendingMessageContent) is considered to be part 0,           so the valid part numbers start at 1 (for the second message part).
 *
 * Values (D-Bus type <literal>v</literal>,
 * named <literal>Content</literal>):
 * The message part&apos;s content. The variant MUST contain either type           &apos;s&apos; or &apos;ay&apos; (UTF-8 text string, or byte array), following the           same rules as for the value of the &apos;content&apos; key in           the &lt;tp:type&gt;Message_Part&lt;/tp:type&gt; mappings.
 *
 */
#define TP_HASH_TYPE_MESSAGE_PART_CONTENT_MAP (tp_type_dbus_hash_uv ())

/**
 * TP_HASH_TYPE_QUALIFIED_PROPERTY_VALUE_MAP:
 *
 * A mapping from strings representing D-Bus       properties (by their namespaced names) to their values.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{sv}</literal>.
 *
 * Keys (D-Bus type <literal>s</literal>,
 * type <literal>DBus_Qualified_Member</literal>,
 * named <literal>Key</literal>):
 * A D-Bus interface name, followed by a dot and a D-Bus property name.
 *
 * Values (D-Bus type <literal>v</literal>,
 * named <literal>Value</literal>):
 * The value of the property.
 *
 */
#define TP_HASH_TYPE_QUALIFIED_PROPERTY_VALUE_MAP (tp_type_dbus_hash_sv ())

/**
 * TP_ARRAY_TYPE_QUALIFIED_PROPERTY_VALUE_MAP_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_HASH_TYPE_QUALIFIED_PROPERTY_VALUE_MAP.
 */
#define TP_ARRAY_TYPE_QUALIFIED_PROPERTY_VALUE_MAP_LIST (tp_type_dbus_array_of_a_7bsv_7d ())

/**
 * TP_HASH_TYPE_STRING_VARIANT_MAP:
 *
 * A mapping from strings to variants representing extra       key-value pairs.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{sv}</literal>.
 *
 * Keys (D-Bus type <literal>s</literal>,
 * named <literal>Key</literal>):
 * (Undocumented)
 *
 * Values (D-Bus type <literal>v</literal>,
 * named <literal>Value</literal>):
 * (Undocumented)
 *
 */
#define TP_HASH_TYPE_STRING_VARIANT_MAP (tp_type_dbus_hash_sv ())

/**
 * TP_ARRAY_TYPE_STRING_VARIANT_MAP_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_HASH_TYPE_STRING_VARIANT_MAP.
 */
#define TP_ARRAY_TYPE_STRING_VARIANT_MAP_LIST (tp_type_dbus_array_of_a_7bsv_7d ())

/**
 * TP_HASH_TYPE_STRING_STRING_MAP:
 *
 * A mapping from strings to strings representing extra       key-value pairs.
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GHashTable
 * appropriate for representing a D-Bus
 * dictionary of signature
 * <literal>a{ss}</literal>.
 *
 * Keys (D-Bus type <literal>s</literal>,
 * named <literal>Key</literal>):
 * (Undocumented)
 *
 * Values (D-Bus type <literal>s</literal>,
 * named <literal>Value</literal>):
 * (Undocumented)
 *
 */
#define TP_HASH_TYPE_STRING_STRING_MAP (tp_type_dbus_hash_ss ())

/**
 * TP_ARRAY_TYPE_STRING_STRING_MAP_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_HASH_TYPE_STRING_STRING_MAP.
 */
#define TP_ARRAY_TYPE_STRING_STRING_MAP_LIST (tp_type_dbus_array_of_a_7bss_7d ())

GType tp_type_dbus_hash_u_28uss_29 (void);

GType tp_type_dbus_hash_sa_7bsv_7d (void);

GType tp_type_dbus_hash_uu (void);

GType tp_type_dbus_hash_ua_7bsv_7d (void);

GType tp_type_dbus_hash_u_28ua_7bsa_7bsv_7d_7d_29 (void);

GType tp_type_dbus_hash_uv (void);

GType tp_type_dbus_hash_uau (void);

GType tp_type_dbus_hash_s_28ubba_7bss_7d_29 (void);

GType tp_type_dbus_hash_us (void);

GType tp_type_dbus_hash_sv (void);

GType tp_type_dbus_hash_ss (void);

GType tp_type_dbus_hash_ua_28a_7bsv_7das_29 (void);

GType tp_type_dbus_hash_s_28ubb_29 (void);

/**
 * TP_STRUCT_TYPE_PARAM_SPEC:

 * 
	A struct representing an allowed parameter, as returned
        by GetParameters on the ConnectionManager interface.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(susv)</literal>.
 *
 * Member 0 (D-Bus type <literal>s</literal>,
 * named <literal>Name</literal>):
 * A string parameter name
 *
 * Member 1 (D-Bus type <literal>u</literal>,
 * type <literal>Conn_Mgr_Param_Flags</literal>,
 * named <literal>Flags</literal>):
 * A bitwise OR of the parameter flags
 *
 * Member 2 (D-Bus type <literal>s</literal>,
 * type <literal>DBus_Signature</literal>,
 * named <literal>Signature</literal>):
 * A string containing the D-Bus type signature           for this parameter
 *
 * Member 3 (D-Bus type <literal>v</literal>,
 * named <literal>Default_Value</literal>):
 * The default value (if the Has_Default flag is not           present, there is no default and this takes some dummy value,           which SHOULD be of the appropriate D-Bus type)
 *
 */
#define TP_STRUCT_TYPE_PARAM_SPEC (tp_type_dbus_struct_susv ())

/**
 * TP_ARRAY_TYPE_PARAM_SPEC_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_PARAM_SPEC.
 */
#define TP_ARRAY_TYPE_PARAM_SPEC_LIST (tp_type_dbus_array_susv ())

/**
 * TP_STRUCT_TYPE_CHANNEL_INFO:

 * 
	A struct representing a channel, as returned by
        ListChannels on the Connection interface.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(osuu)</literal>.
 *
 * Member 0 (D-Bus type <literal>o</literal>,
 * named <literal>Channel</literal>):
 * The object path of the channel, which is on the           same bus name as the connection
 *
 * Member 1 (D-Bus type <literal>s</literal>,
 * type <literal>DBus_Interface</literal>,
 * named <literal>Channel_Type</literal>):
 * The channel&apos;s type
 *
 * Member 2 (D-Bus type <literal>u</literal>,
 * type <literal>Handle_Type</literal>,
 * named <literal>Handle_Type</literal>):
 * The type of the handle that the channel communicates           with, or Handle_Type_None if there is no associated           handle
 *
 * Member 3 (D-Bus type <literal>u</literal>,
 * type <literal>Handle</literal>,
 * named <literal>Handle</literal>):
 * The handle that the channel communicates with,           or 0 if there is no associated handle
 *
 */
#define TP_STRUCT_TYPE_CHANNEL_INFO (tp_type_dbus_struct_osuu ())

/**
 * TP_ARRAY_TYPE_CHANNEL_INFO_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_CHANNEL_INFO.
 */
#define TP_ARRAY_TYPE_CHANNEL_INFO_LIST (tp_type_dbus_array_osuu ())

/**
 * TP_STRUCT_TYPE_ALIAS_PAIR:

 * 
	
        A pair (contact handle, alias) as seen in the
        
	&lt;tp:member-ref&gt;
		AliasesChanged
	&lt;/tp:member-ref&gt;
	 signal.
      

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(us)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Handle</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>s</literal>,
 * named <literal>Alias</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_ALIAS_PAIR (tp_type_dbus_struct_us ())

/**
 * TP_ARRAY_TYPE_ALIAS_PAIR_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_ALIAS_PAIR.
 */
#define TP_ARRAY_TYPE_ALIAS_PAIR_LIST (tp_type_dbus_array_us ())

/**
 * TP_STRUCT_TYPE_CAPABILITY_PAIR:

 * 
	A pair (channel type, type-specific flags) as passed to
        
	&lt;tp:member-ref&gt;
		AdvertiseCapabilities
	&lt;/tp:member-ref&gt;
	 on the
        Capabilities interface.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(su)</literal>.
 *
 * Member 0 (D-Bus type <literal>s</literal>,
 * type <literal>DBus_Interface</literal>,
 * named <literal>Channel_Type</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>u</literal>,
 * named <literal>Type_Specific_Flags</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_CAPABILITY_PAIR (tp_type_dbus_struct_su ())

/**
 * TP_ARRAY_TYPE_CAPABILITY_PAIR_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_CAPABILITY_PAIR.
 */
#define TP_ARRAY_TYPE_CAPABILITY_PAIR_LIST (tp_type_dbus_array_su ())

/**
 * TP_STRUCT_TYPE_CONTACT_CAPABILITY:

 * 
	A struct (contact handle, channel type, generic flags,
        type-specific flags) representing a capability posessed by a contact,
        as returned by 
	&lt;tp:member-ref&gt;
		GetCapabilities
	&lt;/tp:member-ref&gt;
	 on the
        Capabilities interface.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(usuu)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Handle</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>s</literal>,
 * type <literal>DBus_Interface</literal>,
 * named <literal>Channel_Type</literal>):
 * (Undocumented)
 *
 * Member 2 (D-Bus type <literal>u</literal>,
 * type <literal>Connection_Capability_Flags</literal>,
 * named <literal>Generic_Flags</literal>):
 * (Undocumented)
 *
 * Member 3 (D-Bus type <literal>u</literal>,
 * named <literal>Type_Specific_Flags</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_CONTACT_CAPABILITY (tp_type_dbus_struct_usuu ())

/**
 * TP_ARRAY_TYPE_CONTACT_CAPABILITY_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_CONTACT_CAPABILITY.
 */
#define TP_ARRAY_TYPE_CONTACT_CAPABILITY_LIST (tp_type_dbus_array_usuu ())

/**
 * TP_STRUCT_TYPE_CAPABILITY_CHANGE:

 * 
	A struct (contact handle, channel type, old generic flags,
        new generic flags, old type-specific flags, new type-specific flags)
        representing a change to one of a contact&apos;s capabilities, as seen in the
        
	&lt;tp:member-ref&gt;
		CapabilitiesChanged
	&lt;/tp:member-ref&gt;
	 signal on the
        Capabilities interface.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(usuuuu)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Handle</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>s</literal>,
 * type <literal>DBus_Interface</literal>,
 * named <literal>Channel_Type</literal>):
 * (Undocumented)
 *
 * Member 2 (D-Bus type <literal>u</literal>,
 * type <literal>Connection_Capability_Flags</literal>,
 * named <literal>Old_Generic_Flags</literal>):
 * (Undocumented)
 *
 * Member 3 (D-Bus type <literal>u</literal>,
 * type <literal>Connection_Capability_Flags</literal>,
 * named <literal>New_Generic_Flags</literal>):
 * (Undocumented)
 *
 * Member 4 (D-Bus type <literal>u</literal>,
 * named <literal>Old_Type_Specific_Flags</literal>):
 * (Undocumented)
 *
 * Member 5 (D-Bus type <literal>u</literal>,
 * named <literal>New_Type_Specific_Flags</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_CAPABILITY_CHANGE (tp_type_dbus_struct_usuuuu ())

/**
 * TP_ARRAY_TYPE_CAPABILITY_CHANGE_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_CAPABILITY_CHANGE.
 */
#define TP_ARRAY_TYPE_CAPABILITY_CHANGE_LIST (tp_type_dbus_array_usuuuu ())

/**
 * TP_STRUCT_TYPE_HANDLER_CAPABILITIES:

 * 
	
        A structure representing the capabilities of a single client.
      

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(saa{sv}as)</literal>.
 *
 * Member 0 (D-Bus type <literal>s</literal>,
 * type <literal>DBus_Well_Known_Name</literal>,
 * named <literal>Well_Known_Name</literal>):
 * For implementations of the &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;Client&lt;/tp:dbus-ref&gt;           interface, the well-known bus name name of the client; for any other           process, any other reversed domain name that uniquely identifies it.
 *
 * Member 1 (D-Bus type <literal>aa{sv}</literal>,
 * type <literal>String_Variant_Map[]</literal>,
 * named <literal>Channel_Classes</literal>):
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of channel classes that can be handled by this client.           This will usually be a copy of the client&apos;s &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Handler&quot;&gt;HandlerChannelFilter&lt;/tp:dbus-ref&gt;           property.
 *
 * Member 2 (D-Bus type <literal>as</literal>,
 * type <literal>Handler_Capability_Token[]</literal>,
 * named <literal>Capabilities</literal>):
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           An array of client capabilities supported by this client, to be           used by the connection manager to determine what capabilities to           advertise. This will usually be a copy of the client&apos;s &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Client.Handler&quot;&gt;Capabilities&lt;/tp:dbus-ref&gt;           property.
 *
 */
#define TP_STRUCT_TYPE_HANDLER_CAPABILITIES (tp_type_dbus_struct_saa_7bsv_7das ())

/**
 * TP_ARRAY_TYPE_HANDLER_CAPABILITIES_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_HANDLER_CAPABILITIES.
 */
#define TP_ARRAY_TYPE_HANDLER_CAPABILITIES_LIST (tp_type_dbus_array_saa_7bsv_7das ())

/**
 * TP_STRUCT_TYPE_SIMPLE_PRESENCE:

 * 
	
        A struct representing the presence of a contact.
      

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(uss)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Connection_Presence_Type</literal>,
 * named <literal>Type</literal>):
 * The presence type, e.g. Connection_Presence_Type_Away.
 *
 * Member 1 (D-Bus type <literal>s</literal>,
 * named <literal>Status</literal>):
 * The string identifier of the status, e.g. &amp;quot;brb&amp;quot;, as defined in the           &lt;tp:member-ref&gt;Statuses&lt;/tp:member-ref&gt; property.
 *
 * Member 2 (D-Bus type <literal>s</literal>,
 * named <literal>Status_Message</literal>):
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The user-defined status message, e.g. &amp;quot;Back soon!&amp;quot;.&lt;/p&gt;            &lt;p&gt;Clients SHOULD set the status message for the local             user to the empty string, unless the user has actually provided             a specific message (i.e. one that conveys more information than the             Status).&lt;/p&gt;            &lt;p&gt;User interfaces SHOULD regard an empty status message as unset,             and MAY replace it with a localized string corresponding to the             Status or Type.&lt;/p&gt;            &lt;tp:rationale&gt;             Use case: Daf sets his status in Empathy by choosing the Welsh             translation of &amp;quot;Available&amp;quot; from a menu.             It is more informative for his English-speaking colleagues             to see the English translation of &amp;quot;Available&amp;quot; (as localized             by their own clients) than to see &amp;quot;Ar Gael&amp;quot; (which they don&apos;t             understand anyway).           &lt;/tp:rationale&gt;
 *
 */
#define TP_STRUCT_TYPE_SIMPLE_PRESENCE (tp_type_dbus_struct_uss ())

/**
 * TP_STRUCT_TYPE_SIMPLE_STATUS_SPEC:

 * 
	
        A struct containing information about a status.
      

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(ubb)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Connection_Presence_Type</literal>,
 * named <literal>Type</literal>):
 * The type of a presence. This SHOULD NOT be used as a way to set           statuses that the client does not recognise (as explained in           &lt;tp:member-ref&gt;SetPresence&lt;/tp:member-ref&gt;), but MAY be used to check           that the client&apos;s assumptions about a particular status name           match the connection manager&apos;s.
 *
 * Member 1 (D-Bus type <literal>b</literal>,
 * named <literal>May_Set_On_Self</literal>):
 * If true, the user can set this status on themselves using           &lt;tp:member-ref&gt;SetPresence&lt;/tp:member-ref&gt;.
 *
 * Member 2 (D-Bus type <literal>b</literal>,
 * named <literal>Can_Have_Message</literal>):
 * If true, a non-empty message can be set for this status. Otherwise,           the empty string is the only acceptable message.            &lt;tp:rationale&gt;             On IRC you can be Away with a status message, but if you are             available you cannot set a status message.           &lt;/tp:rationale&gt;
 *
 */
#define TP_STRUCT_TYPE_SIMPLE_STATUS_SPEC (tp_type_dbus_struct_ubb ())

/**
 * TP_STRUCT_TYPE_RICH_PRESENCE_ACCESS_CONTROL:

 * 
	
        An access control mode for extended presence items like geolocation.
        This type isn&apos;t actually used by the SimplePresence interface, but
        it&apos;s included here so it can be referenced by rich presence interfaces
        such as 
	&lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Connection.Interface&quot;&gt;
		Location
	&lt;/tp:dbus-ref&gt;
	.
      

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(uv)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Rich_Presence_Access_Control_Type</literal>,
 * named <literal>Type</literal>):
 * The type of access control to apply.
 *
 * Member 1 (D-Bus type <literal>v</literal>,
 * named <literal>Detail</literal>):
 * Any additional information required by the Type. The required           type and semantics are defined for each           &lt;tp:type&gt;Rich_Presence_Access_Control_Type&lt;/tp:type&gt;.
 *
 */
#define TP_STRUCT_TYPE_RICH_PRESENCE_ACCESS_CONTROL (tp_type_dbus_struct_uv ())

/**
 * TP_STRUCT_TYPE_LAST_ACTIVITY_AND_STATUSES:

 * 
	Structure representing a contact&apos;s presence, containing
        a last-activity time (deprecated) and a Multiple_Status_Map.
      

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(ua{sa{sv}})</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Unix_Timestamp</literal>,
 * named <literal>Last_Activity</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>a{sa{sv}}</literal>,
 * type <literal>Multiple_Status_Map</literal>,
 * named <literal>Statuses</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_LAST_ACTIVITY_AND_STATUSES (tp_type_dbus_struct_ua_7bsa_7bsv_7d_7d ())

/**
 * TP_STRUCT_TYPE_STATUS_SPEC:

 * (Undocumented)
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(ubba{ss})</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Connection_Presence_Type</literal>,
 * named <literal>Type</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>b</literal>,
 * named <literal>May_Set_On_Self</literal>):
 * (Undocumented)
 *
 * Member 2 (D-Bus type <literal>b</literal>,
 * named <literal>Exclusive</literal>):
 * (Undocumented)
 *
 * Member 3 (D-Bus type <literal>a{ss}</literal>,
 * type <literal>String_String_Map</literal>,
 * named <literal>Parameter_Types</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_STATUS_SPEC (tp_type_dbus_struct_ubba_7bss_7d ())

/**
 * TP_STRUCT_TYPE_CHANNEL_DETAILS:

 * 
	
        Enough details of a channel that clients can work out how to dispatch
        or handle it.
      

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(oa{sv})</literal>.
 *
 * Member 0 (D-Bus type <literal>o</literal>,
 * named <literal>Channel</literal>):
 * The object path of the channel.
 *
 * Member 1 (D-Bus type <literal>a{sv}</literal>,
 * type <literal>Qualified_Property_Value_Map</literal>,
 * named <literal>Properties</literal>):
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Properties of the channel.&lt;/p&gt;            &lt;p&gt;Connection managers MUST NOT include properties in this mapping             if their values can change. Clients MUST ignore properties             that appear in this mapping if their values can change.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;If properties that could change were included, the following               race condition would be likely to exist in some cases:&lt;/p&gt;              &lt;ul&gt;               &lt;li&gt;NewChannels or Get(&amp;quot;Channels&amp;quot;) includes a property P with                 value V1&lt;/li&gt;               &lt;li&gt;Client creates a proxy object for the channel&lt;/li&gt;               &lt;li&gt;The value of P changes to V2&lt;/li&gt;               &lt;li&gt;Client connects to PChanged signal&lt;/li&gt;               &lt;li&gt;Client should call Get(&amp;quot;P&amp;quot;) or GetAll here, to avoid the                 race, but client&apos;s author has forgotten to do so&lt;/li&gt;               &lt;li&gt;Proxy object thinks P == V1, but actually P == V2&lt;/li&gt;             &lt;/ul&gt;              &lt;p&gt;We&apos;ve taken the opportunity to make the API encourage the               client author to get it right. Where possible, we intend that               properties whose value will be used in channel dispatching               or other &amp;quot;early&amp;quot; processing will be defined so that they are               immutable (can never change).&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;Each dictionary MUST contain the keys             &lt;tp:dbus-ref&gt;org.freedesktop.Telepathy.Channel.ChannelType&lt;/tp:dbus-ref&gt;,             &lt;tp:dbus-ref&gt;org.freedesktop.Telepathy.Channel.TargetHandleType&lt;/tp:dbus-ref&gt;,             &lt;tp:dbus-ref&gt;org.freedesktop.Telepathy.Channel.TargetHandle&lt;/tp:dbus-ref&gt;,             &lt;tp:dbus-ref&gt;org.freedesktop.Telepathy.Channel.TargetID&lt;/tp:dbus-ref&gt;             and             &lt;tp:dbus-ref&gt;org.freedesktop.Telepathy.Channel.Requested&lt;/tp:dbus-ref&gt;.           &lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;We expect these to be crucial to the channel-dispatching               process.&lt;/p&gt;           &lt;/tp:rationale&gt;
 *
 */
#define TP_STRUCT_TYPE_CHANNEL_DETAILS (tp_type_dbus_struct_oa_7bsv_7d ())

/**
 * TP_ARRAY_TYPE_CHANNEL_DETAILS_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_CHANNEL_DETAILS.
 */
#define TP_ARRAY_TYPE_CHANNEL_DETAILS_LIST (tp_type_dbus_array_oa_7bsv_7d ())

/**
 * TP_STRUCT_TYPE_REQUESTABLE_CHANNEL_CLASS:

 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;
	
        
	&lt;p&gt;
		Structure representing a class of channels that can be requested,
          identified by a set of properties that identify that class of
          channel.
	&lt;/p&gt;
	

        
	&lt;tp:rationale&gt;
		
          
		&lt;p&gt;
			This will often just be the channel type and the handle type,
            but can include other properties of the channel - for instance,
            encrypted channels might require properties that
            unencrypted channels do not, like an encryption key.
		&lt;/p&gt;
		
        
	&lt;/tp:rationale&gt;
	

        
	&lt;p&gt;
		In some cases, these classes of channel may overlap, in the sense
          that one class fixes all the properties that another class does,
          plus some more properties.
	&lt;/p&gt;
	

        
	&lt;tp:rationale&gt;
		
          
		&lt;p&gt;
			For older clients to still be able to understand how to request
            channels in the presence of a hypothetical &amp;quot;encryption&amp;quot; interface,
            we&apos;d need to represent it like this:
		&lt;/p&gt;
		

          
		&lt;ul&gt;
			
            
			&lt;li&gt;
				class 1: ChannelType = Text, TargetHandleType = CONTACT
			&lt;/li&gt;
			
            
			&lt;li&gt;
				class 2: Channel.ChannelType = Text,
              Channel.TargetHandleType = CONTACT,
              Encryption.Encrypted = TRUE
			&lt;/li&gt;
			
          
		&lt;/ul&gt;
		
        
	&lt;/tp:rationale&gt;
	
      

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(a{sv}as)</literal>.
 *
 * Member 0 (D-Bus type <literal>a{sv}</literal>,
 * type <literal>Channel_Class</literal>,
 * named <literal>Fixed_Properties</literal>):
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;The property values that identify this requestable channel class.             These properties MUST be included in requests for a channel of this             class, and MUST take these values.&lt;/p&gt;            &lt;p&gt;Clients that do not understand the semantics of all the             Fixed_Properties MUST NOT request channels of this class, since             they would be unable to avoid making an incorrect request.&lt;/p&gt;            &lt;p&gt;This implies that connection managers wishing to make channels             available to old or minimal clients SHOULD have a channel class             with the minimum number of Fixed_Properties, and MAY additionally             have channel classes with extra Fixed_Properties.&lt;/p&gt;
 *
 * Member 1 (D-Bus type <literal>as</literal>,
 * type <literal>DBus_Qualified_Member[]</literal>,
 * named <literal>Allowed_Properties</literal>):
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Properties that MAY be set when requesting a channel of this             channel type and handle type.&lt;/p&gt;            &lt;p&gt;This array MUST NOT include properties that are in the             Fixed_Properties mapping.&lt;/p&gt;            &lt;p&gt;Properties in this array may either be required or optional,             according to their documented semantics.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;For instance, if               TargetHandleType takes a value that is not Handle_Type_None,               one or the other of TargetHandle and TargetID is required.               Clients are expected to understand the documented relationship               between the properties, so we do not have separate arrays               of required and optional properties.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;If this array contains the             &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy.Channel.FUTURE&quot;&gt;Bundle&lt;/tp:dbus-ref&gt;             property, then this class of channel can be combined with other             channels with that property in a request, or added to an existing             bundle. If not, this signifies that the connection manager is             unable to mark channels of this class as part of a bundle - this             means that to the remote contact they are likely to be             indistinguishable from channels requested separately.&lt;/p&gt;
 *
 */
#define TP_STRUCT_TYPE_REQUESTABLE_CHANNEL_CLASS (tp_type_dbus_struct_a_7bsv_7das ())

/**
 * TP_ARRAY_TYPE_REQUESTABLE_CHANNEL_CLASS_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_REQUESTABLE_CHANNEL_CLASS.
 */
#define TP_ARRAY_TYPE_REQUESTABLE_CHANNEL_CLASS_LIST (tp_type_dbus_array_a_7bsv_7das ())

/**
 * TP_STRUCT_TYPE_MEDIA_STREAM_INFO:

 * (Undocumented)
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(uuuuuu)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Stream_ID</literal>,
 * named <literal>Identifier</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Contact</literal>):
 * (Undocumented)
 *
 * Member 2 (D-Bus type <literal>u</literal>,
 * type <literal>Media_Stream_Type</literal>,
 * named <literal>Type</literal>):
 * (Undocumented)
 *
 * Member 3 (D-Bus type <literal>u</literal>,
 * type <literal>Media_Stream_State</literal>,
 * named <literal>State</literal>):
 * (Undocumented)
 *
 * Member 4 (D-Bus type <literal>u</literal>,
 * type <literal>Media_Stream_Direction</literal>,
 * named <literal>Direction</literal>):
 * (Undocumented)
 *
 * Member 5 (D-Bus type <literal>u</literal>,
 * type <literal>Media_Stream_Pending_Send</literal>,
 * named <literal>Pending_Send_Flags</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_MEDIA_STREAM_INFO (tp_type_dbus_struct_uuuuuu ())

/**
 * TP_ARRAY_TYPE_MEDIA_STREAM_INFO_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_MEDIA_STREAM_INFO.
 */
#define TP_ARRAY_TYPE_MEDIA_STREAM_INFO_LIST (tp_type_dbus_array_uuuuuu ())

/**
 * TP_STRUCT_TYPE_ROOM_INFO:

 * (Undocumented)
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(usa{sv})</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Room_Handle</literal>,
 * named <literal>Handle</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>s</literal>,
 * type <literal>DBus_Interface</literal>,
 * named <literal>Channel_Type</literal>):
 * (Undocumented)
 *
 * Member 2 (D-Bus type <literal>a{sv}</literal>,
 * type <literal>String_Variant_Map</literal>,
 * named <literal>Info</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_ROOM_INFO (tp_type_dbus_struct_usa_7bsv_7d ())

/**
 * TP_ARRAY_TYPE_ROOM_INFO_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_ROOM_INFO.
 */
#define TP_ARRAY_TYPE_ROOM_INFO_LIST (tp_type_dbus_array_usa_7bsv_7d ())

/**
 * TP_STRUCT_TYPE_PENDING_TEXT_MESSAGE:

 * 
	A struct (message ID, timestamp in seconds since
        1970-01-01 00:00 UTC, sender&apos;s handle, message type, flags, text)
        representing a pending text message, as returned by
        
	&lt;tp:member-ref&gt;
		ListPendingMessages
	&lt;/tp:member-ref&gt;
	.  The arguments of
        the 
	&lt;tp:member-ref&gt;
		Received
	&lt;/tp:member-ref&gt;
	 signal also match this
        struct&apos;s signature.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(uuuuus)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Message_ID</literal>,
 * named <literal>Identifier</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>u</literal>,
 * type <literal>Unix_Timestamp</literal>,
 * named <literal>Unix_Timestamp</literal>):
 * (Undocumented)
 *
 * Member 2 (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Sender</literal>):
 * (Undocumented)
 *
 * Member 3 (D-Bus type <literal>u</literal>,
 * type <literal>Channel_Text_Message_Type</literal>,
 * named <literal>Message_Type</literal>):
 * (Undocumented)
 *
 * Member 4 (D-Bus type <literal>u</literal>,
 * type <literal>Channel_Text_Message_Flags</literal>,
 * named <literal>Flags</literal>):
 * (Undocumented)
 *
 * Member 5 (D-Bus type <literal>s</literal>,
 * named <literal>Text</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_PENDING_TEXT_MESSAGE (tp_type_dbus_struct_uuuuus ())

/**
 * TP_ARRAY_TYPE_PENDING_TEXT_MESSAGE_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_PENDING_TEXT_MESSAGE.
 */
#define TP_ARRAY_TYPE_PENDING_TEXT_MESSAGE_LIST (tp_type_dbus_array_uuuuus ())

/**
 * TP_STRUCT_TYPE_TUBE_INFO:

 * 
	A struct (tube ID, initiator handle, tube type,
        service name, parameters, state) representing a tube, as returned
        by ListTubes on the Tubes channel type.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(uuusa{sv}u)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Tube_ID</literal>,
 * named <literal>Identifier</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Initiator</literal>):
 * (Undocumented)
 *
 * Member 2 (D-Bus type <literal>u</literal>,
 * type <literal>Tube_Type</literal>,
 * named <literal>Type</literal>):
 * (Undocumented)
 *
 * Member 3 (D-Bus type <literal>s</literal>,
 * named <literal>Service</literal>):
 * (Undocumented)
 *
 * Member 4 (D-Bus type <literal>a{sv}</literal>,
 * type <literal>String_Variant_Map</literal>,
 * named <literal>Parameters</literal>):
 * (Undocumented)
 *
 * Member 5 (D-Bus type <literal>u</literal>,
 * type <literal>Tube_State</literal>,
 * named <literal>State</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_TUBE_INFO (tp_type_dbus_struct_uuusa_7bsv_7du ())

/**
 * TP_ARRAY_TYPE_TUBE_INFO_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_TUBE_INFO.
 */
#define TP_ARRAY_TYPE_TUBE_INFO_LIST (tp_type_dbus_array_uuusa_7bsv_7du ())

/**
 * TP_STRUCT_TYPE_DBUS_TUBE_MEMBER:

 * 
	Represents a participant in a multi-user D-Bus tube, as
        returned by 
	&lt;tp:member-ref&gt;
		GetDBusNames
	&lt;/tp:member-ref&gt;
	 and seen in the
        
	&lt;tp:member-ref&gt;
		DBusNamesChanged
	&lt;/tp:member-ref&gt;
	 signal.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(us)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Handle</literal>):
 * The handle of a participant in this D-Bus tube.
 *
 * Member 1 (D-Bus type <literal>s</literal>,
 * type <literal>DBus_Unique_Name</literal>,
 * named <literal>Unique_Name</literal>):
 * That participant&apos;s unique name.
 *
 */
#define TP_STRUCT_TYPE_DBUS_TUBE_MEMBER (tp_type_dbus_struct_us ())

/**
 * TP_ARRAY_TYPE_DBUS_TUBE_MEMBER_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_DBUS_TUBE_MEMBER.
 */
#define TP_ARRAY_TYPE_DBUS_TUBE_MEMBER_LIST (tp_type_dbus_array_us ())

/**
 * TP_STRUCT_TYPE_LOCAL_PENDING_INFO:

 * 
	A structure representing a contact whose attempt to
        join a group is to be confirmed by the local user using
        
	&lt;tp:member-ref&gt;
		AddMembers
	&lt;/tp:member-ref&gt;
	.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(uuus)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>To_Be_Added</literal>):
 * The contact to be added to the group
 *
 * Member 1 (D-Bus type <literal>u</literal>,
 * type <literal>Contact_Handle</literal>,
 * named <literal>Actor</literal>):
 * The contact requesting or causing the change
 *
 * Member 2 (D-Bus type <literal>u</literal>,
 * type <literal>Channel_Group_Change_Reason</literal>,
 * named <literal>Reason</literal>):
 * The reason for the change
 *
 * Member 3 (D-Bus type <literal>s</literal>,
 * named <literal>Message</literal>):
 * A human-readable message from the Actor, or an empty string           if there is no message
 *
 */
#define TP_STRUCT_TYPE_LOCAL_PENDING_INFO (tp_type_dbus_struct_uuus ())

/**
 * TP_ARRAY_TYPE_LOCAL_PENDING_INFO_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_LOCAL_PENDING_INFO.
 */
#define TP_ARRAY_TYPE_LOCAL_PENDING_INFO_LIST (tp_type_dbus_array_uuus ())

/**
 * TP_STRUCT_TYPE_MEDIA_SESSION_HANDLER_INFO:

 * 
	A struct representing a active session handler.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(os)</literal>.
 *
 * Member 0 (D-Bus type <literal>o</literal>,
 * named <literal>Session_Handler</literal>):
 * The object path of the session handler, which is on the           same bus name as the channel.
 *
 * Member 1 (D-Bus type <literal>s</literal>,
 * type <literal>Media_Session_Type</literal>,
 * named <literal>Media_Session_Type</literal>):
 * The media session&apos;s type
 *
 */
#define TP_STRUCT_TYPE_MEDIA_SESSION_HANDLER_INFO (tp_type_dbus_struct_os ())

/**
 * TP_ARRAY_TYPE_MEDIA_SESSION_HANDLER_INFO_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_MEDIA_SESSION_HANDLER_INFO.
 */
#define TP_ARRAY_TYPE_MEDIA_SESSION_HANDLER_INFO_LIST (tp_type_dbus_array_os ())

/**
 * TP_STRUCT_TYPE_MEDIA_STREAM_HANDLER_CANDIDATE:

 * (Undocumented)
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(sa(usuussduss))</literal>.
 *
 * Member 0 (D-Bus type <literal>s</literal>,
 * named <literal>Name</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>a(usuussduss)</literal>,
 * type <literal>Media_Stream_Handler_Transport[]</literal>,
 * named <literal>Transports</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_MEDIA_STREAM_HANDLER_CANDIDATE (tp_type_dbus_struct_sa_28usuussduss_29 ())

/**
 * TP_ARRAY_TYPE_MEDIA_STREAM_HANDLER_CANDIDATE_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_MEDIA_STREAM_HANDLER_CANDIDATE.
 */
#define TP_ARRAY_TYPE_MEDIA_STREAM_HANDLER_CANDIDATE_LIST (tp_type_dbus_array_sa_28usuussduss_29 ())

/**
 * TP_STRUCT_TYPE_MEDIA_STREAM_HANDLER_TRANSPORT:

 * (Undocumented)
 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(usuussduss)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * named <literal>Component_Number</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>s</literal>,
 * named <literal>IP_Address</literal>):
 * (Undocumented)
 *
 * Member 2 (D-Bus type <literal>u</literal>,
 * named <literal>Port</literal>):
 * (Undocumented)
 *
 * Member 3 (D-Bus type <literal>u</literal>,
 * type <literal>Media_Stream_Base_Proto</literal>,
 * named <literal>Protocol</literal>):
 * (Undocumented)
 *
 * Member 4 (D-Bus type <literal>s</literal>,
 * named <literal>Subtype</literal>):
 * (Undocumented)
 *
 * Member 5 (D-Bus type <literal>s</literal>,
 * named <literal>Profile</literal>):
 * (Undocumented)
 *
 * Member 6 (D-Bus type <literal>d</literal>,
 * named <literal>Preference_Value</literal>):
 * (Undocumented)
 *
 * Member 7 (D-Bus type <literal>u</literal>,
 * type <literal>Media_Stream_Transport_Type</literal>,
 * named <literal>Transport_Type</literal>):
 * (Undocumented)
 *
 * Member 8 (D-Bus type <literal>s</literal>,
 * named <literal>Username</literal>):
 * (Undocumented)
 *
 * Member 9 (D-Bus type <literal>s</literal>,
 * named <literal>Password</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_MEDIA_STREAM_HANDLER_TRANSPORT (tp_type_dbus_struct_usuussduss ())

/**
 * TP_ARRAY_TYPE_MEDIA_STREAM_HANDLER_TRANSPORT_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_MEDIA_STREAM_HANDLER_TRANSPORT.
 */
#define TP_ARRAY_TYPE_MEDIA_STREAM_HANDLER_TRANSPORT_LIST (tp_type_dbus_array_usuussduss ())

/**
 * TP_STRUCT_TYPE_MEDIA_STREAM_HANDLER_CODEC:

 * 
	
        Information about a codec supported by a client or a peer&apos;s client.
      

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(usuuua{ss})</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * named <literal>Codec_ID</literal>):
 * The codec&apos;s payload identifier, as per RFC 3551 (static or dynamic)
 *
 * Member 1 (D-Bus type <literal>s</literal>,
 * named <literal>Name</literal>):
 * The codec&apos;s name
 *
 * Member 2 (D-Bus type <literal>u</literal>,
 * type <literal>Media_Stream_Type</literal>,
 * named <literal>Media_Type</literal>):
 * Type of stream this codec supports
 *
 * Member 3 (D-Bus type <literal>u</literal>,
 * named <literal>Clock_Rate</literal>):
 * Sampling frequency in Hertz
 *
 * Member 4 (D-Bus type <literal>u</literal>,
 * named <literal>Number_Of_Channels</literal>):
 * Number of supported channels
 *
 * Member 5 (D-Bus type <literal>a{ss}</literal>,
 * type <literal>String_String_Map</literal>,
 * named <literal>Parameters</literal>):
 * Codec-specific optional parameters
 *
 */
#define TP_STRUCT_TYPE_MEDIA_STREAM_HANDLER_CODEC (tp_type_dbus_struct_usuuua_7bss_7d ())

/**
 * TP_ARRAY_TYPE_MEDIA_STREAM_HANDLER_CODEC_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_MEDIA_STREAM_HANDLER_CODEC.
 */
#define TP_ARRAY_TYPE_MEDIA_STREAM_HANDLER_CODEC_LIST (tp_type_dbus_array_usuuua_7bss_7d ())

/**
 * TP_STRUCT_TYPE_PROPERTY_SPEC:

 * 
	A struct (property ID, property name, D-Bus signature,
        flags) representing a property, as returned by ListProperties on the
        Properties interface.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(ussu)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * named <literal>Property_ID</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>s</literal>,
 * named <literal>Name</literal>):
 * (Undocumented)
 *
 * Member 2 (D-Bus type <literal>s</literal>,
 * type <literal>DBus_Signature</literal>,
 * named <literal>Signature</literal>):
 * (Undocumented)
 *
 * Member 3 (D-Bus type <literal>u</literal>,
 * type <literal>Property_Flags</literal>,
 * named <literal>Flags</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_PROPERTY_SPEC (tp_type_dbus_struct_ussu ())

/**
 * TP_ARRAY_TYPE_PROPERTY_SPEC_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_PROPERTY_SPEC.
 */
#define TP_ARRAY_TYPE_PROPERTY_SPEC_LIST (tp_type_dbus_array_ussu ())

/**
 * TP_STRUCT_TYPE_PROPERTY_FLAGS_CHANGE:

 * 
	A struct (property ID, flags) representing a change to
        a property&apos;s flags, as seen in the PropertyFlagsChanged signal on
        the Properties interface.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(uu)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * named <literal>Property_ID</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>u</literal>,
 * named <literal>New_Flags</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_PROPERTY_FLAGS_CHANGE (tp_type_dbus_struct_uu ())

/**
 * TP_ARRAY_TYPE_PROPERTY_FLAGS_CHANGE_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_PROPERTY_FLAGS_CHANGE.
 */
#define TP_ARRAY_TYPE_PROPERTY_FLAGS_CHANGE_LIST (tp_type_dbus_array_uu ())

/**
 * TP_STRUCT_TYPE_PROPERTY_VALUE:

 * 
	A struct (property ID, value) representing a
        property&apos;s value, as seen in the PropertiesChanged signal on
        the Properties interface, returned by the GetProperties method
        and passed to the SetProperties method.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(uv)</literal>.
 *
 * Member 0 (D-Bus type <literal>u</literal>,
 * type <literal>Property_ID</literal>,
 * named <literal>Identifier</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>v</literal>,
 * named <literal>Value</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_PROPERTY_VALUE (tp_type_dbus_struct_uv ())

/**
 * TP_ARRAY_TYPE_PROPERTY_VALUE_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_PROPERTY_VALUE.
 */
#define TP_ARRAY_TYPE_PROPERTY_VALUE_LIST (tp_type_dbus_array_uv ())

/**
 * TP_STRUCT_TYPE_AVATAR:

 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;
	
        
	&lt;p&gt;
		A struct containing avatar data marked with its MIME type.
	&lt;/p&gt;
	
      

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(ays)</literal>.
 *
 * Member 0 (D-Bus type <literal>ay</literal>,
 * named <literal>Avatar_Data</literal>):
 * (Undocumented)
 *
 * Member 1 (D-Bus type <literal>s</literal>,
 * named <literal>MIME_Type</literal>):
 * (Undocumented)
 *
 */
#define TP_STRUCT_TYPE_AVATAR (tp_type_dbus_struct_ays ())

/**
 * TP_STRUCT_TYPE_DISPATCH_OPERATION_DETAILS:

 * 
	
        Details of a channel dispatch operation.
      

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(oa{sv})</literal>.
 *
 * Member 0 (D-Bus type <literal>o</literal>,
 * named <literal>Channel_Dispatch_Operation</literal>):
 * The object path of the           &lt;tp:dbus-ref namespace=&quot;org.freedesktop.Telepathy&quot;&gt;ChannelDispatchOperation&lt;/tp:dbus-ref&gt;.
 *
 * Member 1 (D-Bus type <literal>a{sv}</literal>,
 * type <literal>Qualified_Property_Value_Map</literal>,
 * named <literal>Properties</literal>):
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Properties of the channel dispatch operation.&lt;/p&gt;            &lt;p&gt;Connection managers MUST NOT include properties in this mapping             if their values can change. Clients MUST ignore properties             that appear in this mapping if their values can change.&lt;/p&gt;            &lt;tp:rationale&gt;             &lt;p&gt;The rationale is the same as for               &lt;tp:type-ref&gt;Channel_Details&lt;/tp:type-ref&gt;.&lt;/p&gt;           &lt;/tp:rationale&gt;            &lt;p&gt;Each dictionary MUST contain at least the following keys:&lt;/p&gt;           &lt;ul&gt;             &lt;li&gt;&lt;tp:dbus-ref&gt;org.freedesktop.Telepathy.ChannelDispatchOperation.Interfaces&lt;/tp:dbus-ref&gt;&lt;/li&gt;             &lt;li&gt;&lt;tp:dbus-ref&gt;org.freedesktop.Telepathy.ChannelDispatchOperation.Connection&lt;/tp:dbus-ref&gt;&lt;/li&gt;             &lt;li&gt;&lt;tp:dbus-ref&gt;org.freedesktop.Telepathy.ChannelDispatchOperation.Account&lt;/tp:dbus-ref&gt;&lt;/li&gt;             &lt;li&gt;&lt;tp:dbus-ref&gt;org.freedesktop.Telepathy.ChannelDispatchOperation.PossibleHandlers&lt;/tp:dbus-ref&gt;&lt;/li&gt;           &lt;/ul&gt;
 *
 */
#define TP_STRUCT_TYPE_DISPATCH_OPERATION_DETAILS (tp_type_dbus_struct_oa_7bsv_7d ())

/**
 * TP_ARRAY_TYPE_DISPATCH_OPERATION_DETAILS_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_DISPATCH_OPERATION_DETAILS.
 */
#define TP_ARRAY_TYPE_DISPATCH_OPERATION_DETAILS_LIST (tp_type_dbus_array_oa_7bsv_7d ())

/**
 * TP_STRUCT_TYPE_DEBUG_MESSAGE:

 * 
	
        A struct representing a debug message, as returned by
        
	&lt;tp:member-ref&gt;
		GetMessages
	&lt;/tp:member-ref&gt;
	.
      

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(dsus)</literal>.
 *
 * Member 0 (D-Bus type <literal>d</literal>,
 * named <literal>Timestamp</literal>):
 * Timestamp of the debug message. This is a double to allow           more accuracy in the time the message was logged.
 *
 * Member 1 (D-Bus type <literal>s</literal>,
 * named <literal>Domain</literal>):
 * &lt;tp:docstring xmlns=&quot;http://www.w3.org/1999/xhtml&quot;&gt;           &lt;p&gt;Domain of the debug message. This is used to identify           the source of debug messages. For example, debug messages           from a connection manager could have this Domain struct           member be the name of the connection manager, and logs           from any helper library could have the name of the helper           library.&lt;/p&gt;            &lt;p&gt;The domain could also contain a category as to where           the log message originated separated by a forward-slash.           For example, if a debug message was output in a connection           manager called &amp;quot;dummy&amp;quot;, in the file-transfer code, this           Domain struct member might be &lt;tt&gt;dummy/file-transfer&lt;/tt&gt;.&lt;/p&gt;
 *
 * Member 2 (D-Bus type <literal>u</literal>,
 * type <literal>Debug_Level</literal>,
 * named <literal>Level</literal>):
 * Level of the debug message. This states the severity of the           debug message.
 *
 * Member 3 (D-Bus type <literal>s</literal>,
 * named <literal>Message</literal>):
 * The text of the debug message.
 *
 */
#define TP_STRUCT_TYPE_DEBUG_MESSAGE (tp_type_dbus_struct_dsus ())

/**
 * TP_ARRAY_TYPE_DEBUG_MESSAGE_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_DEBUG_MESSAGE.
 */
#define TP_ARRAY_TYPE_DEBUG_MESSAGE_LIST (tp_type_dbus_array_dsus ())

/**
 * TP_STRUCT_TYPE_SOCKET_ADDRESS_IP:

 * 
	An IP address and port.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(sq)</literal>.
 *
 * Member 0 (D-Bus type <literal>s</literal>,
 * named <literal>Address</literal>):
 * Either a dotted-quad IPv4 address literal as for         &lt;tp:type&gt;Socket_Address_IPv4&lt;/tp:type&gt;, or an RFC2373 IPv6 address         as for &lt;tp:type&gt;Socket_Address_IPv6&lt;/tp:type&gt;.
 *
 * Member 1 (D-Bus type <literal>q</literal>,
 * named <literal>Port</literal>):
 * The TCP or UDP port number.
 *
 */
#define TP_STRUCT_TYPE_SOCKET_ADDRESS_IP (tp_type_dbus_struct_sq ())

/**
 * TP_ARRAY_TYPE_SOCKET_ADDRESS_IP_LIST:

 * Expands to a call to a function
 * that returns the #GType of a #GPtrArray
 * of #TP_STRUCT_TYPE_SOCKET_ADDRESS_IP.
 */
#define TP_ARRAY_TYPE_SOCKET_ADDRESS_IP_LIST (tp_type_dbus_array_sq ())

/**
 * TP_STRUCT_TYPE_SOCKET_ADDRESS_IPV4:

 * 
	An IPv4 address and port.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(sq)</literal>.
 *
 * Member 0 (D-Bus type <literal>s</literal>,
 * named <literal>Address</literal>):
 * A dotted-quad IPv4 address literal: four ASCII decimal         numbers, each between 0 and 255 inclusive, e.g.         &amp;quot;192.168.0.1&amp;quot;.
 *
 * Member 1 (D-Bus type <literal>q</literal>,
 * named <literal>Port</literal>):
 * The TCP or UDP port number.
 *
 */
#define TP_STRUCT_TYPE_SOCKET_ADDRESS_IPV4 (tp_type_dbus_struct_sq ())

/**
 * TP_STRUCT_TYPE_SOCKET_ADDRESS_IPV6:

 * 
	An IPv6 address and port.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(sq)</literal>.
 *
 * Member 0 (D-Bus type <literal>s</literal>,
 * named <literal>Address</literal>):
 * An IPv6 address literal as specified by RFC2373         section 2.2, e.g. &amp;quot;2001:DB8::8:800:200C:4171&amp;quot;.
 *
 * Member 1 (D-Bus type <literal>q</literal>,
 * named <literal>Port</literal>):
 * The TCP or UDP port number.
 *
 */
#define TP_STRUCT_TYPE_SOCKET_ADDRESS_IPV6 (tp_type_dbus_struct_sq ())

/**
 * TP_STRUCT_TYPE_SOCKET_NETMASK_IPV4:

 * 
	An IPv4 network or subnet.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(sy)</literal>.
 *
 * Member 0 (D-Bus type <literal>s</literal>,
 * named <literal>Address</literal>):
 * A dotted-quad IPv4 address literal: four ASCII decimal         numbers, each between 0 and 255 inclusive, e.g.         &amp;quot;192.168.0.1&amp;quot;.
 *
 * Member 1 (D-Bus type <literal>y</literal>,
 * named <literal>Prefix_Length</literal>):
 * The number of leading bits of the address that must         match, for this netmask to be considered to match an         address.
 *
 */
#define TP_STRUCT_TYPE_SOCKET_NETMASK_IPV4 (tp_type_dbus_struct_sy ())

/**
 * TP_STRUCT_TYPE_SOCKET_NETMASK_IPV6:

 * 
	An IPv6 network or subnet.

 *
 * This macro expands to a call to a function
 * that returns the #GType of a #GValueArray
 * appropriate for representing a D-Bus struct
 * with signature <literal>(sy)</literal>.
 *
 * Member 0 (D-Bus type <literal>s</literal>,
 * named <literal>Address</literal>):
 * An IPv6 address literal as specified by RFC2373         section 2.2, e.g. &amp;quot;2001:DB8::8:800:200C:4171&amp;quot;.
 *
 * Member 1 (D-Bus type <literal>y</literal>,
 * named <literal>Prefix_Length</literal>):
 * The number of leading bits of the address that must         match, for this netmask to be considered to match an         address.
 *
 */
#define TP_STRUCT_TYPE_SOCKET_NETMASK_IPV6 (tp_type_dbus_struct_sy ())

GType tp_type_dbus_struct_uv (void);

GType tp_type_dbus_struct_uuus (void);

GType tp_type_dbus_struct_dsus (void);

GType tp_type_dbus_struct_usuuua_7bss_7d (void);

GType tp_type_dbus_struct_us (void);

GType tp_type_dbus_struct_susv (void);

GType tp_type_dbus_struct_osuu (void);

GType tp_type_dbus_struct_usuussduss (void);

GType tp_type_dbus_struct_usuu (void);

GType tp_type_dbus_struct_usuuuu (void);

GType tp_type_dbus_struct_uuuuuu (void);

GType tp_type_dbus_struct_uuuuus (void);

GType tp_type_dbus_struct_uss (void);

GType tp_type_dbus_struct_ays (void);

GType tp_type_dbus_struct_saa_7bsv_7das (void);

GType tp_type_dbus_struct_uuusa_7bsv_7du (void);

GType tp_type_dbus_struct_ubb (void);

GType tp_type_dbus_struct_ua_7bsa_7bsv_7d_7d (void);

GType tp_type_dbus_struct_sy (void);

GType tp_type_dbus_struct_sa_28usuussduss_29 (void);

GType tp_type_dbus_struct_uu (void);

GType tp_type_dbus_struct_os (void);

GType tp_type_dbus_struct_sq (void);

GType tp_type_dbus_struct_usa_7bsv_7d (void);

GType tp_type_dbus_struct_su (void);

GType tp_type_dbus_struct_oa_7bsv_7d (void);

GType tp_type_dbus_struct_ussu (void);

GType tp_type_dbus_struct_ubba_7bss_7d (void);

GType tp_type_dbus_struct_a_7bsv_7das (void);

GType tp_type_dbus_array_usa_7bsv_7d (void);

GType tp_type_dbus_array_dsus (void);

GType tp_type_dbus_array_usuuua_7bss_7d (void);

GType tp_type_dbus_array_us (void);

GType tp_type_dbus_array_susv (void);

GType tp_type_dbus_array_osuu (void);

GType tp_type_dbus_array_usuussduss (void);

GType tp_type_dbus_array_usuu (void);

GType tp_type_dbus_array_usuuuu (void);

GType tp_type_dbus_array_uuuuuu (void);

GType tp_type_dbus_array_uuuuus (void);

GType tp_type_dbus_array_saa_7bsv_7das (void);

GType tp_type_dbus_array_uuusa_7bsv_7du (void);

GType tp_type_dbus_array_uuus (void);

GType tp_type_dbus_array_sa_28usuussduss_29 (void);

GType tp_type_dbus_array_uu (void);

GType tp_type_dbus_array_sq (void);

GType tp_type_dbus_array_uv (void);

GType tp_type_dbus_array_su (void);

GType tp_type_dbus_array_oa_7bsv_7d (void);

GType tp_type_dbus_array_ussu (void);

GType tp_type_dbus_array_os (void);

GType tp_type_dbus_array_a_7bsv_7das (void);

GType tp_type_dbus_array_of_a_7bua_28a_7bsv_7das_29_7d (void);

GType tp_type_dbus_array_of_a_7bsv_7d (void);

GType tp_type_dbus_array_of_a_7bss_7d (void);

