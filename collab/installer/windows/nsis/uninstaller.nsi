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
# The Original Code is the Mozilla Installer code.
#
# The Initial Developer of the Original Code is Mozilla Foundation
# Portions created by the Initial Developer are Copyright (C) 2006
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#  Robert Strong <robert.bugzilla@gmail.com>
#  Scott MacGregor <mscott@mozilla.org>
#  Prasad Sunkari <prasad@synovel.com> (Spicebird Port)
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

# Required Plugins:
# AppAssocReg http://nsis.sourceforge.net/Application_Association_Registration_plug-in
# ShellLink   http://nsis.sourceforge.net/ShellLink_plug-in
# UAC         http://nsis.sourceforge.net/UAC_plug-in

; Set verbosity to 3 (e.g. no script) to lessen the noise in the build logs
!verbose 3

; 7-Zip provides better compression than the lzma from NSIS so we add the files
; uncompressed and use 7-Zip to create a SFX archive of it
SetDatablockOptimize on
SetCompress off
CRCCheck on

RequestExecutionLevel user

!addplugindir ./

; On Vista and above attempt to elevate Standard Users in addition to users that
; are a member of the Administrators group.
!define NONADMIN_ELEVATE

; prevents compiling of the reg write logging.
!define NO_LOG

Var TmpVal

; Other included files may depend upon these includes!
; The following includes are provided by NSIS.
!include FileFunc.nsh
!include LogicLib.nsh
!include MUI.nsh
!include WinMessages.nsh
!include WinVer.nsh
!include WordFunc.nsh

!insertmacro GetOptions
!insertmacro GetParameters
!insertmacro GetParent
!insertmacro WordFind

!insertmacro un.GetParent

; The following includes are custom.
!include branding.nsi
!include defines.nsi
!include common.nsh
!include locales.nsi
!include version.nsh

; This is named BrandShortName helper because we use this for software update
; post update cleanup.
VIAddVersionKey "FileDescription" "${BrandShortName} Helper"
VIAddVersionKey "OriginalFilename" "helper.exe"

; Most commonly used macros for managing shortcuts
!insertmacro _LoggingShortcutsCommon

!insertmacro AddHandlerValues
!insertmacro CleanVirtualStore
!insertmacro ElevateUAC
!insertmacro FindSMProgramsDir
!insertmacro GetLongPath
!insertmacro GetPathFromString
!insertmacro IsHandlerForInstallDir
!insertmacro RegCleanMain
!insertmacro RegCleanUninstall
!insertmacro SetBrandNameVars
!insertmacro UnloadUAC
!insertmacro WriteRegDWORD2
!insertmacro WriteRegStr2

!insertmacro un.ChangeMUIHeaderImage
!insertmacro un.CheckForFilesInUse
!insertmacro un.CleanUpdatesDir
!insertmacro un.CleanVirtualStore
!insertmacro un.DeleteShortcuts
!insertmacro un.GetLongPath
!insertmacro un.GetSecondInstallPath
!insertmacro un.ManualCloseAppPrompt
!insertmacro un.ParseUninstallLog
!insertmacro un.RegCleanAppHandler
!insertmacro un.RegCleanFileHandler
!insertmacro un.RegCleanMain
!insertmacro un.RegCleanProtocolHandler
!insertmacro un.RegCleanUninstall
!insertmacro un.RemoveQuotesFromPath
!insertmacro un.SetBrandNameVars

!include shared.nsh

; Helper macros for ui callbacks. Insert these after shared.nsh
!insertmacro OnEndCommon
!insertmacro UninstallOnInitCommon

!insertmacro un.OnEndCommon

Name "${BrandFullName}"
OutFile "helper.exe"
InstallDirRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${BrandFullNameInternal} (${AppVersion})" "InstallLocation"
InstallDir "$PROGRAMFILES\${BrandFullName}"
ShowUnInstDetails nevershow

################################################################################
# Modern User Interface - MUI

!define MUI_ABORTWARNING
!define MUI_ICON setup.ico
!define MUI_UNICON setup.ico
!define MUI_WELCOMEPAGE_TITLE_3LINES
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_RIGHT
!define MUI_UNWELCOMEFINISHPAGE_BITMAP wizWatermark.bmp

