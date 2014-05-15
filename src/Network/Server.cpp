#include "chat/ChatServer.h"
#include "Server.h"

Server::Server() {
    m_Server = new QTcpServer(this);

    m_Nodes.insert(TargetCode::CHAT_SERVER, new ChatServer(&m_UsersList));
    // TODO m_Nodes.insert(TargetCode::MAP_SERVER, new MapServer(m_UsersList));
}

Server::~Server() {
    m_Server->deleteLater();
    qDeleteAll(m_UsersList.begin(), m_UsersList.end());
    m_UsersList.clear();
}

void Server::init() {
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

void Server::newClientConnection()
{
    User *newUser = new User(m_Server->nextPendingConnection());

    // identify User and update his nicknames list
    ChatServer *chatServer = dynamic_cast<ChatServer*>(
                m_Nodes.value(TargetCode::CHAT_SERVER));
    chatServer->newClientConnection(newUser);

    // send a packet to the intended Receiver when fully received
    connect(newUser, SIGNAL(receivedFullData(Header, QString)),
            this, SLOT(switchNewMessage(Header, QString)));
    connect(newUser, SIGNAL(userDisconnectedNotify(User&)), this, SLOT(userDisconnected(User&)));
}

void Server::userDisconnected(User &user)
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
