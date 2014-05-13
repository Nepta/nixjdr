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
    Main.cpp \
    MainWindow.cpp \
    StartDialog.cpp \
    User.cpp \
    TokenMenu.cpp \
    DiceMenu.cpp \
    CustomMdiArea.cpp \
    ChatWidget.cpp \
    QTSFML/Canvas.cpp \
    QTSFML/Map.cpp \
    QTSFML/Action.cpp \
    QTSFML/ActionChooser.cpp \
    QTSFML/TokenNoAction.cpp \
    QTSFML/SpriteList.cpp \
    QTSFML/MapMdiSubwindow.cpp \
    chat/ChatServer.cpp \
    chat/ChatCommon.cpp \
    chat/ChatClient.cpp \
    chat/ChatHeader.cpp \
    chat/ChatProcessor.cpp \
    chat/commands/AbstractCmd.cpp \
    chat/commands/CmdMessageall.cpp \
    chat/commands/CmdNickname.cpp \
    chat/commands/CmdWhisper.cpp \
    chat/commands/Commands.cpp \
    chat/commands/CmdMessageui.cpp \
    chat/commands/CmdNicknameAck.cpp \
    chat/commands/CmdWhisperRep.cpp \
    chat/commands/CmdRoll.cpp \
    chat/commands/CmdDisconnect.cpp \
    chat/commands/CmdNicknamesList.cpp \
    chat/commands/CmdNicknamesListAck.cpp \
	 ConnexionHelper.cpp

HEADERS  += \
    MainWindow.h \
    StartDialog.h \
    User.h \
    TokenMenu.h \
    DiceMenu.h \
    CustomMdiArea.h \
    ChatWidget.h \
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
    QTSFML/MapMdiSubwindow.h \
    chat/ChatServer.h \
    chat/ChatCommon.h \
    chat/ChatClient.h \
    chat/ChatHeader.h \
    chat/ChatProcessor.h \
    chat/commands/AbstractCmd.h \
    chat/commands/CmdMessageall.h \
    chat/commands/CmdNickname.h \
    chat/commands/CmdWhisper.h \
    chat/commands/Commands.h \
    chat/commands/CmdMessageui.h \
    chat/commands/CmdNicknameAck.h \
    chat/commands/CmdWhisperRep.h \
    chat/commands/CmdRoll.h \
    chat/commands/CmdDisconnect.h \
    chat/commands/CmdNicknamesList.h \
    chat/commands/CmdNicknamesListAck.h \
	 ConnexionHelper.h

FORMS    += mainwindow.ui \
    TokenMenu.ui \
    DiceMenu.ui \
    ChatWidget.ui \
	 ConnexionHelper.ui
