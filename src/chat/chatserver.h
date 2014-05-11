#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QtNetwork>
#include "chatprocessor.h"
#include "user.h"

class ChatServer : public ChatProcessor
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

    quint16 getPort();

/*-------------------------------------------------------------------------------------------------------*/
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
    void processNewMessage(ChatHeader header, QString message);

    /**
     * @brief sendPacketToAll   Prepares a packet and forwards it to all the users of m_UsersList
     * @param code      Forwarded message's command code
     * @param message   Forwarded message's content
     */
    void sendPacketToAll(ChatCodes code, QString message);

    /**
     * @brief sendPacketToOne   Prepares a packet and forwards it to the specified user
     * @param code      Forwarded message's command code
     * @param message   Forwarded message's content
     * @param receiverNickname  User to forward the message to
     */
    void sendPacketToOne(ChatCodes code, QString message, QString receiverNickname);

private:
    QTcpServer *m_Server;
    QHash<QString, User *> m_UsersList;
};

#endif // CHATSERVER_H
