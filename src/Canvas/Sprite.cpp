#include <QObject>
#include "Sprite.h"

#include <QDebug>

Sprite::Sprite(TokenItem *tokenItem, QGraphicsItem *parent, int zValue)
{
    construct(tokenItem, parent, zValue);
}

Sprite::Sprite(DBItem item, TokenItem *tokenItem, QGraphicsItem *parent) {
    QHash<QString, QVariant> itemHashMap = item.getHashMap();
    columnsValues_ = item.getHashMap();

    int id = itemHashMap.value("id").toInt();
    int posx = itemHashMap.value("posx").toInt();
    int posy = itemHashMap.value("posy").toInt();
    int zvalue = itemHashMap.value("zvalue").toInt();

    id_ = id;
    setPos(posx, posy);

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
    QDataStream stream(data);

    stream >> id_;

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

QByteArray Sprite::toQByteArray() {
    QByteArray out;
    QDataStream stream(&out, QIODevice::WriteOnly);

    stream << id_;
    m_TokenItem->toQByteArray(&stream);

    return out;
}
