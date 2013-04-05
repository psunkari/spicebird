// File taken from ScribeFire 2.1 Firefox Blogging Extension licensed under GPL 2.0.
// Some of the API Functions below are derived from GPL code originally by Flock Inc:
// Released under the same GLP license.
//
// For the original source, see: http://cvs-mirror.flock.com/index.cgi/mozilla/browser/components/flock/blog/content/blogapi.js?rev=1.19&content-type=text/vnd.viewcvs-markup
// and http://cvs-mirror.flock.com/index.cgi/mozilla/browser/components/flock/blog/content/
//
// Usage: myblog.init('blogger', '0123456789ABCDEF', 'http://plant.blogger.com/api/RPC2' ,'3724458', null, 'BillyBob',  'bbBaby'  )


var gPFFDebugTemp = [];

var perFormancingBlogAPI= function () {
    this.addCategories = false;
    this.extendedEntries = false;
	
	this.supportsPages = false;
	this.supportsTags = false;
	this.supportsDrafts = true;
	
	this.standard = true;
}

perFormancingBlogAPI.prototype = {
    init: function (aName, aAppKey, aAPILink, aBlogID, aPreferred, aUsername, aPassword, aNeedsAuth) {
        this.name = aName;
        this.appKey = aAppKey;
        this.editLink = "";
        this.apiLink = aAPILink;
        this.appKey = "";
        this.blogID = aBlogID;
        this.username = aUsername;
        this.password = aPassword;
        this.needsAuth = aNeedsAuth;
    },
    setAuth: function (aUsername, aPassword, aURL){},
    doSetup: function (){},
    doAuth: function (aUsername, aPassword) {},
    newPost: function (aTitle, aDescription, aArrayOfCats, aDateCreated, aPublish) {},
    editPost: function (aPostid, aTitle, aDescription, aArrayOfCats, aDateCreated, aPublish) {},
    deletePost: function (aPostid, aEditURI) {},
	deletePage: function (pageId) {},
    getUsersBlogs: function () {},
    getRecentPosts: function (aNumber) {},
    setPostCategories: function (aPostid, aCategories) {},
    getCategoryList: function () {},
    publishPost: function (aPostid) {},
    fileUpload: function (aFileName, aMimeType, aDataString) {},
    aggregateCategories : function (catArray) {}
}

//This Function is derived from GPL code originally by Flock Inc:
//myblog = new perFormancingBloggerAPI()
var perFormancingBloggerAPI = function () {
    this.newPost = function (aTitle, aDescription, aArrayOfCats, aDateCreated, aPublish) {
		// Doesn't support dateCreated
        var argArray = [this.apiLink, this.appKey, this.blogID, this.username, this.password, aDescription, aPublish];
        return performancingAPICalls.blogger_newPost(argArray);
    };
    this.editPost = function (aPostid, aTitle, aDescription, aArrayOfCats, aDateCreated, aPublish) { 
		// Doesn't support dateCreated
        var argArray = [this.apiLink, this.appKey, aPostid, this.username, this.password, aDescription, aPublish];
        return performancingAPICalls.blogger_editPost(argArray);
    };
    this.deletePost = function (aPostid) {
        var argArray = [this.apiLink, this.appKey, aPostid, this.username, this.password, true];
        return performancingAPICalls.blogger_deletePost(argArray);
    };
	this.deletePage = function (pageId) {
		return false;
	};
    this.getUsersBlogs = function () {
        var argArray = [this.apiLink, this.appKey, this.username, this.password];
        return performancingAPICalls.blogger_getUsersBlogs(argArray);
    };
    this.getRecentPosts = function () {
        var argArray = [this.apiLink, this.appKey, this.blogID, this.username, this.password, 50];
        return performancingAPICalls.blogger_getRecentPosts(argArray);
    };
    this.getCategoryList = function (argArray) { //Not available
		return false;
    };
    this.setPostCategories = function (aPostid, aCategories) { //Not Available
        return false;
    };
    this.publishPost = function (aPostid) {
        return false;
    };
}
perFormancingBloggerAPI.prototype = new perFormancingBlogAPI();

//This Function is derived from GPL code originally by Flock Inc:
var performancingMetaweblogAPI = function () {
    this.newPost = function (aTitle, aDescription, aArrayOfCats, aDateCreated, aPublish) {
		var ourNewDate = "";

        if(aDateCreated != ""){
           ourNewDate = new Date(aDateCreated)
        }
		
        var content_t =
        {
            title: aTitle,
            description: aDescription,
            categories: aArrayOfCats,
			dateCreated : ourNewDate
        };

        var argArray = [this.apiLink, this.blogID, this.username, this.password, content_t, aPublish];
        return performancingAPICalls.metaWeblog_newPost(argArray);
    };
    this.editPost = function (aPostid, aTitle, aDescription, aArrayOfCats, aDateCreated, aPublish) {
        var ourNewDate = "";

        if(aDateCreated != ""){
           ourNewDate = new Date(aDateCreated)
        }
		
        var content_t =
        {
            title: aTitle,
            description: aDescription,
            dateCreated: ourNewDate,
            categories: aArrayOfCats
        };
		
        var argArray = [this.apiLink, aPostid, this.username, this.password, content_t, aPublish];
        return performancingAPICalls.metaWeblog_editPost(argArray);
    };
    this.deletePost = function (aPostid) {
        var argArray = [this.apiLink, this.appKey, aPostid, this.username, this.password, 'bool1'];
        return performancingAPICalls.blogger_deletePost(argArray);
    };
	this.deletePage = function (pageId){
		return false;
	};
    this.getUsersBlogs = function () {
        var argArray = [this.apiLink, this.appKey, this.username, this.password];
        return performancingAPICalls.blogger_getUsersBlogs(argArray);
    };
    this.getRecentPosts = function (aNumber) {
        var argArray = [this.apiLink, this.blogID, this.username, this.password, aNumber];
        return performancingAPICalls.metaWeblog_getRecentPosts(argArray);
        //return blogger_getRecentPosts(this.apiLink, this.appKey, this.blogID, this.username, this.password, aNumber);
    };
    /*
    metaWeblog.getCategories 
    metaWeblog.getCategories (blogid, username, password) returns struct
    The struct returned contains one struct for each category, containing the following elements: description, htmlUrl and rssUrl.
    This entry-point allows editing tools to offer category-routing as a feature.
    */
    this.getCategoryList = function () { //Not Available
        //return false;
        var argArray = [this.apiLink, this.blogID, this.username, this.password];
        return performancingAPICalls.metaWeblog_getCategoryList(argArray);
        
    };
    this.setPostCategories = function (aPostid, aCategories) { //Not Available
        //var argArray = [];
        return false;
    };
    this.publishPost = function (aPostid) {
        return false;
    };
    
    //metaWeblog.newMediaObject (blogid, username, password, struct)
    this.fileUpload = function (aFileName, aMimeType, aDataString) {
        var content_t =
        {
            name: aFileName,
            type: aMimeType,
            bits: aDataString.toString() //aBase64Data
        };
        var argArray = [this.apiLink, this.blogID, this.username, this.password, content_t];
        return performancingAPICalls.metaWeblog_newMediaObject(argArray);
    };
}
performancingMetaweblogAPI.prototype = new perFormancingBlogAPI();

var perFormancingMovableTypeAPI = function () {
	this.newPost = function (aTitle, aDescription, aArrayOfCats, aDateCreated, aPublish, tags) {
		var ourNewDate = "";

        if(aDateCreated != ""){
           ourNewDate = new Date(aDateCreated)
        }
		
		var content_t = {
			title : aTitle,
			description : aDescription,
			categories : aArrayOfCats,
			mt_keywords : tags,
			dateCreated : ourNewDate
		};
		
		var argArray = [this.apiLink, this.blogID, this.username, this.password, content_t, aPublish];
		return performancingAPICalls.metaWeblog_newPost(argArray);
	};
	
	this.newPage = function (aTitle, aDescription, aDateCreated, aPublish) {
		var ourNewDate = "";

        if(aDateCreated != ""){
           ourNewDate = new Date(aDateCreated)
        }
		
		var content_t = {
			title : aTitle,
			description : aDescription,
			dateCreated : ourNewDate
		};

		var argArray = [this.apiLink, this.blogID, this.username, this.password, content_t, aPublish];
		return performancingAPICalls.wp_newPage(argArray);
	};
	
	this.editPost = function (aPostid, aTitle, aDescription, aArrayOfCats, aDateCreated, aPublish, tags) {
		var ourNewDate = "";
		if (!tags) tags = "";
		if(aDateCreated != ""){
			ourNewDate = new Date(aDateCreated)
		}

		var content_t = {
			title: aTitle,
			description: aDescription,
			categories: aArrayOfCats,
			dateCreated: ourNewDate,
			mt_keywords : tags
		};
		
		var argArray = [this.apiLink, aPostid, this.username, this.password, content_t, aPublish];
		return performancingAPICalls.metaWeblog_editPost(argArray);
	};
	
	this.deletePost = function (aPostid) {
		var argArray = [this.apiLink, this.appKey, aPostid, this.username, this.password, 1];
		return performancingAPICalls.blogger_deletePost(argArray);
	};
	
	this.deletePage = function (pageId) {
        var argArray = [this.apiLink, this.blogID, this.username, this.password, pageId, true];
        return performancingAPICalls.wp_deletePage(argArray);
	};
	
	this.getUsersBlogs = function () {
		var argArray = [this.apiLink, this.appKey, this.username, this.password];
		return performancingAPICalls.blogger_getUsersBlogs(argArray);
	};
	
	this.getRecentPosts = function () {
		var argArray = [this.apiLink, this.blogID, this.username, this.password, 50];
		return performancingAPICalls.metaWeblog_getRecentPosts(argArray);
	};
	
	this.getPages = function () {
		var argArray = [this.apiLink, this.blogID, this.username, this.password];
		return performancingAPICalls.wp_getPages(argArray);
	};
	
	this.getPageList = function () {
		var argArray = [this.apiLink, this.blogID, this.username, this.password];
		return performancingAPICalls.wp_getPageList(argArray);
	};
	
	this.getCategoryList = function () {
		var argArray = [this.apiLink, this.blogID, this.username, this.password];
		return performancingAPICalls.mt_getCategoryList(argArray);
	};
	
	this.newCategory = function (aCategory) {
		var argArray = [this.apiLink, this.blogID, this.username, this.password, { name : aCategory} ];
		return performancingAPICalls.wp_newCategory(argArray);
	};
	
	this.setPostCategories = function (aPostid, aCategories) {
		var argArray = [this.apiLink, aPostid, this.username, this.password, aCategories];
		return performancingAPICalls.mt_setPostCategories(argArray);
	};

	this.publishPost = function (aPostid) {
		var argArray = [this.apiLink, aPostid, this.username, this.password];
		return performancingAPICalls.mt_publishPost(argArray);
	};

	this.fileUpload = function (aFileName, aMimeType, aDataString) {
		var content_t = {
			name: aFileName,
			type: aMimeType,
			bits: aDataString.toString()
		};
		
		var argArray = [this.apiLink, this.blogID, this.username, this.password, content_t];
		return performancingAPICalls.metaWeblog_newMediaObject(argArray);
	};
	
	this.supportsPages = true;
	this.supportsTags = true;
};

