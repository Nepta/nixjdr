#ifndef DRAWINGLAYER_H
#define DRAWINGLAYER_H

#include <QGraphicsPixmapItem>
#include <QColor>
#include "Layer.h"

class DrawingLayer : public Layer
{
    Q_OBJECT

public:
    DrawingLayer(int penSize, int eraserSize, QColor color);
    ~DrawingLayer();

    void initDrawingZone();

    void drawBackground(QPainter *, const QRectF &);

public slots:
    void setPenSize(int size);
    void setEraserSize(int size);
    void erasePixmapContent();

private:
    void paintOnPixmap(const QPointF &oldPos, const QPointF &pos, QColor color);
    void paintOnPixmap(QPainter &painter, const QPointF &oldPos, const QPointF &pos);
    void eraseOnPixmap(const QPointF &oldPos, const QPointF &pos);

    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);

    QGraphicsPixmapItem m_DrawingZone;
    QPixmap *m_Pixmap;
    QColor m_Color;
    int m_PenSize;
    int m_EraserSize;
};

#endif // DRAWINGLAYER_H
