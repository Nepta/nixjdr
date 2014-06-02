#include "MapClient.h"

MapClient::MapClient(User *user, QHash<QString, User *> *usersList) :
    ClientReceiver(user, usersList)
{
}

MapClient::~MapClient() {}
