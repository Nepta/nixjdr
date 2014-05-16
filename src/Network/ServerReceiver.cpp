#include "NetworkCommon.h"
#include "ServerReceiver.h"

ServerReceiver::ServerReceiver(QHash<QString, User *> *usersList) : Receiver(usersList) {}

void ServerReceiver::sendPacketToAll(quint16 target, quint16 code, Serializable &data) {
    QByteArray packet;
    packet = NetworkCommon::preparePacket(code, target, data.serialize());

    foreach (User *user, *m_UsersList) {
        user->getSocket()->write(packet);
    }
}

void ServerReceiver::sendPacketToOne(quint16 target, quint16 code, Serializable &data, QString receiverNickname) {
    QByteArray packet;

    packet = NetworkCommon::preparePacket(code, target, data.serialize());
    m_UsersList->value(receiverNickname)->getSocket()->write(packet);
}
