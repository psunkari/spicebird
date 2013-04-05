/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*- */
/* config-loader-expat.c  expat XML loader
 *
 * Copyright (C) 2003 Red Hat, Inc.
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

#include "config-parser.h"
#include <dbus/dbus-internals.h>
#include <expat_config.h>
#include <expat.h>

static XML_Memory_Handling_Suite memsuite =
{
  dbus_malloc,
  dbus_realloc,
  dbus_free
};

typedef struct
{
  BusConfigParser *parser;
  const char *filename;
  DBusString content;
  DBusError *error;
  dbus_bool_t failed;
} ExpatParseContext;

static dbus_bool_t
process_content (ExpatParseContext *context)
{
  if (context->failed)
    return FALSE;

  if (_dbus_string_get_length (&context->content) > 0)
    {
      if (!bus_config_parser_content (context->parser,
                                      &context->content,
                                      context->error))
        {
          context->failed = TRUE;
          return FALSE;
        }
      _dbus_string_set_length (&context->content, 0);
    }

  return TRUE;
}

/* BEGIN SPICEBIRD CHANGES */
#define UTF8_ENCODE_MAX 4

#ifdef IS_LITTLE_ENDIAN
#define GET_LO(buf) (buf[0])
#define GET_HI(buf) (buf[1])
#else
#define GET_LO(buf) (buf[1])
#define GET_HI(buf) (buf[0])
#endif

/* Following function is taken from expat */
/*
Copyright (c) 1998, 1999, 2000 Thai Open Source Software Center Ltd
                               and Clark Cooper
Copyright (c) 2001, 2002, 2003, 2004, 2005, 2006 Expat maintainers.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

enum {  /* UTF8_cvalN is value of masked first byte of N byte sequence */
  UTF8_cval1 = 0x00,
  UTF8_cval2 = 0xc0,
  UTF8_cval3 = 0xe0,
  UTF8_cval4 = 0xf0
};

static void
_ConvertToUTF8(const char **fromP, const char *fromLim,
               char **toP, const char *toLim)
{
  const char *from;
  for (from = *fromP; from != fromLim; from += 2) {
    int plane;
    unsigned char lo2;
    unsigned char lo = GET_LO(from);
    unsigned char hi = GET_HI(from);
    switch (hi) {
    case 0:
      if (lo < 0x80) {
        if (*toP == toLim) {
          *fromP = from;
          return;
        }
        *(*toP)++ = lo;
        break;
      }
      /* fall through */
    case 0x1: case 0x2: case 0x3:
    case 0x4: case 0x5: case 0x6: case 0x7:
      if (toLim -  *toP < 2) {
        *fromP = from;
        return;
      }
      *(*toP)++ = ((lo >> 6) | (hi << 2) |  UTF8_cval2);
      *(*toP)++ = ((lo & 0x3f) | 0x80);
      break;
    default:
      if (toLim -  *toP < 3)  {
        *fromP = from;
        return;
      }
      /* 16 bits divided 4, 6, 6 amongst 3 bytes */
      *(*toP)++ = ((hi >> 4) | UTF8_cval3);
      *(*toP)++ = (((hi & 0xf) << 2) | (lo >> 6) | 0x80);
      *(*toP)++ = ((lo & 0x3f) | 0x80);
      break;
    case 0xD8: case 0xD9: case 0xDA: case 0xDB:
      if (toLim -  *toP < 4) {
        *fromP = from;
        return;
      }
      plane = (((hi & 0x3) << 2) | ((lo >> 6) & 0x3)) + 1;
      *(*toP)++ = ((plane >> 2) | UTF8_cval4);
      *(*toP)++ = (((lo >> 2) & 0xF) | ((plane & 0x3) << 4) | 0x80);
      from += 2;
      lo2 = GET_LO(from);
      *(*toP)++ = (((lo & 0x3) << 4)
                   | ((GET_HI(from) & 0x3) << 2)
                   | (lo2 >> 6)
                   | 0x80);
      *(*toP)++ = ((lo2 & 0x3f) | 0x80);
      break;
    }
  }
  *fromP = from;
}

static char *
ConvertToUTF8Length (const XML_Char *str, int length)
{
#ifndef XML_UNICODE
  return (char *)str;
#else
  const XML_Char *end;

  int new_length;
  char *new_str;
  char *new_end;

  if (length == -1)
    {
      length = 0;
      for (end = str; *end; end++)
        length++;
    }

  new_length = length * UTF8_ENCODE_MAX + 1;
  new_str = dbus_malloc (new_length * sizeof (char));
  new_end = new_str;

  _ConvertToUTF8((const char **)&str, (const char *)(str + length),
                 &new_end, new_str + new_length - 1);

  *new_end = 0;

  return new_str;
#endif
}

static char *
ConvertToUTF8 (const XML_Char *str)
{
  return ConvertToUTF8Length (str, -1);
}

/* END SPICEBIRD CHANGES */

