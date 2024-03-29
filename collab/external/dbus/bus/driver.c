/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/* driver.c  Bus client (driver)
 *
 * Copyright (C) 2003 CodeFactory AB
 * Copyright (C) 2003, 2004, 2005 Red Hat, Inc.
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "activation.h"
#include "connection.h"
#include "driver.h"
#include "dispatch.h"
#include "services.h"
#include "selinux.h"
#include "signals.h"
#include "utils.h"
#include <dbus/dbus-string.h>
#include <dbus/dbus-internals.h>
#include <dbus/dbus-marshal-recursive.h>
#include <string.h>

static dbus_bool_t bus_driver_send_welcome_message (DBusConnection *connection,
                                                    DBusMessage    *hello_message,
                                                    BusTransaction *transaction,
                                                    DBusError      *error);

dbus_bool_t
bus_driver_send_service_owner_changed (const char     *service_name,
				       const char     *old_owner,
				       const char     *new_owner,
				       BusTransaction *transaction,
				       DBusError      *error)
{
  DBusMessage *message;
  dbus_bool_t retval;
  const char *null_service;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  null_service = "";
  _dbus_verbose ("sending name owner changed: %s [%s -> %s]\n",
                 service_name, 
                 old_owner ? old_owner : null_service, 
                 new_owner ? new_owner : null_service);

  message = dbus_message_new_signal (DBUS_PATH_DBUS,
                                     DBUS_INTERFACE_DBUS,
                                     "NameOwnerChanged");
  
  if (message == NULL)
    {
      BUS_SET_OOM (error);
      return FALSE;
    }
  
  if (!dbus_message_set_sender (message, DBUS_SERVICE_DBUS))
    goto oom;

  if (!dbus_message_append_args (message,
                                 DBUS_TYPE_STRING, &service_name,
                                 DBUS_TYPE_STRING, old_owner ? &old_owner : &null_service,
                                 DBUS_TYPE_STRING, new_owner ? &new_owner : &null_service,
                                 DBUS_TYPE_INVALID))
    goto oom;

  _dbus_assert (dbus_message_has_signature (message, "sss"));
  
  retval = bus_dispatch_matches (transaction, NULL, NULL, message, error);
  dbus_message_unref (message);

  return retval;

 oom:
  dbus_message_unref (message);
  BUS_SET_OOM (error);
  return FALSE;
}

dbus_bool_t
bus_driver_send_service_lost (DBusConnection *connection,
			      const char     *service_name,
                              BusTransaction *transaction,
                              DBusError      *error)
{
  DBusMessage *message;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);
  
  message = dbus_message_new_signal (DBUS_PATH_DBUS,
                                     DBUS_INTERFACE_DBUS,
                                     "NameLost");
  
  if (message == NULL)
    {
      BUS_SET_OOM (error);
      return FALSE;
    }
  
  if (!dbus_message_set_destination (message, bus_connection_get_name (connection)) ||
      !dbus_message_append_args (message,
                                 DBUS_TYPE_STRING, &service_name,
                                 DBUS_TYPE_INVALID))
    {
      dbus_message_unref (message);
      BUS_SET_OOM (error);
      return FALSE;
    }

  if (!bus_transaction_send_from_driver (transaction, connection, message))
    {
      dbus_message_unref (message);
      BUS_SET_OOM (error);
      return FALSE;
    }
  else
    {
      dbus_message_unref (message);
      return TRUE;
    }
}

dbus_bool_t
bus_driver_send_service_acquired (DBusConnection *connection,
                                  const char     *service_name,
                                  BusTransaction *transaction,
                                  DBusError      *error)
{
  DBusMessage *message;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);
  
  message = dbus_message_new_signal (DBUS_PATH_DBUS,
                                     DBUS_INTERFACE_DBUS,
                                     "NameAcquired");

  if (message == NULL)
    {
      BUS_SET_OOM (error);
      return FALSE;
    }
  
  if (!dbus_message_set_destination (message, bus_connection_get_name (connection)) ||
      !dbus_message_append_args (message,
                                 DBUS_TYPE_STRING, &service_name,
                                 DBUS_TYPE_INVALID))
    {
      dbus_message_unref (message);
      BUS_SET_OOM (error);
      return FALSE;
    }

  if (!bus_transaction_send_from_driver (transaction, connection, message))
    {
      dbus_message_unref (message);
      BUS_SET_OOM (error);
      return FALSE;
    }
  else
    {
      dbus_message_unref (message);
      return TRUE;
    }
}

static dbus_bool_t
create_unique_client_name (BusRegistry *registry,
                           DBusString  *str)
{
  /* We never want to use the same unique client name twice, because
   * we want to guarantee that if you send a message to a given unique
   * name, you always get the same application. So we use two numbers
   * for INT_MAX * INT_MAX combinations, should be pretty safe against
   * wraparound.
   */
  /* FIXME these should be in BusRegistry rather than static vars */
  static int next_major_number = 0;
  static int next_minor_number = 0;
  int len;
  
  len = _dbus_string_get_length (str);
  
  while (TRUE)
    {
      /* start out with 1-0, go to 1-1, 1-2, 1-3,
       * up to 1-MAXINT, then 2-0, 2-1, etc.
       */
      if (next_minor_number <= 0)
        {
          next_major_number += 1;
          next_minor_number = 0;
          if (next_major_number <= 0)
            _dbus_assert_not_reached ("INT_MAX * INT_MAX clients were added");
        }

      _dbus_assert (next_major_number > 0);
      _dbus_assert (next_minor_number >= 0);

      /* appname:MAJOR-MINOR */
      
      if (!_dbus_string_append (str, ":"))
        return FALSE;
      
      if (!_dbus_string_append_int (str, next_major_number))
        return FALSE;

      if (!_dbus_string_append (str, "."))
        return FALSE;
      
      if (!_dbus_string_append_int (str, next_minor_number))
        return FALSE;

      next_minor_number += 1;
      
      /* Check if a client with the name exists */
      if (bus_registry_lookup (registry, str) == NULL)
	break;

      /* drop the number again, try the next one. */
      _dbus_string_set_length (str, len);
    }

  return TRUE;
}

