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

/*void CanvasView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasImage()){
            event->acceptProposedAction();
    }
}*/

/*void CanvasView::dragMoveEvent(QDragMoveEvent * event) {
    QGraphicsView;;dragMoveEvent(event);

    if(event->mimeData()->hasImage()){
        event->acceptProposedAction();
    }
}*/

/*void CanvasView::dropEvent(QDropEvent *event)
{
    QGraphicsView::dropEvent(event);

    int x = event->pos().x();
    int y = event->pos().y();
    QPixmap* sprite = new QPixmap();
    QImage image = qvariant_cast<QImage>(event->mimeData()->imageData());
    *sprite = sprite->fromImage(image);

    m_scene->addSprite(sprite, x, y);

    event->acceptProposedAction();
}*/


/*void CanvasView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    m_xClick = event->x();
    m_yClick = event->y();

    qDebug() << __FILE__
             << "pos: " << event->pos()
             << "local pos: " << event->localPos()
             << "global pos: " << event->globalPos()
             << "window pos: " << event->windowPos();

    if (event->button() == Qt::LeftButton) {
        m_dragStartPosition = event->pos();
    }
    else if (event->button() == Qt::RightButton) {
        //m_scene->removeSprite(m_xClick, m_yClick);
    }
}*/

/*void CanvasView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

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
}*/

/*void CanvasView::mouseReleaseEvent(QMouseEvent *event) {
    QGraphicsView::mouseReleaseEvent(event);

    m_xClick = event->x();
    m_yClick = event->y();

    if (event->button() == Qt::LeftButton) {
        // TODO purpose? m_dragStartPosition = event->pos();

        //QPixmap* sprite = new QPixmap(m_scene->getSpritePath());
        //m_scene->addSprite(sprite, m_xClick, m_yClick);
    }
}*/
