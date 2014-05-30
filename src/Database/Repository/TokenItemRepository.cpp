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
    qb.select("ti.id, ti.text, ti.path, ti.size")
     ->from(getTableName(), "ti");

    return qb;
}

/**
 * @brief TokenItemRepository::getTokenItems Retrieve all the TokenItems from the database and store
 * them in a QList of TokenItem.
 * @param db The database in which the TokenItems will be retrieved.
 * @return QList of TokenItem
 */
QList<TokenItem*> TokenItemRepository::getTokenItems(Database *db) {
    QueryBuilder qb = getTokenItemsQB();
    DBItemList<TokenItem> dbItems(db->pull(qb));
    QList<TokenItem*> tokenItems = dbItems.construct();

    return tokenItems;
}

QueryBuilder TokenItemRepository::insertTokenItemQB(TokenItem *tokenItem) {
    QList<QString> args;
    args.append(tokenItem->text());
    args.append(tokenItem->path());
    args.append(QString::number(tokenItem->size()));

    QueryBuilder qb;
    qb.insertInto(getTableName(), "text, path, size")->values(args);

    return qb;
}

int TokenItemRepository::insertTokenItem(TokenItem *tokenItem, Database *db) {
    QueryBuilder qb = insertTokenItemQB(tokenItem);
    int id = db->pushWithId(qb);

    return id;
}
