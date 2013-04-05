/***********************************************************
constants
***********************************************************/

const nsIProtocolHandler = Components.interfaces.nsIProtocolHandler;
const nsIURI = Components.interfaces.nsIURI;
const nsISupports = Components.interfaces.nsISupports;

const CLASS_ID = Components.ID("{c85bf507-efe8-4c4f-b931-962fe15f0040}");

const CLASS_NAME = "Protocol handler for loading Google Applets";

const CONTRACT_ID = "@mozilla.org/network/protocol;1?name=x-applet";

/***********************************************************
class definition
***********************************************************/


function AppletProtocolHandler()
{
}

AppletProtocolHandler.prototype =
{
  QueryInterface: function(iid)
  {
    if (!iid.equals(nsIProtocolHandler) &&
        !iid.equals(nsISupports))
      throw Components.results.NS_ERROR_NO_INTERFACE;
    return this;
  },

  scheme: "x-applet",
  defaultPort: -1,
  protocolFlags: nsIProtocolHandler.URI_NORELATIVE |
             nsIProtocolHandler.URI_NOAUTH ,

  allowPort: function(port, scheme)
  {
    return false;
  },

  newURI: function(spec, charset, baseURI)
  {
    var uri = Components.classes["@synovel.com/applet-uri;1"].createInstance(nsIURI);
    uri.spec = spec;
    return uri;
  },

  newChannel: function(aURI)
  {
    var ioService = Components.classes["@mozilla.org/network/io-service;1"].getService();
    ioService = ioService.QueryInterface(Components.interfaces.nsIIOService);


    if (aURI.spec.indexOf("_CS_UrlType=http") >= 0)
    { // create a http channel for this url 
      var uri_str = aURI.spec.split("&url=")[1];
      uri_str = unescape(uri_str);
      var ext_uri = ioService.newURI(uri_str, null, null);
      return ioService.newChannelFromURI(ext_uri);
    }

      
     var windowMediator = Components.classes["@mozilla.org/appshell/window-mediator;1"]
                                    .getService(Components.interfaces.nsIWindowMediator);
    var mainWindow = windowMediator.getMostRecentWindow("collab:main");
    var doc = mainWindow.document;
    var appletKey = aURI.spec.split("&_CS_appletId=")[1];

    var applet = doc.getElementById("collab-google-applet-" + appletKey);
    applet = applet.getElementsByTagName("collab-google-applet")[0];
    applet = applet.wrappedJSObject;

    var base64Src = applet.mSrc;
    var uri_str = "data:text/html;base64," + base64Src;

    var ext_uri = ioService.newURI(uri_str, null, null);
    var ext_channel = ioService.newChannelFromURI(ext_uri);
    return ext_channel;
  }    
}

var AppletProtocolHandlerFactory = {
  createInstance: function (aOuter, aIID)
  {
    if (aOuter != null)
      throw Components.results.NS_ERROR_NO_AGGREGATION;
    return (new AppletProtocolHandler()).QueryInterface(aIID);
  }
};

/***********************************************************
module definition (xpcom registration)
***********************************************************/
var AppletProtocolHandlerModule = {
  registerSelf: function(aCompMgr, aFileSpec, aLocation, aType)
  {
    aCompMgr = aCompMgr.
        QueryInterface(Components.interfaces.nsIComponentRegistrar);
    aCompMgr.registerFactoryLocation(CLASS_ID, CLASS_NAME, 
        CONTRACT_ID, aFileSpec, aLocation, aType);
  },

  unregisterSelf: function(aCompMgr, aLocation, aType)
  {
    aCompMgr = aCompMgr.
        QueryInterface(Components.interfaces.nsIComponentRegistrar);
    aCompMgr.unregisterFactoryLocation(CLASS_ID, aLocation);        
  },
  
  getClassObject: function(aCompMgr, aCID, aIID)
  {
    if (!aIID.equals(Components.interfaces.nsIFactory))
      throw Components.results.NS_ERROR_NOT_IMPLEMENTED;

    if (aCID.equals(CLASS_ID))
      return AppletProtocolHandlerFactory;

    throw Components.results.NS_ERROR_NO_INTERFACE;
  },

  canUnload: function(aCompMgr) { return true; }
};

/***********************************************************
module initialization

When the application registers the component, this function
is called.
***********************************************************/
function NSGetModule(aCompMgr, aFileSpec) { return AppletProtocolHandlerModule; } 
