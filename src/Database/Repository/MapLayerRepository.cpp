#include "MapLayerRepository.h"

const QString MapLayerRepository::getTableName() {
    return "maplayer";
}

QueryBuilder MapLayerRepository::insertMapLayerQB(MapLayer *) {
    QueryBuilder qb;
    qb.insertIntoDefault(getTableName());

    return qb;
}

int MapLayerRepository::insertMapLayer(MapLayer *mapLayer, Database *db) {
    QueryBuilder qb = insertMapLayerQB(mapLayer);
    int id = insert(mapLayer, qb, db);

    return id;
}
