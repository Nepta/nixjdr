#include "Database/Repository/RepositoryManager.h"
#include "Network/Serializable/Message.h"
#include "Network/Switch.h"
#include "MapClient.h"
#include "Common.h"

MapClient::MapClient(User *user, QHash<QString, User *> *usersList, Database *db, TokenList *tokenList) :
    SenderClient(user, usersList),
    DBComponent(db)
{
    m_TokenList = tokenList;
}

MapClient::~MapClient() {}

void MapClient::processNewData(Header header, QByteArray& data) {
    Message msg(data);
    MapCodes code = (MapCodes) header.getCode();

    if (code == MapCodes::OPEN_MAP) {
        openMapAction(msg.getString());
    }
    else if (code == MapCodes::ADD_SPRITE) {
        addSpriteAction(msg.getString());
    }
    else if (code == MapCodes::REMOVE_SPRITE) {
        removeSpriteAction(msg.getString());
    }
    else if (code == MapCodes::REMOVE_ALL_FOW) {
        removeAllFoWAction(msg.getString());
    }
}

void MapClient::sendMessageToServer(const QString& msg) {
    QString strippedMsg = msg;
    QString action = Common::extractFirstWord(strippedMsg);
    Message message(strippedMsg);

    TargetCode target = TargetCode::MAP_SERVER;
    quint16 mapCode;

    if (action == "openMap") {
        mapCode = (quint16) MapCodes::OPEN_MAP;
    }
    else if (action == "addSprite") {
        mapCode = (quint16) MapCodes::ADD_SPRITE;
    }
    else if (action == "removeSprite") {
        mapCode = (quint16) MapCodes::REMOVE_SPRITE;
    }
    else if (action == "removeAllFoW") {
        mapCode = (quint16) MapCodes::REMOVE_ALL_FOW;
    }

    sendPacketToServer(mapCode, (quint16) target, message);
}

void MapClient::addMapToList(Map* map) {
    m_MapsList.append(map);
}

void MapClient::openMapAction(const QString& msg) {
    int mapId = msg.toInt();
    Map *map = RepositoryManager::s_MapRepository.findMapById(mapId, db_);
    map->getMapLayer()->setTokenItem(m_TokenList->currentItem());

    emit openMap(map);
}

void MapClient::addSpriteAction(const QString& msg) {
    int id = msg.toInt();
    DBItem dbItem = RepositoryManager::s_SpriteRepository.findById(id, db_);

    // Retrieves the TokenItem from its id in the TokenList
    int tokenItemId = dbItem.getHashMap().value("tokenitemid").toInt();
    TokenItem *tokenItem = m_TokenList->findTokenItemById(tokenItemId);

    // Retrieve the map and the layer on which the sprite should be added
    Map *map = NULL;
    GridLayer *layer = NULL;

    int mapLayerId = dbItem.getHashMap().value("maplayerid").toInt();
    int fowLayerId = dbItem.getHashMap().value("fowlayerid").toInt();

    if (mapLayerId != 0) {
        map = getMapByMapLayerId(mapLayerId);
        layer = dynamic_cast<GridLayer*>(map->getMapLayer());
    }
    else if (fowLayerId != 0) {
        map = getMapByFoWLayerId(fowLayerId);
        layer = dynamic_cast<GridLayer*>(map->getFoWLayer());
    }

    // Creates the Sprite and adds it to the intended map and layer
    if (map != NULL) {
        Sprite *sprite = new Sprite(dbItem, tokenItem, layer);
        layer->addSpriteToLayer(sprite);
    }
}

void MapClient::removeSpriteAction(const QString& msg) {
    int id = msg.toInt();
    DBItem dbItem = RepositoryManager::s_SpriteRepository.findById(id, db_);

    // Retrieve the map and the layer on which the sprite should be deleted
    Map *map = NULL;
    GridLayer *layer = NULL;

    int mapLayerId = dbItem.getHashMap().value("maplayerid").toInt();
    int fowLayerId = dbItem.getHashMap().value("fowlayerid").toInt();

    if (mapLayerId != 0) {
        map = getMapByMapLayerId(mapLayerId);
        layer = dynamic_cast<GridLayer*>(map->getMapLayer());
    }
    else if (fowLayerId != 0) {
        map = getMapByFoWLayerId(fowLayerId);
        layer = dynamic_cast<GridLayer*>(map->getFoWLayer());
    }

    // Delete the sprite
    if (map != NULL) {
        // Delete the sprite from the database
        RepositoryManager::s_SpriteRepository.deleteById(id, db_);

        // Delete the sprite from the correct layer
        layer->removeSpriteById(id);
    }
}

void MapClient::removeAllFoWAction(const QString& msg) {
    int fowLayerId = msg.toInt();
    Map *map = getMapByFoWLayerId(fowLayerId);

    if (map != NULL) {
        map->getFoWLayer()->removeAllSprites();
    }
}

Map *MapClient::getMapById(int mapId) {
    Map *result = NULL;

    for (Map *map : m_MapsList) {
        if (map->id() == mapId) {
            result = map;
        }
    }

    return result;
}

Map *MapClient::getMapByMapLayerId(int mapLayerId) {
    Map *result = NULL;

    for (Map *map : m_MapsList) {
        if (map->getMapLayer()->id() == mapLayerId) {
            result = map;
        }
    }

    return result;
}

Map *MapClient::getMapByFoWLayerId(int fowLayerId) {
    Map *result = NULL;

    for (Map *map : m_MapsList) {
        if (map->getFoWLayer()->id() == fowLayerId) {
            result = map;
        }
    }

    return result;
}
