#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneDragDropEvent>
#include "Network/Serializable.h"
#include "Database/DBItem.h"
#include "Token/TokenItem.h"

class Sprite : public QGraphicsPixmapItem, public DBItem
{
public:
    Sprite(TokenItem *tokenItem, QGraphicsItem *parent = 0, int zValue = 1);
    ~Sprite();
    void setTransparent(bool enabled);
    TokenItem *getTokenItem();

private:
    TokenItem *m_TokenItem;
    bool m_Transparent;
};

#endif // SPRITE_H
