#include <QPainter>
#include <QKeyEvent>

#include "ToolPen.h"

ToolPen::ToolPen(QGraphicsItem *drawingItem, int penSize, QColor color):
    m_PenSize(penSize),
    m_Color(color),
    m_LineItem(drawingItem)
{}

ToolPen::~ToolPen()
{}

void ToolPen::setSize(int size){
    m_PenSize = size;
}

void ToolPen::paintOnPixmap(const QPointF &oldPos, const QPointF &pos, QColor color) {
    QPainter painter(AbstractTool::getPixmap());
    painter.setPen(QPen(color, m_PenSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    paintOnPixmap(painter, oldPos, pos);
}

void ToolPen::paintOnPixmap(QPainter &painter, const QPointF &oldPos, const QPointF &pos) {
    if (oldPos == pos) {
        painter.drawPoint(pos);
    }
    else {
        painter.drawLine(oldPos, pos);
    }
}


bool ToolPen::sceneEventFilter(QGraphicsItem *, QEvent *event){
    switch (event->type()) {
    case QEvent::GraphicsSceneMousePress:{
        pressMouse(static_cast<QGraphicsSceneMouseEvent*>(event));
    }
        break;
    case QEvent::GraphicsSceneMouseMove	:{
        moveMouse(static_cast<QGraphicsSceneMouseEvent*>(event));
    }
        break;
    case QEvent::GraphicsSceneMouseRelease: {
        releaseMouse(static_cast<QGraphicsSceneMouseEvent*>(event));
    }
        break;
    case QEvent::KeyPress: {
        pressKey((QKeyEvent*)(event));
    }
        break;
    case QEvent::KeyRelease: {
        releaseKey((QKeyEvent*)(event));
    }
        break;
    default:
        break;
    }
    AbstractTool::updateDisplay();
    return true;
}

void ToolPen::pressMouse(QGraphicsSceneMouseEvent *mouseEvent){
    if(mouseEvent->button() == Qt::LeftButton){
        m_DrawStartPosition = mouseEvent->pos();
        m_DrawLastPosition = mouseEvent->pos();
        m_LineItem.setLine(QLineF(m_DrawStartPosition, m_DrawStartPosition));
        paintOnPixmap(m_DrawStartPosition, m_DrawStartPosition, m_Color);
    }
}

void ToolPen::moveMouse(QGraphicsSceneMouseEvent *mouseEvent){
    if(mouseEvent->modifiers() != Qt::ShiftModifier){
        paintOnPixmap(mouseEvent->lastScenePos(), mouseEvent->scenePos(), m_Color);
        m_DrawStartPosition = mouseEvent->pos();
    }
    else if(mouseEvent->modifiers() == Qt::ShiftModifier){
        m_LineItem.setLine(QLineF(m_DrawStartPosition, mouseEvent->pos()));
        m_LineItem.show();
    }
    m_DrawLastPosition = mouseEvent->pos();
}

void ToolPen::releaseMouse(QGraphicsSceneMouseEvent *mouseEvent){
    m_LineItem.hide();
    if(mouseEvent->button() == Qt::LeftButton && mouseEvent->modifiers() == Qt::ShiftModifier){
        paintOnPixmap(m_DrawStartPosition, mouseEvent->pos(), m_Color);
    }
}

void ToolPen::pressKey(QKeyEvent *keyEvent){
    if(keyEvent->key() == Qt::Key_Shift){
        m_DrawStartPosition = m_DrawLastPosition;
        keyEvent->accept();
    }
    else if(keyEvent->modifiers() & Qt::ShiftModifier ){
        m_LineItem.hide();
        paintOnPixmap(m_LineItem.line().p1(), m_LineItem.line().p2(), m_Color);
        m_DrawStartPosition = m_DrawLastPosition;
        keyEvent->accept();
        }
    else{
        keyEvent->ignore();
    }
}

void ToolPen::releaseKey(QKeyEvent *keyEvent){
    if(keyEvent->key() == Qt::Key_Shift){
        m_LineItem.hide();
        paintOnPixmap(m_LineItem.line().p1(), m_LineItem.line().p2(), m_Color);
        keyEvent->accept();
    }
    else{
        keyEvent->ignore();
    }
}
