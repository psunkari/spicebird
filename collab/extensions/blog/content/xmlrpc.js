// File taken from ScribeFire 2.1 Firefox Blogging Extension licensed under GPL 2.0.
/*
XMLRPC Utility code.
------------------------------------------------------
*/

var DEBUG = false;

var gLastPostID = null;
var gPFFTempObject = [];
var gPFFRightAfterPost = false;
var gPFFLastURIPost = "";
var performancing_xmlcall = new Object();
//performancing_atomcall = new Object();

performancing_xmlcall.init = function() {
    this.lastResponseData = null;
    this.appkey = "0123456789ABCDEF";
}

//Send XMLRPC Command
performancing_xmlcall.sendCommand = function(theURL, theXMLString, theAction, additionalInfo, theGUID, aCallFunction) { //Both arguments have to be strings
	var theCall = new PffXmlHttpReq(theURL, "POST", theXMLString, false, null, null);

	theCall.onResult = function( aText, aXML ){
		aCallFunction(theCall.request.responseText, additionalInfo, theAction, theGUID);
	};

	theCall.onError = function (aStatusMsg, Msg) {
	        var faultCode = -1;
		var faultString = '';

		switch (theCall.request.status) {
			case 403:
			        faultCode = 403;
				faultString = BlogUtils.getString("blog.error.http403");
			break;
			case 404:
			        faultCode = 404;
				faultString = BlogUtils.getString("blog.error.http404");
			break;
			default:
				faultString = BlogUtils.getString("blog.error.httpGeneric", [theCall.request.status, theURL]);
			break;
		}

		if (typeof(theAction) == "function")
		        theAction({"faultCode" : faultCode, "faultString" : faultString}, additionalInfo, null, theGUID);
	};

	theCall.prepCall();
	theCall.request.setRequestHeader("Content-Type", "text/xml");
	theCall.makeCall();
	theCall.request.overrideMimeType ('text/xml');
}

performancing_xmlcall.processData = function(theXML, additionalInfo, theAction, theGUID, isAtom) {
    var ourParsedResponse = null;
    var faultString = '';
    if(!isAtom){
        var re = /(\<\?\xml[0-9A-Za-z\D]*\?\>)/;
        var newstr = theXML.replace(re, "");

		try {
        	var e4xXMLObject = new XML(newstr);
		} catch (e) {
			faultString = BlogUtils.getString("blog.error.malformedXML");
		}

        if (e4xXMLObject.name() != 'methodResponse' ||
                !(e4xXMLObject.params.param.value.length() == 1 ||
                    e4xXMLObject.fault.value.struct.length() == 1)) {
            faultString = BlogUtils.getString('blog.error.notAPIAddress', [theXML]);
        }
    
        if (e4xXMLObject.params.param.value.length() == 1) {
            ourParsedResponse = bfXMLRPC.XMLToObject(e4xXMLObject.params.param.value.children()[0]);
        }
        
        if(e4xXMLObject.fault.children().length() > 0 ) {
            ourParsedResponse = bfXMLRPC.XMLToObject( e4xXMLObject.fault.value.children()[0]);
        }
    }else{
        ourParsedResponse = theXML;
    }

    if (faultString)
        this.lastResponseDataObject = { "faultCode" : -1, "faultString" : faultString };
    else
        this.lastResponseDataObject = ourParsedResponse;

    /*
    //Now do something!
    if(theAction == "accountwizard"){
        processReturnData(this.lastResponseDataObject, isAtom, theXML); //For account wizard calls
    }else{
        performancing_xmlcall.processReturnData(this.lastResponseDataObject , theAction, additionalInfo, isAtom, theGUID, newstr); //for all other calls
    }*/
    if (typeof(theAction) == "function")
        theAction (this.lastResponseDataObject, additionalInfo, isAtom, theGUID);
}

performancing_xmlcall.replaceText = function(inString,oldText,newText) {
return (inString.split(oldText).join(newText));
}

