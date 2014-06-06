#include "MapRepository.h"
#include "RepositoryManager.h"

const QString MapRepository::getTableName() {
    return "map";
}

int MapRepository::insertMap(Map *map, Database *db) {
    QHash<QString, QVariant> args {
        {"sceneheight", map->getSceneHeight()},
        {"scenewidth", map->getSceneWidth()},
        {"backgroundlayerid", map->getBgLayer()->id()},
        {"maplayerid", map->getMapLayer()->id()},
        {"fowlayerid", map->getFoWLayer()->id()},
        {"drawinglayerid", map->getDrawingLayer()->id()}
    };

    QueryBuilder qb = insertQB(args.keys());
    int id = insert(map, qb, args, db);

    return id;
}

/**
 * @brief MapRepository::findMapById Retrieve a complete Map from the database by its id.
 * @param id Map's id
 * @return Map
 */
Map *MapRepository::findMapById(int id, Database *db) {
    DBItem mapItem = RepositoryManager::s_MapRepository.findById(id, db);

    // Retrieve & construct BackgroundLayer
    int bgLayerId = mapItem.getHashMap().value("backgroundlayerid").toInt();
    DBItem bgLayerItem = RepositoryManager::s_BgLayerRepository.findById(bgLayerId, db);
    BackgroundLayer *bgLayer = new BackgroundLayer(bgLayerItem);

    // Retrieve & construct MapLayer
    int mapLayerId = mapItem.getHashMap().value("maplayerid").toInt();
    DBItem mapLayerItem = RepositoryManager::s_MapLayerRepository.findById(mapLayerId, db);
    MapLayer *mapLayer = new MapLayer(mapLayerItem);

    // Retrieve & construct FoWLayer
    int fowLayerId = mapItem.getHashMap().value("fowlayerid").toInt();
    DBItem fowLayerItem = RepositoryManager::s_FoWLayerRepository.findById(fowLayerId, db);
    FoWLayer *fowLayer = new FoWLayer(fowLayerItem);

    // Retrieve & construct DrawingLayer
    int drawingLayerId = mapItem.getHashMap().value("drawinglayerid").toInt();
    DBItem drawingLayerItem = RepositoryManager::s_DrawingLayerRepository.findById(drawingLayerId, db);
    DrawingLayer *drawingLayer = new DrawingLayer(drawingLayerItem);

    // TODO Retrieve Sprites

    // Construct map
    Map *map = new Map(mapItem, bgLayer, mapLayer, fowLayer, drawingLayer);

    return map;
}
