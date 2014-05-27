#include <QGraphicsScene>

#include "FoWLayer.h"

FoWLayer::FoWLayer(int step, bool transparentSprites) :
    GridLayer(step),
    m_TransparentSprites(transparentSprites)
{
    // TODO multiple colors for multiple players (shift the hue of the pixmap?)
    GridLayer::setSpritePixmap("fow");
}

FoWLayer::~FoWLayer() {}

// reimplemented from GridLayer
Sprite *FoWLayer::addSprite(QPixmap *spritePixmap, QPoint position, Sprite*) {
    Sprite* sprite = GridLayer::addSprite(spritePixmap, position);
    sprite->setTransparent(m_TransparentSprites);

    return sprite;
}

void FoWLayer::mousePressEvent(QGraphicsSceneMouseEvent *) {}

bool FoWLayer::sceneEventFilter(QGraphicsItem *watched, QEvent *event) {
    bool eventHandled = true;

    Sprite *sprite = dynamic_cast<Sprite *>(watched);
    QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

    if (event->type() == QEvent::GraphicsSceneMouseRelease) {
        spriteMouseReleaseEvent(sprite, mouseEvent);
    }

    return eventHandled;
}

/**
 * @brief FoWLayer::fillFoW Fill the entire map with FoW sprites (delete all the FoW sprites before).
 */
void FoWLayer::fillFoW() {

    removeFoW();

    QPoint iterator(0,0);

    for(int i = 0; i < boundingRect().width(); i+=m_Step){
        for(int j = 0; j < boundingRect().height(); j +=m_Step){
            iterator.setX(i);
            iterator.setY(j);
            addSprite(&m_SpritePixmap, iterator);
        }
    }

}

/**
 * @brief FoWLayer::removeFoW Remove all the FoW sprites from the map.
 */
void FoWLayer::removeFoW() {
    foreach (QGraphicsItem* item, childItems()) {
        removeSprite(item);
    }
}
