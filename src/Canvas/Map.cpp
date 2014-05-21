#include "Map.h"

Map::Map(QString bgFilename, QString tokenPath, int tileStep) :
    m_MapLayer(tokenPath, tileStep)
{
    CanvasScene *scene = new CanvasScene(bgFilename);
    scene->addLayer(&m_MapLayer);
    setScene(scene);
    setWindowTitle(tr("Carte"));
}

Map::~Map() {
}

MapLayer *Map::getMapLayer() {
    return &m_MapLayer;
}
