#include "NetworkCommon.h"
#include "ServerReceiver.h"

ServerReceiver::ServerReceiver(QHash<QString, User *> *usersList) : Receiver(usersList) {}

void ServerReceiver::sendPacketToAll(quint16 target, quint16 code, QString message) {
    QByteArray packet;
    packet = NetworkCommon::preparePacket(code, target, message);

    foreach (User *user, *m_UsersList) {
        user->getSocket()->write(packet);
    }
}

void ServerReceiver::sendPacketToOne(quint16 target, quint16 code, QString message, QString receiverNickname) {
    QByteArray packet;

    packet = NetworkCommon::preparePacket(code, target, message);
    m_UsersList->value(receiverNickname)->getSocket()->write(packet);
}
