#include "CanvasScene.h"

#include <QDebug>

CanvasScene::CanvasScene(QString filename)
{
    m_background = new QPixmap(filename);

    const int width = m_background->width();
    const int height = m_background->height();

    //initMatrix(width, height);

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

/*void CanvasScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsScene::mousePressEvent(mouseEvent);

    qDebug() << __FILE__ << " Press "
             << "item pos: " << mouseEvent->pos()
             << "scene pos: " << mouseEvent->scenePos()
             << "view pos: " << mouseEvent->screenPos();

    foreach(Layer *layer, m_Layers) {
        layer->mousePressEvent(mouseEvent);
    }
}*/

/*void CanvasScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsScene::mouseReleaseEvent(mouseEvent);

    qDebug() << __FILE__ << " Release "
             << "item pos: " << mouseEvent->pos()
             << "scene pos: " << mouseEvent->scenePos()
             << "view pos: " << mouseEvent->screenPos();

    foreach(Layer *layer, m_Layers) {
        layer->mouseReleaseEvent(mouseEvent);
    }
}*/

