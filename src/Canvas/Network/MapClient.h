#ifndef MAPCLIENT_H
#define MAPCLIENT_H

#include "Network/ClientReceiver.h"
//TODO #include "Canvas/Map.h"

class Map;

// TODO MapCodes dans action.h
enum class MapCodes : quint16 {
    UNDEFINED = Receiver::UNDEFINED_CODE,

    ADD_SPRITE
};

class MapClient : public ClientReceiver
{
    Q_OBJECT

private:
    QList<Map*> m_MapsList;

public:
    MapClient(User *user, QHash<QString, User *> *usersList);
    ~MapClient();

    void addMapToList(Map* map);

public slots:
    void sendMessageToServer(const QString& msg);

private slots:
    void processNewMessage(Header header, QByteArray &data);
};

#endif // MAPCLIENT_H
