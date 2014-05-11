#include<QTranslator>
#include "commands/abstractchatcmd.h"
#include "commands/chatcmdnickname.h"
#include "commands/CmdNicknamesList.h"
#include "chatcommon.h"
#include "chatserver.h"

ChatServer::ChatServer()
{
    m_Server = new QTcpServer(this);

    // init commands
    AbstractChatCmd::setUsersListServer(&m_UsersList);
    connect(&m_ChatCmds, SIGNAL(cmdSendPacketToAll(ChatCodes, QString)),
            this, SLOT(sendPacketToAll(ChatCodes, QString)));
    connect(&m_ChatCmds, SIGNAL(cmdSendPacketToOne(ChatCodes, QString, QString)),
            this, SLOT(sendPacketToOne(ChatCodes, QString, QString)));
}

ChatServer::~ChatServer()
{
    m_Server->deleteLater();
    qDeleteAll(m_UsersList.begin(), m_UsersList.end());
    m_UsersList.clear();
}

void ChatServer::init() {
    //if (!m_Server->listen(QHostAddress::Any)) {
    //TEST
    if (!m_Server->listen(QHostAddress::Any, 50885)) {
    //TEST
        QString msg = tr("Le serveur n'a pas pu être démarré. Raison :<br />") +
                m_Server->errorString();
        emit sendMessageToChatUi(msg);
    }
    else {
        QString msg = tr("Le serveur a été démarré sur le port <strong>")
                + QString::number(m_Server->serverPort())
                + tr("</strong>.<br />Des clients peuvent maintenant se connecter.");
        emit sendMessageToChatUi(msg);

        connect(m_Server, SIGNAL(newConnection()), this, SLOT(newClientConnection()));
    }
}

/**
 * @brief ChatServer::newClientConnection
 */
void ChatServer::newClientConnection()
{
    User *newUser = new User(m_Server->nextPendingConnection());

    ChatCmdNickname *cmdNickname = dynamic_cast<ChatCmdNickname*>(
                m_ChatCmds.getUserCommand(ChatCodes::USERCMD_NICK));
    cmdNickname->executeOnUser(newUser, "guest", "guest", true);

    CmdNicknamesList *cmdNicknamesList = dynamic_cast<CmdNicknamesList*>(
                m_ChatCmds.getUserCommand(ChatCodes::USERCMD_LIST));
    cmdNicknamesList->executeOnUser(newUser);

    // process and send a packet when fully received
    connect(newUser, SIGNAL(receivedFullData(ChatHeader, QString)),
            this, SLOT(processNewMessage(ChatHeader, QString)));
    connect(newUser, SIGNAL(userDisconnectedNotify(User&)), this, SLOT(userDisconnected(User&)));
}

void ChatServer::userDisconnected(User &user)
{
    sendPacketToAll(ChatCodes::SRVCMD_DISCONNECT, user.getNickname());

    m_UsersList.remove(user.getNickname());

    // The socket may still be in use even though the client is disconnected (e.g.
    // message still being sent).
    user.deleteLater();
}


void ChatServer::processNewMessage(ChatHeader header, QString message) {
    ChatCodes code = (ChatCodes) header.getCmd();

    m_ChatCmds.getUserCommand(code)->execute(header, message);
}

void ChatServer::sendPacketToAll(ChatCodes code, QString message)
{
    QByteArray packet;
    packet = ChatCommon::preparePacket(code, message);

    for (int i = 0; i < m_UsersList.values().size(); i++)
    {
        m_UsersList.values()[i]->getSocket()->write(packet);
    }
}

void ChatServer::sendPacketToOne(ChatCodes code, QString message,
                                 QString receiverNickname) {
    QByteArray packet;

    packet = ChatCommon::preparePacket(code, message);
    m_UsersList.value(receiverNickname)->getSocket()->write(packet);
}

quint16 ChatServer::getPort()
{
    return m_Server->serverPort();
}
