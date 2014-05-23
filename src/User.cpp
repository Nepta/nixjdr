#include "Network/Receiver.h"
#include "Network/Switch.h"
#include "User.h"

User::User(QTcpSocket *socket)
{
    m_Socket = socket;
    m_Header = Header();
    m_Nickname = QString("guest");

    connect(m_Socket, SIGNAL(readyRead()), this, SLOT(receivedData()));
    connect(m_Socket, SIGNAL(disconnected()), this, SLOT(userDisconnected()));
    connect(m_Socket, SIGNAL(connected()), this, SIGNAL(userConnectedNotify()));
    connect(m_Socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SIGNAL(socketErrorNotify(QAbstractSocket::SocketError)));
}

User::User() : User(new QTcpSocket) {}

User::~User() {
    delete m_Socket;
    delete m_DataBase;
}

void User::receivedData()
{
    QByteArray data;

    if (packetReadyToReceive(m_Socket, m_Header, data)) {
        m_Header.setSocketUserNickname(getNickname());
        emit receivedFullData(m_Header, data);
        m_Header.reset();
    }

    // receivedData() is called by the signal readyRead() when new data is available.
    // However readyRead() cannot be emitted again while the receivedData slot
    // is executed. The following lines fix the problem by calling received Data
    // once again while m_Socket contains available bytes.
    if (m_Socket->bytesAvailable() > 0) {
        receivedData();
    }
}

bool User::packetReadyToReceive(QTcpSocket *socket, Header &header, QByteArray &data) {
    if (socket == 0) {
        return false;
    }

    QDataStream in(socket);

    // object size
    if (header.getDataSize() == 0) { // new packet being received
        quint16 dataSize;

        if (socket->bytesAvailable() < (qint64) sizeof(quint16)) {
            // The size has not been fully received
            return false;
        }

        in >> dataSize;
        header.setDataSize(dataSize);
    }

    // target
    if (header.getTarget() == (quint16) TargetCode::UNDEFINED) {
        quint16 target;

        if (socket->bytesAvailable() < (qint64) sizeof(quint16)) {
            return false;
        }

        in >> target;
        header.setTarget(target);
    }

    // command
    if (header.getCode() == Receiver::UNDEFINED_CODE) {
        quint16 code;

        if (socket->bytesAvailable() < (qint64) sizeof(quint16)) {
            return false;
        }

        in >> code;
        header.setCode(code);
    }

    // content
    if (socket->bytesAvailable() < header.getDataSize()) {
        // the data has not been fully received
        return false;
    }

    in >> data;
    return true;
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

Header User::getHeader() {
    return m_Header;
}

QString User::getNickname() {
    return m_Nickname;
}

QString User::getPendingNickname() {
    return m_PendingNickname;
}

QString User::getServerIpAddress() {
    return m_serverIpAddress;
}

Role User::getRole() {
    return m_Role;
}

User* User::setNickname(const QString &nickname) {
    m_Nickname = nickname;

    return this;
}

User* User::setPendingNickname(const QString &nickname) {
    m_PendingNickname = nickname;

    return this;
}

User* User::setServerIpAddress(const QString &serverIpAddress) {
    m_serverIpAddress = serverIpAddress;
	 m_DataBase = new DataBase("jdrDB", serverIpAddress);

    return this;
}

User* User::setRole(const Role &role) {
    m_Role = role;

    return this;
}
