#ifndef MAPCLIENT_H
#define MAPCLIENT_H

#include "Network/SenderClient.h"
#include "Network/Receiver.h"
#include "Database/DBComponent.h"
#include "Token/TokenList.h"
#include "Canvas/Map.h"

class Map;

// TODO MapCodes dans actions.h
enum class MapCodes : quint16 {
    UNDEFINED = Receiver::UNDEFINED_CODE,

    ADD_SPRITE,
    REMOVE_SPRITE,
    REMOVE_ALL_FOW
};

class MapClient : public SenderClient, public Receiver, public DBComponent
{
    Q_OBJECT

public:
    MapClient(User *user, QHash<QString, User *> *usersList, Database *db, TokenList *tokenList);
    ~MapClient();

    void addMapToList(Map* map);

public slots:
    void sendMessageToServer(const QString& msg);

private:
    TokenList *m_TokenList;
    QList<Map*> m_MapsList;

    void addSpriteAction(const QString& msg);
    void removeSpriteAction(const QString& msg);
    void removeAllFoWAction(const QString& msg);

    Map *GetMapById(int id);

private slots:
    void processNewData(Header header, QByteArray &data);
};

#endif // MAPCLIENT_H
