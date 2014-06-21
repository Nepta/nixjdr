#include "Database/Repository/RepositoryManager.h"
#include "Network/Serializable/Message.h"
#include "Network/Switch.h"
#include "MapServer.h"

MapServer::MapServer(QHash<QString, User *> *usersList) :
    SenderServer(usersList)
{
	isLoggable(true);
}

MapServer::~MapServer() {}

void MapServer::processNewData(Header header, QByteArray& data) {
    Message message(data);

    // TODO permission system : action accepted -> sendPacketToList,
    //                          action refused -> sendPacketToOne

    // Creates a list of Users to whom the message must be transmitted excluding the sender of the
    // currently received data
    QList<User *> recipients = m_UsersList->values();
    recipients.removeOne(m_UsersList->value(header.getSocketUserNickname()));

    sendPacketToList((quint16) TargetCode::MAP_CLIENT, header.getCode(), message, recipients);
}
