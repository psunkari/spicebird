#include "_gen/signals-marshal.h"

#include	<glib-object.h>


#ifdef G_ENABLE_DEBUG
#define g_marshal_value_peek_boolean(v)  g_value_get_boolean (v)
#define g_marshal_value_peek_char(v)     g_value_get_char (v)
#define g_marshal_value_peek_uchar(v)    g_value_get_uchar (v)
#define g_marshal_value_peek_int(v)      g_value_get_int (v)
#define g_marshal_value_peek_uint(v)     g_value_get_uint (v)
#define g_marshal_value_peek_long(v)     g_value_get_long (v)
#define g_marshal_value_peek_ulong(v)    g_value_get_ulong (v)
#define g_marshal_value_peek_int64(v)    g_value_get_int64 (v)
#define g_marshal_value_peek_uint64(v)   g_value_get_uint64 (v)
#define g_marshal_value_peek_enum(v)     g_value_get_enum (v)
#define g_marshal_value_peek_flags(v)    g_value_get_flags (v)
#define g_marshal_value_peek_float(v)    g_value_get_float (v)
#define g_marshal_value_peek_double(v)   g_value_get_double (v)
#define g_marshal_value_peek_string(v)   (char*) g_value_get_string (v)
#define g_marshal_value_peek_param(v)    g_value_get_param (v)
#define g_marshal_value_peek_boxed(v)    g_value_get_boxed (v)
#define g_marshal_value_peek_pointer(v)  g_value_get_pointer (v)
#define g_marshal_value_peek_object(v)   g_value_get_object (v)
#else /* !G_ENABLE_DEBUG */
/* WARNING: This code accesses GValues directly, which is UNSUPPORTED API.
 *          Do not access GValues directly in your code. Instead, use the
 *          g_value_get_*() functions
 */
#define g_marshal_value_peek_boolean(v)  (v)->data[0].v_int
#define g_marshal_value_peek_char(v)     (v)->data[0].v_int
#define g_marshal_value_peek_uchar(v)    (v)->data[0].v_uint
#define g_marshal_value_peek_int(v)      (v)->data[0].v_int
#define g_marshal_value_peek_uint(v)     (v)->data[0].v_uint
#define g_marshal_value_peek_long(v)     (v)->data[0].v_long
#define g_marshal_value_peek_ulong(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_int64(v)    (v)->data[0].v_int64
#define g_marshal_value_peek_uint64(v)   (v)->data[0].v_uint64
#define g_marshal_value_peek_enum(v)     (v)->data[0].v_long
#define g_marshal_value_peek_flags(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_float(v)    (v)->data[0].v_float
#define g_marshal_value_peek_double(v)   (v)->data[0].v_double
#define g_marshal_value_peek_string(v)   (v)->data[0].v_pointer
#define g_marshal_value_peek_param(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_boxed(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_pointer(v)  (v)->data[0].v_pointer
#define g_marshal_value_peek_object(v)   (v)->data[0].v_pointer
#endif /* !G_ENABLE_DEBUG */


/* VOID:BOOLEAN,POINTER (_gen/signals-marshal.list:1) */
void
_tp_marshal_VOID__BOOLEAN_POINTER (GClosure     *closure,
                                   GValue       *return_value G_GNUC_UNUSED,
                                   guint         n_param_values,
                                   const GValue *param_values,
                                   gpointer      invocation_hint G_GNUC_UNUSED,
                                   gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOOLEAN_POINTER) (gpointer     data1,
                                                      gboolean     arg_1,
                                                      gpointer     arg_2,
                                                      gpointer     data2);
  register GMarshalFunc_VOID__BOOLEAN_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOOLEAN_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boolean (param_values + 1),
            g_marshal_value_peek_pointer (param_values + 2),
            data2);
}

/* VOID:BOXED,BOOLEAN (_gen/signals-marshal.list:2) */
void
_tp_marshal_VOID__BOXED_BOOLEAN (GClosure     *closure,
                                 GValue       *return_value G_GNUC_UNUSED,
                                 guint         n_param_values,
                                 const GValue *param_values,
                                 gpointer      invocation_hint G_GNUC_UNUSED,
                                 gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_BOOLEAN) (gpointer     data1,
                                                    gpointer     arg_1,
                                                    gboolean     arg_2,
                                                    gpointer     data2);
  register GMarshalFunc_VOID__BOXED_BOOLEAN callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_BOOLEAN) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_boolean (param_values + 2),
            data2);
}

/* VOID:BOXED,BOXED (_gen/signals-marshal.list:3) */
void
_tp_marshal_VOID__BOXED_BOXED (GClosure     *closure,
                               GValue       *return_value G_GNUC_UNUSED,
                               guint         n_param_values,
                               const GValue *param_values,
                               gpointer      invocation_hint G_GNUC_UNUSED,
                               gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_BOXED) (gpointer     data1,
                                                  gpointer     arg_1,
                                                  gpointer     arg_2,
                                                  gpointer     data2);
  register GMarshalFunc_VOID__BOXED_BOXED callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_BOXED) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            data2);
}

/* VOID:BOXED,BOXED,BOOLEAN,POINTER (_gen/signals-marshal.list:4) */
void
_tp_marshal_VOID__BOXED_BOXED_BOOLEAN_POINTER (GClosure     *closure,
                                               GValue       *return_value G_GNUC_UNUSED,
                                               guint         n_param_values,
                                               const GValue *param_values,
                                               gpointer      invocation_hint G_GNUC_UNUSED,
                                               gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_BOXED_BOOLEAN_POINTER) (gpointer     data1,
                                                                  gpointer     arg_1,
                                                                  gpointer     arg_2,
                                                                  gboolean     arg_3,
                                                                  gpointer     arg_4,
                                                                  gpointer     data2);
  register GMarshalFunc_VOID__BOXED_BOXED_BOOLEAN_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_BOXED_BOOLEAN_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_boolean (param_values + 3),
            g_marshal_value_peek_pointer (param_values + 4),
            data2);
}

/* VOID:BOXED,BOXED,BOXED,BOXED,BOXED (_gen/signals-marshal.list:5) */
void
_tp_marshal_VOID__BOXED_BOXED_BOXED_BOXED_BOXED (GClosure     *closure,
                                                 GValue       *return_value G_GNUC_UNUSED,
                                                 guint         n_param_values,
                                                 const GValue *param_values,
                                                 gpointer      invocation_hint G_GNUC_UNUSED,
                                                 gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_BOXED_BOXED_BOXED_BOXED) (gpointer     data1,
                                                                    gpointer     arg_1,
                                                                    gpointer     arg_2,
                                                                    gpointer     arg_3,
                                                                    gpointer     arg_4,
                                                                    gpointer     arg_5,
                                                                    gpointer     data2);
  register GMarshalFunc_VOID__BOXED_BOXED_BOXED_BOXED_BOXED callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 6);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_BOXED_BOXED_BOXED_BOXED) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_boxed (param_values + 3),
            g_marshal_value_peek_boxed (param_values + 4),
            g_marshal_value_peek_boxed (param_values + 5),
            data2);
}

