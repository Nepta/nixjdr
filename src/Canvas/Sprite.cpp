#include <QObject>

#include "Database/Repository/RepositoryManager.h"
#include "Database/Repository/GameObjectRepository.h"
#include "Sprite.h"

Sprite::Sprite(TokenItem *tokenItem, QGraphicsItem *parent, int zValue)
{
    m_GameObject = NULL;
    copyGameObjectFromTokenItem(tokenItem);
    construct(tokenItem, parent, zValue);
}

Sprite::Sprite(DBItem item, TokenItem *tokenItem, QGraphicsItem *parent) {
    columnsValues_ = item.getHashMap();

    int id = columnsValues_.value("id").toInt();
    int posx = columnsValues_.value("posx").toInt();
    int posy = columnsValues_.value("posy").toInt();
    int zvalue = columnsValues_.value("zvalue").toInt();
    int gameobjectid = columnsValues_.value("gameobjectid").toInt();

    id_ = id;
    setPos(posx, posy);

    if (gameobjectid != 0) {
        m_GameObject = RepositoryManager::s_CharacterRepository.getFullGameObject(gameobjectid);
    } else {
        m_GameObject = NULL;
    }

    construct(tokenItem, parent, zvalue);
}

/**
 * @brief Sprite::Sprite Constructs a Sprite with information stored in a QByteArray.
 * @remarks Used in a drag&drop event to restore data previously stored in a QByteArray throuh the
 * toQByteArray() method.
 * @param data
 * @param parent
 * @param zValue
 * @sa toQByteArray()
 */
Sprite::Sprite(const QByteArray& data, QGraphicsItem *parent, int zValue) :
    QGraphicsPixmapItem(parent)
{
    m_GameObject = NULL;

    QDataStream stream(data);
    int gameObjectId;
    stream >> id_ >> gameObjectId;

    if (gameObjectId != 0) {
        m_GameObject = RepositoryManager::s_CharacterRepository.getFullGameObject(gameObjectId);
    }

    TokenItem *tokenItem = new TokenItem(&stream);
    construct(tokenItem, parent, zValue);
}

void Sprite::construct(TokenItem *tokenItem, QGraphicsItem *parent, int zValue) {
    m_TokenItem = tokenItem;

    int tokenSize = tokenItem->size();
    QPixmap spritePixmap = tokenItem->icon().pixmap(QSize(tokenSize, tokenSize));
    setPixmap(spritePixmap);

    /* transparent pixels are part of the Sprite shape -> events can be triggered on the transparent
     * pixels of the sprite */
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    setAcceptHoverEvents(true);
    setAcceptDrops(true);

    setParentItem(parent);

    setZValue(zValue);
}

Sprite::~Sprite() {
}

/**
 * @brief Sprite::copyGameObjectFromTokenItem Creates a copy of the GameObject in the specified
 * TokenItem, adds it to the database and sets it for this sprite.
 * @param tokenItem TokenItem from which the GameObject copy will be taken.
 */
void Sprite::copyGameObjectFromTokenItem(TokenItem *tokenItem) {
    if (tokenItem->gameObject() != NULL) {
        m_GameObject = tokenItem->gameObject()->clone();
        RepositoryManager::s_GameObjectRepository.insertGameObject(m_GameObject);
    }
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

/**
 * @brief Sprite::toQByteArray Stores a current instance of Sprite in a QByteArray.
 * @remarks Used in drag&drop events to pass a Sprite through the MimeData.
 * @return QByteArray containing sufficient information about the tokenItem to reconstruct it.
 */
QByteArray Sprite::toQByteArray() {
    QByteArray out;
    QDataStream stream(&out, QIODevice::WriteOnly);

    stream << id_;

    // If this Sprite possess a GameObject, adds its Id to the QByteArray, otherwise adds the id 0
    // which does not correspond to any GameObject.
    if (m_GameObject != NULL) {
        stream << m_GameObject->id();
    } else {
        int id = 0;
        stream << id;
    }

    m_TokenItem->toQByteArray(&stream);

    return out;
}

GameObject *Sprite::getGameObject() {
    return m_GameObject;
}

/**
 * @brief Sprite::boundingRect Reimplemented from QGraphicsPixmapItem. Use the TokenItem's size to
 * avoid problems with pixmaps having a size inferior to the TokenItem's one.
 * @return bounding rectangle (QRectF)
 */
QRectF Sprite::boundingRect() const {
    int tokenItemSize = m_TokenItem->size();
    return QRectF(offset(), QSize(tokenItemSize, tokenItemSize));
}

/**
 * @brief Sprite::shape Reimplemented from QGraphicsPixmapItem. Use the boundingRect as the shape
 * of the Sprite to avoid problems with pixmaps having a size inferior to the TokenItem's one.
 * @return QPainterPath representing the shape of this sprite.
 */
QPainterPath Sprite::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
