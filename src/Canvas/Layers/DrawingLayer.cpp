#include <QGraphicsScene>
#include "DrawingLayer.h"
#include "Canvas/Tools/AbstractTool.h"

DrawingLayer::DrawingLayer(int penSize, int eraserSize, QColor color):
    m_PenSize(penSize),
    m_EraserSize(eraserSize),
    m_Color(color)
{}

DrawingLayer::~DrawingLayer() {
    delete m_Pixmap;
    delete m_DrawingZone;
    delete m_Tools;
}

void DrawingLayer::drawBackground(QPainter *, const QRectF &) {}

Tools *DrawingLayer::getTools(){
    return m_Tools;
}

void DrawingLayer::setPenSize(int size) {
    m_PenSize = size;
    m_Tools->getTool(ToolCodes::TOOL_PEN)->setSize(size);
}

void DrawingLayer::setEraserSize(int size) {
    m_EraserSize = size;
    m_Tools->getTool(ToolCodes::TOOL_ERASER)->setSize(size);
}

void DrawingLayer::initDrawingZone() {
    m_Pixmap = new QPixmap(scene()->sceneRect().size().toSize());
    m_Pixmap->fill(Qt::transparent);
    m_DrawingZone = new QGraphicsPixmapItem(this);
    m_DrawingZone->setPixmap(*m_Pixmap);

    m_Tools = new Tools(this, m_PenSize, m_Color, m_EraserSize, this, this->scene());

    AbstractTool::setPixmap(m_Pixmap);
    AbstractTool::setDrawingZone(m_DrawingZone);

    foreach (ToolCodes code, m_Tools->s_ToolCodesMap.values()) {
        this->scene()->addItem(m_Tools->getTool(code));
    }
    this->installSceneEventFilter(m_Tools->getCurrentTool());
    m_OldTool = m_Tools->getCurrentTool();

    connect(m_Tools, SIGNAL(changeTool()), this, SLOT(changeTool()));
}

void DrawingLayer::changeTool(){
    this->removeEventFilter(m_OldTool);
    this->installSceneEventFilter(m_Tools->getCurrentTool());
}


void DrawingLayer::erasePixmapContent() {
    m_Pixmap->fill(Qt::transparent);
    m_DrawingZone->setPixmap(*m_Pixmap);
}