/* VOID:BOXED,BOXED,BOXED,BOXED,BOXED,BOXED,POINTER (_gen/signals-marshal.list:6) */
void
_tp_marshal_VOID__BOXED_BOXED_BOXED_BOXED_BOXED_BOXED_POINTER (GClosure     *closure,
                                                               GValue       *return_value G_GNUC_UNUSED,
                                                               guint         n_param_values,
                                                               const GValue *param_values,
                                                               gpointer      invocation_hint G_GNUC_UNUSED,
                                                               gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_BOXED_BOXED_BOXED_BOXED_BOXED_POINTER) (gpointer     data1,
                                                                                  gpointer     arg_1,
                                                                                  gpointer     arg_2,
                                                                                  gpointer     arg_3,
                                                                                  gpointer     arg_4,
                                                                                  gpointer     arg_5,
                                                                                  gpointer     arg_6,
                                                                                  gpointer     arg_7,
                                                                                  gpointer     data2);
  register GMarshalFunc_VOID__BOXED_BOXED_BOXED_BOXED_BOXED_BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 8);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_BOXED_BOXED_BOXED_BOXED_BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_boxed (param_values + 3),
            g_marshal_value_peek_boxed (param_values + 4),
            g_marshal_value_peek_boxed (param_values + 5),
            g_marshal_value_peek_boxed (param_values + 6),
            g_marshal_value_peek_pointer (param_values + 7),
            data2);
}

/* VOID:BOXED,BOXED,BOXED,BOXED,UINT64,BOXED,POINTER (_gen/signals-marshal.list:7) */
void
_tp_marshal_VOID__BOXED_BOXED_BOXED_BOXED_UINT64_BOXED_POINTER (GClosure     *closure,
                                                                GValue       *return_value G_GNUC_UNUSED,
                                                                guint         n_param_values,
                                                                const GValue *param_values,
                                                                gpointer      invocation_hint G_GNUC_UNUSED,
                                                                gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_BOXED_BOXED_BOXED_UINT64_BOXED_POINTER) (gpointer     data1,
                                                                                   gpointer     arg_1,
                                                                                   gpointer     arg_2,
                                                                                   gpointer     arg_3,
                                                                                   gpointer     arg_4,
                                                                                   guint64      arg_5,
                                                                                   gpointer     arg_6,
                                                                                   gpointer     arg_7,
                                                                                   gpointer     data2);
  register GMarshalFunc_VOID__BOXED_BOXED_BOXED_BOXED_UINT64_BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 8);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_BOXED_BOXED_BOXED_UINT64_BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_boxed (param_values + 3),
            g_marshal_value_peek_boxed (param_values + 4),
            g_marshal_value_peek_uint64 (param_values + 5),
            g_marshal_value_peek_boxed (param_values + 6),
            g_marshal_value_peek_pointer (param_values + 7),
            data2);
}

/* VOID:BOXED,BOXED,BOXED,POINTER (_gen/signals-marshal.list:8) */
void
_tp_marshal_VOID__BOXED_BOXED_BOXED_POINTER (GClosure     *closure,
                                             GValue       *return_value G_GNUC_UNUSED,
                                             guint         n_param_values,
                                             const GValue *param_values,
                                             gpointer      invocation_hint G_GNUC_UNUSED,
                                             gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_BOXED_BOXED_POINTER) (gpointer     data1,
                                                                gpointer     arg_1,
                                                                gpointer     arg_2,
                                                                gpointer     arg_3,
                                                                gpointer     arg_4,
                                                                gpointer     data2);
  register GMarshalFunc_VOID__BOXED_BOXED_BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_BOXED_BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_boxed (param_values + 3),
            g_marshal_value_peek_pointer (param_values + 4),
            data2);
}

/* VOID:BOXED,BOXED,INT64,STRING,POINTER (_gen/signals-marshal.list:9) */
void
_tp_marshal_VOID__BOXED_BOXED_INT64_STRING_POINTER (GClosure     *closure,
                                                    GValue       *return_value G_GNUC_UNUSED,
                                                    guint         n_param_values,
                                                    const GValue *param_values,
                                                    gpointer      invocation_hint G_GNUC_UNUSED,
                                                    gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_BOXED_INT64_STRING_POINTER) (gpointer     data1,
                                                                       gpointer     arg_1,
                                                                       gpointer     arg_2,
                                                                       gint64       arg_3,
                                                                       gpointer     arg_4,
                                                                       gpointer     arg_5,
                                                                       gpointer     data2);
  register GMarshalFunc_VOID__BOXED_BOXED_INT64_STRING_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 6);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_BOXED_INT64_STRING_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_int64 (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_pointer (param_values + 5),
            data2);
}

/* VOID:BOXED,BOXED,POINTER (_gen/signals-marshal.list:10) */
void
_tp_marshal_VOID__BOXED_BOXED_POINTER (GClosure     *closure,
                                       GValue       *return_value G_GNUC_UNUSED,
                                       guint         n_param_values,
                                       const GValue *param_values,
                                       gpointer      invocation_hint G_GNUC_UNUSED,
                                       gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_BOXED_POINTER) (gpointer     data1,
                                                          gpointer     arg_1,
                                                          gpointer     arg_2,
                                                          gpointer     arg_3,
                                                          gpointer     data2);
  register GMarshalFunc_VOID__BOXED_BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_pointer (param_values + 3),
            data2);
}

/* VOID:BOXED,POINTER (_gen/signals-marshal.list:11) */
void
_tp_marshal_VOID__BOXED_POINTER (GClosure     *closure,
                                 GValue       *return_value G_GNUC_UNUSED,
                                 guint         n_param_values,
                                 const GValue *param_values,
                                 gpointer      invocation_hint G_GNUC_UNUSED,
                                 gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_POINTER) (gpointer     data1,
                                                    gpointer     arg_1,
                                                    gpointer     arg_2,
                                                    gpointer     data2);
  register GMarshalFunc_VOID__BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_pointer (param_values + 2),
            data2);
}

