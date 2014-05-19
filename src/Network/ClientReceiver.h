#ifndef CLIENTRECEIVER_H
#define CLIENTRECEIVER_H

#include  "Receiver.h"
#include "Serializable.h"

class ClientReceiver : public Receiver
{
    Q_OBJECT

public:
    ClientReceiver(User *user, QHash<QString, User *> *usersList);
    virtual ~ClientReceiver(){}

    /**
     * @brief getUser   Returns the user associated with the client
     * @return  A pointer towards the current client's user
     */
    User *getUser();

public slots:
    /**
     * @brief ChatClient::sendMessageToServer   Sends the message to the server in order
     * to broadcast it to all the users.
     * @param msg   Reference to the message to send
     */
    void sendPacketToServer(quint16 code, quint16 target, Serializable &data);

protected:
    User *m_User;

};

#endif // CLIENTRECEIVER_H
