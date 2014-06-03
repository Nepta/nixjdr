#ifndef TOOLPING_H
#define TOOLPING_H

#include <QLabel>
#include <QMovie>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

#include "AbstractTool.h"

class ToolPing : public AbstractTool
{
public:
    ToolPing(QGraphicsScene *scene, QString gifPath);
    ~ToolPing();

    void setSize(int);
    bool sceneEventFilter(QGraphicsItem *, QEvent *event);

    void ping(QPointF);

private:
    QGraphicsScene *m_Scene;
    QString m_GifPath;
    bool m_Pinging;
    QGraphicsProxyWidget *m_Proxy;

    QLabel *m_Gif;
    QMovie *m_Movie;

    void pressMouse(QGraphicsSceneMouseEvent *mouseEvent);
    void timerEvent(QTimerEvent *timerEvent);

};

#endif // TOOLPING_H
