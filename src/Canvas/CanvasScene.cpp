#include "CanvasScene.h"

CanvasScene::CanvasScene(QString filename)
{
    m_background = new QPixmap(filename);

    const int width = m_background->width();
    const int height = m_background->height();

    this->setSceneRect(0, 0, width, height);
    this->setBackgroundBrush(*m_background);
}

CanvasScene::~CanvasScene()
{
    delete m_background;
}

void CanvasScene::addLayer(Layer *layer) {
    addItem(layer);
    m_Layers << layer;
}

void CanvasScene::drawBackground(QPainter *painter, const QRectF &rect) {
    QGraphicsScene::drawBackground(painter, rect);

    foreach(Layer *layer, m_Layers) {
        layer->drawBackground(painter, sceneRect());
    }
}
