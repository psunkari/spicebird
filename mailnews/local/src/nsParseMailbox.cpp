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
 * Portions created by the Initial Developer are Copyright (C) 1999
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Pierre Phaneuf <pp@ludusdesign.com>
 *   David Bienvenu <bienvenu@mozilla.org>
 *   Karsten Düsterloh <mnyromyr@tprac.de>
 *   Jeremy Morton <bugzilla@game-point.net>
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

#include "msgCore.h"
#include "nsIURI.h"
#include "nsParseMailbox.h"
#include "nsIMsgHdr.h"
#include "nsIMsgDatabase.h"
#include "nsMsgMessageFlags.h"
#include "nsIDBFolderInfo.h"
#include "nsIInputStream.h"
#include "nsILocalFile.h"
#include "nsMsgLocalFolderHdrs.h"
#include "nsMsgBaseCID.h"
#include "nsMsgDBCID.h"
#include "nsIMailboxUrl.h"
#include "nsNetUtil.h"
#include "nsMsgFolderFlags.h"
#include "nsIMsgFolder.h"
#include "nsIURL.h"
#include "nsIMsgMailNewsUrl.h"
#include "nsIMsgFilterList.h"
#include "nsIMsgFilter.h"
#include "nsIIOService.h"
#include "nsNetCID.h"
#include "nsRDFCID.h"
#include "nsIRDFService.h"
#include "nsMsgI18N.h"
#include "nsAppDirectoryServiceDefs.h"
#include "nsIMsgLocalMailFolder.h"
#include "nsMsgUtils.h"
#include "prprf.h"
#include "prmem.h"
#include "nsISeekableStream.h"
#include "nsIMimeHeaders.h"
#include "nsIMsgMdnGenerator.h"
#include "nsMsgSearchCore.h"
#include "nsMailHeaders.h"
#include "nsIMsgMailSession.h"
#include "nsIMsgComposeParams.h"
#include "nsMsgCompCID.h"
#include "nsIInterfaceRequestor.h"
#include "nsIInterfaceRequestorUtils.h"
#include "nsIDocShell.h"
#include "nsIMsgCompose.h"
#include "nsIDOMWindowInternal.h"
#include "nsIPrefBranch.h"
#include "nsIPrefService.h"
#include "nsIMsgComposeService.h"
#include "nsIMsgCopyService.h"
#include "nsICryptoHash.h"
#include "nsIStringBundle.h"
#include "nsLocalStrings.h"
#include "nsIMsgFilterPlugin.h"
#include "nsIMutableArray.h"
#include "nsArrayUtils.h"
#include "nsIMsgFilterCustomAction.h"
#include <ctype.h>

static NS_DEFINE_CID(kCMailDB, NS_MAILDB_CID);
static NS_DEFINE_CID(kRDFServiceCID, NS_RDFSERVICE_CID);

/* the following macros actually implement addref, release and query interface for our component. */
NS_IMPL_ISUPPORTS_INHERITED2(nsMsgMailboxParser,
                             nsParseMailMessageState,
                             nsIStreamListener,
                             nsIRequestObserver)

// Whenever data arrives from the connection, core netlib notifices the protocol by calling
// OnDataAvailable. We then read and process the incoming data from the input stream.
NS_IMETHODIMP nsMsgMailboxParser::OnDataAvailable(nsIRequest *request, nsISupports *ctxt, nsIInputStream *aIStream, PRUint32 sourceOffset, PRUint32 aLength)
{
    // right now, this really just means turn around and process the url
    nsresult rv = NS_OK;
    nsCOMPtr<nsIURI> url = do_QueryInterface(ctxt, &rv);
    if (NS_SUCCEEDED(rv))
        rv = ProcessMailboxInputStream(url, aIStream, aLength);
    return rv;
}

NS_IMETHODIMP nsMsgMailboxParser::OnStartRequest(nsIRequest *request, nsISupports *ctxt)
{
    nsTime currentTime;
    m_startTime = currentTime;


    // extract the appropriate event sinks from the url and initialize them in our protocol data
    // the URL should be queried for a nsIMailboxURL. If it doesn't support a mailbox URL interface then
    // we have an error.
    nsresult rv = NS_OK;

    nsCOMPtr<nsIIOService> ioServ(do_GetService(NS_IOSERVICE_CONTRACTID, &rv));

    nsCOMPtr<nsIMailboxUrl> runningUrl = do_QueryInterface(ctxt, &rv);

    nsCOMPtr<nsIMsgMailNewsUrl> url = do_QueryInterface(ctxt);
    nsCOMPtr<nsIMsgFolder> folder = do_QueryReferent(m_folder);

    if (NS_SUCCEEDED(rv) && runningUrl && folder)
    {
        url->GetStatusFeedback(getter_AddRefs(m_statusFeedback));

        // okay, now fill in our event sinks...Note that each getter ref counts before
        // it returns the interface to us...we'll release when we are done

        folder->GetName(m_folderName);

        nsCOMPtr<nsILocalFile> path;
        folder->GetFilePath(getter_AddRefs(path));

        if (path)
        {
          PRInt64 fileSize;
          path->GetFileSize(&fileSize);
            // the size of the mailbox file is our total base line for measuring progress
            m_graph_progress_total = (PRUint32) fileSize;
            UpdateStatusText(LOCAL_STATUS_SELECTING_MAILBOX);

            nsCOMPtr<nsIMsgDBService> msgDBService = do_GetService(NS_MSGDB_SERVICE_CONTRACTID, &rv);
            if (msgDBService)
            {
                // Use OpenFolderDB to always open the db so that db's m_folder
                // is set correctly.
                rv = msgDBService->OpenFolderDB(folder, PR_TRUE,
                                                getter_AddRefs(m_mailDB));
                if (rv == NS_MSG_ERROR_FOLDER_SUMMARY_MISSING)
                  rv = msgDBService->CreateNewDB(folder,
                                                 getter_AddRefs(m_mailDB));

                if (m_mailDB)
                    m_mailDB->AddListener(this);
            }
            NS_ASSERTION(m_mailDB, "failed to open mail db parsing folder");

            // try to get a backup message database
            nsresult rvignore = folder->GetBackupMsgDatabase(
                getter_AddRefs(m_backupMailDB));

            // We'll accept failures and move on, as we're dealing with some
            // sort of unknown problem to begin with.
            if (NS_FAILED(rvignore))
            {
              if (m_backupMailDB)
                m_backupMailDB->RemoveListener(this);
              m_backupMailDB = nsnull;
            }
            else if (m_backupMailDB)
            {
              m_backupMailDB->AddListener(this);
            }
        }
    }

    // need to get the mailbox name out of the url and call SetMailboxName with it.
    // then, we need to open the mail db for this parser.
    return rv;
}

// stop binding is a "notification" informing us that the stream associated with aURL is going away.
NS_IMETHODIMP nsMsgMailboxParser::OnStopRequest(nsIRequest *request, nsISupports *ctxt, nsresult aStatus)
{
    DoneParsingFolder(aStatus);
    // what can we do? we can close the stream?
    m_urlInProgress = PR_FALSE;  // don't close the connection...we may be re-using it.

    if (m_mailDB)
        m_mailDB->RemoveListener(this);
    // and we want to mark ourselves for deletion or some how inform our protocol manager that we are
    // available for another url if there is one....

    ReleaseFolderLock();
    // be sure to clear any status text and progress info..
    m_graph_progress_received = 0;
    UpdateProgressPercent();
    UpdateStatusText(LOCAL_STATUS_DOCUMENT_DONE);

    return NS_OK;
}

NS_IMETHODIMP
nsParseMailMessageState::OnHdrPropertyChanged(nsIMsgDBHdr *aHdrToChange,
    PRBool aPreChange, PRUint32 *aStatus, nsIDBChangeListener * aInstigator)
{
  return NS_OK;
}


NS_IMETHODIMP
nsParseMailMessageState::OnHdrFlagsChanged(nsIMsgDBHdr *aHdrChanged,
    PRUint32 aOldFlags, PRUint32 aNewFlags, nsIDBChangeListener *aInstigator)
{
    return NS_OK;
}

NS_IMETHODIMP
nsParseMailMessageState::OnHdrDeleted(nsIMsgDBHdr *aHdrChanged,
    nsMsgKey aParentKey, PRInt32 aFlags, nsIDBChangeListener *aInstigator)
{
    return NS_OK;
}

NS_IMETHODIMP
nsParseMailMessageState::OnHdrAdded(nsIMsgDBHdr *aHdrAdded,
    nsMsgKey aParentKey, PRInt32 aFlags, nsIDBChangeListener *aInstigator)
{
    return NS_OK;
}

/* void OnParentChanged (in nsMsgKey aKeyChanged, in nsMsgKey oldParent, in nsMsgKey newParent, in nsIDBChangeListener aInstigator); */
NS_IMETHODIMP
nsParseMailMessageState::OnParentChanged(nsMsgKey aKeyChanged,
    nsMsgKey oldParent, nsMsgKey newParent, nsIDBChangeListener *aInstigator)
{
    return NS_OK;
}

/* void OnAnnouncerGoingAway (in nsIDBChangeAnnouncer instigator); */
NS_IMETHODIMP
nsParseMailMessageState::OnAnnouncerGoingAway(nsIDBChangeAnnouncer *instigator)
{
  if (m_backupMailDB && m_backupMailDB == instigator)
  {
    m_backupMailDB->RemoveListener(this);
    m_backupMailDB = nsnull;
  }
  else if (m_mailDB)
  {
    m_mailDB->RemoveListener(this);
    m_mailDB = nsnull;
    m_newMsgHdr = nsnull;
  }
  return NS_OK;
}

NS_IMETHODIMP nsParseMailMessageState::OnEvent(nsIMsgDatabase *aDB, const char *aEvent)
{
  return NS_OK;
}

/* void OnReadChanged (in nsIDBChangeListener instigator); */
NS_IMETHODIMP
nsParseMailMessageState::OnReadChanged(nsIDBChangeListener *instigator)
{
    return NS_OK;
}

/* void OnJunkScoreChanged (in nsIDBChangeListener instigator); */
NS_IMETHODIMP
nsParseMailMessageState::OnJunkScoreChanged(nsIDBChangeListener *instigator)
{
    return NS_OK;
}

nsMsgMailboxParser::nsMsgMailboxParser() : nsMsgLineBuffer(nsnull, PR_FALSE)
{
  Init();
}

nsMsgMailboxParser::nsMsgMailboxParser(nsIMsgFolder *aFolder) : nsMsgLineBuffer(nsnull, PR_FALSE)
{
  Init();
  m_folder = do_GetWeakReference(aFolder);
}

nsMsgMailboxParser::~nsMsgMailboxParser()
{
  ReleaseFolderLock();
}

void nsMsgMailboxParser::Init()
{
  m_obuffer = nsnull;
  m_obuffer_size = 0;
  m_graph_progress_total = 0;
  m_graph_progress_received = 0;
}

void nsMsgMailboxParser::UpdateStatusText (PRUint32 stringID)
{
  if (m_statusFeedback)
  {
    nsresult rv;
    nsCOMPtr<nsIStringBundleService> bundleService(do_GetService("@mozilla.org/intl/stringbundle;1", &rv));
    if (NS_FAILED(rv))
      return;
    nsCOMPtr<nsIStringBundle> bundle;
    rv = bundleService->CreateBundle("chrome://messenger/locale/localMsgs.properties", getter_AddRefs(bundle));
    if (NS_FAILED(rv))
      return;
    nsString finalString;
    if (stringID == LOCAL_STATUS_SELECTING_MAILBOX)
    {
      const PRUnichar * stringArray[] = { m_folderName.get() };
      rv = bundle->FormatStringFromID(stringID, stringArray, 1,
                                      getter_Copies(finalString));
    }
    else
      bundle->GetStringFromID(stringID, getter_Copies(finalString));
    m_statusFeedback->ShowStatusString(finalString);
  }
}

void nsMsgMailboxParser::UpdateProgressPercent ()
{
  if (m_statusFeedback && m_graph_progress_total != 0)
  {
    // prevent overflow by dividing both by 100
    PRUint32 progressTotal = m_graph_progress_total / 100;
    PRUint32 progressReceived = m_graph_progress_received / 100;
    if (progressTotal > 0)
      m_statusFeedback->ShowProgress((100 *(progressReceived))  / progressTotal);
  }
}

