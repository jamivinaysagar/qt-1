TARGET = qintelceirkbddriver
include(../../qpluginbase.pri)

QTDIR_build:DESTDIR = $$QT_BUILD_TREE/plugins/kbddrivers
target.path = $$[QT_INSTALL_PLUGINS]/kbddrivers
INSTALLS += target

DEFINES += QT_QWS_KBD_INTELCE_IR  

HEADERS	= qkbdintelceir.h

SOURCES	= main.cpp qkbdintelceir.cpp NRD_IRReceiver.cpp

QT += xml
