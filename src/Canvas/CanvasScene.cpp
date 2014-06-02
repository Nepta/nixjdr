#include "CanvasScene.h"

CanvasScene::CanvasScene(int width, int height)
{
    setSceneRect(0, 0, width, height);
}

CanvasScene::~CanvasScene() {}

void CanvasScene::addLayer(AbstractLayer *layer) {
    addItem(layer);
    m_Layers << layer;
}

int CanvasScene::getStep()
{
    return m_step;
}

void CanvasScene::drawBackground(QPainter *painter, const QRectF &rect) {
    QGraphicsScene::drawBackground(painter, rect);

    foreach(AbstractLayer *layer, m_Layers) {
        if (layer->isVisible()) {
            layer->drawBackground(painter, sceneRect());
        }
    }
}
