#include "ServerReceiver.h"
#include "chat/ChatCommon.h"

void ServerReceiver::sendPacketToAll(quint16 target, quint16 code, QString message) {
    QByteArray packet;
    packet = ChatCommon::preparePacket(code, target, message);

    foreach (User *user, *m_UsersList) {
        user->getSocket()->write(packet);
    }
}

void ServerReceiver::sendPacketToOne(quint16 target, quint16 code, QString message, QString receiverNickname) {
    QByteArray packet;

    packet = ChatCommon::preparePacket(code, target, message);
    m_UsersList->value(receiverNickname)->getSocket()->write(packet);
}