static dbus_bool_t
bus_driver_handle_hello (DBusConnection *connection,
                         BusTransaction *transaction,
                         DBusMessage    *message,
                         DBusError      *error)
{
  DBusString unique_name;
  BusService *service;
  dbus_bool_t retval;
  BusRegistry *registry;
  BusConnections *connections;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  if (bus_connection_is_active (connection))
    {
      /* We already handled an Hello message for this connection. */
      dbus_set_error (error, DBUS_ERROR_FAILED,
                      "Already handled an Hello message");
      return FALSE;
    }

  /* Note that when these limits are exceeded we don't disconnect the
   * connection; we just sort of leave it hanging there until it times
   * out or disconnects itself or is dropped due to the max number of
   * incomplete connections. It's even OK if the connection wants to
   * retry the hello message, we support that.
   */
  connections = bus_connection_get_connections (connection);
  if (!bus_connections_check_limits (connections, connection,
                                     error))
    {
      _DBUS_ASSERT_ERROR_IS_SET (error);
      return FALSE;
    }
  
  if (!_dbus_string_init (&unique_name))
    {
      BUS_SET_OOM (error);
      return FALSE;
    }

  retval = FALSE;

  registry = bus_connection_get_registry (connection);
  
  if (!create_unique_client_name (registry, &unique_name))
    {
      BUS_SET_OOM (error);
      goto out_0;
    }

  if (!bus_connection_complete (connection, &unique_name, error))
    {
      _DBUS_ASSERT_ERROR_IS_SET (error);
      goto out_0;
    }
  
  if (!dbus_message_set_sender (message,
                                bus_connection_get_name (connection)))
    {
      BUS_SET_OOM (error);
      goto out_0;
    }
  
  if (!bus_driver_send_welcome_message (connection, message, transaction, error))
    goto out_0;

  /* Create the service */
  service = bus_registry_ensure (registry,
                                 &unique_name, connection, 0, transaction, error);
  if (service == NULL)
    goto out_0;
  
  _dbus_assert (bus_connection_is_active (connection));
  retval = TRUE;
  
 out_0:
  _dbus_string_free (&unique_name);
  return retval;
}

static dbus_bool_t
bus_driver_send_welcome_message (DBusConnection *connection,
                                 DBusMessage    *hello_message,
                                 BusTransaction *transaction,
                                 DBusError      *error)
{
  DBusMessage *welcome;
  const char *name;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);
  
  name = bus_connection_get_name (connection);
  _dbus_assert (name != NULL);
  
  welcome = dbus_message_new_method_return (hello_message);
  if (welcome == NULL)
    {
      BUS_SET_OOM (error);
      return FALSE;
    }
  
  if (!dbus_message_append_args (welcome,
                                 DBUS_TYPE_STRING, &name,
                                 DBUS_TYPE_INVALID))
    {
      dbus_message_unref (welcome);
      BUS_SET_OOM (error);
      return FALSE;
    }

  _dbus_assert (dbus_message_has_signature (welcome, DBUS_TYPE_STRING_AS_STRING));
  
  if (!bus_transaction_send_from_driver (transaction, connection, welcome))
    {
      dbus_message_unref (welcome);
      BUS_SET_OOM (error);
      return FALSE;
    }
  else
    {
      dbus_message_unref (welcome);
      return TRUE;
    }
}

static dbus_bool_t
bus_driver_handle_list_services (DBusConnection *connection,
                                 BusTransaction *transaction,
                                 DBusMessage    *message,
                                 DBusError      *error)
{
  DBusMessage *reply;
  int len;
  char **services;
  BusRegistry *registry;
  int i;
  DBusMessageIter iter;
  DBusMessageIter sub;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);
  
  registry = bus_connection_get_registry (connection);
  
  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    {
      BUS_SET_OOM (error);
      return FALSE;
    }

  if (!bus_registry_list_services (registry, &services, &len))
    {
      dbus_message_unref (reply);
      BUS_SET_OOM (error);
      return FALSE;
    }

  dbus_message_iter_init_append (reply, &iter);
  
  if (!dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
                                         DBUS_TYPE_STRING_AS_STRING,
                                         &sub))
    {
      dbus_free_string_array (services);
      dbus_message_unref (reply);
      BUS_SET_OOM (error);
      return FALSE;
    }

  {
    /* Include the bus driver in the list */
    const char *v_STRING = DBUS_SERVICE_DBUS;
    if (!dbus_message_iter_append_basic (&sub, DBUS_TYPE_STRING,
                                         &v_STRING))
      {
        dbus_free_string_array (services);
        dbus_message_unref (reply);
        BUS_SET_OOM (error);
        return FALSE;
      }
  }
  
  i = 0;
  while (i < len)
    {
      if (!dbus_message_iter_append_basic (&sub, DBUS_TYPE_STRING,
                                           &services[i]))
        {
          dbus_free_string_array (services);
          dbus_message_unref (reply);
          BUS_SET_OOM (error);
          return FALSE;
        }
      ++i;
    }

  dbus_free_string_array (services);

  if (!dbus_message_iter_close_container (&iter, &sub))
    {
      dbus_message_unref (reply);
      BUS_SET_OOM (error);
      return FALSE;
    }
  
  if (!bus_transaction_send_from_driver (transaction, connection, reply))
    {
      dbus_message_unref (reply);
      BUS_SET_OOM (error);
      return FALSE;
    }
  else
    {
      dbus_message_unref (reply);
      return TRUE;
    }
}

static dbus_bool_t
bus_driver_handle_list_activatable_services (DBusConnection *connection,
					     BusTransaction *transaction,
					     DBusMessage    *message,
					     DBusError      *error)
{
  DBusMessage *reply;
  int len;
  char **services;
  BusActivation *activation;
  int i;
  DBusMessageIter iter;
  DBusMessageIter sub;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  activation = bus_connection_get_activation (connection);

  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    {
      BUS_SET_OOM (error);
      return FALSE;
    }

  if (!bus_activation_list_services (activation, &services, &len))
    {
      dbus_message_unref (reply);
      BUS_SET_OOM (error);
      return FALSE;
    }

  dbus_message_iter_init_append (reply, &iter);

  if (!dbus_message_iter_open_container (&iter, DBUS_TYPE_ARRAY,
					 DBUS_TYPE_STRING_AS_STRING,
					 &sub))
    {
      dbus_free_string_array (services);
      dbus_message_unref (reply);
      BUS_SET_OOM (error);
      return FALSE;
    }

  {
    /* Include the bus driver in the list */
    const char *v_STRING = DBUS_SERVICE_DBUS;
    if (!dbus_message_iter_append_basic (&sub, DBUS_TYPE_STRING,
					 &v_STRING))
      {
	dbus_free_string_array (services);
	dbus_message_unref (reply);
	BUS_SET_OOM (error);
	return FALSE;
      }
  }

  i = 0;
  while (i < len)
    {
      if (!dbus_message_iter_append_basic (&sub, DBUS_TYPE_STRING,
					   &services[i]))
	{
	  dbus_free_string_array (services);
	  dbus_message_unref (reply);
	  BUS_SET_OOM (error);
	  return FALSE;
	}
      ++i;
    }

  dbus_free_string_array (services);

  if (!dbus_message_iter_close_container (&iter, &sub))
    {
      dbus_message_unref (reply);
      BUS_SET_OOM (error);
      return FALSE;
    }

  if (!bus_transaction_send_from_driver (transaction, connection, reply))
    {
      dbus_message_unref (reply);
      BUS_SET_OOM (error);
      return FALSE;
    }
  else
    {
      dbus_message_unref (reply);
      return TRUE;
    }
}

