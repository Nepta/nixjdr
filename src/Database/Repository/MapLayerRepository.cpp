#include "MapLayerRepository.h"

const QString MapLayerRepository::getTableName() {
    return "maplayer";
}

int MapLayerRepository::insertMapLayer(MapLayer *mapLayer, Database *db) {
    int id = insertIntoDefault(mapLayer, db);

    return id;
}