/* VOID:BOXED,STRING (_gen/signals-marshal.list:12) */
void
_tp_marshal_VOID__BOXED_STRING (GClosure     *closure,
                                GValue       *return_value G_GNUC_UNUSED,
                                guint         n_param_values,
                                const GValue *param_values,
                                gpointer      invocation_hint G_GNUC_UNUSED,
                                gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_STRING) (gpointer     data1,
                                                   gpointer     arg_1,
                                                   gpointer     arg_2,
                                                   gpointer     data2);
  register GMarshalFunc_VOID__BOXED_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            data2);
}

/* VOID:BOXED,STRING,POINTER (_gen/signals-marshal.list:13) */
void
_tp_marshal_VOID__BOXED_STRING_POINTER (GClosure     *closure,
                                        GValue       *return_value G_GNUC_UNUSED,
                                        guint         n_param_values,
                                        const GValue *param_values,
                                        gpointer      invocation_hint G_GNUC_UNUSED,
                                        gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_STRING_POINTER) (gpointer     data1,
                                                           gpointer     arg_1,
                                                           gpointer     arg_2,
                                                           gpointer     arg_3,
                                                           gpointer     data2);
  register GMarshalFunc_VOID__BOXED_STRING_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_STRING_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_pointer (param_values + 3),
            data2);
}

/* VOID:BOXED,STRING,STRING (_gen/signals-marshal.list:14) */
void
_tp_marshal_VOID__BOXED_STRING_STRING (GClosure     *closure,
                                       GValue       *return_value G_GNUC_UNUSED,
                                       guint         n_param_values,
                                       const GValue *param_values,
                                       gpointer      invocation_hint G_GNUC_UNUSED,
                                       gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_STRING_STRING) (gpointer     data1,
                                                          gpointer     arg_1,
                                                          gpointer     arg_2,
                                                          gpointer     arg_3,
                                                          gpointer     data2);
  register GMarshalFunc_VOID__BOXED_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            data2);
}

/* VOID:BOXED,STRING,STRING,POINTER (_gen/signals-marshal.list:15) */
void
_tp_marshal_VOID__BOXED_STRING_STRING_POINTER (GClosure     *closure,
                                               GValue       *return_value G_GNUC_UNUSED,
                                               guint         n_param_values,
                                               const GValue *param_values,
                                               gpointer      invocation_hint G_GNUC_UNUSED,
                                               gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_STRING_STRING_POINTER) (gpointer     data1,
                                                                  gpointer     arg_1,
                                                                  gpointer     arg_2,
                                                                  gpointer     arg_3,
                                                                  gpointer     arg_4,
                                                                  gpointer     data2);
  register GMarshalFunc_VOID__BOXED_STRING_STRING_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_STRING_STRING_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_pointer (param_values + 4),
            data2);
}

/* VOID:BOXED,STRING,UINT,POINTER (_gen/signals-marshal.list:16) */
void
_tp_marshal_VOID__BOXED_STRING_UINT_POINTER (GClosure     *closure,
                                             GValue       *return_value G_GNUC_UNUSED,
                                             guint         n_param_values,
                                             const GValue *param_values,
                                             gpointer      invocation_hint G_GNUC_UNUSED,
                                             gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_STRING_UINT_POINTER) (gpointer     data1,
                                                                gpointer     arg_1,
                                                                gpointer     arg_2,
                                                                guint        arg_3,
                                                                gpointer     arg_4,
                                                                gpointer     data2);
  register GMarshalFunc_VOID__BOXED_STRING_UINT_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_STRING_UINT_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_pointer (param_values + 4),
            data2);
}

/* VOID:BOXED,STRING,UINT,UINT,BOOLEAN (_gen/signals-marshal.list:17) */
void
_tp_marshal_VOID__BOXED_STRING_UINT_UINT_BOOLEAN (GClosure     *closure,
                                                  GValue       *return_value G_GNUC_UNUSED,
                                                  guint         n_param_values,
                                                  const GValue *param_values,
                                                  gpointer      invocation_hint G_GNUC_UNUSED,
                                                  gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_STRING_UINT_UINT_BOOLEAN) (gpointer     data1,
                                                                     gpointer     arg_1,
                                                                     gpointer     arg_2,
                                                                     guint        arg_3,
                                                                     guint        arg_4,
                                                                     gboolean     arg_5,
                                                                     gpointer     data2);
  register GMarshalFunc_VOID__BOXED_STRING_UINT_UINT_BOOLEAN callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 6);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_STRING_UINT_UINT_BOOLEAN) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_uint (param_values + 4),
            g_marshal_value_peek_boolean (param_values + 5),
            data2);
}

/* VOID:BOXED,UINT,POINTER (_gen/signals-marshal.list:18) */
void
_tp_marshal_VOID__BOXED_UINT_POINTER (GClosure     *closure,
                                      GValue       *return_value G_GNUC_UNUSED,
                                      guint         n_param_values,
                                      const GValue *param_values,
                                      gpointer      invocation_hint G_GNUC_UNUSED,
                                      gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_UINT_POINTER) (gpointer     data1,
                                                         gpointer     arg_1,
                                                         guint        arg_2,
                                                         gpointer     arg_3,
                                                         gpointer     data2);
  register GMarshalFunc_VOID__BOXED_UINT_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_UINT_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_pointer (param_values + 3),
            data2);
}

/* VOID:BOXED,UINT,STRING (_gen/signals-marshal.list:19) */
void
_tp_marshal_VOID__BOXED_UINT_STRING (GClosure     *closure,
                                     GValue       *return_value G_GNUC_UNUSED,
                                     guint         n_param_values,
                                     const GValue *param_values,
                                     gpointer      invocation_hint G_GNUC_UNUSED,
                                     gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_UINT_STRING) (gpointer     data1,
                                                        gpointer     arg_1,
                                                        guint        arg_2,
                                                        gpointer     arg_3,
                                                        gpointer     data2);
  register GMarshalFunc_VOID__BOXED_UINT_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_UINT_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            data2);
}

/* VOID:BOXED,UINT,UINT,UINT (_gen/signals-marshal.list:20) */
void
_tp_marshal_VOID__BOXED_UINT_UINT_UINT (GClosure     *closure,
                                        GValue       *return_value G_GNUC_UNUSED,
                                        guint         n_param_values,
                                        const GValue *param_values,
                                        gpointer      invocation_hint G_GNUC_UNUSED,
                                        gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__BOXED_UINT_UINT_UINT) (gpointer     data1,
                                                           gpointer     arg_1,
                                                           guint        arg_2,
                                                           guint        arg_3,
                                                           guint        arg_4,
                                                           gpointer     data2);
  register GMarshalFunc_VOID__BOXED_UINT_UINT_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__BOXED_UINT_UINT_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_boxed (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_uint (param_values + 4),
            data2);
}

