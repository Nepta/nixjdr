#include <QMimeData>
#include <QDrag>
#include <QDragEnterEvent>
#include <QMenu>

#include "Canvas/Sprite.h"
#include "MapLayer.h"

MapLayer::MapLayer(TokenItem *tokenItem, int step) :
    GridLayer(step)
{
    setTokenItem(tokenItem);
    setAcceptDrops(true);
}

MapLayer::MapLayer(DBItem item) : GridLayer()
{
    QHash<QString, QVariant> itemHashMap = item.getHashMap();
    columnsValues_ = item.getHashMap();

    int id =  itemHashMap.value("id").toInt();
    int step = itemHashMap.value("step").toInt();

    id_ = id;
    m_Step = step;
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
    emit hideMapTooltip();
}

void MapLayer::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    event->acceptProposedAction();

    QPoint pos = event->scenePos().toPoint();
    addMoveInfoTooltip(pos);
    emit showMapTooltip();
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
        int zValue = (watched ? watched->zValue() + 1 : 1);
        addSpriteToDb(tokenItem, event->scenePos().toPoint(), zValue);

        event->acceptProposedAction();
    }
}

/**
 * @brief MapLayer::spriteMouseReleaseEvent overrides GridLayer's function to create a context menu
 * @param watched
 * @param mouseEvent
 */
void MapLayer::spriteMouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, Sprite *watched) {
    /* Avoid unexpected behaviours when both mouse buttons can be used (see also
     * GridLayer::mouseReleaseEvent) */
    if (mouseEvent->buttons() != Qt::NoButton) {
        return;
    }

    if (mouseEvent->button() == Qt::LeftButton) {
        QPoint mouseScenePos = mouseEvent->scenePos().toPoint();
        addSpriteToDb(m_TokenItem, mouseScenePos, watched->zValue() + 1);
    }

    if(mouseEvent->button() == Qt::RightButton){
        ShowContextMenu(mouseEvent, watched);
    }

    emit hideMapTooltip();
}


void MapLayer::ShowContextMenu(QGraphicsSceneMouseEvent *mouseEvent, Sprite *watched){
    QMenu menu;

    QAction* deleteAction = menu.addAction(tr("Supprimer"));
    QAction* rangeAction = menu.addAction(tr("Rechercher une portée"));

    QAction* selectedItem = menu.exec(mouseEvent->screenPos());
    if(selectedItem == deleteAction){
        removeSprite(watched);
    }
    else if(selectedItem == rangeAction){

    }
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

        case QEvent::GraphicsSceneWheel: {
            if (!isEnabled()) {
                event->ignore();
            }
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
        .arg(sprite->zValue());

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
