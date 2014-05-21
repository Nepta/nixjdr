#ifndef TOKENMENU_H
#define TOKENMENU_H

#include <QWidget>
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
    TokenList *getTokenList();

private:
    Ui::TokenMenu *ui;
    TokenList *m_tokenList;
};

#endif // TOKENMENU_H
