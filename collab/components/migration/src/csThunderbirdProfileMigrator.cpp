/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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
 * The Original Code is The Mail Profile Migrator.
 *
 * The Initial Developer of the Original Code is Ben Goodger.
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *  Ben Goodger <ben@bengoodger.com>
 *  Scott MacGregor <mscott@mozilla.org>
 *  Sunil Mohan Adapa <sunil@synovel.com>
 *  Prasad Sunkari <prasad@synovel.com>
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

#include "nsMailProfileMigratorUtils.h"
#include "nsDirectoryServiceDefs.h"
#include "nsIObserverService.h"
#include "nsIPasswordManagerInternal.h"
#include "nsIPrefLocalizedString.h"
#include "nsIPrefService.h"
#include "nsIServiceManager.h"
#include "nsArrayUtils.h"
#include "nsISupportsPrimitives.h"
#include "nsNetCID.h"
#include "nsNetUtil.h"
#include "csThunderbirdProfileMigrator.h"
#include "nsIRelativeFilePref.h"
#include "nsAppDirectoryServiceDefs.h"
#include "prprf.h"
#include "nsVoidArray.h"
#include "msgCore.h"
#include "nsINIParser.h"

static PRUint32 StringHash(const char *ubuf);
nsresult NS_MsgHashIfNecessary(nsCString &name);

// Mail specific folder paths
#define MAIL_DIR_50_NAME             NS_LITERAL_STRING("Mail")
#define IMAP_MAIL_DIR_50_NAME        NS_LITERAL_STRING("ImapMail")
#define NEWS_DIR_50_NAME             NS_LITERAL_STRING("News")


///////////////////////////////////////////////////////////////////////////////
// csThunderbirdProfileMigrator
#define FILE_NAME_JUNKTRAINING    NS_LITERAL_STRING("training.dat")
#define FILE_NAME_PERSONALDICTIONARY NS_LITERAL_STRING("persdict.dat")
#define FILE_NAME_PERSONAL_ADDRESSBOOK NS_LITERAL_STRING("abook.mab")
#define FILE_NAME_MAILVIEWS       NS_LITERAL_STRING("mailviews.dat")
#define FILE_NAME_CERT8DB         NS_LITERAL_STRING("cert8.db")
#define FILE_NAME_KEY3DB          NS_LITERAL_STRING("key3.db")
#define FILE_NAME_SECMODDB        NS_LITERAL_STRING("secmod.db")
#define FILE_NAME_MIMETYPES       NS_LITERAL_STRING("mimeTypes.rdf")
#define FILE_NAME_PREFS           NS_LITERAL_STRING("prefs.js")
#define FILE_NAME_USER_PREFS      NS_LITERAL_STRING("user.js")
#define FILE_NAME_CALENDARS       NS_LITERAL_STRING("storage.sdb")

struct PrefBranchStruct {
  char*         prefName;
  PRInt32       type;
  union {
    char*       stringValue;
    PRInt32     intValue;
    PRBool      boolValue;
    PRUnichar*  wstringValue;
  };
};

NS_IMPL_ISUPPORTS2(csThunderbirdProfileMigrator, nsIMailProfileMigrator, nsITimerCallback)


csThunderbirdProfileMigrator::csThunderbirdProfileMigrator()
{
  mObserverService = do_GetService("@mozilla.org/observer-service;1");
  mMaxProgress = LL_ZERO;
  mCurrentProgress = LL_ZERO;
}

csThunderbirdProfileMigrator::~csThunderbirdProfileMigrator()
{
}

///////////////////////////////////////////////////////////////////////////////
// nsITimerCallback

NS_IMETHODIMP
csThunderbirdProfileMigrator::Notify(nsITimer *timer)
{
  CopyNextFolder();
  return NS_OK;
}

void csThunderbirdProfileMigrator::CopyNextFolder()
{
  if (mFileCopyTransactionIndex < mFileCopyTransactions->Count())
  {
    PRUint32 percentage = 0;
    fileTransactionEntry* fileTransaction = (fileTransactionEntry*) mFileCopyTransactions->SafeElementAt(mFileCopyTransactionIndex++);
    if (fileTransaction) // copy the file
    {
      fileTransaction->srcFile->CopyTo(fileTransaction->destFile, EmptyString());

      // add to our current progress
      PRInt64 fileSize;
      fileTransaction->srcFile->GetFileSize(&fileSize);
      LL_ADD(mCurrentProgress, mCurrentProgress, fileSize);

      PRInt64 percentDone;
      LL_MUL(percentDone, mCurrentProgress, 100);

      LL_DIV(percentDone, percentDone, mMaxProgress);

      LL_L2UI(percentage, percentDone);

      nsAutoString index;
      index.AppendInt( percentage );

      NOTIFY_OBSERVERS(MIGRATION_PROGRESS, index.get());
    }
    // fire a timer to handle the next one.
    mFileIOTimer = do_CreateInstance("@mozilla.org/timer;1");
    if (mFileIOTimer)
      mFileIOTimer->InitWithCallback(static_cast<nsITimerCallback *>(this), percentage == 100 ? 500 : 0, nsITimer::TYPE_ONE_SHOT);
  } else
    EndCopyFolders();

  return;
}

