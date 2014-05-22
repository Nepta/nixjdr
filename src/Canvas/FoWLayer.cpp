#include "FoWLayer.h"

#include <QDebug>

FoWLayer::FoWLayer(int step) :
    GridLayer(step)
{
    // TODO multiple colors for multiple players (shift the hue of the pixmap?)
    GridLayer::setSpritePath("fow");
}

FoWLayer::~FoWLayer() {}

// reimplemented from GridLayer
void FoWLayer::mousePressEvent(QGraphicsSceneMouseEvent *) {
    qDebug() << __FILE__ << "mousePressEvent";
}

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

    return eventHandled;
}
