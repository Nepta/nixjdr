#ifndef MAPLAYER_H
#define MAPLAYER_H

#include <QListWidgetItem>
#include <QPainter>
#include "Layer.h"

/**
 * @brief The MapLayer class contains a painted grid on which sprites can be positionned.
 */
class MapLayer : public Layer
{
    Q_OBJECT

public:
    /**
     * @brief START_DRAG_DISTANCE Distance to cover in order to start a drag event.
     */
    static const int START_DRAG_DISTANCE = 10;

    /**
     * @brief DELTA_DELETE_SPRITE The event called to delete a Sprite is valid if the cursor does not
     * cover a distance superior to this constant.
     */
    static const int DELTA_DELETE_SPRITE = 40;

    MapLayer(QString tokenPath, int step = 1);
    ~MapLayer();

    void setTokenPath(QString tokenPath);
    void addSprite(QPoint position);
    void addSprite(QPixmap *pixmap, QPoint position);
    void removeSprite(QGraphicsItem *sprite);

public slots:
    void setTokenPath(QListWidgetItem* token);

private:
    int m_Step;
    QString m_SpritePath;
    QPoint m_dragStartPosition;

    void initDragEvent(QGraphicsItem *watched, QGraphicsSceneMouseEvent *mouseEvent);

    /**
     * @brief drawBackground Draw a grid.
     * @param painter
     * @param rect
     */
    void drawBackground(QPainter *painter, const QRectF &rect);

    /**
     * @brief sceneEventFilter Handles events on Sprites.
     * @param watched
     * @param event
     * @return true if the event is handled by this class, false if the event should be handled by
     * the watched item.
     */
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

    /**
     * @brief mousePressEvent Reimplemented from Layer in order to grab mouse events
     * @param mouseEvent
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

    /**
     * @brief mouseReleaseEvent Reimplemented from Layer in order to create Sprites when the left
     * mouse button is released on an empty cell. Also called by sceneEventFilter to add Sprites on
     * top of already present ones.
     * @param mouseEvent
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief dropEvent Reimplemented from Layer in order to create a Sprite at the position of the
     * drop event with the stored information in the mimeData.
     * @param event
     */
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent * event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);

};

#endif // MAPLAYER_H
