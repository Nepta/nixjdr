#include <QGraphicsScene>
#include <QDebug>
#include "DrawingLayer.h"
#include "Canvas/Tools/AbstractTool.h"

DrawingLayer::DrawingLayer(int penSize, int eraserSize, QColor color) :
    m_PenSize(penSize),
    m_EraserSize(eraserSize),
    m_Color(color),
    m_LineItem(this),
    m_Tools(this, penSize, color, eraserSize)
{}

DrawingLayer::~DrawingLayer() {
    delete m_Pixmap;
    delete m_DrawingZone;
}

void DrawingLayer::setPenSize(int size) {
    m_PenSize = size;
    m_DrawingZone->setPixmap(*m_Pixmap);
}

void DrawingLayer::setEraserSize(int size) {
    m_EraserSize = size;
}

void DrawingLayer::initDrawingZone() {
    m_Pixmap = new QPixmap(scene()->sceneRect().size().toSize());
    m_Pixmap->fill(Qt::transparent);
    m_DrawingZone = new QGraphicsPixmapItem(this);
    m_DrawingZone->setPixmap(*m_Pixmap);

    AbstractTool::setPixmap(m_Pixmap);
    AbstractTool::setDrawingZone(m_DrawingZone);

    this->scene()->addItem(m_Tools.getCurrentTool(ToolCodes::TOOL_PEN));
    this->installSceneEventFilter(m_Tools.getCurrentTool(ToolCodes::TOOL_PEN));
}

void DrawingLayer::drawBackground(QPainter *, const QRectF &) {}

void DrawingLayer::erasePixmapContent() {
    m_Pixmap->fill(Qt::transparent);
    m_DrawingZone->setPixmap(*m_Pixmap);
}
