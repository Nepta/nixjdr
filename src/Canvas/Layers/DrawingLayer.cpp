#include <QGraphicsScene>
#include <QBuffer>

#include "Database/Repository/RepositoryManager.h"
#include "Canvas/Tools/AbstractTool.h"
#include "Canvas/Tools/ToolPing.h"
#include "Canvas/Network/MapCodes.h"
#include "DrawingLayer.h"

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

    ToolPing *toolPing = dynamic_cast<ToolPing*>(m_Tools->getTool(ToolCodes::TOOL_PING));
    connect(toolPing, SIGNAL(sendPing(QPointF)), this, SLOT(sendPing(QPointF)));

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
    updateDisplay();
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

/**
 * @brief DrawingLayer::updateDisplayRemote Sends the modification made to the drawing zone to the
 * database and the remote clients.
 */
void DrawingLayer::updateDisplayRemote() {
    // Update this layer's pixmap in the database
    RepositoryManager::s_DrawingLayerRepository.updateDrawingLayer(this);

    // Notifies all the clients to update their pixmap for this layer
    QString msg = QString("%1").arg(this->id());
    m_SenderClient->sendMessageToServer(msg, (quint16) MapCodes::UPDATE_DRAWING_LAYER_PIXMAP);
}

void DrawingLayer::setPixmap(QPixmap *pixmap) {
    delete m_Pixmap;
    m_Pixmap = pixmap;
}

/**
 * @brief DrawingLayer::sendPing Sends a ping to all the clients.
 * @param pos
 */
void DrawingLayer::sendPing(QPointF pos) {
    QString msg = QString("%1 %2 %3").arg(this->id()).arg(pos.x()).arg(pos.y());
    m_SenderClient->sendMessageToServer(msg, (quint16) MapCodes::PING);
}
