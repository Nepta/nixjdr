#include "commands/abstractchatcmd.h"
#include "chatclient.h"
#include "chatcommon.h"

ChatClient::ChatClient(const QString &serverIP, const quint16 &serverPort)
{
    QTcpSocket *socket = new QTcpSocket(this);
    m_User = new User(socket);
    m_UsersList.insert(m_User->getNickname(), m_User);

    connect(m_User, SIGNAL(receivedFullData(ChatHeader, QString)),
            this, SLOT(processNewMessage(ChatHeader, QString)));
    connect(m_User, SIGNAL(userDisconnectedNotify(User&)),
            this, SLOT(clientDisconnected(User&)));
    connect(m_User, SIGNAL(userConnectedNotify()),
            this, SLOT(clientConnected()));
    connect(m_User, SIGNAL(socketErrorNotify(QAbstractSocket::SocketError)),
            this, SLOT(socketError(QAbstractSocket::SocketError)));

    // init commands
    AbstractChatCmd::setUsersListClient(&m_UsersList);
    connect(&m_ChatCmds, SIGNAL(cmdsendMessageToChatUi(QString)),
            this, SIGNAL(sendMessageToChatUi(QString)));

    // connect the client socket to the server
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

    switch(error)
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

    emit sendMessageToChatUi(errMsg);
}

void ChatClient::processNewMessage(ChatHeader header, QString message) {
    ChatCodes code = (ChatCodes) header.getCmd();

    m_ChatCmds.getServerCommand(code)->execute(header, message);
}

void ChatClient::clientConnected()
{
    emit sendMessageToChatUi(tr("<em>Connexion réussie !</em>"));
}

void ChatClient::clientDisconnected(User &)
{
    emit sendMessageToChatUi(tr("<em>Déconnecté du serveur</em>"));
}

User *ChatClient::getUser() {
    return m_User;
}
