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
 * Portions created by the Initial Developer are Copyright (C) 2001
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Paul Sandoz <paul.sandoz@sun.com>
 *   Mark Banner <mark@standard8.demon.co.uk>
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

#include "nsAbView.h"
#include "nsISupports.h"
#include "nsCOMPtr.h"
#include "nsIServiceManager.h"
#include "nsIAbCard.h"
#include "nsILocale.h"
#include "nsILocaleService.h"
#include "prmem.h"
#include "nsCollationCID.h"
#include "nsIAbManager.h"
#include "nsAbBaseCID.h"
#include "nsXPCOM.h"
#include "nsISupportsPrimitives.h"
#include "nsITreeColumns.h"
#include "nsCRTGlue.h"
#include "nsIMutableArray.h"
#include "nsIPrefService.h"
#include "nsIPrefBranch2.h"
#include "nsIStringBundle.h"
#include "nsIPrefLocalizedString.h"
#include "nsArrayUtils.h"
#include "nsIAddrDatabase.h" // for kPriEmailColumn

#define CARD_NOT_FOUND -1
#define ALL_ROWS -1

#define PREF_MAIL_ADDR_BOOK_LASTNAMEFIRST "mail.addr_book.lastnamefirst"
#define PREF_MAIL_ADDR_BOOK_DISPLAYNAME_AUTOGENERATION "mail.addr_book.displayName.autoGeneration"
#define PREF_MAIL_ADDR_BOOK_DISPLAYNAME_LASTNAMEFIRST "mail.addr_book.displayName.lastnamefirst"

// Also, our default primary sort
#define GENERATED_NAME_COLUMN_ID "GeneratedName" 

NS_IMPL_ISUPPORTS4(nsAbView, nsIAbView, nsITreeView, nsIAbListener, nsIObserver)

nsAbView::nsAbView() : mInitialized(PR_FALSE),
                       mSuppressSelectionChange(PR_FALSE),
                       mSuppressCountChange(PR_FALSE),
                       mGeneratedNameFormat(0)
{
  mMailListAtom = do_GetAtom("MailList");
  mCustomColumnHandlers.Init();
}

nsAbView::~nsAbView()
{
  if (mInitialized) {
    NS_ASSERTION(NS_SUCCEEDED(ClearView()), "failed to close view");
  }
}

NS_IMETHODIMP nsAbView::ClearView()
{
  mDirectory = nsnull;
  mAbViewListener = nsnull;
  if (mTree)
    mTree->SetView(nsnull);
  mTree = nsnull;
  mTreeSelection = nsnull;

  if (mInitialized)
  {
    nsresult rv;
    mInitialized = PR_FALSE;
    nsCOMPtr<nsIPrefBranch2> pbi(do_GetService(NS_PREFSERVICE_CONTRACTID,
                                               &rv));
    NS_ENSURE_SUCCESS(rv,rv);

    rv = pbi->RemoveObserver(PREF_MAIL_ADDR_BOOK_LASTNAMEFIRST, this);
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsIAbManager> abManager(do_GetService(NS_ABMANAGER_CONTRACTID,
                                                   &rv));
    NS_ENSURE_SUCCESS(rv, rv);

    rv = abManager->RemoveAddressBookListener(this);
    NS_ENSURE_SUCCESS(rv, rv);
  }

  PRInt32 i = mCards.Count();
  while(i-- > 0)
    NS_ASSERTION(NS_SUCCEEDED(RemoveCardAt(i)), "remove card failed\n");

  return NS_OK;
}

nsresult nsAbView::RemoveCardAt(PRInt32 row)
{
  nsresult rv;

  AbCard *abcard = (AbCard*) (mCards.ElementAt(row));
  NS_IF_RELEASE(abcard->card);
  mCards.RemoveElementAt(row);
  PR_FREEIF(abcard->primaryCollationKey);
  PR_FREEIF(abcard->secondaryCollationKey);
  PR_FREEIF(abcard);

  
  // This needs to happen after we remove the card, as RowCountChanged() will call GetRowCount()
  if (mTree) {
    rv = mTree->RowCountChanged(row, -1);
    NS_ENSURE_SUCCESS(rv,rv);
  }

  if (mAbViewListener && !mSuppressCountChange) {
    rv = mAbViewListener->OnCountChanged(mCards.Count());
    NS_ENSURE_SUCCESS(rv,rv);
  }
  return NS_OK;
}

nsresult nsAbView::SetGeneratedNameFormatFromPrefs()
{
  nsresult rv;
  nsCOMPtr<nsIPrefBranch2> prefBranchInt(do_GetService(NS_PREFSERVICE_CONTRACTID, &rv));
  NS_ENSURE_SUCCESS(rv,rv);

  return prefBranchInt->GetIntPref(PREF_MAIL_ADDR_BOOK_LASTNAMEFIRST, &mGeneratedNameFormat);
}

nsresult nsAbView::Initialize()
{
  if (mInitialized)
    return NS_OK;

  mInitialized = PR_TRUE;

  nsresult rv;
  nsCOMPtr<nsIAbManager> abManager(do_GetService(NS_ABMANAGER_CONTRACTID, &rv));
  NS_ENSURE_SUCCESS(rv, rv);

  rv = abManager->AddAddressBookListener(this, nsIAbListener::all);
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIPrefBranch2> pbi(do_GetService(NS_PREFSERVICE_CONTRACTID, &rv));
  NS_ENSURE_SUCCESS(rv, rv);

  rv = pbi->AddObserver(PREF_MAIL_ADDR_BOOK_LASTNAMEFIRST, this, PR_FALSE);
  NS_ENSURE_SUCCESS(rv, rv);

  if (!mABBundle)
  {
    nsCOMPtr<nsIStringBundleService> stringBundleService =
      do_GetService(NS_STRINGBUNDLE_CONTRACTID, &rv); 
    NS_ENSURE_SUCCESS(rv, rv);

    rv = stringBundleService->CreateBundle("chrome://messenger/locale/addressbook/addressBook.properties", getter_AddRefs(mABBundle));
    NS_ENSURE_SUCCESS(rv, rv);
  }

  return SetGeneratedNameFormatFromPrefs();
}

