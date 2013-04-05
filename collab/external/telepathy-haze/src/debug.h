/*
 * debug.h - header for haze's debug machinery for itself and libpurple
 * Copyright (C) 2007-2008 Collabora Ltd.
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

#include <glib.h>

void haze_debug_init(void);

void haze_debug (const gchar *format, ...)
    G_GNUC_PRINTF (1,2);

void haze_debug_set_flags_from_env (void);

#define DEBUG(format, ...) \
    haze_debug ("%s: " format, G_STRFUNC, ##__VA_ARGS__)
