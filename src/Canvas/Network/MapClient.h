#ifndef MAPCLIENT_H
#define MAPCLIENT_H

#include "Network/ClientReceiver.h"

class MapClient : public ClientReceiver
{
public:
    MapClient(User *user, QHash<QString, User *> *usersList);
    ~MapClient();
};

#endif // MAPCLIENT_H
