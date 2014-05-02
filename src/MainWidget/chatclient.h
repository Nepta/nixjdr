#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QtGui>
#include <QtNetwork>

class ChatClient : public QObject
{
    Q_OBJECT
public:
    ChatClient();
    ChatClient(const QString &serverIP, const quint16 &serverPort);
    void connection(const QString &serverIP, const quint16 &serverPort);
    void sendMessageToServer(const QString &pseudo, const QString &msg);

private slots:
    void receivedData();
    void socketError(QAbstractSocket::SocketError error);

signals:
    void sendMessageToUI(const QString &msg);
    void clientConnected();
    void clientDisconnected();

private:
    QTcpSocket *socket;
    quint16 msgSize;
};

#endif // CHATCLIENT_H
