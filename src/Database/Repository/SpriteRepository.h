#ifndef SPRITEREPOSITORY_H
#define SPRITEREPOSITORY_H

#include <QString>

#include "Database/Repository/Repository.h"
#include "Database/QueryBuilder.h"
#include "Database/Database.h"

#include "Canvas/Sprite.h"

class SpriteRepository : public Repository
{
public:
    const QString getTableName();

    QueryBuilder getSpritesQB();
    QueryBuilder insertSpriteQB(Sprite *sprite);

    int insertSprite(Sprite *sprite, Database *db);
};

#endif // SPRITEREPOSITORY_H
