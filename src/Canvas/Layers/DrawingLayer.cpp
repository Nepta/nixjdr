#include <QGraphicsScene>
#include <QBuffer>

#include "DrawingLayer.h"
#include "Canvas/Tools/AbstractTool.h"

DrawingLayer::DrawingLayer(int penSize, int eraserSize, QColor color):
    m_PenSize(penSize),
    m_EraserSize(eraserSize),
    m_Color(color)
{}

DrawingLayer::DrawingLayer(DBItem item) {
    QHash<QString, QVariant> itemHashMap = item.getHashMap();
    columnsValues_ = item.getHashMap();

    int id = itemHashMap.value("id").toInt();
    QByteArray pixmap = itemHashMap.value("pixmap").toByteArray();

    id_ = id;
    m_Pixmap = new QPixmap;
    m_Pixmap->loadFromData(pixmap, "PNG");

    m_PenSize = 2;
    m_EraserSize = 2;
    m_Color = Qt::black;
}

DrawingLayer::~DrawingLayer() {
    AbstractTool::setPixmap(NULL);
    delete m_Pixmap;

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

void DrawingLayer::initDrawingZone(bool newPixmap) {
    if (newPixmap) {
        m_Pixmap = new QPixmap(scene()->sceneRect().size().toSize());
        m_Pixmap->fill(Qt::transparent);
    }

    m_DrawingZone = new QGraphicsPixmapItem(this);
    m_DrawingZone->setPixmap(*m_Pixmap);

    m_Tools = new Tools(this, m_PenSize, m_Color, m_EraserSize, this, this->scene());

    AbstractTool::setPixmap(m_Pixmap);

    foreach (AbstractTool *tool, m_Tools->getTools()) {
        this->scene()->addItem(tool);
        connect(tool, SIGNAL(updateDisplay()), this, SLOT(updateDisplay()));
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
    AbstractTool::setPixmap(m_Pixmap);
    return AbstractLayer::sceneEventFilter(watched, event);
}

/**
 * @brief AbstractTool::updateDisplay Updates the drawing zone.
 */
void DrawingLayer::updateDisplay() {
    m_DrawingZone->setPixmap(*m_Pixmap);
}
