#include "MapServer.h"

MapServer::MapServer(QHash<QString, User *> *usersList) :
    ServerReceiver(usersList)
{
}

MapServer::~MapServer() {}

void MapServer::processNewMessage(Header header, QByteArray& data) {
    // TODO
}
