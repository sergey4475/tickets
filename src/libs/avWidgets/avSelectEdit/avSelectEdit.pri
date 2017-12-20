contains(TARGET, plugin){
    HEADERS += ../../../plugins/designer_plugin/qslistwidgetplugin.h
    SOURCES += ../../../plugins/designer_plugin/qslistwidgetplugin.cpp
}else{
    HEADERS += $$PWD/avselectedit.h
    SOURCES += $$PWD/avselectedit.cpp
}

RESOURCES += \
    $$PWD/resource.qrc
