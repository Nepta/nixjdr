#ifndef TURNMENU_H
#define TURNMENU_H

#include <QWidget>
#include <QContextMenuEvent>

#include "Network/SenderHandler.h"
#include "TurnList.h"

namespace Ui {
    class TurnMenu;
}

class TurnMenu : public QWidget, public SenderHandler
{
    Q_OBJECT

public:
    explicit TurnMenu(QWidget *parent = 0);
    ~TurnMenu();

    void setTurnList(QStringList turnItems);
    TurnList *getTurnList();

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void sendUpdatedTurnList(const QString& turnListItems);

private:
    Ui::TurnMenu *ui;
};

#endif // TURNMENU_H
