#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QContextMenuEvent>

#include "Chat/ChatServer.h"
#include "Chat/ChatClient.h"
#include "User.h"

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = 0);
    ~ChatWidget();
    void setupChatServer(ChatServer *chatServer);
    void setupChatClient(ChatClient *chatClient);
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
    void sendRolledDiceToQWidgetItemList(QList<QListWidgetItem *> list);
    void prepareWhispForListOfQWidgetItem(QList<QListWidgetItem *> list);
    void setFocusToChat();

private:
    Ui::ChatWidget *ui;
    ChatServer *m_ChatServer;
    ChatClient *m_ChatClient;

};

#endif // CHATWIDGET_H
