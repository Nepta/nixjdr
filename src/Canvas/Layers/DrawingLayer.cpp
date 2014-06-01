#include <QGraphicsScene>
#include "DrawingLayer.h"
#include "Canvas/Tools/AbstractTool.h"

DrawingLayer::DrawingLayer(int penSize, int eraserSize, QColor color){
    m_Tools = new Tools(this, penSize, color, eraserSize, this, this->scene());
}

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
    m_Tools->getTool(ToolCodes::TOOL_PEN)->setSize(size);
}

void DrawingLayer::setEraserSize(int size) {
    m_Tools->getTool(ToolCodes::TOOL_ERASER)->setSize(size);
}

void DrawingLayer::initDrawingZone() {
    m_Pixmap = new QPixmap(scene()->sceneRect().size().toSize());
    m_Pixmap->fill(Qt::transparent);
    m_DrawingZone = new QGraphicsPixmapItem(this);
    m_DrawingZone->setPixmap(*m_Pixmap);

    AbstractTool::setPixmap(m_Pixmap);
    AbstractTool::setDrawingZone(m_DrawingZone);

    foreach (ToolCodes code, m_Tools->s_ToolCodes.values()) {
        this->scene()->addItem(m_Tools->getTool(code));
    }
    this->installSceneEventFilter(m_Tools->getCurrentTool());

    connect(m_Tools, SIGNAL(changeTool()), this, SLOT(changeTool()));
}

void DrawingLayer::changeTool(){
    this->installSceneEventFilter(m_Tools->getCurrentTool());
}


void DrawingLayer::erasePixmapContent() {
    m_Pixmap->fill(Qt::transparent);
    m_DrawingZone->setPixmap(*m_Pixmap);
}
