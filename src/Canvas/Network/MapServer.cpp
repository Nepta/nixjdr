#include "Network/Serializable/Message.h"
#include "Network/Switch.h"

#include "MapServer.h"

MapServer::MapServer(QHash<QString, User *> *usersList) : SenderServer(usersList) {}
MapServer::~MapServer() {}

void MapServer::processNewData(Header header, QByteArray& data) {
    Message message(data);

    sendPacketToAll((quint16) TargetCode::MAP_CLIENT, header.getCode(), message);
}
