#include "CanvasView.h"

CanvasView::CanvasView() {
    setAcceptDrops(true);
}

CanvasView::CanvasView(CanvasScene* scene) :
    CanvasView()
{
    setScene(scene);
}

CanvasView::~CanvasView() {}
