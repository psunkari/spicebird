/***********************************************************
constants
***********************************************************/

const nsIURI = Components.interfaces.nsIURI;
const nsISupports = Components.interfaces.nsISupports;

const CLASS_ID = Components.ID("{5eb11cd6-fd4f-4fc7-9a06-b36c2352df1e}");

const CLASS_NAME = "Custom URL for Google Applets";

const CONTRACT_ID = "@synovel.com/applet-uri;1";
/*const CONTRACT_ID = "@mozilla.org/network/simple-uri;1?type=applet";
*/

/***********************************************************
class definition
***********************************************************/

function GoogleAppletURL()
{
}

GoogleAppletURL.prototype =
{
  QueryInterface: function(iid)
  {
    if (!iid.equals(nsIURI) &&
        !iid.equals(nsISupports))
      throw Components.results.NS_ERROR_NO_INTERFACE;
    return this;
  },

  spec: null,
  prePath: "",
  scheme: "x-applet",
  userPass: "",
  username: "",
  password: "",
  hostPort: -1,
  host: "www.synovel.com",
  port: 80,
  path: "/",

  schemeIs : function(aStr) {
    return this.scheme == aStr;
  },

  equals : function(aUri) {
    return this.spec == aUri.spec;
  },

  clone : function() {
    var uri = Components.classes["@synovel.com/applet-uri;1"].createInstance(nsIURI);
    uri.spec = this.spec; // Need to copy other params also ??
    return uri;
  },
}

var GoogleAppletURLFactory = {
  createInstance: function (aOuter, aIID)
  {
    if (aOuter != null)
      throw Components.results.NS_ERROR_NO_AGGREGATION;
    return (new GoogleAppletURL()).QueryInterface(aIID);
  }
};

/***********************************************************
module definition (xpcom registration)
***********************************************************/
var GoogleAppletURLModule = {
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
      return GoogleAppletURLFactory;

    throw Components.results.NS_ERROR_NO_INTERFACE;
  },

  canUnload: function(aCompMgr) { return true; }
};

/***********************************************************
module initialization

When the application registers the component, this function
is called.
***********************************************************/
function NSGetModule(aCompMgr, aFileSpec) { return GoogleAppletURLModule; } 
