#ifndef RECEIVERHANDLER_H
#define RECEIVERHANDLER_H

#include "ClientReceiver.h"
#include "ServerReceiver.h"

class ReceiverHandler
{
public:
    ReceiverHandler();
    ~ReceiverHandler();

    virtual void setupClientReceiver(ClientReceiver *clientReceiver);
    virtual void setupServerReceiver(ServerReceiver *serverReceiver);

protected:
    ClientReceiver *m_ClientReceiver;
    ServerReceiver *m_ServerReceiver;
};

#endif // RECEIVERHANDLER_H
