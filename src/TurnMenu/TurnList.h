#ifndef TURNLIST_H
#define TURNLIST_H

#include <QListWidget>
#include <QPoint>
#include <QKeyEvent>
#include <QContextMenuEvent>

namespace Ui {
    class TurnList;
}

class TurnList : public QListWidget
{
    Q_OBJECT

public:
    explicit TurnList(QWidget *parent = 0);
    ~TurnList();
    static const bool RIGHT = true;
    static const bool LEFT = false;

    void selectNextItem();
    void deleteCurrentItems();
    void addTurn();
    void addTurn(QString text, bool update = true);

private slots:
    void showContextMenu(const QPoint& pos);
    void deleteTurn(QListWidgetItem *item);
    void turnItemChanged(QWidget*);
    void updateTurnList();

private:
    Ui::TurnList *ui;

    void keyPressEvent(QKeyEvent *event);
    void dropEvent(QDropEvent *event);
    void moveItemList(QList<QListWidgetItem*> itemsToMove, bool direction);
    void selectNearestItem(bool direction);
    void moveToItemInDirection(bool direction);
    int directionToInt(bool direction);
    void unselectItems();

signals:
    void updatedTurnList(QString items);
};

#endif //TURNLIST_H