static dbus_bool_t
bus_driver_handle_acquire_service (DBusConnection *connection,
                                   BusTransaction *transaction,
                                   DBusMessage    *message,
                                   DBusError      *error)
{
  DBusMessage *reply;
  DBusString service_name;
  const char *name;
  dbus_uint32_t service_reply;
  dbus_uint32_t flags;
  dbus_bool_t retval;
  BusRegistry *registry;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);
  
  registry = bus_connection_get_registry (connection);
  
  if (!dbus_message_get_args (message, error,
                              DBUS_TYPE_STRING, &name,
                              DBUS_TYPE_UINT32, &flags,
                              DBUS_TYPE_INVALID))
    return FALSE;
  
  _dbus_verbose ("Trying to own name %s with flags 0x%x\n", name, flags);
  
  retval = FALSE;
  reply = NULL;

  _dbus_string_init_const (&service_name, name);

  if (!bus_registry_acquire_service (registry, connection,
                                     &service_name, flags,
                                     &service_reply, transaction,
                                     error))
    goto out;
  
  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    {
      BUS_SET_OOM (error);
      goto out;
    }

  if (!dbus_message_append_args (reply, DBUS_TYPE_UINT32, &service_reply, DBUS_TYPE_INVALID))
    {
      BUS_SET_OOM (error);
      goto out;
    }

  if (!bus_transaction_send_from_driver (transaction, connection, reply))
    {
      BUS_SET_OOM (error);
      goto out;
    }

  retval = TRUE;
  
 out:
  if (reply)
    dbus_message_unref (reply);
  return retval;
} 

static dbus_bool_t
bus_driver_handle_release_service (DBusConnection *connection,
                                   BusTransaction *transaction,
                                   DBusMessage    *message,
                                   DBusError      *error)
{
  DBusMessage *reply;
  DBusString service_name;
  const char *name;
  dbus_uint32_t service_reply;
  dbus_bool_t retval;
  BusRegistry *registry;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  registry = bus_connection_get_registry (connection);

  if (!dbus_message_get_args (message, error,
                              DBUS_TYPE_STRING, &name,
                              DBUS_TYPE_INVALID))
    return FALSE;

  _dbus_verbose ("Trying to release name %s\n", name);

  retval = FALSE;
  reply = NULL;

  _dbus_string_init_const (&service_name, name);

  if (!bus_registry_release_service (registry, connection,
                                     &service_name, &service_reply,
                                     transaction, error))
    goto out;

  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    {
      BUS_SET_OOM (error);
      goto out;
    }

  if (!dbus_message_append_args (reply, DBUS_TYPE_UINT32, &service_reply, DBUS_TYPE_INVALID))
    {
      BUS_SET_OOM (error);
      goto out;
    }

  if (!bus_transaction_send_from_driver (transaction, connection, reply))
    {
      BUS_SET_OOM (error);
      goto out;
    }

  retval = TRUE;

 out:
  if (reply)
    dbus_message_unref (reply);
  return retval;
}

static dbus_bool_t
bus_driver_handle_service_exists (DBusConnection *connection,
                                  BusTransaction *transaction,
                                  DBusMessage    *message,
                                  DBusError      *error)
{
  DBusMessage *reply;
  DBusString service_name;
  BusService *service;
  dbus_bool_t service_exists;
  const char *name;
  dbus_bool_t retval;
  BusRegistry *registry;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);
  
  registry = bus_connection_get_registry (connection);
  
  if (!dbus_message_get_args (message, error,
                              DBUS_TYPE_STRING, &name,
                              DBUS_TYPE_INVALID))
    return FALSE;

  retval = FALSE;

  if (strcmp (name, DBUS_SERVICE_DBUS) == 0)
    {
      service_exists = TRUE;
    }
  else
    {
      _dbus_string_init_const (&service_name, name);
      service = bus_registry_lookup (registry, &service_name);
      service_exists = service != NULL;
    }
  
  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    {
      BUS_SET_OOM (error);
      goto out;
    }

  if (!dbus_message_append_args (reply,
                                 DBUS_TYPE_BOOLEAN, &service_exists,
                                 0))
    {
      BUS_SET_OOM (error);
      goto out;
    }

  if (!bus_transaction_send_from_driver (transaction, connection, reply))
    {
      BUS_SET_OOM (error);
      goto out;
    }

  retval = TRUE;
  
 out:
  if (reply)
    dbus_message_unref (reply);

  return retval;
}

static dbus_bool_t
bus_driver_handle_activate_service (DBusConnection *connection,
                                    BusTransaction *transaction,
                                    DBusMessage    *message,
                                    DBusError      *error)
{
  dbus_uint32_t flags;
  const char *name;
  dbus_bool_t retval;
  BusActivation *activation;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);
  
  activation = bus_connection_get_activation (connection);
  
  if (!dbus_message_get_args (message, error,
                              DBUS_TYPE_STRING, &name,
                              DBUS_TYPE_UINT32, &flags,
                              DBUS_TYPE_INVALID))
    {
      _DBUS_ASSERT_ERROR_IS_SET (error);
      _dbus_verbose ("No memory to get arguments to StartServiceByName\n");
      return FALSE;
    }

  retval = FALSE;

  if (!bus_activation_activate_service (activation, connection, transaction, FALSE,
                                        message, name, error))
    {
      _DBUS_ASSERT_ERROR_IS_SET (error);
      _dbus_verbose ("bus_activation_activate_service() failed\n");
      goto out;
    }

  retval = TRUE;
  
 out:
  return retval;
}

static dbus_bool_t
send_ack_reply (DBusConnection *connection,
                BusTransaction *transaction,
                DBusMessage    *message,
                DBusError      *error)
{
  DBusMessage *reply;

  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    {
      BUS_SET_OOM (error);
      return FALSE;
    }

  if (!bus_transaction_send_from_driver (transaction, connection, reply))
    {
      BUS_SET_OOM (error);
      dbus_message_unref (reply);
      return FALSE;
    }

  dbus_message_unref (reply);
  
  return TRUE;
}

