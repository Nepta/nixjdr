#-------------------------------------------------
#
# Project created by QtCreator 2014-04-30T18:48:32
#
#-------------------------------------------------

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# SFML
LIBS += -L /usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

TARGET = jdrnix.out
TEMPLATE = app
DESTDIR = ../

SOURCES += \
    main.cpp\
    mainwindow.cpp \
    startdialog.cpp \
    user.cpp \
    tokenmenu.cpp \
    dicemenu.cpp \
    CustomMdiArea.cpp \
    QTSFML/Canvas.cpp \
    QTSFML/Map.cpp \
    QTSFML/Action.cpp \
    QTSFML/ActionChooser.cpp \
    QTSFML/TokenNoAction.cpp \
    QTSFML/SpriteList.cpp \
    QTSFML/QTSFMLMdiSubwindow.cpp \
    chat/chatserver.cpp \
    chat/chatcommon.cpp \
    chat/chatclient.cpp \
    chat/chatheader.cpp \
    chat/ChatProcessor.cpp \
    chat/commands/abstractchatcmd.cpp \
    chat/commands/chatcmdmessageall.cpp \
    chat/commands/chatcmdnickname.cpp \
    chat/commands/chatcmdwhisper.cpp \
    chat/commands/chatcmds.cpp \
    chat/commands/chatcmdmessageui.cpp \
    chat/commands/chatcmdnicknameack.cpp \
    chat/commands/chatcmdwhisperrep.cpp \
    chat/commands/chatcmdroll.cpp \
    chat/commands/chatcmddisconnect.cpp \
    chat/commands/CmdNicknamesList.cpp \
    chat/commands/CmdNicknamesListAck.cpp

HEADERS  += \
    mainwindow.h \
    startdialog.h \
    user.h \
    tokenmenu.h \
    dicemenu.h \
    CustomMdiArea.h \
    QTSFML/Canvas.h \
    QTSFML/Map.h \
    QTSFML/Action.h \
    QTSFML/ActionChooser.h \
    QTSFML/GraphicAction.h \
    QTSFML/SpriteList.h \
    QTSFML/TokenAddAction.h \
    QTSFML/TokenDelAction.h \
    QTSFML/TokenMoveAction.h \
    QTSFML/TokenNoAction.h \
    QTSFML/QTSFMLMdiSubwindow.h \
    chat/chatserver.h \
    chat/chatcommon.h \
    chat/chatclient.h \
    chat/chatheader.h \
    chat/chatprocessor.h \
    chat/commands/abstractchatcmd.h \
    chat/commands/chatcmdmessageall.h \
    chat/commands/chatcmdnickname.h \
    chat/commands/chatcmdwhisper.h \
    chat/commands/chatcmds.h \
    chat/commands/chatcmdmessageui.h \
    chat/commands/chatcmdnicknameack.h \
    chat/commands/chatcmdwhisperrep.h \
    chat/commands/chatcmdroll.h \
    chat/commands/chatcmddisconnect.h \
    chat/commands/CmdNicknamesList.h \
    chat/commands/CmdNicknamesListAck.h

FORMS    += mainwindow.ui \
    tokenmenu.ui \
    dicemenu.ui
