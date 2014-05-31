#include <QObject>
#include "Sprite.h"

Sprite::Sprite(TokenItem *tokenItem, QGraphicsItem *parent, int zValue) :
    QGraphicsPixmapItem(parent)
{
    m_TokenItem = tokenItem;

    int tokenSize = tokenItem->size();
    QPixmap spritePixmap = tokenItem->icon().pixmap(QSize(tokenSize, tokenSize));
    setPixmap(spritePixmap);

    /* transparent pixels are part of the Sprite shape -> events can be triggered on the transparent
     * pixels of the sprite */
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    setAcceptHoverEvents(true);
    setAcceptDrops(true);

    setZValue(zValue);
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

TokenItem *Sprite::getTokenItem() {
    return m_TokenItem;
}
