#ifndef MAPLAYER_H
#define MAPLAYER_H

#include <QListWidgetItem>
#include <QPainter>

#include "General/TextPixmap.h"
#include "General/CircularProgressBar.h"
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

    CircularProgressBar m_LifeBar;
    TextPixmap m_SpriteName;

    void initDragEvent(Sprite *watched, QGraphicsSceneMouseEvent *mouseEvent);

    int getShorterDistance(QPoint currentMousePos);

    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event, Sprite *watched);

    void prepareSpriteAdded(QPoint eventPosition, QString tokenName);
    void prepareSpriteMoved(QPoint eventPosition, QString tokenName);

    void dragMoveEvent(QGraphicsSceneDragDropEvent * event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent * event);
    void spriteMouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, Sprite *watched);
    void ShowContextMenu(QGraphicsSceneMouseEvent *mouseEvent, Sprite *watched);

    void showLifeBar(Sprite *sprite);
    void hideLifeBar();

    void showSpriteName(Sprite *sprite);
    void hideSpriteName();

signals:
    void spriteMoved(QString info);

};

#endif // MAPLAYER_H
