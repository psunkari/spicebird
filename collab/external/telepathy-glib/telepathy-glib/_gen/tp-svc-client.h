#include <glib-object.h>
#include <dbus/dbus-glib.h>
#include <telepathy-glib/dbus-properties-mixin.h>

G_BEGIN_DECLS

/**
 * TpSvcClient:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcClient TpSvcClient;

/**
 * TpSvcClientClass:
 *
 * The class of TpSvcClient.
 * This interface has no D-Bus methods, so an
 * implementation can typically pass %NULL to
 * G_IMPLEMENT_INTERFACE() as the interface
 * initialization function.
 */
typedef struct _TpSvcClientClass TpSvcClientClass;

GType tp_svc_client_get_type (void);
#define TP_TYPE_SVC_CLIENT \
  (tp_svc_client_get_type ())
#define TP_SVC_CLIENT(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CLIENT, TpSvcClient))
#define TP_IS_SVC_CLIENT(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CLIENT))
#define TP_SVC_CLIENT_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CLIENT, TpSvcClientClass))



/**
 * TpSvcClientApprover:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcClientApprover TpSvcClientApprover;

/**
 * TpSvcClientApproverClass:
 *
 * The class of TpSvcClientApprover.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_client_approver (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_client_approver_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (add_dispatch_operation);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcClientApproverClass TpSvcClientApproverClass;

GType tp_svc_client_approver_get_type (void);
#define TP_TYPE_SVC_CLIENT_APPROVER \
  (tp_svc_client_approver_get_type ())
#define TP_SVC_CLIENT_APPROVER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CLIENT_APPROVER, TpSvcClientApprover))
#define TP_IS_SVC_CLIENT_APPROVER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CLIENT_APPROVER))
#define TP_SVC_CLIENT_APPROVER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CLIENT_APPROVER, TpSvcClientApproverClass))


typedef void (*tp_svc_client_approver_add_dispatch_operation_impl) (TpSvcClientApprover *self,
    const GPtrArray *in_Channels,
    const gchar *in_DispatchOperation,
    GHashTable *in_Properties,
    DBusGMethodInvocation *context);
void tp_svc_client_approver_implement_add_dispatch_operation (TpSvcClientApproverClass *klass, tp_svc_client_approver_add_dispatch_operation_impl impl);
/**
 * tp_svc_client_approver_return_from_add_dispatch_operation:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_client_approver_return_from_add_dispatch_operation (DBusGMethodInvocation *context);
static inline void
tp_svc_client_approver_return_from_add_dispatch_operation (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}


/**
 * TpSvcClientHandler:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcClientHandler TpSvcClientHandler;

/**
 * TpSvcClientHandlerClass:
 *
 * The class of TpSvcClientHandler.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_client_handler (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_client_handler_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (handle_channels);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcClientHandlerClass TpSvcClientHandlerClass;

GType tp_svc_client_handler_get_type (void);
#define TP_TYPE_SVC_CLIENT_HANDLER \
  (tp_svc_client_handler_get_type ())
#define TP_SVC_CLIENT_HANDLER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CLIENT_HANDLER, TpSvcClientHandler))
#define TP_IS_SVC_CLIENT_HANDLER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CLIENT_HANDLER))
#define TP_SVC_CLIENT_HANDLER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CLIENT_HANDLER, TpSvcClientHandlerClass))


typedef void (*tp_svc_client_handler_handle_channels_impl) (TpSvcClientHandler *self,
    const gchar *in_Account,
    const gchar *in_Connection,
    const GPtrArray *in_Channels,
    const GPtrArray *in_Requests_Satisfied,
    guint64 in_User_Action_Time,
    GHashTable *in_Handler_Info,
    DBusGMethodInvocation *context);
void tp_svc_client_handler_implement_handle_channels (TpSvcClientHandlerClass *klass, tp_svc_client_handler_handle_channels_impl impl);
/**
 * tp_svc_client_handler_return_from_handle_channels:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_client_handler_return_from_handle_channels (DBusGMethodInvocation *context);
static inline void
tp_svc_client_handler_return_from_handle_channels (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}


/**
 * TpSvcClientInterfaceRequests:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcClientInterfaceRequests TpSvcClientInterfaceRequests;

/**
 * TpSvcClientInterfaceRequestsClass:
 *
 * The class of TpSvcClientInterfaceRequests.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_client_interface_requests (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_client_interface_requests_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (add_request);
 *   IMPLEMENT (remove_request);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcClientInterfaceRequestsClass TpSvcClientInterfaceRequestsClass;

GType tp_svc_client_interface_requests_get_type (void);
#define TP_TYPE_SVC_CLIENT_INTERFACE_REQUESTS \
  (tp_svc_client_interface_requests_get_type ())
#define TP_SVC_CLIENT_INTERFACE_REQUESTS(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CLIENT_INTERFACE_REQUESTS, TpSvcClientInterfaceRequests))
#define TP_IS_SVC_CLIENT_INTERFACE_REQUESTS(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CLIENT_INTERFACE_REQUESTS))
#define TP_SVC_CLIENT_INTERFACE_REQUESTS_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CLIENT_INTERFACE_REQUESTS, TpSvcClientInterfaceRequestsClass))


typedef void (*tp_svc_client_interface_requests_add_request_impl) (TpSvcClientInterfaceRequests *self,
    const gchar *in_Request,
    GHashTable *in_Properties,
    DBusGMethodInvocation *context);
void tp_svc_client_interface_requests_implement_add_request (TpSvcClientInterfaceRequestsClass *klass, tp_svc_client_interface_requests_add_request_impl impl);
/**
 * tp_svc_client_interface_requests_return_from_add_request:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_client_interface_requests_return_from_add_request (DBusGMethodInvocation *context);
static inline void
tp_svc_client_interface_requests_return_from_add_request (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}

typedef void (*tp_svc_client_interface_requests_remove_request_impl) (TpSvcClientInterfaceRequests *self,
    const gchar *in_Request,
    const gchar *in_Error,
    const gchar *in_Message,
    DBusGMethodInvocation *context);
void tp_svc_client_interface_requests_implement_remove_request (TpSvcClientInterfaceRequestsClass *klass, tp_svc_client_interface_requests_remove_request_impl impl);
/**
 * tp_svc_client_interface_requests_return_from_remove_request:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_client_interface_requests_return_from_remove_request (DBusGMethodInvocation *context);
static inline void
tp_svc_client_interface_requests_return_from_remove_request (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}


/**
 * TpSvcClientObserver:
 *
 * Dummy typedef representing any implementation of this interface.
 */
