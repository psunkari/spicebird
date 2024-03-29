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
 * The Original Code is The Browser Profile Migrator.
 *
 * The Initial Developer of the Original Code is Ben Goodger.
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *  Ben Goodger <ben@bengoodger.com>
 *  Scott MacGregor <mscott@mozilla.org>
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

#ifndef netscapeprofilemigratorbase___h___
#define netscapeprofilemigratorbase___h___

#include "nsILocalFile.h"
#include "nsIStringBundle.h"
#include "nsStringGlue.h"

class nsIFile;
class nsIPrefBranch;
class nsVoidArray;
class nsIMutableArray;

struct fileTransactionEntry {
  nsCOMPtr<nsIFile> srcFile;  // the src path including leaf name
  nsCOMPtr<nsIFile> destFile; // the destination path
  nsString newName; // only valid if the file should be renamed after getting copied
};


class nsNetscapeProfileMigratorBase
{
public:
  nsNetscapeProfileMigratorBase();
  virtual ~nsNetscapeProfileMigratorBase() { };

public:
  typedef nsresult(*prefConverter)(void*, nsIPrefBranch*);

  struct PrefTransform {
    const char*   sourcePrefName;
    const char*   targetPrefName;
    prefConverter prefGetterFunc;
    prefConverter prefSetterFunc;
    PRBool        prefHasValue;
    union {
      PRInt32     intValue;
      PRBool      boolValue;
      char*       stringValue;
    };
  };

  static nsresult GetString(void* aTransform, nsIPrefBranch* aBranch);
  static nsresult SetString(void* aTransform, nsIPrefBranch* aBranch);
  static nsresult GetWString(void* aTransform, nsIPrefBranch* aBranch);
  static nsresult SetWString(void* aTransform, nsIPrefBranch* aBranch);
  static nsresult SetWStringFromASCII(void* aTransform, nsIPrefBranch* aBranch);
  static nsresult GetBool(void* aTransform, nsIPrefBranch* aBranch);
  static nsresult SetBool(void* aTransform, nsIPrefBranch* aBranch);
  static nsresult GetInt(void* aTransform, nsIPrefBranch* aBranch);
  static nsresult SetInt(void* aTransform, nsIPrefBranch* aBranch);

  nsresult RecursiveCopy(nsIFile* srcDir, nsIFile* destDir); // helper routine

protected:
  nsresult GetProfileDataFromProfilesIni(nsILocalFile* aDataDir,
                                         nsIMutableArray* aProfileNames,
                                         nsIMutableArray* aProfileLocations);
  nsresult GetProfileDataFromRegistry(nsILocalFile* aRegistryFile,
                                      nsIMutableArray* aProfileNames,
                                      nsIMutableArray* aProfileLocations);

  nsresult CopyFile(const nsAString& aSourceFileName, const nsAString& aTargetFileName);

  nsresult GetSignonFileName(PRBool aReplace, char** aFileName);
  nsresult LocateSignonsFile(char** aResult);

protected:
  nsCOMPtr<nsILocalFile> mSourceProfile;
  nsCOMPtr<nsIFile> mTargetProfile;
  nsCOMPtr<nsIStringBundle> mBundle;

  nsVoidArray * mFileCopyTransactions; // list of src/destination files we still have to copy into the new profile directory
  PRUint32 mFileCopyTransactionIndex;
};
 
#endif