performancing_xmlcall.processReturnData = function(theObject, theAction, additionalInfo, isAtom, theGUID){
    var isError = false;
	
    if(!isAtom){
        if(theObject.length == null){
            if(theObject.faultString){
				if ((theAction != "pagelistcall") && (theAction != "newcategorycall")){
	                var localeString = performancingUI.getLocaleString('requesterror', [theObject.faultString]);
	       	        alert(localeString);
	           	    performancingUI.okClearPost();
				}
				else {
					// Wordpress API pre new API
					gPerformancingUtil.serviceObject.supportsPages = false;
					gPerformancingUtil.serviceObject.addCategories = false;
					gPerformancingUtil.serviceObject.createCategories = false;
				}
				
               	isError = true;
            }
		}
	}
	
	if (theAction == "newcategorycall"){
		if (isError){
			// The category already exists.
			var catArr = [additionalInfo];
			var doNotCheckClear = performancingUI.hasCheckboxChildren('blog-sidebar-listing-categories');
			gPerformancingUtil.setCategoriesSidebar(theCategoryArray, !doNotCheckClear);
		}
		else {
			// We need to set the "cat" attribute to the id that was returned.
			var catID = theObject.toString();
			
			var checkList = document.getElementById("blog-sidebar-listing-categories");
			for (var i = 0; i < checkList.childNodes.length; i++) {
				if (checkList.childNodes[i].getAttribute("label") == additionalInfo){
					checkList.childNodes[i].setAttribute("cat",catID);
					break;
				}
			}
		}
	}
	else if ((theAction == "pagelistcall") && (!isError)){
		gPerformancingUtil.serviceObject.supportsPages = true;
		gPerformancingUtil.serviceObject.addCategories = true;
		gPerformancingUtil.serviceObject.createCategories = true;
		
		// Wordpress blog whose API supports Pages and adding categories
		window.setTimeout('gPerformancingUtil.getBlogPages("'+theGUID+'")', 0, true);
		document.getElementById("blog-sidebar-categories-addbtn").hidden = false;
		
		document.getElementById("tab-pages").setAttribute("disabled","false");
	}
	else if (theAction == "pagescall") {
		gPerformancingUtil.clearListOut('performancing-pages-list');
		
		if(!isError){
			var theTitle = null;
			var theContent = null;
			var moreContent = "";
			var theCategories = "";
			var thePostID = null;
			var thePostLink = null;
			var atomEditURI = null;
			var blogName = gPerformancingUtil.currentBlogName;
			gPerformancingUtil.clearPagesXMLFile();
	
			for(k = 0; k < theObject.length; k++){
				try { theTitle = theObject[k].title.toString(); theTitle = theTitle.replace(/\s\s+/gi, " "); } catch(e) { theTitle = "Untitled" }
				try { theContent = theObject[k].description.toString(); } catch(e) { }
				try { thePostLink = theObject[k].permaLink.toString(); } catch(e) { thePostLink = ""; }
				try { theDateCreated = theObject[k].dateCreated.toString(); } catch(e) { theDateCreated = ""; }
				try { thePostID = theObject[k].page_id; } catch(e) { thePostID = ""; }
				try { isDraft = theObject[k].page_status.toString() == 'draft'; } catch (e) { isDraft = false; }
				
				gPerformancingUtil.setPagesXML(thePostID, theContent, theTitle, theCategories, theDateCreated, isDraft);
	
				var tempArray = [theTitle];
				gPerformancingUtil.addItemToList([tempArray], k, 'performancing-pages-list', theGUID, theTitle, "gPerformancingUtil.addPageToEditor(this);", theDateCreated, thePostID );
	
				if(gPFFRightAfterPost == true && gLastPostID == thePostID) {
					gPFFRightAfterPost = false;
					performancingUI.deliciousAddTechnorati(thePostLink, theTitle, isAtom, atomEditURI);
					window.setTimeout("performancingUI.sendTrackBacks('"+theTitle+"','"+thePostLink+"','"+blogName+"')", 2500, true);
				}
			}
			
			gPerformancingUtil.savePagesXMLFile();
		}
	}
	else if(theAction == "historycall"){
        gPerformancingUtil.clearListOut('performancing-history-list');
        if(!isError){
                //aPostid, aTitle, aDescription, aDateCreated, aPublish
                //gPerformancingUtil.addItemToList(tempArray, j, 'performancing-history-list');
                //dump("History Response Length: "+theObject.length + "\n");
                gPerformancingUtil.clearListOut('performancing-history-list');
                var theTitle = null;
                var theContent = null;
                var theCategories = null;
				var theTags = null;
                var thePostID = null;
                var thePostLink = null;
                var atomEditURI = null;
				var isDraft = false;
                var blogName = gPerformancingUtil.currentBlogName;
                gPerformancingUtil.clearHistoryXMLFile();
                
                for(k = 0; k < theObject.length; k++){
                    //gBlogObject[k].postid, gBlogObject[k].postDate
                    try{
                        //dump("Try finding .TITLE \n");
                        theTitle = theObject[k].title.toString();
                    }catch(e){
                        theTitle = "Untitled"
                    }
                    //Remove any extra spaces (atleast 2 or more consecutive spaces)
                    theTitle = theTitle.replace(/\s\s+/gi, " ");
                    try{
                        theContent = theObject[k].content.toString();
                    }catch(e){
                        
                    }

					try {
						isDraft = (theObject[k].post_status.toString() == 'draft');
					} catch (e) {
						isDraft = false;
					}
                    
                    try{
                        theContent = theObject[k].description.toString();
                        //alert("theContent: "+ theContent)
                    }catch(e){
                        //alert("Content Error: "+ e)
                    }

                    dump("\n\n History Content: \n" +theContent+ "\n\n");
                    //categories
                    var moreContent = "";
                    try{
                        moreContent = theObject[k].mt_text_more.toString();
                    }catch(e){
                    }

                    if(moreContent != ""){
                        theContent = theContent + "<!--more-->" + moreContent;
                    }
                    
					try {
						var ljTitle = null;
						
						if (ljTitle = theContent.match(/<title>([^<]*)<\/title>/i)[1]) {
							theTitle = ljTitle;
							theContent = theContent.replace("<title>"+ljTitle+"</title>", "");
						}
					} catch (e) {
					}

                    try{
                        theCategories = theObject[k].categories.toString();
                        //alert("theCategories: " + theCategories);
                    }catch(e){
                        theCategories = "";
                    }
                    
					try {
						theTags = theObject[k].mt_keywords.toString();
					} catch (e) {
						try {
							theTags = theObject[k].tags.toString();
						} catch (e) {
							theTags = '';
						}
					}
					

                     //links
                    try{
                        thePostLink = theObject[k].permaLink.toString();
                    }catch(e){
                        thePostLink = "";
                    }
                    
                    //theDateCreated
                    try{
                        theDateCreated = theObject[k].dateCreated.toString();
                    }catch(e){
                        theDateCreated = "";
                    }
                    
                     //Atom links
                    try{
                        atomEditURI = theObject[k].editURI.toString();
                        //thePostLink = atomEditURI;
                    }catch(e){
                        atomEditURI = "";
                    }
                    
                    try{
                        if(theObject[k].postid == null){
                            thePostID = theObject[k].postId; //LiveJournal Hack, bastards!!
                        }else{
                            thePostID = theObject[k].postid;
                        }
                    }catch(e){
                        thePostID = "";
                    }
                    //gPFFTempObject.push(thePostID);
                    
                    gPerformancingUtil.setHistoryXML(thePostID, theContent, theTitle, theCategories, theDateCreated, theTags, isDraft);
                    var tempArray = [ theTitle];
                    //dataArray, number, listIDname, theGUID, theURL, onItemClick, aDate, aPostId
                    gPerformancingUtil.addItemToList([tempArray], k, 'performancing-history-list', theGUID, theTitle, "gPerformancingUtil.addHistoryItemToEditor( this );", theDateCreated, thePostID );
                    
                    if( gPFFRightAfterPost == true && gLastPostID == thePostID ){
                        gPFFRightAfterPost = false;
                        performancingUI.deliciousAddTechnorati(thePostLink, theTitle, isAtom, atomEditURI);
                        window.setTimeout("performancingUI.sendTrackBacks('"+theTitle+"','"+thePostLink+"','"+blogName+"')", 2500, true);
                    }
                }
                gPerformancingUtil.saveHistoryXMLFile();
        }
    }else if(theAction == "categorycall"){
        //dump('\n Got Categorycall BlogObject: ' + theObject + '\n');
        if(!isError){
            //dump("Response Length: "+theObject.length + "\n");
            gPerformancingUtil.clearCheckListOut('blog-sidebar-listing-categories');
            //gBlogObject.categoryId, gBlogObject.categoryName
            //gPFFTempObject = theObject;
            var theCatArray = [];
            var theCatIdArray = [];
            if( theObject.length >= 0 ){
                for(k = 0; k < theObject.length; k++){
                    //ROLLER metaWebLoghack
                    var tempArray = null;
                    try{
                        if(theObject[k].categoryName.toString() != ""){
                            tempArray = [theObject[k].categoryName];
                        }
                    }catch(e){
                        try{
                            if(theObject[k].title.toString() != ""){
                                tempArray = [theObject[k].title];
                            }
                        }catch(e){
                            if(theObject[k].description.toString() != ""){
                            tempArray = [theObject[k].description];
                            }
                        }
                    }
                    //gPerformancingUtil.addItemToCheckList([tempArray], k, 'blog-sidebar-listing-categories', null, theObject[k].categoryId, "" );
                    theCatArray.push(tempArray + "," + theObject[k].categoryId);
                    //theCatIdArray.push(theObject[k].categoryId);
                }
                
                //Should we sort the list?
                var doTheSort = false;
                try{
                    doTheSort = gPerformancingUtil.prefs.getBoolPref("display.sortcats");
                }catch(e){
                    doTheSort = false;
                }
                
                function sortTags(a, b) {
                	a = a.toLowerCase();
                	b = b.toLowerCase();
                	if (a < b) return -1;
                	else if (b < a) return 1;
                	else return 0;
                }
                
                if(doTheSort){
                    theCatArray.sort(sortTags);
                }
                
                //Now add the Cat List
                var theCatID = "";
                for(l = 0; l < theCatArray.length; l++){
                    theNewCatArray = theCatArray[l].split(",");
                    gPerformancingUtil.addItemToCheckList([theNewCatArray[0].replace(/&amp;/g, "&")], l, 'blog-sidebar-listing-categories', null, theNewCatArray[1], "" );
                }
                
            }else{
                for(x in theObject){ 
                    var tempArray = x.toString();
                    gPerformancingUtil.addItemToCheckList([tempArray], 0, 'blog-sidebar-listing-categories', null, '', "" );
                }
            }
        }
    }else if(theAction == "newpostcall"){
        if(!isError){
            gPFFRightAfterPost = true;
            //dump('\n Got New Post BlogObject: ' + theObject + '\n');
            //Call clear content and mark as posted to user!
            performancingEditor.postSuccessful();
            
            //Fix for Blogger/ATOM
            if(theObject.uid != null){
                gLastPostID = theObject.uid;
            }else{
                gLastPostID = theObject;
            }
            gLastPostID = gLastPostID.toString();
            //Now set the category (if there are categories checked)
            gPerformancingUtil.setCategoryList(gLastPostID, additionalInfo);
            
            theGUID = gPerformancingUtil.prefs.getCharPref("settings.lastselected.blog");
            var theBlogURL = document.getElementById("blog-group").selectedItem.getAttribute("tooltiptext");
            var blogName = gPerformancingUtil.currentBlogName;
            
            window.setTimeout("performancingUI.doPing(\""+ blogName+"\",\""+ theBlogURL+"\")", 3000, true);
            
            window.setTimeout('gPerformancingUtil.getBlogHistory("'+theGUID+'")', 0, true);
            //gPerformancingUtil.getBlogHistory(theGUID);
        }

		document.getElementById("input-tags").value = '';
    }else if(theAction == "newpagecall"){
        if(!isError){
            gPFFRightAfterPost = true;
			
            //Call clear content and mark as posted to user!
            performancingEditor.postSuccessful();
            
            //Fix for Blogger/ATOM
            if(theObject.uid != null){
                gLastPostID = theObject.uid;
            }else{
                gLastPostID = theObject;
            }
            gLastPostID = gLastPostID.toString();
            
            theGUID = gPerformancingUtil.prefs.getCharPref("settings.lastselected.blog");
            var theBlogURL = document.getElementById("blog-group").selectedItem.getAttribute("tooltiptext");
            var blogName = gPerformancingUtil.currentBlogName;
            
            window.setTimeout("performancingUI.doPing(\""+ blogName+"\",\""+ theBlogURL+"\")", 3000, true);
            
            window.setTimeout('gPerformancingUtil.getBlogPages("'+theGUID+'")', 0, true);
        }
    }else if(theAction == "editpostcall"){
        if(!isError){
            gPFFRightAfterPost = true;
            //dump('\n Got Edit Post BlogObject: ' + theObject + '\n');
            //Call clear content and mark as posted to user!
            performancingEditor.postSuccessful();
            
            //Now set the category (if there are categories checked)
            var thePostID = performancingEditor.getCurrentEditorWindow().pffEditorUI.entryId;
            gPerformancingUtil.setCategoryList(thePostID, additionalInfo);
            
            theGUID = gPerformancingUtil.prefs.getCharPref("settings.lastselected.blog");
            
            var theBlogURL = document.getElementById("blog-group").selectedItem.getAttribute("tooltiptext");
            var blogName = gPerformancingUtil.currentBlogName;
            window.setTimeout("performancingUI.doPing('"+ blogName+"','"+ theBlogURL+"')", 3000, true);
            
            window.setTimeout('gPerformancingUtil.getBlogHistory("'+theGUID+'")', 0, true);
            //gPerformancingUtil.getBlogHistory(theGUID);
            gLastPostID = thePostID;
        }
    }else if(theAction == "setcategoriescall"){
        //dump('\n Categories got set!!\n');
        //Now publish it! This fixes a typepad category bug
        //gPerformancingUtil.publishThePost(gLastPostID);
        //Now publish it! This fixes a typepad category bug
        if(!gIsDraft){
            gPerformancingUtil.publishThePost(gLastPostID);
        }
    }else if(theAction == "deletehistorycall"){
        //dump('\n\n Post Deleted!!\n');
        theGUID = gPerformancingUtil.prefs.getCharPref("settings.lastselected.blog");
        gPerformancingUtil.getBlogHistory(theGUID); //re get the new list now
        var localeString = performancingUI.getLocaleString('postdeleted', []);
        alert(localeString);
        
		performancingUI.reLoadBlogs();
		performancingEditor.closeTab();
	}
	
	return true;
}

