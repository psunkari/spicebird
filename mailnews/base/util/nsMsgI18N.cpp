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

// as does this
#include "nsICharsetConverterManager.h"
#include "nsICharsetAlias.h"
#include "nsIPlatformCharset.h"
#include "nsIServiceManager.h"

#include "nsISupports.h"
#include "nsIPrefBranch.h"
#include "nsIPrefService.h"
#include "nsIMimeConverter.h"
#include "nsMsgUtils.h"
#include "nsMsgI18N.h"
#include "nsMsgMimeCID.h"
#include "nsILineInputStream.h"
#include "nsMimeTypes.h"
#include "nsISaveAsCharset.h"
#include "nsHankakuToZenkakuCID.h"
#include "nsStringGlue.h"
#include "prmem.h"
#include "plstr.h"
#include "nsUTF8Utils.h"
#include "nsNetUtil.h"
#include "nsCRTGlue.h"
//
// International functions necessary for composition
//

nsresult nsMsgI18NConvertFromUnicode(const char* aCharset,
                                     const nsString& inString,
                                     nsACString& outString,
                                     PRBool aIsCharsetCanonical)
{
  if (inString.IsEmpty()) {
    outString.Truncate();
    return NS_OK;
  }
  // Note: this will hide a possible error when the unicode text may contain more than one charset.
  // (e.g. Latin1 + Japanese). Use nsMsgI18NSaveAsCharset instead to avoid that problem.
  else if (!*aCharset || !PL_strcasecmp(aCharset, "us-ascii") ||
           !PL_strcasecmp(aCharset, "ISO-8859-1")) {
    LossyCopyUTF16toASCII(inString, outString);
    return NS_OK;
  }
  else if (!PL_strcasecmp(aCharset, "UTF-8")) {
    CopyUTF16toUTF8(inString, outString);
    return NS_OK;
  }

  nsresult rv;
  nsCOMPtr <nsICharsetConverterManager> ccm = do_GetService(NS_CHARSETCONVERTERMANAGER_CONTRACTID, &rv);
  NS_ENSURE_SUCCESS(rv, rv);
  nsCOMPtr <nsIUnicodeEncoder> encoder;

  // get an unicode converter
  if (aIsCharsetCanonical)  // optimize for modified UTF-7 used by IMAP
    rv = ccm->GetUnicodeEncoderRaw(aCharset, getter_AddRefs(encoder));
  else
    rv = ccm->GetUnicodeEncoder(aCharset, getter_AddRefs(encoder));
  NS_ENSURE_SUCCESS(rv, rv);
  rv = encoder->SetOutputErrorBehavior(nsIUnicodeEncoder::kOnError_Replace, nsnull, '?');
  NS_ENSURE_SUCCESS(rv, rv);

  const PRUnichar *originalSrcPtr = inString.get();
  const PRUnichar *currentSrcPtr = originalSrcPtr;
  PRInt32 originalUnicharLength = inString.Length();
  PRInt32 srcLength;
  PRInt32 dstLength;
  char localbuf[512];
  PRInt32 consumedLen = 0;

  outString.Truncate();
  // convert
  while (consumedLen < originalUnicharLength) {
    srcLength = originalUnicharLength - consumedLen;  
    dstLength = 512;
    rv = encoder->Convert(currentSrcPtr, &srcLength, localbuf, &dstLength);
    if (NS_FAILED(rv) || dstLength == 0)
      break;
    outString.Append(localbuf, dstLength);

    currentSrcPtr += srcLength;
    consumedLen = currentSrcPtr - originalSrcPtr; // src length used so far
  }
  rv = encoder->Finish(localbuf, &dstLength);
  if (NS_SUCCEEDED(rv))
    outString.Append(localbuf, dstLength);
  return rv;
}

