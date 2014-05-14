#ifndef Commands_H
#define Commands_H

#include <QObject>
#include <QHash>
#include <QString>
#include "AbstractCmd.h"

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
    SRVCMD_CONNECT_ACK,

    UNDEFINED
};
inline uint qHash(const ChatCodes &key) { return qHash((quint16) key); }

class Commands : public QObject
{
    Q_OBJECT

public:
    const static QHash<QString, ChatCodes> s_CommandCodes;

    Commands();
    ~Commands();

    AbstractCmd *getUserCommand(ChatCodes code);
    AbstractCmd *getServerCommand(ChatCodes code);
    QString getPrintableCommandsList();

private:
    QHash<ChatCodes, AbstractCmd *> m_UserCommands;
    QHash<ChatCodes, AbstractCmd *> m_ServerCommands;

signals:
    void cmdSendPacketToAll(ChatCodes code, QString message);
    void cmdSendPacketToOne(ChatCodes code, QString message,
                            QString receiverNickname);
    void cmdSendMessageToChatUi(const QString &msg);
    void cmdSendMessageToServer(const QString &msg);
    void cmdUpdateUserListView();
};

#endif // Commands_H
