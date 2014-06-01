#include "MapRepository.h"

const QString MapRepository::getTableName() {
    return "map";
}

QueryBuilder MapRepository::insertMapQB(Map *map) {
    QList<QString> args;
    args.append(QString::number(map->getSceneHeight()));
    args.append(QString::number(map->getSceneWidth()));
    args.append(QString::number(map->getBgLayer()->id()));
    args.append(QString::number(map->getMapLayer()->id()));
    args.append(QString::number(map->getFoWLayer()->id()));
    args.append(QString::number(map->getDrawingLayer()->id()));

    QueryBuilder qb;
    qb.insertInto(
        getTableName(),
        "sceneHeight, sceneWidth, backgroundlayerid, maplayerid, fowlayerid, drawinglayerid"
    )->values(args);

    return qb;
}

int MapRepository::insertMap(Map *map, Database *db) {
    QueryBuilder qb = insertMapQB(map);
    int id = insert(map, qb, db);

    return id;
}