#include "chat/ChatServer.h"
#include "chat/ChatCommon.h"
#include "Server.h"

Server::Server() {
    m_Server = new QTcpServer(this);

    m_Nodes.insert(TargetCode::CHAT_SERVER, new ChatServer(&m_UsersList));
    // TODO m_Nodes.insert(TargetCode::MAP_SERVER, new MapServer(m_UsersList));

    foreach(Receiver *node, m_Nodes) {
        connect(node, SIGNAL(sendPacketToAll(quint16, quint16, QString)),
                this, SLOT(sendPacketToAll(quint16, quint16, QString)));
        connect(node, SIGNAL(sendPacketToOne(quint16, quint16, QString, QString)),
                this, SLOT(sendPacketToOne(quint16, quint16, QString, QString)));
    }
}

Server::Server(QTcpServer *server, QHash<QString, User *> usersList) {
    m_Server = server;
    m_UsersList = usersList;
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
    ChatServer *chatServerReceiver = dynamic_cast<ChatServer*>(
                m_Nodes.value(TargetCode::CHAT_SERVER));
    chatServerReceiver->newClientConnection(newUser);

    // send a packet to the intended Receiver when fully received
    connect(newUser, SIGNAL(receivedFullData(Header, QString)),
            this, SLOT(switchNewMessage(Header, QString)));
    connect(newUser, SIGNAL(userDisconnectedNotify(User&)), this, SLOT(userDisconnected(User&)));
}

void Server::userDisconnected(User &user)
{
    sendPacketToAll((quint16) TargetCode::CHAT_CLIENT,
                    (quint16) ChatCodes::SRVCMD_DISCONNECT,
                    user.getNickname());

    m_UsersList.remove(user.getNickname());

    // The socket may still be in use even though the client is disconnected (e.g.
    // message still being sent).
    user.deleteLater();
}

void Server::sendPacketToAll(quint16 target, quint16 code, QString message) {
    QByteArray packet;
    packet = ChatCommon::preparePacket(code, target, message);

    foreach (User *user, m_UsersList) {
        user->getSocket()->write(packet);
    }
}

void Server::sendPacketToOne(quint16 target, quint16 code, QString message, QString receiverNickname) {
    QByteArray packet;

    packet = ChatCommon::preparePacket(code, target, message);
    m_UsersList.value(receiverNickname)->getSocket()->write(packet);
}
