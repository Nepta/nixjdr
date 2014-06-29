#include <QGraphicsScene>

#include "Database/Repository/RepositoryManager.h"
#include "Canvas/Network/MapCodes.h"
#include "FoWLayer.h"

FoWLayer::FoWLayer(int step, bool transparentSprites) :
    GridLayer(step),
    m_TransparentSprites(transparentSprites)
{
    construct(step, transparentSprites);
}

FoWLayer::FoWLayer(DBItem item, bool transparentSprites) : GridLayer()
{
    QHash<QString, QVariant> itemHashMap = item.getHashMap();
    columnsValues_ = item.getHashMap();

    int id =  itemHashMap.value("id").toInt();
    int step = itemHashMap.value("step").toInt();

    id_ = id;
    construct(step, transparentSprites);
}

FoWLayer::~FoWLayer() {
    delete m_GridPixmap;
}

void FoWLayer::construct(int step, bool transparentSprites) {
    m_LayerType = LayerType::FOW_LAYER;
    m_TransparentSprites = transparentSprites;
    m_Step = step;

    // Retrieve the fow TokenItem from the database
    TokenItem *fowItem = RepositoryManager::s_TokenItemRepository.getFowTokenItem();
    setTokenItem(fowItem);
}

void FoWLayer::usePixmapAsBackgroundGrid(){
    m_GridPixmap = new QPixmap(scene()->sceneRect().size().toSize());
    m_DrawingZone = new QGraphicsPixmapItem(this);

    m_GridPixmap->fill(Qt::transparent);
    paintGridOnPixmap(m_GridPixmap);
    m_DrawingZone->setPixmap(*m_GridPixmap);
}

void FoWLayer::paintGridOnPixmap(QPixmap *pixmap){
    QPainter *painter = new QPainter(pixmap);
    GridLayer::drawBackground(painter, QRectF(pixmap->rect()));
    delete painter;
}

/**
 * @brief FoWLayer::addSpriteToLayer Reimplemented from GridLayer to add transparency to the new
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
    else if (event->type() == QEvent::GraphicsSceneWheel) {
        if (!isEnabled()) {
            event->ignore();
        }
    }

    return eventHandled;
}

/**
 * @brief FoWLayer::fillFoW Fill the entire map with FoW sprites (delete all the FoW sprites before).
 */
void FoWLayer::fillFoW() {
    removeFoW();

    int firstId;
    int lastId;

    Database::instance()->begin();
    for(int i = 0 ; i < boundingRect().width() ; i += m_Step) {
        for(int j = 0 ; j < boundingRect().height() ; j += m_Step) {            
            int id = GridLayer::addSprite(m_TokenItem, QPoint(i, j), 1, false);

            if (i == 0 && j == 0) {
                firstId = id;
                lastId = id;
            }
            else {
                lastId++;
            }
        }
    }
    Database::instance()->commit();

    // Notifies all the clients that FoW sprites in the range [firstId;lastId] were added
    QString msg = QString("%1 %2 %3")
        .arg(this->id())
        .arg(firstId)
        .arg(lastId);
    m_SenderClient->sendMessageToServer(msg, (quint16) MapCodes::ADD_ALL_FOW);
}

/**
 * @brief FoWLayer::removeFoW Remove all the FoW sprites from the layer and notifies all the clients
 * that they need to remove those sprites..
 */
void FoWLayer::removeFoW() {
    // Notifies all the clients that all the FoW sprites for this layer need to be removed
    QString msg = QString("%1").arg(this->id());
    m_SenderClient->sendMessageToServer(msg, (quint16) MapCodes::REMOVE_ALL_FOW);

    // Remove all the FoW Sprites for this layer from the db
    RepositoryManager::s_SpriteRepository.removeAllSpritesFromFoWLayer(this->id());

    // Removes the FoW locally
    removeAllSprites();
}
