#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneDragDropEvent>
#include "Network/Serializable.h"
#include "Token/TokenItem.h"

class Sprite : public QGraphicsPixmapItem
{
public:
    Sprite(TokenItem *tokenItem, QGraphicsItem *parent = 0, Sprite *parentSprite = NULL);
    ~Sprite();
    void setTransparent(bool enabled);
    int getStackNumber();
    TokenItem *getTokenItem();

private:
    TokenItem *m_TokenItem;

    /**
     * @brief m_ParentSprite Pointer to the sprite positionned below in the stack.
     */
    Sprite *m_PreviousSpriteStack;

    /**
     * @brief m_SpriteStackNumber Number this sprite holds in the stack.
     */
    int m_StackNumber;
    bool m_Transparent;
};

#endif // SPRITE_H
