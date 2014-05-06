#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QtGui>
#include <QtNetwork>
#include "commands/chatcmds.h"
#include "user.h"

class ChatClient : public QObject
{
    Q_OBJECT
public:
    ChatClient();
    ~ChatClient();
    ChatClient(const QString &serverIP, const quint16 &serverPort);
    void connection(const QString &serverIP, const quint16 &serverPort);
    void sendMessageToServer(const QString &msg);

private slots:
    void socketError(QAbstractSocket::SocketError error);
    void processNewMessage(ChatHeader header, QString message);
    void clientConnected();
    void clientDisconnected(User &user);

signals:
    void sendMessageToUI(const QString &msg);

private:
    User *m_User;
    QHash<QString, User *> m_UsersList;
    ChatCmds m_ChatCmds;
};

#endif // CHATCLIENT_H
