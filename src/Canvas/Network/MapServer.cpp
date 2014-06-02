#include "Network/Switch.h"

#include "Chat/Message.h"

#include "MapServer.h"

MapServer::MapServer(QHash<QString, User *> *usersList) : ServerReceiver(usersList) {}
MapServer::~MapServer() {}

void MapServer::processNewMessage(Header header, QByteArray& data) {
    Message message(data);

    sendPacketToAll((quint16) TargetCode::MAP_CLIENT, header.getCode(), message);
}
