#ifndef FOWLAYER_H
#define FOWLAYER_H

#include "GridLayer.h"

class FoWLayer : public GridLayer
{
public:
    FoWLayer(int step = 1);
    ~FoWLayer();

private:

    /**
     * @brief mousePressEvent Reimplemented from GridLayer in order to grab mouse events
     * @param mouseEvent
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);
};

#endif // FOWLAYER_H
