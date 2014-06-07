#ifndef SENDERCLIENT_H
#define SENDERCLIENT_H

#include "Serializable/Serializable.h"
#include "Receiver.h"
#include "Sender.h"

class SenderClient : public Sender
{
    Q_OBJECT

public:
    SenderClient(User *user, QHash<QString, User *> *usersList);
    ~SenderClient();

    User *getUser();

public slots:
    virtual void sendMessageToServer(const QString& msg, quint16 code = Receiver::UNDEFINED_CODE) = 0;

protected:
    User *m_User;

    void sendPacketToServer(quint16 code, quint16 target, Serializable &data);

};

#endif // SENDERCLIENT_H