void csThunderbirdProfileMigrator::EndCopyFolders()
{
  // clear out the file transaction array
  if (mFileCopyTransactions)
  {
    PRUint32 count = mFileCopyTransactions->Count();
    for (PRUint32 i = 0; i < count; ++i)
    {
      fileTransactionEntry* fileTransaction = (fileTransactionEntry*) mFileCopyTransactions->ElementAt(i);
      if (fileTransaction)
      {
        fileTransaction->srcFile = nsnull;
        fileTransaction->destFile = nsnull;
        delete fileTransaction;
      }
    }

    mFileCopyTransactions->Clear();
    delete mFileCopyTransactions;
  }

  // notify the UI that we are done with the migration process
  nsAutoString index;
  index.AppendInt(nsIMailProfileMigrator::MAILDATA);
  NOTIFY_OBSERVERS(MIGRATION_ITEMAFTERMIGRATE, index.get());

  NOTIFY_OBSERVERS(MIGRATION_ENDED, nsnull);
}

///////////////////////////////////////////////////////////////////////////////
// nsIMailProfileMigrator

NS_IMETHODIMP
csThunderbirdProfileMigrator::Migrate(PRUint16 aItems, nsIProfileStartup* aStartup, const PRUnichar* aProfile)
{
  nsresult rv = NS_OK;
  PRBool aReplace = aStartup ? PR_TRUE : PR_FALSE;

  if (!mTargetProfile) {
    GetProfilePath(aStartup, mTargetProfile);
    if (!mTargetProfile) return NS_ERROR_FAILURE;
  }
  if (!mSourceProfile)
    GetSourceProfile(aProfile);

  NOTIFY_OBSERVERS(MIGRATION_STARTED, nsnull);

  COPY_DATA(CopyPreferences,  aReplace, nsIMailProfileMigrator::SETTINGS);

  // fake notifications for things we've already imported as part of CopyPreferences
  COPY_DATA(DummyCopyRoutine, aReplace, nsIMailProfileMigrator::ACCOUNT_SETTINGS);
  COPY_DATA(DummyCopyRoutine, aReplace, nsIMailProfileMigrator::NEWSDATA);

  // copy junk mail training file
  COPY_DATA(CopyJunkTraining, aReplace, nsIMailProfileMigrator::JUNKTRAINING);
  COPY_DATA(CopyPasswords,    aReplace, nsIMailProfileMigrator::PASSWORDS);

  // copy calendar data
  COPY_DATA(CopyCalendars,    aReplace, nsIMailProfileMigrator::OTHERDATA);

  // the last thing to do is to actually copy over any mail folders we have marked for copying
  // we want to do this last and it will be asynchronous so the UI doesn't freeze up while we perform
  // this potentially very long operation.

  nsAutoString index;
  index.AppendInt(nsIMailProfileMigrator::MAILDATA);
  NOTIFY_OBSERVERS(MIGRATION_ITEMBEFOREMIGRATE, index.get());

  // Generate the max progress value now that we know all of the files we need to copy
  PRUint32 count = mFileCopyTransactions->Count();
  for (PRUint32 i = 0; i < count; ++i)
  {
    fileTransactionEntry* fileTransaction = (fileTransactionEntry*) mFileCopyTransactions->ElementAt(i);
    if (fileTransaction)
    {
      PRInt64 fileSize;
      fileTransaction->srcFile->GetFileSize(&fileSize);
      LL_ADD(mMaxProgress, mMaxProgress, fileSize);
    }
  }

  CopyNextFolder();

  return rv;
}

NS_IMETHODIMP
csThunderbirdProfileMigrator::GetMigrateData(const PRUnichar* aProfile,
                                           PRBool aReplace,
                                           PRUint16* aResult)
{
  *aResult = 0;

  if (!mSourceProfile) {
    GetSourceProfile(aProfile);
    if (!mSourceProfile)
      return NS_ERROR_FILE_NOT_FOUND;
  }

  MigrationData data[] = { { ToNewUnicode(FILE_NAME_PREFS),
                             nsIMailProfileMigrator::SETTINGS,
                             PR_TRUE },
                           { ToNewUnicode(FILE_NAME_JUNKTRAINING),
                             nsIMailProfileMigrator::JUNKTRAINING,
                             PR_TRUE },
                           { ToNewUnicode(FILE_NAME_CALENDARS),
                             nsIMailProfileMigrator::OTHERDATA,
                             PR_TRUE },
                          };

  // Frees file name strings allocated above.
  GetMigrateDataFromArray(data, sizeof(data)/sizeof(MigrationData),
                          aReplace, mSourceProfile, aResult);

  // Now locate passwords
  nsCString signonsFileName;
  GetSignonFileName(aReplace, getter_Copies(signonsFileName));

  if (!signonsFileName.IsEmpty()) {
    nsAutoString fileName;
    CopyASCIItoUTF16(signonsFileName, fileName);
    nsCOMPtr<nsIFile> sourcePasswordsFile;
    mSourceProfile->Clone(getter_AddRefs(sourcePasswordsFile));
    sourcePasswordsFile->Append(fileName);

    PRBool exists;
    sourcePasswordsFile->Exists(&exists);
    if (exists)
      *aResult |= nsIMailProfileMigrator::PASSWORDS;
  }

  // add some extra migration fields for things we also migrate
  *aResult |= nsIMailProfileMigrator::ACCOUNT_SETTINGS
           | nsIMailProfileMigrator::MAILDATA
           | nsIMailProfileMigrator::NEWSDATA
           | nsIMailProfileMigrator::ADDRESSBOOK_DATA;

  return NS_OK;
}

NS_IMETHODIMP
csThunderbirdProfileMigrator::GetSourceExists(PRBool* aResult)
{
  nsCOMPtr<nsIArray> profiles;
  GetSourceProfiles(getter_AddRefs(profiles));

  if (profiles) {
    PRUint32 count;
    profiles->GetLength(&count);
    *aResult = count > 0;
  }
  else
    *aResult = PR_FALSE;

  return NS_OK;
}

