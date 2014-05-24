#include <QGraphicsScene>
#include "DrawingLayer.h"

DrawingLayer::DrawingLayer(int penSize, int eraserSize) :
    m_DrawingZone(this),
    m_PenSize(penSize),
    m_EraserSize(eraserSize, eraserSize)
{}

DrawingLayer::~DrawingLayer() {
    delete m_Pixmap;
}

void DrawingLayer::setPenSize(int size) {
    m_PenSize = size;
}

void DrawingLayer::setEraserSize(int size) {
    m_EraserSize = QSize(size, size);
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
        paintOnPixmap(mouseEvent->lastScenePos(), mouseEvent->scenePos());
    }
    else if (mouseEvent->buttons() & Qt::RightButton) {
        eraseOnPixmap(mouseEvent->scenePos());

    }


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

void DrawingLayer::eraseOnPixmap(const QPointF pos) {
    QPainter painter(m_Pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_Clear);

    painter.fillRect(QRect(pos.toPoint(), m_EraserSize), Qt::transparent);
}

void DrawingLayer::erasePixmapContent() {
    m_Pixmap->fill(Qt::transparent);
    m_DrawingZone.setPixmap(*m_Pixmap);
}
