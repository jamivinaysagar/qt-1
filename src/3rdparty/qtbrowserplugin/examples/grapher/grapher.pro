TARGET		= grapher

SOURCES		= grapher.cpp

# On Windows, uncomment the following line to build a plugin that can
# be used also in Internet Explorer, through ActiveX.
# CONFIG += qaxserver

win32 {
   RC_FILE		= grapher.rc
} else:mac {
   QMAKE_INFO_PLIST = Info.plist
   REZ_FILES += grapher.r
   rsrc_files.files = grapher.rsrc
   rsrc_files.path = Contents/Resources
   QMAKE_BUNDLE_DATA += rsrc_files
}

include(../../src/qtbrowserplugin.pri)
