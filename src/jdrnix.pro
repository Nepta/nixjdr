#-------------------------------------------------
#
# Project created by QtCreator 2014-04-30T18:48:32
#
#-------------------------------------------------

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jdrnix.out
TEMPLATE = app
DESTDIR = ../

SOURCES += \
    Main.cpp \
    MainWindow.cpp \
    User.cpp \
    TokenMenu.cpp \
    DiceMenu.cpp \
    CustomMdiArea.cpp \
    ChatWidget.cpp \
    ConnectionHelper.cpp \
    Common.cpp \
    Chat/Message.cpp \
    Chat/ChatServer.cpp \
    Chat/ChatClient.cpp \
    Chat/ChatProcessor.cpp \
    Chat/Commands/AbstractCmd.cpp \
    Chat/Commands/CmdMessageall.cpp \
    Chat/Commands/CmdNickname.cpp \
    Chat/Commands/CmdWhisper.cpp \
    Chat/Commands/Commands.cpp \
    Chat/Commands/CmdMessageui.cpp \
    Chat/Commands/CmdNicknameAck.cpp \
    Chat/Commands/CmdWhisperRep.cpp \
    Chat/Commands/CmdRoll.cpp \
    Chat/Commands/CmdDisconnect.cpp \
    Chat/Commands/CmdNicknamesList.cpp \
    Chat/Commands/CmdNicknamesListAck.cpp \
    Chat/Commands/CmdConnectionAck.cpp \
    Canvas/CanvasView.cpp \
    Canvas/CanvasScene.cpp \
    Canvas/Sprite.cpp \
    Canvas/MapLayer.cpp \
    Canvas/Layer.cpp \
    Network/Header.cpp \
    Network/Server.cpp \
    Network/Switch.cpp \
    Network/ServerReceiver.cpp \
    Network/Client.cpp \
    Network/ClientReceiver.cpp \
    Network/Receiver.cpp \
    Canvas/Map.cpp

HEADERS  += \
    MainWindow.h \
    User.h \
    TokenMenu.h \
    DiceMenu.h \
    ConnectionHelper.h \
    CustomMdiArea.h \
    ChatWidget.h \
    Common.h \
    Chat/Message.h \
    Chat/ChatServer.h \
    Chat/ChatClient.h \
    Chat/ChatProcessor.h \
    Chat/Commands/AbstractCmd.h \
    Chat/Commands/CmdMessageall.h \
    Chat/Commands/CmdNickname.h \
    Chat/Commands/CmdWhisper.h \
    Chat/Commands/Commands.h \
    Chat/Commands/CmdMessageui.h \
    Chat/Commands/CmdNicknameAck.h \
    Chat/Commands/CmdWhisperRep.h \
    Chat/Commands/CmdRoll.h \
    Chat/Commands/CmdDisconnect.h \
    Chat/Commands/CmdNicknamesList.h \
    Chat/Commands/CmdNicknamesListAck.h \
    Chat/Commands/CmdConnectionAck.h \
    Canvas/CanvasScene.h \
    Canvas/CanvasView.h \
    Canvas/Sprite.h \
    Canvas/Layer.h \
    Canvas/MapLayer.h \
    Network/Switch.h \
    Network/Receiver.h \
    Network/Header.h \
    Network/Server.h \
    Network/ServerReceiver.h \
    Network/Client.h \
    Network/ClientReceiver.h \
    Network/Serializable.h \
    Canvas/Map.h

FORMS    += mainwindow.ui \
    TokenMenu.ui \
    DiceMenu.ui \
    ChatWidget.ui \
    ConnectionHelper.ui
