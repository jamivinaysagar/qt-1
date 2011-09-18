TEMPLATE        = app
TARGET          = lrelease
DESTDIR         = ../../../bin

DEFINES += QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII
SOURCES += main.cpp

INCLUDEPATH += ../../../src/corelib/global # qlibraryinfo.cpp includes qconfig.cpp
SOURCES += \
    ../../../src/corelib/global/qlibraryinfo.cpp \
    ../../../src/corelib/io/qsettings.cpp
win32:SOURCES += ../../../src/corelib/io/qsettings_win.cpp
macx:SOURCES += ../../../src/corelib/io/qsettings_mac.cpp

include(../../../src/tools/bootstrap/bootstrap.pri)
include(../shared/formats.pri)
include(../shared/proparser.pri)
include(../../shared/symbian/epocroot.pri)

win32:LIBS += -ladvapi32   # for qsettings_win.cpp

target.path=$$[QT_INSTALL_BINS]
INSTALLS        += target