/* VOID:DOUBLE,STRING,UINT,STRING (_gen/signals-marshal.list:21) */
void
_tp_marshal_VOID__DOUBLE_STRING_UINT_STRING (GClosure     *closure,
                                             GValue       *return_value G_GNUC_UNUSED,
                                             guint         n_param_values,
                                             const GValue *param_values,
                                             gpointer      invocation_hint G_GNUC_UNUSED,
                                             gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__DOUBLE_STRING_UINT_STRING) (gpointer     data1,
                                                                gdouble      arg_1,
                                                                gpointer     arg_2,
                                                                guint        arg_3,
                                                                gpointer     arg_4,
                                                                gpointer     data2);
  register GMarshalFunc_VOID__DOUBLE_STRING_UINT_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__DOUBLE_STRING_UINT_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_double (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            data2);
}

/* VOID:OBJECT,POINTER (_gen/signals-marshal.list:22) */
void
_tp_marshal_VOID__OBJECT_POINTER (GClosure     *closure,
                                  GValue       *return_value G_GNUC_UNUSED,
                                  guint         n_param_values,
                                  const GValue *param_values,
                                  gpointer      invocation_hint G_GNUC_UNUSED,
                                  gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__OBJECT_POINTER) (gpointer     data1,
                                                     gpointer     arg_1,
                                                     gpointer     arg_2,
                                                     gpointer     data2);
  register GMarshalFunc_VOID__OBJECT_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__OBJECT_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_object (param_values + 1),
            g_marshal_value_peek_pointer (param_values + 2),
            data2);
}

/* VOID:OBJECT,POINTER,POINTER (_gen/signals-marshal.list:23) */
void
_tp_marshal_VOID__OBJECT_POINTER_POINTER (GClosure     *closure,
                                          GValue       *return_value G_GNUC_UNUSED,
                                          guint         n_param_values,
                                          const GValue *param_values,
                                          gpointer      invocation_hint G_GNUC_UNUSED,
                                          gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__OBJECT_POINTER_POINTER) (gpointer     data1,
                                                             gpointer     arg_1,
                                                             gpointer     arg_2,
                                                             gpointer     arg_3,
                                                             gpointer     data2);
  register GMarshalFunc_VOID__OBJECT_POINTER_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__OBJECT_POINTER_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_object (param_values + 1),
            g_marshal_value_peek_pointer (param_values + 2),
            g_marshal_value_peek_pointer (param_values + 3),
            data2);
}

/* VOID:POINTER,OBJECT (_gen/signals-marshal.list:24) */
void
_tp_marshal_VOID__POINTER_OBJECT (GClosure     *closure,
                                  GValue       *return_value G_GNUC_UNUSED,
                                  guint         n_param_values,
                                  const GValue *param_values,
                                  gpointer      invocation_hint G_GNUC_UNUSED,
                                  gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__POINTER_OBJECT) (gpointer     data1,
                                                     gpointer     arg_1,
                                                     gpointer     arg_2,
                                                     gpointer     data2);
  register GMarshalFunc_VOID__POINTER_OBJECT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__POINTER_OBJECT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_pointer (param_values + 1),
            g_marshal_value_peek_object (param_values + 2),
            data2);
}

/* VOID:POINTER,UINT,INT,STRING (_gen/signals-marshal.list:25) */
void
_tp_marshal_VOID__POINTER_UINT_INT_STRING (GClosure     *closure,
                                           GValue       *return_value G_GNUC_UNUSED,
                                           guint         n_param_values,
                                           const GValue *param_values,
                                           gpointer      invocation_hint G_GNUC_UNUSED,
                                           gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__POINTER_UINT_INT_STRING) (gpointer     data1,
                                                              gpointer     arg_1,
                                                              guint        arg_2,
                                                              gint         arg_3,
                                                              gpointer     arg_4,
                                                              gpointer     data2);
  register GMarshalFunc_VOID__POINTER_UINT_INT_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__POINTER_UINT_INT_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_pointer (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_int (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            data2);
}

/* VOID:STRING,BOXED (_gen/signals-marshal.list:26) */
void
_tp_marshal_VOID__STRING_BOXED (GClosure     *closure,
                                GValue       *return_value G_GNUC_UNUSED,
                                guint         n_param_values,
                                const GValue *param_values,
                                gpointer      invocation_hint G_GNUC_UNUSED,
                                gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_BOXED) (gpointer     data1,
                                                   gpointer     arg_1,
                                                   gpointer     arg_2,
                                                   gpointer     data2);
  register GMarshalFunc_VOID__STRING_BOXED callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_BOXED) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            data2);
}

/* VOID:STRING,BOXED,BOXED,BOXED,BOXED,UINT,UINT (_gen/signals-marshal.list:27) */
void
_tp_marshal_VOID__STRING_BOXED_BOXED_BOXED_BOXED_UINT_UINT (GClosure     *closure,
                                                            GValue       *return_value G_GNUC_UNUSED,
                                                            guint         n_param_values,
                                                            const GValue *param_values,
                                                            gpointer      invocation_hint G_GNUC_UNUSED,
                                                            gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_BOXED_BOXED_BOXED_BOXED_UINT_UINT) (gpointer     data1,
                                                                               gpointer     arg_1,
                                                                               gpointer     arg_2,
                                                                               gpointer     arg_3,
                                                                               gpointer     arg_4,
                                                                               gpointer     arg_5,
                                                                               guint        arg_6,
                                                                               guint        arg_7,
                                                                               gpointer     data2);
  register GMarshalFunc_VOID__STRING_BOXED_BOXED_BOXED_BOXED_UINT_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 8);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_BOXED_BOXED_BOXED_BOXED_UINT_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_boxed (param_values + 3),
            g_marshal_value_peek_boxed (param_values + 4),
            g_marshal_value_peek_boxed (param_values + 5),
            g_marshal_value_peek_uint (param_values + 6),
            g_marshal_value_peek_uint (param_values + 7),
            data2);
}

/* VOID:STRING,BOXED,POINTER (_gen/signals-marshal.list:28) */
void
_tp_marshal_VOID__STRING_BOXED_POINTER (GClosure     *closure,
                                        GValue       *return_value G_GNUC_UNUSED,
                                        guint         n_param_values,
                                        const GValue *param_values,
                                        gpointer      invocation_hint G_GNUC_UNUSED,
                                        gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_BOXED_POINTER) (gpointer     data1,
                                                           gpointer     arg_1,
                                                           gpointer     arg_2,
                                                           gpointer     arg_3,
                                                           gpointer     data2);
  register GMarshalFunc_VOID__STRING_BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_pointer (param_values + 3),
            data2);
}

