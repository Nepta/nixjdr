#-------------------------------------------------
#
# Project created by QtCreator 2014-04-30T18:48:32
#
#-------------------------------------------------

QT       += core gui network
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jdrnix
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    startdialog.cpp \
    chatserver.cpp \
    chatcommon.cpp \
    chatclient.cpp \
    user.cpp \
    chatheader.cpp

HEADERS  += mainwindow.h \
    startdialog.h \
    chatserver.h \
    chatcommon.h \
    chatclient.h \
    user.h \
    chatheader.h

FORMS    += mainwindow.ui
