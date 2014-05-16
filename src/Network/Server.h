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

signals:
    void sendMessageToChatUi(const QString &msg);
};

#endif // SERVERNODE_H
