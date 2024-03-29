/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* configure arguments */
#define CONFIG_ARGS " '--disable-screensaver' '--disable-startup-notification' '--disable-gtkspell' '--disable-gstreamer' '--disable-vv' '--disable-idn' '--disable-meanwhile' '--disable-avahi' '--disable-nm' '--disable-perl' '--disable-tcl' '--disable-sm' '--disable-dbus' '--disable-gtkui' '--without-x' '--disable-gestures' '--disable-pixmaps-install' '--disable-nls' '--enable-cyrus-sasl'"

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* Define if debugging is enabled. */
/* #undef DEBUG */

/* display version info */
#define DISPLAY_VERSION "2.6.5"

/* Define if mono enabled. */
/* #undef ENABLE_MONO */

/* always defined to indicate that i18n is enabled */
/* #undef ENABLE_NLS */

/* Define if gst_registry_fork_set_enabled exists */
/* #undef GST_CAN_DISABLE_FORKING */

/* Define to 1 if you have `alloca', as a function or macro. */
#define HAVE_ALLOCA 1

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
#define HAVE_ALLOCA_H 1

/* Define if you have the external 'altzone' variable. */
/* #undef HAVE_ALTZONE */

/* Define to 1 if you have the <arpa/nameser_compat.h> header file. */
#define HAVE_ARPA_NAMESER_COMPAT_H 1

/* Define to 1 if you have the `atexit' function. */
#define HAVE_ATEXIT 1

/* Define to 1 if you have the `bind_textdomain_codeset' function. */
#define HAVE_BIND_TEXTDOMAIN_CODESET 1

/* Define to 1 if you have the `connect' function. */
#define HAVE_CONNECT 1

/* Define to 1 if Cyrus SASL is present */
#define HAVE_CYRUS_SASL 1

/* Define if you have the external 'daylight' variable. */
#define HAVE_DAYLIGHT 1

/* Define if we are using D-Bus. */
/* #undef HAVE_DBUS */

/* Define to 1 if you have the `dcgettext' function. */
#define HAVE_DCGETTEXT 1

/* Define to 1 if you have the declaration of `tzname', and to 0 if you don't.
   */
/* #undef HAVE_DECL_TZNAME */

/* Define to 1 if you have the <dlfcn.h> header file. */
#ifndef XP_WIN
#define HAVE_DLFCN_H 1
#endif

/* whether or not we have dot */
/* #undef HAVE_DOT */

/* whether or not we have doxygen */
/* #undef HAVE_DOXYGEN */

/* Define if we're using evolution addressbook. */
/* #undef HAVE_EVOLUTION_ADDRESSBOOK */

/* Define to 1 if you have the <EXTERN.h> header file. */
/* #undef HAVE_EXTERN_H */

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if your stdio has int fileno(FILE *). */
#define HAVE_FILENO 1

/* Define to 1 if you have the getaddrinfo function. */
#define HAVE_GETADDRINFO 1

/* Define to 1 if you have the `gethostid' function. */
#define HAVE_GETHOSTID 1

/* Define to 1 if you have the `getopt_long' function. */
#define HAVE_GETOPT_LONG 1

/* Define if the GNU gettext() function is already present or preinstalled. */
#define HAVE_GETTEXT 1

/* Define if you have GnuTLS */
/* #undef HAVE_GNUTLS */

/* Define if your gnutls has the GNUTLS_CERT_INSECURE_ALGORITHM flag */
/* #undef HAVE_GNUTLS_CERT_INSECURE_ALGORITHM */

/* Define to 1 if you have the <gnutls/gnutls.h> header file. */
/* #undef HAVE_GNUTLS_GNUTLS_H */

/* Define if your gnutls has gnutls_priority_set_direct and friends */
/* #undef HAVE_GNUTLS_PRIORITY_FUNCS */

/* Define to 1 if you have the `inet_ntop' function. */
#define HAVE_INET_NTOP 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define if we have IOKit */
/* #undef HAVE_IOKIT */

/* Define to 1 if you have the `krb_get_err_text' function. */
/* #undef HAVE_KRB_GET_ERR_TEXT */

/* Define to 1 if you have the `krb_get_lrealm' function. */
/* #undef HAVE_KRB_GET_LREALM */

/* Define to 1 if you have the `krb_log' function. */
/* #undef HAVE_KRB_LOG */

/* Define to 1 if you have the `krb_rd_req' function. */
/* #undef HAVE_KRB_RD_REQ */

