#include <QDataStream>
#include "chat/commands/Commands.h"
#include "NetworkCommon.h"
#include "Switch.h"

QByteArray NetworkCommon::preparePacket(quint16 code, quint16 target, const QByteArray &data) {
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    out << (quint16) data.size() << target << code << data;

    return packet;
}

bool NetworkCommon::packetReadyToReceive(QTcpSocket *socket, Header &header, QByteArray &data) {
    if (socket == 0) {
        return false;
    }

    QDataStream in(socket);

    // object size
    if (header.getDataSize() == 0) { // new packet being received
        quint16 dataSize;

        if (socket->bytesAvailable() < (qint64) sizeof(quint16)) {
            // The size has not been fully received
            return false;
        }

        in >> dataSize;
        header.setDataSize(dataSize);
    }

    // target
    if (header.getTarget() == (quint16) TargetCode::UNDEFINED) {
        quint16 target;

        if (socket->bytesAvailable() < (qint64) sizeof(quint16)) {
            return false;
        }

        in >> target;
        header.setTarget(target);
    }

    // command
    if (header.getCode() == (quint16) ChatCodes::UNDEFINED) {
        quint16 code;

        if (socket->bytesAvailable() < (qint64) sizeof(quint16)) {
            return false;
        }

        in >> code;
        header.setCode(code);
    }

    // content
    if (socket->bytesAvailable() < header.getDataSize()) {
        // the data has not been fully received
        return false;
    }

    in >> data;
    return true;
}
