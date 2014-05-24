#ifndef DRAWINGLAYER_H
#define DRAWINGLAYER_H

#include <QGraphicsPixmapItem>
#include "Layer.h"

class DrawingLayer : public Layer
{
    Q_OBJECT

public:
    DrawingLayer(int penSize, int eraserSize);
    ~DrawingLayer();

    void initDrawingZone();

    void drawBackground(QPainter *, const QRectF &);

public slots:
    void setPenSize(int size);
    void setEraserSize(int size);
    void erasePixmapContent();

private:
    void paintOnPixmap(const QPointF &oldPos, const QPointF &pos, Qt::GlobalColor color);
    void paintOnPixmap(QPainter &painter, const QPointF &oldPos, const QPointF &pos);
    void eraseOnPixmap(const QPointF &oldPos, const QPointF &pos);

    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);

    QGraphicsPixmapItem m_DrawingZone;
    QPixmap *m_Pixmap;
    int m_PenSize;
    int m_EraserSize;
};

#endif // DRAWINGLAYER_H