int nsMsgMailboxParser::ProcessMailboxInputStream(nsIURI* aURL, nsIInputStream *aIStream, PRUint32 aLength)
{
  nsresult ret = NS_OK;

  PRUint32 bytesRead = 0;

  if (NS_SUCCEEDED(m_inputStream.GrowBuffer(aLength)))
  {
    // OK, this sucks, but we're going to have to copy into our
    // own byte buffer, and then pass that to the line buffering code,
    // which means a couple buffer copies.
    ret = aIStream->Read(m_inputStream.GetBuffer(), aLength, &bytesRead);
    if (NS_SUCCEEDED(ret))
      ret = BufferInput(m_inputStream.GetBuffer(), bytesRead);
  }
  if (m_graph_progress_total > 0)
  {
    if (NS_SUCCEEDED(ret))
      m_graph_progress_received += bytesRead;
  }
  return (ret);
}

void nsMsgMailboxParser::DoneParsingFolder(nsresult status)
{
  /* End of file.  Flush out any partial line remaining in the buffer. */
  FlushLastLine();
  PublishMsgHeader(nsnull);

  // only mark the db valid if we've succeeded.
  if (NS_SUCCEEDED(status) && m_mailDB)  // finished parsing, so flush db folder info
    UpdateDBFolderInfo();
  else if (m_mailDB)
    m_mailDB->SetSummaryValid(PR_FALSE);

  // remove the backup database
  if (m_backupMailDB)
  {
    nsCOMPtr<nsIMsgFolder> folder = do_QueryReferent(m_folder);
    if (folder)
      folder->RemoveBackupMsgDatabase();
    m_backupMailDB = nsnull;
  }

  //  if (m_folder != nsnull)
  //    m_folder->SummaryChanged();
  FreeBuffers();
}

void nsMsgMailboxParser::FreeBuffers()
{
  /* We're done reading the folder - we don't need these things
   any more. */
  PR_FREEIF (m_obuffer);
  m_obuffer_size = 0;
}

void nsMsgMailboxParser::UpdateDBFolderInfo()
{
  UpdateDBFolderInfo(m_mailDB);
}

// update folder info in db so we know not to reparse.
void nsMsgMailboxParser::UpdateDBFolderInfo(nsIMsgDatabase *mailDB)
{
  mailDB->SetSummaryValid(PR_TRUE);
}

// Tell the world about the message header (add to db, and view, if any)
PRInt32 nsMsgMailboxParser::PublishMsgHeader(nsIMsgWindow *msgWindow)
{
  FinishHeader();
  if (m_newMsgHdr)
  {
    PRUint32 flags;
    (void)m_newMsgHdr->GetFlags(&flags);
    if (flags & nsMsgMessageFlags::Expunged)
    {
      nsCOMPtr<nsIDBFolderInfo> folderInfo;
      m_mailDB->GetDBFolderInfo(getter_AddRefs(folderInfo));
      PRUint32 size;
      (void)m_newMsgHdr->GetMessageSize(&size);
      folderInfo->ChangeExpungedBytes(size);
      m_newMsgHdr = nsnull;
    }
    else if (m_mailDB)
    {
      // add hdr but don't notify - shouldn't be requiring notifications
      // during summary file rebuilding
      m_mailDB->AddNewHdrToDB(m_newMsgHdr, PR_FALSE);
      m_newMsgHdr = nsnull;
    }
    else
      NS_ASSERTION(PR_FALSE, "no database while parsing local folder");  // should have a DB, no?
  }
  else if (m_mailDB)
  {
    nsCOMPtr<nsIDBFolderInfo> folderInfo;
    m_mailDB->GetDBFolderInfo(getter_AddRefs(folderInfo));
    if (folderInfo)
      folderInfo->ChangeExpungedBytes(m_position - m_envelope_pos);
  }
  return 0;
}

void nsMsgMailboxParser::AbortNewHeader()
{
  if (m_newMsgHdr && m_mailDB)
    m_newMsgHdr = nsnull;
}

PRInt32 nsMsgMailboxParser::HandleLine(char *line, PRUint32 lineLength)
{
  int status = 0;

  /* If this is the very first line of a non-empty folder, make sure it's an envelope */
  if (m_graph_progress_received == 0)
  {
    /* This is the first block from the file.  Check to see if this
       looks like a mail file. */
    const char *s = line;
    const char *end = s + lineLength;
    while (s < end && IS_SPACE(*s))
      s++;
    if ((end - s) < 20 || !IsEnvelopeLine(s, end - s))
    {
//      char buf[500];
//      PR_snprintf (buf, sizeof(buf),
//             XP_GetString(MK_MSG_NON_MAIL_FILE_READ_QUESTION),
//             folder_name);
//      else if (!FE_Confirm (m_context, buf))
//        return NS_MSG_NOT_A_MAIL_FOLDER; /* #### NOT_A_MAIL_FILE */
    }
  }
//  m_graph_progress_received += lineLength;

  // mailbox parser needs to do special stuff when it finds an envelope
  // after parsing a message body. So do that.
  if (line[0] == 'F' && IsEnvelopeLine(line, lineLength))
  {
    // **** This used to be
    // PR_ASSERT (m_parseMsgState->m_state == nsMailboxParseBodyState);
    // **** I am not sure this is a right thing to do. This happens when
    // going online, downloading a message while playing back append
    // draft/template offline operation. We are mixing
        // nsMailboxParseBodyState &&
    // nsMailboxParseHeadersState. David I need your help here too. **** jt

    NS_ASSERTION (m_state == nsIMsgParseMailMsgState::ParseBodyState ||
           m_state == nsIMsgParseMailMsgState::ParseHeadersState, "invalid parse state"); /* else folder corrupted */
    PublishMsgHeader(nsnull);
    Clear();
    status = StartNewEnvelope(line, lineLength);
    NS_ASSERTION(status >= 0, " error starting envelope parsing mailbox");
    // at the start of each new message, update the progress bar
    UpdateProgressPercent();
    if (status < 0)
      return status;
  }
  // otherwise, the message parser can handle it completely.
  else if (m_mailDB != nsnull)  // if no DB, do we need to parse at all?
    return ParseFolderLine(line, lineLength);
        else
          return NS_ERROR_NULL_POINTER; // need to error out if we don't have a db.

  return 0;

}

void
nsMsgMailboxParser::ReleaseFolderLock()
{
  nsresult result;
  nsCOMPtr<nsIMsgFolder> folder = do_QueryReferent(m_folder);
  if (!folder)
    return;
  PRBool haveSemaphore;
  nsCOMPtr <nsISupports> supports = do_QueryInterface(static_cast<nsIMsgParseMailMsgState*>(this));
  result = folder->TestSemaphore(supports, &haveSemaphore);
  if(NS_SUCCEEDED(result) && haveSemaphore)
    result = folder->ReleaseSemaphore(supports);
  return;
}

NS_IMPL_ISUPPORTS2(nsParseMailMessageState, nsIMsgParseMailMsgState, nsIDBChangeListener)

nsParseMailMessageState::nsParseMailMessageState()
{
  m_position = 0;
  m_IgnoreXMozillaStatus = PR_FALSE;
  m_state = nsIMsgParseMailMsgState::ParseBodyState;

  // setup handling of custom db headers, headers that are added to .msf files
  // as properties of the nsMsgHdr objects, controlled by the
  // pref mailnews.customDBHeaders, a space-delimited list of headers.
  // E.g., if mailnews.customDBHeaders is "X-Spam-Score", and we're parsing
  // a mail message with the X-Spam-Score header, we'll set the
  // "x-spam-score" property of nsMsgHdr to the value of the header.
  m_customDBHeaderValues = nsnull;
  nsCString customDBHeaders;
  nsCOMPtr<nsIPrefBranch> pPrefBranch(do_GetService(NS_PREFSERVICE_CONTRACTID));
  if (pPrefBranch)
  {
     pPrefBranch->GetCharPref("mailnews.customDBHeaders",  getter_Copies(customDBHeaders));
     ToLowerCase(customDBHeaders);
     ParseString(customDBHeaders, ' ', m_customDBHeaders);
     if (m_customDBHeaders.Length())
     {
       m_customDBHeaderValues = new struct message_header [m_customDBHeaders.Length()];
       if (!m_customDBHeaderValues)
         m_customDBHeaders.Clear();
     }
  }
  Clear();
  m_HeaderAddressParser = do_GetService(NS_MAILNEWS_MIME_HEADER_PARSER_CONTRACTID);
}

nsParseMailMessageState::~nsParseMailMessageState()
{
  ClearAggregateHeader (m_toList);
  ClearAggregateHeader (m_ccList);
  delete [] m_customDBHeaderValues;
}

void nsParseMailMessageState::Init(PRUint32 fileposition)
{
  m_state = nsIMsgParseMailMsgState::ParseBodyState;
  m_position = fileposition;
  m_newMsgHdr = nsnull;
}

NS_IMETHODIMP nsParseMailMessageState::Clear()
{
  m_message_id.length = 0;
  m_references.length = 0;
  m_date.length = 0;
  m_delivery_date.length = 0;
  m_from.length = 0;
  m_sender.length = 0;
  m_newsgroups.length = 0;
  m_subject.length = 0;
  m_status.length = 0;
  m_mozstatus.length = 0;
  m_mozstatus2.length = 0;
  m_envelope_from.length = 0;
  m_envelope_date.length = 0;
  m_priority.length = 0;
  m_keywords.length = 0;
  m_mdn_dnt.length = 0;
  m_return_path.length = 0;
  m_account_key.length = 0;
  m_in_reply_to.length = 0;
  m_replyTo.length = 0;
  m_content_type.length = 0;
  m_mdn_original_recipient.length = 0;
  m_bccList.length = 0;
  m_body_lines = 0;
  m_newMsgHdr = nsnull;
  m_envelope_pos = 0;
  ClearAggregateHeader (m_toList);
  ClearAggregateHeader (m_ccList);
  m_headers.ResetWritePos();
  m_envelope.ResetWritePos();
  m_receivedTime = LL_ZERO;
  for (PRUint32 i = 0; i < m_customDBHeaders.Length(); i++)
    m_customDBHeaderValues[i].length = 0;

  return NS_OK;
}

NS_IMETHODIMP nsParseMailMessageState::SetState(nsMailboxParseState aState)
{
  m_state = aState;
  return NS_OK;
}

NS_IMETHODIMP nsParseMailMessageState::GetState(nsMailboxParseState *aState)
{
  if (!aState)
    return NS_ERROR_NULL_POINTER;

  *aState = m_state;
  return NS_OK;
}

NS_IMETHODIMP
nsParseMailMessageState::GetEnvelopePos(PRUint32 *aEnvelopePos)
{
    if (!aEnvelopePos)
        return NS_ERROR_NULL_POINTER;
    *aEnvelopePos = m_envelope_pos;
    return NS_OK;
}

NS_IMETHODIMP nsParseMailMessageState::SetEnvelopePos(PRUint32 aEnvelopePos)
{
  m_envelope_pos = aEnvelopePos;
  m_position = m_envelope_pos;
  m_headerstartpos = m_position;
  return NS_OK;
}

NS_IMETHODIMP nsParseMailMessageState::GetNewMsgHdr(nsIMsgDBHdr ** aMsgHeader)
{
  NS_ENSURE_ARG_POINTER(aMsgHeader);
  NS_IF_ADDREF(*aMsgHeader = m_newMsgHdr);
  return m_newMsgHdr ? NS_OK : NS_ERROR_NULL_POINTER;
}

NS_IMETHODIMP nsParseMailMessageState::ParseAFolderLine(const char *line, PRUint32 lineLength)
{
  ParseFolderLine(line, lineLength);
  return NS_OK;
}

PRInt32 nsParseMailMessageState::ParseFolderLine(const char *line, PRUint32 lineLength)
{
  int status = 0;

  if (m_state == nsIMsgParseMailMsgState::ParseHeadersState)
  {
    if (EMPTY_MESSAGE_LINE(line))
    {
      /* End of headers.  Now parse them. */
      status = ParseHeaders();
      NS_ASSERTION(status >= 0, "error parsing headers parsing mailbox");
      if (status < 0)
        return status;

      status = FinalizeHeaders();
      NS_ASSERTION(status >= 0, "error finalizing headers parsing mailbox");
      if (status < 0)
        return status;
      m_state = nsIMsgParseMailMsgState::ParseBodyState;
    }
    else
    {
      /* Otherwise, this line belongs to a header.  So append it to the
         header data, and stay in MBOX `MIME_PARSE_HEADERS' state.
      */
      m_headers.AppendBuffer(line, lineLength);
    }
  }
  else if ( m_state == nsIMsgParseMailMsgState::ParseBodyState)
  {
    m_body_lines++;
  }

  m_position += lineLength;

  return 0;
}

