#ifndef SENDERCLIENT_H
#define SENDERCLIENT_H

#include "Serializable/Serializable.h"
#include "Sender.h"

class SenderClient : public Sender
{
public:
    SenderClient(User *user, QHash<QString, User *> *usersList);
    ~SenderClient();

    User *getUser();

protected:
    User *m_User;

    void sendPacketToServer(quint16 code, quint16 target, Serializable &data);
};

#endif // SENDERCLIENT_H
