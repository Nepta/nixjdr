#ifndef TOKENMENUCLIENT_H
#define TOKENMENUCLIENT_H

#include "Network/SenderClient.h"
#include "Network/Receiver.h"

class TokenMenuClient  : public SenderClient, public Receiver
{
public:
    TokenMenuClient(User *user, QHash<QString, User *> *usersList);
    ~TokenMenuClient();

    void processNewData(Header header, QByteArray &data);

public slots:
    void sendMessageToServer(const QString& msg);
};

#endif // TOKENMENUCLIENT_H
