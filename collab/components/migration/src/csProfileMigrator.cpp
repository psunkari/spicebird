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
 *  Benjamin Smedberg <bsmedberg@covad.net>
 *  Sunil Mohan Adapa <sunil@synovel.com>
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

#include "nsIDOMWindowInternal.h"
#include "nsIWindowWatcher.h"
#include "nsISupportsPrimitives.h"
#include "nsISupportsArray.h"
#include "nsComponentManagerUtils.h"
#include "nsServiceManagerUtils.h"
#include "nsMailMigrationCID.h"
#include "csProfileMigrator.h"

#define MIGRATION_WIZARD_FE_URL "chrome://messenger/content/migration/migration.xul"
#define MIGRATION_WIZARD_FE_FEATURES "chrome,dialog,modal,centerscreen"

NS_IMETHODIMP
csProfileMigrator::Migrate(nsIProfileStartup* aStartup)
{
  nsCAutoString key;
  nsCOMPtr<nsIMailProfileMigrator> mailMigrator;
  nsresult rv = GetDefaultMailMigratorKey(key, mailMigrator);
  NS_ENSURE_SUCCESS(rv, rv); // abort migration if we failed to get a mailMigrator (if we were supposed to)

  nsCOMPtr<nsISupportsCString> cstr (do_CreateInstance("@mozilla.org/supports-cstring;1"));
  NS_ENSURE_TRUE(cstr, NS_ERROR_OUT_OF_MEMORY);
  cstr->SetData(key);

  // By opening the Migration FE with a supplied mailMigrator, it will automatically
  // migrate from it.
  nsCOMPtr<nsIWindowWatcher> ww (do_GetService(NS_WINDOWWATCHER_CONTRACTID));
  nsCOMPtr<nsISupportsArray> params;
  NS_NewISupportsArray(getter_AddRefs(params));
  if (!ww || !params) return NS_ERROR_FAILURE;

  params->AppendElement(cstr);
  params->AppendElement(mailMigrator);
  params->AppendElement(aStartup);

  nsCOMPtr<nsIDOMWindow> migrateWizard;
  return ww->OpenWindow(nsnull,
                        MIGRATION_WIZARD_FE_URL,
                        "_blank",
                        MIGRATION_WIZARD_FE_FEATURES,
                        params,
                        getter_AddRefs(migrateWizard));
}

nsresult
csProfileMigrator::GetDefaultMailMigratorKey(nsACString& aKey, nsCOMPtr<nsIMailProfileMigrator>& mailMigrator)
{
  nsresult rv;

  rv = nsProfileMigrator::GetDefaultMailMigratorKey(aKey, mailMigrator);
  if (!NS_FAILED(rv))
    return rv;

  #define MAX_SOURCE_LENGTH 15
  const char sources[][MAX_SOURCE_LENGTH] = {
    "thunderbird",
    ""
  };

  NS_NAMED_LITERAL_CSTRING(migratorPrefix,
                           NS_MAILPROFILEMIGRATOR_CONTRACTID_PREFIX);
  for (PRUint32 i = 0; sources[i][0]; ++i)
  {
    nsCAutoString migratorID;
    migratorID.Assign(migratorPrefix);
    migratorID.Append(sources[i]);
    mailMigrator = do_CreateInstance(migratorID.get());
    if (!mailMigrator)
      continue;

    PRBool exists = PR_FALSE;
    mailMigrator->GetSourceExists(&exists);
    if (exists)
    {
      mailMigrator = nsnull;
      return NS_OK;
    }
  }

  return NS_ERROR_NOT_AVAILABLE;
}

NS_IMETHODIMP
csProfileMigrator::Import()
{
  if (ImportRegistryProfiles(NS_LITERAL_CSTRING("Spicebird")))
    return NS_OK;

  return NS_ERROR_FAILURE;
}
