#include<QTranslator>
#include "commands/AbstractCmd.h"
#include "commands/CmdNickname.h"
#include "commands/CmdNicknamesList.h"
#include "ChatCommon.h"
#include "ChatServer.h"

ChatServer::ChatServer()
{
    m_Server = new QTcpServer(this);

    AbstractCmd::setUsersListServer(&m_UsersList);

    // init commands
    connect(&m_Commands, SIGNAL(sendPacketToAll(quint16, QString)),
            this, SLOT(sendPacketToAll(quint16, QString)));
    connect(&m_Commands, SIGNAL(sendPacketToOne(quint16, QString, QString)),
            this, SLOT(sendPacketToOne(quint16, QString, QString)));
}

ChatServer::~ChatServer()
{
    m_Server->deleteLater();
    qDeleteAll(m_UsersList.begin(), m_UsersList.end());
    m_UsersList.clear();
}

void ChatServer::init() {
    if (!m_Server->listen(QHostAddress::Any, 50885)) {
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

void ChatServer::newClientConnection()
{
    User *newUser = new User(m_Server->nextPendingConnection());

    CmdNickname *cmdNickname = dynamic_cast<CmdNickname*>(
                m_Commands.getUserCommand(ChatCodes::USERCMD_NICK));
    cmdNickname->executeOnUser(newUser, "guest", "guest", true);

    CmdNicknamesList *cmdNicknamesList = dynamic_cast<CmdNicknamesList*>(
                m_Commands.getUserCommand(ChatCodes::USERCMD_LIST));
    cmdNicknamesList->executeOnUser(newUser);

    // process and send a packet when fully received
    connect(newUser, SIGNAL(receivedFullData(Header, QString)),
            this, SLOT(processNewMessage(Header, QString)));
    connect(newUser, SIGNAL(userDisconnectedNotify(User&)), this, SLOT(userDisconnected(User&)));
}

void ChatServer::userDisconnected(User &user)
{
    sendPacketToAll((quint16) ChatCodes::SRVCMD_DISCONNECT, user.getNickname());

    m_UsersList.remove(user.getNickname());

    // The socket may still be in use even though the client is disconnected (e.g.
    // message still being sent).
    user.deleteLater();
}


void ChatServer::processNewMessage(Header header, QString message) {
    ChatCodes code = (ChatCodes) header.getCode();

    m_Commands.getUserCommand(code)->execute(header, message);
}
