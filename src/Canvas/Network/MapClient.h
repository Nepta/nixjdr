#ifndef MAPCLIENT_H
#define MAPCLIENT_H

#include "Network/SenderClient.h"
#include "Network/Receiver.h"
#include "Token/TokenList.h"
#include "Canvas/Map.h"
#include "MapCodes.h"

class MapClient : public SenderClient, public Receiver
{
    Q_OBJECT

public:
    MapClient(User *user, QHash<QString, User *> *usersList, TokenList *tokenList);
    ~MapClient();

    void addMapToList(Map* map);
    void removeMapFromList(Map *map);
    void processNewData(Header header, QByteArray &data);
    bool containsMap(int mapId);

public slots:
    void sendMessageToServer(const QString& msg, quint16 code);

private:
    TokenList *m_TokenList;
    QList<Map*> m_MapsList;

    void openMapAction(const QString& msg);
    void addSpriteAction(const QString& msg);
    void removeSpriteAction(const QString& msg);
    void removeAllFoWAction(const QString& msg);
    void addAllFoWAction(const QString& msg);
    void updateDrawingLayerPixmapAction(const QString& msg);
    void pingAction(const QString& msg);

    Map *getMapById(int mapId);
    Map *getMapByMapLayerId(int mapLayerId);
    Map *getMapByFoWLayerId(int fowLayerId);
    Map *getMapByDrawingLayerId(int drawingLayerId);

signals:
    void openMap(Map *map);
};

#endif // MAPCLIENT_H
