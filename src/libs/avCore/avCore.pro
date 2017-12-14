#-------------------------------------------------
#
# Project created by QtCreator 2014-11-22T19:52:37
#
#-------------------------------------------------

QT       += core xml
QT       -= gui

include('../../../libs.pri')

TARGET = avCore$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += AVCORE_LIBRARY

SOURCES += avcore.cpp \
    avxml.cpp

#DESTDIR = ../../../bin

#DESTDIR = $${BIN_PATH}/

HEADERS += avcore.h\
        avcore_global.h \
    avxml.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
