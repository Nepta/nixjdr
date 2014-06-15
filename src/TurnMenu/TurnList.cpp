#include <QMenu>
#include <QAction>

#include "TurnList.h"
TurnList::TurnList(QWidget *parent)
    : QListWidget(parent)
{
    //orientation & navigation
    this->setFlow(QListView::LeftToRight);
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->setMovement(QListView::Static);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // selection & drag / drop
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
    this->setDragDropMode(QAbstractItemView::InternalMove);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
        SLOT(showContextMenu(const QPoint&)));
}

TurnList::~TurnList()
{

}

/**
 * @brief TurnList::addQStringAsItem Adds an item to the TurnList with the given QString. Sets the
 * selected item to the one inserted in order to scroll to the end of the list.
 * @param p_string QString to insert in the TurnList.
 * @param update Sends a notification that the TurnList has been updated if true, false otherwise.
 */
void TurnList::addQStringAsItem(QString p_string, bool update) {
    this->setFocus();
    this->addItem(new QListWidgetItem(p_string));
    this->setCurrentRow(this->count()-1);
    this->item(this->count()-1)->setSelected(false);

    if (update) {
        updateTurnList();
    }
}

void TurnList::deleteCurrentItems(){
    qDeleteAll(this->selectedItems());

    updateTurnList();
}

void TurnList::selectNextItem(){
    if(this->count() != 0){
        this->setFocus();
        unselectItems();
        moveToItemInDirection(RIGHT);
    }
}

void TurnList::moveItemList(QList<QListWidgetItem*> itemsToMove, bool direction){
    if(this->count() != 0 && itemsToMove.count() != 0){
        int move = directionToInt(direction);
        int rowOfFirstItem = this->row(itemsToMove.first());

        if((this->currentRow() < rowOfFirstItem && direction == LEFT)
                || (this->currentRow() > rowOfFirstItem && direction == RIGHT))
        {
            for(int i=0; i<itemsToMove.size()/2; i++){
                itemsToMove.swap(i, itemsToMove.size()-(1+i));
            }
            rowOfFirstItem = this->row(itemsToMove.first());
        }

        if((rowOfFirstItem != 0 && direction == LEFT)
                || (rowOfFirstItem != this->count()-1 && direction == RIGHT)){
            foreach (QListWidgetItem *oldItem, itemsToMove) {
                int oldRow = this->indexFromItem(oldItem).row();
                int newRow = oldRow + move;

                while(newRow>0 && newRow < this->count() && this->item(newRow)->isSelected()){
                    newRow += move;
                }

                if(newRow < 0){
                    newRow = 0;
                }
                else if(newRow >= this->count()){
                    newRow = this->count()-1;
                }

                QListWidgetItem *newItem = this->takeItem(oldRow);
                this->insertItem(newRow, newItem);
                this->setCurrentRow(newRow);
            }
        }
    }

    updateTurnList();
}

void TurnList::selectNearestItem(bool direction){
    if(this->count() != 0){
        this->currentItem()->setSelected(true);
        moveToItemInDirection(direction);
    }
}

void TurnList::moveToItemInDirection(bool direction){
    int move = directionToInt(direction);

    if(this->currentRow()==this->count()-1 && direction == RIGHT){
        this->setCurrentRow(0);
    }
    else if(this->currentRow()==0 && direction == LEFT){
        this->setCurrentRow(this->count()-1);
    }
    else{
        this->setCurrentRow(this->currentRow()+move);
    }

    updateTurnList();
}

int TurnList::directionToInt(bool direction){
    int intToReturn = 1;
    if(direction == LEFT){
        intToReturn = -1;
    }
    return intToReturn;
}

void TurnList::unselectItems(){
    foreach (QListWidgetItem* itemToUnselect, this->selectedItems()) {
        itemToUnselect->setSelected(false);
    }
    this->currentItem()->setSelected(true);
}

void TurnList::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete){
        deleteCurrentItems();
    }

    else if(event->key() == Qt::Key_A && event->modifiers() == Qt::ControlModifier){
        this->selectAll();
    }

    else if(event->key() == Qt::Key_Right || event->key() == Qt::Key_Left){
        bool direction = RIGHT;
        if(event->key()==Qt::Key_Left){
            direction = LEFT;
        }
        if(event->modifiers() == Qt::ControlModifier){
            moveItemList(this->selectedItems(), direction);
        }
        else if(event->modifiers() == Qt::ShiftModifier){
            selectNearestItem(direction);
        }
        else{
            moveToItemInDirection(direction);
        }
    }

    else if(event->key() == Qt::Key_Space){
        moveToItemInDirection(RIGHT);
    }
    else if(event->key() == Qt::Key_Escape){
        unselectItems();
    }
}

void TurnList::dropEvent(QDropEvent *event) {
    QListWidget::dropEvent(event);

    updateTurnList();
}

void TurnList::showContextMenu(const QPoint& pos){
    QPoint globalPos = this->mapToGlobal(pos);
    QString msg;
    QMenu menu;

    QAction* deleteAction = menu.addAction(tr("Supprimer"));
    QAction* selectedItem = menu.exec(globalPos);
    if (selectedItem == deleteAction)
    {
        deleteCurrentItems();
    }
}

/**
 * @brief TurnList::updateTurnList Notifies that the TurnList has been updated, and sends all the
 * items strings.
 */
void TurnList::updateTurnList() {
    QStringList itemStrings;
    QString result = "";

    for (int i = 0 ; i < count() ; i++) {
        itemStrings.append(item(i)->text());
    }

    if (!itemStrings.isEmpty()) {
        result = itemStrings.join(" ");
    }

    emit updatedTurnList(result);
}
