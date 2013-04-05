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
 * The Original Code is Synovel Software code.
 * Initial developer of the original code is
 *  Sunil Mohan Adapa <sunil@synovel.com>
 *
 * The Initial Developer of the Original Code is Synovel Software.
 * Portions created by the Initial Developer are Copyright (C) 2007
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Ashok <ashok@synovel.com>
 *  Sivakrishna Edpuganti <sivakrishna@synovel.com>
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
/* -*- Mode: javascript; tab-width: 20; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/* 

Features:
========
* Matches many date and time formats
* All pattern strings are separate from the main code 
  allowing easy extension and localisation
* returns all events in the text
* simple merging of events
* automated testing with a lot of test cases
* doesn't match invalid dates
* sliding window century detection
* today, tomorrow etc.
* am/pm
* various separators
* nd,rd,th,st
* o'clock,
* Hrs/Hours
* Ignore past events
* set context date and current date
* only week days
* dates with week days

TODO:
====

- Handle next previous months
- Handle next previous year
- Handle evening/night etc.
- Handle abbreviated generic timezones like IST
- Handle full generic timezones like Indian Standard Time
- Handle 3.5 getting detected
- Omit headers
- Parse headers
- Handle replied messages' context date
- Handle word boundaries properly

*/


/***********************************************************
* constants
***********************************************************/

const csIEventFilter = Components.interfaces.csIEventFilter;
const nsISupports = Components.interfaces.nsISupports;

// UUID uniquely identifying our component
const CLASS_ID = Components.ID("{58a9123f-980e-4516-9a9d-90078a171efc}");

// description
const CLASS_NAME = "Component that detects calendar events in a given text";

// textual unique identifier
const CONTRACT_ID = "@synovel.com/collab/calendar/event-filter;1";

const USEC_PER_MSEC = 1000;

/***********************************************************
* class definition
***********************************************************/

// Class constructor
function csEventFilter() {
  this.messenger = Components.classes['@mozilla.org/messenger;1']
            .createInstance(Components.interfaces.nsIMessenger);
};

