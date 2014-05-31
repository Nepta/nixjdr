#ifndef DRAWINGLAYER_H
#define DRAWINGLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QPointF>
#include <QKeyEvent>
#include <QCursor>
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

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);

    QGraphicsPixmapItem m_DrawingZone;
    QPixmap *m_Pixmap;
    int m_PenSize;
    int m_EraserSize;
    QColor m_Color;
    QPointF m_DrawStartPosition;
    QPointF m_DrawLastPosition;
    QGraphicsLineItem m_LineItem;
};

#endif // DRAWINGLAYER_H
