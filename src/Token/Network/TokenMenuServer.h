#ifndef TOKENMENUSERVER_H
#define TOKENMENUSERVER_H

#include "Network/SenderServer.h"
#include "Network/Receiver.h"

class TokenMenuServer : public SenderServer, public Receiver
{
public:
    TokenMenuServer(QHash<QString, User *> *usersList);
    ~TokenMenuServer();

    void processNewData(Header header, QByteArray& data);
};

#endif // TOKENMENUSERVER_H
