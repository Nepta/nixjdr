#include "Receiver.h"

Receiver::Receiver(QHash<QString, User *> *usersList) {
    m_UsersList = usersList;
}

QByteArray Receiver::preparePacket(quint16 code, quint16 target, const QByteArray &data) {
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    out << (quint16) data.size() << target << code << data;

    return packet;
}
