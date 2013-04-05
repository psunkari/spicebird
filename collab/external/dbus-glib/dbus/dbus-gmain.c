/* -*- mode: C; c-file-style: "gnu" -*- */
/* dbus-gmain.c GLib main loop integration
 *
 * Copyright (C) 2002, 2003 CodeFactory AB
 * Copyright (C) 2005 Red Hat, Inc.
 *
 * Licensed under the Academic Free License version 2.1
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

#include <config.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-lowlevel.h>
#include "dbus-gtest.h"
#include "dbus-gutils.h"
#include "dbus-gvalue.h"
#include "dbus-gobject.h"
#include "dbus-gvalue-utils.h"
#include "dbus-gsignature.h"
#include <string.h>

/* BEGIN SPICEBIRD CHANGES */
#if 0
#include <libintl.h>
#define _(x) dgettext (GETTEXT_PACKAGE, x)
#define N_(x) x
#endif
#ifdef ENABLE_NLS
#include <libintl.h>
#define _(x) dgettext (GETTEXT_PACKAGE, x)
#define N_(x) (x)
#else
#define _(x) (x)
#define N_(x) (x)
#endif
/* END SPICEBIRD CHANGES */

/**
 * @defgroup DBusGLibInternals GLib bindings implementation details
 * @ingroup  DBusInternals
 * @brief Implementation details of GLib bindings
 *
 * @{
 */

/**
 * DBusGMessageQueue:
 * A GSource subclass for dispatching DBusConnection messages.
 * We need this on top of the IO handlers, because sometimes
 * there are messages to dispatch queued up but no IO pending.
 */
typedef struct
{
  GSource source; /**< the parent GSource */
  DBusConnection *connection; /**< the connection to dispatch */
} DBusGMessageQueue;

static gboolean message_queue_prepare  (GSource     *source,
                                        gint        *timeout);
static gboolean message_queue_check    (GSource     *source);
static gboolean message_queue_dispatch (GSource     *source,
                                        GSourceFunc  callback,
                                        gpointer     user_data);

static const GSourceFuncs message_queue_funcs = {
  message_queue_prepare,
  message_queue_check,
  message_queue_dispatch,
  NULL
};

static gboolean
message_queue_prepare (GSource *source,
                       gint    *timeout)
{
  DBusConnection *connection = ((DBusGMessageQueue *)source)->connection;
  
  *timeout = -1;

  return (dbus_connection_get_dispatch_status (connection) == DBUS_DISPATCH_DATA_REMAINS);  
}

static gboolean
message_queue_check (GSource *source)
{
  return FALSE;
}

static gboolean
message_queue_dispatch (GSource     *source,
                        GSourceFunc  callback,
                        gpointer     user_data)
{
  DBusConnection *connection = ((DBusGMessageQueue *)source)->connection;

  dbus_connection_ref (connection);

  /* Only dispatch once - we don't want to starve other GSource */
  dbus_connection_dispatch (connection);
  
  dbus_connection_unref (connection);

  return TRUE;
}

typedef struct
{
  GMainContext *context;      /**< the main context */
  GSList *ios;                /**< all IOHandler */
  GSList *timeouts;           /**< all TimeoutHandler */
  DBusConnection *connection; /**< NULL if this is really for a server not a connection */
  GSource *message_queue_source; /**< DBusGMessageQueue */
} ConnectionSetup;


typedef struct
{
  ConnectionSetup *cs;
  GSource *source;
  DBusWatch *watch;
} IOHandler;

typedef struct
{
  ConnectionSetup *cs;
  GSource *source;
  DBusTimeout *timeout;
} TimeoutHandler;

dbus_int32_t _dbus_gmain_connection_slot = -1;
static dbus_int32_t server_slot = -1;

static void io_handler_add_source (ConnectionSetup *cs, int fd);

