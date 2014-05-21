#ifndef MAP_H
#define MAP_H

#include "CanvasView.h"
#include "CanvasScene.h"
#include "MapLayer.h"

class Map : public CanvasView
{
public:
    Map(QString bgFilename, QString tokenPath, int tileStep);
    ~Map();

    MapLayer *getMapLayer();

private:
    MapLayer m_MapLayer;
};

#endif // MAP_H
