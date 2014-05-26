#include <QGraphicsScene>

#include "FoWLayer.h"

FoWLayer::FoWLayer(int step, bool transparentSprites) :
    GridLayer(step),
    m_TransparentSprites(transparentSprites)
{
    // TODO multiple colors for multiple players (shift the hue of the pixmap?)
    GridLayer::setSpritePixmap("fow");
}

FoWLayer::~FoWLayer() {}

// reimplemented from GridLayer
Sprite *FoWLayer::addSprite(QPixmap *spritePixmap, QPoint position, Sprite*) {
    Sprite* sprite = GridLayer::addSprite(spritePixmap, position);
    sprite->setTransparent(m_TransparentSprites);

    return sprite;
}

void FoWLayer::mousePressEvent(QGraphicsSceneMouseEvent *) {}

bool FoWLayer::sceneEventFilter(QGraphicsItem *watched, QEvent *event) {
    bool eventHandled = true;

    QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);

    if (event->type() == QEvent::GraphicsSceneMouseRelease) {
        qreal distanceCovered = (mouseEvent->buttonDownScenePos(Qt::RightButton)
                                        - mouseEvent->scenePos()).manhattanLength();

        if (mouseEvent->button() == Qt::RightButton && distanceCovered < DELTA_DELETE_SPRITE) {
            removeSprite(watched);
        }
    }

    if(event->type() == QEvent::GraphicsSceneMouseMove){
        if (mouseEvent->buttons() & Qt::LeftButton) {
            qreal distanceCovered = (mouseEvent->buttonDownScenePos(Qt::LeftButton)
                                     - mouseEvent->scenePos()).manhattanLength();
            if(distanceCovered > m_Step){
                addSprite(&m_SpritePixmap, mouseEvent->scenePos().toPoint());

            }
        }
    }

    return eventHandled;
}

void FoWLayer::fillFoW() {

    removeFoW();

    QPoint iterator(0,0);

    for(int i = 0; i < boundingRect().width(); i+=m_Step){
        for(int j = 0; j < boundingRect().height(); j +=m_Step){
            iterator.setX(i);
            iterator.setY(j);
            addSprite(&m_SpritePixmap, iterator);
        }
    }

}

void FoWLayer::removeFoW() {

    //QList<QGraphicsItem *> spriteList = this->findChildren<QGraphicsItem *>();

    foreach (QGraphicsItem* item, childItems()) {
        removeSprite(item);
    }

    /*for(auto sprite : spriteList){
        removeSprite(sprite);
    }*/
}