static ConnectionSetup*
connection_setup_new (GMainContext   *context,
                      DBusConnection *connection)
{
  ConnectionSetup *cs;

  cs = g_new0 (ConnectionSetup, 1);

  g_assert (context != NULL);
  
  cs->context = context;
  g_main_context_ref (cs->context);  

  if (connection)
    {
      cs->connection = connection;

      cs->message_queue_source = g_source_new ((GSourceFuncs *) &message_queue_funcs,
                                               sizeof (DBusGMessageQueue));
      ((DBusGMessageQueue*)cs->message_queue_source)->connection = connection;
      g_source_attach (cs->message_queue_source, cs->context);
    }
  
  return cs;
}

static void
io_handler_source_finalized (gpointer data)
{
  IOHandler *handler;

  handler = data;

  //if (handler->watch)
  //  dbus_watch_set_data (handler->watch, NULL, NULL);

  handler->cs->ios = g_slist_remove (handler->cs->ios, handler);  

  g_free (handler);
}

static void
io_handler_destroy_source (void *data)
{
  IOHandler *handler;

  handler = data;

  if (handler->source)
    {
      GSource *source = handler->source;
      handler->source = NULL;
      g_source_destroy (source);
      g_source_unref (source);
    }
}

static void
io_handler_watch_freed (void *data)
{
  IOHandler *handler;
  ConnectionSetup *cs;
  int fd;

  handler = data;

  cs = handler->cs;
#ifdef _WIN32
  fd = dbus_watch_get_socket (handler->watch);
#else
  fd = dbus_watch_get_unix_fd (handler->watch);
#endif

  handler->watch = NULL;

  io_handler_destroy_source (handler);
  io_handler_source_finalized (handler);

  /* Check if there are other handlers with same fd and give them a new
   * source
   */
  io_handler_add_source (cs, fd);
}

static gboolean
io_handler_dispatch (GIOChannel   *source,
                     GIOCondition  condition,
                     gpointer      data)
{
  guint dbus_condition = 0;
  ConnectionSetup *cs;
  DBusConnection *connection;
  GSList *iterator;

  cs = data;

  connection = cs->connection;

  if (connection)
    dbus_connection_ref (connection);
  
  for (iterator = cs->ios; iterator != NULL;)
    {
      IOHandler *handler;
      unsigned int flags;

      handler = iterator->data;
      iterator = g_slist_next (iterator);

      /* BUNNY: getting a list of watch to dispatch for and then dispatching
       * conditionally if the watch still exist may be a bit more safer
       */
      flags = dbus_watch_get_flags (handler->watch);

      if (condition & G_IO_IN)
	dbus_condition |= DBUS_WATCH_READABLE;
      if (condition & G_IO_OUT)
	dbus_condition |= DBUS_WATCH_WRITABLE;
      if (condition & G_IO_ERR)
	dbus_condition |= DBUS_WATCH_ERROR;
      if (condition & G_IO_HUP)
	dbus_condition |= DBUS_WATCH_HANGUP;

      /* Check if the io condition is interesting to this watch */
      if (!((dbus_condition & DBUS_WATCH_ERROR) ||
	    (dbus_condition & DBUS_WATCH_HANGUP) ||
	    ((dbus_condition & flags) &
             (DBUS_WATCH_READABLE | DBUS_WATCH_WRITABLE))))
	continue;

      /* Note that we don't touch the handler after this, because
       * dbus may have disabled the watch and thus killed the
       * handler.
       */
      dbus_watch_handle (handler->watch, dbus_condition);
	  break;
    }

  if (connection)
    dbus_connection_unref (connection);
  
  return TRUE;
}

