#-------------------------------------------------
#
# Project created by QtCreator 2014-04-30T18:48:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jdrnix
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    startdialog.cpp

HEADERS  += mainwindow.h \
    startdialog.h

FORMS    += mainwindow.ui
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

INCLUDEPATH += /usr/local/include/SFML/include

DEPENDPATH += /usr/local/include/SFML/include

LIBS += -L /usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

HEADERS += \
	 ../Qt-sfml/QTSFML/QTSFMLCanvas.h \
	 ../Qt-sfml/QTSFML/Canvas.h \
	 ../Qt-sfml/QTSFML/Map.h \
	 ../Qt-sfml/QTSFML/Action.h \
	 ../Qt-sfml/QTSFML/ActionChooser.h \
	 ../Qt-sfml/QTSFML/CoutAction.h \
	 ../Qt-sfml/QTSFML/GraphicAction.h \
	 ../Qt-sfml/QTSFML/SpriteList.h \
	 ../Qt-sfml/QTSFML/TokenAddAction.h \
	 ../Qt-sfml/QTSFML/TokenDelAction.h \
	 ../Qt-sfml/QTSFML/TokenMoveAction.h

SOURCES += \
	 ../Qt-sfml/QTSFML/QTSFMLCanvas.cpp \
	 ../Qt-sfml/QTSFML/Canvas.cpp \
	 ../Qt-sfml/QTSFML/Map.cpp \
	 ../Qt-sfml/QTSFML/Action.cpp \
	 ../Qt-sfml/QTSFML/ActionChooser.cpp \
	 ../Qt-sfml/QTSFML/CoutAction.cpp \
	 ../Qt-sfml/QTSFML/SpriteList.cpp

QT += \
	 widgets \
	 core gui
