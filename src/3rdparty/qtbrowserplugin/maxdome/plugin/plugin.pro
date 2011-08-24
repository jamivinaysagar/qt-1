TARGET      	= CEPlugin

SOURCES		= CEPlugin.cpp

win32 {
   RC_FILE		= plugin.rc
} else:mac {
   QMAKE_INFO_PLIST = Info.plist
   REZ_FILES += plugin.r
   rsrc_files.files = plugin.rsrc
   rsrc_files.path = Contents/Resources
   QMAKE_BUNDLE_DATA += rsrc_files
}

include(../../src/qtbrowserplugin.pri)

HEADERS += \
    CEPlugin.h
