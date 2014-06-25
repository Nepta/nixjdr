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
    void initTokenMenuPush();
    void initTokenMenuPull();
    void addItem(QListWidgetItem *item);
    TokenItem* addToken(QString text, QString filePath = TokenItem::DEFAULT_ICON_PATH, int size = 32, bool special = false, GameObject *gameObject = NULL);
    void editTokenCharacter(TokenItem *tokenItem);
    TokenList *getTokenList();

private slots:
    void on_tokenButton_clicked();

    void on_m_tokenList_customContextMenuRequested(const QPoint &pos);

    void on_inputSearchField_textChanged(const QString &arg1);

signals:
    void sendNotification(QString str);

private:
    Ui::TokenMenu *ui;
};

#endif // TOKENMENU_H
