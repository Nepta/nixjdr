#ifndef SPRITEREPOSITORY_H
#define SPRITEREPOSITORY_H

#include <QString>
#include "DataBase/QueryBuilder.h"
#include "Canvas/Sprite.h"

class SpriteRepository
{
public:
    static const QString getTableName();
    static QueryBuilder addSprite(Sprite *sprite);
    static QueryBuilder getSprites();
};

#endif // SPRITEREPOSITORY_H
