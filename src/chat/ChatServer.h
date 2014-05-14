#ifndef ChatServer_H
#define ChatServer_H

#include <QtNetwork>
#include "Network/ServerNode.h"
#include "ChatProcessor.h"
#include "User.h"

class ChatServer : public ServerNode, public ChatProcessor
{
    Q_OBJECT

public:
    /**
     * @brief ChatServer Default constructor. Initializes m_Server with a new server, sets the user list,
     * and connects the ports
     */
    ChatServer();
    ~ChatServer();

    /**
     * @brief init Initializes the server to listen to any IP adress on the port 50885, and checks
     * if the connection went as expected.
     */
    void init();

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
     * @brief processNewMessage     Executes the command associated with an incoming message
     * @param header    Incoming message's header
     * @param message   incomming message's content
     */
    void processNewMessage(Header header, QString message);

signals:
    void sendMessageToChatUi(const QString &msg);
};

#endif // ChatServer_H
