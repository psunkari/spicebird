/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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
#include "msgCore.h"    // precompiled header...
#include "nsStringGlue.h"
#include "nsIIOService.h"

#include "nsIStreamListener.h"
#include "nsAddbookProtocolHandler.h"

#include "nsAddbookUrl.h"
#include "nsAddbookProtocolHandler.h"
#include "nsCOMPtr.h"
#include "nsAbBaseCID.h"
#include "nsNetUtil.h"
#include "nsStringStream.h"
#include "nsIAbDirectory.h"
#include "nsIAbManager.h"
#include "prmem.h"
#include "nsIAbView.h"
#include "nsITreeView.h"
#include "nsIStringBundle.h"
#include "nsIServiceManager.h"

nsAddbookProtocolHandler::nsAddbookProtocolHandler()
{
  mAddbookOperation = nsIAddbookUrlOperation::InvalidUrl;
}

nsAddbookProtocolHandler::~nsAddbookProtocolHandler()
{
}

NS_IMPL_ISUPPORTS1(nsAddbookProtocolHandler, nsIProtocolHandler)

NS_IMETHODIMP nsAddbookProtocolHandler::GetScheme(nsACString &aScheme)
{
	aScheme = "addbook";
	return NS_OK; 
}

NS_IMETHODIMP nsAddbookProtocolHandler::GetDefaultPort(PRInt32 *aDefaultPort)
{
  return NS_OK;
}

NS_IMETHODIMP nsAddbookProtocolHandler::GetProtocolFlags(PRUint32 *aUritype)
{
  *aUritype = URI_STD | URI_LOADABLE_BY_ANYONE;
  return NS_OK;
}

NS_IMETHODIMP nsAddbookProtocolHandler::NewURI(const nsACString &aSpec,
                                               const char *aOriginCharset, // ignored
                                               nsIURI *aBaseURI,
                                               nsIURI **_retval)
{
  nsresult rv;
	nsCOMPtr <nsIAddbookUrl> addbookUrl = do_CreateInstance(NS_ADDBOOKURL_CONTRACTID, &rv);
  NS_ENSURE_SUCCESS(rv,rv);

  rv = addbookUrl->SetSpec(aSpec);
  NS_ENSURE_SUCCESS(rv,rv);

  nsCOMPtr <nsIURI> uri = do_QueryInterface(addbookUrl, &rv);
  NS_ENSURE_SUCCESS(rv,rv);

  NS_ADDREF(*_retval = uri);
  return NS_OK;
}

NS_IMETHODIMP 
nsAddbookProtocolHandler::AllowPort(PRInt32 port, const char *scheme, PRBool *_retval)
{
    // don't override anything.  
    *_retval = PR_FALSE;
    return NS_OK;
}

nsresult
nsAddbookProtocolHandler::GenerateXMLOutputChannel( nsString &aOutput,
                                                     nsIAddbookUrl *addbookUrl,
                                                     nsIURI *aURI, 
                                                     nsIChannel **_retval)
{
  nsIChannel                *channel;
  nsresult rv;
  nsCOMPtr<nsIStringInputStream> inStr(do_CreateInstance("@mozilla.org/io/string-input-stream;1", &rv));
  NS_ENSURE_SUCCESS(rv, rv);

  NS_ConvertUTF16toUTF8 utf8String(aOutput.get());

  rv = inStr->SetData(utf8String.get(), utf8String.Length());

  rv = NS_NewInputStreamChannel(&channel, aURI, inStr,
                                NS_LITERAL_CSTRING("text/xml"));
  NS_ENSURE_SUCCESS(rv, rv);
  
  *_retval = channel;
  return rv;
}

NS_IMETHODIMP 
nsAddbookProtocolHandler::NewChannel(nsIURI *aURI, nsIChannel **_retval)
{
  nsresult rv;
  nsCOMPtr <nsIAddbookUrl> addbookUrl = do_QueryInterface(aURI, &rv);
  NS_ENSURE_SUCCESS(rv,rv);
  
  rv = addbookUrl->GetAddbookOperation(&mAddbookOperation);
  NS_ENSURE_SUCCESS(rv,rv);

  if (mAddbookOperation == nsIAddbookUrlOperation::InvalidUrl) {
    nsAutoString errorString;
    errorString.AssignLiteral("Unsupported format/operation requested for ");
    nsCAutoString spec;
    rv = aURI->GetSpec(spec);
    NS_ENSURE_SUCCESS(rv,rv);

     errorString.Append(NS_ConvertUTF8toUTF16(spec));
    rv = GenerateXMLOutputChannel(errorString, addbookUrl, aURI, _retval);
    NS_ENSURE_SUCCESS(rv,rv);
    return NS_OK;
  }
 
  if (mAddbookOperation == nsIAddbookUrlOperation::AddVCard) {
      // create an empty pipe for use with the input stream channel.
      nsCOMPtr<nsIAsyncInputStream> pipeIn;
      nsCOMPtr<nsIAsyncOutputStream> pipeOut;
      nsCOMPtr<nsIPipe> pipe = do_CreateInstance("@mozilla.org/pipe;1");
      
      rv = pipe->Init(PR_FALSE, PR_FALSE, 0, 0, nsnull);
      NS_ENSURE_SUCCESS(rv, rv);

      pipe->GetInputStream(getter_AddRefs(pipeIn));
      pipe->GetOutputStream(getter_AddRefs(pipeOut));
      
      pipeOut->Close();
      
      return NS_NewInputStreamChannel(_retval, aURI, pipeIn,
          NS_LITERAL_CSTRING("application/x-addvcard"));
  }

  nsString output;
  rv = GeneratePrintOutput(addbookUrl, output);
  if (NS_FAILED(rv)) {
    output.AssignLiteral("failed to print. url=");
    nsCAutoString spec;
    rv = aURI->GetSpec(spec);
    NS_ENSURE_SUCCESS(rv,rv);
    output.Append(NS_ConvertUTF8toUTF16(spec));
  }
 
  rv = GenerateXMLOutputChannel(output, addbookUrl, aURI, _retval);
  NS_ENSURE_SUCCESS(rv,rv);
  return NS_OK;
}

