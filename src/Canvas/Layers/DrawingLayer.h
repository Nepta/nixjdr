#ifndef DRAWINGLAYER_H
#define DRAWINGLAYER_H

#include <QGraphicsPixmapItem>
#include <QColor>
#include <QPointF>
#include <QKeyEvent>
#include <QCursor>
#include <QByteArray>

#include "AbstractLayer.h"
#include "Canvas/Tools/Tools.h"

class DrawingLayer : public AbstractLayer
{
    Q_OBJECT

public:

    DrawingLayer(int penSize, int eraserSize, QColor color);
    DrawingLayer(DBItem item);
    ~DrawingLayer();
    void drawBackground(QPainter *, const QRectF &);
    QByteArray getPixmapData();
    void initDrawingZone(bool newPixmap = true);
    Tools *getTools();

public slots:
    void setPenSize(int size);
    void setEraserSize(int size);
    void erasePixmapContent();
    void changeTool();

private:
    int m_PenSize;
    int m_EraserSize;
    QColor m_Color;

    QGraphicsPixmapItem *m_DrawingZone;
    QPixmap *m_Pixmap;
    Tools *m_Tools;
    AbstractTool *m_OldTool;

    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);
};

#endif // DRAWINGLAYER_H
