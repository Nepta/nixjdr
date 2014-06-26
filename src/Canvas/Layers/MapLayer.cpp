#include <QMimeData>
#include <QDrag>
#include <QDragEnterEvent>
#include <QMenu>

#include "Database/Repository/RepositoryManager.h"
#include "Database/Repository/CharacterRepository.h"
#include "GameObjects/GameObjectDialog.h"
#include "GameObjects/Character.h"
#include "Canvas/Sprite.h"
#include "StyleSheet.h"
#include "MapLayer.h"

MapLayer::MapLayer(TokenItem *tokenItem, int step) :
    GridLayer(step)
{
    m_LayerType = LayerType::MAP_LAYER;

    m_SpriteName.setParentItem(this);
    m_SpriteName.hide();

    m_LifeBar.setParentItem(this);
    m_LifeBar.hide();

    m_Tooltip = NULL;

    setTokenItem(tokenItem);
    setAcceptDrops(true);
}

MapLayer::MapLayer(DBItem item) : GridLayer()
{
    m_LayerType = LayerType::MAP_LAYER;

    m_SpriteName.setParentItem(this);
    m_SpriteName.hide();

    m_LifeBar.setParentItem(this);
    m_LifeBar.hide();

    m_Tooltip = NULL;

    QHash<QString, QVariant> itemHashMap = item.getHashMap();
    columnsValues_ = item.getHashMap();

    int id =  itemHashMap.value("id").toInt();
    int step = itemHashMap.value("step").toInt();

    id_ = id;
    m_Step = step;

    setAcceptDrops(true);
}

MapLayer::~MapLayer() {}

/**
 * @brief MapLayer::initDragEvent Starts a drag event if a START_DRAG_DISTANCE has been traveled.
 * The sprite given in parameters (watched) becomes transparent at the beginning of the drag event.
 * Then, it becomes opaque again if the drag and drop failed, or the Sprite (watched) is deleted
 * from its original position after the drop succeeded.
 * @param watched
 * @param mouseEvent
 */
void MapLayer::initDragEvent(Sprite *watched, QGraphicsSceneMouseEvent *mouseEvent) {
    // only start the drag event when a certain distance has been traveled
    if ((mouseEvent->scenePos() - m_dragStartPosition).manhattanLength() < START_DRAG_DISTANCE) {
        return;
    }

    QDrag *drag = new QDrag(mouseEvent->widget());
    QMimeData *mime = new QMimeData;
    QByteArray data = watched->toQByteArray();

    mime->setData("application/sprite", data);
    drag->setMimeData(mime);

    QGraphicsPixmapItem *pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(watched);
    drag->setPixmap(pixmapItem->pixmap());

    watched->setTransparent(true);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);

    if (dropAction == Qt::IgnoreAction) {
        watched->setTransparent(false);
    } else {
        removeSprite(watched);
    }
}

/**
 * @brief MapLayer::mousePressEvent Reimplemented from GridLayer in order to grab mouse events.
 * @param mouseEvent
 */
void MapLayer::mousePressEvent(QGraphicsSceneMouseEvent *) {
}

void MapLayer::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    event->acceptProposedAction();
}

void MapLayer::dragLeaveEvent(QGraphicsSceneDragDropEvent *) {
    m_Tooltip->hide();
}

void MapLayer::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    event->acceptProposedAction();

    QPoint pos = event->scenePos().toPoint();
    m_Tooltip->addMoveInfo(getShorterDistance(pos));
    m_Tooltip->show();
}

/**
 * @brief MapLayer::dropEvent Reimplemented from GridLayer in order to create a Sprite at the
 * position of the drop event with the stored information in the mimeData.
 * @param event
 */
void MapLayer::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    hideLifeBar();
    hideSpriteName();
    dropEvent(event, NULL);
}

/**
 * @brief MapLayer::dropEvent Reimplemented from GridLayer. Adds a sprite at the position of the
 * drop event with the given MIME data through the event.
 * @param event
 * @param watched
 */
