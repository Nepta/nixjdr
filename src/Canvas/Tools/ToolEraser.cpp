#include <QPainter>

#include "ToolEraser.h"

ToolEraser::ToolEraser(int eraserSize):
    m_EraserSize(eraserSize)
{
}

/**
 * @brief ToolEraser::eraseOnPixmap uses paintOnPixmap(QPainter, QPointF, QPointF) to draw with a
 * transparent pen
 * @param oldPos old cursor position
 * @param pos current cursor position
 */
void ToolEraser::eraseOnPixmap(const QPointF &oldPos, const QPointF &pos) {
    QPainter painter(AbstractTool::getPixmap());
    painter.setPen(QPen(Qt::transparent, m_EraserSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setCompositionMode(QPainter::CompositionMode_Clear);

    paintOnPixmap(painter, oldPos, pos);
}

void ToolEraser::setSize(int size){
    m_EraserSize = size;
}

/**
 * @brief ToolEraser::paintOnPixmap paints between two positions
 * @param painter Qpainter to paint with
 * @param oldPos position to begin painting at
 * @param pos position to end painting at
 */
void ToolEraser::paintOnPixmap(QPainter &painter, const QPointF &oldPos, const QPointF &pos) {
    if (oldPos == pos) {
        painter.drawPoint(pos);
    }
    else {
        painter.drawLine(oldPos, pos);
    }
}

/**
 * @brief ToolEraser::sceneEventFilter erases when the user clicks or clicks & moves the mouse
 * @param event
 * @return
 */
bool ToolEraser::sceneEventFilter(QGraphicsItem *, QEvent *event){
    bool eventFiltered = false;

    QGraphicsSceneMouseEvent *mouseEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);

    switch (event->type()) {
        case QEvent::GraphicsSceneMousePress: {
            eventFiltered = true;
        } break;

        case QEvent::GraphicsSceneMouseMove :{
            moveMouse(mouseEvent);
            eventFiltered = true;
        } break;

        default: break;
    }

    if (eventFiltered) {
        emit AbstractTool::updateDisplay();
        event->accept();
    }

    return eventFiltered;
}

/**
 * @brief ToolEraser::moveMouse erases the pixmap at the mouse's position
 * @param mouseEvent
 */
void ToolEraser::moveMouse(QGraphicsSceneMouseEvent *mouseEvent){
    if (mouseEvent->buttons() & Qt::LeftButton) {
        eraseOnPixmap(mouseEvent->lastScenePos(), mouseEvent->scenePos());
    }
}
