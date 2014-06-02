#ifndef CANVASSCENE_H
#define CANVASSCENE_H

#include <QPixmap>
#include <QGraphicsScene>
#include <QList>
#include "Layers/AbstractLayer.h"

class CanvasScene : public QGraphicsScene {
    Q_OBJECT

public:
    CanvasScene(int width, int height);
    ~CanvasScene();
    void addLayer(AbstractLayer *layer);
    int getStep();

private:
    void drawBackground (QPainter *painter, const QRectF &rect);

    int m_step;
    QList<AbstractLayer*> m_Layers;
};

#endif // CANVASSCENE_H


