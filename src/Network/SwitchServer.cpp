#include "Canvas/Network/MapServer.h"
#include "Chat/ChatServer.h"
#include "Token/Network/TokenMenuServer.h"
#include "TurnMenu/Network/TurnMenuServer.h"
#include "SwitchServer.h"

SwitchServer::SwitchServer() {
    m_Server = new QTcpServer(this);

    m_Nodes.insert(TargetCode::CHAT_SERVER, new ChatServer(&m_UsersList));
    m_Nodes.insert(TargetCode::TOKEN_MENU_SERVER, new TokenMenuServer(&m_UsersList));
    m_Nodes.insert(TargetCode::TURN_MENU_SERVER, new TurnMenuServer(&m_UsersList));
	 m_Nodes.insert(TargetCode::MAP_SERVER, new MapServer(&m_UsersList));
}

SwitchServer::~SwitchServer() {
    m_Server->deleteLater();
    qDeleteAll(m_Nodes);
}

void SwitchServer::init() {
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

QHash<QString, User *>* SwitchServer::getUserList()
{
	return &m_UsersList;
}

void SwitchServer::newClientConnection()
{
    User *newUser = new User(m_Server->nextPendingConnection());

    // identify User and update his nicknames list
    ChatServer *chatServer = dynamic_cast<ChatServer*>(
                m_Nodes.value(TargetCode::CHAT_SERVER));
    chatServer->newClientConnection(newUser);

    // send a packet to the intended Receiver when fully received
    connect(newUser, SIGNAL(receivedFullData(Header, QByteArray)),
            this, SLOT(switchNewMessage(Header, QByteArray)));
    connect(newUser, SIGNAL(userDisconnectedNotify(User&)), this, SLOT(userDisconnected(User&)));
}

void SwitchServer::userDisconnected(User &user)
{
    // Notify everyone on the chat that a user has been disconnected
    ChatServer *chatServer = dynamic_cast<ChatServer*>(
                m_Nodes.value(TargetCode::CHAT_SERVER));
    chatServer->userDisconnected(user);

    m_UsersList.remove(user.getNickname());

    /* The socket may still be in use even though the client is disconnected (e.g.
     * message still being sent).*/
    user.deleteLater();
}
