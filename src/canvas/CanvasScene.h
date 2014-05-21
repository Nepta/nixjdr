#ifndef CANVASSCENE_H
#define CANVASSCENE_H

#include <QPainter>
#include <QPixmap>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include <QGraphicsSceneMouseEvent>
#include "Layer.h"

class CanvasScene : public QGraphicsScene {
    Q_OBJECT

public:
    CanvasScene(QString filename);
    ~CanvasScene();
    void addLayer(Layer *layer);

private:
    void drawBackground (QPainter *painter, const QRectF &rect);

    int m_step;
    QPixmap *m_background;
    QList<Layer*> m_Layers;
};

#endif // CANVASSCENE_H