/* TODO - Have only one xmlhttp request  */

//REMOVE
function gMakeXMLCall(theURL, message, theAction, additionalInfo, theGUID) {
 //gPFFTempObject.push(message);
 var xmlhttp = Components.classes["@mozilla.org/xmlextras/xmlhttprequest;1"].createInstance(Components.interfaces.nsIXMLHttpRequest);
 xmlhttp.open('POST', theURL, true);
 gPFFLastURIPost = theURL;
 xmlhttp.onreadystatechange=function() {
      if (xmlhttp.readyState==4) {
          if (xmlhttp.status == 200) { //We actually want to catch bad pages
              if(theAction == "atomAPIpost"){
                  performancingUI.addDeliciousTechnoratiATOM( xmlhttp.responseText, additionalInfo );
              }else{
                  //gPFFTempObject.push(xmlhttp.responseText) ;
                  //processData = function(theXML, additionalInfo, theAction, theGUID, isAtom)
                  performancing_xmlcall.processData(xmlhttp.responseText, additionalInfo, theAction, theGUID, null);
              }
          }else{
              //dump("Bad XML return: " + xmlhttp.readyState + "\n");
          }
      }
 }
 xmlhttp.setRequestHeader("Content-Type", "text/xml");
 xmlhttp.setRequestHeader('Content-Length', message.length );
 xmlhttp.setRequestHeader("User-Agent", "Mozilla/5.0 (compatible; ScribeFire; http://www.scribefire.com/)");
 xmlhttp.send(message); 
 xmlhttp.overrideMimeType ('text/xml');
}

