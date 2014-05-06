#-------------------------------------------------
#
# Project created by QtCreator 2014-04-30T18:48:32
#
#-------------------------------------------------

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

QT += core gui
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
    QTSFML/Canvas.cpp \
    QTSFML/Map.cpp \
    QTSFML/Action.cpp \
    QTSFML/ActionChooser.cpp \
    QTSFML/CoutAction.cpp \
    QTSFML/SpriteList.cpp

HEADERS  += \
    mainwindow.h \
    startdialog.h \
    QTSFML/Canvas.h \
    QTSFML/Map.h \
    QTSFML/Action.h \
    QTSFML/ActionChooser.h \
    QTSFML/CoutAction.h \
    QTSFML/GraphicAction.h \
    QTSFML/SpriteList.h \
    QTSFML/TokenAddAction.h \
    QTSFML/TokenDelAction.h \
    QTSFML/TokenMoveAction.h

FORMS    += mainwindow.ui

