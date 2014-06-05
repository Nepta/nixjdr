#include <QGraphicsScene>

#include "Database/Repository/RepositoryManager.h"

#include "FoWLayer.h"

FoWLayer::FoWLayer(int step, bool transparentSprites) :
    GridLayer(step),
    m_TransparentSprites(transparentSprites)
{
    construct(step, transparentSprites);
}

FoWLayer::FoWLayer(DBItem item) : GridLayer()
{
    QHash<QString, QVariant> itemHashMap = item.getHashMap();
    columnsValues_ = item.getHashMap();

    int id =  itemHashMap.value("id").toInt();
    int step = itemHashMap.value("step").toInt();

    id_ = id;
    construct(step, true);
}

FoWLayer::~FoWLayer() {}

void FoWLayer::construct(int step, bool transparentSprites) {
    m_TransparentSprites = transparentSprites;
    m_Step = step;

    // Retrieve the fow TokenItem from the database
    TokenItem *fowItem = RepositoryManager::s_TokenItemRepository.getFowTokenItem(db_);
    setTokenItem(fowItem);
}

/**
 * @brief FoWLayer::addSpriteFromDb Reimplemented from GridLayer to add transparency to the new
 * Sprite if m_TransparentSprites is true.
 * @param sprite
 */
Sprite *FoWLayer::addSpriteToLayer(Sprite* sprite)
{
    GridLayer::addSpriteToLayer(sprite);
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

    for(int i = 0 ; i < boundingRect().width() ; i += m_Step) {
        for(int j = 0 ; j < boundingRect().height() ; j += m_Step) {
            GridLayer::addSpriteToDb(m_TokenItem, QPoint(i, j));
        }
    }
}

/**
 * @brief FoWLayer::removeFoW Remove all the FoW sprites from the db and notifies all the clients
 * that they need to remove those sprites from their layers. The FoW is then removed locally.
 */
void FoWLayer::removeFoW() {
    // Remove all the FoW Sprites for this layer from the db
    RepositoryManager::s_SpriteRepository.removeAllSpritesFromFoWLayer(this->id(), db_);

    // Notifies all the clients that all the FoW sprites for this layer need to be removed
    QString msg = QString("removeAllFoW %1").arg(this->id());
    m_SenderClient->sendMessageToServer(msg);

    // Removes the FoW locally
    removeAllSprites();
}