NS_IMETHODIMP
csThunderbirdProfileMigrator::GetSourceHasMultipleProfiles(PRBool* aResult)
{
  nsCOMPtr<nsIArray> profiles;
  GetSourceProfiles(getter_AddRefs(profiles));

  if (profiles) {
    PRUint32 count;
    profiles->GetLength(&count);
    *aResult = count > 1;
  }
  else
    *aResult = PR_FALSE;

  return NS_OK;
}

NS_IMETHODIMP
csThunderbirdProfileMigrator::GetSourceProfiles(nsIArray** aResult)
{
  if (!mProfileNames && !mProfileLocations) {
    nsresult rv;
    mProfileNames = do_CreateInstance(NS_ARRAY_CONTRACTID, &rv);
    if (NS_FAILED(rv))
      return rv;

    mProfileLocations = do_CreateInstance(NS_ARRAY_CONTRACTID, &rv);
    if (NS_FAILED(rv))
      return rv;

    // Fills mProfileNames and mProfileLocations
    FillProfileDataFromThunderbirdRegistry();
  }

  NS_IF_ADDREF(*aResult = mProfileNames);
  return NS_OK;
}

///////////////////////////////////////////////////////////////////////////////
// csThunderbirdProfileMigrator

nsresult
csThunderbirdProfileMigrator::GetSourceProfile(const PRUnichar* aProfile)
{
  PRUint32 count;
  mProfileNames->GetLength(&count);
  for (PRUint32 i = 0; i < count; ++i) {
    nsCOMPtr<nsISupportsString> str(do_QueryElementAt(mProfileNames, i));
    nsString profileName;
    str->GetData(profileName);
    if (profileName.Equals(aProfile)) {
      mSourceProfile = do_QueryElementAt(mProfileLocations, i);
      break;
    }
  }

  return NS_OK;
}

nsresult
csThunderbirdProfileMigrator::GetProfileDataFromINI(nsILocalFile* aProfileDir,
                                                    nsIMutableArray* aProfileNames,
                                                    nsIMutableArray* aProfileLocations,
                                                    PRBool aAppendLocationToName)
{
  nsresult rv;

  nsINIParser parser;
  nsCOMPtr<nsILocalFile> iniFile;
  rv = NS_NewNativeLocalFile(EmptyCString(), PR_TRUE, getter_AddRefs(iniFile));
  if (NS_FAILED(rv)) return rv;

  iniFile->InitWithFile (aProfileDir);
  iniFile->Append (NS_LITERAL_STRING("profiles.ini"));

  rv = parser.Init (iniFile);
  if (NS_FAILED(rv))
    return rv;

  unsigned int c = 0;
  for (c = 0; PR_TRUE; ++c) {
    nsCAutoString isRelative, path, name;

    nsCAutoString profileID("Profile");
    profileID.AppendInt(c);

    rv = parser.GetString (profileID.get(), "IsRelative", isRelative);
    if (NS_FAILED(rv)) break;

    rv = parser.GetString (profileID.get(), "Path", path);
    if (NS_FAILED(rv)) continue;

    rv = parser.GetString (profileID.get(), "Name", name);
    if (NS_FAILED(rv)) continue;
    
    printf ("%s - %s\n", path.get(), name.get());

    nsCOMPtr<nsILocalFile> dir;
    rv = NS_NewNativeLocalFile(EmptyCString(), PR_TRUE, getter_AddRefs(dir));
    if (NS_FAILED(rv)) break;

    if (isRelative.EqualsLiteral("1"))
        dir->SetRelativeDescriptor(aProfileDir, path);
    else
        dir->SetPersistentDescriptor(path);

    PRBool exists;
    dir->Exists (&exists);

    if (exists) {
        aProfileLocations->AppendElement(dir, PR_FALSE);

        // Get the profile name and add it to the names array
        nsString profileName;
        CopyUTF8toUTF16(name, profileName);

        if (aAppendLocationToName) {
            nsString dirPathString;
            rv = dir->GetPath(dirPathString);

            if (!NS_FAILED(rv)) {
                profileName.AppendLiteral(" (");
                profileName.Append(dirPathString.get());
                profileName.AppendLiteral(")");
            }
        }

        nsCOMPtr<nsISupportsString> profileNameString(
            do_CreateInstance("@mozilla.org/supports-string;1"));

        profileNameString->SetData(profileName);
        aProfileNames->AppendElement(profileNameString, PR_FALSE);
    }
  }

  return rv;
}

