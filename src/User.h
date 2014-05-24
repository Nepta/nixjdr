#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
#include <QtNetwork>
#include "Network/Header.h"
#include "User.h"
#include "DataBase/DataBase.h"

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
    QString getPendingNickname();
    QString getServerIpAddress();
    Role getRole();

    User* setNickname(const QString &nickname);
    User* setPendingNickname(const QString &nickname);
    User* setServerIpAddress(const QString &serverIpAddress);
    User* setRole(const Role &role);
    User* setDatabase(DataBase *database);

private slots:
    void receivedData();
    void userDisconnected();

signals:
    void userConnectedNotify();
    void userDisconnectedNotify(User &user);
    void socketErrorNotify(QAbstractSocket::SocketError);
    void receivedFullData(Header header, QByteArray data);

private:
    /**
     * @brief packetReadyToReceive Returns if the packet has been fully received, and fill the
     * header and the object.
     * @param socket Socket receiving a packet
     * @param header Header to fill
     * @param data data to fill
     * @return packet reception state (true: fully received, false: being received)
     */
    bool packetReadyToReceive(QTcpSocket *socket, Header &header, QByteArray &data);

    QTcpSocket *m_Socket;
    Header m_Header;
    QString m_Nickname;
    QString m_PendingNickname;
    QString m_serverIpAddress;
    Role m_Role;
    DataBase *m_Database;
};

#endif // USER_H