perFormancingMovableTypeAPI.prototype = new perFormancingBlogAPI();

var perFormancingAtomAPI = function () {
    this.newPost = function (aTitle, aDescription, aArrayOfCats, aDateCreated, aPublish) {
        var J = new perFormancingAtomAPIObject();
        J.init2(this.apiLink, this.username, this.password);
        J.newPost(aTitle, aDescription, aDateCreated, aPublish);
    };
    this.editPost = function (aPostid, aTitle, aDescription, aArrayOfCats, aDateCreated, aPublish, aEditURI, aAtomID) {
        var J = new perFormancingAtomAPIObject();
        J.init2(this.apiLink, this.username, this.password);
        J.editPost(aPostid, aTitle, aDescription, aDateCreated, aPublish, aEditURI, aAtomID);
    };
    this.deletePost = function (aPostid, aEditURI) {
        var J = new perFormancingAtomAPIObject();
        J.init2(this.apiLink, this.username, this.password);
        J.deletePost(aPostid, aEditURI);
    };
    this.getUsersBlogs = function () {
        var J = new perFormancingAtomAPIObject();
        J.init2(this.apiLink, this.username, this.password);
        J.getUsersBlogs();
    };
    this.getRecentPosts = function () {
        var J = new perFormancingAtomAPIObject();
        J.init2(this.apiLink, this.username, this.password);
        J.getRecentPosts();
    };
    this.getCategoryList = function () {
        //aListener.onResult(null);
        return false;
    };
    this.setPostCategories = function (aPostid, aCategories) {
        //aListener.onResult(null);
        return false;
    };
    
    this.publishPost = function (aPostid) {
         return false;
    };
	
	this.deletePage = function () {
		return false;
	};
}
perFormancingAtomAPI.prototype = new perFormancingBlogAPI();

//BLOGGER BETA
var perFormancingBloggerAtomAPI = function () {
    this.theObject = new perFormancingBloggerAtomAPIObject();
    this.theObject.authToken = null;
    this.theObject.isLoggedIn = null;
    
	this.staticCategories = [];

    this.newPost = function (aTitle, aDescription, aArrayOfCats, aDateCreated, aPublish) {
		// Does not support dateCreated
        this.theObject.init2(this.apiLink, this.username, this.password);
        this.theObject.newPost(aTitle, aDescription, aDateCreated, aPublish);
    };
    this.editPost = function (aPostid, aTitle, aDescription, aArrayOfCats, aDateCreated, aPublish, aEditURI, aAtomID, forODS) {
		// Does not support dateCreated
        this.theObject.init2(this.apiLink, this.username, this.password);
        this.theObject.editPost(aPostid, aTitle, aDescription, aDateCreated, aPublish, aEditURI, aAtomID, forODS);
    };
    this.deletePost = function (aPostid, aEditURI) {
        this.theObject.init2(this.apiLink, this.username, this.password);
        this.theObject.deletePost(aPostid, aEditURI);
    };
    this.getUsersBlogs = function () {
        this.theObject.init2(this.apiLink, this.username, this.password);
        this.theObject.getUsersBlogs();
    };
    this.getRecentPosts = function (aNumber, forODS, type) {
        this.theObject.init2(this.apiLink, this.username, this.password);
        this.theObject.getRecentPosts(50, forODS, type);
    };

	this.aggregateCategories = function (catArray) {
		add : for (var i = 0; i < catArray.length; i++) {
			find : for (var j = 0; j < this.staticCategories.length; j++) {
				if (this.staticCategories[j].categoryName == catArray[i]) {
					continue add;
				}
			}
			
			this.staticCategories.push({ "categoryName" : catArray[i], "categoryId" : catArray[i] });
		}
	},

    this.getCategoryList = function () {
        return this.staticCategories;
    };
    this.setPostCategories = function (aPostid, aCategories) {
        return false;
    };
    this.publishPost = function (aPostid) {
         return false;
    };
    this.doAuth = function () {
        this.theObject.init2(this.apiLink, this.username, this.password);
        this.theObject.doAuth();
    };
    this.doSetup = function () {
        this.theObject.doSetup();
    };
    
	this.deletePage = function () {
		return false;
	};
	
    this.addCategories = true;
}
perFormancingBloggerAtomAPI.prototype = new perFormancingBlogAPI();