NS_IMETHODIMP nsAbView::SetView(nsIAbDirectory *aAddressBook,
                                nsIAbViewListener *aAbViewListener,
                                const nsAString &aSortColumn,
                                const nsAString &aSortDirection,
                                nsAString &aResult)
{
  // Ensure we are initialized
  nsresult rv = Initialize();

  mAbViewListener = nsnull;
  if (mTree)
  {
    // Try and speed deletion of old cards by disconnecting the tree from us.
    mTreeSelection->ClearSelection();
    mTree->SetView(nsnull);
  }

  // Clear out old cards
  PRInt32 i = mCards.Count();
  while(i-- > 0)
  {
    rv = RemoveCardAt(i);
    NS_ASSERTION(NS_SUCCEEDED(rv), "remove card failed\n");
  }

  mDirectory = aAddressBook;

  rv = EnumerateCards();
  NS_ENSURE_SUCCESS(rv, rv);

  NS_NAMED_LITERAL_STRING(generatedNameColumnId, GENERATED_NAME_COLUMN_ID);

  // See if the persisted sortColumn is valid.
  // It may not be, if you migrated from older versions, or switched between
  // a mozilla build and a commercial build, which have different columns.
  nsAutoString actualSortColumn;
  if (!generatedNameColumnId.Equals(aSortColumn) && mCards.Count()) {
    nsIAbCard *card = ((AbCard *)(mCards.ElementAt(0)))->card;
    nsString value;
    // XXX todo
    // Need to check if _Generic is valid.  GetCardValue() will always return NS_OK for _Generic
    // We're going to have to ask mDirectory if it is.
    // It might not be.  example:  _ScreenName is valid in Netscape, but not Mozilla.
    rv = GetCardValue(card, PromiseFlatString(aSortColumn).get(), value);
    if (NS_FAILED(rv))
      actualSortColumn = generatedNameColumnId;
    else
      actualSortColumn = aSortColumn;
  }
  else
    actualSortColumn = aSortColumn;

  rv = SortBy(actualSortColumn.get(), PromiseFlatString(aSortDirection).get());
  NS_ENSURE_SUCCESS(rv, rv);

  mAbViewListener = aAbViewListener;
  if (mAbViewListener && !mSuppressCountChange) {
    rv = mAbViewListener->OnCountChanged(mCards.Count());
    NS_ENSURE_SUCCESS(rv, rv);
  }

  aResult = actualSortColumn;
  return NS_OK;
}

NS_IMETHODIMP nsAbView::GetDirectory(nsIAbDirectory **aDirectory)
{
  NS_ENSURE_ARG_POINTER(aDirectory);
  NS_IF_ADDREF(*aDirectory = mDirectory);
  return NS_OK;
}

nsresult nsAbView::EnumerateCards()
{
  nsresult rv;    
  nsCOMPtr<nsISimpleEnumerator> cardsEnumerator;
  nsCOMPtr<nsIAbCard> card;

  if (!mDirectory)
    return NS_ERROR_UNEXPECTED;

  rv = mDirectory->GetChildCards(getter_AddRefs(cardsEnumerator));
  if (NS_SUCCEEDED(rv) && cardsEnumerator)
  {
    nsCOMPtr<nsISupports> item;
    PRBool more;
    while (NS_SUCCEEDED(cardsEnumerator->HasMoreElements(&more)) && more)
    {
      rv = cardsEnumerator->GetNext(getter_AddRefs(item));
      if (NS_SUCCEEDED(rv))
      {
        nsCOMPtr <nsIAbCard> card = do_QueryInterface(item);
        // Malloc these from an arena
        AbCard *abcard = (AbCard *) PR_Calloc(1, sizeof(struct AbCard));
        if (!abcard) 
          return NS_ERROR_OUT_OF_MEMORY;

        abcard->card = card;
        NS_IF_ADDREF(abcard->card);

        // XXX todo
        // Would it be better to do an insertion sort, than append and sort?
        // XXX todo
        // If we knew how many cards there was going to be
        // we could allocate an array of the size,
        // instead of growing and copying as we append.
        rv = mCards.AppendElement((void *)abcard);
        NS_ASSERTION(NS_SUCCEEDED(rv), "failed to append card");
      }
    }
  }

  return NS_OK;
}

NS_IMETHODIMP nsAbView::GetRowCount(PRInt32 *aRowCount)
{
  *aRowCount = mCards.Count();
  return NS_OK;
}

NS_IMETHODIMP nsAbView::GetSelection(nsITreeSelection * *aSelection)
{
  NS_IF_ADDREF(*aSelection = mTreeSelection);
  return NS_OK;
}

NS_IMETHODIMP nsAbView::SetSelection(nsITreeSelection * aSelection)
{
  mTreeSelection = aSelection;
  return NS_OK;
}

NS_IMETHODIMP nsAbView::GetRowProperties(PRInt32 index, nsISupportsArray *properties)
{
    return NS_OK;
}

NS_IMETHODIMP nsAbView::GetCellProperties(PRInt32 row, nsITreeColumn* col, nsISupportsArray *properties)
{
  NS_ENSURE_TRUE(row >= 0, NS_ERROR_UNEXPECTED);

  if (mCards.Count() <= row)
    return NS_OK;

  const PRUnichar* colID;
  col->GetIdConst(&colID);

  // Give custom handlers a chance to set the properties
  nsIAbCustomColumnHandler *colHandler = nsnull;
  mCustomColumnHandlers.Get(nsDependentString(colID), &colHandler);
  if (colHandler) 
    colHandler->GetCellProperties(row, col, properties);

  // "G" == "GeneratedName"
  if (colID[0] != PRUnichar('G'))
    return NS_OK;

  nsIAbCard *card = ((AbCard *)(mCards.ElementAt(row)))->card;

  PRBool isMailList;
  nsresult rv = card->GetIsMailList(&isMailList);
  NS_ENSURE_SUCCESS(rv,rv);

  if (isMailList) {
    rv = properties->AppendElement(mMailListAtom);  
    NS_ENSURE_SUCCESS(rv,rv);
  }

  return NS_OK;
}

NS_IMETHODIMP nsAbView::GetColumnProperties(nsITreeColumn* col, nsISupportsArray *properties)
{
    return NS_OK;
}

NS_IMETHODIMP nsAbView::IsContainer(PRInt32 index, PRBool *_retval)
{
    *_retval = PR_FALSE;
    return NS_OK;
}

