#include "Repository.h"

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
int Repository::insert(DBItem *item, QueryBuilder qb, QHash<QString, QVariant> pBindValues,
    Database *db)
{
    qb.withAsSelect(qb, "id");
    QSqlQuery query = qb.getPreparedQuery();
    bindValues(&query, pBindValues);

    int id = db->pushPreparedWithId(query);
    item->setId(id);

    return id;
}

int Repository::insertIntoDefault(DBItem *item, Database *db) {
    QueryBuilder qb;
    qb.insertIntoDefault(getTableName());
    qb.withAsSelect(qb, "id");
    QSqlQuery query = qb.getQuery();

    int id = db->pushWithId(query);
    item->setId(id);

    return id;
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
