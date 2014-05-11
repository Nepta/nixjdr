#ifndef CHATCMDS_H
#define CHATCMDS_H

#include <QObject>
#include <QHash>
#include <QString>
#include "abstractchatcmd.h"

enum class ChatCodes {
    USERCMD_MESSAGE = 0,
    USERCMD_NICK,
    USERCMD_WHISPER,
    USERCMD_ROLL,
    USERCMD_LIST,

    SRVCMD_MESSAGE,
    SRVCMD_NICK_ACK,
    SRVCMD_WHISPER_REP,
    SRVCMD_DISCONNECT,
    SRVCMD_LIST,

    UNDEFINED
};
inline uint qHash(const ChatCodes &key) { return qHash((quint16) key); }

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
    void cmdsendMessageToChatUi(const QString &msg);
    void cmdUpdateUserListView();
};

#endif // CHATCMDS_H
