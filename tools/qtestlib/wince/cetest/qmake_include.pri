#qmake source files needed for cetest
HEADERS += \
           ../../../../qmake/option.h
SOURCES += \
           ../../../../qmake/option.cpp \
           ../../../../qmake/project.cpp \
           ../../../../qmake/property.cpp \
           ../../../../qmake/generators/metamakefile.cpp \
           ../../../../qmake/generators/symbian/initprojectdeploy_symbian.cpp \
           ../../../../tools/shared/symbian/epocroot.cpp \
           ../../../../tools/shared/windows/registry.cpp

DEFINES += QT_QMAKE_PARSER_ONLY
