#include <QPainter>

#include "ToolEraser.h"

ToolEraser::ToolEraser(int eraserSize):
    m_EraserSize(eraserSize)
{
}

void ToolEraser::eraseOnPixmap(const QPointF &oldPos, const QPointF &pos) {
    QPainter painter(AbstractTool::getPixmap());
    painter.setPen(QPen(Qt::transparent, m_EraserSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setCompositionMode(QPainter::CompositionMode_Clear);

    paintOnPixmap(painter, oldPos, pos);
}


void ToolEraser::paintOnPixmap(const QPointF &oldPos, const QPointF &pos, QColor color) {
    QPainter painter(AbstractTool::getPixmap());
    painter.setPen(QPen(color, m_EraserSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    paintOnPixmap(painter, oldPos, pos);
}

void ToolEraser::paintOnPixmap(QPainter &painter, const QPointF &oldPos, const QPointF &pos) {
    if (oldPos == pos) {
        painter.drawPoint(pos);
    }
    else {
        painter.drawLine(oldPos, pos);
    }
}


bool ToolEraser::sceneEventFilter(QGraphicsItem *, QEvent *event){
    switch (event->type()) {
    case QEvent::MouseMove:
        moveMouse(static_cast<QGraphicsSceneMouseEvent*>(event));
        break;
    default:
        break;
    }
    return true;
}


void ToolEraser::moveMouse(QGraphicsSceneMouseEvent *mouseEvent){
    if (mouseEvent->buttons() & Qt::RightButton) {
        eraseOnPixmap(mouseEvent->lastScenePos(), mouseEvent->scenePos());
    }
}
