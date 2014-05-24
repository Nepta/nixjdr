#ifndef DRAWINGLAYER_H
#define DRAWINGLAYER_H

#include <QGraphicsPixmapItem>
#include "Layer.h"

class DrawingLayer : public Layer
{
public:
    DrawingLayer();
    ~DrawingLayer();

    void initDrawingZone();

    void drawBackground(QPainter *, const QRectF &);

private:
    void paintOnPixmap(const QPointF &oldPos, const QPointF &pos);
    void eraseOnPixmap(const QPointF pos);

    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);

    QGraphicsPixmapItem m_DrawingZone;
    QPixmap *m_Pixmap;
    int m_PenSize;
    QSize m_EraserSize;
};

#endif // DRAWINGLAYER_H