/* VOID:STRING,BOXED,STRING (_gen/signals-marshal.list:29) */
void
_tp_marshal_VOID__STRING_BOXED_STRING (GClosure     *closure,
                                       GValue       *return_value G_GNUC_UNUSED,
                                       guint         n_param_values,
                                       const GValue *param_values,
                                       gpointer      invocation_hint G_GNUC_UNUSED,
                                       gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_BOXED_STRING) (gpointer     data1,
                                                          gpointer     arg_1,
                                                          gpointer     arg_2,
                                                          gpointer     arg_3,
                                                          gpointer     data2);
  register GMarshalFunc_VOID__STRING_BOXED_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_BOXED_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            data2);
}

/* VOID:STRING,BOXED,UINT,BOXED,UINT,BOXED,POINTER (_gen/signals-marshal.list:30) */
void
_tp_marshal_VOID__STRING_BOXED_UINT_BOXED_UINT_BOXED_POINTER (GClosure     *closure,
                                                              GValue       *return_value G_GNUC_UNUSED,
                                                              guint         n_param_values,
                                                              const GValue *param_values,
                                                              gpointer      invocation_hint G_GNUC_UNUSED,
                                                              gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_BOXED_UINT_BOXED_UINT_BOXED_POINTER) (gpointer     data1,
                                                                                 gpointer     arg_1,
                                                                                 gpointer     arg_2,
                                                                                 guint        arg_3,
                                                                                 gpointer     arg_4,
                                                                                 guint        arg_5,
                                                                                 gpointer     arg_6,
                                                                                 gpointer     arg_7,
                                                                                 gpointer     data2);
  register GMarshalFunc_VOID__STRING_BOXED_UINT_BOXED_UINT_BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 8);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_BOXED_UINT_BOXED_UINT_BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_boxed (param_values + 4),
            g_marshal_value_peek_uint (param_values + 5),
            g_marshal_value_peek_boxed (param_values + 6),
            g_marshal_value_peek_pointer (param_values + 7),
            data2);
}

/* VOID:STRING,POINTER (_gen/signals-marshal.list:31) */
void
_tp_marshal_VOID__STRING_POINTER (GClosure     *closure,
                                  GValue       *return_value G_GNUC_UNUSED,
                                  guint         n_param_values,
                                  const GValue *param_values,
                                  gpointer      invocation_hint G_GNUC_UNUSED,
                                  gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_POINTER) (gpointer     data1,
                                                     gpointer     arg_1,
                                                     gpointer     arg_2,
                                                     gpointer     data2);
  register GMarshalFunc_VOID__STRING_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_pointer (param_values + 2),
            data2);
}

/* VOID:STRING,STRING (_gen/signals-marshal.list:32) */
void
_tp_marshal_VOID__STRING_STRING (GClosure     *closure,
                                 GValue       *return_value G_GNUC_UNUSED,
                                 guint         n_param_values,
                                 const GValue *param_values,
                                 gpointer      invocation_hint G_GNUC_UNUSED,
                                 gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING) (gpointer     data1,
                                                    gpointer     arg_1,
                                                    gpointer     arg_2,
                                                    gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            data2);
}

/* VOID:STRING,STRING,BOXED,POINTER (_gen/signals-marshal.list:33) */
void
_tp_marshal_VOID__STRING_STRING_BOXED_POINTER (GClosure     *closure,
                                               GValue       *return_value G_GNUC_UNUSED,
                                               guint         n_param_values,
                                               const GValue *param_values,
                                               gpointer      invocation_hint G_GNUC_UNUSED,
                                               gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_BOXED_POINTER) (gpointer     data1,
                                                                  gpointer     arg_1,
                                                                  gpointer     arg_2,
                                                                  gpointer     arg_3,
                                                                  gpointer     arg_4,
                                                                  gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_boxed (param_values + 3),
            g_marshal_value_peek_pointer (param_values + 4),
            data2);
}

/* VOID:STRING,STRING,POINTER (_gen/signals-marshal.list:34) */
void
_tp_marshal_VOID__STRING_STRING_POINTER (GClosure     *closure,
                                         GValue       *return_value G_GNUC_UNUSED,
                                         guint         n_param_values,
                                         const GValue *param_values,
                                         gpointer      invocation_hint G_GNUC_UNUSED,
                                         gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_POINTER) (gpointer     data1,
                                                            gpointer     arg_1,
                                                            gpointer     arg_2,
                                                            gpointer     arg_3,
                                                            gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_pointer (param_values + 3),
            data2);
}

/* VOID:STRING,STRING,STRING (_gen/signals-marshal.list:35) */
void
_tp_marshal_VOID__STRING_STRING_STRING (GClosure     *closure,
                                        GValue       *return_value G_GNUC_UNUSED,
                                        guint         n_param_values,
                                        const GValue *param_values,
                                        gpointer      invocation_hint G_GNUC_UNUSED,
                                        gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING) (gpointer     data1,
                                                           gpointer     arg_1,
                                                           gpointer     arg_2,
                                                           gpointer     arg_3,
                                                           gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            data2);
}

/* VOID:STRING,STRING,STRING,BOXED,BOXED,POINTER (_gen/signals-marshal.list:36) */
void
_tp_marshal_VOID__STRING_STRING_STRING_BOXED_BOXED_POINTER (GClosure     *closure,
                                                            GValue       *return_value G_GNUC_UNUSED,
                                                            guint         n_param_values,
                                                            const GValue *param_values,
                                                            gpointer      invocation_hint G_GNUC_UNUSED,
                                                            gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_BOXED_BOXED_POINTER) (gpointer     data1,
                                                                               gpointer     arg_1,
                                                                               gpointer     arg_2,
                                                                               gpointer     arg_3,
                                                                               gpointer     arg_4,
                                                                               gpointer     arg_5,
                                                                               gpointer     arg_6,
                                                                               gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_BOXED_BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 7);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_BOXED_BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_boxed (param_values + 4),
            g_marshal_value_peek_boxed (param_values + 5),
            g_marshal_value_peek_pointer (param_values + 6),
            data2);
}

