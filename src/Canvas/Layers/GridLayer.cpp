#include <QGraphicsScene>

#include "Database/Repository/RepositoryManager.h"

#include "GridLayer.h"

GridLayer::GridLayer(int step)
{
    m_Step = step;
    m_ActiveMouseMoveEvent = false;
    m_LastRemovedSpritePoint = QPointF(-1,-1);
}

/**
 * @brief GridLayer::addSpriteToLayer Creates a new Sprite with the given parameters and adds it to
 * the layer.
 * @param tokenItem
 * @param position
 * @param zValue
 * @return The newly created and added Sprite.
 */
Sprite *GridLayer::addSpriteToLayer(TokenItem *tokenItem, QPoint position, int zValue) {
    QPoint spritePos(position.x()/m_Step, position.y()/m_Step);
    spritePos *= m_Step;

    Sprite *sprite = new Sprite(tokenItem, this, zValue);
    sprite->setPos(spritePos);

    addSpriteToLayer(sprite);

    return sprite;
}

/**
 * @brief GridLayer::addSprite Adds the given sprite to this layer.
 * @param sprite Sprite to add to this layer.
 * @return The added Sprite.
 */
Sprite *GridLayer::addSpriteToLayer(Sprite* sprite) {
    sprite->installSceneEventFilter(this);

    return sprite;
}

/**
 * @brief GridLayer::addSprite Adds a sprite to the db and sends a notification to all the clients.
 * @param tokenItem Sprite's associated TokenItem.
 * @param position Sprite's position
 * @param zValue Indicates the position of the sprite in the stack.
 */
void GridLayer::addSprite(TokenItem *tokenItem, QPoint position, int zValue) {
    Sprite *sprite = addSpriteToLayer(tokenItem, position, zValue);

    // Insert the sprite in the database
    RepositoryManager::s_SpriteRepository.insertSprite(sprite);

    // Notifies every client that a new sprite has been added
    QString msg = QString("addSprite %1").arg(sprite->id());
    m_SenderClient->sendMessageToServer(msg);
}

/**
 * @brief GridLayer::removeSpriteToDb Notifies to all the clients that a sprite need to be
 * removed and delete it locally on the layer.
 * @param sprite
 */
void GridLayer::removeSprite(Sprite *sprite) {
    // Notifies all the clients that a Sprite needs to be removed
    QString msg = QString("removeSprite %1").arg(sprite->id());
    m_SenderClient->sendMessageToServer(msg);

    // Delete the sprite from the layer
    delete sprite;
}

/**
 * @brief GridLayer::removeSpriteById Remove a sprite on the grid which possess the given id
 * @param id
 */
void GridLayer::removeSpriteById(int id) {
    for (QGraphicsItem *item : childItems()) {
        Sprite *sprite = dynamic_cast<Sprite*>(item);

        if (sprite->id() == id) {
            delete sprite;
            break;
        }
    }
}

/**
 * @brief GridLayer::removeAllSprites Remove all the sprites from the layer.
 */
void GridLayer::removeAllSprites() {
    qDeleteAll(childItems());
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
            painter->setPen(QPen(QBrush(Qt::lightGray), 2));
        } else {
            painter->setPen(QPen(QBrush(Qt::lightGray), 1));
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

    /* Avoid unexpected behaviours when both mouse buttons can be used (e.g. a sprite is added on the
     * left mouse button release, and then the sprite under the new one is deleted on a right mouse
     * button release */
    if (mouseEvent->buttons() != Qt::NoButton) {
        return;
    }

    if (mouseEvent->button() == Qt::LeftButton) {
        QPoint mouseScenePos = mouseEvent->scenePos().toPoint();
        addSprite(m_TokenItem, mouseScenePos);
    }
}

/**
 * @brief GridLayer::mouseMoveEvent Reimplemented from Layer. Handles the creation (left mouse
 * button held) and deletion (right mouse button held) of Sprites continuously.
 * @param mouseEvent
 */
void GridLayer::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QPoint mouseScenePos = mouseEvent->scenePos().toPoint();
    m_ActiveMouseMoveEvent = true;

    QGraphicsItem *item = scene()->itemAt(mouseEvent->pos(), QTransform());
    Sprite *sprite = dynamic_cast<Sprite*>(item);

    if (mouseEvent->buttons() & Qt::LeftButton) {
        if (!sprite && isInScene(mouseEvent)) {
            addSprite(m_TokenItem, mouseScenePos, 1);
        }
    }
    else if (mouseEvent->buttons() & Qt::RightButton) {
        // avoid deletion of items from another layer
        if (!childItems().contains(item)) {
            m_LastRemovedSpritePoint = QPointF(-1,-1);
            return;
        }

        if (sprite && m_LastRemovedSpritePoint != sprite->scenePos()) { // TODO timer or boolean to slow down the deletion
            m_LastRemovedSpritePoint = sprite->scenePos();
            removeSprite(sprite);
        }
    }
}

bool GridLayer::isInScene(QGraphicsSceneMouseEvent *mouseEvent){
    int x = mouseEvent->pos().x();
    int y = mouseEvent->pos().y();
    QRectF sceneRect = scene()->sceneRect();
    if(x > sceneRect.left()
            && x < sceneRect.right()
            && y < sceneRect.bottom()
            && y > sceneRect.top()){
        return true;
    }
    else{
        return false;
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

int GridLayer::getStep() {
    return m_Step;
}

void GridLayer::setTokenItem(QListWidgetItem* token) {
    TokenItem *tokenItem = dynamic_cast<TokenItem*>(token);
    m_TokenItem = tokenItem;
}
