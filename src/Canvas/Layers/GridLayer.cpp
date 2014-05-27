#include "GridLayer.h"

GridLayer::GridLayer(int step) {
    m_Step = step;
    m_ActiveMouseMoveEvent = false;
}

void GridLayer::setSpritePixmap(QString spritePath) {
    QString newPath = QString("resource/%1.png").arg(spritePath);

    setSpritePixmap(QPixmap(newPath));
}

void GridLayer::setSpritePixmap(QListWidgetItem* token) {
    if (token != NULL) {
        QPixmap spritePixmap = token->icon().pixmap(QSize(m_Step, m_Step));
        setSpritePixmap(spritePixmap);
    }
}

void GridLayer::setSpritePixmap(QPixmap spritePixmap) {
    m_SpritePixmap = spritePixmap;
}

/**
 * @brief GridLayer::addSprite Adds a sprite to the Layer.
 * @param spritePixmap Sprite's pixmap.
 * @param position Sprite's position
 * @param previousSpriteStack Indicates the Sprite on top of which the new Sprite will be created
 * (Sprites can be stacked).
 * @param parentItem Indicates in which QGraphicsItem the new Sprite belongs (in general the layer
 * in which the sprite is created).
 * @return The newly created sprite.
 */
Sprite *GridLayer::addSprite(QPixmap *spritePixmap, QPoint position, Sprite* previousSpriteStack,
    QGraphicsItem *parentItem)
{
    QPoint spritePos(position.x()/m_Step, position.y()/m_Step);
    spritePos *= m_Step;

    Sprite *sprite = new Sprite(*spritePixmap, parentItem, previousSpriteStack);
    sprite->setPos(spritePos);

    if (parentItem != NULL) {
        sprite->installSceneEventFilter(this);
    }

    return sprite;
}

/**
 * @brief GridLayer::addSprite Overloaded for convenience.
 * @param spritePixmap
 * @param position
 * @param previousSpriteStack
 * @return The newly created sprite.
 * @sa addSprite()
 */
Sprite *GridLayer::addSprite(QPixmap *spritePixmap, QPoint position, Sprite *previousSpriteStack) {
    return addSprite(spritePixmap, position, previousSpriteStack, this);
}

/**
 * @brief GridLayer::removeSprite Remove the given Sprite.
 * @param sprite
 */
void GridLayer::removeSprite(QGraphicsItem *sprite) {
    delete sprite;
}

/**
 * @brief GridLayer::drawBackground Reimplemented from Layer. Draw a grid.
 * @param painter
 * @param rect
 */
void GridLayer::drawBackground(QPainter *painter, const QRectF &rect) {
    if(m_Step > 1) {
        drawRows(painter, rect.height(), rect.width(), true);
        drawRows(painter, rect.width(), rect.height(), false);
    }
}

/**
 * @brief GridLayer::drawRows Draws parallel lines with the given painter with an interval equal to m_Step.
 * Every two lines, draws a thicker line.
 * @param painter
 * @param rowLength Line length.
 * @param limit Number of lines to draw.
 * @param orientation true vertical, false horizontal
 */
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

/**
 * @brief GridLayer::mouseReleaseEvent Reimplemented from Layer. Creates Sprites when the left mouse
 * button is released on an empty cell. Don't create a Sprite if the previous event was a
 * mouseMoveEvent (prevents an additional Sprite from appearing at the end of the mouseMoveEvent).
 * @param mouseEvent
 */
void GridLayer::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (m_ActiveMouseMoveEvent) {
        m_ActiveMouseMoveEvent = false;
        return;
    }

    if (mouseEvent->button() == Qt::LeftButton) {
        QPoint mouseScenePos = mouseEvent->scenePos().toPoint();
        addSprite(&m_SpritePixmap, mouseScenePos);
    }
}

/**
 * @brief GridLayer::mouseMoveEvent Reimplemented from Layer. Handles the creation (left mouse
 * button held) and deletion (right mouse button held) of Sprites continuously.
 * @param mouseEvent
 */
void GridLayer::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QPoint mouseScenePos = mouseEvent->scenePos().toPoint();
    Sprite *sprite = addSprite(&m_SpritePixmap, mouseScenePos, NULL, NULL);
    m_ActiveMouseMoveEvent = true;

    if (mouseEvent->buttons() & Qt::LeftButton) {
        foreach (QGraphicsItem *item, childItems()) {
            if (item->collidesWithItem(sprite)) {
                delete sprite;
                return;
            }
        }

        sprite->setParentItem(this);
        sprite->installSceneEventFilter(this);
    }
    else if (mouseEvent->buttons() & Qt::RightButton) {
        foreach (QGraphicsItem *item, childItems()) {
            if (item->collidesWithItem(sprite)) {
                delete item;
            }
        }
        delete sprite;
    }
}

/**
 * @brief GridLayer::spriteMouseReleaseEvent On a right mouse button release, delete the sprite (only
 * if the cursor does not move outside the DELTA_DELETE_SPRITE distance).
 * @param watched
 * @param mouseEvent
 */
void GridLayer::spriteMouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, Sprite *watched) {
    qreal distanceCovered = (mouseEvent->buttonDownScenePos(Qt::RightButton)
                                    - mouseEvent->scenePos()).manhattanLength();

    if (mouseEvent->button() == Qt::RightButton && distanceCovered < DELTA_DELETE_SPRITE) {
        removeSprite(watched);
    }
}
