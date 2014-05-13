# This files contains the NSIS script for building the installer for KITRIS Visual SP
# Xavier Michelon
# 2012-05-26

!include "MUI2.nsh" # use the MUI2 scripts for better visual aspect
!include "LogicLib.nsh" # we use the logic lib for easy conditional statements
!include "nsDialogs.nsh" # used for custom dialog pages
!include "FileFunc.nsh" # file functions (used for GetSize)


#global defines ( basically compile time constants)
!define APP_FANCY_NAME "XMi Snake"
!define APP_NAME "XMiSnake"
!define EXE_SRC_DIR ..\_build\Win32\Release
!define UNINSTALLER_FILE_NAME Uninstall.exe
!define REGISTRY_UNINSTALLER_FOLDER Software\Microsoft\Windows\CurrentVersion\Uninstall
!define OUTPUT_DIR _build
!define VS_DEVENV_PATH "c:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\devenv.com"
!define VC_REDIST_RUNTIME_FILE "vcredist_x86.exe"
!define WEBSITE "http://x-mi.com/"
!define AUTHOR "Xavier Michelon"
!define COMPANY "x-mi.com"
!define VERSION_MAJOR 2
!define VERSION_MINOR 0
!define APP_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}"
!define LEFT_IMAGE_PATH "resources\installerLeftImage.bmp"
!define TOP_IMAGE_PATH "resources\installerTopImage.bmp"
!define APP_DATA_REGISTRY_KEY "Software\${COMPANY}\${APP_NAME}"
!define QT_DIR "c:\Qt\5.2.1_vs2013\qtbase"

# Settings for the Modern UI 2 NSIS plugin
!define MUI_WELCOMEFINISHPAGE_BITMAP ${LEFT_IMAGE_PATH}
!define MUI_UNWELCOMEFINISHPAGE_BITMAP ${LEFT_IMAGE_PATH}
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_RIGHT
!define MUI_HEADERIMAGE_BITMAP ${TOP_IMAGE_PATH}
!define MUI_HEADERIMAGE_UNBITMAP ${TOP_IMAGE_PATH}
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_UNFINISHPAGE_NOAUTOCLOSE

# Build the solution file and stop if the result is not 0
!system '"${VS_DEVENV_PATH}" "..\${APP_NAME}.sln" /rebuild "Release|Win32"' = 0


# General attributes for the installer/uninstaller
Name  "${APP_FANCY_NAME} v${VERSION_MAJOR}.${VERSION_MINOR}"
!system "mkdir ${OUTPUT_DIR}" # create the directory where the installer file will be created, if it does not exist yet
OutFile "${OUTPUT_DIR}\${APP_NAME}Installer.exe"
SetCompressor lzma # better result than default zlib, but slower
RequestExecutionLevel none
InstallDir "$PROGRAMFILES32\${APP_FANCY_NAME}"


#define the sequence of pages for the installer
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH


#define the sequence of pages for the uninstaller
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH


# Installer in english only. These call are not necessary but removes a lot of warning from the compiler output
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_RESERVEFILE_LANGDLL


###################################
# Installer initialization function
###################################
Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
  Call checkAlreadyInstalled
FunctionEnd


#######################################################
# install the VC Redistributable Runtime for VS2010 SP1
#######################################################
Function InstallVCRedistributableRuntime
   SetOutPath $TEMP
   ${Unless} ${FileExists} "$TEMP\${VC_REDIST_RUNTIME_FILE}"         
       DetailPrint "Installing VC++ 2013 Redistributable Runtime"         
       File "vendor\${VC_REDIST_RUNTIME_FILE}"
       ExecWait "$TEMP\${VC_REDIST_RUNTIME_FILE} /q"         
       DetailPrint "Cleaning up"         
       Delete $TEMP\${VC_REDIST_RUNTIME_FILE}     
   ${EndUnless}
FunctionEnd


###############################################
# Check if the application is already installed
###############################################
Function checkAlreadyInstalled
  Push $0 
  ReadRegStr $0 HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "UninstallString"
  ${If} $0 != ""
    MessageBox MB_YESNO|MB_ICONQUESTION "Before you can install ${APP_FANCY_NAME}, you must uninstall the version that is currently installed on your computer.$\n$\nDo you want to uninstall the previous version of ${APP_FANCY_NAME} ?" /SD IDNO IDYES yes IDNO no
no:
    Abort
yes:
    ExecWait '"$INSTDIR\${UNINSTALLER_FILE_NAME}" _?=$INSTDIR' # the _?=$INSTDIR means that the uninstaller will not copy itself but run from the installer folder, forcing ExecWait to actually wait for the uninstaller to finish.
  ${Endif}
  Pop $0
FunctionEnd


#########################################################################
# Retrieve the installation folder size - in kB - and put it on the stack 
# Do not call before all files are installed
#########################################################################
Function getInstallDirSize
  Push $0
  Push $1
  Push $2
  ${GetSize} "$INSTDIR" "/S=0K /G=1" $0 $1 $2 # File the size in MB of the Install dir, including subdirs
  Pop $2
  Pop $1
  Exch $0 # Exchange the value of $0 and the top of the Stack
