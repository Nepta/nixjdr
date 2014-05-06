#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QtNetwork>
#include "commands/chatcmds.h"
#include "user.h"
#include "chatheader.h"

class ChatServer : public QObject
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
    void sendMessageToUI(const QString &msg);

private:
    QTcpServer *m_Server;
    QHash<QString, User *> m_UsersList;
    ChatCmds m_ChatCmds;
};

#endif // CHATSERVER_H
