/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * ***** BEGIN LICENSE BLOCK *****
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
 * The Original Code is mozilla.org Code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
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

#ifndef nsOutlookCompose_h__
#define nsOutlookCompose_h__

#include "nscore.h"
#include "nsString.h"
#include "nsIFile.h"
#include "nsVoidArray.h"
#include "nsIImportService.h"

class nsIMsgSend;
class nsIMsgCompFields;
class nsIMsgIdentity;
class nsIMsgSendListener;
class nsIIOService;

#include "nsIMsgSend.h"
#include "nsNetUtil.h"

typedef class {
public:
  nsCOMPtr <nsILocalFile>  pAttachment;
  char *      mimeType;
  char *      description;
} OutlookAttachment;

typedef class {
public:
  PRUint32    offset;
  PRInt64    size;
  nsCOMPtr <nsIFile>  pFile;
        nsCOMPtr <nsIInputStream> pInputStream;
} ReadFileState;

class SimpleBufferTonyRCopiedTwice {
public:
  SimpleBufferTonyRCopiedTwice() {m_pBuffer = nsnull; m_size = 0; m_growBy = 4096; m_writeOffset = 0;
          m_bytesInBuf = 0; m_convertCRs = PR_FALSE;}
  ~SimpleBufferTonyRCopiedTwice() { if (m_pBuffer) delete [] m_pBuffer;}

  PRBool Allocate( PRInt32 sz) {
    if (m_pBuffer) delete [] m_pBuffer;
    m_pBuffer = new char[sz];
    if (m_pBuffer) { m_size = sz; return( PR_TRUE); }
    else { m_size = 0; return( PR_FALSE);}
  }

  PRBool Grow( PRInt32 newSize) { if (newSize > m_size) return( ReAllocate( newSize)); else return( PR_TRUE);}
  PRBool ReAllocate( PRInt32 newSize) {
    if (newSize <= m_size) return( PR_TRUE);
    char *pOldBuffer = m_pBuffer;
    PRInt32  oldSize = m_size;
    m_pBuffer = nsnull;
    while (m_size < newSize) m_size += m_growBy;
    if (Allocate( m_size)) {
      if (pOldBuffer) { memcpy( m_pBuffer, pOldBuffer, oldSize); delete [] pOldBuffer;}
      return( PR_TRUE);
    }
    else { m_pBuffer = pOldBuffer; m_size = oldSize; return( PR_FALSE);}
  }

  PRBool Write( PRInt32 offset, const char *pData, PRInt32 len, PRInt32 *pWritten) {
    *pWritten = len;
    if (!len) return( PR_TRUE);
    if (!Grow( offset + len)) return( PR_FALSE);
    if (m_convertCRs)
      return( SpecialMemCpy( offset, pData, len, pWritten));
    memcpy( m_pBuffer + offset, pData, len);
    return( PR_TRUE);
  }

  PRBool Write( const char *pData, PRInt32 len) {
    PRInt32 written;
    if (Write( m_writeOffset, pData, len, &written)) { m_writeOffset += written; return( PR_TRUE);}
    else return( PR_FALSE);
  }

  PRBool  SpecialMemCpy( PRInt32 offset, const char *pData, PRInt32 len, PRInt32 *pWritten);

  PRBool  m_convertCRs;
  char *  m_pBuffer;
  PRInt32  m_bytesInBuf;  // used when reading into this buffer
  PRInt32  m_size;      // allocated size of buffer
  PRInt32  m_growBy;    // duh
  PRInt32  m_writeOffset;  // used when writing into and reading from the buffer
};



class nsOutlookCompose {
public:
  nsOutlookCompose();
  ~nsOutlookCompose();

  nsresult  SendTheMessage(nsMsgDeliverMode mode, nsCString &useThisCType, nsIFile **pMsg);

  void    SetBody( const char *pBody) { m_Body = pBody;}
  void    SetHeaders( const char *pHeaders) { m_Headers = pHeaders;}
  void    SetAttachments( nsVoidArray *pAttachments) { m_pAttachments = pAttachments;}

  nsresult  CopyComposedMessage( nsCString& fromLine, nsIFile *pSrc, nsIOutputStream *pDst, SimpleBufferTonyRCopiedTwice& copy);

  static nsresult  FillMailBuffer( ReadFileState *pState, SimpleBufferTonyRCopiedTwice& read);

private:
  nsresult  CreateComponents( void);
  nsresult  CreateIdentity( void);

  void    GetNthHeader( const char *pData, PRInt32 dataLen, PRInt32 n, nsCString& header, nsCString& val, PRBool unwrap);
  void    GetHeaderValue( const char *pData, PRInt32 dataLen, const char *pHeader, nsCString& val, PRBool unwrap = PR_TRUE);
  void    GetHeaderValue( const char *pData, PRInt32 dataLen, const char *pHeader, nsString& val) {
    val.Truncate();
    nsCString  hVal;
    GetHeaderValue( pData, dataLen, pHeader, hVal, PR_TRUE);
    CopyUTF8toUTF16(hVal, val);
  }
  void    ExtractCharset( nsString& str);
  void    ExtractType( nsString& str);

  nsMsgAttachedFile * GetLocalAttachments( void);
  void        CleanUpAttach( nsMsgAttachedFile *a, PRInt32 count);

  nsresult  ReadHeaders( ReadFileState *pState, SimpleBufferTonyRCopiedTwice& copy, SimpleBufferTonyRCopiedTwice& header);
  PRInt32    FindNextEndLine( SimpleBufferTonyRCopiedTwice& data);
  PRInt32    IsEndHeaders( SimpleBufferTonyRCopiedTwice& data);
  PRInt32    IsSpecialHeader( const char *pHeader);
  nsresult  WriteHeaders( nsIOutputStream *pDst, SimpleBufferTonyRCopiedTwice& newHeaders);
  PRBool    IsReplaceHeader( const char *pHeader);
  void      ConvertSystemStringToUnicode( const char *pSysStr, nsString& uniStr);


private:
  nsVoidArray *      m_pAttachments;
  nsIMsgSendListener *  m_pListener;
  nsIMsgSend *      m_pMsgSend;
  nsIMsgSend *      m_pSendProxy;
  nsIMsgCompFields *    m_pMsgFields;
  nsIMsgIdentity *    m_pIdentity;
  nsIIOService *      m_pIOService;
  nsCString       m_Headers;
  nsCString       m_Body;
  SimpleBufferTonyRCopiedTwice      m_readHeaders;
  nsCOMPtr<nsIImportService>  m_pImportService;
};


#endif /* nsOutlookCompose_h__ */
