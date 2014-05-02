#ifndef CHATCOMMON_H
#define CHATCOMMON_H

#include <QtNetwork>

class ChatCommon
{
public:
    ChatCommon();
    static QByteArray preparePacket(const QString &msg);
    static bool messageReadyToReceive(QTcpSocket *socket,
                                      QString &msg, quint16 tailleMessage);
};

#endif // CHATCOMMON_H
