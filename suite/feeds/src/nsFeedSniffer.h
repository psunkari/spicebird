/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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
 * The Original Code is the Feed Content Sniffer.
 *
 * The Initial Developer of the Original Code is Google Inc.
 * Portions created by the Initial Developer are Copyright (C) 2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Ben Goodger <beng@google.com>
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

#include "nsIGenericFactory.h"
#include "nsIContentSniffer.h"
#include "nsIStreamListener.h"
#include "nsStringAPI.h"

#define NS_FEEDSNIFFER_CONTRACTID \
  "@mozilla.org/browser/feeds/sniffer;1"

// {E5EEEF51-05CE-4885-9434-7287616D9547}
#define NS_FEEDSNIFFER_CID \
  { 0xe5eeef51, 0x5ce, 0x4885, { 0x94, 0x34, 0x72, 0x87, 0x61, 0x6d, 0x95, 0x47 } }


class nsFeedSniffer : public nsIContentSniffer, nsIStreamListener
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICONTENTSNIFFER
  NS_DECL_NSIREQUESTOBSERVER
  NS_DECL_NSISTREAMLISTENER

  static NS_METHOD AppendSegmentToString(nsIInputStream* inputStream,
                                         void* closure,
                                         const char* rawSegment,
                                         PRUint32 toOffset,
                                         PRUint32 count,
                                         PRUint32* writeCount);

  static NS_METHOD Register(nsIComponentManager* compMgr, nsIFile* path,
                            const char* registryLocation,
                            const char* componentType,
                            const nsModuleComponentInfo *info);

protected:
  nsresult ConvertEncodedData(nsIRequest* request, const PRUint8* data,
                              PRUint32 length);

private:
  nsCString mDecodedData;
};
