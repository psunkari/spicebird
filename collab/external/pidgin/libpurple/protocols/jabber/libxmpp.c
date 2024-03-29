/* purple
 *
 * Purple is the legal property of its developers, whose names are too numerous
 * to list here.  Please refer to the COPYRIGHT file distributed with this
 * source distribution.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
 *
 */

/* libxmpp is the XMPP protocol plugin. It is linked against libjabbercommon,
 * which may be used to support other protocols (Bonjour) which may need to
 * share code.
 */

#include "internal.h"

#include "accountopt.h"
#include "core.h"
#include "debug.h"
#include "version.h"

#include "iq.h"
#include "jabber.h"
#include "chat.h"
#include "disco.h"
#include "message.h"
#include "roster.h"
#include "si.h"
#include "message.h"
#include "presence.h"
#include "google.h"
#include "pep.h"
#include "usertune.h"
#include "caps.h"
#include "data.h"
#include "ibb.h"

static PurplePlugin *my_protocol = NULL;

static PurplePluginProtocolInfo prpl_info =
{
	OPT_PROTO_CHAT_TOPIC | OPT_PROTO_UNIQUE_CHATNAME | OPT_PROTO_MAIL_CHECK |
#ifdef HAVE_CYRUS_SASL
	OPT_PROTO_PASSWORD_OPTIONAL |
#endif
	OPT_PROTO_SLASH_COMMANDS_NATIVE,
	NULL,							/* user_splits */
	NULL,							/* protocol_options */
	{"png", 32, 32, 96, 96, 0, PURPLE_ICON_SCALE_SEND | PURPLE_ICON_SCALE_DISPLAY}, /* icon_spec */
	jabber_list_icon,				/* list_icon */
	jabber_list_emblem,			/* list_emblems */
	jabber_status_text,				/* status_text */
	jabber_tooltip_text,			/* tooltip_text */
	jabber_status_types,			/* status_types */
	jabber_blist_node_menu,			/* blist_node_menu */
	jabber_chat_info,				/* chat_info */
	jabber_chat_info_defaults,		/* chat_info_defaults */
	jabber_login,					/* login */
	jabber_close,					/* close */
	jabber_message_send_im,			/* send_im */
	jabber_set_info,				/* set_info */
	jabber_send_typing,				/* send_typing */
	jabber_buddy_get_info,			/* get_info */
	jabber_set_status,				/* set_status */
	jabber_idle_set,				/* set_idle */
	NULL,							/* change_passwd */
	jabber_roster_add_buddy,		/* add_buddy */
	NULL,							/* add_buddies */
	jabber_roster_remove_buddy,		/* remove_buddy */
	NULL,							/* remove_buddies */
	NULL,							/* add_permit */
	jabber_add_deny,				/* add_deny */
	NULL,							/* rem_permit */
	jabber_rem_deny,				/* rem_deny */
	NULL,							/* set_permit_deny */
	jabber_chat_join,				/* join_chat */
	NULL,							/* reject_chat */
	jabber_get_chat_name,			/* get_chat_name */
	jabber_chat_invite,				/* chat_invite */
	jabber_chat_leave,				/* chat_leave */
	NULL,							/* chat_whisper */
	jabber_message_send_chat,		/* chat_send */
	jabber_keepalive,				/* keepalive */
	jabber_register_account,		/* register_user */
	NULL,							/* get_cb_info */
	NULL,							/* get_cb_away */
	jabber_roster_alias_change,		/* alias_buddy */
	jabber_roster_group_change,		/* group_buddy */
	jabber_roster_group_rename,		/* rename_group */
	NULL,							/* buddy_free */
	jabber_convo_closed,			/* convo_closed */
	jabber_normalize,				/* normalize */
	jabber_set_buddy_icon,			/* set_buddy_icon */
	NULL,							/* remove_group */
	jabber_chat_buddy_real_name,	/* get_cb_real_name */
	jabber_chat_set_topic,			/* set_chat_topic */
	jabber_find_blist_chat,			/* find_blist_chat */
	jabber_roomlist_get_list,		/* roomlist_get_list */
	jabber_roomlist_cancel,			/* roomlist_cancel */
	NULL,							/* roomlist_expand_category */
	jabber_can_receive_file,		/* can_receive_file */
	jabber_si_xfer_send,			/* send_file */
	jabber_si_new_xfer,				/* new_xfer */
	jabber_offline_message,			/* offline_message */
	NULL,							/* whiteboard_prpl_ops */
	jabber_prpl_send_raw,			/* send_raw */
	jabber_roomlist_room_serialize, /* roomlist_room_serialize */
	jabber_unregister_account,		/* unregister_user */
	jabber_send_attention,			/* send_attention */
	jabber_attention_types,			/* attention_types */

	sizeof(PurplePluginProtocolInfo),       /* struct_size */
	NULL, /* get_account_text_table */
	jabber_initiate_media,          /* initiate_media */
	jabber_get_media_caps,                  /* get_media_caps */
};

