#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QMouseEvent>
#include <QDrag>
#include <QDropEvent>
#include <QMimeData>
#include <QImage>
#include <QPoint>

#include "CanvasScene.h"

#define START_DRAG_DISTANCE 4

class CanvasView : public QGraphicsView{

public:
    CanvasView();
    CanvasView(CanvasScene* scene);
    ~CanvasView();
    CanvasView* getCanvasView();
    CanvasScene* getCanvasScene();

private:
    void setCanvasScene(CanvasScene* scene);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * event);

private:
    CanvasScene* m_scene;
    QPoint m_dragStartPosition;
    int m_xClick;
    int m_yClick;
};

#endif // CANVASVIEW_H
