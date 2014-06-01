#ifndef TOOLPING_H
#define TOOLPING_H

#include <QLabel>
#include <QMovie>
#include <QGraphicsScene>

#include "AbstractTool.h"

class ToolPing : public AbstractTool
{
public:
    ToolPing(QGraphicsScene *scene, QString gifPath);
    ~ToolPing();

    void setSize(int size);
    bool sceneEventFilter(QGraphicsItem *, QEvent *event);

    void ping(QPointF);

private:
    QGraphicsScene *m_Scene;
    QLabel *m_Gif;
    QString m_GifPath;
    QMovie *m_Movie;

    void pressMouse(QGraphicsSceneMouseEvent *mouseEvent);

};

#endif // TOOLPING_H