void MapLayer::dropEvent(QGraphicsSceneDragDropEvent *event, Sprite *watched)
{
    QByteArray tokenItemData = event->mimeData()->data("application/tokenitem");
    QByteArray spriteData = event->mimeData()->data("application/sprite");

    if(!tokenItemData.isEmpty()) {
        int zValue = (watched ? watched->zValue() + 1 : 1);
        TokenItem *tokenItem = new TokenItem(tokenItemData);
        addSprite(tokenItem, event->scenePos().toPoint(), zValue);
        prepareSpriteAdded(event->scenePos().toPoint(), tokenItem->text());

        event->acceptProposedAction();
    }
    else if (!spriteData.isEmpty()) {
        int zValue = (watched ? watched->zValue() + 1 : 1);
        Sprite *sprite = new Sprite(spriteData, this, zValue);
        addSprite(sprite, event->scenePos().toPoint());
        prepareSpriteMoved(event->scenePos().toPoint(), sprite->getTokenItem()->text());

        event->acceptProposedAction();
    }
}


void MapLayer::prepareSpriteAdded(QPoint eventPosition, QString tokenName){
    QString tokenItemPosition = QString("(%1,%2)")
        .arg(QString::number(eventPosition.x()/m_Step))
        .arg(QString::number(eventPosition.y()/m_Step));
    emit spriteAdded("[added]:"+tokenName+":"+tokenItemPosition);
}


void MapLayer::prepareSpriteMoved(QPoint eventPosition, QString tokenName){
    QString oldSpritePosition = QString("(%1,%2)")
            .arg(QString::number(m_dragStartPosition.x()/m_Step))
            .arg(QString::number(m_dragStartPosition.y()/m_Step));

    QString spritePosition = QString("(%1,%2)")
            .arg(QString::number(eventPosition.x()/m_Step))
            .arg(QString::number(eventPosition.y()/m_Step));

    QString wholeString = QString("[moved]: %1: %2->%3. Distance: %4")
            .arg(tokenName)
            .arg(oldSpritePosition)
            .arg(spritePosition)
            .arg(getShorterDistance(eventPosition));
    emit spriteMoved(wholeString);
}

/**
 * @brief MapLayer::spriteMouseReleaseEvent overrides GridLayer's function to create a context menu
 * @param watched
 * @param mouseEvent
 */
void MapLayer::spriteMouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent, Sprite *watched) {
    /* Avoid unexpected behaviours when both mouse buttons can be used (see also
     * GridLayer::mouseReleaseEvent) */
    if (mouseEvent->buttons() != Qt::NoButton) {
        return;
    }

    if (mouseEvent->button() == Qt::LeftButton) {
        QPoint mouseScenePos = mouseEvent->scenePos().toPoint();
        addSprite(m_TokenItem, mouseScenePos, watched->zValue() + 1);
		  QString tokenItemPosition = QString("(%1,%2)")
			  .arg(QString::number(mouseScenePos.x()/m_Step))
			  .arg(QString::number(mouseScenePos.y()/m_Step));
		  //NOTE never used?
		  emit spriteAdded("[added]:"+m_TokenItem->text()+":"+tokenItemPosition);
    }

    if(mouseEvent->button() == Qt::RightButton){
        ShowContextMenu(mouseEvent, watched);
    }

    m_Tooltip->hide();
}

/**
 * @brief MapLayer::ShowContextMenu shows a menu containing two actions: delete a token, or edit a
 * character
 * @param mouseEvent determines where the menu should be displayed from the event's position
 * @param watched sprite on which the event occured
 */
void MapLayer::ShowContextMenu(QGraphicsSceneMouseEvent *mouseEvent, Sprite *watched){
    QMenu menu;

    QAction* deleteAction = menu.addAction(tr("Supprimer"));
    QAction* editCharacterAction = menu.addAction(tr("Editer le personnage"));

    GameObject *gameObject = watched->getGameObject();
    Character *character = dynamic_cast<Character*>(gameObject);
    if (character == NULL) {
        editCharacterAction->setEnabled(false);
    }

    QAction* selectedItem = menu.exec(mouseEvent->screenPos());
    if(selectedItem == deleteAction){
		  QString spritePosition = QString("(%1,%2)")
			  .arg(QString::number(mouseEvent->scenePos().toPoint().x()/m_Step))
			  .arg(QString::number(mouseEvent->scenePos().toPoint().y()/m_Step));
          emit spriteRemoved("[delete]:"+watched->getTokenItem()->text()+":"+spritePosition);
		  removeSprite(watched);
    }
    else if(selectedItem == editCharacterAction) {
        GameObjectDialog gameObjectDlg(character);
        gameObjectDlg.exec();
        gameObjectDlg.close();

        // Update the Character in the database
        RepositoryManager::s_CharacterRepository.updateCharacter(character);

        // Update the character for all the clients
        updateSprite(watched);
    }
}

