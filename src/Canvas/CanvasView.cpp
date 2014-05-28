#include "CanvasView.h"

CanvasView::CanvasView(QWidget *parent) :
    QGraphicsView(parent)
{
    m_ScaleFactor = 1.0;
    setAcceptDrops(true);
}

CanvasView::~CanvasView() {}

void CanvasView::zoom(int value)
{
    this->scale(value/m_ScaleFactor, value/m_ScaleFactor);
    m_ScaleFactor = value;
}
