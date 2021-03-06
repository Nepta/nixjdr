#include "Repository.h"

/**
 * @brief Repository::findByIdQB Constructs a query to find one row by its id from the child's
 * repository associated table.
 * @param id Id of the row to find.
 * @return QueryBuilder
 */
QueryBuilder Repository::findByIdQB(int id) {
    QueryBuilder qb;

    qb.select("*")
    ->from(getTableName())
    ->where("id = " + QString::number(id));

    return qb;
}

QueryBuilder Repository::deleteByIdQb(int id) {
    QueryBuilder qb;
    qb.deleteFrom(getTableName())
     ->where("id = " + QString::number(id));

    return qb;
}

/**
 * @brief Repository::findAllQB Constructs a query to retrieve all the rows from the child's
 * Repository associated table.
 * @return QueryBuilder
 */
QueryBuilder Repository::findAllQB() {
    QueryBuilder qb;
    qb.select("*")->from(getTableName());

    return qb;
}

/**
 * @brief Repository::insertQB Constructs a query to insert a row in the child's Repository
 * associated table.
 * @param cols Columns for which values will be inserted.
 * @return QueryBuilder
 */
QueryBuilder Repository::insertQB(QList<QString> cols) {
    QueryBuilder qb;
    qb.insertInto(getTableName(), QStringList(cols));

    return qb;
}

/**
 * @brief Repository::updateByIdQB Constructs a query to update a row identified by its ID in the
 * child's Repository associated table.
 * @param id Id of the row to update.
 * @param cols Columns to update.
 */
QueryBuilder Repository::updateByIdQB(int id, QList<QString> cols) {
    QueryBuilder qb;
    qb.update(getTableName(), QStringList(cols));
    qb.where("id = " + QString::number(id));

    return qb;
}

/**
 * @brief Repository::findById Constructs a query to find a row by its ID in the child's Repository
 * associated table.
 * @param id Id of the row to find.
 * @return DBItem filled with the retrieved row columns.
 */
DBItem Repository::findById(int id) {
    QueryBuilder qb = findByIdQB(id);

    DBItem dbItem = Database::instance()->pullFirst(qb.getQuery());
    return dbItem;
}

/**
 * @brief Repository::updateById Updates the row associated with the given id in the database. The
 * new values are in the pBindValues Qhash.
 * @param id Id of the row to update.
 * @param pBindValues Columns to update with their new values.
 */
void Repository::updateById(int id, QHash<QString, QVariant> pBindValues) {
    QueryBuilder qb = updateByIdQB(id, pBindValues.keys());
    QSqlQuery query = qb.getPreparedQuery();

    bindValues(&query, pBindValues);

    Database::instance()->push(query);
}

/**
 * @brief Repository::insert Inserts a row in the database with the query given by the QueryBuilder
 * (qb) and the given bind values (pBindValues). Retrieves the id of the inserted row and sets it on
 * the DBItem.
 * @param item Item associated with the inserted row in the database which will be given an id once
 * the insertion is successful.
 * @param qb QueryBuilder holding the query which will be executed.
 * @param pBindValues Holds the values to be bound with the request.
 * @param db Database
 * @return Id of the inserted row.
 */
int Repository::insert(DBItem *item, QueryBuilder qb, QHash<QString, QVariant> pBindValues)
{
    qb.withAsSelect(qb, "id");
    QSqlQuery query = qb.getPreparedQuery();
    bindValues(&query, pBindValues);

    int id = Database::instance()->pushPreparedWithId(query);
    item->setId(id);

    return id;
}

int Repository::insertIntoDefault(DBItem *item) {
    QueryBuilder qb;
    qb.insertIntoDefault(getTableName());
    qb.withAsSelect(qb, "id");
    QSqlQuery query = qb.getQuery();

    int id = Database::instance()->pushWithId(query);
    item->setId(id);

    return id;
}

void Repository::deleteById(int id) {
    QueryBuilder qb = deleteByIdQb(id);

    Database::instance()->push(qb.getQuery());
}

/**
 * @brief Repository::bindValues Bind all the placeholders to their values in the given query.
 * @param query Query for which values will be bound.
 * @param args QHash associating a value to a placeholder.
 */
void Repository::bindValues(QSqlQuery *query, QHash<QString, QVariant> bindValues) {
    for (QString placeholder : bindValues.keys()) {
        bindValue(query, placeholder, bindValues.value(placeholder));
    }
}

/**
 * @brief Repository::bindValue Convenience method which adds the suffix ":" to the placeholder
 * before binding the value.
 * @param query
 * @param placeholder
 * @param val
 */
void Repository::bindValue(QSqlQuery *query, const QString& placeholder, const QVariant& val) {
    query->bindValue(":" + placeholder, val);
}

/**
 * @brief Repository::isEmpty Verifies if the table is empty.
 * @return Return whether the table associated with the inherithing Repository is empty or not.
 */
bool Repository::isEmpty() {
    QueryBuilder qb;
    qb.select("count(*) AS rows")
      ->from(getTableName());

    DBItem dbItem = Database::instance()->pullFirst(qb.getQuery());

    int rowCount = dbItem.getHashMap().value("rows").toInt();

    return (rowCount == 0);
}
