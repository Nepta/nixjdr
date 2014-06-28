#ifndef TOOLPEN_H
#define TOOLPEN_H

#include "AbstractTool.h"

class ToolPen : public AbstractTool
{
public:
    ToolPen(QGraphicsItem *drawingItem, int penSize, QColor color);
    ~ToolPen();

    bool sceneEventFilter(QGraphicsItem *obj, QEvent *event);
    void setSize(int size);
    void setColor(QColor color);

private:
    int m_PenSize;
    QColor m_Color;
    QPointF m_DrawStartPosition;
    QPointF m_DrawLastPosition;
    QGraphicsLineItem m_LineItem;

    void paintOnPixmap(const QPointF &oldPos, const QPointF &pos, QColor color);
    void paintOnPixmap(QPainter &painter, const QPointF &oldPos, const QPointF &pos);

    void pressMouse(QGraphicsSceneMouseEvent *mouseEvent);
    void moveMouse(QGraphicsSceneMouseEvent *mouseEvent);
    void releaseMouse(QGraphicsSceneMouseEvent *mouseEvent);
    void pressKey(QKeyEvent *keyEvent);
    void releaseKey(QKeyEvent *keyEvent);
};

#endif // TOOLPEN_H