//REMOVE
function gMakeXMLCall2(theURL, message, theAction, additionalInfo, theGUID) {
    
 var xmlhttp = Components.classes["@mozilla.org/xmlextras/xmlhttprequest;1"].createInstance(Components.interfaces.nsIXMLHttpRequest);
 xmlhttp.open('GET', theURL, true);
 gPFFLastURIPost = theURL;
 xmlhttp.onreadystatechange=function() {
      if (xmlhttp.readyState==4) {
          if (xmlhttp.status == 200) { //We actually want to catch bad pages
              //xmlhttp.responseText
              if(theAction == "atomAPIpost"){
                  //alert("RESPONSE BABY: " +  xmlhttp.responseText);
                  performancingUI.addDeliciousTechnoratiATOM( xmlhttp.responseText, additionalInfo );
              }else if(theAction == "ping"){
                  //alert("RESPONSE BABY: " +  xmlhttp.responseText);
                  performancingUI.processPingRecData(xmlhttp.responseText, message, theAction);
              }else if(theAction == "checklogin"){
                  var isLoggedin = xmlhttp.responseText.search(/User Login/);
                  //alert("Login: "+isLoggedin);
              }else if(theAction == "accountw-autodetect"){
                  prossessAutoDetectPage(message, xmlhttp.responseXML);
                  //alert("Login: "+isLoggedin);
              }
              //performancing_xmlcall.processData(xmlhttp.responseXML);
          }else{
              //dump("Bad XML return: " + xmlhttp.readyState + "\n");
          }
      }
 }
 //xmlhttp.send(null)
 if(theAction != "checklogin"){
     xmlhttp.setRequestHeader("Content-Type", "text/xml");
     xmlhttp.setRequestHeader("User-Agent", "ScribeFire " + gPerformancingVersionUA);
     xmlhttp.overrideMimeType ('text/xml');
 }
 xmlhttp.send(message);
 //dump("\nXML SENT: " + message + "\n");
}

