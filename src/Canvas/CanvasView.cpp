#include "CanvasView.h"

#include <QDebug>

CanvasView::CanvasView(CanvasScene* scene)
{
    m_scene = scene;
    setScene(m_scene);
    setAcceptDrops(true);
}

CanvasView::~CanvasView()
{
    delete m_scene;
}
