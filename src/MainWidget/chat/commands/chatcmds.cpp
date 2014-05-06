#include "chatcmds.h"
#include "chatcmdmessageall.h"
#include "chatcmdnickname.h"
#include "chatcmdwhisper.h"
#include "chatcmdmessageui.h"
#include "chatcmdnicknameack.h"
#include "chatcmdwhisperrep.h"

inline uint qHash(const ChatCodes &key)
{
    return qHash((quint16) key);
}

const QHash<QString, ChatCodes> ChatCmds::s_CommandCodes = {
    {"/nickname", ChatCodes::USERCMD_NICK},
    {"/w", ChatCodes::USERCMD_WHISPER}
};

ChatCmds::ChatCmds()
{
    // User commands
    m_UserCommands.insert(ChatCodes::USERCMD_MESSAGE, new ChatCmdMessageAll());
    m_UserCommands.insert(ChatCodes::USERCMD_NICK, new ChatCmdNickname());
    m_UserCommands.insert(ChatCodes::USERCMD_WHISPER, new ChatCmdWhisper());

    // Server commands
    m_ServerCommands.insert(ChatCodes::SRVCMD_MESSAGE, new ChatCmdMessageUI);
    m_ServerCommands.insert(ChatCodes::SRVCMD_NICK_ACK, new ChatCmdNicknameAck);
    m_ServerCommands.insert(ChatCodes::SRVCMD_WHISPER_REP, new ChatCmdWhisperRep);

    // Allow each command to send packets (server side)
    foreach (AbstractChatCmd *command, m_UserCommands) {
        connect(command, SIGNAL(cmdSendPacketToAll(ChatCodes, QString)),
                this, SIGNAL(cmdSendPacketToAll(ChatCodes, QString)));

        connect(command, SIGNAL(cmdSendPacketToOne(ChatCodes, QString, QString)),
                this, SIGNAL(cmdSendPacketToOne(ChatCodes, QString,QString )));
    }

    // Allow each command to send messages to the UI (client side)
    foreach (AbstractChatCmd *command, m_ServerCommands) {
        connect(command, SIGNAL(cmdSendMessageToUI(QString)),
                this, SIGNAL(cmdSendMessageToUI(QString)));
    }
}

ChatCmds::~ChatCmds() {
}

AbstractChatCmd *ChatCmds::getUserCommand(ChatCodes code) {
    return m_UserCommands.value(code);
}

AbstractChatCmd *ChatCmds::getServerCommand(ChatCodes code) {
    return m_ServerCommands.value(code);
}

QString ChatCmds::getPrintableCommandsList() {
    // TODO

    return NULL;
}
