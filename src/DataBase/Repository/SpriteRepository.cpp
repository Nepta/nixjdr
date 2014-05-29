#include "SpriteRepository.h"

const QString SpriteRepository::getTableName() {
    return "sprite";
}

QueryBuilder SpriteRepository::addSprite(Sprite *sprite) {
    // TODO
}

QueryBuilder SpriteRepository::getSprites() {
    QueryBuilder qb;
    qb.select("id, name, path, size")
     ->from(getTableName());

    return qb;
}
