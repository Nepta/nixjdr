#include "Tools.h"
#include "Canvas/Tools/ToolPen.h"
#include "Canvas/Tools/ToolEraser.h"

const QHash<QString, ToolCodes> Tools::s_ToolCodes = {
    {"bla" , ToolCodes::TOOL_PEN},
    {"blabla", ToolCodes::TOOL_ERASER}
};


Tools::Tools(QObject *parent, int penSize, QColor color, int eraserSize) :
    QObject(parent)
{
    m_Tools.insert(ToolCodes::TOOL_PEN, new ToolPen(penSize, color));
    m_Tools.insert(ToolCodes::TOOL_ERASER, new ToolEraser(eraserSize));
}

Tools::~Tools(){
    qDeleteAll(m_Tools);
}

AbstractTool *Tools::getCurrentTool(ToolCodes code){
    return m_Tools.value(code);
}
