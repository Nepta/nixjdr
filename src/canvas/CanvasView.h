#ifndef CANVASVIEW_H
#define CANVASVIEW_H

// TODO faire le tri dans les includes
#include <QGraphicsView>
#include <QMouseEvent>
#include <QMouseEvent>
#include <QDrag>
#include <QDropEvent>
#include <QMimeData>
#include <QImage>
#include <QPoint>

#include "CanvasScene.h"

class CanvasView : public QGraphicsView {

public:
    CanvasView();
    CanvasView(CanvasScene* scene);
    ~CanvasView();

private:
    CanvasScene* m_scene;
};

#endif // CANVASVIEW_H
