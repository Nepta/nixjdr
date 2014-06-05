#ifndef MAPSERVER_H
#define MAPSERVER_H

#include "Network/SenderServer.h"
#include "Network/Receiver.h"
#include "Database/DBComponent.h"

#include "MapClient.h" // TODO MapCodes should be elsewhere

class MapServer : public SenderServer, public Receiver, public DBComponent
{
    Q_OBJECT

public:
    MapServer(QHash<QString, User *> *usersList, Database *db);
    ~MapServer();
    void processNewData(Header header, QByteArray& data);

private:
    void removeAllFoWAction(const QString& msg);
};

#endif // MAPSERVER_H
