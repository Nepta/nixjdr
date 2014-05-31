#ifndef TOOLERASER_H
#define TOOLERASER_H

#include "AbstractTool.h"

class ToolEraser : public AbstractTool
{
public:
    ToolEraser(int eraserSize);


public:
    bool sceneEventFilter(QGraphicsItem *, QEvent *event);

private:
    int m_EraserSize;

    void paintOnPixmap(const QPointF &oldPos, const QPointF &pos, QColor color);
    void paintOnPixmap(QPainter &painter, const QPointF &oldPos, const QPointF &pos);

    void pressMouse(QGraphicsSceneMouseEvent *mouseEvent);
    void moveMouse(QGraphicsSceneMouseEvent *mouseEvent);
    void eraseOnPixmap(const QPointF &oldPos, const QPointF &pos);
};

#endif // TOOLERASER_H
