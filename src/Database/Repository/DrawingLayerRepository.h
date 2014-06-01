#ifndef DRAWINGLAYERREPOSITORY_H
#define DRAWINGLAYERREPOSITORY_H

#include "Canvas/Layers/DrawingLayer.h"

#include "Repository.h"

class DrawingLayerRepository : public Repository
{
public:
    DrawingLayerRepository() {}
    ~DrawingLayerRepository() {}

    const QString getTableName();

    int insertDrawingLayer(DrawingLayer *drawingLayer, Database *db);
};

#endif // DRAWINGLAYERREPOSITORY_H