/**
 * @brief MapLayer::sceneEventFilter Handles events on Sprites.
 * @param watched
 * @param event
 * @return true if the event is handled by this class, false if the event should be handled by
 * the watched item.
 */
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
            spriteMouseReleaseEvent(mouseEvent, sprite);
        } break;

        case QEvent::GraphicsSceneMouseMove: {
            if (mouseEvent->buttons() & Qt::LeftButton) {
                initDragEvent(sprite, mouseEvent);
            }
        } break;

        case QEvent::GraphicsSceneDragEnter: {
        } break;

        case QEvent::GraphicsSceneDragMove: {
            QPoint pos = mouseEvent->scenePos().toPoint();

            m_Tooltip->addSpriteInfo(sprite);
            m_Tooltip->addMoveInfo(getShorterDistance(pos));
            m_Tooltip->addNameInfo(sprite);
            m_Tooltip->show();
        } break;

        case QEvent::GraphicsSceneDrop: {
            hideLifeBar();
            hideSpriteName();
            dropEvent(dragDropEvent, sprite);
            m_Tooltip->hide();
        }

        case QEvent::GraphicsSceneHoverEnter: {
            showLifeBar(sprite);
            showSpriteName(sprite);
        }

        case QEvent::GraphicsSceneHoverMove: {
            m_Tooltip->addSpriteInfo(sprite);
            m_Tooltip->addCharacterInfo(sprite->getGameObject());
            m_Tooltip->addNameInfo(sprite);
            m_Tooltip->show();
        } break;

        case QEvent::GraphicsSceneHoverLeave: {
            hideLifeBar();
            hideSpriteName();
            m_Tooltip->hide();
        } break;

        case QEvent::GraphicsSceneWheel: {
            if (!isEnabled()) {
                event->ignore();
            }
        } break;
    }

    return eventHandled;
}

int MapLayer::getShorterDistance(QPoint currentMousePos){
    QPoint oldPos(
        m_dragStartPosition.x() / m_Step,
        m_dragStartPosition.y() /m_Step
    );

    QPoint currentPos(
        currentMousePos.x() / m_Step,
        currentMousePos.y() / m_Step
    );

    int diffX = qAbs(oldPos.x() - currentPos.x());
    int diffY = qAbs(oldPos.y() - currentPos.y());
    int shorterDistance = std::max(diffX, diffY) + std::min(diffX,diffY)/2;
    return shorterDistance;
}

/**
 * @brief MapLayer::showLifeBar displays a sprite's lifebar as a circle around it
 * @param sprite sprite of which you want to display the lifebar
 */
void MapLayer::showLifeBar(Sprite *sprite) {
    GameObject *gameObject = sprite->getGameObject();
    Character *character = dynamic_cast<Character*>(gameObject);

    if (character != NULL) {
        m_LifeBar.setRadius(sprite->getTokenItem()->size());
        m_LifeBar.setPos(sprite->pos());
        m_LifeBar.setMaxValue(character->getMaxHp());
        m_LifeBar.setValue(character->getHp());
        m_LifeBar.setZValue(sprite->zValue() + 1);
        m_LifeBar.show();
    }
}

void MapLayer::hideLifeBar() {
    m_LifeBar.hide();
}

void MapLayer::showSpriteName(Sprite *sprite) {
    m_SpriteName.setText(sprite->getTokenItem()->text());
    m_SpriteName.setPosCenterItem(sprite, TextPixmap::SPRITE_OFFSET);
    m_SpriteName.setZValue(sprite->zValue() + 2);
    m_SpriteName.show();
}

void MapLayer::hideSpriteName() {
    m_SpriteName.hide();
}
