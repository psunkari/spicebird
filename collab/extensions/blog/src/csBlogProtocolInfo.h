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
 * The Original Code is Spicebird code.
 *
 * The Initial Developer of the Original Code is
 * Synovel Software Technologies
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Sunil Mohan Adapa <sunil@synovel.com>, original author
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
#ifndef __CS_BLOGPROTOCOLINFO_H__
#define __CS_BLOGPROTOCOLINFO_H__

#include "nsIMsgProtocolInfo.h"

#define CS_BLOGPROTOCOLINFO_CONTRACTID                \
        NS_MSGPROTOCOLINFO_CONTRACTID_PREFIX "blog"

#define CS_BLOGPROTOCOLINFO_CID                       \
  { /* "{905cfb30-f5c4-4b5e-ae15-47cfb9ff332b}" */    \
    0x905cfb30, 0xf5c4, 0x4b5e,                       \
    { 0xae, 0x15, 0x47, 0xcf, 0xb9, 0xff, 0x33, 0x2b }}

#define CS_BLOGPROTOCOLINFO_DESC                      \
  "Provider for Blog Protocol Info"

class csBlogProtocolInfo : public nsIMsgProtocolInfo
{
public:

    csBlogProtocolInfo();
    virtual ~csBlogProtocolInfo();

    NS_DECL_ISUPPORTS
    NS_DECL_NSIMSGPROTOCOLINFO
};

#endif /* __CS_BLOGPROTOCOLINFO_H__ */
