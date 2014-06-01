#include <QStringList>

#include "TokenItemRepository.h"

/**
 * @brief TokenItemRepository::getTableName Retrieve the table name associated with this Repository.
 * @return table name
 */
const QString TokenItemRepository::getTableName() {
    return "tokenitem";
}

QueryBuilder TokenItemRepository::getNormalTokenItemsQB() {
    QueryBuilder qb = findAllQB();
    qb.where("special = false");

    return qb;
}

QueryBuilder TokenItemRepository::getSpecialTokenItemsQB() {
    QueryBuilder qb = findAllQB();
    qb.where("special = true");

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
    DBItemList<TokenItem> dbItems(db->pull(qb.getQuery()));
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
    qb.andWhere("text = 'fow'");

    DBItem dbItem = db->pullFirst(qb.getQuery());
    TokenItem* tokenItem = new TokenItem(dbItem);

    return tokenItem;
}

/**
 * @brief TokenItemRepository::insertTokenItem Inserts the given TokenItem in the database, retrieve
 * the id given by the db to the new row and sets it on the TokenItem.
 * @param tokenItem TokenItem which will be inserted in the db.
 * @param db
 * @return Id given by the database to the newly inserted row.
 */
int TokenItemRepository::insertTokenItem(TokenItem *tokenItem, Database *db) {
    QHash<QString, QVariant> args {
        {"text", tokenItem->text()},
        {"path", tokenItem->path()},
        {"size", tokenItem->size()},
        {"custom", tokenItem->isCustom()},
        {"special", tokenItem->isSpecial()}
    };

    QueryBuilder qb = insertQB(args.keys());
    int id = insert(tokenItem, qb, args, db);

    return id;
}
