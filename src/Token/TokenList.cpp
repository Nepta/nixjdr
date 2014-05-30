#include "TokenList.h"

TokenList::TokenList(QWidget *parent) :
    QListWidget(parent)
{
    addItem(new TokenItem("resource/flandre.png", "flandre", 32));

    setCurrentItem(item(0));
}

void TokenList::dragMoveEvent(QDragMoveEvent * event){
    if(event->mimeData()->hasImage()){
        event->acceptProposedAction();
    }
}

QListWidgetItem TokenList::getCurrentItem(){
    return this->getCurrentItem();
}


void TokenList::mousePressEvent(QMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton) {
        m_dragStartPosition = mouseEvent->pos();
        this->setCurrentItem(this->itemAt(mouseEvent->pos()));
    }
}


void TokenList::mouseMoveEvent(QMouseEvent *event){

	 QPoint pos = event->localPos().toPoint();
	 QListWidgetItem *clickedItem = this->itemAt(pos);

	 if (!(event->buttons() & Qt::LeftButton)){
		  return;
	 }

	 if ((event->pos() - m_dragStartPosition).manhattanLength() < START_DRAG_DISTANCE) {
		  return;
	 }

	 QDrag *drag = new QDrag(this);
	 QMimeData *mimeData = new QMimeData;

	 this->setCurrentItem(clickedItem);
	 if(clickedItem != NULL){
		  QPixmap spriteToMove = clickedItem->icon().pixmap(QSize(32,32));

		  drag->setPixmap(spriteToMove);

		  mimeData->setImageData(spriteToMove.toImage());
		  drag->setMimeData(mimeData);

		  drag->exec(Qt::CopyAction | Qt::MoveAction);
	 }
}
