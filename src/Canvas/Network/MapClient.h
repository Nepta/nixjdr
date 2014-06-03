#ifndef MAPCLIENT_H
#define MAPCLIENT_H

#include "Network/ClientReceiver.h"
#include "Database/DBComponent.h"
#include "Token/TokenList.h"
#include "Canvas/Map.h"

class Map;

// TODO MapCodes dans action.h
enum class MapCodes : quint16 {
    UNDEFINED = Receiver::UNDEFINED_CODE,

    ADD_SPRITE,
    REMOVE_SPRITE
};

class MapClient : public ClientReceiver, public DBComponent
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

private slots:
    void processNewMessage(Header header, QByteArray &data);
};

#endif // MAPCLIENT_H
