#include <QGraphicsScene>

#include "Layer.h"

/**
 * @brief Layer::boundingRect Reimplemented from QGraphicsObject. The bounding rectangle corresponds
 * to the scene rectangle when the layer is enabled. Otherwise the bounding rect is a 0 width/height
 * rectangle to avoid intercepting mouse events when the layer is disabled.
 * @return bounding rectangle
 */
QRectF Layer::boundingRect() const {
    if (isEnabled()) {
        return scene()->sceneRect();
    }
    else {
        return QRectF(0, 0, 0, 0);
    }
}

/**
 * @brief Layer::paint Reimplemented from QGraphicsObject. Does not paint anything, a Layer does not
 * possess a content.
 */
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