nsresult nsMsgI18NConvertToUnicode(const char* aCharset,
                                   const nsCString& inString, 
                                   nsAString& outString,
                                   PRBool aIsCharsetCanonical)
{
  if (inString.IsEmpty()) {
    outString.Truncate();
    return NS_OK;
  }
  else if (!*aCharset || !PL_strcasecmp(aCharset, "us-ascii") ||
           !PL_strcasecmp(aCharset, "ISO-8859-1")) {
    // Despite its name, it also works for Latin-1.
    CopyASCIItoUTF16(inString, outString);
    return NS_OK;
  }
  else if (!PL_strcasecmp(aCharset, "UTF-8")) {
    if (MsgIsUTF8(inString)) {
      nsAutoString tmp;
      CopyUTF8toUTF16(inString, tmp);
      if (!tmp.IsEmpty() && tmp.get()[0] == PRUnichar(0xFEFF))
        tmp.Cut(0, 1);
      outString.Assign(tmp);
      return NS_OK;
    }
    NS_WARNING("Invalid UTF-8 string");
    return NS_ERROR_UNEXPECTED;
  }

  nsresult rv;
  nsCOMPtr <nsICharsetConverterManager> ccm = do_GetService(NS_CHARSETCONVERTERMANAGER_CONTRACTID, &rv);
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr <nsIUnicodeDecoder> decoder;

  // get an unicode converter
  if (aIsCharsetCanonical)  // optimize for modified UTF-7 used by IMAP
    rv = ccm->GetUnicodeDecoderRaw(aCharset, getter_AddRefs(decoder));
  else
    rv = ccm->GetUnicodeDecoder(aCharset, getter_AddRefs(decoder));
  NS_ENSURE_SUCCESS(rv, rv);

  const char *originalSrcPtr = inString.get();
  const char *currentSrcPtr = originalSrcPtr;
  PRInt32 originalLength = inString.Length();
  PRInt32 srcLength;
  PRInt32 dstLength;
  PRUnichar localbuf[512];
  PRInt32 consumedLen = 0;

  outString.Truncate();

  // convert
  while (consumedLen < originalLength) {
    srcLength = originalLength - consumedLen;  
    dstLength = 512;
    rv = decoder->Convert(currentSrcPtr, &srcLength, localbuf, &dstLength);
    if (NS_FAILED(rv) || dstLength == 0)
      break;
    outString.Append(localbuf, dstLength);

    currentSrcPtr += srcLength;
    consumedLen = currentSrcPtr - originalSrcPtr; // src length used so far
  }
  return rv;
}

// Charset used by the file system.
const char * nsMsgI18NFileSystemCharset()
{
  /* Get a charset used for the file. */
  static nsCAutoString fileSystemCharset;

  if (fileSystemCharset.IsEmpty()) 
  {
    nsresult rv;
    nsCOMPtr <nsIPlatformCharset> platformCharset = do_GetService(NS_PLATFORMCHARSET_CONTRACTID, &rv);
        if (NS_SUCCEEDED(rv)) {
          rv = platformCharset->GetCharset(kPlatformCharsetSel_FileName,
                                           fileSystemCharset);
        }

    if (NS_FAILED(rv)) 
      fileSystemCharset.Assign("ISO-8859-1");
  }
  return fileSystemCharset.get();
}

// Charset used by the text file.
void nsMsgI18NTextFileCharset(nsACString& aCharset)
{
  nsresult rv;
  nsCOMPtr <nsIPlatformCharset> platformCharset =
    do_GetService(NS_PLATFORMCHARSET_CONTRACTID, &rv);
  if (NS_SUCCEEDED(rv)) {
    rv = platformCharset->GetCharset(kPlatformCharsetSel_PlainTextInFile,
                                     aCharset);
  }

  if (NS_FAILED(rv))
    aCharset.Assign("ISO-8859-1");
}

// MIME encoder, output string should be freed by PR_FREE
// XXX : fix callers later to avoid allocation and copy
char * nsMsgI18NEncodeMimePartIIStr(const char *header, PRBool structured, const char *charset, PRInt32 fieldnamelen, PRBool usemime) 
{
  // No MIME, convert to the outgoing mail charset.
  if (PR_FALSE == usemime) {
    nsCAutoString convertedStr;
    if (NS_SUCCEEDED(ConvertFromUnicode(charset, NS_ConvertUTF8toUTF16(header),
                                        convertedStr)))
      return PL_strdup(convertedStr.get());
    else
      return PL_strdup(header);
  }

  char *encodedString = nsnull;
  nsresult res;
  nsCOMPtr<nsIMimeConverter> converter = do_GetService(NS_MIME_CONVERTER_CONTRACTID, &res);
  if (NS_SUCCEEDED(res) && nsnull != converter)
    res = converter->EncodeMimePartIIStr_UTF8(nsDependentCString(header), structured, charset,
      fieldnamelen, nsIMimeConverter::MIME_ENCODED_WORD_SIZE, &encodedString);

  return NS_SUCCEEDED(res) ? encodedString : nsnull;
}

// Return True if a charset is stateful (e.g. JIS).
PRBool nsMsgI18Nstateful_charset(const char *charset)
{
  //TODO: use charset manager's service
  return (PL_strcasecmp(charset, "ISO-2022-JP") == 0);
}

