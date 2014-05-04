### TO ALLOW SFML LIBRARY ###

CONFIG_APP_NAME = App

INCLUDEPATH += /usr/local/include/SFML/include

DEPENDPATH += /usr/local/include/SFML/include

CONFIG(release, debug|release): LIBS += -L /usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

CONFIG(debug, debug|release): LIBS += -L /usr/local/lib/ -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

TARGET = sfml
TEMPLATE = app

HEADERS += \
    QTSFMLCanvas.h \
    Canvas.h \
    Map.h \
    Action.h \
    ActionChooser.h \
    CoutAction.h \
    GraphicAction.h \
    SpriteList.h \
    TokenAddAction.h \
    TokenDelAction.h \
    TokenMoveAction.h

SOURCES += \
    QTSFMLCanvas.cpp \
    Canvas.cpp \
    Main.cpp \
    Map.cpp \
    Action.cpp \
    ActionChooser.cpp \
    CoutAction.cpp \
    SpriteList.cpp

QT += \
    widgets \
    core gui

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11