FunctionEnd


# Definitions of the different installation types
InstType "Default" #1


#################
# Default Section
#################
Section "${APP_NAME}" secApp

SectionIn RO # This section is mandatory
SetShellVarContext all

call InstallVCRedistributableRuntime

# copy file
setOutPath $INSTDIR
file "${EXE_SRC_DIR}\${APP_NAME}.exe"
file "${QT_DIR}\bin\Qt5Core.dll"
file "${QT_DIR}\bin\Qt5Gui.dll"
file "${QT_DIR}\bin\Qt5Widgets.dll"
file "${QT_DIR}\bin\Qt5OpenGL.dll"
file "resources\ReadMe.txt"
file "resources\GPLv3.txt"
file "resources\OFL.txt"

setOutPath $INSTDIR\platforms
file "${QT_DIR}\plugins\platforms\qwindows.dll"

# Create uninstall
WriteUninstaller "${UNINSTALLER_FILE_NAME}"

# Add Windows registry keys for uninstaller
WriteRegStr HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "DisplayName" "${APP_FANCY_NAME}"
WriteRegStr HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "UninstallString" '"$INSTDIR\${UNINSTALLER_FILE_NAME}"'
WriteRegStr HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "InstallLocation" "$INSTDIR"
WriteRegStr HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "DisplayIcon" "$INSTDIR\${APP_NAME}.exe"
WriteRegStr HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "Publisher" "${COMPANY}"
WriteRegStr HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "RegOwner" "${AUTHOR}"
WriteRegStr HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "RegCompany" "${COMPANY}"
WriteRegStr HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "URLUpdateInfo" "${WEBSITE}"
WriteRegStr HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "URLInfoAbout" "${WEBSITE}"
WriteRegStr HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "DisplayVersion" "${APP_VERSION}"
WriteRegDWORD HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "VersionMajor" ${VERSION_MAJOR}
WriteRegDWORD HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "VersionMinor" ${VERSION_MINOR}
WriteRegDWORD HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "NoModify" 1
WriteRegDWORD HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "NoRepair" 1
Call getInstallDirSize
Pop $0
WriteRegDWORD HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}" "EstimatedSize" $0

SectionEnd


#############################
# Start menu shortcut section
#############################
Section "Start Menu Shortcuts" secStartMenuShortcuts

SectionIn 1 # This section is enabled for the Full and Default installation types
SetShellVarContext all # The shortcut in the start menu wil be created for all users

CreateDirectory "$SMPROGRAMS\${APP_FANCY_NAME}"
CreateShortCut "$SMPROGRAMS\${APP_FANCY_NAME}\${APP_FANCY_NAME}.lnk" "$INSTDIR\${APP_NAME}.exe" "" "$INSTDIR\${APP_NAME}.exe" 0
CreateShortCut "$SMPROGRAMS\${APP_FANCY_NAME}\Uninstall ${APP_FANCY_NAME}.lnk" "$INSTDIR\${UNINSTALLER_FILE_NAME}" "" "$INSTDIR\${UNINSTALLER_FILE_NAME}" 0

SectionEnd


##########################
# Desktop shortcut section
##########################
Section "Desktop Shortcut" secDesktopShortcut

SectionIn 1 # This section is enabled for the Full installation type only
SetShellVarContext current # The shortcut will be created for the current user only

CreateShortCut "$DESKTOP\${APP_FANCY_NAME}.lnk" "$INSTDIR\${APP_NAME}.exe" "" "$INSTDIR\${APP_NAME}.exe" 0

SectionEnd


#####################################
# Uninstaller
#####################################

Section "Uninstall"


# Remove application files and folders
SetShellVarContext all
Delete "$INSTDIR\${APP_NAME}.exe"
Delete "$INSTDIR\Qt5Core.dll"
Delete "$INSTDIR\Qt5Gui.dll"
Delete "$INSTDIR\Qt5Widgets.dll"
Delete "$INSTDIR\Qt5OpenGL.dll"
Delete "$INSTDIR\${UNINSTALLER_FILE_NAME}"
Delete "$INSTDIR\ReadMe.txt"
Delete "$INSTDIR\GPLv3.txt"
Delete "$INSTDIR\OFL.txt"
Delete "$INSTDIR\platforms\qwindows.dll"
RMDir "$INSTDIR\platforms"
RMDir "$INSTDIR"

# Remove registry keys that are used for the uninstaller
DeleteRegKey HKLM "${REGISTRY_UNINSTALLER_FOLDER}\${APP_NAME}"

# Remove Start menu entries, if any
Delete "$SMPROGRAMS\${APP_fANCY_NAME}\*.*"
RMDir "$SMPROGRAMS\${APP_FANCY_NAME}"

# Remove Desktop shortcut, if any
SetShellVarContext current
Delete "$DESKTOP\${APP_FANCY_NAME}.lnk"

SectionEnd
