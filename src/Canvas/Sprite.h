#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneDragDropEvent>

#include "GameObjects/GameObject.h"
#include "Database/DBItem.h"
#include "Token/TokenItem.h"

class SpriteRepository;

class Sprite : public QGraphicsPixmapItem, public DBItem
{
public:
    Sprite(TokenItem *tokenItem, QGraphicsItem *parent = 0, int zValue = 1);
    Sprite(DBItem item, TokenItem *tokenItem, QGraphicsItem *parent);
    Sprite(const QByteArray& data, QGraphicsItem *parent = 0, int zValue = 1);
    ~Sprite();

    void construct(TokenItem *tokenItem, QGraphicsItem *parent, int zValue);
    void setTransparent(bool enabled);
    TokenItem *getTokenItem();
    QByteArray toQByteArray();
    GameObject *getGameObject();
    void setGameObject(GameObject *gameObject);

private:
    TokenItem *m_TokenItem;
    bool m_Transparent;
    GameObject *m_GameObject;

    void copyGameObjectFromTokenItem(TokenItem *tokenItem);
};

#endif // SPRITE_H