/* Define to 1 if you have the `krb_set_key' function. */
/* #undef HAVE_KRB_SET_KEY */

/* Define if your <locale.h> file defines LC_MESSAGES. */
#define HAVE_LC_MESSAGES 1

/* Define to 1 if you have the `db' library (-ldb). */
/* #undef HAVE_LIBDB */

/* Define to 1 if you have libgadu. */
/* #undef HAVE_LIBGADU */

/* Define to 1 if you have the `nsl' library (-lnsl). */
#define HAVE_LIBNSL 1

/* Define to 1 if you have the `pthread' library (-lpthread). */
/* #undef HAVE_LIBPTHREAD */

/* Define to 1 if you have the `resolv' library (-lresolv). */
#define HAVE_LIBRESOLV 1

/* Define to 1 if you have the `socket' library (-lsocket). */
/* #undef HAVE_LIBSOCKET */

/* Define to 1 if you have the `util' library (-lutil). */
/* #undef HAVE_LIBUTIL */

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the `lrand48' function. */
#define HAVE_LRAND48 1

/* Define to 1 if you have the <malloc.h> header file. */
#define HAVE_MALLOC_H 1

/* Define to 1 if you have the `memcpy' function. */
#define HAVE_MEMCPY 1

/* Define to 1 if you have the `memmove' function. */
#define HAVE_MEMMOVE 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `mono_jit_init' function. */
/* #undef HAVE_MONO_JIT_INIT */

/* Define to 1 if you have the <mono/jit/jit.h> header file. */
/* #undef HAVE_MONO_JIT_JIT_H */

/* Define to 1 if you have the <mono/metadata/object.h> header file. */
/* #undef HAVE_MONO_METADATA_OBJECT_H */

/* Define if we have NetworkManager. */
/* #undef HAVE_NETWORKMANAGER */

/* Define to 1 if you have the <nspr.h> header file. */
/* #undef HAVE_NSPR_H */

/* Define if you have Mozilla NSS */
#define HAVE_NSS 1

/* Define to 1 if you have the <nss.h> header file. */
/* #undef HAVE_NSS_H */

/* Define if we have Pango 1.4 or newer. */
/* #undef HAVE_PANGO14 */

/* Define to 1 if you have the <paths.h> header file. */
#define HAVE_PATHS_H 1

/* Compile with support for perl */
/* #undef HAVE_PERL */

/* Define to 1 if you have the `Perl_eval_pv' function. */
/* #undef HAVE_PERL_EVAL_PV */

/* Define to 1 if you have the <perl.h> header file. */
/* #undef HAVE_PERL_H */

/* Define to 1 if you have the `perl_run' function. */
/* #undef HAVE_PERL_RUN */

/* Define to 1 if you have the <prio.h> header file. */
/* #undef HAVE_PRIO_H */

/* Define to 1 if you have the `random' function. */
#define HAVE_RANDOM 1

/* Define to 1 if you have the <regex.h> header file. */
#define HAVE_REGEX_H 1

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the <sgtty.h> header file. */
#define HAVE_SGTTY_H 1

/* Define to 1 if you have the <signal.h> header file. */
#define HAVE_SIGNAL_H 1

/* Define if we have silcmime.h */
/* #undef HAVE_SILCMIME_H */

/* Define to 1 if you have the <smime.h> header file. */
/* #undef HAVE_SMIME_H */

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define if you have SSL */
#define HAVE_SSL 1

/* Define to 1 if you have the <ssl.h> header file. */
/* #undef HAVE_SSL_H */

/* Define if we're using libstartup-notification. */
/* #undef HAVE_STARTUP_NOTIFICATION */

/* Define to 1 if you have the <stdarg.h> header file. */
#define HAVE_STDARG_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the `strftime' function. */
#define HAVE_STRFTIME 1

/* Define to 1 if you have a strftime() that supports the %z format string. */
#define HAVE_STRFTIME_Z_FORMAT 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define if struct sockaddr has an sa_len member */
/* #undef HAVE_STRUCT_SOCKADDR_SA_LEN */

/* Define to 1 if `tm_zone' is member of `struct tm'. */
#ifndef XP_WIN
#define HAVE_STRUCT_TM_TM_ZONE 1
#endif

/* Define to 1 if you have the <sys/cdefs.h> header file. */
#define HAVE_SYS_CDEFS_H 1

/* Define to 1 if you have the <sys/file.h> header file. */
#define HAVE_SYS_FILE_H 1