var performancingMySpaceAPI = function () {
	this.supportsDrafts = false;
	
	this.login = function (successCallback, failureCallback, isLoggedOut) {
		var topObject = this;
		
		// Get a login page to get a challenge token
		var tokenReq = new XMLHttpRequest();
		
		tokenReq.open("GET", "http://www.myspace.com/", true);
		tokenReq.setRequestHeader("Referer", "http://www.myspace.com/");
		
		tokenReq.onreadystatechange = function () {
			if (tokenReq.readyState == 4) {
				try {
					if (tokenReq.responseText.match(/>SignOut</)) {
						throw "Logged in.";
					}
					
					var token = tokenReq.responseText.match(/VIEWSTATE" value="([^"]+)"/)[1];
				} catch (e) {
					if (!tokenReq.responseText.match(/>SignUp</)) {
						var logoutReq = new XMLHttpRequest();
						logoutReq.open("GET", "http://collect.myspace.com/index.cfm?fuseaction=signout", true);
						logoutReq.onreadystatechange = function () {
							if (logoutReq.readyState == 4) {
								topObject.login(successCallback, failureCallback, true);
							}
						};
						
						logoutReq.send(null);
					}
					else {
						// Paradox.
					}
					
					return;
				}
				
				var url = "http://secure.myspace.com/index.cfm?fuseaction=login.process";
				
				var args = {};
				args["__VIEWSTATE"] = token;
				args.NextPage = "";
				args["ctl00$Main$SplashDisplay$ctl00$Email_Textbox"] = topObject.username;
				args["ctl00$Main$SplashDisplay$ctl00$Password_Textbox"] = topObject.password;
				args["ctl00$Main$SplashDisplay$ctl00$Login_ImageButton.x"] = 12;
				args["ctl00$Main$SplashDisplay$ctl00$Login_ImageButton.y"] = 2;
				args["ctl00$Main$SplashDisplay$ctl00$nexturl"] = "";
				args["ctl00$Main$SplashDisplay$ctl00$apikey"] = "";
				args["ctl00$Main$SplashDisplay$ctl00$ContainerPage"] = "";
				
				var argstring = "";
				
				for (var i in args) {
					argstring += encodeURIComponent(i) + "=" + encodeURIComponent(args[i]) + "&";
				}
				
				argstring = argstring.substr(0, argstring.length - 1);
				
				var loginReq = new XMLHttpRequest();
				loginReq.open("POST", url, true);
				loginReq.overrideMimeType("text/html");
				loginReq.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
				loginReq.setRequestHeader("Content-Length", argstring.length);
				loginReq.setRequestHeader("Referer", "http://www.myspace.com/", true);
				
				loginReq.onreadystatechange = function () {
					if (loginReq.readyState == 4) {
						if (loginReq.responseText.match(/>SignOut</)) {
							successCallback(loginReq.responseText);
						}
						else {
							failureCallback();
						}
					}
				};
		
				loginReq.send(argstring);
			}
		};

		tokenReq.send(null);
	};
	
    this.newPost = function (aTitle, aDescription, aArrayOfCats, aDateCreated) {
		var categoryId = 0;
		
		if (aArrayOfCats.length > 0) {
			var cats = this.getCategoryList();
			
			for (var i = 0; i < cats.length; i++) {
				if (cats[i].categoryName == aArrayOfCats[0]) {
					categoryId = cats[i].value;
					break;
				}
			}
		}
		
		function callback() {
			var url = "http://blog.myspace.com/index.cfm?fuseaction=blog.create&editor=false";
			
			var req = new XMLHttpRequest();
			req.open("GET", url, true);
			req.setRequestHeader("Referer", url);
			
			req.onreadystatechange = function () {
				if (req.readyState == 4) {
					try {
						var nextUrl = req.responseText.match(/(http:\/\/blog\.myspace\.com\/index\.cfm\?fuseaction=blog\.previewBlog&Mytoken=[^']+)'/i)[1];
					} catch (e) {
						return;
					}
					
					var req2 = new XMLHttpRequest();
					req2.open("POST", nextUrl, true);
					req2.setRequestHeader("Referer", url, true);
					
					var today = new Date(aDateCreated);
					
					var args = {};
					args.blogID = "-1";
					args.postMonth = today.getMonth() + 1;
					args.postDay = today.getDate();
					args.postYear = today.getFullYear();
					args.postHour = today.getHours();
					args.postMinute = today.getMinutes();
					args.postTimeMarker = (args.postHour > 11) ? "PM" : "AM";
					
					if (args.postHour > 12) args.postHour = args.postHour - 12;
					if (args.postHour == 0) args.postHour = "12";
					
					args.subject = aTitle;
					args.BlogCategoryID = (categoryId) ? categoryId : "0";
					args.editor = "false";
					
					args.body = aDescription;
					args.CurrentlyASIN = "";
					args.CurrentlyProductName = "";
					args.CurrentlyProductBy = "";
					args.CurrentlyImageURL = "";
					args.CurrentlyProductURL = "";
					args.CurrentlyProductReleaseDate = "";
					args.CurrentlyProductType = "";
					args.MoodSetID = "7";
					args.MoodID = "0";
					args.MoodOther = "";
					args.BlogViewingPrivacyID = "0";
					args.Enclosure = "";
					
					var argstring = "";
					
					for (var i in args) {
						argstring += encodeURIComponent(i) + "=" + encodeURIComponent(args[i]).replace(/%20/g, "+") + "&";
					}
					
					argstring = argstring.substring(0, argstring.length - 1);
					
					req2.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
					req2.setRequestHeader("Content-Length", argstring.length);
					
					req2.onreadystatechange = function () {
						if (req2.readyState == 4) {
							for (var i in args) {
								var newKey = i.charAt(0).toUpperCase() + i.substring(1);
								var value = args[i];
								
								delete args[i];
								
								args[newKey] = value;
							}
							
							args.isPreviewed = "true";
							
							try {
								var hash = req2.responseText.match(/hash" value="([^"]+)"/i)[1];
							} catch (e) {
								return;
							}
							
							args.hash = hash;
							
							var argstring = "";

							for (var i in args) {
								argstring += encodeURIComponent(i) + "=" + encodeURIComponent(args[i]) + "&";
							}
							
							argstring = argstring.substring(0, argstring.length - 1);
							
							var req3 = new XMLHttpRequest();
							req3.open("POST", "http://blog.myspace.com/index.cfm?fuseaction=blog.processCreate", true);
							req3.setRequestHeader("Referer", nextUrl, true);
							req3.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
							req3.setRequestHeader("Content-Length", argstring.length);
							
							req3.onreadystatechange = function () {
								if (req3.readyState == 4) {
									// Success!
									performancing_xmlcall.processReturnData({ }, 'newpostcall', null, true, null, null);
								}
							};
							
							req3.send(argstring);
						}
					};
					
					req2.send(argstring);
				}
			};
			
			req.send(null);
		}
		
		this.login(callback, this.loginFailed );
	};
	
    this.editPost = function (aPostid, aTitle, aDescription, aArrayOfCats, aDateCreated, aPublish, aEditURI, aAtomID, forODS) {
		var categoryId = 0;
		
		if (aArrayOfCats.length > 0) {
			var cats = this.getCategoryList();
			
			for (var i = 0; i < cats.length; i++) {
				if (cats[i].categoryName == aArrayOfCats[0]) {
					categoryId = cats[i].value;
					break;
				}
			}
		}
		
		function callback() {
			var url = "http://blog.myspace.com/index.cfm?fuseaction=blog.create&editor=false&BlogID="+aPostid;
			
			var req = new XMLHttpRequest();
			req.open("GET", url, true);
			req.setRequestHeader("Referer", url);
			
			req.onreadystatechange = function () {
				if (req.readyState == 4) {
					try {
						var nextUrl = req.responseText.match(/(http:\/\/blog\.myspace\.com\/index\.cfm\?fuseaction=blog\.previewBlog&Mytoken=[^']+)'/i)[1];
					} catch (e) {
						return;
					}
					
					var req2 = new XMLHttpRequest();
					req2.open("POST", nextUrl, true);
					req2.setRequestHeader("Referer", url, true);
					
					aDateCreated = new Date();
					var today = new Date(aDateCreated);
					
					var args = {};
					args.blogID = aPostid;
					args.postMonth = today.getMonth() + 1;
					args.postDay = today.getDate();
					args.postYear = today.getFullYear();
					args.postHour = today.getHours();
					args.postMinute = today.getMinutes();
					args.postTimeMarker = (args.postHour > 11) ? "PM" : "AM";
					
					if (args.postHour > 12) args.postHour = args.postHour - 12;
					if (args.postHour == 0) args.postHour = "12";
					
					args.subject = aTitle;
					args.BlogCategoryID = (categoryId) ? categoryId : "0";
					args.editor = "false";
					
					args.body = aDescription;
					args.CurrentlyASIN = "";
					args.CurrentlyProductName = "";
					args.CurrentlyProductBy = "";
					args.CurrentlyImageURL = "";
					args.CurrentlyProductURL = "";
					args.CurrentlyProductReleaseDate = "";
					args.CurrentlyProductType = "";
					args.MoodSetID = "7";
					args.MoodID = "0";
					args.MoodOther = "";
					args.BlogViewingPrivacyID = "0";
					args.Enclosure = "";
					
					var argstring = "";
					
					for (var i in args) {
						argstring += encodeURIComponent(i) + "=" + encodeURIComponent(args[i]).replace(/%20/g, "+") + "&";
					}
					
					argstring = argstring.substring(0, argstring.length - 1);
					
					req2.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
					req2.setRequestHeader("Content-Length", argstring.length);
					
					req2.onreadystatechange = function () {
						if (req2.readyState == 4) {
							for (var i in args) {
								var newKey = i.charAt(0).toUpperCase() + i.substring(1);
								var value = args[i];
								
								delete args[i];
								
								args[newKey] = value;
							}
							
							args.isPreviewed = "true";
							
							try {
								var hash = req2.responseText.match(/hash" value="([^"]+)"/i)[1];
							} catch (e) {
								return;
							}
							
							args.hash = hash;
							
							var argstring = "";

							for (var i in args) {
								argstring += encodeURIComponent(i) + "=" + encodeURIComponent(args[i]) + "&";
							}
							
							argstring = argstring.substring(0, argstring.length - 1);
							
							var req3 = new XMLHttpRequest();
							req3.open("POST", "http://blog.myspace.com/index.cfm?fuseaction=blog.processEdit&safe=0", true);
							req3.setRequestHeader("Referer", nextUrl, true);
							req3.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
							req3.setRequestHeader("Content-Length", argstring.length);
							
							req3.onreadystatechange = function () {
								if (req3.readyState == 4) {
									// Success!
									performancing_xmlcall.processReturnData({ }, 'editpostcall', null, true, null, null);
								}
							};
							
							req3.send(argstring);
						}
					};
					
					req2.send(argstring);
				}
			};
			
			req.send(null);
		}
		
		this.login(callback, this.loginFailed);
    };

	this.deletePost = function (aPostid) {
		function callback() {
			var req = new XMLHttpRequest();
			req.open("GET", "http://blog.myspace.com/index.cfm?fuseaction=blog.confirmRemove&blogID=" + aPostid, true);
		
			req.onreadystatechange = function () {
				if (req.readyState == 4) {
					var t = req.responseText;
				
					var postUrl = t.match(/name="blogRemove" action="([^"]+)"/i)[1];
					var hash = t.match(/name="hash" value="([^"]+)"/i)[1];
				
					var postReq = new XMLHttpRequest();
					postReq.open("POST", postUrl, true);
				
					var argstring = "BlogID=" + encodeURIComponent(aPostid) + "&hash=" + encodeURIComponent(hash);
					postReq.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
					postReq.setRequestHeader("Content-Length", argstring.length);
				
					postReq.onreadystatechange = function () {
						if (postReq.readyState == 4) {
							performancing_xmlcall.processReturnData(null, 'deletehistorycall', null, true);
						}
					}
				
					postReq.send(argstring);
				}
			};
		
			req.send(null);
		}
		
		this.login(callback, this.loginFailed );
    };

    this.getUsersBlogs = function () {
		function callback(text) {
			var blogUrl = "http://blog.myspace.com/index.cfm?fuseaction=blog&friendID=";
			var userId = text.match(/var ifpc_ownerid = ([0-9]+);/i)[1];
			
			var rval = [
				{ blogName : "MySpace Blog", blogid : 1, url : blogUrl + userId }
			];

	        performancing_xmlcall.processData(rval, null, 'accountwizard', "", true);
		}
	
		this.login(callback, this.loginFailed);
    };

	this.loginFailed = function () {
		alert(performancingUI.getLocaleString("myspaceLoginFailed"));
	};

    this.getRecentPosts = function (aNumber, forODS, type) {
    };

	this.populateHistoryList = function () {
		function callback(text, callback2, doc) {
			var rv = [];
			
			var date = '';
			
			try {
				for (var i = 1; i <= 10; i++) {
					var entry = doc.getElementById("blog-" + i);
				
					if (entry) {
						var entryObject = { 'title' : "", 'description' : "", 'dateCreated' : "", 'postid' : "", 'categories' : "" };
						
						var paragraphs = entry.getElementsByTagName("p");
						
						for (var q = 0; q < paragraphs.length; q++) {
							if (paragraphs[q].getAttribute("class") == 'blogTimeStamp') {
								// If it doesn't find the date, just use the last one we did find.
								date = paragraphs[q].innerHTML.replace(/^\s+|\s+$/g, "");
							}

							if (paragraphs[q].getAttribute("class") == 'blogSubject') {
								entryObject.title = paragraphs[q].innerHTML.split("<")[0].replace(/^\s+|\s+$/g, "");
								
								// Get the category from here.
								var categoryLink = paragraphs[q].getElementsByTagName("a");
								
								if (categoryLink.length > 0) {
									categoryLink = categoryLink[0];
									entryObject.categories = categoryLink.innerHTML.replace(/^\s+|\s+$/g, "");
								}
							}

							if (paragraphs[q].getAttribute("class") == 'blogContentInfo') {
								var timeNode = paragraphs[q].getElementsByTagName("a")[0];
								
								var time = timeNode.innerHTML.replace(/<[^>]+>/g, "").replace(/^\s+|\s+$/g, "");
								var postId = timeNode.href.match(/&blogID=([0-9]+)&/)[1];
								
								entryObject.dateCreated = new Date(date + " " + time);
								
								entryObject.postid = postId;
							}
						}
						
						entryObject.description = entry.innerHTML.match(/<p class="blogContent">([\s\S]*)<p class="blogContentInfo"/im)[1].replace(/^\s+|\s+$/g, "");
						
						rv.push(entryObject);
					}
				}
			} catch (e) {
				alert(e);
			}
			
			performancing_xmlcall.processData(rv, null, 'historycall', "", true);
		}
		
		var req = new XMLHttpRequest();
		req.open("GET", gPerformancingUtil.serviceObjectXML..url.toString(), true);
		
		req.onreadystatechange = function () {
			if (req.readyState == 4) {
				var t = req.responseText;
				
				gPerformancingUtil.convertTextToHTML(t, callback);
			}
		};
		
		req.send(null);
	};

    this.getCategoryList = function () {
		var rv = [
			{ 'value' : 1, 'categoryName' : 'Art and Photography' },
			{ 'value' : 4, 'categoryName' : 'Automotive' },
			{ 'value' : 2, 'categoryName' : 'Blogging' },
			{ 'value' : 6, 'categoryName' : 'Dreams and the Supernatural' },
			{ 'value' : 3, 'categoryName' : 'Fashion, Style, Shopping' },
			{ 'value' : 7, 'categoryName' : 'Food and Restaurants' },
			{ 'value' : 8, 'categoryName' : 'Friends' },
			{ 'value' : 9, 'categoryName' : 'Games' },
			{ 'value' : 10, 'categoryName' : 'Goals, Plans, Hopes' },
			{ 'value' : 11, 'categoryName' : 'Jobs, Work, Careers' },
			{ 'value' : 12, 'categoryName' : 'Life' },
			{ 'value' : 14, 'categoryName' : 'Movies, TV, Celebrities' },
			{ 'value' : 15, 'categoryName' : 'Music' },
			{ 'value' : 16, 'categoryName' : 'MySpace' },
			{ 'value' : 17, 'categoryName' : 'News and Politics' },
			{ 'value' : 18, 'categoryName' : 'Parties and Nightlife' },
			{ 'value' : 19, 'categoryName' : 'Pets and Animals' },
			{ 'value' : 26, 'categoryName' : 'Podcast' },
			{ 'value' : 20, 'categoryName' : 'Quiz/Survey' },
			{ 'value' : 21, 'categoryName' : 'Religion and Philosophy' },
			{ 'value' : 13, 'categoryName' : 'Romance and Relationships' },
			{ 'value' : 22, 'categoryName' : 'School, College, Greek' },
			{ 'value' : 23, 'categoryName' : 'Sports' },
			{ 'value' : 24, 'categoryName' : 'Travel and Places' },
			{ 'value' : 5, 'categoryName' : 'Web, HTML, Tech' },
			{ 'value' : 25, 'categoryName' : 'Writing and Poetry' }
		];
		
		return rv;
    };

	this.populateCategoryChecklist = function () {
		var categories = this.getCategoryList();
		
		performancing_xmlcall.processReturnData(categories, 'categorycall');
	};
    this.publishPost = function (aPostid) {
         return false;
    };
    this.doAuth = function () {
        //var J = new perFormancingBloggerAtomAPIObject();
        this.theObject.init2(this.apiLink, this.username, this.password);
        this.theObject.doAuth();
    };
    this.doSetup = function () {
    };
    
	this.deletePage = function () {
		return false;
	};
	
    this.addCategories = false;
	this.standard = false;
}
performancingMySpaceAPI.prototype = new perFormancingBlogAPI();

var performancingTumblrAPI = function () {
	this.supportsDrafts = false;
	
	this.login = function (successCallback, failureCallback) {
		var url = "http://www.tumblr.com/api/write";
		
		var args = {};
		args.action = 'authenticate';
		args.email = this.username;
		args.password = this.password;
		
		var argstring = "";
		
		for (var i in args) {
			argstring += encodeURIComponent(i) + "=" + encodeURIComponent(args[i]) + "&";
		}
		
		argstring = argstring.substr(0, argstring.length - 1);
		
		var req = new XMLHttpRequest();
		req.open("POST", url, true);
		req.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
		req.setRequestHeader("Content-Length", argstring.length);
		
		req.onreadystatechange = function () {
			try {
				if (req.readyState == 4) {
					if (req.status == 200) {
						successCallback(req.responseText);
					}
					else {
						failureCallback();
					}
				}
			} catch (e) {
				alert(e);
				failureCallback();
			}
		};
		
		req.send(argstring);
	};
	
    this.newPost = function (aTitle, aDescription, aArrayOfCats, aDateCreated, notUsed, aTags) {
		var args = {};
		args.email = this.username;
		args.password = this.password;
		args.generator = "ScribeFire";
		
		var theDate = new Date(aDateCreated);
		var now = new Date();
		
		if (theDate > now) {
			aDateCreated = now;
		}
		else {
			aDateCreated = theDate;
		}
		
		args.date = aDateCreated.toString();
		args.tags = aTags;
		args.type = 'regular';
		args.format = 'html';
		args.title = aTitle;
		args.body = aDescription;

		var argstring = "";
		
		for (var i in args) {
			argstring += encodeURIComponent(i) + "=" + encodeURIComponent(args[i]) + "&";
		}
		
		argstring = argstring.substr(0, argstring.length - 1);
		
		var req = new XMLHttpRequest();
		req.open("POST", "http://www.tumblr.com/api/write", true);
		req.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
		req.setRequestHeader("Content-Length", argstring.length);

		req.onreadystatechange = function (event) {
			if (req.readyState == 4) {
				if (req.status == 201) {
					// No problem.
					performancing_xmlcall.processReturnData({ }, 'newpostcall', null, true, null, null);
				}
				else {
					// TODO posting error
					alert(req.responseText);
				}
			}
		};
		
		req.send(argstring);
	};
	
    this.editPost = function (aPostid, aTitle, aDescription, aArrayOfCats, aDateCreated, aPublish, aTags, aAtomID, forODS) {
		function callback() {
			var url = "http://www.tumblr.com/edit/" + aPostid;

			var req1 = new XMLHttpRequest();
			req1.open("GET", url, true);

			req1.onreadystatechange = function () {
				if (req1.readyState == 4) {
					var formKey = req1.responseText.match(/name="form_key" value="([^"]+)"/i)[1];
					
					var theDate = new Date(aDateCreated);
					var now = new Date();

					if (theDate > now) {
						aDateCreated = now;
					}
					else {
						aDateCreated = theDate;
					}
					
					var args = {};
					args["is_rich_text[one]"] = 0;
					args["is_rich_text[two]"] = 0;
					args["is_rich_text[three]"] = 0;
					args["post[one]"] = aTitle;
					args["post[two]"] = aDescription;
					args["post[is_private]"] = 0;
					args["post[date]"] = aDateCreated.toString();
					args["post[tags]"] = aTags;
					args["post[type]"] = "regular";
					args["post[id]"] = aPostid;
					args.form_key = formKey;
					
					var argstring = "";

					for (var i in args) {
						argstring += i + "=" + encodeURIComponent(args[i]) + "&";
					}

					argstring = argstring.substr(0, argstring.length - 1);
					
					var req2 = new XMLHttpRequest();
					req2.open("POST", url, true);
					req2.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
					req2.setRequestHeader("Content-Length", argstring.length);

					req2.onreadystatechange = function () {
						if (req2.readyState == 4) {
							performancing_xmlcall.processReturnData({ }, 'editpostcall', null, true, null, null);
						}
					};
					
					req2.send(argstring);
				}
			};
			
			req1.send(null);
		}
		
		this.webLogin(callback, this.loginFailed);
    };

	this.webLogin = function (callback) {
		var args = {};
		args.email = this.username;
		args.password = this.password;
		
		var argstring = "";
		
		for (var i in args) {
			argstring += encodeURIComponent(i) + "=" + encodeURIComponent(args[i]) + "&";
		}
		
		argstring = argstring.substr(0, argstring.length - 1);
		
		var req = new XMLHttpRequest();
		req.open("POST", "http://www.tumblr.com/login", true);
		req.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
		req.setRequestHeader("Content-Length", argstring.length);

		req.onreadystatechange = function (event) {
			if (req.readyState == 4) {
				callback();
			}
		};
		
		req.send(argstring);
		
	};

	this.deletePost = function (aPostid) {
		function callback() {
			var args = {};
			args.id = aPostid;
		
			var argstring = "";
		
			for (var i in args) {
				argstring += encodeURIComponent(i) + "=" + encodeURIComponent(args[i]) + "&";
			}
		
			argstring = argstring.substr(0, argstring.length - 1);
		
			var req = new XMLHttpRequest();
			req.open("POST", "http://www.tumblr.com/delete", true);
			req.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
			req.setRequestHeader("Content-Length", argstring.length);

			req.onreadystatechange = function (event) {
				if (req.readyState == 4) {
					performancing_xmlcall.processReturnData(null, 'deletehistorycall', null, true);
				}
			};
		
			req.send(argstring);
		}
		
		this.webLogin(callback, this.loginFailed);
    };

    this.getUsersBlogs = function (blogUrl) {
		function callback(blogUrl) {
			var rval = [
				{ blogName : "Tumblr Blog", blogid : 1, url : blogUrl }
			];

	        performancing_xmlcall.processData(rval, null, 'accountwizard', "", true);
		}
	
		this.login(callback, this.loginFailed);
    };

	this.loginFailed = function () {
		alert(performancingUI.getLocaleString("tumblrLoginFailed"));
	};

	this.populateHistoryList = function () {
		var url = gPerformancingUtil.serviceObjectXML..url + "api/read/json?start=0&num=50&type=regular";
		
		var req = new XMLHttpRequest();
		req.open("GET", url, true);
		
		req.onreadystatechange = function () {
			if (req.readyState == 4) {
				eval(req.responseText);
				
				var json = tumblr_api_read;
				
				var rv = [];
				
				for (var i = 0; i < json.posts.length; i++) {
					var entryObject = { 'title' : json.posts[i]["regular-title"], 'description' : json.posts[i]["regular-body"], 'dateCreated' : json.posts[i]["date-gmt"], 'postid' : json.posts[i].id, 'tags' : "", 'permaLink': json.posts[i].url };
					
					try {
						var tags = json.posts[i]["tags"].join(", ");
						entryObject.tags = tags;
					} catch (noTags) { }
					
					rv.push(entryObject);
				}
				
				performancing_xmlcall.processData(rv, null, 'historycall', "", true);
			}
		};
		
		req.send(null);
	};

	this.populateCategoryChecklist = function () {
		var categories = [];
		
		performancing_xmlcall.processReturnData(categories, 'categorycall');
	};
    
    this.addCategories = false;
	this.standard = false;
	this.supportsTags = true;
}
performancingTumblrAPI.prototype = new perFormancingBlogAPI();

var performancingAPICalls = new Object();

performancingAPICalls = {
    //myParams  = [url, appkey, blogid, username, password, content, publish]
    blogger_newPost: function(myParams) {
      return bfXMLRPC.makeXML("blogger.newPost", myParams);
    },
    
    //myParams  = [url, appkey, postid, username, password, content, publish]
    blogger_editPost: function(myParams) {
      return bfXMLRPC.makeXML("blogger.editPost", myParams);
    },
    
    //myParams  = [url, appkey, postid, username, password, publish]
    blogger_deletePost: function(myParams) {
      return bfXMLRPC.makeXML("blogger.deletePost", myParams);
    },
    
    //myParams  = [url, appkey, blogid, username, password, numberOfPosts]
    blogger_getRecentPosts: function(myParams) {
      return bfXMLRPC.makeXML("blogger.getRecentPosts", myParams);
    },
    
    //myParams  = [url, appkey, username, password]
    blogger_getUsersBlogs: function(myParams) {
      return bfXMLRPC.makeXML("blogger.getUsersBlogs", myParams);
    },
    
    //myParams  = [url, appkey, username, password]
    blogger_getUserInfo: function(myParams) {
      return bfXMLRPC.makeXML("blogger.getUserInfo", myParams);
    },
    
    //myParams  = [url, blogid, username, password, content_t, publish]
    metaWeblog_newPost: function(myParams) {
		return bfXMLRPC.makeXML("metaWeblog.newPost", myParams);
    },
    
    metaWeblog_editPost: function(myParams) {
      return bfXMLRPC.makeXML("metaWeblog.editPost", myParams);
    },
    
    //myParams  = [url, blogid, username, password, numberOfPosts]
    metaWeblog_getRecentPosts: function(myParams) {
      return bfXMLRPC.makeXML("metaWeblog.getRecentPosts", myParams);
    },
    
    //myParams  = [url, blogid, username, password]
    metaWeblog_getCategoryList: function(myParams) {
      return bfXMLRPC.makeXML("metaWeblog.getCategories", myParams);
    },
    
    //myParams  = [url, blogid, username, password, mediaStruct]
    metaWeblog_newMediaObject: function(myParams) {
      return bfXMLRPC.makeXML("metaWeblog.newMediaObject", myParams);
    },
    
    //myParams  = [url, blogid, username, password, numberOfPosts]
    mt_getRecentPostTitles: function(myParams) {
      return bfXMLRPC.makeXML("mt.getRecentPostTitles", myParams);
    },
    
    //myParams  = [url, blogid, username, password]
    mt_getCategoryList: function(myParams) {
      return bfXMLRPC.makeXML("mt.getCategoryList", myParams);
    },
    
    //myParams  = [url, postid, username, password, categories]
    mt_setPostCategories: function(myParams) {
      return bfXMLRPC.makeXML("mt.setPostCategories", myParams);
    },
    //mt_publishPost
    //myParams  = [url, postid, username, password]
    mt_publishPost: function(myParams) {
      return bfXMLRPC.makeXML("mt.publishPost", myParams);
    },
	
	wp_getPage : function (myParams) {
		return bfXMLRPC.makeXML("wp.getPage", myParams);
	},
	wp_getPages : function (myParams) {
		//	    $blog_id    = $args[0];
		//      $username    = $args[1];
		//      $password    = $args[2];
		return bfXMLRPC.makeXML("wp.getPages", myParams);
	},
	wp_newPage : function (myParams) {
		return bfXMLRPC.makeXML("wp.newPage", myParams);
	},
	wp_deletePage : function (myParams) {
		return bfXMLRPC.makeXML("wp.deletePage", myParams);
	},
	wp_editPage : function (myParams) {
		return bfXMLRPC.makeXML("wp.editPage", myParams);
	},
	wp_getPageList : function (myParams) {
		return bfXMLRPC.makeXML("wp.getPageList", myParams);
	},
	wp_getAuthors : function (myParams) {
		return bfXMLRPC.makeXML("wp.getAuthors", myParams);
	},
	wp_newCategory : function (myParams) {
		return bfXMLRPC.makeXML("wp.newCategory", myParams);
	},
	wp_suggestCategories : function (myParams) {
		return bfXMLRPC.makeXML("wp.suggestCategories", myParams);
	}
}

function perFormancingAtomAPIObject() {
}

perFormancingAtomAPIObject.prototype = {
    _req: null,
    _url: null,

    ERROR_HTTP:   10,
    ERROR_FAULT:   11,
    ERROR_PARSER:   12,

    init2: function(aUrl, aUsername, aPassword) {
        this._url = aUrl;
        this._user = aUsername;
        this._pass = aPassword;
    },

    doRequest: function( method, url, body, processor) {
		alert(performancingUI.getLocaleString("reAddBlogger"));
    },

    getRecentPosts: function() {
        //var url = this._url; 
        //url.match(/(.+\/)(.+)/);
        //if(RegExp.$2=="post") {
        //    url = RegExp.$1 + "feed";
        //}
        this.doRequest("GET", this._url,null, this.parseRecentPosts);
        return true;
    },
    getUsersBlogs: function() {
        this.doRequest("GET", this._url, null, this.parseUsersBlogs);
    },

    parseUsersBlogs: function( inst) {
        try {
            var rval = new Array();
            var dom = inst._req.responseXML;
            var links = dom.getElementsByTagName("link");
            for(var i=0;i<links.length;++i)
            {
                var link = links[i];
                var title = link.getAttribute("title");
                var rel = link.getAttribute("rel");
                var href = link.getAttribute("href");
                if(rel!="service.post") continue;

                href.match(/.+\/(.+)/);
                var bid = RegExp.$1;

                var obj  =
                {
                    blogName: title,
                    blogid:  bid,
                    url:  href
                };
                rval[rval.length++] = obj;
            }
            //listener.onResult(rval);
            performancing_xmlcall.processData(rval, null, 'accountwizard', "", true);
        }
        catch(e) {
        }
    },

    parseRecentPosts: function( inst) {
        //dump("\n\n parseRecentPosts ATOM \n\n");
        var rval = new Array();
        var dom = inst._req.responseXML;
        var entries = dom.getElementsByTagName("entry");
        for(var i=0;i<entries.length;++i)
        {
            try
            {
                var entry_n = entries[i];
                var content_n = inst.getNamedChild(entry_n, "content");
                var title_n = inst.getNamedChild(entry_n, "title");
                var created_n = inst.getNamedChild(entry_n, "issued");
                var author_n = inst.getNamedChild(entry_n, "author");
                var link_n = null;
                var atomid_n = inst.getNamedChild(entry_n, "id");
                var atomid = "";
                if(atomid_n) atomid = atomid_n.firstChild.nodeValue;

                for(var j=0;j<entry_n.childNodes.length;++j) {
                    if(entry_n.childNodes[j].nodeName=="link") {
                        var tmp = entry_n.childNodes[j];
                        if(tmp.getAttribute("rel").match(/edit/)) {
                            link_n = tmp;
                        }
                    }
                }

                var href = link_n.getAttribute("href");
                href.match(/.+\/(.+)/);
                var postid = RegExp.$1;

                var dateval = created_n.firstChild.nodeValue;
                //var date = flock_parseDate(dateval);
                var val = dateval;
                var dateutc =  Date.UTC(val.slice(0, 4), val.slice(4, 6) - 1, 
                        val.slice(6, 8), val.slice(9, 11), val.slice(12, 14), 
                        val.slice(15));
                var date =  new Date(dateutc);

                var xs = new XMLSerializer();

                var data = "";
                if(content_n) {
                    for(var j=0;j<content_n.childNodes.length;++j) {
                        data += xs.serializeToString(content_n.childNodes.item(j));
                    }
                }
                data = data.replace(/&lt;/g,"<");
                data = data.replace(/&gt;/g,">");
                data = data.replace(/&quot;/g,"\"");
                data = data.replace(/&amp;/g,"&");

                var obj  =
                {
                    description: data,
                    title: title_n.firstChild.nodeValue,
                    dateCreated: date,
                    postid:  postid,
                    editURI:  href,
                    atomid:  atomid
                };
                rval[rval.length] = obj;
            }
            catch(e)
            {
            }
        }
        //listener.onResult(rval);
        //dump("\n\n parseRecentPosts ATOM Finished \n\n");
        performancing_xmlcall.processData(rval, null, 'historycall', "", true);
    },
    getNamedChild: function(node, name) {
        for(var i=0;i<node.childNodes.length;++i) {
            if(node.childNodes[i].nodeName==name) return node.childNodes[i];
        }
        return null;
    },
    deletePost: function ( postid, aEditURI) {
        var url = this._url;
        if(postid) url += "/" + postid;
        if(aEditURI) url = aEditURI;
        this.doRequest("DELETE", url,null, this.handleDelete);
    },
    doPost: function ( method, postid, title, description, date_created, doPublish, aEditURI, aAtomID, isEdit) {

        var url = this._url;
        if(postid) url += "/" + postid;

        //if(aEditURI) url += "/" + aEditURI;

        //var date = bfXMLRPC.iso8601Format(date_created);
        var date = "";
        try{
            date = bfXMLRPC.iso8601Format(date_created);
        }catch(e){
            //foo
        }

        var body = "";
        var version = "ScribeFire 2.1";
        var theBlogCharType = gPerformancingUtil.getCharType();
        body += '<?xml version="1.0" encoding="UTF-8" ?>';
        body += '<entry xmlns="http://purl.org/atom/ns#">';

        var draft = "false";
        if(doPublish == false || doPublish == 'bool0') draft = "true";
        
		var useEntities = true;
            var entity_description = "";
            for (var desc_i=0; desc_i < description.length; desc_i++){
                entity_description += "&#" + description.charCodeAt(desc_i) + ";";
            }
        
            var entity_title = "";
            for (var title_i=0; title_i < title.length; title_i++){
                entity_title += "&#" + title.charCodeAt(title_i) + ";";
            }
            
            description = entity_description;
            title = entity_title;
            body += '  <title type="text/plain" mode="escaped">' + title + '</title>';
            body += '  <issued>' + date + '</issued>';
            body += '  <generator url="http://performancing.com/firefox">' + version + '</generator>';
            body += '  <content type="text/plain" mode="escaped">' + description + '</content>';
            body += '  <draft xmlns="http://purl.org/atom-blog/ns#">' + draft + '</draft> ';
            body += '</entry>';
        
        dump("\n\n********** \nDescription: " + description +"\n\n********** \title: "+ title);
        //dump(body);
        this.doRequest(method,url,body,this.parsePosts, doPublish);
    },
    editPost: function ( postid, title, description, date_created, isDraft, aEditURI, aAtomID) {
        this.doPost( "PUT", postid, title, description, date_created, isDraft, aEditURI, aAtomID, "isEdit");
    },
    newPost: function ( title, description, date_created, isDraft) {
        this.doPost( "POST", null, title, description, date_created, isDraft);
    },
    parsePosts: function( inst) {
        //dump("\n\n NewPost response: " + inst +"\n\n");
        var dom = inst._req.responseXML;
        if(!dom)
        {
            // LiveJournal - everone wants to be different, don't they?
            if(inst._req.responseText.match(/OK/)) {
                //listener.onResult(1);
                performancing_xmlcall.processData(1, null, null, "", true);
                return;
            }
            else {
				alert(performancingUI.getLocaleString("reAddBlogger"));
                return;
            }
        }
        var entries = dom.getElementsByTagName("entry");
        var rval = new Object();
        try
        {
            var entry_n = entries[0];
            var link_n = null;
            var perm_link_n = null;
            var atomid_n = inst.getNamedChild(entry_n, "id");
            var atomid = "";
            if(atomid_n) atomid = atomid_n.firstChild.nodeValue;
            for(var j=0;j<entry_n.childNodes.length;++j) {
                if(entry_n.childNodes[j].nodeName=="link") {
                    var tmp = entry_n.childNodes[j];
                    if(tmp.getAttribute("rel").match(/edit/)) {
                        link_n = tmp;
                    }
                    else if(tmp.getAttribute("rel").match(/alternate/)) {
                        perm_link_n = tmp;
                    }
                }
            }
            var href = link_n.getAttribute("href");
            rval.editURI = href;
            rval.atomid = atomid;
            href.match(/.+\/(.+)/);
            rval.uid = RegExp.$1;;
            //Livejournal hackage
            if(rval.editURI.length>0 && rval.atomid.length==0) {
                var perm_link = perm_link_n.getAttribute("href");
                if(perm_link.match(/livejournal/)) {
                    perm_link.match(/.+livejournal.com\/users\/(.+?)\/(.+?)\./);
                    rval.atomid = "urn:lj:livejournal.com:atom1:" + RegExp.$1 + ":" + RegExp.$2;
                }
            }
        }
        catch(e)
        {
            var localeString = performancingUI.getLocaleString('proccessingposterror', []);
            alert(localeString);
        }
        performancing_xmlcall.processData(rval, null, 'newpostcall', "", true );
        //performancing_xmlcall.processData(rval, 'historycall', null, true);
    },
    
    handleDelete: function( inst) {
        //listener.onResult(1);
        performancing_xmlcall.processData(1, null, 'deletehistorycall', "", true);
    }
}

/*
    Blogger Beta
    -------------------
    GET "http://beta.blogger.com/feeds/214142430004041626/posts/full"
    
    //URL
    theLinks = theGood.getElementsByTagName("link")
    for(i in theLinks){
        if(theLinks[i].getAttribute("rel") == "alternate"){
                 alert(theLinks[i].getAttribute("href") ); 
                 break;
        }
    }
    
    //Title
    theTitles = theGood.getElementsByTagName("title");
    theTitles[0].firstChild.nodeValue;
    
    //ID
    theIDs = theGood.getElementsByTagName("id");
    theIDs[0].firstChild.nodeValue;
*/
function perFormancingBloggerAtomAPIObject() {
}
var pffGoogleAuth = "";
var pffGoogleAuthIsLoggedin = false;

perFormancingBloggerAtomAPIObject.prototype= {
    titleRegExp: /(?:\<title\stype\=\'\w*\'\>)([\s\S\s]*)(?=\<\/title\>)/,
    getFullIDRegExp: /(?:\<id\>)(\S*)(?=\<\/id\>)/,
    urlRegExp: /(?:\<link\srel\=\'\w*\'\stype\=\'[\w\W]*\'\shref\=\')([\s\S\s]*)(?=\<\/link>)/,
    
    idRegexp: /(?:[\S]*feeds\/)([\d]*)(?=\/posts)/,
    postIDRegexp: /(?:[\S]*posts\/full\/)([\d]*)(?=\")/,
    
    _req: null,
    _url: null,

    ERROR_HTTP:   10,
    ERROR_FAULT:   11,
    ERROR_PARSER:   12,
    
    init2: function( aUrl, aUsername, aPassword) {
        this._url = aUrl;
        this._user = aUsername;
        this._pass = aPassword;
    },
    
    doSetup: function( aUrl, aUsername, aPassword) {
        pffGoogleAuth = "";
        pffGoogleAuthIsLoggedin = false;
    },
    
	doBlockingAuth : function () {
		var theUA = "scribefire-2.1";
		var theMsg = "Email="+this._user+"&Passwd="+encodeURIComponent(this._pass)+"&service=blogger&source="+theUA;
		var theGood = null; 
		var theObject = this;

		var req = new XMLHttpRequest();
		req.open("POST", "https://www.google.com/accounts/ClientLogin", false);
		req.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
		req.setRequestHeader("Content-Length", theMsg.length);

		req.send(theMsg);

		if (req.status == 200) {
			theGood = req.responseText;
			theAuth = theGood.match(/(?:Auth\=)(.*)/);
			pffGoogleAuth = theAuth[1];
			pffGoogleAuthIsLoggedin = true;
		}
		else {
			try {
				var errorType = req.responseText.split('=')[1].replace(/\s*$/,""); 
				var errorMessage = '';

				switch (errorType) {
					case 'BadAuthentication':
						errorMessage = performancingUI.getLocaleString('errors.blogger.badauthentication');
					break;
					case 'NotVerified':
						errorMessage = performancingUI.getLocaleString('errors.blogger.notverified');
					break;
					case 'TermsNotAgreed':
						errorMessage = performancingUI.getLocaleString('errors.blogger.termsnotagreed');
					break;
					case 'AccountDeleted':
						errorMessage = performancingUI.getLocaleString('errors.blogger.accountdeleted');
					break;
					case 'ServiceDisabled':
						errorMessage = performancingUI.getLocaleString('errors.blogger.servicedisabled');
					break;
					case 'ServiceUnavailable':
						errorMessage = performancingUI.getLocaleString('errors.blogger.serviceunavailable');
					break;
					case 'Unknown':
					default:
						errorMessage = performancingUI.getLocaleString('errors.blogger.unknown');
					break;
				}

				alert(errorMessage);
			
			} catch (e) {
				alert(performancingUI.getLocaleString("upload.error.googleError", [ theCall.request.responseText ]));
			}
		}
	},

    doAuth: function(processor, forODS, type) {
        if(!pffGoogleAuthIsLoggedin){
            var theUA = "scribefire-2.1";
            var theMsg = "Email="+this._user+"&Passwd="+encodeURIComponent(this._pass)+"&service=blogger&source="+theUA;
            var theCall = new PffXmlHttpReq("https://www.google.com/accounts/ClientLogin", "POST", theMsg, false, null, null);
            var theGood = null; 
            var theProcessor = processor;
            var theObject = this;

            theCall.onResult = function( aText, aXML ){ 
                theGood = aText;
                theAuth = theGood.match(/(?:Auth\=)(.*)/);
                pffGoogleAuth = theAuth[1];
                pffGoogleAuthIsLoggedin = true;
                theObject.doRequest("GET", theObject._url, null, theProcessor, forODS, type);
            } 

            theCall.onError = function (aStatusMsg, Msg) {
				try {
					var errorType = theCall.request.responseText.split('=')[1].replace(/\s*$/,""); 
				
					var errorMessage = '';
				
					switch (errorType) {
						case 'BadAuthentication':
							errorMessage = performancingUI.getLocaleString('errors.blogger.badauthentication');
							break;
						case 'NotVerified':
							errorMessage = performancingUI.getLocaleString('errors.blogger.notverified');
							break;
						case 'TermsNotAgreed':
							errorMessage = performancingUI.getLocaleString('errors.blogger.termsnotagreed');
							break;
						case 'AccountDeleted':
							errorMessage = performancingUI.getLocaleString('errors.blogger.accountdeleted');
							break;
						case 'ServiceDisabled':
							errorMessage = performancingUI.getLocaleString('errors.blogger.servicedisabled');
							break;
						case 'ServiceUnavailable':
							errorMessage = performancingUI.getLocaleString('errors.blogger.serviceunavailable');
							break;
						case 'Unknown':
						default:
							errorMessage = performancingUI.getLocaleString('errors.blogger.unknown', []);
							break;
					}
				
	                alert(errorMessage);
				} catch (e) {
					alert(performancingUI.getLocaleString("upload.error.googleError", [ theCall.request.responseText ]));
				}

				if (scribefireAccountWizard) {
					goTo('login');
				}
            }

            theCall.prepCall();

            theCall.request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
            theCall.makeCall();
        }else{
            this.doRequest("GET", this._url, null, processor, forODS, type);
        }
    },

    doRequest: function(method, url, body, processor, forODS, type) {
        var inst = this;
        gPFFLastURIPost = url;
        this._req = new XMLHttpRequest();
        this._req.onreadystatechange = function (aEvt) {
            if(inst._req.readyState == 4) {
                if(inst._req.status == 200 || inst._req.status == 201 || inst._req.status == 204)
                {
                    try
                    {
                        processor(inst, forODS, type);
                    }
                    catch(e)
                    {
                        var localeString = performancingUI.getLocaleString('atomservererror', []);
                        var localeString2 = performancingUI.getLocaleString('atomerrormessage', [e]);
                        alert(localeString + " #101\n" + localeString2 + "\n" + e + "\nServer Response:" + inst._req.responseText);
                    }
                }
                else {
					alert(performancingUI.getLocaleString("bloggerFailed", [ inst._req.responseText ]));
                }
            }
        };

        var rval = this._req.open(method, url, true, this._user, this._pass);
        rval = this._req.setRequestHeader("Authorization", "GoogleLogin auth=" +pffGoogleAuth );
        rval = this._req.setRequestHeader("User-Agent", "Mozilla/5.0 (compatible; ScribeFire; http://www.scribefire.com/)");
        rval = this._req.setRequestHeader("Content-Type", "application/atom+xml");
        rval = this._req.send(body); 
    },

    getRecentPosts: function(numPosts, forODS, type) {
        this.doAuth(this.parseRecentPosts, forODS, type);
    },

    getUsersBlogs: function() {
        this.doAuth(this.parseUsersBlogs);
    },

    parseUsersBlogs: function( inst) {
        try {
            var rval = new Array();
            var dom = inst._req.responseXML;
            //gPFFDebugTemp.push(dom);
            //gPFFDebugTemp.push(inst._req.responseText);
            var url = "";
            var id = "";
            var title = "";
            //URL
            var theLinks = dom.getElementsByTagName("link")
            for(i in theLinks){
                try{
                    if(theLinks[i].getAttribute("rel") == "alternate"){
                             url = (theLinks[i].getAttribute("href") ); 
                             break;
                    }
                }catch(e){}
            }
            
            //Title
            var theTitles = dom.getElementsByTagName("title");
            title = theTitles[0].firstChild.nodeValue;
            
            //ID
            var theIDs = dom.getElementsByTagName("id");
            try{
                id = theIDs[0].firstChild.nodeValue.match(/(?:[\S]*feeds\/)([\d]*)(?=\/posts)/)[1];
            }catch(e){
                id = "";
            }
            var obj  =
                {
                    blogName: title,
                    blogid:  id,
                    url:  url
                };
                rval[rval.length++] = obj;
            //listener.onResult(rval);
            performancing_xmlcall.processData(rval, null, 'accountwizard', "", true);
        }
        catch(e) {
			alert(performancingUI.getLocaleString("bloggerProgrammingError", [ e, e.lineNumber ]));
        }
    },
    
    parseRecentPosts: function(inst, forODS, type) {
        var rval = new Array();

        //gPFFDebugTemp.push(inst._req.responseText);
        
        var re = /(\<\?xml[0-9A-Za-z\D]*\?\>)/;
        var newstr = inst._req.responseText.replace(re, "");
        
        var re = /(\<feed[0-9A-Za-z\D]*["']>)(?=\<id\>)/;
        newstr = newstr.replace(re, "<feed>");
        
        var re = /(\<openSearch:[0-9A-Za-z]*\>[\d]+\<\/openSearch:[0-9A-Za-z]*\>)/ig;
        newstr = newstr.replace(re, "");

        var re = /(\<feedburner:[0-9A-Za-z]*\>.*\<\/feedburner:[0-9A-Za-z]*\>)/ig;
        newstr = newstr.replace(re, "");
        
		try {
        	var theXML = new XML(newstr);
		} catch (invalidXML) {
			throw("The XML returned by the server is invalid.");
		}
		
        for(var i=0; i<theXML.entry.length(); i++){
            try{
                var catArray = [];
                var theContent = theXML.entry[i].content.toString();
                
                theContent = theContent.replace("<content type=\"xhtml\">\n  ", ""); //Stupid blogger hack
                theContent = theContent.replace("\n</content>", ""); //Stupid blogger hack
                
                var divRegexp = /\<div xmlns\=\'http:\/\/www.w3.org\/1999\/xhtml\'\>|\<div xmlns\=\"http:\/\/www.w3.org\/1999\/xhtml\"\>/;
                var divIndex = theContent.search(divRegexp);
                
                if( divIndex >= 0 && divIndex < 30 ){ //If we have a <div xmlns='http://www.w3.org/1999/xhtml'> at the top
                    theContent = theContent.substring(42, theContent.length - 6); //Get rid of the outer div
                }

                var theTitle = theXML.entry[i].title;
                var theDate = theXML.entry[i].published;
                var thePostURL = theXML.entry[i].id;
                var theHREF =  theXML.entry[i].link.(@rel == 'alternate').@href;
                var theEditHREF =  theXML.entry[i].link.(@rel == 'edit').@href;
                var theCatsObj = theXML.entry[i].category.@term;
                
                var atomid = thePostURL.match( /(?:\/|post-)(\d{5,})(?!\d*\/)/ )[1];
                
                for(var j=0; j < theCatsObj.length(); j++){
                    catArray.push( theCatsObj[j].toString() );
                }
                
                var val = theDate;
                //Date.UTC(year, month[, date[, hrs[, min[, sec[, ms]]]]])
                var dateutc =  Date.UTC( val.slice(0, 4), val.slice(5, 7) - 1, val.slice(8, 10), val.slice(11, 13), val.slice(14, 16) );
                var date =  new Date(dateutc);
                
                var obj  =
                {
                    description: theContent,
                    title: theTitle,
                    dateCreated: date,
                    postid:  atomid,
                    editURI:  theEditHREF,
                    atomid:  thePostURL,
                    permaLink: theHREF,
                    categories: catArray
                };

				gPerformancingUtil.serviceObject.aggregateCategories(catArray);

                rval[rval.length] = obj;
            } catch(e){
            }
        }
		
		if (!forODS) {
        	performancing_xmlcall.processData(rval, null, 'historycall', "", true);
			gPerformancingUtil.getCategoryList();
		}
		else {
			SF_QUICKBLOG.processRecentPosts(rval, true, type);
		}
    },

    parseRecentPosts_dom: function( inst) {
        //dump("\n\n parseRecentPosts ATOM \n\n");
        //gPFFDebugTemp.push(inst._req.responseText);
        var rval = new Array();
        var dom = inst._req.responseXML;
        var entries = dom.getElementsByTagName("entry");
        for(var i=0;i<entries.length;++i)
        {
            try
            {
                var entry_n = entries[i];
                var content_n = inst.getNamedChild(entry_n, "content");
                var title_n = inst.getNamedChild(entry_n, "title");
                var date_n = inst.getNamedChild(entry_n, "updated");
                //var author_n = inst.getNamedChild(entry_n, "author");
                var posturl_n = inst.getNamedChild(entry_n, "id");
                var atomid = "";
                var link_n = "";
                var postlink = "";
                
                var content = content_n.firstChild.nodeValue;
                var title = title_n.firstChild.nodeValue;
                var date = date_n.firstChild.nodeValue;
                var posturl = posturl_n.firstChild.nodeValue;
                //atomid = posturl_n.match(postIDRegexp)[1];
                if(content == null){
                    try{
                        content = content_n.firstChild.firstChild.nodeValue;
                    }catch(e){
                        
                    }
                }
                
                if(content == null){
                    content = "";
                }
                var theCats = [];//Define the categories (labels)
                //if(atomid_n) atomid = atomid_n.firstChild.nodeValue;
                for(var j=0;j<entry_n.childNodes.length;++j) {
                    if(entry_n.childNodes[j].nodeName=="link") {
                        var tmp = entry_n.childNodes[j];
                        if(tmp.getAttribute("rel").match(/edit/)) {
                            link_n = tmp;
                        }
                        if(tmp.getAttribute("rel").match(/alternate/)) {
                            postlink = tmp;
                        }
                    }else if(entry_n.childNodes[j].nodeName=="category") {
                        var tmp = entry_n.childNodes[j];
                        var term = tmp.getAttribute("term");
                        theCats.push(term);
                    }
                }
                
                var href = link_n.getAttribute("href");
                atomid = href.match(/.+\/(.+)/)[1];
                
                var thePostlink = postlink.getAttribute("href");
                
                var val = date;
                var dateutc =  Date.UTC( val.slice(0, 4), val.slice(5, 7), val.slice(8, 10), val.slice(11, 13), val.slice(14, 16) );
                var date =  new Date(dateutc);

                var xs = new XMLSerializer();

                var obj  =
                {
                    description: content,
                    title: title,
                    dateCreated: date,
                    postid:  atomid,
                    editURI:  href,
                    atomid:  posturl,
                    permaLink: thePostlink,
                    categories: theCats
                };
                rval[rval.length] = obj;
            }
            catch(e)
            {
            }
        }
        //listener.onResult(rval);
        //dump("\n\n parseRecentPosts ATOM Finished \n\n");

		if (!forODS) {
			performancing_xmlcall.processData(rval, null, 'historycall', "", true);
		}
    },
    getNamedChild: function(node, name) {
        for(var i=0;i<node.childNodes.length;++i) {
            if(node.childNodes[i].nodeName==name) return node.childNodes[i];
        }
        return null;
    },
    deletePost: function ( postid, aEditURI) {
        var url = this._url;
        if(postid) url += "/" + postid;
        if(aEditURI) url = aEditURI;
        this.doRequest("DELETE", url, null, this.handleDelete);
    },
	
    doPost: function ( method, postid, title, description, date_created, doPublish, aEditURI, aAtomID, isEdit, forODS) {
        var url = this._url;
        if(postid) url += "/" + postid;

        var date = "";
        try{
            date = bfXMLRPC.iso8601Format(date_created);
        }catch(e){
        }

        var body = "";
        var version = "ScribeFire 2.1";
        var theBlogCharType = gPerformancingUtil.getCharType();
        body += '<?xml version="1.0" encoding="UTF-8" ?>';
        body += '<entry xmlns="http://www.w3.org/2005/Atom" xmlns:app="http://purl.org/atom/app#">';

        var draft = false;
        if(doPublish == false || doPublish == 'bool0') draft = true;
		
		title = title.replace(/&amp;/g, '&');
		title = title.replace(/&/g, '&amp;');
		
            //Set the Labels (categories)
			var getLabelArray = "";
            try { getLabelArray = gPerformancingUtil.getArrOfCatChecked('blog-sidebar-listing-categories', false); } catch (e) { }
			
            if( getLabelArray != "" && getLabelArray.length > 0 ){
                for(var i=0; i < getLabelArray.length; i++){
                    body += '<category scheme="http://www.blogger.com/atom/ns#" term="'+getLabelArray[i].replace(/&/g,'&amp;')+'"/>';
                }
            }
            
            body += '<title mode="escaped" type="text">' + title + '</title>';
            body += '<issued>' + date + '</issued>';
            body += '<content type="xhtml">'
           // description = description.replace(/(&\S+)/g, "");
            var containsDIV = description.indexOf("<div xmlns=\"http://www.w3.org/1999/xhtml\">");
            if(containsDIV >= 0){
                body += description;
            }else{
                body += '<div xmlns="http://www.w3.org/1999/xhtml">' + description + '</div>';
            }
            body += '</content>';
            
            if(draft){
                body += '<app:control>';
                body += '  <app:draft>yes</app:draft>';
                body += '</app:control>';
            }else{
               // body += '<app:control>';
                //body += '  <app:draft>no</app:draft>';
                //body += '</app:control>';
            }
            body += ' </entry>';
		
		if (forODS) {
        	this.doRequest(method, url, body, SF_QUICKBLOG.processPostEdit, doPublish);
		}
		else {
        	this.doRequest(method,url,body,this.parsePosts, doPublish);
		}
    },
    editPost: function ( postid, title, description, date_created, isDraft, aEditURI, aAtomID, forODS) {
		this.doBlockingAuth();
        this.doPost( "PUT", postid, title, description, date_created, isDraft, aEditURI, aAtomID, "isEdit", forODS);
    },
    newPost: function ( title, description, date_created, isDraft) {
        this.doPost( "POST", null, title, description, date_created, isDraft);
    },
    parsePosts: function( inst) {
        //dump("\n\n NewPost response: " + inst +"\n\n");
        //gPFFDebugTemp.push(inst._req.responseXML);
        //gPFFDebugTemp.push(inst._req.responseText);
        var dom = inst._req.responseXML;
        if(!dom)
        {
            // LiveJournal - everone wants to be different, don't they?
            if(inst._req.responseText.match(/OK/)) {
                //listener.onResult(1);
                performancing_xmlcall.processData(1, null, null, "", true);
                return;
            }
            else {
				alert(inst._req.responseText);
                return;
            }
        }
        var entries = dom.getElementsByTagName("entry");
        var rval = new Object();
        try
        {
            var entry_n = entries[0];
            var link_n = null;
            var perm_link_n = null;
            var atomid_n = inst.getNamedChild(entry_n, "id");
            var atomid = "";
            if(atomid_n) atomid = atomid_n.firstChild.nodeValue;
            for(var j=0;j<entry_n.childNodes.length;++j) {
                if(entry_n.childNodes[j].nodeName=="link") {
                    var tmp = entry_n.childNodes[j];
                    if(tmp.getAttribute("rel").match(/edit/)) {
                        link_n = tmp;
                    }
                    else if(tmp.getAttribute("rel").match(/self/)) {
                        perm_link_n = tmp;
                    }
                }
            }
            var href = link_n.getAttribute("href");
            rval.editURI = href;
            rval.atomid = atomid;
            href.match(/.+\/(.+)/);
            rval.uid = RegExp.$1;;
            //Livejournal hackage
            if(rval.editURI.length>0 && rval.atomid.length==0) {
                var perm_link = perm_link_n.getAttribute("href");
                if(perm_link.match(/livejournal/)) {
                    perm_link.match(/.+livejournal.com\/users\/(.+?)\/(.+?)\./);
                    rval.atomid = "urn:lj:livejournal.com:atom1:" + RegExp.$1 + ":" + RegExp.$2;
                }
            }
        }
        catch(e)
        {
            var localeString = performancingUI.getLocaleString('proccessingposterror', []);
            alert(localeString);
        }
        performancing_xmlcall.processData(rval, null, 'newpostcall', "", true );
        //performancing_xmlcall.processData(rval, 'historycall', null, true);
    },
    
    handleDelete: function( inst) {
        //listener.onResult(1);
        performancing_xmlcall.processData(1, null, 'deletehistorycall', "", true);
    }
}