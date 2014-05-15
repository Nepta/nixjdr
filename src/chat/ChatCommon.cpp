#include <QDataStream>
#include "Network/Switch.h"
#include "commands/Commands.h"
#include "ChatCommon.h"

//TODO QString->QObject
QByteArray ChatCommon::preparePacket(quint16 code, quint16 target, const QString &msg) {
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    out << (quint16) msg.size() << target << code << msg;

    return packet;
}

QString ChatCommon::extractFirstWord(QString &msg) {
    QString firstWord;

    firstWord = msg.section(" ", 0, 0);
    msg = msg.section(" ", 1, -1);

    return firstWord;
}

//TODO 3 argument (+target) et QString->QObject
bool ChatCommon::messageReadyToReceive(QTcpSocket *socket, Header &header, QString &msg) {
    if (socket == 0) {
        return false;
    }

    QDataStream in(socket);

    // message size
    if (header.getMsgSize() == 0) { // new message being received
        quint16 msgSize;

        if (socket->bytesAvailable() < (qint64) sizeof(quint16)) {
            // The message has not been fully received
            return false;
        }

        in >> msgSize;
        header.setMsgSize(msgSize);
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

    // message
    if (socket->bytesAvailable() < header.getMsgSize()) {
        // the message has not been fully received
        return false;
    }

    in >> msg;
    return true;
}