//REMOVE
function gMakeXMLCall3(theURL, message, theAction, additionalInfo, theGUID) {
    
 var xmlhttp = Components.classes["@mozilla.org/xmlextras/xmlhttprequest;1"].createInstance(Components.interfaces.nsIXMLHttpRequest);
 xmlhttp.open('GET', theURL, true);
 xmlhttp.onreadystatechange=function() {
      if (xmlhttp.readyState==4) {
          if (xmlhttp.status == 200) { //We actually want to catch bad pages
              //xmlhttp.responseText
              if(theAction == "accountw-autodetect"){
                  doProssessAutoDetectPage(message, xmlhttp.responseText, "1");
              }else if(theAction == "accountw-autodetect-2"){
                  doProssessAutoDetectPage(message, xmlhttp.responseXML, "2");
              }
          }else{
              //dump("Bad XML return: " + xmlhttp.readyState + "\n");
          }
      }
 }
 xmlhttp.send(null)
 xmlhttp.overrideMimeType ('text/xml');
 //xmlhttp.send(message);
 //dump("\nXML SENT: " + message + "\n");
}

//application/x-www-form-urlencoded
function gMakeTrackBackXMLCall(theURL, message, theAction, additionalInfo, aNumber, aSecondTry, theGUID) {
    
 var xmlhttp = Components.classes["@mozilla.org/xmlextras/xmlhttprequest;1"].createInstance(Components.interfaces.nsIXMLHttpRequest);
 xmlhttp.open('POST', theURL, true);
 gPFFLastURIPost = theURL;
 xmlhttp.onreadystatechange=function() {
      if (xmlhttp.readyState==4) {
          if (xmlhttp.status == 200) { //We actually want to catch bad pages
              //xmlhttp.responseText
              if(theAction == "trackback"){
                  //alert("RESPONSE BABY: " +  xmlhttp.responseText);
                  performancingUI.trackBackResponse( xmlhttp.responseText, theURL, message, theAction, additionalInfo, aNumber, aSecondTry, theGUID);
              }
          }else{
              //dump("Bad XML return: " + xmlhttp.readyState + "\n");
          }
      }
 }
 //xmlhttp.send(null) 
 xmlhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
 xmlhttp.setRequestHeader('Content-Length', message.length );
 xmlhttp.send(message); 
 //dump("\nXML SENT: " + message + "\n");
}

//REMOVE
function gMakeDeliciousXMLCall(theURL, message, theAction, userName, passWord) {
    
 var xmlhttp = Components.classes["@mozilla.org/xmlextras/xmlhttprequest;1"].createInstance(Components.interfaces.nsIXMLHttpRequest);
 //rval = this._req.open(method, url, true, this._user, this._pass);
 xmlhttp.open('GET', theURL, true, userName, passWord);
 gPFFLastURIPost = theURL;
 xmlhttp.onreadystatechange=function() {
      if (xmlhttp.readyState==4) {
          if (xmlhttp.status == 200) { //We actually want to catch bad pages
              performancingUI.deliciousResponse(xmlhttp.responseText, message, theAction, userName, passWord);
          }else{
              //dump("Bad XML return: " + xmlhttp.readyState + "\n");
          }
      }
 }
 //xmlhttp.send(null) 
 xmlhttp.setRequestHeader("Content-Type", "text/xml");
 xmlhttp.setRequestHeader("User-Agent", "ScribeFire " + gPerformancingVersionUA);
 //xmlhttp.setRequestHeader('Content-Length', message.length );
 //xmlhttp.send(message);
 xmlhttp.send("");  
 xmlhttp.overrideMimeType ('text/xml');
 //dump("\nXML SENT: " + message + "\n");
}

