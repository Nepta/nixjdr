#ifndef MAPLAYER_H
#define MAPLAYER_H

#include <QListWidgetItem>
#include <QPainter>
#include "GridLayer.h"

/**
 * @brief The MapLayer class contains a painted grid on which sprites can be positionned.
 */
class MapLayer : public GridLayer
{
    Q_OBJECT

public:
    /**
     * @brief START_DRAG_DISTANCE Distance to cover in order to start a drag event.
     */
    static const int START_DRAG_DISTANCE = 5;

    MapLayer(QString spritePath, int step = 1);
    ~MapLayer();

private:
    /**
     * @brief m_dragStartPosition Origin of a drag event
     */
    QPoint m_dragStartPosition;

    void initDragEvent(Sprite *watched, QGraphicsSceneMouseEvent *mouseEvent);
    void showSpriteTooltip(Sprite *sprite, QPoint pos);

    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event, Sprite *watched);
    void dragMoveEvent(QGraphicsSceneDragDropEvent * event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent * event);
    void spriteMouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, Sprite *watched);

signals:
    void showSpriteInfo(Sprite *sprite);
    void showMoveInfo(int oldPosX, int oldPosY, int CurrentPosX, int CurrentPosY);
    void hideInfo();

};

#endif // MAPLAYER_H