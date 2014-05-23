#ifndef GRIDLAYER_H
#define GRIDLAYER_H

#include <QPainter>
#include <QRectF>
#include <QString>
#include "Sprite.h"
#include "Layer.h"

class GridLayer : public Layer
{
public:
    /**
     * @brief DELTA_DELETE_SPRITE The event called to delete a Sprite is valid if the cursor does not
     * cover a distance superior to this constant.
     */
    static const int DELTA_DELETE_SPRITE = 40;

    GridLayer(int step = 1);
    virtual ~GridLayer() {}

    void setSpritePath(QString spritePath);

    virtual void addSprite(QPoint position);
    virtual Sprite *addSprite(QPixmap *spritePixmap, QPoint spritePos);
    virtual void removeSprite(QGraphicsItem *sprite);

    /**
     * @brief drawBackground Draw a grid.
     * @param painter
     * @param rect
     */
    void drawBackground(QPainter *painter, const QRectF &rect);

    /**
     * @brief drawRows Draws parallel lines with the given painter with an interval equal to the
     * given step. Every two lines, draws a thicker line.
     * @param painter
     * @param step
     * @param limit
     * @param orientation
     */
    void drawRows(QPainter *painter, int step, int limit, bool orientation);

    /**
     * @brief mouseReleaseEvent Reimplemented from GridLayer in order to create Sprites when the left
     * mouse button is released on an empty cell.
     * @param mouseEvent
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

protected:
    int m_Step;
    QString m_SpritePath;
};

#endif // GRIDLAYER_H
