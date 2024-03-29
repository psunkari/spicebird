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
 *   Christian Eyrich <ch.ey@gmx.net>
 *   Olivier Parniere BT Global Services / Etat francais Ministere de la Defense
 *   Eric Ballet Baz BT Global Services / Etat francais Ministere de la Defense
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

#ifdef MOZ_LOGGING
// sorry, this has to be before the pre-compiled header
#define FORCE_PR_LOG /* Allow logging in the release build */
#endif

#include "msgCore.h"
#include "nsSmtpProtocol.h"
#include "nscore.h"
#include "nsIStreamListener.h"
#include "nsIInputStream.h"
#include "nsIOutputStream.h"
#include "nsISocketTransport.h"
#include "nsIMsgHeaderParser.h"
#include "nsIMsgMailNewsUrl.h"
#include "nsMsgBaseCID.h"
#include "nsMsgCompCID.h"
#include "nsIPrompt.h"
#include "nsIAuthPrompt.h"
#include "nsString.h"
#include "nsTextFormatter.h"
#include "nsIMsgIdentity.h"
#include "nsISmtpServer.h"
#include "prtime.h"
#include "prlog.h"
#include "prerror.h"
#include "prprf.h"
#include "prmem.h"
#include "plbase64.h"
#include "prnetdb.h"
#include "prsystem.h"
#include "nsEscape.h"
#include "nsMsgUtils.h"
#include "nsIPipe.h"
#include "nsNetUtil.h"
#include "nsIPrefService.h"
#include "nsISignatureVerifier.h"
#include "nsISSLSocketControl.h"
#include "nsComposeStrings.h"
#include "nsIStringBundle.h"
#include "nsMsgCompUtils.h"
#include "nsIMsgWindow.h"


#ifndef XP_UNIX
#include <stdarg.h>
#endif /* !XP_UNIX */

static PRLogModuleInfo *SMTPLogModule = nsnull;

/* the output_buffer_size must be larger than the largest possible line
 * 2000 seems good for news
 *
 * jwz: I increased this to 4k since it must be big enough to hold the
 * entire button-bar HTML, and with the new "mailto" format, that can
 * contain arbitrarily long header fields like "references".
 *
 * fortezza: proxy auth is huge, buffer increased to 8k (sigh).
 */
#define OUTPUT_BUFFER_SIZE (4096*2)

////////////////////////////////////////////////////////////////////////////////////////////
// TEMPORARY HARD CODED FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////

/* based on in NET_ExplainErrorDetails in mkmessag.c */
nsresult nsExplainErrorDetails(nsISmtpUrl * aSmtpUrl, int code, ...)
{
  NS_ENSURE_ARG(aSmtpUrl);

  nsresult rv = NS_OK;
  va_list args;

  nsCOMPtr<nsIPrompt> dialog;
  aSmtpUrl->GetPrompt(getter_AddRefs(dialog));
  NS_ENSURE_TRUE(dialog, NS_ERROR_FAILURE);

  PRUnichar *  msg;
  nsString eMsg;
  nsCOMPtr<nsIStringBundleService> bundleService(do_GetService("@mozilla.org/intl/stringbundle;1", &rv));
  NS_ENSURE_SUCCESS(rv, rv);
  nsCOMPtr<nsIStringBundle> bundle;
  rv = bundleService->CreateBundle("chrome://messenger/locale/messengercompose/composeMsgs.properties", getter_AddRefs(bundle));
  NS_ENSURE_SUCCESS(rv, rv);

  va_start (args, code);

  switch (code)
  {
      case NS_ERROR_SMTP_SERVER_ERROR:
      case NS_ERROR_TCP_READ_ERROR:
      case NS_ERROR_SMTP_TEMP_SIZE_EXCEEDED:
      case NS_ERROR_SMTP_PERM_SIZE_EXCEEDED_1:
      case NS_ERROR_SMTP_PERM_SIZE_EXCEEDED_2:
      case NS_ERROR_SENDING_FROM_COMMAND:
      case NS_ERROR_SENDING_RCPT_COMMAND:
      case NS_ERROR_SENDING_DATA_COMMAND:
      case NS_ERROR_SENDING_MESSAGE:
      case NS_ERROR_SMTP_GREETING:
         bundle->GetStringFromID(NS_ERROR_GET_CODE(code), getter_Copies(eMsg));
         msg = nsTextFormatter::vsmprintf(eMsg.get(), args);
         break;
      default:
         bundle->GetStringFromID(NS_ERROR_GET_CODE(NS_ERROR_COMMUNICATIONS_ERROR), getter_Copies(eMsg));
         msg = nsTextFormatter::smprintf(eMsg.get(), code);
         break;
  }

  if (msg)
  {
    rv = dialog->Alert(nsnull, msg);
    nsTextFormatter::smprintf_free(msg);
  }

  va_end (args);

  return rv;
}

/* RFC 1891 -- extended smtp value encoding scheme

  5. Additional parameters for RCPT and MAIL commands

     The extended RCPT and MAIL commands are issued by a client when it wishes to request a DSN from the
     server, under certain conditions, for a particular recipient. The extended RCPT and MAIL commands are
     identical to the RCPT and MAIL commands defined in [1], except that one or more of the following parameters
     appear after the sender or recipient address, respectively. The general syntax for extended SMTP commands is
     defined in [4].

     NOTE: Although RFC 822 ABNF is used to describe the syntax of these parameters, they are not, in the
     language of that document, "structured field bodies". Therefore, while parentheses MAY appear within an
     emstp-value, they are not recognized as comment delimiters.

     The syntax for "esmtp-value" in [4] does not allow SP, "=", control characters, or characters outside the
     traditional ASCII range of 1- 127 decimal to be transmitted in an esmtp-value. Because the ENVID and
     ORCPT parameters may need to convey values outside this range, the esmtp-values for these parameters are
     encoded as "xtext". "xtext" is formally defined as follows:

     xtext = *( xchar / hexchar )

     xchar = any ASCII CHAR between "!" (33) and "~" (126) inclusive, except for "+" and "=".

	; "hexchar"s are intended to encode octets that cannot appear
	; as ASCII characters within an esmtp-value.

		 hexchar = ASCII "+" immediately followed by two upper case hexadecimal digits

	When encoding an octet sequence as xtext:

	+ Any ASCII CHAR between "!" and "~" inclusive, except for "+" and "=",
		 MAY be encoded as itself. (A CHAR in this range MAY instead be encoded as a "hexchar", at the
		 implementor's discretion.)

	+ ASCII CHARs that fall outside the range above must be encoded as
		 "hexchar".

 */
/* caller must free the return buffer */
static char *
esmtp_value_encode(char *addr)
{
  char *buffer = (char *) PR_Malloc(512); /* esmtp ORCPT allow up to 500 chars encoded addresses */
  char *bp = buffer, *bpEnd = buffer+500;
  int len, i;

  if (!buffer) return NULL;

  *bp=0;
  if (! addr || *addr == 0) /* this will never happen */
    return buffer;

  for (i=0, len=PL_strlen(addr); i < len && bp < bpEnd; i++)
  {
    if (*addr >= 0x21 &&
      *addr <= 0x7E &&
      *addr != '+' &&
      *addr != '=')
    {
      *bp++ = *addr++;
    }
    else
    {
      PR_snprintf(bp, bpEnd-bp, "+%.2X", ((int)*addr++));
      bp += PL_strlen(bp);
    }
  }
  *bp=0;
  return buffer;
}

////////////////////////////////////////////////////////////////////////////////////////////
// END OF TEMPORARY HARD CODED FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////

NS_IMPL_ADDREF_INHERITED(nsSmtpProtocol, nsMsgAsyncWriteProtocol)
NS_IMPL_RELEASE_INHERITED(nsSmtpProtocol, nsMsgAsyncWriteProtocol)

NS_INTERFACE_MAP_BEGIN(nsSmtpProtocol)
NS_INTERFACE_MAP_END_INHERITING(nsMsgAsyncWriteProtocol)

nsSmtpProtocol::nsSmtpProtocol(nsIURI * aURL)
    : nsMsgAsyncWriteProtocol(aURL)
{
}

nsSmtpProtocol::~nsSmtpProtocol()
{
  // free our local state
  PR_Free(m_addressCopy);
  PR_Free(m_dataBuf);
  delete m_lineStreamBuffer;
}

