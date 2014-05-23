#ifndef TOKENMENU_H
#define TOKENMENU_H

#include <QWidget>
#include <QSqlQueryModel>
#include "TokenList.h"

namespace Ui {
    class TokenMenu;
}

class TokenMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TokenMenu(QWidget *parent = 0);
    ~TokenMenu();
    Ui::TokenMenu *getUi();

private:
    Ui::TokenMenu *ui;
	 QSqlQueryModel *model_;
};

#endif // TOKENMENU_H
