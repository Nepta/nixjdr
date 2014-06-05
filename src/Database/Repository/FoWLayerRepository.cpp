#include "FoWLayerRepository.h"

const QString FoWLayerRepository::getTableName() {
    return "fowlayer";
}

int FoWLayerRepository::insertFoWLayer(FoWLayer *fowLayer, Database *db) {
    QHash<QString, QVariant> args {
        {"step", fowLayer->getStep()}
    };

    QueryBuilder qb = insertQB(args.keys());
    int id = insert(fowLayer, qb, args, db);

    return id;
}
