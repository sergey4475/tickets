#-------------------------------------------------
#
# Project created by QtCreator 2014-11-17T23:47:42
#
#-------------------------------------------------

QT       += sql widgets

QT       -= gui

include('../../../libs.pri')
include('./avUsers/avUsers.pri')
include('./avSql/avSql.pri')

TARGET = avModules$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += AVSQL_LIBRARY
LIBS += -lavCore$${LIB_SUFFIX}1

#DESTDIR = $${BIN_PATH}/

#SOURCES += avsql.cpp \
#    qsqlgenerator.cpp

#HEADERS += ./avSql/avsql.h\
#        avsql_global.h \
#    ./avSql/qsqlgenerator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
