/*
 * main.c - entry point and libpurple boilerplate for telepathy-haze
 * Copyright (C) 2007 Will Thompson
 * Copyright (C) 2007-2008 Collabora Ltd.
 * Portions taken from libpurple/examples/nullclient.c:
 *   Copyright (C) 2007 Sadrul Habib Chowdhury, Sean Egan, Gary Kramlich,
 *                      Mark Doliner, Richard Laager
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "config.h"

#include <string.h>
#include <errno.h>
#include <signal.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <libpurple/account.h>
#include <libpurple/core.h>
#include <libpurple/blist.h>
#include <libpurple/version.h>
#include <libpurple/eventloop.h>
#include <libpurple/prefs.h>
#include <libpurple/util.h>

#ifdef HAVE_PURPLE_DBUS_UNINIT
#include <libpurple/dbus-server.h>
#endif

#if !PURPLE_VERSION_CHECK (2, 4, 0)
extern const guint purple_major_version;
extern const guint purple_minor_version;
extern const guint purple_micro_version;
#endif

#include <telepathy-glib/run.h>

#include "defines.h"
#include "debug.h"
#include "connection-manager.h"
#include "notify.h"
#include "request.h"

/* BEGIN SPICEBIRD CHANGES */
#ifdef _WIN32
#include <libpurple/win32/win32dep.h>
#endif
/* END SPICEBIRD CHANGES */

/* Copied verbatim from nullclient, modulo changing whitespace. */
#define PURPLE_GLIB_READ_COND  (G_IO_IN | G_IO_HUP | G_IO_ERR)
#define PURPLE_GLIB_WRITE_COND (G_IO_OUT | G_IO_HUP | G_IO_ERR | G_IO_NVAL)

typedef struct _PurpleGLibIOClosure {
    PurpleInputFunction function;
    guint result;
    gpointer data;
} PurpleGLibIOClosure;

static void purple_glib_io_destroy(gpointer data)
{
    g_free(data);
}

static gboolean purple_glib_io_invoke(GIOChannel *source,
                                      GIOCondition condition,
                                      gpointer data)
{
    PurpleGLibIOClosure *closure = data;
    PurpleInputCondition purple_cond = 0;

    if (condition & PURPLE_GLIB_READ_COND)
        purple_cond |= PURPLE_INPUT_READ;
    if (condition & PURPLE_GLIB_WRITE_COND)
        purple_cond |= PURPLE_INPUT_WRITE;

    closure->function(closure->data, g_io_channel_unix_get_fd(source),
                      purple_cond);

    return TRUE;
}

static guint glib_input_add(gint fd,
                            PurpleInputCondition condition,
                            PurpleInputFunction function,
                            gpointer data)
{
    PurpleGLibIOClosure *closure = g_new0(PurpleGLibIOClosure, 1);
    GIOChannel *channel;
    GIOCondition cond = 0;
    /* BEGIN SPICEBIRD CHANGES */
#ifdef _WIN32
    static int use_glib_io_channel = -1;
        
    if (use_glib_io_channel == -1)
        use_glib_io_channel = (g_getenv("HAZE_GLIB_IO_CHANNEL") != NULL) ? 1 : 0;
#endif
    /* END SPICEBIRD CHANGES */

    closure->function = function;
    closure->data = data;

    if (condition & PURPLE_INPUT_READ)
        cond |= PURPLE_GLIB_READ_COND;
    if (condition & PURPLE_INPUT_WRITE)
        cond |= PURPLE_GLIB_WRITE_COND;

    /* BEGIN SPICEBIRD CHANGES */
#ifdef _WIN32
        if (use_glib_io_channel == 0)
                channel = wpurple_g_io_channel_win32_new_socket(fd);
        else
#endif
    /* END SPICEBIRD CHANGES */
    channel = g_io_channel_unix_new(fd);
    closure->result = g_io_add_watch_full(channel, G_PRIORITY_DEFAULT, cond,
            purple_glib_io_invoke, closure, purple_glib_io_destroy);

    g_io_channel_unref(channel);
    return closure->result;
}

static PurpleEventLoopUiOps glib_eventloops = 
{
    g_timeout_add,
    g_source_remove,
    glib_input_add,
    g_source_remove,
    NULL,

    /* padding */
    NULL,
    NULL,
    NULL,
    NULL
};
/*** End of the eventloop functions. ***/

static char *user_dir = NULL;

static void
haze_ui_init (void)
{
    purple_accounts_set_ui_ops (haze_get_account_ui_ops ());
    purple_conversations_set_ui_ops (haze_get_conv_ui_ops ());
    purple_connections_set_ui_ops (haze_get_connection_ui_ops ());
#ifdef ENABLE_LEAKY_REQUEST_STUBS
    purple_request_set_ui_ops (haze_request_get_ui_ops ());
#endif
    purple_notify_set_ui_ops (haze_notify_get_ui_ops ());
}

static PurpleCoreUiOps haze_core_uiops = 
{
    NULL,
    haze_debug_init,
    haze_ui_init,
    NULL,

    /* padding */
    NULL,
    NULL,
    NULL,
    NULL
};