NS_IMETHODIMP nsParseMailMessageState::SetMailDB(nsIMsgDatabase *mailDB)
{
  m_mailDB = mailDB;
  return NS_OK;
}

NS_IMETHODIMP nsParseMailMessageState::SetBackupMailDB(nsIMsgDatabase *aBackupMailDB)
{
  m_backupMailDB = aBackupMailDB;
  if (m_backupMailDB)
    m_backupMailDB->AddListener(this);
  return NS_OK;
}

NS_IMETHODIMP nsParseMailMessageState::SetDBFolderStream(nsIOutputStream *fileStream)
{
  NS_ASSERTION(m_mailDB, "m_mailDB is not set");
  if (m_mailDB)
    m_mailDB->SetFolderStream(fileStream);
  return NS_OK;
}

/* #define STRICT_ENVELOPE */

PRBool
nsParseMailMessageState::IsEnvelopeLine(const char *buf, PRInt32 buf_size)
{
#ifdef STRICT_ENVELOPE
  /* The required format is
     From jwz  Fri Jul  1 09:13:09 1994
   But we should also allow at least:
     From jwz  Fri, Jul 01 09:13:09 1994
     From jwz  Fri Jul  1 09:13:09 1994 PST
     From jwz  Fri Jul  1 09:13:09 1994 (+0700)

   We can't easily call XP_ParseTimeString() because the string is not
   null terminated (ok, we could copy it after a quick check...) but
   XP_ParseTimeString() may be too lenient for our purposes.

   DANGER!!  The released version of 2.0b1 was (on some systems,
   some Unix, some NT, possibly others) writing out envelope lines
   like "From - 10/13/95 11:22:33" which STRICT_ENVELOPE will reject!
   */
  const char *date, *end;

  if (buf_size < 29) return PR_FALSE;
  if (*buf != 'F') return PR_FALSE;
  if (strncmp(buf, "From ", 5)) return PR_FALSE;

  end = buf + buf_size;
  date = buf + 5;

  /* Skip horizontal whitespace between "From " and user name. */
  while ((*date == ' ' || *date == '\t') && date < end)
  date++;

  /* If at the end, it doesn't match. */
  if (IS_SPACE(*date) || date == end)
  return PR_FALSE;

  /* Skip over user name. */
  while (!IS_SPACE(*date) && date < end)
  date++;

  /* Skip horizontal whitespace between user name and date. */
  while ((*date == ' ' || *date == '\t') && date < end)
  date++;

  /* Don't want this to be localized. */
# define TMP_ISALPHA(x) (((x) >= 'A' && (x) <= 'Z') || \
             ((x) >= 'a' && (x) <= 'z'))

  /* take off day-of-the-week. */
  if (date >= end - 3)
  return PR_FALSE;
  if (!TMP_ISALPHA(date[0]) || !TMP_ISALPHA(date[1]) || !TMP_ISALPHA(date[2]))
  return PR_FALSE;
  date += 3;
  /* Skip horizontal whitespace (and commas) between dotw and month. */
  if (*date != ' ' && *date != '\t' && *date != ',')
  return PR_FALSE;
  while ((*date == ' ' || *date == '\t' || *date == ',') && date < end)
  date++;

  /* take off month. */
  if (date >= end - 3)
  return PR_FALSE;
  if (!TMP_ISALPHA(date[0]) || !TMP_ISALPHA(date[1]) || !TMP_ISALPHA(date[2]))
  return PR_FALSE;
  date += 3;
  /* Skip horizontal whitespace between month and dotm. */
  if (date == end || (*date != ' ' && *date != '\t'))
  return PR_FALSE;
  while ((*date == ' ' || *date == '\t') && date < end)
  date++;

  /* Skip over digits and whitespace. */
  while (((*date >= '0' && *date <= '9') || *date == ' ' || *date == '\t') &&
     date < end)
  date++;
  /* Next character should be a colon. */
  if (date >= end || *date != ':')
  return PR_FALSE;

  /* Ok, that ought to be enough... */

# undef TMP_ISALPHA

#else  /* !STRICT_ENVELOPE */

  if (buf_size < 5) return PR_FALSE;
  if (*buf != 'F') return PR_FALSE;
  if (strncmp(buf, "From ", 5)) return PR_FALSE;

#endif /* !STRICT_ENVELOPE */

  return PR_TRUE;
}


// We've found the start of the next message, so finish this one off.
NS_IMETHODIMP nsParseMailMessageState::FinishHeader()
{
  if (m_newMsgHdr)
  {
    m_newMsgHdr->SetMessageKey(m_envelope_pos);
    m_newMsgHdr->SetMessageSize(m_position - m_envelope_pos);  // dmb - no longer number of lines.
    m_newMsgHdr->SetLineCount(m_body_lines);
  }

  return NS_OK;
}

NS_IMETHODIMP nsParseMailMessageState::GetAllHeaders(char ** pHeaders, PRInt32 *pHeadersSize)
{
  if (!pHeaders || !pHeadersSize)
    return NS_ERROR_NULL_POINTER;
  *pHeaders = m_headers.GetBuffer();
  *pHeadersSize = m_headers.GetBufferPos();
  return NS_OK;
}

// generate headers as a string, with CRLF between the headers
NS_IMETHODIMP nsParseMailMessageState::GetHeaders(char ** pHeaders)
{
  NS_ENSURE_ARG_POINTER(pHeaders);
  nsCString crlfHeaders;
  char *curHeader = m_headers.GetBuffer();
  for (PRUint32 headerPos = 0; headerPos < m_headers.GetBufferPos();)
  {
    crlfHeaders.Append(curHeader);
    crlfHeaders.Append(CRLF);
    PRInt32 headerLen = strlen(curHeader);
    curHeader += headerLen + 1;
    headerPos += headerLen + 1;
  }
  *pHeaders = ToNewCString(crlfHeaders);
  return NS_OK;
}

struct message_header *nsParseMailMessageState::GetNextHeaderInAggregate (nsVoidArray &list)
{
  // When parsing a message with multiple To or CC header lines, we're storing each line in a
  // list, where the list represents the "aggregate" total of all the header. Here we get a new
  // line for the list

  struct message_header *header = (struct message_header*) PR_Calloc (1, sizeof(struct message_header));
  list.AppendElement (header);
  return header;
}

void nsParseMailMessageState::GetAggregateHeader (nsVoidArray &list, struct message_header *outHeader)
{
  // When parsing a message with multiple To or CC header lines, we're storing each line in a
  // list, where the list represents the "aggregate" total of all the header. Here we combine
  // all the lines together, as though they were really all found on the same line

  struct message_header *header = nsnull;
  int length = 0;
  int i;

  // Count up the bytes required to allocate the aggregated header
  for (i = 0; i < list.Count(); i++)
  {
    header = (struct message_header*) list.ElementAt(i);
    length += (header->length + 1); //+ for ","
    NS_ASSERTION(header->length == (PRInt32)strlen(header->value), "header corrupted");
  }

  if (length > 0)
  {
    char *value = (char*) PR_MALLOC (length + 1); //+1 for null term
    if (value)
    {
      // Catenate all the To lines together, separated by commas
      value[0] = '\0';
      int size = list.Count();
      for (i = 0; i < size; i++)
      {
        header = (struct message_header*) list.ElementAt(i);
        PL_strcat (value, header->value);
        if (i + 1 < size)
          PL_strcat (value, ",");
      }
      outHeader->length = length;
      outHeader->value = value;
    }
  }
  else
  {
    outHeader->length = 0;
    outHeader->value = nsnull;
  }
}

void nsParseMailMessageState::ClearAggregateHeader (nsVoidArray &list)
{
  // Reset the aggregate headers. Free only the message_header struct since
  // we don't own the value pointer

  for (int i = 0; i < list.Count(); i++)
    PR_Free ((struct message_header*) list.ElementAt(i));
  list.Clear();
}

// We've found a new envelope to parse.
int nsParseMailMessageState::StartNewEnvelope(const char *line, PRUint32 lineLength)
{
  m_envelope_pos = m_position;
  m_state = nsIMsgParseMailMsgState::ParseHeadersState;
  m_position += lineLength;
  m_headerstartpos = m_position;
  return ParseEnvelope (line, lineLength);
}

/* largely lifted from mimehtml.c, which does similar parsing, sigh...
*/
int nsParseMailMessageState::ParseHeaders ()
{
  char *buf = m_headers.GetBuffer();
  char *buf_end = buf + m_headers.GetBufferPos();
  while (buf < buf_end)
  {
    char *colon = PL_strchr (buf, ':');
    char *end;
    char *value = 0;
    struct message_header *header = 0;
    struct message_header receivedBy;

    if (! colon)
      break;

    end = colon;
    while (end > buf && (*end == ' ' || *end == '\t'))
      end--;

    switch (buf [0])
    {
    case 'B': case 'b':
      if (!PL_strncasecmp ("BCC", buf, end - buf))
        header = &m_bccList;
      break;
    case 'C': case 'c':
      if (!PL_strncasecmp ("CC", buf, end - buf))
        header = GetNextHeaderInAggregate(m_ccList);
      else if (!PL_strncasecmp ("Content-Type", buf, end - buf))
        header = &m_content_type;
      break;
    case 'D': case 'd':
      if (!PL_strncasecmp ("Date", buf, end - buf))
        header = &m_date;
      else if (!PL_strncasecmp("Disposition-Notification-To", buf, end - buf))
        header = &m_mdn_dnt;
      else if (!PL_strncasecmp("Delivery-date", buf, end - buf))
        header = &m_delivery_date;
      break;
    case 'F': case 'f':
      if (!PL_strncasecmp ("From", buf, end - buf))
        header = &m_from;
      break;
    case 'I' : case 'i':
      if (!PL_strncasecmp ("In-Reply-To", buf, end - buf))
        header = &m_in_reply_to;
      break;
    case 'M': case 'm':
      if (!PL_strncasecmp ("Message-ID", buf, end - buf))
        header = &m_message_id;
      break;
    case 'N': case 'n':
      if (!PL_strncasecmp ("Newsgroups", buf, end - buf))
        header = &m_newsgroups;
      break;
    case 'O': case 'o':
      if (!PL_strncasecmp ("Original-Recipient", buf, end - buf))
        header = &m_mdn_original_recipient;
      break;
    case 'R': case 'r':
      if (!PL_strncasecmp ("References", buf, end - buf))
        header = &m_references;
      else if (!PL_strncasecmp ("Return-Path", buf, end - buf))
        header = &m_return_path;
      // treat conventional Return-Receipt-To as MDN
      // Disposition-Notification-To
      else if (!PL_strncasecmp ("Return-Receipt-To", buf, end - buf))
        header = &m_mdn_dnt;
      else if (!PL_strncasecmp("Reply-To", buf, end - buf))
        header = &m_replyTo;
      else if (!PL_strncasecmp("Received", buf, end - buf))
      {
        header = &receivedBy;
        header->length = 0;
      }
      break;
    case 'S': case 's':
      if (!PL_strncasecmp ("Subject", buf, end - buf))
        header = &m_subject;
      else if (!PL_strncasecmp ("Sender", buf, end - buf))
        header = &m_sender;
      else if (!PL_strncasecmp ("Status", buf, end - buf))
        header = &m_status;
      break;
    case 'T': case 't':
      if (!PL_strncasecmp ("To", buf, end - buf))
        header = GetNextHeaderInAggregate(m_toList);
      break;
    case 'X':
      if (X_MOZILLA_STATUS2_LEN == end - buf &&
        !PL_strncasecmp(X_MOZILLA_STATUS2, buf, end - buf) &&
        !m_IgnoreXMozillaStatus && !m_mozstatus2.length)
        header = &m_mozstatus2;
      else if ( X_MOZILLA_STATUS_LEN == end - buf &&
        !PL_strncasecmp(X_MOZILLA_STATUS, buf, end - buf) && !m_IgnoreXMozillaStatus
        && !m_mozstatus.length)
        header = &m_mozstatus;
      else if (!PL_strncasecmp(HEADER_X_MOZILLA_ACCOUNT_KEY, buf, end - buf)
        && !m_account_key.length)
        header = &m_account_key;
      // we could very well care what the priority header was when we
      // remember its value. If so, need to remember it here. Also,
      // different priority headers can appear in the same message,
      // but we only rememeber the last one that we see.
      else if (!PL_strncasecmp("X-Priority", buf, end - buf)
        || !PL_strncasecmp("Priority", buf, end - buf))
        header = &m_priority;
      else if (!PL_strncasecmp(HEADER_X_MOZILLA_KEYWORDS, buf, end - buf)
        && !m_keywords.length)
        header = &m_keywords;
      break;
    }
    if (!header && m_customDBHeaders.Length())
    {
#ifdef MOZILLA_INTERNAL_API
      nsDependentCSubstring headerStr(buf, end);
#else
      nsDependentCSubstring headerStr(buf, end - buf);
#endif

      ToLowerCase(headerStr);
      PRInt32 customHeaderIndex = m_customDBHeaders.IndexOf(headerStr);
      if (customHeaderIndex != -1)
        header = & m_customDBHeaderValues[customHeaderIndex];
    }

    buf = colon + 1;
    while (*buf == ' ' || *buf == '\t')
      buf++;

    value = buf;
    if (header)
      header->value = value;
    else
    {
    }

SEARCH_NEWLINE:
    while (*buf != 0 && *buf != '\r' && *buf != '\n')
      buf++;

    if (buf+1 >= buf_end)
      ;
    /* If "\r\n " or "\r\n\t" is next, that doesn't terminate the header. */
    else if (buf+2 < buf_end &&
         (buf[0] == '\r'  && buf[1] == '\n') &&
                           (buf[2] == ' ' || buf[2] == '\t'))
    {
      buf += 3;
      goto SEARCH_NEWLINE;
    }
    /* If "\r " or "\r\t" or "\n " or "\n\t" is next, that doesn't terminate
    the header either. */
    else if ((buf[0] == '\r'  || buf[0] == '\n') &&
         (buf[1] == ' ' || buf[1] == '\t'))
    {
      buf += 2;
      goto SEARCH_NEWLINE;
    }

    if (header)
      header->length = buf - header->value;

    if (*buf == '\r' || *buf == '\n')
    {
      char *last = buf;
      if (*buf == '\r' && buf[1] == '\n')
        buf++;
      buf++;
      *last = 0;  /* short-circuit const, and null-terminate header. */
    }

    if (header)
    {
      /* More const short-circuitry... */
      /* strip leading whitespace */
      while (IS_SPACE (*header->value))
        header->value++, header->length--;
      /* strip trailing whitespace */
      while (header->length > 0 &&
        IS_SPACE (header->value [header->length - 1]))
        ((char *) header->value) [--header->length] = 0;
      if (header == &receivedBy && LL_IS_ZERO(m_receivedTime))
      {
        // parse Received: header for date.
        // We trust the first header as that is closest to recipient,
        // and less likely to be spoofed.
        nsCAutoString receivedHdr(header->value, header->length);
        PRInt32 lastSemicolon = receivedHdr.RFindChar(';');
        if (lastSemicolon != -1)
        {
          nsCAutoString receivedDate;
          receivedDate = StringTail(receivedHdr, receivedHdr.Length() - lastSemicolon - 1);
          receivedDate.Trim(" \t\b\r\n");
          PRTime resultTime;
          if (PR_ParseTimeString (receivedDate.get(), PR_FALSE, &resultTime) == PR_SUCCESS)
            m_receivedTime = resultTime;
        }
      }
    }
  }
  return 0;
}

