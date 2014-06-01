#include "FoWLayerRepository.h"

const QString FoWLayerRepository::getTableName() {
    return "fowlayer";
}

int FoWLayerRepository::insertFoWLayer(FoWLayer *fowLayer, Database *db) {
    int id = insertIntoDefault(fowLayer, db);

    return id;
}
