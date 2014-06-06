#include "FoWLayerRepository.h"

const QString FoWLayerRepository::getTableName() {
    return "fowlayer";
}

int FoWLayerRepository::insertFoWLayer(FoWLayer *fowLayer) {
    QHash<QString, QVariant> args {
        {"step", fowLayer->getStep()}
    };

    QueryBuilder qb = insertQB(args.keys());
    int id = insert(fowLayer, qb, args);

    return id;
}
