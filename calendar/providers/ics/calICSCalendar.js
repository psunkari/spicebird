/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla calendar code.
 *
 * The Initial Developer of the Original Code is
 *   Michiel van Leeuwen <mvl@exedo.nl>
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Vladimir Vukicevic <vladimir.vukicevic@oracle.com>
 *   Dan Mosedale <dan.mosedale@oracle.com>
 *   Joey Minta <jminta@gmail.com>
 *   Philipp Kewisch <mozilla@kewis.ch>
 *   Daniel Boelzle <daniel.boelzle@sun.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

Components.utils.import("resource://calendar/modules/calProviderUtils.jsm");

//
// calICSCalendar.js
//
// This is a non-sync ics file. It reads the file pointer to by uri when set,
// then writes it on updates. External changes to the file will be
// ignored and overwritten.
//
// XXX Should do locks, so that external changes are not overwritten.

const CI = Components.interfaces;
const calIOperationListener = Components.interfaces.calIOperationListener;
const calICalendar = Components.interfaces.calICalendar;
const calIErrors = Components.interfaces.calIErrors;

function calICSCalendar() {
    this.initProviderBase();
    this.initICSCalendar();

    this.unmappedComponents = [];
    this.unmappedProperties = [];
    this.queue = new Array();
    this.mModificationActions = [];
}

