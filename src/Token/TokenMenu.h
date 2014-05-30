#ifndef TOKENMENU_H
#define TOKENMENU_H

#include <QWidget>
#include "Database/DBComponent.h"
#include "TokenList.h"

namespace Ui {
    class TokenMenu;
}

class TokenMenu : public QWidget, public DBComponent
{
    Q_OBJECT

public:
    explicit TokenMenu(QWidget *parent = 0);
    ~TokenMenu();
    Ui::TokenMenu *getUi();
    void initTokenMenu(Database *db);

private slots:
    void on_tokenButton_clicked();

private:
    Ui::TokenMenu *ui;
};

#endif // TOKENMENU_H