int nsParseMailMessageState::ParseEnvelope (const char *line, PRUint32 line_size)
{
  const char *end;
  char *s;

  m_envelope.AppendBuffer(line, line_size);
  end = m_envelope.GetBuffer() + line_size;
  s = m_envelope.GetBuffer() + 5;

  while (s < end && IS_SPACE (*s))
    s++;
  m_envelope_from.value = s;
  while (s < end && !IS_SPACE (*s))
    s++;
  m_envelope_from.length = s - m_envelope_from.value;

  while (s < end && IS_SPACE (*s))
    s++;
  m_envelope_date.value = s;
  m_envelope_date.length = (PRUint16) (line_size - (s - m_envelope.GetBuffer()));
  while (IS_SPACE (m_envelope_date.value [m_envelope_date.length - 1]))
    m_envelope_date.length--;

  /* #### short-circuit const */
  ((char *) m_envelope_from.value) [m_envelope_from.length] = 0;
  ((char *) m_envelope_date.value) [m_envelope_date.length] = 0;

  return 0;
}

#ifdef WE_CONDENSE_MIME_STRINGS
static char *
msg_condense_mime2_string(char *sourceStr)
{
  char *returnVal = strdup(sourceStr);
  if (!returnVal)
    return nsnull;

  MIME_StripContinuations(returnVal);

  return returnVal;
}
#endif // WE_CONDENSE_MIME_STRINGS

int nsParseMailMessageState::InternSubject (struct message_header *header)
{
  char *key;
  PRUint32 L;

  if (!header || header->length == 0)
  {
    m_newMsgHdr->SetSubject("");
    return 0;
  }

  NS_ASSERTION (header->length == (short) strlen(header->value), "subject corrupt while parsing message");

  key = (char *) header->value;  /* #### const evilness */

  L = header->length;


  PRUint32 flags;
  (void)m_newMsgHdr->GetFlags(&flags);
  /* strip "Re: " */
  /**
        We trust the X-Mozilla-Status line to be the smartest in almost
        all things.  One exception, however, is the HAS_RE flag.  Since
         we just parsed the subject header anyway, we expect that parsing
         to be smartest.  (After all, what if someone just went in and
        edited the subject line by hand?)
     */
  nsCString modifiedSubject;
  if (NS_MsgStripRE((const char **) &key, &L, getter_Copies(modifiedSubject)))
    flags |= nsMsgMessageFlags::HasRe;
  else
    flags &= ~nsMsgMessageFlags::HasRe;
  m_newMsgHdr->SetFlags(flags); // this *does not* update the mozilla-status header in the local folder

  //  if (!*key) return 0; /* To catch a subject of "Re:" */

  // Condense the subject text into as few MIME-2 encoded words as possible.
#ifdef WE_CONDENSE_MIME_STRINGS
  char *condensedKey = msg_condense_mime2_string(modifiedSubject.IsEmpty() ? key : modifiedSubject.get());
#else
  char *condensedKey = nsnull;
#endif
  m_newMsgHdr->SetSubject(condensedKey ? condensedKey :
  (modifiedSubject.IsEmpty() ? key : modifiedSubject.get()));
  PR_FREEIF(condensedKey);

  return 0;
}

