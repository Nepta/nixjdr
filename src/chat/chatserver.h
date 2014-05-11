#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QtNetwork>
#include "chatprocessor.h"
#include "user.h"

class ChatServer : public ChatProcessor
{
    Q_OBJECT

public:
    ChatServer();
    ~ChatServer();
    void init();
    quint16 getPort();

private slots:
    void newClientConnection();
    void userDisconnected(User &user);
    void processNewMessage(ChatHeader header, QString message);
    void sendPacketToAll(ChatCodes code, QString message);
    void sendPacketToOne(ChatCodes code, QString message, QString receiverNickname);

signals:
    void sendMessageToChatUi(const QString &msg);

private:
    QTcpServer *m_Server;
    QHash<QString, User *> m_UsersList;
};

#endif // CHATSERVER_H
