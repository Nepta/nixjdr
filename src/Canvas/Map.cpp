#include "Map.h"

Map::Map(QString bgFilename, QString tokenPath, int tileStep) :
    m_Scene(bgFilename), m_View(&m_Scene), m_MapLayer(tokenPath, tileStep)
{
    m_Scene.addLayer(&m_MapLayer);
}

Map::~Map() {}

CanvasView *Map::getView() {
    return &m_View;
}

MapLayer *Map::getMapLayer() {
    return &m_MapLayer;
}
