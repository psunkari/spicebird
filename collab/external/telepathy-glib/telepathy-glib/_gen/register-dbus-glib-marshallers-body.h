void
_tp_register_dbus_glib_marshallers (void)
{
  dbus_g_object_register_marshaller (_tp_marshal_VOID__BOXED_BOOLEAN,
      G_TYPE_NONE,       /* return */
      G_TYPE_BOXED,
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__BOXED_BOXED,
      G_TYPE_NONE,       /* return */
      G_TYPE_BOXED,
      G_TYPE_BOXED,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__BOXED_BOXED_BOXED_BOXED_BOXED,
      G_TYPE_NONE,       /* return */
      G_TYPE_BOXED,
      G_TYPE_BOXED,
      G_TYPE_BOXED,
      G_TYPE_BOXED,
      G_TYPE_BOXED,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__BOXED_STRING,
      G_TYPE_NONE,       /* return */
      G_TYPE_BOXED,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__BOXED_STRING_STRING,
      G_TYPE_NONE,       /* return */
      G_TYPE_BOXED,
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__BOXED_STRING_UINT_UINT_BOOLEAN,
      G_TYPE_NONE,       /* return */
      G_TYPE_BOXED,
      G_TYPE_STRING,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__BOXED_UINT_STRING,
      G_TYPE_NONE,       /* return */
      G_TYPE_BOXED,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__BOXED_UINT_UINT_UINT,
      G_TYPE_NONE,       /* return */
      G_TYPE_BOXED,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__DOUBLE_STRING_UINT_STRING,
      G_TYPE_NONE,       /* return */
      G_TYPE_DOUBLE,
      G_TYPE_STRING,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__STRING_BOXED,
      G_TYPE_NONE,       /* return */
      G_TYPE_STRING,
      G_TYPE_BOXED,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__STRING_BOXED_BOXED_BOXED_BOXED_UINT_UINT,
      G_TYPE_NONE,       /* return */
      G_TYPE_STRING,
      G_TYPE_BOXED,
      G_TYPE_BOXED,
      G_TYPE_BOXED,
      G_TYPE_BOXED,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__STRING_BOXED_STRING,
      G_TYPE_NONE,       /* return */
      G_TYPE_STRING,
      G_TYPE_BOXED,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__STRING_STRING,
      G_TYPE_NONE,       /* return */
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__STRING_STRING_STRING,
      G_TYPE_NONE,       /* return */
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__UINT64,
      G_TYPE_NONE,       /* return */
      G_TYPE_UINT64,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__UINT_BOXED,
      G_TYPE_NONE,       /* return */
      G_TYPE_UINT,
      G_TYPE_BOXED,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__UINT_BOXED_BOXED,
      G_TYPE_NONE,       /* return */
      G_TYPE_UINT,
      G_TYPE_BOXED,
      G_TYPE_BOXED,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__UINT_BOXED_UINT,
      G_TYPE_NONE,       /* return */
      G_TYPE_UINT,
      G_TYPE_BOXED,
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__UINT_STRING,
      G_TYPE_NONE,       /* return */
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__UINT_STRING_BOXED_STRING,
      G_TYPE_NONE,       /* return */
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_BOXED,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__UINT_STRING_STRING,
      G_TYPE_NONE,       /* return */
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__UINT_UINT,
      G_TYPE_NONE,       /* return */
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__UINT_UINT_STRING,
      G_TYPE_NONE,       /* return */
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__UINT_UINT_UINT,
      G_TYPE_NONE,       /* return */
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__UINT_UINT_UINT_STRING,
      G_TYPE_NONE,       /* return */
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__UINT_UINT_UINT_STRING_BOXED_UINT,
      G_TYPE_NONE,       /* return */
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_BOXED,
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (_tp_marshal_VOID__UINT_UINT_UINT_UINT_UINT_STRING,
      G_TYPE_NONE,       /* return */
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_UINT,
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (g_cclosure_marshal_VOID__BOOLEAN,
      G_TYPE_NONE,       /* return */
      G_TYPE_BOOLEAN,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (g_cclosure_marshal_VOID__BOXED,
      G_TYPE_NONE,       /* return */
      G_TYPE_BOXED,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (g_cclosure_marshal_VOID__STRING,
      G_TYPE_NONE,       /* return */
      G_TYPE_STRING,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (g_cclosure_marshal_VOID__UCHAR,
      G_TYPE_NONE,       /* return */
      G_TYPE_UCHAR,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (g_cclosure_marshal_VOID__UINT,
      G_TYPE_NONE,       /* return */
      G_TYPE_UINT,
      G_TYPE_INVALID);
  dbus_g_object_register_marshaller (g_cclosure_marshal_VOID__VOID,
      G_TYPE_NONE,       /* return */
      G_TYPE_NONE,
      G_TYPE_INVALID);
}
