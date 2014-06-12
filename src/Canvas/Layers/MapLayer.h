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

    MapLayer(TokenItem *tokenItem, int step = 1);
    MapLayer(DBItem item);
    ~MapLayer();

private:
    /**
     * @brief m_dragStartPosition Origin of a drag event
     */
    QPoint m_dragStartPosition;

    void initDragEvent(Sprite *watched, QGraphicsSceneMouseEvent *mouseEvent);
    void addSpriteInfoTooltip(Sprite *sprite);
    void addMoveInfoTooltip(QPoint currentMousePoss);
    void addCharacterInfoTooltip(GameObject *gameObject);

    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event, Sprite *watched);
    void dragMoveEvent(QGraphicsSceneDragDropEvent * event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent * event);
    void spriteMouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, Sprite *watched);
    void ShowContextMenu(QGraphicsSceneMouseEvent *mouseEvent, Sprite *watched);

signals:
    void pushInfoTooltip(QString info);
    void showMapTooltip();
    void hideMapTooltip();

};

#endif // MAPLAYER_H