static gboolean load_plugin(PurplePlugin *plugin)
{
	purple_signal_register(plugin, "jabber-receiving-xmlnode",
			purple_marshal_VOID__POINTER_POINTER, NULL, 2,
			purple_value_new(PURPLE_TYPE_SUBTYPE, PURPLE_SUBTYPE_CONNECTION),
			purple_value_new_outgoing(PURPLE_TYPE_SUBTYPE, PURPLE_SUBTYPE_XMLNODE));

	purple_signal_register(plugin, "jabber-sending-xmlnode",
			purple_marshal_VOID__POINTER_POINTER, NULL, 2,
			purple_value_new(PURPLE_TYPE_SUBTYPE, PURPLE_SUBTYPE_CONNECTION),
			purple_value_new_outgoing(PURPLE_TYPE_SUBTYPE, PURPLE_SUBTYPE_XMLNODE));

	/*
	 * Do not remove this or the plugin will fail. Completely. You have been
	 * warned!
	 */
	purple_signal_connect_priority(plugin, "jabber-sending-xmlnode",
			plugin, PURPLE_CALLBACK(jabber_send_signal_cb),
			NULL, PURPLE_SIGNAL_PRIORITY_HIGHEST);

	purple_signal_register(plugin, "jabber-sending-text",
			     purple_marshal_VOID__POINTER_POINTER, NULL, 2,
			     purple_value_new(PURPLE_TYPE_SUBTYPE, PURPLE_SUBTYPE_CONNECTION),
			     purple_value_new_outgoing(PURPLE_TYPE_STRING));

	purple_signal_register(plugin, "jabber-receiving-message",
			purple_marshal_BOOLEAN__POINTER_POINTER_POINTER_POINTER_POINTER_POINTER,
			purple_value_new(PURPLE_TYPE_BOOLEAN), 6,
			purple_value_new(PURPLE_TYPE_SUBTYPE, PURPLE_SUBTYPE_CONNECTION),
			purple_value_new(PURPLE_TYPE_STRING), /* type */
			purple_value_new(PURPLE_TYPE_STRING), /* id */
			purple_value_new(PURPLE_TYPE_STRING), /* from */
			purple_value_new(PURPLE_TYPE_STRING), /* to */
			purple_value_new(PURPLE_TYPE_SUBTYPE, PURPLE_SUBTYPE_XMLNODE));

	purple_signal_register(plugin, "jabber-receiving-iq",
			purple_marshal_BOOLEAN__POINTER_POINTER_POINTER_POINTER_POINTER,
			purple_value_new(PURPLE_TYPE_BOOLEAN), 5,
			purple_value_new(PURPLE_TYPE_SUBTYPE, PURPLE_SUBTYPE_CONNECTION),
			purple_value_new(PURPLE_TYPE_STRING), /* type */
			purple_value_new(PURPLE_TYPE_STRING), /* id */
			purple_value_new(PURPLE_TYPE_STRING), /* from */
			purple_value_new(PURPLE_TYPE_SUBTYPE, PURPLE_SUBTYPE_XMLNODE));

	purple_signal_register(plugin, "jabber-watched-iq",
			purple_marshal_BOOLEAN__POINTER_POINTER_POINTER_POINTER_POINTER,
			purple_value_new(PURPLE_TYPE_BOOLEAN), 5,
			purple_value_new(PURPLE_TYPE_SUBTYPE, PURPLE_SUBTYPE_CONNECTION),
			purple_value_new(PURPLE_TYPE_STRING), /* type */
			purple_value_new(PURPLE_TYPE_STRING), /* id */
			purple_value_new(PURPLE_TYPE_STRING), /* from */
			purple_value_new(PURPLE_TYPE_SUBTYPE, PURPLE_SUBTYPE_XMLNODE)); /* child */

	/* Modifying these? Look at jabber_init_plugin for the ipc versions */
	purple_signal_register(plugin, "jabber-register-namespace-watcher",
			purple_marshal_VOID__POINTER_POINTER,
			NULL, 2,
			purple_value_new(PURPLE_TYPE_STRING),  /* node */
			purple_value_new(PURPLE_TYPE_STRING)); /* namespace */

	purple_signal_register(plugin, "jabber-unregister-namespace-watcher",
			purple_marshal_VOID__POINTER_POINTER,
			NULL, 2,
			purple_value_new(PURPLE_TYPE_STRING),  /* node */
			purple_value_new(PURPLE_TYPE_STRING)); /* namespace */

	purple_signal_connect(plugin, "jabber-register-namespace-watcher",
			plugin, PURPLE_CALLBACK(jabber_iq_signal_register), NULL);
	purple_signal_connect(plugin, "jabber-unregister-namespace-watcher",
			plugin, PURPLE_CALLBACK(jabber_iq_signal_unregister), NULL);

	purple_signal_register(plugin, "jabber-receiving-presence",
			purple_marshal_BOOLEAN__POINTER_POINTER_POINTER_POINTER,
			purple_value_new(PURPLE_TYPE_BOOLEAN), 4,
			purple_value_new(PURPLE_TYPE_SUBTYPE, PURPLE_SUBTYPE_CONNECTION),
			purple_value_new(PURPLE_TYPE_STRING), /* type */
			purple_value_new(PURPLE_TYPE_STRING), /* from */
			purple_value_new(PURPLE_TYPE_SUBTYPE, PURPLE_SUBTYPE_XMLNODE));

	return TRUE;
}