PRBool nsMsgI18Nmultibyte_charset(const char *charset)
{
  nsresult res;
  nsCOMPtr <nsICharsetConverterManager> ccm = do_GetService(NS_CHARSETCONVERTERMANAGER_CONTRACTID, &res);
  PRBool result = PR_FALSE;

  if (NS_SUCCEEDED(res)) {
    nsAutoString charsetData;
    res = ccm->GetCharsetData(charset, NS_LITERAL_STRING(".isMultibyte").get(), charsetData);
    if (NS_SUCCEEDED(res)) {
      result = charsetData.LowerCaseEqualsLiteral("true");
    }
  }

  return result;
}

PRBool nsMsgI18Ncheck_data_in_charset_range(const char *charset, const PRUnichar* inString, char **fallbackCharset)
{
  if (!charset || !*charset || !inString || !*inString)
    return PR_TRUE;

  nsresult res;
  PRBool result = PR_TRUE;
  
  nsCOMPtr <nsICharsetConverterManager> ccm = do_GetService(NS_CHARSETCONVERTERMANAGER_CONTRACTID, &res);

  if (NS_SUCCEEDED(res)) {
    nsCOMPtr <nsIUnicodeEncoder> encoder;

    // get an unicode converter
    res = ccm->GetUnicodeEncoderRaw(charset, getter_AddRefs(encoder));
    if(NS_SUCCEEDED(res)) {
      const PRUnichar *originalPtr = inString;
      PRInt32 originalLen = NS_strlen(inString);
      const PRUnichar *currentSrcPtr = originalPtr;
      char localBuff[512];
      PRInt32 consumedLen = 0;
      PRInt32 srcLen;
      PRInt32 dstLength;

      // convert from unicode
      while (consumedLen < originalLen) {
        srcLen = originalLen - consumedLen;
        dstLength = 512;
        res = encoder->Convert(currentSrcPtr, &srcLen, localBuff, &dstLength);
        if (NS_ERROR_UENC_NOMAPPING == res) {
          result = PR_FALSE;
          break;
        }
        else if (NS_FAILED(res) || (0 == dstLength))
          break;

        currentSrcPtr += srcLen;
        consumedLen = currentSrcPtr - originalPtr; // src length used so far
      }
    }    
  }

  // if the conversion was not successful then try fallback to other charsets
  if (!result && fallbackCharset) {
    nsCString convertedString;
    res = nsMsgI18NSaveAsCharset("text/plain", charset, inString, 
                                 getter_Copies(convertedString), fallbackCharset);
    result = (NS_SUCCEEDED(res) && NS_ERROR_UENC_NOMAPPING != res);
  }

  return result;
}

// Simple parser to parse META charset. 
// It only supports the case when the description is within one line. 
const char * 
nsMsgI18NParseMetaCharset(nsILocalFile* file) 
{ 
  static char charset[nsIMimeConverter::MAX_CHARSET_NAME_LENGTH+1];

  *charset = '\0'; 

  PRBool isDirectory = PR_FALSE;
  file->IsDirectory(&isDirectory);
  if (isDirectory) {
    NS_ERROR("file is a directory");
    return charset; 
  }

  nsresult rv;
  nsCOMPtr <nsIFileInputStream> fileStream = do_CreateInstance(NS_LOCALFILEINPUTSTREAM_CONTRACTID, &rv);
  NS_ENSURE_SUCCESS(rv, charset);
  
  rv = fileStream->Init(file, PR_RDONLY, 0664, PR_FALSE);
  nsCOMPtr <nsILineInputStream> lineStream = do_QueryInterface(fileStream, &rv);

  nsCString curLine;
  PRBool more = PR_TRUE;
  while (NS_SUCCEEDED(rv) && more) { 
    rv = lineStream->ReadLine(curLine, &more); 
    if (curLine.IsEmpty()) 
      continue; 

    ToUpperCase(curLine);

    if (curLine.Find("/HEAD") != -1) 
      break; 

    if (curLine.Find("META") != -1 && 
       curLine.Find("HTTP-EQUIV") != -1 && 
        curLine.Find("CONTENT-TYPE") != -1 && 
       curLine.Find("CHARSET") != -1) { 
      char *cp = (char *) PL_strchr(PL_strstr(curLine.get(), "CHARSET"), '=');
      char *token = nsnull;
      if (cp)
      {
        char *newStr = cp + 1;
        token = NS_strtok(" \"\'", &newStr);
      }
      if (token) { 
        PL_strncpy(charset, token, sizeof(charset));
        charset[sizeof(charset)-1] = '\0';

        // this function cannot parse a file if it is really
        // encoded by one of the following charsets
        // so we can say that the charset label must be incorrect for
        // the .html if we actually see those charsets parsed
        // and we should ignore them
        if (!PL_strncasecmp("UTF-16", charset, sizeof("UTF-16")-1) || 
            !PL_strncasecmp("UTF-32", charset, sizeof("UTF-32")-1))
          charset[0] = '\0';

        break;
      } 
    } 
  } 

  return charset; 
} 