static void
expat_StartElementHandler (void            *userData,
                           const XML_Char  *name,
                           const XML_Char **atts)
{
  ExpatParseContext *context = userData;
  int i;
  char **names;
  char **values;
  char *n;

  /* Expat seems to suck and can't abort the parse if we
   * throw an error. Expat 2.0 is supposed to fix this.
   */
  if (context->failed)
    return;

  if (!process_content (context))
    return;

  /* "atts" is key, value, key, value, NULL */
  for (i = 0; atts[i] != NULL; ++i)
    ; /* nothing */

  _dbus_assert (i % 2 == 0);
  names = dbus_new0 (char *, i / 2 + 1);
  values = dbus_new0 (char *, i / 2 + 1);

  if (names == NULL || values == NULL)
    {
      dbus_set_error (context->error, DBUS_ERROR_NO_MEMORY, NULL);
      context->failed = TRUE;
      dbus_free (names);
      dbus_free (values);
      return;
    }

  i = 0;
  while (atts[i] != NULL)
    {
      _dbus_assert (i % 2 == 0);
      names [i / 2] = ConvertToUTF8(atts[i]);
      values[i / 2] = ConvertToUTF8(atts[i+1]);

      i += 2;
    }

  n = ConvertToUTF8(name);
  if (!bus_config_parser_start_element (context->parser,
                                        n,
                                        (const char **) names,
                                        (const char **) values,
                                        context->error))
    {
      context->failed = TRUE;
    }

  for (i=0; names[i]; i++)
    dbus_free (names[i]);
  for (i=0; values[i]; i++)
    dbus_free (values[i]);

  dbus_free (n);

  dbus_free (names);
  dbus_free (values);
}

static void
expat_EndElementHandler (void           *userData,
                         const XML_Char *name)
{
  ExpatParseContext *context = userData;
  char *n;

  if (!process_content (context))
    return;

  n = ConvertToUTF8(name);
  if (!bus_config_parser_end_element (context->parser,
                                      n,
                                      context->error))
    {
      context->failed = TRUE;
      dbus_free (n);
      return;
    }

  dbus_free(n);
}

/* s is not 0 terminated. */
static void
expat_CharacterDataHandler (void           *userData,
                            const XML_Char *s,
                            int             len)
{
  ExpatParseContext *context = userData;
  char * str;

  if (context->failed)
    return;

  str = ConvertToUTF8Length(s, len);
  if (!_dbus_string_append_len (&context->content,
                                str, strlen(str)))
    {
      dbus_set_error (context->error, DBUS_ERROR_NO_MEMORY, NULL);
      context->failed = TRUE;
      dbus_free(str);
      return;
    }

  dbus_free(str);
}


BusConfigParser*
bus_config_load (const DBusString      *file,
                 dbus_bool_t            is_toplevel,
                 const BusConfigParser *parent,
                 DBusError             *error)
{
  XML_Parser expat;
  const char *filename;
  BusConfigParser *parser;
  ExpatParseContext context;
  DBusString dirname;
  
  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  parser = NULL;
  expat = NULL;
  context.error = error;
  context.failed = FALSE;

  filename = _dbus_string_get_const_data (file);

  if (!_dbus_string_init (&context.content))
    {
      dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
      return NULL;
    }

  if (!_dbus_string_init (&dirname))
    {
      dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
      _dbus_string_free (&context.content);
      return NULL;
    }
  
  expat = XML_ParserCreate_MM (NULL, &memsuite, NULL);
  if (expat == NULL)
    {
      dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
      goto failed;
    }

  if (!_dbus_string_get_dirname (file, &dirname))
    {
      dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
      goto failed;
    }
  
  parser = bus_config_parser_new (&dirname, is_toplevel, parent);
  if (parser == NULL)
    {
      dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
      goto failed;
    }
  context.parser = parser;

  XML_SetUserData (expat, &context);
  XML_SetElementHandler (expat,
                         expat_StartElementHandler,
                         expat_EndElementHandler);
  XML_SetCharacterDataHandler (expat,
                               expat_CharacterDataHandler);

  {
    DBusString data;
    const char *data_str;

    if (!_dbus_string_init (&data))
      {
        dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
        goto failed;
      }

    if (!_dbus_file_get_contents (&data, file, error))
      {
        _dbus_string_free (&data);
        goto failed;
      }

    data_str = _dbus_string_get_const_data (&data);

    if (!XML_Parse (expat, data_str, _dbus_string_get_length (&data), TRUE))
      {
        if (context.error != NULL &&
            !dbus_error_is_set (context.error))
          {
            enum XML_Error e;

            e = XML_GetErrorCode (expat);
            if (e == XML_ERROR_NO_MEMORY)
              dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
            else
              dbus_set_error (error, DBUS_ERROR_FAILED,
                              "Error in file %s, line %d, column %d: %d\n",
                              filename,
                              XML_GetCurrentLineNumber (expat),
                              XML_GetCurrentColumnNumber (expat),
                              /* Spicebird
                              ,
                              XML_ErrorString (e));
                              */
                              e);
          }

        _dbus_string_free (&data);
        goto failed;
      }

    _dbus_string_free (&data);

    if (context.failed)
      goto failed;
  }

  if (!bus_config_parser_finished (parser, error))
    goto failed;

  _dbus_string_free (&dirname);
  _dbus_string_free (&context.content);
  XML_ParserFree (expat);

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);
  return parser;

 failed:
  _DBUS_ASSERT_ERROR_IS_SET (error);

  _dbus_string_free (&dirname);
  _dbus_string_free (&context.content);
  if (expat)
    XML_ParserFree (expat);
  if (parser)
    bus_config_parser_unref (parser);
  return NULL;
}
