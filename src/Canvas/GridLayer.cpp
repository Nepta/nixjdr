#include "GridLayer.h"
#include "Sprite.h"

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

void GridLayer::addSprite(QPixmap *spritePixmap, QPoint position) {
    QPoint spritePos(position.x()/m_Step, position.y()/m_Step);
    spritePos *= m_Step;

    Sprite *sprite = new Sprite(*spritePixmap, this);
    sprite->setPos(spritePos);

    sprite->installSceneEventFilter(this);
}

void GridLayer::removeSprite(QGraphicsItem *sprite) {
    delete sprite;
}

// Reimplemented from layer

void GridLayer::drawBackground(QPainter *painter, const QRectF &rect) {
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

void GridLayer::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        QPoint mouseScenePos = mouseEvent->scenePos().toPoint();
        addSprite(mouseScenePos);
    }
}
