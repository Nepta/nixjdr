#include <QGraphicsScene>

#include "Layer.h"

QRectF Layer::boundingRect() const {
    if (isEnabled()) {
        return scene()->sceneRect();
    }
    else {
        return QRectF(0, 0, 0, 0);
    }
}

void Layer::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) {}

void Layer::setEnabled(bool enabled) {
    prepareGeometryChange();
    QGraphicsObject::setEnabled(enabled);
}