static void
io_handler_add_source (ConnectionSetup *cs,
		       int fd)
{
  GIOChannel *channel;
  GIOCondition condition;
  GSource *source;
  GSList *iterator;

  /* Get the union of all io condition flags with the given fd
   * Also delete the old source.
   */
  condition = 0;
  for (iterator = cs->ios; iterator != NULL;
       iterator = g_slist_next (iterator))
    {
      IOHandler *handler;
      DBusWatch *watch;
      guint flags;

      handler = iterator->data;

      watch = handler->watch;

#ifdef _WIN32
      if (dbus_watch_get_socket (watch) != fd)
#else
      if (dbus_watch_get_unix_fd (watch) != fd)
#endif
	continue;

      flags = dbus_watch_get_flags (watch);
      if (flags & DBUS_WATCH_READABLE)
	condition |= G_IO_IN;
      if (flags & DBUS_WATCH_WRITABLE)
	condition |= G_IO_OUT;

      io_handler_destroy_source (handler);
    }
  if (!condition)
    return;
  condition |= G_IO_ERR | G_IO_HUP;

  /* Create the new source with the required io conditions */
#ifdef _WIN32
  channel = g_io_channel_win32_new_socket (fd);
#else
  channel = g_io_channel_unix_new (fd);
#endif
  
  source = g_io_create_watch (channel, condition);
  g_source_set_callback (source, (GSourceFunc) io_handler_dispatch, cs, NULL);
  g_source_attach (source, cs->context);
  g_io_channel_unref (channel);

  /* Attach the new source to all the the handlers. */
  for (iterator = cs->ios; iterator != NULL;
       iterator = g_slist_next (iterator))
    {
      IOHandler *handler;
      DBusWatch *watch;

      handler = iterator->data;

      watch = handler->watch;

#ifdef _WIN32
      if (dbus_watch_get_socket (watch) != fd)
#else
      if (dbus_watch_get_unix_fd (watch) != fd)
#endif
	continue;

      g_source_ref (source);
      handler->source = source;
    }

  /* Since all the handlers have their references */
  g_source_unref (source);
}

static void
connection_setup_add_watch (ConnectionSetup *cs,
                            DBusWatch       *watch)
{
  IOHandler *handler;
  int fd;
  
  if (!dbus_watch_get_enabled (watch))
    return;
  
  g_assert (dbus_watch_get_data (watch) == NULL);
  
  handler = g_new0 (IOHandler, 1);
  handler->cs = cs;
  handler->watch = watch;
  handler->source = NULL;
  
  cs->ios = g_slist_prepend (cs->ios, handler);
  
  dbus_watch_set_data (watch, handler, io_handler_watch_freed);

#ifdef _WIN32
  fd = dbus_watch_get_socket (watch);
#else
  fd = dbus_watch_get_unix_fd (watch);
#endif 

  io_handler_add_source (cs, fd);
}

static void
connection_setup_remove_watch (ConnectionSetup *cs,
                               DBusWatch       *watch)
{
  dbus_watch_set_data (watch, NULL, NULL);
}

static void
timeout_handler_source_finalized (gpointer data)
{
  TimeoutHandler *handler;

  handler = data;

  if (handler->timeout)
    dbus_timeout_set_data (handler->timeout, NULL, NULL);
  
  g_free (handler);
}

static void
timeout_handler_destroy_source (void *data)
{
  TimeoutHandler *handler;

  handler = data;

  if (handler->source)
    {
      GSource *source = handler->source;
      handler->source = NULL;
      handler->cs->timeouts = g_slist_remove (handler->cs->timeouts, handler);
      g_source_destroy (source);
      g_source_unref (source);
    }
}

static void
timeout_handler_timeout_freed (void *data)
{
  TimeoutHandler *handler;

  handler = data;

  handler->timeout = NULL;

  timeout_handler_destroy_source (handler);
}

static gboolean
timeout_handler_dispatch (gpointer      data)
{
  TimeoutHandler *handler;

  handler = data;

  dbus_timeout_handle (handler->timeout);
  
  return TRUE;
}