; Use a right to left header image when the language is right to left
!ifdef ${AB_CD}_rtl
!define MUI_HEADERIMAGE_BITMAP_RTL wizHeaderRTL.bmp
!else
!define MUI_HEADERIMAGE_BITMAP wizHeader.bmp
!endif

/**
 * Uninstall Pages
 */
; Welcome Page
!define MUI_PAGE_CUSTOMFUNCTION_PRE un.preWelcome
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE un.leaveWelcome
!insertmacro MUI_UNPAGE_WELCOME

; Custom Uninstall Confirm Page
UninstPage custom un.preConfirm un.leaveConfirm

; Remove Files Page
!insertmacro MUI_UNPAGE_INSTFILES

; Finish Page

; Don't setup the survey controls, functions, etc. when the application has
; defined NO_UNINSTALL_SURVEY
!ifndef NO_UNINSTALL_SURVEY
!define MUI_PAGE_CUSTOMFUNCTION_PRE un.preFinish
!define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED
!define MUI_FINISHPAGE_SHOWREADME ""
!define MUI_FINISHPAGE_SHOWREADME_TEXT $(SURVEY_TEXT)
!define MUI_FINISHPAGE_SHOWREADME_FUNCTION un.Survey
!endif

!insertmacro MUI_UNPAGE_FINISH

; Use the default dialog for IDD_VERIFY for a simple Banner
ChangeUI IDD_VERIFY "${NSISDIR}\Contrib\UIs\default.exe"

################################################################################
# Install Sections
; Empty section required for the installer to compile as an uninstaller
Section ""
SectionEnd

################################################################################
# Uninstall Sections

