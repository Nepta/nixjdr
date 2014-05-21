#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include <QGraphicsView>
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
