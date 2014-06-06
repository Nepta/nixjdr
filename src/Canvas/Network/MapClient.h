#ifndef MAPCLIENT_H
#define MAPCLIENT_H

#include "Network/SenderClient.h"
#include "Network/Receiver.h"
#include "Token/TokenList.h"
#include "Canvas/Map.h"

class Map;

// TODO MapCodes dans actions.h
enum class MapCodes : quint16 {
    UNDEFINED = Receiver::UNDEFINED_CODE,

    OPEN_MAP,
    ADD_SPRITE,
    REMOVE_SPRITE,
    REMOVE_ALL_FOW
};

class MapClient : public SenderClient, public Receiver
{
    Q_OBJECT

public:
    MapClient(User *user, QHash<QString, User *> *usersList, TokenList *tokenList);
    ~MapClient();

    void addMapToList(Map* map);
    void removeMapFromList(Map *map);
    void processNewData(Header header, QByteArray &data);

public slots:
    void sendMessageToServer(const QString& msg);

private:
    TokenList *m_TokenList;
    QList<Map*> m_MapsList;

    void openMapAction(const QString& msg);
    void addSpriteAction(const QString& msg);
    void removeSpriteAction(const QString& msg);
    void removeAllFoWAction(const QString& msg);

    Map *getMapById(int mapId);
    Map *getMapByMapLayerId(int mapLayerId);
    Map *getMapByFoWLayerId(int fowLayerId);

signals:
    void openMap(Map *map);
};

#endif // MAPCLIENT_H
