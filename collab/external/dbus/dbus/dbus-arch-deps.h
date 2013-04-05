/* -*- mode: C; c-file-style: "gnu" -*- */
/* dbus-arch-deps.h Header with architecture/compiler specific information, installed to libdir
 *
 * Copyright (C) 2003 Red Hat, Inc.
 *
 * Licensed under the Academic Free License version 2.0
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
#if !defined (DBUS_INSIDE_DBUS_H) && !defined (DBUS_COMPILATION)
#error "Only <dbus/dbus.h> can be included directly, this file may disappear or change contents."
#endif

#ifndef DBUS_ARCH_DEPS_H
#define DBUS_ARCH_DEPS_H

#include <dbus/dbus-macros.h>
#include <nspr.h>

DBUS_BEGIN_DECLS

#ifdef HAVE_LONG_LONG
#define DBUS_HAVE_INT64 1

typedef PRInt64 dbus_int64_t;
typedef PRUint64 dbus_uint64_t;

#define DBUS_INT64_CONSTANT(val)  (val##L)
#define DBUS_UINT64_CONSTANT(val) (val##UL)

#else
#undef DBUS_HAVE_INT64
#undef DBUS_INT64_CONSTANT
#undef DBUS_UINT64_CONSTANT
#endif


typedef PRInt32 dbus_int32_t;
typedef PRUint32 dbus_uint32_t;

typedef PRInt16 dbus_int16_t;
typedef PRUint16 dbus_uint16_t;

/* This is not really arch-dependent, but it's not worth
 * creating an additional generated header just for this
 */
#define DBUS_MAJOR_VERSION 1
#define DBUS_MINOR_VERSION 3
#define DBUS_MICRO_VERSION 0

#define DBUS_VERSION_STRING "1.3.0"

#define DBUS_VERSION ((DBUS_MAJOR_VERSION << 16) | (DBUS_MINOR_VERSION << 8) | (DBUS_MICRO_VERSION)) 

DBUS_END_DECLS

#endif /* DBUS_ARCH_DEPS_H */