static gboolean unload_plugin(PurplePlugin *plugin)
{
	purple_signals_unregister_by_instance(plugin);

	/* reverse order of init_plugin */
	jabber_bosh_uninit();
	jabber_data_uninit();
	jabber_si_uninit();
	jabber_ibb_uninit();
	/* PEP things should be uninit via jabber_pep_uninit, not here */
	jabber_pep_uninit();
	jabber_caps_uninit();
	jabber_iq_uninit();

	jabber_unregister_commands();

	/* Stay on target...stay on target... Almost there... */
	jabber_uninit_plugin(plugin);

	return TRUE;
}

static PurplePluginInfo info =
{
	PURPLE_PLUGIN_MAGIC,
	PURPLE_MAJOR_VERSION,
	PURPLE_MINOR_VERSION,
	PURPLE_PLUGIN_PROTOCOL,                             /**< type           */
	NULL,                                             /**< ui_requirement */
	0,                                                /**< flags          */
	NULL,                                             /**< dependencies   */
	PURPLE_PRIORITY_DEFAULT,                            /**< priority       */

	"prpl-jabber",                                    /**< id             */
	"XMPP",                                           /**< name           */
	DISPLAY_VERSION,                                  /**< version        */
	                                                  /**  summary        */
	N_("XMPP Protocol Plugin"),
	                                                  /**  description    */
	N_("XMPP Protocol Plugin"),
	NULL,                                             /**< author         */
	PURPLE_WEBSITE,                                     /**< homepage       */

	load_plugin,                                      /**< load           */
	unload_plugin,                                    /**< unload         */
	NULL,                                             /**< destroy        */

	NULL,                                             /**< ui_info        */
	&prpl_info,                                       /**< extra_info     */
	NULL,                                             /**< prefs_info     */
	jabber_actions,

	/* padding */
	NULL,
	NULL,
	NULL,
	NULL
};

static PurpleAccount *find_acct(const char *prpl, const char *acct_id)
{
	PurpleAccount *acct = NULL;

	/* If we have a specific acct, use it */
	if (acct_id) {
		acct = purple_accounts_find(acct_id, prpl);
		if (acct && !purple_account_is_connected(acct))
			acct = NULL;
	} else { /* Otherwise find an active account for the protocol */
		GList *l = purple_accounts_get_all();
		while (l) {
			if (!strcmp(prpl, purple_account_get_protocol_id(l->data))
					&& purple_account_is_connected(l->data)) {
				acct = l->data;
				break;
			}
			l = l->next;
		}
	}

	return acct;
}

static gboolean xmpp_uri_handler(const char *proto, const char *user, GHashTable *params)
{
	char *acct_id = g_hash_table_lookup(params, "account");
	PurpleAccount *acct;

	if (g_ascii_strcasecmp(proto, "xmpp"))
		return FALSE;

	acct = find_acct(purple_plugin_get_id(my_protocol), acct_id);

	if (!acct)
		return FALSE;

	/* xmpp:romeo@montague.net?message;subject=Test%20Message;body=Here%27s%20a%20test%20message */
	if (g_hash_table_lookup_extended(params, "message", NULL, NULL)) {
		char *body = g_hash_table_lookup(params, "body");
		if (user && *user) {
			PurpleConversation *conv =
					purple_conversation_new(PURPLE_CONV_TYPE_IM, acct, user);
			purple_conversation_present(conv);
			if (body && *body)
				purple_conv_send_confirm(conv, body);
		}
	} else if (g_hash_table_lookup_extended(params, "roster", NULL, NULL)) {
		char *name = g_hash_table_lookup(params, "name");
		if (user && *user)
			purple_blist_request_add_buddy(acct, user, NULL, name);
	} else if (g_hash_table_lookup_extended(params, "join", NULL, NULL)) {
		PurpleConnection *gc = purple_account_get_connection(acct);
		if (user && *user) {
			GHashTable *params = jabber_chat_info_defaults(gc, user);
			jabber_chat_join(gc, params);
		}
		return TRUE;
	}

	return FALSE;
}


