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

void Sprite::unserialize(QByteArray&) {
    // TODO
}
