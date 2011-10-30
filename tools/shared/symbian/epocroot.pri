# Epocroot resolving is only required for tools, so omit it from all mobile/embedded builds
!symbian:!wince*:!embedded:!mac:!linux:!unix {
HEADERS += \
        ../../../tools/shared/symbian/epocroot_p.h \
        ../../../tools/shared/windows/registry_p.h
SOURCES += \
        ../../../tools/shared/symbian/epocroot.cpp \
        ../../../tools/shared/windows/registry.cpp
INCLUDEPATH += ../../../tools/shared
DEFINES += QLIBRARYINFO_EPOCROOT
}