NS_IMETHODIMP nsAbView::IsContainerOpen(PRInt32 index, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP nsAbView::IsContainerEmpty(PRInt32 index, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP nsAbView::IsSeparator(PRInt32 index, PRBool *_retval)
{
  *_retval = PR_FALSE;
  return NS_OK;
}

NS_IMETHODIMP nsAbView::IsSorted(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

#ifdef MOZILLA_1_9_1_BRANCH
NS_IMETHODIMP nsAbView::CanDrop(PRInt32 index, PRInt32 orientation, PRBool *_retval)
#else
NS_IMETHODIMP nsAbView::CanDrop(PRInt32 index,
                                PRInt32 orientation,
                                nsIDOMDataTransfer *dataTransfer,
                                PRBool *_retval)
#endif
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

#ifdef MOZILLA_1_9_1_BRANCH
NS_IMETHODIMP nsAbView::Drop(PRInt32 row, PRInt32 orientation)
#else
NS_IMETHODIMP nsAbView::Drop(PRInt32 row,
                             PRInt32 orientation,
                             nsIDOMDataTransfer *dataTransfer)
#endif
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP nsAbView::GetParentIndex(PRInt32 rowIndex, PRInt32 *_retval)
{
  *_retval = -1;
  return NS_OK;
}

NS_IMETHODIMP nsAbView::HasNextSibling(PRInt32 rowIndex, PRInt32 afterIndex, PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP nsAbView::GetLevel(PRInt32 index, PRInt32 *_retval)
{
  *_retval = 0;
  return NS_OK;
}

NS_IMETHODIMP nsAbView::GetImageSrc(PRInt32 row, nsITreeColumn* col, nsAString& _retval)
{
  return NS_OK;
}

NS_IMETHODIMP nsAbView::GetProgressMode(PRInt32 row, nsITreeColumn* col, PRInt32* _retval)
{
  return NS_OK;
}

NS_IMETHODIMP nsAbView::GetCellValue(PRInt32 row, nsITreeColumn* col, nsAString& _retval)
{
  return NS_OK;
}

nsresult nsAbView::GetCardValue(nsIAbCard *card, const PRUnichar *colID,
                                nsAString &_retval)
{
  // "G" == "GeneratedName", "_P" == "_PhoneticName"
  // else, standard column (like PrimaryEmail and _AimScreenName)
  if (colID[0] == PRUnichar('G'))
    return card->GenerateName(mGeneratedNameFormat, mABBundle, _retval);

  if (colID[0] == PRUnichar('_') && colID[1] == PRUnichar('P'))
    // Use LN/FN order for the phonetic name
    return card->GeneratePhoneticName(PR_TRUE, _retval);

  nsresult rv = card->GetPropertyAsAString(NS_ConvertUTF16toUTF8(colID).get(), _retval);
  if (rv == NS_ERROR_NOT_AVAILABLE) {
    rv = NS_OK;
    _retval.Truncate();
  }
  return rv;
}

nsresult nsAbView::RefreshTree()
{
  nsresult rv;

  // The PREF_MAIL_ADDR_BOOK_LASTNAMEFIRST pref affects how the GeneratedName column looks.
  // so if the GeneratedName is our primary or secondary sort,
  // we need to resort.
  // the same applies for kPhoneticNameColumn
  //
  // XXX optimize me
  // PrimaryEmail is always the secondary sort, unless it is currently the
  // primary sort.  So, if PrimaryEmail is the primary sort,
  // GeneratedName might be the secondary sort.
  //
  // One day, we can get fancy and remember what the secondary sort is.
  // We do that, we can fix this code. At best, it will turn a sort into a invalidate.
  // 
  // If neither the primary nor the secondary sorts are GeneratedName (or kPhoneticNameColumn),
  // all we have to do is invalidate (to show the new GeneratedNames),
  // but the sort will not change.
  if (mSortColumn.EqualsLiteral(GENERATED_NAME_COLUMN_ID) ||
      mSortColumn.EqualsLiteral(kPriEmailProperty) ||
      mSortColumn.EqualsLiteral(kPhoneticNameColumn)) {
    rv = SortBy(mSortColumn.get(), mSortDirection.get());
  }
  else {
    rv = InvalidateTree(ALL_ROWS);

    // Although the selection hasn't changed, the card that is selected may need
    // to be displayed differently, therefore pretend that the selection has
    // changed to force that update.
    SelectionChanged();
  }

  return rv;
}

NS_IMETHODIMP nsAbView::GetCellText(PRInt32 row, nsITreeColumn* col, nsAString& _retval)
{
  NS_ENSURE_TRUE(row >= 0 && row < mCards.Count(), NS_ERROR_UNEXPECTED);

  nsIAbCard *card = ((AbCard *)(mCards.ElementAt(row)))->card;
  const PRUnichar* colID;
  col->GetIdConst(&colID);

  nsIAbCustomColumnHandler *colHandler = nsnull;
  mCustomColumnHandlers.Get(nsDependentString(colID), &colHandler);
  if (colHandler){
    colHandler->GetCellText(row, col, _retval);
    return NS_OK;
  }

  return GetCardValue(card, colID, _retval);
}

NS_IMETHODIMP nsAbView::SetTree(nsITreeBoxObject *tree)
{
  mTree = tree;
  return NS_OK;
}

NS_IMETHODIMP nsAbView::ToggleOpenState(PRInt32 index)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP nsAbView::CycleHeader(nsITreeColumn* col)
{
  return NS_OK;
}

nsresult nsAbView::InvalidateTree(PRInt32 row)
{
  if (!mTree)
    return NS_OK;
  
  if (row == ALL_ROWS)
    return mTree->Invalidate();
  else
    return mTree->InvalidateRow(row);
}

NS_IMETHODIMP nsAbView::SelectionChanged()
{
  if (mAbViewListener && !mSuppressSelectionChange) {
    nsresult rv = mAbViewListener->OnSelectionChanged();
    NS_ENSURE_SUCCESS(rv,rv);
  }
  return NS_OK;
}

NS_IMETHODIMP nsAbView::CycleCell(PRInt32 row, nsITreeColumn* col)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP nsAbView::IsEditable(PRInt32 row, nsITreeColumn* col, PRBool* _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP nsAbView::IsSelectable(PRInt32 row, nsITreeColumn* col, PRBool* _retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP nsAbView::SetCellValue(PRInt32 row, nsITreeColumn* col, const nsAString& value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP nsAbView::SetCellText(PRInt32 row, nsITreeColumn* col, const nsAString& value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP nsAbView::PerformAction(const PRUnichar *action)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP nsAbView::PerformActionOnRow(const PRUnichar *action, PRInt32 row)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP nsAbView::PerformActionOnCell(const PRUnichar *action, PRInt32 row, nsITreeColumn* col)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP nsAbView::GetCardFromRow(PRInt32 row, nsIAbCard **aCard)
{
  *aCard = nsnull;  
  if (mCards.Count() <= row) {
    return NS_OK;
  }

  NS_ENSURE_TRUE(row >= 0, NS_ERROR_UNEXPECTED);

  AbCard *a = ((AbCard *)(mCards.ElementAt(row)));
  if (!a)
      return NS_OK;

  NS_IF_ADDREF(*aCard = a->card);
  return NS_OK;
}

#define DESCENDING_SORT_FACTOR -1
#define ASCENDING_SORT_FACTOR 1

typedef struct SortClosure
{
  const PRUnichar *colID;
  PRInt32 factor;
  nsAbView *abView;
} SortClosure;

static int
inplaceSortCallback(const void *data1, const void *data2, void *privateData)
{
  AbCard *card1 = (AbCard *)data1;
  AbCard *card2 = (AbCard *)data2;
  
  SortClosure *closure = (SortClosure *) privateData;
  
  PRInt32 sortValue;
  
  // If we are sorting the "PrimaryEmail", swap the collation keys, as the secondary is always the
  // PrimaryEmail. Use the last primary key as the secondary key.
  //
  // "Pr" to distinguish "PrimaryEmail" from "PagerNumber"
  if (closure->colID[0] == PRUnichar('P') && closure->colID[1] == PRUnichar('r')) {
    sortValue = closure->abView->CompareCollationKeys(card1->secondaryCollationKey,card1->secondaryCollationKeyLen,card2->secondaryCollationKey,card2->secondaryCollationKeyLen);
    if (sortValue)
      return sortValue * closure->factor;
    else
      return closure->abView->CompareCollationKeys(card1->primaryCollationKey,card1->primaryCollationKeyLen,card2->primaryCollationKey,card2->primaryCollationKeyLen) * (closure->factor);
  }
  else {
    sortValue = closure->abView->CompareCollationKeys(card1->primaryCollationKey,card1->primaryCollationKeyLen,card2->primaryCollationKey,card2->primaryCollationKeyLen);
    if (sortValue)
      return sortValue * (closure->factor);
    else
      return closure->abView->CompareCollationKeys(card1->secondaryCollationKey,card1->secondaryCollationKeyLen,card2->secondaryCollationKey,card2->secondaryCollationKeyLen) * (closure->factor);
  }
}

static void SetSortClosure(const PRUnichar *sortColumn, const PRUnichar *sortDirection, nsAbView *abView, SortClosure *closure)
{
  closure->colID = sortColumn;
  
  if (sortDirection && !NS_strcmp(sortDirection, NS_LITERAL_STRING("descending").get()))
    closure->factor = DESCENDING_SORT_FACTOR;
  else 
    closure->factor = ASCENDING_SORT_FACTOR;

  closure->abView = abView;
  return;
}

NS_IMETHODIMP nsAbView::SortBy(const PRUnichar *colID, const PRUnichar *sortDir)
{
  nsresult rv;

  PRInt32 count = mCards.Count();

  nsAutoString sortColumn;
  if (!colID) 
    sortColumn = NS_LITERAL_STRING(GENERATED_NAME_COLUMN_ID).get();  // default sort
  else
    sortColumn = colID;

  PRInt32 i;
  // This function does not optimize for the case when sortColumn and sortDirection
  // are identical since the last call, the caller is responsible optimizing
  // for that case

  // If we are sorting by how we are already sorted,
  // and just the sort direction changes, just reverse
  //
  // Note, we'll call SortBy() with the existing sort column and the
  // existing sort direction, and that needs to do a complete resort.
  // For example, we do that when the PREF_MAIL_ADDR_BOOK_LASTNAMEFIRST changes
  if (!NS_strcmp(mSortColumn.get(),sortColumn.get()) && NS_strcmp(mSortDirection.get(), sortDir)) {
    PRInt32 halfPoint = count / 2;
    for (i=0; i < halfPoint; i++) {
      // Swap the elements.
      void *ptr1 = mCards.ElementAt(i);
      void *ptr2 = mCards.ElementAt(count - i - 1);
      mCards.ReplaceElementAt(ptr2, i);
      mCards.ReplaceElementAt(ptr1, count - i - 1);
    }

    mSortDirection = sortDir;
  }
  else {
    // Generate collation keys
    for (i=0; i < count; i++) {
      AbCard *abcard = (AbCard *)(mCards.ElementAt(i));

      rv = GenerateCollationKeysForCard(sortColumn.get(), abcard);
      NS_ENSURE_SUCCESS(rv,rv);
    }

    nsAutoString sortDirection;
    if (!sortDir)
      sortDirection = NS_LITERAL_STRING("ascending").get();  // default direction
    else
      sortDirection = sortDir;

    SortClosure closure;
    SetSortClosure(sortColumn.get(), sortDirection.get(), this, &closure);
    
    nsCOMPtr<nsIArray> selectedCards;
    rv = GetSelectedCards(getter_AddRefs(selectedCards));
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsIAbCard> indexCard;

    if (mTreeSelection) {
      PRInt32 currentIndex = -1;

      rv = mTreeSelection->GetCurrentIndex(&currentIndex);
      NS_ENSURE_SUCCESS(rv,rv);

      if (currentIndex != -1) {
        rv = GetCardFromRow(currentIndex, getter_AddRefs(indexCard));
        NS_ENSURE_SUCCESS(rv,rv);
      }
    }

    mCards.Sort(inplaceSortCallback, (void *)(&closure));
    
    rv = ReselectCards(selectedCards, indexCard);
    NS_ENSURE_SUCCESS(rv, rv);

    mSortColumn = sortColumn;
    mSortDirection = sortDirection;
  }

  rv = InvalidateTree(ALL_ROWS);
  NS_ENSURE_SUCCESS(rv,rv);
  return rv;
}

PRInt32 nsAbView::CompareCollationKeys(PRUint8 *key1, PRUint32 len1, PRUint8 *key2, PRUint32 len2)
{
  NS_ASSERTION(mCollationKeyGenerator, "no key generator");
  if (!mCollationKeyGenerator)
    return 0;

  PRInt32 result;

  nsresult rv = mCollationKeyGenerator->CompareRawSortKey(key1,len1,key2,len2,&result);
  NS_ASSERTION(NS_SUCCEEDED(rv), "key compare failed");
  if (NS_FAILED(rv))
    result = 0;
  return result;
}

nsresult nsAbView::GenerateCollationKeysForCard(const PRUnichar *colID, AbCard *abcard)
{
  nsresult rv;
  nsString value;

  if (!mCollationKeyGenerator)
  {
    nsCOMPtr<nsILocaleService> localeSvc = do_GetService(NS_LOCALESERVICE_CONTRACTID,&rv); 
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsILocale> locale; 
    rv = localeSvc->GetApplicationLocale(getter_AddRefs(locale));
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr <nsICollationFactory> factory = do_CreateInstance(NS_COLLATIONFACTORY_CONTRACTID, &rv); 
    NS_ENSURE_SUCCESS(rv, rv);

    rv = factory->CreateCollation(locale, getter_AddRefs(mCollationKeyGenerator));
    NS_ENSURE_SUCCESS(rv, rv);
  }

  rv = GetCardValue(abcard->card, colID, value);
  NS_ENSURE_SUCCESS(rv,rv);
  
  PR_FREEIF(abcard->primaryCollationKey);
  rv = mCollationKeyGenerator->AllocateRawSortKey(nsICollation::kCollationCaseInSensitive,
    value, &(abcard->primaryCollationKey), &(abcard->primaryCollationKeyLen));
  NS_ENSURE_SUCCESS(rv,rv);
  
  // Hardcode email to be our secondary key. As we are doing this, just call
  // the card's GetCardValue direct, rather than our own function which will
  // end up doing the same as then we can save a bit of time.
  rv = abcard->card->GetPrimaryEmail(value);
  NS_ENSURE_SUCCESS(rv,rv);
  
  PR_FREEIF(abcard->secondaryCollationKey);
  rv = mCollationKeyGenerator->AllocateRawSortKey(nsICollation::kCollationCaseInSensitive,
    value, &(abcard->secondaryCollationKey), &(abcard->secondaryCollationKeyLen));
  NS_ENSURE_SUCCESS(rv,rv);
  return rv;
}

NS_IMETHODIMP nsAbView::OnItemAdded(nsISupports *parentDir, nsISupports *item)
{
  nsresult rv;
  nsCOMPtr <nsIAbDirectory> directory = do_QueryInterface(parentDir,&rv);
  NS_ENSURE_SUCCESS(rv,rv);

  if (directory.get() == mDirectory.get()) {
    nsCOMPtr <nsIAbCard> addedCard = do_QueryInterface(item);
    if (addedCard) {
      // Malloc these from an arena
      AbCard *abcard = (AbCard *) PR_Calloc(1, sizeof(struct AbCard));
      if (!abcard) 
        return NS_ERROR_OUT_OF_MEMORY;

      abcard->card = addedCard;
      NS_IF_ADDREF(abcard->card);
    
      rv = GenerateCollationKeysForCard(mSortColumn.get(), abcard);
      NS_ENSURE_SUCCESS(rv,rv);

      PRInt32 index;
      rv = AddCard(abcard, PR_FALSE /* select card */, &index);
      NS_ENSURE_SUCCESS(rv,rv);
    }
  }
  return rv;
}

NS_IMETHODIMP nsAbView::Observe(nsISupports *aSubject, const char *aTopic, const PRUnichar *someData)
{
  if (!strcmp(aTopic, NS_PREFBRANCH_PREFCHANGE_TOPIC_ID)) {
    if (nsDependentString(someData).EqualsLiteral(PREF_MAIL_ADDR_BOOK_LASTNAMEFIRST)) {
      nsresult rv = SetGeneratedNameFormatFromPrefs();
      NS_ENSURE_SUCCESS(rv, rv);

      rv = RefreshTree();
      NS_ENSURE_SUCCESS(rv, rv);
    }
  }
  return NS_OK;
}

nsresult nsAbView::AddCard(AbCard *abcard, PRBool selectCardAfterAdding, PRInt32 *index)
{
  nsresult rv = NS_OK;
  NS_ENSURE_ARG_POINTER(abcard);
  
  *index = FindIndexForInsert(abcard);
  rv = mCards.InsertElementAt((void *)abcard, *index);
  NS_ENSURE_SUCCESS(rv,rv);
    
  // This needs to happen after we insert the card, as RowCountChanged() will call GetRowCount()
  if (mTree)
    rv = mTree->RowCountChanged(*index, 1);

  // Checking for mTree here works around core bug 399227
  if (selectCardAfterAdding && mTreeSelection && mTree) {
    mTreeSelection->SetCurrentIndex(*index);
    mTreeSelection->RangedSelect(*index, *index, PR_FALSE /* augment */);
  }

  if (mAbViewListener && !mSuppressCountChange) {
    rv = mAbViewListener->OnCountChanged(mCards.Count());
    NS_ENSURE_SUCCESS(rv,rv);
  }

  return rv;
}

PRInt32 nsAbView::FindIndexForInsert(AbCard *abcard)
{
  PRInt32 count = mCards.Count();
  PRInt32 i;

  void *item = (void *)abcard;
  
  SortClosure closure;
  SetSortClosure(mSortColumn.get(), mSortDirection.get(), this, &closure);
  
  // XXX todo
  // Make this a binary search
  for (i=0; i < count; i++) {
    void *current = mCards.ElementAt(i);
    PRInt32 value = inplaceSortCallback(item, current, (void *)(&closure));
    // XXX Fix me, this is not right for both ascending and descending
    if (value <= 0) 
      break;
  }
  return i;
}

NS_IMETHODIMP nsAbView::OnItemRemoved(nsISupports *parentDir, nsISupports *item)
{
  nsresult rv;

  nsCOMPtr <nsIAbDirectory> directory = do_QueryInterface(parentDir,&rv);
  NS_ENSURE_SUCCESS(rv,rv);

  if (directory.get() == mDirectory.get())
    return RemoveCardAndSelectNextCard(item);

  // The pointers aren't the same, are the URI strings similar? This is most
  // likely the case if the current directory is a search on a directory.
  nsCString currentURI;
  rv = mDirectory->GetURI(currentURI);
  NS_ENSURE_SUCCESS(rv, rv);

  // If it is a search, it will have something like ?(or(PrimaryEmail...
  // on the end of the string, so remove that before comparing
  PRInt32 pos = currentURI.FindChar('?');
  if (pos != -1)
    currentURI.SetLength(pos);

  nsCString notifiedURI;
  rv = directory->GetURI(notifiedURI);
  NS_ENSURE_SUCCESS(rv, rv);

  if (currentURI.Equals(notifiedURI))
    return RemoveCardAndSelectNextCard(item);

  return NS_OK;
}

nsresult nsAbView::RemoveCardAndSelectNextCard(nsISupports *item)
{
  nsresult rv = NS_OK;
  nsCOMPtr <nsIAbCard> card = do_QueryInterface(item);
  if (card) {
    PRInt32 index = FindIndexForCard(card);
    if (index != CARD_NOT_FOUND) {
      PRBool selectNextCard = PR_FALSE;
      if (mTreeSelection) {
        PRInt32 selectedIndex;
        // XXX todo
        // Make sure it works if nothing selected
        mTreeSelection->GetCurrentIndex(&selectedIndex);
        if (index == selectedIndex)
          selectNextCard = PR_TRUE;
      }

      rv = RemoveCardAt(index);
      NS_ENSURE_SUCCESS(rv,rv);

      if (selectNextCard) {
      PRInt32 count = mCards.Count();
      if (count && mTreeSelection) {
        // If we deleted the last card, adjust so we select the new "last" card
        if (index >= (count - 1)) {
          index = count -1;
        }
        mTreeSelection->SetCurrentIndex(index);
        mTreeSelection->RangedSelect(index, index, PR_FALSE /* augment */);
      }
    }
  }
  }
  return rv;
}

PRInt32 nsAbView::FindIndexForCard(nsIAbCard *card)
{
  PRInt32 count = mCards.Count();
  PRInt32 i;
 
  // You can't implement the binary search here, as all you have is the nsIAbCard
  // you might be here because one of the card properties has changed, and that property
  // could be the collation key.
  for (i=0; i < count; i++) {
    AbCard *abcard = (AbCard*) (mCards.ElementAt(i));
    PRBool equals;
    nsresult rv = card->Equals(abcard->card, &equals);
    if (NS_SUCCEEDED(rv) && equals) {
      return i;
    }
  }
  return CARD_NOT_FOUND;
}

NS_IMETHODIMP nsAbView::OnItemPropertyChanged(nsISupports *item, const char *property, const PRUnichar *oldValue, const PRUnichar *newValue)
{
  nsresult rv;

  nsCOMPtr <nsIAbCard> card = do_QueryInterface(item);
  if (!card)
    return NS_OK;

  PRInt32 index = FindIndexForCard(card);
  if (index == -1)
    return NS_OK;

  AbCard *oldCard = (AbCard*) (mCards.ElementAt(index));

  // Malloc these from an arena
  AbCard *newCard = (AbCard *) PR_Calloc(1, sizeof(struct AbCard));
  if (!newCard)
    return NS_ERROR_OUT_OF_MEMORY;

  newCard->card = card;
  NS_IF_ADDREF(newCard->card);
    
  rv = GenerateCollationKeysForCard(mSortColumn.get(), newCard);
  NS_ENSURE_SUCCESS(rv,rv);

  PRBool cardWasSelected = PR_FALSE;

  if (mTreeSelection) {
    rv = mTreeSelection->IsSelected(index, &cardWasSelected);
    NS_ENSURE_SUCCESS(rv,rv);
  }
  
  if (!CompareCollationKeys(newCard->primaryCollationKey,newCard->primaryCollationKeyLen,oldCard->primaryCollationKey,oldCard->primaryCollationKeyLen)
    && CompareCollationKeys(newCard->secondaryCollationKey,newCard->secondaryCollationKeyLen,oldCard->secondaryCollationKey,oldCard->secondaryCollationKeyLen)) {
    // No need to remove and add, since the collation keys haven't changed.
    // Since they haven't changed, the card will sort to the same place.
    // We just need to clean up what we allocated.
    NS_IF_RELEASE(newCard->card);
    if (newCard->primaryCollationKey)
      nsMemory::Free(newCard->primaryCollationKey);
    if (newCard->secondaryCollationKey)
      nsMemory::Free(newCard->secondaryCollationKey);
    PR_FREEIF(newCard);

    // Still need to invalidate, as the other columns may have changed.
    rv = InvalidateTree(index);
    NS_ENSURE_SUCCESS(rv,rv);
  }
  else {
    mSuppressSelectionChange = PR_TRUE;
    mSuppressCountChange = PR_TRUE;

    // Remove the old card.
    rv = RemoveCardAt(index);
    NS_ASSERTION(NS_SUCCEEDED(rv), "remove card failed\n");

    // Add the card we created, and select it (to restore selection) if it was selected.
    rv = AddCard(newCard, cardWasSelected /* select card */, &index);
    NS_ASSERTION(NS_SUCCEEDED(rv), "add card failed\n");

    mSuppressSelectionChange = PR_FALSE;
    mSuppressCountChange = PR_FALSE;

    // Ensure restored selection is visible
    if (cardWasSelected && mTree) 
      mTree->EnsureRowIsVisible(index);
  }

  // Although the selection hasn't changed, the card that is selected may need
  // to be displayed differently, therefore pretend that the selection has
  // changed to force that update.
  if (cardWasSelected)
    SelectionChanged();

  return NS_OK;
}

NS_IMETHODIMP nsAbView::SelectAll()
{
  if (mTreeSelection && mTree) {
    mTreeSelection->SelectAll();
    mTree->Invalidate();
  }
  return NS_OK;
}

NS_IMETHODIMP nsAbView::GetSortDirection(nsAString & aDirection)
{
  aDirection = mSortDirection;
  return NS_OK;
}

NS_IMETHODIMP nsAbView::GetSortColumn(nsAString & aColumn)
{
  aColumn = mSortColumn;
  return NS_OK;
}

nsresult nsAbView::ReselectCards(nsIArray *aCards, nsIAbCard *aIndexCard)
{
  PRUint32 count;
  PRUint32 i;

  if (!mTreeSelection || !aCards)
    return NS_OK;

  nsresult rv = mTreeSelection->ClearSelection();
  NS_ENSURE_SUCCESS(rv,rv);

  rv = aCards->GetLength(&count);
  NS_ENSURE_SUCCESS(rv, rv);

  for (i = 0; i < count; i++) {
    nsCOMPtr<nsIAbCard> card = do_QueryElementAt(aCards, i);
    if (card) {
      PRInt32 index = FindIndexForCard(card);
      if (index != CARD_NOT_FOUND) {
        mTreeSelection->RangedSelect(index, index, PR_TRUE /* augment */);
      }
    }
  }

  // Reset the index card, and ensure it is visible.
  if (aIndexCard) {
    PRInt32 currentIndex = FindIndexForCard(aIndexCard);
    rv = mTreeSelection->SetCurrentIndex(currentIndex);
    NS_ENSURE_SUCCESS(rv, rv);
  
    if (mTree) {
      rv = mTree->EnsureRowIsVisible(currentIndex);
      NS_ENSURE_SUCCESS(rv, rv);
    }
  }

  return NS_OK;
}

NS_IMETHODIMP nsAbView::DeleteSelectedCards()
{
  nsCOMPtr<nsIArray> cardsToDelete;
  
  nsresult rv = GetSelectedCards(getter_AddRefs(cardsToDelete));
  NS_ENSURE_SUCCESS(rv, rv);

  // mDirectory should not be null
  // Bullet proof (and assert) to help figure out bug #127748
  NS_ENSURE_TRUE(mDirectory, NS_ERROR_UNEXPECTED);

  rv = mDirectory->DeleteCards(cardsToDelete);
  NS_ENSURE_SUCCESS(rv, rv);
  return rv;
}

nsresult nsAbView::GetSelectedCards(nsIArray **aSelectedCards)
{
  *aSelectedCards = nsnull;
  if (!mTreeSelection)
    return NS_OK;

  PRInt32 selectionCount; 
  nsresult rv = mTreeSelection->GetRangeCount(&selectionCount);
  NS_ENSURE_SUCCESS(rv, rv);

  if (!selectionCount)
    return NS_OK;

  nsCOMPtr<nsIMutableArray> result(do_CreateInstance(NS_ARRAY_CONTRACTID, &rv));
  NS_ENSURE_SUCCESS(rv,rv);
  
  for (PRInt32 i = 0; i < selectionCount; i++)
  {
    PRInt32 startRange;
    PRInt32 endRange;
    rv = mTreeSelection->GetRangeAt(i, &startRange, &endRange);
    NS_ENSURE_SUCCESS(rv, NS_OK); 
    PRInt32 totalCards = mCards.Count();
    if (startRange >= 0 && startRange < totalCards)
    {
      for (PRInt32 rangeIndex = startRange; rangeIndex <= endRange && rangeIndex < totalCards; rangeIndex++) {
        nsCOMPtr<nsIAbCard> abCard;
        rv = GetCardFromRow(rangeIndex, getter_AddRefs(abCard));
        NS_ENSURE_SUCCESS(rv,rv);
        
        rv = result->AppendElement(abCard, PR_FALSE);
        NS_ENSURE_SUCCESS(rv, rv);
      }
    }
  }

  NS_ADDREF(*aSelectedCards = result);

  return NS_OK;
}

NS_IMETHODIMP nsAbView::SwapFirstNameLastName()
{
  if (!mTreeSelection)
    return NS_OK;
  
  PRInt32 selectionCount; 
  nsresult rv = mTreeSelection->GetRangeCount(&selectionCount);
  NS_ENSURE_SUCCESS(rv, rv);
  
  if (!selectionCount)
    return NS_OK;
  
  // Prepare for displayname generation
  // No cache for pref and bundle since the swap operation is not executed frequently
  PRBool displayNameAutoGeneration;
  PRBool displayNameLastnamefirst = PR_FALSE;

  nsCOMPtr<nsIPrefBranch2> pPrefBranchInt(do_GetService(NS_PREFSERVICE_CONTRACTID, &rv));
  NS_ENSURE_SUCCESS(rv, rv);

  rv = pPrefBranchInt->GetBoolPref(PREF_MAIL_ADDR_BOOK_DISPLAYNAME_AUTOGENERATION, &displayNameAutoGeneration);
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIStringBundle> bundle;
  if (displayNameAutoGeneration)
  {
    nsCOMPtr<nsIPrefLocalizedString> pls;
    rv = pPrefBranchInt->GetComplexValue(PREF_MAIL_ADDR_BOOK_DISPLAYNAME_LASTNAMEFIRST,
                                         NS_GET_IID(nsIPrefLocalizedString), getter_AddRefs(pls));
    NS_ENSURE_SUCCESS(rv, rv);

    nsString str;
    pls->ToString(getter_Copies(str));
    displayNameLastnamefirst = str.EqualsLiteral("true");
    nsCOMPtr<nsIStringBundleService> bundleService = do_GetService(NS_STRINGBUNDLE_CONTRACTID, &rv);
    NS_ENSURE_SUCCESS(rv, rv);

    rv = bundleService->CreateBundle("chrome://messenger/locale/addressbook/addressBook.properties", 
                                     getter_AddRefs(bundle));
    NS_ENSURE_SUCCESS(rv, rv);
  }

  for (PRInt32 i = 0; i < selectionCount; i++)
  {
    PRInt32 startRange;
    PRInt32 endRange;
    rv = mTreeSelection->GetRangeAt(i, &startRange, &endRange);
    NS_ENSURE_SUCCESS(rv, NS_OK); 
    PRInt32 totalCards = mCards.Count();
    if (startRange >= 0 && startRange < totalCards)
    {
      for (PRInt32 rangeIndex = startRange; rangeIndex <= endRange && rangeIndex < totalCards; rangeIndex++) {
        nsCOMPtr<nsIAbCard> abCard;
        rv = GetCardFromRow(rangeIndex, getter_AddRefs(abCard));
        NS_ENSURE_SUCCESS(rv, rv);

        // Swap FN/LN
        nsAutoString fn, ln;
        abCard->GetFirstName(fn);
        abCard->GetLastName(ln);
        if (!fn.IsEmpty() || !ln.IsEmpty())
        {
          abCard->SetFirstName(ln);
          abCard->SetLastName(fn);

          // Generate display name using the new order
          if (displayNameAutoGeneration &&
              !fn.IsEmpty() && !ln.IsEmpty())
          {
            nsString dnLnFn;
            nsString dnFnLn;
            const PRUnichar *nameString[2];
            const PRUnichar *formatString;

            // The format should stays the same before/after we swap the names
            formatString = displayNameLastnamefirst ?
                              NS_LITERAL_STRING("lastFirstFormat").get() :
                              NS_LITERAL_STRING("firstLastFormat").get();

            // Generate both ln/fn and fn/ln combination since we need both later
            // to check to see if the current display name was edited
            // note that fn/ln still hold the values before the swap
            nameString[0] = ln.get();
            nameString[1] = fn.get();
            rv = bundle->FormatStringFromName(formatString,
                                              nameString, 2, getter_Copies(dnLnFn));
            NS_ENSURE_SUCCESS(rv, rv);
            nameString[0] = fn.get();
            nameString[1] = ln.get();
            rv = bundle->FormatStringFromName(formatString,
                                              nameString, 2, getter_Copies(dnFnLn));
            NS_ENSURE_SUCCESS(rv, rv);

            // Get the current display name
            nsAutoString dn;
            rv = abCard->GetDisplayName(dn);
            NS_ENSURE_SUCCESS(rv, rv);

            // Swap the display name if not edited
            if (displayNameLastnamefirst)
            {
              if (dn.Equals(dnLnFn))
                abCard->SetDisplayName(dnFnLn);
            }
            else
            {
              if (dn.Equals(dnFnLn))
                abCard->SetDisplayName(dnLnFn);
            }
          }

          // Swap phonetic names
          rv = abCard->GetPropertyAsAString(kPhoneticFirstNameProperty, fn);
          NS_ENSURE_SUCCESS(rv, rv);
          rv = abCard->GetPropertyAsAString(kPhoneticLastNameProperty, ln);
          NS_ENSURE_SUCCESS(rv, rv);
          if (!fn.IsEmpty() || !ln.IsEmpty())
          {
            abCard->SetPropertyAsAString(kPhoneticFirstNameProperty, ln);
            abCard->SetPropertyAsAString(kPhoneticLastNameProperty, fn);
          }
        }
      }
    }
  }
  // Update the tree
  // Re-sort if either generated or phonetic name is primary or secondary sort,
  // otherwise invalidate to reflect the change
  rv = RefreshTree();

  return rv;
}

NS_IMETHODIMP nsAbView::GetSelectedAddresses(nsIArray **_retval)
{
  NS_ENSURE_ARG_POINTER(_retval);
 
  nsCOMPtr<nsIArray> selectedCards;
  nsresult rv = GetSelectedCards(getter_AddRefs(selectedCards));
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIMutableArray> addresses = do_CreateInstance(NS_ARRAY_CONTRACTID);
  PRUint32 count;
  selectedCards->GetLength(&count);

  for (PRUint32 i = 0; i < count; i++) {
    nsCOMPtr<nsIAbCard> card(do_QueryElementAt(selectedCards, i, &rv));
    NS_ENSURE_SUCCESS(rv, rv);

    PRBool isMailList;
    card->GetIsMailList(&isMailList);
    nsAutoString primaryEmail;
    if (isMailList) {
      nsCOMPtr<nsIAbManager> abManager(do_GetService(NS_ABMANAGER_CONTRACTID,
                                                     &rv));
      NS_ENSURE_SUCCESS(rv, rv);

      nsCString mailListURI;
      rv = card->GetMailListURI(getter_Copies(mailListURI));
      NS_ENSURE_SUCCESS(rv, rv);

      nsCOMPtr<nsIAbDirectory> mailList;
      rv = abManager->GetDirectory(mailListURI, getter_AddRefs(mailList));
      NS_ENSURE_SUCCESS(rv, rv);

      nsCOMPtr<nsIMutableArray> mailListAddresses;
      rv = mailList->GetAddressLists(getter_AddRefs(mailListAddresses));
      NS_ENSURE_SUCCESS(rv,rv);

      PRUint32 mailListCount = 0;
      mailListAddresses->GetLength(&mailListCount);	

      for (PRUint32 j = 0; j < mailListCount; j++) {
        nsCOMPtr<nsIAbCard> mailListCard = do_QueryElementAt(mailListAddresses, j, &rv);
        NS_ENSURE_SUCCESS(rv,rv);

        rv = mailListCard->GetPrimaryEmail(primaryEmail);
        NS_ENSURE_SUCCESS(rv,rv);

        if (!primaryEmail.IsEmpty()) {
          nsCOMPtr<nsISupportsString> supportsEmail(do_CreateInstance(NS_SUPPORTS_STRING_CONTRACTID));
          supportsEmail->SetData(primaryEmail);
          addresses->AppendElement(supportsEmail, PR_FALSE);
        }
      }
    }
    else {
      rv = card->GetPrimaryEmail(primaryEmail);
      NS_ENSURE_SUCCESS(rv,rv);

      if (!primaryEmail.IsEmpty()) {
        nsCOMPtr<nsISupportsString> supportsEmail(do_CreateInstance(NS_SUPPORTS_STRING_CONTRACTID));
        supportsEmail->SetData(primaryEmail);
        addresses->AppendElement(supportsEmail, PR_FALSE);
      }
    }    
  }

  NS_IF_ADDREF(*_retval = addresses);

  return NS_OK;
}

NS_IMETHODIMP nsAbView::AddColumnHandler(const nsAString& aColID, nsIAbCustomColumnHandler* aHandler)
{
  NS_ENSURE_ARG_POINTER(aHandler);

  return mCustomColumnHandlers.Put(aColID, aHandler);
}

NS_IMETHODIMP nsAbView::RemoveColumnHandler(const nsAString& aColID)
{
  if (!mCustomColumnHandlers.Get(aColID, NULL))
    return NS_ERROR_FAILURE;

  mCustomColumnHandlers.Remove(aColID);
  return NS_OK;
}

NS_IMETHODIMP nsAbView::GetColumnHandler(const nsAString& aColID, nsIAbCustomColumnHandler** aHandler)
{
  NS_ENSURE_ARG_POINTER(aHandler);
  
  mCustomColumnHandlers.Get(aColID, aHandler);
  NS_IF_ADDREF(*aHandler);
  
  return (*aHandler) ? NS_OK : NS_ERROR_FAILURE;
}
