#include <QGraphicsItem>

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

    // Retrieve the sprite name from the db's view "spritename"
    qb.select("name")->from("spritename")->where("id = " + QString::number(spriteId));
    DBItem spriteName = Database::instance()->pullFirst(qb.getQuery());
	return spriteName.getHashMap().value("name").toString();
}

/**
 * @brief SpriteRepository::getFoWSprites Get all the FoW Sprites associated with the given FoWLayer.
 * @param tokenList TokenList containing TokenItems which are used to load a Sprite (a Sprite possess
 * a TokenItem).
 * @param fowLayer FoWLayer which is empty and needs to be filled with the Sprites which are
 * associated to it.
 * @return QList of Sprites
 * @remarks The FoWLayer given in parameter must be a FoWLayer which has just been retrieved from
 * the database and which is empty (the associated Sprites are not yet retrieved from the database).
 */
QList<Sprite*> SpriteRepository::getFoWSprites(TokenList *tokenList, FoWLayer *fowLayer) {
    QueryBuilder qb = findAllQB();
    qb.where("fowlayerid = " + QString::number(fowLayer->id()));

    return getSprites(qb, tokenList, fowLayer);
}

/**
 * @brief SpriteRepository::getMapSprites Get all the Map Sprites associated with the given MapLayer.
 * @param tokenList
 * @param mapLayer
 * @return QList of Sprites
 * @sa getFoWSprites()
 */
QList<Sprite*> SpriteRepository::getMapSprites(TokenList *tokenList, MapLayer *mapLayer) {
    QueryBuilder qb = findAllQB();
    qb.where("maplayerid = " + QString::number(mapLayer->id()));

    return getSprites(qb, tokenList, mapLayer);
}

QList<Sprite*> SpriteRepository::getSprites(QueryBuilder qb, TokenList *tokenList,
    AbstractLayer *layer)
{
    DBItemList<Sprite> dbItemList(Database::instance()->pull(qb.getQuery()));
    QList<DBItem> dbItems = dbItemList.getList();
    QList<Sprite*> sprites;

    for (DBItem dbItem : dbItems) {
        int tokenItemId = dbItem.getHashMap().value("tokenitemid").toInt();
        TokenItem *tokenItem = tokenList->findTokenItemById(tokenItemId);
        Sprite *sprite = new Sprite(dbItem, tokenItem, layer);
        sprites.append(sprite);
    }

    return sprites;
}
