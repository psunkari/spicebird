#!/usr/bin/perl -w
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
# The Original Code is Spicebird code.
#
# The Initial Developer of the Original Code is
# Synovel Software Technologies
# Portions created by the Initial Developer are Copyright (C) 2008
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Sunil Mohan Adapa <sunil@synovel.com> (Original Author)
#
# Alternatively, the contents of this file may be used under the terms of
# either of the GNU General Public License Version 2 or later (the "GPL"),
# or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
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

use strict;

my @locales = @ARGV;

if (!-e "mozilla/client.mk")
{
  system ("CVSROOT=:pserver:anonymous\@cvs-mirror.mozilla.org:/cvsroot cvs -z3 co -r 'THUNDERBIRD_3_0a2_RELEASE' mozilla/client.mk");
}
else
{
  print "Checkout of client.mk not required\n";
}

if (!-e "mozilla/tools/l10n")
{
  system ("CVSROOT=:pserver:anonymous\@cvs-mirror.mozilla.org:/cvsroot cvs -z3 co mozilla/tools/l10n");
}
else
{
  print "Checkout of tools/l10n not required\n";
}

system ("grep COLLAB mozilla/client.mk > /dev/null");
if ($? != 0)
{
  system ("wget http://www.spicebird.com/pub/mozilla/client_TAG_THUNDERBIRD_3_0a2_RELEASE.mk -O mozilla/client.mk");
}
else
{
  print "client.mk already has Spicebird changes\n";
}

my $locale_checkout_string;
my $locales = join(" ", @locales);
if ($locales)
{
  $locale_checkout_string = " MOZ_CO_LOCALES='$locales'";
}

print ("LOCALES = $locales\n");

system("cd mozilla && make -f client.mk l10n-checkout MOZ_CO_PROJECT=collab $locale_checkout_string");
