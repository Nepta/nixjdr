#include "GameObjects/Character.h"
#include "MapTooltip.h"

#include <QDebug>

MapTooltip::MapTooltip(QGraphicsView *view, QWidget *parent) :
    Tooltip(parent)
{
    m_View = view;
}

MapTooltip::~MapTooltip() {}

/**
 * @brief MapTooltip::addSpriteInfo Adds the number of sprites contained under the specified
 * sprite to the map tooltip.
 * @param sprite
 */
void MapTooltip::addSpriteInfo(Sprite *sprite) {
    QString spriteInfo = tr("Pile de jetons : %1 jeton(s).")
        .arg(sprite->zValue());

    pushInfo(spriteInfo);
}

/**
 * @brief MapTooltip::addCharacterInfo Displays information about the GameObject passed in parameter.
 * Character -> displays HP
 * @param gameObject
 */
void MapTooltip::addCharacterInfo(GameObject *gameObject) {
    Character *character = dynamic_cast<Character*>(gameObject);

    if (character != NULL) {
        QString charInfo = tr("HP : %1/%2")
                .arg(character->getHp())
                .arg(character->getMaxHp());

        pushInfo(charInfo);
    }
}

/**
 * @brief MapTooltip::addMoveInfo Adds the shortest distance between the start position of a
 * drag event and the current mouse position to the map tooltip.
 * @param currentMousePos
 */
void MapTooltip::addMoveInfo(int shortestDistance) {
    QString moveInfo = tr("Distance la plus courte: %1")
            .arg(shortestDistance);
    pushInfo(moveInfo);
}

/**
 * @brief MapTooltip::addNameInfo Adds the sprite's name to the map tooltip.
 * @param sprite
 */
void MapTooltip::addNameInfo(Sprite *sprite) {
    QString nameInfo = tr("Nom: %1").arg(sprite->getTokenItem()->text());
    pushInfo(nameInfo);
}

/**
 * @brief MapTooltip::show Displays the tooltip at the bottom right of the associated view.
 */
void MapTooltip::show() {
    QPoint position(
        m_View->size().width()  - size().width()  - Tooltip::TOOLTIP_OFFSET,
        m_View->size().height() - size().height() - Tooltip::TOOLTIP_OFFSET
    );

     Tooltip::show(position);
}
