# ***** BEGIN LICENSE BLOCK *****
# Version: MPL 1.1/GPL 2.0/LGPL 2.1
#
# The contents of this file are subject to the Mozilla Public License Version
# 1.1 (the "License"); you may not use this file except in compliance with
# the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
# for the specific language governing rights and limitations under the
# License.
#
# The Original Code is Mozilla Build System
#
# The Initial Developer of the Original Code is
# Ben Turner <mozilla@songbirdnest.com>
#
# Portions created by the Initial Developer are Copyright (C) 2007
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Prasad Sunkari <prasad@synovel.com>
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
# in which case the provisions of the GPL or the LGPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of either the GPL or the LGPL, and not to allow others to
# use your version of this file under the terms of the MPL, indicate your
# decision by deleting the provisions above and replace them with the notice
# and other provisions required by the GPL or the LGPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the MPL, the GPL or the LGPL.
#
# ***** END LICENSE BLOCK *****
#! /bin/sh

MOZ_APP_NAME="spicebird"
MOZ_APP_DISPLAYNAME="Spicebird"
MOZ_UPDATER=1
MOZ_THUNDERBIRD=1
MOZ_NO_ACTIVEX_SUPPORT=1
MOZ_ACTIVEX_SCRIPTING_SUPPORT=
# MOZ_OJI is only required to be cleared for MOZILLA_1_9_1_BRANCH.
# mozilla-central does not have this.
MOZ_OJI=
NECKO_PROTOCOLS_DEFAULT="about data file ftp http res viewsource"
MOZ_IMG_DECODERS_DEFAULT=`echo "$MOZ_IMG_DECODERS_DEFAULT" | sed "s/ xbm//"`
MOZ_MAIL_NEWS=1
if [ "$COMM_BUILD" ]; then
  MOZ_LDAP_XPCOM=1
fi
MOZ_STATIC_MAIL_BUILD=1
MOZ_COMPOSER=1
MOZ_SAFE_BROWSING=1

# Needed for the mozilla-central build side of the system.
# Can be dropped when we branch MOZILLA_1_9_1_BRANCH
MOZILLA_BRANCH_VERSION=`echo ${MOZILLA_VERSION} | sed -e 's/\(^[0-9]\.[0-9]\.[0-9]\).*/\1/;'`

MOZ_APP_VERSION_TXT=$topsrcdir/$MOZ_BUILD_APP/config/version.txt
MOZ_APP_VERSION=`cat $MOZ_APP_VERSION_TXT`

SPICEBIRD_VERSION=$MOZ_APP_VERSION
MOZ_NO_XPCOM_OBSOLETE=1
MOZ_ENABLE_CANVAS=1
