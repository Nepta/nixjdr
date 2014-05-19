#include "CanvasView.h"

CanvasView::CanvasView()
{

}

CanvasView::CanvasView(CanvasScene* scene)
{
    m_scene = scene;
    m_xClick = 0;
    m_yClick = 0;
    this->setScene(m_scene);
    this->ensureVisible(m_scene->sceneRect());
    this->setAcceptDrops(true);

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

void CanvasView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasImage()){
            event->acceptProposedAction();
    }
}

void CanvasView::dragMoveEvent(QDragMoveEvent * event){
    if(event->mimeData()->hasImage()){
        event->acceptProposedAction();
    }
}

void CanvasView::dropEvent(QDropEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    QPixmap* sprite = new QPixmap();
    QImage image = qvariant_cast<QImage>(event->mimeData()->imageData());
    *sprite = sprite->fromImage(image);

    m_scene->addSprite(sprite, x, y);

    event->acceptProposedAction();
}


void CanvasView::mousePressEvent(QMouseEvent *event)
{
    m_xClick = event->x();
    m_yClick = event->y();

    if(event->button() == Qt::LeftButton){

        m_dragStartPosition = event->pos();

        QPixmap* sprite = new QPixmap(this->getCanvasScene()->getSpritePath());

//        m_scene->addSprite(sprite, m_xClick, m_yClick);
    }

    else if(event->button() == Qt::RightButton){
        m_scene->removeSprite(m_xClick, m_yClick);
    }
}

void CanvasView::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - m_dragStartPosition).manhattanLength()
         < START_DRAG_DISTANCE)
        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    QGraphicsPixmapItem *pixmapItem = m_scene->getPixmapItem(m_xClick, m_yClick);
    if (pixmapItem == NULL) {
        return;
    }

    QPixmap spriteToMove = pixmapItem->pixmap();
    drag->setPixmap(spriteToMove);

    mimeData->setImageData(spriteToMove.toImage());
    drag->setMimeData(mimeData);

    m_scene->removeSprite(m_xClick, m_yClick);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
}

void CanvasView::mouseReleaseEvent(QMouseEvent *event){
    m_xClick = event->x();
    m_yClick = event->y();

    if(event->button() == Qt::LeftButton){

        m_dragStartPosition = event->pos();

        QPixmap* sprite = new QPixmap(this->getCanvasScene()->getSpritePath());

        m_scene->addSprite(sprite, m_xClick, m_yClick);
    }
}
