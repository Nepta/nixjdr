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

public slots:
    void sendMessageToServer(const QString& msg, quint16 code = Receiver::UNDEFINED_CODE);

signals:
    void sendMessageToChatUi(const QString &msg);
};

#endif // ChatClient_H
