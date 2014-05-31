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
    void drawBackground(QPainter *, const QRectF &);

    void initDrawingZone();
    Tools *getTools();

public slots:
    void setPenSize(int size);
    void setEraserSize(int size);
    void erasePixmapContent();
    void changeTool();

private:
    QGraphicsPixmapItem *m_DrawingZone;
    QPixmap *m_Pixmap;
    Tools *m_Tools;
};

#endif // DRAWINGLAYER_H
