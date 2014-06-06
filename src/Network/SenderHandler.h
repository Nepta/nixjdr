#ifndef SENDERHANDLER_H
#define SENDERHANDLER_H

#include "SenderClient.h"
#include "SenderServer.h"

class SenderHandler
{
public:
    SenderHandler();
    ~SenderHandler();

    virtual void setupSenderClient(SenderClient *senderClient);
    virtual void setupSenderServer(SenderServer *senderServer);

protected:
    SenderClient *m_SenderClient;
    SenderServer *m_SenderServer;
};

#endif // SENDERHANDLER_H
