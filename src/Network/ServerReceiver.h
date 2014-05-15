#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include "Receiver.h"

class ServerReceiver : public Receiver
{
    Q_OBJECT

public:
    ServerReceiver(){}
    virtual ~ServerReceiver(){}

protected slots:
    /**
     * @brief sendPacketToAll Prepares a packet and forwards it to all the users of m_UsersList
     * @param code            Forwarded message's command code
     * @param message         Forwarded message's content
     */
    void sendPacketToAll(quint16 target, quint16 code, QString message);

    /**
     * @brief sendPacketToOne   Prepares a packet and forwards it to the specified user
     * @param code              Forwarded message's command code
     * @param message           Forwarded message's content
     * @param receiverNickname  User to forward the message to
     */
    void sendPacketToOne(quint16 target, quint16 code, QString message, QString receiverNickname);
};

#endif // SERVER_RECEIVER_H
