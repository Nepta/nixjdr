#include <QMenu>
#include <QAction>

#include "TurnList.h"

#define RIGHT true
#define LEFT false

TurnList::TurnList(QWidget *parent)
    : QListWidget(parent)
{
    //orientation & navigation
    this->setFlow(QListView::LeftToRight);
    this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    this->setMovement(QListView::Static);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //style
    this->setStyleSheet( "QListWidget::item {background: lightgray; border: 1px solid black; \
                         selection-background-color: blue;}" );
    for(int i=0; i<10;i++){
        this->insertItem(i, new QListWidgetItem(QString("creep %1").arg(i)));
    }

    // selection & drag / drop
    this->setSelectionMode(QAbstractItemView::ExtendedSelection);
    this->setDragDropMode(QAbstractItemView::InternalMove);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
        SLOT(ShowContextMenu(const QPoint&)));
}

TurnList::~TurnList()
{

}

void TurnList::addQStringAsItem(QString p_string){
    this->setFocus();
    this->addItem(new QListWidgetItem(p_string));
    this->setCurrentRow(this->count()-1);
}

void TurnList::deleteCurrentItems(){
    qDeleteAll(this->selectedItems());
}

void TurnList::selectNextItem(){
    this->setFocus();
    moveToItemInDirection(RIGHT);
}

void TurnList::moveItemList(QList<QListWidgetItem*> itemsToMove, bool direction){
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

void TurnList::selectNearestItem(bool direction){
    this->currentItem()->setSelected(true);
    moveToItemInDirection(direction);
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
}

int TurnList::directionToInt(bool direction){
    int intToReturn = 1;
    if(direction == LEFT){
        intToReturn = -1;
    }
    return intToReturn;
}

void TurnList::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete){
        deleteCurrentItems();
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
        foreach (QListWidgetItem* itemToUnselect, this->selectedItems()) {
            itemToUnselect->setSelected(false);
        }
        this->currentItem()->setSelected(true);
    }
}


void TurnList::ShowContextMenu(const QPoint& pos){
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
