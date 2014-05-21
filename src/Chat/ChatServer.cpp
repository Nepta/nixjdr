#include <QTranslator>
#include "Commands/AbstractCmd.h"
#include "Commands/CmdNickname.h"
#include "Commands/CmdNicknamesList.h"
#include "Message.h"
#include "ChatServer.h"

ChatServer::ChatServer(QHash<QString, User *> *usersList) :
    ServerReceiver(usersList)
{
    AbstractCmd::setUsersListServer(m_UsersList);

    // init commands
    connect(&m_Commands, SIGNAL(sendPacketToAll(quint16, quint16, Serializable&)),
            this, SLOT(sendPacketToAll(quint16, quint16, Serializable&)));
    connect(&m_Commands, SIGNAL(sendPacketToOne(quint16, quint16, Serializable&, QString)),
            this, SLOT(sendPacketToOne(quint16, quint16, Serializable&, QString)));
}

ChatServer::~ChatServer()
{
}

void ChatServer::newClientConnection(User *newUser)
{
    // identify the user on both the client and server side
    CmdNickname *cmdNickname = dynamic_cast<CmdNickname*>(
                m_Commands.getUserCommand(ChatCodes::USERCMD_NICK));
    cmdNickname->executeOnUser(newUser, "guest", "guest", true);

    Message msg("");
    sendPacketToOne(
        (quint16) TargetCode::CHAT_CLIENT,
        (quint16) ChatCodes::SRVCMD_CONNECT_ACK,
        msg,
        newUser->getNickname()
    );


    // update the nicknames list on the new client side
    CmdNicknamesList *cmdNicknamesList = dynamic_cast<CmdNicknamesList*>(
                m_Commands.getUserCommand(ChatCodes::USERCMD_LIST));
    cmdNicknamesList->executeOnUser(newUser);
}

void ChatServer::userDisconnected(User &user)
{
    Message msg(user.getNickname());

    sendPacketToAll((quint16) TargetCode::CHAT_CLIENT,
                    (quint16) ChatCodes::SRVCMD_DISCONNECT,
                    msg);
}

void ChatServer::processNewMessage(Header header, QByteArray &data) {
    ChatCodes code = (ChatCodes) header.getCode();
    Message message(data);

    m_Commands.getUserCommand(code)->execute(header, message.getString());
}