static void
init_plugin(PurplePlugin *plugin)
{
#ifdef HAVE_CYRUS_SASL
#ifdef _WIN32
	UINT old_error_mode;
	gchar *sasldir;
#endif
	int ret;
#endif
	PurpleAccountUserSplit *split;
	PurpleAccountOption *option;

	/* Translators: 'domain' is used here in the context of Internet domains, e.g. pidgin.im */
	split = purple_account_user_split_new(_("Domain"), NULL, '@');
	purple_account_user_split_set_reverse(split, FALSE);
	prpl_info.user_splits = g_list_append(prpl_info.user_splits, split);

	split = purple_account_user_split_new(_("Resource"), NULL, '/');
	purple_account_user_split_set_reverse(split, FALSE);
	prpl_info.user_splits = g_list_append(prpl_info.user_splits, split);

	option = purple_account_option_bool_new(_("Require SSL/TLS"), "require_tls", JABBER_DEFAULT_REQUIRE_TLS);
	prpl_info.protocol_options = g_list_append(prpl_info.protocol_options,
											   option);

	option = purple_account_option_bool_new(_("Force old (port 5223) SSL"), "old_ssl", FALSE);
	prpl_info.protocol_options = g_list_append(prpl_info.protocol_options,
											   option);

	option = purple_account_option_bool_new(
						_("Allow plaintext auth over unencrypted streams"),
						"auth_plain_in_clear", FALSE);
	prpl_info.protocol_options = g_list_append(prpl_info.protocol_options,
						   option);

	option = purple_account_option_int_new(_("Connect port"), "port", 5222);
	prpl_info.protocol_options = g_list_append(prpl_info.protocol_options,
						   option);

	option = purple_account_option_string_new(_("Connect server"),
						  "connect_server", NULL);
	prpl_info.protocol_options = g_list_append(prpl_info.protocol_options,
						  option);

	option = purple_account_option_string_new(_("File transfer proxies"),
						  "ft_proxies",
						/* TODO: Is this an acceptable default?
						 * Also, keep this in sync as they add more servers */
						  "proxy.eu.jabber.org");
	prpl_info.protocol_options = g_list_append(prpl_info.protocol_options,
						  option);

	option = purple_account_option_string_new(_("BOSH URL"),
						  "bosh_url", NULL);
	prpl_info.protocol_options = g_list_append(prpl_info.protocol_options,
						  option);

	/* this should probably be part of global smiley theme settings later on,
	  shared with MSN */
	option = purple_account_option_bool_new(_("Show Custom Smileys"),
		"custom_smileys", TRUE);
	prpl_info.protocol_options = g_list_append(prpl_info.protocol_options,
		option);

	my_protocol = plugin;
	jabber_init_plugin(plugin);

	purple_prefs_remove("/plugins/prpl/jabber");

	/* XXX - If any other plugin wants SASL this won't be good ... */
#ifdef HAVE_CYRUS_SASL
#ifdef _WIN32
	sasldir = g_build_filename(wpurple_install_dir(), "sasl2", NULL);
	sasl_set_path(SASL_PATH_TYPE_PLUGIN, sasldir);
	g_free(sasldir);
	/* Suppress error popups for failing to load sasl plugins */
	old_error_mode = SetErrorMode(SEM_FAILCRITICALERRORS);
#endif
	if ((ret = sasl_client_init(NULL)) != SASL_OK) {
		purple_debug_error("xmpp", "Error (%d) initializing SASL.\n", ret);
	}
#ifdef _WIN32
	/* Restore the original error mode */
	SetErrorMode(old_error_mode);
#endif
#endif
	jabber_register_commands();

	/* reverse order of unload_plugin */
	jabber_iq_init();
	jabber_caps_init();
	/* PEP things should be init via jabber_pep_init, not here */
	jabber_pep_init();
	jabber_data_init();
	jabber_bosh_init();

/* BEGIN SPICEBIRD CHANGES */
#if 0
	#warning implement adding and retrieving own features via IPC API
#endif
/* END SPICEBIRD CHANGES */

	jabber_ibb_init();
	jabber_si_init();

	purple_signal_connect(purple_get_core(), "uri-handler", plugin,
		PURPLE_CALLBACK(xmpp_uri_handler), NULL);
}


PURPLE_INIT_PLUGIN(jabber, init_plugin, info);
