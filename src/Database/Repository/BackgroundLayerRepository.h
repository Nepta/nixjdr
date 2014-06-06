#ifndef BACKGROUNDLAYERREPOSITORY_H
#define BACKGROUNDLAYERREPOSITORY_H

#include "Canvas/Layers/BackgroundLayer.h"

#include "Repository.h"

class BackgroundLayerRepository : public Repository
{
public:
    BackgroundLayerRepository() {}
    ~BackgroundLayerRepository() {}

    const QString getTableName();

    int insertBgLayer(BackgroundLayer *bgLayer);
};

#endif // BACKGROUNDLAYERREPOSITORY_H
