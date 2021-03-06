#include <QStringList>

#include "Token/TokenList.h"
#include "MapRepository.h"
#include "RepositoryManager.h"

const QString MapRepository::getTableName() {
    return "map";
}

int MapRepository::insertMap(Map *map) {
    QHash<QString, QVariant> args {
        {"windowtitle", map->windowTitle()},
        {"sceneheight", map->getSceneHeight()},
        {"scenewidth", map->getSceneWidth()},
        {"isimage", map->getIsImage()},
        {"backgroundlayerid", map->getBgLayer()->id()},
        {"maplayerid", map->getMapLayer()->id()},
        {"fowlayerid", map->getFoWLayer()->id()},
        {"drawinglayerid", map->getDrawingLayer()->id()}
    };

    QueryBuilder qb = insertQB(args.keys());
    int id = insert(map, qb, args);

    return id;
}

/**
 * @brief MapRepository::findMapById Retrieve a complete Map from the database by its id.
 * @param id Map's id
 * @return Map
 */
Map *MapRepository::findMapById(int id, TokenList *tokenList, Role userRole) {
    DBItem mapItem = RepositoryManager::s_MapRepository.findById(id);

    // Define whether the user is Mj or not
    bool isMj = (userRole == Role::ROLE_MJ);

    // Retrieve & construct BackgroundLayer
    int bgLayerId = mapItem.getHashMap().value("backgroundlayerid").toInt();
    DBItem bgLayerItem = RepositoryManager::s_BgLayerRepository.findById(bgLayerId);
    BackgroundLayer *bgLayer = new BackgroundLayer(bgLayerItem);

    // Retrieve & construct MapLayer
    int mapLayerId = mapItem.getHashMap().value("maplayerid").toInt();
    DBItem mapLayerItem = RepositoryManager::s_MapLayerRepository.findById(mapLayerId);
    MapLayer *mapLayer = new MapLayer(mapLayerItem);

    // Retrieve & construct FoWLayer
    int fowLayerId = mapItem.getHashMap().value("fowlayerid").toInt();
    DBItem fowLayerItem = RepositoryManager::s_FoWLayerRepository.findById(fowLayerId);
    FoWLayer *fowLayer = new FoWLayer(fowLayerItem, isMj);

    // Retrieve & construct DrawingLayer
    int drawingLayerId = mapItem.getHashMap().value("drawinglayerid").toInt();
    DBItem drawingLayerItem = RepositoryManager::s_DrawingLayerRepository.findById(drawingLayerId);
    DrawingLayer *drawingLayer = new DrawingLayer(drawingLayerItem);

    // Construct map
    Map *map = new Map(mapItem, bgLayer, mapLayer, fowLayer, drawingLayer, isMj);

    // Retrieve Sprites
    RepositoryManager::s_SpriteRepository.getMapSprites(tokenList, mapLayer);
    RepositoryManager::s_SpriteRepository.getFoWSprites(tokenList, fowLayer);

    return map;
}
