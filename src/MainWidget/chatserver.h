#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QtNetwork>

class ChatServer : public QObject
{
    Q_OBJECT

public:
    ChatServer();
    ~ChatServer();
    void sendMessageToClients(const QString &message);
    quint16 getPort();
    void init();

private slots:
    void newClientConnection();
    void receivedData();
    void clientDisconnected();

signals:
    void sendMessageToUI(const QString &msg);

private:
    QTcpServer *server;
    QList<QTcpSocket *> listClients;
    quint16 msgSize;
};

#endif // CHATSERVER_H