nsresult nsMsgI18NSaveAsCharset(const char* contentType, const char *charset, 
                                const PRUnichar* inString, char** outString, 
                                char **fallbackCharset, PRBool *isAsciiOnly)
{
  NS_ENSURE_ARG_POINTER(contentType);
  NS_ENSURE_ARG_POINTER(charset);
  NS_ENSURE_ARG_POINTER(inString);
  NS_ENSURE_ARG_POINTER(outString);

  *outString = nsnull;

  if (NS_IsAscii(inString)) {
    if (isAsciiOnly)
      *isAsciiOnly = PR_TRUE;
    *outString = ToNewCString(NS_LossyConvertUTF16toASCII(inString));
    return (nsnull != *outString) ? NS_OK : NS_ERROR_OUT_OF_MEMORY;
  }
  if (isAsciiOnly)
    *isAsciiOnly = PR_FALSE;

  PRBool bTEXT_HTML = PR_FALSE;
  nsresult res;

  if (!PL_strcasecmp(contentType, TEXT_HTML)) {
    bTEXT_HTML = PR_TRUE;
  }
  else if (PL_strcasecmp(contentType, TEXT_PLAIN)) {
    return NS_ERROR_ILLEGAL_VALUE;  // not supported type
  }

  nsCOMPtr <nsICharsetAlias> calias =
    do_GetService(NS_CHARSETALIAS_CONTRACTID, &res);
  NS_ENSURE_SUCCESS(res, res);

  nsCAutoString charsetName;
  res = calias->GetPreferred(nsDependentCString(charset),
                             charsetName);
  NS_ENSURE_SUCCESS(res, res);

  // charset converter plus entity, NCR generation
  nsCOMPtr <nsISaveAsCharset> conv = do_CreateInstance(NS_SAVEASCHARSET_CONTRACTID, &res);
  NS_ENSURE_SUCCESS(res, res);

  // attribute: 
  // html text - charset conv then fallback to entity or NCR
  // plain text - charset conv then fallback to '?'
  if (bTEXT_HTML)
    // For ISO-8859-1 only, convert to entity first (always generate entites like &nbsp;).
    res = conv->Init(charsetName.get(),
                     charsetName.EqualsLiteral("ISO-8859-1") ?
                     nsISaveAsCharset::attr_htmlTextDefault :
                     nsISaveAsCharset::attr_EntityAfterCharsetConv + nsISaveAsCharset::attr_FallbackDecimalNCR, 
                     nsIEntityConverter::html32);
  else
    // fallback for text/plain: first try transliterate then '?'
    res = conv->Init(charsetName.get(), 
                     nsISaveAsCharset::attr_FallbackQuestionMark + nsISaveAsCharset::attr_EntityAfterCharsetConv, 
                     nsIEntityConverter::transliterate);
  NS_ENSURE_SUCCESS(res, res);

  const PRUnichar *input = inString;

  // Mapping characters in a certain range (required for Japanese only)
  nsAutoString mapped;
  if (charsetName.EqualsLiteral("ISO-2022-JP")) {
    static PRInt32 sSendHankakuKana = -1;
    if (sSendHankakuKana < 0) {
      nsCOMPtr<nsIPrefBranch> prefBranch(do_GetService(NS_PREFSERVICE_CONTRACTID, &res));
      NS_ENSURE_SUCCESS(res, res);
      PRBool sendHankaku;
      // Get a hidden 4.x pref with no UI, get it only once.
      if (NS_FAILED(prefBranch->GetBoolPref("mailnews.send_hankaku_kana", &sendHankaku)))
        sSendHankakuKana = 0;  // no pref means need the mapping
      else
        sSendHankakuKana = sendHankaku ? 1 : 0;
    }

    if (!sSendHankakuKana) {
      nsCOMPtr <nsITextTransform> textTransform = do_CreateInstance(NS_HANKAKUTOZENKAKU_CONTRACTID, &res);
        
      if (NS_SUCCEEDED(res)) {
        res = textTransform->Change(inString, NS_strlen(inString), mapped);
        if (NS_SUCCEEDED(res))
          input = mapped.get();
      }
    }
  }

  // Convert to charset
  res = conv->Convert(input, outString);

  // If the converer cannot encode to the charset,
  // then fallback to pref sepcified charsets.
  if (NS_ERROR_UENC_NOMAPPING == res && !bTEXT_HTML && fallbackCharset) {
    nsCOMPtr<nsIPrefBranch> prefBranch(do_GetService(NS_PREFSERVICE_CONTRACTID, &res));
    NS_ENSURE_SUCCESS(res, res);

    nsCAutoString prefString("intl.fallbackCharsetList.");
    prefString.Append(charset);
    nsCString fallbackList;
    res = prefBranch->GetCharPref(prefString.get(), getter_Copies(fallbackList));
    // do the fallback only if there is a pref for the charset
    if (NS_FAILED(res) || fallbackList.IsEmpty())
      return NS_ERROR_UENC_NOMAPPING;

    res = conv->Init(fallbackList.get(), 
                     nsISaveAsCharset::attr_FallbackQuestionMark + 
                     nsISaveAsCharset::attr_EntityAfterCharsetConv +
                     nsISaveAsCharset::attr_CharsetFallback, 
                     nsIEntityConverter::transliterate);
    NS_ENSURE_SUCCESS(res, res);

    // free whatever we have now
    PR_FREEIF(*outString);  

    res = conv->Convert(input, outString);
    NS_ENSURE_SUCCESS(res, res);

    // get the actual charset used for the conversion
    if (NS_FAILED(conv->GetCharset(fallbackCharset)))
      *fallbackCharset = nsnull;
  }
  // In case of HTML, non ASCII may be encoded as CER, NCR.
  // Exclude stateful charset which is 7 bit but not ASCII only.
  else if (isAsciiOnly && bTEXT_HTML && *outString &&
           !nsMsgI18Nstateful_charset(charsetName.get()))
    *isAsciiOnly = NS_IsAscii(*outString);

  return res;
}

