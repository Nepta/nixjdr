#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QtNetwork>
#include <user.h>

class ChatServer : public QObject
{
    Q_OBJECT

public:
    ChatServer();
    ~ChatServer();
    quint16 getPort();
    void init();

private slots:
    void newClientConnection();
    void userDisconnected(User &user);
    void sendMessageToAll(const QString &message);

signals:
    void sendMessageToUI(const QString &msg);

private:
    QTcpServer *server;
    QList<User *> listUsers;
};

#endif // CHATSERVER_H
