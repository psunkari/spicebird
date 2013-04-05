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

our $debug_level = $ENV{"DEBUG_LEVEL"};
$debug_level = 0 if not defined($debug_level);

sub html_encode
{
  my $string = shift;

  $string =~ s/>/&gt;/g;
  $string =~ s/</&lt;/g;

  return $string;
}

sub html_decode
{
  my $string = shift;

  $string =~ s/&gt;/>/g;
  $string =~ s/&lt;/</g;
  $string =~ s/&apos;/'/g;
  $string =~ s/&quot;/"/g;
  
  return $string;
}

sub unicode_decode
{
  my $string = shift;

  $string =~ s/\\u([a-fA-F0-9]{4})/chr(hex($1))/eg;

  return $string;
}

sub dtd_equivalent
{
  my $first = shift;
  my $second = shift;
  
  $first = html_decode(trim($first));
  $second = html_decode(trim($second));

  return 1 if ($first eq $second);

  return 0;
}

sub properties_equivalent
{
  my $first = shift;
  my $second = shift;
  
  $first = unicode_decode(trim($first));
  $second = unicode_decode(trim($second));

  return 1 if ($first eq $second);

  return 0;
}

sub trim
{
  my $string = shift;
  $string =~ s/^\s+//;
  $string =~ s/\s+$//;

  return $string;
}

sub same_file
{
  my $file1 = shift;
  my $file2 = shift;
  my $result = `diff -q $file1 $file2`;
  return !$result;
}

sub debug_print
{
  our $debug_level;
  my $current_level = shift;
  my $string = shift;

  if ($debug_level >= $current_level)
  {
    print STDERR $string;
  }
}

1;
