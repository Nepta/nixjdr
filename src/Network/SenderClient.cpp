#include "SenderClient.h"

SenderClient::SenderClient(User *user, QHash<QString, User *> *usersList) :
    Sender(usersList)
{
    m_User = user;
}

SenderClient::~SenderClient() {}

/**
 * @brief SenderClient::sendMessageToServer Sends the packet to the server.
 * @param code
 * @param target
 * @param data
 */
void SenderClient::sendPacketToServer(quint16 code, quint16 target, Serializable &data) {
    QByteArray packet = preparePacket(code, target, data.serialize());

    sendPacketToOne(m_User, packet);
}


User *SenderClient::getUser() {
    return m_User;
}
