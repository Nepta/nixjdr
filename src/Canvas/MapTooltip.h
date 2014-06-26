#ifndef MAPTOOLTIP_H
#define MAPTOOLTIP_H

#include <QGraphicsView>

#include "GameObjects/GameObject.h"
#include "Tooltip.h"
#include "Sprite.h"

class MapTooltip : public Tooltip
{
public:
    MapTooltip(QGraphicsView *view, QWidget *parent = 0);
    ~MapTooltip();

    void addCharacterInfo(GameObject *gameObject);
    void addSpriteInfo(Sprite *sprite);
    void addMoveInfo(int shortestDistance);
    void addNameInfo(Sprite *sprite);
    void show();

private:
    QGraphicsView *m_View;
};

#endif // MAPTOOLTIP_H
