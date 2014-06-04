#ifndef SENDERSERVER_H
#define SENDERSERVER_H

#include "Serializable/Serializable.h"
#include "Sender.h"

class SenderServer : public Sender
{
    Q_OBJECT

public:
    SenderServer(QHash<QString, User *> *usersList);
    ~SenderServer();

protected slots:
    void sendPacketToAll(quint16 target, quint16 code, Serializable &data);
    void sendPacketToOne(quint16 target, quint16 code, Serializable& data, QString receiverNickname);
};

#endif // SENDERSERVER_H
