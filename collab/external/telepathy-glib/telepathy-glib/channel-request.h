/*
 * channel-request.h - proxy for a request to the channel dispatcher
 *
 * Copyright (C) 2009 Collabora Ltd. <http://www.collabora.co.uk/>
 * Copyright (C) 2009 Nokia Corporation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef TP_CHANNEL_REQUEST_H
#define TP_CHANNEL_REQUEST_H

#include <telepathy-glib/proxy.h>
#include <telepathy-glib/dbus.h>

G_BEGIN_DECLS

typedef struct _TpChannelRequest TpChannelRequest;
typedef struct _TpChannelRequestClass TpChannelRequestClass;
typedef struct _TpChannelRequestPrivate TpChannelRequestPrivate;
typedef struct _TpChannelRequestClassPrivate TpChannelRequestClassPrivate;

struct _TpChannelRequest {
    /*<private>*/
    TpProxy parent;
    TpChannelRequestPrivate *priv;
};

struct _TpChannelRequestClass {
    /*<private>*/
    TpProxyClass parent_class;
    GCallback _padding[7];
    TpChannelRequestClassPrivate *priv;
};

GType tp_channel_request_get_type (void);

#define TP_TYPE_CHANNEL_REQUEST \
  (tp_channel_request_get_type ())
#define TP_CHANNEL_REQUEST(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), TP_TYPE_CHANNEL_REQUEST, \
                               TpChannelRequest))
#define TP_CHANNEL_REQUEST_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST ((klass), TP_TYPE_CHANNEL_REQUEST, \
                            TpChannelRequestClass))
#define TP_IS_CHANNEL_REQUEST(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TP_TYPE_CHANNEL_REQUEST))
#define TP_IS_CHANNEL_REQUEST_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE ((klass), TP_TYPE_CHANNEL_REQUEST))
#define TP_CHANNEL_REQUEST_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), TP_TYPE_CHANNEL_REQUEST, \
                              TpChannelRequestClass))

TpChannelRequest *tp_channel_request_new (TpDBusDaemon *bus_daemon,
    const gchar *object_path, GHashTable *immutable_properties,
    GError **error);

void tp_channel_request_init_known_interfaces (void);

G_END_DECLS

#include <telepathy-glib/_gen/tp-cli-channel-request.h>

#endif
