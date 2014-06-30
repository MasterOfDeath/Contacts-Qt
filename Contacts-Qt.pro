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


SOURCES += main.cpp\
        mainwindow.cpp \
    databasehandler.cpp \
    person.cpp \
    customwidget.cpp \
    detaildelegate.cpp

HEADERS  += mainwindow.h \
    databasehandler.h \
    person.h \
    customwidget.h \
    detaildelegate.h

FORMS    += mainwindow.ui \
    customlistviewitem.ui

RESOURCES += \
    resources/icons.qrc

win32:RC_ICONS += resources/icons/ic_launcher.ico
