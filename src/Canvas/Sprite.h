#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneDragDropEvent>
#include "Network/Serializable.h"
#include "Token/TokenItem.h"

class Sprite : public QGraphicsPixmapItem
{
public:
    Sprite(TokenItem *tokenItem, QGraphicsItem *parent = 0, int zValue = 1);
    ~Sprite();
    void setTransparent(bool enabled);
    int getStackNumber();
    TokenItem *getTokenItem();

private:
    TokenItem *m_TokenItem;
    bool m_Transparent;
};

#endif // SPRITE_H
