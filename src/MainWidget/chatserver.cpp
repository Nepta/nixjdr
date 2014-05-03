#include "chatserver.h"
#include "chatcommon.h"
#include<QTranslator>

ChatServer::ChatServer()
{
    server = new QTcpServer(this);
}

ChatServer::~ChatServer()
{
    delete server;
    qDeleteAll(listUsers.begin(), listUsers.end());
    listUsers.clear();
}

void ChatServer::init() {
    //if (!server->listen(QHostAddress::Any)) {
    //TEST
    if (!server->listen(QHostAddress::Any, 50885)) {
    //TEST
        QString msg = tr("Le server n'a pas pu être démarré. Raison :<br />") + server->errorString();
        emit sendMessageToUI(msg);
    }
    else {
        QString msg = tr("Le server a été démarré sur le port <strong>")
                + QString::number(server->serverPort())
                + tr("</strong>.<br />Des clients peuvent maintenant se connecter.");
        emit sendMessageToUI(msg);

        connect(server, SIGNAL(newConnection()), this, SLOT(newClientConnection()));
    }
}

/**
 * @brief ChatServer::newClientConnection
 * @todo rename newUserConnection
 */
void ChatServer::newClientConnection()
{
    sendMessageToAll(tr("<em>Un nouveau client vient de se connecter</em>"));

    //QTcpSocket *newUserSocket = server->nextPendingConnection();
    User *newUser = new User(server->nextPendingConnection());
    listUsers << newUser;

    // full packet has been received -> process and send it
    // TODO refactor -> ChatCommon contains a parser to retrieve which action to use (see enum)
    connect(newUser, SIGNAL(receivedFullData(QString)), this, SLOT(sendMessageToAll(QString)));
    connect(newUser, SIGNAL(userDisconnectedNotify(User&)), this, SLOT(userDisconnected(User&)));
}

void ChatServer::userDisconnected(User &user)
{
    sendMessageToAll(user.getPseudo() + tr(" <em>vient de se déconnecter</em>"));

    listUsers.removeOne(&user);

    // The socket may still be in use even though the client is disconnected (e.g.
    // message still being sent).
    user.deleteLater();
}

void ChatServer::sendMessageToAll(const QString &message)
{
    QByteArray packet;

    packet = ChatCommon::preparePacket(message);

    // Envoi du paquet préparé à tous les clients connectés au server
    for (int i = 0; i < listUsers.size(); i++)
    {
        listUsers[i]->getSocket()->write(packet);
    }
}

quint16 ChatServer::getPort()
{
    return server->serverPort();
}
