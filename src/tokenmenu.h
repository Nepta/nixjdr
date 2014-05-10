#ifndef TOKENMENU_H
#define TOKENMENU_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

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

private slots:
    void on_researchButton_clicked();

private:
    Ui::TokenMenu *ui;
};

#endif // TOKENMENU_H