#ifndef TOKENMENU_H
#define TOKENMENU_H

#include <QWidget>

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
};

#endif // TOKENMENU_H
