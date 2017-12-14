#-------------------------------------------------
#
# Project created by QtCreator 2014-11-17T23:17:53
#
#-------------------------------------------------

QT       += core gui sql quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include('../../../app.pri')

TARGET = app
TEMPLATE = app

DESTDIR = ../../../bin

LIBS += -lavCore$${LIB_SUFFIX}1
LIBS += -lavModules$${LIB_SUFFIX}1
LIBS += -ltickets$${LIB_SUFFIX}1

SOURCES += main.cpp\
        mainform.cpp \
    ../CustomWidgets/avmainmenu.cpp

HEADERS  += mainform.h \
    ../CustomWidgets/avmainmenu.h
FORMS    += mainform.ui

INCLUDEPATH += ../../libs/avModules
INCLUDEPATH += ../../libs/avCore
INCLUDEPATH += ../../libs/tickets

RESOURCES += \
    ../../resources/resource.qrc

DISTFILES += \
    qml/MenuBackButton.qml \
    qml/main.qml \
    qml/BtnMenuItem.qml
