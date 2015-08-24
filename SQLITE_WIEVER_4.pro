#-------------------------------------------------
#
# Project created by QtCreator 2015-08-07T12:53:40
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SQLITE_WIEVER_4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    createtable.cpp \
    deletetable.cpp

HEADERS  += mainwindow.h \
    createtable.h \
    deletetable.h \
    main.h

FORMS    += mainwindow.ui \
    createtable.ui \
    deletetable.ui

CONFIG += mobility
MOBILITY = 

