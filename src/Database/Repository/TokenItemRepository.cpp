#include "TokenItemRepository.h"

/**
 * @brief TokenItemRepository::getTableName Retrieve the table name associated with this Repository.
 * @return table name
 */
const QString TokenItemRepository::getTableName() {
    return "tokenitem";
}

/**
 * @brief TokenItemRepository::getTokenItemsQB Constructs a query with the QueryBuilder to retrieve
 * the TokenItems from the database.
 * @return QueryBuilder
 */
QueryBuilder TokenItemRepository::getTokenItemsQB() {
    QueryBuilder qb;
    qb.select("ti.id, ti.name, ti.path, ti.size")
     ->from(getTableName(), "ti");

    return qb;
}

/**
 * @brief TokenItemRepository::getTokenItems Retrieve all the TokenItems from the database and store
 * them in a QList of TokenItem.
 * @param db The database in which the TokenItems will be retrieved.
 * @return QList of TokenItem
 */
QList<TokenItem> TokenItemRepository::getTokenItems(Database *db) {
    QueryBuilder qb = TokenItemRepository::getTokenItemsQB();
    DBItemList<TokenItem> dbItems(db->pull(qb));
    QList<TokenItem> tokenItems = dbItems.construct();

    return tokenItems;
}
