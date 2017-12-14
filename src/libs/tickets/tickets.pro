#-------------------------------------------------
#
# Project created by QtCreator 2016-04-02T22:32:20
#
#-------------------------------------------------

QT       += widgets sql

QT       -= gui

include('../../../libs.pri')

TARGET = tickets$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += TICKETS_LIBRARY

#DESTDIR = ../../../bin
#DESTDIR = $${BIN_PATH}/

#LIBS += -L../../../bin/ -lavCore
#LIBS += -L../../../bin/ -lavModules
#LIBS += -L../../../bin/ -lavWidgets

LIBS += -lavCore$${LIB_SUFFIX}1
LIBS += -lavModules$${LIB_SUFFIX}1


SOURCES += tickets.cpp

HEADERS += tickets.h\
        tickets_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ../../libs/avModules
INCLUDEPATH += ../../libs/avCore
INCLUDEPATH += ../../libs/avWidgets
