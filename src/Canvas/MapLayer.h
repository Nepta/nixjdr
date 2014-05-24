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
    static const int START_DRAG_DISTANCE = 40;

    MapLayer(QString spritePath, int step = 1);
    ~MapLayer();

public slots:
    void setSpritePath(QListWidgetItem* token);

private:
    QPoint m_dragStartPosition;

    void initDragEvent(QGraphicsItem *watched, QGraphicsSceneMouseEvent *mouseEvent);

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
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief dropEvent Reimplemented from GridLayer in order to create a Sprite at the position of the
     * drop event with the stored information in the mimeData.
     * @param event
     */
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent * event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
};

#endif // MAPLAYER_H