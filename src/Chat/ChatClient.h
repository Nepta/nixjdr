#ifndef ChatClient_H
#define ChatClient_H

#include <QtNetwork>
#include <QString>

#include "Network/ClientReceiver.h"
#include "ChatProcessor.h"
#include "User.h"

class ChatClient : public ClientReceiver, public ChatProcessor
{
    Q_OBJECT

public:
    /**
     * @brief ChatClient::ChatClient    Connects signals, initializes the userlist, and connects to
     * the server's IP and port
     * @param user - user behind the ChatClient, holds server information (IP)
     */
    ChatClient(User *user, QHash<QString, User *> *usersList);
    ~ChatClient();

private:
    ChatCodes translateCommandToCode(const QString &msg);
    QString stripCommandFromMessage(const QString &msg);

    QHash<QString, User *> *m_UsersList;

public slots:
    /**
     * @brief ChatClient::sendMessageToServer   Sends the message to the server in order
     * to broadcast it to all the users.
     * @param msg   Reference to the message to send
     */
    void sendMessageToServer(const QString &msg);

private slots:
    /**
     * @brief processNewMessage     Interprets incoming server message's commands
     * @param header    message's header, contains the command to interpret
     * @param message   message to process
     */
    void processNewMessage(Header header, QByteArray &data);

signals:
    void sendMessageToChatUi(const QString &msg);
};

#endif // ChatClient_H