// class definition
csEventFilter.prototype = {

    mPatterns: new Array (
        // See man 3 strftime
        // Date basics
        "%a", "L", "sun|mon|tue|wed|thu|fri|sat",
        "%A", "L", "sunday|monday|tuesday|wednesday|thursday|friday|saturday",
        "%b", "L", "jan|feb|mar|apr|may|jun|jul|aug|sep|oct|nov|dec",
        "%B", "L", "january|february|march|april|may|june|july|august|september|october|november|december",
        "%m", "L", "01|02|03|04|05|06|07|08|09|10|11|12",
        "%m", "L", "1|2|3|4|5|6|7|8|9|10|11|12", // FIXME: check correctness
        "%d", "L", "01|02|03|04|05|06|07|08|09|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27|28|29|30|31",
        "%d", "L", "1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|27|28|29|30|31", // FIXME: check correctness
        "%D", "L", "day before yesterday|yesterday|today|tomorrow|day after tomorrow",
        // "%g", "I", "[0-9]{2}",
        "%Y", "I", "[12][0-9]{3}", // only 1xxx and 2xxx years for conservative matching
        "%y", "I", "[0-9]{2}",
        // "%t", "S", "%1%/%d(?:%/%4)?", // This pattern is added conditionally based on the locale, see initializePatterns
        "%t", "S", "%Y%/%m%/%d", // ISO 8601 date format
        "%t", "S", "%d%/%1(?:%/%4)?",
        "%t", "S", "(?:%6[,\\s]+)?%2\\s+%d(?:%3)?(?:[,\\s]+%4)?",
        "%t", "S", "(?:%6[,\\s]+)?%d(?:%3)?\\s*%2[,\\s]*%4?",
        "%t", "S", "%D", // relative days
        "%t", "S", "%A",
        
        // Time basics
        "%I", "I", "01|02|03|04|05|06|07|08|09|10|11|12",
        "%I", "I", "1|2|3|4|5|6|7|8|9|10|11|12",
        "%H", "I", "00|01|02|03|04|05|06|07|08|09|10|11|12|13|14|15|16|17|18|19|20|21|22|23",
        "%H", "I", "0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|20|21|22|23",
        "%M", "I", "[0-5][0-9]",
        "%S", "I", "[0-5][0-9]",
        "%p", "L", "am|pm",
        "%z", "I", "[-+](?:01|02|03|04|05|06|07|08|09|10|11|12)(?:[0-5][0-9])?",
        "%z", "I", "[-+](?:1|2|3|4|5|6|7|8|9|10|11|12)(?:[0-5][0-9])?",
        "%N", "L", "morning|afternoon|evening|night",
        "%T", "S", "(?:%r|%R)",
        "%T", "S", "%H:?%M\\s+(?:Hrs|Hours)%U",
        "%T", "S", "%H(?:\\s*)?o[' ]?clock%U",
        
        // Event basics, not in strftime
        "%e", "S", "(?:meet|meeting|appointment|conf|conference|seminar|interview)(?:\\s+with\\s+\\w+)?",
        
        // This is the marker to say that the above should be captured
        "--", "-", "--", 
        
        // Date compounds
        "%1", "C", "%m|%B|%b",
        "%2", "C", "%B|%b",
        "%3", "C", "st|nd|rd|th",
        "%4", "C", "%Y|%y",
        "%5", "C", "[<>?,;:'`~!@#&*\"]|\b",
        "%6", "C", "%a|%A",
        "%^", "C", "(?:^|[\\s({\\[]|%5)",
        "%$", "C", "(?:$|[\\s)}\\].]|%5)",
        "%/", "C", "[-/,.]",
        
        // Time compounds
        "%U", "C", "(?:\\s+(?:UTC%z|\\(UTC%z\\)|GMT%z|\\(GMT%z\\)))?",
        "%r", "C", "%I(?::?%M)?(?::%S)?\\s*%p%U",
        "%R", "C", "%H:%M(?::%S)?%U",
        
        // Final full match
        "%.", "C", "%^%t%$", // Date
        "%.", "C", "%^%T%$", // Time
        "%.", "C", "%^%e%$", // Event
        
        null
    ),

    mContextDate : NaN,
    get contextDate () {
      return this.mContextDate;
    },
    set contextDate (aContextDate) {
        this.mContextDate = aContextDate;
    },

    getContextDate: function () {
        var contextDate = new Date();

        if (!isNaN (this.mContextDate))
            contextDate = new Date (this.mContextDate / USEC_PER_MSEC);

        return contextDate;
    },

    mContextTimezone: NaN,
    get contextTimezone () {
        return this.mContextTimezone;
    },

    set contextTimezone (aContextTimezone) {
        this.mContextTimezone = aContextTimezone;
    },

    getContextTimezone: function () {

        if (!isNaN (this.mContextTimezone))
           return this.mContextTimezone;

        var tempDate = new Date();
        return tempDate.getTimezoneOffset ();
    },

    mNowDate : NaN,
    get nowDate () {
        return this.mNowDate;
    },
    set nowDate (aNowDate) {
        this.mNowDate = aNowDate;
    },

    getNowDate: function () {
        if (!isNaN (this.mNowDate))
          return new Date (this.mNowDate / USEC_PER_MSEC);
        return new Date();
    },

    // The main function that is exported which extracts strings
    mPattern : "",
    mMatchInfo : new Array (),
    extractEvents: function (text, uri, count) {
        this.initializePatterns();

        var re = new RegExp (this.mPattern, "gi");
        var matches = null;
        var matchText = text;        
        var finalEvents = new Array();
        var sentences = text.split(/\?|\.\s/); // Break down the text into sentences
        for each (var sentence in sentences ) {
           var events = new Array();
           while ((matches = re.exec (sentence)) != null) {
               matches.shift ();
               events.push (this.parseValues (matches, this.mMatchInfo));
               // Apparently there is problem with matching ^ when we do second
               // and later matches, so this hack
               sentence = sentence.substr (re.lastIndex);
               re.lastIndex = 0;
           }
           this.mergeEvents (events);
           this.normalizeEvents (events);
           this.removePastEvents (events);
           if (uri) // If there is a message associated with this text
             this.addMessageInfo (events, uri); // add message data to events
           for each (var ev in events)
             finalEvents.push(ev);
        }
        
        count.value = finalEvents.length;
        return finalEvents;
    },

    initializePatterns: function ()
    {
        if (this.mPattern == "")
        {
            // Ugly hack to handle dates with month in the beginning
            let dateSample = new Date(2010, 11, 30);
            let localeDateString = dateSample.toLocaleFormat("%x");
            // Check if in this locale month comes before date in arabic numerals
            // Add a new pattern based on this to the list of patterns
            if (localeDateString.match(/12.*30/))
               this.mPatterns.unshift("%t", "S", "%1%/%d(?:%/%4)?");

            this.mPattern = this.generatePatterns ("%.", this.mMatchInfo);
        }
    },

    generatePatterns: function (key, matchInfo) {
        var capture = this.needCapture (key);
        var result = "";
        var matches = 0;
        
        for (var i = 0; this.mPatterns[i]; i += 3)
            if (this.mPatterns[i] == key)
                matches++;

        if (matches > 1)
            result += "(?:";

        var first = true;
        for (var i = 0; this.mPatterns[i]; i += 3) {
            if (this.mPatterns[i] == key) {
                var noCapture = "?:";
                if (capture) {
                    noCapture = "";
                    matchInfo.push (i);
                }

                var subResult = (first ? "" : "|") + "(" + noCapture + 
                                this.mPatterns[i + 2] + ")";
                subResult = this.expandPatterns (subResult, matchInfo);
                result += subResult;
                first = false;
            }
        }

        if (matches > 1)
            result += ")";
  
        return result;
    },

    needCapture: function (key) {
        for (var i = 0; this.mPatterns[i] && this.mPatterns[i] != "--"; i += 3)
            if (this.mPatterns[i] == key)
                return true;
        return false;
    },

    expandPatterns: function (str, matchInfo) {
        var result = "";
        var processString = str;

        var lastIndex = 0;
        while (1) {
            var index = processString.indexOf ("%", lastIndex);
            if (index == -1) {
                result += processString.substr (lastIndex);
                break;
            }

            result += processString.substring (lastIndex, index);
            if (processString.length > index + 1) {
                result += this.generatePatterns 
                               (processString.substr (index, 2), matchInfo);
                index += 2;
            }

            lastIndex = index;
        }

        return result;
    },

    parseValues: function (matches, matchInfo) {
        var result = Components.classes["@mozilla.org/calendar/event;1"].
                     createInstance (Components.interfaces.calIEvent);
        /* XXX: Ok, the initEvent was removed from the current code so we have
        initialise the startDate member ourselves */
        result.startDate =
                Components.classes["@mozilla.org/calendar/datetime;1"].
                createInstance (Components.interfaces.calIDateTime);

        var isYearSet = false;
        var isMonthSet = false;
        var isDaySet = false;
        var weekDay = NaN;

        var contextDate = this.getContextDate ();
        var contextTimezoneMinutes = this.getContextTimezone ();

        result.startDate.isDate = true;

        for (i = 0; i < matches.length; i++) {
            // Skip empty values
            if (!matches[i])
                continue;
            
            // Parse the value
            var value;
            switch (this.mPatterns[matchInfo[i] + 1]) {
                case "I":
                    // FIXME: localisation problem
                    value = parseInt (matches[i], 10);
                    break;
                case "L":
                    {
                        var itemList = this.mPatterns[matchInfo[i] + 2].
                                       split ("|");
                        var match = matches[i].toLowerCase();
                        for (var j = 0; j < itemList.length; j++) {
                            if (itemList[j].toLowerCase() == match) {
                                value = j;
                                break;
                            }
                        }
                        break;
                    }
                case 'S':
                    value = matches[i];
                    break;
            }

            // Store the value in event structure
            switch (this.mPatterns[matchInfo[i]]) {
                case "%a":
                    // abbrivated days names are used only when given full
                    // dates. So we ignore it and just take the date
                    break;
                case "%A":
                    weekDay = value;
                    break;
                case "%b":
                case "%B":
                case "%m":
                    result.startDate.month = value; // 0-11 values
                    isMonthSet = true;
                    break;
                case "%d":
                    result.startDate.day =  value + 1;
                    isDaySet = true;
                    break;
                case "%D":
                    var duration = Components.
                        classes["@mozilla.org/calendar/duration;1"].
                        createInstance(Components.interfaces.calIDuration);
                    result.startDate.year = contextDate.getUTCFullYear ();
                    result.startDate.month = contextDate.getUTCMonth ();
                    result.startDate.day = contextDate.getUTCDate ();
                    duration.isNegative = (value < 2);
                    duration.days = Math.abs (value - 2);
                    result.startDate.addDuration (duration);
                    isDaySet = true;
                    isMonthSet = true;
                    isYearSet = true;
                    break;
                case "%Y":
                    result.startDate.year = value;
                    isYearSet = true;
                    break;
                case "%y":
                    {
                        // Sliding window algorithm for determining century
                        // described at
                        // http://www.firebirdsql.org/doc/contrib/FirebirdDateLiterals.html
                        var currentYear = contextDate.getUTCFullYear();
                        var currentCentury = Math.round (currentYear / 100);
                        var currentCenturyValue = currentCentury * 100 + value;
                        var nextCenturyValue  = (currentCentury + 1) * 100 + 
                                                 value;
                        var previousCenturyValue = (currentCentury -1) * 100 + 
                                                   value;
                        
                        if ((currentYear - previousCenturyValue) <= 
                            Math.abs (currentCenturyValue - currentYear))
                            result.startDate.year = previousCenturyValue;
                        else {
                            if (Math.abs (currentCenturyValue - currentYear) <=
                                (nextCenturyValue - currentYear))
                                result.startDate.year = currentCenturyValue;
                            else
                                result.startDate.year = nextCenturyValue;
                        }
                        
                        isYearSet = true;

                        break;
                    }
                case "%I":
                    // If we set any of the time fields,
                    // then its not just date anymore
                    result.startDate.isDate = false;
                    // To allow for am/pm additions
                    result.startDate.hour += value;
                    break;
                case "%H":
                    // If we set any of the time fields,
                    // then its not just date anymore
                    result.startDate.isDate = false;
                    result.startDate.hour = value;
                    break;
                case "%M":
                    // If we set any of the time fields,
                    // then its not just date anymore
                    result.startDate.isDate = false;
                    result.startDate.minute = value;
                    break;
                case "%S":
                    // If we set any of the time fields,
                    // then its not just date anymore
                    result.startDate.isDate = false;
                    result.startDate.second = value;
                    break;
                case "%p":
                    // If we set any of the time fields,
                    // then its not just date anymore
                    result.startDate.isDate = false;
                    result.startDate.hour += value * 12;
                    break;
                case "%z":
                  if (Math.abs (value) < 100)
                     contextTimezoneMinutes = -(value * 60);
                  else
                     contextTimezoneMinutes = -(Math.round (value/100) * 60
                                             +(value - Math.round (value/100) * 100));
                    break;
                case "%t":
                    result.setProperty ("X-DATE-MATCH", value);
                    break;
                case "%T":
                    result.setProperty ("X-TIME-MATCH", value);
                    break;
                case "%e":
                    result.setProperty("X-TITLE-MATCH", value);
                    break;
                default:
                    dump ("Warning: an unimplemented basic value is matched");
            }
        }

        // Fill event structure with default values
        if (isYearSet || isMonthSet || isDaySet) {
            if (!isYearSet) {
                result.startDate.year = contextDate.getUTCFullYear ();
                if (isMonthSet && result.startDate.month <= contextDate.getUTCMonth() ) {
                  if (result.startDate.month == contextDate.getUTCMonth()) {
                      if (isDaySet && result.startDate.day < contextDate.getUTCDate() )  
                        result.startDate.year += 1;
                  } else
                      result.startDate.year += 1;
                }
                if (!isMonthSet) {
                    result.startDate.month = contextDate.getUTCMonth ();
                    isMonthSet = true;
                }
            }
            if (!isMonthSet && !isDaySet) {
                result.startDate.month = 0;
                result.startDate.day = 1;
            }
            if (!isDaySet) 
                result.startDate.day = 1;
        }

	if (!isNaN (weekDay) && !this.isDateSet (result)) {
            result.startDate.year = contextDate.getUTCFullYear ();
            result.startDate.month = contextDate.getUTCMonth ();
            result.startDate.day = contextDate.getUTCDate ();
            weekDay -= contextDate.getUTCDay ();
            if (weekDay <= 0)
                weekDay += 7;

            var duration = Components.
                    classes["@mozilla.org/calendar/duration;1"].
                    createInstance(Components.interfaces.calIDuration);
            duration.days = weekDay;
            result.startDate.addDuration (duration);
	}

        result.setProperty ("X-TIMEZONE", contextTimezoneMinutes);
       
        return result;
    },

    mergeEvents: function (events) {
        var newEvents = new Array ();
        var l;
        var i;

        for (i = 0; i < events.length; i++) {
            if (i < 1) {
                newEvents.push (events[i].clone());
                l = newEvents.length - 1;
                continue;
            }

            var newEventIsDateSet = this.isDateSet (newEvents[l]);
            var curEventIsDateSet = this.isDateSet (events[i]);

            if ((newEventIsDateSet && curEventIsDateSet) ||
                (newEvents[l].startDate.isDate == false && 
                 events[i].startDate.isDate == false) ||
                (newEvents[l].title && events[i].title)) {
                newEvents.push (events[i].clone());
                l = newEvents.length - 1;
            }
            else {
                if (events[i].startDate.isDate == false) {
                    newEvents[l].startDate.isDate = false;
                    newEvents[l].startDate.hour = events[i].startDate.hour;
                    newEvents[l].startDate.minute = events[i].startDate.minute;
                    newEvents[l].startDate.second = events[i].startDate.second;
                    newEvents[l].setProperty ("X-TIME-MATCH", 
                                    events[i].getProperty ("X-TIME-MATCH"));
                }
                if (curEventIsDateSet) {
                    newEvents[l].startDate.day = events[i].startDate.day;
                    newEvents[l].startDate.month = events[i].startDate.month;
                    newEvents[l].startDate.year = events[i].startDate.year;
                    newEvents[l].setProperty ("X-DATE-MATCH", 
                                    events[i].getProperty ("X-DATE-MATCH"));
                }
                if (events[i].title)
                    newEvents[l].title = events[i].title;
            }
        }

        events.length = 0;
        for (i = 0; i < newEvents.length; i++) {
            // consider only those events which have a date or time set.
            if (newEvents[i].hasProperty("X-DATE-MATCH") || newEvents[i].hasProperty("X-TIME-MATCH"))
               events.push (newEvents[i]);
        }
    },

    normalizeEvents: function (events) {
        var contextDate = this.getContextDate ();

        for (var i = 0; i < events.length; i++) {
            if (!this.isDateSet (events[i])) {
                events[i].startDate.year = contextDate.getUTCFullYear ();
                events[i].startDate.month = contextDate.getUTCMonth ();
                events[i].startDate.day = contextDate.getUTCDate ();
            }
            if (!events[i].title)
                events[i].title = "";

            if (events[i].startDate.isDate ) { // Most likely time info is absent in data. so set default time
               events[i].startDate.isDate = false;
               events[i].startDate.hour = 11;
            }

            /*
             * Timezone adjustment, because we want to do this only after the
             * date is set.
             */
            var timezoneMinutes = events[i].getProperty ("X-TIMEZONE");
            var duration = Components.classes["@mozilla.org/calendar/duration;1"].
                           createInstance(Components.interfaces.calIDuration);
            var absTimezoneMinutes = Math.abs (timezoneMinutes);
            duration.isNegative = (timezoneMinutes < 0);
            duration.hours = Math.round (absTimezoneMinutes / 60);
            duration.minutes = absTimezoneMinutes - (duration.hours * 60);
            events[i].startDate.addDuration (duration);

            /*
             * Enddate: for now we just assume that duration of the event 
             * is one hour
             */
            if (!events[i].endDate || !events[i].startDate.compare(events[i].endDate)) {
              // If endDate not defined or endDate equals startDate
                events[i].endDate = events[i].startDate.clone ();
                events[i].endDate.hour += 1;
            }
        }
    },

    removePastEvents: function (events) {
        for (i = events.length -1; i >=0 ; i--)
            if (this.isPast (events[i].startDate))
                events.splice (i, 1);
    },

    addMessageInfo: function(events, uri) {
      var service = this.messenger.messageServiceFromURI(uri);
      var messageHdr = service.messageURIToMsgHdr(uri); 
      var msgSubject = messageHdr.subject;
      if (msgSubject)
        msgSubject = " - " + msgSubject;
      else 
        msgSubject = "";
      for each (var event in events ) {
        // Include mail subject in event title.
        event.title = event.getProperty("X-TITLE-MATCH") + msgSubject;
        // Add recipients of mail as attendees to event.
        var recipients = messageHdr.recipients.split(/[,;]/);
        recipients.push(messageHdr.author);
        for each (var recipient in recipients) {
          var attendee = Components.classes["@mozilla.org/calendar/attendee;1"].
                         createInstance(Components.interfaces.calIAttendee);
          attendee.id = recipient;
          attendee.role = "OPT-PARTICIPANT";
          attendee.participationStatus = "NEEDS-ACTION";
          attendee.rsvp = true;
          event.addAttendee(attendee);
        }
      }
    },

    isDateSet: function (aEvent) {
        return (aEvent.startDate.year > 1970);
    },

    isPast: function (dateTime) {
        var contextDate = this.getNowDate ();
        if (dateTime.year < contextDate.getUTCFullYear ())
            return true;
        if (dateTime.year > contextDate.getUTCFullYear ())
            return false;
        if (dateTime.month < contextDate.getUTCMonth ())
            return true;
        if (dateTime.month > contextDate.getUTCMonth ())
            return false;
        if (dateTime.day < contextDate.getUTCDate ())
            return true;
        if (dateTime.day > contextDate.getUTCDate ())
            return false;
        // This means that there is no time component
        // So we don't check the time
        if (dateTime.isDate)
            return false;
        if (dateTime.hour < contextDate.getUTCHours ())
            return true;
        if (dateTime.hour > contextDate.getUTCHours ())
            return false;
        if (dateTime.minute < contextDate.getUTCMinutes ())
            return true;
        if (dateTime.minute > contextDate.getUTCMinutes ())
            return false;
        if (dateTime.second < contextDate.getUTCSeconds ())
            return true;
        if (dateTime.second > contextDate.getUTCSeconds ())
            return false;
        return false;
    },

    QueryInterface: function(aIID) {
        if (!aIID.equals(csIEventFilter) &&    
            !aIID.equals(nsISupports))
            throw Components.results.NS_ERROR_NO_INTERFACE;
        return this;
    }
};

