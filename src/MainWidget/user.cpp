#include "user.h"
#include "chatcommon.h"

User::User(QTcpSocket *socket)
{
    m_Socket = socket;
    m_MsgSize = 0;
    m_Pseudo = QString("guest");

    connect(m_Socket, SIGNAL(readyRead()), this, SLOT(receivedData()));
    connect(m_Socket, SIGNAL(disconnected()), this, SLOT(userDisconnected()));
    connect(m_Socket, SIGNAL(connected()), this, SIGNAL(userConnectedNotify()));
    connect(m_Socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SIGNAL(socketErrorNotify(QAbstractSocket::SocketError)));
}

User::~User() {
    delete m_Socket;
}

// TODO connect aussi dans chatClient
void User::receivedData()
{
    QString message;
    if (ChatCommon::messageReadyToReceive(m_Socket, message, m_MsgSize)) {
        emit receivedFullData(message);
        m_MsgSize = 0;
    }
}

/**
 * @brief User::userDisconnected notify the client or the server that a user
 * has been disconnected through the signal userDisconnectedNotify.
 */
void User::userDisconnected() {
    emit userDisconnectedNotify(*this);
}

QTcpSocket* User::getSocket() {
    return m_Socket;
}

QString User::getPseudo() {
    return m_Pseudo;
}

quint16 User::getMsgSize() {
    return m_MsgSize;
}

User* User::setPseudo(const QString &pseudo) {
    m_Pseudo = pseudo;

    return this;
}