static dbus_bool_t
bus_driver_handle_update_activation_environment (DBusConnection *connection,
                                                 BusTransaction *transaction,
                                                 DBusMessage    *message,
                                                 DBusError      *error)
{
  dbus_bool_t retval;
  BusActivation *activation;
  DBusMessageIter iter;
  DBusMessageIter dict_iter;
  DBusMessageIter dict_entry_iter;
  int msg_type;
  int array_type;
  int key_type;
  DBusList *keys, *key_link;
  DBusList *values, *value_link;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  activation = bus_connection_get_activation (connection);

  dbus_message_iter_init (message, &iter);

  /* The message signature has already been checked for us,
   * so let's just assert it's right.
   */
  msg_type = dbus_message_iter_get_arg_type (&iter);

  _dbus_assert (msg_type == DBUS_TYPE_ARRAY);

  dbus_message_iter_recurse (&iter, &dict_iter);

  retval = FALSE;

  /* Then loop through the sent dictionary, add the location of
   * the environment keys and values to lists. The result will
   * be in reverse order, so we don't have to constantly search
   * for the end of the list in a loop.
   */
  keys = NULL;
  values = NULL;
  while ((array_type = dbus_message_iter_get_arg_type (&dict_iter)) == DBUS_TYPE_DICT_ENTRY)
    {
      dbus_message_iter_recurse (&dict_iter, &dict_entry_iter);

      while ((key_type = dbus_message_iter_get_arg_type (&dict_entry_iter)) == DBUS_TYPE_STRING)
        {
          char *key;
          char *value;
          int value_type;

          dbus_message_iter_get_basic (&dict_entry_iter, &key);
          dbus_message_iter_next (&dict_entry_iter);

          value_type = dbus_message_iter_get_arg_type (&dict_entry_iter);

          if (value_type != DBUS_TYPE_STRING)
            break;

          dbus_message_iter_get_basic (&dict_entry_iter, &value);

          if (!_dbus_list_append (&keys, key))
            {
              BUS_SET_OOM (error);
              break;
            }

          if (!_dbus_list_append (&values, value))
            {
              BUS_SET_OOM (error);
              break;
            }

          dbus_message_iter_next (&dict_entry_iter);
        }

      if (key_type != DBUS_TYPE_INVALID)
        break;

      dbus_message_iter_next (&dict_iter);
    }

  if (array_type != DBUS_TYPE_INVALID)
    goto out;

  _dbus_assert (_dbus_list_get_length (&keys) == _dbus_list_get_length (&values));

  key_link = keys;
  value_link = values;
  while (key_link != NULL)
  {
      const char *key;
      const char *value;

      key = key_link->data;
      value = value_link->data;

      if (!bus_activation_set_environment_variable (activation,
                                                    key, value, error))
      {
          _DBUS_ASSERT_ERROR_IS_SET (error);
          _dbus_verbose ("bus_activation_set_environment_variable() failed\n");
          break;
      }
      key_link = _dbus_list_get_next_link (&keys, key_link);
      value_link = _dbus_list_get_next_link (&values, value_link);
  }

  /* FIXME: We can fail early having set only some of the environment variables,
   * (because of OOM failure).  It's sort of hard to fix and it doesn't really
   * matter, so we're punting for now.
   */
  if (key_link != NULL)
    goto out;

  if (!send_ack_reply (connection, transaction,
                       message, error))
    goto out;

  retval = TRUE;

 out:
  _dbus_list_clear (&keys);
  _dbus_list_clear (&values);
  return retval;
}

static dbus_bool_t
bus_driver_handle_add_match (DBusConnection *connection,
                             BusTransaction *transaction,
                             DBusMessage    *message,
                             DBusError      *error)
{
  BusMatchRule *rule;
  const char *text;
  DBusString str;
  BusMatchmaker *matchmaker;
  
  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  text = NULL;
  rule = NULL;

  if (bus_connection_get_n_match_rules (connection) >=
      bus_context_get_max_match_rules_per_connection (bus_transaction_get_context (transaction)))
    {
      dbus_set_error (error, DBUS_ERROR_LIMITS_EXCEEDED,
                      "Connection \"%s\" is not allowed to add more match rules "
                      "(increase limits in configuration file if required)",
                      bus_connection_is_active (connection) ?
                      bus_connection_get_name (connection) :
                      "(inactive)");
      goto failed;
    }
  
  if (!dbus_message_get_args (message, error,
                              DBUS_TYPE_STRING, &text,
                              DBUS_TYPE_INVALID))
    {
      _dbus_verbose ("No memory to get arguments to AddMatch\n");
      goto failed;
    }

  _dbus_string_init_const (&str, text);

  rule = bus_match_rule_parse (connection, &str, error);
  if (rule == NULL)
    goto failed;

  matchmaker = bus_connection_get_matchmaker (connection);

  if (!bus_matchmaker_add_rule (matchmaker, rule))
    {
      BUS_SET_OOM (error);
      goto failed;
    }

  if (!send_ack_reply (connection, transaction,
                       message, error))
    {
      bus_matchmaker_remove_rule (matchmaker, rule);
      goto failed;
    }
  
  bus_match_rule_unref (rule);
  
  return TRUE;

 failed:
  _DBUS_ASSERT_ERROR_IS_SET (error);
  if (rule)
    bus_match_rule_unref (rule);
  return FALSE;
}

static dbus_bool_t
bus_driver_handle_remove_match (DBusConnection *connection,
                                BusTransaction *transaction,
                                DBusMessage    *message,
                                DBusError      *error)
{
  BusMatchRule *rule;
  const char *text;
  DBusString str;
  BusMatchmaker *matchmaker;
  
  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  text = NULL;
  rule = NULL;
  
  if (!dbus_message_get_args (message, error,
                              DBUS_TYPE_STRING, &text,
                              DBUS_TYPE_INVALID))
    {
      _dbus_verbose ("No memory to get arguments to RemoveMatch\n");
      goto failed;
    }

  _dbus_string_init_const (&str, text);

  rule = bus_match_rule_parse (connection, &str, error);
  if (rule == NULL)
    goto failed;

  /* Send the ack before we remove the rule, since the ack is undone
   * on transaction cancel, but rule removal isn't.
   */
  if (!send_ack_reply (connection, transaction,
                       message, error))
    goto failed;
  
  matchmaker = bus_connection_get_matchmaker (connection);

  if (!bus_matchmaker_remove_rule_by_value (matchmaker, rule, error))
    goto failed;

  bus_match_rule_unref (rule);
  
  return TRUE;

 failed:
  _DBUS_ASSERT_ERROR_IS_SET (error);
  if (rule)
    bus_match_rule_unref (rule);
  return FALSE;
}

