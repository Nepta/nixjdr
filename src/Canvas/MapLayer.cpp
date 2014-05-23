#include <QMimeData>
#include <QDrag>
#include <QDragEnterEvent>
#include "MapLayer.h"
#include "Sprite.h"

MapLayer::MapLayer(QString tokenPath, int step) {
    m_Step = step;
    setTokenPath(tokenPath);
    setAcceptDrops(true);
}

MapLayer::~MapLayer() {}

void MapLayer::setTokenPath(QString tokenPath) {
    QString newPath = QString("resource/%1.png").arg(tokenPath);
    m_SpritePath = newPath;
}

void MapLayer::setTokenPath(QListWidgetItem *token) {
    setTokenPath(token->text());
}

void MapLayer::addSprite(QPoint position) {
    QPixmap *spritePixmap = new QPixmap(m_SpritePath);

    addSprite(spritePixmap, position);
}

void MapLayer::addSprite(QPixmap *spritePixmap, QPoint position) {
    // QPoint division operator is not used in order to avoid results rounded to the nearest integer
    QPoint spritePos(position.x()/m_Step, position.y()/m_Step);
    spritePos *= m_Step;

    Sprite *sprite = new Sprite(*spritePixmap, this);
    sprite->setPos(spritePos);

    sprite->installSceneEventFilter(this);
}

void MapLayer::removeSprite(QGraphicsItem *sprite) {
    delete sprite;
}

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

    removeSprite(watched);

    drag->exec(Qt::CopyAction | Qt::MoveAction);
}

// Reimplemented from Layer

void MapLayer::drawBackground(QPainter *painter, const QRectF &rect) {
    if(m_Step > 1) {
        drawRows(painter, rect.height(), rect.width(), true);
        drawRows(painter, rect.width(), rect.height(), false);
    }
}

void MapLayer::drawRows(QPainter *painter, int step, int limit, bool orientation){
    for (int i = 0 ; i < limit ; i ++) {
        painter->setPen(QPen(QBrush(Qt::black), 1));
        if(i%2 == 0){
            painter->setPen(QPen(QBrush(Qt::black), 2));
        }
        if(orientation){
            painter->drawLine(i*m_Step, 0, i*m_Step, step);
        }
        else{
            painter->drawLine(0, i*m_Step, step
                              , i*m_Step);
        }
    }
}


void MapLayer::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        m_dragStartPosition = mouseEvent->scenePos().toPoint();
    }
}

void MapLayer::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        QPoint mouseScenePos = mouseEvent->scenePos().toPoint();
        addSprite(mouseScenePos);
    }
}

void MapLayer::mouseMoveEvent(QGraphicsSceneMouseEvent *) {
}

void MapLayer::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    if (event->mimeData()->hasImage()){
        event->acceptProposedAction();
    }
}

void MapLayer::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    if(event->mimeData()->hasImage()){
        event->acceptProposedAction();
    }
}

void MapLayer::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QPixmap* sprite = new QPixmap;
    QImage image = qvariant_cast<QImage>(event->mimeData()->imageData());
    sprite->convertFromImage(image);

    addSprite(sprite, event->scenePos().toPoint());

    event->acceptProposedAction();
}

bool MapLayer::sceneEventFilter(QGraphicsItem *watched, QEvent *event) {
    bool eventHandled = true;

    QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

    switch ((int) event->type()) {
        case QEvent::GraphicsSceneMouseRelease: {
            qreal distanceCovered = (mouseEvent->buttonDownScenePos(Qt::RightButton)
                                            - mouseEvent->scenePos()).manhattanLength();

            if (mouseEvent->button() == Qt::RightButton && distanceCovered < DELTA_DELETE_SPRITE) {
                removeSprite(watched);
            }
            else if (mouseEvent->button() == Qt::LeftButton) {
                mouseReleaseEvent(mouseEvent);
            }
        } break;

        case QEvent::GraphicsSceneMouseMove: {
            if (mouseEvent->buttons() & Qt::LeftButton) {
                initDragEvent(watched, mouseEvent);
            }
        } break;
    }

    return eventHandled;
}
