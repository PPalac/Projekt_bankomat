#-------------------------------------------------
#
# Project created by QtCreator 2016-10-22T14:06:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projekt_bankomat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    operations.cpp \
    addnew.cpp \
    sendmail.cpp \
    base64.cpp \
    account.cpp \
    manage.cpp

HEADERS  += mainwindow.h \
    operations.h \
    addnew.h \
    account.h \
    sendmail.h \
    base64.h \
    manage.h

FORMS    += mainwindow.ui \
    addnew.ui \
    manage.ui

DISTFILES +=
