#include "Canvas.h"
#include "Map.h"

#include <QApplication>
#include <QFrame>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

int main(int argc, char **argv)
{
    QApplication App(argc, argv);

    // On crée la fenêtre principale
    QWidget* MainFrame = new QWidget;
    MainFrame->setWindowTitle("Qt SFML");
    MainFrame->resize(800, 600);

    MainFrame->show();

    //On crée une vue SFML dans la fenêtre principale
    Map* map = new Map(MainFrame, QPoint(0, 0), QSize(800, 600));
    map->show();

    Canvas* suwako = new Canvas(MainFrame, QPoint(20, 0), QSize(75, 95));
    suwako->show();

    return App.exec();
}
