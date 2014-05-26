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

void MapLayer::initDragEvent(QGraphicsItem *watched, QGraphicsSceneMouseEvent *mouseEvent) {
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

    watched->setOpacity(0.50);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);

    if (dropAction == Qt::IgnoreAction) {
        watched->setOpacity(1.0);
    } else {
        removeSprite(watched);
    }
}

// Reimplemented from GridLayer

void MapLayer::mousePressEvent(QGraphicsSceneMouseEvent *) {
}

void MapLayer::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    if (event->mimeData()->hasImage()){
        event->acceptProposedAction();
    }
}

void MapLayer::dragLeaveEvent(QGraphicsSceneDragDropEvent *event){
    emit hideInfo();
}

void MapLayer::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    if(event->mimeData()->hasImage()){
        QPoint pos = event->scenePos().toPoint();
        event->acceptProposedAction();
        emit showMoveInfo(m_dragStartPosition.x() / m_Step, m_dragStartPosition.y() /m_Step,
                          pos.x() / m_Step, pos.y() / m_Step);
    }
}

void MapLayer::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dropEvent(event, NULL);
}

void MapLayer::dropEvent(QGraphicsSceneDragDropEvent *event, Sprite *parentSprite)
{
    QPixmap* sprite = new QPixmap;
    QImage image = qvariant_cast<QImage>(event->mimeData()->imageData());
    sprite->convertFromImage(image);

    addSprite(sprite, event->scenePos().toPoint(), parentSprite);

    event->acceptProposedAction();
}

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
            qreal distanceCovered = (mouseEvent->buttonDownScenePos(Qt::RightButton)
                                            - mouseEvent->scenePos()).manhattanLength();

            if (mouseEvent->button() == Qt::RightButton && distanceCovered < DELTA_DELETE_SPRITE) {
                removeSprite(watched);
            }
            else if (mouseEvent->button() == Qt::LeftButton) {
                QPoint mouseScenePos = mouseEvent->scenePos().toPoint();
                addSprite(&m_SpritePixmap, mouseScenePos, sprite);
            }

            emit hideInfo();

        } break;

        case QEvent::GraphicsSceneMouseMove: {
            if (mouseEvent->buttons() & Qt::LeftButton) {
                initDragEvent(watched, mouseEvent);
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
