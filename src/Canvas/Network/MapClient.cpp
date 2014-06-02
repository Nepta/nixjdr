#include "Database/Repository/RepositoryManager.h"
#include "Network/Switch.h"
#include "Chat/Message.h"
#include "MapClient.h"
#include "Common.h"

MapClient::MapClient(User *user, QHash<QString, User *> *usersList, Database *db, TokenList *tokenList) :
    ClientReceiver(user, usersList),
    DBComponent(db)
{
    m_TokenList = tokenList;
}

MapClient::~MapClient() {}

void MapClient::processNewMessage(Header header, QByteArray& data) {
    Message msg(data);

    if ((MapCodes) header.getCode() == MapCodes::ADD_SPRITE) {
        addSpriteAction(msg.getString());
    }
}

void MapClient::sendMessageToServer(const QString& msg) {
    QString strippedMsg = msg;
    QString action = Common::extractFirstWord(strippedMsg);
    Message message(strippedMsg);

    if (action == "addSprite") {
        TargetCode target = TargetCode::MAP_SERVER;
        quint16 mapCode = (quint16) MapCodes::ADD_SPRITE;

        sendPacketToServer(mapCode, (quint16) target, message);
    }
}

void MapClient::addMapToList(Map* map) {
    m_MapsList.append(map);
}

void MapClient::addSpriteAction(const QString& msg) {
    int id = msg.toInt();
    DBItem dbItem = RepositoryManager::s_SpriteRepository.findById(id, db_);

    // Retrieves the TokenItem from its id in the TokenList
    int tokenItemId = dbItem.getHashMap().value("tokenitemid").toInt();
    TokenItem *tokenItem = m_TokenList->findTokenItemById(tokenItemId);

    // Creates the Sprite and adds it to the intended map and layer
    Sprite *sprite;
    GridLayer *layer;
    Map *map = m_MapsList.at(0); // TODO select the correct map
    if (dbItem.getHashMap().contains("maplayerid")) {
        layer = dynamic_cast<GridLayer*>(map->getMapLayer());
        sprite = new Sprite(dbItem, tokenItem,layer);
    } else {
        layer = dynamic_cast<GridLayer*>(map->getFoWLayer());
        sprite =  new Sprite(dbItem, tokenItem, layer);
    }
    layer->addSpriteFromDb(sprite);
}
