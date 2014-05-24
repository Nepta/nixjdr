#include <QGraphicsScene>
#include "DrawingLayer.h"

DrawingLayer::DrawingLayer(int penSize, int eraserSize) :
    m_DrawingZone(this),
    m_PenSize(penSize),
    m_EraserSize(eraserSize)
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

void DrawingLayer::mousePressEvent(QGraphicsSceneMouseEvent *) {}

void DrawingLayer::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->buttons() & Qt::LeftButton) {
        paintOnPixmap(mouseEvent->lastScenePos(), mouseEvent->scenePos(), Qt::black);
    }
    else if (mouseEvent->buttons() & Qt::RightButton) {
        eraseOnPixmap(mouseEvent->lastScenePos(), mouseEvent->scenePos());
    }

    m_DrawingZone.setPixmap(*m_Pixmap); // update the drawing zone
}

void DrawingLayer::paintOnPixmap(const QPointF &oldPos, const QPointF &pos, Qt::GlobalColor color) {
    QPainter painter(m_Pixmap);
    painter.setPen(QPen(color, m_PenSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    paintOnPixmap(painter, oldPos, pos);
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
