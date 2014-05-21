#include "MapLayer.h"
#include "Sprite.h"

#include <QDebug>

MapLayer::MapLayer(QString tokenPath, int step) {
    m_Step = step;
    setTokenPath(tokenPath);
}

MapLayer::~MapLayer() {}

void MapLayer::setTokenPath(QString tokenPath) {
    QString newPath = QString("resource/%1.png").arg(tokenPath);
    m_SpritePath = newPath;
}

void MapLayer::setTokenPath(QListWidgetItem *token) {
    setTokenPath(token->text());
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

// only redefined to grab events
void MapLayer::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {}

void MapLayer::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        QPoint mouseScenePos = mouseEvent->scenePos().toPoint();
        addSprite(mouseScenePos);
    }
}

void MapLayer::addSprite(QPoint position) {
    // QPoint division operator is not used in order to avoid results rounded to the nearest integer
    QPoint spritePos(position.x()/m_Step, position.y()/m_Step);
    spritePos *= m_Step;

    QPixmap *spritePixmap = new QPixmap(m_SpritePath);

    Sprite *sprite = new Sprite(*spritePixmap, this);
    sprite->setPos(spritePos);

    sprite->installSceneEventFilter(this);
}

void MapLayer::removeSprite(QGraphicsItem *sprite) {
    delete sprite;
}

bool MapLayer::sceneEventFilter(QGraphicsItem *watched, QEvent *event) {
    bool eventHandled = true;

    if (event->type() == QEvent::GraphicsSceneMouseRelease) {
        QGraphicsSceneMouseEvent *sceneMouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

        if (sceneMouseEvent->button() == Qt::RightButton) {
            removeSprite(watched);
        }
        else if (sceneMouseEvent->button() == Qt::LeftButton) {
            mouseReleaseEvent(sceneMouseEvent);
        }
    }

    //qDebug() << __FILE__ << "sceneEventFilter, Event: " << event->type() << " handled: " << eventHandled;

    return eventHandled;
}
