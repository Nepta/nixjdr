#ifndef DRAWINGLAYER_H
#define DRAWINGLAYER_H

#include <QGraphicsPixmapItem>
#include <QColor>
#include <QPointF>
#include <QKeyEvent>
#include <QCursor>

#include "Layer.h"
#include "Canvas/Tools/Tools.h"

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
    QGraphicsPixmapItem *m_DrawingZone;
    QPixmap *m_Pixmap;
    int m_PenSize;
    int m_EraserSize;
    QColor m_Color;
    QPointF m_DrawStartPosition;
    QPointF m_DrawLastPosition;
    QGraphicsLineItem m_LineItem;

    Tools m_Tools;
};

#endif // DRAWINGLAYER_H
