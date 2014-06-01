#ifndef FOWLAYERREPOSITORY_H
#define FOWLAYERREPOSITORY_H

#include "Database/Repository/Repository.h"

#include "Canvas/Layers/FoWLayer.h"

class FoWLayerRepository : public Repository
{
public:
    FoWLayerRepository() {}
    ~FoWLayerRepository() {}

    const QString getTableName();

    QueryBuilder insertFoWLayerQB(FoWLayer *fowLayer);

    int insertFoWLayer(FoWLayer *fowLayer, Database *db);
};

#endif // FOWLAYERREPOSITORY_H
