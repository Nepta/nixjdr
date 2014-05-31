#include <QGraphicsScene>
#include <QDebug>
#include "DrawingLayer.h"
#include "Canvas/Tools/AbstractTool.h"

DrawingLayer::DrawingLayer(int penSize, int eraserSize, QColor color) :
    m_Tools(this, penSize, color, eraserSize, this)
{}

DrawingLayer::~DrawingLayer() {
    delete m_Pixmap;
    delete m_DrawingZone;
}

void DrawingLayer::setPenSize(int size) {
    m_Tools.getTool(ToolCodes::TOOL_PEN)->setSize(size);
}

void DrawingLayer::setEraserSize(int size) {
    m_Tools.getTool(ToolCodes::TOOL_ERASER)->setSize(size);
}

void DrawingLayer::initDrawingZone() {
    m_Pixmap = new QPixmap(scene()->sceneRect().size().toSize());
    m_Pixmap->fill(Qt::transparent);
    m_DrawingZone = new QGraphicsPixmapItem(this);
    m_DrawingZone->setPixmap(*m_Pixmap);

    AbstractTool::setPixmap(m_Pixmap);
    AbstractTool::setDrawingZone(m_DrawingZone);

    this->scene()->addItem(m_Tools.getTool(ToolCodes::TOOL_PEN));
    this->installSceneEventFilter(m_Tools.getTool(ToolCodes::TOOL_PEN));
}

void DrawingLayer::drawBackground(QPainter *, const QRectF &) {}

void DrawingLayer::erasePixmapContent() {
    m_Pixmap->fill(Qt::transparent);
    m_DrawingZone->setPixmap(*m_Pixmap);
}
