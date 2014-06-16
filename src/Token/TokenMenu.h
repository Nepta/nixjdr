#ifndef TOKENMENU_H
#define TOKENMENU_H

#include <QWidget>

#include "GameObjects/GameObject.h"
#include "Network/SenderHandler.h"
#include "TokenList.h"

namespace Ui {
    class TokenMenu;
}

class TokenMenu : public QWidget, public SenderHandler
{
    Q_OBJECT

public:
    explicit TokenMenu(QWidget *parent = 0);
    ~TokenMenu();
    Ui::TokenMenu *getUi();
    void initTokenMenu();
    void addItem(QListWidgetItem *item);
    void addToken(QString text, QString filePath, int size, bool custom, GameObject *gameObject = NULL);
    void addCustomToken(QString text, GameObject *gameObject = NULL);
    void editTokenCharacter(const QPoint &pos);
    TokenList *getTokenList();

private slots:
    void on_tokenButton_clicked();

    void on_m_tokenList_customContextMenuRequested(const QPoint &pos);

private:
    Ui::TokenMenu *ui;
};

#endif // TOKENMENU_H
