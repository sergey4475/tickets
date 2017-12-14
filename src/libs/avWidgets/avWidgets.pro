#-------------------------------------------------
#
# Project created by QtCreator 2014-11-22T00:05:07
#
#-------------------------------------------------

QT       += widgets sql

QT       -= gui

include('../../../libs.pri')

TARGET = avWidgets$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += AVWIDGETS_LIBRARY

LIBS += -lavCore$${LIB_SUFFIX}1

#DESTDIR = ../../../bin
#DESTDIR = $${BIN_PATH}/

SOURCES += \
    avLoginDialog.cpp

HEADERS +=\
        avwidgets_global.h \
    avLoginDialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ../avCore
