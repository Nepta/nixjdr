#ifndef MAP_H
#define MAP_H

#include "CanvasView.h"
#include "CanvasScene.h"
#include "MapLayer.h"

class Map
{
public:
    Map(QString bgFilename, QString tokenPath, int tileStep);
    ~Map();

    CanvasView *getView();
    MapLayer *getMapLayer();

private:
    CanvasScene m_Scene;
    CanvasView m_View;
    MapLayer m_MapLayer;
};

#endif // MAP_H
