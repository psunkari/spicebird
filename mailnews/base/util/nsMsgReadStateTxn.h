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
 *
 * Portions created by the Initial Developer are Copyright (C) 2008 
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Nick Kreeger <nick.kreeger@park.edu>
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

#ifndef nsMsgBaseUndoTxn_h_
#define nsMsgBaseUndoTxn_h_

#include "nsMsgTxn.h"
#include "nsTArray.h"
#include "nsCOMPtr.h"
#include "MailNewsTypes.h"
#include "nsIMsgFolder.h"


#define NS_MSGREADSTATETXN_IID \
{ /* 121FCE4A-3EA1-455C-8161-839E1557D0CF */ \
  0x121FCE4A, 0x3EA1, 0x455C, \
  { 0x81, 0x61, 0x83, 0x9E, 0x15, 0x57, 0xD0, 0xCF } \
}


//------------------------------------------------------------------------------
// A mark-all transaction handler. Helper for redo/undo of message read states.
//------------------------------------------------------------------------------
class NS_MSG_BASE nsMsgReadStateTxn : public nsMsgTxn
{
public:
  nsMsgReadStateTxn();
  virtual ~nsMsgReadStateTxn();

  nsresult Init(nsIMsgFolder *aParentFolder, 
                nsTArray<nsMsgKey> & aMsgKeyArray);
  NS_IMETHOD UndoTransaction();
  NS_IMETHOD RedoTransaction();

protected:
  NS_IMETHOD MarkMessages(PRBool aAsRead);

private:
  nsCOMPtr<nsIMsgFolder> mParentFolder;
  nsTArray<nsMsgKey>     mMarkedMessages;
  PRBool                 mWasMarkedRead;
};

#endif  // nsMsgBaseUndoTxn_h_

