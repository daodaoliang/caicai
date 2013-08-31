#-------------------------------------------------
#
# Project created by QtCreator 2012-08-23T20:18:46
#
#-------------------------------------------------

QT       += core gui sql network
CONFIG  += qaxcontainer
TARGET = restaurant
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    sysbutton.cpp \
    mypushbutton.cpp \
    titlewidget.cpp \
    toolbutton.cpp \
    toolwidget.cpp \
    statuswidget.cpp \
    contentwidget.cpp \
    skinwidget.cpp \
    printerwidget.cpp \
    printerprocesser.cpp \
    configerfileprocesser.cpp \
    vipmanager.cpp \
    sqlmanager.cpp \
    cardreadermanager.cpp \
    functionwidget.cpp \
    dinnerwidget.cpp \
    windowseventhandler.cpp \
    icommandhandler.cpp \
    tabledelegate.cpp \
    vipwidget.cpp \
    readonlydelegate.cpp \
    orderhelper.cpp \
    dishestypedelegeate.cpp \
    dishesdelegate.cpp \
    dishescountwidget.cpp \
    detailwidget.cpp \
    checkwidget.cpp \
    orderwidget.cpp \
    loginwidget.cpp \
    backprinter.cpp \
    frontprinter.cpp \
    adddiningtablewidget.cpp \
    dinnertabledata.cpp \
    tablewidget.cpp \
    dishesinfobll.cpp \
    orderdata.cpp \
    dinnertablebll.cpp \
    statiswidget.cpp \
    excelengine.cpp \
    dishesdata.cpp \
    logmsg.cpp \
    fileoperate.cpp \
    carddetailwidget.cpp \
    membercustomwidget.cpp \
    backwidget.cpp \
    userwidget.cpp


HEADERS  += mainwidget.h \
    sysbutton.h \
    mypushbutton.h \
    titlewidget.h \
    toolbutton.h \
    toolwidget.h \
    statuswidget.h \
    contentwidget.h \
    skinwidget.h \
    functionwidget.h \
    printerwidget.h \
    printerprocesser.h \
    configerfileprocesser.h \
    vipmanager.h \
    sqlmanager.h \
    cardreadermanager.h \
    function.h \
    dinnerwidget.h \
    windowseventhandler.h \
    icommandhandler.h \
    tabledelegate.h \
    vipwidget.h \
    readonlydelegate.h \
    orderhelper.h \
    dishestypedelegeate.h \
    dishesdelegate.h \
    dishescountwidget.h \
    detailwidget.h \
    checkwidget.h \
    orderwidget.h \
    loginwidget.h \
    backprinter.h \
    frontprinter.h \
    adddiningtablewidget.h \
    dinnertabledata.h \
    tablewidget.h \
    dishesinfobll.h \
    orderdata.h \
    dinnertablebll.h \
    statiswidget.h \
    excelengine.h \
    dishesdata.h \
    logmsg.h \
    fileoperate.h \
    carddetailwidget.h \
    membercustomwidget.h \
    backwidget.h \
    userwidget.h

RESOURCES += \
    src.qrc

FORMS += \
    functionwidget.ui \
    printerwidget.ui \
    dinnerwidget.ui \
    vipwidget.ui \
    dishescountwidget.ui \
    detailwidget.ui \
    checkwidget.ui \
    orderwidget.ui \
    loginwidget.ui \
    adddiningtablewidget.ui \
    tablewidget.ui \
    statiswidget.ui \
    carddetailwidget.ui \
    membercustomwidget.ui \
    backwidget.ui \
    userwidget.ui

#INCLUDEPATH += $$PWD/qwt/include
#LIBS += -L$$PWD/qwt/lib -lqwt
