#ifndef _CS_TELEPATHY_MACROS_H_
#define _CS_TELEPATHY_MACROS_H_

/*
 * Some magic here to support only those
 * interfaces that are supported by this object on DBus
 * NS_IMPL_ISUPPORTS uses NS_INTERFACE_TABLE_TAIL to
 * return the status of the QueryInterface.
 */

#define CS_TELEPATHY_INTERFACE_LIST_BEGIN                       \
  if (NS_SUCCEEDED(rv)) {                                       \
    char *dbusInterfaceName = NULL;

#define CS_TELEPATHY_INTERFACE_ITEM(_interface, _name)          \
    if (aIID.Equals(NS_GET_IID(_interface))) {                  \
      dbusInterfaceName = (char *)_name;                        \
      goto _csInterfaceCheck;                                   \
    }

#define CS_TELEPATHY_INTERFACE_LIST_END                         \
    goto _csSkipInterfaceCheck;                                 \
                                                                \
_csInterfaceCheck:                                              \
    rv = SupportsInterface((const char *)dbusInterfaceName);    \
  } /* NS_SUCCEEDED */                                          \
                                                                \
_csSkipInterfaceCheck:                                          \
  return rv;                                                    \
} /* End of QueryInterface Function */

#ifdef NS_INTERFACE_TABLE_TAIL
  #undef NS_INTERFACE_TABLE_TAIL
#endif

#ifndef NS_INTERFACE_TABLE12
#define NS_INTERFACE_TABLE12(_class, _i1, _i2, _i3, _i4, _i5, _i6, _i7,       \
                             _i8, _i9, _i10, _i11, _i12)                      \
  NS_INTERFACE_TABLE_BEGIN                                                    \
    NS_INTERFACE_TABLE_ENTRY(_class, _i1)                                     \
    NS_INTERFACE_TABLE_ENTRY(_class, _i2)                                     \
    NS_INTERFACE_TABLE_ENTRY(_class, _i3)                                     \
    NS_INTERFACE_TABLE_ENTRY(_class, _i4)                                     \
    NS_INTERFACE_TABLE_ENTRY(_class, _i5)                                     \
    NS_INTERFACE_TABLE_ENTRY(_class, _i6)                                     \
    NS_INTERFACE_TABLE_ENTRY(_class, _i7)                                     \
    NS_INTERFACE_TABLE_ENTRY(_class, _i8)                                     \
    NS_INTERFACE_TABLE_ENTRY(_class, _i9)                                     \
    NS_INTERFACE_TABLE_ENTRY(_class, _i10)                                    \
    NS_INTERFACE_TABLE_ENTRY(_class, _i11)                                    \
    NS_INTERFACE_TABLE_ENTRY(_class, _i12)                                    \
    NS_INTERFACE_TABLE_ENTRY_AMBIGUOUS(_class, nsISupports, _i1)              \
  NS_INTERFACE_TABLE_END
#endif

#ifndef NS_IMPL_QUERY_INTERFACE12
#define NS_IMPL_QUERY_INTERFACE12(_class, _i1, _i2, _i3, _i4, _i5, _i6,       \
                                  _i7, _i8, _i9, _i10, _i11, _i12)            \
  NS_INTERFACE_TABLE_HEAD(_class)                                             \
  NS_INTERFACE_TABLE12(_class, _i1, _i2, _i3, _i4, _i5, _i6, _i7, _i8,        \
                       _i9, _i10, _i11, _i12)                                 \
  NS_INTERFACE_TABLE_TAIL
#endif

#ifndef NS_IMPL_ISUPPORTS12
#define NS_IMPL_ISUPPORTS12(_class, _i1, _i2, _i3, _i4, _i5, _i6, _i7, _i8,   \
                            _i9, _i10, _i11, _i12)                            \
  NS_IMPL_ADDREF(_class)                                                      \
  NS_IMPL_RELEASE(_class)                                                     \
  NS_IMPL_QUERY_INTERFACE12(_class, _i1, _i2, _i3, _i4, _i5, _i6, _i7, _i8,   \
                            _i9, _i10, _i11, _i12)
#endif

#endif
