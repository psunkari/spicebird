#- tinder-config.pl - Tinderbox configuration file.
#-    Uncomment the variables you need to set.
#-    The default values are the same as the commented variables.

# $ENV{MOZ_PACKAGE_MSI}
#-----------------------------------------------------------------------------
#  Default: 0
#   Values: 0 | 1
#  Purpose: Controls whether a MSI package is made.
# Requires: Windows and a local MakeMSI installation.
#$ENV{MOZ_PACKAGE_MSI} = 0;

# $ENV{MOZ_SYMBOLS_TRANSFER_TYPE}
#-----------------------------------------------------------------------------
#  Default: scp
#   Values: scp | rsync
#  Purpose: Use scp or rsync to transfer symbols to the Talkback server.
# Requires: The selected type requires the command be available both locally
#           and on the Talkback server.
#$ENV{MOZ_SYMBOLS_TRANSFER_TYPE} = "scp";

#- PLEASE FILL THIS IN WITH YOUR PROPER EMAIL ADDRESS
#$BuildAdministrator = "$ENV{USER}\@$ENV{HOST}";
$BuildAdministrator = 'sunil@synovel.com';
#$BuildAdministrator = ($ENV{USER} || "cltbld") . "\@" . ($ENV{HOST} || "dhcp");

#- You'll need to change these to suit your machine's needs
#$DisplayServer = ':0.0';

#- Default values of command-line opts
#-
$BuildDepend       = 0;      # Depend or Clobber
#$BuildDebug        = 0;      # Debug or Opt (Darwin)
$ReportStatus      = 0;      # Send results to server, or not
$ReportFinalStatus = 0;      # Finer control over $ReportStatus.
#$UseTimeStamp      = 1;      # Use the CVS 'pull-by-timestamp' option, or not
$BuildOnce         = 1;      # Build once, don't send results to server
#$ConfigureOnly     = 0;      # Configure, but do not build.
#$TestOnly          = 0;      # Only run tests, don't pull/build
#$BuildEmbed        = 0;      # After building seamonkey, go build embed app.
#$SkipMozilla       = 0;      # Use to debug post-mozilla.pl scripts.
$SkipCheckout      = 1;      # Use to debug build process without checking out new source.
#$BuildLocales      = 0;      # Do l10n packaging?
#$ForceRebuild      = 0;      # Do a full re-build even when in depend mode; used
                             # internally; you probably shouldn't set this

# Only used when $BuildLocales = 1
%WGetFiles         = ();  # Pull files from the web, URL => Location
#$WGetTimeout       = 360; # Wget timeout, in seconds
#$BuildLocalesArgs  = "";  # Extra attributes to add to the makefile command
                          # which builds the "installers-<locale>" target.
                          # Typically used to set ZIP_IN and WIN32_INSTALLER_IN
# If defined, the version file used in the local l10n build tree to construct
# a URL to download for l10n repackaging (makes it so %WGetFiles doesn't need
# to be modified every release).
# $LocalizationVersionFile = "browser/config/version.txt";

# Tests
#$CleanProfile             = 0;
#$ResetHomeDirForTests     = 1;
#$ProductName              = "Mozilla";
#$VendorName               = '';

$RunMozillaTests          = 0;  # Allow turning off of all tests if needed.
#$RegxpcomTest             = 1;
#$AliveTest                = 1;
#$JavaTest                 = 0;
#$ViewerTest               = 0;
#$BloatTest                = 0;  # warren memory bloat test
#$BloatTest2               = 0;  # dbaron memory bloat test, require tracemalloc
#$DomToTextConversionTest  = 0;  
#$XpcomGlueTest            = 0;
#$CodesizeTest             = 0;  # Z,  require mozilla/tools/codesighs
#$EmbedCodesizeTest        = 0;  # mZ, require mozilla/tools/codesigns
#$MailBloatTest            = 0;
#$EmbedTest                = 0;  # Assumes you wanted $BuildEmbed=1
#$LayoutPerformanceTest    = 0;  # Tp
#$LayoutPerformanceLocalTest   = 0;  # Tp2
#$DHTMLPerformanceTest     = 0;  # Tdhtml
#$QATest                   = 0;  
#$XULWindowOpenTest        = 0;  # Txul
#$StartupPerformanceTest   = 0;  # Ts
#$NeckoUnitTest            = 0;
#$RenderPerformanceTest    = 0;  # Tgfx
#$RunUnitTests             = 0;  # TUnit
#@CompareLocaleDirs        = (); # Run compare-locales test on these directories
# ("network","dom","toolkit","security/manager");
#$CompareLocalesAviary     = 0;  # Should the compare-locales commands use the
                                # aviary directory structure?
#$TestWithJprof            = 0;  # Use jprof profiler during tests
#$LeakFailureThreshold     = 0;  # How many RLk bytes leaked is a testfailure

#$TestsPhoneHome           = 0;  # Should test report back to server?
#$GraphNameOverride        = ''; # Override name built from ::hostname() and $BuildTag