calICSCalendar.prototype = {
    __proto__: cal.ProviderBase.prototype,

    mObserver: null,
    locked: false,

    QueryInterface: function (aIID) {
        return doQueryInterface(this, calICSCalendar.prototype, aIID,
                                [Components.interfaces.calICalendarProvider,
                                 Components.interfaces.nsIStreamListener,
                                 Components.interfaces.nsIStreamLoaderObserver,
                                 Components.interfaces.nsIChannelEventSink,
                                 Components.interfaces.nsIInterfaceRequestor]);
    },
    
    initICSCalendar: function() {
        this.mMemoryCalendar = Components.classes["@mozilla.org/calendar/calendar;1?type=memory"]
                                         .createInstance(Components.interfaces.calICalendar);

        this.mMemoryCalendar.superCalendar = this;
        this.mObserver = new calICSObserver(this);
        this.mMemoryCalendar.addObserver(this.mObserver); // XXX Not removed
    },

    //
    // calICalendarProvider interface
    //
    get prefChromeOverlay() {
        return null;
    },

    get displayName() {
        return calGetString("calendar", "icsName");
    },

    createCalendar: function ics_createCal() {
        throw NS_ERROR_NOT_IMPLEMENTED;
    },

    deleteCalendar: function ics_deleteCal(cal, listener) {
        throw NS_ERROR_NOT_IMPLEMENTED;
    },

    //
    // calICalendar interface
    //
    get type() { return "ics"; },

    get canRefresh() {
        return true;
    },

    get uri() { return this.mUri },
    set uri(aUri) {
        this.mUri = aUri;
        this.mMemoryCalendar.uri = this.mUri;

        // Use the ioservice, to create a channel, which makes finding the
        // right hooks to use easier.
        var ioService = Components.classes["@mozilla.org/network/io-service;1"]
                                  .getService(Components.interfaces.nsIIOService);
        var channel = ioService.newChannelFromURI(this.mUri);

        if (calInstanceOf(channel, Components.interfaces.nsIHttpChannel)) {
            this.mHooks = new httpHooks();
        } else if (calInstanceOf(channel, Components.interfaces.nsIFileChannel)) {
            this.mHooks = new fileHooks();
        } else {
            this.mHooks = new dummyHooks();
        }
    },

    getProperty: function calICSCalendar_getProperty(aName) {
        switch (aName) {
            case "requiresNetwork":
                return (!this.uri.schemeIs("file"));
        }
        return this.__proto__.__proto__.getProperty.apply(this, arguments);
    },

    refresh: function calICSCalendar_refresh() {
        this.queue.push({action: 'refresh'});
        this.processQueue();
    },

    prepareChannel: function calICSCalendar_prepareChannel(aChannel) {
        aChannel.loadFlags |= Components.interfaces.nsIRequest.LOAD_BYPASS_CACHE;
        aChannel.notificationCallbacks = this;

        // Allow the hook to do its work, like a performing a quick check to
        // see if the remote file really changed. Might save a lot of time
        this.mHooks.onBeforeGet(aChannel);
    },

    doRefresh: function calICSCalendar_doRefresh() {
        var ioService = Components.classes["@mozilla.org/network/io-service;1"]
                                  .getService(Components.interfaces.nsIIOService);

        var channel = ioService.newChannelFromURI(this.mUri);
        this.prepareChannel(channel);

        var streamLoader = Components.classes["@mozilla.org/network/stream-loader;1"]
                                     .createInstance(Components.interfaces.nsIStreamLoader);

        // Lock other changes to the item list.
        this.lock();

        try {
            streamLoader.init(this);
            channel.asyncOpen(streamLoader, this);
        } catch(e) {
            // File not found: a new calendar. No problem.
            this.unlock();
        }
    },

    // nsIChannelEventSink implementation
    onChannelRedirect: function(aOldChannel, aNewChannel, aFlags) {
        this.prepareChannel(aNewChannel);
    },

    // nsIStreamLoaderObserver impl
    // Listener for download. Parse the downloaded file

    onStreamComplete: function(loader, ctxt, status, resultLength, result)
    {
        // No need to do anything if there was no result
        if (!resultLength) {
            this.unlock();
            return;
        }
        
        // Allow the hook to get needed data (like an etag) of the channel
        var cont = this.mHooks.onAfterGet();
        if (!cont) {
            this.unlock();
            return;
        }

        // This conversion is needed, because the stream only knows about
        // byte arrays, not about strings or encodings. The array of bytes
        // need to be interpreted as utf8 and put into a javascript string.
        var unicodeConverter = Components.classes["@mozilla.org/intl/scriptableunicodeconverter"]
                                         .createInstance(Components.interfaces.nsIScriptableUnicodeConverter);
        // ics files are always utf8
        unicodeConverter.charset = "UTF-8";
        var str;
        try {
            str = unicodeConverter.convertFromByteArray(result, result.length);
        } catch(e) {
            this.mObserver.onError(this.superCalendar, calIErrors.CAL_UTF8_DECODING_FAILED, e.toString());
            this.mObserver.onError(this.superCalendar, calIErrors.READ_FAILED, "");
            this.unlock();
            return;
        }

        // Create a new calendar, to get rid of all the old events
        // Don't forget to remove the observer
        this.mMemoryCalendar.removeObserver(this.mObserver);
        this.mMemoryCalendar = Components.classes["@mozilla.org/calendar/calendar;1?type=memory"]
                                         .createInstance(Components.interfaces.calICalendar);
        this.mMemoryCalendar.uri = this.mUri;
        this.mMemoryCalendar.superCalendar = this;

        this.mObserver.onStartBatch();

        // Wrap parsing in a try block. Will ignore errors. That's a good thing
        // for non-existing or empty files, but not good for invalid files.
        // That's why we put them in readOnly mode
        let parser = Components.classes["@mozilla.org/calendar/ics-parser;1"]
                               .createInstance(Components.interfaces.calIIcsParser);
        let this_ = this;
        let listener = { // calIIcsParsingListener
            onParsingComplete: function ics_onParsingComplete(rc, parser_) {
                try {
                    for each (let item in parser_.getItems({})) {
                        this_.mMemoryCalendar.adoptItem(item, null);
                    }
                    this_.unmappedComponents = parser_.getComponents({});
                    this_.unmappedProperties = parser_.getProperties({});
                } catch (exc) {
                    cal.LOG("Parsing the file failed: " + exc);
                    this_.mObserver.onError(this_.superCalendar, exc.result, exc.toString());
                    this_.mObserver.onError(this_.superCalendar, calIErrors.READ_FAILED, "");
                }
                this_.mObserver.onEndBatch();
                this_.mObserver.onLoad(this_);

                // Now that all items have been stuffed into the memory calendar
                // we should add ourselves as observer. It is important that this
                // happens *after* the calls to adoptItem in the above loop to prevent
                // the views from being notified.
                this_.mMemoryCalendar.addObserver(this_.mObserver);
                this_.unlock();
            }
        };
        parser.parseString(str, null, listener);
    },

    writeICS: function () {
        this.lock();
        try {
            if (!this.mUri)
                throw Components.results.NS_ERROR_FAILURE;
            // makeBackup will call doWriteICS
            this.makeBackup(this.doWriteICS);
        } catch (exc) {
            this.unlock(calIErrors.MODIFICATION_FAILED);
            throw exc;
        }
    },

    doWriteICS: function () {
        var savedthis = this;
        var appStartup = Components.classes["@mozilla.org/toolkit/app-startup;1"]
                                   .getService(Components.interfaces.nsIAppStartup);
        var listener =
        {
            serializer: null,
            onOperationComplete: function(aCalendar, aStatus, aOperationType, aId, aDetail)
            {
                var inLastWindowClosingSurvivalArea = false;
                try  {
                    // All events are returned. Now set up a channel and a
                    // streamloader to upload.  onStopRequest will be called
                    // once the write has finished
                    var ioService = Components.classes
                        ["@mozilla.org/network/io-service;1"]
                        .getService(Components.interfaces.nsIIOService);
                    var channel = ioService.newChannelFromURI(savedthis.mUri);

                    // Allow the hook to add things to the channel, like a
                    // header that checks etags
                    var notChanged = savedthis.mHooks.onBeforePut(channel);
                    if (notChanged) {
                        channel.notificationCallbacks = savedthis;
                        var uploadChannel = channel.QueryInterface(
                            Components.interfaces.nsIUploadChannel);

                        // Serialize
                        var icsStream = this.serializer.serializeToInputStream();

                        // Upload
                        uploadChannel.setUploadStream(icsStream,
                                                    "text/calendar", -1);

                        appStartup.enterLastWindowClosingSurvivalArea();
                        inLastWindowClosingSurvivalArea = true;
                        channel.asyncOpen(savedthis, savedthis);
                    } else {
                        if (inLastWindowClosingSurvivalArea) {
                            appStartup.exitLastWindowClosingSurvivalArea();
                        }
                        savedthis.mObserver.onError(savedthis.superCalendar,
                                                    calIErrors.MODIFICATION_FAILED,
                                                    "The calendar has been changed remotely. Please reload and apply your changes again!");
                        savedthis.unlock(calIErrors.MODIFICATION_FAILED);
                    }
                } catch (ex) {
                    if (inLastWindowClosingSurvivalArea) {
                        appStartup.exitLastWindowClosingSurvivalArea();
                    }
                    savedthis.mObserver.onError(savedthis.superCalendar,
                                                ex.result, "The calendar could not be saved; there " +
                                                "was a failure: 0x" + ex.result.toString(16));
                    savedthis.mObserver.onError(savedthis.superCalendar, calIErrors.MODIFICATION_FAILED, "");
                    savedthis.unlock(calIErrors.MODIFICATION_FAILED);
                }
            },
            onGetResult: function(aCalendar, aStatus, aItemType, aDetail, aCount, aItems)
            {
                this.serializer.addItems(aItems, aCount);
            }
        };
        listener.serializer = Components.classes["@mozilla.org/calendar/ics-serializer;1"].
                                         createInstance(Components.interfaces.calIIcsSerializer);
        for each (let comp in this.unmappedComponents) {
            listener.serializer.addComponent(comp);
        }
        for each (let prop in this.unmappedProperties) {
            switch (prop.propertyName) {
                // we always set the current name and timezone:
                case "X-WR-CALNAME":
                case "X-WR-TIMEZONE":
                    break;
                default:
                    listener.serializer.addProperty(prop);
                    break;
            }
        }
        let prop = cal.getIcsService().createIcalProperty("X-WR-CALNAME");
        prop.value = this.name;
        listener.serializer.addProperty(prop);
        prop = cal.getIcsService().createIcalProperty("X-WR-TIMEZONE");
        prop.value = cal.getTimezoneService().defaultTimezone.tzid;
        listener.serializer.addProperty(prop);

        // don't call this.getItems, because we are locked:
        this.mMemoryCalendar.getItems(calICalendar.ITEM_FILTER_TYPE_ALL | calICalendar.ITEM_FILTER_COMPLETED_ALL,
                                      0, null, null, listener);
    },

    // nsIStreamListener impl
    // For after publishing. Do error checks here
    onStartRequest: function(request, ctxt) {},
    onDataAvailable: function(request, ctxt, inStream, sourceOffset, count) {
         // All data must be consumed. For an upload channel, there is
         // no meaningfull data. So it gets read and then ignored
         var scriptableInputStream = 
             Components.classes["@mozilla.org/scriptableinputstream;1"]
                       .createInstance(Components.interfaces.nsIScriptableInputStream);
         scriptableInputStream.init(inStream);
         scriptableInputStream.read(-1);
    },
    onStopRequest: function(request, ctxt, status, errorMsg)
    {
        ctxt = ctxt.wrappedJSObject;
        var channel;
        try {
            channel = request.QueryInterface(Components.interfaces.nsIHttpChannel);
            LOG("calICSCalendar channel.requestSucceeded: " + channel.requestSucceeded);
        } catch(e) {
        }

        let appStartup = Components.classes["@mozilla.org/toolkit/app-startup;1"]
                                   .getService(Components.interfaces.nsIAppStartup);

        if ((channel && !channel.requestSucceeded) ||
            (!channel && !Components.isSuccessCode(request.status))) {
            ctxt.mObserver.onError(this.superCalendar,
                                   Components.isSuccessCode(request.status)
                                   ? calIErrors.DAV_PUT_ERROR
                                   : request.status,
                                   "Publishing the calendar file failed\n" +
                                       "Status code: "+request.status.toString(16)+"\n");
            ctxt.mObserver.onError(this.superCalendar, calIErrors.MODIFICATION_FAILED, "");

            // the PUT has failed, refresh, and signal error to all modifying operations:
            this.refresh();
            ctxt.unlock(calIErrors.MODIFICATION_FAILED);
            appStartup.exitLastWindowClosingSurvivalArea();
            return;
        }

        // Allow the hook to grab data of the channel, like the new etag
        ctxt.mHooks.onAfterPut(channel,
                               function() {
                                   ctxt.unlock();
                                   appStartup.exitLastWindowClosingSurvivalArea();
                               });
    },

    // Always use the queue, just to reduce the amount of places where
    // this.mMemoryCalendar.addItem() and friends are called. less
    // copied code.
    addItem: function (aItem, aListener) {
        this.adoptItem(aItem.clone(), aListener);
    },
    adoptItem: function (aItem, aListener) {
        if (this.readOnly) 
            throw calIErrors.CAL_IS_READONLY;
        this.queue.push({action:'add', item:aItem, listener:aListener});
        this.processQueue();
    },

    modifyItem: function (aNewItem, aOldItem, aListener) {
        if (this.readOnly) 
            throw calIErrors.CAL_IS_READONLY;
        this.queue.push({action:'modify', oldItem: aOldItem,
                         newItem: aNewItem, listener:aListener});
        this.processQueue();
    },

    deleteItem: function (aItem, aListener) {
        if (this.readOnly) 
            throw calIErrors.CAL_IS_READONLY;
        this.queue.push({action:'delete', item:aItem, listener:aListener});
        this.processQueue();
    },

    getItem: function (aId, aListener) {
        this.queue.push({action:'get_item', id:aId, listener:aListener});
        this.processQueue();
    },

    getItems: function (aItemFilter, aCount,
                        aRangeStart, aRangeEnd, aListener)
    {
        this.queue.push({action:'get_items',
                         itemFilter:aItemFilter, count:aCount,
                         rangeStart:aRangeStart, rangeEnd:aRangeEnd,
                         listener:aListener});
        this.processQueue();
    },

    processQueue: function ()
    {
        if (this.isLocked())
            return;

        function modListener(action) {
            this.mAction = action;
        }
        modListener.prototype = {
            onGetResult: function() {},
            onOperationComplete: function() {
                this.mAction.opCompleteArgs = arguments;
            }
        };

        var a;
        var writeICS = false;
        var refreshAction = null;
        while ((a = this.queue.shift())) {
            switch (a.action) {
                case 'add':
                    this.mMemoryCalendar.addItem(a.item, new modListener(a));
                    this.mModificationActions.push(a);
                    writeICS = true;
                    break;
                case 'modify':
                    this.mMemoryCalendar.modifyItem(a.newItem, a.oldItem, new modListener(a));
                    this.mModificationActions.push(a);
                    writeICS = true;
                    break;
                case 'delete':
                    this.mMemoryCalendar.deleteItem(a.item, new modListener(a));
                    this.mModificationActions.push(a);
                    writeICS = true;
                    break;
                case 'get_item':
                    this.mMemoryCalendar.getItem(a.id, a.listener);
                    break;
                case 'get_items':
                    this.mMemoryCalendar.getItems(a.itemFilter, a.count,
                                                  a.rangeStart, a.rangeEnd,
                                                  a.listener);
                    break;
                case 'refresh':
                    refreshAction = a;
                    break;
            }
            if (refreshAction) {
                // break queue processing here and wait for refresh to finish
                // before processing further operations
                break;
            }
        }
        if (writeICS) {
            if (refreshAction) {
                // reschedule the refresh for next round, after the file has been written;
                // strictly we may not need to refresh once the file has been successfully
                // written, but we don't know if that write will succeed.
                this.queue.unshift(refreshAction);
            }
            this.writeICS();
        }
        else if (refreshAction) {
            this.doRefresh();
        }
    },

    lock: function () {
        this.locked = true;
    },

    unlock: function (errCode) {
        ASSERT(this.locked, "unexpected!");

        this.mModificationActions.forEach(
            function(action) {
                let args = action.opCompleteArgs;
                ASSERT(args, "missing onOperationComplete call!");
                let listener = action.listener;
                if (listener) {
                    if (Components.isSuccessCode(args[1]) &&
                        errCode && !Components.isSuccessCode(errCode)) {
                        listener.onOperationComplete(args[0], errCode, args[2], args[3], null);
                    } else {
                        listener.onOperationComplete.apply(listener, args);
                    }
                }
            });
        this.mModificationActions = [];

        this.locked = false;
        this.processQueue();
    },
    
    isLocked: function () {
        return this.locked;
    },

    startBatch: function ()
    {
        this.mObserver.onStartBatch();
    },
    endBatch: function ()
    {
        this.mObserver.onEndBatch();
    },

    /**
     * @see nsIInterfaceRequestor
     * @see calProviderUtils.jsm
     */
    getInterface: cal.InterfaceRequestor_getInterface,

    /**
     * Make a backup of the (remote) calendar
     *
     * This will download the remote file into the profile dir.
     * It should be called before every upload, so every change can be
     * restored. By default, it will keep 3 backups. It also keeps one
     * file each day, for 3 days. That way, even if the user doesn't notice
     * the remote calendar has become corrupted, he will still loose max 1
     * day of work.
     * After the back up is finished, will call aCallback.
     *
     * @param aCallback
     *           Function that will be calles after the backup is finished.
     *           will be called in the original context in which makeBackup
     *           was called
     */
    makeBackup: function(aCallback) {
        // Uses |pseudoID|, an id of the calendar, defined below
        function makeName(type) {
            return 'calBackupData_'+pseudoID+'_'+type+'.ics';
        }
        
        // This is a bit messy. createUnique creates an empty file,
        // but we don't use that file. All we want is a filename, to be used
        // in the call to copyTo later. So we create a file, get the filename,
        // and never use the file again, but write over it.
        // Using createUnique anyway, because I don't feel like 
        // re-implementing it
        function makeDailyFileName() {
            var dailyBackupFile = backupDir.clone();
            dailyBackupFile.append(makeName('day'));
            dailyBackupFile.createUnique(CI.nsIFile.NORMAL_FILE_TYPE, 0600);
            dailyBackupFileName = dailyBackupFile.leafName;

            // Remove the reference to the nsIFile, because we need to
            // write over the file later, and you never know what happens
            // if something still has a reference.
            // Also makes it explicit that we don't need the file itself,
            // just the name.
            dailyBackupFile = null;

            return dailyBackupFileName;
        }

        function purgeBackupsByType(files, type) {
            // filter out backups of the type we care about.
            var filteredFiles = files.filter(
                function f(v) { 
                    return (v.name.indexOf("calBackupData_"+pseudoID+"_"+type) != -1)
                });
            // Sort by lastmodifed
            filteredFiles.sort(
                function s(a,b) {
                    return (a.lastmodified - b.lastmodified);
                });
            // And delete the oldest files, and keep the desired number of
            // old backups
            var i;
            for (i = 0; i < filteredFiles.length - numBackupFiles; ++i) {
                let file = backupDir.clone();
                file.append(filteredFiles[i].name);

                // This can fail because of some crappy code in nsILocalFile.
                // That's not the end of the world.  We can try to remove the
                // file the next time around.
                try {
                    file.remove(false);
                } catch(ex) {}
            }
            return;
        }

        function purgeOldBackups() {
            // Enumerate files in the backupdir for expiry of old backups
            var dirEnum = backupDir.directoryEntries;
            var files = [];
            while (dirEnum.hasMoreElements()) {
                var file = dirEnum.getNext().QueryInterface(CI.nsIFile);
                if (file.isFile()) {
                    files.push({name: file.leafName, lastmodified: file.lastModifiedTime});
                }
            }

            if (doDailyBackup)
                purgeBackupsByType(files, 'day');
            else
                purgeBackupsByType(files, 'edit');

            return;
        }
        
        function copyToOverwriting(oldFile, newParentDir, newName) {
            try {
                var newFile = newParentDir.clone();
                newFile.append(newName);
            
                if (newFile.exists()) {
                    newFile.remove(false);
                }
                oldFile.copyTo(newParentDir, newName);
            } catch(e) {
                Components.utils.reportError("Backup failed, no copy:"+e);
                // Error in making a daily/initial backup.
                // not fatal, so just continue
            }
        }

        var backupDays = getPrefSafe("calendar.backup.days", 1);
        var numBackupFiles = getPrefSafe("calendar.backup.filenum", 3);

        try {
            var backupDir = cal.getCalendarDirectory();
            backupDir.append("backup");
            if (!backupDir.exists()) {
                backupDir.create(CI.nsIFile.DIRECTORY_TYPE, 0755);
            }
        } catch(e) {
            // Backup dir wasn't found. Likely because we are running in
            // xpcshell. Don't die, but continue the upload.
            LOG("Backup failed, no backupdir:"+e);
            aCallback.call(this);
            return;
        }

        try {
            var pseudoID = this.getProperty("uniquenum");
            if (!pseudoID) {
                pseudoID = new Date().getTime();
                this.setProperty("uniquenum", pseudoID);
            }
        } catch(e) {
            // calendarmgr not found. Likely because we are running in
            // xpcshell. Don't die, but continue the upload.
            LOG("Backup failed, no calendarmanager:"+e);
            aCallback.call(this);
            return;
        }

        var doInitialBackup = false;
        var initialBackupFile = backupDir.clone();
        initialBackupFile.append(makeName('initial'));
        if (!initialBackupFile.exists())
            doInitialBackup = true;

        var doDailyBackup = false;
        var backupTime = this.getProperty('backup-time');
        if (!backupTime ||
            (new Date().getTime() > backupTime + backupDays*24*60*60*1000)) {
            // It's time do to a daily backup
            doDailyBackup = true;
            this.setProperty('backup-time', new Date().getTime());
        }

        var dailyBackupFileName;
        if (doDailyBackup) {
            dailyBackupFileName = makeDailyFileName(backupDir);
        }

        var backupFile = backupDir.clone();
        backupFile.append(makeName('edit'));
        backupFile.createUnique(CI.nsIFile.NORMAL_FILE_TYPE, 0600);
        
        purgeOldBackups();

        // Now go download the remote file, and store it somewhere local.
        var ioService = Components.classes["@mozilla.org/network/io-service;1"]
                                  .getService(CI.nsIIOService);
        var channel = ioService.newChannelFromURI(this.mUri);
        channel.loadFlags |= Components.interfaces.nsIRequest.LOAD_BYPASS_CACHE;
        channel.notificationCallbacks = this;

        var downloader = Components.classes["@mozilla.org/network/downloader;1"]
                                   .createInstance(CI.nsIDownloader);

        var savedthis = this;
        var listener = {
            onDownloadComplete: function(downloader, request, ctxt, status, result) {
                if (doInitialBackup)
                    copyToOverwriting(result, backupDir, makeName('initial'));
                if (doDailyBackup)
                    copyToOverwriting(result, backupDir, dailyBackupFileName);

                aCallback.call(savedthis);
            }
        }

        downloader.init(listener, backupFile);
        try {
            channel.asyncOpen(downloader, null);
        } catch(e) {
            // For local files, asyncOpen throws on new (calendar) files
            // No problem, go and upload something
            LOG("Backup failed in asyncOpen:"+e);
            aCallback.call(this);
            return;
        }

        return;
    }
};