/***********************************************************
* class factory
***********************************************************/

var csEventFilterFactory = {
    createInstance: function (aOuter, aIID) {
        if (aOuter != null)
            throw Components.results.NS_ERROR_NO_AGGREGATION;
        return (new csEventFilter()).QueryInterface(aIID);
    }
};

/***********************************************************
* module definition (xpcom registration)
***********************************************************/
var csEventFilterModule = {
    registerSelf: function(aCompMgr, aFileSpec, aLocation, aType) {
        aCompMgr = aCompMgr.
        QueryInterface(Components.interfaces.nsIComponentRegistrar);
        aCompMgr.registerFactoryLocation(CLASS_ID, CLASS_NAME, 
                                         CONTRACT_ID, aFileSpec,
                                         aLocation, aType);
    },

    unregisterSelf: function(aCompMgr, aLocation, aType) {
        aCompMgr = aCompMgr.
                   QueryInterface(Components.interfaces.nsIComponentRegistrar);
        aCompMgr.unregisterFactoryLocation(CLASS_ID, aLocation);        
    },
  
    getClassObject: function(aCompMgr, aCID, aIID) {
        if (!aIID.equals(Components.interfaces.nsIFactory))
            throw Components.results.NS_ERROR_NOT_IMPLEMENTED;

        if (aCID.equals(CLASS_ID))
            return csEventFilterFactory;
        
        throw Components.results.NS_ERROR_NO_INTERFACE;
    },

    canUnload: function(aCompMgr) { return true; }
};

/***********************************************************
* module initialization
*
* When the application registers the component, this function
* is called.
***********************************************************/
function NSGetModule(aCompMgr, aFileSpec) { return csEventFilterModule; }

