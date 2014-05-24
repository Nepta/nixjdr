#include "FoWLayer.h"

#include <QDebug>

FoWLayer::FoWLayer(int step, bool transparentSprites) :
    GridLayer(step),
    m_TransparentSprites(transparentSprites)
{
    // TODO multiple colors for multiple players (shift the hue of the pixmap?)
    GridLayer::setSpritePixmap("fow");
}

FoWLayer::~FoWLayer() {}

// reimplemented from GridLayer
Sprite *FoWLayer::addSprite(QPixmap *spritePixmap, QPoint position) {
    Sprite* sprite = GridLayer::addSprite(spritePixmap, position);
    sprite->setTransparent(m_TransparentSprites);

    return sprite;
}

void FoWLayer::mousePressEvent(QGraphicsSceneMouseEvent *) {}

bool FoWLayer::sceneEventFilter(QGraphicsItem *watched, QEvent *event) {
    bool eventHandled = true;

    QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

    if (event->type() == QEvent::GraphicsSceneMouseRelease) {
        qreal distanceCovered = (mouseEvent->buttonDownScenePos(Qt::RightButton)
                                        - mouseEvent->scenePos()).manhattanLength();

        if (mouseEvent->button() == Qt::RightButton && distanceCovered < DELTA_DELETE_SPRITE) {
            removeSprite(watched);
        }
    }

    return eventHandled;
}