//REMOVE
function gMakePingXMLCall(theURL, message, theAction) {
    
 var xmlhttp = Components.classes["@mozilla.org/xmlextras/xmlhttprequest;1"].createInstance(Components.interfaces.nsIXMLHttpRequest);
 //rval = this._req.open(method, url, true, this._user, this._pass);
 xmlhttp.open('POST', theURL, true);
 gPFFLastURIPost = theURL;
 xmlhttp.onreadystatechange=function() {
      if (xmlhttp.readyState==4) {
          if (xmlhttp.status == 200) { //We actually want to catch bad pages
              //xmlhttp.responseText
              performancingUI.processPingRecData(xmlhttp.responseText, message, theAction);
          }else{
              //dump("Bad XML return: " + xmlhttp.readyState + "\n");
          }
      }
 }
 //xmlhttp.send(null) 
 xmlhttp.setRequestHeader("Content-Type", "text/xml");
 xmlhttp.setRequestHeader("User-Agent", "ScribeFire " + gPerformancingVersionUA);
 xmlhttp.setRequestHeader('Content-Length', message.length );
 xmlhttp.send(message); 
 xmlhttp.overrideMimeType ('text/xml');
 //dump("\nXML SENT: " + message + "\n");
}

var bfXMLRPC = new Object();

bfXMLRPC.makeXML = function(method, myParams, isAtom) {
    if(!isAtom){
        var xml = <methodCall></methodCall>;
        xml.methodName = method;
        //i->0 is the URL
        for(var i=1; i < myParams.length; i++){
            xml.params.param += <param> <value> { bfXMLRPC.convertToXML(myParams[i], isAtom) }</value> </param>;
        }
		
        var theBlogCharType = "UTF-8";
		
        return '<?xml version="1.0" encoding="' + theBlogCharType + '" ?>' + xml.toXMLString();
    }
	
    return 0;
}

bfXMLRPC.convertToXML = function(myParams, isAtom) {
    //gPFFTempObject = myParams;
    if(!isAtom){
        var paramType = myParams.constructor.name;
        var paramTemp = null;
        switch (paramType){
            
          case "Number"://12, 12.12, etc.
            if( myParams == parseInt(myParams) ){
                paramTemp = "<int>" + myParams + "</int>";
            }else{
                paramTemp = "<double>" + myParams + "</double>";
            }
            break;
            
          case "String":
            if( myParams.toString() == 'bool1'){
                paramTemp = "<boolean>1</boolean>";
            }else if( myParams.toString() == 'bool0' ){
                paramTemp = "<boolean>0</boolean>";
            }else{
                paramTemp = "<string><![CDATA[" + myParams + "]]></string>";
            }
            break;
            
          case "Boolean"://0,1, true, false
            paramTemp = "<boolean>" + myParams + "</boolean>";
            break;
            
          case "Date": //Date Object: var date = new Date();
            var theDate = bfXMLRPC.iso8601Format(myParams).toString();
            var theErrorString = "NaNNaNNaNTNaN:NaN:NaN";
            if(theDate != theErrorString){
                paramTemp = "<dateTime.iso8601>" + theDate + "Z</dateTime.iso8601>";
            }else{
                paramTemp = "<dateTime.iso8601></dateTime.iso8601>";
            }
            break;
            
          case "Array": //Array Object
            var tempVal = "<array><data>";
            //for(var i=0;i<myParams.length;++i)
            for(var i = 0; i < myParams.length; i++)
            {
                //dump("\n i: " + i + "\n")
                tempVal += "<value>" + bfXMLRPC.convertToXML(myParams[i]) + "</value>";
            }
            tempVal += "</data></array>";
            paramTemp = tempVal;
            break;
            
          case "Object": //Array Object
            var tempVal = "<struct>";
            //for(var i=0;i<myParams.length;++i)
            for(x in myParams)
            {
				if (typeof myParams[x] != 'undefined') {
	                if(myParams[x].constructor.name == 'String'){
	                    if(x == "bits"){
	                        tempVal += "<member><name>" + x + "</name>" + "<value><base64><![CDATA[" +bfXMLRPC.convertToXML(myParams[x]) + "]]></base64></value>" +"</member>";
	                    }else{
	                        tempVal += "<member><name>" + x + "</name>" + "<value><string><![CDATA[" +bfXMLRPC.convertToXML(myParams[x]) + "]]></string></value>" +"</member>";
	                    }
                    
	                }else if(myParams[x].constructor.name == 'Date'){
	                    var theDate = bfXMLRPC.iso8601Format(myParams[x]).toString();
	                    var theErrorString = "NaNNaNNaNTNaN:NaN:NaN";
	                    if(theDate != theErrorString){
	                        tempVal += "<member><name>" + x + "</name>" + "<value>" +"<dateTime.iso8601>" + theDate + "Z</dateTime.iso8601>" + "</value>" +"</member>";
	                    }else{
	                        tempVal += "<member><name>" + x + "</name>" + "<value>" +"<dateTime.iso8601></dateTime.iso8601>" + "</value>" +"</member>";
	                    }
                    
	                }else if(myParams[x].constructor.name == 'Number'){
	                    if( myParams[x] == parseInt(myParams[x]) ){
	                        tempVal += "<member><name>" + x + "</name>" + "<value>" +"<int>"  +bfXMLRPC.convertToXML(myParams[x]) + "</int>" + "</value>" +"</member>";
	                    }else{
	                        tempVal += "<member><name>" + x + "</name>" + "<value>" + "<double>" + bfXMLRPC.convertToXML(myParams[x]) + "</double>" + "</value>" +"</member>";
	                    }
	                }else{
	                    tempVal += "<member><name>" + x + "</name>" + "<value>" +bfXMLRPC.convertToXML(myParams[x]) + "</value>" +"</member>";
	                }
				}
            }
            tempVal += "</struct>";
            paramTemp = tempVal;
            break;
            
          default:
            paramTemp = "<![CDATA[" + myParams + "]]>";
            break;
            
        }
            
        //var paramObject = new XML("<string>" + myParams +"</string>");
        var paramObject = new XML(paramTemp);
        
        return paramObject;
    }
    
    return 0;
}

