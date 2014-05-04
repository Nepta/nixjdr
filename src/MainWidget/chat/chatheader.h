#ifndef CHATHEADER_H
#define CHATHEADER_H

#include <QtGlobal>
#include <QString>

class ChatHeader
{
public:
    ChatHeader();
    ChatHeader(quint16 msgSize, quint16 cmd);

    quint16 getMsgSize();
    quint16 getCmd();
    QString getSocketUserNickname();

    ChatHeader *setMsgSize(quint16 msgSize);
    ChatHeader *setCmd(quint16 cmd);
    ChatHeader *setSocketUserNickname(QString socketUser);

private:
    quint16 m_MsgSize;
    quint16 m_Cmd;
    QString m_SocketUserNickName;
};

#endif // CHATHEADER_H
