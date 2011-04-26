CONFIG      += designer plugin debug_and_release
TARGET      = $$qtLibraryTarget(YRichEditorPlugin)
TEMPLATE    = lib

HEADERS     = yricheditorplugin.h
SOURCES     = yricheditorplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(yricheditor.pri)
