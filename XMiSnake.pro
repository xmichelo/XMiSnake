# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = XMiSnake
DESTDIR = ./_build/Win32/Release
QT += core opengl widgets gui
CONFIG += release
DEFINES += QT_DLL QT_OPENGL_LIB QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Release
LIBS += -lopengl32 \
    -lglu32
PRECOMPILED_HEADER = StdAfx.h
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(XMiSnake.pri)
win32:RC_FILE = XMiSnake.rc
