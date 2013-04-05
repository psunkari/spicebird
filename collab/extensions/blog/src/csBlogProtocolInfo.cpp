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
 * The Original Code is mozilla mailnews.
 *
 * The Initial Developer of the Original Code is
 * Seth Spitzer <sspitzer@mozilla.org>.
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Sunil Mohan Adapa <sunil@synovel.com>
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

#include "nsCOMPtr.h"
#include "nsILocalFile.h"
#include "nsMsgUtils.h"
#include "nsMailDirServiceDefs.h"

#include "csBlogProtocolInfo.h"

#define PREF_MAIL_ROOT_BLOG	"mail.root.blog"
#define PREF_MAIL_ROOT_BLOG_REL "mail.root.blog-rel"

csBlogProtocolInfo::csBlogProtocolInfo()
{
}

csBlogProtocolInfo::~csBlogProtocolInfo()
{
}

NS_IMPL_ISUPPORTS1(csBlogProtocolInfo,
                   nsIMsgProtocolInfo)
                   
NS_IMETHODIMP csBlogProtocolInfo::GetDefaultLocalPath(nsILocalFile **aResult)
{
  NS_ENSURE_ARG_POINTER(aResult);
  *aResult = nsnull;

  PRBool havePref;
  nsCOMPtr<nsILocalFile> localFile;
  // XXX: We should create our own folder for Blogs instead of creating inside
  // Mails directory of the profile directory. Like Imap does.
  nsresult rv = NS_GetPersistentFile(PREF_MAIL_ROOT_BLOG_REL,
                                     PREF_MAIL_ROOT_BLOG,
                                     NS_APP_MAIL_50_DIR,
                                     havePref,
                                     getter_AddRefs(localFile));

  PRBool exists;
  rv = localFile->Exists(&exists);
  if (NS_SUCCEEDED(rv) && !exists)
    rv = localFile->Create(nsIFile::DIRECTORY_TYPE, 0775);
  NS_ENSURE_SUCCESS(rv, rv);

  if (!havePref || !exists)
  {
    rv = NS_SetPersistentFile(PREF_MAIL_ROOT_BLOG_REL, PREF_MAIL_ROOT_BLOG, localFile);
    NS_ASSERTION(NS_SUCCEEDED(rv), "Failed to set root dir pref.");
  }

  localFile.swap(*aResult);
  return NS_OK;
}

NS_IMETHODIMP csBlogProtocolInfo::SetDefaultLocalPath(nsILocalFile * aPath)
{
    NS_ENSURE_ARG(aPath);
    return NS_SetPersistentFile(PREF_MAIL_ROOT_BLOG_REL, PREF_MAIL_ROOT_BLOG, aPath);
}

NS_IMETHODIMP csBlogProtocolInfo::GetServerIID(nsIID * *aServerIID)
{
    NS_ASSERTION(0,"foo");
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP csBlogProtocolInfo::GetRequiresUsername(PRBool *aRequiresUsername)
{
    NS_ASSERTION(0,"foo");
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP csBlogProtocolInfo::GetPreflightPrettyNameWithEmailAddress(PRBool *aPreflightPrettyNameWithEmailAddress)
{
    NS_ASSERTION(0,"foo");
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP csBlogProtocolInfo::GetCanDelete(PRBool *aCanDelete)
{
    NS_ENSURE_ARG_POINTER(aCanDelete);
    *aCanDelete = PR_TRUE;
    return NS_OK;
}

NS_IMETHODIMP csBlogProtocolInfo::GetCanLoginAtStartUp(PRBool *aCanLoginAtStartUp)
{
    NS_ENSURE_ARG_POINTER(aCanLoginAtStartUp);
    *aCanLoginAtStartUp = PR_TRUE;
    return NS_OK;
}

NS_IMETHODIMP csBlogProtocolInfo::GetCanDuplicate(PRBool *aCanDuplicate)
{
    NS_ENSURE_ARG_POINTER(aCanDuplicate);
    *aCanDuplicate = PR_TRUE;
    return NS_OK;
}

NS_IMETHODIMP csBlogProtocolInfo::GetDefaultServerPort(PRBool isSecure, PRInt32 *_retval)
{
    *_retval = -1;
    return NS_OK;
}

NS_IMETHODIMP csBlogProtocolInfo::GetCanGetMessages(PRBool *aCanGetMessages)
{
    NS_ENSURE_ARG_POINTER(aCanGetMessages);
    *aCanGetMessages = PR_TRUE;
    return NS_OK;
}

NS_IMETHODIMP csBlogProtocolInfo::GetCanGetIncomingMessages(PRBool *aCanGetIncomingMessages)
{
    NS_ENSURE_ARG_POINTER(aCanGetIncomingMessages);
    *aCanGetIncomingMessages = PR_TRUE;
    return NS_OK;
}

NS_IMETHODIMP csBlogProtocolInfo::GetDefaultDoBiff(PRBool *aDefaultDoBiff)
{
    NS_ENSURE_ARG_POINTER(aDefaultDoBiff);
    // by default, do biff for RSS feeds
    *aDefaultDoBiff = PR_TRUE;    
    return NS_OK;
}

NS_IMETHODIMP csBlogProtocolInfo::GetShowComposeMsgLink(PRBool *aShowComposeMsgLink)
{
    NS_ENSURE_ARG_POINTER(aShowComposeMsgLink);
    *aShowComposeMsgLink = PR_FALSE;    
    return NS_OK;
}

NS_IMETHODIMP csBlogProtocolInfo::GetSpecialFoldersDeletionAllowed(PRBool *aSpecialFoldersDeletionAllowed)
{
    NS_ASSERTION(0,"foo");
    return NS_ERROR_NOT_IMPLEMENTED;
}
