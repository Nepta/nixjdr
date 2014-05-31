#ifndef FOWLAYER_H
#define FOWLAYER_H

#include "GridLayer.h"

/**
 * @brief The FoWLayer class represents a Grid on which fog of war Sprites can be positionned and
 * removed.
 */
class FoWLayer : public GridLayer
{
    Q_OBJECT

public:
    FoWLayer(int step = 1, bool transparentSprites = true);
    ~FoWLayer();

    Sprite *addSprite(TokenItem *tokenItem, QPoint position, int zValue, QGraphicsItem *parentItem);

private:
    /**
     * @brief m_TransparentSprites Defined whether or not Sprites should be transparent or not when
     * added to the Layer.
     */
    bool m_TransparentSprites;

    void mousePressEvent(QGraphicsSceneMouseEvent *);
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

private slots:
    void fillFoW();
    void removeFoW();
};

#endif // FOWLAYER_H
