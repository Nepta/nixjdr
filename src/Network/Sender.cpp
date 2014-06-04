#include "Sender.h"

Sender::Sender(QHash<QString, User *> *usersList) {
    m_UsersList = usersList;
}

Sender::~Sender() {}

/**
 * @brief Sender::sendPacketToOne Sends a packet to the specified User.
 * @param user User to send the packet to.
 * @param packet Packet which will be sent.
 */
void Sender::sendPacketToOne(User *user, const QByteArray& packet) {
    user->getSocket()->write(packet);
}

/**
 * @brief Sender::sendPacketToList Sends a packet to a list of Users.
 * @param users Users to send the packet to.
 * @param packet Packet which will be sent.
 */
void Sender::sendPacketToList(QList<User*> users, const QByteArray& packet) {
    for (User *user : users) {
        if (user != NULL) {
            user->getSocket()->write(packet);
        }
    }
}

/**
 * @brief preparePacket Prepare a packet containing a header and the object to send.
 * @param code Specifies which action should be executed when the packet is received
 * @param target Specifies to which Receiver the packet should be redirected when received
 * @param data Content of the packet
 * @return packet
 */
QByteArray Sender::preparePacket(quint16 code, quint16 target, const QByteArray &data) {
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    out << (quint16) data.size() << target << code << data;

    return packet;
}
