#include "SpriteRepository.h"

const QString SpriteRepository::getTableName() {
    return "sprite";
}

QueryBuilder SpriteRepository::addSprite(Sprite *sprite) {
    // TODO
}

QueryBuilder SpriteRepository::getSprites() {
    QueryBuilder qb;
    qb.select("s.id, s.name, s.path, s.size")
     ->from(getTableName(), "s");

    return qb;
}
