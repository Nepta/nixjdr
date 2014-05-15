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
#include <QGraphicsPixmapItem>

#include "canvaseventhandler.h"

#define LAYER_MAX 4

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
    QList<QList<QList<QGraphicsPixmapItem*>>> m_SpriteMatrix;

signals:
    void moveSprite();

public slots:
    void addSprite(QPixmap* sprite, int x, int y, bool isMoving);
    void removeSprite(int x, int y);
};

#endif // CANVAS_H
