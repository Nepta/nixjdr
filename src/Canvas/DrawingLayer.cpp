#include <QGraphicsScene>
#include "DrawingLayer.h"

DrawingLayer::DrawingLayer() :
    m_DrawingZone(this),
    m_PenSize(2)
{}

DrawingLayer::~DrawingLayer() {
    delete m_Pixmap;
}

void DrawingLayer::initDrawingZone() {
    m_Pixmap = new QPixmap(scene()->sceneRect().size().toSize());
    m_Pixmap->fill(Qt::transparent);
    m_DrawingZone.setPixmap(*m_Pixmap);
}

void DrawingLayer::drawBackground(QPainter *, const QRectF &) {}

void DrawingLayer::mousePressEvent(QGraphicsSceneMouseEvent *) {}

void DrawingLayer::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    paintOnPixmap(mouseEvent->lastScenePos(), mouseEvent->scenePos());
    m_DrawingZone.setPixmap(*m_Pixmap); // update the drawing zone
}

void DrawingLayer::paintOnPixmap(const QPointF &oldPos, const QPointF &pos) {
    QPainter painter(m_Pixmap);
    painter.setPen(QPen(Qt::black, m_PenSize));

    if (oldPos == pos) {
        painter.drawPoint(pos);
    }
    else {
        painter.drawLine(oldPos, pos);
    }
}
