#ifndef SPRITEREPOSITORY_H
#define SPRITEREPOSITORY_H

#include "Database/Repository/Repository.h"

#include "Canvas/Sprite.h"

class SpriteRepository : public Repository
{
public:
    SpriteRepository() {}
    ~SpriteRepository() {}

    const QString getTableName();

    int insertSprite(Sprite *sprite, Database *db);
    void removeAllSpritesFromFoWLayer(int fowLayerId, Database *db);
	 QString getSpriteName(int spriteId, Database *db);
};

#endif // SPRITEREPOSITORY_H