nsresult    
nsAddbookProtocolHandler::GeneratePrintOutput(nsIAddbookUrl *addbookUrl, 
                                              nsString &aOutput)
{
  NS_ENSURE_ARG_POINTER(addbookUrl);

  nsCAutoString uri;
  nsresult rv = addbookUrl->GetPath(uri);
  NS_ENSURE_SUCCESS(rv,rv);

  /* turn
   "//moz-abmdbdirectory/abook.mab?action=print"
   into "moz-abmdbdirectory://abook.mab"
  */

  /* step 1:  
   turn "//moz-abmdbdirectory/abook.mab?action=print"
   into "moz-abmdbdirectory/abook.mab?action=print"
   */
  if (uri[0] != '/' && uri[1] != '/')
    return NS_ERROR_UNEXPECTED;

  uri.Cut(0,2);

  /* step 2:  
   turn "moz-abmdbdirectory/abook.mab?action=print"
   into "moz-abmdbdirectory/abook.mab"
   */
  PRInt32 pos = uri.Find("?action=print");
	if (pos == -1)
    return NS_ERROR_UNEXPECTED;

  uri.SetLength(pos);

  /* step 2:  
   turn "moz-abmdbdirectory/abook.mab"
   into "moz-abmdbdirectory://abook.mab"
   */
  pos = uri.Find("/");
  if (pos == -1)
    return NS_ERROR_UNEXPECTED;

  uri.Insert('/', pos);
  uri.Insert(':', pos);

  nsCOMPtr<nsIAbManager> abManager(do_GetService(NS_ABMANAGER_CONTRACTID, &rv));
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIAbDirectory> directory;
  rv = abManager->GetDirectory(uri, getter_AddRefs(directory));
  NS_ENSURE_SUCCESS(rv, rv);

  rv = BuildDirectoryXML(directory, aOutput);
  NS_ENSURE_SUCCESS(rv, rv);

  return NS_OK;
}

nsresult
nsAddbookProtocolHandler::BuildDirectoryXML(nsIAbDirectory *aDirectory, 
                                       nsString &aOutput)
{
  NS_ENSURE_ARG_POINTER(aDirectory);

  nsresult rv;    
  nsCOMPtr<nsISimpleEnumerator> cardsEnumerator;
  nsCOMPtr<nsIAbCard> card;

  aOutput.AppendLiteral("<?xml version=\"1.0\"?>\n"
                        "<?xml-stylesheet type=\"text/css\" href=\"chrome://messagebody/content/addressbook/print.css\"?>\n"
                        "<directory>\n");

  // Get Address Book string and set it as title of XML document
  nsCOMPtr<nsIStringBundle> bundle;
  nsCOMPtr<nsIStringBundleService> stringBundleService = do_GetService(NS_STRINGBUNDLE_CONTRACTID, &rv); 
  if (NS_SUCCEEDED(rv)) {
    rv = stringBundleService->CreateBundle("chrome://messenger/locale/addressbook/addressBook.properties", getter_AddRefs(bundle));
    if (NS_SUCCEEDED(rv)) {
      nsString addrBook;
      rv = bundle->GetStringFromName(NS_LITERAL_STRING("addressBook").get(), getter_Copies(addrBook));
      if (NS_SUCCEEDED(rv)) {
        aOutput.AppendLiteral("<title xmlns=\"http://www.w3.org/1999/xhtml\">");
        aOutput.Append(addrBook);
        aOutput.AppendLiteral("</title>\n");
      }
    }
  }

 // create a view and init it with the generated name sort order. Then, iterate
  // over the view, getting the card for each row, and printing them.
  nsString sortColumn;
  nsCOMPtr <nsIAbView> view = do_CreateInstance("@mozilla.org/addressbook/abview;1", &rv);
  
  view->SetView(aDirectory, nsnull, NS_LITERAL_STRING("GeneratedName"),
                NS_LITERAL_STRING("ascending"), sortColumn);

  PRInt32 numRows;
  nsCOMPtr <nsITreeView> treeView = do_QueryInterface(view, &rv);
  NS_ENSURE_SUCCESS(rv, rv);
  treeView->GetRowCount(&numRows);
  
  for (PRInt32 row = 0; row < numRows; row++)
  {
    
    nsCOMPtr <nsIAbCard> card;
    view->GetCardFromRow(row, getter_AddRefs(card));
    nsCString xmlSubstr;

    rv = card->TranslateTo(NS_LITERAL_CSTRING("xml"), xmlSubstr);
    NS_ENSURE_SUCCESS(rv,rv);

    aOutput.AppendLiteral("<separator/>");
    aOutput.Append(NS_ConvertUTF8toUTF16(xmlSubstr));
    aOutput.AppendLiteral("<separator/>");
  }

  aOutput.AppendLiteral("</directory>\n");

  return NS_OK;
}
