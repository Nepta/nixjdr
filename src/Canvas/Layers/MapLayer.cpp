#include <QMimeData>
#include <QDrag>
#include <QDragEnterEvent>

#include "Canvas/Sprite.h"
#include "MapLayer.h"

MapLayer::MapLayer(Database *db, TokenItem *tokenItem, int step) :
    GridLayer(db, step)
{
    setTokenItem(tokenItem);
    setAcceptDrops(true);
}

MapLayer::~MapLayer() {}

/**
 * @brief MapLayer::initDragEvent Starts a drag event if a START_DRAG_DISTANCE has been traveled.
 * The sprite given in parameters (watched) becomes transparent at the beginning of the drag event.
 * Then, it becomes opaque again if the drag and drop failed, or the Sprite (watched) is deleted
 * from its original position after the drop succeeded.
 * @param watched
 * @param mouseEvent
 */
void MapLayer::initDragEvent(Sprite *watched, QGraphicsSceneMouseEvent *mouseEvent) {
    // only start the drag event when a certain distance has been traveled
    if ((mouseEvent->scenePos() - m_dragStartPosition).manhattanLength() < START_DRAG_DISTANCE) {
        return;
    }

    QDrag *drag = new QDrag(mouseEvent->widget());
    QMimeData *mime = new QMimeData;
    QByteArray data = watched->getTokenItem()->toQByteArray();

    mime->setData("application/tokenitem", data);
    drag->setMimeData(mime);

    QGraphicsPixmapItem *pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(watched);
    drag->setPixmap(pixmapItem->pixmap());

    watched->setTransparent(true);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);

    if (dropAction == Qt::IgnoreAction) {
        watched->setTransparent(false);
    } else {
        removeSprite(watched);
    }
}

/**
 * @brief MapLayer::mousePressEvent Reimplemented from GridLayer in order to grab mouse events.
 * @param mouseEvent
 */
void MapLayer::mousePressEvent(QGraphicsSceneMouseEvent *) {
}

void MapLayer::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    event->acceptProposedAction();
}

void MapLayer::dragLeaveEvent(QGraphicsSceneDragDropEvent *) {
    emit hideInfo();
}

void MapLayer::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    QPoint pos = event->scenePos().toPoint();
    event->acceptProposedAction();

    emit showMoveInfo(
        m_dragStartPosition.x() / m_Step,
        m_dragStartPosition.y() /m_Step,
        pos.x() / m_Step,
        pos.y() / m_Step
    );
}

/**
 * @brief MapLayer::dropEvent Reimplemented from GridLayer in order to create a Sprite at the
 * position of the drop event with the stored information in the mimeData.
 * @param event
 */
void MapLayer::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dropEvent(event, NULL);
}

/**
 * @brief MapLayer::dropEvent Reimplemented from GridLayer. Adds a sprite at the position of the
 * drop event with the given MIME data through the event.
 * @param event
 * @param watched
 */
void MapLayer::dropEvent(QGraphicsSceneDragDropEvent *event, Sprite *watched)
{
    QByteArray data = event->mimeData()->data("application/tokenitem");
    if(!data.isEmpty()) {
        TokenItem *tokenItem = new TokenItem(data);
        addSprite(tokenItem, event->scenePos().toPoint(), watched);

        event->acceptProposedAction();
    }
}

/**
 * @brief MapLayer::spriteMouseReleaseEvent Reimplemented from GridLayer to add the following
 * behaviour : on a left mouse button release, add a sprite at the given position.
 * @param watched
 * @param mouseEvent
 */
void MapLayer::spriteMouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, Sprite *watched) {
    GridLayer::spriteMouseReleaseEvent(mouseEvent, watched);

    if (mouseEvent->button() == Qt::LeftButton) {
        QPoint mouseScenePos = mouseEvent->scenePos().toPoint();
        addSprite(m_TokenItem, mouseScenePos, watched);
    }

    emit hideInfo();
}

/**
 * @brief MapLayer::sceneEventFilter Handles events on Sprites.
 * @param watched
 * @param event
 * @return true if the event is handled by this class, false if the event should be handled by
 * the watched item.
 */
bool MapLayer::sceneEventFilter(QGraphicsItem *watched, QEvent *event) {
    bool eventHandled = true;

    Sprite *sprite = dynamic_cast<Sprite *>(watched);
    QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
    QGraphicsSceneDragDropEvent *dragDropEvent = static_cast<QGraphicsSceneDragDropEvent*>(event);

    switch ((int) event->type()) {
        case QEvent::GraphicsSceneMousePress: {
            if (mouseEvent->button() == Qt::LeftButton) {
                m_dragStartPosition = mouseEvent->scenePos().toPoint();
            }
        } break;

        case QEvent::GraphicsSceneMouseRelease: {
            spriteMouseReleaseEvent(mouseEvent, sprite);
        } break;

        case QEvent::GraphicsSceneMouseMove: {
            if (mouseEvent->buttons() & Qt::LeftButton) {
                initDragEvent(sprite, mouseEvent);
            }
        } break;

        case QEvent::GraphicsSceneDrop: {
            dropEvent(dragDropEvent, sprite);
            emit hideInfo();
        }

        case QEvent::GraphicsSceneHoverMove: {
            emit showSpriteInfo(sprite);
        } break;

        case QEvent::GraphicsSceneHoverLeave: {
            emit hideInfo();
        } break;
    }

    return eventHandled;
}
