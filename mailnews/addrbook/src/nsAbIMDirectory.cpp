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
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Seth Spitzer <sspitzer@netscape.com>
 *   Pierre Phaneuf <pp@ludusdesign.com>
 *   Siva Edpuganti <sivakrishna@synovel.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
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

#include "nsAbIMDirectory.h" 
#include "nsAbMDBDirectory.h" 
#include "nsIAbIMDirectory.h" 
#include "nsIPrefService.h"
#include "nsServiceManagerUtils.h"

nsAbIMDirectory::nsAbIMDirectory(void):
     nsAbMDBDirectory()
{
}

nsAbIMDirectory::~nsAbIMDirectory(void)
{
}

NS_IMPL_ISUPPORTS_INHERITED0(nsAbIMDirectory, nsAbMDBDirectory)

NS_IMETHODIMP nsAbIMDirectory::GetReadOnly(PRInt32 *aReadOnly)
{
  NS_ENSURE_ARG_POINTER(aReadOnly);
  *aReadOnly = PR_TRUE;
  return NS_OK;
}

NS_IMETHODIMP nsAbIMDirectory::Init(const char *aUri)
{
  // We need to ensure  that the m_DirPrefId is initialized properly
  nsDependentCString uri(aUri);

  if (uri.Find("MailList") != -1)
    m_IsMailList = PR_TRUE;

  // Mailing lists don't have their own prefs.
  if (m_DirPrefId.IsEmpty() && !m_IsMailList)
  {
    // Find the first ? (of the search params) if there is one.
    // We know we can start at the end of the moz-abmdbdirectory:// because
    // that's the URI we should have been passed.
    PRInt32 searchCharLocation = uri.FindChar('?', kIMDirectoryRootLen);

    nsCAutoString filename;

    // extract the filename from the uri.
    if (searchCharLocation == -1)
      filename = StringTail(uri, uri.Length() - kIMDirectoryRootLen);
    else
      filename = Substring(uri, kIMDirectoryRootLen, searchCharLocation - kIMDirectoryRootLen);

    // Get the pref servers and the address book directory branch
    nsresult rv;
    nsCOMPtr<nsIPrefService> prefService(do_GetService(NS_PREFSERVICE_CONTRACTID, &rv));
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsIPrefBranch> prefBranch;
    rv = prefService->GetBranch(NS_LITERAL_CSTRING(PREF_LDAP_SERVER_TREE_NAME ".").get(),
                                getter_AddRefs(prefBranch));
    NS_ENSURE_SUCCESS(rv, rv);

    char** childArray;
    PRUint32 childCount, i;
    PRInt32 dotOffset;
    nsCString childValue;
    nsDependentCString child;

    rv = prefBranch->GetChildList("", &childCount, &childArray);
    NS_ENSURE_SUCCESS(rv, rv);

    for (i = 0; i < childCount; ++i)
    {
      child.Assign(childArray[i]);

      if (StringEndsWith(child, NS_LITERAL_CSTRING(".filename")))
      {
        if (NS_SUCCEEDED(prefBranch->GetCharPref(child.get(),
                                                 getter_Copies(childValue))))
        {
          if (childValue == filename)
          {
            dotOffset = child.RFindChar('.');
            if (dotOffset != -1)
            {
              nsCAutoString prefName(StringHead(child, dotOffset));
              m_DirPrefId.AssignLiteral(PREF_LDAP_SERVER_TREE_NAME ".");
              m_DirPrefId.Append(prefName);
            }
          }
        }
      }
    }     
    NS_FREE_XPCOM_ALLOCATED_POINTER_ARRAY(childCount, childArray);

    NS_ASSERTION(!m_DirPrefId.IsEmpty(),
                 "Error, Could not set m_DirPrefId in nsAbIMDirectory::Init");
  }

  return nsAbMDBDirectory::Init(aUri);
}
