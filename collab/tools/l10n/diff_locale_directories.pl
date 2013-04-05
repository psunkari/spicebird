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
use File::Basename;
use IO::File;
require Utils;

if ($#ARGV != 2)
{
  print "Usage: ./diff_locale_directories.pl <l10n_directory_1> <l10n_directory_2> <output_directory>\n";
  exit -1;
}

our $template_dir = $ARGV[0];
our $data_dir = $ARGV[1];
our $output_dir = $ARGV[2];

binmode STDOUT, ":utf8";

process("");

sub process
{
  our $template_dir;
  our $data_dir;
  our $output_dir;

  my $current_path = shift;

  my $full_path = "$template_dir/$current_path";

  debug_print (2, "Processing file $full_path\n");

  if (-f $full_path) 
  {
    my $template_file = $full_path;
    my $data_file = "$data_dir/$current_path";
    my $output_file = "$output_dir/$current_path";
    
    my $output_base_dir = dirname($output_file);
    `mkdir -p $output_base_dir`;

    if (!(-f $data_file))
    {
      debug_print (1, "File not present in the data directory, ignoring: $data_file\n");
      return;
    }

    if ($template_file =~ /.dtd$/)
    {
      process_dtd ($template_file, $data_file, $output_file);
      return;
    }

    if ($template_file =~ /.properties$/)
    {
      process_properties ($template_file, $data_file, $output_file);
      return;
    }
    
    if (!same_file($template_file, $data_file))
    {
      `cp $data_file $output_file`;
    }

    return;
  }

  if (-d $full_path)
  {
    my $dir;
    opendir($dir, $full_path) || print "can’t opendir $full_path: $!\n";
    while (my $path = readdir($dir))
    {
      next unless $path !~ /^\./;
      next unless $path !~ /^CVS$/;

      process ("$current_path/$path");
    }
    closedir($dir);
    return;
  }

  print ("Warning: Strange or non-existant file $full_path");
  return;
}

sub process_dtd
{
  my $template = shift;
  my $data = shift;
  my $output = shift;

  # parse
  our (%pairs, %used_pairs);
  %pairs = ();
  %used_pairs = ();
  parse_dtd ($data);

  # print
  foreach my $key (keys(%pairs))
  {
    #print $key . " = " . $pairs{$key} . "\n";
  }

  # substitute
  substitute_dtd ($template, $output);
}

sub parse_dtd
{
  my $data_file = shift;

  open FILE, "<$data_file" or print "Can't open dtd file: $data_file\n";
  my @data = <FILE>;
  close FILE;

  my $data = join("", @data);
  $data =~ s/<!ENTITY\s+(\S*)\s+"([^"]*)"\s*>/parse_func($1,$2)/emg;

  sub parse_func
  {
    our %pairs;
    my $key = shift;
    my $value = shift;
    $pairs{$key} = $value;
  }
}

sub substitute_dtd
{
  my $template_file = shift;
  my $o_file = shift;

  open TEMPLATE, "<$template_file";
  my @template = <TEMPLATE>;
  close TEMPLATE;

  my $template = join("", @template);

  our $output_fh;
  undef ($output_fh);
  our $output_file = $o_file;
  our $output_utf8 = 0;
  $template =~ s/<!ENTITY\s+(\S*)\s+"([^"]*)"\s*>/substitute_func($1,$2)/emg;

  our (%pairs, %used_pairs);
  foreach my $key (keys %pairs)
  {
    if (not defined $used_pairs{$key} or $used_pairs{$key} != 1)
    {
      output("<!ENTITY $key \"$pairs{$key}\">\n");
    }
  }
  close $output_fh if (defined($output_fh));

  sub substitute_func
  {
    my $key = shift;
    my $value= shift;
    our %pairs;
    our %used_pairs;

    if (exists($pairs{$key}))
    {
      $used_pairs{$key} = 1;
    }

    if (exists($pairs{$key}) && !dtd_equivalent($value, $pairs{$key}))
    {
      output("<!ENTITY $key \"" . html_encode($pairs{$key}) . "\">\n");
    }
    return "";
  }
}

sub process_properties
{
  my $template = shift;
  my $data = shift;
  my $output = shift;

  # parse
  our (%pairs, %used_pairs);
  %pairs = ();
  %used_pairs = ();
  parse_properties ($data);

  # print
  foreach my $key (keys(%pairs))
  {
    #print $key . " = " . $pairs{$key} . "\n";
  }

  # substitute
  substitute_properties ($template, $output);
}

sub parse_properties 
{
  my $data_file = shift;

  open FILE, "<$data_file" or print "Can't open properties file: $data_file\n";
  binmode FILE, ":utf8";
  my @data = <FILE>;
  close FILE;

  my $data = join("", @data);
  $data =~ s/^\s*?([^#\s]*?)\s*?=\s*?(.*?)\s*?$/parse_properties_func($1,$2)/emg;

  sub parse_properties_func
  {
    our %pairs;
    my $key = shift;
    my $value = shift;
    $pairs{$key} = $value;
  }
}

sub substitute_properties
{
  my $template_file = shift;
  my $o_file = shift;

  open TEMPLATE, "<$template_file";
  binmode TEMPLATE, ":utf8";
  my @template = <TEMPLATE>;
  close TEMPLATE;

  my $template = join("", @template);

  our $output_fh;
  undef ($output_fh);
  our $output_file = $o_file;
  our $output_utf8 = 1;
  $template =~ s/^\s*?([^#\s]*?)\s*?=\s*?(.*?)\s*?$/substitute_properties_func($1,$2)/emg;

  our (%pairs, %used_pairs);
  foreach my $key (keys %pairs)
  {
    if (not defined $used_pairs{$key} or $used_pairs{$key} != 1)
    {
      output("$key = $pairs{$key}\n");
    }
  }
  close $output_fh if (defined($output_fh));

  sub substitute_properties_func
  {
    my $key = shift;
    my $value= shift;
    my $output_file = shift;
    my $ret;
    our %pairs;

    if (exists($pairs{$key}))
    {
      $used_pairs{$key} = 1;
    }

    if (exists($pairs{$key}) && !properties_equivalent($value, $pairs{$key}))
    {
      output($key."=".$pairs{$key}."\n");
    }
    return "";
  }
}

sub output
{
  my $string = shift;

  our $output_fh;
  our $output_file;
  our $output_utf8;
  if (!defined($output_fh))
  {
    $output_fh = new IO::File "> $output_file" or die $!;
    if ($output_utf8)
    {
      binmode $output_fh, ":utf8";
    }
  }

  print $output_fh $string;
}
