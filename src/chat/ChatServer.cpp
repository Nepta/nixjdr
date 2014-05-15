#include<QTranslator>
#include "commands/AbstractCmd.h"
#include "commands/CmdNickname.h"
#include "commands/CmdNicknamesList.h"
#include "ChatCommon.h"
#include "ChatServer.h"

ChatServer::ChatServer(QHash<QString, User *> *usersList)
{
    m_UsersList = usersList;
    AbstractCmd::setUsersListServer(m_UsersList);

    // init commands
    connect(&m_Commands, SIGNAL(sendPacketToAll(quint16, quint16, QString)),
            this, SIGNAL(sendPacketToAll(quint16, quint16, QString)));
    connect(&m_Commands, SIGNAL(sendPacketToOne(quint16, quint16, QString, QString)),
            this, SIGNAL(sendPacketToOne(quint16, quint16, QString, QString)));
}

ChatServer::~ChatServer()
{
}

void ChatServer::newClientConnection(User *newUser)
{
    CmdNickname *cmdNickname = dynamic_cast<CmdNickname*>(
                m_Commands.getUserCommand(ChatCodes::USERCMD_NICK));
    cmdNickname->executeOnUser(newUser, "guest", "guest", true);

    CmdNicknamesList *cmdNicknamesList = dynamic_cast<CmdNicknamesList*>(
                m_Commands.getUserCommand(ChatCodes::USERCMD_LIST));
    cmdNicknamesList->executeOnUser(newUser);
}

void ChatServer::processNewMessage(Header header, QString message) {
    ChatCodes code = (ChatCodes) header.getCode();

    m_Commands.getUserCommand(code)->execute(header, message);
}
