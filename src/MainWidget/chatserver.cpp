#include "chatserver.h"
#include "chatcommon.h"

ChatServer::ChatServer()
{
    server = new QTcpServer(this);

    msgSize = 0;
}

ChatServer::~ChatServer()
{
    delete server;
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

void ChatServer::newClientConnection()
{
    sendMessageToClients(tr("<em>Un nouveau client vient de se connecter</em>"));

    QTcpSocket *nouveauClient = server->nextPendingConnection();
    listClients << nouveauClient;

    connect(nouveauClient, SIGNAL(readyRead()), this, SLOT(receivedData()));
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
}

void ChatServer::receivedData()
{
    // Retrieve client who sent the message
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());

    QString message;
    if (ChatCommon::messageReadyToReceive(socket, message, msgSize)) {
        sendMessageToClients(message);
        msgSize = 0;
    }
}

void ChatServer::clientDisconnected()
{
    sendMessageToClients(tr("<em>Un client vient de se déconnecter</em>"));

    // On détermine quel client se déconnecte
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) { // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;
    }

    listClients.removeOne(socket);

    // The socket may still be in use even though the client is disconnected (e.g.
    // message still being sent).
    socket->deleteLater();
}

void ChatServer::sendMessageToClients(const QString &message)
{
    QByteArray packet;

    packet = ChatCommon::preparePacket(message);

    // Envoi du paquet préparé à tous les clients connectés au server
    for (int i = 0; i < listClients.size(); i++)
    {
        listClients[i]->write(packet);
    }
}

quint16 ChatServer::getPort()
{
    return server->serverPort();
}
