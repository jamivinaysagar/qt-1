TEMPLATE = lib
CONFIG += plugin
QT += opengl gui

QTDIR_build:DESTDIR = $$QT_BUILD_TREE/plugins/gfxdrivers

TARGET = intelcescreen
target.path = $$[QT_INSTALL_PLUGINS]/gfxdrivers
INSTALLS += target

HEADERS	= intelcescreen.h \
          intelcesurface.h \
		  intelcecursor.h
SOURCES	= intelcescreen.cpp \
          intelcesurface.cpp \
          intelceplugin.cpp \
		  intelcecursor.cpp

INCLUDEPATH += ${QT_SOURCE}/include/Qt
LIBS += -L ${CANMORE_SDK}/lib -l gdl