static dbus_bool_t
bus_driver_handle_get_service_owner (DBusConnection *connection,
				     BusTransaction *transaction,
				     DBusMessage    *message,
				     DBusError      *error)
{
  const char *text;
  const char *base_name;
  DBusString str;
  BusRegistry *registry;
  BusService *service;
  DBusMessage *reply;
  
  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  registry = bus_connection_get_registry (connection);

  text = NULL;
  reply = NULL;

  if (! dbus_message_get_args (message, error,
			       DBUS_TYPE_STRING, &text,
			       DBUS_TYPE_INVALID))
      goto failed;

  _dbus_string_init_const (&str, text);
  service = bus_registry_lookup (registry, &str);
  if (service == NULL &&
      _dbus_string_equal_c_str (&str, DBUS_SERVICE_DBUS))
    {
      /* ORG_FREEDESKTOP_DBUS owns itself */
      base_name = DBUS_SERVICE_DBUS;
    }
  else if (service == NULL)
    {
      dbus_set_error (error, 
                      DBUS_ERROR_NAME_HAS_NO_OWNER,
                      "Could not get owner of name '%s': no such name", text);
      goto failed;
    }
  else
    {
      base_name = bus_connection_get_name (bus_service_get_primary_owners_connection (service));
      if (base_name == NULL)
        {
          /* FIXME - how is this error possible? */
          dbus_set_error (error,
                          DBUS_ERROR_FAILED,
                          "Could not determine unique name for '%s'", text);
          goto failed;
        }
      _dbus_assert (*base_name == ':');      
    }

  _dbus_assert (base_name != NULL);

  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    goto oom;

  if (! dbus_message_append_args (reply, 
				  DBUS_TYPE_STRING, &base_name,
				  DBUS_TYPE_INVALID))
    goto oom;
  
  if (! bus_transaction_send_from_driver (transaction, connection, reply))
    goto oom;

  dbus_message_unref (reply);

  return TRUE;

 oom:
  BUS_SET_OOM (error);

 failed:
  _DBUS_ASSERT_ERROR_IS_SET (error);
  if (reply)
    dbus_message_unref (reply);
  return FALSE;
}

static dbus_bool_t
bus_driver_handle_list_queued_owners (DBusConnection *connection,
				      BusTransaction *transaction,
				      DBusMessage    *message,
				      DBusError      *error)
{
  const char *text;
  DBusList *base_names;
  DBusList *link;
  DBusString str;
  BusRegistry *registry;
  BusService *service;
  DBusMessage *reply;
  DBusMessageIter iter, array_iter;
  char *dbus_service_name = DBUS_SERVICE_DBUS;
  
  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  registry = bus_connection_get_registry (connection);

  base_names = NULL;
  text = NULL;
  reply = NULL;

  if (! dbus_message_get_args (message, error,
			       DBUS_TYPE_STRING, &text,
			       DBUS_TYPE_INVALID))
      goto failed;

  _dbus_string_init_const (&str, text);
  service = bus_registry_lookup (registry, &str);
  if (service == NULL &&
      _dbus_string_equal_c_str (&str, DBUS_SERVICE_DBUS))
    {
      /* ORG_FREEDESKTOP_DBUS owns itself */
      if (! _dbus_list_append (&base_names, dbus_service_name))
        goto oom;
    }
  else if (service == NULL)
    {
      dbus_set_error (error, 
                      DBUS_ERROR_NAME_HAS_NO_OWNER,
                      "Could not get owners of name '%s': no such name", text);
      goto failed;
    }
  else
    {
      if (!bus_service_list_queued_owners (service, 
                                           &base_names,
                                           error))
        goto failed;
    }

  _dbus_assert (base_names != NULL);

  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    goto oom;

  dbus_message_iter_init_append (reply, &iter);
  if (!dbus_message_iter_open_container (&iter,
                                         DBUS_TYPE_ARRAY,
                                         DBUS_TYPE_STRING_AS_STRING,
                                         &array_iter))
    goto oom;
  
  link = _dbus_list_get_first_link (&base_names);
  while (link != NULL)
    {
      char *uname;

      _dbus_assert (link->data != NULL);
      uname = (char *)link->data;
    
      if (!dbus_message_iter_append_basic (&array_iter, 
                                           DBUS_TYPE_STRING,
                                           &uname))
        goto oom;

      link = _dbus_list_get_next_link (&base_names, link);
    }

  if (! dbus_message_iter_close_container (&iter, &array_iter))
    goto oom;
                                    
 
  if (! bus_transaction_send_from_driver (transaction, connection, reply))
    goto oom;

  dbus_message_unref (reply);

  return TRUE;

 oom:
  BUS_SET_OOM (error);

 failed:
  _DBUS_ASSERT_ERROR_IS_SET (error);
  if (reply)
    dbus_message_unref (reply);

  if (base_names)
    _dbus_list_clear (&base_names);

  return FALSE;
}

static dbus_bool_t
bus_driver_handle_get_connection_unix_user (DBusConnection *connection,
                                            BusTransaction *transaction,
                                            DBusMessage    *message,
                                            DBusError      *error)
{
  const char *service;
  DBusString str;
  BusRegistry *registry;
  BusService *serv;
  DBusConnection *conn;
  DBusMessage *reply;
  unsigned long uid;
  dbus_uint32_t uid32;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  registry = bus_connection_get_registry (connection);

  service = NULL;
  reply = NULL;

  if (! dbus_message_get_args (message, error,
			       DBUS_TYPE_STRING, &service,
			       DBUS_TYPE_INVALID))
      goto failed;

  _dbus_verbose ("asked for UID of connection %s\n", service);

  _dbus_string_init_const (&str, service);
  serv = bus_registry_lookup (registry, &str);
  if (serv == NULL)
    {
      dbus_set_error (error, 
		      DBUS_ERROR_NAME_HAS_NO_OWNER,
		      "Could not get UID of name '%s': no such name", service);
      goto failed;
    }

  conn = bus_service_get_primary_owners_connection (serv);

  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    goto oom;

  if (!dbus_connection_get_unix_user (conn, &uid))
    {
      dbus_set_error (error,
                      DBUS_ERROR_FAILED,
                      "Could not determine UID for '%s'", service);
      goto failed;
    }

  uid32 = uid;
  if (! dbus_message_append_args (reply,
                                  DBUS_TYPE_UINT32, &uid32,
                                  DBUS_TYPE_INVALID))
    goto oom;

  if (! bus_transaction_send_from_driver (transaction, connection, reply))
    goto oom;

  dbus_message_unref (reply);

  return TRUE;

 oom:
  BUS_SET_OOM (error);

 failed:
  _DBUS_ASSERT_ERROR_IS_SET (error);
  if (reply)
    dbus_message_unref (reply);
  return FALSE;
}