Section "Uninstall"
  SetDetailsPrint textonly
  DetailPrint $(STATUS_UNINSTALL_MAIN)
  SetDetailsPrint none

  ; Delete the app exe to prevent launching the app while we are uninstalling.
  ClearErrors
  ${DeleteFile} "$INSTDIR\${FileMainEXE}"
  ${If} ${Errors}
    ; If the user closed the application it can take several seconds for it to
    ; shut down completely. If the application is being used by another user we
    ; can still delete the files when the system is restarted. 
    Sleep 5000
    ${DeleteFile} "$INSTDIR\${FileMainEXE}"
    ClearErrors
  ${EndIf}

  SetShellVarContext current  ; Set SHCTX to HKCU
  ${un.RegCleanMain} "Software\Synovel"
  ${un.RegCleanUninstall}
  ${un.DeleteShortcuts}

  ClearErrors
  WriteRegStr HKLM "Software\Synovel" "${BrandShortName}InstallerTest" "Write Test"
  ${If} ${Errors}
    StrCpy $TmpVal "HKCU" ; used primarily for logging
  ${Else}
    SetShellVarContext all  ; Set SHCTX to HKLM
    DeleteRegValue HKLM "Software\Synovel" "${BrandShortName}InstallerTest"
    StrCpy $TmpVal "HKLM" ; used primarily for logging
    ${un.RegCleanMain} "Software\Synovel"
    ${un.RegCleanUninstall}
    ${un.DeleteShortcuts}
  ${EndIf}

  ${un.RegCleanAppHandler} "Spicebird.MAILTO"
  ${un.RegCleanAppHandler} "Spicebird.NEWS"
  ${un.RegCleanAppHandler} "Spicebird.EML"
  ${un.RegCleanAppHandler} "Spicebird.ICS"
  ${un.RegCleanProtocolHandler} "mailto"
  ${un.RegCleanProtocolHandler} "news"
  ${un.RegCleanProtocolHandler} "nntp"
  ${un.RegCleanProtocolHandler} "snews"

  ClearErrors
  ReadRegStr $R9 HKCR "Spicebird.EML" ""
  ; Don't clean up the file handlers if the Spicebird.EML key still exists
  ; since there could be a second installation that may be the default file
  ; handler.
  ${If} ${Errors}
    ${un.RegCleanFileHandler}  ".eml"   "Spicebird.EML"
    ${un.RegCleanFileHandler}  ".wdseml" "Spicebird.EML"
    DeleteRegValue HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\explorer\KindMap" ".wdseml"
    ; It doesn't matter if the value didn't exist
    ClearErrors
  ${EndIf}

  SetShellVarContext all  ; Set SHCTX to HKLM
  ${un.GetSecondInstallPath} "Software\Synovel" $R9
  ${If} $R9 == "false"
    SetShellVarContext current  ; Set SHCTX to HKCU
    ${un.GetSecondInstallPath} "Software\Synovel" $R9
  ${EndIf}

  StrCpy $0 "Software\Clients\Mail\${ClientsRegName}\shell\open\command"
  ReadRegStr $R1 HKLM "$0" ""
  ${un.RemoveQuotesFromPath} "$R1" $R1
  ${un.GetParent} "$R1" $R1

  ; Only remove the Clients\Mail and Clients\News key if it refers to this 
  ; install location. The Clients\Mail & Clients\News keys are independent 
  ; of the default app for the OS settings. The XPInstall base un-installer 
  ; always removes these keys if it is uninstalling the default app and it 
  ; will always replace the keys when installing even if there is another 
  ; install of Spicebird that is set as the
  ; default app. Now the keys are always updated on install but are only
  ; removed if they refer to this install location.
  ${If} "$INSTDIR" == "$R1"
    DeleteRegKey HKLM "Software\Clients\Mail\${ClientsRegName}"
    DeleteRegKey HKLM "Software\Clients\News\${ClientsRegName}"
    DeleteRegKey HKLM "Software\Clients\Calendar\${ClientsRegName}"
    DeleteRegValue HKLM "Software\RegisteredApplications" "${AppRegNameMail}"
    DeleteRegValue HKLM "Software\RegisteredApplications" "${AppRegNameNews}"
    DeleteRegValue HKLM "Software\RegisteredApplications" "${AppRegNameCalendar}"
  ${EndIf}

  StrCpy $0 "Software\Microsoft\Windows\CurrentVersion\App Paths\${FileMainEXE}"
  ${If} $R9 == "false"
    DeleteRegKey HKLM "$0"
    DeleteRegKey HKCU "$0"
  ${Else}
    ReadRegStr $R1 HKLM "$0" ""
    ${un.RemoveQuotesFromPath} "$R1" $R1
    ${un.GetParent} "$R1" $R1
    ${If} "$INSTDIR" == "$R1"
      WriteRegStr HKLM "$0" "" "$R9"
      ${un.GetParent} "$R9" $R1
      WriteRegStr HKLM "$0" "Path" "$R1"
    ${EndIf}
  ${EndIf}

  ; Remove directories and files we always control before parsing the uninstall
  ; log so empty directories can be removed.
  ${If} ${FileExists} "$INSTDIR\updates"
    RmDir /r /REBOOTOK "$INSTDIR\updates"
  ${EndIf}
  ${If} ${FileExists} "$INSTDIR\defaults\shortcuts"
    RmDir /r /REBOOTOK "$INSTDIR\defaults\shortcuts"
  ${EndIf}
  ${If} ${FileExists} "$INSTDIR\distribution"
    RmDir /r /REBOOTOK "$INSTDIR\distribution"
  ${EndIf}
  ${If} ${FileExists} "$INSTDIR\removed-files"
    Delete /REBOOTOK "$INSTDIR\removed-files"
  ${EndIf}

  ; Application update won't add these files to the uninstall log so delete
  ; them if they still exist.
  ${If} ${FileExists} "$INSTDIR\MapiProxy_InUse.dll"
    Delete /REBOOTOK "$INSTDIR\MapiProxy_InUse.dll"
  ${EndIf}
  ${If} ${FileExists} "$INSTDIR\mozMapi32_InUse.dll"
    Delete /REBOOTOK "$INSTDIR\mozMapi32_InUse.dll"
  ${EndIf}

  ; Remove the updates directory for Vista and above
  ${un.CleanUpdatesDir} "Spicebird"

  ; Remove files that may be left behind by the application in the
  ; VirtualStore directory.
  ${un.CleanVirtualStore}

  ; Parse the uninstall log to unregister dll's and remove all installed
  ; files / directories this install is responsible for.
  ${un.ParseUninstallLog}

  ; Remove the uninstall directory that we control
  RmDir /r /REBOOTOK "$INSTDIR\uninstall"

  ; Remove the installation directory if it is empty
  ${RemoveDir} "$INSTDIR"

  ; If spicebird.exe was successfully deleted yet we still need to restart to
  ; remove other files create a dummy spicebird.exe.moz-delete to prevent the
  ; installer from allowing an install without restart when it is required
  ; to complete an uninstall.
  ${If} ${RebootFlag}
    ${Unless} ${FileExists} "$INSTDIR\${FileMainEXE}.moz-delete"
      FileOpen $0 "$INSTDIR\${FileMainEXE}.moz-delete" w
      FileWrite $0 "Will be deleted on restart"
      Delete /REBOOTOK "$INSTDIR\${FileMainEXE}.moz-delete"
      FileClose $0
    ${EndUnless}
  ${EndIf}

  ; Refresh desktop icons otherwise the start menu internet item won't be
  ; removed and other ugly things will happen like recreation of the app's
  ; clients registry key by the OS under some conditions.
  System::Call "shell32::SHChangeNotify(i, i, i, i) v (0x08000000, 0, 0, 0)"
