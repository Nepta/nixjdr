#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QContextMenuEvent>

#include "Network/SenderHandler.h"

#include "DiceMenu/DiceMenu.h"

#include "Chat/ChatServer.h"
#include "Chat/ChatClient.h"

#include "User.h"

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget, public SenderHandler
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = 0);
    ~ChatWidget();
    void setSenderClient(SenderClient *senderClient);
    void setSenderServer(SenderServer *senderServer);
    void sendMessageFromClientToServer(QString message);

signals:
    void requestDice(QString &msg);

private slots:
    void on_msgField_returnPressed();
    void receivedMessage(const QString &msg);
    void updateNicknamesListView();
    void rollDice(QString, bool hidden);
    void ShowContextMenu(const QPoint& pos);

    void on_diceButton_clicked();

private:
    void sendRolledDiceToUsers(QList<QListWidgetItem *> list);
    void prepareWhispUsers(QList<QListWidgetItem *> list);
    void setFocusToChat();

private:
    Ui::ChatWidget *ui;
    DiceMenu *m_DiceMenu;
};

#endif // CHATWIDGET_H
