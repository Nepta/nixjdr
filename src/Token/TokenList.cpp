#include "TokenList.h"

TokenList::TokenList(QWidget *parent) :
    QListWidget(parent)
{
    //addItem(new TokenItem("resource/flandre.png", "flandre", 32));

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
    if (!(event->buttons() & Qt::LeftButton)){
        return;
    }

    if ((event->pos() - m_dragStartPosition).manhattanLength() < START_DRAG_DISTANCE) {
        return;
    }

    QPoint pos = event->localPos().toPoint();
    QListWidgetItem *clickedItem = this->itemAt(pos);
    this->setCurrentItem(clickedItem);

    TokenItem *tokenItem = dynamic_cast<TokenItem*>(clickedItem);
    if(tokenItem != NULL) {
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;
        QByteArray data = tokenItem->toQByteArray();

        mimeData->setData("application/tokenitem", data);
        drag->setMimeData(mimeData);

        QPixmap spriteToMove = tokenItem->icon().pixmap(QSize(32,32));
        drag->setPixmap(spriteToMove);

        drag->exec(Qt::CopyAction | Qt::MoveAction);
    }
}

/**
 * @brief TokenList::findTokenItemById Find a token in the list by its id (assignated by the db).
 * @param id Id of the token to find.
 * @return The TokenItem associated with the given id, or NULL if no TokenItem is found.
 */
TokenItem *TokenList::findTokenItemById(int id) {
    TokenItem *result = NULL;

    for (int i = 0 ; i < count() ; i++) {
        QListWidgetItem *listWidgetItem = item(i);
        TokenItem *tokenItem = dynamic_cast<TokenItem*>(listWidgetItem);

        if (tokenItem->id() == id) {
            result = tokenItem;
            break;
        }
    }

    return result;
}
