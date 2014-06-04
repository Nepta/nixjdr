#ifndef ChatServer_H
#define ChatServer_H

#include <QtNetwork>

#include "Network/Receiver.h"
#include "Network/SenderServer.h"
#include "ChatProcessor.h"
#include "User.h"

class ChatServer : public SenderServer, public Receiver, public ChatProcessor
{
    Q_OBJECT

public:
    ChatServer(QHash<QString, User *> *usersList);
    ~ChatServer();

    void newClientConnection(User *newUser);
    void userDisconnected(User &user);
    void processNewData(Header header, QByteArray &data);

signals:
    void sendMessageToChatUi(const QString &msg);
};

#endif // ChatServer_H
