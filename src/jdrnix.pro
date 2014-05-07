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
INCLUDEPATH += /usr/local/include/SFML/include
DEPENDPATH += /usr/local/include/SFML/include
LIBS += -L /usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

TARGET = jdrnix.out
TEMPLATE = app
DESTDIR = ../

SOURCES += \
    main.cpp\
    mainwindow.cpp \
    startdialog.cpp \
    user.cpp \
    QTSFML/Canvas.cpp \
    QTSFML/Map.cpp \
    QTSFML/Action.cpp \
    QTSFML/ActionChooser.cpp \
    QTSFML/CoutAction.cpp \
    QTSFML/SpriteList.cpp \
    QTSFML/QTSFMLMdiSubwindow.cpp \
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

HEADERS  += \
    mainwindow.h \
    startdialog.h \
    user.h \
    QTSFML/Canvas.h \
    QTSFML/Map.h \
    QTSFML/Action.h \
    QTSFML/ActionChooser.h \
    QTSFML/CoutAction.h \
    QTSFML/GraphicAction.h \
    QTSFML/SpriteList.h \
    QTSFML/TokenAddAction.h \
    QTSFML/TokenDelAction.h \
    QTSFML/TokenMoveAction.h \
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
    chat/commands/chatcmdwhisperrep.h

FORMS    += mainwindow.ui