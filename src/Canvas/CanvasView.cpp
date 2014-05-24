#include "CanvasView.h"

CanvasView::CanvasView(QWidget *parent) :
    QGraphicsView(parent)
{
    setAcceptDrops(true);
}

CanvasView::~CanvasView() {}
