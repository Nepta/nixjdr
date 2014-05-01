### TO ALLOW SFML LIBRARY ###

CONFIG_APP_NAME = App

INCLUDEPATH += /usr/local/include/SFML/include

DEPENDPATH += /usr/local/include/SFML/include

CONFIG(release, debug|release): LIBS += -L /usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

CONFIG(debug, debug|release): LIBS += -L /usr/local/lib/ -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

TARGET = sfml
TEMPLATE = app

HEADERS += \
    qsfmlcanvas.h \
    mycanvas.h

SOURCES += \
    qsfmlcanvas.cpp \
    mycanvas.cpp \
    Main.cpp

QT += \
    widgets \
    core gui
