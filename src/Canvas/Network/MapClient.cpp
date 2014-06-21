#include "Database/Repository/RepositoryManager.h"
#include "Network/Serializable/Message.h"
#include "Network/Switch.h"
#include "Canvas/Tools/ToolPing.h"
#include "Canvas/Layers/LayerType.h"
#include "MapClient.h"
#include "Common.h"

MapClient::MapClient(User *user, QHash<QString, User *> *usersList, TokenList *tokenList) :
    SenderClient(user, usersList)
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
    else if (code == MapCodes::ADD_ALL_FOW) {
        addAllFoWAction(msg.getString());
    }
    else if (code == MapCodes::UPDATE_DRAWING_LAYER_PIXMAP) {
        updateDrawingLayerPixmapAction(msg.getString());
    }
    else if (code == MapCodes::PING) {
        pingAction(msg.getString());
    }
}

void MapClient::sendMessageToServer(const QString& msg, quint16 code) {
    Message message(msg);
    TargetCode target = TargetCode::MAP_SERVER;

    sendPacketToServer(code, (quint16) target, message);
}

void MapClient::addMapToList(Map* map) {
    m_MapsList.append(map);
}

void MapClient::removeMapFromList(Map *map) {
    m_MapsList.removeOne(map);
}

/**
 * @brief MapClient::openMapAction Opens a map with the given id.
 * @param msg QString containing the id of the map to open.
 */
void MapClient::openMapAction(const QString& msg) {
    int mapId = msg.toInt();

    // If the map has already been opened, don't open it again
    if (containsMap(mapId)) {
        return;
    }

    Map *map = RepositoryManager::s_MapRepository.findMapById(mapId, m_TokenList,
                                                              this->m_User->getRole());
    map->getMapLayer()->setTokenItem(m_TokenList->currentItem());

    emit openMap(map);
}

void MapClient::addSpriteAction(const QString& msg) {
    int id = msg.toInt();
    DBItem dbItem = RepositoryManager::s_SpriteRepository.findById(id);

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
        if (map != NULL) {
            layer = dynamic_cast<GridLayer*>(map->getMapLayer());
        }
    }
    else if (fowLayerId != 0) {
        map = getMapByFoWLayerId(fowLayerId);
        if (map != NULL) {
            layer = dynamic_cast<GridLayer*>(map->getFoWLayer());
        }
    }

    // Creates the Sprite and adds it to the intended map and layer
    if (map != NULL) {
        Sprite *sprite = new Sprite(dbItem, tokenItem, layer);
        layer->addSpriteToLayer(sprite);
    }
}

void MapClient::removeSpriteAction(const QString& msg) {
    QString temp = msg;
    int spriteId = Common::extractFirstWord(temp).toInt();
    int layerId = Common::extractFirstWord(temp).toInt();
    LayerType layerType = (LayerType) Common::extractFirstWord(temp).toInt();

    // Retrieve the map and the layer on which the sprite should be deleted
    Map *map = NULL;
    GridLayer *layer = NULL;

    if (layerType == LayerType::MAP_LAYER) {
        map = getMapByMapLayerId(layerId);
        if (map != NULL) {
            layer = dynamic_cast<GridLayer*>(map->getMapLayer());
        }
    }
    else if (layerType == LayerType::FOW_LAYER) {
        map = getMapByFoWLayerId(layerId);
        if (map != NULL) {
            layer = dynamic_cast<GridLayer*>(map->getFoWLayer());
        }
    }

    // Delete the sprite
    if (map != NULL) {
        // Delete the sprite from the correct layer
        layer->removeSpriteById(spriteId);
    }
}

void MapClient::removeAllFoWAction(const QString& msg) {
    int fowLayerId = msg.toInt();
    Map *map = getMapByFoWLayerId(fowLayerId);

    if (map != NULL) {
        map->getFoWLayer()->removeAllSprites();
    }
}

void MapClient::addAllFoWAction(const QString& msg) {
    QString temp = msg;
    int fowLayerId = Common::extractFirstWord(temp).toInt();
    int firstId = Common::extractFirstWord(temp).toInt();
    int lastId = Common::extractFirstWord(temp).toInt();

    // Retrieves the FoW TokenItem from its name
    TokenItem *tokenItem = m_TokenList->findTokenItemByName("fow");

    Map *map = getMapByFoWLayerId(fowLayerId);

    if (map != NULL) {
        for (int i = firstId ; i <= lastId ; i++) {
            if (map != NULL) {
                DBItem dbItem = RepositoryManager::s_SpriteRepository.findById(i);

                FoWLayer *layer = map->getFoWLayer();

                // Creates the Sprite and adds it to the intended map and layer
                Sprite *sprite = new Sprite(dbItem, tokenItem, layer);
                layer->addSpriteToLayer(sprite);
            }
        }
    }
}

void MapClient::updateDrawingLayerPixmapAction(const QString& msg) {
    int drawingLayerId = msg.toInt();
    Map *map = getMapByDrawingLayerId(drawingLayerId);

    if (map != NULL) {
        // Retrieve pixmap from the DrawingLayer stored in the Db
        DBItem dbItem = RepositoryManager::s_DrawingLayerRepository.findById(drawingLayerId);
        QByteArray pixmapData = dbItem.getHashMap().value("pixmap").toByteArray();
        QPixmap *pixmap = new QPixmap;
        pixmap->loadFromData(pixmapData, "PNG");

        // Sets the new pixmap to the DrawingLayer
        map->getDrawingLayer()->setPixmap(pixmap);
        map->getDrawingLayer()->updateDisplay();
    }
}

void MapClient::pingAction(const QString& msg) {
    QString temp = msg;
    int drawingLayerId = Common::extractFirstWord(temp).toInt();
    qreal x = Common::extractFirstWord(temp).toDouble();
    qreal y = Common::extractFirstWord(temp).toDouble();

     Map *map = getMapByDrawingLayerId(drawingLayerId);
    if (map != NULL) {
        ToolPing *toolPing = dynamic_cast<ToolPing*>(
            map->getDrawingLayer()->getTools()->getTool(ToolCodes::TOOL_PING)
        );
        toolPing->ping(QPointF(x, y));
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

/**
 * @brief MapClient::containsMap Returns whether the list of maps contains the map specified
 * in parameter (id of the map).
 * @param mapId Id of the map to verify.
 * @return true if the map is contained in the list, false otherwise.
 */
bool MapClient::containsMap(int mapId) {
    if (getMapById(mapId) != NULL) {
        return true;
    }
    else {
        return false;
    }
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

Map *MapClient::getMapByDrawingLayerId(int drawingLayerId) {
    Map *result = NULL;

    for (Map *map : m_MapsList) {
        if (map->getDrawingLayer()->id() == drawingLayerId) {
            result = map;
        }
    }

    return result;
}
