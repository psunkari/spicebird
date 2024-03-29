/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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
 *   Scott Collins <scc@mozilla.org>: |do_QueryElementAt|
 *   Pierre Phaneuf <pp@ludusdesign.com>
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

#include "nsISupportsArray.h"

nsresult NS_FASTCALL
nsQueryElementAt::operator()(const nsIID& aIID, void** aResult) const
{
  nsresult status = mCollection ?
    mCollection->QueryElementAt(mIndex, aIID, aResult) : NS_ERROR_NULL_POINTER;
  if (mErrorPtr)
    *mErrorPtr = status;
  return status;
}

class nsArrayEnumerator : public nsISimpleEnumerator
{
public:
  // nsISupports interface
  NS_DECL_ISUPPORTS

  // nsISimpleEnumerator interface
  NS_DECL_NSISIMPLEENUMERATOR

  // nsArrayEnumerator methods
  nsArrayEnumerator(nsISupportsArray* aValueArray);

protected:
  nsCOMPtr<nsISupportsArray> mValueArray;
  PRInt32 mIndex;
};

nsArrayEnumerator::nsArrayEnumerator(nsISupportsArray* aValueArray)
  : mValueArray(aValueArray),
    mIndex(0)
{
}

NS_IMPL_ISUPPORTS1(nsArrayEnumerator, nsISimpleEnumerator)

NS_IMETHODIMP
nsArrayEnumerator::HasMoreElements(PRBool* aResult)
{
  NS_ENSURE_ARG_POINTER(aResult);

  if (!mValueArray) {
    *aResult = PR_FALSE;
    return NS_OK;
  }

  PRUint32 cnt;
  nsresult rv = mValueArray->Count(&cnt);
  if (NS_FAILED(rv)) return rv;
  *aResult = (mIndex < (PRInt32) cnt);
  return NS_OK;
}

NS_IMETHODIMP
nsArrayEnumerator::GetNext(nsISupports** aResult)
{
  NS_ENSURE_ARG_POINTER(aResult);

  if (!mValueArray) {
    *aResult = nsnull;
    return NS_OK;
  }

  PRUint32 cnt;
  nsresult rv = mValueArray->Count(&cnt);
  if (NS_FAILED(rv)) return rv;
  if (mIndex >= (PRInt32) cnt)
    return NS_ERROR_UNEXPECTED;

  *aResult = mValueArray->ElementAt(mIndex++);
  return NS_OK;
}

nsresult
 NS_NewArrayEnumerator(nsISimpleEnumerator** result, nsISupportsArray* array) {
    *result = new nsArrayEnumerator(array);
    NS_IF_ADDREF(*result);
    return *result ? NS_OK : NS_ERROR_OUT_OF_MEMORY;
}