function calICSObserver(aCalendar) {
    this.mCalendar = aCalendar;
}

calICSObserver.prototype = {
    mCalendar: null,
    mInBatch: false,

    // calIObserver:
    onStartBatch: function() {
        this.mCalendar.observers.notify("onStartBatch");
        this.mInBatch = true;
    },
    onEndBatch: function() {
        this.mCalendar.observers.notify("onEndBatch");
        this.mInBatch = false;
    },
    onLoad: function(calendar) {
        this.mCalendar.observers.notify("onLoad", [calendar]);
    },
    onAddItem: function(aItem) {
        this.mCalendar.observers.notify("onAddItem", [aItem]);
    },
    onModifyItem: function(aNewItem, aOldItem) {
        this.mCalendar.observers.notify("onModifyItem", [aNewItem, aOldItem]);
    },
    onDeleteItem: function(aDeletedItem) {
        this.mCalendar.observers.notify("onDeleteItem", [aDeletedItem]);
    },
    onPropertyChanged: function(aCalendar, aName, aValue, aOldValue) {
        this.mCalendar.observers.notify("onPropertyChanged", [aCalendar, aName, aValue, aOldValue]);
    },
    onPropertyDeleting: function(aCalendar, aName) {
        this.mCalendar.observers.notify("onPropertyDeleting", [aCalendar, aName]);
    },

    onError: function(aCalendar, aErrNo, aMessage) {
        this.mCalendar.readOnly = true;
        this.mCalendar.notifyError(aErrNo, aMessage);
    }
};

