CONFIG      += plugin debug_and_release

include('../../../libs.pri')

TARGET      = $$qtLibraryTarget(avwidgetstplugin)
TEMPLATE    = lib

HEADERS     = avselecteditplugin.h
SOURCES     = avselecteditplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -lavWidgets$${LIB_SUFFIX}1

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target


