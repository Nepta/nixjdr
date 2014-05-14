#ifndef SERVERNODE_H
#define SERVERNODE_H

#include <QTcpServer>
#include "User.h"
#include "Receiver.h"

class ServerNode : public Receiver
{
    Q_OBJECT

public:
    ServerNode();
    ServerNode(QTcpServer *server, QHash<QString, User *> usersList);
    virtual ~ServerNode(){}

protected:
    QTcpServer *m_Server;
    QHash<QString, User *> m_UsersList;

protected slots:
    virtual void newClientConnection() = 0;
    virtual void userDisconnected(User &user) = 0;

    /**
     * @brief sendPacketToAll Prepares a packet and forwards it to all the users of m_UsersList
     * @param code            Forwarded message's command code
     * @param message         Forwarded message's content
     */
    void sendPacketToAll(quint16 code, QString message);

    /**
     * @brief sendPacketToOne   Prepares a packet and forwards it to the specified user
     * @param code              Forwarded message's command code
     * @param message           Forwarded message's content
     * @param receiverNickname  User to forward the message to
     */
    void sendPacketToOne(quint16 code, QString message, QString receiverNickname);
};

#endif // SERVERNODE_H

