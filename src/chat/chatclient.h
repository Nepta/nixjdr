#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QtNetwork>
#include <QString>
#include "chatprocessor.h"
#include "user.h"

class ChatClient : public ChatProcessor
{
    Q_OBJECT
public:
    ChatClient(const QString &serverIP, const quint16 &serverPort);
    ~ChatClient();
    void connection(const QString &serverIP, const quint16 &serverPort);
    void sendMessageToServer(const QString &msg);
    User *getUser();

private slots:
    void socketError(QAbstractSocket::SocketError error);
    void processNewMessage(ChatHeader header, QString message);
    void clientConnected();
    void clientDisconnected(User &);

private:
    User *m_User;
    QHash<QString, User *> m_UsersList;
};

#endif // CHATCLIENT_H
