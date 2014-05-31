#ifndef CANVASSCENE_H
#define CANVASSCENE_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QList>
#include "Layers/Layer.h"

class CanvasScene : public QGraphicsScene {
    Q_OBJECT

public:
    CanvasScene(int sceneWidth, int sceneHeight);
    CanvasScene();
    ~CanvasScene();
    void addLayer(Layer *layer);
    int getStep();

private:
    void drawBackground (QPainter *painter, const QRectF &rect);

    int m_step;
    QList<Layer*> m_Layers;
};

#endif // CANVASSCENE_H


