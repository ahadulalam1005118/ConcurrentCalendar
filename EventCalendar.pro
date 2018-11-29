#-------------------------------------------------
#
# Project created by QtCreator 2018-11-24T20:36:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EventCalendar
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    loginwindow.cpp \
    client.cpp

HEADERS  += mainwindow.h \
    loginwindow.h \
    client.h

FORMS    += mainwindow.ui \
    loginwindow.ui

DISTFILES += \
    configurations