nsresult nsMsgI18NShrinkUTF8Str(const nsCString &inString,
                                PRUint32 aMaxLength,
                                nsACString &outString)
{
  if (inString.IsEmpty()) {
    outString.Truncate();
    return NS_OK;
  }
  if (inString.Length() < aMaxLength) {
    outString.Assign(inString);
    return NS_OK;
  }
  NS_ASSERTION(MsgIsUTF8(inString), "Invalid UTF-8 string is inputted");
  const char* start = inString.get();
  const char* end = start + inString.Length();
  const char* last = start + aMaxLength;
  const char* cur = start;
  const char* prev = nsnull;
  while (cur < last) {
    prev = cur;
    if (!UTF8CharEnumerator::NextChar(&cur, end))
      break;
  }
  if (!prev) {
    outString.Truncate();
    return NS_OK;
  }
  PRUint32 len = prev - start;
  outString.Assign(Substring(inString, 0, len));
  return NS_OK;
}

void nsMsgI18NConvertRawBytesToUTF16(const nsCString& inString, 
                                     const char* charset,
                                     nsAString& outString)
{
  if (IsUTF8(inString))
  {
    CopyUTF8toUTF16(inString, outString);
    return;
  }

  nsresult rv = ConvertToUnicode(charset, inString, outString);
  if (NS_SUCCEEDED(rv))
    return;

  const char* cur = inString.BeginReading();
  const char* end = inString.EndReading();
  outString.Truncate();
  while (cur < end) {
    char c = *cur++;
    if (c & char(0x80))
      outString.Append(UCS2_REPLACEMENT_CHAR);
    else
      outString.Append(c);
  }
}

void nsMsgI18NConvertRawBytesToUTF8(const nsCString& inString, 
                                    const char* charset,
                                    nsACString& outString)
{
  if (IsUTF8(inString))
  {
    outString.Assign(inString);
    return;
  }

  nsAutoString utf16Text;
  nsresult rv = ConvertToUnicode(charset, inString, utf16Text);
  if (NS_SUCCEEDED(rv))
  {
    CopyUTF16toUTF8(utf16Text, outString);
    return;
  }

  // EF BF BD (UTF-8 encoding of U+FFFD)
  NS_NAMED_LITERAL_CSTRING(utf8ReplacementChar, "\357\277\275");
  const char* cur = inString.BeginReading();
  const char* end = inString.EndReading();
  outString.Truncate();
  while (cur < end) {
    char c = *cur++;
    if (c & char(0x80))
      outString.Append(utf8ReplacementChar);
    else
      outString.Append(c);
  }
}
