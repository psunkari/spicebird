var gPageA = null;
var gPageB = null;

// cached data from events
var gTabOpenPageA = null;
var gTabOpenPageB = null;
var gTabOpenCount = 0;
var gTabCloseCount = 0;
var gTabMoveCount = 0;
var gPageLoadCount = 0;

function test() {
  waitForExplicitFinish();

  // nsIFocusManager is not available on MOZILLA_1_9_1
  if ("nsIFocusManager" in Ci) {
    if (Cc["@mozilla.org/focus-manager;1"].getService(Ci.nsIFocusManager)
                                          .activeWindow != window) {
      executeSoon(test);
      window.focus();
      return;
    }
  } else if (!document.hasFocus()) {
    executeSoon(test);
    window.focus();
    return;
  }

  var windows = Application.windows;
  ok(windows, "Check access to browser windows");
  is(windows.length, 1, "There should be one browser window open");

  var activeWin = Application.activeWindow;
  activeWin.events.addListener("TabOpen", onTabOpen);
  activeWin.events.addListener("TabClose", onTabClose);
  activeWin.events.addListener("TabMove", onTabMove);

  gPageA = activeWin.open(makeURI("chrome://mochikit/content/browser/suite/smile/test/ContentA.html"));
  gPageA.events.addListener("load", onPageAFirstLoad);

  is(activeWin.tabs.length, 2, "Checking length of 'Browser.tabs' after opening 1 additional tab");

  function onPageAFirstLoad(event) {
    gPageA.events.removeListener("load", onPageAFirstLoad);
    is(gPageA.uri.spec, event.data.uri.spec, "Checking event browser tab is equal to page A");

    gPageB = activeWin.open(makeURI("chrome://mochikit/content/browser/suite/smile/test/ContentB.html"));
    gPageB.events.addListener("load", delayAfterOpen);
    gPageB.focus();

    is(activeWin.tabs.length, 3, "Checking length of 'Browser.tabs' after opening a second additional tab");
    is(activeWin.activeTab.index, gPageB.index, "Checking 'Browser.activeTab' after setting focus");
  }

  function delayAfterOpen() {
    executeSoon(afterOpen);
  }

  // need to wait for the url's to be refreshed during the load
  function afterOpen(event) {
    gPageB.events.removeListener("load", delayAfterOpen);
    // check actuals
    is(gPageA.uri.spec, "chrome://mochikit/content/browser/suite/smile/test/ContentA.html", "Checking 'BrowserTab.uri' after opening");
    is(gPageB.uri.spec, "chrome://mochikit/content/browser/suite/smile/test/ContentB.html", "Checking 'BrowserTab.uri' after opening");

    // check cached values from TabOpen event
    is(gPageA.uri.spec, gTabOpenPageA.uri.spec, "Checking first browser tab open is equal to page A");
    is(gPageB.uri.spec, gTabOpenPageB.uri.spec, "Checking second browser tab open is equal to page B");
    // check event
    is(gTabOpenCount, 2, "Checking event handler for tab open");

    // test document access
    var test1 = gPageA.document.getElementById("test1");
    ok(test1, "Checking existence of element in content DOM");
    is(test1.innerHTML, "A", "Checking content of element in content DOM");

    // test moving tab
    is(gTabMoveCount, 0, "Checking initial tab move count");

    // move the tab
    gPageA.moveToEnd();
    is(gPageA.index, 2, "Checking index after moving tab");

    // check event
    is(gTabMoveCount, 1, "Checking event handler for tab move");

    let browser = gBrowser.getBrowserAtIndex(gPageB.index);
    browser.addProgressListener({
      onStateChange: function(webProgress, request, stateFlags, status) {
        const complete = Ci.nsIWebProgressListener.STATE_IS_WINDOW +
                         Ci.nsIWebProgressListener.STATE_IS_NETWORK +
                         Ci.nsIWebProgressListener.STATE_STOP;
        if ((stateFlags & complete) == complete) {
          browser.removeProgressListener(this);
          onPageBLoadComplete();
        }
      },

      onLocationChange: function() { return 0; },
      onProgressChange: function() { return 0; },
      onStatusChange: function() { return 0; },
      onSecurityChange: function() { return 0; },
      QueryInterface: function(iid) {
        if (iid.equals(Ci.nsISupportsWeakReference) ||
           iid.equals(Ci.nsIWebProgressListener) ||
           iid.equals(Ci.nsISupports))
           return this;

        throw Components.results.NS_ERROR_NO_INTERFACE;
      }
    });

    // test loading new content with a frame into a tab
    // the event will be checked in onPageBLoadComplete
    gPageB.events.addListener("load", onPageBLoadWithFrames);
    gPageB.load(makeURI("chrome://mochikit/content/browser/suite/smile/test/ContentWithFrames.html"));
  }

  function onPageBLoadWithFrames(event) {
    gPageLoadCount++;
  }

  function onPageBLoadComplete() {
    gPageB.events.removeListener("load", onPageBLoadWithFrames);
    // check page load with frame event
    is(gPageLoadCount, 1, "Checking load count after loading new content with a frame");

    // test loading new content into a tab
    // the event will be checked in onPageASecondLoad
    gPageA.events.addListener("load", onPageASecondLoad);
    gPageA.load(makeURI("chrome://mochikit/content/browser/suite/smile/test/ContentB.html"));
  }

  function onPageASecondLoad(event) {
    gPageA.events.removeListener("load", onPageASecondLoad);
    is(gPageA.uri.spec, "chrome://mochikit/content/browser/suite/smile/test/ContentB.html", "Checking 'BrowserTab.uri' after loading new content");

    // start testing closing tabs
    // the event will be checked in afterClose
    // use executeSoon so the onPageASecondLoad
    // has a chance to finish first
    gPageA.close();
    gPageB.close();

    is(gTabCloseCount, 2, "Checking that tabs closed");
    is(activeWin.tabs.length, 1, "Checking length of 'Browser.tabs' after closing 2 tabs");
    finish();
  }
}

function onTabOpen(event) {
  gTabOpenCount++;

  // cache these values so we can check them later (after loading completes)
  if (gTabOpenCount == 1)
    gTabOpenPageA = event.data;

  if (gTabOpenCount == 2)
    gTabOpenPageB = event.data;
}

function onTabClose(event) {
  gTabCloseCount++;
}

function onTabMove(event) {
  gTabMoveCount++;
}
