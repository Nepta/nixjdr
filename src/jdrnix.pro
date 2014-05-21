#-------------------------------------------------
#
# Project created by QtCreator 2014-04-30T18:48:32
#
#-------------------------------------------------

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

QT += core gui network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jdrnix.out
TEMPLATE = app
DESTDIR = ../

SOURCES += \
    Main.cpp \
    MainWindow.cpp \
    User.cpp \
    DiceMenu.cpp \
    CustomMdiArea.cpp \
    ChatWidget.cpp \
    ConnectionHelper.cpp \
    Common.cpp \
    chat/Message.cpp \
    chat/ChatServer.cpp \
    chat/ChatClient.cpp \
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
    chat/commands/CmdConnectionAck.cpp \
    Network/Header.cpp \
    Network/Server.cpp \
    Network/Switch.cpp \
    Network/ServerReceiver.cpp \
    Network/Client.cpp \
    Network/ClientReceiver.cpp \
    Network/Receiver.cpp \
    token/TokenMenu.cpp \
    token/TokenList.cpp \
    canvas/CanvasView.cpp \
    canvas/CanvasScene.cpp \
    DataBase/DataBase.cpp

HEADERS  += \
    MainWindow.h \
    User.h \
    DiceMenu.h \
    ConnectionHelper.h \
    CustomMdiArea.h \
    ChatWidget.h \
    Common.h \
    chat/Message.h \
    chat/ChatServer.h \
    chat/ChatClient.h \
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
    chat/commands/CmdConnectionAck.h \
    canvas/canvas.h \
    canvas/canvaseventhandler.h \
    Network/Switch.h \
    Network/Receiver.h \
    Network/Header.h \
    Network/Server.h \
    Network/ServerReceiver.h \
    Network/Client.h \
    Network/ClientReceiver.h \
    Network/Serializable.h \
    token/TokenMenu.h \
    token/TokenList.h \
    canvas/CanvasView.h \
    canvas/CanvasScene.h \ 
    DataBase/DataBase.h

FORMS    += mainwindow.ui \
    TokenMenu.ui \
    DiceMenu.ui \
    ChatWidget.ui \
    ConnectionHelper.ui
