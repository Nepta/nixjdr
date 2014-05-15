#include "chat/ChatClient.h"
#include "Client.h"

Client::Client(User *user)
{    
    m_User = user;
    m_UsersList.insert(m_User->getNickname(), m_User);

    m_Nodes.insert(TargetCode::CHAT_CLIENT, new ChatClient(m_User, &m_UsersList));
    // TODO m_Nodes.insert(TargetCode::MAP_CLIENT, new MapClient(m_UsersList));

    connect(m_User, SIGNAL(receivedFullData(Header, QString)),
            this, SLOT(switchNewMessage(Header, QString)));
    connect(m_User, SIGNAL(userDisconnectedNotify(User&)),
            this, SLOT(clientDisconnected(User&)));
    connect(m_User, SIGNAL(userConnectedNotify()),
            this, SLOT(clientConnected()));
    connect(m_User, SIGNAL(socketErrorNotify(QAbstractSocket::SocketError)),
            this, SLOT(socketError(QAbstractSocket::SocketError)));

    // connect the client socket to the server
    connection(m_User->getServerIpAddress(), 50885);
}

Client::~Client() {
    delete m_User;
}

void Client::connection(const QString &serverIP, const quint16 &serverPort)
{
    m_User->getSocket()->abort(); // disable previous connection
    m_User->getSocket()->connectToHost(serverIP, serverPort);
}

void Client::socketError(QAbstractSocket::SocketError error)
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

void Client::clientConnected()
{
    emit sendMessageToChatUi(tr("<em>Connexion réussie !</em>"));
}

void Client::clientDisconnected(User &)
{
    emit sendMessageToChatUi(tr("<em>Déconnecté du serveur</em>"));
}

User *Client::getUser() {
    return m_User;
}