static void
set_libpurple_preferences (void)
{
    /* Out of the box, libpurple tracks your idle time based on when you last
     * sent a message or similar, and auto-aways you after 5 minutes of
     * inactivity, and sends auto-reply messages on protocols that have such a
     * concept natively when you're away.  Let's disable all that.
     */
    purple_prefs_set_string ("/purple/away/idle_reporting", "none");
    purple_prefs_set_bool ("/purple/away/away_when_idle", FALSE);
    purple_prefs_set_string ("/purple/away/auto_reply", "never");

}

static void
init_libpurple (void)
{
/* BEGIN SPICEBIRD CHANGES */
#ifndef _WIN32
    user_dir = g_strconcat (g_get_tmp_dir (), G_DIR_SEPARATOR_S,
                                  "haze-XXXXXX", NULL);

    if (!mkdtemp (user_dir)) {
        g_error ("Couldn't make temporary conf directory: %s",
                 strerror (errno));
    }
#else
    guint i;
    gchar random_buffer[33];
    for (i = 0; i < 4; i++)
	sprintf (random_buffer + i * 8, "%08X", g_random_int());
    random_buffer[32] = '\0';
    user_dir = g_strconcat (g_get_tmp_dir (), G_DIR_SEPARATOR_S,
			    "haze-", random_buffer, NULL);
    g_printf ("user_dir is %s\n", user_dir);
    if (g_mkdir (user_dir, 0755)) {
        g_error ("Couldn't make temporary conf directory: %s",
                 strerror (errno));
    }
#endif
/* END SPICEBIRD CHANGES */

    purple_util_set_user_dir (user_dir);

    purple_core_set_ui_ops(&haze_core_uiops);

    purple_eventloop_set_ui_ops(&glib_eventloops);

    if (!purple_core_init(UI_ID))
        g_error ("libpurple initialization failed.  :-/");
#ifdef HAVE_PURPLE_DBUS_UNINIT
    /* purple_core_init () calls purple_dbus_init ().  We don't want libpurple's
     * own dbus server, so let's kill it here.  Ideally, it would never be
     * initialized in the first place, but hey.
     */
    purple_dbus_uninit ();
#endif

    purple_set_blist(purple_blist_new());
    purple_blist_load();

    purple_prefs_load();

    /* BEGIN SPICEBIRD CHANGES */
#if 0
    DEBUG ("libpurple %d.%d.%d loaded (compiled against %d.%d.%d)",
#endif
    DEBUG ("libpurple %u.%u.%u loaded (compiled against %u.%u.%u)",
    /* END SPICEBIRD CHANGES */
        purple_major_version, purple_minor_version, purple_micro_version,
        PURPLE_MAJOR_VERSION, PURPLE_MINOR_VERSION, PURPLE_MICRO_VERSION);

    set_libpurple_preferences ();
}

static TpBaseConnectionManager *
get_cm (void)
{
    GLogLevelFlags fatal_mask;

    /* libpurple throws critical errors all over the place because of
     * g_return_val_if_fail().
     * Particularly in MSN.
     * I hate MSN.
     */
    fatal_mask = g_log_set_always_fatal (G_LOG_FATAL_MASK);
    fatal_mask &= ~G_LOG_LEVEL_CRITICAL;
    g_log_set_always_fatal (fatal_mask);

    return (TpBaseConnectionManager *) g_object_new (HAZE_TYPE_CONNECTION_MANAGER, NULL);
}

static gboolean
delete_directory (const char *path)
{
    const gchar *child_path;
    GDir *dir = g_dir_open (path, 0, NULL);
    gboolean ret = TRUE;

    if (!dir)
        return FALSE;

    while (ret && (child_path = g_dir_read_name (dir)))
    {
        gchar *child_full_path =
            g_strconcat (path, G_DIR_SEPARATOR_S, child_path, NULL);
        if (g_file_test (child_full_path, G_FILE_TEST_IS_DIR))
        {
            if (!delete_directory (child_full_path))
                ret = FALSE;
        }
        else
        {
            DEBUG ("deleting %s", child_full_path);
            if (g_unlink (child_full_path))
                ret = FALSE;
        }
        g_free (child_full_path);
    }

    g_dir_close (dir);

    if (ret)
    {
        DEBUG ("deleting %s", path);
        ret = !g_rmdir (path);
    }

    return ret;
}

static void
delete_user_dir (void)
{
    if (!delete_directory (user_dir))
        g_warning ("couldn't delete %s", user_dir);
    g_free (user_dir);
}

int
main(int argc,
     char **argv)
{
    int ret = 0;

    g_set_prgname(UI_ID);

    haze_debug_set_flags_from_env ();

/* BEGIN SPICEBIRD CHANGES */
#ifndef _WIN32
    signal (SIGCHLD, SIG_IGN);
#endif
/* END SPICEBIRD CHANGES */
    init_libpurple();

    ret = tp_run_connection_manager (UI_ID, PACKAGE_VERSION, get_cm, argc,
                                     argv);

    purple_core_quit ();
    delete_user_dir ();

    return ret;
}

