#ifndef ChatServer_H
#define ChatServer_H

#include <QtNetwork>
#include "Network/ServerReceiver.h"
#include "ChatProcessor.h"
#include "User.h"

class ChatServer : public ServerReceiver, public ChatProcessor
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
     * @brief newClientConnection identify the new client user and send him the list of nicknames.
     */
    void newClientConnection(User *newUser);

    void userDisconnected(User &user);

private slots:
    /**
     * @brief processNewMessage     Executes the command associated with an incoming message
     * @param header    Incoming message's header
     * @param message   incomming message's content
     */
    void processNewMessage(Header header, QByteArray &data);

signals:
    void sendMessageToChatUi(const QString &msg);
};

#endif // ChatServer_H
