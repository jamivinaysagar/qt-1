TARGET      = $$qtLibraryTarget(qaxwidget)
TEMPLATE    = lib
QTDIR_build:DESTDIR 	= ../../../../../plugins/designer

CONFIG     += qt warn_on qaxcontainer plugin designer debug_and_release
build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

INCLUDEPATH += ../../../../../src/activeqt/shared/ \
               ../../../../../src/activeqt/container \
               ../../lib/uilib

# Input
SOURCES += qaxwidgetextrainfo.cpp \
qaxwidgetplugin.cpp \
qdesigneraxwidget.cpp \
qaxwidgetpropertysheet.cpp \
qaxwidgettaskmenu.cpp \
    ../../../../../src/activeqt/shared/qaxtypes.cpp

HEADERS += qaxwidgetextrainfo.h \
qaxwidgetplugin.h \
qdesigneraxwidget.h \
qaxwidgetpropertysheet.h \
qaxwidgettaskmenu.h \
    ../../../../../src/activeqt/shared/qaxtypes.h

# install
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target
