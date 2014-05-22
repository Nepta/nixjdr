#ifndef TURNMENU_H
#define TURNMENU_H

#include <QWidget>

#include "TurnList.h"

namespace Ui {
class TurnMenu;
}

class TurnMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TurnMenu(QWidget *parent = 0);
    ~TurnMenu();

private slots:
    void on_addItemEdit_returnPressed();

    void on_addButton_clicked();

    void on_nextButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::TurnMenu *ui;
    TurnList *m_turnList;
};

#endif // TURNMENU_H
