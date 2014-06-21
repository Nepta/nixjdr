#ifndef MAPSERVER_H
#define MAPSERVER_H

#include "Network/SenderServer.h"
#include "Network/Receiver.h"
#include "MapCodes.h"

class MapServer : public SenderServer, public Receiver
{
    Q_OBJECT

public:
    MapServer(QHash<QString, User *> *usersList);
    ~MapServer();
    void processNewData(Header header, QByteArray& data);
};

#endif // MAPSERVER_H
