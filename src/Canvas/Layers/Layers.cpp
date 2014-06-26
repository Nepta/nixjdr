#include "Layers.h"

const QHash<QString, LayerCodes> Layers::s_ButtonCodesMap = {
    {"m_BgDisplay", LayerCodes::LAYER_BACKGROUND},

    {"m_DrawingDisplay", LayerCodes::LAYER_DRAW},
    {"m_DrawingEdit", LayerCodes::LAYER_DRAW},

    {"m_FowDisplay", LayerCodes::LAYER_FOW},
    {"m_FowEdit", LayerCodes::LAYER_FOW},

    {"m_MapDisplay", LayerCodes::LAYER_MAP},
    {"m_MapEdit", LayerCodes::LAYER_MAP}
};

Layers::Layers(QPixmap bgPixmap, int penSize, int eraserSize, QColor color, int step,
               TokenItem *tokenItem, bool transparentFoW){

    m_LayersMap.insert(LayerCodes::LAYER_BACKGROUND, new BackgroundLayer(bgPixmap));
    m_LayersMap.insert(LayerCodes::LAYER_DRAW, new DrawingLayer(penSize, eraserSize, color));
    m_LayersMap.insert(LayerCodes::LAYER_FOW, new FoWLayer(step, transparentFoW));
    m_LayersMap.insert(LayerCodes::LAYER_MAP, new MapLayer(tokenItem, step));

    m_CurrentLayerCode = LayerCodes::LAYER_MAP;
}

Layers::Layers(BackgroundLayer *bgLayer, MapLayer *mapLayer, FoWLayer *fowLayer,
    DrawingLayer *drawingLayer)
{
    m_LayersMap.insert(LayerCodes::LAYER_BACKGROUND, bgLayer);
    m_LayersMap.insert(LayerCodes::LAYER_DRAW, drawingLayer);
    m_LayersMap.insert(LayerCodes::LAYER_FOW, fowLayer);
    m_LayersMap.insert(LayerCodes::LAYER_MAP, mapLayer);

    m_CurrentLayerCode = LayerCodes::LAYER_MAP;
}

Layers::~Layers(){
    qDeleteAll(m_LayersMap);
}

QList<AbstractLayer *> Layers::getLayersList(){
    return m_LayersMap.values();
}

AbstractLayer *Layers::getLayer(LayerCodes code){
    return m_LayersMap.value(code);
}

void Layers::setCurrentLayerCode(QString key){
    getLayer(m_CurrentLayerCode)->setEnabled(false);
    m_CurrentLayerCode = s_ButtonCodesMap.value(key);
    getLayer(m_CurrentLayerCode)->setEnabled(true);
}

AbstractLayer *Layers::getCurrentLayer(){
    return getLayer(m_CurrentLayerCode);
}