void nsSmtpProtocol::Initialize(nsIURI * aURL)
{
    NS_PRECONDITION(aURL, "invalid URL passed into Smtp Protocol");
    nsresult rv = NS_OK;

    m_flags = 0;
    m_origAuthFlags = 0;
    m_prefAuthMethod = PREF_AUTH_NONE;
    m_usernamePrompted = PR_FALSE;
    m_prefTrySSL = PREF_SECURE_TRY_STARTTLS;
    m_prefUseSecAuth = PR_TRUE;
    m_prefTrySecAuth = PR_FALSE;
    m_tlsInitiated = PR_FALSE;

    m_urlErrorState = NS_ERROR_FAILURE;

    if (!SMTPLogModule)
        SMTPLogModule = PR_NewLogModule("SMTP");

    if (aURL)
        m_runningURL = do_QueryInterface(aURL);

    // extract out message feedback if there is any.
    nsCOMPtr<nsIMsgMailNewsUrl> mailnewsUrl = do_QueryInterface(aURL);
    if (mailnewsUrl)
        mailnewsUrl->GetStatusFeedback(getter_AddRefs(m_statusFeedback));

    m_dataBuf = (char *) PR_Malloc(sizeof(char) * OUTPUT_BUFFER_SIZE);
    m_dataBufSize = OUTPUT_BUFFER_SIZE;

    m_nextState = SMTP_START_CONNECT;
    m_nextStateAfterResponse = SMTP_START_CONNECT;
    m_responseCode = 0;
    m_previousResponseCode = 0;
    m_continuationResponse = -1;
    m_tlsEnabled = PR_FALSE;
    m_addressCopy = nsnull;
    m_addresses = nsnull;
    m_addressesLeft = 0;

#ifdef UNREADY_CODE
    m_totalAmountWritten = 0;
#endif /* UNREADY_CODE */

    m_sendDone = PR_FALSE;

    m_sizelimit = 0;
    m_totalMessageSize = 0;
    nsCOMPtr<nsIFile> file;
    m_runningURL->GetPostMessageFile(getter_AddRefs(file));
    if (file)
        file->GetFileSize(&m_totalMessageSize);

    m_originalContentLength = 0;
    m_totalAmountRead = 0;

    m_lineStreamBuffer = new nsMsgLineStreamBuffer(OUTPUT_BUFFER_SIZE, PR_TRUE);
    // ** may want to consider caching the server capability to save lots of
    // round trip communication between the client and server
    nsCOMPtr<nsISmtpServer> smtpServer;
    m_runningURL->GetSmtpServer(getter_AddRefs(smtpServer));
    if (smtpServer) {
        smtpServer->GetAuthMethod(&m_prefAuthMethod);
        smtpServer->GetTrySSL(&m_prefTrySSL);
        smtpServer->GetUseSecAuth(&m_prefUseSecAuth);
        // Uncomment out the following line to turn back on sec auth probing
        // smtpServer->GetTrySecAuth(&m_prefTrySecAuth);
        smtpServer->GetHelloArgument(getter_Copies(m_helloArgument));
    }

#if defined(PR_LOGGING)
    nsCAutoString hostName;
    aURL->GetAsciiHost(hostName);
    PR_LOG(SMTPLogModule, PR_LOG_ALWAYS, ("SMTP Connecting to: %s", hostName.get()));
#endif

    // When we are making a secure connection, we need to make sure that we
    // pass an interface requestor down to the socket transport so that PSM can
    // retrieve a nsIPrompt instance if needed.
    nsCOMPtr<nsIInterfaceRequestor> callbacks;
    nsCOMPtr<nsISmtpUrl> smtpUrl(do_QueryInterface(aURL));
    if (smtpUrl)
        smtpUrl->GetNotificationCallbacks(getter_AddRefs(callbacks));

    if (m_prefTrySSL == PREF_SECURE_ALWAYS_SMTPS)
        rv = OpenNetworkSocket(aURL, "ssl", callbacks);
    else if (m_prefTrySSL != PREF_SECURE_NEVER)
    {
        rv = OpenNetworkSocket(aURL, "starttls", callbacks);
        if (NS_FAILED(rv) && m_prefTrySSL == PREF_SECURE_TRY_STARTTLS)
        {
            m_prefTrySSL = PREF_SECURE_NEVER;
            rv = OpenNetworkSocket(aURL, nsnull, callbacks);
        }
    }
    else
        rv = OpenNetworkSocket(aURL, nsnull, callbacks);

    if (NS_FAILED(rv))
        return;
}

