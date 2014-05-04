#ifndef USER_H
#define USER_H

#include <QObject>
#include <QtNetwork>
#include "chatheader.h"

class User : public QObject
{
    Q_OBJECT

public:
    User(QTcpSocket *socket);
    ~User();
    QTcpSocket *getSocket();
    QString getPseudo();
    ChatHeader getHeader();
    User* setPseudo(const QString &pseudo);

private slots:
    void receivedData();
    void userDisconnected();

signals:
    void userConnectedNotify();
    void userDisconnectedNotify(User &user);
    void socketErrorNotify(QAbstractSocket::SocketError);
    void receivedFullData(ChatHeader header, QString message);

private:
    QTcpSocket *m_Socket;
    QString m_Pseudo;
    ChatHeader m_Header;
};

#endif // USER_H
