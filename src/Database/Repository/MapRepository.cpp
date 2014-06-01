#include "MapRepository.h"

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
