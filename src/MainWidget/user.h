#ifndef USER_H
#define USER_H

#include <QObject>
#include <QtNetwork>

class User : public QObject
{
    Q_OBJECT

public:
    User(QTcpSocket *socket);
    ~User();
    QTcpSocket *getSocket();
    QString getPseudo();
    quint16 getMsgSize();
    User* setPseudo(const QString &pseudo);

private slots:
    void receivedData();
    void userDisconnected();

signals:
    void userConnectedNotify();
    void userDisconnectedNotify(User &user);
    void socketErrorNotify(QAbstractSocket::SocketError);
    void receivedFullData(QString message);

private:
    QTcpSocket *m_Socket;
    QString m_Pseudo;
    quint16 m_MsgSize;
};

#endif // USER_H
