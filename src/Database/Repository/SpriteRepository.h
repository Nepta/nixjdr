#ifndef SPRITEREPOSITORY_H
#define SPRITEREPOSITORY_H

#include <QString>
#include "Database/QueryBuilder.h"
#include "Database/Database.h"
#include "Canvas/Sprite.h"

class SpriteRepository
{
public:
    static const QString getTableName();

    static QueryBuilder getSpritesQB();
    static QueryBuilder insertSpriteQB(Sprite *sprite);

    static int insertSprite(Sprite *sprite, Database *db);
};

#endif // SPRITEREPOSITORY_H