/* VOID:STRING,UINT,POINTER (_gen/signals-marshal.list:37) */
void
_tp_marshal_VOID__STRING_UINT_POINTER (GClosure     *closure,
                                       GValue       *return_value G_GNUC_UNUSED,
                                       guint         n_param_values,
                                       const GValue *param_values,
                                       gpointer      invocation_hint G_GNUC_UNUSED,
                                       gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_UINT_POINTER) (gpointer     data1,
                                                          gpointer     arg_1,
                                                          guint        arg_2,
                                                          gpointer     arg_3,
                                                          gpointer     data2);
  register GMarshalFunc_VOID__STRING_UINT_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_UINT_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_pointer (param_values + 3),
            data2);
}

/* VOID:STRING,UINT,UINT,BOOLEAN,POINTER (_gen/signals-marshal.list:38) */
void
_tp_marshal_VOID__STRING_UINT_UINT_BOOLEAN_POINTER (GClosure     *closure,
                                                    GValue       *return_value G_GNUC_UNUSED,
                                                    guint         n_param_values,
                                                    const GValue *param_values,
                                                    gpointer      invocation_hint G_GNUC_UNUSED,
                                                    gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_UINT_UINT_BOOLEAN_POINTER) (gpointer     data1,
                                                                       gpointer     arg_1,
                                                                       guint        arg_2,
                                                                       guint        arg_3,
                                                                       gboolean     arg_4,
                                                                       gpointer     arg_5,
                                                                       gpointer     data2);
  register GMarshalFunc_VOID__STRING_UINT_UINT_BOOLEAN_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 6);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_UINT_UINT_BOOLEAN_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_boolean (param_values + 4),
            g_marshal_value_peek_pointer (param_values + 5),
            data2);
}

/* VOID:STRING,UINT,UINT,BOXED (_gen/signals-marshal.list:39) */
void
_tp_marshal_VOID__STRING_UINT_UINT_BOXED (GClosure     *closure,
                                          GValue       *return_value G_GNUC_UNUSED,
                                          guint         n_param_values,
                                          const GValue *param_values,
                                          gpointer      invocation_hint G_GNUC_UNUSED,
                                          gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_UINT_UINT_BOXED) (gpointer     data1,
                                                             gpointer     arg_1,
                                                             guint        arg_2,
                                                             guint        arg_3,
                                                             gpointer     arg_4,
                                                             gpointer     data2);
  register GMarshalFunc_VOID__STRING_UINT_UINT_BOXED callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_UINT_UINT_BOXED) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_boxed (param_values + 4),
            data2);
}

/* VOID:UINT64 (_gen/signals-marshal.list:40) */
void
_tp_marshal_VOID__UINT64 (GClosure     *closure,
                          GValue       *return_value G_GNUC_UNUSED,
                          guint         n_param_values,
                          const GValue *param_values,
                          gpointer      invocation_hint G_GNUC_UNUSED,
                          gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT64) (gpointer     data1,
                                             guint64      arg_1,
                                             gpointer     data2);
  register GMarshalFunc_VOID__UINT64 callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 2);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT64) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint64 (param_values + 1),
            data2);
}

/* VOID:UINT,BOXED (_gen/signals-marshal.list:41) */
void
_tp_marshal_VOID__UINT_BOXED (GClosure     *closure,
                              GValue       *return_value G_GNUC_UNUSED,
                              guint         n_param_values,
                              const GValue *param_values,
                              gpointer      invocation_hint G_GNUC_UNUSED,
                              gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_BOXED) (gpointer     data1,
                                                 guint        arg_1,
                                                 gpointer     arg_2,
                                                 gpointer     data2);
  register GMarshalFunc_VOID__UINT_BOXED callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_BOXED) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            data2);
}

/* VOID:UINT,BOXED,BOXED (_gen/signals-marshal.list:42) */
void
_tp_marshal_VOID__UINT_BOXED_BOXED (GClosure     *closure,
                                    GValue       *return_value G_GNUC_UNUSED,
                                    guint         n_param_values,
                                    const GValue *param_values,
                                    gpointer      invocation_hint G_GNUC_UNUSED,
                                    gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_BOXED_BOXED) (gpointer     data1,
                                                       guint        arg_1,
                                                       gpointer     arg_2,
                                                       gpointer     arg_3,
                                                       gpointer     data2);
  register GMarshalFunc_VOID__UINT_BOXED_BOXED callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_BOXED_BOXED) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_boxed (param_values + 3),
            data2);
}

/* VOID:UINT,BOXED,POINTER (_gen/signals-marshal.list:43) */
void
_tp_marshal_VOID__UINT_BOXED_POINTER (GClosure     *closure,
                                      GValue       *return_value G_GNUC_UNUSED,
                                      guint         n_param_values,
                                      const GValue *param_values,
                                      gpointer      invocation_hint G_GNUC_UNUSED,
                                      gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_BOXED_POINTER) (gpointer     data1,
                                                         guint        arg_1,
                                                         gpointer     arg_2,
                                                         gpointer     arg_3,
                                                         gpointer     data2);
  register GMarshalFunc_VOID__UINT_BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_pointer (param_values + 3),
            data2);
}

/* VOID:UINT,BOXED,UINT (_gen/signals-marshal.list:44) */
void
_tp_marshal_VOID__UINT_BOXED_UINT (GClosure     *closure,
                                   GValue       *return_value G_GNUC_UNUSED,
                                   guint         n_param_values,
                                   const GValue *param_values,
                                   gpointer      invocation_hint G_GNUC_UNUSED,
                                   gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_BOXED_UINT) (gpointer     data1,
                                                      guint        arg_1,
                                                      gpointer     arg_2,
                                                      guint        arg_3,
                                                      gpointer     data2);
  register GMarshalFunc_VOID__UINT_BOXED_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_BOXED_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            data2);
}

/* VOID:UINT,BOXED,UINT,BOXED,POINTER (_gen/signals-marshal.list:45) */
void
_tp_marshal_VOID__UINT_BOXED_UINT_BOXED_POINTER (GClosure     *closure,
                                                 GValue       *return_value G_GNUC_UNUSED,
                                                 guint         n_param_values,
                                                 const GValue *param_values,
                                                 gpointer      invocation_hint G_GNUC_UNUSED,
                                                 gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_BOXED_UINT_BOXED_POINTER) (gpointer     data1,
                                                                    guint        arg_1,
                                                                    gpointer     arg_2,
                                                                    guint        arg_3,
                                                                    gpointer     arg_4,
                                                                    gpointer     arg_5,
                                                                    gpointer     data2);
  register GMarshalFunc_VOID__UINT_BOXED_UINT_BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 6);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_BOXED_UINT_BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_boxed (param_values + 4),
            g_marshal_value_peek_pointer (param_values + 5),
            data2);
}

