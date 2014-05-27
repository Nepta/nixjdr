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

/**
 * @brief setEnabled Reimplemented from QGraphicsObject. Notifies the layer that the geometry of
 * the layer will change before calling QGraphicsObject::setEnabled(). The boundingRect() depends
 * on the enabled attribute.
 * @param enabled
 */
void Layer::setEnabled(bool enabled) {
    prepareGeometryChange();
    QGraphicsObject::setEnabled(enabled);
}