# $results_server
#----------------------------------------------------------------------------
# Server on which test results will be accessible.  This was originally tegu,
# then became axolotl.  Once we moved services from axolotl, it was time
# to give this service its own hostname to make future transitions easier.
# - cmp@mozilla.org
#$results_server           = "build-graphs.mozilla.org";

#$pageload_server          = "pageload.build.mozilla.org";  # localhost

#
# Timeouts, values are in seconds.
#
#$CVSCheckoutTimeout               = 3600;
#$CreateProfileTimeout             = 45;
#$RegxpcomTestTimeout              = 120;

#$AliveTestTimeout                 = 45;
#$ViewerTestTimeout                = 45;
#$EmbedTestTimeout                 = 45;
#$BloatTestTimeout                 = 120;   # seconds
#$MailBloatTestTimeout             = 120;   # seconds
#$JavaTestTimeout                  = 45;
#$DomTestTimeout	                  = 45;    # seconds
#$XpcomGlueTestTimeout             = 15;
#$CodesizeTestTimeout              = 900;     # seconds
#$CodesizeTestType                 = "auto";  # {"auto"|"base"}
#$LayoutPerformanceTestTimeout     = 1200;  # entire test, seconds
#$LayoutPerformanceLocalTestTimeout    = 1200;  # entire test, seconds
#$DHTMLPerformanceTestTimeout      = 1200;  # entire test, seconds
#$QATestTimeout                    = 1200;   # entire test, seconds
#$LayoutPerformanceTestPageTimeout = 30000; # each page, ms
#$StartupPerformanceTestTimeout    = 15;    # seconds
#$NeckoUnitTestTimeout             = 30;    # seconds
#$XULWindowOpenTestTimeout	      = 150;   # seconds
#$RenderTestTimeout                = 1800;  # seconds
#$RunUnitTestsTimeout              = 600;   # seconds

#$MozConfigFileName = 'mozconfig';

#$UseMozillaProfile = 1;
#$MozProfileName = 'default';

# This sets the value of the XPCOM_DEBUG_BREAK environment variable.  We
# default to 'warn', which suppresses the assertion dialogs on Windows
# and gives platform parity.  Use 'abort' (or, on trunk after 2007-08-10,
# 'stack-and-abort') for fatal assertions.
#$MozAssertBehavior = 'warn';

#- Set these to what makes sense for your system
$Make          = 'make';       # Must be GNU make
#$MakeOverrides = '';
#$mail          = '/usr/bin/mail';
#$CVS           = 'cvs -q';
#$CVSCO         = 'checkout -P';

# win32 usually doesn't have /bin/mail
$blat           = '/c/mozilla-build/blat261/full/blat';
#$use_blat       = 0;

# Set moz_cvsroot to something like:
# :pserver:$ENV{USER}%netscape.com\@cvs.mozilla.org:/cvsroot
# :pserver:anonymous\@cvs-mirror.mozilla.org:/cvsroot
#
# Note that win32 may not need \@, depends on ' or ".
# :pserver:$ENV{USER}%netscape.com@cvs.mozilla.org:/cvsroot

#$moz_cvsroot   = $ENV{CVSROOT};

# Used for checking out sources (e.g. Talkback) from the internal
# Mozilla repository. If you don't have a CVS account with access,
# just leave this set to 0.
#$MofoRoot = 0;

#- Set these proper values for your tinderbox server
$Tinderbox_server = 'tinderbox@spicebird.org';

# Allow for non-client builds, e.g. camino.
#$moz_client_mk = 'client.mk';

# Set if you're building an app on top of XULRunner.
#$XULRunnerApp = 0;

#- Set if you want to build in a separate object tree
$ObjDir = 'obj-sb-trunk';

# If the build is a combined xulrunner+something, set the "something"
# subdirectory: example "firefox/" - NOTE: need trailing slash!
#$SubObjDir = '';

# Extra build name, if needed.
$BuildNameExtra = 'Nightly';

# User comment, eg. ip address for dhcp builds.
# ex: $UserComment = "ip = 208.12.36.108";
#$UserComment = 0;

#-
#- The rest should not need to be changed
#-

#- Minimum wait period from start of build to start of next build in minutes.
#$BuildSleep = 10;

#- Until you get the script working. When it works,
#- change to the tree you're actually building
$BuildTree  = 'Spicebird';

#$BuildName = '';
#$BuildTag = '';
#$BuildConfigDir = 'mozilla/config';
#$Topsrcdir = 'mozilla';

$BinaryName = 'spicebird.exe';
#$RequireExecutableBinary = 1;

#
# For embedding app, use:
#$EmbedBinaryName = 'TestGtkEmbed';
#$EmbedDistDir    = 'dist/bin';


#$ShellOverride = ''; # Only used if the default shell is too stupid
#$ConfigureArgs = '';
#$ConfigureEnvArgs = '';
#$Compiler = 'gcc';
#$NSPRArgs = '';
#$ShellOverride = '';

# UsePrebuiltTalkback:
# If set to a filepath, tinderbox will use the file contents (presumed to be a bz2
# archive of a compatible Talkback extension) rather than compiling Talkback
# from source. 
#$UsePrebuiltTalkback = 0;

