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
    DiceMenu/DiceMenu.cpp \
    CustomMdiArea.cpp \
    ConnectionHelper.cpp \
    Common.cpp \
    Tooltip.cpp \
    NotificationStacker.cpp \
    StyleSheet.cpp \
    Chat/ChatWidget.cpp \
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
    Canvas/Network/MapClient.cpp \
    Canvas/Network/MapServer.cpp \
    Canvas/Layers/AbstractLayer.cpp \
    Canvas/Layers/Layers.cpp \
    Canvas/Tools/AbstractTool.cpp \
    Canvas/Tools/ToolPen.cpp \
    Canvas/Tools/ToolEraser.cpp \
    Canvas/Tools/ToolPing.cpp \
    Canvas/Tools/Tools.cpp \
    Canvas/SideMenuWidgets/DrawingMenu.cpp \
    Canvas/MapCreationWidget.cpp \
    Canvas/OpenMapWidget.cpp \
    Network/Header.cpp \
    Network/SwitchServer.cpp \
    Network/SwitchClient.cpp \
    Network/Switch.cpp \
    Network/SenderHandler.cpp \
    Network/Serializable/Message.cpp \
    Network/Sender.cpp \
    Network/SenderClient.cpp \
    Network/SenderServer.cpp \
    Network/Receiver.cpp \
    Database/Database.cpp \
    Database/DBItem.cpp \
    Database/QueryBuilder.cpp \
    Database/Repository/Repository.cpp \
    Database/Repository/RepositoryManager.cpp \
    Database/Repository/TokenItemRepository.cpp \
    Database/Repository/SpriteRepository.cpp \
    Database/Repository/MapRepository.cpp \
    Database/Repository/MapLayerRepository.cpp \
    Database/Repository/FoWLayerRepository.cpp \
    Database/Repository/BackgroundLayerRepository.cpp \
    Database/Repository/DrawingLayerRepository.cpp \
    Database/Repository/GameObjectRepository.cpp \
    Database/Repository/CharacterRepository.cpp \
    Token/TokenMenu.cpp \
    Token/TokenList.cpp \
    Token/TokenItem.cpp \
    Token/Network/TokenMenuClient.cpp \
    Token/Network/TokenMenuServer.cpp \
    TurnMenu/TurnList.cpp \
    TurnMenu/TurnMenu.cpp \
    TurnMenu/Network/TurnMenuClient.cpp \
    TurnMenu/Network/TurnMenuServer.cpp \
    Log/LogGui.cpp \
    Log/LogServer.cpp \
    Log/LogClient.cpp \
    GameObjects/GameObject.cpp \
    GameObjects/Character.cpp \
    GameObjects/GameObjectDialog.cpp \
    General/CircularProgressBar.cpp \
    General/TextPixmap.cpp \
    Canvas/SideMenuWidgets/ColorSelectionWidget.cpp \
    Canvas/SideMenuWidgets/DisplaySelectionWidget.cpp \
    Canvas/SideMenuWidgets/EditSelectionWidget.cpp

HEADERS  += \
    MainWindow.h \
    User.h \
    ConnectionHelper.h \
    CustomMdiArea.h \
    Common.h \
    Tooltip.h \
    NotificationStacker.h \
    StyleSheet.h \
    DiceMenu/DiceMenu.h \
    Chat/ChatWidget.h \
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
    Canvas/Layers/GridLayer.h \
    Canvas/Layers/MapLayer.h \
    Canvas/Layers/FoWLayer.h \
    Canvas/Layers/BackgroundLayer.h \
    Canvas/Layers/DrawingLayer.h \
    Canvas/Layers/AbstractLayer.h \
    Canvas/Layers/Layers.h \
    Canvas/Layers/LayerType.h \
    Canvas/Tools/AbstractTool.h \
    Canvas/Tools/ToolPen.h \
    Canvas/Tools/ToolEraser.h \
    Canvas/Tools/Tools.h \
    Canvas/Tools/ToolPing.h \
    Canvas/SideMenuWidgets/DrawingMenu.h \
    Canvas/Network/MapClient.h \
    Canvas/Network/MapServer.h \
    Canvas/Network/MapCodes.h \
    Canvas/MapCreationWidget.h \
    Canvas/OpenMapWidget.h \
    Canvas/MapTooltip.h \
    Network/Switch.h \
    Network/SwitchServer.h \
    Network/SwitchClient.h \
    Network/Receiver.h \
    Network/Sender.h \
    Network/SenderClient.h \
    Network/SenderServer.h \
    Network/Header.h \
    Network/SenderHandler.h \
    Network/Serializable/Message.h \
    Network/Serializable/Serializable.h \
    Database/Database.h \
    Database/DBItem.h \
    Database/QueryBuilder.h \
    Database/DBItemList.h \
    Database/Repository/Repository.h \
    Database/Repository/RepositoryManager.h \
    Database/Repository/TokenItemRepository.h \
    Database/Repository/SpriteRepository.h \
    Database/Repository/MapRepository.h \
    Database/Repository/MapLayerRepository.h \
    Database/Repository/FoWLayerRepository.h \
    Database/Repository/BackgroundLayerRepository.h \
    Database/Repository/DrawingLayerRepository.h \
    Database/Repository/GameObjectRepository.h \
    Database/Repository/CharacterRepository.h \
    Database/Repository/GameObjectSubRepository.h \
    Token/TokenMenu.h \
    Token/TokenList.h \
    Token/TokenItem.h \
    Token/Network/TokenMenuClient.h \
    Token/Network/TokenMenuServer.h \
    Token/Network/TokenMenuCodes.h \
    TurnMenu/TurnList.h \
    TurnMenu/TurnMenu.h \
    TurnMenu/Network/TurnMenuClient.h \
    TurnMenu/Network/TurnMenuServer.h \
    TurnMenu/Network/TurnMenuCodes.h \
    Log/LogGui.h \
    Log/LogServer.h \
    Log/LogClient.h \
    GameObjects/GameObject.h \
    GameObjects/GameObjectType.h \
    GameObjects/Character.h \
    GameObjects/GameObjectDialog.h \
    General/CircularProgressBar.h \
    General/TextPixmap.h \
    Canvas/SideMenuWidgets/ColorSelectionWidget.h \
    Canvas/SideMenuWidgets/DisplaySelectionWidget.h \
    Canvas/SideMenuWidgets/EditSelectionWidget.h

FORMS    += \
    MainWindow.ui \
    Tooltip.ui \
    ConnectionHelper.ui \
    CustomMdiArea.ui \
    Token/TokenMenu.ui \
    DiceMenu/DiceMenu.ui \
    Chat/ChatWidget.ui \
    TurnMenu/TurnMenu.ui \
    TurnMenu/TurnList.ui \
    Log/LogGui.ui \
    Canvas/Map.ui \
    Canvas/SideMenuWidgets/DrawingMenu.ui \
    Canvas/MapCreationWidget.ui \
    Canvas/OpenMapWidget.ui \
    GameObjects/GameObjectDialog.ui \
    Canvas/SideMenuWidgets/ColorSelectionWidget.ui \
    Canvas/SideMenuWidgets/DisplaySelectionWidget.ui \
    Canvas/SideMenuWidgets/EditSelectionWidget.ui
