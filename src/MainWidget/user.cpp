#include "user.h"
#include "chat/chatcommon.h"

User::User(QTcpSocket *socket)
{
    m_Socket = socket;
    //m_MsgSize = 0;
    m_Header = ChatHeader();
    m_Nickname = QString("guest");

    connect(m_Socket, SIGNAL(readyRead()), this, SLOT(receivedData()));
    connect(m_Socket, SIGNAL(disconnected()), this, SLOT(userDisconnected()));
    connect(m_Socket, SIGNAL(connected()), this, SIGNAL(userConnectedNotify()));
    connect(m_Socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SIGNAL(socketErrorNotify(QAbstractSocket::SocketError)));
}

User::~User() {
    m_Socket->deleteLater();
}

void User::receivedData()
{
    ChatHeader header;
    QString message;

    if (ChatCommon::messageReadyToReceive(m_Socket, header, message)) {
        header.setSocketUserNickname(getNickname());
        emit receivedFullData(header, message);
        m_Header.setMsgSize(0);
    }

    // receivedData() is called by the signal readyRead() when new data is available.
    // However readyRead() cannot be emitted again while the receivedData slot
    // is executed. The following lines fix the problem by calling received Data
    // once again while m_Socket contains available bytes.
    if (m_Socket->bytesAvailable() > 0) {
        receivedData();
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

QString User::getNickname() {
    return m_Nickname;
}

ChatHeader User::getHeader() {
    return m_Header;
}

User* User::setNickname(const QString &nickname) {
    m_Nickname = nickname;

    return this;
}
