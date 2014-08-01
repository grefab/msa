#-------------------------------------------------
#
# Project created by QtCreator 2014-07-31T00:23:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MareikesStengelAnalysator
TEMPLATE = app

INCLUDEPATH += $$PWD

SOURCES += main.cpp\
        mainwindow.cpp \
    engine.cpp \
    zoompangraphicsview.cpp

HEADERS  += mainwindow.h \
    engine.h \
    zoompangraphicsview.h

FORMS    += mainwindow.ui
