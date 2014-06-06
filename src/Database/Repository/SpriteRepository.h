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

    int insertSprite(Sprite *sprite);
    void removeAllSpritesFromFoWLayer(int fowLayerId);
    QString getSpriteName(int spriteId);
};

#endif // SPRITEREPOSITORY_H
