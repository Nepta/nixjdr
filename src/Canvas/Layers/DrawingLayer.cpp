#include <QGraphicsScene>

#include "DrawingLayer.h"

DrawingLayer::DrawingLayer(int penSize, int eraserSize, QColor color) :
    m_DrawingZone(this),
    m_PenSize(penSize),
    m_EraserSize(eraserSize),
    m_Color(color),
    m_LineItem(this)
{}

DrawingLayer::~DrawingLayer() {
    delete m_Pixmap;
}

void DrawingLayer::setPenSize(int size) {
    m_PenSize = size;
}

void DrawingLayer::setEraserSize(int size) {
    m_EraserSize = size;
}

void DrawingLayer::initDrawingZone() {
    m_Pixmap = new QPixmap(scene()->sceneRect().size().toSize());
    m_Pixmap->fill(Qt::transparent);
    m_DrawingZone.setPixmap(*m_Pixmap);
}

void DrawingLayer::drawBackground(QPainter *, const QRectF &) {}

void DrawingLayer::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(mouseEvent->button() == Qt::LeftButton){
        m_DrawStartPosition = mouseEvent->pos();
        m_DrawLastPosition = mouseEvent->pos();
        m_LineItem.setLine(QLineF(m_DrawStartPosition, m_DrawStartPosition));
        paintOnPixmap(m_DrawStartPosition, m_DrawStartPosition, m_Color);
        mouseEvent->accept();
    }
    else if(mouseEvent->button() == Qt::RightButton){
        eraseOnPixmap(mouseEvent->lastScenePos(), mouseEvent->scenePos());
        m_DrawingZone.setPixmap(*m_Pixmap); // update the drawing zone
        mouseEvent->accept();
    }
    else{
        mouseEvent->ignore();
    }
}

void DrawingLayer::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->buttons() & Qt::LeftButton) {
        if(mouseEvent->modifiers() != Qt::ShiftModifier){
            this->setCursor(Qt::BlankCursor);
            paintOnPixmap(mouseEvent->lastScenePos(), mouseEvent->scenePos(), m_Color);
            m_DrawStartPosition = mouseEvent->pos();
        }
        else if(mouseEvent->modifiers() == Qt::ShiftModifier){
            this->setCursor(Qt::CrossCursor);
            m_LineItem.setLine(QLineF(m_DrawStartPosition, mouseEvent->pos()));
            m_LineItem.show();
        }
        m_DrawLastPosition = mouseEvent->pos();
        mouseEvent->accept();
    }
    else if (mouseEvent->buttons() & Qt::RightButton) {
        eraseOnPixmap(mouseEvent->lastScenePos(), mouseEvent->scenePos());
        mouseEvent->accept();
    }
    else {
        mouseEvent->ignore();
    }

    m_DrawingZone.setPixmap(*m_Pixmap); // update the drawing zone
}

void DrawingLayer::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent){
    m_LineItem.hide();
    if(mouseEvent->button() == Qt::LeftButton && mouseEvent->modifiers() == Qt::ShiftModifier){
        paintOnPixmap(m_DrawStartPosition, mouseEvent->pos(), m_Color);
    }

    this->setCursor(Qt::ArrowCursor);
}

void DrawingLayer::keyPressEvent(QKeyEvent *keyEvent){
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

void DrawingLayer::keyReleaseEvent(QKeyEvent *keyEvent){
    if(keyEvent->key() == Qt::Key_Shift){
        m_LineItem.hide();
        paintOnPixmap(m_LineItem.line().p1(), m_LineItem.line().p2(), m_Color);
        keyEvent->accept();
    }
    else{
        keyEvent->ignore();
    }
}

void DrawingLayer::paintOnPixmap(const QPointF &oldPos, const QPointF &pos, QColor color) {
    QPainter painter(m_Pixmap);
    painter.setPen(QPen(color, m_PenSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    paintOnPixmap(painter, oldPos, pos);
    m_DrawingZone.setPixmap(*m_Pixmap);
}

void DrawingLayer::paintOnPixmap(QPainter &painter, const QPointF &oldPos, const QPointF &pos) {
    if (oldPos == pos) {
        painter.drawPoint(pos);
    }
    else {
        painter.drawLine(oldPos, pos);
    }
}

void DrawingLayer::eraseOnPixmap(const QPointF &oldPos, const QPointF &pos) {
    QPainter painter(m_Pixmap);
    painter.setPen(QPen(Qt::transparent, m_EraserSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setCompositionMode(QPainter::CompositionMode_Clear);

    paintOnPixmap(painter, oldPos, pos);
}

void DrawingLayer::erasePixmapContent() {
    m_Pixmap->fill(Qt::transparent);
    m_DrawingZone.setPixmap(*m_Pixmap);
}
