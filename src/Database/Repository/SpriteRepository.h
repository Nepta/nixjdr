#ifndef SPRITEREPOSITORY_H
#define SPRITEREPOSITORY_H

#include "Database/Repository/Repository.h"
#include "Token/TokenList.h"
#include "Canvas/Layers/AbstractLayer.h"
#include "Canvas/Layers/FoWLayer.h"
#include "Canvas/Layers/MapLayer.h"
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
    QList<Sprite*> getFoWSprites(TokenList *tokenList, FoWLayer *fowLayer);
    QList<Sprite*> getMapSprites(TokenList *tokenList, MapLayer *mapLayer);
    QList<Sprite*> getSprites(QueryBuilder qb, TokenList *tokenList, AbstractLayer *layer);
};

#endif // SPRITEREPOSITORY_H
