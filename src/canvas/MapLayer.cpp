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
    QGraphicsPixmapItem *pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(watched);

    QDrag *drag = new QDrag(mouseEvent->widget());
    QMimeData *mime = new QMimeData;

    mime->setImageData(pixmapItem->pixmap().toImage());
    drag->setMimeData(mime);

    drag->setPixmap(pixmapItem->pixmap());

    removeSprite(watched);

    drag->exec(Qt::CopyAction | Qt::MoveAction);
}

// Reimplemented from Layer

void MapLayer::drawBackground(QPainter *painter, const QRectF &rect) {
    if(m_Step > 1) {
        painter->setPen(Qt::black);

        for (int i = 0 ; i < rect.width() ; i += m_Step) {
            painter->drawLine(i, 0, i, rect.height());
        }

        for (int i = 0 ; i < rect.height() ; i += m_Step) {
            painter->drawLine(0, i, rect.width(), i);
        }
    }
}

void MapLayer::mousePressEvent(QGraphicsSceneMouseEvent *) {}

void MapLayer::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        QPoint mouseScenePos = mouseEvent->scenePos().toPoint();
        addSprite(mouseScenePos);
    }
}

void MapLayer::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    if (event->mimeData()->hasImage()){
        event->acceptProposedAction();
    }
}

void MapLayer::dragMoveEvent(QGraphicsSceneDragDropEvent * event) {
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

void MapLayer::mouseMoveEvent(QGraphicsSceneMouseEvent *) {
}


bool MapLayer::sceneEventFilter(QGraphicsItem *watched, QEvent *event) {
    bool eventHandled = true;

    QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

    switch ((int) event->type()) {
        case QEvent::GraphicsSceneMouseRelease: {
            if (mouseEvent->button() == Qt::RightButton &&
                    mouseEvent->buttonDownScenePos(Qt::RightButton) == mouseEvent->scenePos()) {
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
