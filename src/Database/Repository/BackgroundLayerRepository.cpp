#include "BackgroundLayerRepository.h"

const QString BackgroundLayerRepository::getTableName() {
    return "backgroundlayer";
}

int BackgroundLayerRepository::insertBgLayer(BackgroundLayer *bgLayer, Database *db) {
    /* TODO
    QHash<QString, QVariant> args {
        {"pixmap", *bgLayer->getBackground()}
    };


    QueryBuilder qb = insertQB(args.keys());
    int id = insert(bgLayer, qb, args, db);
    */

    int id = insertIntoDefault(bgLayer, db);

    return id;
}
