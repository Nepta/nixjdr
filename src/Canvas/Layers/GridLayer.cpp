#include "GridLayer.h"

GridLayer::GridLayer(int step) {
    m_Step = step;
}

void GridLayer::setSpritePath(QString spritePath) {
    QString newPath = QString("resource/%1.png").arg(spritePath);
    m_SpritePath = newPath;
}

void GridLayer::addSprite(QPoint position) {
    QPixmap *spritePixmap = new QPixmap(m_SpritePath);

    addSprite(spritePixmap, position);
}

Sprite *GridLayer::addSprite(QPixmap *spritePixmap, QPoint position) {
    QPoint spritePos(position.x()/m_Step, position.y()/m_Step);
    spritePos *= m_Step;

    Sprite *sprite = new Sprite(*spritePixmap, this);
    sprite->setPos(spritePos);

    sprite->installSceneEventFilter(this);

    return sprite;
}

void GridLayer::removeSprite(QGraphicsItem *sprite) {
    delete sprite;
}

// Reimplemented from layer

void GridLayer::drawBackground(QPainter *painter, const QRectF &rect) {
    if(m_Step > 1) {
        drawRows(painter, rect.height(), rect.width(), true);
        drawRows(painter, rect.width(), rect.height(), false);
    }
}

void GridLayer::drawRows(QPainter *painter, int rowLength, int limit, bool orientation){
    for (int i = 0 ; i < limit ; i += m_Step) {
        if (i/m_Step % 2 == 0) {
            painter->setPen(QPen(QBrush(Qt::black), 2));
        } else {
            painter->setPen(QPen(QBrush(Qt::black), 1));
        }

        if (orientation) {
            painter->drawLine(i, 0, i, rowLength);
        }
        else {
            painter->drawLine(0, i, rowLength, i);
        }
    }
}

void GridLayer::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        QPoint mouseScenePos = mouseEvent->scenePos().toPoint();
        addSprite(mouseScenePos);
    }
}
