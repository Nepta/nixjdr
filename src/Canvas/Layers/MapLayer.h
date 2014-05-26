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
    QPoint m_dragStartPosition;

    void initDragEvent(QGraphicsItem *watched, QGraphicsSceneMouseEvent *mouseEvent);
    void showSpriteTooltip(Sprite *sprite, QPoint pos);

    /**
     * @brief sceneEventFilter Handles events on Sprites.
     * @param watched
     * @param event
     * @return true if the event is handled by this class, false if the event should be handled by
     * the watched item.
     */
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

    /**
     * @brief mousePressEvent Reimplemented from GridLayer in order to grab mouse events
     * @param mouseEvent
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *);

    /**
     * @brief dropEvent Reimplemented from GridLayer in order to create a Sprite at the position of the
     * drop event with the stored information in the mimeData.
     * @param event
     */
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event, Sprite *parentSprite);
    void dragMoveEvent(QGraphicsSceneDragDropEvent * event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);

signals:
    void showSpriteInfo(Sprite *sprite);
    void hideSpriteInfo();
};

#endif // MAPLAYER_H
