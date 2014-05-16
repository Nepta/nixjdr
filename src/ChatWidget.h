#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include "chat/ChatServer.h"
#include "chat/ChatClient.h"
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

private slots:
    void on_msgField_returnPressed();
    void receivedMessage(const QString &msg);
    void updateNicknamesListView();
    void rollDice(QString, bool hidden);

private:
    Ui::ChatWidget *ui;
    ChatServer *m_ChatServer;
    ChatClient *m_ChatClient;
    QStringListModel *m_NicknamesListModel;
};

#endif // CHATWIDGET_H
