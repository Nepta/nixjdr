#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include "CanvasScene.h"
#include <QGraphicsView>
#include <QMouseEvent>

class CanvasView : public QGraphicsView{

public:
    CanvasView();
    CanvasView(CanvasScene* scene);
    ~CanvasView();
    CanvasView* getCanvasView();
    CanvasScene* getCanvasScene();

private:
    void setCanvasScene(CanvasScene* scene);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * event);

private:
    CanvasScene* m_scene;
};

#endif // CANVASVIEW_H
