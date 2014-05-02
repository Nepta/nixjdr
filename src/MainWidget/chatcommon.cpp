#include "chatcommon.h"
#include <QDataStream>

ChatCommon::ChatCommon()
{
}

QByteArray ChatCommon::preparePacket(const QString &msg) {
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    out << (quint16) msg.size();
    out << msg;

    return packet;
}

bool ChatCommon::messageReadyToReceive(QTcpSocket *socket, QString &msg, quint16 tailleMessage) {
    if (socket == 0) {
        return false;
    }

    QDataStream in(socket);

    if (tailleMessage == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) { // On n'a pas reçu la taille du message en entier
             return false;
        }

        in >> tailleMessage;
    }

    // Si on connaît la taille du message, on vérifie si on a reçu le message en entier
    if (socket->bytesAvailable() < tailleMessage) {
        return false;
    }

    in >> msg;
    return true;
}