// we've reached the end of the envelope, and need to turn all our accumulated message_headers
// into a single nsIMsgDBHdr to store in a database.
int nsParseMailMessageState::FinalizeHeaders()
{
  int status = 0;
  struct message_header *sender;
  struct message_header *recipient;
  struct message_header *subject;
  struct message_header *id;
  struct message_header *inReplyTo;
  struct message_header *replyTo;
  struct message_header *references;
  struct message_header *date;
  struct message_header *deliveryDate;
  struct message_header *statush;
  struct message_header *mozstatus;
  struct message_header *mozstatus2;
  struct message_header *priority;
  struct message_header *keywords;
  struct message_header *account_key;
  struct message_header *ccList;
  struct message_header *bccList;
  struct message_header *mdn_dnt;
  struct message_header md5_header;
  struct message_header *content_type;
  char md5_data [50];

  const char *s;
  PRUint32 flags = 0;
  PRUint32 delta = 0;
  nsMsgPriorityValue priorityFlags = nsMsgPriority::notSet;
  PRUint32 labelFlags = 0;

  if (!m_mailDB)    // if we don't have a valid db, skip the header.
    return 0;

  struct message_header to;
  GetAggregateHeader (m_toList, &to);
  struct message_header cc;
  GetAggregateHeader (m_ccList, &cc);
  // we don't aggregate bcc, as we only generate it locally,
  // and we don't use multiple lines

  sender     = (m_from.length          ? &m_from :
  m_sender.length        ? &m_sender :
  m_envelope_from.length ? &m_envelope_from :
  0);
  recipient  = (to.length         ? &to :
  cc.length         ? &cc :
  m_newsgroups.length ? &m_newsgroups :
  sender);
  ccList     = (cc.length ? &cc : 0);
  bccList    = (m_bccList.length    ? &m_bccList    : 0);
  subject    = (m_subject.length    ? &m_subject    : 0);
  id         = (m_message_id.length ? &m_message_id : 0);
  references = (m_references.length ? &m_references : 0);
  statush    = (m_status.length     ? &m_status     : 0);
  mozstatus  = (m_mozstatus.length  ? &m_mozstatus  : 0);
  mozstatus2 = (m_mozstatus2.length  ? &m_mozstatus2  : 0);
  date       = (m_date.length       ? &m_date :
  m_envelope_date.length ? &m_envelope_date :
  0);
  deliveryDate = (m_delivery_date.length ? &m_delivery_date : 0);
  priority   = (m_priority.length   ? &m_priority   : 0);
  keywords   =  (m_keywords.length   ? &m_keywords  : 0);
  mdn_dnt     = (m_mdn_dnt.length    ? &m_mdn_dnt    : 0);
  inReplyTo = (m_in_reply_to.length ? &m_in_reply_to : 0);
  replyTo = (m_replyTo.length ? &m_replyTo : 0);
  content_type = (m_content_type.length ? &m_content_type : 0);
  account_key = (m_account_key.length ? &m_account_key :0);

  if (mozstatus)
  {
    if (strlen(mozstatus->value) == 4)
    {
      int i;
      for (i=0,s=mozstatus->value ; i<4 ; i++,s++)
      {
        flags = (flags << 4) | msg_UnHex(*s);
      }
      // strip off and remember priority bits.
      flags &= ~nsMsgMessageFlags::RuntimeOnly;
      priorityFlags = (nsMsgPriorityValue) ((flags & nsMsgMessageFlags::Priorities) >> 13);
      flags &= ~nsMsgMessageFlags::Priorities;
    }
    delta = (m_headerstartpos +
      (mozstatus->value - m_headers.GetBuffer()) -
      (2 + X_MOZILLA_STATUS_LEN)    /* 2 extra bytes for ": ". */
      ) - m_envelope_pos;
  }

  if (mozstatus2)
  {
    PRUint32 flags2 = 0;
    sscanf(mozstatus2->value, " %x ", &flags2);
    flags |= flags2;
  }

  if (!(flags & nsMsgMessageFlags::Expunged))  // message was deleted, don't bother creating a hdr.
  {
    // We'll need the message id first to recover data from the backup database
    nsCAutoString rawMsgId;
    /* Take off <> around message ID. */
    if (id)
    {
      if (id->value[0] == '<')
        id->value++, id->length--;
      if (id->value[id->length - 1] == '>')
        /* generate a new null-terminated string without the final > */
        rawMsgId.Assign(id->value, id->length - 1);
      else
        rawMsgId.Assign(id->value);
    }

    /*
     * Try to copy the data from the backup database, referencing the MessageID
     * If that fails, just create a new header
     */
    nsCOMPtr<nsIMsgDBHdr> oldHeader;
    nsresult ret = NS_ERROR_FAILURE;

    if (m_backupMailDB && !rawMsgId.IsEmpty())
      ret = m_backupMailDB->GetMsgHdrForMessageID(
              rawMsgId.get(), getter_AddRefs(oldHeader));

    if (NS_SUCCEEDED(ret) && oldHeader)
        ret = m_mailDB->CopyHdrFromExistingHdr(m_envelope_pos,
                oldHeader, PR_FALSE, getter_AddRefs(m_newMsgHdr));
    else
      ret = m_mailDB->CreateNewHdr(m_envelope_pos, getter_AddRefs(m_newMsgHdr));

    if (NS_SUCCEEDED(ret) && m_newMsgHdr)
    {
      PRUint32 origFlags;
      (void)m_newMsgHdr->GetFlags(&origFlags);
      if (origFlags & nsMsgMessageFlags::HasRe)
        flags |= nsMsgMessageFlags::HasRe;
      else
        flags &= ~nsMsgMessageFlags::HasRe;

      flags &= ~nsMsgMessageFlags::Offline; // don't keep nsMsgMessageFlags::Offline for local msgs
      if (mdn_dnt && !(origFlags & nsMsgMessageFlags::Read) &&
          !(origFlags & nsMsgMessageFlags::MDNReportSent) &&
          !(flags & nsMsgMessageFlags::MDNReportSent))
        flags |= nsMsgMessageFlags::MDNReportNeeded;

      m_newMsgHdr->SetFlags(flags);
      if (priorityFlags != nsMsgPriority::notSet)
        m_newMsgHdr->SetPriority(priorityFlags);

      // if we have a reply to header, and it's different from the from: header,
      // set the "replyTo" attribute on the msg hdr.
      if (replyTo && (!sender || replyTo->length != sender->length || strncmp(replyTo->value, sender->value, sender->length)))
        m_newMsgHdr->SetStringProperty("replyTo", replyTo->value);
      // convert the flag values (0xE000000) to label values (0-5)
      if (mozstatus2) // only do this if we have a mozstatus2 header
      {
        labelFlags = ((flags & nsMsgMessageFlags::Labels) >> 25);
        m_newMsgHdr->SetLabel(labelFlags);
      }
      if (delta < 0xffff)
      {    /* Only use if fits in 16 bits. */
        m_newMsgHdr->SetStatusOffset((PRUint16) delta);
        if (!m_IgnoreXMozillaStatus) {  // imap doesn't care about X-MozillaStatus
          PRUint32 offset;
          (void)m_newMsgHdr->GetStatusOffset(&offset);
          NS_ASSERTION(offset < 10000, "invalid status offset"); /* ### Debugging hack */
        }
      }
      if (sender)
        m_newMsgHdr->SetAuthor(sender->value);
      if (recipient == &m_newsgroups)
      {
      /* In the case where the recipient is a newsgroup, truncate the string
      at the first comma.  This is used only for presenting the thread list,
      and newsgroup lines tend to be long and non-shared, and tend to bloat
      the string table.  So, by only showing the first newsgroup, we can
      reduce memory and file usage at the expense of only showing the one
      group in the summary list, and only being able to sort on the first
        group rather than the whole list.  It's worth it. */
        char * ch;
        NS_ASSERTION (recipient->length == (PRUint16) strlen(recipient->value), "invalid recipient");
        ch = PL_strchr(recipient->value, ',');
        if (ch)
        {
          /* generate a new string that terminates before the , */
          nsCAutoString firstGroup;
          firstGroup.Assign(recipient->value, ch - recipient->value);
          m_newMsgHdr->SetRecipients(firstGroup.get());
        }
        m_newMsgHdr->SetRecipients(recipient->value);
      }
      else if (recipient)
      {
        // note that we're now setting the whole recipient list,
        // not just the pretty name of the first recipient.
        PRUint32 numAddresses;
        char  *names;
        char  *addresses;

        ret = m_HeaderAddressParser->ParseHeaderAddresses(recipient->value,
                                                          &names, &addresses,
                                                          &numAddresses);
        if (ret == NS_OK)
        {
          m_newMsgHdr->SetRecipientsArray(names, addresses, numAddresses);
          PR_Free(addresses);
          PR_Free(names);
        }
        else {  // hmm, should we just use the original string?
          m_newMsgHdr->SetRecipients(recipient->value);
        }
      }
      if (ccList)
      {
        PRUint32 numAddresses;
        char  *names;
        char  *addresses;

        ret = m_HeaderAddressParser->ParseHeaderAddresses(ccList->value,
                                                          &names, &addresses,
                                                          &numAddresses);
        if (ret == NS_OK)
        {
          m_newMsgHdr->SetCCListArray(names, addresses, numAddresses);
          PR_Free(addresses);
          PR_Free(names);
        }
        else  // hmm, should we just use the original string?
          m_newMsgHdr->SetCcList(ccList->value);
      }

      if (bccList)
      {
        PRUint32 numAddresses;
        char  *names;
        char  *addresses;

        ret = m_HeaderAddressParser->ParseHeaderAddresses(bccList->value,
                                                          &names, &addresses,
                                                          &numAddresses);
        if (NS_SUCCEEDED(ret))
        {
          m_newMsgHdr->SetBCCListArray(names, addresses, numAddresses);
          PR_Free(addresses);
          PR_Free(names);
        }
        else  // hmm, should we just use the original string?
          m_newMsgHdr->SetBccList(bccList->value);
      }

      status = InternSubject (subject);
      if (status >= 0)
      {
        if (! id)
        {
          // what to do about this? we used to do a hash of all the headers...
          nsCAutoString hash;
          const char *md5_b64 = "dummy.message.id";
          nsresult rv;
          nsCOMPtr<nsICryptoHash> hasher = do_CreateInstance("@mozilla.org/security/hash;1", &rv);
          if (NS_SUCCEEDED(rv))
          {
            if (NS_SUCCEEDED(hasher->Init(nsICryptoHash::MD5)) &&
                NS_SUCCEEDED(hasher->Update((const PRUint8*) m_headers.GetBuffer(), m_headers.GetSize())) &&
                NS_SUCCEEDED(hasher->Finish(PR_TRUE, hash)))
              md5_b64 = hash.get();
          }
          PR_snprintf (md5_data, sizeof(md5_data), "<md5:%s>", md5_b64);
          md5_header.value = md5_data;
          md5_header.length = strlen(md5_data);
          id = &md5_header;
        }

        if (!rawMsgId.IsEmpty())
          m_newMsgHdr->SetMessageId(rawMsgId.get());
        else
          m_newMsgHdr->SetMessageId(id->value);

        if (!mozstatus && statush)
        {
          /* Parse a little bit of the Berkeley Mail status header. */
          for (s = statush->value; *s; s++) {
            PRUint32 msgFlags = 0;
            (void)m_newMsgHdr->GetFlags(&msgFlags);
            switch (*s)
            {
            case 'R': case 'r':
              m_newMsgHdr->SetFlags(msgFlags | nsMsgMessageFlags::Read);
              break;
            case 'D': case 'd':
              /* msg->flags |= nsMsgMessageFlags::Expunged;  ### Is this reasonable? */
              break;
            case 'N': case 'n':
            case 'U': case 'u':
              m_newMsgHdr->SetFlags(msgFlags & ~nsMsgMessageFlags::Read);
              break;
            }
          }
        }

        if (account_key != nsnull)
          m_newMsgHdr->SetAccountKey(account_key->value);
        // use in-reply-to header as references, if there's no references header
        if (references != nsnull)
          m_newMsgHdr->SetReferences(references->value);
        else if (inReplyTo != nsnull)
          m_newMsgHdr->SetReferences(inReplyTo->value);

        // 'Received' should be as reliable an indicator of the receipt
        // date+time as possible, whilst always giving something *from
        // the message*.  It won't use PR_Now() under any circumstance.
        // Therefore, the fall-thru order for 'Received' is:
        // Received: -> Delivery-date: -> date
        // 'Date' uses:
        // date -> PR_Now()
        //
        // date is:
        // Date: -> m_envelope_date

        PRUint32 rcvTimeSecs = 0;
        if (date)
        {  // Date:
          PRTime resultTime;
          PRStatus timeStatus = PR_ParseTimeString (date->value, PR_FALSE, &resultTime);
          if (PR_SUCCESS == timeStatus)
          {
            m_newMsgHdr->SetDate(resultTime);
            PRTime2Seconds(resultTime, &rcvTimeSecs);
          }
        }
        else
        {  // PR_Now()
          // If there was some problem parsing the Date header *AND* we
          // couldn't get a valid envelope date, use now as the time.
          // PR_ParseTimeString won't touch resultTime unless it succeeds.
          // This doesn't affect local (POP3) messages, because we use the envelope
          // date if there's no Date: header, but it will affect IMAP msgs
          // w/o a Date: hdr or Received: headers.
          PRTime resultTime = PR_Now();
          m_newMsgHdr->SetDate(resultTime);
        }
        if (!LL_IS_ZERO(m_receivedTime))
        {  // Upgrade 'Received' to Received: ?
          PRTime2Seconds(m_receivedTime, &rcvTimeSecs);
        }
        else if (deliveryDate)
        {  // Upgrade 'Received' to Delivery-date: ?
          PRTime resultTime;
          PRStatus timeStatus = PR_ParseTimeString (deliveryDate->value, PR_FALSE, &resultTime);
          if (PR_SUCCESS == timeStatus)
            PRTime2Seconds(resultTime, &rcvTimeSecs);
        }
        m_newMsgHdr->SetUint32Property("dateReceived", rcvTimeSecs);

        if (priority)
          m_newMsgHdr->SetPriorityString(priority->value);
        else if (priorityFlags == nsMsgPriority::notSet)
          m_newMsgHdr->SetPriority(nsMsgPriority::none);
        if (keywords)
        {
          // When there are many keywords, some may not have been written
          // to the message file, so add extra keywords from the backup
          nsCAutoString oldKeywords;
          m_newMsgHdr->GetStringProperty("keywords", getter_Copies(oldKeywords));
          nsTArray<nsCString> newKeywordArray, oldKeywordArray;
          ParseString(Substring(keywords->value, keywords->value + keywords->length), ' ', newKeywordArray);
          ParseString(oldKeywords, ' ', oldKeywordArray);
          for (PRUint32 i = 0; i < oldKeywordArray.Length(); i++)
            if (!newKeywordArray.Contains(oldKeywordArray[i]))
              newKeywordArray.AppendElement(oldKeywordArray[i]);
          nsCAutoString newKeywords;
          for (PRUint32 i = 0; i < newKeywordArray.Length(); i++)
          {
            if (i)
              newKeywords.Append(" ");
            newKeywords.Append(newKeywordArray[i]);
          }
          m_newMsgHdr->SetStringProperty("keywords", newKeywords.get());
        }
        for (PRUint32 i = 0; i < m_customDBHeaders.Length(); i++)
        {
          if (m_customDBHeaderValues[i].length)
            m_newMsgHdr->SetStringProperty(m_customDBHeaders[i].get(), m_customDBHeaderValues[i].value);
        }
        if (content_type)
        {
          char *substring = PL_strstr(content_type->value, "charset");
          if (substring)
          {
            char *charset = PL_strchr (substring, '=');
            if (charset)
            {
              charset++;
              /* strip leading whitespace and double-quote */
              while (*charset && (IS_SPACE (*charset) || '\"' == *charset))
                charset++;
              /* strip trailing whitespace and double-quote */
              char *end = charset;
              while (*end && !IS_SPACE (*end) && '\"' != *end && ';' != *end)
                end++;
              if (*charset)
              {
                if (*end != '\0') {
                  // if we're not at the very end of the line, we need
                  // to generate a new string without the trailing crud
                  nsCAutoString rawCharSet;
                  rawCharSet.Assign(charset, end - charset);
                  m_newMsgHdr->SetCharset(rawCharSet.get());
                } else {
                  m_newMsgHdr->SetCharset(charset);
                }
              }
            }
          }
          substring = PL_strcasestr(content_type->value, "multipart/mixed");
          if (substring)
          {
            PRUint32 newFlags;
            m_newMsgHdr->OrFlags(nsMsgMessageFlags::Attachment, &newFlags);
          }
        }
      }
    }
    else
    {
      NS_ASSERTION(PR_FALSE, "error creating message header");
      status = NS_ERROR_OUT_OF_MEMORY;
    }
  }
  else
    status = 0;

  //### why is this stuff const?
  char *tmp = (char*) to.value;
  PR_Free(tmp);
  tmp = (char*) cc.value;
  PR_Free(tmp);

  return status;
}

nsParseNewMailState::nsParseNewMailState()
    : m_disableFilters(PR_FALSE)
{
  m_inboxFileStream = nsnull;
  m_ibuffer = nsnull;
  m_ibuffer_size = 0;
  m_ibuffer_fp = 0;
  m_numNotNewMessages = 0;
 }

NS_IMPL_ISUPPORTS_INHERITED1(nsParseNewMailState, nsMsgMailboxParser, nsIMsgFilterHitNotify)