SectionEnd

################################################################################
# Helper Functions

; Don't setup the survey controls, functions, etc. when the application has
; defined NO_UNINSTALL_SURVEY
!ifndef NO_UNINSTALL_SURVEY
Function un.Survey
  ExecShell "open" "${SurveyURL}"
FunctionEnd
!endif

################################################################################
# Language

!insertmacro MOZ_MUI_LANGUAGE 'baseLocale'
!verbose push
!verbose 3
!include "overrideLocale.nsh"
!include "customLocale.nsh"
!verbose pop

; Set this after the locale files to override it if it is in the locale. Using
; " " for BrandingText will hide the "Nullsoft Install System..." branding.
BrandingText " "

################################################################################
# Page pre, show, and leave functions

Function un.preWelcome
  ${If} ${FileExists} "$INSTDIR\distribution\modern-wizard.bmp"
    Delete "$PLUGINSDIR\modern-wizard.bmp"
    CopyFiles /SILENT "$INSTDIR\distribution\modern-wizard.bmp" "$PLUGINSDIR\modern-wizard.bmp"
  ${EndIf}
FunctionEnd

Function un.leaveWelcome
  ${If} ${FileExists} "$INSTDIR\${FileMainEXE}"
    Banner::show /NOUNLOAD "$(BANNER_CHECK_EXISTING)"

    ${If} "$TmpVal" == "FoundMessageWindow"
      Sleep 5000
    ${EndIf}

    ${PushFilesToCheck}

    ${un.CheckForFilesInUse} $TmpVal

    Banner::destroy

    ${If} "$TmpVal" == "true"
      StrCpy $TmpVal "FoundMessageWindow"
      ${un.ManualCloseAppPrompt} "${WindowClass}" "$(WARN_MANUALLY_CLOSE_APP_UNINSTALL)"
      StrCpy $TmpVal "true"
    ${EndIf}
  ${EndIf}
FunctionEnd

