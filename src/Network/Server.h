#ifndef SERVERNODE_H
#define SERVERNODE_H

#include <QTcpServer>
#include "User.h"
#include "Switch.h"

class Server : public Switch
{
    Q_OBJECT

public:
    Server();
    Server(QTcpServer *server, QHash<QString, User *> usersList);
    ~Server();

    /**
     * @brief init Initializes the server to listen to any IP adress on the port 50885, and checks
     * if the connection went as expected.
     */
    void init();

private:
    QTcpServer *m_Server;
    QHash<QString, User *> m_UsersList;

private slots:
    /**
     * @brief newClientConnection   Creates a new connection towards the next client, adds the new user
     * to the database, and incorporates the new client in the network management
     */
    void newClientConnection();

    /**
     * @brief userDisconnected  Informs other users of the disconnection, and supresses both
     * the client and the user from the database
     * @param user  Reference to the user who disconnected
     */
    void userDisconnected(User &user);

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

signals:
    void sendMessageToChatUi(const QString &msg);
};

#endif // SERVERNODE_H

