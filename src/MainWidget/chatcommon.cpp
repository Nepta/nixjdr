#include "chatcommon.h"
#include <QDataStream>
#include <QDebug>
#include <QtEndian>

ChatCommon::ChatCommon()
{
}

QByteArray ChatCommon::preparePacket(const QString &msg) {
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    out << quint16(0) << msg;
    out.device()->seek(0);
    out << (quint16) (packet.size() - sizeof(quint16));

    return packet;
}

bool ChatCommon::messageReadyToReceive(QTcpSocket *socket, QString &msg, quint16 &msgSize) {
    if (socket == 0) {
        return false;
    }

    QDataStream in(socket);

    if (msgSize == 0) { // new message being received
        if (socket->bytesAvailable() < (qint64) sizeof(quint16)) {
            // The message has not been fully received
            return false;
        }

        in >> msgSize;
    }

    if (socket->bytesAvailable() < msgSize) {
        // the message has not been fully received
        return false;
    }

    in >> msg;
    return true;
}