/* Define to 1 if you have the <sys/filio.h> header file. */
/* #undef HAVE_SYS_FILIO_H */

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/msgbuf.h> header file. */
/* #undef HAVE_SYS_MSGBUF_H */

/* Define to 1 if you have the <sys/param.h> header file. */
#ifndef XP_WIN
#define HAVE_SYS_PARAM_H 1
#endif

/* Define to 1 if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#ifndef XP_WIN
#define HAVE_SYS_SOCKET_H 1
#endif

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/sysctl.h> header file. */
#ifndef XP_WIN
#define HAVE_SYS_SYSCTL_H 1
#endif

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/uio.h> header file. */
#define HAVE_SYS_UIO_H 1

/* Define to 1 if you have the <sys/utsname.h> header file. */
#define HAVE_SYS_UTSNAME_H 1

/* Define to 1 if you have the <sys/wait.h> header file. */
#define HAVE_SYS_WAIT_H 1

/* Compile with support for the Tcl toolkit */
/* #undef HAVE_TCL */

/* Define to 1 if you have the <termios.h> header file. */
#define HAVE_TERMIOS_H 1

/* Define if you have the external 'timezone' variable. */
#define HAVE_TIMEZONE 1

/* Compile with support for the Tk toolkit */
/* #undef HAVE_TK */

/* Define if you have a tm_gmtoff member in struct tm */
#ifndef XP_WIN
#define HAVE_TM_GMTOFF 1
#endif

/* Define to 1 if your `struct tm' has `tm_zone'. Deprecated, use
   `HAVE_STRUCT_TM_TM_ZONE' instead. */
#define HAVE_TM_ZONE 1

/* Define to 1 if you don't have `tm_zone' but do have the external array
   `tzname'. */
/* #undef HAVE_TZNAME */

/* Define to 1 if you have the <unistd.h> header file. */
#ifndef XP_WIN
#define HAVE_UNISTD_H 1
#endif

/* Define to 1 if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/* Define to 1 if you have X11 */
/* #undef HAVE_X11 */

/* Define to 1 if you have the <X11/SM/SMlib.h> header file. */
/* #undef HAVE_X11_SM_SMLIB_H */

/* whether or not we have xsltproc for devhelp index */
/* #undef HAVE_XSLTPROC */

/* Define if external libzephyr should be used. */
/* #undef LIBZEPHYR_EXT */

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Define to 1 if you don't have wide-character support. */
#define NO_WIDECHAR 1

/* Define if old perl is installed. */
/* #undef OLD_PERL */

/* Name of package */
#define PACKAGE "pidgin"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "devel@pidgin.im"

/* Define to the full name of this package. */
#define PACKAGE_NAME "pidgin"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "pidgin 2.6.5"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "pidgin"

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.6.5"

/* Define if plugins are enabled. */
#define PURPLE_PLUGINS 1

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* The size of `time_t', as computed by sizeof. */
#define SIZEOF_TIME_T 8

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Loads static protocol plugin module initialization functions. */
#define STATIC_PROTO_INIT static void static_proto_init(void) {  }

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* Use Farsight for voice and video */
/* #undef USE_FARSIGHT */

/* Use GStreamer interfaces for X overlay support */
/* #undef USE_GSTINTERFACES */

/* Use GStreamer for playing sounds */
/* #undef USE_GSTREAMER */

/* Define if we're using GtkSpell */
/* #undef USE_GTKSPELL */

/* Use GNU Libidn for stringprep and IDN */
/* #undef USE_IDN */

/* Define if python headers are available. */
/* #undef USE_PYTHON */

/* Define if we're using XScreenSaver. */
/* #undef USE_SCREENSAVER */

/* Define if we're using X Session Management. */
/* #undef USE_SM */

/* Use voice and video */
/* #undef USE_VV */

/* 'va_lists' cannot be copied as values */
#define VA_COPY_AS_ARRAY 1

/* Version number of package */
#define VERSION "2.6.5"

/* Define to 1 if your processor stores words with the most significant byte
   first (like Motorola and SPARC, unlike Intel and VAX). */
/* #undef WORDS_BIGENDIAN */

/* Define to 1 if the X Window System is missing or not being used. */
#define X_DISPLAY_MISSING 1

/* Size of an int32. */
#define ZEPHYR_INT32 long

/* Define if kerberos should be used in Zephyr. */
/* #undef ZEPHYR_USES_KERBEROS */

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* socklen_t size */
/* #undef socklen_t */
