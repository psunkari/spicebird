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
 * The Original Code is Thunderbird.
 *
 * The Initial Developer of the Original Code is
 * IBM Corporation.
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *  Brian Ryner <bryner@brianryner.com>
 *  Asaf Romano <mozilla.mano@sent.com>
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
#include "nsMailMigrationCID.h"
#include "csCollabMigrationCID.h"
#include "csProfileMigrator.h"
#include "nsSeamonkeyProfileMigrator.h"
#include "csThunderbirdProfileMigrator.h"

#if !defined(XP_BEOS)
#include "nsDogbertProfileMigrator.h"
#endif

NS_GENERIC_FACTORY_CONSTRUCTOR(csProfileMigrator)
NS_GENERIC_FACTORY_CONSTRUCTOR(nsSeamonkeyProfileMigrator)
NS_GENERIC_FACTORY_CONSTRUCTOR(csThunderbirdProfileMigrator)

#if !defined(XP_BEOS)
NS_GENERIC_FACTORY_CONSTRUCTOR(nsDogbertProfileMigrator)
#endif

#ifdef XP_WIN32

#include "nsOEProfileMigrator.h"
NS_GENERIC_FACTORY_CONSTRUCTOR(nsOEProfileMigrator)

#include "nsOutlookProfileMigrator.h"
NS_GENERIC_FACTORY_CONSTRUCTOR(nsOutlookProfileMigrator)

#include "csWindowsIntegration.h"
NS_GENERIC_FACTORY_CONSTRUCTOR_INIT(nsWindowsShellService, Init)
#endif

#if defined(XP_WIN32) || defined(XP_MACOSX)
#include "nsEudoraProfileMigrator.h"
NS_GENERIC_FACTORY_CONSTRUCTOR(nsEudoraProfileMigrator)
#endif
#ifdef MOZ_WIDGET_GTK2
#include "csGNOMEIntegration.h"
NS_GENERIC_FACTORY_CONSTRUCTOR_INIT(nsMailGNOMEIntegration, Init)
#endif
#ifdef XP_MACOSX
#include "csMacIntegration.h"
NS_GENERIC_FACTORY_CONSTRUCTOR(nsMailMacIntegration)
#endif

#if defined(XP_WIN32) && !defined(MOZ_DISABLE_VISTA_SDK_REQUIREMENTS)
#include "nsMailWinSearchHelper.h"
NS_GENERIC_FACTORY_CONSTRUCTOR_INIT(nsMailWinSearchHelper, Init)
#endif

static const nsModuleComponentInfo components[] = {
  { "Profile Importer",
    NS_SPICEBIRD_PROFILEIMPORT_CID,
    NS_PROFILEMIGRATOR_CONTRACTID,
    csProfileMigratorConstructor },
  { "Thunderbird Profile Migrator",
    CS_THUNDERBIRDPROFILEMIGRATOR_CID,
    NS_MAILPROFILEMIGRATOR_CONTRACTID_PREFIX "thunderbird",
    csThunderbirdProfileMigratorConstructor},
  { "Seamonkey Profile Migrator",
    NS_SEAMONKEYPROFILEMIGRATOR_CID,
    NS_MAILPROFILEMIGRATOR_CONTRACTID_PREFIX "seamonkey",
    nsSeamonkeyProfileMigratorConstructor },
#if !defined(XP_BEOS)
  { "Netscape Communicator 4.x",
    NS_DOGBERTPROFILEMIGRATOR_CID,
    NS_MAILPROFILEMIGRATOR_CONTRACTID_PREFIX "dogbert",
    nsDogbertProfileMigratorConstructor },
#endif
#ifdef XP_WIN32
  { "Outlook Express Profile Migrator",
    NS_OEXPRESSPROFILEMIGRATOR_CID,
    NS_MAILPROFILEMIGRATOR_CONTRACTID_PREFIX "oexpress",
    nsOEProfileMigratorConstructor },
  { "Outlook Profile Migrator",
    NS_OUTLOOKPROFILEMIGRATOR_CID,
    NS_MAILPROFILEMIGRATOR_CONTRACTID_PREFIX "outlook",
    nsOutlookProfileMigratorConstructor },
#endif
#if defined (XP_WIN32) || defined (XP_MACOSX)
  { "Eudora Profile Migrator",
    NS_EUDORAPROFILEMIGRATOR_CID,
    NS_MAILPROFILEMIGRATOR_CONTRACTID_PREFIX "eudora",
    nsEudoraProfileMigratorConstructor },
#endif
#ifdef XP_WIN32
  { "Collab Windows Integration",
    CS_WINDOWS_INTEGRATION_CID,
    "@synovel.com/collab/shell-service;1",
    nsWindowsShellServiceConstructor},
#endif
#ifdef MOZ_WIDGET_GTK2
  { "Collab GNOME Integration",
    CS_GNOME_INTEGRATION_CID,
    "@synovel.com/collab/shell-service;1",
    nsMailGNOMEIntegrationConstructor },
#endif
#ifdef XP_MACOSX
  { "Collab Mac Integration",
    CS_MAC_INTEGRATION_CID,
    "@synovel.com/collab/shell-service;1",
    nsMailMacIntegrationConstructor },
#endif
#if defined(XP_WIN32) && !defined(MOZ_DISABLE_VISTA_SDK_REQUIREMENTS)
  { "Mail Windows Search Integration Helper",
    NS_MAILWINSEARCHHELPER_CID,
    "@mozilla.org/mail/windows-search-helper;1",
    nsMailWinSearchHelperConstructor },
#endif
};

NS_IMPL_NSGETMODULE(csCollabCompsModule, components)