nsresult
csThunderbirdProfileMigrator::FillProfileDataFromThunderbirdRegistry()
{
  // Find the Thunderbird Registry
  nsCOMPtr<nsIProperties> fileLocator(do_GetService("@mozilla.org/file/directory_service;1"));
  nsCOMPtr<nsILocalFile> profileDirectory;

#if defined(XP_UNIX)
  fileLocator->Get(NS_UNIX_HOME_DIR, NS_GET_IID(nsILocalFile), getter_AddRefs(profileDirectory));
  NS_ENSURE_TRUE(profileDirectory, NS_ERROR_FAILURE);

  profileDirectory->Append(NS_LITERAL_STRING(".thunderbird"));
  GetProfileDataFromINI(profileDirectory, mProfileNames, mProfileLocations, PR_TRUE);

  nsCOMPtr<nsILocalFile> alterDirectory;
  fileLocator->Get(NS_UNIX_HOME_DIR, NS_GET_IID(nsILocalFile), getter_AddRefs(alterDirectory));
  NS_ENSURE_TRUE(alterDirectory, NS_ERROR_FAILURE);
  alterDirectory->Append(NS_LITERAL_STRING(".mozilla-thunderbird"));
  return GetProfileDataFromINI(alterDirectory, mProfileNames, mProfileLocations, PR_TRUE);
#endif

#ifdef XP_WIN
  fileLocator->Get(NS_WIN_APPDATA_DIR, NS_GET_IID(nsILocalFile), getter_AddRefs(profileDirectory));
  NS_ENSURE_TRUE(profileDirectory, NS_ERROR_FAILURE);

  profileDirectory->Append(NS_LITERAL_STRING("Thunderbird"));
#elif defined(XP_MACOSX)
  fileLocator->Get(NS_MAC_USER_LIB_DIR, NS_GET_IID(nsILocalFile), getter_AddRefs(profileDirectory));
  NS_ENSURE_TRUE(profileDirectory, NS_ERROR_FAILURE);

  profileDirectory->Append(NS_LITERAL_STRING("Thunderbird"));
#elif defined(XP_OS2)
  fileLocator->Get(NS_OS2_HOME_DIR, NS_GET_IID(nsILocalFile), getter_AddRefs(profileDirectory));
  NS_ENSURE_TRUE(profileDirectory, NS_ERROR_FAILURE);

  profileDirectory->Append(NS_LITERAL_STRING("Thunderbird"));
#endif

  return GetProfileDataFromINI(profileDirectory, mProfileNames, mProfileLocations, PR_FALSE);
}

#define F(a) csThunderbirdProfileMigrator::a

