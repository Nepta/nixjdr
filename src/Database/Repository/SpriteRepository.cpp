#include <QGraphicsItem>
#include "Canvas/Layers/FoWLayer.h"
#include "Canvas/Layers/MapLayer.h"
#include "SpriteRepository.h"

const QString SpriteRepository::getTableName() {
    return "sprite";
}

/**
 * @brief SpriteRepository::insertSprite Inserts the given Sprite in the database, retrieve the id
 * given by the db to the new row and sets it on the Sprite.
 * @param sprite Sprite which will be inserted in the db.
 * @param db
 * @return Id given by the database to the newly inserted row.
 */
int SpriteRepository::insertSprite(Sprite *sprite) {
    QHash<QString, QVariant> args {
        {"posx", sprite->pos().x()},
        {"posy", sprite->pos().y()},
        {"zvalue", sprite->zValue()},
        {"tokenitemid", sprite->getTokenItem()->id()},
    };

    QGraphicsItem* item = sprite->parentItem();
    MapLayer *mapLayer = dynamic_cast<MapLayer*>(item);
    FoWLayer *fowLayer = dynamic_cast<FoWLayer*>(item);
    if (mapLayer) {
        args.insert("maplayerid", mapLayer->id());
    }
    else if (fowLayer) {
        args.insert("fowlayerid", fowLayer->id());
    }

    QueryBuilder qb = insertQB(args.keys());
    int id = insert(sprite, qb, args);

    return id;
}

void SpriteRepository::removeAllSpritesFromFoWLayer(int fowLayerId) {
    QueryBuilder qb;

    qb.deleteFrom(getTableName())->where("fowlayerid = " + QString::number(fowLayerId));
    Database::instance()->push(qb.getQuery());
}

QString SpriteRepository::getSpriteName(int spriteId){
	QueryBuilder qb;

    // Retrieve the sprite name from the db's view "sprite_name"
	qb.select("name")->from("sprite_name")->where("id = " + QString::number(spriteId));
    DBItem spriteName = Database::instance()->pullFirst(qb.getQuery());
	return spriteName.getHashMap().value("name").toString();
}