typedef struct _TpSvcClientObserver TpSvcClientObserver;

/**
 * TpSvcClientObserverClass:
 *
 * The class of TpSvcClientObserver.
 *
 * In a full implementation of this interface (i.e. all
 * methods implemented), the interface initialization
 * function used in G_IMPLEMENT_INTERFACE() would
 * typically look like this:
 *
 * <programlisting>
 * static void
 * implement_client_observer (gpointer klass,
 *     gpointer unused G_GNUC_UNUSED)
 * {
 * #define IMPLEMENT(x) tp_svc_client_observer_implement_###x (\
 *   klass, my_object_###x)
 *   IMPLEMENT (observe_channels);
 * #undef IMPLEMENT
 * }
 * </programlisting>
 */
typedef struct _TpSvcClientObserverClass TpSvcClientObserverClass;

GType tp_svc_client_observer_get_type (void);
#define TP_TYPE_SVC_CLIENT_OBSERVER \
  (tp_svc_client_observer_get_type ())
#define TP_SVC_CLIENT_OBSERVER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), TP_TYPE_SVC_CLIENT_OBSERVER, TpSvcClientObserver))
#define TP_IS_SVC_CLIENT_OBSERVER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TP_TYPE_SVC_CLIENT_OBSERVER))
#define TP_SVC_CLIENT_OBSERVER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_INTERFACE((obj), TP_TYPE_SVC_CLIENT_OBSERVER, TpSvcClientObserverClass))


typedef void (*tp_svc_client_observer_observe_channels_impl) (TpSvcClientObserver *self,
    const gchar *in_Account,
    const gchar *in_Connection,
    const GPtrArray *in_Channels,
    const gchar *in_Dispatch_Operation,
    const GPtrArray *in_Requests_Satisfied,
    GHashTable *in_Observer_Info,
    DBusGMethodInvocation *context);
void tp_svc_client_observer_implement_observe_channels (TpSvcClientObserverClass *klass, tp_svc_client_observer_observe_channels_impl impl);
/**
 * tp_svc_client_observer_return_from_observe_channels:
 * @context: The D-Bus method invocation context
 *
 * Return successfully by calling dbus_g_method_return().
 * This inline function exists only to provide type-safety.
 */
static inline
/* this comment is to stop gtkdoc realising this is static */
void tp_svc_client_observer_return_from_observe_channels (DBusGMethodInvocation *context);
static inline void
tp_svc_client_observer_return_from_observe_channels (DBusGMethodInvocation *context)
{
  dbus_g_method_return (context);
}



G_END_DECLS