nsresult
nsParseNewMailState::Init(nsIMsgFolder *serverFolder, nsIMsgFolder *downloadFolder, nsILocalFile *folder,
                          nsIInputStream *inboxFileStream, nsIMsgWindow *aMsgWindow,
                          PRBool downloadingToTempFile)
{
  nsresult rv;
  PRInt64 folderSize;
  folder->GetFileSize(&folderSize);
  m_position = folderSize;
  m_rootFolder = serverFolder;
  m_inboxFile = folder;
  m_inboxFileStream = inboxFileStream;
  m_msgWindow = aMsgWindow;
  m_downloadFolder = downloadFolder;
  m_downloadingToTempFile = downloadingToTempFile;

  // the new mail parser isn't going to get the stream input, it seems, so we can't use
  // the OnStartRequest mechanism the mailbox parser uses. So, let's open the db right now.
  nsCOMPtr<nsIMsgDBService> msgDBService = do_GetService(NS_MSGDB_SERVICE_CONTRACTID, &rv);
  if (msgDBService)
    rv = msgDBService->OpenFolderDB(downloadFolder, PR_FALSE,
                                    getter_AddRefs(m_mailDB));
  NS_ENSURE_SUCCESS(rv, rv);
  nsCOMPtr <nsIMsgFolder> rootMsgFolder = do_QueryInterface(serverFolder, &rv);
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIMsgIncomingServer> server;
  rv = rootMsgFolder->GetServer(getter_AddRefs(server));
  if (NS_SUCCEEDED(rv))
  {
    rv = server->GetFilterList(aMsgWindow, getter_AddRefs(m_filterList));

    if (m_filterList)
    {
      rv = server->ConfigureTemporaryFilters(m_filterList);
    }
    // check if this server defers to another server, in which case
    // we'll use that server's filters as well.
    nsCOMPtr <nsIMsgFolder> deferredToRootFolder;
    server->GetRootMsgFolder(getter_AddRefs(deferredToRootFolder));
    if (rootMsgFolder != deferredToRootFolder)
    {
      nsCOMPtr <nsIMsgIncomingServer> deferredToServer;
      deferredToRootFolder->GetServer(getter_AddRefs(deferredToServer));
      if (deferredToServer)
        deferredToServer->GetFilterList(aMsgWindow, getter_AddRefs(m_deferredToServerFilterList));
    }
  }
  m_disableFilters = PR_FALSE;
  return NS_OK;
}

nsParseNewMailState::~nsParseNewMailState()
{
  if (m_mailDB)
    m_mailDB->Close(PR_TRUE);
  if (m_backupMailDB)
    m_backupMailDB->ForceClosed();
#ifdef DOING_JSFILTERS
  JSFilter_cleanup();
#endif
}

// not an IMETHOD so we don't need to do error checking or return an error.
// We only have one caller.
void nsParseNewMailState::GetMsgWindow(nsIMsgWindow **aMsgWindow)
{
  NS_IF_ADDREF(*aMsgWindow = m_msgWindow);
}


// This gets called for every message because libnet calls IncorporateBegin,
// IncorporateWrite (once or more), and IncorporateComplete for every message.
void nsParseNewMailState::DoneParsingFolder(nsresult status)
{
  /* End of file.  Flush out any partial line remaining in the buffer. */
  if (m_ibuffer_fp > 0)
  {
    ParseFolderLine(m_ibuffer, m_ibuffer_fp);
    m_ibuffer_fp = 0;
  }
  PublishMsgHeader(nsnull);
  if (m_mailDB)  // finished parsing, so flush db folder info
    UpdateDBFolderInfo();

    /* We're done reading the folder - we don't need these things
   any more. */
  PR_FREEIF (m_ibuffer);
  m_ibuffer_size = 0;
  PR_FREEIF (m_obuffer);
  m_obuffer_size = 0;
}

PRInt32 nsParseNewMailState::PublishMsgHeader(nsIMsgWindow *msgWindow)
{
  PRBool moved = PR_FALSE;
  FinishHeader();

  if (m_newMsgHdr)
  {
    PRUint32 newFlags, oldFlags;
    m_newMsgHdr->GetFlags(&oldFlags);
    if (!(oldFlags & nsMsgMessageFlags::Read)) // don't mark read messages as new.
      m_newMsgHdr->OrFlags(nsMsgMessageFlags::New, &newFlags);

    if (!m_disableFilters)
    {
      // seems like the code that's writing to disk should do
      // the flushing...
      // flush the inbox because filters will read from disk
      // m_inboxFileStream->Flush();
      PRUint32 msgOffset;
      (void) m_newMsgHdr->GetMessageOffset(&msgOffset);
      m_curHdrOffset = msgOffset;

      nsCOMPtr<nsIMsgIncomingServer> server;
      nsresult rv = m_rootFolder->GetServer(getter_AddRefs(server));
      NS_ENSURE_SUCCESS(rv, 0);
      PRInt32 duplicateAction;
      server->GetIncomingDuplicateAction(&duplicateAction);
      if (duplicateAction != nsIMsgIncomingServer::keepDups)
      {
        PRBool isDup;
        server->IsNewHdrDuplicate(m_newMsgHdr, &isDup);
        if (isDup)
        {
          // we want to do something similar to applying filter hits.
          // if a dup is marked read, it shouldn't trigger biff.
          // Same for deleting it or moving it to trash.
          switch (duplicateAction)
          {
            case nsIMsgIncomingServer::deleteDups:
              {
                m_inboxFileStream->Close();

                nsresult truncRet = m_inboxFile->SetFileSize(msgOffset);
                NS_ASSERTION(NS_SUCCEEDED(truncRet), "unable to truncate file");
                if (NS_FAILED(truncRet))
                  m_rootFolder->ThrowAlertMsg("dupDeleteFolderTruncateFailed", msgWindow);

                MsgReopenFileStream(m_inboxFile, m_inboxFileStream);

                nsCOMPtr <nsISeekableStream> seekableStream = do_QueryInterface(m_inboxFileStream);
                if (seekableStream)
                  seekableStream->Seek(nsISeekableStream::NS_SEEK_END, 0);

                m_mailDB->RemoveHeaderMdbRow(m_newMsgHdr);
                // tell parser we've truncated the inbox.
                nsParseMailMessageState::Init(msgOffset);

              }
              break;
            case nsIMsgIncomingServer::moveDupsToTrash:
              {
                nsCOMPtr <nsIMsgFolder> trash;
                GetTrashFolder(getter_AddRefs(trash));
                if (trash)
                {
                  PRUint32 newFlags;
                  m_newMsgHdr->AndFlags(~nsMsgMessageFlags::New, &newFlags);
                  // save off m_newMsgHdr because MoveIncorporatedMessage 
                  // clears it by calling nsParseMailMessageState::Init
                  nsCOMPtr<nsIMsgDBHdr> msgHdr = m_newMsgHdr;
                  MoveIncorporatedMessage(m_newMsgHdr, m_mailDB, trash,
                                                          nsnull, msgWindow);
                  if (!m_downloadingToTempFile)
                    m_mailDB->RemoveHeaderMdbRow(msgHdr);
                }
              }
              break;
            case nsIMsgIncomingServer::markDupsRead:
              MarkFilteredMessageRead(m_newMsgHdr);
              break;
          }
          PRInt32 numNewMessages;
          m_downloadFolder->GetNumNewMessages(PR_FALSE, &numNewMessages);
          m_downloadFolder->SetNumNewMessages(numNewMessages - 1);

          m_newMsgHdr = nsnull;
          return 0;
        }
      }

      ApplyFilters(&moved, msgWindow, msgOffset);
    }
    if (!moved)
    {
      if (m_mailDB)
      {
        m_mailDB->AddNewHdrToDB(m_newMsgHdr, PR_TRUE);
        nsCOMPtr<nsIMsgFolderNotificationService> notifier(do_GetService(NS_MSGNOTIFICATIONSERVICE_CONTRACTID));
        if (notifier)
          notifier->NotifyMsgAdded(m_newMsgHdr);
        // mark the header as not yet reported classified
        nsMsgKey msgKey;
        m_newMsgHdr->GetMessageKey(&msgKey);
        m_downloadFolder->OrProcessingFlags(
           msgKey, nsMsgProcessingFlags::NotReportedClassified);
      }
    } // if it was moved by imap filter, m_parseMsgState->m_newMsgHdr == nsnull
    m_newMsgHdr = nsnull;
  }
  return 0;
}

nsresult nsParseNewMailState::GetTrashFolder(nsIMsgFolder **pTrashFolder)
{
  nsresult rv=NS_ERROR_UNEXPECTED;
  if (!pTrashFolder)
    return NS_ERROR_NULL_POINTER;

  if(m_downloadFolder)
  {
    nsCOMPtr <nsIMsgIncomingServer> incomingServer;
    m_downloadFolder->GetServer(getter_AddRefs(incomingServer));
    nsCOMPtr <nsIMsgFolder> rootMsgFolder;
    incomingServer->GetRootMsgFolder(getter_AddRefs(rootMsgFolder));
    if (rootMsgFolder)
    {
      rv = rootMsgFolder->GetFolderWithFlags(nsMsgFolderFlags::Trash, pTrashFolder);
      if (!*pTrashFolder)
        rv = NS_ERROR_FAILURE;
    }
  }
  return rv;
}

void nsParseNewMailState::ApplyFilters(PRBool *pMoved, nsIMsgWindow *msgWindow, PRUint32 msgOffset)
{
  m_msgMovedByFilter = m_msgCopiedByFilter = PR_FALSE;
  m_curHdrOffset = msgOffset;

  if (!m_disableFilters)
  {
    nsCOMPtr<nsIMsgDBHdr> msgHdr = m_newMsgHdr;
    nsCOMPtr<nsIMsgFolder> downloadFolder = m_downloadFolder;
    nsCOMPtr <nsIMsgFolder> rootMsgFolder = do_QueryInterface(m_rootFolder);
    if (rootMsgFolder)
    {
      if (!downloadFolder)
        rootMsgFolder->GetFolderWithFlags(nsMsgFolderFlags::Inbox,
                                          getter_AddRefs(downloadFolder));
      if (downloadFolder)
        downloadFolder->GetURI(m_inboxUri);
      char * headers = m_headers.GetBuffer();
      PRUint32 headersSize = m_headers.GetBufferPos();
      nsresult matchTermStatus;
      if (m_filterList)
        matchTermStatus = m_filterList->ApplyFiltersToHdr(nsMsgFilterType::InboxRule,
                    msgHdr, downloadFolder, m_mailDB, headers, headersSize, this, msgWindow, m_inboxFile);
      if (!m_msgMovedByFilter && m_deferredToServerFilterList)
      {
        matchTermStatus = m_deferredToServerFilterList->ApplyFiltersToHdr(nsMsgFilterType::InboxRule,
                    msgHdr, downloadFolder, m_mailDB, headers, headersSize, this, msgWindow, m_inboxFile);
      }
    }
  }
  if (pMoved)
    *pMoved = m_msgMovedByFilter;
}

