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
    qreal newValue = value/5.0;
    this->scale(newValue/m_ScaleFactor, newValue/m_ScaleFactor);
    m_ScaleFactor = newValue;
    emit changeLabelScale(newValue);
}
