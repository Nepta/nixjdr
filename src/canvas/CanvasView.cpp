#include <QMouseEvent>
#include <QDrag>
#include <QDropEvent>
#include <QDebug>

#include "CanvasView.h"

CanvasView::CanvasView()
{

}

CanvasView::CanvasView(CanvasScene* scene)
{
    m_scene = scene;
    this->setScene(m_scene);
    this->ensureVisible(m_scene->sceneRect());
}

CanvasView::~CanvasView()
{
    delete m_scene;
}


CanvasView *CanvasView::getCanvasView()
{
    return this;
}

CanvasScene *CanvasView::getCanvasScene()
{
    return m_scene;
}


void CanvasView::setCanvasScene(CanvasScene *scene)
{
    m_scene = scene;
}


void CanvasView::mouseReleaseEvent(QMouseEvent *event)
{

}


void CanvasView::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    if(event->button() == Qt::LeftButton){

        QPixmap* sprite = new QPixmap(this->getCanvasScene()->getSpritePath());

        m_scene->addSprite(sprite, x, y);

//        QDrag *drag = new QDrag(this);

//        drag->setPixmap(m_scene->getPixmapItem(x, y)->pixmap());
    }

    else if(event->button() == Qt::RightButton){

    }
}


void CanvasView::mouseMoveEvent(QMouseEvent *event)
{

}
