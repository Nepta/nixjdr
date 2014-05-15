#ifndef Commands_H
#define Commands_H

#include <QObject>
#include <QHash>
#include <QString>
#include "AbstractCmd.h"

enum class ChatCodes : quint16 {
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

private slots:
    void cmdSendPacketToAll(TargetCode target, ChatCodes code, QString message);
    void cmdSendPacketToOne(TargetCode target, ChatCodes code, QString message, QString receiverNickname);

signals:
    void cmdSendMessageToChatUi(const QString &msg);
    void cmdUpdateUserListView();
    void sendPacketToAll(quint16 target, quint16 code, QString message);
    void sendPacketToOne(quint16 target, quint16 code, QString message, QString receiverNickname);
};

#endif // Commands_H
