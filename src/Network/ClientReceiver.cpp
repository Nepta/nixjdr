#include "ClientReceiver.h"
#include "chat/ChatCommon.h"

ClientReceiver::ClientReceiver(User *user, QHash<QString, User *> *usersList) :
    Receiver(usersList)
{
    m_User = user;
}

void ClientReceiver::sendPacketToServer(quint16 code, quint16 target, const QString &msg)
{
    QByteArray packet = ChatCommon::preparePacket(code, target, msg);

    m_User->getSocket()->write(packet);
}

User *ClientReceiver::getUser() {
    return m_User;
}
