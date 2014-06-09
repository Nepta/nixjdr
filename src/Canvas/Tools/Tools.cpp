#include <QPushButton>

#include "Tools.h"
#include "Canvas/Tools/ToolPen.h"
#include "Canvas/Tools/ToolEraser.h"
#include "Canvas/Tools/ToolPing.h"

const QHash<QString, ToolCodes> Tools::s_ToolCodesMap = {
    {"m_PenButton", ToolCodes::TOOL_PEN},
    {"m_EraserButton", ToolCodes::TOOL_ERASER},
    {"m_PingButton", ToolCodes::TOOL_PING}
};

Tools::Tools(QObject *parent, int penSize, QColor color, int eraserSize,
             QGraphicsItem *drawingItem, QGraphicsScene *scene) :
    QObject(parent)
{
    m_ToolsMap.insert(ToolCodes::TOOL_PEN, new ToolPen(drawingItem, penSize, color));
    m_ToolsMap.insert(ToolCodes::TOOL_ERASER, new ToolEraser(eraserSize));
    m_ToolsMap.insert(ToolCodes::TOOL_PING, new ToolPing(scene, "resource/Map/Ping/ping.gif"));

    m_CurrentToolCode = ToolCodes::TOOL_PEN;
}

Tools::~Tools(){
    qDeleteAll(m_ToolsMap);
}

QList<AbstractTool*> Tools::getTools() {
    return m_ToolsMap.values();
}

AbstractTool *Tools::getTool(ToolCodes code){
    return m_ToolsMap.value(code);
}

void Tools::setCurrentToolCode(){
    if(qobject_cast<QPushButton*>(sender()) != NULL){
        m_CurrentToolCode = s_ToolCodesMap.value(sender()->objectName());
        emit changeTool();
    }
}

AbstractTool *Tools::getCurrentTool(){
    return getTool(m_CurrentToolCode);
}
