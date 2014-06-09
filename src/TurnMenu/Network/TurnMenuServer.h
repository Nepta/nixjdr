#ifndef TURNMENUSERVER_H
#define TURNMENUSERVER_H

#include "Network/SenderServer.h"
#include "Network/Receiver.h"

class TurnMenuServer : public SenderServer, public Receiver
{
    Q_OBJECT

public:
    TurnMenuServer(QHash<QString, User *> *usersList);
    ~TurnMenuServer();

    void processNewData(Header header, QByteArray& data);
};

#endif // TURNMENUSERVER_H
