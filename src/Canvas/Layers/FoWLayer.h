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
    FoWLayer(DBItem item, bool transparentSprites = true);
    ~FoWLayer();

    Sprite *addSpriteToLayer(Sprite* sprite);
    void usePixmapAsBackgroundGrid();

private:
    /**
     * @brief m_TransparentSprites Defined whether or not Sprites should be transparent or not when
     * added to the Layer.
     */
    bool m_TransparentSprites;

    void construct(int step, bool transparentSprites);
    void paintGridOnPixmap(QPixmap *pixmap);

    void mousePressEvent(QGraphicsSceneMouseEvent *);
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

    QPixmap *m_GridPixmap;
    QGraphicsPixmapItem *m_DrawingZone;


private slots:
    void fillFoW();
    void removeFoW();
};

#endif // FOWLAYER_H
