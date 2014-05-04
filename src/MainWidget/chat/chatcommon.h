#ifndef CHATCOMMON_H
#define CHATCOMMON_H

#include <QtNetwork>
#include <QHash>
#include "chatheader.h"

class ChatCommon
{
public:
    enum commands {
        MESSAGE = 0,
        USERCMD_NICK,
        SRVCMD_NICK_ACK,
        USERCMD_WHISP,
        SRVCMD_WHISP_REP,
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
