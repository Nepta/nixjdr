#include "BackgroundLayerRepository.h"

const QString BackgroundLayerRepository::getTableName() {
    return "backgroundlayer";
}

int BackgroundLayerRepository::insertBgLayer(BackgroundLayer *bgLayer) {
    QHash<QString, QVariant> args {
        {"pixmap", bgLayer->getBackgroundData()}
    };

    QueryBuilder qb = insertQB(args.keys());
    int id = insert(bgLayer, qb, args);

    return id;
}