NS_IMETHODIMP nsParseNewMailState::ApplyFilterHit(nsIMsgFilter *filter, nsIMsgWindow *msgWindow, PRBool *applyMore)
{
  NS_ENSURE_ARG_POINTER(applyMore);

  nsMsgRuleActionType actionType;
  nsCString actionTargetFolderUri;
  PRUint32 newFlags;
  nsresult rv = NS_OK;

  *applyMore = PR_TRUE;

  nsCOMPtr<nsIMsgDBHdr> msgHdr = m_newMsgHdr;

  nsCOMPtr<nsISupportsArray> filterActionList;
  rv = NS_NewISupportsArray(getter_AddRefs(filterActionList));
  NS_ENSURE_SUCCESS(rv, rv);
  rv = filter->GetSortedActionList(filterActionList);
  NS_ENSURE_SUCCESS(rv, rv);

  PRUint32 numActions;
  rv = filterActionList->Count(&numActions);
  NS_ENSURE_SUCCESS(rv, rv);

  PRBool loggingEnabled = PR_FALSE;
  if (m_filterList && numActions)
    m_filterList->GetLoggingEnabled(&loggingEnabled);

  PRBool msgIsNew = PR_TRUE;
  for (PRUint32 actionIndex =0; actionIndex < numActions && *applyMore; actionIndex++)
  {
    nsCOMPtr<nsIMsgRuleAction> filterAction;
    filterActionList->QueryElementAt(actionIndex, NS_GET_IID(nsIMsgRuleAction), getter_AddRefs(filterAction));
    if (!filterAction)
      continue;

    if (NS_SUCCEEDED(filterAction->GetType(&actionType)))
    {
      if (actionType == nsMsgFilterAction::MoveToFolder ||
          actionType == nsMsgFilterAction::CopyToFolder)
      {
        filterAction->GetTargetFolderUri(actionTargetFolderUri);
        if (actionTargetFolderUri.IsEmpty())
        {
          NS_ASSERTION(PR_FALSE, "actionTargetFolderUri is empty");
          continue;
        }
      }
      switch (actionType)
      {
      case nsMsgFilterAction::Delete:
        {
          nsCOMPtr <nsIMsgFolder> trash;
          // set value to trash folder
          rv = GetTrashFolder(getter_AddRefs(trash));
          if (NS_SUCCEEDED(rv) && trash)
            rv = trash->GetURI(actionTargetFolderUri);

          msgHdr->OrFlags(nsMsgMessageFlags::Read, &newFlags); // mark read in trash.
          msgIsNew = PR_FALSE;
        }
      case nsMsgFilterAction::MoveToFolder:
        // if moving to a different file, do it.
#ifdef MOZILLA_INTERNAL_API
        if (actionTargetFolderUri.get() && !m_inboxUri.Equals(actionTargetFolderUri,
                                                              nsCaseInsensitiveCStringComparator()))
#else
        if (actionTargetFolderUri.get() && !m_inboxUri.Equals(actionTargetFolderUri,
                                                              CaseInsensitiveCompare))
#endif
        {
          nsresult err;
          nsCOMPtr<nsIRDFService> rdf(do_GetService(kRDFServiceCID, &err));
          NS_ENSURE_SUCCESS(err, err);
          nsCOMPtr<nsIRDFResource> res;
          err = rdf->GetResource(actionTargetFolderUri, getter_AddRefs(res));
          if (NS_FAILED(err))
            return err;

          nsCOMPtr<nsIMsgFolder> destIFolder(do_QueryInterface(res, &err));
          if (NS_FAILED(err))
            return err;

          // if we're moving to an imap folder, or this message has already 
          // has a pending copy action, use the imap coalescer so that
          // we won't truncate the inbox before the copy fires.
          if (m_msgCopiedByFilter ||
              StringBeginsWith(actionTargetFolderUri, NS_LITERAL_CSTRING("imap:")))
          {
            if (!m_moveCoalescer)
              m_moveCoalescer = new nsImapMoveCoalescer(m_downloadFolder, m_msgWindow);
            NS_ENSURE_TRUE(m_moveCoalescer, NS_ERROR_OUT_OF_MEMORY);
            nsMsgKey msgKey;
            (void) msgHdr->GetMessageKey(&msgKey);
            m_moveCoalescer->AddMove(destIFolder , msgKey);
            if (loggingEnabled)
              (void)filter->LogRuleHit(filterAction, msgHdr);
            err = NS_OK;
            msgIsNew = PR_FALSE;
          }
          else
          {
            err = MoveIncorporatedMessage(msgHdr, m_mailDB, destIFolder, filter, msgWindow);
            m_msgMovedByFilter = NS_SUCCEEDED(err);
            if (m_msgMovedByFilter)
            {
              if (loggingEnabled)
                (void)filter->LogRuleHit(filterAction, msgHdr);
              // if we're downloading to a temp file, our message key is wrong,
              // i.e., relative to the temp file and not the original mailbox,
              // and we need to let nsPop3Sink remove the message hdr after
              // it fixes the key.
              if (!m_downloadingToTempFile)
                m_mailDB->RemoveHeaderMdbRow(msgHdr);
            }
          }
        }
        *applyMore = PR_FALSE;
        break;
        case nsMsgFilterAction::CopyToFolder:
        {
          nsCString uri;
          rv = m_rootFolder->GetURI(uri);

          if (!actionTargetFolderUri.IsEmpty() && !actionTargetFolderUri.Equals(uri))
          {
            nsCOMPtr<nsIMutableArray> messageArray(do_CreateInstance(NS_ARRAY_CONTRACTID));
            messageArray->AppendElement(msgHdr, PR_FALSE);

            nsCOMPtr<nsIMsgFolder> dstFolder;
            rv = GetExistingFolder(actionTargetFolderUri,
                                   getter_AddRefs(dstFolder));
            NS_ENSURE_SUCCESS(rv, rv);

            nsCOMPtr<nsIMsgCopyService> copyService =
              do_GetService(NS_MSGCOPYSERVICE_CONTRACTID, &rv);
            NS_ENSURE_SUCCESS(rv, rv);
            rv = copyService->CopyMessages(m_downloadFolder, messageArray, dstFolder,
                                           PR_FALSE, nsnull, msgWindow, PR_FALSE);
            NS_ENSURE_SUCCESS(rv, rv);
            m_msgCopiedByFilter = PR_TRUE;
          }
        }
        break;
      case nsMsgFilterAction::MarkRead:
        msgIsNew = PR_FALSE;
        MarkFilteredMessageRead(msgHdr);
        break;
      case nsMsgFilterAction::KillThread:
        msgHdr->SetUint32Property("ProtoThreadFlags", nsMsgMessageFlags::Ignored);
        break;
      case nsMsgFilterAction::KillSubthread:
        msgHdr->OrFlags(nsMsgMessageFlags::Ignored, &newFlags);
        break;
      case nsMsgFilterAction::WatchThread:
        msgHdr->OrFlags(nsMsgMessageFlags::Watched, &newFlags);
        break;
      case nsMsgFilterAction::MarkFlagged:
        msgHdr->MarkFlagged(PR_TRUE);
        break;
      case nsMsgFilterAction::ChangePriority:
        nsMsgPriorityValue filterPriority;
        filterAction->GetPriority(&filterPriority);
        msgHdr->SetPriority(filterPriority);
        break;
      case nsMsgFilterAction::AddTag:
      {
        nsCString keyword;
        filterAction->GetStrValue(keyword);
        nsCOMPtr<nsIMutableArray> messageArray(do_CreateInstance(NS_ARRAY_CONTRACTID));
        messageArray->AppendElement(msgHdr, PR_FALSE);
        m_downloadFolder->AddKeywordsToMessages(messageArray, keyword);
        break;
      }
      case nsMsgFilterAction::Label:
        nsMsgLabelValue filterLabel;
        filterAction->GetLabel(&filterLabel);
        nsMsgKey msgKey;
        msgHdr->GetMessageKey(&msgKey);
        m_mailDB->SetLabel(msgKey, filterLabel);
        break;
      case nsMsgFilterAction::JunkScore:
      {
        nsCAutoString junkScoreStr;
        PRInt32 junkScore;
        filterAction->GetJunkScore(&junkScore);
        junkScoreStr.AppendInt(junkScore);
        if (junkScore == nsIJunkMailPlugin::IS_SPAM_SCORE)
          msgIsNew = PR_FALSE;
        nsMsgKey msgKey;
        msgHdr->GetMessageKey(&msgKey);
        msgHdr->SetStringProperty("junkscore", junkScoreStr.get());
        msgHdr->SetStringProperty("junkscoreorigin", "filter");
        break;
      }
      case nsMsgFilterAction::Forward:
        {
          nsCString forwardTo;
          filterAction->GetStrValue(forwardTo);
          m_forwardTo.AppendCString(forwardTo);
          m_msgToForwardOrReply = msgHdr;
        }
        break;
      case nsMsgFilterAction::Reply:
        {
          nsCString replyTemplateUri;
          filterAction->GetStrValue(replyTemplateUri);
          m_replyTemplateUri.AppendCString(replyTemplateUri);
          m_msgToForwardOrReply = msgHdr;
        }
        break;
      case nsMsgFilterAction::DeleteFromPop3Server:
        {
          PRUint32 flags = 0;
          nsCOMPtr <nsIMsgFolder> downloadFolder;
          msgHdr->GetFolder(getter_AddRefs(downloadFolder));
          nsCOMPtr <nsIMsgLocalMailFolder> localFolder = do_QueryInterface(downloadFolder);
          msgHdr->GetFlags(&flags);
          if (localFolder)
          {
            nsCOMPtr<nsIMutableArray> messages = do_CreateInstance(NS_ARRAY_CONTRACTID, &rv);
            NS_ENSURE_SUCCESS(rv, rv);
            messages->AppendElement(msgHdr, PR_FALSE);
            // This action ignores the deleteMailLeftOnServer preference
            localFolder->MarkMsgsOnPop3Server(messages, POP3_FORCE_DEL);

            // If this is just a header, throw it away. It's useless now
            // that the server copy is being deleted.
            if (flags & nsMsgMessageFlags::Partial)
            {
              m_msgMovedByFilter = PR_TRUE;
              msgIsNew = PR_FALSE;
            }
          }
        }
        break;
      case nsMsgFilterAction::FetchBodyFromPop3Server:
        {
          PRUint32 flags = 0;
          nsCOMPtr <nsIMsgFolder> downloadFolder;
          msgHdr->GetFolder(getter_AddRefs(downloadFolder));
          nsCOMPtr <nsIMsgLocalMailFolder> localFolder = do_QueryInterface(downloadFolder);
          msgHdr->GetFlags(&flags);
          if (localFolder && (flags & nsMsgMessageFlags::Partial))
          {
            nsCOMPtr<nsIMutableArray> messages = do_CreateInstance(NS_ARRAY_CONTRACTID, &rv);
            NS_ENSURE_SUCCESS(rv, rv);
            messages->AppendElement(msgHdr, PR_FALSE);
            localFolder->MarkMsgsOnPop3Server(messages, POP3_FETCH_BODY);
            // Don't add this header to the DB, we're going to replace it
            // with the full message.
            m_msgMovedByFilter = PR_TRUE;
            msgIsNew = PR_FALSE;
            // Don't do anything else in this filter, wait until we
            // have the full message.
            *applyMore = PR_FALSE;
          }
        }
        break;

      case nsMsgFilterAction::StopExecution:
      {
        // don't apply any more filters
        *applyMore = PR_FALSE;
      }
      break;

      case nsMsgFilterAction::Custom:
      {
        nsCOMPtr<nsIMsgFilterCustomAction> customAction;
        rv = filterAction->GetCustomAction(getter_AddRefs(customAction));
        NS_ENSURE_SUCCESS(rv, rv);

        nsCAutoString value;
        filterAction->GetStrValue(value);

        nsCOMPtr<nsIMutableArray> messageArray(
            do_CreateInstance(NS_ARRAY_CONTRACTID, &rv));
        NS_ENSURE_TRUE(messageArray, rv);
        messageArray->AppendElement(msgHdr, PR_FALSE);

        customAction->Apply(messageArray, value, nsnull,
                            nsMsgFilterType::InboxRule, msgWindow);
      }
      break;


      default:
        break;
      }
      if (loggingEnabled && actionType != nsMsgFilterAction::MoveToFolder && actionType != nsMsgFilterAction::Delete)
        (void)filter->LogRuleHit(filterAction, msgHdr);
    }
  }
  if (!msgIsNew)
  {
    PRInt32 numNewMessages;
    m_downloadFolder->GetNumNewMessages(PR_FALSE, &numNewMessages);
    if (numNewMessages > 0)
      m_downloadFolder->SetNumNewMessages(numNewMessages - 1);
    m_numNotNewMessages++;
  }
  return rv;
}

// this gets run in a second pass, after apply filters to a header.
nsresult nsParseNewMailState::ApplyForwardAndReplyFilter(nsIMsgWindow *msgWindow)
{
  nsresult rv = NS_OK;
  nsCOMPtr <nsIMsgIncomingServer> server;

  PRInt32 i;
  for (i = 0; i < m_forwardTo.Count(); i++)
  {
    if (!m_forwardTo[i]->IsEmpty())
    {
      nsAutoString forwardStr;
      CopyASCIItoUTF16(*(m_forwardTo[i]), forwardStr);
      rv = m_rootFolder->GetServer(getter_AddRefs(server));
      NS_ENSURE_SUCCESS(rv, rv);
      {
        nsCOMPtr <nsIMsgComposeService> compService = do_GetService (NS_MSGCOMPOSESERVICE_CONTRACTID) ;
        if (compService)
          rv = compService->ForwardMessage(forwardStr, m_msgToForwardOrReply, msgWindow, server);
      }
    }
  }
  m_forwardTo.Clear();

  for (i = 0; i < m_replyTemplateUri.Count(); i++)
  {
    if (!m_replyTemplateUri[i]->IsEmpty())
    {
      // copy this and truncate the original, so we don't accidentally re-use it on the next hdr.
      nsCAutoString replyTemplateUri(*m_replyTemplateUri[i]);
      rv = m_rootFolder->GetServer(getter_AddRefs(server));
      if (server && !replyTemplateUri.IsEmpty())
      {
        nsCOMPtr <nsIMsgComposeService> compService = do_GetService (NS_MSGCOMPOSESERVICE_CONTRACTID) ;
        if (compService)
          rv = compService->ReplyWithTemplate(m_msgToForwardOrReply, replyTemplateUri.get(), msgWindow, server);
      }
    }
  }
  m_replyTemplateUri.Clear();
  m_msgToForwardOrReply = nsnull;
  return rv;
}


