#ifndef ChatClient_H
#define ChatClient_H

#include <QtNetwork>
#include <QString>

#include "Network/Receiver.h"
#include "Network/SenderClient.h"
#include "ChatProcessor.h"
#include "User.h"

class ChatClient : public SenderClient, public Receiver, public ChatProcessor
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

    void processNewData(Header header, QByteArray &data);

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

signals:
    void sendMessageToChatUi(const QString &msg);
};

#endif // ChatClient_H
