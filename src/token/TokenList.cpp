#include "TokenList.h"

TokenList::TokenList()
{
    this->insertItem(0, new QListWidgetItem(
        QIcon("resource/flandre.png"), "flandre"));
    this->insertItem(1, new QListWidgetItem(
        QIcon("resource/cirno.png"), "cirno"));
    this->insertItem(2, new QListWidgetItem(
        QIcon("resource/sakuya.png"), "sakuya"));
    this->insertItem(3, new QListWidgetItem(
        QIcon("resource/marisa.png"), "marisa"));
    this->insertItem(4, new QListWidgetItem(
        QIcon("resource/rumia.png"), "rumia"));
    this->insertItem(5, new QListWidgetItem(
        QIcon("resource/reimu.png"), "reimu"));
    this->insertItem(6, new QListWidgetItem(
        QIcon("resource/patchouli.png"), "patchouli"));
    this->insertItem(7, new QListWidgetItem(
        QIcon("resource/youmu.png"), "youmu"));
    this->insertItem(8, new QListWidgetItem(
        QIcon("resource/remilia.png"), "remilia"));
    this->insertItem(9, new QListWidgetItem(
        QIcon("resource/yuyuko.png"), "yuyuko"));
    this->insertItem(10, new QListWidgetItem(
        QIcon("resource/sanae.png"), "sanae"));
    this->insertItem(11, new QListWidgetItem(
        QIcon("resource/aya.png"), "aya"));
}

void TokenList::dragMoveEvent(QDragMoveEvent * event){
    if(event->mimeData()->hasImage()){
        event->acceptProposedAction();
    }
}

void TokenList::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton){
        return;
    }

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    QPoint pos = event->localPos().toPoint();
    QListWidgetItem *clickedItem = this->itemAt(pos);

    this->setCurrentItem(clickedItem);
    QPixmap spriteToMove = clickedItem->icon().pixmap(QSize(32,32));

    drag->setPixmap(spriteToMove);

    mimeData->setImageData(spriteToMove.toImage());
    drag->setMimeData(mimeData);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
}

QListWidgetItem TokenList::getCurrentItem(){
    return this->getCurrentItem();
}
