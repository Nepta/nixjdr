#include "MapLayerRepository.h"

const QString MapLayerRepository::getTableName() {
    return "maplayer";
}

int MapLayerRepository::insertMapLayer(MapLayer *mapLayer, Database *db) {
    QHash<QString, QVariant> args {
        {"step", mapLayer->getStep()}
    };

    QueryBuilder qb = insertQB(args.keys());
    int id = insert(mapLayer, qb, args, db);

    return id;
}