void nsSmtpProtocol::AppendHelloArgument(nsACString& aResult)
{
  nsresult rv;

  // is a custom EHLO/HELO argument configured for the transport to be used?
  if (!m_helloArgument.IsEmpty())
  {
      aResult += m_helloArgument;
  }
  else
  {
      // is a FQDN known for this system?
      char hostName[256];
      PR_GetSystemInfo(PR_SI_HOSTNAME_UNTRUNCATED, hostName, sizeof hostName);
      if ((hostName[0] != '\0') && (strchr(hostName, '.') != NULL))
      {
          nsDependentCString cleanedHostName(hostName);
          // avoid problems with hostnames containing newlines/whitespace
          cleanedHostName.StripWhitespace();
          aResult += cleanedHostName;
      }
      else
      {
          PRNetAddr iaddr; // IP address for this connection
          // our transport is always a nsISocketTransport
          nsCOMPtr<nsISocketTransport> socketTransport = do_QueryInterface(m_transport);
          // should return the interface ip of the SMTP connection
          // minimum case - see bug 68877 and RFC 2821, chapter 4.1.1.1
          rv = socketTransport->GetSelfAddr(&iaddr);

          if (NS_SUCCEEDED(rv))
          {
              // turn it into a string
              char ipAddressString[64];
              if (PR_NetAddrToString(&iaddr, ipAddressString, sizeof(ipAddressString)) == PR_SUCCESS)
              {
                  NS_ASSERTION(!PR_IsNetAddrType(&iaddr, PR_IpAddrV4Mapped),
                               "unexpected IPv4-mapped IPv6 address");

                  if (iaddr.raw.family == PR_AF_INET6)   // IPv6 style address?
                      aResult.AppendLiteral("[IPv6:");
                  else
                      aResult.AppendLiteral("[");

                  aResult.Append(nsDependentCString(ipAddressString) + NS_LITERAL_CSTRING("]"));
              }
          }
      }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
// we suppport the nsIStreamListener interface
////////////////////////////////////////////////////////////////////////////////////////////

// stop binding is a "notification" informing us that the stream
// associated with aURL is going away.
NS_IMETHODIMP nsSmtpProtocol::OnStopRequest(nsIRequest *request, nsISupports *ctxt,
                                            nsresult aStatus)
{
  PRBool connDroppedDuringAuth = aStatus == NS_OK && !m_sendDone &&
      (m_nextStateAfterResponse == SMTP_AUTH_LOGIN_STEP0_RESPONSE ||
       m_nextStateAfterResponse == SMTP_AUTH_LOGIN_RESPONSE);
  if (aStatus == NS_OK && !m_sendDone) {
    // if we are getting OnStopRequest() with NS_OK,
    // but we haven't finished clean, that's spells trouble.
    // it means that the server has dropped us before we could send the whole mail
    // for example, see bug #200647
    PR_LOG(SMTPLogModule, PR_LOG_ALWAYS,
 ("SMTP connection dropped after %ld total bytes read", m_totalAmountRead));
    if (!connDroppedDuringAuth)
      nsMsgAsyncWriteProtocol::OnStopRequest(nsnull, ctxt, NS_ERROR_NET_INTERRUPT);
  }
  else
    nsMsgAsyncWriteProtocol::OnStopRequest(nsnull, ctxt, aStatus);

  // okay, we've been told that the send is done and the connection is going away. So
  // we need to release all of our state
  nsresult rv = nsMsgAsyncWriteProtocol::CloseSocket();
  // If the server dropped the connection when we were expecting
  // a login response, reprompt for password, and if the user asks,
  // retry the url.
  if (connDroppedDuringAuth)
  {
    nsCOMPtr<nsIURI> runningURI = do_QueryInterface(m_runningURL);
    PRInt32 rv = AuthLoginResponse(nsnull, 0);
    if (rv < 0)
      return rv;
    return LoadUrl(runningURI, ctxt);
  }

  return rv;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// End of nsIStreamListenerSupport
//////////////////////////////////////////////////////////////////////////////////////////////

void nsSmtpProtocol::UpdateStatus(PRInt32 aStatusID)
{
  if (m_statusFeedback)
  {
    nsresult rv;
    nsCOMPtr<nsIStringBundleService> bundleService(do_GetService("@mozilla.org/intl/stringbundle;1", &rv));
    if (NS_FAILED(rv)) return;
    nsCOMPtr<nsIStringBundle> bundle;
    rv = bundleService->CreateBundle("chrome://messenger/locale/messengercompose/composeMsgs.properties", getter_AddRefs(bundle));
    if (NS_FAILED(rv)) return;
    nsString msg;
    bundle->GetStringFromID(aStatusID, getter_Copies(msg));
    UpdateStatusWithString(msg.get());
  }
}

void nsSmtpProtocol::UpdateStatusWithString(const PRUnichar * aStatusString)
{
  if (m_statusFeedback && aStatusString)
    m_statusFeedback->ShowStatusString(nsDependentString(aStatusString));
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Begin protocol state machine functions...
//////////////////////////////////////////////////////////////////////////////////////////////

/*
 * gets the response code from the SMTP server and the
 * response line
 *
 * returns the TCP return code from the read
 */
PRInt32 nsSmtpProtocol::SmtpResponse(nsIInputStream * inputStream, PRUint32 length)
{
  char * line = nsnull;
  char cont_char;
  PRUint32 ln = 0;
  PRBool pauseForMoreData = PR_FALSE;

  if (!m_lineStreamBuffer)
    return -1; // this will force an error and at least we won't crash

  line = m_lineStreamBuffer->ReadNextLine(inputStream, ln, pauseForMoreData);

  if (pauseForMoreData || !line)
  {
    SetFlag(SMTP_PAUSE_FOR_READ); /* pause */
    PR_Free(line);
    return(ln);
  }

  m_totalAmountRead += ln;

  PR_LOG(SMTPLogModule, PR_LOG_ALWAYS, ("SMTP Response: %s", line));
  cont_char = ' '; /* default */
  // sscanf() doesn't update m_responseCode if line doesn't start
  // with a number. That can be dangerous. So be sure to set
  // m_responseCode to 0 if no items read.
  if (PR_sscanf(line, "%d%c", &m_responseCode, &cont_char) <= 0)
    m_responseCode = 0;

  if (m_continuationResponse == -1)
  {
    if (cont_char == '-')  /* begin continuation */
      m_continuationResponse = m_responseCode;

    // display the whole message if no valid response code or
    // message shorter than 4 chars
    m_responseText = (m_responseCode >= 100 && PL_strlen(line) > 3) ? line + 4 : line;
  }
  else
  { /* have to continue */
    if (m_continuationResponse == m_responseCode && cont_char == ' ')
      m_continuationResponse = -1;    /* ended */

    if (m_responseText.IsEmpty() || m_responseText.Last() != '\n')
      m_responseText += "\n";

    m_responseText += (PL_strlen(line) > 3) ? line + 4 : line;
  }

  if (m_responseCode == 220 && m_responseText.Length() && !m_tlsInitiated)
  {
    m_nextStateAfterResponse = SMTP_EXTN_LOGIN_RESPONSE;
  }

  if (m_continuationResponse == -1)  /* all done with this response? */
  {
    m_nextState = m_nextStateAfterResponse;
    ClearFlag(SMTP_PAUSE_FOR_READ); /* don't pause */
  }

  PR_Free(line);
  return(0);  /* everything ok */
}

PRInt32 nsSmtpProtocol::ExtensionLoginResponse(nsIInputStream * inputStream, PRUint32 length)
{
  PRInt32 status = 0;

  if (m_responseCode != 220)
  {
#ifdef DEBUG
    nsresult rv =
#endif
    nsExplainErrorDetails(m_runningURL, NS_ERROR_SMTP_GREETING,
                          m_responseText.get());
    NS_ASSERTION(NS_SUCCEEDED(rv), "failed to explain SMTP error");

    m_urlErrorState = NS_ERROR_BUT_DONT_SHOW_ALERT;
    return(NS_ERROR_COULD_NOT_LOGIN_TO_SMTP_SERVER);
  }

  nsCAutoString buffer("EHLO ");
  AppendHelloArgument(buffer);
  buffer += CRLF;

  nsCOMPtr<nsIURI> url = do_QueryInterface(m_runningURL);

  status = SendData(url, buffer.get());

  m_nextState = SMTP_RESPONSE;
  m_nextStateAfterResponse = SMTP_SEND_EHLO_RESPONSE;
  SetFlag(SMTP_PAUSE_FOR_READ);

  return(status);
}

PRInt32 nsSmtpProtocol::SendHeloResponse(nsIInputStream * inputStream, PRUint32 length)
{
  PRInt32 status = 0;
  nsCAutoString buffer;
  nsresult rv;

  if (m_responseCode != 250)
  {
#ifdef DEBUG
    rv =
#endif
    nsExplainErrorDetails(m_runningURL, NS_ERROR_SMTP_SERVER_ERROR,
                          m_responseText.get());
    NS_ASSERTION(NS_SUCCEEDED(rv), "failed to explain SMTP error");

    m_urlErrorState = NS_ERROR_BUT_DONT_SHOW_ALERT;
    return(NS_ERROR_COULD_NOT_LOGIN_TO_SMTP_SERVER);
  }

  // check if we're just verifying the ability to logon
  nsCOMPtr<nsISmtpUrl> smtpUrl = do_QueryInterface(m_runningURL, &rv);
  NS_ENSURE_SUCCESS(rv, rv);
  PRBool verifyingLogon = PR_FALSE;
  smtpUrl->GetVerifyLogon(&verifyingLogon);
  if (verifyingLogon)
    return SendQuit();

  // extract the email address from the identity
  nsCString emailAddress;
  nsCOMPtr <nsIMsgIdentity> senderIdentity;
  rv = m_runningURL->GetSenderIdentity(getter_AddRefs(senderIdentity));
  if (NS_FAILED(rv) || !senderIdentity)
  {
    m_urlErrorState = NS_ERROR_COULD_NOT_GET_USERS_MAIL_ADDRESS;
    return(NS_ERROR_COULD_NOT_GET_USERS_MAIL_ADDRESS);
  }
  senderIdentity->GetEmail(emailAddress);

  if (emailAddress.IsEmpty())
  {
    m_urlErrorState = NS_ERROR_COULD_NOT_GET_USERS_MAIL_ADDRESS;
    return(NS_ERROR_COULD_NOT_GET_USERS_MAIL_ADDRESS);
  }

  nsCOMPtr<nsIMsgHeaderParser> parser = do_GetService(NS_MAILNEWS_MIME_HEADER_PARSER_CONTRACTID);
  nsCString fullAddress;
  if (parser)
  {
    // pass nsnull for the name, since we just want the email.
    //
    // seems a little weird that we are passing in the emailAddress
    // when that's the out parameter
    parser->MakeFullAddressString(nsnull, emailAddress.get(),
                                  getter_Copies(fullAddress));
  }

  buffer = "MAIL FROM:<";
  buffer += fullAddress;
  buffer += ">";

  if (TestFlag(SMTP_EHLO_DSN_ENABLED))
  {
    PRBool requestDSN = PR_FALSE;
    rv = m_runningURL->GetRequestDSN(&requestDSN);

    if (requestDSN)
    {
      nsCOMPtr <nsIPrefService> prefs = do_GetService(NS_PREFSERVICE_CONTRACTID, &rv);
      NS_ENSURE_SUCCESS(rv,rv);

      nsCOMPtr<nsIPrefBranch> prefBranch;
      rv = prefs->GetBranch(nsnull, getter_AddRefs(prefBranch));
      NS_ENSURE_SUCCESS(rv,rv);

      PRBool requestRetFull = PR_FALSE;
      rv = prefBranch->GetBoolPref("mail.dsn.ret_full_on", &requestRetFull);

      buffer += requestRetFull ? " RET=FULL" : " RET=HDRS";

      char* msgID = msg_generate_message_id(senderIdentity);
      buffer += " ENVID=";
      buffer += msgID;

      PR_Free(msgID);
    }
  }

  if(TestFlag(SMTP_EHLO_SIZE_ENABLED))
  {
    buffer.Append(" SIZE=");
    buffer.AppendInt(m_totalMessageSize);
  }
  buffer += CRLF;

  nsCOMPtr<nsIURI> url = do_QueryInterface(m_runningURL);
  status = SendData(url, buffer.get());

  m_nextState = SMTP_RESPONSE;


  m_nextStateAfterResponse = SMTP_SEND_MAIL_RESPONSE;
  SetFlag(SMTP_PAUSE_FOR_READ);

  return(status);
}

PRInt32 nsSmtpProtocol::SendEhloResponse(nsIInputStream * inputStream, PRUint32 length)
{
    PRInt32 status = 0;
    nsCOMPtr<nsIURI> url = do_QueryInterface(m_runningURL);

    if (m_responseCode != 250)
    {
        /* EHLO must not be implemented by the server, so fall back to the HELO case
         * if command is unrecognized or unimplemented.
         */
        if (m_responseCode == 500 || m_responseCode == 502)
        {
            /* If STARTTLS is requested by the user, EHLO is required to advertise it.
             * But only if TLS handshake is not already accomplished.
             */
            if (m_prefTrySSL == PREF_SECURE_ALWAYS_STARTTLS && !m_tlsEnabled)
            {
                m_nextState = SMTP_ERROR_DONE;
                m_urlErrorState = NS_ERROR_STARTTLS_FAILED_EHLO_STARTTLS;
                return(NS_ERROR_STARTTLS_FAILED_EHLO_STARTTLS);
            }
            else
                // EHLO is always needed if authentication is requested.
                if (m_prefAuthMethod == PREF_AUTH_ANY)
                {
                    m_nextState = SMTP_ERROR_DONE;
                    m_urlErrorState = NS_ERROR_COULD_NOT_LOGIN_TO_SMTP_SERVER_AUTH_NONE;
                    return(NS_ERROR_COULD_NOT_LOGIN_TO_SMTP_SERVER);
                }

            nsCAutoString buffer("HELO ");
            AppendHelloArgument(buffer);
            buffer += CRLF;

            status = SendData(url, buffer.get());

            m_nextState = SMTP_RESPONSE;
            m_nextStateAfterResponse = SMTP_SEND_HELO_RESPONSE;
            SetFlag(SMTP_PAUSE_FOR_READ);
            return (status);
        }
        /* e.g. getting 421 "Server says unauthorized, bye" or
         * 501 "Syntax error in EHLOs parameters or arguments"
         */
        else
        {
#ifdef DEBUG
            nsresult rv =
#endif
            nsExplainErrorDetails(m_runningURL, NS_ERROR_SMTP_SERVER_ERROR,
                                  m_responseText.get());
            NS_ASSERTION(NS_SUCCEEDED(rv), "failed to explain SMTP error");

            m_urlErrorState = NS_ERROR_BUT_DONT_SHOW_ALERT;
            return(NS_ERROR_COULD_NOT_LOGIN_TO_SMTP_SERVER);
        }
    }

    PRInt32 responseLength = m_responseText.Length();
    PRInt32 startPos = 0;
    PRInt32 endPos;
    do
    {
        endPos = m_responseText.FindChar('\n', startPos + 1);
        nsCAutoString responseLine;
        responseLine.Assign(Substring(m_responseText, startPos,
            (endPos >= 0 ? endPos : responseLength) - startPos));
        responseLine.CompressWhitespace();

        if (responseLine.Compare("STARTTLS", PR_TRUE) == 0)
        {
            SetFlag(SMTP_EHLO_STARTTLS_ENABLED);
        }
        else if (responseLine.Compare("DSN", PR_TRUE) == 0)
        {
            SetFlag(SMTP_EHLO_DSN_ENABLED);
        }
        else if (responseLine.Compare("AUTH", PR_TRUE, 4) == 0)
        {
            SetFlag(SMTP_AUTH);

            if (m_prefUseSecAuth || m_prefTrySecAuth)
            {
                if (responseLine.Find("GSSAPI", PR_TRUE, 5) >= 0)
                    SetFlag(SMTP_AUTH_GSSAPI_ENABLED);

                nsresult rv;
                nsCOMPtr<nsISignatureVerifier> verifier = do_GetService(SIGNATURE_VERIFIER_CONTRACTID, &rv);
                // this checks if psm is installed...
                if (NS_SUCCEEDED(rv))
                {
                    if (responseLine.Find("CRAM-MD5", PR_TRUE, 5) >= 0)
                        SetFlag(SMTP_AUTH_CRAM_MD5_ENABLED);

                    if (responseLine.Find("NTLM", PR_TRUE, 5) >= 0)
                        SetFlag(SMTP_AUTH_NTLM_ENABLED);

                    if (responseLine.Find("MSN", PR_TRUE, 5) >= 0)
                        SetFlag(SMTP_AUTH_MSN_ENABLED);
                }

                if (m_prefTrySecAuth)
                {
                  // don't adopt value for m_prefTrySecAuth instantly
                  // so that we reprobe in case of STARTTLS

                  nsCOMPtr<nsISmtpServer> smtpServer;
                  m_runningURL->GetSmtpServer(getter_AddRefs(smtpServer));
                  if (smtpServer)
                  {
                    // If we are in probe mode, save what we found out for the future.
                    // Don't trust GSSAPI since the server can advertise it 
                    // but the client may not be set up for it.
                    m_prefUseSecAuth = TestFlag(SMTP_AUTH_SEC_ENABLED &
                                                ~SMTP_AUTH_GSSAPI_ENABLED);
                    smtpServer->SetUseSecAuth(m_prefUseSecAuth);
                    // then disable probing for next run
                    smtpServer->SetTrySecAuth(PR_FALSE);
                  }
                }
            }

            if (!m_prefUseSecAuth)
            {
                if (responseLine.Find("PLAIN", PR_TRUE, 5) >= 0)
                    SetFlag(SMTP_AUTH_PLAIN_ENABLED);

                if (responseLine.Find("LOGIN", PR_TRUE, 5) >= 0)
                    SetFlag(SMTP_AUTH_LOGIN_ENABLED);

                if (responseLine.Find("EXTERNAL", PR_TRUE, 5) >= 0)
                    SetFlag(SMTP_AUTH_EXTERNAL_ENABLED);
            }

            // for use after mechs disabled fallbacks when login failed
            BackupAuthFlags();
        }
        else if (responseLine.Compare("SIZE", PR_TRUE, 4) == 0)
        {
            SetFlag(SMTP_EHLO_SIZE_ENABLED);

            m_sizelimit = atol((responseLine.get()) + 4);
        }

        startPos = endPos + 1;
    } while (endPos >= 0);

    if (TestFlag(SMTP_EHLO_SIZE_ENABLED) &&
       m_sizelimit > 0 && (PRInt32)m_totalMessageSize > m_sizelimit)
    {
#ifdef DEBUG
        nsresult rv =
#endif
        nsExplainErrorDetails(m_runningURL,
                      NS_ERROR_SMTP_PERM_SIZE_EXCEEDED_1, m_sizelimit);
        NS_ASSERTION(NS_SUCCEEDED(rv), "failed to explain SMTP error");

        m_urlErrorState = NS_ERROR_BUT_DONT_SHOW_ALERT;
        return(NS_ERROR_SENDING_FROM_COMMAND);
    }

    m_nextState = SMTP_AUTH_PROCESS_STATE;
    return status;
}


PRInt32 nsSmtpProtocol::SendTLSResponse()
{
  // only tear down our existing connection and open a new one if we received a 220 response
  // from the smtp server after we issued the STARTTLS
  nsresult rv = NS_OK;
  if (m_responseCode == 220)
  {
      nsCOMPtr<nsISupports> secInfo;
      nsCOMPtr<nsISocketTransport> strans = do_QueryInterface(m_transport, &rv);
      if (NS_FAILED(rv)) return rv;

      rv = strans->GetSecurityInfo(getter_AddRefs(secInfo));

      if (NS_SUCCEEDED(rv) && secInfo) {
          nsCOMPtr<nsISSLSocketControl> sslControl = do_QueryInterface(secInfo, &rv);

          if (NS_SUCCEEDED(rv) && sslControl)
              rv = sslControl->StartTLS();
      }

      if (NS_SUCCEEDED(rv))
      {
          m_nextState = SMTP_EXTN_LOGIN_RESPONSE;
          m_nextStateAfterResponse = SMTP_EXTN_LOGIN_RESPONSE;
          m_tlsEnabled = PR_TRUE;
          m_flags = 0; // resetting the flags
          BackupAuthFlags();
          return rv;
      }
  }

  ClearFlag(SMTP_EHLO_STARTTLS_ENABLED);
  m_tlsInitiated = PR_FALSE;
  m_nextState = SMTP_AUTH_PROCESS_STATE;

  return rv;
}

PRInt32 nsSmtpProtocol::ProcessAuth()
{
    PRInt32 status = 0;
    nsCAutoString buffer;
    nsCOMPtr<nsIURI> url = do_QueryInterface(m_runningURL);

    if (!m_tlsEnabled)
    {
        if (TestFlag(SMTP_EHLO_STARTTLS_ENABLED))
        {
            // Do not try to combine SMTPS with STARTTLS.
            // If PREF_SECURE_ALWAYS_SMTPS is set,
            // we are alrady using a secure connection.
            // Do not attempt to do STARTTLS,
            // even if server offers it.
            if (m_prefTrySSL == PREF_SECURE_TRY_STARTTLS ||
                m_prefTrySSL == PREF_SECURE_ALWAYS_STARTTLS)
            {
                buffer = "STARTTLS";
                buffer += CRLF;

                status = SendData(url, buffer.get());

                m_tlsInitiated = PR_TRUE;

                m_nextState = SMTP_RESPONSE;
                m_nextStateAfterResponse = SMTP_TLS_RESPONSE;
                SetFlag(SMTP_PAUSE_FOR_READ);
                return status;
            }
        }
        else if (m_prefTrySSL == PREF_SECURE_ALWAYS_STARTTLS)
        {
            m_nextState = SMTP_ERROR_DONE;
            m_urlErrorState = NS_ERROR_STARTTLS_FAILED_EHLO_STARTTLS;
            return NS_ERROR_COULD_NOT_LOGIN_TO_SMTP_SERVER;
        }
    }

    if (TestFlag(SMTP_AUTH_EXTERNAL_ENABLED))
    {
        buffer = "AUTH EXTERNAL =";
        buffer += CRLF;
        SendData(url, buffer.get());
        m_nextState = SMTP_RESPONSE;
        m_nextStateAfterResponse = SMTP_AUTH_EXTERNAL_RESPONSE;
        SetFlag(SMTP_PAUSE_FOR_READ);
        return NS_OK;
    }
    else
    if (m_prefAuthMethod == PREF_AUTH_ANY)
    {
        // did the server advertise authentication capability at all?
        if (!TestFlag(SMTP_AUTH))
        {
            m_nextState = SMTP_ERROR_DONE;
            m_urlErrorState = NS_ERROR_COULD_NOT_LOGIN_TO_SMTP_SERVER_AUTH_NONE;
            return NS_ERROR_COULD_NOT_LOGIN_TO_SMTP_SERVER;
        }

        /* check if the server supports at least one of the mechanisms
           in the class the user wants us to use */
        if (m_prefUseSecAuth)
        {
            if (!TestFlag(SMTP_AUTH_SEC_ENABLED))
                m_urlErrorState = NS_ERROR_COULD_NOT_LOGIN_TO_SMTP_SERVER_SECAUTH;
        }
        else
        {
            if (!TestFlag(SMTP_AUTH_INSEC_ENABLED))
                m_urlErrorState = NS_ERROR_COULD_NOT_LOGIN_TO_SMTP_SERVER_INSECAUTH;
        }

        if (m_urlErrorState != NS_ERROR_FAILURE)
        {
            m_nextState = SMTP_ERROR_DONE;
            return NS_ERROR_COULD_NOT_LOGIN_TO_SMTP_SERVER;
        }


        if (TestFlag(SMTP_AUTH_GSSAPI_ENABLED))
            m_nextState = SMTP_SEND_AUTH_GSSAPI_FIRST;
        else if (TestFlag(SMTP_AUTH_CRAM_MD5_ENABLED) ||
                 TestFlag(SMTP_AUTH_NTLM_ENABLED) ||
                 TestFlag(SMTP_AUTH_PLAIN_ENABLED))
            m_nextState = SMTP_SEND_AUTH_LOGIN_STEP1;
        else if (TestFlag(SMTP_AUTH_MSN_ENABLED) ||
                 TestFlag(SMTP_AUTH_LOGIN_ENABLED))
            m_nextState = SMTP_SEND_AUTH_LOGIN_STEP0;
    }
    else
    {
        m_nextState = SMTP_SEND_HELO_RESPONSE;
        // fake to 250 because SendHeloResponse() tests for this
        m_responseCode = 250;
    }

    return NS_OK;
}


void nsSmtpProtocol::BackupAuthFlags()
{
  m_origAuthFlags = m_flags & SMTP_AUTH_ANY_ENABLED;
}

void nsSmtpProtocol::RestoreAuthFlags()
{
  m_flags |= m_origAuthFlags;
}


PRInt32 nsSmtpProtocol::AuthLoginResponse(nsIInputStream * stream, PRUint32 length)
{
  PRInt32 status = 0;
  nsCOMPtr<nsISmtpServer> smtpServer;
  m_runningURL->GetSmtpServer(getter_AddRefs(smtpServer));

  switch (m_responseCode/100)
  {
    case 2:
      m_nextState = SMTP_SEND_HELO_RESPONSE;
      // fake to 250 because SendHeloResponse() tests for this
      m_responseCode = 250;
      break;
    case 3:
      m_nextState = SMTP_SEND_AUTH_LOGIN_STEP2;
      break;
    case 5:
    default:
      if (smtpServer)
      {
        // If one authentication failed, we're going to
        // fall back on a less secure login method.
        if(TestFlag(SMTP_AUTH_GSSAPI_ENABLED))
          ClearFlag(SMTP_AUTH_GSSAPI_ENABLED);
        else if(TestFlag(SMTP_AUTH_DIGEST_MD5_ENABLED))
          // if DIGEST-MD5 enabled, clear it if we failed.
          ClearFlag(SMTP_AUTH_DIGEST_MD5_ENABLED);
        else if(TestFlag(SMTP_AUTH_CRAM_MD5_ENABLED))
          // if CRAM-MD5 enabled, clear it if we failed.
          ClearFlag(SMTP_AUTH_CRAM_MD5_ENABLED);
        else if(TestFlag(SMTP_AUTH_NTLM_ENABLED))
          // if NTLM enabled, clear it if we failed.
          ClearFlag(SMTP_AUTH_NTLM_ENABLED);
        else if(TestFlag(SMTP_AUTH_MSN_ENABLED))
          // if MSN enabled, clear it if we failed.
          ClearFlag(SMTP_AUTH_MSN_ENABLED);
        else if(TestFlag(SMTP_AUTH_PLAIN_ENABLED))
          // if PLAIN enabled, clear it if we failed.
          ClearFlag(SMTP_AUTH_PLAIN_ENABLED);
        else if(TestFlag(SMTP_AUTH_LOGIN_ENABLED))
          // if LOGIN enabled, clear it if we failed.
          ClearFlag(SMTP_AUTH_LOGIN_ENABLED);

        // Only forget the password if we've no mechanism left.
        if (!TestFlag(SMTP_AUTH_ANY_ENABLED))
        {
          nsCOMPtr<nsISmtpServer> smtpServer;
          nsresult rv = m_runningURL->GetSmtpServer(getter_AddRefs(smtpServer));
          NS_ENSURE_SUCCESS(rv, rv);

          nsCString hostname;
          rv = smtpServer->GetHostname(hostname);
          NS_ENSURE_SUCCESS(rv, rv);

          PRInt32 buttonPressed = 0;
          if (NS_SUCCEEDED(MsgPromptLoginFailed(nsnull, hostname,
                                                &buttonPressed)))
          {
            if (buttonPressed == 1)
            {
              // Cancel button pressed, so we need to abort.
              status = NS_ERROR_FAILURE;

              // and just get out of here.
              break;
            }
            if (buttonPressed == 2)
            {
              // Change password was pressed. For now, forget the stored
              // password and we'll prompt for a new one next time around.
              smtpServer->ForgetPassword();
            }
          }
          if (m_usernamePrompted)
            smtpServer->SetUsername(EmptyCString());

          // Let's restore the original auth flags from SendEhloResponse
          // so we can try them again with new password and username
          RestoreAuthFlags();
          // except for gssapi, which doesn't care about the new password.
          ClearFlag(SMTP_AUTH_GSSAPI_ENABLED);
        }

        m_nextState = SMTP_AUTH_PROCESS_STATE;
      }
      else
          status = NS_ERROR_SMTP_PASSWORD_UNDEFINED;
      break;
  }

  return (status);
}

// GSSAPI may consist of multiple round trips

PRInt32 nsSmtpProtocol::AuthGSSAPIFirst()
{
  nsCAutoString command("AUTH GSSAPI ");
  nsCAutoString resp;
  nsCAutoString service("smtp@");
  nsCString hostName;
  nsCString userName;
  nsresult rv;
  nsCOMPtr<nsISmtpServer> smtpServer;
  rv = m_runningURL->GetSmtpServer(getter_AddRefs(smtpServer));
  if (NS_FAILED(rv))
    return NS_ERROR_FAILURE;

  rv = smtpServer->GetUsername(userName);
  if (NS_FAILED(rv))
    return NS_ERROR_FAILURE;

  rv = smtpServer->GetHostname(hostName);
  if (NS_FAILED(rv))
    return NS_ERROR_FAILURE;

 service.Append(hostName);
  rv = DoGSSAPIStep1(service.get(), userName.get(), resp);
  if (NS_FAILED(rv))
  {
    m_nextState = SMTP_AUTH_PROCESS_STATE;
    ClearFlag(SMTP_AUTH_GSSAPI_ENABLED);
    return 0;
  }
  else
    command.Append(resp);
  command.Append(CRLF);
  m_nextState = SMTP_RESPONSE;
  m_nextStateAfterResponse = SMTP_SEND_AUTH_GSSAPI_STEP;
  SetFlag(SMTP_PAUSE_FOR_READ);
  nsCOMPtr<nsIURI> url = do_QueryInterface(m_runningURL);
  return SendData(url, command.get());
}

PRInt32 nsSmtpProtocol::AuthGSSAPIStep()
{
  nsresult rv;
  nsCAutoString cmd;

  // Check to see what the server said
  if (m_responseCode / 100 != 3) {
    m_nextState = SMTP_AUTH_LOGIN_RESPONSE;
    return 0;
  }

  rv = DoGSSAPIStep2(m_responseText, cmd);
  if (NS_FAILED(rv))
    cmd = "*";
  cmd += CRLF;

  m_nextStateAfterResponse = (rv == NS_SUCCESS_AUTH_FINISHED)?SMTP_AUTH_LOGIN_RESPONSE:SMTP_SEND_AUTH_GSSAPI_STEP;
  m_nextState = SMTP_RESPONSE;
  SetFlag(SMTP_PAUSE_FOR_READ);

  nsCOMPtr<nsIURI> url = do_QueryInterface(m_runningURL);
  return SendData(url, cmd.get());
}


// LOGIN and MSN consist of three steps (MSN not through the mechanism
// but by non-RFC2821 compliant implementation in MS servers) not two as
// PLAIN or CRAM-MD5, so we've to start here and continue with AuthStep1
// if the server responds with with a 3xx code to "AUTH LOGIN" or "AUTH MSN"
PRInt32 nsSmtpProtocol::AuthLoginStep0()
{
    nsCAutoString command(TestFlag(SMTP_AUTH_MSN_ENABLED) ? "AUTH MSN" CRLF :
                                                            "AUTH LOGIN" CRLF);
    m_nextState = SMTP_RESPONSE;
    m_nextStateAfterResponse = SMTP_AUTH_LOGIN_STEP0_RESPONSE;
    SetFlag(SMTP_PAUSE_FOR_READ);

    return SendData(m_url, command.get());
}

PRInt32 nsSmtpProtocol::AuthLoginStep0Response()
{
    // need the test to be here instead in AuthLoginResponse() to
    // continue with step 1 instead of 2 in case of a code 3xx
    m_nextState = (m_responseCode/100 == 3) ?
                  SMTP_SEND_AUTH_LOGIN_STEP1 : SMTP_AUTH_LOGIN_RESPONSE;

    return 0;
}

PRInt32 nsSmtpProtocol::AuthLoginStep1()
{
  char buffer[512];
  nsresult rv;
  PRInt32 status = 0;
  nsCString username;
  char *base64Str = nsnull;
  nsCAutoString password;
  nsCOMPtr<nsISmtpServer> smtpServer;
  rv = m_runningURL->GetSmtpServer(getter_AddRefs(smtpServer));
  if (NS_FAILED(rv)) return NS_ERROR_FAILURE;

  rv = smtpServer->GetUsername(username);
  if (username.IsEmpty())
  {
    rv = GetUsernamePassword(username, password);
    m_usernamePrompted = PR_TRUE;
    if (username.IsEmpty() || password.IsEmpty())
      return NS_ERROR_SMTP_PASSWORD_UNDEFINED;
  }

  GetPassword(password);
  if (password.IsEmpty())
  {
    m_urlErrorState = NS_ERROR_SMTP_PASSWORD_UNDEFINED;
    return NS_ERROR_SMTP_PASSWORD_UNDEFINED;
  }

  if (TestFlag(SMTP_AUTH_CRAM_MD5_ENABLED))
    PR_snprintf(buffer, sizeof(buffer), "AUTH CRAM-MD5" CRLF);
  else
  if (TestFlag(SMTP_AUTH_NTLM_ENABLED) || TestFlag(SMTP_AUTH_MSN_ENABLED))
  {
    nsCAutoString response;
    rv = DoNtlmStep1(username.get(), password.get(), response);
    PR_snprintf(buffer, sizeof(buffer), TestFlag(SMTP_AUTH_NTLM_ENABLED) ?
                                        "AUTH NTLM %.256s" CRLF :
                                        "%.256s" CRLF, response.get());
  }
  else
  if (TestFlag(SMTP_AUTH_PLAIN_ENABLED))
  {
    char plain_string[512];
    int len = 1; /* first <NUL> char */

    memset(plain_string, 0, 512);
    PR_snprintf(&plain_string[1], 510, "%s", username.get());
    len += username.Length();
    len++; /* second <NUL> char */
    PR_snprintf(&plain_string[len], 511-len, "%s", password.get());
    len += password.Length();

    base64Str = PL_Base64Encode(plain_string, len, nsnull);
    PR_snprintf(buffer, sizeof(buffer), "AUTH PLAIN %.256s" CRLF, base64Str);
  }
  else
  if (TestFlag(SMTP_AUTH_LOGIN_ENABLED))
  {
    base64Str = PL_Base64Encode(username.get(),
        username.Length(), nsnull);
    PR_snprintf(buffer, sizeof(buffer), "%.256s" CRLF, base64Str);
  }
  else
    return (NS_ERROR_COMMUNICATIONS_ERROR);

  nsCOMPtr<nsIURI> url = do_QueryInterface(m_runningURL);
  status = SendData(url, buffer, PR_TRUE);
  m_nextState = SMTP_RESPONSE;
  m_nextStateAfterResponse = SMTP_AUTH_LOGIN_RESPONSE;
  SetFlag(SMTP_PAUSE_FOR_READ);
  NS_Free(base64Str);

  return (status);
}

PRInt32 nsSmtpProtocol::AuthLoginStep2()
{
  /* use cached smtp password first
  * if not then use cached pop password
  * if pop password undefined
  * sync with smtp password
  */
  PRInt32 status = 0;
  nsresult rv;
  nsCAutoString password;

  GetPassword(password);
  if (password.IsEmpty())
  {
    m_urlErrorState = NS_ERROR_SMTP_PASSWORD_UNDEFINED;
    return NS_ERROR_SMTP_PASSWORD_UNDEFINED;
  }

  if (!password.IsEmpty())
  {
    char buffer[512];
    if (TestFlag(SMTP_AUTH_CRAM_MD5_ENABLED))
    {
      unsigned char digest[DIGEST_LENGTH];
      char * decodedChallenge = PL_Base64Decode(m_responseText.get(),
        m_responseText.Length(), nsnull);

      if (decodedChallenge)
        rv = MSGCramMD5(decodedChallenge, strlen(decodedChallenge), password.get(), password.Length(), digest);
      else
        rv = NS_ERROR_FAILURE;

      PR_Free(decodedChallenge);
      if (NS_SUCCEEDED(rv) && digest)
      {
        nsCAutoString encodedDigest;
        char hexVal[8];

        for (PRUint32 j=0; j<16; j++)
        {
          PR_snprintf (hexVal,8, "%.2x", 0x0ff & (unsigned short)digest[j]);
          encodedDigest.Append(hexVal);
        }

        nsCOMPtr<nsISmtpServer> smtpServer;
        rv = m_runningURL->GetSmtpServer(getter_AddRefs(smtpServer));
        if (NS_FAILED(rv)) return NS_ERROR_FAILURE;

        nsCString userName;
        rv = smtpServer->GetUsername(userName);

        PR_snprintf(buffer, sizeof(buffer), "%s %s", userName.get(), encodedDigest.get());
        char *base64Str = PL_Base64Encode(buffer, strlen(buffer), nsnull);
        PR_snprintf(buffer, sizeof(buffer), "%s" CRLF, base64Str);
        NS_Free(base64Str);
      }
      if (NS_FAILED(rv))
        PR_snprintf(buffer, sizeof(buffer), "*" CRLF);
    }
    else
    if (TestFlag(SMTP_AUTH_NTLM_ENABLED) || TestFlag(SMTP_AUTH_MSN_ENABLED))
    {
      nsCAutoString response;
      rv = DoNtlmStep2(m_responseText, response);
      PR_snprintf(buffer, sizeof(buffer), "%.256s" CRLF, response.get());
    }
    else
    {
      char *base64Str = PL_Base64Encode(password.get(), password.Length(), nsnull);
      PR_snprintf(buffer, sizeof(buffer), "%.256s" CRLF, base64Str);
      NS_Free(base64Str);
    }

    nsCOMPtr<nsIURI> url = do_QueryInterface(m_runningURL);
    status = SendData(url, buffer, PR_TRUE);
    m_nextState = SMTP_RESPONSE;
    m_nextStateAfterResponse = SMTP_AUTH_LOGIN_RESPONSE;
    SetFlag(SMTP_PAUSE_FOR_READ);
    return (status);
  }

  return -1;
}


PRInt32 nsSmtpProtocol::SendMailResponse()
{
  PRInt32 status = 0;
  nsCAutoString buffer;
  nsresult rv;

  if (m_responseCode/10 != 25)
  {
    int errorcode;
    if (TestFlag(SMTP_EHLO_SIZE_ENABLED))
      errorcode = (m_responseCode == 452) ? NS_ERROR_SMTP_TEMP_SIZE_EXCEEDED :
                  (m_responseCode == 552) ? NS_ERROR_SMTP_PERM_SIZE_EXCEEDED_2 :
                  NS_ERROR_SENDING_FROM_COMMAND;
    else
      errorcode = NS_ERROR_SENDING_FROM_COMMAND;

    rv = nsExplainErrorDetails(m_runningURL, errorcode, m_responseText.get());
    NS_ASSERTION(NS_SUCCEEDED(rv), "failed to explain SMTP error");

    m_urlErrorState = NS_ERROR_BUT_DONT_SHOW_ALERT;
    return(NS_ERROR_SENDING_FROM_COMMAND);
  }

  /* Send the RCPT TO: command */
  PRBool requestDSN = PR_FALSE;
  rv = m_runningURL->GetRequestDSN(&requestDSN);

  nsCOMPtr <nsIPrefService> prefs = do_GetService(NS_PREFSERVICE_CONTRACTID, &rv);
  NS_ENSURE_SUCCESS(rv,rv);

  nsCOMPtr<nsIPrefBranch> prefBranch;
  rv = prefs->GetBranch(nsnull, getter_AddRefs(prefBranch));
  NS_ENSURE_SUCCESS(rv,rv);

  PRBool requestOnSuccess = PR_FALSE;
  rv = prefBranch->GetBoolPref("mail.dsn.request_on_success_on", &requestOnSuccess);

  PRBool requestOnFailure = PR_FALSE;
  rv = prefBranch->GetBoolPref("mail.dsn.request_on_failure_on", &requestOnFailure);

  PRBool requestOnDelay = PR_FALSE;
  rv = prefBranch->GetBoolPref("mail.dsn.request_on_delay_on", &requestOnDelay);

  PRBool requestOnNever = PR_FALSE;
  rv = prefBranch->GetBoolPref("mail.dsn.request_never_on", &requestOnNever);

  if (TestFlag(SMTP_EHLO_DSN_ENABLED) && requestDSN && (requestOnSuccess || requestOnFailure || requestOnDelay || requestOnNever))
    {
      char *encodedAddress = esmtp_value_encode(m_addresses);
      nsCAutoString dsnBuffer;

      if (encodedAddress)
      {
        buffer = "RCPT TO:<";
        buffer += m_addresses;
        buffer += "> NOTIFY=";

        if (requestOnNever)
          dsnBuffer += "NEVER";
        else
        {
          if (requestOnSuccess)
            dsnBuffer += "SUCCESS";

          if (requestOnFailure)
            dsnBuffer += dsnBuffer.IsEmpty() ? "FAILURE" : ",FAILURE";

          if (requestOnDelay)
            dsnBuffer += dsnBuffer.IsEmpty() ? "DELAY" : ",DELAY";
        }

        buffer += dsnBuffer;
        buffer += " ORCPT=rfc822;";
        buffer += encodedAddress;
        buffer += CRLF;
        PR_FREEIF(encodedAddress);
      }
      else
      {
        m_urlErrorState = NS_ERROR_OUT_OF_MEMORY;
        return (NS_ERROR_OUT_OF_MEMORY);
      }
    }
    else
    {
      buffer = "RCPT TO:<";
      buffer += m_addresses;
      buffer += ">";
      buffer += CRLF;
    }
    nsCOMPtr<nsIURI> url = do_QueryInterface(m_runningURL);
    status = SendData(url, buffer.get());

    m_nextState = SMTP_RESPONSE;
    m_nextStateAfterResponse = SMTP_SEND_RCPT_RESPONSE;
    SetFlag(SMTP_PAUSE_FOR_READ);

    return(status);
}

PRInt32 nsSmtpProtocol::SendRecipientResponse()
{
  PRInt32 status = 0;
  nsCAutoString buffer;
  nsresult rv;

  if (m_responseCode / 10 != 25)
  {
    int errorcode;
    if (TestFlag(SMTP_EHLO_SIZE_ENABLED))
      errorcode = (m_responseCode == 452) ? NS_ERROR_SMTP_TEMP_SIZE_EXCEEDED :
                  (m_responseCode == 552) ? NS_ERROR_SMTP_PERM_SIZE_EXCEEDED_2 :
                  NS_ERROR_SENDING_RCPT_COMMAND;
    else
      errorcode = NS_ERROR_SENDING_RCPT_COMMAND;

    rv = nsExplainErrorDetails(m_runningURL, errorcode,
                               m_responseText.get(), m_addresses);
    NS_ASSERTION(NS_SUCCEEDED(rv), "failed to explain SMTP error");

    m_urlErrorState = NS_ERROR_BUT_DONT_SHOW_ALERT;
    return(NS_ERROR_SENDING_RCPT_COMMAND);
  }

  /* take the address we sent off the list (move the pointer to just
     past the terminating null.) */
  m_addresses += PL_strlen (m_addresses) + 1;
  if (--m_addressesLeft > 0)
  {
    // more senders to RCPT to
    // fake to 250 because SendMailResponse() can't handle 251
    m_responseCode = 250;
    m_nextState = SMTP_SEND_MAIL_RESPONSE;
    return(0);
  }

  /* else send the DATA command */
  buffer = "DATA";
  buffer += CRLF;
  nsCOMPtr<nsIURI> url = do_QueryInterface(m_runningURL);
  status = SendData(url, buffer.get());

  m_nextState = SMTP_RESPONSE;
  m_nextStateAfterResponse = SMTP_SEND_DATA_RESPONSE;
  SetFlag(SMTP_PAUSE_FOR_READ);

  return(status);
}


PRInt32 nsSmtpProtocol::SendData(nsIURI *url, const char *dataBuffer, PRBool aSuppressLogging)
{
  if (!dataBuffer) return -1;

  if (!aSuppressLogging) {
      PR_LOG(SMTPLogModule, PR_LOG_ALWAYS, ("SMTP Send: %s", dataBuffer));
  } else {
      PR_LOG(SMTPLogModule, PR_LOG_ALWAYS, ("Logging suppressed for this command (it probably contained authentication information)"));
  }
  return nsMsgAsyncWriteProtocol::SendData(url, dataBuffer);
}


PRInt32 nsSmtpProtocol::SendDataResponse()
{
  PRInt32 status = 0;
  char *command = nsnull;

  if (m_responseCode != 354)
  {
    nsresult rv = nsExplainErrorDetails(m_runningURL, NS_ERROR_SENDING_DATA_COMMAND, m_responseText.get());
    NS_ASSERTION(NS_SUCCEEDED(rv), "failed to explain SMTP error");

    m_urlErrorState = NS_ERROR_BUT_DONT_SHOW_ALERT;
    return(NS_ERROR_SENDING_DATA_COMMAND);
  }

  PR_FREEIF(command);

  m_nextState = SMTP_SEND_POST_DATA;
  ClearFlag(SMTP_PAUSE_FOR_READ);   /* send data directly */

  UpdateStatus(SMTP_DELIV_MAIL);

  {
//      m_runningURL->GetBodySize(&m_totalMessageSize);
  }
  return(status);
}

PRInt32 nsSmtpProtocol::SendMessageInFile()
{
  nsCOMPtr<nsIFile> file;
  nsCOMPtr<nsIURI> url = do_QueryInterface(m_runningURL);
  m_runningURL->GetPostMessageFile(getter_AddRefs(file));
  if (url && file)
    // need to fully qualify to avoid getting overwritten by a #define
    // in some windows header file
    nsMsgAsyncWriteProtocol::PostMessage(url, file);

  SetFlag(SMTP_PAUSE_FOR_READ);

  // for now, we are always done at this point..we aren't making multiple calls
  // to post data...

  UpdateStatus(SMTP_DELIV_MAIL);
  m_nextState = SMTP_RESPONSE;
  m_nextStateAfterResponse = SMTP_SEND_MESSAGE_RESPONSE;
  return(0);
}

PRInt32 nsSmtpProtocol::SendPostData()
{
	// mscott: as a first pass, I'm writing everything at once and am not
	// doing it in chunks...

    PRInt32 status = 0;

	/* returns 0 on done and negative on error
	 * positive if it needs to continue.
	 */

	// check to see if url is a file..if it is...call our file handler...
	PRBool postMessageInFile = PR_TRUE;
	m_runningURL->GetPostMessage(&postMessageInFile);
	if (postMessageInFile)
	{
		return SendMessageInFile();
	}

	/* Update the thermo and the status bar.  This is done by hand, rather
	   than using the FE_GraphProgress* functions, because there seems to be
	   no way to make FE_GraphProgress shut up and not display anything more
	   when all the data has arrived.  At the end, we want to show the
	   "message sent; waiting for reply" status; FE_GraphProgress gets in
	   the way of that.  See bug #23414. */

    return(status);
}



PRInt32 nsSmtpProtocol::SendMessageResponse()
{
  if((m_responseCode/10 != 25))
  {
    nsresult rv = nsExplainErrorDetails(m_runningURL, NS_ERROR_SENDING_MESSAGE, m_responseText.get());
    NS_ASSERTION(NS_SUCCEEDED(rv), "failed to explain SMTP error");

    m_urlErrorState = NS_ERROR_BUT_DONT_SHOW_ALERT;
    return(NS_ERROR_SENDING_MESSAGE);
  }

  UpdateStatus(SMTP_PROGRESS_MAILSENT);

  /* else */
  return SendQuit();
}

PRInt32 nsSmtpProtocol::SendQuit()
{
  m_sendDone = PR_TRUE;
  nsCOMPtr<nsIURI> url = do_QueryInterface(m_runningURL);
  SendData(url, "QUIT"CRLF); // send a quit command to close the connection with the server.
  m_nextState = SMTP_RESPONSE;
  m_nextStateAfterResponse = SMTP_DONE;
  return(0);
}

nsresult nsSmtpProtocol::LoadUrl(nsIURI * aURL, nsISupports * aConsumer )
{
  if (!aURL)
    return NS_OK;

  Initialize(aURL);

  m_continuationResponse = -1;  /* init */
  m_runningURL = do_QueryInterface(aURL);
  if (!m_runningURL)
    return NS_ERROR_FAILURE;

  // we had a bug where we failed to bring up an alert if the host
  // name was empty....so throw up an alert saying we don't have
  // a host name and inform the caller that we are not going to
  // run the url...
  nsCAutoString hostName;
  aURL->GetHost(hostName);
  if (hostName.IsEmpty())
  {
    nsCOMPtr <nsIMsgMailNewsUrl> aMsgUrl = do_QueryInterface(aURL);
    if (aMsgUrl)
    {
      aMsgUrl->SetUrlState(PR_TRUE, NS_OK);
      // set the url as a url currently being run...
      aMsgUrl->SetUrlState(PR_FALSE /* we aren't running the url */,
                           NS_ERROR_COULD_NOT_LOGIN_TO_SMTP_SERVER); 
    }
    return NS_ERROR_BUT_DONT_SHOW_ALERT;
  }

  PRBool postMessage = PR_FALSE;
  m_runningURL->GetPostMessage(&postMessage);

  if (postMessage)
  {
    nsCString addrs1;
    char *addrs2 = 0;
    m_nextState = SMTP_RESPONSE;
    m_nextStateAfterResponse = SMTP_EXTN_LOGIN_RESPONSE;

    // Remove duplicates from the list, to prevent people from getting
    // more than one copy (the SMTP host may do this too, or it may not.)
    // This causes the address list to be parsed twice; this probably
    // doesn't matter.
    nsCString addresses;
    nsCOMPtr<nsIMsgHeaderParser> parser =
      do_GetService(NS_MAILNEWS_MIME_HEADER_PARSER_CONTRACTID);

    m_runningURL->GetRecipients(getter_Copies(addresses));

    if (parser)
    {
      parser->RemoveDuplicateAddresses(addresses, EmptyCString(), addrs1);

      // Extract just the mailboxes from the full RFC822 address list.
      // This means that people can post to mailto: URLs which contain
      // full RFC822 address specs, and we will still send the right
      // thing in the SMTP RCPT command.
      if (!addrs1.IsEmpty())
        parser->ParseHeaderAddresses(addrs1.get(), nsnull, &addrs2,
                                     &m_addressesLeft);

      // hmm no addresses to send message to...
      if (m_addressesLeft == 0 || !addrs2)
      {
        m_nextState = SMTP_ERROR_DONE;
        ClearFlag(SMTP_PAUSE_FOR_READ);
        m_urlErrorState = NS_MSG_NO_RECIPIENTS;
        return NS_MSG_NO_RECIPIENTS;
      }

      m_addressCopy = addrs2;
      m_addresses = m_addressCopy;
    } // if parser
  } // if post message

  return nsMsgProtocol::LoadUrl(aURL, aConsumer);
}

/*
 * returns negative if the transfer is finished or error'd out
 *
 * returns zero or more if the transfer needs to be continued.
 */
 nsresult nsSmtpProtocol::ProcessProtocolState(nsIURI * url, nsIInputStream * inputStream,
   PRUint32 sourceOffset, PRUint32 length)
 {
   PRInt32 status = 0;
   ClearFlag(SMTP_PAUSE_FOR_READ); /* already paused; reset */

   while(!TestFlag(SMTP_PAUSE_FOR_READ))
   {
     PR_LOG(SMTPLogModule, PR_LOG_ALWAYS, ("SMTP entering state: %d",
       m_nextState));
     switch(m_nextState)
     {
     case SMTP_RESPONSE:
       if (inputStream == nsnull)
         SetFlag(SMTP_PAUSE_FOR_READ);
       else
         status = SmtpResponse(inputStream, length);
       break;

     case SMTP_START_CONNECT:
       SetFlag(SMTP_PAUSE_FOR_READ);
       m_nextState = SMTP_RESPONSE;
       m_nextStateAfterResponse = SMTP_EXTN_LOGIN_RESPONSE;
       break;
     case SMTP_FINISH_CONNECT:
       SetFlag(SMTP_PAUSE_FOR_READ);
       break;
     case SMTP_TLS_RESPONSE:
       if (inputStream == nsnull)
         SetFlag(SMTP_PAUSE_FOR_READ);
       else
         status = SendTLSResponse();
       break;
     case SMTP_EXTN_LOGIN_RESPONSE:
       if (inputStream == nsnull)
         SetFlag(SMTP_PAUSE_FOR_READ);
       else
         status = ExtensionLoginResponse(inputStream, length);
       break;

     case SMTP_SEND_HELO_RESPONSE:
       if (inputStream == nsnull)
         SetFlag(SMTP_PAUSE_FOR_READ);
       else
         status = SendHeloResponse(inputStream, length);
       break;
     case SMTP_SEND_EHLO_RESPONSE:
       if (inputStream == nsnull)
         SetFlag(SMTP_PAUSE_FOR_READ);
       else
         status = SendEhloResponse(inputStream, length);
       break;
     case SMTP_AUTH_PROCESS_STATE:
       status = ProcessAuth();
       break;

      case SMTP_SEND_AUTH_GSSAPI_FIRST:
        status = AuthGSSAPIFirst();
        break;

      case SMTP_SEND_AUTH_GSSAPI_STEP:
        status = AuthGSSAPIStep();
        break;

      case SMTP_SEND_AUTH_LOGIN_STEP0:
        status = AuthLoginStep0();
        break;

      case SMTP_AUTH_LOGIN_STEP0_RESPONSE:
        status = AuthLoginStep0Response();
        break;

      case SMTP_AUTH_EXTERNAL_RESPONSE:
      case SMTP_AUTH_LOGIN_RESPONSE:
        if (inputStream == nsnull)
          SetFlag(SMTP_PAUSE_FOR_READ);
        else
          status = AuthLoginResponse(inputStream, length);
        break;

      case SMTP_SEND_AUTH_LOGIN_STEP1:
        status = AuthLoginStep1();
        break;

      case SMTP_SEND_AUTH_LOGIN_STEP2:
        status = AuthLoginStep2();
        break;


      case SMTP_SEND_MAIL_RESPONSE:
        if (inputStream == nsnull)
          SetFlag(SMTP_PAUSE_FOR_READ);
        else
          status = SendMailResponse();
        break;

      case SMTP_SEND_RCPT_RESPONSE:
        if (inputStream == nsnull)
          SetFlag(SMTP_PAUSE_FOR_READ);
        else
          status = SendRecipientResponse();
        break;

      case SMTP_SEND_DATA_RESPONSE:
        if (inputStream == nsnull)
          SetFlag(SMTP_PAUSE_FOR_READ);
        else
          status = SendDataResponse();
        break;

      case SMTP_SEND_POST_DATA:
        status = SendPostData();
        break;

      case SMTP_SEND_MESSAGE_RESPONSE:
        if (inputStream == nsnull)
          SetFlag(SMTP_PAUSE_FOR_READ);
        else
          status = SendMessageResponse();
        break;
      case SMTP_DONE:
        {
          nsCOMPtr <nsIMsgMailNewsUrl> mailNewsUrl = do_QueryInterface(m_runningURL);
          mailNewsUrl->SetUrlState(PR_FALSE, NS_OK);
        }

        m_nextState = SMTP_FREE;
        break;

      case SMTP_ERROR_DONE:
        {
          nsCOMPtr <nsIMsgMailNewsUrl> mailNewsUrl = do_QueryInterface(m_runningURL);
          // propagate the right error code
          mailNewsUrl->SetUrlState(PR_FALSE, m_urlErrorState);
        }

        m_nextState = SMTP_FREE;
        break;

      case SMTP_FREE:
        // smtp is a one time use connection so kill it if we get here...
        nsMsgAsyncWriteProtocol::CloseSocket();
        return NS_OK; /* final end */

      default: /* should never happen !!! */
        m_nextState = SMTP_ERROR_DONE;
        break;
    }

    /* check for errors during load and call error
    * state if found
    */
    if(status < 0 && m_nextState != SMTP_FREE)
    {
      nsCOMPtr<nsIURI> url = do_QueryInterface(m_runningURL);
      // send a quit command to close the connection with the server.
      if (SendData(url, "QUIT"CRLF) == NS_OK)
      {
        m_nextState = SMTP_RESPONSE;
        m_nextStateAfterResponse = SMTP_ERROR_DONE;
      }
      else
      {
      m_nextState = SMTP_ERROR_DONE;
      /* don't exit! loop around again and do the free case */
      ClearFlag(SMTP_PAUSE_FOR_READ);
    }
    }
  } /* while(!SMTP_PAUSE_FOR_READ) */

  return NS_OK;
}

nsresult
nsSmtpProtocol::GetPassword(nsCString &aPassword)
{
    nsresult rv;
    nsCOMPtr<nsISmtpUrl> smtpUrl = do_QueryInterface(m_runningURL, &rv);
    NS_ENSURE_SUCCESS(rv,rv);

    nsCOMPtr<nsISmtpServer> smtpServer;
    rv = smtpUrl->GetSmtpServer(getter_AddRefs(smtpServer));
    NS_ENSURE_SUCCESS(rv,rv);

    rv = smtpServer->GetPassword(aPassword);
    NS_ENSURE_SUCCESS(rv,rv);

    if (!aPassword.IsEmpty())
        return rv;
    // empty password

    nsCOMPtr <nsIPrefService> prefs = do_GetService(NS_PREFSERVICE_CONTRACTID, &rv);
    NS_ENSURE_SUCCESS(rv,rv);

    nsCOMPtr<nsIPrefBranch> prefBranch;
    rv = prefs->GetBranch(nsnull, getter_AddRefs(prefBranch));
    NS_ENSURE_SUCCESS(rv,rv);

    nsCString username;
    rv = smtpServer->GetUsername(username);
    NS_ENSURE_SUCCESS(rv, rv);

    NS_ConvertASCIItoUTF16 usernameUTF16(username);

    nsCString hostname;
    rv = smtpServer->GetHostname(hostname);
    NS_ENSURE_SUCCESS(rv, rv);

    nsAutoString hostnameUTF16;
    CopyASCIItoUTF16(hostname, hostnameUTF16);

    const PRUnichar *formatStrings[] =
    {
      hostnameUTF16.get(),
      usernameUTF16.get()
    };

    rv = PromptForPassword(smtpServer, smtpUrl, formatStrings, aPassword);
    NS_ENSURE_SUCCESS(rv,rv);
    return rv;
}

/**
 * formatStrings is an array for the prompts, item 0 is the hostname, item 1
 * is the username.
 */
nsresult
nsSmtpProtocol::PromptForPassword(nsISmtpServer *aSmtpServer, nsISmtpUrl *aSmtpUrl, const PRUnichar **formatStrings, nsACString &aPassword)
{
  nsresult rv;
  nsCOMPtr<nsIStringBundleService> stringService = do_GetService(NS_STRINGBUNDLE_CONTRACTID, &rv);
  NS_ENSURE_SUCCESS(rv,rv);

  nsCOMPtr<nsIStringBundle> composeStringBundle;
  rv = stringService->CreateBundle("chrome://messenger/locale/messengercompose/composeMsgs.properties", getter_AddRefs(composeStringBundle));
  NS_ENSURE_SUCCESS(rv,rv);

  nsString passwordPromptString;
  if(formatStrings[1])
    rv = composeStringBundle->FormatStringFromName(
      NS_LITERAL_STRING("smtpEnterPasswordPromptWithUsername").get(),
      formatStrings, 2, getter_Copies(passwordPromptString));
  else
    rv = composeStringBundle->FormatStringFromName(
      NS_LITERAL_STRING("smtpEnterPasswordPrompt").get(),
      formatStrings, 1, getter_Copies(passwordPromptString));
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsIAuthPrompt> netPrompt;
  rv = aSmtpUrl->GetAuthPrompt(getter_AddRefs(netPrompt));
  NS_ENSURE_SUCCESS(rv, rv);

  nsString passwordTitle;
  rv = composeStringBundle->GetStringFromName(
    NS_LITERAL_STRING("smtpEnterPasswordPromptTitle").get(),
    getter_Copies(passwordTitle));
  NS_ENSURE_SUCCESS(rv,rv);

  rv = aSmtpServer->GetPasswordWithUI(passwordPromptString.get(), passwordTitle.get(),
    netPrompt, aPassword);
  NS_ENSURE_SUCCESS(rv,rv);
  return rv;
}

nsresult
nsSmtpProtocol::GetUsernamePassword(nsACString &aUsername,
                                    nsACString &aPassword)
{
    nsresult rv;
    nsCOMPtr<nsISmtpUrl> smtpUrl = do_QueryInterface(m_runningURL, &rv);
    NS_ENSURE_SUCCESS(rv,rv);

    nsCOMPtr<nsISmtpServer> smtpServer;
    rv = smtpUrl->GetSmtpServer(getter_AddRefs(smtpServer));
    NS_ENSURE_SUCCESS(rv,rv);

    rv = smtpServer->GetPassword(aPassword);
    NS_ENSURE_SUCCESS(rv,rv);

    if (!aPassword.IsEmpty())
    {
        rv = smtpServer->GetUsername(aUsername);
        NS_ENSURE_SUCCESS(rv,rv);

        if (!aUsername.IsEmpty())
          return rv;
    }
    // empty password

    aPassword.Truncate();

    nsCString hostname;
    rv = smtpServer->GetHostname(hostname);
    NS_ENSURE_SUCCESS(rv, rv);

    const PRUnichar *formatStrings[] =
    {
      NS_ConvertASCIItoUTF16(hostname).get(),
      nsnull
    };

    rv = PromptForPassword(smtpServer, smtpUrl, formatStrings, aPassword);
    NS_ENSURE_SUCCESS(rv,rv);
    return rv;
}
