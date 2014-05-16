#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
#include <QtNetwork>
#include "Network/Header.h"
#include "User.h"

enum class Role {
    ROLE_MJ = 0,
    ROLE_PLAYER
};

class User : public QObject
{
    Q_OBJECT

public:
    User();
    User(QTcpSocket *socket);
    ~User();

    QTcpSocket *getSocket();
    Header getHeader();
    QString getNickname();
    QString getServerIpAddress();
    Role getRole();

    User* setNickname(const QString &nickname);
    User* setServerIpAddress(const QString &serverIpAddress);
    User* setRole(const Role &role);

private slots:
    void receivedData();
    void userDisconnected();

signals:
    void userConnectedNotify();
    void userDisconnectedNotify(User &user);
    void socketErrorNotify(QAbstractSocket::SocketError);
    void receivedFullData(Header header, QByteArray data);

private:
    QTcpSocket *m_Socket;
    Header m_Header;
    QString m_Nickname;
    QString m_serverIpAddress;
    Role m_Role;
};

#endif // USER_H
