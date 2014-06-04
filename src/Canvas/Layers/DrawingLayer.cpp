#include <QGraphicsScene>
#include <QBuffer>
#include <QDebug>

#include "DrawingLayer.h"
#include "Canvas/Tools/AbstractTool.h"

DrawingLayer::DrawingLayer(int penSize, int eraserSize, QColor color):
    m_PenSize(penSize),
    m_EraserSize(eraserSize),
    m_Color(color)
{}

DrawingLayer::~DrawingLayer() {
    AbstractTool::setPixmap(NULL);
    delete m_Pixmap;
    AbstractTool::setDrawingZone(NULL);
    delete m_DrawingZone;
    delete m_Tools;
}

void DrawingLayer::drawBackground(QPainter *, const QRectF &) {}

QByteArray DrawingLayer::getPixmapData() {
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    m_Pixmap->save(&buffer, "PNG");

    return data;
}

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

    this->installSceneEventFilter(this);
    m_OldTool = m_Tools->getCurrentTool();
    this->installSceneEventFilter(m_Tools->getCurrentTool());

    connect(m_Tools, SIGNAL(changeTool()), this, SLOT(changeTool()));
}

void DrawingLayer::changeTool(){
    this->removeSceneEventFilter(m_OldTool);
    m_OldTool = m_Tools->getCurrentTool();
    this->installSceneEventFilter(m_Tools->getCurrentTool());
}


void DrawingLayer::erasePixmapContent() {
    m_Pixmap->fill(Qt::transparent);
    m_DrawingZone->setPixmap(*m_Pixmap);
}


bool DrawingLayer::sceneEventFilter(QGraphicsItem *watched, QEvent *event){
    AbstractTool::setDrawingZone(m_DrawingZone);
    AbstractTool::setPixmap(m_Pixmap);
    return AbstractLayer::sceneEventFilter(watched, event);
}
