#ifndef SPRITEREPOSITORY_H
#define SPRITEREPOSITORY_H

#include <QString>

#include "Database/Repository/Repository.h"
#include "Database/Database.h"

#include "Canvas/Sprite.h"

class SpriteRepository : public Repository
{
public:
    SpriteRepository() {}
    ~SpriteRepository() {}

    const QString getTableName();

    QueryBuilder insertSpriteQB(Sprite *sprite);

    int insertSprite(Sprite *sprite, Database *db);
};

#endif // SPRITEREPOSITORY_H