#define MAKEPREFTRANSFORM(pref, newpref, getmethod, setmethod) \
  { pref, newpref, F(Get##getmethod), F(Set##setmethod), PR_FALSE, -1 }

#define MAKESAMETYPEPREFTRANSFORM(pref, method) \
  { pref, 0, F(Get##method), F(Set##method), PR_FALSE, -1 }


static
csThunderbirdProfileMigrator::PrefTransform gTransforms[] = {


  MAKESAMETYPEPREFTRANSFORM("signon.SignonFileName",                    String),
  MAKESAMETYPEPREFTRANSFORM("mailnews.headers.showUserAgent",           Bool),
  MAKESAMETYPEPREFTRANSFORM("mailnews.headers.showOrganization",        Bool),
  MAKESAMETYPEPREFTRANSFORM("mail.collect_addressbook",                 String),
  MAKESAMETYPEPREFTRANSFORM("mail.collect_email_address_outgoing",      Bool),
  MAKESAMETYPEPREFTRANSFORM("mail.wrap_long_lines",                     Bool),
  MAKESAMETYPEPREFTRANSFORM("news.wrap_long_lines",                     Bool),
  MAKESAMETYPEPREFTRANSFORM("mailnews.customHeaders",                   String),
  MAKESAMETYPEPREFTRANSFORM("mail.default_html_action",                 Int),
  MAKESAMETYPEPREFTRANSFORM("mail.forward_message_mode",                Int),
  MAKESAMETYPEPREFTRANSFORM("mail.SpellCheckBeforeSend",                Bool),
  MAKESAMETYPEPREFTRANSFORM("mail.warn_on_send_accel_key",              Bool),
  MAKESAMETYPEPREFTRANSFORM("mailnews.html_domains",                    String),
  MAKESAMETYPEPREFTRANSFORM("mailnews.plaintext_domains",               String),
  MAKESAMETYPEPREFTRANSFORM("mailnews.headers.showUserAgent",           Bool),
  MAKESAMETYPEPREFTRANSFORM("mailnews.headers.showOrganization",        Bool),
  MAKESAMETYPEPREFTRANSFORM("mail.biff.play_sound",                     Bool),
  MAKESAMETYPEPREFTRANSFORM("mail.biff.play_sound.type",                Int),
  MAKESAMETYPEPREFTRANSFORM("mail.biff.play_sound.url",                 String),
  MAKESAMETYPEPREFTRANSFORM("mail.biff.show_alert",                     Bool),
  MAKESAMETYPEPREFTRANSFORM("network.proxy.type",                       Int),
  MAKESAMETYPEPREFTRANSFORM("network.proxy.http",                       String),
  MAKESAMETYPEPREFTRANSFORM("network.proxy.http_port",                  Int),
  MAKESAMETYPEPREFTRANSFORM("network.proxy.ftp",                        String),
  MAKESAMETYPEPREFTRANSFORM("network.proxy.ftp_port",                   Int),
  MAKESAMETYPEPREFTRANSFORM("network.proxy.ssl",                        String),
  MAKESAMETYPEPREFTRANSFORM("network.proxy.ssl_port",                   Int),
  MAKESAMETYPEPREFTRANSFORM("network.proxy.socks",                      String),
  MAKESAMETYPEPREFTRANSFORM("network.proxy.socks_port",                 Int),
  MAKESAMETYPEPREFTRANSFORM("network.proxy.gopher",                     String),
  MAKESAMETYPEPREFTRANSFORM("network.proxy.gopher_port",                Int),
  MAKESAMETYPEPREFTRANSFORM("network.proxy.no_proxies_on",              String),
  MAKESAMETYPEPREFTRANSFORM("network.proxy.autoconfig_url",             String),

  MAKESAMETYPEPREFTRANSFORM("mail.accountmanager.accounts",             String),
  MAKESAMETYPEPREFTRANSFORM("mail.accountmanager.defaultaccount",       String),
  MAKESAMETYPEPREFTRANSFORM("mail.accountmanager.localfoldersserver",   String),
  MAKESAMETYPEPREFTRANSFORM("mail.smtp.defaultserver",                  String),
  MAKESAMETYPEPREFTRANSFORM("mail.smtpservers",                         String),

  MAKESAMETYPEPREFTRANSFORM("msgcompose.font_face",                     String),
  MAKESAMETYPEPREFTRANSFORM("msgcompose.font_size",                     String),
  MAKESAMETYPEPREFTRANSFORM("msgcompose.text_color",                    String),
  MAKESAMETYPEPREFTRANSFORM("msgcompose.background_color",              String),

  MAKEPREFTRANSFORM("mail.pane_config","mail.pane_config.dynamic", Int, Int),

  /*
   * Lightning preferences
   */ 
  // General prefs
  MAKESAMETYPEPREFTRANSFORM("calendar.date.format",                     Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.event.defaultlength",             Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.alarms.defaultsnoozelength",      Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.autorefresh.enabled",             Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.autorefresh.timeout",             Int),

  // Alarms prefs
  MAKESAMETYPEPREFTRANSFORM("calendar.alarms.playsound",                Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.alarms.soundURL",                 String),
  MAKESAMETYPEPREFTRANSFORM("calendar.alarms.show",                     Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.alarms.showmissed",               Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.alarms.onforevents",              Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.alarms.onfortodos",               Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.alarms.eventalarmlen",            Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.alarms.eventalarmunit",           String),
  MAKESAMETYPEPREFTRANSFORM("calendar.alarms.todoalarmlen",             Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.alarms.todoalarmunit",            String),

  // Categories prefs
  MAKESAMETYPEPREFTRANSFORM("calendar.categories.names",                String),

  // Views prefs
  MAKESAMETYPEPREFTRANSFORM("calendar.week.start",                      Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.week.d0sundaysoff",               Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.week.d1mondaysoff",               Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.week.d2tuesdaysoff",              Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.week.d3wednesdaysoff",            Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.week.d4thursdaysoff",             Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.week.d5fridaysoff",               Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.week.d6saturdaysoff",             Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.view.daystarthour",               Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.view.dayendhour",                 Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.view.visiblehours",               Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.weeks.inview",                    Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.previousweeks.inview",            Int),

  // Timezone prefs
  MAKESAMETYPEPREFTRANSFORM("calendar.timezone.local",                  String),

  // Misc.
  MAKESAMETYPEPREFTRANSFORM("calendar.debug.log",                       Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.debug.log.verbose",               Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.itip.compatSendMode",             Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.itip.email.log",                  Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.migrator.enabled",                Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.migration.log",                   Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.alarms.indicator.show",           Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.alarms.indicator.totaltime",      Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.cache.type",                      String),
  MAKESAMETYPEPREFTRANSFORM("calendar.reminder.custom",                 String),
  MAKESAMETYPEPREFTRANSFORM("calendar.date.formatTimeBeforeDate",       Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.allday.defaultTransparency",      String),
  MAKESAMETYPEPREFTRANSFORM("calendar.backup.days",                     Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.backup.filenum",                  Int),

  // GCal
  MAKESAMETYPEPREFTRANSFORM("calendar.google.useHTTPMethodOverride",    Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.google.alarmClosest",             Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.google.sendEventNotifications",   Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.google.enableAttendees",          Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.google.migrate",                  Bool),

  // WCAP
  MAKESAMETYPEPREFTRANSFORM("calendar.wcap.log_level",                  Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.wcap.log_file",                   String),
  MAKESAMETYPEPREFTRANSFORM("calendar.wcap.log_file_append",            Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.wcap.cache_last_results",         Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.wcap.cache_last_results_invalidate", Int),
  MAKESAMETYPEPREFTRANSFORM("calendar.wcap.subscriptions",              Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.wcap.no_get_calprops",            Bool),
  MAKESAMETYPEPREFTRANSFORM("calendar.wcap.confirmed_http_logins",      String)
};

nsresult
csThunderbirdProfileMigrator::TransformPreferences(const nsAString& aSourcePrefFileName,
                                                 const nsAString& aTargetPrefFileName)
{
  PrefTransform* transform;
  PrefTransform* end = gTransforms + sizeof(gTransforms)/sizeof(PrefTransform);

  // Load the source pref file
  nsCOMPtr<nsIPrefService> psvc(do_GetService(NS_PREFSERVICE_CONTRACTID));
  psvc->ResetPrefs();

  nsCOMPtr<nsIFile> sourcePrefsFile;
  mSourceProfile->Clone(getter_AddRefs(sourcePrefsFile));
  sourcePrefsFile->Append(aSourcePrefFileName);
  psvc->ReadUserPrefs(sourcePrefsFile);

  nsCOMPtr<nsIPrefBranch> branch(do_QueryInterface(psvc));
  for (transform = gTransforms; transform < end; ++transform)
    transform->prefGetterFunc(transform, branch);

  // read in the various pref branch trees for accounts, identities, servers, etc.

  nsVoidArray* accounts = new nsVoidArray();
  nsVoidArray* identities = new nsVoidArray();
  nsVoidArray* servers = new nsVoidArray();
  nsVoidArray* smtpservers = new nsVoidArray();
  nsVoidArray* ldapservers = new nsVoidArray();
  nsVoidArray* labelPrefs = new nsVoidArray();
  nsVoidArray* calendarColorPrefs = new nsVoidArray();
  nsVoidArray* calendarGoogleCalPrefs = new nsVoidArray();

  if (!accounts || !identities || !servers || !smtpservers || !ldapservers)
    return NS_ERROR_OUT_OF_MEMORY;

  ReadBranch("mail.account.", psvc, accounts);
  ReadBranch("mail.identity.", psvc, identities);
  ReadBranch("mail.server.", psvc, servers);
  ReadBranch("mail.smtpserver.", psvc, smtpservers);
  ReadBranch("ldap_2.servers.", psvc, ldapservers);
  ReadBranch("mailnews.labels.", psvc, labelPrefs);
  ReadBranch("calendar.category.color.", psvc, calendarColorPrefs);
  ReadBranch("calendar.google.calPrefs.", psvc, calendarGoogleCalPrefs);

  // the signature file prefs may be paths to files in the seamonkey profile path
  // so we need to copy them over and fix these paths up before we write them out to the new prefs.js
  CopySignatureFiles(identities, psvc);

  // certain mail prefs may actually be absolute paths instead of profile relative paths
  // we need to fix these paths up before we write them out to the new prefs.js
  CopyMailFolders(servers, psvc);

  CopyAddressBookDirectories(ldapservers, psvc);

  // Now that we have all the pref data in memory, load the target pref file,
  // and write it back out
  psvc->ResetPrefs();
  for (transform = gTransforms; transform < end; ++transform)
    transform->prefSetterFunc(transform, branch);

  WriteBranch("mail.account.", psvc, accounts);
  WriteBranch("mail.identity.", psvc, identities);
  WriteBranch("mail.server.", psvc, servers);
  WriteBranch("mail.smtpserver.", psvc, smtpservers);
  WriteBranch("ldap_2.servers.", psvc, ldapservers);
  WriteBranch("mailnews.labels.", psvc, labelPrefs);
  WriteBranch("calendar.category.color.", psvc, calendarColorPrefs);
  WriteBranch("calendar.google.calPrefs.", psvc, calendarGoogleCalPrefs);

  delete accounts;
  delete identities;
  delete servers;
  delete smtpservers;
  delete ldapservers;
  delete labelPrefs;
  delete calendarColorPrefs;
  delete calendarGoogleCalPrefs;

  nsCOMPtr<nsIFile> targetPrefsFile;
  mTargetProfile->Clone(getter_AddRefs(targetPrefsFile));
  targetPrefsFile->Append(aTargetPrefFileName);
  psvc->SavePrefFile(targetPrefsFile);

  return NS_OK;
}

nsresult csThunderbirdProfileMigrator::CopyAddressBookDirectories(nsVoidArray* aLdapServers, nsIPrefService* aPrefService)
{
  // each server has a pref ending with .filename. The value of that pref points to a profile which we
  // need to migrate.
  nsAutoString index;
  index.AppendInt(nsIMailProfileMigrator::ADDRESSBOOK_DATA);
  NOTIFY_OBSERVERS(MIGRATION_ITEMBEFOREMIGRATE, index.get());

  PRUint32 count = aLdapServers->Count();
  for (PRUint32 i = 0; i < count; ++i)
  {
    PrefBranchStruct* pref = (PrefBranchStruct*) aLdapServers->ElementAt(i);
    nsDependentCString prefName (pref->prefName);

    if (StringEndsWith(prefName, nsDependentCString(".filename")))
    {
      // should we be assuming utf-8 or ascii here?
      CopyFile(NS_ConvertUTF8toUTF16(pref->stringValue), NS_ConvertUTF8toUTF16(pref->stringValue));
    }

    // we don't need to do anything to the fileName pref itself
  }

  NOTIFY_OBSERVERS(MIGRATION_ITEMAFTERMIGRATE, index.get());

  return NS_OK;
}


nsresult csThunderbirdProfileMigrator::CopySignatureFiles(nsVoidArray* aIdentities, nsIPrefService* aPrefService)
{
  nsresult rv = NS_OK;

  PRUint32 count = aIdentities->Count();
  for (PRUint32 i = 0; i < count; ++i)
  {
    PrefBranchStruct* pref = (PrefBranchStruct*)aIdentities->ElementAt(i);
    nsDependentCString prefName (pref->prefName);

    // a partial fix for bug #255043
    // if the user's signature file from seamonkey lives in the
    // seamonkey profile root, we'll copy it over to the new
    // thunderbird profile root and thenn set the pref to the new value
    // note, this doesn't work for multiple signatures that live
    // below the seamonkey profile root
    if (StringEndsWith(prefName, nsDependentCString(".sig_file")))
    {
      // turn the pref into a nsILocalFile
      nsCOMPtr<nsILocalFile> srcSigFile = do_CreateInstance(NS_LOCAL_FILE_CONTRACTID);
      srcSigFile->SetPersistentDescriptor(nsDependentCString(pref->stringValue));

      nsCOMPtr<nsIFile> targetSigFile;
      rv = mTargetProfile->Clone(getter_AddRefs(targetSigFile));
      NS_ENSURE_SUCCESS(rv, rv);

      // now make the copy
      PRBool exists;
      srcSigFile->Exists(&exists);
      if (exists)
      {
        nsAutoString leafName;
        srcSigFile->GetLeafName(leafName);
        srcSigFile->CopyTo(targetSigFile,leafName); // will fail if we've already copied a sig file here
        targetSigFile->Append(leafName);

        // now write out the new descriptor
        nsCAutoString descriptorString;
        nsCOMPtr<nsILocalFile> localFile = do_QueryInterface(targetSigFile);
        localFile->GetPersistentDescriptor(descriptorString);
        NS_Free(pref->stringValue);
        pref->stringValue = ToNewCString(descriptorString);
      }
    }
  }
  return NS_OK;
}

nsresult csThunderbirdProfileMigrator::CopyMailFolders(nsVoidArray* aMailServers, nsIPrefService* aPrefService)
{
  // Each server has a .directory pref which points to the location of the mail data
  // for that server. We need to do two things for that case...
  // (1) Fix up the directory path for the new profile
  // (2) copy the mail folder data from the source directory pref to the destination directory pref

  nsresult rv = NS_OK;

  PRUint32 count = aMailServers->Count();
  for (PRUint32 i = 0; i < count; ++i)
  {
    PrefBranchStruct* pref = (PrefBranchStruct*)aMailServers->ElementAt(i);
    nsDependentCString prefName (pref->prefName);

    if (StringEndsWith(prefName, NS_LITERAL_CSTRING(".directory-rel"))) {
      // When the directories are modified below, we may change the .directory
      // pref. As we don't have a pref branch to modify at this stage and set
      // up the relative folders properly, we'll just remove all the
      // *.directory-rel prefs. Mailnews will cope with this, creating them
      // when it first needs them.
      if (pref->type == nsIPrefBranch::PREF_STRING)
        NS_Free(pref->stringValue);

      aMailServers->RemoveElementAt(i);
      // Now decrease i and count to match the removed element
      --i;
      --count;
    }
    else if (StringEndsWith(prefName, nsDependentCString(".directory")))
    {
      // let's try to get a branch for this particular server to simplify things
      prefName.Cut( prefName.Length() - strlen("directory"), strlen("directory"));
      prefName.Insert("mail.server.", 0);

      nsCOMPtr<nsIPrefBranch> serverBranch;
      aPrefService->GetBranch(prefName.get(), getter_AddRefs(serverBranch));

      if (!serverBranch)
        break; // should we clear out this server pref from aMailServers?

      nsCString serverType;
      serverBranch->GetCharPref("type", getter_Copies(serverType));

      nsCOMPtr<nsILocalFile> sourceMailFolder;
      serverBranch->GetComplexValue("directory", NS_GET_IID(nsILocalFile), getter_AddRefs(sourceMailFolder));

      // now based on type, we need to build a new destination path for the mail folders for this server
      nsCOMPtr<nsIFile> targetMailFolder;
      if (serverType.Equals("imap"))
      {
        mTargetProfile->Clone(getter_AddRefs(targetMailFolder));
        targetMailFolder->Append(IMAP_MAIL_DIR_50_NAME);
      }
      else if (serverType.Equals("none") || serverType.Equals("pop3"))
      {
        // local folders and POP3 servers go under <profile>\Mail
        mTargetProfile->Clone(getter_AddRefs(targetMailFolder));
        targetMailFolder->Append(MAIL_DIR_50_NAME);
      }
      else if (serverType.Equals("nntp"))
      {
        mTargetProfile->Clone(getter_AddRefs(targetMailFolder));
        targetMailFolder->Append(NEWS_DIR_50_NAME);
      }

      if (targetMailFolder)
      {
        // for all of our server types, append the host name to the directory as part of the new location
        nsCString hostName;
        serverBranch->GetCharPref("hostname", getter_Copies(hostName));
        targetMailFolder->Append(NS_ConvertASCIItoUTF16(hostName));

        // we should make sure the host name based directory we are going to migrate
        // the accounts into is unique. This protects against the case where the user
        // has multiple servers with the same host name.
        targetMailFolder->CreateUnique(nsIFile::DIRECTORY_TYPE, 0777);

        rv = RecursiveCopy(sourceMailFolder, targetMailFolder);
        // now we want to make sure the actual directory pref that gets
        // transformed into the new profile's pref.js has the right file
        // location.
        nsCAutoString descriptorString;
        nsCOMPtr<nsILocalFile> localFile = do_QueryInterface(targetMailFolder);
        localFile->GetPersistentDescriptor(descriptorString);
        NS_Free(pref->stringValue);
        pref->stringValue = ToNewCString(descriptorString);
      }
    }
    else if (StringEndsWith(prefName, nsDependentCString(".newsrc.file")))
    {
      // copy the news RC file into \News. this won't work if the user has different newsrc files for each account
      // I don't know what to do in that situation.

      nsCOMPtr<nsIFile> targetNewsRCFile;
      mTargetProfile->Clone(getter_AddRefs(targetNewsRCFile));
      targetNewsRCFile->Append(NEWS_DIR_50_NAME);

      // turn the pref into a nsILocalFile
      nsCOMPtr<nsILocalFile> srcNewsRCFile = do_CreateInstance(NS_LOCAL_FILE_CONTRACTID);
      srcNewsRCFile->SetPersistentDescriptor(nsDependentCString(pref->stringValue));

      // now make the copy
      PRBool exists;
      srcNewsRCFile->Exists(&exists);
      if (exists)
      {
        nsAutoString leafName;
        srcNewsRCFile->GetLeafName(leafName);
        srcNewsRCFile->CopyTo(targetNewsRCFile,leafName); // will fail if we've already copied a newsrc file here
        targetNewsRCFile->Append(leafName);

        // now write out the new descriptor
        nsCAutoString descriptorString;
        nsCOMPtr<nsILocalFile> localFile = do_QueryInterface(targetNewsRCFile);
        localFile->GetPersistentDescriptor(descriptorString);
        NS_Free(pref->stringValue);
        pref->stringValue = ToNewCString(descriptorString);
      }
    }
  }

  return NS_OK;
}

nsresult
csThunderbirdProfileMigrator::CopyPreferences(PRBool aReplace)
{
  nsresult rv = NS_OK;
  if (!aReplace)
    return rv;

  rv |= TransformPreferences(FILE_NAME_PREFS, FILE_NAME_PREFS);
  rv |= CopyFile(FILE_NAME_USER_PREFS, FILE_NAME_USER_PREFS);

  // Security Stuff
  rv |= CopyFile(FILE_NAME_CERT8DB, FILE_NAME_CERT8DB);
  rv |= CopyFile(FILE_NAME_KEY3DB, FILE_NAME_KEY3DB);
  rv |= CopyFile(FILE_NAME_SECMODDB, FILE_NAME_SECMODDB);

  // User MIME Type overrides
  rv |= CopyFile(FILE_NAME_MIMETYPES, FILE_NAME_MIMETYPES);
  rv |= CopyFile(FILE_NAME_PERSONALDICTIONARY, FILE_NAME_PERSONALDICTIONARY);
  rv |= CopyFile(FILE_NAME_MAILVIEWS, FILE_NAME_MAILVIEWS);
  return rv;
}

void csThunderbirdProfileMigrator::ReadBranch(const char * branchName, nsIPrefService* aPrefService,
                                            nsVoidArray* aPrefs)
{
  // Enumerate the branch
  nsCOMPtr<nsIPrefBranch> branch;
  aPrefService->GetBranch(branchName, getter_AddRefs(branch));

  PRUint32 count;
  char** prefs = nsnull;
  nsresult rv = branch->GetChildList("", &count, &prefs);
  if (NS_FAILED(rv)) return;

  for (PRUint32 i = 0; i < count; ++i) {
    // Save each pref's value into an array
    char* currPref = prefs[i];
    PRInt32 type;
    branch->GetPrefType(currPref, &type);
    PrefBranchStruct* pref = new PrefBranchStruct;
    pref->prefName = currPref;
    pref->type = type;
    switch (type) {
    case nsIPrefBranch::PREF_STRING:
      rv = branch->GetCharPref(currPref, &pref->stringValue);
      break;
    case nsIPrefBranch::PREF_BOOL:
      rv = branch->GetBoolPref(currPref, &pref->boolValue);
      break;
    case nsIPrefBranch::PREF_INT:
      rv = branch->GetIntPref(currPref, &pref->intValue);
      break;
    case nsIPrefBranch::PREF_INVALID:
      {
        nsCOMPtr<nsIPrefLocalizedString> str;
        rv = branch->GetComplexValue(currPref,
                                    NS_GET_IID(nsIPrefLocalizedString),
                                    getter_AddRefs(str));
        if (NS_SUCCEEDED(rv) && str)
          str->ToString(&pref->wstringValue);
      }
      break;
    }

    if (NS_SUCCEEDED(rv))
      aPrefs->AppendElement((void*)pref);
  }
}

void
csThunderbirdProfileMigrator::WriteBranch(const char * branchName, nsIPrefService* aPrefService,
                                        nsVoidArray* aPrefs)
{
  nsresult rv;

  // Enumerate the branch
  nsCOMPtr<nsIPrefBranch> branch;
  aPrefService->GetBranch(branchName, getter_AddRefs(branch));

  PRUint32 count = aPrefs->Count();
  for (PRUint32 i = 0; i < count; ++i) {
    PrefBranchStruct* pref = (PrefBranchStruct*)aPrefs->ElementAt(i);
    switch (pref->type) {
    case nsIPrefBranch::PREF_STRING:
      rv = branch->SetCharPref(pref->prefName, pref->stringValue);
      NS_Free(pref->stringValue);
      pref->stringValue = nsnull;
      break;
    case nsIPrefBranch::PREF_BOOL:
      rv = branch->SetBoolPref(pref->prefName, pref->boolValue);
      break;
    case nsIPrefBranch::PREF_INT:
      rv = branch->SetIntPref(pref->prefName, pref->intValue);
      break;
    case nsIPrefBranch::PREF_INVALID:
      nsCOMPtr<nsIPrefLocalizedString> pls(do_CreateInstance("@mozilla.org/pref-localizedstring;1"));
      pls->SetData(pref->wstringValue);
      rv = branch->SetComplexValue(pref->prefName,
                                   NS_GET_IID(nsIPrefLocalizedString),
                                   pls);
      NS_Free(pref->wstringValue);
      pref->wstringValue = nsnull;
      break;
    }
    NS_Free(pref->prefName);
    pref->prefName = nsnull;
    delete pref;
    pref = nsnull;
  }
  aPrefs->Clear();
}

nsresult csThunderbirdProfileMigrator::DummyCopyRoutine(PRBool aReplace)
{
  // place holder function only to fake the UI out into showing some migration process.
  return NS_OK;
}

nsresult
csThunderbirdProfileMigrator::CopyJunkTraining(PRBool aReplace)
{
  return aReplace ? CopyFile(FILE_NAME_JUNKTRAINING, FILE_NAME_JUNKTRAINING) : NS_OK;
}

nsresult
csThunderbirdProfileMigrator::CopyPasswords(PRBool aReplace)
{
  nsresult rv;

  nsCString signonsFileName;
  GetSignonFileName(aReplace, getter_Copies(signonsFileName));

  if (signonsFileName.IsEmpty())
    return NS_ERROR_FILE_NOT_FOUND;

  nsAutoString fileName;
  CopyASCIItoUTF16(signonsFileName, fileName);
  if (aReplace)
    rv = CopyFile(fileName, fileName);
  else {
    // don't do anything right now
  }
  return rv;
}

nsresult
csThunderbirdProfileMigrator::CopyCalendars(PRBool aReplace)
{
  nsresult rv = NS_OK;
  if(!aReplace)
    return rv;

  return CopyFile(FILE_NAME_CALENDARS, FILE_NAME_CALENDARS);
}
