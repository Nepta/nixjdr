#include <QGraphicsScene>

#include "FoWLayer.h"
#include "Database/Repository/TokenItemRepository.h"

FoWLayer::FoWLayer(int step, bool transparentSprites) :
    GridLayer(step),
    m_TransparentSprites(transparentSprites)
{
    // TODO multiple colors for multiple players (shift the hue of the pixmap?)

    // Retrieve the fow TokenItem from the database
    TokenItem *fowItem = TokenItemRepository::getFowTokenItem(db_);
    setTokenItem(fowItem);
}

FoWLayer::~FoWLayer() {}

/**
 * @brief FoWLayer::addSprite Reimplemented from GridLayer to add transparency to the new Sprite if
 * m_TransparentSprites is true.
 * @param tokenItem
 * @param position
 * @param zValue
 * @param parentItem
 * @return Returns the added sprite.
 */
Sprite *FoWLayer::addSprite(TokenItem *tokenItem, QPoint position, int zValue, QGraphicsItem *parentItem)
{
    Sprite* sprite = GridLayer::addSprite(tokenItem, position, zValue, parentItem);
    sprite->setTransparent(m_TransparentSprites);

    return sprite;
}

/**
 * @brief FoWLayer::mousePressEvent Reimplemented from GridLayer to grab mouse events.
 */
void FoWLayer::mousePressEvent(QGraphicsSceneMouseEvent *) {}

/**
 * @brief FoWLayer::sceneEventFilter Reimplemented from GridLayer. Handles events on Sprites.
 * @param watched QGraphicsItem on which an event occured.
 * @param event
 * @return true if the event is handled by this class, false if the event should be handled by
 * the watched item.
 */
bool FoWLayer::sceneEventFilter(QGraphicsItem *watched, QEvent *event) {
    bool eventHandled = true;

    Sprite *sprite = dynamic_cast<Sprite *>(watched);
    QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

    if (event->type() == QEvent::GraphicsSceneMouseRelease) {
        spriteMouseReleaseEvent(mouseEvent, sprite);
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
            GridLayer::addSprite(m_TokenItem, iterator);
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
