#include <QPainter>
#include <QKeyEvent>

#include "ToolPen.h"

ToolPen::ToolPen(QGraphicsItem *drawingItem, int penSize, QColor color):
    m_PenSize(penSize),
    m_Color(color),
    m_LineItem(drawingItem)
{}

ToolPen::~ToolPen() {}

void ToolPen::setSize(int size){
    m_PenSize = size;
}

/**
 * @brief ToolPen::paintOnPixmap creates a QPainter with the specified QColor, and calls to
 * paintOnPixmap(QPainter, QPointF, QPointf) to draw on the QPixmap
 * @param oldPos position to start drawin from
 * @param pos position to end drawing at
 * @param color color to draw with
 */
void ToolPen::paintOnPixmap(const QPointF &oldPos, const QPointF &pos, QColor color) {
    QPainter painter(AbstractTool::getPixmap());
    painter.setPen(QPen(color, m_PenSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    paintOnPixmap(painter, oldPos, pos);
}

/**
 * @brief ToolPen::paintOnPixmap paints from one point to another
 * @param painter painter to paint with
 * @param oldPos point to start drawing from
 * @param pos point to end drawing at
 */
void ToolPen::paintOnPixmap(QPainter &painter, const QPointF &oldPos, const QPointF &pos) {
    if (oldPos == pos) {
        painter.drawPoint(pos);
    }
    else {
        painter.drawLine(oldPos, pos);
    }
}

/**
 * @brief ToolPen::sceneEventFilter draws when the mouse is pressed; may draw a line if shift is
 * pressed in the process.
 * @param event event to handle
 * @return
 */
bool ToolPen::sceneEventFilter(QGraphicsItem *, QEvent *event){
    bool eventFiltered = false;

    QGraphicsSceneMouseEvent *mouseEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
    QKeyEvent *keyEvent = dynamic_cast<QKeyEvent*>(event);

    switch (event->type()) {
        case QEvent::GraphicsSceneMousePress:{
            pressMouse(mouseEvent);
            eventFiltered = true;
        } break;

        case QEvent::GraphicsSceneMouseMove	:{
            moveMouse(mouseEvent);
            eventFiltered = true;
        } break;

        case QEvent::GraphicsSceneMouseRelease: {
            releaseMouse(mouseEvent);
            eventFiltered = true;
        } break;

        case QEvent::KeyPress: {
            pressKey(keyEvent);
            eventFiltered = true;
        } break;

        case QEvent::KeyRelease: {
            releaseKey(keyEvent);
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
 * @brief ToolPen::pressMouse paints at the cursor's position, and resets the m_LineItem
 * @param mouseEvent
 */
void ToolPen::pressMouse(QGraphicsSceneMouseEvent *mouseEvent){
    if(mouseEvent->button() == Qt::LeftButton){
        m_DrawStartPosition = mouseEvent->pos();
        m_DrawLastPosition = mouseEvent->pos();

        m_LineItem.setLine(QLineF(m_DrawStartPosition, m_DrawStartPosition));
        paintOnPixmap(m_DrawStartPosition, m_DrawStartPosition, m_Color);
    }
}

/**
 * @brief ToolPen::moveMouse if shift is not being pressed, draws at the cursor's position, else
 * previews a line ending at the cursor's position
 * @param mouseEvent
 */
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

/**
 * @brief ToolPen::releaseMouse hides and draws the preview line if it was being used
 * @param mouseEvent
 */
void ToolPen::releaseMouse(QGraphicsSceneMouseEvent *mouseEvent){
    m_LineItem.hide();
    if(mouseEvent->button() == Qt::LeftButton && mouseEvent->modifiers() == Qt::ShiftModifier){
        paintOnPixmap(m_DrawStartPosition, mouseEvent->pos(), m_Color);
    }
}

/**
 * @brief ToolPen::pressKey if shift is pressed, sets the preview line's beginning position at the
 * current cursor's position; if it is maintained pressed, updates the preview line
 * @param keyEvent
 */
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
    else {
        keyEvent->ignore();
    }
}

/**
 * @brief ToolPen::releaseKey draws the preview line if shift is released
 * @param keyEvent
 */
void ToolPen::releaseKey(QKeyEvent *keyEvent){
    if (keyEvent->key() == Qt::Key_Shift && m_LineItem.isVisible()) {
        m_LineItem.hide();
        paintOnPixmap(m_LineItem.line().p1(), m_LineItem.line().p2(), m_Color);

        m_LineItem.setEnabled(false);
        keyEvent->accept();
    }
    else {
        keyEvent->ignore();
    }
}
