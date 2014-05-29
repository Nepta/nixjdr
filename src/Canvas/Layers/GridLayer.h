#ifndef GRIDLAYER_H
#define GRIDLAYER_H

#include <QPainter>
#include <QRectF>
#include <QString>
#include <QListWidgetItem>

#include "Canvas/Sprite.h"
#include "Layer.h"

/**
 * @brief The GridLayer class represents a Grid on which sprites can be positionned and removed.
 */
class GridLayer : public Layer
{
    Q_OBJECT

public:
    /**
     * @brief DELTA_DELETE_SPRITE The event called to delete a Sprite is valid if the cursor does not
     * cover a distance superior to this constant.
     */
    static const int DELTA_DELETE_SPRITE = 40;

    GridLayer(int step = 1);
    virtual ~GridLayer() {}

    int getStep();

    void setSpritePixmap(QString spritePath);
    void setSpritePixmap(QPixmap spritePixmap);

    virtual Sprite *addSprite(QPixmap *spritePixmap, QPoint position, Sprite* previousSpriteStack,
                              QGraphicsItem *parentItem);
    Sprite *addSprite(QPixmap *spritePixmap, QPoint position, Sprite *previousSpriteStack = NULL);
    virtual void removeSprite(QGraphicsItem *sprite);

    void drawBackground(QPainter *painter, const QRectF &rect);

public slots:
    void setSpritePixmap(QListWidgetItem* token);

protected:
    /**
     * @brief m_Step Cell's side size
     */
    int m_Step;

    /**
     * @brief m_SpritePixmap Currently selected pixmap, used to add new sprites.
     */
    QPixmap m_SpritePixmap;

    /**
     * @brief m_ActiveMouseMoveEvent true when mouseMoveEvent() is called, false when
     * mouseReleaseEvent() occurs.
     */
    bool m_ActiveMouseMoveEvent;

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void spriteMouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, Sprite *watched);

private:
    void drawRows(QPainter *painter, int rowLength, int limit, bool orientation);

};


#endif // GRIDLAYER_H