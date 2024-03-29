/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/* dbus-sockets.h Wrappers around socket features (internal to D-BUS implementation)
 * 
 * Copyright (C) 2005 Novell, Inc.
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

#ifndef DBUS_SOCKETS_H
#define DBUS_SOCKETS_H

#if defined(DBUS_WIN) || defined(DBUS_WINCE)



#ifndef STRICT
#define STRICT
#include <winsock2.h>
#undef STRICT
#endif
#include <winsock2.h>

#undef interface

#include <errno.h>

/* Make use of the fact that the WSAE* error codes don't
 * overlap with errno E* codes. Wrapper functions store
 * the return value from WSAGetLastError() in errno.
 */
#if defined(EPROTONOSUPPORT) || \
    defined(EAFNOSUPPORT) || \
    defined(EWOULDBLOCK)
#error This does not look like Win32 and the Microsoft C library
#endif

#define DBUS_SOCKET_IS_INVALID(s) ((SOCKET)(s) == INVALID_SOCKET)
#define DBUS_SOCKET_API_RETURNS_ERROR(n) ((n) == SOCKET_ERROR)
#define DBUS_SOCKET_SET_ERRNO() errno = WSAGetLastError()

#define DBUS_CLOSE_SOCKET(s) closesocket(s)

#else

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#define DBUS_SOCKET_IS_INVALID(s) ((s) < 0)
#define DBUS_SOCKET_API_RETURNS_ERROR(n) ((n) < 0)
#define DBUS_SOCKET_SET_ERRNO()	/* empty */

#define DBUS_CLOSE_SOCKET(s) close(s)

#endif /* !Win32 */

#endif /* DBUS_SOCKETS_H */
