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

// TODO should be in MapRepository
// TODO add openMap menu action in MainWindow
void MapClient::openMapAction(const QString& msg) {
    // Retrieve Map
    int mapId = msg.toInt();
    DBItem mapItem = RepositoryManager::s_MapRepository.findById(mapId, db_);

    // Retrieve & construct BackgroundLayer
    int bgLayerId = mapItem.getHashMap().value("backgroundlayerid").toInt();
    DBItem bgLayerItem = RepositoryManager::s_BgLayerRepository.findById(bgLayerId, db_);
    BackgroundLayer *bgLayer = new BackgroundLayer(bgLayerItem);

    // Retrieve & construct MapLayer
    int mapLayerId = mapItem.getHashMap().value("maplayerid").toInt();
    DBItem mapLayerItem = RepositoryManager::s_MapLayerRepository.findById(mapLayerId, db_);
    MapLayer *mapLayer = new MapLayer(mapLayerItem);

    // Retrieve & construct FoWLayer
    int fowLayerId = mapItem.getHashMap().value("fowlayerid").toInt();
    DBItem fowLayerItem = RepositoryManager::s_FoWLayerRepository.findById(fowLayerId, db_);
    FoWLayer *fowLayer = new FoWLayer(fowLayerItem);

    // Retrieve & construct DrawingLayer
    int drawingLayerId = mapItem.getHashMap().value("drawingLayerId").toInt();
    DBItem drawingLayerItem = RepositoryManager::s_DrawingLayerRepository.findById(drawingLayerId, db_);
    DrawingLayer *drawingLayer = new DrawingLayer(drawingLayerItem);

    // TODO Retrieve Sprites

    // Construct map
    Map *map = new Map(mapItem, bgLayer, mapLayer, fowLayer, drawingLayer);
    addMapToList(map);
    map->setupSenderClient(this);

    // TODO add Map to the tableArea
}

void MapClient::addSpriteAction(const QString& msg) {
    int id = msg.toInt();
    DBItem dbItem = RepositoryManager::s_SpriteRepository.findById(id, db_);

    // Retrieves the TokenItem from its id in the TokenList
    int tokenItemId = dbItem.getHashMap().value("tokenitemid").toInt();
    TokenItem *tokenItem = m_TokenList->findTokenItemById(tokenItemId);

    // Creates the Sprite and adds it to the intended map and layer
    Sprite *sprite;

    if (!m_MapsList.isEmpty()) {
        Map *map = m_MapsList.at(0); // TODO select the correct map

        int mapLayerId = dbItem.getHashMap().value("maplayerid").toInt();
        int fowLayerId = dbItem.getHashMap().value("fowlayerid").toInt();

        GridLayer *layer;
        if (mapLayerId != 0) {
            layer = dynamic_cast<MapLayer*>(map->getMapLayer());
        }
        else if (fowLayerId != 0) {
            layer = dynamic_cast<FoWLayer*>(map->getFoWLayer());
        }
        else {
            return;
        }
        sprite =  new Sprite(dbItem, tokenItem, layer);
        layer->addSpriteToLayer(sprite);

    }
}

void MapClient::removeSpriteAction(const QString& msg) {
    int id = msg.toInt();
    DBItem dbItem = RepositoryManager::s_SpriteRepository.findById(id, db_);

    if (!m_MapsList.isEmpty()) {
        Map *map = m_MapsList.at(0); // TODO select the correct map

        int mapLayerId = dbItem.getHashMap().value("maplayerid").toInt();
        int fowLayerId = dbItem.getHashMap().value("fowlayerid").toInt();

        GridLayer *layer;
        if (mapLayerId != 0) {
            layer = dynamic_cast<GridLayer*>(map->getMapLayer());
        }
        else if (fowLayerId != 0) {
            layer = dynamic_cast<GridLayer*>(map->getFoWLayer());
        }
        else {
            return;
        }

        // Delete the sprite from the database
        RepositoryManager::s_SpriteRepository.deleteById(id, db_);

        // Delete the sprite from the correct layer
        layer->removeSpriteById(id);
    }
}

void MapClient::removeAllFoWAction(const QString&) {
    if (!m_MapsList.isEmpty()) {
        Map *map = m_MapsList.at(0); // TODO select the correct map

        map->getFoWLayer()->removeAllSprites();
    }
}

Map *MapClient::GetMapById(int id) {
    Map *result = NULL;

    for (Map *map : m_MapsList) {
        if (map->id() == id) {
            result = map;
        }
    }

    return result;
}
