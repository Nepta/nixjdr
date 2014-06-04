#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QContextMenuEvent>

#include "Network/SenderHandler.h"

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
    void setupSenderClient(SenderClient *senderClient);
    void setupSenderServer(SenderServer *senderServer);
    void sendMessageFromClientToServer(QString message);

signals:
    void requestDice(QString &msg);

private slots:
    void on_msgField_returnPressed();
    void receivedMessage(const QString &msg);
    void updateNicknamesListView();
    void rollDice(QString, bool hidden);
    void ShowContextMenu(const QPoint& pos);

private:
    void sendRolledDiceToUsers(QList<QListWidgetItem *> list);
    void prepareWhispUsers(QList<QListWidgetItem *> list);
    void setFocusToChat();

private:
    Ui::ChatWidget *ui;

};

#endif // CHATWIDGET_H
