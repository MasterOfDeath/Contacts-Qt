#-------------------------------------------------
#
# Project created by QtCreator 2014-06-12T10:38:18
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Contacts-Qt
TEMPLATE = app

include(qtxlsx/src/xlsx/qtxlsx.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    databasehandler.cpp \
    person.cpp \
    detaildelegate.cpp \
    searchdialog.cpp \
    toexcel.cpp

HEADERS  += mainwindow.h \
    databasehandler.h \
    person.h \
    detaildelegate.h \
    common.h \
    searchdialog.h \
    toexcel.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources/resources.qrc

win32:RC_ICONS += resources/icons/ic_launcher.ico

#CONFIG += c++11
