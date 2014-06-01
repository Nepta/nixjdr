#include <QGraphicsItem>
#include "Canvas/Layers/FoWLayer.h"
#include "Canvas/Layers/MapLayer.h"
#include "SpriteRepository.h"

const QString SpriteRepository::getTableName() {
    return "sprite";
}

QueryBuilder SpriteRepository::insertSpriteQB(Sprite *sprite) {
    QList<QString> args;
    args.append(QString::number(sprite->pos().x()));
    args.append(QString::number(sprite->pos().y()));
    args.append(QString::number(sprite->zValue()));
    args.append(QString::number(sprite->getTokenItem()->id()));

    QGraphicsItem* item = sprite->parentItem();
    MapLayer *mapLayer = dynamic_cast<MapLayer*>(item);
    FoWLayer *fowLayer = dynamic_cast<FoWLayer*>(item);
    if (mapLayer) {
        args.append(QString::number(mapLayer->id()));
        args.append("NULL");
    }
    else if (fowLayer) {
        args.append("NULL");
        args.append(QString::number(fowLayer->id()));
    }

    QueryBuilder qb;
    qb.insertInto(getTableName(), "posx, posy, zvalue, tokenitemid, maplayerid, fowlayerid")
     ->values(args);

    return qb;
}

/**
 * @brief SpriteRepository::insertSprite Inserts the given Sprite in the database, retrieve the id
 * given by the db to the new row and sets it on the Sprite.
 * @param sprite Sprite which will be inserted in the db.
 * @param db
 * @return Id given by the database to the newly inserted row.
 */
int SpriteRepository::insertSprite(Sprite *sprite, Database *db) {
    QueryBuilder qb = insertSpriteQB(sprite);
    int id = db->pushWithId(qb);
    sprite->setId(id);

    return id;
}

