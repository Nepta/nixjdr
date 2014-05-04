#include "chatclient.h"
#include "chatcommon.h"

ChatClient::ChatClient() :
    QObject()
{
    QTcpSocket *socket = new QTcpSocket(this);
    m_User = new User(socket);

    connect(m_User, SIGNAL(receivedFullData(ChatHeader, QString)),
            this, SLOT(processNewMessage(ChatHeader, QString)));
    connect(m_User, SIGNAL(userDisconnectedNotify(User&)), this, SIGNAL(clientDisconnected(User&)));
    connect(m_User, SIGNAL(userConnectedNotify()), this, SIGNAL(clientConnected()));
    connect(m_User, SIGNAL(socketErrorNotify(QAbstractSocket::SocketError)),
            this, SLOT(socketError(QAbstractSocket::SocketError)));
}

ChatClient::ChatClient(const QString &serverIP, const quint16 &serverPort) :
    ChatClient()
{
    connection(serverIP, serverPort);
}

ChatClient::~ChatClient() {
    delete m_User;
}

/**
 * @brief ChatClient::connection Connect to the specified host (IP and port).
 * @param serverIP
 * @param serverPort
 */
void ChatClient::connection(const QString &serverIP, const quint16 &serverPort)
{
    m_User->getSocket()->abort(); // disable previous connection
    m_User->getSocket()->connectToHost(serverIP, serverPort);
}

/**
 * @brief ChatClient::sendMessageToServer Send the message to the server in order
 * to broadcast it to all the users.
 * @param pseudo
 * @param msg
 */
void ChatClient::sendMessageToServer(const QString &msg)
{
    QByteArray packet;
    QString formattedMsg;

    formattedMsg = QString(msg);

    packet = ChatCommon::preparePacket(formattedMsg);
    m_User->getSocket()->write(packet);
}

void ChatClient::socketError(QAbstractSocket::SocketError error)
{
    QString errMsg;

    switch(error) // On affiche un message différent selon l'erreur qu'on nous indique
    {
        case QAbstractSocket::HostNotFoundError:
            errMsg = tr("<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            errMsg = tr("<em>ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>");
            break;
        case QAbstractSocket::RemoteHostClosedError:
            errMsg = tr("<em>ERREUR : le serveur a coupé la connexion.</em>");
            break;
        default:
            errMsg = tr("<em>ERREUR : ") + m_User->getSocket()->errorString() + "</em>";
    }

    emit sendMessageToUI(errMsg);
}

void ChatClient::processNewMessage(ChatHeader header, QString message) {
    switch (header.getCmd()) {
        case ChatCommon::MESSAGE :
            emit sendMessageToUI(message);
            break;

        case ChatCommon::SRVCMD_NICK_ACK :
            m_User->setPseudo(message);
            emit sendMessageToUI(tr("Vous avez changé votre peudo en ") + message);
            break;
    }
}
