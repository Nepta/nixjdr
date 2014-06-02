#ifndef MAPSERVER_H
#define MAPSERVER_H

#include "Network/ServerReceiver.h"

class MapServer : public ServerReceiver
{
public:
    MapServer(QHash<QString, User *> *usersList);
    ~MapServer();
};

#endif // MAPSERVER_H
