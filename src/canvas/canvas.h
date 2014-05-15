#ifndef CANVAS_H
#define CANVAS_H


#include <iostream>
#include <QGraphicsItemAnimation>
#include <QGraphicsScene>
#include <QTimeLine>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPainter>
#include <QPixmap>
#include <QPainter>
#include <QList>
#include <QEvent>

#include "canvaseventhandler.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas();
    Canvas(QString filename, int step=1);
    QGraphicsScene* getScene();
    QGraphicsView *getView();
    CanvasEventHandler *getCanvasEventHandler();
    void drawGrid(int width, int height);

private:
    QGraphicsScene* m_scene;
    QGraphicsView* m_view;
    QPixmap* m_background;
    CanvasEventHandler* m_canvasEventHandler;
    int m_step;
    QList<QList<QGraphicsItem*>> m_SpriteMatrix;

public slots:
    void addSprite(QPixmap* sprite, int x, int y, int z);
    void removeSprite(int x, int y, int z);
};

#endif // CANVAS_H
