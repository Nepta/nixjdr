#ifndef CHATCOMMON_H
#define CHATCOMMON_H

#include <QtNetwork>
#include <QHash>
#include "chatheader.h"

class ChatCommon
{
public:
    enum commands {
        USERCMD_MESSAGE = 0,
        USERCMD_NICK,
        USERCMD_WHISPER,

        SRVCMD_MESSAGE,
        SRVCMD_NICK_ACK,
        SRVCMD_WHISPER_REP,

        UNDEFINED = 999
    };
    const static QHash<QString, commands> commandCodes;

    ChatCommon();
    static QByteArray preparePacket(const QString &msg);
    static QByteArray preparePacket(quint16 cmdCode, const QString &msg);
    static quint16 translateCommand(const QString &msg);
    static QString stripCommandFromMessage(const QString &msg);
    static QString extractFirstWord(QString &msg);
    static bool messageReadyToReceive(QTcpSocket *socket, ChatHeader &header,
                                      QString &msg);
};

#endif // CHATCOMMON_H