static dbus_bool_t
bus_driver_handle_get_connection_unix_process_id (DBusConnection *connection,
						  BusTransaction *transaction,
						  DBusMessage    *message,
						  DBusError      *error)
{
  const char *service;
  DBusString str;
  BusRegistry *registry;
  BusService *serv;
  DBusConnection *conn;
  DBusMessage *reply;
  unsigned long pid;
  dbus_uint32_t pid32;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  registry = bus_connection_get_registry (connection);

  service = NULL;
  reply = NULL;

  if (! dbus_message_get_args (message, error,
			       DBUS_TYPE_STRING, &service,
			       DBUS_TYPE_INVALID))
      goto failed;

  _dbus_verbose ("asked for PID of connection %s\n", service);

  _dbus_string_init_const (&str, service);
  serv = bus_registry_lookup (registry, &str);
  if (serv == NULL)
    {
      dbus_set_error (error, 
		      DBUS_ERROR_NAME_HAS_NO_OWNER,
		      "Could not get PID of name '%s': no such name", service);
      goto failed;
    }

  conn = bus_service_get_primary_owners_connection (serv);

  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    goto oom;

  if (!dbus_connection_get_unix_process_id (conn, &pid))
    {
      dbus_set_error (error,
                      DBUS_ERROR_UNIX_PROCESS_ID_UNKNOWN,
                      "Could not determine PID for '%s'", service);
      goto failed;
    }

  pid32 = pid;
  if (! dbus_message_append_args (reply,
                                  DBUS_TYPE_UINT32, &pid32,
                                  DBUS_TYPE_INVALID))
    goto oom;

  if (! bus_transaction_send_from_driver (transaction, connection, reply))
    goto oom;

  dbus_message_unref (reply);

  return TRUE;

 oom:
  BUS_SET_OOM (error);

 failed:
  _DBUS_ASSERT_ERROR_IS_SET (error);
  if (reply)
    dbus_message_unref (reply);
  return FALSE;
}

static dbus_bool_t
bus_driver_handle_get_adt_audit_session_data (DBusConnection *connection,
					      BusTransaction *transaction,
					      DBusMessage    *message,
					      DBusError      *error)
{
  const char *service;
  DBusString str;
  BusRegistry *registry;
  BusService *serv;
  DBusConnection *conn;
  DBusMessage *reply;
  void *data = NULL;
  dbus_uint32_t data_size;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  registry = bus_connection_get_registry (connection);

  service = NULL;
  reply = NULL;

  if (! dbus_message_get_args (message, error,
			       DBUS_TYPE_STRING, &service,
			       DBUS_TYPE_INVALID))
      goto failed;

  _dbus_verbose ("asked for audit session data for connection %s\n", service);

  _dbus_string_init_const (&str, service);
  serv = bus_registry_lookup (registry, &str);
  if (serv == NULL)
    {
      dbus_set_error (error, 
		      DBUS_ERROR_NAME_HAS_NO_OWNER,
		      "Could not get audit session data for name '%s': no such name", service);
      goto failed;
    }

  conn = bus_service_get_primary_owners_connection (serv);

  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    goto oom;

  if (!dbus_connection_get_adt_audit_session_data (conn, &data, &data_size) || data == NULL)
    {
      dbus_set_error (error,
                      DBUS_ERROR_ADT_AUDIT_DATA_UNKNOWN,
                      "Could not determine audit session data for '%s'", service);
      goto failed;
    }

  if (! dbus_message_append_args (reply,
                                  DBUS_TYPE_ARRAY, DBUS_TYPE_BYTE, &data, data_size,
                                  DBUS_TYPE_INVALID))
    goto oom;

  if (! bus_transaction_send_from_driver (transaction, connection, reply))
    goto oom;

  dbus_message_unref (reply);

  return TRUE;

 oom:
  BUS_SET_OOM (error);

 failed:
  _DBUS_ASSERT_ERROR_IS_SET (error);
  if (reply)
    dbus_message_unref (reply);
  return FALSE;
}

static dbus_bool_t
bus_driver_handle_get_connection_selinux_security_context (DBusConnection *connection,
							   BusTransaction *transaction,
							   DBusMessage    *message,
							   DBusError      *error)
{
  const char *service;
  DBusString str;
  BusRegistry *registry;
  BusService *serv;
  DBusConnection *conn;
  DBusMessage *reply;
  BusSELinuxID *context;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  registry = bus_connection_get_registry (connection);

  service = NULL;
  reply = NULL;

  if (! dbus_message_get_args (message, error,
			       DBUS_TYPE_STRING, &service,
			       DBUS_TYPE_INVALID))
      goto failed;

  _dbus_verbose ("asked for security context of connection %s\n", service);

  _dbus_string_init_const (&str, service);
  serv = bus_registry_lookup (registry, &str);
  if (serv == NULL)
    {
      dbus_set_error (error, 
		      DBUS_ERROR_NAME_HAS_NO_OWNER,
		      "Could not get security context of name '%s': no such name", service);
      goto failed;
    }

  conn = bus_service_get_primary_owners_connection (serv);

  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    goto oom;

  context = bus_connection_get_selinux_id (conn);
  if (!context)
    {
      dbus_set_error (error,
                      DBUS_ERROR_SELINUX_SECURITY_CONTEXT_UNKNOWN,
                      "Could not determine security context for '%s'", service);
      goto failed;
    }

  if (! bus_selinux_append_context (reply, context, error))
    goto failed;

  if (! bus_transaction_send_from_driver (transaction, connection, reply))
    goto oom;

  dbus_message_unref (reply);

  return TRUE;

 oom:
  BUS_SET_OOM (error);

 failed:
  _DBUS_ASSERT_ERROR_IS_SET (error);
  if (reply)
    dbus_message_unref (reply);
  return FALSE;
}

static dbus_bool_t
bus_driver_handle_reload_config (DBusConnection *connection,
				 BusTransaction *transaction,
				 DBusMessage    *message,
				 DBusError      *error)
{
  BusContext *context;
  DBusMessage *reply;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  reply = NULL;
  
  context = bus_connection_get_context (connection);
  if (!bus_context_reload_config (context, error))
    goto failed;

  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    goto oom;

  if (! bus_transaction_send_from_driver (transaction, connection, reply))
    goto oom;

  dbus_message_unref (reply);
  return TRUE;

 oom:
  BUS_SET_OOM (error);

 failed:
  _DBUS_ASSERT_ERROR_IS_SET (error);
  if (reply)
    dbus_message_unref (reply);
  return FALSE;
}

static dbus_bool_t
bus_driver_handle_get_id (DBusConnection *connection,
                          BusTransaction *transaction,
                          DBusMessage    *message,
                          DBusError      *error)
{
  BusContext *context;
  DBusMessage *reply;
  DBusString uuid;
  const char *v_STRING;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  if (!_dbus_string_init (&uuid))
    {
      BUS_SET_OOM (error);
      return FALSE;
    }

  reply = NULL;
  
  context = bus_connection_get_context (connection);
  if (!bus_context_get_id (context, &uuid))
    goto oom;

  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    goto oom;

  v_STRING = _dbus_string_get_const_data (&uuid);
  if (!dbus_message_append_args (reply,
                                 DBUS_TYPE_STRING, &v_STRING,
                                 DBUS_TYPE_INVALID))
    goto oom;
  
  _dbus_assert (dbus_message_has_signature (reply, "s"));
  
  if (! bus_transaction_send_from_driver (transaction, connection, reply))
    goto oom;

  _dbus_string_free (&uuid);  
  dbus_message_unref (reply);
  return TRUE;

 oom:
  _DBUS_ASSERT_ERROR_IS_CLEAR (error);
  
  BUS_SET_OOM (error);

  if (reply)
    dbus_message_unref (reply);
  _dbus_string_free (&uuid);  
  return FALSE;
}