//XMLToObject is derived from GPL code originally by Flock Inc:
//For the original source, see: http://cvs-mirror.flock.com/index.cgi/mozilla/browser/components/flock/xmlrpc/content/xmlrpchelper.js?rev=1.1&content-type=text/vnd.viewcvs-markup
bfXMLRPC.XMLToObject = function(xml) {
    try{
        if (xml.nodeKind()) {
            //foo
        }
    }catch(e){
        //foo
        xml = new XML(xml);
    }
    //gPFFTempObject = xml;
    
    if (xml.nodeKind() == 'text') {
            // the default type in string
            return xml.toString();
    }
        
    switch (xml.name().toString()) {
        case 'int':
        case 'i4':
            return parseInt (xml.text());
        case 'boolean':
            return (parseInt (xml.text()) == 1);
        case 'string':
            return (xml.text().toString());
        case 'double':
            return parseFloat (xml.text());
        case 'dateTime.iso8601':
            var val = xml.text().toString();
            //MSN Spaces hack for dates that look like: 2006-01-26T07:24:20Z
            val = val.replace(/\-/gi, "");
            val = val.replace(/\z/gi, "");
            //end MSN hack
            var dateutc =  Date.UTC(val.slice(0, 4), val.slice(4, 6) - 1, 
                    val.slice(6, 8), val.slice(9, 11), val.slice(12, 14), 
                    val.slice(15));
            //alert('Date Val: ' + val + " RealDate: "+ new Date(dateutc));
            return new Date(dateutc);
        case 'array':
            var arr = new Array ();
            for (var i=0; i<xml.data.value.length(); i++) {
                arr.push (bfXMLRPC.XMLToObject(xml.data.value[i].children()[0]));
            }
            return arr;
        case 'struct':
            var struct = new Object ();
            for (var i=0; i < xml.member.length(); i++) {
                struct[xml.member[i].name.text()] = 
                    bfXMLRPC.XMLToObject(xml.member[i].value.children()[0]);
            }
            return struct;
            
        default:
            //dump('error parsing XML');
    }
}

//Function is derived from GPL code originally by Flock Inc:
//For more informationm See:
bfXMLRPC.iso8601Format = function(date) 
{
    var datetime = date.getUTCFullYear();
    var month = String(date.getUTCMonth() + 1);
    datetime += (month.length == 1 ?  '0' + month : month);
    var day = date.getUTCDate();
    datetime += (day < 10 ? '0' + day : day);

    datetime += 'T';

    var hour = date.getUTCHours();
    datetime += (hour < 10 ? '0' + hour : hour) + ':';
    var minutes = date.getUTCMinutes();
    datetime += (minutes < 10 ? '0' + minutes : minutes) + ':';
    var seconds = date.getUTCSeconds();
    datetime += (seconds < 10 ? '0' + seconds : seconds);
	
	return datetime;
}

bfXMLRPC.setUpBlogObject = function(theBlogXML) {
	var theXMLObject = theBlogXML;
	var apiObject = null;
	var aService = null;
	
	if(theXMLObject.blogapi.toString() == ""){
		aService = theXMLObject.blogtype.toString(); //for legacy 1.0 release issues
	}
	else{
		aService = theXMLObject.blogapi.toString();
	}
	
	if (DEBUG) alert("Using API: " + aService);
	
	// Determine the API type from either the blogtype value of the blogapi value.
	switch (aService) {
		case "blogger_com":
		case "livejournal_atom_com":
		case "s_atom":
		case "atom":
			apiObject = new perFormancingAtomAPI();
			break;
		case "atom_blogger":
		case "atom_blogger_cust":
			apiObject = new perFormancingBloggerAtomAPI();
			break;
		case "livejournal_com":
		case "blogger_cust":
		case "s_blogger":
		case "blogger":
			apiObject = new perFormancingBloggerAPI();
			break;
		case "wordpress_com":
		case "typepad_com":
		case "wordpress_cust":
		case "moveabletype_cust":
		case "s_mt":
		case "mt":
			apiObject = new perFormancingMovableTypeAPI();
			break;
		case "metaweblog":
		case "s_metaweblog":
		case "msnspaces_com":
			apiObject = new performancingMetaweblogAPI();
			break;
		case "s_myspace":
			apiObject = new performancingMySpaceAPI();
			break;
		case "s_tumblr":
			apiObject = new performancingTumblrAPI();
			break;
		default:
			if (DEBUG) alert("Could not find API service. " + aService);
			break;
	}
	
	var thePassword = gPerformancingUtil.goGetPassword(theXMLObject.username.toString(), theXMLObject.url.toString());
	apiObject.doSetup();
	apiObject.init(theXMLObject.blogtype.toString(), theXMLObject.appkey.toString(), theXMLObject.apiurl.toString(), theXMLObject.blogid.toString(), null, theXMLObject.username.toString(),  thePassword, false  );
	
	return apiObject;
}

