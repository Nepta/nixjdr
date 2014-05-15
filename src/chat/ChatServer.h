#ifndef ChatServer_H
#define ChatServer_H

#include <QtNetwork>
#include "Network/Receiver.h"
#include "ChatProcessor.h"
#include "User.h"

class ChatServer : public Receiver, public ChatProcessor
{
    Q_OBJECT

public:
    /**
     * @brief Server Initializes m_Server with a new server, sets the user list,
     * and connects the ports
     */
    ChatServer(QHash<QString, User *> *usersList);
    ~ChatServer();

    /**
     * @brief init Initializes the server to listen to any IP adress on the port 50885, and checks
     * if the connection went as expected.
     *
    void init();*/


    /**
     * @brief newClientConnection identify the new client user and send him the list of nicknames.
     */
    void newClientConnection(User *newUser);

private:
    QHash<QString, User *> *m_UsersList;

private slots:
    /**
     * @brief userDisconnected  Informs other users of the disconnection, and supresses both
     * the client and the user from the database
     * @param user  Reference to the user who disconnected
     *
    void userDisconnected(User &user);*/

    /**
     * @brief processNewMessage     Executes the command associated with an incoming message
     * @param header    Incoming message's header
     * @param message   incomming message's content
     */
    void processNewMessage(Header header, QString message);

signals:
    void sendPacketToAll(quint16 code, QString message);
    void sendPacketToOne(quint16 code, QString message, QString receiverNickname);
    void sendMessageToChatUi(const QString &msg);
};

#endif // ChatServer_H
