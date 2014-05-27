#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneDragDropEvent>
#include "Network/Serializable.h"

class Sprite : public QGraphicsPixmapItem, public Serializable
{
public:
    Sprite(const QPixmap &pixmap, QGraphicsItem *parent = 0, Sprite *parentSprite = NULL);
    Sprite(QByteArray& data);
    ~Sprite();
    void setTransparent(bool enabled);
    int getStackNumber();

    QByteArray serialize();

private:
    /**
     * @brief m_ParentSprite Pointer to the sprite positionned below in the stack.
     */
    Sprite *m_PreviousSpriteStack;

    /**
     * @brief m_SpriteStackNumber Number this sprite holds in the stack.
     */
    int m_StackNumber;
    bool m_Transparent;

    void unserialize(QByteArray& data);
};

#endif // SPRITE_H
