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
 * The Original Code is Calendar migration code
 *
 * The Initial Developer of the Original Code is
 *   Joey Minta <jminta@gmail.com>
 * Portions created by the Initial Developer are Copyright (C) 2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Matthew Willis <mattwillis@gmail.com>
 *   Clint Talbert <cmtalbert@myfastmail.com>
 *   Stefan Sitter <ssitter@gmail.com>
 *   Prasad Sunkari <prasad@synovel.com>
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

const SUNBIRD_UID = "{718e30fb-e89b-41dd-9da7-e25a45638b28}";
const FIREFOX_UID = "{ec8030f7-c20a-464f-9b0e-13a3a9e97384}";

//
// The front-end wizard bits.
//
var gMigrateWizard = {
    /**
     * Called from onload of the migrator window.  Takes all of the migrators
     * that were passed in via window.arguments and adds them to checklist. The
     * user can then check these off to migrate the data from those sources.
     */
    loadMigrators: function gmw_load() {
        var listbox = document.getElementById("datasource-list");

        LOG("migrators: " + window.arguments.length);
        for each (var migrator in window.arguments[0]) {
            var listItem = document.createElement("listitem");
            listItem.setAttribute("type", "checkbox");
            listItem.setAttribute("checked", true);
            listItem.setAttribute("label", migrator.title);
            listItem.migrator = migrator;
            listbox.appendChild(listItem);
        }
    },

    /**
     * Called from the second page of the wizard.  Finds all of the migrators
     * that were checked and begins migrating their data.  Also controls the
     * progress dialog so the user can see what is happening. (somewhat)
     */
    migrateChecked: function gmw_migrate() {
        var migrators = [];

        // Get all the checked migrators into an array
        var listbox = document.getElementById("datasource-list");
        for (var i = listbox.childNodes.length-1; i >= 0; i--) {
            LOG("Checking child node: " + listbox.childNodes[i]);
            if (listbox.childNodes[i].getAttribute("checked")) {
                LOG("Adding migrator");
                migrators.push(listbox.childNodes[i].migrator);
            }
        }

        // If no migrators were checked, then we're done
        if (migrators.length == 0) {
            window.close();
        }

        // Don't let the user get away while we're migrating
        //XXX may want to wire this into the 'cancel' function once that's
        //    written
        var wizard = document.getElementById("migration-wizard");
        wizard.canAdvance = false;
        wizard.canRewind = false;

        // We're going to need this for the progress meter's description
        var sbs = Components.classes["@mozilla.org/intl/stringbundle;1"]
                  .getService(Components.interfaces.nsIStringBundleService);
        var props = sbs.createBundle("chrome://calendar/locale/migration.properties");
        var label = document.getElementById("progress-label");
        var meter = document.getElementById("migrate-progressmeter");

        var i = 0;
        // Because some of our migrators involve async code, we need this
        // call-back function so we know when to start the next migrator.
        function getNextMigrator() {
            if (migrators[i]) {
                var mig = migrators[i];

                // Increment i to point to the next migrator
                i++;
                LOG("starting migrator: " + mig.title);
                label.value = props.formatStringFromName("migratingApp",
                                                         [mig.title],
                                                         1);
                meter.value = (i-1)/migrators.length*100;
                mig.args.push(getNextMigrator);

                try {
                    mig.migrate.apply(mig, mig.args);
                } catch (e) {
                    LOG("Failed to migrate: " + mig.title);
                    LOG(e);
                    getNextMigrator();
                }
            } else {
                LOG("migration done");
                wizard.canAdvance = true;
                label.value = props.GetStringFromName("finished");
                meter.value = 100;
                gMigrateWizard.setCanRewindFalse();
            }
         }

        // And get the first migrator
        getNextMigrator();
   },

    /**
     * Makes sure the wizard "back" button can not be pressed.
     */
    setCanRewindFalse: function gmw_finish() {
        document.getElementById('migration-wizard').canRewind = false;
    }
};

//
// The more back-end data detection bits
//


/**
 * A data migrator prototype, holding the information for migration
 *
 * @class
 * @param aTitle    The title of the migrator
 * @param aMigrateFunction    The function to call when migrating
 * @param aArguments          The arguments to pass in.
 */
function dataMigrator(aTitle, aMigrateFunction, aArguments) {
    this.title = aTitle;
    this.migrate = aMigrateFunction;
    this.args = aArguments;
}

