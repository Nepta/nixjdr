#ifndef MAPLAYERREPOSITORY_H
#define MAPLAYERREPOSITORY_H

#include "Canvas/Layers/MapLayer.h"

#include "Repository.h"

class MapLayerRepository : public Repository
{
public:
    MapLayerRepository() {}
    ~MapLayerRepository() {}

    const QString getTableName();

    QueryBuilder insertMapLayerQB(MapLayer *mapLayer);

    int insertMapLayer(MapLayer *mapLayer, Database *db);
};

#endif // MAPLAYERREPOSITORY_H
