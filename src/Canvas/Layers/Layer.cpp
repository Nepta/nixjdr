#include <QGraphicsScene>

#include "Layer.h"

/**
 * @brief Layer::boundingRect Reimplemented from QGraphicsObject. The bounding rect corresponds to
 * the scene rect when the layer is enable, otherwise the bounding rect is
 * @return
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