# Release build options
#$ReleaseBuild  = 1;
#$clean_objdir = 1; # remove objdir when starting release cycle?
$clean_srcdir = 0; # remove srcdir when starting release cycle?
#$LocaleProduct = "browser";
$shiptalkback  = 0;
$ReleaseToLatest = 0; # Push the release to latest-<milestone>?
#$ReleaseToDated = 1; # Push the release to YYYY-MM-DD-HH-<milestone>?
#$OfficialBuildMachinery = 1; # Allow official clobber nightlies.  When false, $cachebuild in post-mozilla-rel.pl can never be true.
#$ReleaseGroup = ''; # group to set uploaded files to (if non-empty)
#$build_hour    = "8";
$package_creation_path = "/collab/installer";
# path to make in to recreate mac bundle, needed for mac + talkback:
# $mac_bundle_path = "/browser/app";
#$ssh_version   = "2";
$ssh_user      = "files";
$ssh_server    = "files.spicebird.org";
$ssh_opts      = "-p 1301";
$scp_opts      = "-P 1301";
$ftp_path      = "/var/www/html/files/pub/spicebird.org/spicebird/nightly";
$url_path      = "http://files.spicebird.org/pub/spicebird.org/spicebird/nightly";
#$tbox_ftp_path = $ftp_path;
#$tbox_url_path = $url_path;
#$milestone     = "trunk";
$notify_list   = 'sunil@synovel.com';
$stub_installer = 0;
$sea_installer = 1;
$archive       = 1;
$push_raw_xpis = 0;
$update_package = 1;
$update_product = "Spicebird";
$update_version = "1.0";
$update_platform = "WINNT_x86-msvc";
$update_hash = "SHA1";
#$update_filehost = "ftp.mozilla.org";
# use $update_appv and $update_extv to set app and extension version explicitly, or
# use $update_ver_file to read a value for either/both from a file (relative to topsrcdir). 
# The first two variables take precedence over $update_ver_file
#$update_appv = "1.0+";
#$update_extv = "1.0+";
# the master file for app version in Firefox, use mail instead of browser for Thunderbird
$update_ver_file = "collab/config/version.txt"; 
$update_pushinfo = 1;
$update_aus_user = 'aus';
$update_aus_host = 'aus.spicebird.com';
$update_aus_ssh_opts = '-p 1301';
$update_aus_scp_opts = '-P 1301';
$update_aus_path = '/home/aus/incoming_aus_data/2';

#$crashreporter_buildsymbols = 0;
#$crashreporter_pushsymbols = 0;
#$ENV{SYMBOL_SERVER_HOST} = '';
#$ENV{SYMBOL_SERVER_USER}   = '';
#$ENV{SYMBOL_SERVER_PATH}   = '';
# this is optional, it's a full path to a ssh private key
#$ENV{SYMBOL_SERVER_SSH_KEY} = '';

# Reboot the OS at the end of build-and-test cycle. This is primarily
# intended for Win9x, which can't last more than a few cycles before
# locking up (and testing would be suspect even after a couple of cycles).
# Right now, there is only code to force the reboot for Win9x, so even
# setting this to 1, will not have an effect on other platforms. Setting
# up win9x to automatically logon and begin running tinderbox is left 
# as an exercise to the reader. 
#$RebootSystem = 0;

# LogCompression specifies the type of compression used on the log file.
# Valid options are 'gzip', and 'bzip2'. Please make sure the binaries
# for 'gzip' or 'bzip2' are in the user's path before setting this
# option.
#$LogCompression = '';

# LogEncoding specifies the encoding format used for the logs. Valid
# options are 'base64', and 'uuencode'. If $LogCompression is set above,
# this needs to be set to 'base64' or 'uuencode' to ensure that the
# binary data is transferred properly.
#$LogEncoding = '';

# Prevent Extension Manager from spawning child processes during tests
# - processes that tbox scripts cannot kill. 
#$ENV{NO_EM_RESTART} = '1';

# Build Mac OS X universal binaries (must be used with an objdir and
# universal support from mozilla/build/macosx/universal)
#$MacUniversalBinary = 0;

# If tinderbox is running in a test-only mode, it needs to be able to download
# the latest build and unpack it rather than building it.
#$TestOnlyTinderbox = 0;
#$DownloadBuildFile = 'firefox-2.0a3.en-US.linux-i686.tar.gz';
#$DownloadBuildURL = 'http://ftp.mozilla.org/pub/mozilla.org/firefox/nightly/latest-mozilla1.8';
#$DownloadBuildDir = 'firefox';

# If TestOnlyTinderbox is enabled, fetch the latest build info from tinderbox in a 
# parseable format
#$TinderboxServerURL = 'http://tinderbox.mozilla.org/showbuilds.cgi?tree=MozillaTest&quickparse=1';
#$MatchBuildname = "Linux bl-bldlnx01 Depend Fx-Mozilla1.5.0.4-baseline-test2";
