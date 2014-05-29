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
    Chat/Commands/CmdHelp.cpp \
    Chat/Commands/CmdDisconnect.cpp \
    Chat/Commands/CmdNicknamesList.cpp \
    Chat/Commands/CmdNicknamesListAck.cpp \
    Chat/Commands/CmdConnectionAck.cpp \
    Canvas/CanvasView.cpp \
    Canvas/CanvasScene.cpp \
    Canvas/Sprite.cpp \
    Canvas/Map.cpp \
    Canvas/MapTooltip.cpp \
    Canvas/Layers/GridLayer.cpp \
    Canvas/Layers/MapLayer.cpp \
    Canvas/Layers/FoWLayer.cpp \
    Canvas/Layers/BackgroundLayer.cpp \
    Canvas/Layers/DrawingLayer.cpp \
    Canvas/Layers/Layer.cpp \
    Network/Header.cpp \
    Network/Server.cpp \
    Network/Switch.cpp \
    Network/ServerReceiver.cpp \
    Network/Client.cpp \
    Network/ClientReceiver.cpp \
    Network/Receiver.cpp \
    DataBase/DataBase.cpp \
    DataBase/DBItem.cpp \
    DataBase/QueryBuilder.cpp \
    DataBase/DBComponent.cpp \
    DataBase/DBItemList.cpp \
    DataBase/Repository/TokenItemRepository.cpp \
    Token/TokenMenu.cpp \
    Token/TokenList.cpp \
    Token/TokenItem.cpp \
    TurnMenu/TurnList.cpp \
    TurnMenu/TurnMenu.cpp

HEADERS  += \
    MainWindow.h \
    User.h \
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
    Chat/Commands/CmdHelp.h \
    Chat/Commands/CmdDisconnect.h \
    Chat/Commands/CmdNicknamesList.h \
    Chat/Commands/CmdNicknamesListAck.h \
    Chat/Commands/CmdConnectionAck.h \
    Canvas/CanvasScene.h \
    Canvas/CanvasView.h \
    Canvas/Sprite.h \
    Canvas/Map.h \
    Canvas/MapTooltip.h \
    Canvas/Layers/Layer.h \
    Canvas/Layers/GridLayer.h \
    Canvas/Layers/MapLayer.h \
    Canvas/Layers/FoWLayer.h \
    Canvas/Layers/BackgroundLayer.h \
    Canvas/Layers/DrawingLayer.h \
    Network/Switch.h \
    Network/Receiver.h \
    Network/Header.h \
    Network/Server.h \
    Network/ServerReceiver.h \
    Network/Client.h \
    Network/ClientReceiver.h \
    Network/Serializable.h \
    DataBase/DataBase.h \
    DataBase/DBItem.h \
    DataBase/QueryBuilder.h \
    DataBase/DBComponent.h \
    DataBase/DBItemList.h \
    DataBase/Repository/TokenItemRepository.h \
    Token/TokenMenu.h \
    Token/TokenList.h \
    Token/TokenItem.h \
    TurnMenu/TurnList.h \
    TurnMenu/TurnMenu.h


FORMS    += \
    TokenMenu.ui \
    DiceMenu.ui \
    ChatWidget.ui \
    ConnectionHelper.ui \
    MainWindow.ui \
    TurnMenu.ui \
    Map.ui \
    MapTooltip.ui
