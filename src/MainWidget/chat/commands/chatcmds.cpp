#include "chatcmds.h"
#include "chatcmdnickname.h"
#include "chatcmdmessageall.h"
#include "chatcmdwhisper.h"

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
    m_Commands.insert(ChatCodes::USERCMD_MESSAGE, new ChatCmdMessageAll());
    m_Commands.insert(ChatCodes::USERCMD_NICK, new ChatCmdNickname());
    m_Commands.insert(ChatCodes::USERCMD_WHISPER, new ChatCmdWhisper());

    // allow each command to send packets
    foreach (AbstractChatCmd *command, m_Commands) {
        connect(command, SIGNAL(cmdSendPacketToAll(ChatCodes, QString)),
                this, SIGNAL(cmdSendPacketToAll(ChatCodes, QString)));

        connect(command, SIGNAL(cmdSendPacketToOne(ChatCodes, QString, QString)),
                this, SIGNAL(cmdSendPacketToOne(ChatCodes, QString,QString )));
    }
}

ChatCmds::~ChatCmds() {
}

AbstractChatCmd *ChatCmds::getCommand(ChatCodes code) {
    return m_Commands.value(code);
}

QString ChatCmds::getPrintableCommandsList() {
    // TODO

    return NULL;
}
