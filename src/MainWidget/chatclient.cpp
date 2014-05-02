#include "chatclient.h"
#include "chatcommon.h"

ChatClient::ChatClient() :
    QObject()
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(receivedData()));
    connect(socket, SIGNAL(connected()), this, SIGNAL(clientConnected()));
    connect(socket, SIGNAL(disconnected()), this, SIGNAL(clientDisconnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(socketError(QAbstractSocket::SocketError)));

    msgSize = 0;
}

ChatClient::ChatClient(const QString &serverIP, const quint16 &serverPort) :
    ChatClient()
{
    connection(serverIP, serverPort);
}

/**
 * @brief ChatClient::connection Connect to the specified host (IP and port).
 * @param serverIP
 * @param serverPort
 */
void ChatClient::connection(const QString &serverIP, const quint16 &serverPort)
{
    socket->abort(); // disable previous connection
    socket->connectToHost(serverIP, serverPort);
}

/**
 * @brief ChatClient::sendMessageToServer Send the message to the server in order
 * to broadcast it to all the users
 * @param pseudo
 * @param msg
 *
 * @todo refacto : pseudo in User class
 */
void ChatClient::sendMessageToServer(const QString &pseudo, const QString &msg)
{
    QByteArray packet;
    QString formattedMsg;

    formattedMsg = QString("<strong>" + pseudo + "</strong> : " + msg);

    packet = ChatCommon::preparePacket(formattedMsg);
    socket->write(packet);
}

void ChatClient::receivedData()
{
    QString message;

    if (ChatCommon::messageReadyToReceive(socket, message, msgSize)) {
        emit sendMessageToUI(message);
        msgSize = 0;
    }
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
            errMsg = tr("<em>ERREUR : ") + socket->errorString() + tr("</em>");
    }

    emit sendMessageToUI(errMsg);
}
