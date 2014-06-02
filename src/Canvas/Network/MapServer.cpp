#include "MapServer.h"

MapServer::MapServer(QHash<QString, User *> *usersList) :
    ServerReceiver(usersList)
{
}

MapServer::~MapServer() {}
