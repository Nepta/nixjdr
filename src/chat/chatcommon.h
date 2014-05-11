#ifndef CHATCOMMON_H
#define CHATCOMMON_H

#include <QtNetwork>
#include <QHash>
#include <QByteArray>
#include <QString>
#include "commands/chatcmds.h"
#include "chatheader.h"

class ChatCommon
{
public:
    ChatCommon();
    static QByteArray preparePacket(const QString &msg);
    static QByteArray preparePacket(ChatCodes cmdCode, const QString &msg);
    static ChatCodes translateCommandToCode(const QString &msg);
    static QString stripCommandFromMessage(const QString &msg);
    static QString extractFirstWord(QString &msg);
    static bool messageReadyToReceive(QTcpSocket *socket, ChatHeader &header,
                                      QString &msg);
};

#endif // CHATCOMMON_H
