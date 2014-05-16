#include "NetworkCommon.h"
#include "ClientReceiver.h"

ClientReceiver::ClientReceiver(User *user, QHash<QString, User *> *usersList) :
    Receiver(usersList)
{
    m_User = user;
}

void ClientReceiver::sendPacketToServer(quint16 code, quint16 target, Serializable &data)
{
    QByteArray packet = NetworkCommon::preparePacket(code, target, data.serialize());

    m_User->getSocket()->write(packet);
}

User *ClientReceiver::getUser() {
    return m_User;
}