bfXMLRPC.makePingXML = function(theMethodName, theBlogName, theBlogURL) {
         thePingXML = new XML();
        //The Content for each Blog
        thePingXML =
                     <methodCall>
                         <methodName>{theMethodName}</methodName>
                          <params>
                           <param>
                           <value>{theBlogName}</value>
                           </param>
                           <param>
                           <value>{theBlogURL}</value>
                           </param>
                          </params>
                      </methodCall>;
        return "<?xml version=\"1.0\"?>" + thePingXML.toXMLString();
}

/*
    Replace all Stupid XML Requests with this object
    
    USAGE:
    //PffXmlHttpReq( aUrl, aType, aContent, aDoAuthBool, aUser, aPass) 
    theCall = new PffXmlHttpReq('http://theurl.com', "GET", null, false, null, null);
    
    theCall.onResult = function (aText, aXML) {
        alert("Good Result:" + aText);
    }
    theCall.onError = function (aStatusMsg, aXML) {
        alert("Bad Result:" + aStatusMsg);
    }
    theCall.prepCall(); //Set up The call (open connection, etc.)
    theCall.request.setRequestHeader("Content-Type", "text/xml");
    theCall.makeCall(); //Make the call
    theCall.makeCall();
    theCall.request.overrideMimeType ('text/xml');
*/
function PffXmlHttpReq( aUrl, aType, aContent, aDoAuthBool, aUser, aPass) {
    this.url = aUrl;
    this.posttype = aType;
    this.content = aContent;
    this.username = aUser;
    this.password = aPass;
    this.doAuth = aDoAuthBool;
    //this.callback = aCallBackFunc;
    this.request = Components.classes["@mozilla.org/xmlextras/xmlhttprequest;1"].createInstance(Components.interfaces.nsIXMLHttpRequest);
}

PffXmlHttpReq.prototype.prepCall = function () {
    
    if(this.doAuth){
        this.request.open(this.posttype, this.url, true, this.username, this.password);
        
        //Keeps stupid Authentication window from poping up
        this.request.channel.notificationCallbacks = {
            QueryInterface: function (iid) { // nsISupports
                if (iid.equals (Components.interfaces.nsISupports) ||
                    iid.equals (Components.interfaces.nsIAuthPrompt) ||
                    iid.equals (Components.interfaces.nsIInterfaceRequestor)) {
                        return this;
                }
                throw Components.results.NS_ERROR_NO_INTERFACE;
            },
            getInterface: function (iid, result) { // nsIInterfaceRequestor
                if (iid.equals (Components.interfaces.nsIAuthPrompt)) {
                    return this;
                }
                Components.returnCode = Components.results.NS_ERROR_NO_INTERFACE;
                return null;
            },
            prompt: function (dialogTitle, text, passwordRealm, savePAssword, 
                    defaultText, result) { // nsIAuthPromptInterface
                return false;
            },
            promptUsernameAndPassword: function (dialogTitle, text, 
                    passwordRealm, savePassword, user, pwd) {
                          //Didn't work, asking for password again
                return false;
            },
            promptPassword: function (dialogTitle, text, passwordRealm, savePassword, user) {
                return false;
            }
        }
    }else{
        this.request.open(this.posttype, this.url, true);
    }
    
    var request = this.request;
    var onResult = this.onResult;
    var onError = this.onError;
    this.request.onreadystatechange = function () {
        if(request.readyState == 4){ 
            if (request.status == 200 || request.status == 201 || request.status == 202){
                onResult(request.responseText, request.responseXML);
            }else{
                try{
                    onError(request.statusMessage, request.responseText);
                } catch(e) { alert("Error running onError: " + e); }
            } 
        }
    }
    
    if(this.posttype.toLowerCase() == "post"){
        try{
            this.request.setRequestHeader('Content-Length', this.content.length );
        }catch(e){}
    }
}

PffXmlHttpReq.prototype.makeCall = function () {
    this.request.send(this.content)
}
   
/*
    Defined by Inheritor
*/

PffXmlHttpReq.prototype.onError = function (message) {
    //foo
}

PffXmlHttpReq.prototype.onResult = function (aTestRes, aXMLRes) {
    //foo
}

