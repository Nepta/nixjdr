#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>
#include <QHash>

#include "Canvas/Tools/AbstractTool.h"

enum class ToolCodes : quint16 {
    TOOL_PEN,
    TOOL_ERASER,
    TOOL_PING
};

inline uint qHash(const ToolCodes &key) { return qHash((quint16) key); }

class Tools : public QObject
{
    Q_OBJECT

public:
    const static QHash<QString, ToolCodes> s_ToolCodesMap;

    explicit Tools(QObject *parent = 0, int penSize = 0, QColor color = Qt::black,
                   int eraserSize = 0, QGraphicsItem *drawingItem =0, QGraphicsScene *scene =0);
    ~Tools();

    AbstractTool *getTool(ToolCodes code);
    AbstractTool *getCurrentTool();

signals:
    void changeTool();

private:
    QHash<ToolCodes, AbstractTool *> m_ToolsMap;
    ToolCodes m_CurrentToolCode;

public slots:
    void setCurrentToolCode();

};

#endif // TOOLS_H