static void
connection_setup_add_timeout (ConnectionSetup *cs,
                              DBusTimeout     *timeout)
{
  TimeoutHandler *handler;
  
  if (!dbus_timeout_get_enabled (timeout))
    return;
  
  g_assert (dbus_timeout_get_data (timeout) == NULL);

  handler = g_new0 (TimeoutHandler, 1);
  handler->cs = cs;
  handler->timeout = timeout;

  handler->source = g_timeout_source_new (dbus_timeout_get_interval (timeout));
  g_source_set_callback (handler->source, timeout_handler_dispatch, handler,
                         timeout_handler_source_finalized);
  g_source_attach (handler->source, handler->cs->context);

  cs->timeouts = g_slist_prepend (cs->timeouts, handler);

  dbus_timeout_set_data (timeout, handler, timeout_handler_timeout_freed);
}

static void
connection_setup_remove_timeout (ConnectionSetup *cs,
                                 DBusTimeout       *timeout)
{
  TimeoutHandler *handler;
  
  handler = dbus_timeout_get_data (timeout);

  if (handler == NULL)
    return;
  
  timeout_handler_destroy_source (handler);
}

static void
connection_setup_free (ConnectionSetup *cs)
{
  while (cs->ios)
  {
    IOHandler *handler = cs->ios->data;
    io_handler_destroy_source (handler);
    io_handler_source_finalized (handler);
  }

  while (cs->timeouts)
    timeout_handler_destroy_source (cs->timeouts->data);

  if (cs->message_queue_source)
    {
      GSource *source;

      source = cs->message_queue_source;
      cs->message_queue_source = NULL;

      g_source_destroy (source);
      g_source_unref (source);
    }
  
  g_main_context_unref (cs->context);
  g_free (cs);
}

static dbus_bool_t
add_watch (DBusWatch *watch,
	   gpointer   data)
{
  ConnectionSetup *cs;

  cs = data;

  connection_setup_add_watch (cs, watch);
  
  return TRUE;
}

static void
remove_watch (DBusWatch *watch,
	      gpointer   data)
{
  ConnectionSetup *cs;

  cs = data;

  connection_setup_remove_watch (cs, watch);
}

static void
watch_toggled (DBusWatch *watch,
               void      *data)
{
  /* Because we just exit on OOM, enable/disable is
   * no different from add/remove
   */
  if (dbus_watch_get_enabled (watch))
    add_watch (watch, data);
  else
    remove_watch (watch, data);
}

static dbus_bool_t
add_timeout (DBusTimeout *timeout,
	     void        *data)
{
  ConnectionSetup *cs;

  cs = data;
  
  if (!dbus_timeout_get_enabled (timeout))
    return TRUE;

  connection_setup_add_timeout (cs, timeout);

  return TRUE;
}

static void
remove_timeout (DBusTimeout *timeout,
		void        *data)
{
  ConnectionSetup *cs;

  cs = data;

  connection_setup_remove_timeout (cs, timeout);
}

static void
timeout_toggled (DBusTimeout *timeout,
                 void        *data)
{
  /* Because we just exit on OOM, enable/disable is
   * no different from add/remove
   */
  if (dbus_timeout_get_enabled (timeout))
    add_timeout (timeout, data);
  else
    remove_timeout (timeout, data);
}

static void
wakeup_main (void *data)
{
  ConnectionSetup *cs = data;

  g_main_context_wakeup (cs->context);
}


/* Move to a new context */
static ConnectionSetup*
connection_setup_new_from_old (GMainContext    *context,
                               ConnectionSetup *old)
{
  GSList *tmp;
  ConnectionSetup *cs;

  g_assert (old->context != context);
  
  cs = connection_setup_new (context, old->connection);
  
  tmp = old->ios;
  while (tmp != NULL)
    {
      IOHandler *handler = tmp->data;

      connection_setup_add_watch (cs, handler->watch);
      
      tmp = tmp->next;
    }

  tmp = old->timeouts;
  while (tmp != NULL)
    {
      TimeoutHandler *handler = tmp->data;

      connection_setup_add_timeout (cs, handler->timeout);
      
      tmp = tmp->next;
    }

  return cs;
}

