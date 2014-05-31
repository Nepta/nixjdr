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
    qb.select("ti.id, ti.text, ti.path, ti.size, ti.custom, ti.special")
     ->from(getTableName(), "ti");

    return qb;
}

QueryBuilder TokenItemRepository::getNormalTokenItemsQB() {
    QueryBuilder qb = getTokenItemsQB();
    qb.where("ti.special = 0");

    return qb;
}

QueryBuilder TokenItemRepository::getSpecialTokenItemsQB() {
    QueryBuilder qb = getTokenItemsQB();
    qb.where("ti.special = 1");

    return qb;
}

/**
 * @brief TokenItemRepository::getTokenItems Retrieve all the TokenItems from the database and store
 * them in a QList of TokenItem.
 * @param db The database in which the TokenItems will be retrieved.
 * @return QList of TokenItem
 */
QList<TokenItem*> TokenItemRepository::getTokenItems(Database *db) {
    QueryBuilder qb = getNormalTokenItemsQB();
    DBItemList<TokenItem> dbItems(db->pull(qb));
    QList<TokenItem*> tokenItems = dbItems.construct();

    return tokenItems;
}

/**
 * @brief TokenItemRepository::getFowTokenItem Retrieve the fog of war TokenItem from the database.
 * @param db
 * @return Fog of war TokenItem
 */
TokenItem* TokenItemRepository::getFowTokenItem(Database *db) {
    QueryBuilder qb = getSpecialTokenItemsQB();
    qb.andWhere("ti.text = 'fow'");

    DBItem dbItem = db->pullFirst(qb);
    TokenItem* tokenItem = new TokenItem(dbItem);

    return tokenItem;
}

QueryBuilder TokenItemRepository::insertTokenItemQB(TokenItem *tokenItem) {
    QList<QString> args;
    args.append(tokenItem->text());
    args.append(tokenItem->path());
    args.append(QString::number(tokenItem->size()));
    args.append(QString::number(tokenItem->isCustom()));
    args.append(QString::number(tokenItem->isSpecial()));

    QueryBuilder qb;
    qb.insertInto(getTableName(), "text, path, size, custom, special")->values(args);

    return qb;
}

/**
 * @brief TokenItemRepository::insertTokenItem Inserts the given TokenItem in the database, retrieve
 * the id given by the db to the new row and sets it on the TokenItem.
 * @param tokenItem TokenItem which will be inserted in the db.
 * @param db
 * @return Id given by the database to the newly inserted row.
 */
int TokenItemRepository::insertTokenItem(TokenItem *tokenItem, Database *db) {
    QueryBuilder qb = insertTokenItemQB(tokenItem);
    int id = db->pushWithId(qb);
    tokenItem->setId(id);

    return id;
}