/* VOID:UINT,INT,STRING (_gen/signals-marshal.list:46) */
void
_tp_marshal_VOID__UINT_INT_STRING (GClosure     *closure,
                                   GValue       *return_value G_GNUC_UNUSED,
                                   guint         n_param_values,
                                   const GValue *param_values,
                                   gpointer      invocation_hint G_GNUC_UNUSED,
                                   gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_INT_STRING) (gpointer     data1,
                                                      guint        arg_1,
                                                      gint         arg_2,
                                                      gpointer     arg_3,
                                                      gpointer     data2);
  register GMarshalFunc_VOID__UINT_INT_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_INT_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_int (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            data2);
}

/* VOID:UINT,OBJECT (_gen/signals-marshal.list:47) */
void
_tp_marshal_VOID__UINT_OBJECT (GClosure     *closure,
                               GValue       *return_value G_GNUC_UNUSED,
                               guint         n_param_values,
                               const GValue *param_values,
                               gpointer      invocation_hint G_GNUC_UNUSED,
                               gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_OBJECT) (gpointer     data1,
                                                  guint        arg_1,
                                                  gpointer     arg_2,
                                                  gpointer     data2);
  register GMarshalFunc_VOID__UINT_OBJECT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_OBJECT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_object (param_values + 2),
            data2);
}

/* VOID:UINT,STRING (_gen/signals-marshal.list:48) */
void
_tp_marshal_VOID__UINT_STRING (GClosure     *closure,
                               GValue       *return_value G_GNUC_UNUSED,
                               guint         n_param_values,
                               const GValue *param_values,
                               gpointer      invocation_hint G_GNUC_UNUSED,
                               gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_STRING) (gpointer     data1,
                                                  guint        arg_1,
                                                  gpointer     arg_2,
                                                  gpointer     data2);
  register GMarshalFunc_VOID__UINT_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            data2);
}

/* VOID:UINT,STRING,BOXED,STRING (_gen/signals-marshal.list:49) */
void
_tp_marshal_VOID__UINT_STRING_BOXED_STRING (GClosure     *closure,
                                            GValue       *return_value G_GNUC_UNUSED,
                                            guint         n_param_values,
                                            const GValue *param_values,
                                            gpointer      invocation_hint G_GNUC_UNUSED,
                                            gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_STRING_BOXED_STRING) (gpointer     data1,
                                                               guint        arg_1,
                                                               gpointer     arg_2,
                                                               gpointer     arg_3,
                                                               gpointer     arg_4,
                                                               gpointer     data2);
  register GMarshalFunc_VOID__UINT_STRING_BOXED_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_STRING_BOXED_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_boxed (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            data2);
}

/* VOID:UINT,STRING,POINTER (_gen/signals-marshal.list:50) */
void
_tp_marshal_VOID__UINT_STRING_POINTER (GClosure     *closure,
                                       GValue       *return_value G_GNUC_UNUSED,
                                       guint         n_param_values,
                                       const GValue *param_values,
                                       gpointer      invocation_hint G_GNUC_UNUSED,
                                       gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_STRING_POINTER) (gpointer     data1,
                                                          guint        arg_1,
                                                          gpointer     arg_2,
                                                          gpointer     arg_3,
                                                          gpointer     data2);
  register GMarshalFunc_VOID__UINT_STRING_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_STRING_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_pointer (param_values + 3),
            data2);
}

/* VOID:UINT,STRING,STRING (_gen/signals-marshal.list:51) */
void
_tp_marshal_VOID__UINT_STRING_STRING (GClosure     *closure,
                                      GValue       *return_value G_GNUC_UNUSED,
                                      guint         n_param_values,
                                      const GValue *param_values,
                                      gpointer      invocation_hint G_GNUC_UNUSED,
                                      gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_STRING_STRING) (gpointer     data1,
                                                         guint        arg_1,
                                                         gpointer     arg_2,
                                                         gpointer     arg_3,
                                                         gpointer     data2);
  register GMarshalFunc_VOID__UINT_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            data2);
}

/* VOID:UINT,UCHAR,POINTER (_gen/signals-marshal.list:52) */
void
_tp_marshal_VOID__UINT_UCHAR_POINTER (GClosure     *closure,
                                      GValue       *return_value G_GNUC_UNUSED,
                                      guint         n_param_values,
                                      const GValue *param_values,
                                      gpointer      invocation_hint G_GNUC_UNUSED,
                                      gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_UCHAR_POINTER) (gpointer     data1,
                                                         guint        arg_1,
                                                         guchar       arg_2,
                                                         gpointer     arg_3,
                                                         gpointer     data2);
  register GMarshalFunc_VOID__UINT_UCHAR_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_UCHAR_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_uchar (param_values + 2),
            g_marshal_value_peek_pointer (param_values + 3),
            data2);
}

/* VOID:UINT,UINT (_gen/signals-marshal.list:53) */
void
_tp_marshal_VOID__UINT_UINT (GClosure     *closure,
                             GValue       *return_value G_GNUC_UNUSED,
                             guint         n_param_values,
                             const GValue *param_values,
                             gpointer      invocation_hint G_GNUC_UNUSED,
                             gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_UINT) (gpointer     data1,
                                                guint        arg_1,
                                                guint        arg_2,
                                                gpointer     data2);
  register GMarshalFunc_VOID__UINT_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            data2);
}

/* VOID:UINT,UINT,BOXED,POINTER (_gen/signals-marshal.list:54) */
void
_tp_marshal_VOID__UINT_UINT_BOXED_POINTER (GClosure     *closure,
                                           GValue       *return_value G_GNUC_UNUSED,
                                           guint         n_param_values,
                                           const GValue *param_values,
                                           gpointer      invocation_hint G_GNUC_UNUSED,
                                           gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_UINT_BOXED_POINTER) (gpointer     data1,
                                                              guint        arg_1,
                                                              guint        arg_2,
                                                              gpointer     arg_3,
                                                              gpointer     arg_4,
                                                              gpointer     data2);
  register GMarshalFunc_VOID__UINT_UINT_BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_UINT_BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_boxed (param_values + 3),
            g_marshal_value_peek_pointer (param_values + 4),
            data2);
}

