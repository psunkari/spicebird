#!/bin/bash

# Script to apply patches on the mozilla source code before building the suite

SCRIPT_DIR=`dirname $0`

# 10. Let addons add a custom column to addressbook list view
#patch -p1 -N < $SCRIPT_DIR/addrbook_custom_column.patch

# 30. Modify nsMessengerBootstrap.cpp to open collab when 
#     the '-mail' command line switch is passed.
#patch -p1 -N < $SCRIPT_DIR/messenger_bootstrap_collab.patch

# 50. Patch configure.ac for Spicebird specific options and checks
#patch -p1 -N < $SCRIPT_DIR/configure_telepathy.patch

# 70. Patch for nsMsgDBView.cpp & .h to add support for custom date formats.
#patch -p1 -N < $SCRIPT_DIR/custom_dates.patch

# 80. Patch for getting blogs working with current mailnews code.
#patch -p1 -N < $SCRIPT_DIR/mailnews_local_blog_change.patch

# 90. Patch for defering the findSession part in google calendar code
#patch -p1 -N < $SCRIPT_DIR/gdata_provider_defer_findsession.patch

# 100. Patch to enable only fcc without recepients in compose dialog
#patch -p1 -N < $SCRIPT_DIR/allow_only_fcc.patch

# 120. Patch to fix errors while migration from Sp 0.4 calendars to 0.7 (Bug 642)
#patch -p1 -N < $SCRIPT_DIR/calendar_migration_fix.patch

# 200. Patch to create new directory type (IMDirectory)
#patch -p1 -N < $SCRIPT_DIR/addrbook_imdirectory.patch

# 220. Patch alarm dialog code to launch item details (Bug 992)
#patch -p1 -N < $SCRIPT_DIR/alarm-dialog.patch

# 230. Minimonth flex changes (Bug 965)
#patch -p1 -N < $SCRIPT_DIR/minimonth_styling_changes.patch

# 240. Changes to csTimezoneService.js to get timezones.sqlite from install dir
#patch -p1 -N < $SCRIPT_DIR/timezone_service.patch


####### Apply patches to the mozilla platform code (mozilla-central)
if [ ! -d mozilla ]; then
  echo "Did you forget to checkout the mozilla-central source?";
  echo "Run 'python client.py checkout' to update/checkout the sources."
  exit 1;
fi
CURRENT_DIR=`pwd`
cd mozilla

# 60. Patch to integrate glib event loop into Windows event loop
patch -p1 -N < $CURRENT_DIR/$SCRIPT_DIR/mozilla/windows_glib_event_loop.patch

# 190. Patch to use applications.manifest in profile directory for chome loading
patch -p1 -N < $CURRENT_DIR/$SCRIPT_DIR/mozilla/use_applications_manifest_from_profile.patch

# 250. Add more smileys to mozITXTToHTMLConv
patch -p1 -N < $CURRENT_DIR/$SCRIPT_DIR/mozilla/streamconv_more_smileys.patch

# 260. Add support for multiple lines in a tree view
patch -p1 -N < $CURRENT_DIR/$SCRIPT_DIR/mozilla/441414_multiline_trees.patch

# Go back to the parent directory
cd $CURRENT_DIR
