#-------------------------------------------------
#
# Project created by QtCreator 2015-01-23T20:39:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wetm
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    cprojectfile.cpp \
    rasternet.cpp \
    params.cpp \
    dialogdata.cpp \
    cutilities.cpp \
    fireLib.c \
    cthreaddata.cpp \
    cfirebehavior.cpp \
    crasterdataset.cpp \
    ctriggers.cpp \
    crastertriggerinput.cpp

HEADERS  += \
    mainwindow.h \
    cprojectfile.h \
    rasternet.h \
    params.h \
    dialogdata.h \
    cutilities.h \
    fireLib.h \
    cthreaddata.h \
    cfirebehavior.h \
    crasterdataset.h \
    ctriggers.h \
    crastertriggerinput.h

FORMS    += mainwindow.ui \
    dialogdata.ui

RESOURCES += \
    myrsfile.qrc