/* VOID:UINT,UINT,BOXED,UINT64,POINTER (_gen/signals-marshal.list:55) */
void
_tp_marshal_VOID__UINT_UINT_BOXED_UINT64_POINTER (GClosure     *closure,
                                                  GValue       *return_value G_GNUC_UNUSED,
                                                  guint         n_param_values,
                                                  const GValue *param_values,
                                                  gpointer      invocation_hint G_GNUC_UNUSED,
                                                  gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_UINT_BOXED_UINT64_POINTER) (gpointer     data1,
                                                                     guint        arg_1,
                                                                     guint        arg_2,
                                                                     gpointer     arg_3,
                                                                     guint64      arg_4,
                                                                     gpointer     arg_5,
                                                                     gpointer     data2);
  register GMarshalFunc_VOID__UINT_UINT_BOXED_UINT64_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 6);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_UINT_BOXED_UINT64_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_boxed (param_values + 3),
            g_marshal_value_peek_uint64 (param_values + 4),
            g_marshal_value_peek_pointer (param_values + 5),
            data2);
}

/* VOID:UINT,UINT,POINTER (_gen/signals-marshal.list:56) */
void
_tp_marshal_VOID__UINT_UINT_POINTER (GClosure     *closure,
                                     GValue       *return_value G_GNUC_UNUSED,
                                     guint         n_param_values,
                                     const GValue *param_values,
                                     gpointer      invocation_hint G_GNUC_UNUSED,
                                     gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_UINT_POINTER) (gpointer     data1,
                                                        guint        arg_1,
                                                        guint        arg_2,
                                                        gpointer     arg_3,
                                                        gpointer     data2);
  register GMarshalFunc_VOID__UINT_UINT_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_UINT_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_pointer (param_values + 3),
            data2);
}

/* VOID:UINT,UINT,STRING (_gen/signals-marshal.list:57) */
void
_tp_marshal_VOID__UINT_UINT_STRING (GClosure     *closure,
                                    GValue       *return_value G_GNUC_UNUSED,
                                    guint         n_param_values,
                                    const GValue *param_values,
                                    gpointer      invocation_hint G_GNUC_UNUSED,
                                    gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_UINT_STRING) (gpointer     data1,
                                                       guint        arg_1,
                                                       guint        arg_2,
                                                       gpointer     arg_3,
                                                       gpointer     data2);
  register GMarshalFunc_VOID__UINT_UINT_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_UINT_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            data2);
}

/* VOID:UINT,UINT,UINT (_gen/signals-marshal.list:58) */
void
_tp_marshal_VOID__UINT_UINT_UINT (GClosure     *closure,
                                  GValue       *return_value G_GNUC_UNUSED,
                                  guint         n_param_values,
                                  const GValue *param_values,
                                  gpointer      invocation_hint G_GNUC_UNUSED,
                                  gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_UINT_UINT) (gpointer     data1,
                                                     guint        arg_1,
                                                     guint        arg_2,
                                                     guint        arg_3,
                                                     gpointer     data2);
  register GMarshalFunc_VOID__UINT_UINT_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_UINT_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            data2);
}

/* VOID:UINT,UINT,UINT,BOXED,POINTER (_gen/signals-marshal.list:59) */
void
_tp_marshal_VOID__UINT_UINT_UINT_BOXED_POINTER (GClosure     *closure,
                                                GValue       *return_value G_GNUC_UNUSED,
                                                guint         n_param_values,
                                                const GValue *param_values,
                                                gpointer      invocation_hint G_GNUC_UNUSED,
                                                gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_UINT_UINT_BOXED_POINTER) (gpointer     data1,
                                                                   guint        arg_1,
                                                                   guint        arg_2,
                                                                   guint        arg_3,
                                                                   gpointer     arg_4,
                                                                   gpointer     arg_5,
                                                                   gpointer     data2);
  register GMarshalFunc_VOID__UINT_UINT_UINT_BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 6);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_UINT_UINT_BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_boxed (param_values + 4),
            g_marshal_value_peek_pointer (param_values + 5),
            data2);
}

/* VOID:UINT,UINT,UINT,STRING (_gen/signals-marshal.list:60) */
void
_tp_marshal_VOID__UINT_UINT_UINT_STRING (GClosure     *closure,
                                         GValue       *return_value G_GNUC_UNUSED,
                                         guint         n_param_values,
                                         const GValue *param_values,
                                         gpointer      invocation_hint G_GNUC_UNUSED,
                                         gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_UINT_UINT_STRING) (gpointer     data1,
                                                            guint        arg_1,
                                                            guint        arg_2,
                                                            guint        arg_3,
                                                            gpointer     arg_4,
                                                            gpointer     data2);
  register GMarshalFunc_VOID__UINT_UINT_UINT_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_UINT_UINT_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            data2);
}

/* VOID:UINT,UINT,UINT,STRING,BOXED,UINT (_gen/signals-marshal.list:61) */
void
_tp_marshal_VOID__UINT_UINT_UINT_STRING_BOXED_UINT (GClosure     *closure,
                                                    GValue       *return_value G_GNUC_UNUSED,
                                                    guint         n_param_values,
                                                    const GValue *param_values,
                                                    gpointer      invocation_hint G_GNUC_UNUSED,
                                                    gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_UINT_UINT_STRING_BOXED_UINT) (gpointer     data1,
                                                                       guint        arg_1,
                                                                       guint        arg_2,
                                                                       guint        arg_3,
                                                                       gpointer     arg_4,
                                                                       gpointer     arg_5,
                                                                       guint        arg_6,
                                                                       gpointer     data2);
  register GMarshalFunc_VOID__UINT_UINT_UINT_STRING_BOXED_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 7);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_UINT_UINT_STRING_BOXED_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_boxed (param_values + 5),
            g_marshal_value_peek_uint (param_values + 6),
            data2);
}

/* VOID:UINT,UINT,UINT,UINT,UINT,STRING (_gen/signals-marshal.list:62) */
void
_tp_marshal_VOID__UINT_UINT_UINT_UINT_UINT_STRING (GClosure     *closure,
                                                   GValue       *return_value G_GNUC_UNUSED,
                                                   guint         n_param_values,
                                                   const GValue *param_values,
                                                   gpointer      invocation_hint G_GNUC_UNUSED,
                                                   gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_UINT_UINT_UINT_UINT_STRING) (gpointer     data1,
                                                                      guint        arg_1,
                                                                      guint        arg_2,
                                                                      guint        arg_3,
                                                                      guint        arg_4,
                                                                      guint        arg_5,
                                                                      gpointer     arg_6,
                                                                      gpointer     data2);
  register GMarshalFunc_VOID__UINT_UINT_UINT_UINT_UINT_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 7);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_UINT_UINT_UINT_UINT_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_uint (param_values + 4),
            g_marshal_value_peek_uint (param_values + 5),
            g_marshal_value_peek_string (param_values + 6),
            data2);
}

