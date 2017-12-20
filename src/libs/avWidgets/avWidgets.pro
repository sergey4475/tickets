#-------------------------------------------------
#
# Project created by QtCreator 2017-12-14T23:59:22
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

include('../../../libs.pri')
include(avSelectEdit/avSelectEdit.pri)

TARGET = avWidgets$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += AVWIDGETS_LIBRARY

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
        avwidgets_global.h  

unix {
    target.path = /usr/lib
    INSTALLS += target
}
