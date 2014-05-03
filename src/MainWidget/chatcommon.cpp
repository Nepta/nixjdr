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

    if (msgSize == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) { // On n'a pas reçu la taille du message en entier
             return false;
        }

        in >> msgSize;
    }

    // Si on connaît la taille du message, on vérifie si on a reçu le message en entier
    if (socket->bytesAvailable() < msgSize) {
        return false;
    }

    in >> msg;
    return true;
}