/***************************
 * Transport Abstraction Hooks
 *
 * Those hooks provide a way to do checks before or after publishing an
 * ics file. The main use will be to check etags (or some other way to check
 * for remote changes) to protect remote changes from being overwritten.
 *
 * Different protocols need different checks (webdav can do etag, but
 * local files need last-modified stamps), hence different hooks for each
 * types
 */

// dummyHooks are for transport types that don't have hooks of their own.
// Also serves as poor-mans interface definition.
function dummyHooks() {
}

dummyHooks.prototype = {
    onBeforeGet: function(aChannel) {
        return true;
    },
    
    /**
     * @return
     *     a boolean, false if the previous data should be used (the datastore
     *     didn't change, there might be no data in this GET), true in all
     *     other cases
     */
    onAfterGet: function() {
        return true;
    },

    onBeforePut: function(aChannel) {
        return true;
    },
    
    onAfterPut: function(aChannel, aRespFunc) {
        aRespFunc();
        return true;
    }
};

function httpHooks() {
    this.mChannel = null;
}

httpHooks.prototype = {
    onBeforeGet: function(aChannel) {
        this.mChannel = aChannel;
        if (this.mEtag) {
            var httpchannel = aChannel.QueryInterface(Components.interfaces.nsIHttpChannel);
            // Somehow the webdav header 'If' doesn't work on apache when
            // passing in a Not, so use the http version here.
            httpchannel.setRequestHeader("If-None-Match", this.mEtag, false);
        }

        return true;
    },
    
    onAfterGet: function() {
        var httpchannel = this.mChannel.QueryInterface(Components.interfaces.nsIHttpChannel);

        // 304: Not Modified
        // Can use the old data, so tell the caller that it can skip parsing.
        if (httpchannel.responseStatus == 304)
            return false;

        // 404: Not Found
        // This is a new calendar. Shouldn't try to parse it. But it also
        // isn't a failure, so don't throw.
        if (httpchannel.responseStatus == 404)
            return false;

        try {
            this.mEtag = httpchannel.getResponseHeader("ETag");
        } catch(e) {
            // No etag header. Now what?
            this.mEtag = null;
        }
        this.mChannel = null;
        return true;
    },

    onBeforePut: function(aChannel) {
        if (this.mEtag) {
            var httpchannel = aChannel.QueryInterface(Components.interfaces.nsIHttpChannel);

            // Apache doesn't work correctly with if-match on a PUT method,
            // so use the webdav header
            httpchannel.setRequestHeader("If", '(['+this.mEtag+'])', false);
        }
        return true;
    },
    
    onAfterPut: function(aChannel, aRespFunc) {
        var httpchannel = aChannel.QueryInterface(Components.interfaces.nsIHttpChannel);
        try {
            this.mEtag = httpchannel.getResponseHeader("ETag");
            aRespFunc();
        } catch(e) {
            // There was no ETag header on the response. This means that
            // putting is not atomic. This is bad. Race conditions can happen,
            // because there is a time in which we don't know the right
            // etag.
            // Try to do the best we can, by immediatly getting the etag.

            var etagListener = {};
            var thisCalendar = this; // need to reference in callback

            etagListener.onStreamComplete =
                function ics_etLoSC(aLoader, aContext, aStatus, aResultLength,
                                    aResult) {
                var resultConverter = Components.classes["@mozilla.org/intl/scriptableunicodeconverter"]
                                                .createInstance(Components
                                                .interfaces.nsIScriptableUnicodeConverter);
                resultConverter.charset = "UTF-8";

                var str;
                try {
                    str = resultConverter.convertFromByteArray(aResult, aResultLength);
                } catch (e) {
                    LOG("Failed to fetch channel etag");
                }
                var multistatus = cal.safeNewXML(str);
                try {
                    thisCalendar.mEtag = multistatus..D::getetag;
                } catch (e) {
                    thisCalendar.mEtag = null;
                }
                aRespFunc();
            }
            var D = new Namespace("D", "DAV:");
            default xml namespace = D;
            var queryXml = <D:propfind xmlns:D="DAV:">
                    <D:prop>
                      <D:getetag/>
                    </D:prop>
                  </D:propfind>;

            let etagChannel = cal.prepHttpChannel(aChannel.URI, queryXml,
                                                  "text/xml; charset=utf-8",
                                                  this);
            etagChannel.setRequestHeader("Depth", "0", false);
            etagChannel.requestMethod = "PROPFIND";
            var streamLoader = Components.classes["@mozilla.org/network/stream-loader;1"]
                                         .createInstance(Components.interfaces
                                         .nsIStreamLoader);

            cal.sendHttpRequest(streamLoader, etagChannel, etagListener);
        }
        return true;
    },

    // nsIProgressEventSink
    onProgress: function onProgress(aRequest, aContext, aProgress, aProgressMax) {},
    onStatus: function onStatus(aRequest, aContext, aStatus, aStatusArg) {},

    getInterface: function(aIid) {
        if (aIid.equals(Components.interfaces.nsIProgressEventSink)) {
            return this;
        } else {    
            throw Components.results.NS_ERROR_NO_INTERFACE;
        }
    }
};

