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

    int insertMapLayer(MapLayer *mapLayer);
};

#endif // MAPLAYERREPOSITORY_H
