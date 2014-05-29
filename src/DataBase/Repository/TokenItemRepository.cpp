#include "TokenItemRepository.h"

const QString TokenItemRepository::getTableName() {
    return "tokenitem";
}

QueryBuilder TokenItemRepository::getTokenItems() {
    QueryBuilder qb;
    qb.select("ti.id, ti.name, ti.path, ti.size")
     ->from(getTableName(), "ti");

    return qb;
}
