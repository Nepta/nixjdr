#include "CanvasScene.h"

CanvasScene::CanvasScene(int width, int height)
{
    setSceneRect(0, 0, width, height);
}

CanvasScene::~CanvasScene() {}

void CanvasScene::addLayer(Layer *layer) {
    addItem(layer);
    m_Layers << layer;
}

void CanvasScene::drawBackground(QPainter *painter, const QRectF &rect) {
    QGraphicsScene::drawBackground(painter, rect);

    foreach(Layer *layer, m_Layers) {
        if (layer->isVisible()) {
            layer->drawBackground(painter, sceneRect());
        }
    }
}