/** @} */ /* End of GLib bindings internals */

/** @addtogroup DBusGLib
 * @{
 */

/**
 * dbus_connection_setup_with_g_main:
 * @connection: the connection
 * @context: the #GMainContext or #NULL for default context
 *
 * Sets the watch and timeout functions of a #DBusConnection
 * to integrate the connection with the GLib main loop.
 * Pass in #NULL for the #GMainContext unless you're
 * doing something specialized.
 *
 * If called twice for the same context, does nothing the second
 * time. If called once with context A and once with context B,
 * context B replaces context A as the context monitoring the
 * connection.
 */
void
dbus_connection_setup_with_g_main (DBusConnection *connection,
				   GMainContext   *context)
{
  ConnectionSetup *old_setup;
  ConnectionSetup *cs;
  
  /* FIXME we never free the slot, so its refcount just keeps growing,
   * which is kind of broken.
   */
  dbus_connection_allocate_data_slot (&_dbus_gmain_connection_slot);
  if (_dbus_gmain_connection_slot < 0)
    goto nomem;

  if (context == NULL)
    context = g_main_context_default ();

  cs = NULL;
  
  old_setup = dbus_connection_get_data (connection, _dbus_gmain_connection_slot);
  if (old_setup != NULL)
    {
      if (old_setup->context == context)
        return; /* nothing to do */

      cs = connection_setup_new_from_old (context, old_setup);
      
      /* Nuke the old setup */
      dbus_connection_set_data (connection, _dbus_gmain_connection_slot, NULL, NULL);
      old_setup = NULL;
    }

  if (cs == NULL)
    cs = connection_setup_new (context, connection);

  if (!dbus_connection_set_data (connection, _dbus_gmain_connection_slot, cs,
                                 (DBusFreeFunction)connection_setup_free))
    goto nomem;
  
  if (!dbus_connection_set_watch_functions (connection,
                                            add_watch,
                                            remove_watch,
                                            watch_toggled,
                                            cs, NULL))
    goto nomem;

  if (!dbus_connection_set_timeout_functions (connection,
                                              add_timeout,
                                              remove_timeout,
                                              timeout_toggled,
                                              cs, NULL))
    goto nomem;
    
  dbus_connection_set_wakeup_main_function (connection,
					    wakeup_main,
					    cs, NULL);
      
  return;

 nomem:
  g_error ("Not enough memory to set up DBusConnection for use with GLib");
}

/**
 * dbus_server_setup_with_g_main:
 * @server: the server
 * @context: the #GMainContext or #NULL for default
 *
 * Sets the watch and timeout functions of a #DBusServer
 * to integrate the server with the GLib main loop.
 * In most cases the context argument should be #NULL.
 *
 * If called twice for the same context, does nothing the second
 * time. If called once with context A and once with context B,
 * context B replaces context A as the context monitoring the
 * connection.
 */
void
dbus_server_setup_with_g_main (DBusServer   *server,
                               GMainContext *context)
{
  ConnectionSetup *old_setup;
  ConnectionSetup *cs;
  
  /* FIXME we never free the slot, so its refcount just keeps growing,
   * which is kind of broken.
   */
  dbus_server_allocate_data_slot (&server_slot);
  if (server_slot < 0)
    goto nomem;

  if (context == NULL)
    context = g_main_context_default ();

  cs = NULL;
  
  old_setup = dbus_server_get_data (server, server_slot);
  if (old_setup != NULL)
    {
      if (old_setup->context == context)
        return; /* nothing to do */

      cs = connection_setup_new_from_old (context, old_setup);
      
      /* Nuke the old setup */
      dbus_server_set_data (server, server_slot, NULL, NULL);
      old_setup = NULL;
    }

  if (cs == NULL)
    cs = connection_setup_new (context, NULL);

  if (!dbus_server_set_data (server, server_slot, cs,
                             (DBusFreeFunction)connection_setup_free))
    goto nomem;
  
  if (!dbus_server_set_watch_functions (server,
                                        add_watch,
                                        remove_watch,
                                        watch_toggled,
                                        cs, NULL))
    goto nomem;

  if (!dbus_server_set_timeout_functions (server,
                                          add_timeout,
                                          remove_timeout,
                                          timeout_toggled,
                                          cs, NULL))
    goto nomem;
      
  return;

 nomem:
  g_error ("Not enough memory to set up DBusServer for use with GLib");
}