/* For speed it might be useful to sort this in order of
 * frequency of use (but doesn't matter with only a few items
 * anyhow)
 */
static struct
{
  const char *name;
  const char *in_args;
  const char *out_args;
  dbus_bool_t (* handler) (DBusConnection *connection,
                           BusTransaction *transaction,
                           DBusMessage    *message,
                           DBusError      *error);
} message_handlers[] = {
  { "Hello",
    "",
    DBUS_TYPE_STRING_AS_STRING,
    bus_driver_handle_hello },  
  { "RequestName",
    DBUS_TYPE_STRING_AS_STRING DBUS_TYPE_UINT32_AS_STRING,
    DBUS_TYPE_UINT32_AS_STRING,
    bus_driver_handle_acquire_service },
  { "ReleaseName",
    DBUS_TYPE_STRING_AS_STRING,
    DBUS_TYPE_UINT32_AS_STRING,
    bus_driver_handle_release_service },
  { "StartServiceByName",
    DBUS_TYPE_STRING_AS_STRING DBUS_TYPE_UINT32_AS_STRING,
    DBUS_TYPE_UINT32_AS_STRING,
    bus_driver_handle_activate_service },
  { "UpdateActivationEnvironment",
    DBUS_TYPE_ARRAY_AS_STRING DBUS_DICT_ENTRY_BEGIN_CHAR_AS_STRING DBUS_TYPE_STRING_AS_STRING DBUS_TYPE_STRING_AS_STRING DBUS_DICT_ENTRY_END_CHAR_AS_STRING,
    "",
    bus_driver_handle_update_activation_environment },
  { "NameHasOwner",
    DBUS_TYPE_STRING_AS_STRING,
    DBUS_TYPE_BOOLEAN_AS_STRING,
    bus_driver_handle_service_exists },
  { "ListNames",
    "",
    DBUS_TYPE_ARRAY_AS_STRING DBUS_TYPE_STRING_AS_STRING,
    bus_driver_handle_list_services },
  { "ListActivatableNames",
    "",
    DBUS_TYPE_ARRAY_AS_STRING DBUS_TYPE_STRING_AS_STRING,
    bus_driver_handle_list_activatable_services },
  { "AddMatch",
    DBUS_TYPE_STRING_AS_STRING,
    "",
    bus_driver_handle_add_match },
  { "RemoveMatch",
    DBUS_TYPE_STRING_AS_STRING,
    "",
    bus_driver_handle_remove_match },
  { "GetNameOwner",
    DBUS_TYPE_STRING_AS_STRING,
    DBUS_TYPE_STRING_AS_STRING,
    bus_driver_handle_get_service_owner },
  { "ListQueuedOwners",
    DBUS_TYPE_STRING_AS_STRING,
    DBUS_TYPE_ARRAY_AS_STRING DBUS_TYPE_STRING_AS_STRING,
    bus_driver_handle_list_queued_owners },
  { "GetConnectionUnixUser",
    DBUS_TYPE_STRING_AS_STRING,
    DBUS_TYPE_UINT32_AS_STRING,
    bus_driver_handle_get_connection_unix_user },
  { "GetConnectionUnixProcessID",
    DBUS_TYPE_STRING_AS_STRING,
    DBUS_TYPE_UINT32_AS_STRING,
    bus_driver_handle_get_connection_unix_process_id },
  { "GetAdtAuditSessionData",
    DBUS_TYPE_STRING_AS_STRING,
    DBUS_TYPE_ARRAY_AS_STRING DBUS_TYPE_BYTE_AS_STRING,
    bus_driver_handle_get_adt_audit_session_data },
  { "GetConnectionSELinuxSecurityContext",
    DBUS_TYPE_STRING_AS_STRING,
    DBUS_TYPE_ARRAY_AS_STRING DBUS_TYPE_BYTE_AS_STRING,
    bus_driver_handle_get_connection_selinux_security_context },
  { "ReloadConfig",
    "",
    "",
    bus_driver_handle_reload_config },
  { "GetId",
    "",
    DBUS_TYPE_STRING_AS_STRING,
    bus_driver_handle_get_id }
};

static dbus_bool_t
write_args_for_direction (DBusString *xml,
			  const char *signature,
			  dbus_bool_t in)
{
  DBusTypeReader typereader;
  DBusString sigstr;
  int current_type;
  
  _dbus_string_init_const (&sigstr, signature);
  _dbus_type_reader_init_types_only (&typereader, &sigstr, 0);
      
  while ((current_type = _dbus_type_reader_get_current_type (&typereader)) != DBUS_TYPE_INVALID)
    {
      const DBusString *subsig;
      int start, len;

      _dbus_type_reader_get_signature (&typereader, &subsig, &start, &len);
      if (!_dbus_string_append_printf (xml, "      <arg direction=\"%s\" type=\"",
				       in ? "in" : "out"))
	goto oom;
      if (!_dbus_string_append_len (xml,
				    _dbus_string_get_const_data (subsig) + start,
				    len))
	goto oom;
      if (!_dbus_string_append (xml, "\"/>\n"))
	goto oom;

      _dbus_type_reader_next (&typereader);
    }
  return TRUE;
 oom:
  return FALSE;
}

