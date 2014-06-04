#include "SenderServer.h"

SenderServer::SenderServer(QHash<QString, User *> *usersList) : Sender(usersList) {}
SenderServer::~SenderServer() {}

/**
 * @brief SenderServer::sendPacketToAll Prepares a packet and forwards it to all the users of
 * m_UsersList.
 * @param target Forwarded packet's target Receiver
 * @param code Forwarded packet's code
 * @param data Forwarded packet's content
 */
void SenderServer::sendPacketToAll(quint16 target, quint16 code, Serializable &data) {
    QByteArray packet = preparePacket(code, target, data.serialize());

    sendPacketToList(m_UsersList->values(), packet);
}

/**
 * @brief SenderServer::sendPacketToOne Prepares a packet and forwards it to the specified user
 * (identified by his nickname).
 * @param code Forwarded packet's code
 * @param message Forwarded packet's content
 * @param data Forwarded packet's content
 * @param receiverNickname User to forward the message to.
 */
void SenderServer::sendPacketToOne(quint16 target, quint16 code, Serializable& data, QString receiverNickname) {
    QByteArray packet = preparePacket(code, target, data.serialize());

    Sender::sendPacketToOne(m_UsersList->value(receiverNickname), packet);
}
