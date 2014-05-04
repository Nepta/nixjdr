#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QtGui>
#include <QtNetwork>
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
    void processNewMessage(ChatHeader, QString);

signals:
    void sendMessageToUI(const QString &msg);
    void clientConnected();
    void clientDisconnected(User &user);

private:
    User *m_User;
};

#endif // CHATCLIENT_H
