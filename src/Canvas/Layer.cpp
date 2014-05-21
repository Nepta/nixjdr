#include <QGraphicsScene>

#include "Layer.h"

QRectF Layer::boundingRect() const {
    return this->scene()->sceneRect();
}

void Layer::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) {}