function fileHooks() {
    this.mChannel = null;
}

fileHooks.prototype = {
    onBeforeGet: function fH_onBeforeGet(aChannel) {
        this.mChannel = aChannel;
        let fileChannel = this.mChannel.QueryInterface(Components.interfaces.nsIFileChannel);
        return true;
    },

    /**
     * @return
     *     a boolean, false if the previous data should be used (the datastore
     *     didn't change, there might be no data in this GET), true in all
     *     other cases
     */
    onAfterGet: function fH_onAfterGet() {
        let filechannel = this.mChannel.QueryInterface(Components.interfaces.nsIFileChannel);
        if (this.mtime) {
            let newMtime = filechannel.file.lastModifiedTime;
            if (this.mtime == newMtime) {
                return false;
            } else {
                this.mtime = newMtime;
                return true;
            }
        } else {
            this.mtime = filechannel.file.lastModifiedTime;
        return true;
        }
    },

    onBeforePut: function fH_onBeforePut(aChannel) {
        let filechannel = aChannel.QueryInterface(Components.interfaces.nsIFileChannel);
        if (this.mtime && this.mtime != filechannel.file.lastModifiedTime) {
            return false;
        } else {
            return true;
        }
    },

    onAfterPut: function fH_onAfterPut(aChannel, aRespFunc) {
        let filechannel = this.mChannel.QueryInterface(Components.interfaces.nsIFileChannel);
        this.mtime = filechannel.file.lastModifiedTime;
        aRespFunc();
        return true;
    }
};