Function un.preConfirm
  ${If} ${FileExists} "$INSTDIR\distribution\modern-header.bmp"
  ${AndIf} $hHeaderBitmap == ""
    Delete "$PLUGINSDIR\modern-header.bmp"
    CopyFiles /SILENT "$INSTDIR\distribution\modern-header.bmp" "$PLUGINSDIR\modern-header.bmp"
    ${un.ChangeMUIHeaderImage} "$PLUGINSDIR\modern-header.bmp"
  ${EndIf}

  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Settings" NumFields "3"

  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 1" Type   "label"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 1" Text   "$(UN_CONFIRM_UNINSTALLED_FROM)"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 1" Left   "0"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 1" Right  "-1"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 1" Top    "5"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 1" Bottom "15"

  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 2" Type   "text"
  ; The contents of this control must be set as follows in the pre function
  ; ${MUI_INSTALLOPTIONS_READ} $1 "unconfirm.ini" "Field 2" "HWND"
  ; SendMessage $1 ${WM_SETTEXT} 0 "STR:$INSTDIR"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 2" State  ""
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 2" Left   "0"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 2" Right  "-1"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 2" Top    "17"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 2" Bottom "30"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 2" flags  "READONLY"

  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 3" Type   "label"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 3" Text   "$(UN_CONFIRM_CLICK)"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 3" Left   "0"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 3" Right  "-1"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 3" Top    "130"
  WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 3" Bottom "150"

  ${If} "$TmpVal" == "true"
    WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 4" Type   "label"
    WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 4" Text   "$(SUMMARY_REBOOT_REQUIRED_UNINSTALL)"
    WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 4" Left   "0"
    WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 4" Right  "-1"
    WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 4" Top    "35"
    WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Field 4" Bottom "45"

    WriteINIStr "$PLUGINSDIR\unconfirm.ini" "Settings" NumFields "4"
  ${EndIf}

  !insertmacro MUI_HEADER_TEXT "$(UN_CONFIRM_PAGE_TITLE)" "$(UN_CONFIRM_PAGE_SUBTITLE)"
  ; The Summary custom page has a textbox that will automatically receive
  ; focus. This sets the focus to the Install button instead.
  !insertmacro MUI_INSTALLOPTIONS_INITDIALOG "unconfirm.ini"
  GetDlgItem $0 $HWNDPARENT 1
  System::Call "user32::SetFocus(i r0, i 0x0007, i,i)i"
  ${MUI_INSTALLOPTIONS_READ} $1 "unconfirm.ini" "Field 2" "HWND"
  SendMessage $1 ${WM_SETTEXT} 0 "STR:$INSTDIR"
  !insertmacro MUI_INSTALLOPTIONS_SHOW
FunctionEnd

Function un.leaveConfirm
  ; Try to delete the app executable and if we can't delete it try to find the
  ; app's message window and prompt the user to close the app. This allows
  ; running an instance that is located in another directory. If for whatever
  ; reason there is no message window we will just rename the app's files and
  ; then remove them on restart if they are in use.
  ClearErrors
  ${DeleteFile} "$INSTDIR\${FileMainEXE}"
  ${If} ${Errors}
    ${un.ManualCloseAppPrompt} "${WindowClass}" "$(WARN_MANUALLY_CLOSE_APP_UNINSTALL)"
  ${EndIf}
FunctionEnd

!ifndef NO_UNINSTALL_SURVEY
Function un.preFinish
  ; Do not modify the finish page if there is a reboot pending
  ${Unless} ${RebootFlag}
    ; Don't display the option to take a survey on the finish page if the OS is
    ; Vista or above since the process will be running elevated.
    ${If} ${AtLeastWinVista}
      !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "settings" "NumFields" "3"
    ${Else}
      ; When we add an optional action to the finish page the cancel button
      ; is enabled. This disables it and leaves the finish button as the
      ; only choice.
      !insertmacro MUI_INSTALLOPTIONS_WRITE "ioSpecial.ini" "settings" "cancelenabled" "0"
    ${EndIf}
  ${EndUnless}
FunctionEnd
!endif

################################################################################
# Initialization Functions

Function .onInit
  ${UninstallOnInitCommon}
FunctionEnd

Function un.onInit
  ${un.GetParent} "$INSTDIR" $INSTDIR
  ${un.GetLongPath} "$INSTDIR" $INSTDIR
  ${Unless} ${FileExists} "$INSTDIR\${FileMainEXE}"
    Abort
  ${EndUnless}

  StrCpy $LANGUAGE 0
  ${un.SetBrandNameVars} "$INSTDIR\distribution\setup.ini"

  ; Initialize $hHeaderBitmap to prevent redundant changing of the bitmap if
  ; the user clicks the back button
  StrCpy $hHeaderBitmap ""

  !insertmacro InitInstallOptionsFile "unconfirm.ini"
FunctionEnd

Function .onGUIEnd
  ${OnEndCommon}
FunctionEnd

Function un.onGUIEnd
  ${un.OnEndCommon}
FunctionEnd