int nsParseNewMailState::MarkFilteredMessageRead(nsIMsgDBHdr *msgHdr)
{
  PRUint32 newFlags;
  if (m_mailDB)
  {
    m_mailDB->MarkHdrRead(msgHdr, PR_TRUE, nsnull);
  }
  else
  {
    msgHdr->OrFlags(nsMsgMessageFlags::Read, &newFlags);
    msgHdr->AndFlags(~nsMsgMessageFlags::New, &newFlags);
  }
  return 0;
}

nsresult nsParseNewMailState::EndMsgDownload()
{
  if (m_moveCoalescer)
    m_moveCoalescer->PlaybackMoves();

  // need to do this for all folders that had messages filtered into them
  PRUint32 serverCount = m_filterTargetFolders.Count();
  nsresult rv;
  nsCOMPtr<nsIMsgMailSession> session =
           do_GetService(NS_MSGMAILSESSION_CONTRACTID, &rv);
  if (NS_SUCCEEDED(rv) && session) // don't use NS_ENSURE_SUCCESS here - we need to release semaphore below
  {
    for (PRUint32 index = 0; index < serverCount; index++)
    {
      PRBool folderOpen;
      session->IsFolderOpenInWindow(m_filterTargetFolders[index], &folderOpen);
      if (!folderOpen)
      {
        PRUint32 folderFlags;
        m_filterTargetFolders[index]->GetFlags(&folderFlags);
        if (! (folderFlags & (nsMsgFolderFlags::Trash | nsMsgFolderFlags::Inbox)))
        {
          PRBool filtersRun;
          m_filterTargetFolders[index]->CallFilterPlugins(nsnull, &filtersRun);
          if (!filtersRun)
            m_filterTargetFolders[index]->SetMsgDatabase(nsnull);
        }
      }
    }
  }
  m_filterTargetFolders.Clear();
  return rv;
}

nsresult nsParseNewMailState::AppendMsgFromFile(nsIInputStream *fileStream,
                                                PRUint32 offset, PRUint32 length,
                                                nsILocalFile *destFile)
{
  nsCOMPtr <nsISeekableStream> seekableStream = do_QueryInterface(fileStream);
  seekableStream->Seek(nsISeekableStream::NS_SEEK_SET, offset);

  nsCOMPtr <nsIOutputStream> destFileStream;
  MsgNewBufferedFileOutputStream(getter_AddRefs(destFileStream), destFile, PR_RDWR | PR_CREATE_FILE, 00600);

  if (!destFileStream)
  {
#ifdef DEBUG_bienvenu
    NS_ASSERTION(PR_FALSE, "out of memory");
#endif
    return  NS_MSG_ERROR_WRITING_MAIL_FOLDER;
  }

  nsCOMPtr <nsISeekableStream> seekableDestStream = do_QueryInterface(destFileStream);
  seekableDestStream->Seek(nsISeekableStream::NS_SEEK_END, 0);
  PRInt64 filePos;
  seekableDestStream->Tell(&filePos);
  PRUint32 newMsgPos = filePos;

  if (!m_ibuffer)
    m_ibuffer_size = 10240;
  m_ibuffer_fp = 0;

  while (!m_ibuffer && (m_ibuffer_size >= 512))
  {
    m_ibuffer = (char *) PR_Malloc(m_ibuffer_size);
    if (m_ibuffer == nsnull)
      m_ibuffer_size /= 2;
  }
  NS_ASSERTION(m_ibuffer != nsnull, "couldn't get memory to move msg");
  while ((length > 0) && m_ibuffer)
  {
    PRUint32 nRead;
    fileStream->Read (m_ibuffer, length > m_ibuffer_size ? m_ibuffer_size  : length, &nRead);
    if (nRead == 0)
      break;

    PRUint32 bytesWritten;
    // we must monitor the number of bytes actually written to the file. (mscott)
    destFileStream->Write(m_ibuffer, nRead, &bytesWritten);
    if (bytesWritten != nRead)
    {
      destFileStream->Close();

      // truncate  destination file in case message was partially written
      // ### how to do this with a stream?
      destFile->SetFileSize(newMsgPos);
      return NS_MSG_ERROR_WRITING_MAIL_FOLDER;
    }

    length -= nRead;
  }

  NS_ASSERTION(length == 0, "didn't read all of original message in filter move");
  return NS_OK;
}

nsresult nsParseNewMailState::MoveIncorporatedMessage(nsIMsgDBHdr *mailHdr,
                                                      nsIMsgDatabase *sourceDB,
                                                      nsIMsgFolder *destIFolder,
                                                      nsIMsgFilter *filter,
                                                      nsIMsgWindow *msgWindow)
{
  nsresult err = 0;

  // check if the destination is a real folder (by checking for null parent)
  // and if it can file messages (e.g., servers or news folders can't file messages).
  // Or read only imap folders...
  PRBool canFileMessages = PR_TRUE;
  nsCOMPtr<nsIMsgFolder> parentFolder;
  destIFolder->GetParent(getter_AddRefs(parentFolder));
  if (parentFolder)
    destIFolder->GetCanFileMessages(&canFileMessages);
  if (!parentFolder || !canFileMessages)
  {
    if (filter)
    {
      filter->SetEnabled(PR_FALSE);
      // we need to explicitly save the filter file.
      if (m_filterList)
        m_filterList->SaveToDefaultFile();
      destIFolder->ThrowAlertMsg("filterDisabled", msgWindow);
    }
    return NS_MSG_NOT_A_MAIL_FOLDER;
  }

  nsCOMPtr <nsIMsgLocalMailFolder> destLocalFolder = do_QueryInterface(destIFolder);
  if (destLocalFolder)
  {
    PRBool destFolderTooBig;
    destLocalFolder->WarnIfLocalFileTooBig(msgWindow, &destFolderTooBig);
    if (destFolderTooBig)
      return NS_MSG_ERROR_WRITING_MAIL_FOLDER;
  }
  nsCOMPtr <nsILocalFile> destFolderFile;
  destIFolder->GetFilePath(getter_AddRefs(destFolderFile));

  if (NS_FAILED(err))
    return err;

  nsCOMPtr <nsISupports> myISupports = do_QueryInterface(static_cast<nsIMsgParseMailMsgState*>(this));

  //  NS_RELEASE(myThis);
  // Make sure no one else is writing into this folder
  if (destIFolder && (err = destIFolder->AcquireSemaphore (myISupports)) != 0)
  {
    destIFolder->ThrowAlertMsg("filterFolderDeniedLocked", msgWindow);
    return err;
  }

  NS_ASSERTION(m_inboxFileStream != 0, "no input file stream");
  if (m_inboxFileStream == 0)
  {
#ifdef DEBUG_bienvenu
    NS_ASSERTION(PR_FALSE, "couldn't get source file in move filter");
#endif
    if (destIFolder)
      destIFolder->ReleaseSemaphore (myISupports);

    return NS_MSG_FOLDER_UNREADABLE;  // ### dmb
  }
  nsCOMPtr <nsISeekableStream> seekableStream = do_QueryInterface(m_inboxFileStream);
  seekableStream->Seek(nsISeekableStream::NS_SEEK_SET, m_curHdrOffset);
  PRInt64 destFolderSize;
  destFolderFile->GetFileSize(&destFolderSize);
  PRUint32 newMsgPos = destFolderSize;

  nsCOMPtr<nsIMsgLocalMailFolder> localFolder = do_QueryInterface(destIFolder);
  nsCOMPtr<nsIMsgDatabase> destMailDB;

  if (!localFolder)
    return NS_MSG_POP_FILTER_TARGET_ERROR;

  nsresult rv = localFolder->GetDatabaseWOReparse(getter_AddRefs(destMailDB));
  NS_ASSERTION(destMailDB, "failed to open mail db parsing folder");
  // don't force upgrade in place - open the db here before we start writing to the
  // destination file because XP_Stat can return file size including bytes written...

  PRUint32 messageLength;
  mailHdr->GetMessageSize(&messageLength);
  rv = AppendMsgFromFile(m_inboxFileStream, m_curHdrOffset, messageLength, destFolderFile);

  if (NS_FAILED(rv))
  {
    if (destMailDB)
      destMailDB->Close(PR_TRUE);

    if (destIFolder)
    {
      destIFolder->ReleaseSemaphore(myISupports);
      destIFolder->ThrowAlertMsg("filterFolderWriteFailed", msgWindow);
    }
    return NS_MSG_ERROR_WRITING_MAIL_FOLDER;
  }

  PRBool movedMsgIsNew = PR_FALSE;
  // if we have made it this far then the message has successfully been written to the new folder
  // now add the header to the destMailDB.
  if (NS_SUCCEEDED(rv) && destMailDB)
  {
    nsCOMPtr <nsIMsgDBHdr> newHdr;

    nsresult msgErr = destMailDB->CopyHdrFromExistingHdr(newMsgPos, mailHdr, PR_FALSE, getter_AddRefs(newHdr));
    if (NS_SUCCEEDED(msgErr) && newHdr)
    {
      PRUint32 newFlags;
      // set new byte offset, since the offset in the old file is certainly wrong
      newHdr->SetMessageKey (newMsgPos);
      newHdr->GetFlags(&newFlags);
      if (! (newFlags & nsMsgMessageFlags::Read))
      {
        nsCString junkScoreStr;
        (void) newHdr->GetStringProperty("junkscore", getter_Copies(junkScoreStr));
        if (atoi(junkScoreStr.get()) == nsIJunkMailPlugin::IS_HAM_SCORE)
        {
          newHdr->OrFlags(nsMsgMessageFlags::New, &newFlags);
          destMailDB->AddToNewList(newMsgPos);
          movedMsgIsNew = PR_TRUE;
        }
      }
      destMailDB->AddNewHdrToDB(newHdr, PR_TRUE);
      nsCOMPtr<nsIMsgFolderNotificationService> notifier(do_GetService(NS_MSGNOTIFICATIONSERVICE_CONTRACTID));
      if (notifier)
        notifier->NotifyMsgAdded(newHdr);
      // mark the header as not yet reported classified
      destIFolder->OrProcessingFlags(
        newMsgPos, nsMsgProcessingFlags::NotReportedClassified);
      m_msgToForwardOrReply = newHdr;
    }
  }
  else
  {
    if (destMailDB)
      destMailDB = nsnull;
  }
  if (movedMsgIsNew)
    destIFolder->SetHasNewMessages(PR_TRUE);
  if (m_filterTargetFolders.IndexOf(destIFolder) == -1)
    m_filterTargetFolders.AppendObject(destIFolder);
  m_inboxFileStream->Close();

  nsresult truncRet = m_inboxFile->SetFileSize(m_curHdrOffset);
  NS_ASSERTION(NS_SUCCEEDED(truncRet), "unable to truncate file");
  if (NS_FAILED(truncRet))
   destIFolder->ThrowAlertMsg("filterFolderTruncateFailed", msgWindow);
  else
    // tell parser that we've truncated the Inbox
    nsParseMailMessageState::Init(m_curHdrOffset);

  MsgReopenFileStream(m_inboxFile, m_inboxFileStream);

  seekableStream = do_QueryInterface(m_inboxFileStream);
  PRInt64 inboxFileSize;
  m_inboxFile->GetFileSize(&inboxFileSize);
 if (seekableStream)
    seekableStream->Seek(nsISeekableStream::NS_SEEK_SET, inboxFileSize);

  if (destIFolder)
    destIFolder->ReleaseSemaphore (myISupports);


  (void) localFolder->RefreshSizeOnDisk();
  if (destIFolder)
    destIFolder->SetFlag(nsMsgFolderFlags::GotNew);

  if (destMailDB != nsnull)
  {
    // update the folder size so we won't reparse.
    UpdateDBFolderInfo(destMailDB);
    if (destIFolder != nsnull)
      destIFolder->UpdateSummaryTotals(PR_TRUE);

    destMailDB->Commit(nsMsgDBCommitType::kLargeCommit);
  }
  return err;
}

