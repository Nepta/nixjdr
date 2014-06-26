#include <QGraphicsScene>

#include "AbstractLayer.h"

/**
 * @brief AbstractLayer::boundingRect Reimplemented from QGraphicsObject. The bounding rectangle corresponds
 * to the scene rectangle when the layer is enabled. Otherwise the bounding rect is a 0 width/height
 * rectangle to avoid intercepting mouse events when the layer is disabled.
 * @return bounding rectangle
 */
QRectF AbstractLayer::boundingRect() const {
    if (isEnabled()) {
        return scene()->sceneRect();
    }
    else {
        return QRectF(0, 0, 0, 0);
    }
}

/**
 * @brief AbstractLayer::paint Reimplemented from QGraphicsObject. Does not paint anything, a layer does not
 * possess a content.
 */
void AbstractLayer::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) {}

/**
 * @brief setEnabled Reimplemented from QGraphicsObject. Notifies the layer that the geometry of
 * the layer will change before calling QGraphicsObject::setEnabled(). The boundingRect() depends
 * on the enabled attribute.
 * @param enabled
 */
void AbstractLayer::setEnabled(bool enabled) {
    prepareGeometryChange();
    QGraphicsObject::setEnabled(enabled);
}

void AbstractLayer::setSenderClient(SenderClient *senderClient) {
    m_SenderClient = senderClient;
}

/**
 * @brief AbstractLayer::keyPressEvent Reimplemented from QObject; required since the QGraphicsScene
 * forwards all events
 */
void AbstractLayer::keyPressEvent(QKeyEvent *) {}

/**
 * @brief AbstractLayer::keyReleaseEvent Reimplemented from QObject; required since the QGraphicsScene
 * forwards all events
 */
void AbstractLayer::keyReleaseEvent(QKeyEvent *) {}

void AbstractLayer::setTooltip(MapTooltip *tooltip) {
    m_Tooltip = tooltip;
}
