#ifndef MAPSERVER_H
#define MAPSERVER_H

#include "Network/ServerReceiver.h"

class MapServer : public ServerReceiver
{
    Q_OBJECT

public:
    MapServer(QHash<QString, User *> *usersList);
    ~MapServer();

public slots:
    void processNewMessage(Header header, QByteArray& data);
};

#endif // MAPSERVER_H
