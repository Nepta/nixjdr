#include <QObject>
#include "Sprite.h"

Sprite::Sprite(const QPixmap &pixmap, QGraphicsItem *parent, Sprite* previousSpriteStack) :
    QGraphicsPixmapItem(pixmap, parent)
{
    /* transparent pixels are part of the Sprite shape -> events can be triggered on the transparent
     * pixels of the sprite */
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    setAcceptHoverEvents(true);
    setAcceptDrops(true);

    m_PreviousSpriteStack = previousSpriteStack;

    if (m_PreviousSpriteStack == NULL) {
        m_StackNumber = 1;
    }
    else {
        m_StackNumber = m_PreviousSpriteStack->getStackNumber() + 1;
    }
}

Sprite::Sprite(QByteArray& data) {
    unserialize(data);
}

Sprite::~Sprite() {
}

/**
 * @brief boundingRect Reimplemented from QGraphicsPixmapItem. The bounding rectangle corresponds to
 * QGraphicsPixmapItem::boundingRect() when the layer is enabled, otherwise it is a 0 width/height
 * rectangle to avoid intercepting mouse events when the layer is disabled.
 * @return bounding rectangle
 */
QRectF Sprite::boundingRect() const {
    if (isEnabled()) {
        return QGraphicsPixmapItem::boundingRect();
    } else {
        return QRectF(0, 0, 0, 0);
    }
}

/**
 * @brief Sprite::setEnabled Reimplemented from QGraphicsPixmapItem. Notifies the Sprite that the
 * geometry of the sprite will change before calling QGraphicsPixmapItem::setEnabled(enabled). When
 * the sprite is disabled, boundingRect() is updated to a 0 width/height bounding rectangle.
 * @param enabled
 * @sa boundingRect()
 */
void Sprite::setEnabled(bool enabled) {
    prepareGeometryChange();
    QGraphicsPixmapItem::setEnabled(enabled);
}

void Sprite::setTransparent(bool enabled) {
    if (enabled) {
        setOpacity(0.75);
    } else {
        setOpacity(1.0);
    }
}

int Sprite::getStackNumber() {
    return m_StackNumber;
}

// Reimplemented from Serializable

QByteArray Sprite::serialize() {
    // TODO
    return NULL;
}

void Sprite::unserialize(QByteArray& data) {
    // TODO
}
