TEMPLATE = app
TARGET = XMiSnake
DESTDIR = ./_build/Win32/Release
QT += core opengl widgets gui
CONFIG += release
CONFIG += c++11
DEFINES += QT_DLL QT_OPENGL_LIB QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Release
win32 {
LIBS += -lopengl32 \
    -lglu32
}
PRECOMPILED_HEADER = stdafx.h
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(XMiSnake.pri)
win32:RC_FILE = XMiSnake.rc
macx:PRECOMPILED_HEADER = stdafx.h
