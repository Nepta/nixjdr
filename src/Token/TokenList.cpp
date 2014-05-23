#include "TokenList.h"

TokenList::TokenList(QWidget *parent) :
    QListWidget(parent)
{
    appendCustomItem(QIcon("resource/flandre.png"), "flandre");
    appendCustomItem(QIcon("resource/cirno.png"), "cirno");
    appendCustomItem(QIcon("resource/sakuya.png"), "sakuya");
    appendCustomItem(QIcon("resource/marisa.png"), "marisa");
    appendCustomItem(QIcon("resource/rumia.png"), "rumia");
    appendCustomItem(QIcon("resource/reimu.png"), "remiu");
    appendCustomItem(QIcon("resource/youmu.png"), "youmu");
    appendCustomItem(QIcon("resource/remilia.png"), "remilia");
    appendCustomItem(QIcon("resource/yuyuko.png"), "yuyuko");
    appendCustomItem(QIcon("resource/sanae.png"), "sanae");
    appendCustomItem(QIcon("resource/aya.png"), "aya");
    appendCustomItem(QIcon("resource/patchouli.png"), "patchouli");

    setCurrentItem(item(0));
}

void TokenList::appendCustomItem(QIcon icon, QString name){
    this->insertItem(this->count(), new QListWidgetItem(icon, name));
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

    drag->exec(Qt::CopyAction | Qt::MoveAction);
}

QListWidgetItem TokenList::getCurrentItem(){
    return this->getCurrentItem();
}
