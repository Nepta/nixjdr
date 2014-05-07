#include <QDataStream>

#include "commands/chatcmds.h"
#include "chatcommon.h"

ChatCommon::ChatCommon()
{
}

QByteArray ChatCommon::preparePacket(const QString &msg) {
    ChatCodes cmdCode;
    QString strippedMsg;

    cmdCode = translateCommandToCode(msg);
    strippedMsg = stripCommandFromMessage(msg);

    return preparePacket(cmdCode, strippedMsg);
}

QByteArray ChatCommon::preparePacket(ChatCodes cmdCode, const QString &msg) {
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    out << quint16(0) << (quint16) cmdCode << msg;
    out.device()->seek(0);
    out << (quint16) (packet.size() - 2*sizeof(quint16));

    return packet;
}

ChatCodes ChatCommon::translateCommandToCode(const QString &msg) {
    QString cmd = msg.split(" ").at(0);

    if (!msg.startsWith("/")) {
        return ChatCodes::USERCMD_MESSAGE;
    }
    else {
        // TODO remplacer par HELP
        return ChatCmds::s_CommandCodes.value(cmd, ChatCodes::USERCMD_MESSAGE);
    }
}

QString ChatCommon::stripCommandFromMessage(const QString &msg) {
    QString strippedMsg = msg;

    if (msg.startsWith("/")) {
        extractFirstWord(strippedMsg);
    }

    return strippedMsg;
}

QString ChatCommon::extractFirstWord(QString &msg) {
    QString firstWord;

    firstWord = msg.section(" ", 0, 0);
    msg = msg.section(" ", 1, -1);

    return firstWord;
}

bool ChatCommon::messageReadyToReceive(QTcpSocket *socket, ChatHeader &header, QString &msg) {
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

    // command
    if (header.getCmd() == (quint16) ChatCodes::UNDEFINED) {
        quint16 cmd;

        if (socket->bytesAvailable() < (qint64) sizeof(quint16)) {
            return false;
        }

        in >> cmd;
        header.setCmd(cmd);
    }

    // message
    if (socket->bytesAvailable() < header.getMsgSize()) {
        // the message has not been fully received
        return false;
    }

    in >> msg;
    return true;
}