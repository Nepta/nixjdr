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
    user.cpp \
    chat/chatserver.cpp \
    chat/chatcommon.cpp \
    chat/chatclient.cpp \
    chat/chatheader.cpp \
    chat/commands/abstractchatcmd.cpp \
    chat/commands/chatcmdmessageall.cpp \
    chat/commands/chatcmdnickname.cpp \
    chat/commands/chatcmdwhisper.cpp \
    chat/commands/chatcmds.cpp \
    chat/commands/chatcmdmessageui.cpp \
    chat/commands/chatcmdnicknameack.cpp \
    chat/commands/chatcmdwhisperrep.cpp

HEADERS  += mainwindow.h \
    startdialog.h \
    user.h \
    chat/chatserver.h \
    chat/chatcommon.h \
    chat/chatclient.h \
    chat/chatheader.h \
    chat/commands/abstractchatcmd.h \
    chat/commands/chatcmdmessageall.h \
    chat/commands/chatcmdnickname.h \
    chat/commands/chatcmdwhisper.h \
    chat/commands/chatcmds.h \
    chat/commands/chatcmdmessageui.h \
    chat/commands/chatcmdnicknameack.h \
    chat/commands/chatcmdwhisperrep.h

FORMS    += mainwindow.ui
