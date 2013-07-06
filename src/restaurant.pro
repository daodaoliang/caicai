#-------------------------------------------------
#
# Project created by QtCreator 2012-08-23T20:18:46
#
#-------------------------------------------------

QT       += core gui sql network

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
    functionwidget.cpp \
    printerwidget.cpp \
    printerprocesser.cpp \
    configerfileprocesser.cpp
    vipmanager.cpp \
    sqlmanager.cpp \
    cardreadermanager.cpp

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
    configerfileprocesser.h
    vipmanager.h \
    sqlmanager.h \
    cardreadermanager.h

RESOURCES += \
    src.qrc

FORMS += \
    functionwidget.ui \
    printerwidget.ui
