#include "Commands.h"
#include "CmdHelp.h"
#include "CmdMessageall.h"
#include "CmdNickname.h"
#include "CmdWhisper.h"
#include "CmdDisconnect.h"
#include "CmdMessageui.h"
#include "CmdNicknameAck.h"
#include "CmdWhisperRep.h"
#include "CmdRoll.h"
#include "CmdNicknamesList.h"
#include "CmdNicknamesListAck.h"
#include "CmdConnectionAck.h"

const QHash<QString, ChatCodes> Commands::s_CommandCodes = {
    {"/help", ChatCodes::USERCMD_HELP},
    {"/nickname", ChatCodes::USERCMD_NICK},
    {"/w", ChatCodes::USERCMD_WHISPER},
    {"/roll", ChatCodes::USERCMD_ROLL}
};

Commands::Commands()
{
    // User commands
    m_UserCommands.insert(ChatCodes::USERCMD_HELP, new CmdHelp(&m_UserCommands));
    m_UserCommands.insert(ChatCodes::USERCMD_MESSAGE, new CmdMessageAll);
    m_UserCommands.insert(ChatCodes::USERCMD_NICK, new CmdNickname);
    m_UserCommands.insert(ChatCodes::USERCMD_WHISPER, new CmdWhisper);
    m_UserCommands.insert(ChatCodes::USERCMD_ROLL, new CmdRoll(m_UserCommands));
    m_UserCommands.insert(ChatCodes::USERCMD_LIST, new CmdNicknamesList);

    m_ServerCommands.insert(ChatCodes::SRVCMD_MESSAGE, new CmdMessageUI);
    m_ServerCommands.insert(ChatCodes::SRVCMD_NICK_ACK, new CmdNicknameAck);
    m_ServerCommands.insert(ChatCodes::SRVCMD_WHISPER_REP, new CmdWhisperRep);
    m_ServerCommands.insert(ChatCodes::SRVCMD_DISCONNECT, new CmdDisconnect);
    m_ServerCommands.insert(ChatCodes::SRVCMD_LIST, new CmdNicknamesListAck);
    m_ServerCommands.insert(ChatCodes::SRVCMD_CONNECT_ACK, new CmdConnectionAck);


    // Allow each command to send packets (server side)
    foreach (AbstractCmd *command, m_UserCommands) {
        connect(command, SIGNAL(cmdSendPacketToAll(TargetCode, ChatCodes, Serializable&)),
                this, SLOT(cmdSendPacketToAll(TargetCode, ChatCodes, Serializable&)));

        connect(command, SIGNAL(cmdSendPacketToOne(TargetCode, ChatCodes, Serializable&, QString)),
                this, SLOT(cmdSendPacketToOne(TargetCode, ChatCodes, Serializable&, QString)));
    }

    // Allow each command to interact with the UI and send messages to the server (client side)
    foreach (AbstractCmd *command, m_ServerCommands) {
        connect(command, SIGNAL(cmdSendMessageToChatUi(QString)),
                this, SIGNAL(cmdSendMessageToChatUi(QString)));
        connect(command, SIGNAL(cmdUpdateUserListView()),
                this, SIGNAL(cmdUpdateUserListView()));
        connect(command, SIGNAL(cmdSendMessageToServer(QString)),
                this, SIGNAL(cmdSendMessageToServer(QString)));
    }
}

Commands::~Commands() {
    qDeleteAll(m_UserCommands);
    qDeleteAll(m_ServerCommands);
}

AbstractCmd *Commands::getUserCommand(ChatCodes code) {
    return m_UserCommands.value(code);
}

AbstractCmd *Commands::getServerCommand(ChatCodes code) {
    return m_ServerCommands.value(code);
}

void Commands::cmdSendPacketToAll(TargetCode target, ChatCodes code, Serializable &data) {
    emit sendPacketToAll((quint16) target, (quint16) code, data);
}

void Commands::cmdSendPacketToOne(TargetCode target, ChatCodes code, Serializable &data, QString receiverNickname) {
    emit sendPacketToOne((quint16) target, (quint16) code, data, receiverNickname);
}