var gDataMigrator = {
    mIsLightning: false,
    mIsInFirefox: false,
    mPlatform: null,
    mDirService: null,
    mIoService: null,

    /**
     * Cached getter for the directory service.
     */
    get dirService() {
        if (!this.mDirService) {
            this.mDirService = Components.classes["@mozilla.org/file/directory_service;1"]
                               .getService(Components.interfaces.nsIProperties);
        }
        return this.mDirService;
    },

    /**
     * Cached getter for the IO Service
     * XXX replace with cal.getIOService()
     */
    get ioService() {
        if (!this.mIoService) {
            this.mIoService = Components.classes["@mozilla.org/network/io-service;1"]
                              .getService(Components.interfaces.nsIIOService);
        }
        return this.mIoService;
    },

    /**
     * Gets the value for mIsLightning, and sets it if this.mIsLightning is
     * not initialized. This is used by objects outside gDataMigrator to
     * access the mIsLightning member.
     *
     * XXX replace with !cal.isSunbird()
     */
    isLightning: function is_ltn() {
      return false;
    },

    /**
     * Call to do a general data migration (for a clean profile)  Will run
     * through all of the known migrator-checkers.  These checkers will return
     * an array of valid dataMigrator objects, for each kind of data they find.
     * If there is at least one valid migrator, we'll pop open the migration
     * wizard, otherwise, we'll return silently.
     */
    checkAndMigrate: function gdm_migrate() {
        var xulRuntime = Components.classes["@mozilla.org/xre/app-info;1"]
                         .getService(Components.interfaces.nsIXULRuntime);
        this.mPlatform = xulRuntime.OS.toLowerCase();

        LOG("mPlatform is: " + this.mPlatform);

        var DMs = [];
        var migrators = [this.checkEvolution, this.checkIcal];
        // XXX also define a category and an interface here for pluggability
        for each (var migrator in migrators) {
            var migs = migrator.call(this);
            for each (var dm in migs) {
                DMs.push(dm);
            }
        }

        if (DMs.length == 0) {
            // No migration available
            return;
        }
        LOG("DMs: " + DMs.length);

        var url = "chrome://calendar/content/migration.xul";
#ifdef XP_MACOSX
        var wm = Components.classes["@mozilla.org/appshell/window-mediator;1"]
                           .getService(Components.interfaces.nsIWindowMediator);
        var win = wm.getMostRecentWindow("Calendar:MigrationWizard");
        if (win) {
            win.focus();
        } else {
            openDialog(url, "migration", "centerscreen,chrome,resizable=no,width=500,height=400", DMs);
        }
#else
        openDialog(url, "migration", "modal,centerscreen,chrome,resizable=no,width=500,height=400", DMs);
#endif
    },

    /**
     * Checks to see if Apple's iCal is installed and offers to migrate any data
     * the user has created in it.
     */
    checkIcal: function gdm_ical() {
        LOG("Checking for ical data");

        function icalMigrate(aDataDir, aCallback) {
            aDataDir.append("Sources");
            var dirs = aDataDir.directoryEntries;
            var calManager = getCalendarManager();

            var i = 1;
            while(dirs.hasMoreElements()) {
                var dataDir = dirs.getNext().QueryInterface(Components.interfaces.nsIFile);
                var dataStore = dataDir.clone();
                dataStore.append("corestorage.ics");
                if (!dataStore.exists()) {
                    continue;
                }

                var chars = [];
                var fileStream = Components.classes["@mozilla.org/network/file-input-stream;1"]
                                 .createInstance(Components.interfaces.nsIFileInputStream);

                fileStream.init(dataStore, 0x01, 0444, {});
                var convStream = Components.classes["@mozilla.org/intl/converter-input-stream;1"]
                                 .getService(Components.interfaces.nsIConverterInputStream);
                                 convStream.init(fileStream, 'UTF-8', 0, 0x0000);
                var tmpStr = {};
                var str = "";
                while (convStream.readString(-1, tmpStr)) {
                    str += tmpStr.value;
                }

                // Strip out the timezone definitions, since it makes the file
                // invalid otherwise
                var index = str.indexOf(";TZID=");
                while (index != -1) {
                    var endIndex = str.indexOf(':', index);
                    var otherEnd = str.indexOf(';', index+2);
                    if (otherEnd < endIndex) {
                        endIndex = otherEnd;
                    }
                    var sub = str.substring(index, endIndex);
                    str = str.replace(sub, "", "g");
                    index = str.indexOf(";TZID=");
                }
                var tempFile = gDataMigrator.dirService.get("TmpD", Components.interfaces.nsIFile);
                tempFile.append("icalTemp.ics");
                tempFile.createUnique(Components.interfaces.nsIFile.NORMAL_FILE_TYPE, 0600);
                var tempUri = gDataMigrator.ioService.newFileURI(tempFile);

                var stream = Components.classes["@mozilla.org/network/file-output-stream;1"]
                             .createInstance(Components.interfaces.nsIFileOutputStream);
                stream.init(tempFile, 0x2A, 0600, 0);
                var convStream = Components.classes["@mozilla.org/intl/converter-output-stream;1"]
                                .createInstance(Components.interfaces.nsIConverterOutputStream);
                convStream.init(stream, 'UTF-8', 0, 0x0000);
                convStream.writeString(str);

                var cal = gDataMigrator.importICSToStorage(tempFile);
                cal.name = "iCalendar"+i;
                i++;
                calManager.registerCalendar(cal);
                getCompositeCalendar().addCalendar(cal);
            }
            LOG("icalMig making callback");
            aCallback();
        }
        var profileDir = this.dirService.get("ProfD", Components.interfaces.nsILocalFile);
        var icalSpec = profileDir.path;
        var icalFile;
        if (!this.isLightning()) {
            var diverge = icalSpec.indexOf("Sunbird");
            if (diverge == -1) {
                return [];
            }
            icalSpec = icalSpec.substr(0, diverge);
            icalFile = Components.classes["@mozilla.org/file/local;1"]
                       .createInstance(Components.interfaces.nsILocalFile);
            icalFile.initWithPath(icalSpec);
        } else {
            var diverge = icalSpec.indexOf("Thunderbird");
            if (diverge == -1) {
                return [];
            }
            icalSpec = icalSpec.substr(0, diverge);
            icalFile = Components.classes["@mozilla.org/file/local;1"]
                       .createInstance(Components.interfaces.nsILocalFile);
            icalFile.initWithPath(icalSpec);
            icalFile.append("Application Support");
        }

        icalFile.append("iCal");
        if (icalFile.exists()) {
            return [new dataMigrator("Apple iCal", icalMigrate, [icalFile])];
        }

        return [];
    },

    /**
     * Checks to see if Evolution is installed and offers to migrate any data
     * stored there.
     */
    checkEvolution: function gdm_evolution() {
        function evoMigrate(aDataDir, aCallback) {
            var i = 1;
            function evoDataMigrate(dataStore) {
                LOG("Migrating evolution data file in " + dataStore.path);
                if (dataStore.exists()) {
                    var cal = gDataMigrator.importICSToStorage(dataStore);
                    cal.name = "Evolution " + (i++);
                    calManager.registerCalendar(cal);
                    getCompositeCalendar().addCalendar(cal);
                }
                return dataStore.exists();
            }

            var calManager = getCalendarManager();
            var dirs = aDataDir.directoryEntries;
            while (dirs.hasMoreElements()) {
                var dataDir = dirs.getNext().QueryInterface(Components.interfaces.nsIFile);
                var dataStore = dataDir.clone();
                dataStore.append("calendar.ics");
                evoDataMigrate(dataStore);
            }

            aCallback();
        }

        var evoDir = this.dirService.get("Home", Components.interfaces.nsILocalFile);
        evoDir.append(".evolution");
        evoDir.append("calendar");
        evoDir.append("local");
        return (evoDir.exists() ? [new dataMigrator("Evolution", evoMigrate, [evoDir])] : []);
    },

    /**
     * Creates and registers a storage calendar and imports the given ics file into it.
     *
     * @param icsFile     The nsI(Local)File to import.
     */
    importICSToStorage: function migrateIcsStorage(icsFile) {
        var calManager = getCalendarManager();
        var uris = [];
        for each (var oldCal in calManager.getCalendars({})) {
            uris.push(oldCal.uri.spec);
        }
        var uri = 'moz-profile-calendar://?id=';
        var i = 1;
        while (uris.indexOf(uri+i) != -1) {
            i++;
        }

        var cal = calManager.createCalendar("storage", makeURL(uri+i));
        var icsImporter = Components.classes["@mozilla.org/calendar/import;1?type=ics"]
                          .getService(Components.interfaces.calIImporter);

        var inputStream = Components.classes["@mozilla.org/network/file-input-stream;1"]
                          .createInstance(Components.interfaces.nsIFileInputStream);
        var items = [];

        try {
            inputStream.init(icsFile, MODE_RDONLY, 0444, {});
            items = icsImporter.importFromStream(inputStream, {});
        } catch(ex) {
            switch (ex.result) {
                case Components.interfaces.calIErrors.INVALID_TIMEZONE:
                    showError(calGetString("calendar", "timezoneError", [icsFile.path]));
                    break;
                default:
                    showError(calGetString("calendar", "unableToRead") + icsFile.path + "\n"+ ex);
            }
        } finally {
           inputStream.close();
        }

        // Defined in import-export.js
        putItemsIntoCal(cal, items);

        return cal;
    },

    /**
     * Helper functions for getting the profile directory of various MozApps
     * (Getting the profile dir is way harder than it should be.)
     *
     * Sunbird:
     *     Unix:     ~jdoe/.mozilla/sunbird/
     *     Windows:  %APPDATA%\Mozilla\Sunbird\Profiles
     *     Mac OS X: ~jdoe/Library/Application Support/Sunbird/Profiles
     *
     * Firefox:
     *     Unix:     ~jdoe/.mozilla/firefox/
     *     Windows:  %APPDATA%\Mozilla\Firefox\Profiles
     *     Mac OS X: ~jdoe/Library/Application Support/Firefox/Profiles
     *
     * Thunderbird:
     *     Unix:     ~jdoe/.thunderbird/
     *     Windows:  %APPDATA%\Thunderbird\Profiles
     *     Mac OS X: ~jdoe/Library/Thunderbird/Profiles
     *
     * Spicebird:
     *     Unix:     ~jdoe/.spicebird/
     *     Windows:  %APPDATA%\Spicebird\Profiles
     *     Mac OS X: ~jdoe/Library/Spicebird/Profiles
     *
     * Notice that Firefox and Sunbird follow essentially the same pattern, so
     * we group them with getNormalProfile
     */
    getFirefoxProfile: function gdm_getFF() {
        return this.getNormalProfile("Firefox");
    },

    /**
     * @see getFirefoxProfile
     */
    getThunderbirdProfile: function gdm_getTB() {
        var localFile;
        var profileRoot = this.dirService.get("DefProfRt", Components.interfaces.nsILocalFile);
        LOG("profileRoot = " + profileRoot.path);

        switch (this.mPlatform) {
            case "darwin": // Mac OS X
            case "winnt":
                localFile = profileRoot.parent.parent;
                localFile.append("Thunderbird");
                localFile.append("Profiles");
                break;
            default: // Unix
                localFile = profileRoot.parent;
                localFile.append(".thunderbird");
        }

        LOG("searching for Thunderbird in " + localFile.path);
        return localFile.exists() ? localFile : null;
    },

    /**
     * @see getFirefoxProfile
     */
    getSunbirdProfile: function gdm_getSB() {
        return this.getNormalProfile("Sunbird");
    },

    /**
     * Common function to retrieve the profile directory for a given app.
     * @see getFirefoxProfile
     */
    getNormalProfile: function gdm_getNorm(aAppName) {
        var localFile;
        var profileRoot = this.dirService.get("DefProfRt", Components.interfaces.nsILocalFile);
        LOG("profileRoot = " + profileRoot.path);

        switch (this.mPlatform) {
            case "darwin": // Mac OS X
                localFile = profileRoot.parent.parent;
                localFile.append("Application Support");
                localFile.append(aAppName);
                localFile.append("Profiles");
                break;
            case "winnt":
                localFile = profileRoot.parent.parent;
                localFile.append("Mozilla");
                localFile.append(aAppName);
                localFile.append("Profiles");
                break;
            default: // Unix
                localFile = profileRoot.parent;
                localFile.append(".mozilla");
                localFile.append(aAppName.toLowerCase());
                break;
        }

        LOG("searching for " + aAppName + " in " + localFile.path);
        return localFile.exists() ? localFile : null;
    }
};

/**
 * logs to system and error console, depending on the calendar.migration.log
 * preference.
 *
 * XXX Consolidate with calUtils' LOG().
 *
 * @param aString   The string to log
 */
function LOG(aString) {
    if (!getPrefSafe("calendar.migration.log", false)) {
        return;
    }
    var consoleService = Components.classes["@mozilla.org/consoleservice;1"]
                         .getService(Components.interfaces.nsIConsoleService);
    consoleService.logStringMessage(aString);
    dump(aString+"\n");
}
