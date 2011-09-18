TARGET    = configure
DESTDIR   = $$PWD/../..  # build directly in source dir

CONFIG   += console flat
CONFIG   -= moc qt
DEFINES  = UNICODE QT_NODLL QT_NO_CODECS QT_NO_TEXTCODEC QT_NO_UNICODETABLES QT_LITE_COMPONENT QT_NO_STL QT_NO_COMPRESS QT_NO_THREAD QT_NO_QOBJECT _CRT_SECURE_NO_DEPRECATE
DEFINES  += QT_BOOTSTRAPPED

win32 : LIBS += -lole32 -ladvapi32
win32-msvc.net | win32-msvc2* : QMAKE_CXXFLAGS += /EHsc
win32-g++* : LIBS += -luuid

win32-msvc* {
    QMAKE_CFLAGS_RELEASE -= -MD
    QMAKE_CFLAGS_RELEASE += -MT
    QMAKE_CFLAGS_DEBUG -= -MDd
    QMAKE_CFLAGS_DEBUG += -MTd
    QMAKE_CXXFLAGS_RELEASE -= -MD
    QMAKE_CXXFLAGS_RELEASE += -MT
    QMAKE_CXXFLAGS_DEBUG -= -MDd
    QMAKE_CXXFLAGS_DEBUG += -MTd
}

PRECOMPILED_HEADER = configure_pch.h

INCLUDEPATH += \
           ../../src/corelib/arch/generic \
           ../../src/corelib/global \
           $$QT_BUILD_TREE/include \
           $$QT_BUILD_TREE/include/QtCore \
           ../../tools/shared

HEADERS  = configureapp.h environment.h tools.h\
           ../../src/corelib/tools/qbytearray.h \
           ../../src/corelib/tools/qbytearraymatcher.h \
           ../../src/corelib/tools/qchar.h \
           ../../src/corelib/tools/qhash.h \
           ../../src/corelib/tools/qlist.h \
           ../../src/corelib/tools/qlocale.h \
           ../../src/corelib/tools/qvector.h \
           ../../src/corelib/codecs/qutfcodec_p.h \
           ../../src/corelib/codecs/qtextcodec.h \
           ../../src/corelib/global/qglobal.h \
           ../../src/corelib/global/qnumeric.h \
           ../../src/corelib/io/qbuffer.h \
           ../../src/corelib/io/qdatastream.h \
           ../../src/corelib/io/qdir.h \
           ../../src/corelib/io/qdiriterator.h \
           ../../src/corelib/io/qfile.h \
           ../../src/corelib/io/qfileinfo.h \
           ../../src/corelib/io/qfsfileengine.h \
           ../../src/corelib/io/qfsfileengine_iterator_p.h \
           ../../src/corelib/io/qiodevice.h \
           ../../src/corelib/io/qtextstream.h \
           ../../src/corelib/io/qtemporaryfile.h \
           ../../src/corelib/tools/qbitarray.h \
           ../../src/corelib/tools/qdatetime.h \
           ../../src/corelib/tools/qmap.h \
           ../../src/corelib/tools/qregexp.h \
           ../../src/corelib/tools/qstring.h \
           ../../src/corelib/tools/qstringlist.h \
           ../../src/corelib/tools/qstringmatcher.h \
           ../../src/corelib/tools/qunicodetables_p.h \
           ../../src/corelib/xml/qxmlstream.h \
           ../../src/corelib/xml/qxmlutils_p.h \
           ../../tools/shared/symbian/epocroot_p.h \
           ../../tools/shared/windows/registry_p.h


SOURCES  = main.cpp configureapp.cpp environment.cpp tools.cpp \
           ../../src/corelib/tools/qbytearray.cpp \
           ../../src/corelib/tools/qbytearraymatcher.cpp \
           ../../src/corelib/tools/qchar.cpp \
           ../../src/corelib/tools/qhash.cpp \
           ../../src/corelib/tools/qlist.cpp \
           ../../src/corelib/tools/qlocale.cpp \
           ../../src/corelib/tools/qvector.cpp \
           ../../src/corelib/codecs/qutfcodec.cpp \
           ../../src/corelib/codecs/qtextcodec.cpp \
           ../../src/corelib/global/qglobal.cpp \
           ../../src/corelib/global/qnumeric.cpp \
           ../../src/corelib/io/qbuffer.cpp \
           ../../src/corelib/io/qdatastream.cpp \
           ../../src/corelib/io/qdir.cpp \
           ../../src/corelib/io/qdiriterator.cpp \
           ../../src/corelib/io/qfile.cpp \
           ../../src/corelib/io/qfileinfo.cpp \
           ../../src/corelib/io/qabstractfileengine.cpp \
           ../../src/corelib/io/qfsfileengine.cpp \
           ../../src/corelib/io/qfsfileengine_iterator.cpp \
           ../../src/corelib/io/qfsfileengine_iterator_win.cpp \
           ../../src/corelib/io/qiodevice.cpp \
           ../../src/corelib/io/qtextstream.cpp \
           ../../src/corelib/io/qtemporaryfile.cpp \
           ../../src/corelib/plugin/qsystemlibrary.cpp \
           ../../src/corelib/tools/qbitarray.cpp \
           ../../src/corelib/tools/qdatetime.cpp \
           ../../src/corelib/tools/qmap.cpp \
           ../../src/corelib/tools/qregexp.cpp \
           ../../src/corelib/tools/qstring.cpp \
           ../../src/corelib/tools/qstringlist.cpp \
           ../../src/corelib/tools/qstringmatcher.cpp \
           ../../src/corelib/tools/qunicodetables.cpp \
           ../../src/corelib/tools/qvsnprintf.cpp \
           ../../src/corelib/kernel/qvariant.cpp \
           ../../src/corelib/io/qurl.cpp \
           ../../src/corelib/tools/qline.cpp \
           ../../src/corelib/tools/qsize.cpp \
           ../../src/corelib/tools/qpoint.cpp \
           ../../src/corelib/tools/qrect.cpp \
           ../../src/corelib/kernel/qmetatype.cpp \
           ../../src/corelib/global/qmalloc.cpp \
           ../../src/corelib/xml/qxmlstream.cpp \
           ../../src/corelib/xml/qxmlutils.cpp \
           ../../tools/shared/symbian/epocroot.cpp \
           ../../tools/shared/windows/registry.cpp

win32:SOURCES += ../../src/corelib/io/qfsfileengine_win.cpp

DEFINES += COMMERCIAL_VERSION

INCLUDEPATH += ../../src/corelib/arch/generic \
               ../../include/QtCore \
               ../../tools/shared
