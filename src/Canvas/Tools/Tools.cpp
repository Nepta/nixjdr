#include "Tools.h"
#include "Canvas/Tools/ToolPen.h"
#include "Canvas/Tools/ToolEraser.h"
#include "Canvas/Tools/ToolPing.h"

const QHash<QString, ToolCodes> Tools::s_ToolCodes = {
    {"m_PenButton", ToolCodes::TOOL_PEN},
    {"m_EraserButton", ToolCodes::TOOL_ERASER},
    {"m_PingButton", ToolCodes::TOOL_PING}
};

Tools::Tools(QObject *parent, int penSize, QColor color, int eraserSize,
             QGraphicsItem *drawingItem, QGraphicsScene *scene) :
    QObject(parent)
{
    m_Tools.insert(ToolCodes::TOOL_PEN, new ToolPen(drawingItem, penSize, color));
    m_Tools.insert(ToolCodes::TOOL_ERASER, new ToolEraser(eraserSize));
    m_Tools.insert(ToolCodes::TOOL_PING, new ToolPing(scene, "resource/gifs/ping"));

    m_CurrentToolCode = ToolCodes::TOOL_PEN;
}

Tools::~Tools(){
    qDeleteAll(m_Tools);
}

AbstractTool *Tools::getTool(ToolCodes code){
    return m_Tools.value(code);
}

void Tools::setCurrentToolCode(){
    if(qobject_cast<QPushButton*>(sender()) != NULL){
        m_CurrentToolCode = s_ToolCodes.value(sender()->objectName());
        emit changeTool();
    }
}

AbstractTool *Tools::getCurrentTool(){
    return getTool(m_CurrentToolCode);
}