dbus_bool_t
bus_driver_generate_introspect_string (DBusString *xml)
{
  int i;

  if (!_dbus_string_append (xml, DBUS_INTROSPECT_1_0_XML_DOCTYPE_DECL_NODE))
    return FALSE;
  if (!_dbus_string_append (xml, "<node>\n"))
    return FALSE;
  if (!_dbus_string_append_printf (xml, "  <interface name=\"%s\">\n", DBUS_INTERFACE_INTROSPECTABLE))
    return FALSE;
  if (!_dbus_string_append (xml, "    <method name=\"Introspect\">\n"))
    return FALSE;
  if (!_dbus_string_append_printf (xml, "      <arg name=\"data\" direction=\"out\" type=\"%s\"/>\n", DBUS_TYPE_STRING_AS_STRING))
    return FALSE;
  if (!_dbus_string_append (xml, "    </method>\n"))
    return FALSE;
  if (!_dbus_string_append (xml, "  </interface>\n"))
    return FALSE;

  if (!_dbus_string_append_printf (xml, "  <interface name=\"%s\">\n",
                                   DBUS_INTERFACE_DBUS))
    return FALSE;

  i = 0;
  while (i < _DBUS_N_ELEMENTS (message_handlers))
    {
	  
      if (!_dbus_string_append_printf (xml, "    <method name=\"%s\">\n",
                                       message_handlers[i].name))
        return FALSE;

      if (!write_args_for_direction (xml, message_handlers[i].in_args, TRUE))
	return FALSE;

      if (!write_args_for_direction (xml, message_handlers[i].out_args, FALSE))
	return FALSE;

      if (!_dbus_string_append (xml, "    </method>\n"))
	return FALSE;
      
      ++i;
    }

  if (!_dbus_string_append_printf (xml, "    <signal name=\"NameOwnerChanged\">\n"))
    return FALSE;
  
  if (!_dbus_string_append_printf (xml, "      <arg type=\"s\"/>\n"))
    return FALSE;
  
  if (!_dbus_string_append_printf (xml, "      <arg type=\"s\"/>\n"))
    return FALSE;
  
  if (!_dbus_string_append_printf (xml, "      <arg type=\"s\"/>\n"))
    return FALSE;
  
  if (!_dbus_string_append_printf (xml, "    </signal>\n"))
    return FALSE;



  if (!_dbus_string_append_printf (xml, "    <signal name=\"NameLost\">\n"))
    return FALSE;
  
  if (!_dbus_string_append_printf (xml, "      <arg type=\"s\"/>\n"))
    return FALSE;
  
  if (!_dbus_string_append_printf (xml, "    </signal>\n"))
    return FALSE;



  if (!_dbus_string_append_printf (xml, "    <signal name=\"NameAcquired\">\n"))
    return FALSE;
  
  if (!_dbus_string_append_printf (xml, "      <arg type=\"s\"/>\n"))
    return FALSE;
  
  if (!_dbus_string_append_printf (xml, "    </signal>\n"))
    return FALSE;

  if (!_dbus_string_append (xml, "  </interface>\n"))
    return FALSE;
  
  if (!_dbus_string_append (xml, "</node>\n"))
    return FALSE;

  return TRUE;
}

static dbus_bool_t
bus_driver_handle_introspect (DBusConnection *connection,
                              BusTransaction *transaction,
                              DBusMessage    *message,
                              DBusError      *error)
{
  DBusString xml;
  DBusMessage *reply;
  const char *v_STRING;

  _dbus_verbose ("Introspect() on bus driver\n");
  
  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  reply = NULL;

  if (! dbus_message_get_args (message, error,
			       DBUS_TYPE_INVALID))
    {
      _DBUS_ASSERT_ERROR_IS_SET (error);
      return FALSE;
    }

  if (!_dbus_string_init (&xml))
    {
      BUS_SET_OOM (error);
      return FALSE;
    }

  if (!bus_driver_generate_introspect_string (&xml))
    goto oom;

  v_STRING = _dbus_string_get_const_data (&xml);

  reply = dbus_message_new_method_return (message);
  if (reply == NULL)
    goto oom;

  if (! dbus_message_append_args (reply,
                                  DBUS_TYPE_STRING, &v_STRING,
                                  DBUS_TYPE_INVALID))
    goto oom;

  if (! bus_transaction_send_from_driver (transaction, connection, reply))
    goto oom;

  dbus_message_unref (reply);
  _dbus_string_free (&xml);

  return TRUE;

 oom:
  BUS_SET_OOM (error);

  if (reply)
    dbus_message_unref (reply);

  _dbus_string_free (&xml);
  
  return FALSE;
}

dbus_bool_t
bus_driver_handle_message (DBusConnection *connection,
                           BusTransaction *transaction,
			   DBusMessage    *message,
                           DBusError      *error)
{
  const char *name, *sender, *interface;
  int i;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  if (dbus_message_get_type (message) != DBUS_MESSAGE_TYPE_METHOD_CALL)
    {
      _dbus_verbose ("Driver got a non-method-call message, ignoring\n");
      return TRUE; /* we just ignore this */
    }

  if (dbus_message_is_method_call (message,
                                   DBUS_INTERFACE_INTROSPECTABLE,
                                   "Introspect"))
    return bus_driver_handle_introspect (connection, transaction, message, error);
  
  interface = dbus_message_get_interface (message);
  if (interface == NULL)
    interface = DBUS_INTERFACE_DBUS;
  
  _dbus_assert (dbus_message_get_member (message) != NULL);
  
  name = dbus_message_get_member (message);
  sender = dbus_message_get_sender (message);
  
  if (strcmp (interface,
              DBUS_INTERFACE_DBUS) != 0)
    {
      _dbus_verbose ("Driver got message to unknown interface \"%s\"\n",
                     interface);
      goto unknown;
    }
  
  _dbus_verbose ("Driver got a method call: %s\n",
		 dbus_message_get_member (message));
  
  /* security checks should have kept this from getting here */
  _dbus_assert (sender != NULL || strcmp (name, "Hello") == 0);
  
  i = 0;
  while (i < _DBUS_N_ELEMENTS (message_handlers))
    {
      if (strcmp (message_handlers[i].name, name) == 0)
        {
          _dbus_verbose ("Found driver handler for %s\n", name);

          if (!dbus_message_has_signature (message, message_handlers[i].in_args))
            {
              _DBUS_ASSERT_ERROR_IS_CLEAR (error);
              _dbus_verbose ("Call to %s has wrong args (%s, expected %s)\n",
                             name, dbus_message_get_signature (message),
                             message_handlers[i].in_args);
              
              dbus_set_error (error, DBUS_ERROR_INVALID_ARGS,
                              "Call to %s has wrong args (%s, expected %s)\n",
                              name, dbus_message_get_signature (message),
                              message_handlers[i].in_args);
              _DBUS_ASSERT_ERROR_IS_SET (error);
              return FALSE;
            }
          
          if ((* message_handlers[i].handler) (connection, transaction, message, error))
            {
              _DBUS_ASSERT_ERROR_IS_CLEAR (error);
              _dbus_verbose ("Driver handler succeeded\n");
              return TRUE;
            }
          else
            {
              _DBUS_ASSERT_ERROR_IS_SET (error);
              _dbus_verbose ("Driver handler returned failure\n");
              return FALSE;
            }
        }
      
      ++i;
    }

 unknown:
  _dbus_verbose ("No driver handler for message \"%s\"\n",
                 name);

  dbus_set_error (error, DBUS_ERROR_UNKNOWN_METHOD,
                  "%s does not understand message %s",
                  DBUS_SERVICE_DBUS, name);
  
  return FALSE;
}

void
bus_driver_remove_connection (DBusConnection *connection)
{
  /* FIXME 1.0 Does nothing for now, should unregister the connection
   * with the bus driver.
   */
}
