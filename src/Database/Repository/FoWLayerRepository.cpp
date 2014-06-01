#include "FoWLayerRepository.h"

const QString FoWLayerRepository::getTableName() {
    return "fowlayer";
}

QueryBuilder FoWLayerRepository::insertFoWLayerQB(FoWLayer *) {
    QueryBuilder qb;
    qb.insertIntoDefault(getTableName());

    return qb;
}

int FoWLayerRepository::insertFoWLayer(FoWLayer *fowLayer, Database *db) {
    QueryBuilder qb = insertFoWLayerQB(fowLayer);
    int id = insert(fowLayer,  qb, db);

    return id;
}
