#ifndef GRIDLAYER_H
#define GRIDLAYER_H

#include <QPainter>
#include <QRectF>
#include <QString>
#include <QListWidgetItem>
#include "Canvas/Sprite.h"
#include "Layer.h"

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

    void setSpritePixmap(QString spritePath);
    void setSpritePixmap(QPixmap spritePixmap);

    virtual Sprite *addSprite(QPixmap *spritePixmap, QGraphicsItem *parentItem, QPoint position, Sprite* parentSprite);
    virtual Sprite *addSprite(QPixmap *spritePixmap, QPoint position,  Sprite* parentSprite = NULL);
    virtual void removeSprite(QGraphicsItem *sprite);

    /**
     * @brief drawBackground Draw a grid.
     * @param painter
     * @param rect
     */
    void drawBackground(QPainter *painter, const QRectF &rect);

public slots:
    void setSpritePixmap(QListWidgetItem* token);

protected:
    int m_Step;
    QPixmap m_SpritePixmap;

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void spriteMouseReleaseEvent(Sprite *sprite, QGraphicsSceneMouseEvent *mouseEvent);

private:
    /**
     * @brief drawRows Draws parallel lines with the given painter with an interval equal to the
     * given step. Every two lines, draws a thicker line.
     * @param painter
     * @param step
     * @param limit
     * @param orientation true vertical, false horizontal
     */
    void drawRows(QPainter *painter, int rowLength, int limit, bool orientation);

};


#endif // GRIDLAYER_H