/**
 * dbus_g_connection_open:
 * @address: address of the connection to open
 * @error: address where an error can be returned.
 *
 * Returns a connection to the given address.
 *
 * (Internally, calls dbus_connection_open() then calls
 * dbus_connection_setup_with_g_main() on the result.)
 *
 * Returns: a DBusConnection
 */
DBusGConnection*
dbus_g_connection_open (const gchar  *address,
                        GError      **error)
{
  DBusConnection *connection;
  DBusError derror;

  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  _dbus_g_value_types_init ();

  dbus_error_init (&derror);

  connection = dbus_connection_open (address, &derror);
  if (connection == NULL)
    {
      dbus_set_g_error (error, &derror);
      dbus_error_free (&derror);
      return NULL;
    }

  /* does nothing if it's already been done */
  dbus_connection_setup_with_g_main (connection, NULL);

  return DBUS_G_CONNECTION_FROM_CONNECTION (connection);
}

/**
 * dbus_g_bus_get:
 * @type: bus type
 * @error: address where an error can be returned.
 *
 * Returns a connection to the given bus. The connection is a global variable
 * shared with other callers of this function.
 * 
 * (Internally, calls dbus_bus_get() then calls
 * dbus_connection_setup_with_g_main() on the result.)
 *
 * Returns: a DBusConnection
 */
DBusGConnection*
dbus_g_bus_get (DBusBusType     type,
                GError        **error)
{
  DBusConnection *connection;
  DBusError derror;

  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  _dbus_g_value_types_init ();
  
  dbus_error_init (&derror);

  connection = dbus_bus_get (type, &derror);
  if (connection == NULL)
    {
      dbus_set_g_error (error, &derror);
      dbus_error_free (&derror);
      return NULL;
    }

  /* does nothing if it's already been done */
  dbus_connection_setup_with_g_main (connection, NULL);

  return DBUS_G_CONNECTION_FROM_CONNECTION (connection);
}

/** @} */ /* end of public API */

#ifdef DBUS_BUILD_TESTS

/**
 * @ingroup DBusGLibInternals
 * Unit test for GLib main loop integration
 * Returns: #TRUE on success.
 */
gboolean
_dbus_gmain_test (const char *test_data_dir)
{
  GType type;
  GType rectype;

  g_type_init ();
  _dbus_g_value_types_init ();

  rectype = dbus_g_type_get_collection ("GArray", G_TYPE_UINT);
  g_assert (rectype != G_TYPE_INVALID);
  g_assert (!strcmp (g_type_name (rectype), "GArray_guint_"));

  type = _dbus_gtype_from_signature ("au", TRUE);
  g_assert (type == rectype);

  rectype = dbus_g_type_get_map ("GHashTable", G_TYPE_STRING, G_TYPE_STRING);
  g_assert (rectype != G_TYPE_INVALID);
  g_assert (!strcmp (g_type_name (rectype), "GHashTable_gchararray+gchararray_"));

  type = _dbus_gtype_from_signature ("a{ss}", TRUE);
  g_assert (type == rectype);

  type = _dbus_gtype_from_signature ("o", FALSE);
  g_assert (type == DBUS_TYPE_G_OBJECT_PATH);
  type = _dbus_gtype_from_signature ("o", TRUE);
  g_assert (type == DBUS_TYPE_G_OBJECT_PATH);
  
  return TRUE;
}

#endif /* DBUS_BUILD_TESTS */
