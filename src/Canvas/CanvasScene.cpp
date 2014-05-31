#include "CanvasScene.h"

CanvasScene::CanvasScene(int sceneWidth, int sceneHeight) {
    setSceneRect(0, 0, sceneWidth, sceneHeight);
}

CanvasScene::CanvasScene() {
    setSceneRect(0, 0, 1, 1);
}
CanvasScene::~CanvasScene() {}

void CanvasScene::addLayer(Layer *layer) {
    addItem(layer);
    m_Layers << layer;
}

int CanvasScene::getStep()
{
    return m_step;
}

void CanvasScene::drawBackground(QPainter *painter, const QRectF &rect) {
    QGraphicsScene::drawBackground(painter, rect);

    foreach(Layer *layer, m_Layers) {
        if (layer->isVisible()) {
            layer->drawBackground(painter, sceneRect());
        }
    }
}
