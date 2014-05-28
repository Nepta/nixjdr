#include <QMimeData>
#include <QDrag>
#include <QDragEnterEvent>

#include "Canvas/Sprite.h"
#include "MapLayer.h"

MapLayer::MapLayer(QString spritePath, int step) :
    GridLayer(step)
{
    setSpritePixmap(spritePath);
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

    QGraphicsPixmapItem *pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(watched);
    mime->setImageData(pixmapItem->pixmap().toImage());
    drag->setMimeData(mime);
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
    if (event->mimeData()->hasImage()){
        event->acceptProposedAction();
    }
}

void MapLayer::dragLeaveEvent(QGraphicsSceneDragDropEvent *) {
    emit hideMapTooltip();
}

void MapLayer::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    if(event->mimeData()->hasImage()){
        event->acceptProposedAction();

        QPoint pos = event->scenePos().toPoint();
        addMoveInfoTooltip(pos);
        emit showMapTooltip();
    }
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
 * drop event with the image given in the event MIME data.
 * @param event
 * @param watched
 */
void MapLayer::dropEvent(QGraphicsSceneDragDropEvent *event, Sprite *watched)
{
    QPixmap* sprite = new QPixmap;
    QImage image = qvariant_cast<QImage>(event->mimeData()->imageData());
    sprite->convertFromImage(image);

    addSprite(sprite, event->scenePos().toPoint(), watched);

    event->acceptProposedAction();
}

/**
 * @brief MapLayer::spriteMouseReleaseEvent Reimplemented from GridLayer to add the following
 * behaviour : on a left mouse button release, add a sprite at the given position.
 * @param watched
 * @param mouseEvent
 */
void MapLayer::spriteMouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, Sprite *watched) {
    GridLayer::spriteMouseReleaseEvent(mouseEvent, watched);

    /* Avoid unexpected behaviours when both mouse buttons can be used (see also
     * GridLayer::mouseReleaseEvent) */
    if (mouseEvent->buttons() != Qt::NoButton) {
        return;
    }

    if (mouseEvent->button() == Qt::LeftButton) {
        QPoint mouseScenePos = mouseEvent->scenePos().toPoint();
        addSprite(&m_SpritePixmap, mouseScenePos, watched);
    }

    emit hideMapTooltip();
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

        case QEvent::GraphicsSceneDragMove: {
            QPoint pos = mouseEvent->scenePos().toPoint();

            addSpriteInfoTooltip(sprite);
            addMoveInfoTooltip(pos);
            emit showMapTooltip();
        } break;

        case QEvent::GraphicsSceneDrop: {
            dropEvent(dragDropEvent, sprite);
            emit hideMapTooltip();
        }

        case QEvent::GraphicsSceneHoverMove: {
            addSpriteInfoTooltip(sprite);
            emit showMapTooltip();
        } break;

        case QEvent::GraphicsSceneHoverLeave: {
            emit hideMapTooltip();
        } break;
    }

    return eventHandled;
}

/**
 * @brief MapLayer::addSpriteInfoTooltip Adds the number of sprites contained under the specified
 * sprite to the map tooltip.
 * @param sprite
 */
void MapLayer::addSpriteInfoTooltip(Sprite *sprite) {
    QString spriteInfo = tr("Pile de jetons : %1 jeton(s).")
        .arg(sprite->getStackNumber());

    emit pushInfoTooltip(spriteInfo);
}

/**
 * @brief MapLayer::addMoveInfoTooltip Adds the shortest distance between the start position of a
 * drag event and the current mouse position to the map tooltip.
 * @param currentMousePos
 */
void MapLayer::addMoveInfoTooltip(QPoint currentMousePos) {
    QPoint oldPos(
        m_dragStartPosition.x() / m_Step,
        m_dragStartPosition.y() /m_Step
    );

    QPoint currentPos(
        currentMousePos.x() / m_Step,
        currentMousePos.y() / m_Step
    );

    int diffX = qAbs(oldPos.x() - currentPos.x());
    int diffY = qAbs(oldPos.y() - currentPos.y());
    int shorterDistance = std::max(diffX, diffY) + std::min(diffX,diffY)/2;

    QString moveInfo = QString(tr("Distance la plus courte: %1")).arg(shorterDistance);
    emit pushInfoTooltip(moveInfo);
}
