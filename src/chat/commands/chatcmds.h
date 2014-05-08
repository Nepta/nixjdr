#ifndef CHATCMDS_H
#define CHATCMDS_H

#include <QObject>
#include <QString>
#include <QHash>
#include "abstractchatcmd.h"

enum class ChatCodes {
    USERCMD_MESSAGE = 0,
    USERCMD_NICK,
    USERCMD_WHISPER,

    SRVCMD_MESSAGE,
    SRVCMD_NICK_ACK,
    SRVCMD_WHISPER_REP,
    SRVCMD_DISCONNECT,

    UNDEFINED
};
inline uint qHash(const ChatCodes &key);

class ChatCmds : public QObject
{
    Q_OBJECT

public:
    const static QHash<QString, ChatCodes> s_CommandCodes;

    ChatCmds();
    ~ChatCmds();

    AbstractChatCmd *getUserCommand(ChatCodes code);
    AbstractChatCmd *getServerCommand(ChatCodes code);
    QString getPrintableCommandsList();

private:
    QHash<ChatCodes, AbstractChatCmd *> m_UserCommands;
    QHash<ChatCodes, AbstractChatCmd *> m_ServerCommands;

signals:
    void cmdSendPacketToAll(ChatCodes code, QString message);
    void cmdSendPacketToOne(ChatCodes code, QString message,
                            QString receiverNickname);
    void cmdSendMessageToUI(const QString &msg);
};

#endif // CHATCMDS_H
