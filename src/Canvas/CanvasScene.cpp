#include "CanvasScene.h"

CanvasScene::CanvasScene(int sceneWidth, int sceneHeight) {
    setSceneRect(0, 0, sceneWidth, sceneHeight);
}

CanvasScene::CanvasScene() {
    setSceneRect(0, 0, 1, 1);
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

/**
 * @brief CanvasScene::drawBackground calls drawBackground for every layer present on the scene
 * @param painter
 * @param rect
 */
void CanvasScene::drawBackground(QPainter *painter, const QRectF &rect) {
    QGraphicsScene::drawBackground(painter, rect);

    foreach(AbstractLayer *layer, m_Layers) {
        if (layer->isVisible()) {
            layer->drawBackground(painter, sceneRect());
        }
    }
}
